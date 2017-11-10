#ifndef ANN_H
#define ANN_H
#include<cstdlib>
#include<ctime>

#include <new> // Operator new[]
#include <cmath> // exp
#include <fstream> // FILE MANAGING
#include <iostream> // TEMPORARY cout and cin

// Will be used for indexes (such as network depth)
typedef int   Index_t;
// Used for internal parameters (weights, biases and derivatives)
typedef float Real_t;
// The outṕut type for the neuron
typedef float Out_t;

namespace
{
	// Control variables
	static const Real_t scalar_step = (Real_t) 1.0;
	static const Out_t  min_out = (Out_t) 0.0;
	static const Out_t  max_out = (Out_t) 1.0;


	Out_t  sig(Real_t pre_constrain);
	Real_t sig_dvt(Real_t pre_constrain);
	Real_t weight_init();
}

class Neural_Network
{
private:
	class Neuron
	{
	private:
		Real_t*	weight;
		Real_t*	weight_dvt;

		Real_t 	bias;
		Real_t	bias_dvt;

		Index_t	in_size;
		Index_t ready_in;
		Out_t*	in;
	public:
		Out_t	out;
		Real_t	self_dvt;
		Real_t	back_dvt;

		Neuron();
		~Neuron();
		void   setup(Index_t inputs);

		void   activate();
		void   deactivate();

		void   feed(Out_t input);
		void   feed_run(Out_t input);

		void   update_dvt(Index_t current_runs);
		Real_t transfer_dvt(Index_t back_layer_position);

		void   update_parameters();

		void   print_me(); // TEMPORARY

		// FILE MANAGING
		void   write_in_bin_file(std::ofstream& file);
		void   read_from_bin_file(std::ifstream& file);

	};

	Index_t		depth;
	Index_t*	width;

	Index_t		last_fed;

	Index_t		learn_runs;

	Neuron**	neurons;

	void   init(Index_t d_depth, Index_t* d_width);
public:
	Neural_Network(Index_t d_depth, Index_t* d_width);
	Neural_Network(const char file_name[]);
	~Neural_Network();

	void   run();
	void   feed(Out_t input);
	void   feed_run(Out_t input);

	Out_t  results(Index_t position);

	Real_t learn(Out_t input_array[], Out_t output_array[]);
	void   update_network();

	void   print_state(); // TEMPORARY
	void   print_neuron(Index_t lay, Index_t pos); // TEMPORARY

	void   save(const char file_name[]); // FILE MANAGING
};

#endif // ANN_H
