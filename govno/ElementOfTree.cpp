#include "ElementOfTree.h"

ElementOfTree::ElementOfTree() {}

ElementOfTree::ElementOfTree(std::string id) : id(id) {}

ElementOfTree::~ElementOfTree() {
	std::cout << "Destructor of " << id << "!\n";
}