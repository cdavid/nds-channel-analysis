#include <iostream>
#include <fstream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <string>
#include <complex>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>

using namespace std;

string itoa (int a) {
  stringstream out;
  out << a;
  return out.str();
}

int main (int argc, char ** argv) {
  if (argc != 2) {
    return 1;
  }
  string CFG (argv[1]);
  cerr << "Opening file " << CFG << endl;
  ifstream in;
  in.open (CFG.c_str(), ios::in);

  //read the values for the frequency range
  int fstart=0, fend=0, fstep=0;
  //read the values for source, rcv, range, bIndex
  int ns=0, nrcv=0, nrg=0, bIndex=0;

  in >> fstart >> fend >> fstep >> ns >> nrcv >> nrg >> bIndex;

  string hrealS, loghS, noiseS, sig2noise;
  in >> hrealS >> loghS >> noiseS >> sig2noise;

  cout << "Computing Bandwidth. Reading from: " << sig2noise << endl;

  in.close();
  in.open(sig2noise.c_str(), ios::in);

  double f[60000/250], S[60000/250];
  int n = 0;
  while (in.good()) {
    in >> f[n] >> S[n];
    n++;
  }
  n--;
  in.close();
  int fc = 0, fmin = 0;
  for (int i = 0; i < n; i++) {
    if (S[i] > S[fc]) {
      fc = i;
    }
    if (S[i] < S[fmin]) {
      fmin = i;
    }
  }
  cout << "Peak at: " << fc*250+250 << " with value " << S[fc] << endl;
  int j = 0, BW[60000/250];
  for (int i = 0; i < n; i++) {
    if (S[i] > S[fmin] + (S[fc] - S[fmin])/ 2) { //actually we want to know if the signal is more than half way above the distance between fmin and fmax
      BW[j] = i*250 + 250;
      j++;
    }
  }
  //now that we have the bandwidth,
  //we can compute the channel capacity
  //at different frequencies:
  double C = 0;
  int offset = (BW[j-1] - BW[0])/250; // maybe a +1 here?
  int offset2 = offset / 2;
  double cInd[60000/250];
  fstream out; const string capac ("plotScripts/capacity" + itoa(nrcv) + itoa(nrg) +".out");
  out.open(capac.c_str(), ios::out);
  //TODO: find something better than O(n^2)
  for (int i = 0; i < n; i++) { 
    cInd[i] = 0;
    for (int j = i - offset2 > 0 ? i-offset2 : 0; j < i + offset2 && j < n; j++) {
      cInd[i] += 250 * log2(1 + 180 * pow(10,S[j]/20));
    }
    C += cInd[i];
    out << i*250 + 250 << " " << cInd[i] << endl;
  }
  out.close();
  
  out.open("plotScripts/capacities.out", ios::app);
  out << nrcv << " " << nrg << " " << C << endl;
  out.close();

  cout << fc*250+250 <<" " << BW[j-1] - BW[0] << " " << C << endl;
  return 0;
}
