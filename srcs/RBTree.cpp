#include <iostream>
#include "RBTree.hpp"

int RBTree_tester()
{
	ft::RBTree<int, int> bst;
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
	bst.insert(100);
	bst.insert(100);
	bst.insert(100);
	bst.insert(100);
	bst.insert(100);
	bst.insert(101);
	bst.insert(ft::make_pair(84, 42));
	bst.insert(ft::make_pair(74, 42));
	bst.prettyPrint();
	std::cout << "search 100 = ";
	ft::printNode(bst.searchTree(100));
	std::cout << "search 100 parent = ";
	ft::printNode(bst.searchTree(100)->parent);
	return 0;
}