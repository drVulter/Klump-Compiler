/*
  Parser for the PAL subset of the KLUMP programming language
*/

// do I need these?
#include <iostream>
#include <cctype>
#include <cstdlib>
#include "Scanner.h"
#include "KlangError.h"
#include <string>

//  add prototypes
void pal_program(void);
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
void end(void);

Lexeme current;
// main calls this method
void pal_program(void)
{
    // pal_program -> dcl_definitions procedure
    dcl_definitions();
    procedure();

    // make sure we have "." at the end
    if (current.getToken() != ".")
        parseError(current.getLineNum(), current.getValue());
}

void dcl_definitions(void)
{
    // dcl_definitions -> DCL dcl_list | e
    // get the first lexeme
    current = getNext(); // from Scanner.cpp
    if (current.getToken() == "DCL") {
        current = getNext();
        dcl_list();
    }
    // if not, assume no dcl_list and go right to procedure?
    procedure();
}

void dcl_list(void)
{
  // dcl_list -> IDENTIFIER : INT ; dcl_list | e
    if (current.getToken() == "IDENTIFIER") {
        current = getNext();
        if (current.getToken() == ":") {
            current = getNext();
            if (current.getToken() == "INT") {
                current = getNext();
                if (current.getToken() == ";") {
                    current = getNext();
                    dcl_list();
                } else {
                    parseError(current.getLineNum(), current.getValue());
                }
            } else {
                parseError(current.getLineNum(), current.getValue());
            }
        } else {
            parseError(current.getLineNum(), current.getValue());
        }
    } else {
        parseError(current.getLineNum(), current.getValue());
    }
    
}

void procedure(void)
{
    // procedure -> BEGIN statement_list END

    // first check for "BEGIN"
    if (current.getToken() == "BEGIN") {
        current = getNext();
        statement_list();
    } else {
        parseError(current.getLineNum(), current.getValue());
    }

    // if that all passes, check for the "END"
    if (current.getToken() == "END") {
        current = getNext();
        end();
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
        parseError(current.getLineNum(), current.getValue());
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
        current = getNext();
        assignment_statement();
    } else {
        parseError(current.getLineNum(), current.getValue());
    }
}

void write_statement(void)
{
    if (current.getToken() == "(") {
        current = getNext();
        if (current.getToken() == "IDENTIFIER") {
            current = getNext();
            if (current.getToken() == ")") {
                current = getNext();
                if (current.getToken() == ";") {
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
    /* assignment_statement -> IDENTIFIER := espression ; */

    // have IDENTIFIER from before so...
    if (current.getToken() == ":=") {
        current = getNext();
        expression();
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
        current  = getNext(); // get rid of this if using addop()
        //addop();
        term();
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
        current = getNext(); // get rid of if using mulop function
        // mulop();
        factor();
        more_term();
    }
}



/*

void addop(void)
{
    // addop -> + | - 

    if (current.getToken() == "+")
        current = getNext();
    else if (current.getToken() == "-")
        current.getNext();
}
void mulop(void)
{
    {
        // mulop -> * | / 

        if (current.getToken() == "*")
            current = getNext();
        else if (current.getToken() == "/")
            current.getNext();
    }
}
*/
void factor(void)
{
    /* factor -> IDENTIFIER | NUMBER | ( EXPRESSION ) */

    if (current.getToken() == "IDENTIFIER") {
        current = getNext();
    } else if (current.getToken() == "NUMBER") {
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
void end(void)
{
    if (current.getToken() != ".")
        parseError(current.getLineNum(), current.getValue());
}


