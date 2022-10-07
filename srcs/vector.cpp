#include <vector>
#include "vector.hpp"
#include <iostream>

int vector_test()
{
    // Create a vector containing integers
    ft::vector<int> v = { 7, 5, 16, 8 };
 
    // Add two more integers to vector
    v.push_back(25);
    v.push_back(13);
 
    // Print out the vector
    std::cout << "v = { ";
    for (int n : v)
    {
        std::cout << n << ", ";
    }
    std::cout << "};" << std::endl;
}