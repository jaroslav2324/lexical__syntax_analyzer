#pragma once
#include <iostream>
#include <string>
#include <set>
#include <vector>

#include "settings.h"
#include "Token.h"
#include "SyntaxError.h"
#include "MultipleDefinitionError.h"
#include "Tree.h"

using std::cout;
using std::endl;

class SyntaxParser {
public:

	//TODO Must return tree and identifier table
	void parseTokens(vector<Token> listOfTockens);
	void printTree();
	void printIdentifiersTable();

private:

	vector<Token> listOfTokens;

	// <type, id>
	vector<std::pair<string, string>> identifiersTable;

	void addIdToIdTable(Token type, Token id);

	int numCurrentToken = -1;
	Token getNextToken();

	Tree tree;

	void throwError(char* errorMessage, int line, int position);
	void throwError(string& errorMessage, int line, int position);

	void printInDebugMode(const char* msg);

	// Non-terminal symbol functions
	void S();
	void mainProgram();
	void operatorsSequence(bool recursiveCall);
	void functionsDefinition();
	void functionDefinition();
	void type();
	void passedParameters();
	void value();
	void parameter();
	void condition();
	void logicalOperators();
	void comparison();
	void conditionOperator();
	void cycle();
	void _bool(); // bool
	void definition();
	void assignment();
	void arythmeticalExpression(bool recursiveCall);
	void sign();
	void operand();
	void function();
	void functionArguments();
	void conditionsSequence();
};