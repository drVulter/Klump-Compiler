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
    cerr << "klang error: Unrecognized symbol \'" << c
	 << "\' encountered during scan on line: " << lineNum
	 << ".\n";
    exit(EXIT_FAILURE);
}

void parseError(int lineNum, string s)
{
    cerr << "klang error: Parse error on line " << lineNum
	 << " encountered while examining \'" << s
	 << "\'.\n";
    exit(EXIT_FAILURE);
}
#endif
