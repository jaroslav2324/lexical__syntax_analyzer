#include "KeywordReader.h"

std::set<std::string> KeywordReader(const char* keywordsFileName)
{
	std::ifstream keywordsFile; // файл с ключевыми словами
	std::string str; // строка для считывания из файла
	std::set<std::string> keywordsSet; // сет ключевых слов

	keywordsFile.open(keywordsFileName);

	while (std::getline(keywordsFile, str))
		keywordsSet.insert(str); // заполнение сета

	std::set<std::string>::iterator it = keywordsSet.begin(); // инициализация итератора для вывода на экран	| *
	for (int i = 0; it != keywordsSet.end(); i++, it++)		  //												| * ВОТ ЭТИ СТРОКИ НАДО БУДЕТ УБРАТЬ ИЛИ ЗАКОММЕНТИТЬ,
		std::cout << *it << std::endl;						  // вывод содержимого сета на экран				| * ОДНАКО ВАМ ПОТОМ ИТЕРАТОР БУДЕТ НУЖЕН ДЛЯ РАБОТЫ С СЕТОМ, ТАК ЧТО ОБРАТИТЕ ВНИМАНИЕ
															  // 												| *

	keywordsFile.close();

	return keywordsSet;
}