#include<iostream>
#include<fstream>
#include<string>
#include"scanner.cpp"
#include<stdlib.h>

using namespace std;

/* INSTRUCTION:  Complete all ** parts.
   You may use any method to connect this file to scanner.cpp
   that you had written.  
  e.g. You can copy scanner.cpp here by:
          cp ../ScannerFiles/scanner.cpp .  
       and then append the two files into one: 
          cat scanner.cpp parser.cpp > myparser.cpp
*/

//=================================================
// File parser.cpp written by Group Number: 23
//=================================================

// ----- Four Utility Functions and Globals -----------------------------------

// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)
//    to display syntax error messages as specified by me.  

ofstream fout;
string saved_lexeme;
tokentype saved_token;
bool token_available = false;
string token_Name[16] = {"ERROR", "WORD1", "WORD2", "PERIOD", "VERB", "VERBNEG", "VERBPAST", "VERBPASTNEG", "IS", "WAS", "OBJECT", "SUBJECT", "DESTINATION", "PRONOUN", "CONNECTOR", "EOFM"}; 


// Type of error: Match() fails
// Done by: Leouel Guanzon 
void syntaxerror1(tokentype tt, string saved_lexeme)
{
	cout << "SYNTAX ERROR: expected " << token_Name[tt] << " but found " << saved_lexeme << endl;
	exit(EXIT_FAILURE);
}

// Type of error: default of switch cases
// Done by: Leouel Guanzon 
void syntaxerror2(string pFunction, string saved_lexeme) 
{
	cout << "ERROR: unexpected " << saved_lexeme << " found in " << pFunction << endl;
	exit(EXIT_FAILURE);
}

// ** Need the updated match and next_token with 2 global vars
// saved_token and saved_lexeme

// Purpose: Looks at the next token from the scanner
// Done by: Leouel Guanzon
tokentype next_token()
{
	if(!token_available)
	{
		scanner(saved_token, saved_lexeme);
		cout << "Scanner called using word: " << saved_lexeme << endl;
		if(saved_lexeme == "eofm")
		{
			cout << "SUCCESSFULLY PARSED STORY!" << endl;
			fout.close();
			exit(EXIT_SUCCESS);
		}

		token_available = true;
	}

	return saved_token;
}

// Purpose: Checks if token matches;
// 			if true: returns true
// 			if false: handles error using syntaxerror1()
// Done by: Leouel Guanzon
bool match(tokentype expected)
{
	if(next_token() != expected)
	{
		syntaxerror1(expected, saved_lexeme);
	}
	else {
		cout << "Matched " << token_Name[expected] << endl;
		token_available = false;
		return true;
	}
}

// ----- RDP functions - one per non-term -------------------

// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function
// ** Be sure to put the name of the programmer above each function

// Grammar: <tense> ::= VERBPAST | VERBPASTNEG | VERB | VERBNEG
// Done by: Leouel Guanzon
void tense()
{
	cout << "Processing <tense>" << endl;
	switch(next_token())
	{
		case VERBPAST:
			match(VERBPAST);
			break;
		case VERBPASTNEG:
			match(VERBPASTNEG);
			break;
		case VERB:
			match(VERB);
			break;
		case VERBNEG:
			match(VERBNEG);
			break;
		default:
			syntaxerror2("tense", saved_lexeme);
			break;
	}
}

// Grammar: <be> ::= IS | WAS
// Done by: Leouel Guanzon
void be()
{
	cout << "Processing <be>" << endl;
	switch(next_token())
	{
		case IS:
			match(IS);
			break;
		case WAS:
			match(WAS);
			break;
		default:
			syntaxerror2("be", saved_lexeme);
			break;
	}
}

// Grammar: <verb> ::= WORD2
// Done by: Leouel Guanzon
void verb()
{
	cout << "Processing <verb>" << endl;
	match(WORD2);
}

// Grammar: <noun> ::= WORD1 | PRONOUN
// Done by: Leouel Guanzon
void noun()
{
	cout << "Processing <noun>" << endl;
	switch(next_token())
	{
		case WORD1:
			match(WORD1);
			break;
		case PRONOUN:
			match(PRONOUN);
			break;
		default:
			syntaxerror2("noun", saved_lexeme);
			break;
	}
}

// Grammar: <after_object> ::= <verb> <tense> PERIOD | <noun> DESTINATION <verb> <tense> PERIOD
// Done by: Leouel Guanzon
void after_object()
{
	cout << "Processing <after_object>" << endl;
	switch(next_token())
	{
		case WORD2:
			match(WORD2);
			tense();
			match(PERIOD);
			break;
		case WORD1:
			match(WORD1);
			match(DESTINATION);
			verb();
			tense();
			match(PERIOD);
			break;
		case PRONOUN:
			match(PRONOUN);
			match(DESTINATION);
			verb();
			tense();
			match(PERIOD);
			break;
		default:
			syntaxerror2("after_object", saved_lexeme);
			break;
	}
}

// Grammar: <after_noun> ::= <be> PERIOD | DESTINATION <verb> <tense> PERIOD | OBJECT <after_object>
// Done by: Leouel Guanzon
void after_noun()
{
	cout << "Processing <after_noun>" << endl;
	switch(next_token())
	{
		case IS:
			//match(IS);
			be();
			match(PERIOD);
			break;
		case WAS:
			//match(WAS);
			be();
			match(PERIOD);
			break;
		case DESTINATION:
			match(DESTINATION);
			verb();
			tense();
			match(PERIOD);
			break;
		case OBJECT:
			match(OBJECT);
			after_object();
			break;
		default:
			syntaxerror2("after_noun", saved_lexeme);
			break;
	}
}

// Grammar: <after_subject> ::= <verb> <tense> PERIOD | <noun> <aftern_noun>
// Done by: Leouel Guanzon
void after_subject()
{
	cout << "Processing <after_subject>" << endl;
	switch(next_token())
	{
		case WORD2:
			match(WORD2);
			tense();
			match(PERIOD);
			break;
		case WORD1:
			match(WORD1);
			after_noun();
			break;
		case PRONOUN:
			match(PRONOUN);
			after_noun();
			break;
		default:
			syntaxerror2("after)subject", saved_lexeme);
			break;
	}
}

// Grammar: <s> ::= [CONNECTOR] <noun> SUBJECT <after_subject>
// Done by: Leouel Guanzon
void s()
{
	cout << "Processing <s>" << endl;
	if(next_token() == CONNECTOR)
	{
		match(CONNECTOR);
	}
	noun();
	match(SUBJECT);
	after_subject();
}


string filename;

//----------- Driver ---------------------------

// The new test driver to start the parser
// Done by:  Leouel Guanzon
int main()
{
  cout << "Enter the input file name: ";
  cin >> filename;
  fin.open(filename.c_str());

  cout << "Processing <story>\n" << endl;
  
  s();
  
  while(next_token() != EOFM)
  {
	  s();
  }

  //** calls the <story> to start parsing
  //** closes the input file 

}// end
//** require no other input files!
//** syntax error EC requires producing errors.txt of error messages
//** tracing On/Off EC requires sending a flag to trace message output functions
