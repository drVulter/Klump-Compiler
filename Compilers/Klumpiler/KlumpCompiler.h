/*
  Code emitting functions for PAL compiler
*/

// Guards!
#ifndef __PALCOMPILER_H_
#define __PALCOMPILER_H_

#include <iostream>
#include <cstdlib>
#include "Scanner.h"
#include "KlangError.h"
#include "Tables.h"
#include <string>
#include <stack>
#include <set>
#include <map>

// Prototypes
string makeLabel(void);
bool promote(string emp, string boss, string address);
void emitLine(string label, string opcode, string operands, string comment);
void emitNewLine(void);
void blankLine(void);
void comment(string s);
void front(void);
void back(void);
void emitProcHead(GPTMember proc);
void emitProcEnd(GPTMember proc);
void emitLabel(LLTMember label);
void emitGoto(LLTMember label);
void emitWriteStatement(void);
void emitAssingnment(string var);
void emitMulop(string opCode, string type);
void emitAddop(string opCode, string type);
void emitNumber(string num); 
void emitVar(string var, string type);
void emitBss(set<GSTMember> &vars, set<GTTMember> &types);
void emitData(set<GSTMember> &consts, set<GLTMember> &literals); 

using namespace std;

/* Map for KLUMP type to size */

map<string, string> sizes =
{
    {"INT", "dw"}, {"REAL", "dq"}, {"STRING", "db"}
};

// Make a new internal label
string makeLabel(void)
{
    static int count = 0; // label count, STATIC!!!
    string strCount = to_string(count++); // increase the count
    return "_L_" + strCount + "_";
}

bool promote(string emp, string boss, string address)
{
    // try to promote emp type to boss type
    bool promoted = true; // assume worked at first
    if (emp == boss) {
        ; // no promotion necessary, do nothing
    } else if ((emp == "BOOL") && (boss == "INT")) {
        // no work necessary, but make a note
        emitLine("", "nop", "", "Promoting BOOL to INT");
    } else if ((emp == "INT") && (boss == "REAL")) {
        // actually need to do work
        // assume INT value is on stack
        /*
          pop dword [_TEMP_INT_]
          fild dword [_TEMP_INT_]
         */
        emitLine("", "pop dword", "[_TEMP_INT_]", "put integer operand into temporary storage");
        emitLine("", "fild dword", "[_TEMP_INT_]", "then put that value onto floating point stack");
    } else {
        // failure!
        promoted = false;
    }
    return promoted;
}
// emit a line of assembly language
void emitLine(string label, string opcode, string operands, string comment)
{
    /*
      General Format:
      <label> <opcode> <operands> ; <comment>
     */
    if (label != "")
        cout << label + ": ";
    else
        cout << "\t";
    if (opcode != "")
        cout <<  opcode + " ";
    else
        cout << " ";
    if (operands != "")
        cout <<  operands + " ";
    else
        cout <<  " ";
    if (comment != "")
        cout << "\t ; " + comment;
    cout << endl;
}

void emitNewLine(void)
{
    
}
// emits an assembly language comment
void comment(string s)
{
    // possibly remove newline? 
    cout << ";; " << s << "\n";
}

// emits a blank line
void blankLine(void)
{
    cout << "\n";
}

// emits the first part of the .text section
void front(void)
{
    /*
      section .text
      global _main
      _main:
      ;; set up stack frame
      push ebp
      mov ebp, esp 
     */

    // possibly move these to separate function??
    comment("This was made by a machine!");
    blankLine();
    cout << "global _main\n";
    cout << "extern _printf\n";
    blankLine();
    comment("TEXT Section");
    cout << "section .text\n";
    //emitLine("_main", "", "", "");
    /* Don't need stack stuff? */
    //comment("Set up stack frame");
    //cout << "push ebp\n";
    //cout << "mov ebp, esp\n";
}

void back(void)
{
    /*
      ;; Exit
      push dword 0
      mov eax, 0x1
      sub esp, 4
      int 0x80
     */
    comment("Exit");
    emitLine("_exit_main", "", "", "");
    emitLine("", "push", "dword 0", "");
    emitLine("", "mov", "eax, 0x1", "");
    emitLine("", "sub", "esp, 4", "");
    emitLine("", "int", "0x80", "Make exit call");
}

void emitProcHead(GPTMember proc)
{
    // emit beginning of procedure
    string label; // internal label
    if (proc.id == "main") {
        label = "_main";
    } else {
        label = "_ENTER_" + proc.id;
    }
    emitLine(label, "", "", "Begin " + proc.id);
    // set up the stack
    emitLine("", "push", "ebp", "Save base pointer");
    emitLine("", "mov", "ebp, esp", "new base");
    // set up storage
    emitLine("", "sub", "esp, " + to_string(proc.storage), "Reserve memory for local variables");
}

void emitProcEnd(GPTMember proc)
{
    // ESCHATON
    string label = "_EXIT_" + proc.id;
    emitLine(label, "", "","End of " + proc.id);
    emitLine("", "push", "ebp", "Fix stack");
    emitLine("", "mov", "ebp, esp", "");
    emitLine("", "add", "esp, " + to_string(proc.storage), "Deallocate local memory");
}
/* ********************** STATEMENTS ********************** */

void emitLabel(LLTMember label)
{
    /*
      Assembly label
      <label>: nop
     */

    emitLine(label.intLabel, "nop", "", "");
}

void emitGoto(LLTMember label)
{
    /*
      Assembly goto
      jmp label
     */
    emitLine("", "jmp", label.intLabel, ""); 
}

void emitWriteStatement(Lexeme l)
{
    /*
      Basic print statement, uses C printf function.
      str defined in data section, possibly not needed?

      push ebp
      mov ebp, esp
      push dword [<IDENTIFIER>] OR push dword NUMBER
      push dword str
      call _printf
      add esp, 8
      mov esp, ebp
      pop ebp
     */
    string outString;
    if (l.getToken() == "NUMBER")
        outString = l.getValue();
    else
        outString = "[" + l.getValue() + "]";
    comment("Print statement");
    cout << "push ebp\n";
    cout << "mov ebp, esp\n";
    cout << "push dword " << outString << "\n";
    cout << "push dword str\n"; // str predefined for formatting
    cout << "call _printf\n"; // actual function call
    cout << "add esp, 8\n";
    cout << "mov esp, ebp\n";
    cout << "pop ebp\n";
    comment("Stack frame torn down.");
}


void emitNumber(string num)
{
    /*
      pushes a number operand onto the stack

      push <num>
    */
    comment("Emitting a number.");
    cout << "push " << num << "\n";
}

void emitVar(string var, string type)
{
    /*
      pushes a variable operand onto the stack

      push dword [<var>]
    */
    string typeStr;
    if (type == "INT") {
        typeStr = "dword";
        emitLine("", "push " + typeStr, "[" + var + "]", "Emitting a variable");
    } else if (type == "REAL") {
        typeStr = "qword";
        emitLine("", "fld " + typeStr, "[" + var + "]", "Emitting a real variable");
    }

}

void emitMulop(string opCode, string type)
{
    /*
      op1 <op> op2
      pop ebx ; ebx <- op2
      pop eax ; eax <- op1
      cdq     ; Fix sign bit
      <op> ebx ; eax <- op1 <op> op2
      push eax ; saved for later?
    */
    /*
          * or / or % or AND
     */
    comment("Emitting a mulop (" + opCode + ")");
    string op;
    if (type == "REAL") {
        if (opCode == "*") {
            op = "fmul";
        } else if (opCode == "/") {
            op = "fdiv";
        } // check for other ops here? should throw an error
        emitLine("", op, "", "result stored in floating point stack");
    } else if (type == "INT") {
        string source = "eax"; // eax or edx (%)
        if (opCode == "*") {
            op = "mul";
        } else {
            op = "idiv";
            emitLine("", "xor", "edx, edx", "EDX holds remainder");
            if (opCode == "%")
                source = "edx";
        }
        emitLine("", "pop", "ebx", "");
        emitLine("", "pop", "eax", "");
        emitLine("", "cdq", "", "Deal with signs");
        emitLine("", op, "ebx", "Perform operation (like a surgeon)");
        emitLine("", "push", source, "PIOTFS");
    }
}

void emitAddop(string opCode, string type)
{
    string op; // assembly operation
    comment("Emitting an addop (" + opCode + ")");
    if (type == "INT") {
        if (opCode == "+")
            op = "add";
        else
            op = "sub";
        emitLine("", "pop", "ebx", "");
        emitLine("", "pop", "eax", "");
        emitLine("", op, "eax, ebx", "Addop!");
        emitLine("", "push", "eax", "Storing result on stack");
    } else if (type == "REAL") {
        if (opCode == "+") {
            op = "fadd";
        } else {
            op = "fsub";
        }
        emitLine("", op, "", "Addop, result on floating point stack");
    }
    /*
    // do assembly, assume operands (terms) already on stack
    comment("Emitting an addop.");
    cout << "pop ebx\n";
    cout << "pop eax\n";
    cout << op << " eax, ebx\n";
    cout << "push eax\n"; // may need to save for later
    */
}

void emitAssignment(string var)
{
    /*
      assigns eax to var, assuming the expression result is on top of stack

      pop eax
      mov [<var] eax
    */
    comment("Emitting an assignment.");
    cout << "pop eax\n";
    cout << "mov [" << var << "], eax\n";
}

/* ******************************************************** */
void emitBss(set<GSTMember> &vars, set<GTTMember> &types)
{
    /*
      section .bss
      var: resb 4
      ...
    */
    blankLine();
    cout << "section .bss\n";

    for (GSTMember var : vars) {
        if (!var.isConst) {
            GTTMember tempType; tempType.typeID = var.type; // dummy for searching
            set<GTTMember>:: iterator it = types.find(tempType);
            if (it != types.end()) { // cover yourself!
                tempType = *it;
                cout << "\t" << var.id << ": resb " <<
                    tempType.size << endl;
            } else {
                // something? some kinda error?
            }
        }
    }
}

void emitData(set<GSTMember> &consts, set<GLTMember> &literals)
{
    /*
      Constant data for KLUMP
      still need various predefined strings
      str: db "%d", 10, 0
    */

    blankLine();
    cout << "section .data\n";
    cout << "\tintStr: db \"%d\", 10, 0\n";
    cout << "\trealStr: db \"%f\", 10, 0\n";
    cout << "\tstrStr: db \"%s\", 10, 0\n";
    // emit the constants
    for (GSTMember konst : consts) {
        if (konst.isConst) {
            //string sizeStr; // how big?
            cout << "\t" << konst.id << ": " << sizes[konst.type] << " " <<
               konst.value << endl;
        }
    }
    // now emit the literals
    for (GLTMember literal : literals) {
        cout << "\t" << literal.label << ": " << sizes[literal.type] << " " <<
            literal.value << endl;
    }
}

// end guard
#endif
