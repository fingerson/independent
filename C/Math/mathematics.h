//  Header File for the mathematics.h functions.


#ifndef MATHEMATICS_H
#define MATHEMATICS_H

#include <stdio.h>

typedef long long       inty;
typedef long double     floaty;
typedef struct complex  complex;

#define PRECISIONRATE  6
#define LNPRECISION    10000
#define ARCPRECISION   0.000001
#define XMAX           40
#define YMAX           40

#define TAU            6.2831853071796
#define EULER          2.718281828459045953
#define DGTORAD        0.0174532925199433
#define RADTODG        57.29577950130821
#define LN10           2.30258509299405

//##############################################################################################################################################################################################
//##############################################################################################################################################################################################
//##############################################################################################################################################################################################

//  Structure declaration
struct  complex
{
    long double   real;
    long double   imag;
    long double   modl;
    long double   angl;

};

//##############################################################################################################################################################################################
//##############################################################################################################################################################################################
//##############################################################################################################################################################################################

//  Function declaration
struct complex     attribp(long double modl, long double angl);
struct complex     attribr(long double real, long double imag);
struct complex     conjugate(struct complex number);
struct complex     cosinec(struct complex number);
struct complex     cosinehc(struct complex number);
struct complex     cotangentc(struct complex number);
struct complex     lnc(struct complex number);
struct complex     pol_update(struct complex number);
struct complex     rec_update(struct complex  number);
struct complex     sinec(struct complex number);
struct complex     sinehc(struct complex number);
struct complex     tangentc(struct complex number);
struct complex     tangenthc(struct complex number);

struct complex     pscancr(char starray[256]);
struct complex     pscancp(char starray[256]);
struct complex     scancp(void);
struct complex     scancr(void);

struct complex     addc(struct complex number1, struct complex number2);
struct complex     determinant(struct complex (*matrix)[YMAX], int n);
struct complex     divc(struct complex number1, struct complex number2);
struct complex     exponentialc(struct complex number, struct complex level);
struct complex     logc(struct complex number, struct complex base);
struct complex     mulc(struct complex number1, struct complex number2);
struct complex     subc(struct complex number1, struct complex number2);

//##############################################################################################################################################################################################

void          addcmatrix(struct complex (*result)[YMAX], struct complex (*matrix_1)[YMAX], struct complex(*matrix_2)[YMAX], int x, int y);
void          chio(struct complex (*result)[YMAX], struct complex (*matrix)[YMAX], int n);
void          linear_equation_system(struct complex (*variables), struct complex (*coefficients)[YMAX], struct complex (*results), int n);
void          mulcmatrix(struct complex (*result)[YMAX], struct complex (*matrix_1)[YMAX], struct complex (*matrix_2)[YMAX], int x1, int y2, int y1);
void          scmulcmatrix(struct complex (*result)[YMAX], struct complex (*matrix_1)[YMAX], struct complex(*matrix_2)[YMAX], int x, int y);
void          subccmatrix(struct complex (*result)[YMAX], struct complex (*matrix_1)[YMAX], struct complex(*matrix_2)[YMAX], int x, int y);
void          transpcmatrix(struct complex (*result)[YMAX], struct complex (*matrix)[YMAX], int x, int y);

void          fillcmatrix(struct complex (*pointer)[YMAX], int xsize, int ysize);
void          nl(int i);
void          printc(struct complex number);
void          printcmatrix(struct complex (*matrix)[YMAX], int x, int y);

void          addmatrix(long double (*result)[YMAX], long double (*matrix_1)[YMAX], long double (*matrix_2)[YMAX], int x, int y);
void          mulmatrix(long double (*result)[YMAX], long double (*matrix_1)[YMAX], long double (*matrix_2)[YMAX], int x1, int y2, int y1);
void          scmulmatrix(long double (*result)[YMAX], long double (*matrix_1)[YMAX], long double (*matrix_2)[YMAX], int x, int y);
void          submatrix(long double (*result)[YMAX], long double (*matrix_1)[YMAX], long double (*matrix_2)[YMAX], int x, int y);
void          transpmatrix(long double (*result)[YMAX], long double (*matrix)[YMAX], int x, int y);

void          fillmatrix(long double (*pointer)[YMAX], int xsize, int ysize);
void          printmatrix(long double (*matrix)[YMAX], int x, int y);

//##############################################################################################################################################################################################

long double   angle_reduction(long double number);
long double   arccosine(long double number);
long double   arctangent (long double number);
long double   arcsine(long double number);
long double   cossecant(long double number);
long double   cosine(long double number);
long double   cosineh(long double number);
long double   cotangent(long double number);
long double   logn(long double number);
long double   modulec(struct complex number);
long double   modulef(long double number);
long double   secant(long double number);
long double   sine(long double number);
long double   sineh(long double number);
long double   tangent(long double number);
long double   tangenth(long double number);

long double   pscanf(char starray[256]);

long double   exponential(long double number, long long level);
long double   exponentialf(long double number, long double level);
long double   lognb(long double number, long double base);
long double   root(long double number, long long level);

//##############################################################################################################################################################################################

long long     factorial(long long number);
long long     modulei(long long number);
long long     prime(long long number);
long long     round_down(long double number);
long long     round_up(long double number);

long long     pscani(char starray[256]);

long long     combinations(long long number, long long k);
long long     falling_factorial(long long number, long long k);
long long     gcd(long long number1, long long number2);
long long     lcd(long long number1, long long number2);

#endif // mathematics
