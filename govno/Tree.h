#pragma once
#include "ElementOfTree.h"
#include <queue>
#include <iostream>

class ElementOfTree {
public:
	ElementOfTree() {}

	ElementOfTree(std::string id) : id(id) {}

	std::string id{};

	std::vector<ElementOfTree*> sons;
};

class Tree {
private:
	ElementOfTree* root;

	int level{}; // хуетень для вывода по уровням

	void print(ElementOfTree* node);

	ElementOfTree* searchingOfElement(ElementOfTree* node, std::string nameOfDesiredNode);

	void freeMemory();

public:
	Tree();

	~Tree();

	Tree(const Tree& t2);

	Tree(std::string nameOfRoot);

	void addElementInTree(ElementOfTree* node, std::string);

	void printTree();
};