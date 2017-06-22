#include <stdio.h>

//##############################################################################################################################################################################################
//##############################################################################################################################################################################################
//##############################################################################################################################################################################################

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

//##############################################################################################################################################################################################
//  Complex Functions;
//##############################################################################################################################################################################################

//  Attribution of polar parameters (Needs: rec_update, angle_reduction);
struct complex     attribp(long double modl, long double angl)
{
    struct complex  value;
    value.modl = modl;
    value.angl = angle_reduction(angl);
    value = rec_update(value);

    return value;
}

//  Attribution of rectangular parameters (Needs: pol_update);
struct complex     attribr(long double real, long double imag)
{
    struct complex  value;
    value.real = real;
    value.imag = imag;
    value = pol_update(value);

    return value;
}

//  Complex number conjugate (Needs: Nothing);
struct complex     conjugate(struct complex number)
{
    struct complex value;

    value.real = number.real;
    value.imag = -number.imag;
    value.angl = -number.angl;
    value.modl = number.modl;

    return value;
}

// Calculates the cosine of a complex number (Needs: cosinehc, mulc, attrib);
struct complex     cosinec(struct complex number)
{
    struct complex value;
    struct complex iunit;

    iunit = attribr(0,1);

    value = cosinehc(mulc(number, iunit));

    return value;
}

//  Calculates the Hyperbolic Cosine of a complex number (Needs: exponentialc, attribr, addc, divc, subc);
struct complex     cosinehc(struct complex number)
{
    struct complex value;
    struct complex value2;

    value = exponentialc(attribr(EULER,0), number);
    value2 = subc(attribr(0,0), number);
    value = addc(value, exponentialc(attribr(EULER,0), value2));
    value = divc(value,attribr(2,0));

    return value;
}

// Calculates the cotangent of a complex number (Needs: sinec, cosinec, divc);
struct complex     cotangentc(struct complex number)
{
    struct complex value;
    value = divc(cosinec(number), sinec(number));
    return value;
}

//  Complex natural logarithim (Needs: logn);
struct complex     lnc(struct complex number)
{
    struct complex  value;
    value.real = logn(number.modl);
    value.imag = DGTORAD * number.angl;

    value = pol_update(value);
    return value;
}

//  Updates polar parameters with the rectangular parameters (Needs: arctangent, modulec);
struct complex     pol_update(struct complex number)
{
    struct  complex value;

    value.real = number.real;
    value.imag = number.imag;
    value.modl = modulec(number);
    if(number.real == 0 && number.imag > 0)
    {
        value.angl = 90;
    }
    else if(number.real == 0 && number.imag == 0)
    {
        value.angl = 0;
    }
    else if(number.real == 0 && number.imag < 0)
    {
        value.angl = -90;
    }
    else if(number.real > 0 && number.imag == 0)
    {
        value.angl = 0;
    }
    else if(number.real < 0 && number.imag == 0)
    {
        value.angl = 180;
    }
    else
    {
        value.angl = arctangent(number.imag/number.real);
        value.angl = angle_reduction(value.angl);
    }

    if(number.real < 0 && number.imag < 0)
    {
        value.angl -= 180;
    }
    else if(number.real < 0 && number.imag > 0)
    {
        value.angl += 180;
    }


    return value;

}

//  Updates rectangular parameters with the polar parameters (Needs: sine, cosine);
struct  complex    rec_update(struct complex  number)
{
    struct  complex    value;

    value.modl = number.modl;
    value.angl = number.angl;
    value.real = number.modl * cosine(number.angl);
    value.imag = number.modl * sine(number.angl);

    return value;
}

// Calculates the sine of a complex number (Needs: sinehc, mulc, divc, attrib);
struct complex     sinec(struct complex number)
{
    struct complex value;
    struct complex iunit;

    iunit = attribr(0,1);

    value = sinehc(mulc(number, iunit));
    value = divc(value, iunit);

    return value;
}

//  Calculates the Hyperbolic Sine of a complex number (Needs: exponentialc, attribr, subc, divc, subc);
struct complex     sinehc(struct complex number)
{
    struct complex value;
    struct complex value2;

    value = exponentialc(attribr(EULER,0), number);
    value2 = subc(attribr(0,0), number);
    value = subc(value, exponentialc(attribr(EULER,0), value2));
    value = divc(value, attribr(2,0));

    return value;
}

// Calculates the tangent of a complex number (Needs: sinec, cosinec, divc);
struct complex     tangentc(struct complex number)
{
    struct complex value;
    value = divc(sinec(number), cosinec(number));
    return value;
}

// Calculates the Hyperbolic Tangent of a complex number (Needs: sinehc, cosinehc, divc);
struct complex     tangenthc(struct complex number)
{
    struct complex value;
    value = divc(sinehc(number), cosinehc(number));
    return value;
}



//  Prints a message (Up to 256 characters, ending with ": " and scans the polar parameters of a complex) (Needs: scancp);
struct complex     pscancp(char starray[256])
{
    int i;
    struct complex value;

    for(i = 0; i<256; i++)
    {
        printf("%c", starray[i]);
        if(starray[i-1] == ':')
        {
            break;
        }
    }
    value = scancp();

    return value;
}

//  Prints a message (Up to 256 characters, ending with ": " and scans the rectangular parameters of a complex) (Needs: scancr);
struct complex     pscancr(char starray[256])
{
    int i;
    struct complex value;

    for(i = 0; i<256; i++)
    {
        printf("%c", starray[i]);
        if(starray[i-1] == ':')
        {
            break;
        }
    }
    value = scancr();

    return value;
}

//  Scan for complex polar parameters(Needs: rec_update);
struct complex     scancp(void)
{
    struct complex  value;

    printf("\nModule: ");
    scanf("%Lf", &value.modl);
    printf("Angle: ");
    scanf("%Lf", &value.angl);

    value = rec_update(value);
    printf("\n");

    return value;
}

//  Scan for complex rectangular parameters(Needs: pol_update);
struct complex     scancr(void)
{
    struct complex  value;

    printf("\nReal: ");
    scanf("%Lf", &value.real);
    printf("Imaginary: ");
    scanf("%Lf", &value.imag);

    value = pol_update(value);
    printf("\n");

    return value;
}



//  Complex numbers adding (Needs: Nothing);
struct complex     addc(struct complex number1, struct complex number2)
{
    struct complex value;

    value.real = number1.real + number2.real;
    value.imag = number1.imag + number2.imag;

    value = pol_update(value);

    return value;
}

//  Calculates the determinant of a complex matrix (Needs: chio, mulc, subc);
struct complex     determinant(struct complex (*matrix)[YMAX], int n)
{
    int i;
    int j;
    int size;
    int nullmatrix = 1;

    struct complex value = attribr(0,0);
    struct complex subtr;
    struct complex aux;

    struct complex result[XMAX][YMAX];
    struct complex receiver[XMAX][YMAX];

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            receiver[i][j] = matrix[i][j];
            aux = receiver[i][j];
            if(aux.real != 0 || aux.imag != 0)
            {
                nullmatrix = 0;
            }
        }
    }
    if(nullmatrix == 0)
    {
        for(size = n; size > 2; size--)
        {
            chio(result, receiver, size);
            for(i = 0; i < size-1; i++)
            {
                for(j = 0; j < size-1; j++)
                {
                    receiver[i][j] = result[i][j];
                }
            }
        }
        value = mulc(receiver[0][0], receiver[1][1]);
        subtr = mulc(receiver[0][1], receiver[1][0]);
        value = subc(value, subtr);
    }

    return value;
}

// Complex number dividing (Needs: modulecr, mulc, conjugate);
struct complex     divc(struct complex number1, struct complex number2)
{
    struct complex value;
    struct complex number2_conj;


    number2_conj = conjugate(number2);
    value = mulc(number1, number2_conj);
    value.real = value.real/(number2.real*number2.real + number2.imag*number2.imag);
    value.imag = value.imag/(number2.real*number2.real + number2.imag*number2.imag);

    value = pol_update(value);


    return value;
}

//  Complex exponential (Needs: exponentialf, rec_update, logn, mulc);
struct complex     exponentialc(struct complex number, struct complex level)
{
    struct  complex value;
    struct  complex y;

    y.real = 0;
    y.imag = DGTORAD*number.angl;
    y = mulc(y, level);
    value.modl = logn(number.modl);
    value.modl = level.real*value.modl;
    value.modl += y.real;
    value.modl = exponentialf(EULER, value.modl);

    value.angl = logn(number.modl);
    value.angl = level.imag*value.angl;
    value.angl += y.imag;
    value.angl = RADTODG*value.angl;
    value.angl = angle_reduction(value.angl);

    value = rec_update(value);

    return value;

}

//  Complex logarithim (Needs: divc, lnc);
struct complex     logc(struct complex number, struct complex base)
{
    struct complex  value;
    value = divc(lnc(number), lnc(base));

    return value;
}

//  Complex numbers multiplying (Needs: Nothing);
struct complex     mulc(struct complex number1, struct complex number2)
{
    struct complex value;

    value.real = number1.real * number2.real - number1.imag*number2.imag;
    value.imag = number1.real * number2.imag + number1.imag*number2.real;

    value = pol_update(value);


    return value;
}

//  Complex numbers subtracting (Needs: Nothing);
struct complex     subc(struct complex number1, struct complex number2)
{
    struct complex value;

    value.real = number1.real - number2.real;
    value.imag = number1.imag - number2.imag;

    value = pol_update(value);

    return value;
}

//##############################################################################################################################################################################################
//  Matrix functions;
//##############################################################################################################################################################################################

//  Adds two cmatrices (Needs: addc);
void            addcmatrix(struct complex (*result)[YMAX], struct complex (*matrix_1)[YMAX], struct complex(*matrix_2)[YMAX], int x, int y)
{
    int i;
    int j;

    for(i = 0; i < x; i++)
    {
        for(j = 0; j < y; j++)
        {
            result[i][j] = addc(matrix_1[i][j], matrix_2[i][j]);
        }
    }
}

//  Applies Chio's Rule and reduces a complex matrix (Needs: divc, subc, mulc);
void            chio(struct complex (*result)[YMAX], struct complex (*matrix)[YMAX], int n)
{
    int     i;
    int     j;
    int     x;
    int     y;

    int     posx=0;
    int     posy=0;

    struct complex sub;
    struct complex var = attribr(0,0);
    struct complex intermat[XMAX][YMAX];

    for(i = 0; i<n && var.real == 0 && var.imag == 0; i++)
    {
        for(j = 0; j<n && var.real == 0 && var.imag == 0; j++)
        {
            x = i;
            y = j;
            var = matrix[i][j];
        }
    }

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            if(i == 0)
            {
                intermat[i][j] = divc(matrix[i][j], var);
            }
            else
            {
                intermat[i][j] = matrix[i][j];
            }
        }
    }

    for(i = 0; i<n; i++)
    {
        for(j = 0; j<n; j++)
        {
            if(i!= x && j!=y)
            {
                sub = mulc(intermat[x][j], intermat[i][y]);
                result[posx][posy] = subc(intermat[i][j], sub);
                if(posy < n-2)
                {
                    posy++;
                }
                else
                {
                    posx++;
                    posy = 0;
                }
            }
        }
    }

    for(j = 0; j<n-1; j++)
    {
        result[0][j] = mulc(var, result[0][j]);
    }

}

//  Solves complex linear equation systems (Needs: determinant, divc);
void            linear_equation_system(struct complex (*variables), struct complex (*coefficients)[YMAX], struct complex (*results), int n)
{
    int i;
    int j;
    int k;

    struct complex matrix[XMAX][YMAX];
    struct complex det;
    struct complex detdiv;

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            matrix[i][j] = coefficients[i][j];
        }
    }

    detdiv = determinant(matrix, n);

    for(k = 0; k < n; k++)
    {
        for(i = 0; i < n; i++)
        {
            for(j = 0; j < n; j++)
            {
                matrix[i][j] = coefficients[i][j];
            }
        }
        for(i = 0; i < n; i++)
        {
            for(j = 0; j < n; j++)
            {
                if(j == k)
                {
                    matrix[i][j] = results[i];
                }
                else
                {
                    matrix[i][j] = matrix[i][j];
                }
            }
        }
        det = determinant(matrix, n);
        variables[k] = divc(det, detdiv);
    }
}

//  Multiplies two cmatrices (Needs: addc, mulc);
void            mulcmatrix(struct complex (*result)[YMAX], struct complex (*matrix_1)[YMAX], struct complex (*matrix_2)[YMAX], int x1, int y2, int y1)
{
    int              i;
    int              j;
    int              k;
    struct complex   sum;

    for(i = 0; i<x1; i++)
    {
        for(j = 0; j<y2; j++)
        {
            sum.real = 0;
            sum.imag = 0;
            sum.modl = 0;
            sum.angl = 0;

            for(k = 0; k < y1; k++)
            {
                sum = addc(mulc(matrix_1[i][k], matrix_2[k][j]), sum);
            }
            result[i][j] = sum;
        }
    }

}

//  Scalar multiplication of two cmatrices (Needs: mulc);
void            scmulcmatrix(struct complex (*result)[YMAX], struct complex (*matrix_1)[YMAX], struct complex(*matrix_2)[YMAX], int x, int y)
{
    int i;
    int j;

    for(i = 0; i < x; i++)
    {
        for(j = 0; j < y; j++)
        {
            result[i][j] = mulc(matrix_1[i][j], matrix_2[i][j]);
        }
    }
}

//  Subtracts two cmatrices (Needs: addc);
void            subccmatrix(struct complex (*result)[YMAX], struct complex (*matrix_1)[YMAX], struct complex(*matrix_2)[YMAX], int x, int y)
{
    int i;
    int j;

    for(i = 0; i < x; i++)
    {
        for(j = 0; j < y; j++)
        {
            result[i][j] = subc(matrix_1[i][j], matrix_2[i][j]);
        }
    }
}

//  Transposes a cmatrix (Needs: Nothing);
void            transpcmatrix(struct complex (*result)[YMAX], struct complex (*matrix)[YMAX], int x, int y)
{
    int i;
    int j;

    for(i = 0; i < x; i++)
    {
        for(j = 0; j < y; j++)
        {
            result[i][j] = matrix[j][i];
        }
    }
}



//  Fills a cmatrix (Needs: scancr);
void            fillcmatrix(struct complex (*pointer)[YMAX], int xsize, int ysize)
{

    int            i;
    int            j;
    struct complex var;

    for(i = 0; i<xsize; i++)
    {
        for(j = 0; j<ysize; j++)
        {
            printf("Position (%d,%d)", i, j);
            var = scancr();
            pointer[i][j] = var;
        }
    }
}

//  Prints a number of \n (Needs: Nothing)
void            nl(int i)
{
    int j;
    for(j = 0; j < i; j++)
    {
        printf("\n");
    }
}

//  Prints all the parameters of a complex number (Needs: nothing);
void            printc(struct complex number)
{
    printf("\nReal parameter: %Lf", number.real);
    printf("\nImaginary parameter: %Lf", number.imag);
    printf("\nModule: %Lf", number.modl);
    printf("\nAngle: %Lf degrees\n\n", number.angl);
}

//  Prints a cmatrix (Needs: Nothing);
void            printcmatrix(struct complex (*matrix)[YMAX], int x, int y)
{
    int i;
    int j;

    for(i = 0; i<x; i++)
    {
        for(j = 0; j<y; j++)
        {
            printf("%8Lf + %8Lfi   ", matrix[i][j].real, matrix[i][j].imag);
        }
        printf("\n");
    }
}



//  Adds two  float matrices (Needs: Nothing);
void            addmatrix(long double (*result)[YMAX], long double (*matrix_1)[YMAX], long double (*matrix_2)[YMAX], int x, int y)
{
    int i;
    int j;

    for(i = 0; i < x; i++)
    {
        for(j = 0; j < y; j++)
        {
            result[i][j] = matrix_1[i][j] + matrix_2[i][j];
        }
    }
}

//  Multiplies two float matrices (Needs: Nothing);
void            mulmatrix(long double (*result)[YMAX], long double (*matrix_1)[YMAX], long double (*matrix_2)[YMAX], int x1, int y2, int y1)
{
    int           i;
    int           j;
    int           k;
    long double   sum;

    for(i = 0; i<x1; i++)
    {
        for(j = 0; j<y2; j++)
        {
            sum = 0;
            for(k = 0; k < y1; k++)
            {
                sum += matrix_1[i][k] * matrix_2[k][j];
            }
            result[i][j] = sum;
        }
    }

}

//  Scalar multiplication of two float matrices (Needs: Nothing);
void            scmulmatrix(long double (*result)[YMAX], long double (*matrix_1)[YMAX], long double (*matrix_2)[YMAX], int x, int y)
{
    int i;
    int j;

    for(i = 0; i < x; i++)
    {
        for(j = 0; j < y; j++)
        {
            result[i][j] = matrix_1[i][j] * matrix_2[i][j];
        }
    }
}

//  Subtracts two  float matrices (Needs: Nothing);
void            submatrix(long double (*result)[YMAX], long double (*matrix_1)[YMAX], long double (*matrix_2)[YMAX], int x, int y)
{
    int i;
    int j;

    for(i = 0; i < x; i++)
    {
        for(j = 0; j < y; j++)
        {
            result[i][j] = matrix_1[i][j] - matrix_2[i][j];
        }
    }
}

//  Transposes a float matrix (Needs: Nothing);
void            transpmatrix(long double (*result)[YMAX], long double (*matrix)[YMAX], int x, int y)
{
    int i;
    int j;

    for(i = 0; i < x; i++)
    {
        for(j = 0; j < y; j++)
        {
            result[i][j] = matrix[j][i];
        }
    }
}



//  Fills a float matrix (Needs: Nothing);
void            fillmatrix(long double (*pointer)[YMAX], int xsize, int ysize)
{

    int         i;
    int         j;
    long double var;

    for(i = 0; i<xsize; i++)
    {
        for(j = 0; j<ysize; j++)
        {
            printf("\nValue of (%d, %d) = ", i, j);
            scanf("%Lf", &var);
            pointer[i][j] = var;
        }
    }
}

//  Prints a float matrix (Needs: Nothing);
void            printmatrix(long double (*matrix)[YMAX], int x, int y)
{
    int i;
    int j;

    for(i = 0; i<x; i++)
    {
        for(j = 0; j<y; j++)
        {
            printf("%8Lf", matrix[i][j]);
        }
        printf("\n");
    }
}



//##############################################################################################################################################################################################
//  Float functions;
//##############################################################################################################################################################################################

//  Angle Reduction (Needs: Nothing);
long double   angle_reduction(long double number)
{
    long double   value = number;
    if(value < 0)
    {
        while(value <= -360)
        {
            value += 360;
        }
    }
    else if(value > 0)
    {
        while(value >= 360)
        {
            value -= 360;
        }
    }

    if(value < -180)
    {
        value += 360;
    }
    else if(value > 180)
    {
        value -= 360;
    }

    if(value == -180)
    {
        value = 180;
    }

    return value;
}

//  Arccosine (Needs: cosine);
long double   arccosine(long double number)
{
    long double   number_rec = number;
    long double   value;
    long double   acr;
    long long     flag=1;

    if(number_rec < 0)
    {
        number_rec = -number_rec;
        flag = 0;
    }

    value = 0;
    acr = 1;

    for(acr = 1; value <= 90 && acr > ARCPRECISION && cosine(value) != number_rec; value += acr)
    {
        if(cosine(value) < number_rec)
        {
            value -= acr;
            acr = acr/10;
        }

    }

    if(flag == 0)
    {
        value = 180 - value;
    }

    return value;
}

//  Arctangent (Needs: tangent);
long double   arctangent (long double number)
{
    long double   number_rec = number;
    long double   value;
    long double   acr;
    long long     flag=1;

    if(number_rec < 0)
    {
        number_rec = -number_rec;
        flag = -1;
    }

    value = 0;
    acr = 1;

    for(acr = 1; value <= 90 && acr > ARCPRECISION && tangent(value) != number_rec; value += acr)
    {
        if(tangent(value) > number_rec)
        {
            value -= acr;
            acr = acr/10;
        }

    }

    value = flag*value;

    return value;
}

//  Arcsine (Needs: sine);
long double   arcsine(long double number)
{
    long double   number_rec = number;
    long double   value;
    long double   acr;
    long long     flag=1;

    if(number >= -1 && number <= 1)
    {
        if(number_rec < 0)
        {
            number_rec = -number_rec;
            flag = -1;
        }

        value = 0;
        acr = 1;

        for(acr = 1; value <= 90 && acr > ARCPRECISION && sine(value) != number_rec; value += acr)
        {
            if(sine(value) > number_rec)
            {
                value -= acr;
                acr = acr/10;
            }

        }

        value = flag*value;
    }
    else
    {
        value = number;
    }


    return value;
}

//  Calculates the cossecant of a float number (Needs: sine);
long double   cossecant(long double number)
{
    long double value;
    value = sine(number);
    return value;
}

//  Cosine (Needs: Nothing);
long double   cosine(long double number)
{
    long double number_rec = angle_reduction(number)*DGTORAD;
    long double value = 0;
    long double i;
    long double pos_inc;
    long double neg_inc;

    for(i = 0; i < 13; i = i+4)
    {
        pos_inc = exponential(number_rec, i);
        pos_inc = pos_inc/factorial(i);
        neg_inc = exponential(number_rec, i+2);
        neg_inc = neg_inc/factorial(i+2);
        value = value + pos_inc - neg_inc;
    }
    return value;

}

//  Calculates the Hyperbolic Cosine of a float number (Needs: exponentialf);
long double   cosineh(long double number)
{
    long double value;

    value = exponentialf(EULER, number) + exponentialf(EULER, -number);
    value = value/2;

    return value;
}

//  Cotangent (Needs: sine, cosine);
long double   cotangent(long double number)
{
    long double value;
    value = cosine(number)/sine(number);
    return value;
}

//  Natural Logarithim Function (Needs: exponential);
long double   logn(long double number)
{
    long double   number_rec = number;
    long double   value = 0;
    long double   pos_inc;
    long double   neg_inc;
    long long     i;
    long long     j=0;

    if(number > 0)
    {
        for(j=0; number_rec > 2; j++)
        {
            number_rec = number_rec/10;
        }
        for(i=1; i<LNPRECISION; i += 2)
        {
            pos_inc = exponential(number_rec-1, i);
            pos_inc = pos_inc/i;
            neg_inc = exponential(number_rec-1, i+1);
            neg_inc = neg_inc/(i+1);
            value += pos_inc - neg_inc;
        }
        value += j*LN10;

    }
    else
    {
        value = number;
    }

    return value;
}

//  Complex number module (Needs: exponential, root);
long double   modulec(struct complex number)
{
    long double value;
    value = exponential(number.real, 2) + exponential(number.imag, 2);
    value = root(value, 2);

    return value;
}

//  Module long double (Needs: Nothing);
long double   modulef(long double number)
{
    long double number_rec = number;
    if(number<0)
    {
        number_rec= -number_rec;
    }
    return number_rec;
}

//  Calculates the secant of a float number (Needs: cosine);
long double   secant(long double number)
{
    long double value;
    value = cosine(number);
    return value;
}

//  Sine (Needs: Nothing);
long double   sine(long double number)
{
    long double number_rec = angle_reduction(number)*DGTORAD;
    long double value = 0;
    long double i;
    long double pos_inc;
    long double neg_inc;

    for(i = 1; i < 13; i = i+4)
    {
        pos_inc = exponential(number_rec, i);
        pos_inc = pos_inc/factorial(i);
        neg_inc = exponential(number_rec, i+2);
        neg_inc = neg_inc/factorial(i+2);
        value = value + pos_inc - neg_inc;
    }
    return value;

}

//  Calculates the Hyperbolic Sine of a float number (Needs: exponentialf);
long double   sineh(long double number)
{
    long double value;

    value = exponentialf(EULER, number) - exponentialf(EULER, -number);
    value = value/2;

    return value;
}

//  Tangent (Needs: Nothing);
long double   tangent(long double number)
{
    long double value;
    value = sine(number)/cosine(number);
    return value;
}

// Calculates the Hyperbolic Tangent of a float number (Needs: sineh, cosineh);
long double   tangenth(long double number)
{
    long double value;
    value = sineh(number)/cosineh(number);
    return value;
}



//  Prints a message (Up to 256 characters, ending with ": " and scans a float) (Needs: Nothing);
long double    pscanf(char starray[256])
{
    long long i;
    long double value;

    for(i = 0; i<256; i++)
    {
        printf("%c", starray[i]);
        if(starray[i-1] == ':')
        {
            break;
        }
    }
    scanf("%Lf", &value);

    return value;
}



//  Basic Exponential (Needs: Nothing);
long double   exponential(long double number, long long level)
{
    long double value;
    long long   i;

    if(level >= 1)
    {
        value = number;
        for(i = level-1; i > 0; i--)
        {
            value = value*number;
        }
    }
    else if(level == 0)
    {
        value = 1;
    }
    else
    {
        value = number;
    }

    return value;

}


//  Advanced Exponential function (Needs: modulef; exponential; root);
long double   exponentialf(long double number, long double level)
{
    long double     number_rec;
    long double     level_rec;
    long double     value = 1;
    long double     root_number;
    long long   root_level=1;
    long long   exp_level;
    long long   precision = exponential(10, PRECISIONRATE);

    if(number >= 0)
    {
        number_rec = number;
        level_rec = modulef(level);
        do
        {
            exp_level = level_rec;
            level_rec -= exp_level;
            level_rec = level_rec*10;
            root_number = exponential(number_rec, exp_level);
            root_number = root(root_number, root_level);
            value = value * root_number;
            root_level = root_level*10;

        }while(root_level < precision && level_rec != 0);

        if(level < 0)
        {
            value = 1/value;
        }

    }
    else
    {
        value = number;
    }

    return value;

}


//  Logarithim Function (Needs: logn);
long double   lognb(long double number, long double base)
{
    long double   value;
    long double   number_log;
    long double   base_log;

    if(number > 0 && base > 0 && base != 1)
    {
        number_log = logn(number);
        base_log = logn(base);
        value = number_log/base_log;
    }
    else
    {
        value = number;
    }

    return value;
}


//  Basic Root Function (Needs: Nothing);
long double   root(long double number, long long level)
{
    long double       value;
    long double       decrease;
    long double       aprox;
    long double       precision=1;
    long long     loop_end=1;
    long long     i;
    long long     exp_counter;
    long long     precision_level = PRECISIONRATE;

    //  Setting a precision level for the root;
    for(i=0; i<precision_level; i++)
    {
        precision = precision/10;
    }

   //   Initial attribuitions;
   decrease = 1;
   aprox = number;

   //   Parameter checking;
   if(number >= 0 && level >= 1)
   {
        //  The real thing
        while(loop_end==1)
        {
            exp_counter = level-1;
            value = aprox;
            while(exp_counter > 0)
            {
                value = value*aprox;
                exp_counter--;
            }
            if(value <= number && value == number)
            {
                loop_end = 0;
            }
            else if(value < number)
            {
                aprox = aprox + decrease;
                decrease = decrease/10;
                aprox = aprox - decrease;
                if(decrease < precision)
                {
                    loop_end = 0;
                }
            }
            else if(value > number)
            {
                aprox = aprox - decrease;
            }
        }

   }
   return aprox;
}


//##############################################################################################################################################################################################
//  Integer Functions;
//##############################################################################################################################################################################################

//  Factorial function (Needs: Nothing);
long long     factorial(long long number)
{
    long long i;
    long long value = number;

    if(number > 0)
    {
        for(i = number-1; i > 1; i--)
        {
            value = value*i;
        }
    }
    else if(number == 0)
    {
        value = 1;
    }
    return value;
}

//  Module long long (Needs: Nothing);
long long     modulei(long long number)
{
    long long number_rec = number;
    if(number<0)
    {
        number_rec= -number_rec;
    }
    return number_rec;
}

//  Nth Prime number (Needs: Nothing);
long long     prime(long long number)
{
    long long i = 1;
    long long div = 1;
    long long root = 1;
    long long div_count = 0;
    long long value = 0;

    for(value = 2; i < number; value+=2)
    {
        for(div = 1; root <= value && div_count <= 2; div++)
        {
            root = div*div;

            if(value%div == 0)
            {
                div_count++;
            }

        }
        if(div_count == 1)
        {
            i++;
        }
        else if(value == 2)
        {
            i++;
            value--;
        }
        div_count = 0;
        root = 1;
    }

    return value;
}

//  Round Down long double to long long (Needs: modulef);
long long     round_down(long double number)
{
    long double number_rec;
    long long i;

    number_rec = number;
    number_rec = modulef(number_rec);
    for(i = 0; i < number_rec; i++)
    {
        ;
    }
    if(i != number)
    {
        i--;
    }
    if(number<0)
    {
        i = -i;
    }
    return i;
}

//  Round Up long double to long long (Needs: modulef);
long long     round_up(long double number)
{
    long double number_rec;
    long long i;

    number_rec = number;
    number_rec = modulef(number_rec);
    for(i = 0; i < number_rec; i++)
    {
        ;
    }
    if(number<0)
    {
        i = -i;
    }
    return i;
}



//  Prints a message (Up to 256 characters, ending with ": " and scans an integer) (Needs: Nothing);
long long     pscani(char starray[256])
{
    long long i;
    long long value;

    for(i = 0; i<256; i++)
    {
        printf("%c", starray[i]);
        if(starray[i-1] == ':')
        {
            break;
        }
    }
    scanf("%Ld", &value);

    return value;
}



//  Combinations (Binomial coefficient) (Needs: factorial);
long long     combinations(long long number, long long k)
{
    long long value = number;
    if(number >= k)
    {
        value = factorial(number)/factorial(k);
        value = value/factorial(number-k);
    }
    return value;

}

//  Falling factorial (Needs: factorial);
long long     falling_factorial(long long number, long long k)
{
    long long value = number;
    if(number >= k)
    {
        value = factorial(number)/factorial(k);
    }
    return value;
}

//  Greatest common divisor (Needs: Nothing);
long long     gcd(long long number1, long long number2)
{
    long long div = 1;
    long long value = 1;


    for(div = 1; div > number1 || div > number2; div++)
    {
        if(number1%div == 0 && number2%div == 0)
        {
            value = div;
        }
    }

    return value;
}

//  Lowest common denominator (Needs: Nothing);
long long     lcd(long long number1, long long number2)
{
    long long mult = 1;
    long long value = 1;

    for(mult = number1*number2; mult > 1 && mult > number1 && mult > number2; mult--)
    {
        if(mult%number1 == 0 && mult%number2 == 0)
        {
            value = mult;
        }
    }

    return value;
}


//##############################################################################################################################################################################################
//  Main;
//##############################################################################################################################################################################################

//  Main test function
long long     mane()
{
    complex  answer;
    complex  level;
    complex  matrix1[XMAX][YMAX];
    complex  matrix2[XMAX][YMAX];
    complex  iunit = attribp(1,90);
    floaty   num1;
    floaty   num2;
    floaty   num3;
    floaty   num4;
    inty     n;


    n = pscani("Digite o tamanho da matriz: ");

    fillcmatrix(matrix1, n, n);
    printf("\n\n");
    printcmatrix(matrix1, n, n);
    printf("\n\n");
    answer = determinant(matrix1, n);
    printf("\n\nDeterminant:");
    printc(answer);


    level = pscancr("\n\nDigite o valor do numero complexo: ");
    printf("Hyperbolic cosine:\n");
    answer = cosinehc(level);
    printc(answer);
    printf("Cosine:\n");
    answer = cosinec(level);
    printc(answer);
    printf("Hyperbolic Sine Operation:\n");
    answer = cosinehc(mulc(level, iunit));
    printc(answer);

    return 0;
}
