#ifndef ENTRY
#define ENTRY
#include <iostream>
#include <cstring>
class Entry
{
   char *income_type;
   char *message;
   double value;
public:
   explicit Entry(const char *st = "Default", const char *t = "Default", double val = 0.0);
   ~Entry();
   Entry(const Entry & ref);//copy constructor
   Entry & operator=(const Entry & r);
   void show(void) const;
   char* get_income(void) const {return this->income_type;}
   char* get_message(void) const {return this->message;}
   double get_value(void) const {return this->value;}

};
#endif