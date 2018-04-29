/*
Functions related to error handling.
*/

// Guards
#ifndef __KLANGERROR_H_
#define __KLANGERROR_H_

#include<cstdlib> // exit stuff
#include<iostream>
using namespace std;

void scanError(int lineNum, char c)
{
    cerr << "KLANG ERROR: Unrecognized symbol \'" << c
	 << "\' encountered during scan on line: " << lineNum
	 << ".\n";
    exit(EXIT_FAILURE);
}

void parseError(int lineNum, string s)
{
    cerr << "KLANG ERROR: Parse error on line " << lineNum
	 << " encountered while examining \'" << s
	 << "\'.\n";
    exit(EXIT_FAILURE);
}

void semanticError(int lineNum, string s)
{
    // prints line number and an error message
    cerr << "KLANG ERROR: Semantics error on line " << lineNum << ". " << s << endl;
    exit(EXIT_FAILURE);
}
#endif
