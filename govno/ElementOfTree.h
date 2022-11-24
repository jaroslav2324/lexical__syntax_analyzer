#pragma once
#include <vector>
#include <iostream>

class ElementOfTree {
public:
	ElementOfTree() {}
	ElementOfTree(int id, std::string name) : id(id), name(name) {}
	~ElementOfTree();

	int id{};
	std::string name;

	std::vector<ElementOfTree*> sons;
};

