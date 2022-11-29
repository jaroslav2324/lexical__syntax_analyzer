#pragma once
#include "ElementOfTree.h"
#include <queue>
#include <iostream>

class Tree {
private:
	ElementOfTree* root;

	int level{}; // хуетень для вывода по уровням

	void print(ElementOfTree* node);

	int amountElements = 0;

	ElementOfTree* searchingOfElement(ElementOfTree* node, int indexOfDesiredNode);

	void freeMemory();

public:
	Tree();

	~Tree();

	Tree(const Tree& t2);

	Tree(std::string nameOfRoot);

	ElementOfTree* searchFromRoot(int indexOfNode);

	void deleteNodeSChildren(int indexOfNode);

	int getAmountElements();

	void addElementInTree(ElementOfTree* node, int indexOfDesiredNode);
	
	void printTree();
};