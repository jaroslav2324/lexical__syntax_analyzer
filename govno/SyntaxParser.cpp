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
	catch (SyntaxError&) {}

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
	catch (SyntaxError&) {}

	numCurrentToken = savedNumToken;
	try {
		definition();
		operatorsSequence();
		return;
	}
	catch (SyntaxError&) {}

	numCurrentToken = savedNumToken;
	try {
		function();
		operatorsSequence();
		return;
	}
	catch (SyntaxError&) {}

	numCurrentToken = savedNumToken;
	try {
		conditionOperator();
		operatorsSequence();
		return;
	}
	catch (SyntaxError&) {}

	numCurrentToken = savedNumToken;
	try {
		cycle();
		operatorsSequence();
		return;
	}
	catch (SyntaxError&) {}

	numCurrentToken = savedNumToken;
	try {
		assignment();
		return;
	}
	catch (SyntaxError&) {}

	numCurrentToken = savedNumToken;
	try {
		definition();
		return;
	}
	catch (SyntaxError&) {}

	numCurrentToken = savedNumToken;
	try {
		function();
		return;
	}
	catch (SyntaxError&) {}

	numCurrentToken = savedNumToken;
	try {
		conditionOperator();
		return;
	}
	catch (SyntaxError&) {
		numCurrentToken = savedNumToken;
		cycle();
	}
	
}

void SyntaxParser::functionsDefinition()
{
	int savedNumToken = numCurrentToken;
	try {
		functionDefinition();
		return;
	}
	catch (SyntaxError&) {
		numCurrentToken = savedNumToken;
		functionDefinition();
		functionsDefinition();
	}
}

void SyntaxParser::functionDefinition()
{
	std::string errorMessage("Error in functionDefinition");
	Token token;

	type();

	token = getNextToken();
	if (token.type != "KEYWORD" || token.value != "proc")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);
	token = getNextToken();
	if (token.type != "IDENTIFIER")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);
	token = getNextToken();
	if (token.type != "DEVIDER" || token.value != "(")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);

	passedParameters();

	token = getNextToken();
	if (token.type != "DEVIDER" || token.value != ")")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);
	token = getNextToken();
	if (token.type != "DEVIDER" || token.value != "{")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);

	operatorsSequence();

	token = getNextToken();
	if (token.type != "KEYWORD" || token.value != "return")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);

	value();

	token = getNextToken();
	if (token.type != "DEVIDER" || token.value != "}")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);

}

void SyntaxParser::type()
{
	std::string errorMessage("No such type");
	Token token;

	if (token.type != "KEYWORD" || (token.value != "bool" && token.value != "integer" && token.value != "string"))
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);

}

void SyntaxParser::passedParameters()
{
	std::string errorMessage("Error in passing parameters");
	Token token;

	int savedNumToken = numCurrentToken;
	try {
		parameter();
		return;
	}
	catch (SyntaxError&) {
		numCurrentToken = savedNumToken;
		parameter();
		token = getNextToken();
		if (token.type != "DEVIDER" || token.value != ",")
			throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);
		passedParameters();
	}
}

void SyntaxParser::value()
{
	std::string errorMessage("Wrong value");
	Token token;

	int savedNumToken = numCurrentToken;
	try {
		function();
		return;
	}
	catch (SyntaxError&) {}

	numCurrentToken = savedNumToken;
	try {
		arythmeticalExpression();
		return;
	}
	catch (SyntaxError&) {}

	numCurrentToken = savedNumToken;
	token = getNextToken();
	if (token.type != "CONSTANT" || token.type != "IDENTIFIER")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);
}

void SyntaxParser::parameter()
{
	std::string errorMessage("Wrong parameter in function");
	Token token;

	int savedNumToken = numCurrentToken;
	try {
		type();
		token = getNextToken();
		if (token.type != "IDENTIFIER")
			throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);
	}
	catch (SyntaxError&) {
		numCurrentToken = savedNumToken;
		type();
	}
}

void SyntaxParser::condition()
{
	std::string errorMessage("Wrong condition");
	Token token;

	int savedNumToken = numCurrentToken;
	try {
		token = getNextToken();
		if (token.type != "IDENTIFIER")
			throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);
		comparison();
		value();
		return;
	}
	catch (SyntaxError&) {}

	numCurrentToken = savedNumToken;
	try {
		value();
		comparison();
		value();
		return;
	}
	catch (SyntaxError&) {}

	numCurrentToken = savedNumToken;
	_bool();
}

void SyntaxParser::logicalOperators()
{
	std::string errorMessage("Wrong logical operator");
	Token token;

	token = getNextToken();
	if (token.type != "DEVIDER" || (token.value != "&&" && token.value != "||"))
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);

}

void SyntaxParser::comparison()
{
	std::string errorMessage("Wrong comparison operator");
	Token token;

	token = getNextToken();
	if (token.type != "DEVIDER" || (token.value != "==" && token.value != "!=" && token.value != "<"
		&& token.value != ">" && token.value != "<=" && token.value != ">="))
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);
}

void SyntaxParser::conditionOperator()
{
	std::string errorMessage("Wrong if-then-else-endif statement");
	Token token;

	token = getNextToken();
	if (token.type != "KEYWORD" || token.value != "if")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);

	condition();

	token = getNextToken();
	if (token.type != "KEYWORD" || token.value != "then")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);

	operatorsSequence();

	token = getNextToken();
	if (token.type != "KEYWORD" || token.value != "else")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);

	operatorsSequence();

	token = getNextToken();
	if (token.type != "KEYWORD" || token.value != "endif")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);

	token = getNextToken();
	if (token.type != "DEVIDER" || token.value != ";")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);
}

void SyntaxParser::cycle()
{
	std::string errorMessage("Wrong while-do-endwhile statement");
	Token token;

	token = getNextToken();
	if (token.type != "KEYWORD" || token.value != "while")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);

	conditionsSequence();

	token = getNextToken();
	if (token.type != "DEVIDER" || token.value != ";")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);

	operatorsSequence();

	token = getNextToken();
	if (token.type != "KEYWORD" || token.value != "endwhile")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);

	token = getNextToken();
	if (token.type != "DEVIDER" || token.value != ";")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);
}

void SyntaxParser::_bool()
{
	std::string errorMessage("Wrong bool value");
	Token token;

	token = getNextToken();
	if (token.type != "KEYWORD" || (token.value != "true" && token.value != "false"))
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);
}

void SyntaxParser::definition()
{
	std::string errorMessage("wrong definition");
	Token token;

	type();

	token = getNextToken();
	if (token.type != "IDENTIFIER")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);

	token = getNextToken();
	if (token.type != "DEVIDER" || token.value != ";")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);
}

void SyntaxParser::assignment()
{
	std::string errorMessage("wrong assignment of value");
	Token token;

	token = getNextToken();
	if (token.type != "IDENTIFIER")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);

	token = getNextToken();
	if (token.type != "DEVIDER" || token.value != "=")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);

	value();

	token = getNextToken();
	if (token.type != "DEVIDER" || token.value != ";")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);
}

void SyntaxParser::arythmeticalExpression()
{
	std::string errorMessage("Wrong arythmetical expression");
	Token token;

	int savedNumToken = numCurrentToken;
	try {
		operand();
		sign();
		operand();
		return;
	}
	catch (SyntaxError&) {}

	numCurrentToken = savedNumToken;
	try {
		operand();
		sign();
		arythmeticalExpression();
		return;
	}
	catch (SyntaxError&) {}

	numCurrentToken = savedNumToken;
	operand();
	sign();

	token = getNextToken();
	if (token.type != "DEVIDER" || token.value != "(")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);

	arythmeticalExpression();

	token = getNextToken();
	if (token.type != "DEVIDER" || token.value != ")")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);

}

void SyntaxParser::sign()
{
	std::string errorMessage("Wrong arythmetical sign");
	Token token;

	token = getNextToken();
	if (token.type != "DEVIDER" || (token.value != "+" && token.value != "-" && token.value != "/" && token.value != "*"))
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);
}

void SyntaxParser::operand()
{
	std::string errorMessage("wrong operand");
	Token token;

	int savedNumToken = numCurrentToken;
	try {
	token = getNextToken();
	if (token.type != "IDENTIFIER")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);
		return;
	}
	catch (SyntaxError&) {}

	numCurrentToken = savedNumToken;
	try {
		function();
		return;
	}
	catch (SyntaxError&) {}

	numCurrentToken = savedNumToken;
	token = getNextToken();
	if (token.type != "CONSTANT")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);
	return;
}

void SyntaxParser::function()
{
	std::string errorMessage("wrong function call");
	Token token;

	int savedNumToken = numCurrentToken;
	try {
		token = getNextToken();
		if (token.type != "IDENTIFIER")
			throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);
		token = getNextToken();
		if (token.type != "DEVIDER" || token.value != "(")
			throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);
		token = getNextToken();
		if (token.type != "DEVIDER" || token.value != ")")
			throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);
		token = getNextToken();
		if (token.type != "DEVIDER" || token.value != ";")
			throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);

		return;
	}
	catch (SyntaxError&) {}

	numCurrentToken = savedNumToken;
	token = getNextToken();
	if (token.type != "IDENTIFIER")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);
	token = getNextToken();
	if (token.type != "DEVIDER" || token.value != "(")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);

	functionArguments();

	token = getNextToken();
	if (token.type != "DEVIDER" || token.value != ")")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);
	token = getNextToken();
	if (token.type != "DEVIDER" || token.value != ";")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);
}

void SyntaxParser::functionArguments()
{
	std::string errorMessage("wrong function arguments");
	Token token;

	int savedNumToken = numCurrentToken;
	try {
		value();
		return;
	}
	catch (SyntaxError&) {}

	numCurrentToken = savedNumToken;
	value();
	if (token.type != "DEVIDER" || token.value != ",")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);
	functionArguments();
}

void SyntaxParser::conditionsSequence()
{
	std::string errorMessage("wrong conditions sequence");
	Token token;

	int savedNumToken = numCurrentToken;
	try {
		condition();
		return;
	}
	catch (SyntaxError&) {}

	numCurrentToken = savedNumToken;
	condition();
	logicalOperators();
	conditionsSequence();
}
