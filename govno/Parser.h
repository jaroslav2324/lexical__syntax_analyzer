#pragma once
#include <iostream>
#include <string>
#include <set>
#include <vector>

#include "Token.h"
using namespace std;
class Parser {
public:
	void Parser_prog(string, set<string>, set<string>);//сам парсер
	void Write();//вывод токенов
	vector<Token> token;//вектор токенов
	bool Is_digit(string);
};