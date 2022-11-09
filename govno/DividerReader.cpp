#include "DividerReader.h"

std::set<std::string> DividerReader(const char* dividersFileName)
{
	std::ifstream dividersFile; // файл с разделителями
	std::string str; // строка для считывания из файла
	std::set<std::string> dividersSet; // сет разделителей
 	
	dividersFile.open(dividersFileName);
	
	while (std::getline(dividersFile, str))
		dividersSet.insert(str); // заполнение сета

	std::set<std::string>::iterator it = dividersSet.begin(); // инициализация итератора для вывода на экран	| *
	for (int i = 0; it != dividersSet.end(); i++, it++)		  //												| * ВОТ ЭТИ СТРОКИ НАДО БУДЕТ УБРАТЬ ИЛИ ЗАКОММЕНТИТЬ,
		std::cout << *it << std::endl;						  // вывод содержимого сета на экран				| * ОДНАКО ВАМ ПОТОМ ИТЕРАТОР БУДЕТ НУЖЕН ДЛЯ РАБОТЫ С СЕТОМ, ТАК ЧТО ОБРАТИТЕ ВНИМАНИЕ
															  // 												| *

	dividersFile.close();

	return dividersSet;
}