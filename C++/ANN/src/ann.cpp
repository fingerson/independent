#include "ann.h"

namespace{
	// OTHER FUNCTIONS

	// default_constrainer
	Real
	default_constrainer(Real argument)
	{
		if(argument <= 0.0)
		{
			return 0.0;
		}
		else
		{
			return argument/(argument + 1);
		}
	}

	Real
	default_constrainer_derivative(Real argument)
	{
		if(argument < 0)
		{
			return (Real) 0;
		}
		return 1/((argument + 1)*(argument + 1));
	}

	Real
	weigth_initializer(void)
	{
		return (Real) 1;
	}

	Real
	bias_initialzer(void)
	{
		return (Real) 1;
	}

	Real
	out_initializer(void)
	{
		return (Real) 0;
	}

}

// NEURON CLASS

// Neuron constructor
Neural_Network::Neuron::Neuron()
{
	this->self_dvt = (Real) 0;
	this->back_dvt = (Real) 0;
	this->out = out_initializer();
	this->bias = bias_initialzer();
}

// Neuron destructor
Neural_Network::Neuron::~Neuron()
{
	delete [] this->weigth;
}

// load_from_file (WORKS WITH FILES)
void
Neural_Network::Neuron::load_from_file(const char* file_name,
				       Integer number_of_inputs)
{
	std::ifstream conf_file(file_name);
	if(conf_file.is_open())
	{
		conf_file >> this->bias;

		for(Integer i = 0; i < number_of_inputs; i++)
		{
			conf_file >> this->weigth[i];
		}
		conf_file.close();
	}
	else
	{
		// Error opening file;
	}
}

// save_in_file (WORKS WITH FILES)
void
Neural_Network::Neuron::save_in_file(const char* file_name,
				     Integer number_of_inputs)
{
	std::ofstream config_file(file_name);
	if(config_file.is_open())
	{
		config_file << this->bias << " ";
		for(Integer i = 0; i < number_of_inputs; i++)
		{
			config_file << this->weigth[i] << " ";
		}
		config_file.close();
	}
	else
	{
		// Error opening file
	}
}

// set_number_of_inputs
void
Neural_Network::Neuron::set_number_of_inputs(const Integer inputs)
{
	this->weigth = new Real[inputs];
	this->weigth_avg_dvt = new Real[inputs];
	for(Integer i = 0; i < inputs; i++)
	{
		this->weigth[i] = weigth_initializer();
		this->weigth_avg_dvt[i] = (Real) 0;
	}
}

void
Neural_Network::Neuron::update(Integer inputs)
{
	this->bias -= scalar_step*this->bias_avg_dvt;
	for(Integer i = 0; i < inputs; i++)
	{
		this->weigth[i] -= scalar_step *
				   this->weigth_avg_dvt[i];
	}
}

// NEURAL_NETWORK CLASS

// Neural Network constructor from config file (WORKS WITH FILES)
Neural_Network::Neural_Network(const char*	config_folder)
{
	// Initializing constrainer function pointer
	this->constrainer = default_constrainer;

	// Initializing the constrainer derivative function pointer
	this->constrainer_derivative =
	default_constrainer_derivative;

	// Initializing last_fed index;
	this->last_fed = 0;

	// Initializing the learn runs;
	this->learn_runs = 0;

	std::string file_name(config_folder);
	file_name += "neural_settings.config";
	std::ifstream conf_file(file_name.c_str());
	if(conf_file.is_open())
	{
		conf_file >> this->depth;
		this->width = new Integer[depth];
		for(Integer i = 0; i < this->depth; i++)
		{
			conf_file >> this->width[i];
		}

		// Initializing the results vector;
		this->results =new Real[this->width[this->depth-1]];
		for(Integer i=0; i< this->width[this->depth-1]; i++)
		{
			this->results[i] = 0.0;
		}

		// Initializing the neurons
		this->network = new Neuron*[this->depth];
		for(Integer i = 0; i < this->depth; i++)
		{

			this->network[i] =
			new Neuron[this->width[i]];

			for(Integer j = 0; j < this->width[i]; j++)
			{
				Integer inputs = 1;
				if(!i)
				{
					inputs = this->width[i-1];
				}
				this->network[i][j].
				set_number_of_inputs(inputs);
			}
		}
		conf_file.close();
		this->load_network(config_folder);

	}
	else
	{
		// Error opening file
	}
}

// Neural Network constructor
Neural_Network::Neural_Network(const Integer	def_depth,
	       		       const Integer 	def_width[])
{
	// Initializing constrainer function pointer
	this->constrainer = default_constrainer;

	// Initializing the constrainer derivative function pointer
	this->constrainer_derivative =
	default_constrainer_derivative;

	// Initializing last_fed index;
	this->last_fed = 0;

	// Initializing the learn runs;
	this->learn_runs = 0;

	// Initialing the saved depth;
	this->depth = def_depth;

	// Initializing the depth vector;
	this->width = new Integer[def_depth];
	std::memcpy(this->width,
		    def_width,
		    sizeof(Integer)*def_depth);

	// Initializing the results vector;
	this->results = new Real[def_width[def_depth - 1]];
	for(Integer i = 0; i < def_width[def_depth - 1]; i++)
	{
		this->results[i] = 0.0;
	}

	// Initializing the neurons
	this->network = new Neuron*[def_depth];
	for(Integer i = 0; i < def_depth; i++)
	{

		this->network[i] = new Neuron[def_width[i]];

		for(Integer j = 0; j < def_width[i]; j++)
		{
			Integer inputs = 1;
			if(!i)
			{
				inputs = def_width[i-1];
			}
			network[i][j].set_number_of_inputs(
						inputs);

		}
	}

}

// Neural Network destructor
Neural_Network::~Neural_Network()
{
	for(Integer i = 0; i < this->depth; i++)
	{
		for(Integer j = 0; j < this->width[i]; j++)
		{
			this->network[i][j].~Neuron();
		}
	}
	delete [] this->network;
	delete [] this->results;
	delete [] this->width;

	this->depth = (Integer) 0;
	this->last_fed = (Integer) 0;
}

// clear
void
Neural_Network::clear(void)
{
	for(int i = 0; i < this->depth; i++)
	{
		for(int j = 0; j < this->width[i]; j++)
		{
			this->network[i][j].out = (Real) 0;
			this->network[i][j].self_dvt = (Real) 0;
			this->network[i][j].back_dvt = (Real) 0;
		}
	}
}

// feed
void
Neural_Network::feed(Real entry)
{
	if(this->last_fed >= this->width[0])
	{
		return;
	}

	this->network[0][last_fed].out = entry;
	last_fed++;
}

// feed forward
void
Neural_Network::feed_forward(Real entry)
{
	if(this->last_fed >= this->width[0])
	{
		this->forward();
	}
	this->network[0][last_fed].out = entry;
	last_fed++;
}

// forward
void
Neural_Network::forward(void)
{
	this->last_fed = 0;
	for(Integer i = 0; i < this->width[this->depth - 1]; i++)
	{
		results[i] = this->network[this->depth - 1][i].out;
		this->network[this->depth - 1][i].out = 0;
	}

	for(Integer i = this->depth - 1; i > 0; i--)
	{
		for(Integer j = 0; j < this->width[i]; j++)
		{
			Real pre_constrain = (Real) 0;
			for(Integer k = 0; k < this->width[i - 1]; k++)
			{
				pre_constrain +=
				this->network[i][j].weigth[k] *
				this->network[i - 1][k].out;
			}
			pre_constrain += this->network[i][j].bias;
			this->network[i][j].self_dvt =
			this->constrainer_derivative(pre_constrain);
			this->network[i][j].out =
			this->constrainer(pre_constrain);
		}

		// Free last layer
		for(Integer j = 0; j < this->width[i - 1]; j++)
		{
			this->network[i - 1][j].out = 0.0;
		}
	}
}

// learn
Real
Neural_Network::learn(Real input_array[], Real desired_output[])
{
	for(Integer i = 0; i < this->width[0]; i++)
	{
		this->feed(input_array[i]);
	}
	this->run();
	Real error = (Real) 0;
	Integer i;

	// Calculating the total error
	// Attributing last layer neurons' back derivative
	for(i = 0; i < this->width[this->depth - 1]; i++)
	{
		Real single_neuron_error = this->results[i] -
					   desired_output[i];
		this->network[this->depth - 1][i].back_dvt =
		single_neuron_error;

		error += single_neuron_error * single_neuron_error;
	}
	error /= 2;

	for(Integer i = this->depth - 1; i >= 1; i--)
	{
		for(Integer j = 0; j < this->width[i]; j++)
		{
			for(Integer k = 0; k< this->width[i-1]; k++)
			{
				// Updating back derivative of the
				// previous layer
				if(i != 1)
				{
					this->network[i-1][k]
					.back_dvt +=
					this->network[i][j]
					.self_dvt *
					this->network[i][j]
					.back_dvt *
					this->network[i][j]
					.weigth[k];
				}

				// Updating weigth derivative
				this->network[i][j].weigth_avg_dvt
				[k] *= this->learn_runs;

				this->network[i][j].weigth_avg_dvt
				[k] += this->network[i][j].self_dvt*
				this->network[i][j].back_dvt *
				this->network[i-1][k].out;

				this->network[i][j].weigth_avg_dvt
				[k] /= (this->learn_runs + 1);
			}
			// Updating the bias derivative
			this->network[i][j].bias_avg_dvt *=
			this->learn_runs;

			this->network[i][j].bias_avg_dvt +=
			(this->network[i][j].self_dvt *
			 this->network[i][j].back_dvt);

			this->network[i][j].bias_avg_dvt /=
			(this->learn_runs + 1);
		}
	}
	this->learn_runs++;

	return error;
}

// load_network
void
Neural_Network::load_network(const char* folder_address)
{
	for(Integer i = 0; i < this->width[0]; i++)
	{
		Real w0[1] = {(Real) 1};
		this->set_weight_at_neuron(0, i, w0, (Real) 0);
	}
	for(Integer i = 1; i < this->depth; i++)
	{
		for(Integer j = 0; j < this->width[i]; j++)
		{
			std::string folder(folder_address);
			{
				std::ostringstream str1;
				str1 << "nl"
				     << i
				     << "p"
				     << j;
				folder += str1.str();
			}
			Integer number_of_inputs = 1;
			if(i)
			{
				number_of_inputs = this->width[i-1];
			}
			this->network[i][j].load_from_file(
				folder.c_str(), number_of_inputs);
		}
	}
}

// overwrite_constrainer_function
void
Neural_Network::overwrite_constrainer_function(Real (*foo)(Real),
					       Real (*dvt)(Real))
{
	this->constrainer = foo;
	this->constrainer_derivative = dvt;
}

// print_neuron
void
Neural_Network::print_neuron(Integer layer, Integer position)
{
	std::cout << "Neuron at layer "
		  << layer
		  << " and position "
		  << position
		  << std::endl;

	std::cout << "    Output: "
		  << this->network[layer][position].out
		  << std::endl;

	std::cout << "    Bias: "
		  << this->network[layer][position].bias
		  << std::endl;

	std::cout << "    Bias derivative : "
		  << this->network[layer][position].bias_avg_dvt
		  << std::endl;

	std::cout << "    Weigths: { ";
	Integer n_of_w = 1;
	if(layer)
	{
		n_of_w = this->width[layer - 1];
	}

	for(int i = 0; i < n_of_w; i++)
	{
		std::cout << this->network[layer]
			     [position].weigth[i]
		 	  << " ";
	}
	std::cout << "}" << std::endl;

	std::cout << "    Weigth derivatives: { ";
	for(int i = 0; i < n_of_w; i++)
	{
		std::cout << this->network[layer]
			     [position].weigth_avg_dvt[i]
			  << " ";
	}
	std::cout << "}" << std::endl;

	std::cout << "    Self Derivative: "
		  << this->network[layer][position].self_dvt
		  << std::endl;

	std::cout << "    Back Derivative: "
		  << this->network[layer][position].back_dvt
		  << std::endl;
}

// print_state
void
Neural_Network::print_state(void)
{
	for(int i = 0; i < this->depth; i++)
	{
		for(int j = 0; j < this->width[i]; j++)
		{
			std::cout << this->network[i][j].out << " ";
		}
		std::cout << std::endl;
	}
}

// run
void
Neural_Network::run(void)
{
	this->last_fed = 0;
	for(Integer i = 1; i < this->depth; i++)
	{
		for(Integer j = 0; j < this->width[i]; j++)
		{
			Real pre_constrain = (Real) 0;
			for(Integer k = 0; k < this->width[i - 1]; k++)
			{
				pre_constrain +=
				this->network[i][j].weigth[k] *
				this->network[i - 1][k].out;
			}
			pre_constrain += this->network[i][j].bias;
			this->network[i][j].self_dvt =
			this->constrainer_derivative(pre_constrain);
			this->network[i][j].out =
			this->constrainer(pre_constrain);
		}
	}

	for(Integer i = 0; i < this->width[this->depth - 1]; i++)
	{
		results[i] = this->network[this->depth - 1][i].out;
	}
}

// save_network
void
Neural_Network::save_network(const char* folder_address)
{
	// Saving each neuron setting
	for(Integer i = 1; i < this->depth; i++)
	{
		for(Integer j = 0; j < this->width[i]; j++)
		{
			std::string folder(folder_address);
			{
				std::ostringstream str1;
				str1 << "nl"
				     << i
				     << "p"
				     << j;
				folder += str1.str();
			}
			Integer number_of_inputs = 1;
			if(i)
			{
				number_of_inputs = this->width[i-1];
			}
			this->network[i][j].save_in_file(
				folder.c_str(), number_of_inputs);
		}
	}

	// Saving configurations
	std::string conf_file_name(folder_address);
	conf_file_name += "neural_settings.config";
	std::ofstream conf_file(conf_file_name.c_str());
	if(conf_file.is_open())
	{
		conf_file << this->depth << " ";
		for(int i = 0; i < this->depth; i++)
		{
			conf_file << this->width[i] << " ";
		}
		conf_file << folder_address << '\\';

		conf_file.close();
	}
	else
	{
		// Error opening file
	}

}

// set_weight_at_neuron
void
Neural_Network::set_weight_at_neuron(Integer	layer,
		     		     Integer	position,
		     	   	     Real	def_weight[],
			     	     Real	def_bias)
{
	Integer neuron_inputs = 1;
	if(layer)
	{
		neuron_inputs = this->width[layer - 1];
	}
	std::memcpy(this->network[layer][position].weigth,
		    def_weight,
	    	    neuron_inputs*sizeof(Real));
	this->network[layer][position].bias = def_bias;
}

void
Neural_Network::update_neurons(void)
{
	for(Integer i = 1; i < this->depth; i++)
	{
		for(Integer j = 1; j < this->width[i]; j++)
		{
			this->network[i][j]
			.update(this->width[i - 1]);
		}
	}
}
