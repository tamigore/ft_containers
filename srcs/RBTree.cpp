#include <iostream>
#include "RBTree.hpp"

int main(int argc, char** argv)
{
	ft::RBTree<int> bst;
	bst.insert(8, 1);
	bst.insert(18, 30);
	bst.insert(5, 100);
	bst.insert(15, 91);
	bst.insert(17, 2);
	bst.insert(25, 2);
	bst.insert(40, 1);
	bst.insert(80, 1);
	bst.deleteNode(25);
	bst.insert(19, 1);
	bst.insert(1, 1);
	bst.insert(54, 1);
	bst.insert(100, 1);
	bst.prettyPrint();
	std::cout << "min = ";
	printNode(bst.minimum(bst.getRoot()));
	std::cout << "\nmax = ";
	printNode(bst.maximum(bst.getRoot()));
	bst.deleteNode(25);
	bst.insert(100);
	bst.insert(100);
	bst.insert(100);
	bst.insert(100);
	bst.insert(100);
	bst.insert(101);
	bst.prettyPrint();
	std::cout << "search 100 = ";
	ft::printNode(bst.searchTree(100));
	std::cout << "search 100 parent = ";
	ft::printNode(bst.searchTree(100)->parent);
	return 0;
}