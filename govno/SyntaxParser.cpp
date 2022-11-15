#include "SyntaxParser.h"

void SyntaxParser::parseTokens(vector<Token> listOfTockens)
{
	SyntaxParser::listOfTokens = listOfTockens;

	S();
}

void SyntaxParser::printTree()
{
	cout << "TODO print tree";
}

Token SyntaxParser::getNextToken()
{
	numCurrentToken += 1;
	if (numCurrentToken >= listOfTokens.size())
		throw SyntaxError("End of tokens list", -1, -1);
	return listOfTokens[numCurrentToken];
}

void SyntaxParser::throwError(char* errorMessage, int line, int position)
{
	std::string message(errorMessage);
	throwError(message, line, position);
}

void SyntaxParser::throwError(string& errorMessage, int line, int position)
{
	throw SyntaxError(errorMessage, line, position);
}

void SyntaxParser::S()
{
	int savedNumToken = numCurrentToken;
	try {
		mainProgram();
		functionsDefinition();
		return;
	}
	catch (SyntaxError& err) {}

	numCurrentToken = savedNumToken;
	try {
		mainProgram();
	}
	catch (SyntaxError& err) {
		err.printMessage();
		exit(-1);
	}
	
}

void SyntaxParser::mainProgram()
{
	std::string errorMessage("Error in main program");
	Token token;

	token = getNextToken();
	if (token.type != "KEYWORD" || token.value != "main")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);
	token = getNextToken();
	if (token.type != "DIVIDER" || token.value != "(")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);
	token = getNextToken();
	if (token.type != "DIVIDER" || token.value != ")")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);
	token = getNextToken();
	if (token.type != "DIVIDER" || token.value != "{")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);
	operatorsSequence();
	token = getNextToken();
	if (token.type != "DIVIDER" || token.value != "}")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);
}

void SyntaxParser::operatorsSequence()
{

	int savedNumToken = numCurrentToken;
	try {
		assignment();
		operatorsSequence();
		return;
	}
	catch (SyntaxError& err) {}

	numCurrentToken = savedNumToken;
	try {
		definition();
		operatorsSequence();
		return;
	}
	catch (SyntaxError& err) {}

	numCurrentToken = savedNumToken;
	try {
		function();
		operatorsSequence();
		return;
	}
	catch (SyntaxError& err) {}

	numCurrentToken = savedNumToken;
	try {
		conditionOperator();
		operatorsSequence();
		return;
	}
	catch (SyntaxError& err) {}

	numCurrentToken = savedNumToken;
	try {
		cycle();
		operatorsSequence();
		return;
	}
	catch (SyntaxError& err) {}

	numCurrentToken = savedNumToken;
	try {
		assignment();
		return;
	}
	catch (SyntaxError& err) {}

	numCurrentToken = savedNumToken;
	try {
		definition();
		return;
	}
	catch (SyntaxError& err) {}

	numCurrentToken = savedNumToken;
	try {
		function();
		return;
	}
	catch (SyntaxError& err) {}

	numCurrentToken = savedNumToken;
	try {
		conditionOperator();
		return;
	}
	catch (SyntaxError& err) {
		numCurrentToken = savedNumToken;
		cycle();
	}
	
}

void SyntaxParser::functionsDefinition()
{
	cout << "TODO implement functionsDefinition";
}
