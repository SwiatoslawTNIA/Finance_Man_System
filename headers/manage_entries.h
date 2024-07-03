#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <exception>
#include "sys/stat.h"//to change the permissions for files
#include <stdexcept>
//own implementations:
#include "entry.h"
#include "print_m.h"
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


