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
bool promote(string emp, string boss);
void emitLine(string label, string opcode, string operands, string comment);
void emitNewLine(void);
void modStack(int n);
void blankLine(void);
void comment(string s);
void front(void);
void back(void);
void emitCall(GPTMember proc);
void emitProcHead(GPTMember proc);
void emitProcEnd(GPTMember proc);
void emitLabel(LLTMember label);
void emitGoto(string label);
void emitEmptyStatement(void);
void emitWrite(string type);
void emitWriteln(void);
void emitRead(string name, string type, bool isLocal);
void emitReadln(void);
void emitAssignment(string var, string type);
void emitArrayAssignment(GTTMember arrayType);
void emitCompop(string opCode, string type);
void emitCheck(string thenLbl, string elseLbl);
void emitThen(string thenLbl);
void emitThenEnd(string doneLbl);
void emitElse(string label);
void emitElseEnd(string done);
void emitWhileStart(string start);
void emitWhileNext(string start);
void emitDone(string label);
void emitForStatement(bool to);
void emitReturn(string type, string otherType, string label, int lineNum);
void emitFuncRef(string type);
void emitMulop(string opCode, string type);
void emitAddop(string opCode, string type);
void emitNot(void);
bool emitNeg(string type);
void emitNumber(string num);
void emitVar(string var, string type);
void findArrayElem(string name, string type, int elemSize, bool isGlobal);
void emitArrayElem(string type);
void emitArrayElemAddr();
void emitLiteral(string label, string type);
void emitBss(set<GSTMember> &vars, set<GTTMember> &types);
void emitData(set<GSTMember> &consts, set<GLTMember> &literals);

using namespace std;

/* Map for KLUMP type to size */

map<string, string> sizes =
{
    {"INT", "dd"}, {"REAL", "dq"}, {"STRING", "db"}
};

// Make a new internal label
string makeLabel(void)
{
    static int count = 0; // label count, STATIC!!!
    string strCount = to_string(count++); // increase the count
    return "_L_" + strCount + "_";
}

bool promote(string emp, string boss)
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

bool demote(string from, string to)
{
    bool demoted = true;
    if (from == to) {
        ;
    } else if ((from == "REAL") && (to == "INT")) {
        emitLine("", "fstp qword", "[_TEMP_REAL_]", "pop into temp storage");
        emitLine("", "cvtsd2si", "eax, [_TEMP_REAL_]", "Convert the heathen");
        emitLine("", "push", "eax", "Put back onto stack");
    }
    return demoted;
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

void modStack(int n)
{
    // add <n> to esp
    emitLine("", "add", "esp, " + to_string(n), "Stack fix");
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
    emitLine("", "global _main", "", "Entry point");
    emitLine("", "extern _printf", "", "Output");
    emitLine("", "extern _scanf", "", "Input");
    emitLine("", "extern _getchar", "", "Gobbler");
    emitLine("", "extern _fflush", "", "Flush buffers to stdout");
    blankLine();
    comment("TEXT Section");
    emitLine("", "section .text", "", "");
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

void emitCall(GPTMember proc)
{
    comment("Call statement");
    emitLine("", "call", proc.label, "");
    // clean up arguments
    int clean = 0;
    for (int i = 0; i < proc.parameters.size(); i++) {
        /*
        if (proc.parameters.at(i).type == "INT") {
            clean += 4;
        } else if (proc.parameters.at(i).type == "REAL") {
            clean += 8;
        } else {
            // figure out type
        }
        */
        clean += proc.parameters.at(i).size;
    }
    emitLine("", "add", "esp, " + to_string(clean), "");
}

void emitProcHead(GPTMember proc)
{
    // emit beginning of procedure
    string label = proc.label; // internal label

    emitLine(label, "", "", "Begin " + proc.id);
    // set up the stack
    emitLine("", "push", "ebp", "Save base pointer");
    emitLine("", "mov", "ebp, esp", "new base");
    // set up storage
    int offset = proc.storage + (16 - (proc.storage % 16)) - 4 + 16;
    if (proc.id != "MAIN")
        offset -= 4;
    // for bullshit stack align purposes, must also fix stack for arguments
    int clean = 0;
    for (int i = 0; i < proc.parameters.size(); i++) {
        if (proc.parameters.at(i).type == "INT") {
            clean += 4;
        } else if (proc.parameters.at(i).type == "REAL") {
            clean += 8;
        }
    }
    offset -= clean;
    emitLine("", "sub", "esp, " + to_string(offset), "Reserve memory for local variables");
}

void emitProcEnd(GPTMember proc)
{
    // ESCHATON
    string label = "_EXIT_" + proc.id;
    int offset = proc.storage + (16 - (proc.storage % 16)) - 4 + 16;
    emitLine(label, "", "","End of " + proc.id);
    emitLine("", "add", "esp, " + to_string(offset), "Deallocate local memory");
    emitLine("", "mov", "esp, ebp", "");
    emitLine("", "pop", "ebp", "Fix stack");
    if (proc.id != "MAIN") {
        emitLine("", "ret", "", "");
    } else {
        emitLine("", "push", "dword 0", "");
        emitLine("", "mov", "eax, 0x1", "");
        emitLine("", "sub", "esp, 4", "");
        emitLine("", "int", "0x80", "Make exit call");
    }
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

void emitGoto(string label)
{
    /*
      Assembly goto
      jmp label
     */
    emitLine("", "jmp", label, "");
}

void emitEmptyStatement(void)
{
    /*
      nop
     */
    emitLine("", "nop", "", "");
}

void emitWrite(string type)
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
    //for (int i = 0; i < argTypes.size(); i++) {
    //string type = argTypes[i];
        if (type == "REAL") {
            comment("Writing a REAL");
            modStack(4);
            emitLine("", "fstp qword", "[_TEMP_REAL_]", "Put the real in temporary storage");

            emitLine("", "push dword", "[_TEMP_REAL_+4]", "");
            emitLine("", "push dword", "[_TEMP_REAL_]", "");
            emitLine("", "push dword", "_realStr", "string for formatting");
            emitLine("", "call", "_printf", "Make the call");
            emitLine("", "add", "esp, 12", "Fix the stack");

        } else {
            string typeStr; // formatting string
            string arg; // actual pushed arg
            if (type == "INT") {
                typeStr = "_intStr";
                //arg = "[" + name + "]";
                comment("Writing an INT");
            } else if (type == "STRING") {
                typeStr = "_strStr";
                //arg = name;
                comment("Writing a STRING");
            }
            //emitLine("", "push", "ebp", "");
            //emitLine("", "mov", "ebp, esp", "");
            //emitLine("", "push dword", arg, "Actual arg");
            emitLine("", "push dword", typeStr, "");
            emitLine("", "call", "_printf", "Make the call");
            emitLine("", "add", "esp, 12", "stack fixed");
            //emitLine("", "add", "esp, 8", "Fix stack");
            //emitLine("", "mov", "esp, ebp", "");
            //emitLine("", "pop", "ebp", "Stack frame restored");
        }
        //}
    // Sittin' on tha toilet
    comment("Now FLUSH!");
    emitLine("", "sub", "esp, 8", "");
    emitLine("", "push dword", "0", "flush all buffers to stdout");
    emitLine("", "call", "_fflush", "make the call");
    emitLine("", "add", "esp, 12", "Clean up stack");
}

void emitWriteln(void)
{
    comment("Printing a linebreak");
    emitLine("", "push", "ebp", "");
    emitLine("", "mov", "ebp, esp", "");
    emitLine("", "push dword", "_NEW_LINE_", "pushing line break");
    emitLine("", "push dword", "_strStr", "");
    emitLine("", "call", "_printf", "Make the call");
    emitLine("", "add", "esp, 8", "Fix stack");
    emitLine("", "mov", "esp, ebp", "");
    emitLine("", "pop", "ebp", "Stack frame restored");
    // no need to FLUSH
}

void emitRead(string name, string type, bool isLocal)
{
	/*
		Assume that
		add esp, -4
		push dword <VAR>
		have already been emitted
	*/
	comment("Read!");
  string varStr = name;
  if (isLocal) {
      emitLine("", "lea", "eax, [" + varStr + "]", "Use eax to store address of local var");
      varStr = "eax";
  }
  emitLine("", "add", "esp, -4", "Pad the stack");
  emitLine("", "push dword", varStr, "put variable address on stack");
	if (type == "INT") {
      emitLine("", "push dword", "_INT_IN_", "temp storage");
	} else if (type == "REAL") {
      emitLine("", "push dword", "_REAL_IN_", "temp storage");
	} else {
      // shouldn't happen
	}
	emitLine("", "call", "_scanf", "Make the call");
	emitLine("", "add", "esp, 12", "Fix the stack");
}

void emitReadln(void)
{
    comment("Readln!");
    string label = makeLabel();
    emitLine(label, "", "", "read line loop");
    emitLine("", "add", "esp, -12", "");
    emitLine("", "call", "_getchar", "");
    emitLine("", "add", "esp, 12", "");
    emitLine("", "cmp", "eax, 0xa", "check for carriage return");
    emitLine("", "jne", label, "gobble gobble gobble!");
}

void emitAssignment(string var, string type)
{
    comment("Assignment");
    if ((type == "INT")) {
        emitLine("", "pop dword", "eax", "");
        //emitLine("", "mov", "_TEMP_INT_", "Move to temp storage");
        emitLine("", "mov", var + ", eax", "make the move");
    } else if (type == "STRING") {
        emitLine("", "pop dword", "esi", "Source");
        emitLine("", "lea", "edi, " + var, "Destination");
        // this is shitty, bad hack, fix later
        emitLine("", "mov", "ecx, 1000", "mov up to 1000 characters");
        //emitLine("", "mov", "ecx, " + var + ".len", "length");
        emitLine("", "cld", "", "");
        emitLine("", "rep", "movsb", "Do the move");
    } else if (type == "REAL") {
        emitLine("", "fstp qword", var, "");
    }
}

void emitArrayAssignment(GTTMember arrayType)
{
    // make a copy of an array!
    string copyLabel = makeLabel();
    comment("Copying an array...");
    int elemSize;
    if (arrayType.arrayInfo.type == "INT") {
        elemSize = 4;
    } else if (arrayType.arrayInfo.type == "REAL") {
        elemSize = 8;
    }
    int numElements = arrayType.size / elemSize;
    emitLine("", "mov", "ecx, " + to_string(numElements), "Counter");
    emitLine("", "mov", "ebx, " + to_string(elemSize), "size of each element");
    emitLine(copyLabel, "nop", "", "");
    if (arrayType.arrayInfo.type == "REAL") {
        emitLine("", "fld qword", "[esi]", "load source data");
        emitLine("", "fstp qword", "[edi]", "Into destination");
    } else if (arrayType.arrayInfo.type == "INT") {
        emitLine("", "push dword", "[esi]", "load source data");
        emitLine("", "pop dword", "[edi]", "into dest.");
    }
    emitLine("", "add", "esi, ebx", "Increment addresses");
    emitLine("", "add", "edi, ebx", "Increment addresses");
    emitLine("", "loop", copyLabel, "");
}

void emitCompop(string op, string type)
{
    comment("Comparison");
    string resFalse = makeLabel(); // jumped to if true
    string resTrue = makeLabel(); // jumped to if false
    string compDone = makeLabel(); // jump to when finished
    string jump; // type of jump
    if (type == "INT") {
        emitLine("", "pop", "ebx", "");
        emitLine("", "pop", "eax", "");
        emitLine("", "cmp", "eax, ebx", "make comparison");
        if (op == "=") {
            jump = "je";
        } else if (op == "<") {
            jump = "jl";
        } else if (op == "<=") {
            jump = "jle";
        } else if (op == ">") {
            jump = "jg";
        } else if (op == ">=") {
            jump = "jge";
        } else if (op == "<>") {
            jump = "jne";
        }
        emitLine("", jump, resTrue, "make the jump");
    } else if (type == "REAL") {
        //emitLine("", "fstp qword", "xmm1", "");
        //emitLine("", "fstp qword", "xmm0", "");
        emitLine("", "fcom", "st0, st1", "compare top two elements of floating point stack");
        emitLine("", "fstsw", "ax", "");
        emitLine("", "and", "eax, 0100011100000000B", "");
        // flip operations since values are reversed on stack
        if (op == "=") {
            emitLine("", "cmp", "eax, 0100000000000000B", "");
            jump = "je";
        } else if (op == "<") {
            emitLine("", "cmp", "eax, 0000000000000000B", "");
            jump = "je";
        } else if (op == "<=") {
            jump = "je";
            emitLine("", "cmp", "eax, 0000000000000000B", "first check <");
            emitLine("", jump, resTrue, "make the jump");
            emitLine("", "cmp", "eax, 0100000000000000B", "then check =");
        } else if (op == ">") {
            //jump = "jl";
            emitLine("", "cmp", "eax, 0000000100000000B", "");
            jump = "je";
        } else if (op == ">=") {
            jump = "je";
            emitLine("", "cmp", "eax, 0000000100000000B", "");
            emitLine("", jump, resTrue, "make the jump");
            emitLine("", "cmp", "eax, 0100000000000000B", "then check =");
        } else if (op == "<>") {
            jump = "jne";
        }
        emitLine("", jump, resTrue, "make the jump");
    }
    emitLine(resFalse, "nop", "", "first since default");
    emitLine("", "push", "0", "result = FALSE");
    emitLine("", "jmp", compDone, "move on");
    emitLine(resTrue, "nop", "", "");
    emitLine("", "push", "1", "result = TRUE");
    emitLine("", "jmp", compDone, "");
    emitLine(compDone, "", "", "");
}

void emitCheck(string thenLbl, string elseLbl)
{
    comment("Check for if statement");
    emitLine("", "pop", "eax", "get truth value");
    emitLine("", "cmp", "eax, 1", "");
    emitLine("", "jne", elseLbl, "not true so ELSE");
    //emitLine("", "jmp", thenLbl, "");
}

void emitThen(string thenLbl)
{
    comment("Begin THEN clause");
    emitLine(thenLbl, "nop", "", "");
}

void emitThenEnd(string doneLbl)
{
    comment("finsihed so go to done");
    emitLine("", "jmp", doneLbl, "");
}

void emitElse(string label)
{
    comment("Else");
    emitLine(label, "nop", "", "");
}

void emitElseEnd(string done)
{
    comment("Finished with else");
    emitLine("", "jmp", done, "");
}

void emitWhileStart(string start)
{
    comment("While statement");
    emitLine(start, "nop", "", "");
}

void emitWhileNext(string start)
{
    emitLine("", "jmp", start, "go again");
}

void emitDone(string label)
{
    emitLine(label, "nop", "", "");
}

void emitForStatement(bool to)
{
    string step;
    emitLine("", "pop", "edx", "Destination");
    emitLine("", "pop", "ecx", "start");
    if (to) {
        step = "1";
    } else {
        step = "-1";
    }
}

void emitReturn(string type, string otherType, string label, int lineNum)
{
    // puts a return value in registers for access from the previous function
    comment("Return statement");
    // type conversion
    if (type == otherType) {
        if (otherType == "INT") {
            // return val should be on stack, so pop it to eax
            emitLine("", "pop", "eax", "put into register");
        } else if (otherType == "REAL") {
            emitLine("", "fstp qword", "[_TEMP_REAL_]", "");
        } else if (otherType == "STRING") {
            emitLine("", "pop", "eax", "");
            //emitLine("", "lea", "eax, [ebx]", "");
        }
        
    } else if (type < otherType) {
        if (promote(type, otherType)) {
            if (otherType == "INT") {
                // return val should be on stack, so pop it to eax
                emitLine("", "pop", "eax", "put into register");
            } else if (otherType == "REAL") {
                emitLine("", "fstp qword", "[_TEMP_REAL_]", "");
            } else if (otherType == "STRING") {
                emitLine("", "pop", "eax", "");
                //emitLine("", "lea", "eax, [ebx]", "");
            }
        } else {
            semanticError(lineNum, "Wrong return type!");
        }
    } else {
        if (demote(type, otherType)) {
            if (otherType == "INT") {
                // return val should be on stack, so pop it to eax
                emitLine("", "pop", "eax", "put into register");
            } else if (otherType == "REAL") {
                emitLine("", "fstp qword", "[_TEMP_REAL_]", "");
            } else if (otherType == "STRING") {
                emitLine("", "pop", "eax", "");
                //emitLine("", "lea", "eax, [ebx]", "");
            }
        } else {
            semanticError(lineNum, "Wrong return type!");
        }
    }
    emitGoto(label);
}

void emitFuncRef(string type)
{
    if (type == "INT") {
        emitLine("", "push", "eax", "put value back on stack");
    } else if (type == "REAL") {
        emitLine("", "fld qword", "[_TEMP_REAL_]", "");
    }
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
    } else if (type == "STRING") {
        typeStr = "dword";
        emitLine("", "lea", "eax, [" + var + "]", "");
        emitLine("", "push ","eax", "Emitting a STRING var");
    }

}

void findArrayElem(string name, string type, int elemSize, bool isGlobal)
{
    comment("Pushing array element onto the stack");
    if (isGlobal) {
        emitLine("", "mov", "esi, " + name, "Store address of first element");
    } else {
        emitLine("", "lea", "esi, [" + name + "]", "");
    }
    emitLine("", "pop", "eax", "get index");
    emitLine("", "mov", "ebx, " + to_string(elemSize), "");
    emitLine("", "mul", "ebx", "Adjust for size");
    emitLine("", "add", "esi, eax", "Get element at corrent index");
}

void emitArrayElem(string type)
{
    if (type == "INT") {
        emitLine("", "push dword", "[esi]", "push value to stack");
    } else if (type == "REAL") {
        emitLine("", "fld qword", "[esi]", "push real array val to stack");
    }
}

void emitArrayElemAddr()
{
    emitLine("", "push dword", "esi", "putting addresss on top of stack");
}

void emitEntireArray(string name, string type, int elemSize, int size, bool isGlobal)
{
    comment("Putting an entire array on the stack!");
    string loopLabel = makeLabel();

}

void emitLiteral(string label, string type)
{
    if (type == "INT") {
        emitLine("", "push dword", "[" + label + "]", "Emitting an integer literal");
    } else if (type == "REAL") {
        emitLine("", "fld qword", "[" + label + "]", "Emitting a real literal");
    } else if (type == "STRING") {
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
    } else if (type == "BOOL") {
        string labelTrue = makeLabel();
        string labelFalse = makeLabel();
        string labelDone = makeLabel();
        if (opCode == "AND") {
            // both ops must be TRUE!
            emitLine("", "pop", "eax", "");
            emitLine("", "pop", "ebx", "");
            /*
            emitLine("", "cmp", "eax, 1");
            emitLine("", "jne", labelFalse, "false, so false!");
            emitLine("", "cmp", "ebx, 1", "");
            emitLine("", "jne", labelFalse, "false, so false!");
            emitLine("", "push", "1", "passed both so push true, then go to DONE");
            emitLine("","jmp", labelDone, "");
            */
            emitLine("", "add", "eax, ebx", "");
            emitLine("", "cmp", "eax, 2", "were they both true?");
            emitLine("", "jne", labelFalse, "nope!");
            emitLine(labelTrue, "nop", "", "");
            emitLine("", "push", "1", "TRUE!");
            emitLine("", "jmp", labelDone, "");
            emitLine(labelFalse, "nop", "", "");
            emitLine("", "push", "0", "FALSE!");
            emitLine(labelDone, "nop", "", "");
        } else {
            // shouldnt happen, right?
        }
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
    } else if (type == "BOOL") {
        string labelTrue = makeLabel();
        string labelFalse = makeLabel();
        string labelDone = makeLabel();
        emitLine("", "pop", "eax", "");
        emitLine("", "pop", "ebx", "");
        emitLine("", "add", "eax, ebx", "");
        emitLine("", "cmp", "eax, 0", "was one true?");
        emitLine("", "je", labelFalse, "nope!");
        emitLine(labelTrue, "nop", "", "");
        emitLine("", "push", "1", "TRUE!");
        emitLine("", "jmp", labelDone, "");
        emitLine(labelFalse, "nop", "", "");
        emitLine("", "push", "0", "FALSE!");
        emitLine(labelDone, "nop", "", "");
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
void emitNot(void)
{
    comment("Logical negation");
    string labelTrue = makeLabel();
    string labelFalse = makeLabel();
    string labelDone = makeLabel();
    emitLine("", "pop", "eax", "");
    emitLine("", "cmp", "eax, 1", "");
    emitLine("", "jne", labelFalse, "false!");
    emitLine("", "push", "0", "Was true, so push false!");
    emitLine("", "jmp", labelDone, "");
    emitLine(labelFalse, "nop", "", "");
    emitLine("", "push", "1", "was false, so flip to true!");
    emitLine(labelDone, "nop", "", "Done with negation");
}
bool emitNeg(string type)
{
    bool success = true;
    comment("Negation");
    if (type == "INT") {
        emitLine("", "push dword", "-1", "");
        emitMulop("*", "INT");
    } else if (type == "REAL") {
        emitLine("", "fld qword", "[_NEGATIVE_]", "");
        emitMulop("*", "REAL");
    } else {
        success = false;
    }
    return success;
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
    emitLine("", "section", ".bss", "");
    emitLine("", "_TEMP_REAL_: resb", "8", "Temporary storage for reals");
    for (GSTMember var : vars) {
        if (!var.isConst) {
            GTTMember tempType; tempType.typeID = var.type; // dummy for searching
            set<GTTMember>:: iterator it = types.find(tempType);
            if (it != types.end()) { // cover yourself!
                tempType = *it;
                emitLine(var.id, "resb", to_string(tempType.size), "");
                //cout << "\t" << var.id << ": resb " <<
                //    tempType.size << endl;
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
    emitLine("", "section", ".data", "");
    emitLine("_intStr", "db", "\"%d\", 0", "");
    emitLine("_realStr", "db", "\"%f\", 0", "");
    emitLine("_strStr", "db", "\"%s\", 0", "");
    emitLine("_NEW_LINE_",  "db","10, 0", "Just a carriage return");
    emitLine("_NEGATIVE_", "dq -1.0", "", "Just negative one");
    // reading
    emitLine("_INT_IN_", "db \"%d\", 0", "", "");
    emitLine("_REAL_IN_", "db \"%lf\", 0", "", "");
    // emit the constants
    for (GSTMember konst : consts) {
        if (konst.isConst) {
            //string sizeStr; // how big?
            emitLine(konst.id, sizes[konst.type], konst.value, "");
            /*cout << "\t" << konst.id << ": " << sizes[konst.type] << " " <<
              konst.value << endl; */
        }
    }
    // now emit the literals
    for (GLTMember literal : literals) {
        emitLine(literal.label, sizes[literal.type], literal.value, "");
        //cout << "\t" << literal.label << ": " << sizes[literal.type] << " " <<
        //    literal.value << endl;
        //if (literal.type == "STRING")
        //   emitLine(".len", "equ", "$ - " + literal.label, "Length in bytes");
    }
}

// end guard
#endif
