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
void emitLine(string label, string opcode, string operands, string comment);
void emitNewLine(void);
void blankLine(void);
void comment(string s);
void front(void);
void back(void);
void emitWriteStatement(void);
void emitAssingnment(string var);
void emitMulop(string opCode);
void emitAddop(string opCode);
void emitNumber(string num); 
void emitVar(string var);
void emitBss(set<GSTMember> &vars, set<GTTMember> &types);
void emitData(set<GSTMember> &consts); 

using namespace std;

/* Map for KLUMP type to size */

map<string, string> sizes =
{
    {"INT", "dw"}, {"REAL", "dq"}, {"STRING", "db"}
};
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
    emitLine("_main", "", "", "");
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

void emitVar(string var)
{
    /*
      pushes a variable operand onto the stack

      push dword [<var]
    */
    comment("Emitting an identifier.");
    cout << "push dword [" << var << "]\n";

}

void emitMulop(string opCode)
{
    /*
      op1 <op> op2
      pop ebx ; ebx <- op2
      pop eax ; eax <- op1
      cdq     ; Fix sign bit
      <op> ebx ; eax <- op1 <op> op2
      push eax ; saved for later?
    */
    string op; // assembly operation
    comment("Emitting a mulop.");
    if (opCode == "/") {
        op = "idiv"; // SIGNED division
        cout << "mov edx, 0\n"; // edx will hold remainder
    } else
        op = "mul";

    // do the assembly, assumes operands already on stack
    cout << "pop ebx\n";
    cout << "pop eax\n";
    cout << "cdq\n"; // deal with signs
    cout << op << " ebx\n";
    cout << "push eax\n"; // need to save this for later
}

void emitAddop(string opCode)
{
    string op; // assembly operation
    if (opCode == "+")
        op = "add";
    else
        op = "sub";

    // do assembly, assume operands (terms) already on stack
    comment("Emitting an addop.");
    cout << "pop ebx\n";
    cout << "pop eax\n";
    cout << op << " eax, ebx\n";
    cout << "push eax\n"; // may need to save for later
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

void emitData(set<GSTMember> &consts)
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
    for (GSTMember konst : consts) {
        if (konst.isConst) {
            string sizeStr; // how big?
            cout << "\t" << konst.id << ": " << sizes[konst.type] << " " <<
               konst.value << endl;
        }
    }
}

// end guard
#endif
