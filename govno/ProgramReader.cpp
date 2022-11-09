#include "ProgramReader.h"

std::string ProgramReader(const char* programFileName)
{
	std::string programStr; // ������ ��� ������ � ��� ������ ���������
	std::ifstream programFile; // ��� ���� � ������� ���������
	programFile.open(programFileName);
	std::getline(programFile, programStr, '\0'); // ��������� � ������ ��� ������� �� '\0'
	std::cout << programStr; // ����� �� �����, ����� ����� � (!!!)�����(!!!) ������
	programFile.close();

	return programStr;
}