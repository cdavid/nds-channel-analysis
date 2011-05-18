#include <iostream>
#include <fstream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <string.h>
#include <complex>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <limits>


using namespace std;

string itoa (int a) {
  stringstream out;
  out << a;
  return out.str();
}

double db_water (double p) {
  return 20 * log10( p );
}

/**
 * Function used to generate noise, given a frequency
 * f - double, input frequency (kHz)
 * returns N - noise (dB micro Pa / Hz)
 */
double gen_noise(double f) {
  double s = 0.5, w = 0;
  double turbulence,ship,wind,thermal, N;

  turbulence = 17 - 30 * log10(f);
  turbulence = pow(10, turbulence * 0.1);

  ship = 40 + 20 * (s - 0.5) + 26 * log10(f) - 60 * log10(f + 0.03);
  ship = pow(10.0, (ship * 0.1));

  wind = pow(50 + 7.5 * w, 0.5) + 20 * log10(f) - 40 * log10(f + 0.4);
  wind = pow(10.0, (wind * 0.1));

  thermal = -15 + 20 * log10(f);
  thermal = pow(10.0,(thermal * 0.1));

  N = 20 * log10(turbulence + ship + wind + thermal);
  return N;
}

int main(int argc, char** argv) {
  if (argc != 2) {
    return 1;
  }
  string ARG1 (argv[1]);
  const string INDEX (ARG1.substr(ARG1.length()-5,1)); //HARDCODED VALUE... we assume
	    // a filename of type FREQ_Bathymetry.arr
  //  cerr<<"Opening file "<<argv[1]<<endl;
  ifstream in;
  in.open (ARG1.c_str(), ios::in);
  if (in.is_open()) {
    double freq = 0; // frequency
    // number of sources, number of receivers, number of ranges
    int ns = 0, nrcv = 0, nrg = 0; 
    in >> freq >> ns >> nrcv >> nrg;
    // src vector, receiver vector, range vector
    double src[ns], rcv[nrcv], rg[nrg]; 

    //read the source depths
    for (int i = 0; i < ns; i++) {
      in >> src[i];
    }
    //read the receiver depths
    for (int i = 0; i < nrcv; i++) {
      in >> rcv[i];
    }
    //read the receiver ranges
    for (int i = 0; i < nrg; i++) {
      in >> rg[i];
    }

    //read the max arrival count
    int MAX_ARR_CNT = 0;
    in >> MAX_ARR_CNT;
    for (int s = 0; s < ns; s++) {
      for (int i = 0; i < nrcv; i++) {
	for (int j = 0; j < nrg; j++) {
	  int n = 0;
	  in >> n;
	  //amplitude, phase, travel time, angle at source, angle at rcv
	  double amps[n], phase[n], tt[n], as[n], ar[n];
	  //no. of surface reflections, no. of bottom reflections
	  double topr[n], botr[n];
	  for (int k = 0; k < n; k++) {
	    in >> amps[k] >> phase[k] >> tt[k] >> as[k] >> ar[k]
	       >> topr[k] >> botr[k];
	  }
	  //NOW... do your thing
	  // For each of the ns * nrcv * nrg pairs, create an output
	  // file that contains H, Noise, Bandwidth -- as detailed in
	  // Channel Modelling for Acoustic Sensor Networks
	  // Peter King, Ramachandran Vekatesan, Cheng Li
	  // H is given by the sum generated by
	  // H += amps[a] * exp(-i*2*pi*f*tt[a])
	  complex<double> H (0,0);
	  for (int k = 0; k < n; k++) {
	    H += amps[k] * exp(complex<double> (0, -2*M_PI*freq*tt[k])); 
	  }
	  double noise = gen_noise(freq / 1000);
	  double S = db_water(abs(H)) - noise ;

	  fstream out;
	  const string outs ("../gen/val_" + itoa(freq) + "_" + itoa(s) + "_" + itoa(i) + "_" + itoa(j) + "_" + INDEX + ".out");
	  out.open(outs.c_str(), ios::out);
	  out << abs(H) << endl;
	  out << db_water(abs(H)) << endl;
	  out << noise << endl;
	  out << S << endl;
	  out.close();
	}
      }
    }

    in.close();
  } else {
    cout << "Unable to open file " << argv[1] << endl;
  }
  return 0;
}