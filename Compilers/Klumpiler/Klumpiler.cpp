/*
  Compiler for the PAL subset of the KLUMP programming language.
  Code emitting function definitions can be found in PalCompiler.h
*/


#include <iostream>
#include <cctype>
#include <cstdlib>
#include "Scanner.h"
#include "KlangError.h"
#include "PalCompiler.h"
#include <string>
#include <stack>

//  add prototypes
void klump_program(Lexeme c);
void global_definitions(void);
void const_definitions(void);
void const_list(void);
void konst(void); // corresponds to <const> in grammar
void type_definitions(void);
void dcl_definitions(void);
void dcl_list(void);
void procedure(void);
void statement_list(void);
void statement(void);
void write_statement(void);
void assignment_statement(void);
void expression(void);
void more_expression(void);
void term(void);
void more_term(void);
void factor(void);
void end_pal(void);
void addop(void);
void mulop(void);

using namespace std;

Lexeme current;
// store the variable names
stack<string> variables; 

int main(void)
{
    // Start the scanner 
    startScanner();
    // Start scanning
    current = getNext();
    // Start parsing/code emitting
    klump_program(current);

    return 0;
}


// main calls this method
void klump_program(Lexeme c)
{
    current = c;
    // klump_program -> <global_definitions> <procedure_list> .
    global_definitions();
    procedure_list();
    // write .data and .bss sections
    emitBss(variables);
    emitData();
    end_pal();
    // make sure we have "." at the end
    //if (current.getToken() != ".")
    //    parseError(current.getLineNum(), current.getValue());
}
void global_definitions(void)
{
    
}
void dcl_definitions(void)
{
    // dcl_definitions -> DCL dcl_list | e
    // get the first lexeme
    //current = getNext(); // from Scanner.cpp
    if (current.getToken() == "DCL") {
        current = getNext();
        dcl_list();
    } else {
        parseError(current.getLineNum(), current.getValue());
    }
    // if not, assume no dcl_list and go right to procedure?
    //procedure();
}

void dcl_list(void)
{
  // dcl_list -> IDENTIFIER : INT ; dcl_list | e
    if (current.getToken() == "IDENTIFIER") {
        variables.push(current.getValue());
        current = getNext();
        if (current.getToken() == ":") {
            current = getNext();
            if (current.getToken() == "INT") {
                current = getNext();
                if (current.getToken() == ";") {
                    current = getNext();
                    dcl_list();
                } else {
                    // clean off stack, necessary???
                    parseError(current.getLineNum(), current.getValue());
                }
            } else {
                parseError(current.getLineNum(), current.getValue());
            }
        } else {
            parseError(current.getLineNum(), current.getValue());
        }
    } else {
        //parseError(current.getLineNum(), current.getValue());
    }
    
}

void procedure(void)
{
    // procedure -> BEGIN statement_list END

    // first check for "BEGIN"
    if (current.getToken() == "BEGIN") {
        current = getNext();
        front();
        statement_list();
    } else {
        parseError(current.getLineNum(), current.getValue());
    }
    //cout << "passed\n";
    // if that all passes, check for the "END"
    if (current.getToken() == "END") {
        current = getNext();
        back(); // emit cleanup for .data section
        //end_pal();
    } else
        parseError(current.getLineNum(), current.getValue());

}

void statement_list(void)
{
    /* statement_list -> statement statement_list | e */

    // check for a statement
    if ((current.getToken() == "WRITELN") || (current.getToken() == "IDENTIFIER")) {
        statement();
        statement_list();
    } else {
        //parseError(current.getLineNum(), current.getValue());
    }
}
void statement(void)
{
    /* statement -> write_statement | assignment_statement */

    // check for write statement or assignment
    if (current.getToken() == "WRITELN") {
        current = getNext();
        write_statement();
    } else if (current.getToken() == "IDENTIFIER") {
        //current = getNext();
        // don't getNext yet, will need this val for next function
        assignment_statement();
    } else {
        parseError(current.getLineNum(), current.getValue());
    }
}

void write_statement(void)
{
    /* write_statement -> WRITELN ( IDENTIFIER ) ; */
    if (current.getToken() == "(") {
        current = getNext();
        if (current.getToken() == "IDENTIFIER") {
            string var = current.getValue(); // hold onto this
            current = getNext();
            if (current.getToken() == ")") {
                current = getNext();
                if (current.getToken() == ";") {
                    // successful parsing, so emit the statement
                    emitWriteStatement(var);
                    current = getNext();
                } else
                    parseError(current.getLineNum(), current.getValue());
            } else
                parseError(current.getLineNum(), current.getValue());
        } else
            parseError(current.getLineNum(), current.getValue());
    } else
        parseError(current.getLineNum(), current.getValue());
}

void assignment_statement(void)
{
    /* assignment_statement -> IDENTIFIER := expression ; */

    // save the value
    string id = current.getValue();
    // NOW get next lexeme
    current = getNext();
    if (current.getToken() == ":=") {
        current = getNext();
        expression();
        emitAssignment(id);
        if (current.getToken() == ";") {
            current = getNext();
        } else
            parseError(current.getLineNum(), current.getValue());
    } else
        parseError(current.getLineNum(), current.getValue());
}

void expression(void)
{
    /* expression -> term more_expression */

    term();
    more_expression();
}

void more_expression(void)
{
    /* more_expression -> addop term more_expression | e */

    // deal with + or - here ???? or use addop function
    if ((current.getToken() == "+") || (current.getToken() == "-")) {
        //current  = getNext(); // get rid of this if using addop()
        string opCode = current.getValue();
        addop();
        term();
        emitAddop(opCode);
        more_expression();
    }
}

void term(void)
{
    /* term -> factor more_term */

    factor();
    more_term();
}

void more_term(void)
{
    /* more_term -> mulop factor more_term | e */

    if ((current.getToken() == "*") || (current.getToken() == "/")) {
        //current = getNext(); // get rid of if using mulop function
        string opCode = current.getValue();
        mulop();
        factor();
        emitMulop(opCode);
        more_term();
    }
}





void addop(void)
{
    // addop -> + | -

    //string opCode = current.getValue();

    if (current.getToken() == "+") {
        //emitAddop(opCode);
        current = getNext();
    } else if (current.getToken() == "-") {
        //emitAddop(opCode);
        current = getNext();
    }

    
}
void mulop(void)
{
    {
        // mulop -> * | / 

        //string opCode = current.getValue();
        if (current.getToken() == "*") {
            //emitMulop(opCode);
            current = getNext();
        } else if (current.getToken() == "/") {
            //emitMulop(opCode);
            current = getNext();
        }
    }
}

void factor(void)
{
    /* factor -> IDENTIFIER | NUMBER | ( EXPRESSION ) */

    // need to save the value so we can push it onto the stack
    string val;
    if (current.getToken() == "IDENTIFIER") {
        val = current.getValue();
        emitVar(val);
        current = getNext();
    } else if (current.getToken() == "NUMBER") {
        val = current.getValue();
        emitNumber(val);
        current = getNext();
    } else if (current.getToken() == "(") {
        current = getNext();
        expression();
        if (current.getToken() == ")")
            current = getNext();
        else
            parseError(current.getLineNum(), current.getValue());
    } else {
        parseError(current.getLineNum(), current.getValue());
    }

}
void end_pal(void)
{
    if (current.getToken() != ".") {
        cout << current.getToken() << endl;
        parseError(current.getLineNum(), current.getValue());
    }
}

