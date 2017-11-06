#include "ann.h"


// NEURON CLASS

// Neuron constructor
Neural_Network::Neuron::Neuron()
{
	this->out = 0.0;
	this->bias = 1.0;
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
	for(Integer i = 0; i < inputs; i++)
	{
		weigth[i] = 1.0;
	}
}

// NEURAL_NETWORK CLASS

// Neural Netwok constructor
Neural_Network::Neural_Network(const Integer	def_depth,
	       		       const Integer 	def_width[])
{
	// Initializing constrainer function pointer
	this->constrainer = default_constrainer;

	// Initializing last_fed index;
	this->last_fed = 0;

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
			if(i)
			{
				network[i][j].set_number_of_inputs(
						1);
			}
			else
			{
				network[i][j].set_number_of_inputs(
						def_width[i-1]);
			}

		}
	}

}

// Neural Network destructor
Neural_Network::~Neural_Network()
{
	delete [] this->width;
}

// clear
void
Neural_Network::clear(void)
{
	for(int i = 0; i < this->depth; i++)
	{
		for(int j = 0; j < this->width[i]; j++)
		{
			this->network[i][j].out = 0.0;
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
			for(Integer k = 0; k < this->width[i - 1]; k++)
			{
				this->network[i][j].out +=
				this->network[i][j].weigth[k] *
				this->network[i - 1][k].out;
			}
			//if(i == 2){std::cout<<this->network[i][j].out<<std::endl;}
			//if(i == 2){std::cout<<"Here"<<std::endl;}
			this->network[i][j].out +=
			this->network[i][j].bias;
			this->network[i][j].out =
			this->constrainer(this->network[i][j].out);
		}

		// Free last layer
		for(Integer j = 0; j < this->width[i - 1]; j++)
		{
			this->network[i - 1][j].out = 0.0;
		}
	}
}

// load_network
void
Neural_Network::load_network(const char* folder_address)
{
	for(Integer i = 0; i < this->depth; i++)
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
Neural_Network::overwrite_constrainer_function(Real (*foo)(Real))
{
	this->constrainer = foo;
}

// print_neuron
void
Neural_Network::print_neuron(Integer layer, Integer position)
{
	std::cout << "Bias: " << this->network[layer][position].bias << std::endl;
	std::cout << "Weigths: { ";
	Integer n_of_w = 1;
	if(layer)
	{
		n_of_w = this->width[layer - 1];
		for(int i = 0; i < n_of_w; i++)
		{
			std::cout << this->network[layer][position].weigth[i] << " ";
		}
	}
	std::cout << "}" << std::endl;
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
	for(Integer i = 0; i < this->depth; i++)
	{
		this->forward();
	}
}

// save_network
void
Neural_Network::save_network(const char* folder_address)
{
	for(Integer i = 0; i < this->depth; i++)
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
