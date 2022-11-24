#include "MultipleDefinitionError.h"

MultipleDefinitionError::MultipleDefinitionError(std::string errorMessage, int line, int position)
{
	MultipleDefinitionError::errorMessage = errorMessage;
	MultipleDefinitionError::errorLine = line;
	MultipleDefinitionError::errorPosition = position;
}

void MultipleDefinitionError::printMessage()
{
	std::cout << "Error occured at line " << errorLine << " position " << errorPosition << " : "
		<< errorMessage << std::endl;
	return;
}
