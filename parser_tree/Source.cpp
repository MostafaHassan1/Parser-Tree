#include<ctype.h>
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

enum token_type
{
	PROGRAM_SY, IS_SY, BEGIN_SY, ID_SY, END_SY, VAR_SY, INTEGER_SY, BOOLEAN_SY, COLOMN_SY, COMMA_SY, SEMICOMA_SY, ASSIGMENT_SY, READ_SY, WRITE_SY,
	IF_SY, THEN_SY, ELSE_SY, WHILE_SY, DO_SY, LEFTPAR_SY, RIGHTPAR_SY, MINUS_SY, OR_SY, TRUE_SY, FALSE_SY, NOT_SY, AND_SY,
	LESSTHEN_SY, GREATERTHAN_SY, EQUAL_SY, GREATERTHENOREQUAL_SY, LESSTHENOREQUAL_SY, NOTEQUAL_SY, PLUS_SY, STAR_SY, DIVSION_SY, NUMERAL_SY, ERROR_SY, EOF_SY

};
enum node_type {
	undefined, PROGRAM_n, IS_n, BEGIN_n, ID_n, END_n, VAR_n, INTEGER_n, BOOLEAN_n, COLOMN_n, COMMA_n, SEMICOMA_n, ASSIGMENT_n, READ_n, WRITE_n,
	IF_n, THEN_n, ELSE_n, WHILE_n, DO_n, LEFTPAR_n, RIGHTPAR_n, MINUS_n, OR_n, TRUE_n, FALSE_n, NOT_n, AND_n, var_list_n, type_n, command_n, expr_n,
	/*added for the nodes */ dec_seq_n, Block_n, dec_seq_tail_n, dec_n, var_list_tail_n,com_seq_n,com_seq_tail_n,boolExpr_n,bool_expr_tail_n,boolTerm_n,bool_term_tail_n,boolEle_n,intExpr_n,int_expr_tail_n,term_n,term_tail_n,element_n,
	LESSTHEN_n, GREATERTHAN_n, EQUAL_n, GREATERTHENOREQUAL_n, LESSTHENOREQUAL_n, NOTEQUAL_n, PLUS_n, STAR_n, DIVSION_n, NUMERAL_n, ERROR_n, EOF_n
};

class token {
public:
	token_type type;
	string name;
	token() {
		type = ERROR_SY;
		name = "";
	}
};
class Node {
public:
	node_type type;
	string lexem;
	Node* child[8];
	Node() {
		type = undefined;
		lexem = "";
		//child[0] = NULL;
		child[0] = child[1] = child[2] = child[3] = child[4] =child[5]=child[6]=child[7]= NULL;
	}
};

/////////////////////////////////////////////////////////////////
token current_token;
Node* root;
/////////////////////////////////////////////////////////////////
class parser {
private: fstream file;
public:
	token check_reserved(string name) {
		token tokenHolder;
		if (name == "program") {
			tokenHolder.name = name;
			tokenHolder.type = PROGRAM_SY;
			return tokenHolder;
		}
		else if (name == "is") {
			tokenHolder.name = name;
			tokenHolder.type = IS_SY;
			return tokenHolder;
		}
		else if (name == "begin") {
			tokenHolder.name = name;
			tokenHolder.type = BEGIN_SY;
			return tokenHolder;
		}
		else if (name == "end") {
			tokenHolder.name = name;
			tokenHolder.type = END_SY;
			return tokenHolder;
		}
		else if (name == "var") {
			tokenHolder.name = name;
			tokenHolder.type = VAR_SY;
			return tokenHolder;
		}
		else if (name == "integer") {
			tokenHolder.name = name;
			tokenHolder.type = INTEGER_SY;
			return tokenHolder;
		}
		else if (name == "boolean") {
			tokenHolder.name = name;
			tokenHolder.type = BOOLEAN_SY;
			return tokenHolder;
		}
		else if (name == "read") {
			tokenHolder.name = name;
			tokenHolder.type = READ_SY;
			return tokenHolder;
		}
		else if (name == "write") {
			tokenHolder.name = name;
			tokenHolder.type = WRITE_SY;
			return tokenHolder;
		}
		else if (name == "if") {
			tokenHolder.name = name;
			tokenHolder.type = IF_SY;
			return tokenHolder;
		}
		else if (name == "true") {
			tokenHolder.name = name;
			tokenHolder.type = TRUE_SY;
			return tokenHolder;
		}
		else if (name == "false") {
			tokenHolder.name = name;
		tokenHolder.type = FALSE_SY;
		return tokenHolder;
		}
		else if (name == "then") {
			tokenHolder.name = name;
			tokenHolder.type = THEN_SY;
			return tokenHolder;
		}
		else if (name == "else") {
			tokenHolder.name = name;
			tokenHolder.type = ELSE_SY;
			return tokenHolder;
		}
		else if (name == "while") {
			tokenHolder.name = name;
			tokenHolder.type = WHILE_SY;
			return tokenHolder;
		}
		else if (name == "do") {
			tokenHolder.name = name;
			tokenHolder.type = DO_SY;
			return tokenHolder;
		}
		else if (name == "is") {
			tokenHolder.name = name;
			tokenHolder.type = IS_SY;
			return tokenHolder;
		}
		else if (name == "and") {
			tokenHolder.name = name;
			tokenHolder.type = AND_SY;
			return tokenHolder;
		}
		else if (name == "or") {
			tokenHolder.name = name;
			tokenHolder.type = OR_SY;
			return tokenHolder;
		}
		else {
			tokenHolder.name = "identifier";
			tokenHolder.type = ID_SY;
			return tokenHolder;
		}
	}
	token get_token() {
		string stringHolder = "";
		token tokenHolder;
		char ch;
		file.get(ch);
		while (!file.eof() && isspace(ch)) {
			file.get(ch);
		}

		if (file.eof()) {
			tokenHolder.name = "End of file";
			tokenHolder.type = EOF_SY;
			return tokenHolder;
		}
		else if (ch == ':') {
			file.get(ch);
			if (isspace(ch)) {
				tokenHolder.name = ":";
				tokenHolder.type = COLOMN_SY;
				return tokenHolder;
			}
			else if (ch == '=') {
				tokenHolder.name = ":=";
				tokenHolder.type = ASSIGMENT_SY;
				return tokenHolder;
			}
			else {
				file.putback(ch);
				{

					tokenHolder.name = ":";
					tokenHolder.type = COLOMN_SY;
					return tokenHolder;
				}
			}
		}
		else if (ch == ';') {
			tokenHolder.name = ch ;
			tokenHolder.type = SEMICOMA_SY;
			return tokenHolder;
		}
		else if (ch == ',') {
			tokenHolder.name = ch;
			tokenHolder.type = COMMA_SY;
			return tokenHolder;
		}
		else if (ch == '(') {
			tokenHolder.name = ch;
			tokenHolder.type = LEFTPAR_SY;
			return tokenHolder;
		}
		else if (ch == ')') {
			tokenHolder.name = ch;
			tokenHolder.type = RIGHTPAR_SY;
			return tokenHolder;
		}
		else if (ch == '-') {
			tokenHolder.name = ch;
			tokenHolder.type = MINUS_SY;
			return tokenHolder;
		}
		else if (ch == '<') {
			file.get(ch);
			if (isspace(ch)) {
				tokenHolder.name = ch;
				tokenHolder.type = LESSTHEN_SY;
				return tokenHolder;
			}
			else if (ch == '=') {
				tokenHolder.name = "<=";
				tokenHolder.type = LESSTHENOREQUAL_SY;
				return tokenHolder;
			}
			else if (ch == '>') {
				tokenHolder.name = "<>";
				tokenHolder.type = NOTEQUAL_SY;
				return tokenHolder;
			}
			else {
				file.putback(ch);
				{
					tokenHolder.name = ch;
				tokenHolder.type = LESSTHEN_SY;
				return tokenHolder;
				}
			}
		}
		else if (ch == '>') {
			file.get(ch);
			if (isspace(ch)) {
				tokenHolder.name = ch;
				tokenHolder.type = GREATERTHAN_SY;
				return tokenHolder;
			}
			else if (ch == '=') {
				tokenHolder.name = ">=";
			tokenHolder.type = GREATERTHENOREQUAL_SY;
			return tokenHolder;
			}
			else {
				file.putback(ch);
				{
					tokenHolder.name = ch;
					tokenHolder.type = GREATERTHAN_SY;
					return tokenHolder;
				}
			}
		}
		else if (ch == '=') {
			tokenHolder.name = ch;
			tokenHolder.type = EQUAL_SY;
			return tokenHolder;
		}
		else if (ch == '+') {
			tokenHolder.name = ch;
			tokenHolder.type = PLUS_SY;
			return tokenHolder;
		}
		else if (ch == '*') {
			tokenHolder.name = ch;
			tokenHolder.type = STAR_SY;
			return tokenHolder;
		}
		else if (ch == '/') {
			tokenHolder.name = ch;
			tokenHolder.type = DIVSION_SY;
			return tokenHolder;
		}
		else if (isdigit(ch)) { //the start if a number
			file.get(ch);
			if (isspace(ch)) {
				tokenHolder.name = "numeral";
				tokenHolder.type = NUMERAL_SY;
				return tokenHolder;
			} //the number ended
			while (!file.eof() && isdigit(ch)) //loops till the end of that number
			{
				file.get(ch);
			}
			file.putback(ch); //to leave the extra char that made us leave the loop
			{
				tokenHolder.name = "numeral";
				tokenHolder.type = NUMERAL_SY;
				return tokenHolder;
			} //it didn't find any char inside the number then it's not an error		
		}
		else if (isalpha(ch)) { //the start of ident
			stringHolder = ch;
			file.get(ch);
			if (isspace(ch)) {
				tokenHolder.name = stringHolder;
				tokenHolder.type = ID_SY;
				return tokenHolder;
			}//it's only 1 char so we know it's a ident and not a reserved word so we don't need to check
			while (!file.eof() && isalnum(ch)) //loops till the end of that string
			{
				stringHolder += ch;
				file.get(ch);
			}
			file.putback(ch); //to leave the extra char that made us leave the loop
			tokenHolder= check_reserved(stringHolder);
			return tokenHolder;
		}

	}
	void display_tokens() {
		token t = get_token();
		while (t.type != EOF_SY)
		{
			switch (t.type)
			{
			case PROGRAM_SY: cout << "the token is Program_sy" << endl;
				break;
			case IS_SY: cout << "the token is IS SYmbol" << endl;
				break;
			case BEGIN_SY: cout << "the token is Begin SYmbol" << endl;
				break;
			case ID_SY: cout << "the token is Ident SYmbol" << endl;
				break;
			case END_SY: cout << "the token is End SYmbol" << endl;
				break;
			case VAR_SY: cout << "the token is var SYmbol" << endl;
				break;
			case INTEGER_SY: cout << "the token is integer SYmbol" << endl;
				break;
			case BOOLEAN_SY: cout << "the token is bool SYmbol" << endl;
				break;
			case COLOMN_SY: cout << "the token is colomn SYmbol" << endl;
				break;
			case COMMA_SY: cout << "the token is comma SYmbol" << endl;
				break;
			case SEMICOMA_SY: cout << "the token is semicoma SYmbol" << endl;
				break;
			case ASSIGMENT_SY: cout << "the token is assigment SYmbol" << endl;
				break;
			case READ_SY: cout << "the token is read SYmbol" << endl;
				break;
			case WRITE_SY: cout << "the token is write SYmbol" << endl;
				break;
			case IF_SY:cout << "the token is if SYmbol" << endl;
				break;
			case THEN_SY: cout << "the token is then SYmbol" << endl;
				break;
			case ELSE_SY: cout << "the token is else SYmbol" << endl;
				break;
			case WHILE_SY: cout << "the token is while SYmbol" << endl;
				break;
			case DO_SY:cout << "the token is do SYmbol" << endl;
				break;
			case LEFTPAR_SY:cout << "the token is leftBar ( SYmbol" << endl;
				break;
			case RIGHTPAR_SY:cout << "the token is rightpar ) SYmbol" << endl;
				break;
			case MINUS_SY:cout << "the token is minus SYmbol" << endl;
				break;
			case OR_SY:cout << "the token is or SYmbol" << endl;
				break;
			case TRUE_SY:cout << "the token is true SYmbol" << endl;
				break;
			case FALSE_SY:cout << "the token is false SYmbol" << endl;
				break;
			case NOT_SY:cout << "the token is not SYmbol" << endl;
				break;
			case LESSTHEN_SY:cout << "the token is lessthan SYmbol" << endl;
				break;
			case GREATERTHAN_SY:cout << "the token is greater than SYmbol" << endl;
				break;
			case EQUAL_SY:cout << "the token is equal SYmbol" << endl;
				break;
			case GREATERTHENOREQUAL_SY:cout << "the token is greater than or equal SYmbol" << endl;
				break;
			case LESSTHENOREQUAL_SY:cout << "the token is less than or equal SYmbol" << endl;
				break;
			case NOTEQUAL_SY:cout << "the token is not equal SYmbol" << endl;
				break;
			case PLUS_SY:cout << "the token is plus SYmbol" << endl;
				break;
			case STAR_SY:cout << "the token is star SYmbol" << endl;
				break;
			case DIVSION_SY:cout << "the token is division SYmbol" << endl;
				break;
			case NUMERAL_SY:cout << "the token is number SYmbol" << endl;
				break;
			case ERROR_SY:cout << "lexical error: illegal token" << endl;
				break;

			}//end switch
			t = get_token();
		}//end while
		if (t.type == EOF_SY) cout << "end of file symbol" << endl;
	}//end display
	void error_token() {
		token t = current_token;
		switch (t.type)
		{
		case PROGRAM_SY: cout << "the token is Program_sy" << endl;
			break;
		case IS_SY: cout << "the token is IS SYmbol" << endl;
			break;
		case BEGIN_SY: cout << "the token is Begin SYmbol" << endl;
			break;
		case ID_SY: cout << "the token is Ident SYmbol" << endl;
			break;
		case END_SY: cout << "the token is End SYmbol" << endl;
			break;
		case VAR_SY: cout << "the token is var SYmbol" << endl;
			break;
		case INTEGER_SY: cout << "the token is integer SYmbol" << endl;
			break;
		case BOOLEAN_SY: cout << "the token is bool SYmbol" << endl;
			break;
		case COLOMN_SY: cout << "the token is colomn SYmbol" << endl;
			break;
		case COMMA_SY: cout << "the token is comma SYmbol" << endl;
			break;
		case SEMICOMA_SY: cout << "the token is semicoma SYmbol" << endl;
			break;
		case ASSIGMENT_SY: cout << "the token is assigment SYmbol" << endl;
			break;
		case READ_SY: cout << "the token is read SYmbol" << endl;
			break;
		case WRITE_SY: cout << "the token is write SYmbol" << endl;
			break;
		case IF_SY:cout << "the token is if SYmbol" << endl;
			break;
		case THEN_SY: cout << "the token is then SYmbol" << endl;
			break;
		case ELSE_SY: cout << "the token is else SYmbol" << endl;
			break;
		case WHILE_SY: cout << "the token is while SYmbol" << endl;
			break;
		case DO_SY:cout << "the token is do SYmbol" << endl;
			break;
		case LEFTPAR_SY:cout << "the token is leftBar ( SYmbol" << endl;
			break;
		case RIGHTPAR_SY:cout << "the token is rightpar ) SYmbol" << endl;
			break;
		case MINUS_SY:cout << "the token is minus SYmbol" << endl;
			break;
		case OR_SY:cout << "the token is or SYmbol" << endl;
			break;
		case TRUE_SY:cout << "the token is true SYmbol" << endl;
			break;
		case FALSE_SY:cout << "the token is false SYmbol" << endl;
			break;
		case NOT_SY:cout << "the token is not SYmbol" << endl;
			break;
		case LESSTHEN_SY:cout << "the token is lessthan SYmbol" << endl;
			break;
		case GREATERTHAN_SY:cout << "the token is greater than SYmbol" << endl;
			break;
		case EQUAL_SY:cout << "the token is equal SYmbol" << endl;
			break;
		case GREATERTHENOREQUAL_SY:cout << "the token is greater than or equal SYmbol" << endl;
			break;
		case LESSTHENOREQUAL_SY:cout << "the token is less than or equal SYmbol" << endl;
			break;
		case NOTEQUAL_SY:cout << "the token is not equal SYmbol" << endl;
			break;
		case PLUS_SY:cout << "the token is plus SYmbol" << endl;
			break;
		case STAR_SY:cout << "the token is star SYmbol" << endl;
			break;
		case DIVSION_SY:cout << "the token is division SYmbol" << endl;
			break;
		case NUMERAL_SY:cout << "the token is number SYmbol" << endl;
			break;
		case ERROR_SY:cout << "lexical error: illegal token" << endl;
			break;

		}//end switch
		if (t.type == EOF_SY) cout << "end of file symbol" << endl;
	}
	void type_display(node_type n) {
		switch (n)
		{
		case undefined: cout << "undifined";
			break;
		case PROGRAM_n: cout << "program Node";
			break;
		case IS_n:  cout << "is Node";
			break;
		case BEGIN_n: cout << "bbegin Node";
			break;
		case ID_n: cout << "idenifier Node";
			break;
		case END_n: cout << "end Node";
			break;
		case VAR_n: cout << "var Node";
			break;
		case INTEGER_n: cout << "integer Node";
			break;
		case BOOLEAN_n: cout << "boolean Node";
			break;
		case COLOMN_n: cout << "colomn Node";
			break;
		case COMMA_n: cout << "comma Node";
			break;
		case SEMICOMA_n: cout << "semiaComma Node";
			break;
		case ASSIGMENT_n: cout << ":= Node";
			break;
		case READ_n: cout << "read Node";
			break;
		case WRITE_n: cout << "write Node";
			break;
		case IF_n: cout << "if Node";
			break;
		case THEN_n: cout << "then Node";
			break;
		case ELSE_n: cout << "else Node";
			break;
		case WHILE_n: cout << "while Node";
			break;
		case DO_n: cout << "do Node";
			break;
		case LEFTPAR_n: cout << "( Node";
			break;
		case RIGHTPAR_n: cout << ") Node";
			break;
		case MINUS_n: cout << "- Node";
			break;
		case OR_n:cout << "or Node";
			break;
		case TRUE_n:cout << "true Node";
			break;
		case FALSE_n:cout << "false Node";
			break;
		case NOT_n:cout << "not Node";
			break;
		case AND_n:cout << "and Node";
			break;
		case var_list_n:cout << "var list Node";
			break;
		case dec_seq_n:cout <<" dec seq Node";
			break;
		case Block_n:cout << "block Node";
			break;
		case dec_seq_tail_n:cout << "dec seq tail Node";
			break;
		case dec_n:cout << "dec Node";
			break;
		case var_list_tail_n:cout << "var list tail Node";
			break;
		case com_seq_n:cout << "com seq Node";
			break;
		case com_seq_tail_n:cout << "com seq tail Node";
			break;
		case boolExpr_n:cout << "bool expr Node";
			break;
		case bool_expr_tail_n:cout << "bool expr tail Node";
			break;
		case boolTerm_n: cout << "bool term Node";
			break;
		case bool_term_tail_n:cout << "bool term tail Node";
			break;
		case boolEle_n:cout << "bool element Node";
			break;
		case intExpr_n:cout << "int expr Node";
			break;
		case int_expr_tail_n:cout << "int expr tail Node";
			break;
		case term_n:cout << "term Node";
			break;
		case term_tail_n:cout << "term tail Node";
			break;
		case element_n:cout << "element Node";
			break;
		case LESSTHEN_n:cout << "< Node";
			break;
		case GREATERTHAN_n:cout << "> Node";
			break;
		case EQUAL_n:cout << "= Node";
			break;
		case GREATERTHENOREQUAL_n:cout << ">= Node";
			break;
		case LESSTHENOREQUAL_n:cout << "<= Node";
			break;
		case NOTEQUAL_n:cout << "<> Node";
			break;
		case PLUS_n:cout << "+ Node";
			break;
		case STAR_n:cout << "* Node";
			break;
		case DIVSION_n:cout << "/ Node";
			break;
		case NUMERAL_n:cout << "numeral Node";
			break;
		case ERROR_n:cout << "error  Node";
			break;
		case EOF_n:cout << "Eof Node";
			break;
		case type_n:cout << "type Node";
			break;
		case expr_n:cout << "expr Node";
			break;
		case command_n:cout << "command Node";
			break;
		default:
			break;
		}
	}
	/*void simple_parser() s
	current_token = get_token();
	program();
	}*/
	parser(string filename)
	{
		file.open(filename);
		if (!file)
		{
			cout << "Unable to open file" << endl;
			system("pause");
			exit(1);
		}
	}
	//parser tree
	void display_tree(Node* Tree) {
		
			if (Tree)
			{
				cout << "Type: "; type_display(Tree->type);cout << " Lexem: " << Tree->lexem << endl;
				display_tree(Tree->child[0]);
				display_tree(Tree->child[1]);
				display_tree(Tree->child[2]);
				display_tree(Tree->child[3]);
				display_tree(Tree->child[4]);
				display_tree(Tree->child[5]);
				display_tree(Tree->child[6]);
				display_tree(Tree->child[7]);
			}
	}
	//parser
	void match(token_type t) {
		if (current_token.type == t)	current_token = get_token();
		else syntax_error();
	}
	void syntax_error() {
		cout << "syntax error in the program in token:" << endl;
		error_token();
		system("pause");
		exit(1);
	}
	void program() {
		Node* ptr = new Node();
		root = ptr;
		ptr->type = PROGRAM_n;
		current_token = get_token();
		//we need to put thte values before match because it will change the values
		ptr->child[0] = new Node();
		ptr->child[0]->type = PROGRAM_n;
		ptr->child[0]->lexem = current_token.name;
		match(PROGRAM_SY);
		////////////////////////////////
		ptr->child[1] = new Node();
		ptr->child[1]->type = ID_n;
		ptr->child[1]->lexem = current_token.name;
		match(ID_SY);
		/////////////////////////////////
		ptr->child[2] = new Node();
		ptr->child[2]->type = IS_n;
		ptr->child[2]->lexem = current_token.name;
		match(IS_SY);
		/////////////////////////////////////
		ptr->child[3]=block();
		////////////////////////////////////
		ptr->child[4] = new Node();
		ptr->child[4]->type = EOF_n;
		ptr->child[4]->lexem = current_token.name;
		match(EOF_SY);
		cout << "program written successfuly" << endl;
		display_tree(root);
	}
	Node* block() {
		Node* ptr = new Node();
		ptr->type = Block_n;  //doesn't have a lexem because block is not written in the program (i.e not a terminal)
		/////////////////////////////////////
		ptr->child[0]=dec_seq();
		////////////////////////////
		ptr->child[1] = new Node();
		ptr->child[1]->type = BEGIN_n;
		ptr->child[1]->lexem = current_token.name;
		match(BEGIN_SY);
		///////////////////////////
		ptr->child[2]=com_seq();
		/////////////////////////
		ptr->child[3] = new Node();
		ptr->child[3]->type = END_n;
		ptr->child[3]->lexem = current_token.name;
		match(END_SY);
		return ptr;
	}
	Node* dec_seq() {
		//while (current_token.type == VAR_SY) dec();
		Node * ptr = new Node();
		ptr->type = dec_seq_n;
		if (current_token.type==VAR_SY) //then there is atleast 1 var declared
		{
			ptr->child[0] = dec();
			ptr->child[1] = dec_seq_tail();
		}
		return ptr;
	}
	Node* dec_seq_tail() {
		Node* ptr = new Node();
		ptr->type = dec_seq_tail_n;
		if (current_token.type==VAR_SY) //there is an declartion more than onc
		{
			ptr->child[0] = dec();
			ptr->child[1] = dec_seq_tail();
		}
		return ptr;
	}
	Node* dec() {
		Node * ptr = new Node();
		ptr->type = dec_n;
		////////////////////////////
		ptr->child[0] = new Node();
		ptr->child[0]->type = VAR_n;
		ptr->child[0]->lexem = current_token.name;
		match(VAR_SY);
		/////////////////////////////////
		ptr->child[1]=var_list();
		////////////////////////////
		ptr->child[2] = new Node();
		ptr->child[2]->type = COLOMN_n;
		ptr->child[2]->lexem = current_token.name;
		match(COLOMN_SY);
		///////////////////////////////////
		ptr->child[3]=type();
		////////////////////////////
		ptr->child[4] = new Node();
		ptr->child[4]->type = SEMICOMA_n;
		ptr->child[4]->lexem = current_token.name;
		match(SEMICOMA_SY);

		return ptr;
	}
	Node* var_list() {
		Node* ptr = new Node();
		ptr->type = var_list_n;
		////////////////////////////
		ptr->child[0] =var();
		if (current_token.type==COMMA_SY) 	
				ptr->child[1] = var_list_tail();
		return ptr;
	//	while (current_token.type == COMMA_SY) var();  //8lt
	}
	Node* var_list_tail() {
		Node* ptr = new Node();
		ptr->type = var_list_tail_n;
		if (current_token.type==COMMA_SY) //there is more than 1 var declaration
		{
			ptr->child[0] = new Node();
			ptr->child[0]->type = COMMA_n;
			ptr->child[0]->lexem = current_token.name;
			match(COMMA_SY);
			//////////////////////////////////
			ptr->child[1] = var();
			ptr->child[2] = var_list_tail();
		}
		return ptr;
	}
	Node* var() {
		Node* ptr = new Node();
		ptr->type = VAR_n;
		/////////////////////////////
		ptr->child[0] = new Node();
		ptr->child[0]->type = ID_n;
		ptr->child[0]->lexem = current_token.name;
		match(ID_SY);
		return ptr;
		}
	/*Node* ident() {
		match(ID_SY);
	}*/
	Node* type() {  //it have no childs i.e a leaf i.e a lonely node just like me 
		Node* ptr = new Node();
		ptr->type = type_n;
		if (current_token.type == INTEGER_SY) {
			
			ptr->type = INTEGER_n;
			ptr->lexem = current_token.name;
			match(INTEGER_SY);
		}
		else {
			ptr->type = BOOLEAN_n;
			ptr->lexem = current_token.name;
			match(BOOLEAN_SY);
		}
		return ptr;
	}
	Node* com_seq() {
		Node* ptr = new Node();
		ptr->type = com_seq_n;
		ptr->child[0]=command();
		if (current_token.type==SEMICOMA_SY)
					ptr->child[1] = com_seq_tail();
		//while (current_token.type == SEMICOMA_SY) {
		//	match(SEMICOMA_SY);
		//	command();
		//}
		return ptr;
	}
	Node* com_seq_tail(){ 
		Node* ptr = new Node();
		ptr->type = com_seq_tail_n;
		if (current_token.type==SEMICOMA_SY)
		{
			ptr->child[0] = new Node();
			ptr->child[0]->type = SEMICOMA_n;
			ptr->child[0]->lexem = current_token.name;
			match(SEMICOMA_SY);
			//////////////////////////////
			ptr->child[1] = command();
			ptr->child[2] = com_seq_tail();
		}
		return ptr;
	}
	Node* command() {
		Node* ptr = new Node();
		ptr->type = command_n;
		if (current_token.type == ID_SY)
		{
			ptr->child[0]=var();
			///////////////////////////////
			ptr->child[1] = new Node();
			ptr->child[1]->type = ASSIGMENT_n;
			ptr->child[1]->lexem = current_token.name;
			match(ASSIGMENT_SY);
			///////////////////////////////////
			ptr->child[2]=expr();
		}
		else if (current_token.type == READ_SY) {
			ptr->child[0] = new Node();
			ptr->child[0]->type = READ_n;
			ptr->child[0]->lexem = current_token.name;
			match(READ_SY);
			///////////////////////////////////
			ptr->child[1]=var();
		}
		else if (current_token.type == WRITE_SY)
		{
			ptr->child[0] = new Node();
			ptr->child[0]->type = WRITE_n;
			ptr->child[0]->lexem = current_token.name;
			match(WRITE_SY);
			////////////////////////////
			ptr->child[1]=var();
		}
		else if (current_token.type == IF_SY) {
			ptr->child[0] = new Node();
			ptr->child[0]->type = IF_n;
			ptr->child[0]->lexem = current_token.name;
			match(IF_SY);
			///////////////////////////////////////
			ptr->child[1]=boolExpr();
			/////////////////////////////////////////
			ptr->child[2] = new Node();
			ptr->child[2]->type = THEN_n;
			ptr->child[2]->lexem = current_token.name;
			match(THEN_SY);
			//////////////////////////////
			ptr->child[3]=com_seq();
			//////////////////////////////
			if (current_token.type == ELSE_SY) {
				ptr->child[4] = new Node();
				ptr->child[4]->type = ELSE_n;
				ptr->child[4]->lexem = current_token.name;
				match(ELSE_SY);
				///////////////////////
				ptr->child[5]=com_seq();
				//////////////////////////
				ptr->child[6] = new Node();
				ptr->child[6]->type = END_n;
				ptr->child[6]->lexem = current_token.name;
				match(END_SY);
				////////////////////////////////////////
				ptr->child[7] = new Node();
				ptr->child[7]->type = IF_n;
				ptr->child[7]->lexem = current_token.name;
				match(IF_SY);
			}
			else if(current_token.type==END_SY) {
				ptr->child[4] = new Node();
				ptr->child[4]->type = END_n;
				ptr->child[4]->lexem = current_token.name;
				match(END_SY);
				/////////////////////////////////
				ptr->child[5] = new Node();
				ptr->child[5]->type = IF_n;
				ptr->child[5]->lexem = current_token.name;
				match(IF_SY);
			}
			else syntax_error();
		}
		else if (current_token.type == WHILE_SY) {
			ptr->child[0] = new Node();
			ptr->child[0]->type = WHILE_n;
			ptr->child[0]->lexem = current_token.name;
			match(WHILE_SY);
			//////////////////////
			ptr->child[1]=boolExpr();
			///////////////////////////
			ptr->child[2] = new Node();
			ptr->child[2]->type = DO_n;
			ptr->child[2]->lexem = current_token.name;
			match(DO_SY);
			//////////////////////
			ptr->child[3]=com_seq();
			/////////////////////////
			ptr->child[4] = new Node();
			ptr->child[4]->type = END_n;
			ptr->child[4]->lexem = current_token.name;
			match(END_SY);
			//////////////////////////////////
			ptr->child[4] = new Node();
			ptr->child[4]->type = WHILE_n;
			ptr->child[4]->lexem = current_token.name;
			match(WHILE_SY);
		}
		else syntax_error();
		return ptr;
	}
	Node* expr()
	 {
		Node* ptr = new Node();
		ptr->type = expr_n;
		if (current_token.type == NUMERAL_SY || current_token.type == ID_SY || current_token.type == LEFTPAR_SY || current_token.type == MINUS_SY) 	ptr->child[0]=intExpr();
		else if (current_token.type == TRUE_SY || current_token.type == FALSE_SY || current_token.type == NOT_SY || current_token.type == LEFTPAR_SY) ptr->child[0]= boolExpr();
		else syntax_error();
		return ptr;
	}

	Node* boolExpr() {
		Node* ptr = new Node();
		ptr->type = boolExpr_n;
		ptr->child[0]=boolTerm();
		//while (current_token.type == OR_SY) {
		//	match(OR_SY);
		//	boolTerm();
		//}
		if (current_token.type==OR_SY)
		{
			ptr->child[1] = bool_expr_tail();
		}
		return ptr;
	}
	Node* bool_expr_tail() {
		Node* ptr = new Node();
		ptr->type = bool_expr_tail_n;
		if (current_token.type==OR_SY)
		{
			ptr->child[0] = new Node();
			ptr->child[0]->type = OR_n;
			ptr->child[0]->lexem = current_token.name;
			match(OR_SY);
			///////////////////////////
			ptr->child[1] = boolTerm();
			//////////////////////////
			ptr->child[2] = bool_expr_tail();
		}
		return ptr;
	}
	Node* boolTerm() {
		Node* ptr = new Node();
		ptr->type = boolTerm_n;
		ptr->child[0]=boolEle();
	/*	while (current_token.type == AND_SY) {
			match(AND_SY);
			boolEle();
		}*/
		if (current_token.type = AND_SY)ptr->child[1] = bool_term_tail();
	

		return ptr;
	}
	Node* bool_term_tail() {
		Node* ptr = new Node();
		ptr->type = bool_term_tail_n;
		if (current_token.type==AND_SY)
		{
			ptr->child[0] = new Node();
			ptr->child[0]->type = AND_n;
			ptr->child[0]->lexem = current_token.name;
			match(AND_SY);
			///////////////////////////
			ptr->child[1] = boolEle();
			////////////////////////
			ptr->child[2] - bool_term_tail();
		}
		return ptr;
	}
	Node* boolEle() {
		Node* ptr = new Node();
		ptr->type = boolEle_n;
		if (current_token.type == TRUE_SY) {
			ptr->child[0] = new Node();
			ptr->child[0]->type = TRUE_n;
			ptr->child[0]->lexem = current_token.name;
			match(TRUE_SY);
		}
		else if (current_token.type == FALSE_SY) {
			ptr->child[0] = new Node();
			ptr->child[0]->type = FALSE_n;
			ptr->child[0]->lexem = current_token.name;
			match(FALSE_SY);
		}
		else if (current_token.type == NOT_SY) {
			ptr->child[0] = new Node();
			ptr->child[0]->type = NOT_n;
			ptr->child[0]->lexem = current_token.name;
			match(NOT_SY);
			////////////////////////
			ptr->child[1] = new Node();
			ptr->child[1]->type = LEFTPAR_n;
			ptr->child[1]->lexem = current_token.name;
			match(LEFTPAR_SY);
			////////////////////////////////
			ptr->child[2]=boolExpr();
			////////////////////////
			ptr->child[3] = new Node();
			ptr->child[3]->type = RIGHTPAR_n;
			ptr->child[3]->lexem = current_token.name;
			match(RIGHTPAR_SY);
		}
		else if (current_token.type == LEFTPAR_SY) {
			ptr->child[0] = new Node();
			ptr->child[0]->type = LEFTPAR_n;
			ptr->child[0]->lexem = current_token.name;
			match(LEFTPAR_SY);
			/////////////////////////////
			ptr->child[1]=boolExpr();
			///////////////////////////////
			ptr->child[2] = new Node();
			ptr->child[2]->type = LEFTPAR_n;
			ptr->child[2]->lexem = current_token.name;
			match(RIGHTPAR_SY);
		}
		else syntax_error();
		return ptr;
	}
	Node* intExpr() {
		Node* ptr = new Node();
		ptr->type = intExpr_n;
		ptr->child[0]=term();
		/*while (current_token.type == PLUS_SY || current_token.type == MINUS_SY)
		{
			if (current_token.type == PLUS_SY) match(PLUS_SY);
			else if (current_token.type == MINUS_SY) match(MINUS_SY);
			term();
		}*/
		if (current_token.type == PLUS_SY || current_token.type == MINUS_SY) ptr->child[1] = int_expr_tail();
		return ptr;
	}
	Node* int_expr_tail() {
		Node* ptr = new Node();
		ptr->type = int_expr_tail_n;
		if (current_token.type==PLUS_SY)
		{
			ptr->child[0] = new Node();
			ptr->child[0]->type = PLUS_n;
			ptr->child[0]->lexem = current_token.name;
			match(PLUS_SY);
			////////////////////
			ptr->child[1] = term();
			///////////////////////
			ptr->child[2] = int_expr_tail();
		}
		else if (current_token.type == MINUS_SY) {
			ptr->child[0] = new Node();
			ptr->child[0]->type = MINUS_n;
			ptr->child[0]->lexem = current_token.name;
			match(MINUS_SY);
			////////////////////
			ptr->child[1] = term();
			///////////////////////
			ptr->child[2] = int_expr_tail();
		}
		return ptr;
	}
	Node* term() {
		Node* ptr = new Node();
		ptr->type = term_n;
		ptr->child[0]=element();
		/*while (current_token.type == STAR_SY || current_token.type == DIVSION_SY)
		{
			if (current_token.type == STAR_SY) match(STAR_SY);
			else if (current_token.type == DIVSION_SY) match(DIVSION_SY);
			element();
		}*/
		if (current_token.type == STAR_SY || current_token.type == DIVSION_SY) ptr->child[1] = term_tail();
		return ptr;
	}
	Node* term_tail(){
		Node* ptr = new Node();
		ptr->type = term_tail_n;
		if (current_token.type == STAR_SY)
		{
			ptr->child[0] = new Node();
			ptr->child[0]->type = STAR_n;
			ptr->child[0]->lexem = current_token.name;
			match(STAR_SY);
			////////////////////
			ptr->child[1] = element();
			///////////////////////
			ptr->child[2] = term_tail();
		}
		else if (current_token.type == DIVSION_SY) {
			ptr->child[0] = new Node();
			ptr->child[0]->type = DIVSION_n;
			ptr->child[0]->lexem = current_token.name;
			match(DIVSION_SY);
			////////////////////
			ptr->child[1] = element();
			///////////////////////
			ptr->child[2] = term_tail();
		}
		return ptr;
	}
	Node* element() {
		Node* ptr = new Node();
		ptr->type = element_n;
		if (current_token.type == NUMERAL_SY) {
			ptr->child[0] = new Node();
			ptr->child[0]->type = NUMERAL_n;
			ptr->child[0]->lexem = current_token.name;
			match(NUMERAL_SY);
		}
		else if (current_token.type == ID_SY) {
			ptr->child[0] = new Node();
			ptr->child[0]->type = ID_n;
			ptr->child[0]->lexem = current_token.name;
			match(ID_SY);
		}
		else if (current_token.type == LEFTPAR_SY) {
			ptr->child[0] = new Node();
			ptr->child[0]->type = LEFTPAR_n;
			ptr->child[0]->lexem = current_token.name;
			match(LEFTPAR_SY);
			///////////////////////////
			ptr->child[1]=intExpr();
			//////////////////////////////
			ptr->child[2] = new Node();
			ptr->child[2]->type = RIGHTPAR_n;
			ptr->child[2]->lexem = current_token.name;
			match(RIGHTPAR_SY);
		}
		else if (current_token.type == MINUS_SY) {
			ptr->child[0] = new Node();
			ptr->child[0]->type = MINUS_n;
			ptr->child[0]->lexem = current_token.name;
			match(MINUS_SY);
			///////////////////////////
			ptr->child[1]=element();
		}
		return ptr;
	}
};

int main() {
	parser pa("Text.txt");
	pa.program();
	system("pause");
	return 0;
}