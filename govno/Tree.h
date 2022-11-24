#pragma once
#include <vector>
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

	int level{}; // ������� ��� ������ �� �������

	void print(ElementOfTree* node);

	ElementOfTree* searchingOfElement(ElementOfTree* node, std::string nameOfDesiredNode);

public:
	Tree();

	Tree(const Tree& t2);

	Tree(std::string nameOfRoot);

	void addElementInTree(ElementOfTree* node, std::string);

	void printTree();
};