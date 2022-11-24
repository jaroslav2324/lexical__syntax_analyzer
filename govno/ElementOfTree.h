#pragma once
#include <vector>
#include <iostream>

class ElementOfTree {
public:
	ElementOfTree();

	~ElementOfTree();

	ElementOfTree(std::string id);

	std::string id{};

	std::vector<ElementOfTree*> sons;
};

