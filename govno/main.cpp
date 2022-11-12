#include "ProgramReader.h"
#include "DividerReader.h"
#include "KeywordReader.h"
#include "Parser.h"

int main()
{
	const char* programFileName = "program.txt";	//
	const char* dividersFileName = "dividers.txt";  // названия файлов
	const char* keywordsFileName = "keywords.txt";  //

	Parser p;
	p.Parser_prog(ProgramReader(programFileName), DividerReader(dividersFileName), KeywordReader(keywordsFileName));
	p.Write();
	return 0;
}