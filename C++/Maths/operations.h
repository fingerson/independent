#ifndef OPERATIONS_H
#define OPERATIONS_H

// Constants
#define EPSILON        0.00000001
#define EXPPRECISION   10
#define LNPRECISION    20
#define TRIGPRECISION  20                   // Preferabily be a multiple of 4, but don't go beyond 20
#define DERIVPRECISION 0.0001
#define INTEGPRECISION 0.0001

#define TENROOTTEN     1.25892541179416
#define TAU            6.2831853071796
#define EULER          2.718281828459045953
#define DGTORAD        0.0174532925199433
#define RADTODG        57.29577950130821
#define LN10           2.30258509299405
#define LN2            0.693147180559946

using namespace std;

namespace control_variables
{
extern int out_of_domain;
}

namespace units
{
// Arc
const long double dg(360/TAU);
const long double grad(400/TAU);

// Length
const long double pm(0.000000000001);
const long double nm(0.000000001);
const long double um(0.000001);
const long double mm(0.001);
const long double cm(0.01);
const long double in(0.0254);
const long double dm(0.1);
const long double ft(0.3048);
const long double m(1);
const long double dam(10);
const long double hm(100);
const long double km(1000);
const long double mile(1609.344);
const long double Mm(1000000);
const long double Gm(1000000000);
const long double Tm(1000000000000);

// Time
const long double ps(0.000000000001);
const long double ns(0.000000001);
const long double us(0.000001);
const long double ms(0.001);
const long double s(1);
const long double mnt(60);
const long double ks(1000);
const long double h(3600);
const long double Ms(1000000);
const long double Gs(1000000000);
const long double Ts(1000000000000);

// Area
const long double mm2(0.000001);
const long double cm2(0.0001);
const long double dm2(0.01);
const long double m2(1);
const long double dam2(100);
const long double acre(4046.8564224);
const long double hm2(10000);
const long double km2(1000000);

// Volume
const long double mm3(0.000000001);
const long double cm3(0.000001);
const long double ml(0.000001);
const long double dm3(0.001);
const long double floz(0.0000284130625);
const long double l(0.001);
const long double gal(0.000454609);
const long double m3(1);
const long double dam3(1000);
const long double hm3(1000000);
const long double km3(1000000000);

// Eletric Charge
const long double pC(0.000000000001);
const long double nC(0.000000001);
const long double uC(0.000001);
const long double mC(0.001);
const long double C(1);
const long double kC(1000);
const long double MC(1000000);
const long double GC(1000000000);
const long double TC(1000000000000);

// Eletric Current
const long double pA(0.000000000001);
const long double nA(0.000000001);
const long double uA(0.000001);
const long double mA(0.001);
const long double A(1);
const long double kA(1000);
const long double MA(1000000);
const long double GA(1000000000);
const long double TA(1000000000000);

// Capacitance
const long double pF(0.000000000001);
const long double nF(0.000000001);
const long double uF(0.000001);
const long double mF(0.001);
const long double F(1);
const long double kF(1000);
const long double MF(1000000);
const long double GF(1000000000);
const long double TF(1000000000000);

// Indutance
const long double pH(0.000000000001);
const long double nH(0.000000001);
const long double uH(0.000001);
const long double mH(0.001);
const long double H(1);
const long double kH(1000);
const long double MH(1000000);
const long double GH(1000000000);
const long double TH(1000000000000);

// Mass
const long double pg(0.000000000000001);
const long double ng(0.000000000001);
const long double ug(0.000000001);
const long double mg(0.000001);
const long double g(0.001);
const long double oz(0.028349523125);
const long double lb(0.45359237);
const long double kg(1);
const long double ton(1000);

// Energy
const long double eV(1.6021766208e-19);
const long double MeV(1.6021766208e-13);
const long double pJ(0.000000000001);
const long double GeV(1.6021766208e-10);
const long double nJ(0.000000001);
const long double TeV(1.6021766208e-17);
const long double uJ(0.000001);
const long double mJ(0.001);
const long double J(1);
const long double kJ(1000);
const long double MJ(1000000);
const long double kWh(3600000);
const long double GJ(1000000000);
const long double TJ(1000000000000);

// Power
const long double pW(0.000000000001);
const long double nW(0.000000001);
const long double uW(0.000001);
const long double mW(0.001);
const long double W(1);
const long double kW(1000);
const long double MW(1000000);
const long double GW(1000000000);
const long double TW(1000000000000);

// Pressure
const long double pPa(0.000000000001);
const long double nPa(0.000000001);
const long double uPa(0.000001);
const long double mPa(0.001);
const long double Pa(1);
const long double mmHg(133.322387415);
const long double kPa(1000);
const long double psi(6894.8);
const long double bar(100000);
const long double atm(101325);
const long double MPa(1000000);
const long double GPa(1000000000);
const long double TPa(1000000000000);

// Force
const long double pN(0.000000000001);
const long double nN(0.000000001);
const long double uN(0.000001);
const long double mN(0.001);
const long double N(1);
const long double kN(1000);
const long double MN(1000000);
const long double GN(1000000000);
const long double TN(1000000000000);



}

namespace operations
{
//###############################################################################################################################
// Utility functions
//###############################################################################################################################

// Jumps lines
void    nl(int number_of_lines);


//###############################################################################################################################
// Auxiliar functions
//###############################################################################################################################

// Gives the derivative of a function at an especific point
long double derivative(long double (*foo)(long double), long double point);

// Calculates the Riemann sum of the function from the lowbound to the highbound
long double integrate(long double (*foo)(long double), long double lowbound, long double highbound);

// Plots a function foo between lowbound to highbound with the increment step
void plot(long double (*foo)(long double),long double lowbound,long double highbound,long double step);

// Simple exponentiation
long double spow(long double base, long long level);

// Tenth root of positive numbers
long double tenth_root(long double base);


//###############################################################################################################################
// Trigonometric Functions
//###############################################################################################################################

// Reduces the angle to be between between -Tau/2 and Tau/2
long double angle_reduction(long double angle);

// Calculates the arccosine of a number
long double arccos(long double number);

// Calculates the arcsine of a number
long double arcsin(long double number);

// Calculates the arctangent of a number
long double arctg(long double number);

// Cosine of real angles
long double cos(long double angle);

// Cosecant of real angles
long double cossec(long double angle);

// Cotangent of real angles
long double cotg(long double angle);

// Secant of real angles
long double sec(long double angle);

// Sine of real angles
long double sin(long double angle);

// Sinc function (sin(x)/x) for real x
long double sinc(long double angle);

// Tangent of real angles
long double tg(long double angle);

//########################################################################################################################################################
// Hyperbolic operations
//###############################################################################################################################

// Inverse hyperbolic cosine of real numbers
long double arccosh(long double number);

// Inverse hyperbolic sine of real numbers
long double arcsinh(long double number);

// Inverse hyperbolic tangent of real numbers
long double arctgh(long double number);

// Hyperbolic cosine of real numbers
long double cosh(long double number);

// Hyperbolic cosecant of real numbers
long double cosech(long double number);

// Hyperbolic cotangent of real numbers
long double cotgh(long double number);

// Hyperbolic secant of real numbers
long double sech(long double number);

// Hyperbolic sine of real numbers
long double sinh(long double number);

// Hyperbolic tangent of real numbers
long double tgh(long double number);


//###############################################################################################################################
// Numeric operations
//###############################################################################################################################

// Tests to see if the absolute value of the difference divided by the sum of two real numbers is smaller than epsilon
long double eql(long double number1, long double number2);

// Returns 1 if the number is prime, otherwise, returns 0;
long long   is_prime(long long prime_candidate);

// Gives the factorial of an integer
long long   factorial(long long number);

// Gives the greatest common divisor of two numbers
long long   gcd(long long number1, long long number2);

// Gives the least common multiple of two numbers
long long   lcm(long long number1, long long number2);

// Gives the absolute value of a real number
long double module(long double number);
// Gives the module of an integer
long long   module(long long number);

// Gives the #position prime
long long   prime(long long position);

//###############################################################################################################################
// Exponentiation and Logarithm related functions
//###############################################################################################################################

// Calculates e^level;
long double exp(long double level);

// Calculates the natural logarithm of a number
long double ln(long double number);

// Calculates the log of a number in some base
long double log(long double number, long double base);

// Exponentiation of real numbers with real levels;
long double pow(long double base, long double level);

//###############################################################################################################################
// Int functions
//###############################################################################################################################
}

#endif
