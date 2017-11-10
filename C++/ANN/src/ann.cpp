#include "ann.h"

namespace
{
	// sig
	Out_t
	sig(Real_t pre_constrain)
	{
		// return ((pre_constrain > 0) ? pre_constrain : 0);
		return (max_out - min_out) /
		       (1 + exp(-pre_constrain)) +
		       min_out;
	}

	// sig_dvt
	Real_t
	sig_dvt(Real_t pre_constrain)
	{
		// return ((pre_constrain > 0) ? 1 : 0);
		Real_t exp_arg = 1 + exp(pre_constrain);
		return (max_out - min_out) *
		       (exp_arg - 1) /
		       (exp_arg * exp_arg);
	}

	// weight_init
	Real_t
	weight_init()
	{
		return 1;
		// return (rand()%50000)/50000.0 - 0.5;
	}

}
// NEURON CLASS

// Neuron constructor
Neural_Network::Neuron::Neuron()
{
	this->out      =   (Out_t) 0;
	this->bias     =   weight_init() - 1;

	this->bias_dvt =  (Real_t) 0;
	this->self_dvt =  (Real_t) 0;
	this->back_dvt =  (Real_t) 0;

	this->in_size  = (Index_t) 0;
}

// Neuron destructor
Neural_Network::Neuron::~Neuron()
{
	delete [] this->weight_dvt;
	delete [] this->weight;
	delete [] this->in;

	this->in_size = (Index_t) 0;
	this->ready_in = (Index_t) 0;
}

// setup
void
Neural_Network::Neuron::setup(Index_t inputs)
{
	this->in_size    = inputs;

	this->weight 	 = new Real_t[inputs];
	this->weight_dvt = new Real_t[inputs];
	this->in	 = new  Out_t[inputs];

	for(Index_t i = 0; i < inputs; i++)
	{
		this->weight[i]     = weight_init();
		this->weight_dvt[i] = (Real_t) 0;
	}
}


// activate
void
Neural_Network::Neuron::activate()
{
	// Ensures the deactivation of the derivatives
	// this->deactivate();

	this->ready_in = (Index_t) 0;
	Real_t	pre_constrain = (Real_t) 0;
	for(Index_t i = 0; i < this->in_size; i++)
	{
		pre_constrain += this->weight[i] * this->in[i];
	}
	pre_constrain += this->bias;
	this->self_dvt = sig_dvt(pre_constrain);
	this->out      = sig(pre_constrain);
}

// deactivate
void
Neural_Network::Neuron::deactivate()
{
	this->self_dvt = (Real_t) 0;
	this->back_dvt = (Real_t) 0;
	// this->out = (Out_t) 0;
}

// feed
void
Neural_Network::Neuron::feed(Out_t input)
{
	if(this->ready_in < this->in_size)
	{
		this->in[this->ready_in] = input;
		this->ready_in++;
	}
}

// update_dvt
void
Neural_Network::Neuron::update_dvt(Index_t current_runs)
{
	this->bias_dvt = (this->bias_dvt*current_runs +
			  this->self_dvt * this->back_dvt)/
			  (current_runs + 1);

	for(Index_t i = 0; i < this->in_size; i++)
	{
		this->weight_dvt[i] = (this->weight_dvt[i] *
			 	       current_runs +
				       this->self_dvt *
				       this->back_dvt *
				       this->in[i]) /
				      (current_runs + 1);
	}
}

// transfer_dvt
Real_t
Neural_Network::Neuron::transfer_dvt(Index_t back_layer_position)
{
	return this->weight[back_layer_position] *
	       this->self_dvt *
	       this->back_dvt;
}

// update_parameters
void
Neural_Network::Neuron::update_parameters()
{
	this->bias -= scalar_step*bias_dvt;
	this->bias_dvt = (Real_t) 0;

	for(Index_t i = 0; i < this->in_size; i++)
	{
		this->weight[i] -= scalar_step*this->weight_dvt[i];
		this->weight_dvt[i] = (Real_t) 0;
	}
}

// write_in_bin_file
void
Neural_Network::Neuron::write_in_bin_file(std::ofstream& file)
{
	// Writing weights
	file.write(reinterpret_cast<const char *>(this->weight),
	 	   this->in_size*sizeof(Real_t));

	// Writing bias
	file.write(reinterpret_cast<const char *>(&(this->bias)),
	 	   sizeof(Real_t));
}

// read_from_bin_file
void
Neural_Network::Neuron::read_from_bin_file(std::ifstream& file)
{
	// Reading the weights
	file.read(reinterpret_cast<char *>(this->weight),
		  this->in_size * sizeof(Real_t));

	// Reading the bias
	file.read(reinterpret_cast<char *>(&(this->bias)),
	 	  sizeof(Real_t));
}

// NEURAL NETWORK CLASS

// Neural_Network constructor
Neural_Network::Neural_Network(Index_t d_depth, Index_t* d_width)
{
	this->init(d_depth, d_width);
}

// Neural_Network from file constructor
Neural_Network::Neural_Network(const char file_name[])
{
	std::ifstream bin_file;
	bin_file.open(file_name, std::ios::binary | std::ios::in);

	if(!bin_file.is_open())
	{
		return;
	}

	// Checking if the size of the typedefs is valid
	{
		char type_size;
		// Reading Index_t size
		bin_file.read(&type_size, sizeof(char));

		if(type_size != sizeof(Index_t))
		{
			return;
			// Type incongruence;
		}

		// Reading Real_t size
		bin_file.read(&type_size, sizeof(char));
		if(type_size != sizeof(Real_t))
		{
			return;
			// Type incongruence;
		}

		// Reading Out_t size
		bin_file.read(&type_size, sizeof(char));
		if(type_size != sizeof(Out_t))
		{
			return;
			// Type incongruence;
		}
	}

	// Initializing the neural network
	{
		std::cout << "HERE" << std::endl;
		// Loading up the depth element
		Index_t def_depth;
		bin_file.read(
			reinterpret_cast<char *>(&def_depth),
			sizeof(Index_t));

		// Creating an array to hold the weights
		Index_t* def_width = new Index_t[def_depth];
		// Loading the array with the widths
		bin_file.read(
			reinterpret_cast<char *>(def_width),
			def_depth*sizeof(Index_t));

		this->init(def_depth, def_width);

		delete [] def_width;
	}

	for(Index_t i = 0; i < this->depth; i++)
	{
		for(Index_t j = 0; j < this->width[i]; j++)
		{
			this->neurons[i][j]
			.read_from_bin_file(bin_file);
		}
	}
}

// Neural_Network destructor
Neural_Network::~Neural_Network()
{
	for(Index_t i = 0; i < this->depth; i++)
	{
		delete [] this->neurons[i];
	}
	delete [] this->neurons;

	this->depth = (Index_t) 0;
	delete [] this->width;
}

// init
void
Neural_Network::init(Index_t d_depth, Index_t* d_width)
{
	srand(time(0)); // RAMDOMNESS
	this->last_fed   = (Index_t) 0;
	this->learn_runs = (Index_t) 0;

	this->depth = d_depth;

	this->width = new Index_t[d_depth];
	for(Index_t i = 0; i < d_depth; i++)
	{
		this->width[i] = d_width[i];
	}

	this->neurons = new Neuron*[this->depth];
	for(Index_t i = 0; i < this->depth; i++)
	{
		this->neurons[i] = new Neuron[this->width[i]];

		Index_t inputs = (Index_t) 0;
		if(i)
		{
			inputs = this->width[i - 1];
		}
		for(Index_t j = 0; j < this->width[i]; j++)
		{
			this->neurons[i][j].setup(inputs);
		}
	}
}

// run
void
Neural_Network::run()
{
	this->last_fed = (Index_t) 0;

	for(Index_t i = 0; i < this->depth - 1; i++)
	{
		for(Index_t j = 0; j < this->width[i]; j++)
		{
			if(i)
			{
				this->neurons[i][j].activate();
				// this->print_neuron(i,j);
			}
			for(Index_t k = 0; k< this->width[i+1]; k++)
			{
				// std::cout << "Entered when i = "
				// 	  << i
				// 	  << " and j = "
				// 	  << j
				// 	  << ", my output was: "
				// 	  << this->neurons[i][j].out
				// 	  << std::endl;
				this->neurons[i+1][k].feed(
					this->neurons[i][j].out);
			}
		}
		// this->print_state(); // TEMPORARY
	}

	for(Index_t i = 0; i < this->width[this->depth - 1]; i++)
	{
		this->neurons[this->depth - 1][i].activate();
	}
	// this->print_state(); // TEMPORARY
}

// feed
void
Neural_Network::feed(Out_t input)
{
	if(this->last_fed < this->width[0])
	{
		this->neurons[0][this->last_fed].out = input;
		this->last_fed++;
	}
}

// feed_run
void
Neural_Network::feed_run(Out_t input)
{
	if(this->last_fed < this->width[0])
	{
		this->neurons[0][this->last_fed].out = input;
		this->last_fed++;
		if(this->last_fed = this->width[0])
		{
			this->last_fed = 0;
			this->run();
		}
	}
	else
	{
		this->last_fed = (Index_t) 0;
		this->neurons[0][0].out = input;
		this->run();
	}
}

// results
Out_t
Neural_Network::results(Index_t position)
{
	if(position >= 0 && position < this->width[this->depth - 1])
	{
		return this->neurons[this->depth - 1][position].out;
	}
	return (Out_t) 0;
}

// learn
Real_t
Neural_Network::learn(Out_t input_array[], Out_t output_array[])
{
	this->last_fed = 0;
	for(Index_t i = 0; i < this->width[0]; i++)
	{
		this->feed(input_array[i]);
	}
	run();

	Real_t total_error = (Real_t) 0;
	for(Index_t i = 0; i < this->width[this->depth - 1]; i++)
	{
		Real_t neuron_error;
		neuron_error  = this->neurons[this->depth-1][i].out;
		neuron_error -= output_array[i];

		this->neurons[this->depth-1][i].back_dvt +=
			neuron_error;

		total_error += neuron_error*neuron_error;
	}
	total_error /= 2.0;

	for(Index_t i = this->depth - 1; i > 0; i--)
	{
		for(Index_t j = 0; j < this->width[i]; j++)
		{
			if(i != 1)
			{
				for(Index_t k = 0;
				    k < this->width[i-1];
				    k++)
				{
					this->neurons[i-1][k]
						.back_dvt +=
					this->neurons[i][j]
						.transfer_dvt(k);
				}
			}
			this->neurons[i][j]
			.update_dvt(this->learn_runs);
			this->neurons[i][j].deactivate();
		}
	}

	this->learn_runs++;
	return total_error;
}

// update_network
void
Neural_Network::update_network()
{
	this->learn_runs = (Index_t) 0;
	for(Index_t i = 0; i < this->depth; i++)
	{
		for(Index_t j = 0; j < this->width[i]; j++)
		{
			this->neurons[i][j].update_parameters();
		}
	}
}

// save
void
Neural_Network::save(const char file_name[])
{
	std::ofstream bin_file;
	bin_file.open(file_name, std::ios::binary | std::ios::out);
	if(!bin_file.is_open())
	{
		return;
	}

	// Writing the size of the typedefs in file
	{
		// Index_t type size
		char type_size = sizeof(Index_t);
		bin_file.write(&type_size, sizeof(char));

		// Real_t type size
		type_size = sizeof(Real_t);
		bin_file.write(&type_size, sizeof(char));

		// Out_t type size
		type_size = sizeof(Out_t);
		bin_file.write(&type_size, sizeof(char));
	}

	// Writing the depth and width parameters;
	bin_file.write(
		reinterpret_cast<const char *>(&(this->depth)),
	 	sizeof(Index_t));
	bin_file.write(reinterpret_cast<const char *>(this->width),
		       this->depth * sizeof(Index_t));

	for(Index_t i = 0; i < this->depth; i++)
	{
		for(Index_t j = 0; j < this->width[i]; j++)
		{
			this->neurons[i][j]
			.write_in_bin_file(bin_file);
		}
	}
	bin_file.close();

}

// TEMPORARY

using namespace std;

void
Neural_Network::print_state()
{
	for(Index_t i = 0; i < this->depth; i++)
	{
		for(Index_t j = 0; j < this->width[i]; j++)
		{
			cout << this->neurons[i][j].out << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void
Neural_Network::print_neuron(Index_t lay, Index_t pos)
{
	cout << "Neuron at layer "
	     << lay
	     << " and position "
	     << pos
	     << endl
	     << endl;

	this->neurons[lay][pos].print_me();
}

void
Neural_Network::Neuron::print_me()
{
	cout << "Output: " << this->out << endl;

	cout << "Inputs: { ";
	for(Index_t i = 0; i < this->in_size; i++)
	{
		cout << this->in[i] << " ";
	}
	cout << "}" << endl;

	cout << "Weights: { ";
	for(Index_t i = 0; i < this->in_size; i++)
	{
		cout << this->weight[i] << " ";
	}
	cout << "}" << endl;

	cout << "Weight derivatives: { ";
	for(Index_t i = 0; i < this->in_size; i++)
	{
		cout << this->weight_dvt[i] << " ";
	}
	cout << "}" << endl;

	cout << "Bias: " << this->bias << endl;
	cout << "Bias derivative: " << this->bias_dvt << endl;
	cout << "Self derivative: " << this->self_dvt << endl;
	cout << "Back derivative: " << this->back_dvt << endl;
}
