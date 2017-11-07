#include <iostream>
#include "ann.h"

using namespace std;

Real relu(Real arg)
{
	return ((arg > 0) ? arg : 0);
}

Real relu_dvt(Real arg)
{
	return ((arg > 0) ? 1 : 0);
}

int main()
{
	int wid[3] = {2,3,1};
	Neural_Network nxor("./config/");
	nxor.overwrite_constrainer_function(relu, relu_dvt);

	Real des_out[1] = {0.5};
	Real des_inp[2] = {0.5, 0.5};

	Real evar;
	evar = nxor.learn(des_inp, des_out);
	cout << "Total error: " << evar << endl;
	cout << endl;

	for(int i = 0; i < 0; i++)
	{
		nxor.learn(des_inp, des_out);
		nxor.update_neurons();
	}

	evar = nxor.learn(des_inp, des_out);
	cout << "Total error: " << evar << endl;
	cout << endl;
	return 0;
}
