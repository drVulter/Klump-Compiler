/*
  Test functionality of parser
 */
#include<iostream>
#include<iomanip>
#include<cstdlib>
#include "Scanner.h"
#include "PalParser.h"

using namespace std;

Lexeme currentLex;

int main(void)
{
    startScanner();
    currentLex = getNext();
    pal_program(currentLex);
    cout << "Success! no parser errors!\n";
    cout << "Feelin' fine\n";
    return 0;
}
