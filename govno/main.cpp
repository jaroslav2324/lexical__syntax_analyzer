#include "ProgramReader.h"
#include "DividerReader.h"
#include "KeywordReader.h"

int main()
{
	const char* programFileName = "program.txt";	//
	const char* dividersFileName = "dividers.txt";  // названия файлов
	const char* keywordsFileName = "keywords.txt";  //

	std::cout << "====Program in one string====" << std::endl << std::endl;
	ProgramReader(programFileName);
	std::cout << std::endl << std::endl << "====Dividers====" << std::endl << std::endl;
	DividerReader(dividersFileName);
	std::cout << std::endl << std::endl << "====Keywords====" << std::endl << std::endl;
	KeywordReader(keywordsFileName);
	
	return 0;
}