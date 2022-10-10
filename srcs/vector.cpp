#include <vector>
#include "vector.hpp"
#include <iostream>

int vector_test()
{
	// Create a vector containing integers
	std::vector<int>	std_vec = {7, 5, 16, 8};
	ft::vector<int>		ft_vec = {7, 5, 16, 8};

	// Add two more integers to vector
	ft_vec.push_back(25);
	ft_vec.push_back(13);
	std_vec.push_back(25);
	std_vec.push_back(13);
 
	// Print out the vector
	for (int n = 0; n < ft_vec.size() && n < std_vec.size(); n++)
	{
		std::cout << "std_vec[" << n << "] = " << std_vec[n] << std::endl;
		std::cout << "ft_vec[" << n << "] = " << ft_vec[n] << std::endl;
		if (ft_vec[n] != std_vec[n])
			return (0);
	}
	return (1);
}