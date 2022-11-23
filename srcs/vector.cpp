#include <vector>
#include "vector.hpp"
#include <iostream>

int	vector_tester()
{
	// Create a vector containing integers
	std::vector<int>	std_vec;
	ft::vector<int>		ft_vec;

	// Add two more integers to vector
	ft_vec.push_back(25);
	ft_vec.push_back(13);
	ft_vec.push_back(2);
	ft_vec.push_back(1);
	ft_vec.push_back(5);
	ft_vec.push_back(3);
	std_vec.push_back(25);
	std_vec.push_back(13);
	std_vec.push_back(2);
	std_vec.push_back(1);
	std_vec.push_back(5);
	std_vec.push_back(3);
 
	// Print out the vector
	for (size_t n = 0; n < ft_vec.size() && n < std_vec.size(); n++)
	{
		std::cout << "std_vec[" << n << "] = " << std_vec[n] << std::endl;
		std::cout << "ft_vec[" << n << "] = " << ft_vec[n] << std::endl;
		if (ft_vec[n] != std_vec[n])
			return (0);
	}
	return (1);
}