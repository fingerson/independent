#ifndef ANN_H
#define ANN_H

#include <new> // Operator new[]
#include <cstring> // memcpy
#include <string> // string class
#include <sstream> // For string stream
#include <iostream> // cin and cout
#include <fstream> // reading and writing from and to files

typedef int 	Integer;
typedef	float 	Real;

class Neural_Network
{
	// Nested structural class Neuron
	class Neuron
	{
	public:
		// The [0,1] output of the neuron
		Real	out;
		// The weigths of each input
		Real*	weigth;
		// The neuron bias
		Real	bias;

		Neuron();
		~Neuron();

		void load_from_file(const char* file_name,
				    Integer number_of_inputs);
		void save_in_file(const char* file_name,
				  Integer number_of_inputs);
		void set_number_of_inputs(const Integer inputs);
	};
private:
	/* Holds the depth (how many layers) the network has.
	 * Note that depth has to be at least 2, because of the
	 * input and the output layer.
	 */
	Integer		depth;
	// An array that hold how large is each layer
	Integer*	width;
	// Last element of the entry layer
	Integer		last_fed;
	// The matricial system that holds the neurons
	Neuron**	network;
	// The constrainer function to set the values to [0,1]
	Real		(*constrainer)(Real);

public:
	// The results of the last layer
	Real*		results;

	Neural_Network(const char*	config_file);
	Neural_Network(const Integer	def_depth,
		       const Integer 	def_width[]);
	~Neural_Network();

	void clear(void);

	void feed(Real entry);

	void feed_forward(Real entry);

	void forward(void);

	void load_network(const char* folder_address);

	void overwrite_constrainer_function(Real (*foo)(Real));

	void print_neuron(Integer layer, Integer position);

	void print_state(void);

	void run(void);

	void save_network(const char* folder_address);

	void set_weight_at_neuron(Integer 	layer,
				  Integer	position,
				  Real		def_weight[],
			  	  Real 		def_bias);

};

Real default_constrainer(Real argument);

#endif // ANN_H
