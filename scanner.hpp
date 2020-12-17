#pragma once
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

/* Look for all **'s and complete them */

//=====================================================
// File scanner.cpp written by: Group Number: 23 
//=====================================================

//Done by: Leouel Guanzon and John Foster
//Tables are moved here so functions can access them.
enum tokentype {ERROR, WORD1, WORD2, PERIOD, VERB, VERBNEG, VERBPAST, VERBPASTNEG, IS, WAS, OBJECT, SUBJECT, DESTINATION, PRONOUN, CONNECTOR, EOFM};

string tokenName[16] = {"ERROR", "WORD1", "WORD2", "PERIOD", "VERB", "VERBNEG", "VERBPAST", "VERBPASTNEG", "IS", "WAS", "OBJECT", "SUBJECT", "DESTINATION", "PRONOUN", "CONNECTOR", "EOFM"}; 

//Array is used for simplicity
string reservedWords[38] = {"masu", "VERB", "masen", "VERBNEG", "mashita", "VERBPAST", 
"masendeshita", "VERBPASTNEG", "desu", "IS", "deshita", "WAS", 
"o", "OBJECT", "wa", "SUBJECT", "ni", "DESTINATION", 
"watashi", "PRONOUN", "anata", "PRONOUN", "kare", "PRONOUN", 
"kanojo", "PRONOUN", "sore", "PRONOUN", "mata", "CONNECTOR", 
"soshite", "CONNECTOR", "shikashi", "CONNECTOR", 
"dakara", "CONNECTOR", "eofm", "EOFM"};

// --------- Two DFAs ---------------------------------
// WORD DFA 
// Done by: Leouel Guanzon
// RE:
// (b|g|h|k|m|n|p|r) (y ((a|e|i|o|u|E|I)^+ | (a|e|i|o|u|E|I)^+ n) | (a|e|i|o|u|E|I)^+ | (a|e|i|o|u|E|I)^+ n)
// (a|e|i|o|u|E|I)^+ | (a|e|o|i|u|E|I)^+ n
// (d|j|w|y|z) ( (a|e|i|o|u|E|I)^+ | (a|e|i|o|u|E|I)^+ n)
// s (h((a|e|i|o|u|E|I)^+ | (a|e|i|o|u|E|I)^+ n)) | ((a|e|i|o|u|I|E)^+ | (a|e|i|o|u|I|E)^+ n))
// t (s((a|e|i|o|u|I|E)^+ | (a|e|i|o|u|I|E)^+ n))) | ((a|e|i|o|u|I|E)^+ | (a|e|i|o|u|I|E)^+ n)
// ch ((a|e|i|o|u|I|E)^+ | (a|e|i|o|u|I|E)^+ n)

//Done by: Marco Flores
bool isVowel(char c);

//Done by: Marco Flores
bool isConsonant1(char c);

//Done by: Marco Flores
bool isConsonant2(char c);

//Done by: Leouel Guanzon and Marco Flores
bool word (string s);

// PERIOD DFA 
// Done by: Leouel Guanzon and Marco Flores
bool period (string s);

// ------ Three  Tables -------------------------------------

// TABLES Done by: Leouel Guanzon and John Foster
// Moved to the top to be use for global scope

/*
// ** Update the tokentype to be WORD1, WORD2, PERIOD, ERROR, EOFM, etc.
enum tokentype {ERROR, WORD1, WORD2, PERIOD, VERB, VERBNEG, VERBPAST, VERBPASTNEG, IS, WAS, OBJECT, SUBJECT, DESTINATION, PRONOUN, CONNECTOR, EOFM};

// ** For the display names of tokens - must be in the same order as the tokentype.
string tokenName[16] = {"ERROR", "WORD1", "WORD2", "PERIOD", "VERB", "VERBNEG", "VERBPAST", "VERBPASTNEG", "IS", "WAS", "OBJECT", "SUBJECT", "DESTINATION", "PRONOUN", "CONNECTOR", "EOFM"}; 

string reservedWords[38] = {"masu", "VERB", "masen", "VERBNEG", "mashita", "VERBPAST", 
"masendeshita", "VERBPASTNEG", "desu", "IS", "deshita", "WAS", 
"o", "OBJECT", "wa", "SUBJECT", "ni", "DESTINATION", 
"watashi", "PRONOUN", "anata", "PRONOUN", "kare", "PRONOUN", 
"kanojo", "PRONOUN", "sore", "PRONOUN", "mata", "CONNECTOR", 
"soshite", "CONNECTOR", "shikashi", "CONNECTOR", 
"dakara", "CONNECTOR", "eofm", "EOFM"};
*/

// ** Need the reservedwords table to be set up here. 
// ** Do not require any file input for this. Hard code the table.
// ** a.out should work without any additional files.

// ------------ Scanner and Driver ----------------------- 

ifstream fin;  // global stream for reading from the input file

// Scanner processes only one word each time it is called
// Gives back the token type and the word itself
// ** Done by: Leouel Guanzon and John Foster
int scanner(tokentype& tt, string& w);