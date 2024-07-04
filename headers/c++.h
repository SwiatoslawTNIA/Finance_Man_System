//---------------------------------------------------------------------------------------------------------------------
// c++.h
//
// <Header of the file_managment system>
//
//---------------------------------------------------------------------------------------------------------------------
//
#include <iostream>
#include <cstring>
#include <fstream>
#include <exception>
//headers from own code implementations:
#include "string_op.h"
#include "entry.h"
#include "print_m.h"
#include "manage_entries.h"

//other datatypes:

enum TYPE{ADD_INCOME_TAXES, ADD_EXPENSE_ENTRIES, EDIT_ENTRY, DELETE_ENTRY};

enum {DEF_BUFF_SIZE = 50};
const char *arr_input[5] = {"add income taxes", "add expense entries", 
"edit existing entries", "delete entry", "display entry"};
//function prototypes:
void initialize(void);
void print_welcome(void);
bool same_strings(const char * s1, const char *s2);
void trim( char * arr);






