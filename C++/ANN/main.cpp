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
	Neural_Network nxor(3, wid);
	nxor.overwrite_constrainer_function(my_constrainer);

	nxor.load_network("./config/");

	cout << endl << "Feeding 1,1" << endl;
	nxor.feed_forward(1.0);
	nxor.print_state();
	nxor.feed_forward(1.0);
	nxor.print_state();

	cout << endl << "Feeding 0,0" << endl;
	nxor.feed_forward(0.0);
	nxor.print_state();
	nxor.feed_forward(0.0);
	nxor.print_state();

	cout << endl << "Feeding 0,1" << endl;
	nxor.feed_forward(0.0);
	nxor.print_state();
	nxor.feed_forward(1.0);
	nxor.print_state();

	cout << endl << "Feeding 1,0" << endl;
	nxor.feed_forward(1.0);
	nxor.print_state();
	nxor.feed_forward(0.0);
	nxor.print_state();

	return 0;
}
