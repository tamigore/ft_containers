#include <iostream>
#include "RBTree.hpp"

void	second_test()
{
	std::cout << "START \"RBTree\" TEST" << std::endl;
	int i = 0;
	ft::pair<int, int> tmp = ft::make_pair(2, 3);
	ft::RBTree<int, ft::pair<int, int> > bst;
	std::cout << "i = " << i++ << std::endl;
	bst.insert(tmp.first, tmp);
	bst.prettyPrint();
	std::cout << "i = " << i++ << std::endl;
	bst.insert(1);
	bst.prettyPrint();
	std::cout << "i = " << i++ << std::endl;
	bst.insert(5, ft::make_pair(5, 100));
	bst.prettyPrint();
	std::cout << "i = " << i++ << std::endl;
	bst.insert(15, ft::make_pair(15, 91));
	bst.prettyPrint();
	std::cout << "i = " << i++ << std::endl;
	bst.insert(17, ft::make_pair(17, 2));
	bst.prettyPrint();
	std::cout << "i = " << i++ << std::endl;
	bst.insert(25, ft::make_pair(25, 2));
	bst.prettyPrint();
	std::cout << "i = " << i++ << std::endl;
	bst.insert(40, ft::make_pair(40, 1));
	bst.prettyPrint();
	std::cout << "i = " << i++ << std::endl;
	bst.insert(80, ft::make_pair(80, 1));
	bst.prettyPrint();
	std::cout << "i = " << i++ << std::endl;
	bst.deleteNode(25);
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
	std::cout << "END SECOND TEST" << std::endl;
}

void	first_test()
{
	ft::RBTree<int, int> bst;
	bst.insert(8);
	bst.insert(18);
	bst.insert(5);
	bst.insert(15);
	bst.insert(17);
	bst.insert(25);
	bst.insert(40);
	bst.insert(80);
	bst.deleteNode(25);
	bst.insert(19);
	bst.insert(1);
	bst.insert(541);
	bst.insert(1001);
	bst.prettyPrint();
	std::cout << "min :" << std::endl;
	ft::printNode(bst.minimum(bst.getRoot()));
	std::cout << "max :" << std::endl;
	ft::printNode(bst.maximum(bst.getRoot()));
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
	bst.prettyPrint();
	std::cout << "search 100 :" << std::endl;
	ft::printNode(bst.searchTree(100));
	std::cout << "search 100 parent :" << std::endl;
	ft::printNode(bst.searchTree(100)->parent);
	std::cout << "END FIRST TEST" << std::endl;
}

void	third_test()
{
	ft::RBTree<int, int> bst;
	std::cout << "START THIRD TEST" << std::endl;
	bst.prettyPrint();
	std::cout << "okay not stupid" << std::endl;
	bst.insert(8);
	bst.insert(18);
	bst.insert(5);
	bst.insert(15);
	bst.insert(17);
	bst.insert(25);
	bst.insert(40);
	bst.insert(80);
	bst.deleteNode(25);
	bst.insert(19);
	bst.insert(1);
	bst.insert(541);
	bst.insert(1001);
	bst.prettyPrint();
	std::cout << "min :" << std::endl;
	ft::printNode(bst.minimum(bst.getRoot()));
	std::cout << "max :" << std::endl;
	ft::printNode(bst.maximum(bst.getRoot()));
	bst.deleteNode(25);
	bst.insert(100);
	bst.insert(101);
	bst.insert(102);
	bst.insert(103);
	bst.insert(104);
	bst.insert(105);
	bst.insert(106);
	bst.insert(107);
	bst.insert(108);
	bst.insert(109);
	bst.insert(110);
	bst.prettyPrint();
	std::cout << "search 100 :" << std::endl;
	ft::printNode(bst.searchTree(100));
	std::cout << "search 100 parent :" << std::endl;
	ft::printNode(bst.searchTree(100)->parent);
	std::cout << "END THIRD TEST" << std::endl;
}

void	fourth_test()
{
	ft::RBTree<int, int> bst;
	std::cout << "START FOURTH TEST" << std::endl;
	bst.prettyPrint();
	std::cout << "okay not stupid" << std::endl;
	bst.insert(8);
	bst.insert(18);
	bst.insert(5);
	bst.insert(15);
	bst.insert(17);
	bst.insert(25);
	bst.insert(40);
	bst.insert(80);
	bst.deleteNode(25);
	bst.insert(19);
	bst.insert(1);
	bst.insert(541);
	bst.insert(1001);
	bst.prettyPrint();
	std::cout << "min :" << std::endl;
	ft::printNode(bst.minimum(bst.getRoot()));
	std::cout << "max :" << std::endl;
	ft::printNode(bst.maximum(bst.getRoot()));
	bst.deleteNode(25);
	bst.insert(100);
	bst.insert(101);
	bst.insert(102);
	bst.insert(103);
	bst.insert(104);
	bst.insert(105);
	bst.insert(106);
	bst.insert(107);
	bst.insert(108);
	bst.insert(109);
	bst.insert(110);
	bst.prettyPrint();
	std::cout << "delete 100 :" << (bst.deleteNode(100) ? "true" : "false") << std::endl;
	std::cout << "delete 1 :" << (bst.deleteNode(1) ? "true" : "false") << std::endl;
	std::cout << "delete 1001 :" << (bst.deleteNode(1) ? "true" : "false") << std::endl;
	bst.prettyPrint();
	std::cout << "bst mini -> max :" << std::endl;
	ft::Node<int, int>	*ptr = bst.minimum(bst.getRoot());
	for (int i = 0; i < 25; i++)
	{
		std::cout << ptr << std::endl;
		ptr = bst.successor(ptr);
	}
	std::cout << "bst mini-- :" << std::endl;
	ptr = bst.minimum(bst.getRoot());
	for (int i = 0; i < 4; i++)
	{
		std::cout << ptr << std::endl;
		ptr = bst.predecessor(ptr);
	}
	std::cout << "bst max -> min :" << std::endl;
	ptr = bst.maximum(bst.getRoot());
	for (int i = 0; i < 25; i++)
	{
		std::cout << ptr << std::endl;
		ptr = bst.predecessor(ptr);
	}
	std::cout << "bst max++ :" << std::endl;
	ptr = bst.maximum(bst.getRoot());
	for (int i = 0; i < 4; i++)
	{
		std::cout << ptr << std::endl;
		ptr = bst.successor(ptr);
	}
	std::cout << "END FOURTH TEST" << std::endl;
}

int RBTree_tester()
{
	first_test();
	second_test();
	// third_test();
	fourth_test();
	return 0;
}