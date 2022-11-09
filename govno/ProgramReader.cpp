#include "ProgramReader.h"

std::string ProgramReader(const char* programFileName)
{
	std::string programStr; // строка дл€ записи в нее текста программы
	std::ifstream programFile; // сам файл с текстом программы
	programFile.open(programFileName);
	std::getline(programFile, programStr, '\0'); // считываем в строку все символы до '\0'
	std::cout << programStr; // вывод на экран, потом можно и (!!!)Ќ”∆Ќќ(!!!) убрать
	programFile.close();

	return programStr;
}