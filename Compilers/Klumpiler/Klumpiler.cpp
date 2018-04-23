/*
  Compiler for the PAL subset of the KLUMP programming language.
  Code emitting function definitions can be found in KlumpCompiler.h
*/


#include <iostream>
#include <cctype>
#include <cstdlib>
#include "Scanner.h"
#include "KlangError.h"
#include "KlumpCompiler.h"
#include "Tables.h"
#include <string>
#include <stack>
#include <set>
#include <map>

//  add prototypes
void klump_program(Lexeme c);
void global_definitions(void);
void const_definitions(void);
void const_list(void);
void konst(string id); // corresponds to <const> in grammar
void type_definitions(void);
void type_list(void);
void struct_type(string name);
void array_type(string name);
void record_type(void);
void fld_list(void);
void dcl_definitions(void);
void dcl_list(void);
void dcl_type(void);
void atomic_type(void);
void proc_declarations(void);
void signature_list(void);
void proc_signature(void);
void formal_args(void);
void formal_arg_list(void);
void formal_arg(void);
void call_by(void);
void return_type(void);
void actual_args(void);
void actual_arg_list(void);
void actual_arg(void);
void procedure_list(void);
void procedure(void);
void proc_head(void);
void proc_body(void);
void statement_list(void);
void statement(void);
void label(void);
void exec_statement(void);
void read_statement(void);
void write_statement(void);
void assignment_statement(void);
void call_statement(void);
void return_statement(void);
void goto_statement(void);
void empty_statement(void);
void compound_statement(void);
void if_statement(void);
void else_clause(void);
void while_statement(void);
void case_statement(void);
void case_list(void);
void for_statement(void);
void next_statement(void);
void break_statement(void);
void expression(void);
void comparison(void);
void simple_expression(void);
void more_expression(void); // REMOVE THIS
void term(void);
void more_term(void); // REMOVE THIS ???
void factor(void);
void compop(void);
void end_pal(void); // REMOVE THIS
void addop(void);
void mulop(void);
void unary(void);
void lval(void);
void func_ref(void);
void qualifier(void);
// end_klump(void); 
using namespace std;

Lexeme current; // lexeme currently being examined

/* Tables */
set<GSTMember> GST;
set<GLTMember> GLT;
set<GTTMember> GTT;

// Different literals for beginning a <statement>
set<string> beginStatement =
{
    "#", "READ", "READLN", "WRITE", "WRITELN",
    "IDENTIFIER", "CALL", "RETURN", "GOTO", ";",
    "DO", "IF", "CASE", "FOR", "NEXT", "BREAK"
};

int main(void)
{
    // Start the scanner 
    startScanner();
    // Start scanning
    current = getNext();
    // initialize Global Type Table, need this?
    GTTMember intType;
    intType.typeID = "INT";
    intType.size = 4;
    intType.structure = "ATOMIC";
    GTT.insert(intType);
    GTTMember realType;
    realType.typeID = "REAL";
    realType.size = 8;
    realType.structure = "ATOMIC";
    GTT.insert(realType);
    GTTMember strType; // size???
    strType.typeID = "STRING";
    strType.structure = "ATOMIC";
    GTT.insert(strType);
    
    // Start parsing/code emitting
    klump_program(current);

    return 0;
}


// main calls this method
void klump_program(Lexeme c)
{
    current = c;
    // <klump_program> -> <global_definitions> <procedure_list> .
    global_definitions();
    procedure_list();
    for (const GSTMember &member : GST) {
        if (member.isConst)
            cout << member.id << " " << member.type << " " << member.value << endl;
    }
    cout << "types" << endl;
    for (const GTTMember &member : GTT) {
        if (member.structure == "ARRAY")
            cout << member.typeID << " " << member.size << " " << member.structure
                 << " " << member.arrayInfo.range << " " << member.arrayInfo.type << endl;
        else
            cout << member.typeID << " " << member.size << " " << member.structure
                 << endl;
    }
    // write .data and .bss sections
    //emitBss(variables);
    emitData(GST);
    //end_pal();
    // make sure we have "." at the end
    //if (current.getToken() != ".")
    //    parseError(current.getLineNum(), current.getValue());
}
void global_definitions(void)
{
    /* <global_definitions> -> GLOBAL
                               <const_definitions> <type_definitions>
                               <dcl_definitions> <proc_declarations>
                               | e
     */
    if (current.getToken() == "GLOBAL") {
        current = getNext(); // need these after each one?
        const_definitions();
        type_definitions();
        dcl_definitions();
        proc_declarations();
    }
    // otherwise empty
}
void const_definitions(void)
{
    /* <const_definitions> -> CONST <const_list>
                              | e
    */
    if (current.getToken() == "CONST") {
        current = getNext();
        const_list();
    }
}

// how to implement + ????
void const_list(void)
{
    // <const_list> -> { IDENTIFIER : <const> ; }+
        if (current.getToken() == "IDENTIFIER") {
            string konstID = current.getValue();
            current = getNext();
            if (current.getToken() == ":") {
                current = getNext();
                konst(konstID);
                if (current.getToken() == ";") {
                    current = getNext();
                        if (current.getToken() == "IDENTIFIER") {
                            // go again
                            const_list();
                        }
                } else {
                    parseError(current.getLineNum(),current.getValue());
                }
            } else {
                parseError(current.getLineNum(),current.getValue());
            }
        } else {
            parseError(current.getLineNum(),current.getValue());
        }
}
void konst(string id)
{
    // <const> -> NUMBER | DECIMAL | CSTRING

    GSTMember newKonst;
    newKonst.id = id;
    newKonst.isConst = true;
    if (current.getToken() == "NUMBER") {
        newKonst.type = "INT";
        newKonst.value = current.getValue();
        current = getNext();
    } else if (current.getToken() == "DECIMAL") {
        newKonst.type = "REAL";
        newKonst.value = current.getValue();
        current = getNext();
    } else if (current.getToken() == "CSTRING") {
        newKonst.type = "STRING";
        newKonst.value = current.getValue();
        current = getNext();
    } else {
        parseError(current.getLineNum(), current.getValue());
    }
    GST.insert(newKonst);
    
}

void type_definitions()
{
    // <type_definitions> -> TYPE <type_list> | e
    if (current.getToken() == "TYPE") {
        current = getNext();
        type_list();
    }
}

void type_list()
{
    // <type_list> -> { IDENTIFIER : <structure_type> ; }+
        if (current.getToken() == "IDENTIFIER") {
            string typeName = current.getValue();
            current = getNext();
            if (current.getToken() == ":") {
                current = getNext();
                struct_type(typeName);
                if (current.getToken() == ";") {
                    current = getNext();
                        if (current.getToken() == "IDENTIFIER")
                            type_list(); // Do it again
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

void struct_type(string name)
{
    // <struct_type> -> <array_type> | <record_type>

    if (current.getToken() == "ARRAY") {
        current = getNext();
        array_type(name);
    } else if (current.getToken() == "RECORD") {
        current = getNext();
        record_type();
    } else {
        parseError(current.getLineNum(), current.getValue());
    }
}

void array_type(string name)
{
    // <array_type> -> ARRAY [ NUMBER ] OF <dcl_type>

    // already have "ARRAY" so...
    GTTMember array;
    arrInfo info;
    int range = 0;
    string type = "";
    array.typeID = name;
    array.structure = "ARRAY";
    if (current.getToken() == "[") {
        current = getNext();
        if (current.getToken() == "NUMBER") {
            range = stoi(current.getValue());
            current = getNext();
            if (current.getToken() == "]") {
                current = getNext();
                if (current.getToken() == "OF") {
                    current = getNext();
                    type = current.getValue();
                    dcl_type();
                    info.range = range; // success!
                    info.type = type;
                } else {
                    parseError(current.getLineNum(), current.getValue());
                }
            } else {
                parseError(current.getLineNum(), current.getValue());
            }
        } else if (current.getToken() == "IDENTIFIER") { // case where RANGE is a variable
            string rangeStr = current.getValue(); // hold onto variable name
            current = getNext();
            if (current.getToken() == "]") {
                current = getNext();
                if (current.getToken() == "OF") {
                    current = getNext();
                    type = current.getValue();
                    dcl_type();
                    GSTMember temp;
                    temp.id = rangeStr;
                    set<GSTMember>:: iterator iter = GST.find(temp);
                    if (iter != GST.end()) {
                        GSTMember temp = *iter;
                        range = stoi(temp.value);
                        info.range = range;
                        info.type = type;
                    } else
                        semanticError(current.getLineNum(), "");
                } else {
                    parseError(current.getLineNum(), current.getValue());
                }
            } else {
                parseError(current.getLineNum(), current.getValue());
            }
        }
        else {
            parseError(current.getLineNum(), current.getValue());
        }
    } else {
        parseError(current.getLineNum(), current.getValue());
    }
    // everything successful so add to global type table!
    // first determine size
    set<GTTMember>:: iterator it;
    GTTMember tempType;
    tempType.typeID = type;
    it = GTT.find(tempType);
    tempType = *it;
    array.size = tempType.size * range;
    array.arrayInfo = info;
    GTT.insert(array);
}

void record_type(void)
{
    // <record_type> -> RECORD <fld_test> END
    // already have RECORD so...
    fld_list();
    if (current.getToken() == "END") {
        current = getNext();
    } else {
        parseError(current.getLineNum(), current.getValue());
    }
        
}

void fld_list(void)
{
    // { IDENTIFIER : <dcl_type> ; }+
        if (current.getToken() == "IDENTIFIER") {
            current = getNext();
            if (current.getToken() == ":") {
                current = getNext();
                dcl_type();
                if (current.getToken() == ";") {
                    current = getNext();
                        if (current.getToken() == "IDENTIFIER") {
                            fld_list();
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
        /*
        if (current.getToken() == "END") {
            current = getNext();
            if (current.getToken() == ";") {
                current = getNext();
            } else {
                parseError(current.getLineNum(), current.getValue());
            }
        } else {
            parseError(current.getLineNum(), current.getValue());
        }
        */
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
        //parseError(current.getLineNum(), current.getValue());
    }
    // if not, assume no dcl_list and go right to procedure?
    //procedure();
}

void dcl_list(void)
{
  // dcl_list -> { IDENTIFIER : <dcl_type> ; }+
        if (current.getToken() == "IDENTIFIER") {
            //variables.push(current.getValue());
            current = getNext();
            if (current.getToken() == ":") {
                current = getNext();
                dcl_type();
                if (current.getToken() == ";") {
                    current = getNext();
                        if (current.getToken() == "IDENTIFIER") {
                            // play again
                            dcl_list();
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

void dcl_type(void)
{
    // <dcl_type> -> <atomic_type> | IDENTIFIER
    
    if (current.getToken() == "IDENTIFIER")
        current = getNext();
    else
        atomic_type();

}

void atomic_type(void)
{
    // <atomic_type> -> BOOL | INT | REAL | STRING
    if (current.getToken() == "BOOL" || current.getToken() == "INT" ||
        current.getToken() == "REAL" || current.getToken() == "STRING")
        current = getNext();
    else
        parseError(current.getLineNum(), current.getValue());
}

void proc_declarations(void)
{
    // <proc_declarations> -> PROC <signature_list> | e
    if (current.getToken() == "PROC") {

        current = getNext();
        signature_list();
    }
    // otherwise assume no procedure list???
}

void signature_list(void)
{
    // <signature_list> -> <proc_signature> { ; <proc_signature }*

    if (current.getToken() == "IDENTIFIER") {
        current = getNext();
        proc_signature();
        current = getNext();
        if (current.getToken() == ";") {
            // go again 
            current = getNext();
            signature_list();
        }
    }
}

void proc_signature(void)
{
    // <proc_signature> -> IDENTIFIER <formal_args> :  <return_type> ;

    // already have IDENTIFIER so...
    formal_args();
    if (current.getToken() == ":") {
        current = getNext();
        return_type();
        if (current.getToken() != ";")
            parseError(current.getLineNum(), current.getValue());
    }
}

void formal_args(void)
{
    // <formal_args> -> ( <formal_arg_list> ) | e

    if (current.getToken() == "(") {
        current = getNext();
        formal_arg_list();
        if (current.getToken() == ")") {
            current = getNext();
        } else {
            parseError(current.getLineNum(), current.getValue());
        }
    } 
}

void formal_arg_list(void)
{
    // <formal_arg_list> -> <formal_arg> { , <formal_arg> }*

    formal_arg();
    while(current.getToken() == ",") {
        current = getNext();
        formal_arg();
    }
}

void formal_arg(void)
{
    // <formal_arg> -> <call_by> IDENTIFIER : <dcl_type>

    call_by();
    if (current.getToken() == "IDENTIFIER") {
        current = getNext();
        if (current.getToken() == ":") {
            current = getNext();
            dcl_type();
        } else {
            parseError(current.getLineNum(), current.getValue());
        }
    } else {
        parseError(current.getLineNum(), current.getValue());
    }
}

void call_by(void)
{
    // <call_by> -> VAR | e
    if (current.getToken() == "VAR") {
        current = getNext();
    }
}

void return_type(void)
{
    // <return_type> -> <atomic_type> | e
    
    atomic_type();
}

void actual_args(void)
{
    // <actual_args> -> ( <actual_arg_list> ) | e

    if (current.getToken() == "(") {
        current = getNext();
        actual_arg_list();
        if (current.getToken() == ")") {
            current = getNext();
        } else {
            parseError(current.getLineNum(), current.getValue());
        }
    }
    // otherwise assume no actual arguments
}

void actual_arg_list(void)
{
    // <actual_arg_list> -> <actual_arg> { , <actual_arg> }*

    actual_arg();
    while (current.getToken() == ",") {
        current = getNext();
        actual_arg();
    }
}

void actual_arg(void)
{
    // <actual_arg> -> <expression>

    expression();
}

void procedure_list(void)
{
    // <procedure_list> -> { <procedure> }*

    while (current.getToken() == "PROCEDURE") {
        current = getNext();
        procedure();
    }
}

void procedure(void)
{
    // <procedure> -> <proc_head> <proc_body>
    proc_head();
    proc_body();
}

void proc_head(void)
{
    // <proc_head> -> PROCEDURE IDENTIFIER ;

    /* REMEMBER THAT WE ALREADY GOBBLED UP "PROCEUDURE" */
    if (current.getToken() == "IDENTIFIER") {
        current = getNext();
        if (current.getToken() == ";") {
            current = getNext();
        } else {
            parseError(current.getLineNum(), current.getValue());
        }
    } else {
        parseError(current.getLineNum(), current.getValue());
    }
}

void proc_body(void)
{
    // <proc_body> -> <dcl_definitions> BEGIN <statement_list> END
    dcl_definitions();
    if (current.getToken() == "BEGIN") {
        current = getNext();
        statement_list();
        if (current.getToken() == "END") {
            current = getNext();
        } else {
            parseError(current.getLineNum(), current.getValue());
        }
    } else {
        parseError(current.getLineNum(), current.getValue());
    }
}

void statement_list(void)
{
    // <statement_list> -> { <statement> }*

    // check for a literal beginning a statement
    if (beginStatement.find(current.getToken()) != beginStatement.end()) {
        statement();
        statement_list(); // go again
    }
    // otherwise assume empty
}

void statement(void)
{
    // <statement> -> <label> <exec_statement>

    label();
    exec_statement();
}

void label(void)
{
    // <label> -> # NUMBER | e

    if (current.getToken() == "#") {
        current = getNext();
        if (current.getToken() == "NUMBER") {
            current = getNext();
        } else {
            parseError(current.getLineNum(), current.getValue());
        }
    }
}

void exec_statement(void)
{
    /* <exec_statement> -> <read_statement>
       | <write_statement>
       | <assign_statement>
       | <call_statement>
       | <return_statement>
       | <goto_statement>
       | <empty_statement>
       | <compound_statement>
       | <if_statement>
       | <while_statement>
       | <case_statement>
       | <for_statement>
       | <next_statement>
       | <break_statement>
     */
    map<string,int> cases =
    {
        {"READ", 0}, {"READLN", 1}, {"WRITE", 2}, {"WRITELN", 3},
        {"IDENTIFIER", 4}, {"CALL", 5}, {"RETURN", 6}, {"GOTO", 7},
        {";", 8}, {"DO", 9}, {"IF", 10}, {"WHILE", 11}, {"CASE", 12},
        {"FOR", 13}, {"NEXT", 14}, {"BREAK", 15}
    };
    // note: some cases do not gobble current lexeme since
    // there is an option in the applicable statement function
    switch (cases[current.getToken()]) {
    case 0:
        read_statement();
        break;
    case 1:
        read_statement();
        break;
    case 2:
        write_statement();
        break;
    case 3:
        write_statement();
        break;
    case 4:
        assignment_statement();
        break;
    case 5:
        current = getNext();
        call_statement();
        break;
    case 6:
        current = getNext();
        return_statement();
        break;
    case 7:
        current = getNext();
        goto_statement();
        break;
    case 8:
        current = getNext();
        empty_statement();
        break;
    case 9:
        current = getNext();
        compound_statement();
        break;
    case 10:
        current = getNext();
        if_statement();
        break;
    case 11:
        current = getNext();
        while_statement();
        break;
    case 12:
        current = getNext();
        case_statement();
        break;
    case 13:
        current = getNext();
        for_statement();
        break;
    case 14:
        current = getNext();
        next_statement();
        break;
    case 15:
        current = getNext();
        break_statement();
        break;
    default:
        parseError(current.getLineNum(), current.getValue());
        break;
    }
}

void read_statement(void)
{
    /* <read_statement> -> READ <actual_args> ;
       | READLN <actual_args> ;
     */

    if (current.getToken() == "READ") {
        current = getNext();
        actual_args();
        if (current.getToken() == ";") {
            current = getNext();
        } else {
            parseError(current.getLineNum(), current.getValue());
        }
    } else { // safe to use else here?
        current = getNext();
        actual_args();
        if (current.getToken() == ";") {
            current = getNext();
        } else {
            parseError(current.getLineNum(), current.getValue());
        }
    }
}

void write_statement(void)
{
    /* <write_statement> -> WRITE <actual_args> ;
       | WRITELN <actual_args> ;
     */

    if (current.getToken() == "WRITE") {
        current = getNext();
        actual_args();
        if (current.getToken() == ";") {
            current = getNext();
        } else {
            parseError(current.getLineNum(), current.getValue());
        }
    } else { // safe to use else here?
        current = getNext();
        actual_args();
        if (current.getToken() == ";") {
            current = getNext();
        } else {
            parseError(current.getLineNum(), current.getValue());
        }
    }
}

void assignment_statement(void)
{
    // <assignment_statement> -> <lval> := <expression> ;

    lval(); // remember "IDENTIFIER"  gobbled!
    if (current.getToken() == ":=") {
        current = getNext();
        expression();
        if (current.getToken() == ";") {
            current = getNext();
        } else {
            parseError(current.getLineNum(), current.getValue());
        }
    } else {
        parseError(current.getLineNum(), current.getValue());
    }
}

void call_statement(void)
{
    // <call_statement> -> CALL IDENTIFIER <actual_args> ;

    // already have CALL so...
    if (current.getToken() == "IDENTIFIER") {
        current = getNext();
        actual_args();
        if (current.getToken() == ";") {
            current = getNext();
        } else {
            parseError(current.getLineNum(), current.getValue());
        }
    } else {
        parseError(current.getLineNum(), current.getValue());
    }
}

void return_statement(void)
{
    // <return_statement> -> RETURN [ <expression> ] ;

    // already have RETURN so...
    //if (current.getToken() == "[") {
    //    current = getNext();
        expression();
        //if (current.getToken() == "]") {
        //current = getNext();
            if (current.getToken() == ";") {
                current = getNext();
            } else {
                parseError(current.getLineNum(), current.getValue());
            }
            //} else {
            //parseError(current.getLineNum(), current.getValue());
            //}
        //} else {
        //parseError(current.getLineNum(), current.getValue());
        //}
}

void goto_statement(void)
{
    // <goto_statement> -> GOTO <label> ;

    // already have GOTO so...
    label();
    if (current.getToken() == ";")
        current = getNext();
    else
        parseError(current.getLineNum(), current.getValue());
}

void empty_statement(void)
{
    // <empty_statement> -> ;

    // already gobbled ; so...
    // don't do anything!
}

void compound_statement(void)
{
    // <compound_statement> -> DO ; <statement_list> END ;

    // already gobbled DO so...
    if (current.getToken() == ";") {
        current = getNext();
        statement_list();
        if (current.getToken() == "END") {
            current = getNext();
            if (current.getToken() == ";") {
                current = getNext();
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

void if_statement(void)
{
    /* <if_statement> -> IF ( <comparison> )
       THEN <statement>
       <else_clause>
     */

    // already gobbled IF so...
    if (current.getToken() == "(") {
        current = getNext();
        comparison();
        if (current.getToken() == ")") {
            current = getNext();
            if (current.getToken() == "THEN") {
                current = getNext();
                statement();
                else_clause();
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

void else_clause(void)
{
    // <else_clause> -> ELSE <statement> | e

    if (current.getToken() == "ELSE") {
        current = getNext();
        statement();
    }
}

void while_statement(void)
{
    // <while_statement> -> WHILE ( <comparison> ) <statement>

    // already gobbled WHILE so...
    if (current.getToken() == "(") {
        current = getNext();
        comparison();
        if (current.getToken() == ")") {
            current = getNext();
            statement();
        } else {
            parseError(current.getLineNum(), current.getValue());
        }
    } else {
        parseError(current.getLineNum(), current.getValue());
    }
}

void case_statement(void)
{
    // <case_statement> -> CASE ( <expression> ) <case_list>

    // already gobbled CASE so...
    if (current.getToken() == "(") {
        current = getNext();
        expression();
        if (current.getToken() == ")") {
            current = getNext();
            case_list();
        } else {
            parseError(current.getLineNum(), current.getValue());
        }
    } else {
        parseError(current.getLineNum(), current.getValue());
    }
}

void case_list(void)
{
    /* <case_list> -> { <unary> NUMBER : <statement> }*
       DEFAULT : <statement>
     */

    if ((current.getToken() == "+") ||
        (current.getToken() == "-") ||
        (current.getToken() == "NUMBER")) {
        unary();
        if (current.getToken() == "NUMBER") {
            current = getNext();
            if (current.getToken() == ":") {
                current = getNext();
                statement();
                case_list();
            } else {
                parseError(current.getLineNum(), current.getValue());
            }
        } else {
            parseError(current.getLineNum(), current.getValue());
        }
    }

    // Then obligatory DEFAULT
    if (current.getToken() == "DEFAULT") {
        current = getNext();
        if (current.getToken() == ":") {
            current = getNext();
            statement();
        } else {
            parseError(current.getLineNum(), current.getValue());
        }
    } else {
        parseError(current.getLineNum(), current.getValue());
    }
}

void for_statement(void)
{
    /* <for_statement> -> FOR IDENTIFIER := <expression>
       { TO | DOWNTO } <expression> <statement>
     */
    // already got FOR so...
    if (current.getToken() == "IDENTIFIER") {
        current = getNext();
        if (current.getToken() == ":=") {
            current = getNext();
            expression();
            // next two cases separate for compiling
            if (current.getToken() == "TO") {
                current = getNext();
                expression();
                statement();
            } else if (current.getToken() == "DOWNTO") {
                current = getNext();
                expression();
                statement();
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

void next_statement(void)
{
    // <next_statement> -> NEXT ;

    // already gobbled NEXT so...
    if (current.getToken() == ";") {
        current = getNext();
    } else {
        parseError(current.getLineNum(), current.getValue());
    }
}

void break_statement(void)
{
    // <break_statement> -> BREAK ;

    // already gobbled BREAK so...
    if (current.getToken() == ";") {
        current = getNext();
    } else {
        parseError(current.getLineNum(), current.getValue());
    }
}

void expression(void)
{
    // <expression> -> <comparison>

    comparison();
}

void comparison(void)
{
    // <comparison> -> <simple_expression> { <compop> <simple_expression> }*
    simple_expression();
    // maybe change to while loop?
    if ((current.getToken() == "=") ||
        (current.getToken() == "<>") ||
        (current.getToken() == ">") ||
        (current.getToken() == "<") ||
        (current.getToken() == ">=") ||
        (current.getToken() == "<=")) {
        compop(); // don't gobble!
        comparison();
    }
}

void simple_expression(void)
{
    // <simple_expression> -> <unary> <term> { <addop> <term> }*

    unary();
    term();
    // seems like it could give an issue later...
    while ((current.getToken() == "+") || (current.getToken() == "-") ||
           (current.getToken() == "OR")) {
        addop();
        term();
    }
}

void term(void)
{
    // <term> -> <factor> { <mulop> <factor> }*

    factor();
    while ((current.getToken() == "*") || (current.getToken() == "/") ||
           (current.getToken() == "%") || (current.getToken() == "AND")) {
        mulop();
        factor();
    }
}

void factor(void)
{
    /* <factor> -> <const> | <func_ref> | <lval> | ( <expression> ) | NOT <factor> */

    if ((current.getToken() == "NUMBER") || (current.getToken() == "DECIMAL") ||
        (current.getToken() == "CSTRING")) {
        //konst();
        current = getNext();
    } else if (current.getToken() == "IDENTIFIER") {
        // <func_ref> | <lval>
        current = getNext();
        if (current.getToken() == "(") {
            func_ref();
        } else if ((current.getToken() == "[") || (current.getToken() == ".")) {
            qualifier();
        } // \epsilon in both cases
    } else if (current.getToken() == "(") {
        current = getNext();
        expression();
        if (current.getToken() == ")") {
            current = getNext();
        } else {
            parseError(current.getLineNum(), current.getValue());
        }
    } else if (current.getToken() == "NOT") {
        current = getNext();
        factor();
    } else {
        parseError(current.getLineNum(), current.getValue());
    }
}

void compop(void)
{
    //<compop> -> = | <> | > | < | >= | <=

    if ((current.getToken() == "=") ||
        (current.getToken() == "<>") ||
        (current.getToken() == ">") ||
        (current.getToken() == "<") ||
        (current.getToken() == ">=") ||
        (current.getToken() == "<=")) {
        current = getNext();
    } else {
        parseError(current.getLineNum(), current.getValue());
    }
}

void addop(void)
{
    // <addop> -> + | - | OR

    if ((current.getToken() == "+") || (current.getToken() == "-") ||
        (current.getToken() == "OR")) {
        current = getNext();
    } else {
        parseError(current.getLineNum(), current.getValue());
    }
}

void mulop(void)
{
    // <mulop> -> * | / | % | AND

    if ((current.getToken() == "*") || (current.getToken() == "/") ||
        (current.getToken() == "%") || (current.getToken() == "AND")) {
        current = getNext();
    } else {
        parseError(current.getLineNum(), current.getValue());
    }
}

void unary(void)
{
    // <unary> -> + | - | e

    if ((current.getToken() == "+") || (current.getToken() == "-")) {
        current = getNext();
    }
}

void lval(void)
{
    // <lval> -> IDENTIFIER <qualifier>

    if (current.getToken() == "IDENTIFIER") {
        current = getNext();
        qualifier();
    } else {
        parseError(current.getLineNum(), current.getValue());
    }
}

void func_ref(void) {
    // <func_ref> -> IDENTIFIER <actual_args>

    // already gobbled IDENTIFIER so...
    actual_args();
}


void qualifier(void)
{
    /* <qualifier> -> [ <expression> ] <qualifier>
       | . IDENTIFIER <qualifier>
       | e
     */

    if (current.getToken() == "[") {
        current = getNext();
        expression();
        if (current.getToken() == "]") {
            current = getNext();
            qualifier();
        } else {
            parseError(current.getLineNum(), current.getValue());
        }
    } else if (current.getToken() == ".") {
        current = getNext();
        if (current.getToken() == "IDENTIFIER") {
            current = getNext();
            qualifier();
        } else {
            parseError(current.getLineNum(), current.getValue());
        }
    }
}
