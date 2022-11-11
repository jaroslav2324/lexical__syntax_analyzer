#include "Parser.h"

void Parser::Parser_prog(string prog_text, set<string> dividers, set<string> keywords) {

	string symb = " ";//текущий символ (не char потому что должен работать с set<string>)
	string lexem;//слово лексема: кейворд, идентификатор, константа 
	int n_str = 1;//счетчик номера строки
	int n_lex = 1;
	bool flag_const = false;
	bool flag_id = false;

	int i = 0;//счетчик символов
	while (symb[0] != '\0') {
		symb = prog_text[i];

		if (dividers.find(lexem) != dividers.end() || dividers.find(symb) != dividers.end() || symb[0] == '\n' || symb == " ") {//делается проверка на разделитель
			flag_id = true;

						//Проверка на "двойной" divider когда == += <= и тд
			/*string ss;
			ss = symb + prog_text[i + 1];*/
			if (dividers.find(lexem) != dividers.end() && dividers.find(symb) != dividers.end() && dividers.find(lexem+symb) != dividers.end()) {
				flag_id = false;
				Token t;
				t.type = "DIVIDER";
				t.value = lexem + symb;
				t.pos[0] = n_lex;
				t.pos[1] = n_str;
				token.push_back(t);//добавляется divider
				lexem = prog_text[i + 1];
				i+=2;
				continue;
			}

			////Если символ не пробел, конец строки и не двойной divivder, то divider должен записаться
			//if (symb != " " && symb[0] != '\n' && dividers.find(ss) == dividers.end()) { // проверка на divide
			//	Token t;
			//	t.type = "DIVIDER";
			//	t.value = symb;
			//	t.pos[1] = n_str;
			//	token.push_back(t);//добавляется divider
			//}



			if (dividers.find(lexem) != dividers.end() && !flag_const) {
				flag_id = false;
				Token t; 
				t.type = "DIVIDER";
				t.value = lexem;
				t.pos[0] = n_lex;
				t.pos[1] = n_str;
				token.push_back(t);//добавляется divider
			}

			if (keywords.find(lexem) != keywords.end() && !flag_const) {//делается проверка на keyword
				flag_id = false;
				Token t;
				t.type = "KEYWORD";
				t.value = lexem;
				t.pos[0] = n_lex;
				t.pos[1] = n_str;
				token.push_back(t);
			}

			//ЗДесб будет конст
			
			if (flag_const) {
				flag_id = false;
				Token t;
				t.type = "CONSTANT";
				t.value = lexem;
				t.pos[0] = n_lex;
				t.pos[1] = n_str;
				token.push_back(t);
				flag_const = false;

				n_lex++;
				t.type = "DIVIDER";
				t.value = symb;
				t.pos[0] = n_lex;
				t.pos[1] = n_str;
				token.push_back(t);
				lexem = "";
				i++;
				n_lex++;
				continue;
			} 
			if (lexem == "'" || lexem[0] == '\"' && !flag_const) {
				flag_id = false;
				flag_const = true;
			}

			if (Is_digit(lexem)) {
				flag_id = false;
				Token t;
				t.type = "CONSTANT";
				t.value = lexem;
				t.pos[0] = n_lex;
				t.pos[1] = n_str;
				token.push_back(t);
			}
			

			//тута ид

			if (flag_id && lexem != "") {
				Token t;
				t.type = "IDENTIFIER";
				t.value = lexem;
				t.pos[0] = n_lex;
				t.pos[1] = n_str;
				token.push_back(t);
			}

			//eсли это keyword и не divider то это либо константа либо id
			//дописать проверку на константу и на id

			if (lexem != "")
				n_lex++;

			if (symb[0] != '\n' && symb != " ") {
				lexem = symb;
			}
			else 
				lexem = "";
		}
		else 
			lexem += symb;

		if (symb[0] == '\n') {
			n_str++;//проверка на новую строку
			n_lex = 1;
		}
		i++;

	}

}

bool Parser::Is_digit(string s) {
	int i = 0;
	if (s == "") return false;
	while (s[i] != '\0') {
		if (s[i] != '0' && s[i] != '1' && s[i] != '2' && s[i] != '3' && s[i] != '4' && s[i] != '5' && s[i] != '6' && s[i] != '7' && s[i] != '8' && s[i] != '9') return false;
		i++;
	}
	return true;
}

void Parser::Write() {
	for (int i = 0; i < token.size(); i++) {

		//if (i != 0 && (token[i-1].pos[1] != token[i].pos[1])) cout << endl;

		cout << token[i].type << " = " << token[i].value << "[" << token[i].pos[0] << ";" << token[i].pos[1] << "]" << endl;
	}
}