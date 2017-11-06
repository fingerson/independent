#include <iostream>
#include "ann.h"

using namespace std;

Real my_constrainer(Real arg)
{
	//return arg;
	return (arg <= 0) ? 0 : 1;
}

int main()
{
	int wid[3] = {2,3,1};
	Neural_Network nxor("./config/");
	nxor.overwrite_constrainer_function(my_constrainer);

	nxor.feed_forward(1.0);
	nxor.feed_forward(0.0);
	nxor.run();

	cout << nxor.results[0] << endl;
	return 0;
}
