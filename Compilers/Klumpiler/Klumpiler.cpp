/*
  Compiler for the KLUMP programming language.
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
#include <boost/algorithm/string.hpp>

/*  HELPER PROTOTYPES */
void initializeTables(void);
string typeCheck(string a, string b);
int getLocalStorage();

/* PARSER PROTOTYPES */
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
void dcl_definitions(bool isGlobal);
void dcl_list(bool isGlobal);
string dcl_type(void);
string atomic_type(void);
void proc_declarations(void);
void signature_list(void);
string proc_signature(GPTMember &proc);
int formal_args(GPTMember &proc);
int formal_arg_list(GPTMember &proc);
parameter formal_arg(int offset);
void call_by(void);
string return_type(void);
vector<string> actual_args(string caller);
vector<string> actual_arg_list(string caller);
string actual_arg(void);
void procedure_list(void);
void procedure(void);
GPTMember proc_head(void);
void proc_body(GPTMember proc);
void statement_list(void);
void statement(void);
void label(bool fromGoto);
void exec_statement(void);
void read_statement(bool isReadln);
void write_statement(void);
void assignment_statement(void);
void call_statement(void);
void return_statement(void);
void goto_statement(void);
void empty_statement(void);
void compound_statement(void);
void if_statement(void);
void else_clause(string label, string done);
void while_statement(void);
void case_statement(void);
void case_list(void);
void for_statement(void);
void next_statement(void);
void break_statement(void);
string expression(void);
string comparison(void);
string simple_expression(void);
string more_expression(void); // REMOVE THIS
string term(void);
string more_term(void); // REMOVE THIS ???
string factor(void);
void compop(void);
void end_pal(void); // REMOVE THIS
void addop(void);
void mulop(void);
bool unary(void);
string lval(void);
string func_ref(GPTMember proc);
void qualifier(void);
// end_klump(void);
using namespace std;

Lexeme current; // lexeme currently being examined

/* Tables */
set<GSTMember> GST; // Global symbol table
set<GLTMember> GLT; // Global literal table
set<GTTMember> GTT; // Global type table
set<GPTMember> GPT; // Global procedure table
set<LSTMember> LST; // Local symbol table
set<LLTMember> LLT; // Local label table

// Different literals for beginning a <statement>
set<string> beginStatement =
{
    "#", "READ", "READLN", "WRITE", "WRITELN",
    "IDENTIFIER", "CALL", "RETURN", "GOTO", ";",
    "DO", "IF", "WHILE", "CASE", "FOR", "NEXT", "BREAK"
};

map<string,string> types =
{
    {"NUMBER", "INT"}, {"DECIMAL", "REAL"}, {"CSTRING", "STRING"}
};

// predefined ATOMIC TYPES
set<string> atomicTypes =
{
    "INT", "REAL", "STRING", "BOOL"
};

stack<string> startLoopStack; // keep track of where you are in nested loops!
stack<string> endLoopStack;

// labels for returning from call statements
//stack<string> callLabels;

// procedure that we are currently in and the type of that procedure
string globalCurrentExit;
string globalCurrentType;

int main(void)
{
    // Start the scanner
    startScanner();
    // Start scanning
    current = getNext();
    initializeTables();
    // Start parsing/code emitting
    klump_program(current);

    return 0;
}

/* HELPER FUNCTIONS */
void initializeTables(void)
{
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
    strType.size = 4;
    GTT.insert(strType);
    GSTMember tempInt; // used for type conversion
    tempInt.id = "_TEMP_INT_";
    tempInt.type = "INT";
    tempInt.isConst = false;
    GST.insert(tempInt);
    GPTMember main;
    main.id = "MAIN";
    main.parameters = {}; // no parameters
    main.returnType = "VOID"; // returns nothing
    main.label = "_main";
    GPT.insert(main);
}

string typeCheck(string a, string b)
{
    string errorMsg = "Not an atomic type!";
    // first make sure atomic types
    set<string>:: iterator it = atomicTypes.find(a);
    if (it != atomicTypes.end()) {
        // check b
        it = atomicTypes.find(b);
        if (it != atomicTypes.end()) {
            if (a == b) {
                return a; // same type!
            } else if (a > b) {
                // need promotion BOOL -> INT -> REAL
                if (promote(b, a)) {
                    return a;
                } else {
                    semanticError(current.getLineNum(), "Cannot promote " + b + "->" + a + "!");
                }
            } else {
                // need demotion
                if (demote(a, b)) {
                    return b;
                } else {
                    semanticError(current.getLineNum(), "Cannot promote " + a + "->" + b + "!");
                }
            }
        } else {
            semanticError(current.getLineNum(), errorMsg);
        }
    } else {
        semanticError(current.getLineNum(), errorMsg);
    }
}

int getLocalStorage(void)
{
    // Determine amount of local storage necessary
    int storage = 0;
    GTTMember tempType;
    for (LSTMember var : LST) {
        tempType.typeID = var.type;
        set<GTTMember>:: iterator it = GTT.find(tempType);
        if (it != GTT.end()) {
            // found!
            storage += (*it).size;
        }
    }
    return storage;
}

/* PARSER FUNCTIONS */
// main calls this method
void klump_program(Lexeme c)
{
    current = c;
    // <klump_program> -> <global_definitions> <procedure_list> .
    front(); // emit front code
    global_definitions();
    procedure_list();
    //back(); // wrap up main

    /*
    cout << "\ntypes" << endl;
    for (const GTTMember &member : GTT) {
        if (member.structure == "ARRAY")
            cout << member.typeID << " " << member.size << " " << member.structure
                 << " " << member.arrayInfo.range << " " << member.arrayInfo.type << endl;
        else
            cout << member.typeID << " " << member.size << " " << member.structure
                 << endl;
    }
    cout << "\nLocal variables" << endl;
    for (const LSTMember &member : LST) {
        cout << member.id << " " << member.type << " " << member.offset << " " << member.callbyVAR << endl;
    }

    // dump literal table
    cout << "Dumping literals" << endl;
    for (const GLTMember &member : GLT) {
        cout << member.type << " " << member.value << " " << member.label << endl;
    }
    */
    // write .data and .bss sections
    emitBss(GST, GTT); // need GTT for sizes of variables
    emitData(GST, GLT); // emit global constants and literals
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
        dcl_definitions(true);
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
        newKonst.value = current.getValue() + ", 0";
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
                    //type = current.getValue();
                    type = dcl_type();
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
                    type = dcl_type();
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
    GTT.insert(array); // add it to type table
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
                string type = dcl_type();
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
void dcl_definitions(bool isGlobal)
{
    // dcl_definitions -> DCL dcl_list | e
    // get the first lexeme
    //current = getNext(); // from Scanner.cpp
    if (current.getToken() == "DCL") {
        current = getNext();
        dcl_list(isGlobal);
    } else {
        //parseError(current.getLineNum(), current.getValue());
    }
    // if not, assume no dcl_list and go right to procedure?
    //procedure();
}

void dcl_list(bool isGlobal)
{
  // dcl_list -> { IDENTIFIER : <dcl_type> ; }+

    int offset = 0; // to be used for local variables
    while (current.getToken() == "IDENTIFIER") {
        string varName = current.getValue(); // save id
        current = getNext();
        if (current.getToken() == ":") {
            current = getNext();
            string varType = dcl_type();
            if (varType == "CSTRING")
                varType = "STRING";
            if (current.getToken() == ";") {
                current = getNext();
                // success, so add to table!
                if (isGlobal) {
                    GSTMember var;
                    var.id = varName;
                    var.type = varType;
                    var.isConst = false;
                    GST.insert(var);
                } else {
                    LSTMember var;
                    var.id = varName;
                    var.type = varType;
                    // determine size for offset
                    GTTMember tempType;
                    set<GTTMember>:: iterator it;
                    tempType.typeID = varType;
                    it = GTT.find(tempType);
                    tempType = *it;
                    offset += tempType.size;
                    var.offset = to_string(offset);
                    var.internalID = "ebp - " + var.offset;
                    var.callbyVAR = true; // default
                    LST.insert(var);
                }
            } else {
                parseError(current.getLineNum(), current.getValue());
            }
        } else {
            parseError(current.getLineNum(), current.getValue());
        }
    }
}

string dcl_type(void)
{
    // <dcl_type> -> <atomic_type> | IDENTIFIER
    string type;
    if (current.getToken() == "IDENTIFIER") {
        type = current.getValue();
        current = getNext();
    } else
        type = atomic_type();
    return type;

}

string atomic_type(void)
{
    // <atomic_type> -> BOOL | INT | REAL | STRING
    string type;
    set<string>:: iterator it = atomicTypes.find(current.getToken()); // check
    if (it != atomicTypes.end()) {
        // found so okay
        type = (*it);
        current = getNext();
    } else {
        parseError(current.getLineNum(), current.getValue());
    }
    return type;
    /*
    if (current.getToken() == "BOOL" || current.getToken() == "INT" ||
        current.getToken() == "REAL" || current.getToken() == "STRING")
        current = getNext();
    else
        parseError(current.getLineNum(), current.getValue());
    */
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
        string procName = current.getValue(); // get name of proc
        GPTMember newProc; newProc.id = procName;
        if (newProc.id == "MAIN") {
            newProc.label = "_main";
        } else {
            newProc.label = "_ENTER_" + newProc.id;
            newProc.exit = "_EXIT_" + newProc.id;
        }
        newProc.exit = "_EXIT_" + newProc.id;
        current = getNext();
        string type = proc_signature(newProc);
        newProc.returnType = type;
        GPT.insert(newProc);
        if (current.getToken() == ";") {
            // go again
            current = getNext();
            signature_list();
        }
    }
}

string proc_signature(GPTMember &proc)
{
    // <proc_signature> -> IDENTIFIER <formal_args> :  <return_type> ;
    string type;
    // already have IDENTIFIER so...
    int size = formal_args(proc);
    if (current.getToken() == ":") {
        current = getNext();
        type = return_type();
        if (current.getToken() != ";")
            parseError(current.getLineNum(), current.getValue());
    }
    return type;
}

int formal_args(GPTMember &proc)
{
    // <formal_args> -> ( <formal_arg_list> ) | e
    int size = 0;
    if (current.getToken() == "(") {
        current = getNext();
        size = formal_arg_list(proc);
        if (current.getToken() == ")") {
            current = getNext();
            // have total size, now assign offsets
            // total - stoi(offset) + 4?
            for (int i = 0; i < proc.parameters.size(); i++) {
                int bytes;
                if (proc.parameters.at(i).type == "INT") {
                    bytes = 4;
                }
                //cout << "Formal arg " << i << " " << proc.parameters.at(i).offset << endl;
                int pos = size - stoi(proc.parameters.at(i).offset) + 4 + 4;
                proc.parameters.at(i).intLabel = "ebp + " + to_string(pos);
                //cout << "POS " << pos << "intlabel " << proc.parameters.at(i).intLabel << endl;
            }
            return size;
        } else {
            parseError(current.getLineNum(), current.getValue());
        }
    }
}

int formal_arg_list(GPTMember &proc)
{
    // <formal_arg_list> -> <formal_arg> { , <formal_arg> }*
    int offset = 0;
    parameter newParam = formal_arg(offset);
    if (newParam.type == "INT") {
        offset+= 4;
    } else if (newParam.type == "REAL") {
        offset += 8;
    }
    proc.parameters.push_back(newParam);
    while(current.getToken() == ",") {
        current = getNext();
        newParam = formal_arg(offset);
        //offset += stoi(newParam.offset);
        if (newParam.type == "INT") {
            offset+= 4;
        } else if (newParam.type == "REAL") {
            offset += 8;
        }
        proc.parameters.push_back(newParam);
    }
    return offset;
}

parameter formal_arg(int offset)
{
    // <formal_arg> -> <call_by> IDENTIFIER : <dcl_type>

    call_by();
    if (current.getToken() == "IDENTIFIER") {
        string id = current.getValue();
        current = getNext();
        if (current.getToken() == ":") {
            current = getNext();
            string type = current.getValue();
            dcl_type(); // make sure type is ok
            if ((type == "INT") || (type == "STRING"))
                offset += 4;
            else
                offset += 8;
            parameter arg;
            arg.id = id;
            arg.type = type;
            arg.offset = to_string(offset);
            arg.callbyVAR = false; // assume false
            return arg;
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

string return_type(void)
{
    // <return_type> -> <atomic_type> | e

    return atomic_type();
}

vector<string> actual_args(string caller)
{
    // <actual_args> -> ( <actual_arg_list> ) | e

    vector<string> argTypes;
    if (current.getToken() == "(") {
        current = getNext();
        argTypes = actual_arg_list(caller);
        if (current.getToken() == ")") {
            current = getNext();
        } else {
            parseError(current.getLineNum(), current.getValue());
        }
    }
    return argTypes;
    // otherwise assume no actual arguments
}

vector<string> actual_arg_list(string caller)
{
    // <actual_arg_list> -> <actual_arg> { , <actual_arg> }*
    vector<string> args; // will hold types of the arguments, args themleves already on x8086 STACK
    string type;
    if ((caller == "WRITE")) {
        modStack(-4);
        type = expression();
        emitWrite(type);
        while (current.getToken() == ",") {
            current = getNext();
            modStack(-4);
            type = expression();
            emitWrite(type);
        }
    } else if (caller == "READ") {
        /*
        modStack(-4);
        type = expression();
        emitRead(type);
        while (current.getToken() == ",") {
            current = getNext();
            modStack(-4);
            type = expression();
            emitRead(type);
            //cout << "TEST" << current.getValue() << endl;
            } */
    } else {
        args.push_back(actual_arg());
        while (current.getToken() == ",") {
            current = getNext();
            args.push_back(actual_arg());

        }
    }
    return args;
}

string actual_arg(void)
{
    // <actual_arg> -> <expression>
    string type = expression();
    if (type == "REAL") {
        comment("Real arg, needs to go on normal stack");
        emitLine("", "fstp qword", "[_TEMP_REAL_]", "");
        emitLine("", "push dword", "[_TEMP_REAL_+4]", "");
        emitLine("", "push dword", "[_TEMP_REAL_]", "");
    }
    return type;
}

void procedure_list(void)
{
    // <procedure_list> -> { <procedure> }*
    while (current.getToken() == "PROCEDURE") {
        current = getNext();
        //cout << "trigger" << endl;
        procedure();
    }
}

void procedure(void)
{
    // <procedure> -> <proc_head> <proc_body>
    GPTMember proc = proc_head();
    // update global current proc
    proc_body(proc);
}

GPTMember proc_head(void)
{
    // <proc_head> -> PROCEDURE IDENTIFIER ;

    /* REMEMBER THAT WE ALREADY GOBBLED UP "PROCEUDURE" */
    if (current.getToken() == "IDENTIFIER") {
        // check for this id in GLOBAL PROC TABLE
        GPTMember currentProc; currentProc.id = current.getValue();
        set<GPTMember>:: iterator it = GPT.find(currentProc);
        if (it == GPT.end()) {
            // not in table!
            semanticError(current.getLineNum(), "Procedure " + current.getValue() +
                          " not defined!");
        }
        current = getNext();
        if (current.getToken() == ";") {
            current = getNext();
            globalCurrentExit = (*it).exit;
            globalCurrentType = (*it).returnType;
            return (*it);
        } else {
            parseError(current.getLineNum(), current.getValue());
        }
    } else {
        parseError(current.getLineNum(), current.getValue());
    }
}

void proc_body(GPTMember proc)
{
    // <proc_body> -> <dcl_definitions> BEGIN <statement_list> END
    // first clear out local tables
    LST.clear();
    LLT.clear();
    // add FORMAL args to LST
    /*
    stack<parameter> params;
    for (const parameter &p : proc.parameters) {
        params.push(p);
    }
    while (!params.empty()) {
        LSTMember arg; params.top().id = params.top().id;
        arg.offset = params.top().offset;
        arg.internalID = "ebp + " + to_string(stoi(params.top().offset) + 4);
        arg.type = params.top().type;
        LST.insert(arg);
        params.pop();
    }
    */
    
    for (const parameter &p : proc.parameters) {
        LSTMember arg; arg.id = p.id;
        //cout << p.intLabel << endl;
        arg.offset = p.offset;
        arg.internalID = p.intLabel;
        //arg.internalID = "ebp + " + to_string(stoi(p.offset) + 4);
        arg.type = p.type;
        LST.insert(arg);
    }
    for (const LSTMember &mem : LST) {
        //cout << mem.internalID << "asdf" << endl;
    }
    // then add local vars
    dcl_definitions(false); // not global variables
    proc.storage = getLocalStorage(); // figure out how much local storage necessary
    //cout << "TESTING" << proc.storage << endl;
    if (current.getToken() == "BEGIN") {
        current = getNext();
        //cout << "TESTING " << proc.id << proc.label << endl;
        emitProcHead(proc);
        statement_list();
        if (current.getToken() == "END") {
            /* check that labels are okay! */
            for (const LLTMember &member : LLT) {
                if (member.referenced && !(member.defined)) {
                    semanticError(current.getLineNum(), "Label " + member.numLabel + " not defined!");
                }
            }
            emitProcEnd(proc);
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

    label(false); // false because label is not from a goto
    exec_statement();
}

void label(bool fromGoto)
{
    // <label> -> # NUMBER | e

    if (current.getToken() == "#") {
        current = getNext();
        if (current.getToken() == "NUMBER") {
            string number = current.getValue();
            current = getNext();
            // check local label table for a matching label
            LLTMember temp; temp.numLabel = number;
            set<LLTMember>:: iterator it = LLT.find(temp);
            if (it != LLT.end()) {
                // found!
                // check if this is for a goto statement
                LLTMember temp;
                temp.numLabel = (*it).numLabel;
                temp.intLabel = (*it).intLabel;
                if (fromGoto) {
                    emitGoto((*it).intLabel);
                    temp.referenced = true;
                } else {
                    temp.defined = true;
                    emitLabel(*it); // emit the found label
                }
                LLT.erase(it);
                LLT.insert(temp);
            } else {
                // not found, so insert then emit
                // first check if for goto
                // do we need to perform error handling if label never defined? possible with one-pass compiler?
                string label = makeLabel(); // make a new internal label, defined in KlumpCompiler.h
                temp.intLabel = label; // assign an internal label
                if (fromGoto) {
                    temp.referenced = true;
                //    semanticError(current.getLineNum(), "Label " + number + " not defined!");
                    emitGoto(temp.intLabel);
                } else {
                    temp.defined = true;
                    emitLabel(temp); // actually emit the label
                }
                LLT.insert(temp); // add the new label, numeric label already defined
            }
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
        read_statement(false);
        break;
    case 1:
        read_statement(true);
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

void read_statement(bool isReadln)
{
    /* <read_statement> -> READ <actual_args> ;
       | READLN <actual_args> ;
     */
    if ((current.getToken() == "READ") || (current.getToken() == "READLN")) {
        current = getNext();
        if (current.getToken() == "(") {
            current = getNext();
            while (current.getToken() == "IDENTIFIER") {
                string name = current.getValue();
                // lookup name in LST, then GST
                LSTMember tempLST; tempLST.id = name;
                set<LSTMember>:: iterator it = LST.find(tempLST);
                if (it != LST.end()) { // found
                    emitRead((*it).internalID, (*it).type, true);
                } else {
                    // check GST
                    GSTMember tempGST; tempGST.id = name;
                    set<GSTMember>:: iterator gIter = GST.find(tempGST);
                    if (gIter != GST.end()) {
                        if ((*gIter).isConst) {
                            semanticError(current.getLineNum(), "Cannot overwrite a constant!");
                        }
                        emitRead(name, (*gIter).type, false);
                    }
                }
                current = getNext();
                if (current.getToken() == ",") {
                    current = getNext();
                } else if (current.getToken() == ")") {
                    ; // nothing
                } else {
                    parseError(current.getLineNum(), current.getValue());
                }
            }
            if (current.getToken() == ")") {
                current = getNext();
                if (current.getToken() == ";") {
                    current = getNext();
                    if (isReadln)
                        emitReadln();
                } else {
                    parseError(current.getLineNum(), current.getValue());
                }
            } else {
                parseError(current.getLineNum(), current.getValue());
            }

        }
    } else { // safe to use else here?
        current = getNext();
        actual_args("READ");
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
    bool isWriteln = false;
    if (current.getToken() == "WRITELN") {
        isWriteln = true;
    }
    current = getNext();
    actual_args("WRITE");
    if (current.getToken() == ";") {
        if (isWriteln)
            emitWriteln();
        current = getNext();
    } else {
        parseError(current.getLineNum(), current.getValue());
    }
}

void assignment_statement(void)
{
    // <assignment_statement> -> <lval> := <expression> ;

    //string nameStr = val(); // Save the name!!
    string name;
    string lType; // type being assigned to
    string id = lval();
    LSTMember tempLST; tempLST.id = id;
    set<LSTMember>:: iterator it = LST.find(tempLST);
    // first check LST
    if (it != LST.end()) {
        // found!
        //name = "[ebp-" + (*it).offset + "]";
        name = "[" + (*it).internalID + "]";
        lType = (*it).type;
    } else {
        // check GST
        GSTMember tempGST; tempGST.id = id;
        set<GSTMember>:: iterator it = GST.find(tempGST);
        if (it != GST.end()) {
            // found!
            if ((*it).isConst) {
                semanticError(current.getLineNum(), "Cannot overwrite a constant!");
            } else {
                name = "[" + (*it).id + "]";
                lType = (*it).type;
            }
        } else {
            // can't find it!
            semanticError(current.getLineNum(), "Cannot find " + name + "!");
        }
    }
    if (current.getToken() == ":=") {
        current = getNext();
        string rType = expression();
        if (current.getToken() == ";") {
            // emit the statement
            if (rType == lType) {
                emitAssignment(name, lType);
            } else if (lType > rType) {
                // promote rType
                if (promote(rType, lType)) {
                    emitAssignment(name, lType);
                } else {
                    semanticError(current.getLineNum(), "cannot promote " + rType + "->" + lType);
                }
            } else {
                // demote rType
                if (demote(rType, lType)) {
                    emitAssignment(name, lType);
                } else {
                    semanticError(current.getLineNum(), "cannot demote " + rType + "->" + lType);
                }
            }
            //string type = typeCheck(rType, lType);
            //emitAssignment(name, type);
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
        // find the right proc
        GPTMember temp; temp.id = current.getValue();
        set<GPTMember>:: iterator it = GPT.find(temp);
        if (it == GPT.end()) {
            // not found!
            semanticError(current.getLineNum(), "Procedure " + current.getValue() + " not defined!");
        }
        current = getNext();
        vector<string> argTypes = actual_args("PROC");
        // check arg sizes
        if (argTypes.size() != (*it).parameters.size()) {
            semanticError(current.getLineNum(), "Expected " + to_string((*it).parameters.size()) + " argument(s), received "
                          + to_string(argTypes.size()));
        }
        if (current.getToken() == ";") {
            //emitGoto((*it).label);
            emitCall((*it));

            //callLabels.push((*it).exit); 
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
        string type = expression();
        //if (current.getToken() == "]") {
        //current = getNext();
        //string returnLabel = callLabels.top();
        //callLabels.pop();
            if (current.getToken() == ";") {
                //cout << "TEST" << globalCurrentProc.id << globalCurrentProc.exit << endl;
                emitReturn(type,globalCurrentType, globalCurrentExit, current.getLineNum());
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
    label(true);
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
    emitEmptyStatement();
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
        string checkLbl = makeLabel();
        string doneLbl = makeLabel();
        string thenLbl = makeLabel();
        string elseLbl = makeLabel();
        current = getNext();
        string type = comparison();
        if (current.getToken() == ")") {
            emitCheck(thenLbl, elseLbl);
            current = getNext();
            if (current.getToken() == "THEN") {
                current = getNext();
                emitThen(thenLbl);
                statement();
                emitThenEnd(doneLbl);
                else_clause(elseLbl, doneLbl);
                emitDone(doneLbl);
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

void else_clause(string label, string done)
{
    // <else_clause> -> ELSE <statement> | e

    if (current.getToken() == "ELSE") {
        current = getNext();
        emitElse(label);
        statement();
        emitElseEnd(done);
    } else {
        // else clause that does nothing
        emitElse(label);
        emitGoto(done);
    }
}

void while_statement(void)
{
    // <while_statement> -> WHILE ( <comparison> ) <statement>

    // already gobbled WHILE so...
    string whileStart = makeLabel();
    string whileDone = makeLabel();
    startLoopStack.push(whileStart);
    endLoopStack.push(whileDone);
    if (current.getToken() == "(") {
        current = getNext();
        emitWhileStart(whileStart);
        string compType = comparison();
        emitCheck("", whileDone);
        if (current.getToken() == ")") {
            current = getNext();
            statement();
            emitWhileNext(whileStart);
            emitDone(whileDone);
            startLoopStack.pop();
            endLoopStack.pop();
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
        string temp = expression();
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
            string temp = expression();
            // next two cases separate for compiling
            if (current.getToken() == "TO") {
                current = getNext();
                string temp = expression();
                statement();
            } else if (current.getToken() == "DOWNTO") {
                current = getNext();
                string temp = expression();
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
        string label = startLoopStack.top();
        emitGoto(label);
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
        string label = endLoopStack.top();
        emitGoto(label);
        current = getNext();
    } else {
        parseError(current.getLineNum(), current.getValue());
    }
}

string expression(void)
{
    // <expression> -> <comparison>

    string expType = comparison();
    return expType;
}

string comparison(void)
{
    // <comparison> -> <simple_expression> { <compop> <simple_expression> }*
    string compType = simple_expression();
    // maybe change to while loop?
    if ((current.getToken() == "=") ||
        (current.getToken() == "<>") ||
        (current.getToken() == ">") ||
        (current.getToken() == "<") ||
        (current.getToken() == ">=") ||
        (current.getToken() == "<=")) {
        string op = current.getValue();
        current = getNext();
        string otherType = comparison();
        string type = typeCheck(compType, otherType);
        emitCompop(op, type);
        compType = "BOOL";
    }
    return compType;
}

string simple_expression(void)
{
    // <simple_expression> -> <unary> <term> { <addop> <term> }*

    bool isNeg = unary();
    string seType = term(); // type of the simple expression
    if (isNeg) {
        bool success = emitNeg(seType);
        if (!success) {
            semanticError(current.getLineNum(), "Cannot negate a non-number!");
        }
    }
    // seems like it could give an issue later...
    while ((current.getToken() == "+") || (current.getToken() == "-") ||
           (current.getToken() == "OR")) {
        string op = current.getToken(); // save operation
        //addop();
        current = getNext();
        string otherType = term();
        if (seType == otherType) {
            // do nothing!
        } else if (seType < otherType) {
            if (promote(seType, otherType)) {
                seType = otherType; // update the type
            } else {
                semanticError(current.getLineNum(), "type error!");
            }
        } else {
            if (promote(otherType, seType)) {
                otherType = seType;
            }
        }
        emitAddop(op, otherType);
        //string type = typeCheck(seType, otherType); // resolve the types
    }
    return seType;
}

string term(void)
{
    // <term> -> <factor> { <mulop> <factor> }*

    string termType = factor();
    while ((current.getToken() == "*") || (current.getToken() == "/") ||
           (current.getToken() == "%") || (current.getToken() == "AND")) {
        string op = current.getToken(); // save the mulop
        current = getNext();
        string otherType = factor();
        if (termType == otherType) {
            // do nothing!
        } else if (termType < otherType) {
            if (promote(termType, otherType)) {
                termType = otherType; // update the type
            } else {
                semanticError(current.getLineNum(), "type error!");
            }
        } else {
            if (promote(otherType, termType)) {
                otherType = termType;
            }
        }
        emitMulop(op, otherType);
        //mulop();
    }
    return termType;
}

string factor(void)
{
    /* <factor> -> <const> | <func_ref> | <lval> | ( <expression> ) | NOT <factor> */

    // this is where data is emitted, i.e. pushed on the stack
    string factorType; // type to be returned
    if ((current.getToken() == "NUMBER") || (current.getToken() == "DECIMAL") ||
        (current.getToken() == "CSTRING")) {
        // check to see if already in Global literal table
        factorType = types[current.getToken()]; // save this type for returning
        GLTMember seek;
        seek.value = current.getValue();
        if (factorType == "STRING") {
            seek.value += ", 0";
        }
        set<GLTMember>:: iterator it = GLT.find(seek);
        if (it != GLT.end()) {
            // found!
            emitVar((*it).label, (*it).type);
        } else {
            // Not found, so add to table them emit
            GLTMember temp;
            temp.value = current.getValue();
            temp.label = makeLabel();
            temp.type = factorType;
            if (temp.type == "STRING") {
                temp.value += ", 0";
            }
            GLT.insert(temp);
            emitVar(temp.label, temp.type);
        }

        //konst();
        current = getNext();
    } else if (current.getToken() == "IDENTIFIER") {
        // <func_ref> | <lval>
        string name = current.getValue(); // save
        current = getNext(); //GOBBLE
        //cout << "test"<< current.getValue() << endl;
        // check for a function first
        GPTMember findProc; findProc.id = name;
        set<GPTMember>:: iterator procIt = GPT.find(findProc);
        if (procIt != GPT.end()) {
            // function call!
            //cout << "girt" << current.getLineNum() << endl;
            factorType = func_ref((*procIt));
        } else {
            /*if ((current.getToken() == "[") || (current.getToken() == ".")) {
              qualifier();
              } else {*/
            // just a variable, first check local
            LSTMember localTemp; localTemp.id = name;
            set<LSTMember>:: iterator localIt = LST.find(localTemp);
            if (localIt != LST.end()) {
                // found!
                factorType = (*localIt).type;
                string idStr = "ebp - " + (*localIt).offset;
                emitVar((*localIt).internalID, factorType);
            } else {
                // then check global symbol table
                GSTMember globalTemp; globalTemp.id = name;
                set<GSTMember>:: iterator globalIt = GST.find(globalTemp);
                if (globalIt != GST.end()) {
                    // found!
                    factorType = (*globalIt).type;
                    // see if it is not an atomic type
                    if ((factorType != "INT") && (factorType != "REAL") && (factorType != "STRING")) {
                        // search the type table!
                        qualifier(); // puts correct index on stack
                        GTTMember look; look.typeID = factorType;
                        set<GTTMember>::iterator it = GTT.find(look);
                        if (it != GTT.end()) {
                            // found!
                            factorType = (*it).arrayInfo.type;
                            int elemSize;
                            if (factorType == "INT") {
                                elemSize = 4;
                            } else if (factorType == "REAL") {
                                elemSize = 8;
                            }
                            emitArrayElem(name, factorType, elemSize, true);
                        } else {
                            semanticError(current.getLineNum(), "Cannot find type " + factorType + "!");
                        }

                    } else {
                        emitVar((*globalIt).id, factorType);
                    }
                } else {
                    // not found anywhere!
                    semanticError(current.getLineNum(), current.getValue() + " not defined!");
                }
            }
        }
        //}
// \epsilon in both cases
} else if (current.getToken() == "(") {
        current = getNext();
        factorType = expression();
        if (current.getToken() == ")") {
            current = getNext();
        } else {
            parseError(current.getLineNum(), current.getValue());
        }
    } else if (current.getToken() == "NOT") {
        current = getNext();
        factorType = factor();
        if (factorType == "BOOL") {
            emitNot();
        } else {
            semanticError(current.getLineNum(), "Can only negate Booleans!");
        }
    } else {
        parseError(current.getLineNum(), current.getValue());
    }
    if (factorType == "DECIMAL")
        factorType = "REAL";
    else if (factorType == "NUMBER")
        factorType = "INT";
    return factorType;
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

bool unary(void)
{
    // <unary> -> + | - | e
    bool isNeg = false;
    if (current.getToken() == "+") {
        current = getNext();
    } else if (current.getToken() == "-") {
        isNeg = true;
        current = getNext();
    }
    return isNeg;
}

string lval(void)
{
    // <lval> -> IDENTIFIER <qualifier>
    string name = "";
    if (current.getToken() == "IDENTIFIER") {
        name = current.getValue();
        current = getNext();
        qualifier();
    } else {
        parseError(current.getLineNum(), current.getValue());
    }
    return name;
}

string func_ref(GPTMember proc) {
    // <func_ref> -> IDENTIFIER <actual_args>

    // already gobbled IDENTIFIER so...
    string type = proc.returnType; // return type of proc
    // figure that out!
    /*
    GPTMember look; look.id = name;
    set<GPTMember>::iterator it = GPT.find(look);
    if (it != GPT.end()) {
        // got it!
        type = (*it).returnType;
    } else {
        semanticError(current.getLineNum(), "Procedure " + name + "not defined!");
        }*/
    vector<string> argTypes = actual_args("PROC");
    // check arg sizes
    if (argTypes.size() != proc.parameters.size()) {
        semanticError(current.getLineNum(), "Expected " + to_string(proc.parameters.size()) + " arguments, received "
                      + to_string(argTypes.size()));
    }
    // then check types one by one
    for (int i = 0; i < argTypes.size(); i++) {
        if (argTypes.at(i) != proc.parameters.at(i).type) {
            semanticError(current.getLineNum(), "Wrong type for argument " + to_string(i));
        }
    }
    emitCall(proc);

    emitFuncRef(type);
    return type;
    
}


void qualifier(void)
{
    /* <qualifier> -> [ <expression> ] <qualifier>
       | . IDENTIFIER <qualifier>
       | e
     */

    if (current.getToken() == "[") {
        current = getNext();
        string type = expression();
        if (type == "INT") {
            
        } else {
            semanticError(current.getLineNum(), "Cannot use a non integer!");
        }
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
