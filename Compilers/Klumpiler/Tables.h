/*
  Table stuff for KLUMP
 */

// Guards!
#ifndef __TABLES_H_
#define __TABLES_H_

#include "Scanner.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

/* Array Information */
struct arrInfo 
{
    int range; // how many elements, 0 -> (range - 1)
    string type; // what type is each element?
};

/* Record Info */
struct recInfo 
{

};

/* Parameter for function */
struct parameter
{
    string id; // identifier
    string type; // type
    bool callbyVAR;
};

/*********************** GLOBAL TABLE STUFF ************************/
/* Entry in GLOBAL SYMBOL TABLE */
struct GSTMember 
{
    string id;
    string type; // what kind of symbol?
    bool isConst;
    string value; // to be used if constant
    bool operator < (const GSTMember &other) const { return id < other.id; }
};

/* Entry in GLOBAL PROCEDURE TABLE */
struct GPTMember
{
    string id; // Procedure ID
    vector<parameter> parameters; // list of parameters
    string returnType; // return type
    int storage; // local storage in BYTES
    bool operator < (const GPTMember &other) const { return id < other.id; }
};
/* Entry in GLOBAL LITERAL TABLE */
struct GLTMember 
{
    string label;
    string type;
    string value;
    bool operator < (const GLTMember &other) const { return value < other.value; }
};

/* Entry in GLOBAL TYPE TABLE */
struct GTTMember 
{
    string typeID; // Identifier
    int size; // in bytes
    string structure; // atomic (INT,REAL,CSTRING)/array/record
    arrInfo arrayInfo;
    recInfo recordInfo;
    bool operator < (const GTTMember &other) const { return typeID < other.typeID; }
};

/* ********************** LOCAL TABLE STUFF *********************** */
/* Entry in LOCAL SYMBOL TABLE */
struct LSTMember 
{
    string id;
    string type;
    string offset; // depends on size
    bool callbyVAR; // call by VAR or VAL 
    bool operator < (const LSTMember &other) const { return id < other.id; }
};


/* Entry in LOCAL LABEL TABLE */
struct LLTMember
{
    string numLabel; // numeric label
    string intLabel; // internal label
    bool operator < (const LLTMember &other) const { return numLabel < other.numLabel; }
};

#endif // end guard