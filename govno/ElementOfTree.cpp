#include "ElementOfTree.h"

//ElementOfTree::ElementOfTree() {}

//ElementOfTree::ElementOfTree(int id, std::string name) : id(id), name(name) {}

ElementOfTree::~ElementOfTree() {
	if (DEBUG_MODE_ON && DEBUG_PRINT_CONSTRUCTORS)
		std::cout << "Destructor of " << id << "!\n";
}