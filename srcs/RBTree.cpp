#include <iostream>
#include "RBTree.hpp"

int RBTree_tester()
{
	std::cout << "START \"RBTree\" TEST" << std::endl;
	int i = 0;
	ft::pair<int, int> tmp = ft::make_pair(2, 3);
	ft::RBTree<int, ft::pair<int, int> > bst;
	std::cout << "i = " << i++ << std::endl;
	bst.insert(tmp.first, tmp);
	std::cout << "i = " << i++ << std::endl;
	bst.insert(1);
	std::cout << "i = " << i++ << std::endl;
	bst.insert(5, ft::make_pair(5, 100));
	std::cout << "i = " << i++ << std::endl;
	bst.insert(15, ft::make_pair(15, 91));
	std::cout << "i = " << i++ << std::endl;
	bst.insert(17, ft::make_pair(17, 2));
	std::cout << "i = " << i++ << std::endl;
	bst.insert(25, ft::make_pair(25, 2));
	std::cout << "i = " << i++ << std::endl;
	bst.insert(40, ft::make_pair(40, 1));
	std::cout << "i = " << i++ << std::endl;
	bst.insert(80, ft::make_pair(80, 1));
	std::cout << "i = " << i++ << std::endl;
	bst.deleteNode(25);
	std::cout << "i = " << i++ << std::endl;
	bst.prettyPrint();
	std::cout << "min = ";
	ft::printNode(bst.minimum(bst.getRoot()));
	std::cout << "\nmax = ";
	ft::printNode(bst.maximum(bst.getRoot()));
	bst.insert(84, ft::make_pair(84, 42));
	bst.insert(100, ft::make_pair(100, 1));
	tmp.first = 74; tmp.second = 42;
	bst.insert(tmp.first, tmp);
	bst.prettyPrint();
	std::cout << "search 100 = ";
	ft::printNode(bst.searchTree(100));
	std::cout << "search 100 parent = ";
	ft::printNode(bst.searchTree(100)->parent);
	return 0;
}