/*
Simple file to test the functionality of the Scanner.
execute by feeding it a file, e.g. 
./ScanTest < test.klump
 */
#include<iostream>
#include<iomanip>
#include<cstdlib>
#include "Scanner.h"

using namespace std;

Lexeme currentLex;

int main(int argc,char* argv[])
{
    startScanner(); // begin ...

    currentLex = getNext();

    while (!cin.eof()) {
	cout << currentLex.getLineNum() << " "
	     << currentLex.getValue() << " "
	     << currentLex.getToken() << endl;
	currentLex = getNext();
    }
    cout << currentLex.getLineNum() << " "
	     << currentLex.getValue() << " "
	     << currentLex.getToken() << endl;
    exit(EXIT_SUCCESS);
}
/*
char getChar(void) {
    return cin.get();
}
*/
