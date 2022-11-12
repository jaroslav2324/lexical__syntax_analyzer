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

				Push_back("DIVIDER", lexem+symb, n_lex, n_str);
				/*Token t;
				t.type = "DIVIDER";
				t.value = lexem + symb;
				t.pos[0] = n_lex;
				t.pos[1] = n_str;
				token.push_back(t);*///добавляется divider


				if (prog_text[i + 1] != ' ') lexem = prog_text[i + 1];
				else lexem = "";
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
				Push_back("DIVIDER", lexem, n_lex, n_str);
				/*Token t; 
				t.type = "DIVIDER";
				t.value = lexem;
				t.pos[0] = n_lex;
				t.pos[1] = n_str;
				token.push_back(t);*///добавляется divider
			}

			//делается проверка на keyword

			if (keywords.find(lexem) != keywords.end() && !flag_const) {
				flag_id = false;
				Push_back("KEYWORD", lexem, n_lex, n_str);
				/*Token t;
				t.type = "KEYWORD";
				t.value = lexem;
				t.pos[0] = n_lex;
				t.pos[1] = n_str;
				token.push_back(t);*/
			}

			//ЗДесб будет конст
			
			if (flag_const) {
				flag_id = false;
				Push_back("CONSTANT", lexem, n_lex, n_str);
				/*Token t;
				t.type = "CONSTANT";
				t.value = lexem;
				t.pos[0] = n_lex;
				t.pos[1] = n_str;
				token.push_back(t);*/
				flag_const = false;
				//Set_co(t);
				//tab_co.push_back(t);

				n_lex++;
				Push_back("DIVIDER", symb, n_lex, n_str);
				/*t.type = "DIVIDER";
				t.value = symb;
				t.pos[0] = n_lex;
				t.pos[1] = n_str;
				token.push_back(t);*/
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
				Push_back("CONSTANT", lexem, n_lex, n_str);
				/*Token t;
				t.type = "CONSTANT";
				t.value = lexem;
				t.pos[0] = n_lex;
				t.pos[1] = n_str;
				token.push_back(t);*/
				//Set_co(t);
				//tab_co.push_back(t);
			}
			

			//тута ид

			if (flag_id && lexem != "") {
				Push_back("IDENTIFIER", lexem, n_lex, n_str);
				/*Token t;
				t.type = "IDENTIFIER";
				t.value = lexem;
				t.pos[0] = n_lex;
				t.pos[1] = n_str;
				token.push_back(t);*/
				//Set_id(t);
				//tab_id.push_back(t);
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

void Parser::Push_back(string type, string volume, int a1, int a2) {
	Token t;
	t.type = type;
	t.value = volume;
	t.pos[0] = a1;
	t.pos[1] = a2;

	if (type == "IDENTIFIER") {
		Set_id(t);
		if(Find_Error(t)) t.error = true;
	}

	if (type == "CONSTANT") Set_co(t);

	token.push_back(t);

}

bool Parser::Find_Error(Token t) {
	if (Is_digit(t.value[0])) 
		return true;
	return false;
	cout << "";
}

void Parser::Set_id(Token t) {
	for (int i = 0; i < tab_id.size(); i++) {
		if (tab_id[i].value == t.value) return;
	}
	tab_id.push_back(t);
}

void Parser::Set_co(Token t) {
	for (int i = 0; i < tab_co.size(); i++) {
		if (tab_co[i].value == t.value) return;
	}
	tab_co.push_back(t);
}

bool Parser::Is_digit(char c) {
	if (c != '0' && c != '1' && c != '2' && c != '3' && c != '4' && c != '5' && c != '6' && c != '7' && c != '8' && c != '9') return false;
	return true;
}

bool Parser::Is_digit(string s) {
	int i = 0;
	if (s == "") return false;
	while (s[i] != '\0') {
		if (!Is_digit(s[i])) return false;
		i++;
	}
	return true;
}

void Parser::Write() {
	for (int i = 0; i < token.size(); i++) {
		cout << token[i].type << " = " << token[i].value << "[" << token[i].pos[0] << ";" << token[i].pos[1] << "]";
		if (token[i].error) cout << " ERROR";
		cout << endl;
	}


	cout << "-------CO-------" << endl;
	for (int i = 0; i < tab_co.size(); i++) {
		//cout << i << ")" << tab_co[i].type << " = " << tab_co[i].value << "[" << tab_co[i].pos[0] << ";" << tab_co[i].pos[1] << "]" << endl;
		cout << i << ")" << tab_co[i].value << endl;
	}
	cout << "-------ID-------" << endl;
	for (int i = 0; i < tab_id.size(); i++) {
		//cout << i << ")" << tab_id[i].type << " = " << tab_id[i].value << "[" << tab_id[i].pos[0] << ";" << tab_id[i].pos[1] << "]" << endl;
		cout << i << ")" << tab_id[i].value << endl;
	}
}