#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <stdlib.h>
#include <cstring>
#include "scanner.hpp"
using namespace std;

ofstream fout;
ofstream ferr;
string saved_lexeme;
tokentype saved_token;
bool token_available = false;
bool disable_tracing = false;
string token_Name[16] = {"ERROR", "WORD1", "WORD2", "PERIOD", "VERB", "VERBNEG", "VERBPAST", "VERBPASTNEG", "IS", "WAS", "OBJECT", "SUBJECT", "DESTINATION", "PRONOUN", "CONNECTOR", "EOFM"}; 

string filename;


/* INSTRUCTION:  copy your parser.cpp here
      cp ../ParserFiles/parser.cpp .
   Then, insert or append its contents into this file and edit.
   Complete all ** parts.
*/

/* INSTRUCTION:  Complete all ** parts.
   You may use any method to connect this file to scanner.cpp
   that you had written.  
  e.g. You can copy scanner.cpp here by:
          cp ../ScannerFiles/scanner.cpp .  
       and then append the two files into one: 
          cat scanner.cpp parser.cpp > myparser.cpp
*/

//=================================================
// File translator.cpp written by Group Number: 23
//=================================================

// ----- Additions to the parser.cpp ---------------------

// ** Declare Lexicon (i.e. dictionary) that will hold the content of lexicon.txt
// Make sure it is easy and fast to look up the translation.
// Do not change the format or content of lexicon.txt 
//  Done by: Marco Flores
unordered_map<string, string> lexicon_map;
string saved_E_word;


// ** Additions to parser.cpp here:
//    getEword() - using the current saved_lexeme, look up the English word
//                 in Lexicon if it is there -- save the result   
//                 in saved_E_word
//  Done by: Marco Flores 
bool getEword(){
  std::unordered_map<std::string,string>::const_iterator it = lexicon_map.find(saved_lexeme);
  if ( it == lexicon_map.end()) {
	  	//No translation exists, so we set the "english word" as just the original word in japanese
		saved_E_word = saved_lexeme;
		return 0;
  }
  //Found a translation, save it as the english word
  saved_E_word = it->second;
  return 1;
}

//    gen(line_type) - using the line type,
//                     sends a line of an IR to translated.txt
//                     (saved_E_word or saved_token is used)
//Done by: Leouel Guanzon
void gen(string line_type){
  //use fout, the file is already open
	if(line_type == "TENSE")
	{
		cout << line_type << ": " << token_Name[saved_token] << endl;
		fout << line_type << ": " << token_Name[saved_token] << endl;
	}
	else
	{
		cout << line_type << ": " << saved_E_word << endl;
		fout << line_type << ": " << saved_E_word << endl;
	}
}
// ----- Changes to the parser.cpp content ---------------------

// ** Comment update: Be sure to put the corresponding grammar 
//    rule with semantic routine calls
//    above each non-terminal function 

// ** Each non-terminal function should be calling
//    getEword and/or gen now.


// Type of error: Match() fails
// Done by: Leouel Guanzon 
void syntaxerror1(tokentype tt, string saved_lexeme)
{
	cout << "\nSYNTAX ERROR: expected " << token_Name[tt] << " but found " << saved_lexeme << endl;
	ferr << "\nSYNTAX ERROR: expected " << token_Name[tt] << " but found " << saved_lexeme << endl;
	exit(EXIT_FAILURE);
}

// Type of error: default of switch cases
// Done by: Leouel Guanzon 
void syntaxerror2(string pFunction, string saved_lexeme) 
{
	cout << "\nSYNTAX ERROR: unexpected " << saved_lexeme << " found in " << pFunction << endl;
	ferr << "\nSYNTAX ERROR: expected " << saved_lexeme << " but found " << pFunction << endl;
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
		cout << "Scanner called using word: " << saved_lexeme << endl;//not sure if this is a tracing message
		if(saved_lexeme == "eofm")
		{
			cout << endl;
			cout << "Successfully parsed <story>." << endl;
			fout.close();
			ferr.close();
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
		if (!disable_tracing){
			cout << "Matched " << token_Name[expected] << endl;
		}
		token_available = false;
		return true;
	}
	return false;
}

// ----- RDP functions - one per non-term -------------------

// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function
// ** Be sure to put the name of the programmer above each function

// Grammar: <tense> ::= VERBPAST | VERBPASTNEG | VERB | VERBNEG
// Done by: Leouel Guanzon, Marco Flores
void tense()
{
	if (!disable_tracing){
		cout << "Processing <tense>" << endl;
	}
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
// Done by: Leouel Guanzon, Marco Flores
void be()
{
	if (!disable_tracing){
		cout << "Processing <be>" << endl;
	}
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
// Done by: Leouel Guanzon, Marco Flores
void verb()
{
	if (!disable_tracing){
		cout << "Processing <verb>" << endl;
	}
	match(WORD2);
}

// Grammar: <noun> ::= WORD1 | PRONOUN
// Done by: Leouel Guanzon, Marco Flores
void noun()
{
	if (!disable_tracing){
		cout << "Processing <noun>" << endl;
	}
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

// Grammar: <after_object> ::= <verb> #getEword# #gen(ACTION)# 
// 							   <tense> #gen(TENSE)# PERIOD | 
// 							   <noun> #getEword# DESTINATION #gen(TO)#
// 							   <verb> #getEword# #gen(ACTION)#
// 							   <tense> #gen(TENSE)# PERIOD
// Done by: Leouel Guanzon, Marco Flores
void after_object()
{
	if (!disable_tracing){
		cout << "Processing <afterObject>" << endl;
	}
	switch(next_token())
	{
		case WORD2:
			verb();
			getEword();
			gen("ACTION");
			tense();
			gen("TENSE");
			match(PERIOD);
			break;
		case WORD1:
			noun();
			getEword();
			match(DESTINATION);
			gen("TO");
			verb();
			getEword();
			gen("ACTION");
			tense();
			gen("TENSE");
			match(PERIOD);
			break;
		case PRONOUN:
			match(PRONOUN);
			getEword();
			match(DESTINATION);
			gen("TO");
			verb();
			getEword();
			gen("ACTION");
			tense();
			gen("TENSE");
			match(PERIOD);
			break;
		default:
			syntaxerror2("afterObject", saved_lexeme);
			break;
	}
}

// Grammar: <after_noun> ::= <be> #gen(DESCRIPTION)# #gen(TENSE)# PERIOD | 
// 							 DESTINATION #gen(TO)#
// 							 <verb> #getEword# #gen(ACTION)#
// 							 <tense> #gen(TENSE)# PERIOD | 
// 							 OBJECT #gen(OBJECT)#
// 							 <after_object>
// Done by: Leouel Guanzon, Marco Flores
void after_noun()
{
	if (!disable_tracing){
		cout << "Processing <afterNoun>" << endl;
	}
	switch(next_token())
	{
		case IS:
			be();
			gen("DESCRIPTION");
			gen("TENSE");
			match(PERIOD);
			break;
		case WAS:
			be();
			gen("DESCRIPTION");
			gen("TENSE");
			match(PERIOD);
			break;
		case DESTINATION:
			match(DESTINATION);
			gen("TO");
			verb();
			getEword();
			gen("ACTION");
			tense();
			gen("TENSE");
			match(PERIOD);
			break;
		case OBJECT:
			match(OBJECT);
			gen("OBJECT");
			after_object();
			break;
		default:
			syntaxerror2("afterNoun", saved_lexeme);
			break;
	}
}

// Grammar: <after_subject> ::= <verb> #getEword# #gen(ACTION)#
// 								<tense> #gen(TENSE)# PERIOD | 
// 								<noun> #getEword#
// 								<aftern_noun>
// Done by: Leouel Guanzon, Marco Flores
void after_subject()
{
	if (!disable_tracing){
		cout << "Processing <afterSubject>" << endl;
	}
	switch(next_token())
	{
		case WORD2:
			verb();
			getEword();
			gen("ACTION");
			tense();
			gen("TENSE");
			match(PERIOD);
			break;
		case WORD1:
			noun();
			getEword();
			after_noun();
			break;
		case PRONOUN:
			noun();
			getEword();
			after_noun();
			break;
		default:
			syntaxerror2("afterSubject", saved_lexeme);
			break;
	}
}

// Grammar: <s> ::= [CONNECTOR #getEword# #gen(CONNECTOR)#]
// 					<noun> #getEword# SUBJECT #gen(ACTOR)# 
// 					<after_subject>
// Done by: Leouel Guanzon, Marco Flores
void s()
{
	if (!disable_tracing){
		cout << "Processing <s>" << endl;
	}
	if(next_token() == CONNECTOR)
	{
		match(CONNECTOR);
		getEword();
		gen("CONNECTOR");
	}
	noun();
	getEword();
	match(SUBJECT);
	gen("ACTOR");
	after_subject();
}


// ---------------- Driver ---------------------------

// The final test driver to start the translator
// Done by:  John Foster
int main(int argc, char* argv[])
{
  // opens the lexicon.txt file and reads it into Lexicon
  // closes lexicon.txt
  string k,v;
  fin.open("lexicon.txt");
  if (!fin) {
    cerr << "Can't open lexicon.txt";
    return 1;
  }
  while (fin >> k >> v) {
    lexicon_map[k] = v;
  }
  fin.close();

  // opens the output file translated.txt
  fout.open("translated.txt");
  if (!fout) {
    cerr << "Can't open translated.txt";
    return 1;
  }
  
  // opens the output file translated.txt
  ferr.open("errors.txt");
  if (!ferr) {
    cerr << "Can't open errors.txt";
    return 1;
  }
  

  //** calls the <story> to start parsing

  //** closes the input file 
  //** closes traslated.txt
  cout << "Enter the input file name: ";
  cin >> filename;
  fin.open(filename.c_str());
  
  if (argc==2 && strcmp(argv[1],"-dissable") == 0){
	  disable_tracing = true;
  }
  if (!disable_tracing){
	  cout << "Processing <story>\n" << endl;
  }
  // Grammar: <story> ::= <s> { <s> }
  s();
  fout << endl;
  
  while(next_token() != EOFM)
  {
	  s();
	  fout << endl;
  }

  fin.close();
  fout.close();
 
}// end
//** require no other input files!
//** syntax error EC requires producing errors.txt of error messages
//** tracing On/Off EC requires sending a flag to trace message output functions

