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
#include <string>
#include <stack>

// Prototypes

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
void emitBss(stack<string> &s);
void emitData(void); // takes in nothing for now...

using namespace std;

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
    cout << "global _main\n";
    cout << "extern _printf\n";
    blankLine();
    cout << "section .text\n";
    cout << "_main:\n";
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
    cout << "push dword 0\n";
    cout << "mov eax, 0x1\n";
    cout << "sub esp, 4\n";
    cout << "int 0x80\n";
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

void emitBss(stack<string> &s)
{
    /*
      section .bss
      var: resb 4
      ...
    */
    blankLine();
    cout << "section .bss\n";

    while (!s.empty()) {
        cout << s.top() << ": " << "resb 4\n";
        s.pop();
    }
}

void emitData(void)
{
    /*
      No constants yet so simple.

      str: db "%d", 10, 0
    */

    blankLine();
    cout << "section .data\n";
    cout << "str: db \"%d\", 10, 0\n";
}

// end guard
#endif
