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

int main (int argc, char** argv) {
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

  double S[(fend - fstart)/fstep + 1], hreal[(fend - fstart)/fstep + 1], logh[(fend - fstart)/fstep + 1], noise[(fend - fstart)/fstep + 1];
  //read the values from the files into local variables for easy handling
  for (int i = fstart; i < fend; i += fstep) {
    const string ins ("../gen/val_" + itoa(i) + "_" + itoa(ns) + "_" + itoa(nrcv) 
		       + "_" + itoa(nrg) + "_" + itoa(bIndex) + ".out");
    fstream iin; 
    iin.open (ins.c_str(), ios::in);
    if (iin.is_open()) {
      iin >> hreal[i/fstep] >> logh[i/fstep] >> noise[i/fstep] >> S[i/fstep];
      iin.close();
    } else {
      cerr << "Error reading file " << ins << endl;
    }
  }

  fstream hr,lh,nos,sn; // H.real(), 10log(H.real()), noise, sig2noise
  hr.open(hrealS.c_str(), ios::out);
  lh.open(loghS.c_str(), ios::out);
  nos.open(noiseS.c_str(), ios::out);
  sn.open(sig2noise.c_str(), ios::out);
  for (int i = fstart; i < fend; i += fstep) {
    if (i != 0) {
      hr << i << " " << hreal[i/fstep] << endl;
      lh << i << " " << logh[i/fstep] << endl;
      nos << i << " " << noise[i/fstep] << endl;
      sn << i << " " << S[i/fstep] << endl;
    }
  }
  hr.close();lh.close();nos.close();sn.close();


  return 0;
}
