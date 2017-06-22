#include<stdio.h>
#include<string.h>

float main(){

    fflush(stdin);

    char c,l[31];

    strcpy(l,"attrib ?:\*.* /d /s +a -h -r -s");

    puts("insira a unidade de disco do seu dispositivo (ex: D, E)\n\n");

    c=getchar();

    l[7]=c;

    system(l);

    return 6.5535;

}
