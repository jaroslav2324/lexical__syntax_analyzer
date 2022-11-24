#include "SyntaxParser.h"

void SyntaxParser::parseTokens(vector<Token> listOfTockens)
{
	SyntaxParser::listOfTokens = listOfTockens;

	try {
		S();
	}
	catch (MultipleDefinitionError& err) {
		err.printMessage();
	}
		
}

void SyntaxParser::printTree()
{
	tree.printTree();
}

void SyntaxParser::addIdToIdTable(Token typeToken, Token idToken)
{
	for (auto& typeIdPair: identifiersTable)
		if (typeIdPair.first == typeToken.value && typeIdPair.second == idToken.value) {
			string errorMsg = "This identifier was already defined";
			throw MultipleDefinitionError(errorMsg, idToken.pos[0], idToken.pos[1]);
		}
	identifiersTable.push_back(std::make_pair(typeToken.value, idToken.value));
}

void SyntaxParser::printIdentifiersTable()
{
	int counter = 0;
	for (auto& typeIdPair : identifiersTable) {
		cout << counter << "      " << typeIdPair.first << "    " << typeIdPair.second << endl;
		counter++;
	}
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
	printInDebugMode("S");

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
	printInDebugMode("mainProgram");

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
	operatorsSequence(false);
	token = getNextToken();
	if (token.type != "DIVIDER" || token.value != "}")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);
}

void SyntaxParser::operatorsSequence(bool recursiveCall)
{
	printInDebugMode("operatorsSequence");

	bool flag_convolution_worked_on_something = false;
	int savedNumToken = numCurrentToken;

	try {
		assignment();
		flag_convolution_worked_on_something = true;
		savedNumToken = numCurrentToken;
	}
	catch (SyntaxError&) {
		numCurrentToken = savedNumToken;
	}

	try {
		definition();
		flag_convolution_worked_on_something = true;
		savedNumToken = numCurrentToken;
	}
	catch (SyntaxError&) {
		numCurrentToken = savedNumToken;
	}

	try {
		function();
		flag_convolution_worked_on_something = true;
		savedNumToken = numCurrentToken;
	}
	catch (SyntaxError&) {
		numCurrentToken = savedNumToken;
	}

	try {
		conditionOperator();
		flag_convolution_worked_on_something = true;
		savedNumToken = numCurrentToken;
	}
	catch (SyntaxError&) {
		numCurrentToken = savedNumToken;
	}

	try {
		cycle();
		flag_convolution_worked_on_something = true;
		savedNumToken = numCurrentToken;
	}
	catch (SyntaxError&) {
		numCurrentToken = savedNumToken;
	}

	//TODO change
	if (flag_convolution_worked_on_something == false)
		throw SyntaxError("error in operators sequence", -1, -1);

	try
	{
		operatorsSequence(true);
	}
	catch (SyntaxError&){}
	
}

void SyntaxParser::functionsDefinition()
{
	printInDebugMode("functionsDefinition");

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
	printInDebugMode("functionDefinition");

	std::string errorMessage("Error in functionDefinition");
	Token token;

	type();

	token = getNextToken();
	if (token.type != "KEYWORD" || token.value != "proc")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);
	token = getNextToken();
	if (token.type != "IDENTIFIER")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);

	addIdToIdTable(listOfTokens[numCurrentToken - 2], token);

	token = getNextToken();
	if (token.type != "DIVIDER" || token.value != "(")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);

	passedParameters();

	token = getNextToken();
	if (token.type != "DIVIDER" || token.value != ")")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);
	token = getNextToken();
	if (token.type != "DIVIDER" || token.value != "{")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);

	operatorsSequence(false);

	token = getNextToken();
	if (token.type != "KEYWORD" || token.value != "return")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);

	value();

	token = getNextToken();
	if (token.type != "DIVIDER" || token.value != ";")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);

	token = getNextToken();
	if (token.type != "DIVIDER" || token.value != "}")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);

}

void SyntaxParser::type()
{
	printInDebugMode("type");

	std::string errorMessage("No such type");
	Token token;

	token = getNextToken();
	if (token.type != "KEYWORD" || (token.value != "bool" && token.value != "integer" && token.value != "string"))
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);

}

void SyntaxParser::passedParameters()
{
	printInDebugMode("passedParameters");

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
	printInDebugMode("value");

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
		arythmeticalExpression(false);
		return;
	}
	catch (SyntaxError&) {}

	try {
		numCurrentToken = savedNumToken;
		token = getNextToken();
		if (token.type != "IDENTIFIER" && token.type != "CONSTANT" && (token.type != "KEYWORD" || (token.value != "true" && token.value != "false")))
			throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);
		return;
	}
	catch (SyntaxError&) {}

	numCurrentToken = savedNumToken;
	token = getNextToken();
	if (token.type != "DIVIDER" || token.value != "\"")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);
	token = getNextToken();
	if (token.type != "CONSTANT" && token.type != "KEYWORD")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);
	token = getNextToken();
	if (token.type != "DIVIDER" || token.value != "\"")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);
}

void SyntaxParser::parameter()
{
	printInDebugMode("parameter");

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
	printInDebugMode("condition");

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
	printInDebugMode("logicalOperators");

	std::string errorMessage("Wrong logical operator");
	Token token;

	token = getNextToken();
	if (token.type != "DEVIDER" || (token.value != "&&" && token.value != "||"))
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);

}

void SyntaxParser::comparison()
{
	printInDebugMode("comparison");

	std::string errorMessage("Wrong comparison operator");
	Token token;

	token = getNextToken();
	if (token.type != "DIVIDER" || (token.value != "==" && token.value != "!=" && token.value != "<"
		&& token.value != ">" && token.value != "<=" && token.value != ">="))
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);
}

void SyntaxParser::conditionOperator()
{
	printInDebugMode("conditionOperator");

	std::string errorMessage("Wrong if-then-else-endif statement");
	Token token;

	token = getNextToken();
	if (token.type != "KEYWORD" || token.value != "if")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);

	condition();

	token = getNextToken();
	if (token.type != "KEYWORD" || token.value != "then")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);

	operatorsSequence(false);

	token = getNextToken();
	if (token.type != "KEYWORD" || token.value != "else")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);

	operatorsSequence(false);

	token = getNextToken();
	if (token.type != "KEYWORD" || token.value != "endif")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);

	token = getNextToken();
	if (token.type != "DIVIDER" || token.value != ";")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);
}

void SyntaxParser::cycle()
{
	printInDebugMode("cycle");

	std::string errorMessage("Wrong while-do-endwhile statement");
	Token token;

	token = getNextToken();
	if (token.type != "KEYWORD" || token.value != "while")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);

	conditionsSequence();

	token = getNextToken();
	if (token.type != "DIVIDER" || token.value != ";")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);

	operatorsSequence(false);

	token = getNextToken();
	if (token.type != "KEYWORD" || token.value != "endwhile")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);

	token = getNextToken();
	if (token.type != "DIVIDER" || token.value != ";")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);
}

void SyntaxParser::_bool()
{
	printInDebugMode("bool");

	std::string errorMessage("Wrong bool value");
	Token token;

	token = getNextToken();
	if (token.type != "KEYWORD" || (token.value != "true" && token.value != "false"))
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);
}

void SyntaxParser::definition()
{
	printInDebugMode("definition");

	std::string errorMessage("wrong definition");
	Token token;

	type();

	token = getNextToken();
	if (token.type != "IDENTIFIER")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);

	addIdToIdTable(listOfTokens[numCurrentToken - 1], token);

	token = getNextToken();
	if (token.type != "DIVIDER" || token.value != ";")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);
}

void SyntaxParser::assignment()
{
	printInDebugMode("assignment");

	std::string errorMessage("wrong assignment of value");
	Token token;

	token = getNextToken();
	if (token.type != "IDENTIFIER")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);

	token = getNextToken();
	if (token.type != "DIVIDER" || token.value != "=")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);

	value();

	token = getNextToken();
	if (token.type != "DIVIDER" || token.value != ";")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);
}

void SyntaxParser::arythmeticalExpression(bool recursiveCall)
{
	printInDebugMode("arythmeticalExpression");
	bool flag_recursive_error = false;

	std::string errorMessage("Wrong arythmetical expression");
	Token token;
	
	int savedNumToken = numCurrentToken;
	try{
		operand();
		sign();
		arythmeticalExpression(true);
		return;
	}
	catch (SyntaxError& err){}

	numCurrentToken = savedNumToken;
	operand();
	sign();
	operand();
}

void SyntaxParser::sign()
{
	printInDebugMode("sign");

	std::string errorMessage("Wrong arythmetical sign");
	Token token;

	token = getNextToken();
	if (token.type != "DIVIDER" || (token.value != "+" && token.value != "-" && token.value != "/" && token.value != "*"))
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);
}

void SyntaxParser::operand()
{
	printInDebugMode("operand");

	std::string errorMessage("wrong operand");
	Token token;

	int savedNumToken = numCurrentToken;
	try {
		function();
		return;
	}
	catch (SyntaxError&) {}

	numCurrentToken = savedNumToken;
	try {
	token = getNextToken();
	if (token.type != "IDENTIFIER")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);
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
	printInDebugMode("function");

	std::string errorMessage("wrong function call");
	Token token;

	int savedNumToken = numCurrentToken;
	try {
		token = getNextToken();
		if (token.type != "IDENTIFIER")
			throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);
		token = getNextToken();
		if (token.type != "DIVIDER" || token.value != "(")
			throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);
		token = getNextToken();
		if (token.type != "DIVIDER" || token.value != ")")
			throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);

		return;
	}
	catch (SyntaxError&) {}

	numCurrentToken = savedNumToken;
	token = getNextToken();
	if (token.type != "IDENTIFIER")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);
	token = getNextToken();
	if (token.type != "DIVIDER" || token.value != "(")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);

	functionArguments();

	token = getNextToken();
	if (token.type != "DIVIDER" || token.value != ")")
		throw SyntaxError(errorMessage, token.pos[0], token.pos[1]);
}

void SyntaxParser::functionArguments()
{
	printInDebugMode("functionArguments");

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
	printInDebugMode("conditionsSequence");

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

void SyntaxParser::printInDebugMode(const char* msg) {
	if (DEBUG_MODE_ON)
		cout << msg << endl;
}
