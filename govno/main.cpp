
#include "settings.h"
#include "ProgramReader.h"
#include "DividerReader.h"
#include "KeywordReader.h"
#include "Parser.h"
#include "SyntaxParser.h"

int main()
{
	const char* programFileName = "program.txt";	//
	const char* dividersFileName = "dividers.txt";  // названия файлов
	const char* keywordsFileName = "keywords.txt";  //

	Parser p;
	vector<Token> listOfTokens;
	p.Parser_prog(ProgramReader(programFileName), DividerReader(dividersFileName), KeywordReader(keywordsFileName));
	listOfTokens = p.getListOfTokens();
	//p.Write();

	SyntaxParser syntaxParser;
	syntaxParser.parseTokens(listOfTokens);
	syntaxParser.printTree();
	//syntaxParser.printIdentifiersTable();


	return 0;
}