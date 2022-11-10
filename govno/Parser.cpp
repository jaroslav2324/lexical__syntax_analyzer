#include "Parser.h"

void Parser::Parser_prog(string prog_text, set<string> dividers, set<string> keywords) {

	string symb;//текущий символ (не char потому что должен работать с set<string>)
	string lexem;//слово лексема: кейворд, идентификатор, константа 
	int n_str = 1;//счетчик номера строки

	int i = 0;//счетчик символов
	while (prog_text[i] != '\0') {
		symb = prog_text[i];


		if (dividers.find(symb) != dividers.end() || symb[0] == '\n' || symb == " ") {//делается проверка на разделитель

			if (keywords.find(lexem) != keywords.end()) {//делается проверка на keyword
				Token t;
				t.type = "KEYWORD";
				t.value = lexem;
				t.pos = n_str;
				token.push_back(t);
			}

			//Проверка на "двойной" divider когда == += <= и тд
			string ss;
			ss = symb + prog_text[i + 1];
			if (dividers.find(ss) != dividers.end()) {
				Token t;
				t.type = "DIVIDER";
				t.value = ss;
				t.pos = n_str;
				token.push_back(t);//добавляется divider
				i++;
			}

			//Если символ не пробел, конец строки и не двойной divivder, то divider должен записаться
			if (symb != " " && symb[0]!='\n' && dividers.find(ss) == dividers.end()) { // проверка на divide
				Token t;
				t.type = "DIVIDER";
				t.value = symb;
				t.pos = n_str;
				token.push_back(t);//добавляется divider
			}

			//eсли это keyword и не divider то это либо константа либо id
			//дописать проверку на константу и на id
			lexem = "";
		}
		else 
			lexem += symb;
		if (symb[0] == '\n') n_str++;//проверка на новую строку
		i++;

	}

}

void Parser::Write() {
	for (int i = 0; i < token.size(); i++) {
		cout << token[i].type << " = " << token[i].value << "[" << token[i].pos << "]" << endl;
	}
}