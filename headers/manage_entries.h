#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <exception>
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
bool save_in_file(const Entry & entry);
