#pragma once
#include <iostream>
#include <string>
#include <set>
#include <vector>

#include "settings.h"
#include "Token.h"
#include "SyntaxError.h"

using std::cout;
using std::endl;

class SyntaxParser {
public:

	//TODO Must return tree and identifier table
	void parseTokens(vector<Token> listOfTockens);
	void printTree();

	// getTree
	// get IdentifierTable

private:

	vector<Token> listOfTokens;

	int numCurrentToken = -1;
	Token getNextToken();

	// syntax tree
	// IdentifierTable

	void throwError(char* errorMessage, int line, int position);
	void throwError(string& errorMessage, int line, int position);

	void printInDebugMode(const char* msg);

	// Non-terminal symbol functions
	void S();
	void mainProgram();
	void operatorsSequence();
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
	void arythmeticalExpression();
	void sign();
	void operand();
	void function();
	void functionArguments();
	void conditionsSequence();
};