/*
This file contains METHODS associated with the Lexeme class.
Also contains functions related to Scanning
 */
#include <iostream>
#include <cctype>
#include <cstdlib>
#include "Scanner.h"
#include "KlangError.h"
//#include <string>
using namespace std;
void skipWhitespace(void);
void startScanner(void);
char look; // current character being examined
int lineNum = 1; // current line number, start at 1
bool lineBreak = false; // was there a line break?
// reserved words
vector<string>  keywords = 
{
    "AND",     "ARRAY",   "ASCII",  "BEGIN",     "BREAK",     "CALL",
   "CASE",    "CSTRING", "CONST",  "DCL",       "DECIMAL",   "DEFAULT",
   "DO",      "DOWNTO",  "ELSE",   "END",       "FOR",       "GLOBAL",
   "GOTO",    "IF",      "INT",    "NEXT",      "NOT",       "NUMBER",
   "OF",      "OR",      "PROC",   "PROCEDURE", "READ",      "READLN",
   "REAL",    "RECORD",  "RETURN", "STRING",    "THEN",      "TO",
   "TYPE",    "VAR",     "WHILE",  "WRITE",     "WRITELN"
};
vector<char> singleChars =
{
    '=', ';', ',', '#', '+', '-', '*',
    '/', '%', '(', ')', '[', ']'
};
// Start the scanner
void startScanner(void)
{
    look = ' ';
    skipWhitespace(); // Make sure to ignore leading whitespace
}
// Skip all whitespace, but keep track of line breaks
void skipWhitespace(void)
{
    while(isspace(look)) {
	if (look == '\n') {
	    lineNum++; // increase lineNum
	    lineBreak = true; // there was a line break!
	}
	look = cin.get(); // update character
    }
    
}

// Determine whether inputted string is a keyword
bool isKeyword(string& s)
{
    int i;
    for (i = 0; i < keywords.size(); i++) {
	if (keywords[i] == s)
	    return true;
    }
    return false;
}

// determine if current character is a "single character"
bool isSingleChar(char c)
{
    int i;
    for (i = 0; i < singleChars.size(); i++) {
	if (singleChars[i] == c)
	    return true;
    }
    return false;
}
// meat of the scanner, builds lexemes from the input stream
Lexeme getNext(void)
{
    string token, value;
    int line;

mulligan: // goto
    
    if (isalpha(look)) {
	// First, deal with identifiers
	value = toupper(look); // add first character
	look = cin.get(); // get the next character
	while (isalpha(look) || isdigit(look)) {
	    // still part of the identifier, so add it to value
	    
	    value += toupper(look); // okay with numbers?
	    look = cin.get(); // move on to next
	}
	// check for a keyword
	if (isKeyword(value))
	    token = value;
	else
	    token = "IDENTIFIER"; // put this as global const?
	skipWhitespace(); // go on to next thing
    } else if (isdigit(look)) {
	// then, deal with numbers
	bool isDecimal = false;
	value = look;
	look = cin.get();
	while (isdigit(look)) {
	    // get the rest of the number (integral part if a decimal)
	    value += look;
	    look = cin.get();
	}
	if (look == '.') {
	    // decimal case
	    isDecimal = true;
	    value += look;
	    look = cin.get();
	}
	while(isdigit(look)) {
	    // get the rest of the number if it is a decimal
	    value += look;
	    look = cin.get();
	}
	// Assign the token
	if (isDecimal)
	    token = "DECIMAL";
	else
	    token = "NUMBER";
	// finished so go on to next
	skipWhitespace();
    } else if (look == '\'') {
	// ASCII constant
	value = look;
	look = cin.get();
	bool done = false; // finished processing?
	while (!done) {
	    if (look != '\'') {
		value += look;
		look = cin.get();
	    } else {
		value += look;
		look = cin.get();
		done = true;
		if (look == '\'') {
		    // not yet finished
		    value += look;
		    look = cin.get();
		}
	    }
	    // determine the token
	    if (value.length() == 3) 
		token = "ASCII";
	    else
		token = "CSTRING"; // constant???
	}
    } else if (look == '{') {
	// comments
	bool done = false; // comment over?
	while (!done) {
	    if (look == '}') // check for end of comment 
		done = true;
	    // check for multiline comment
	    if (look == '\n') {
		lineNum++;
		lineBreak = true;
	    }
	    look = cin.get();
	}
	token = "COMMENT";
	value = ""; // don't add anything, it's a comment
	look = cin.get();
	skipWhitespace();
	goto mulligan; // start over!
    } else if (look == '.') {
	// periods
	value = look;
	look = cin.get();
	token = value;
	skipWhitespace();
    } else if (look == ':') {
	// colons
	value = look;
	look = cin.get();
	if (look == '=') {
	    // this is an assignment, i.e. ":="
	    value += look;
	    look = cin.get();
	}
	token = value;
	skipWhitespace();
    } else if (isSingleChar(look)) {
	// Single characters
	value = look;
	token = look;
	look = cin.get();
	skipWhitespace();
    } else if (look == '<' || look == '>') {
	// comparisons
	value = look;
	look = cin.get();
	if (look == '=') {
	    value += look;
	    look = cin.get();
	} else if (value == "<" && look == '>') {
	    // what is this case?
	    value += look;
	    look = cin.get();
	}
	token = value;
	skipWhitespace();
    } else {
	// ERROR!!! ERROR!!! ERROR!!!
	scanError(lineNum, look);
    }
    // Build the Lexeme!
    line = lineNum; // TEMP
    Lexeme result(line, token, value);
    return result;
}
