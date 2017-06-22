#include    "mathematics.h"

main ()
{

    complex  answer;
    complex  level;
    complex  base;
    complex  matrix1[XMAX][YMAX];
    complex  matrix2[XMAX][YMAX];
    complex  iunit = attribp(1,90);
    floaty   num1;
    floaty   num2;
    floaty   num3;
    floaty   num4;
    inty     n;

    for(int i=-360; i<361; i++)
    {
        nl(1);
        printf("%8d      %8Lf", i, arccosine(cosine(i)));
    }

    return 0;
}
