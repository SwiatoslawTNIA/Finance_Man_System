//---------------------------------------------------------------------------------------------------------------------
// manage_entries.h
//
// <Header file for manage_entries.cc>
//
//---------------------------------------------------------------------------------------------------------------------
//
#ifndef MANAGE_ENTRIES
#define MANAGE_ENTRIES

#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <exception>
#include "sys/stat.h"//to change the permissions for files
#include <stdexcept>
#include <sstream>
#include <vector>
//own implementations:
#include "entry.h"
#include "print_m.h"
#include "string_op.h"
//rapidjson for json:
#include "../rapidjson/include/rapidjson/document.h"
#include "../rapidjson/include/rapidjson/writer.h"
#include "../rapidjson/stringbuffer.h"
//func prototypes:
void add_income_tax(void);
Entry process_input(void);
bool save_in_file_input(const Entry & entry);
void add_expense_entries(void);
Entry process_expenses(void); //func has internal linkage
bool save_in_file_expenses(const Entry & entry);
void create_file(const char * filename);
std::vector<Entry>* process_string(std::fstream & input_array);
bool display_all(void);
bool file_is_empty(std::ifstream & s);
bool file_is_empty(std::fstream & s);
void edit_existing_entries(void);
bool store_in_file(const Entry & e, std::ofstream & is);
bool edit_file(const char *file);
bool search_for_string(const char *target, const char *sources);
void delete_entry(void);
bool delete_from_file(const char *file);
//other :
static unsigned short int TAXES, EXPENSES;//static, each file has it's own copy

#endif


