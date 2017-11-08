#include <iostream>
#include "ann.h"


using namespace std;

Real foo(Real a)
{
	return 1 - a;
	return 1/(1 + exp(-a));
}

Real bar(Real a[])
{
	//return 10;
	Real ret = foo(a[0]);
	return ret*ret;
}

int main()
{
	int wid[4] = {1, 10, 10, 1};
	Neural_Network neu(4, wid);

	Real a[1];
	a[0] = 0.5;
	cout << "Bar of 0.5 = " << bar(a) << endl;
	neu.feed(0.5);
	neu.run();
	cout << "Neural network for 0.5 = " << neu.results[0] << endl;


	int j = 0;
	for(int k = 0; k < 1000; k++)
	{
		for(Real i = 0; i < 1; i += 0.0001)
		{
			Real inp[1];
			Real outp[1];

			inp[0] = i;
			outp[0] = bar(inp);

			Real evar = neu.learn(inp, outp);
			if(evar < -100)
			{
				cout << "Evar = " << evar << endl;
				cout << "Break at " << i << endl;
				i = 10.0;
			}
			if((i < -1.99 || i > 6.99 ) && 0)
			{
				cout << "Error = ";
				cout << evar << endl;
			}

			if(j > 1000)
			{
				neu.update_neurons();
				j = 0;
			}
			else
			{
				j++;
			}
		}
	}
	//eu.print_all_neurons();
	cout << "Bar of 0.5 = " << bar(a) << endl;
	neu.feed(0.5);
	neu.run();
	cout << "Neural network for 0.5 = " << neu.results[0] << endl;

	return 0;
}
