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
	return listOfTokens[numCurrentToken];
}

void SyntaxParser::S()
{
	int savedNumToken = numCurrentToken;
	try {
		mainProgram();
		functionsDefinition();
	}
	catch (SyntaxError& err) {

		numCurrentToken = savedNumToken;

		try {
			mainProgram();
		}
		catch (SyntaxError& err) {
			err.printMessage();
			exit(-1);
		}
	}

	
}
