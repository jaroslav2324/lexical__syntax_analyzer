#include "SyntaxError.h"

SyntaxError::SyntaxError(std::string errorMessage, int line, int position)
{
	SyntaxError::errorMessage = errorMessage;
	SyntaxError::errorLine = line;
	SyntaxError::errorPosition = position;
}

void SyntaxError::printMessage()
{
	std::cout << "Error occured at line " << errorLine << " position " << errorPosition << " : " 
																	   << errorMessage << std::endl;
	return ;
}
