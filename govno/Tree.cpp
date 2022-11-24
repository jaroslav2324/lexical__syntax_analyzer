#include "Tree.h"

Tree::Tree(const Tree& t2) {
	root = new ElementOfTree(t2.root->id);
	auto node = t2.root;
	std::queue<ElementOfTree*> queue;
	queue.push(node);

	while (!queue.empty()) {
		node = queue.front();
		queue.pop();

		for (int i = 0; i < node->sons.size(); ++i) {
			ElementOfTree* temp = new ElementOfTree(node->sons[i]->id);
			this->addElementInTree(temp, node->id);
			queue.push(node->sons[i]);
		}
	}
	std::cout << "Copying constructor is worked!\n";
}

Tree::Tree(std::string nameOfRoot) {
	root = new ElementOfTree(nameOfRoot);
}

Tree::Tree() {
	root = new ElementOfTree("root");
}

ElementOfTree* Tree::searchingOfElement(ElementOfTree* node, std::string nameOfDesiredNode) {
	std::queue<ElementOfTree*> queue;
	queue.push(node);
	while (!queue.empty()) {
		node = queue.front();
		queue.pop();
		if (node->id == nameOfDesiredNode) return node;

		for (int i = 0; i < node->sons.size(); ++i) {
			queue.push(node->sons[i]);
		}
	}
	return nullptr;
}

void Tree::addElementInTree(ElementOfTree* node, std::string nameOfDesiredNode) {
	ElementOfTree* searchableElement = searchingOfElement(root, nameOfDesiredNode);
	if (searchableElement == nullptr) throw std::runtime_error("Pizdec");
	searchableElement->sons.push_back(node);
}

void Tree::printTree() {
	if (root == nullptr) {
		std::cout << "No elements!\n";
		return;
	}
	print(root);
	level = 0;
}

void Tree::print(ElementOfTree* node) {
	if (node == nullptr) return;

	for (int i = 0; i < level; i++) {
		std::cout << "| ";
	}

	std::cout << "[+](" << level << "-" << (node->id) << ")\n";

	int i = 0;
	while (i != node->sons.size()) {
		level++;
		print(node->sons[i]);
		if (i == node->sons.size() - 1) level--;
		i++;
	}
	if (node->sons.size() == 0) level--;
}

void Tree::freeMemory() {
	ElementOfTree* node = root;
	std::queue<ElementOfTree*> queue;
	queue.push(node);

	while (!queue.empty()) {
		node = queue.front();
		queue.pop();

		for (int i = 0; i < node->sons.size(); ++i) {
			queue.push(node->sons[i]);
		}
		delete node;
	}
}

Tree::~Tree() {
	std::cout << "Destructor!\n";
	freeMemory();
}