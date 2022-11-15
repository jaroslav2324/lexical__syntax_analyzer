#pragma once
#include <iostream>
#include <string>
#include <set>
#include <vector>

#include "Token.h"
#include "SyntaxError.h"

class SyntaxParser {
public:

	//TODO Must return tree
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

	void throwError(char* errorMessage);
	void throwError(string& errorMessage);

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
	void conditionsSequence();
	void logicalOperators();
	void comparison();
	void conditionOperator();
	void cycleDowhile();
	void cycleWhile();
	void _bool(); // bool
	void definition();
	void assignment();
	void arythmeticalExpression();
	void sign();
	void operand();
	void function();
	void functionArguments();
};