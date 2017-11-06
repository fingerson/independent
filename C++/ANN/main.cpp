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
	Neural_Network my_neurons(3, wid);
	my_neurons.overwrite_constrainer_function(my_constrainer);

	/*
	Real l0_0[1] = {1.0};
	Real l0_1[1] = {1.0};

	Real l1_0[2] = {1.0, 0.0};
	Real l1_1[2] = {1.0, 1.0};
	Real l1_2[2] = {0.0, 1.0};

	Real l2_0[3] = {1.0, -2.0, 1};

	my_neurons.set_weight_at_neuron(0, 0, l0_0, 0);
	my_neurons.set_weight_at_neuron(0, 1, l0_1, 0);

	my_neurons.set_weight_at_neuron(1, 0, l1_0, 0);
	my_neurons.set_weight_at_neuron(1, 1, l1_1, -1.1);
	my_neurons.set_weight_at_neuron(1, 2, l1_2, 0);

	my_neurons.set_weight_at_neuron(2, 0, l2_0, 0);

	my_neurons.save_network("/home/diogo/.Programming/C++/ANN/config/");
	*/

	my_neurons.load_network("");

	my_neurons.feed(0.0);
	my_neurons.feed(1.0);
	my_neurons.run();
	/*
	cout << endl << "Initial state" << endl;
	my_neurons.print_state();

	cout << endl << "Fist forward" << endl;
	my_neurons.forward();
	my_neurons.print_state();
	cout << endl << "Result: "<< my_neurons.results[0] << endl;

	cout << endl << "Second forward" << endl;
	my_neurons.forward();
	my_neurons.print_state();
	cout << endl << "Result: "<< my_neurons.results[0] << endl;

	cout << endl << "Third forward" << endl;
	my_neurons.forward();
	my_neurons.print_state();
	cout << endl << "Result: "<< my_neurons.results[0] << endl;

	cout << endl << "Fourth forward" << endl;
	my_neurons.forward();
	my_neurons.print_state();
	*/
	cout << endl << "Result: "<< my_neurons.results[0] << endl;
	return 0;
}
