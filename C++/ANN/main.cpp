#include <iostream>
#include "ann.h"


using namespace std;

Out_t random_inp()
{
	return (rand()%50000)/50000.0;
}

Out_t foo(Out_t a)
{
	return (!a ? 1 : 0.824941893*(sin(6.2831*a)/(6.2831*a) + 0.2122066));
	return 1 - a;
}

int main()
{

	return 0;
}
