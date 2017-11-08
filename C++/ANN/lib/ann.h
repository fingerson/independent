#ifndef ANN_H
#define ANN_H

#include <new> // Operator new[]
#include <cstring> // memcpy
#include <string> // string class
#include <sstream> // For string stream
#include <iostream> // cin and cout
#include <fstream> // reading and writing from and to files
#include <cmath> // For expsig

typedef int 	Integer;
typedef	float 	Real;

namespace
{
	Real 	sig(Real argument);
	Real 	sig_dvt(Real argument);
	Real 	weigth_initializer(void);
	Real 	bias_initialzer(void);
	Real 	out_initializer(void);
}

class Neural_Network
{
private:
	// Nested structural class Neuron
	class Neuron
	{
	public:
		// The [0,1] output of the neuron
		Real	out;
		// The weigths of each input
		Real*	weigth;
		// The avarage request of change for each weigths
		Real* 	weigth_avg_dvt;
		// The neuron bias
		Real	bias;
		// The neuron average change request
		Real	bias_avg_dvt;
		// The neuron self derivative
		Real 	self_dvt;
		// The neuron back propagation derivative
		Real	back_dvt;

		Neuron();
		~Neuron();

		void load_from_file(const char* file_name,
				    Integer number_of_inputs);
		void save_in_file(const char* file_name,
				  Integer number_of_inputs);
		void set_number_of_inputs(const Integer inputs);
		void update(Integer inputs);
	};

	/* Holds the depth (how many layers) the network has.
	 * Note that depth has to be at least 2, because of the
	 * input and the output layer.
	 */
	Integer		depth;
	// An array that hold how large is each layer
	Integer*	width;
	// Last element of the entry layer
	Integer		last_fed;
	// The number of learn runs done from last update
	Integer		learn_runs;
	// The matricial system that holds the neurons
	Neuron**	network;
	// The constrainer function to set the values to [0,1]
	Real		(*constrainer)(Real);
	// The constrainer derivative FUNCTIONS
	Real		(*constrainer_derivative)(Real);

	void load_network(const char* folder_address);

	void set_weight_at_neuron(Integer 	layer,
				  Integer	position,
				  Real		def_weight[],
			  	  Real 		def_bias);

public:
	// The results of the last layer
	Real*		results;

	Neural_Network(const char*	config_file);
	Neural_Network(const Integer	def_depth,
		       const Integer 	def_width[]);

        //~Neural_Network();

	void clear(void);

	void feed(Real entry);

	void feed_forward(Real entry);

	void forward(void);

	Real learn(Real input_array[], Real desired_output[]);

	void overwrite_constrainer_function(Real (*foo)(Real),
					    Real (*dvt)(Real));

	void print_all_neurons(void);

	void print_neuron(Integer layer, Integer position);

	void print_state(void);

	void run(void);

	void save_network(const char* folder_address);

	void update_neurons(void);

};


#endif // ANN_H
