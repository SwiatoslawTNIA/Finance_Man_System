#ifndef STRING_OP
#define STRING_OP
#include <iostream>
#include <cctype>
#include <cstring>
#include <fstream>

bool process_print(std::ifstream & s, const char *header_n);
bool same_strings(const char * s1, const char *s2);
void trim( char * arr);
#endif