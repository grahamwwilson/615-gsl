#include <stdio.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_sf_ellint.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
using namespace std;

// Use GSL to
// evaluate elliptic integral for large angle simple pendulum problem 
//
// F(phi, k) = Integral(t=0, t=phi) {dt / sqrt(1 - k^2 sin^2(t))}
// K(k) = F(pi/2, k)      

int main (void){

double PIE = 4.0*atan(1.0);
double theta0 = PIE/4.0;
double k = sin(theta0/2.0);
double y;

bool natural_form = false;

cout << " " << endl;
cout << "Calculating period for large angle simple pendulum" << endl;
cout << "with theta0 = " << theta0 << endl;
cout << "corresponding to k = " << k << endl;
cout << "with GSL library, GSL_PREC_DOUBLE " << GSL_PREC_DOUBLE << endl;
cout << " " << endl;
/* These routines compute the complete elliptic integral K(k) to the 
accuracy specified by the mode variable. Note that Abramowitz & Stegun 
define this function in terms of the parameter m = k^2. */

if(natural_form){
   // Natural form
   cout << "Using natural form" << endl;
   y = gsl_sf_ellint_Kcomp (k, GSL_PREC_DOUBLE );
   printf ("Complete elliptic integral K(%g) = %.18e\n", k, y);
}
else{
   // Error handling form
   cout << "Using error handling form" << endl;
   gsl_sf_result result;
   int status = gsl_sf_ellint_Kcomp_e (k, GSL_PREC_DOUBLE , &result);
   printf ("status  = %s\n", gsl_strerror(status));
   cout << " " << endl;
   printf ("Complete elliptic integral K(%g) = %.18e +/- % .18e\n",k, 
           result.val, result.err);
   y = result.val;
   double error = result.err;
}

double PIBY2 = PIE/2.0;
double period_factor = y/PIBY2;

// Use FORTRAN compatibility output using examples from 
// page 29 of Barton and Nackmann, Scientific and Engineering C++
cout << setiosflags(ios::showpoint | ios::uppercase);
cout << setiosflags(ios::fixed);
cout.precision(16);

cout << " " << endl;
cout << "Large angle simple pendulum, 45 degree initial amplitude, " 
     << endl;
cout << "has period increased by a factor of " << setw(20) 
     << period_factor << " " << endl;

double length = 2.0;                    // in m
double g = 9.80;                        // in m s^-2
double T0 = 2.0*PIE*sqrt(length/g);     // in s

cout << " " << endl;
cout << "HW3 Part 2.    T0 (s) " << T0 << endl;
cout << "                T (s) " << T0*period_factor << endl;

}
