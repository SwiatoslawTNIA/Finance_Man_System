//---------------------------------------------------------------------------------------------------------------------
// entry.cc
//
// <Implementation of the entry class>
//
//---------------------------------------------------------------------------------------------------------------------
//
#include "entry.h"

//---------------------------------------------------------------------------------------------------------------------
///Entry contructor
/// @param s1 the name of each entry
/// @param str2 the comment for each entry
/// @param val the value
///
/// @return the highest number
//
Entry::Entry(const char *st, const char *str2,  double val): value(val)
{
   input = new char[strlen(st) + 1];
   message = new char[strlen(str2) + 1];
   strcpy(message, str2);
   strcpy(input, st);
}
//---------------------------------------------------------------------------------------------------------------------
///Entry destructor
Entry::~Entry()
{
   if(input != nullptr)
      delete [] input;
   if(message != nullptr)
      delete [] message;
}
//---------------------------------------------------------------------------------------------------------------------
///Entry copy contructor
/// @param ref a const Entry reference to the object, from which a copy is created
Entry::Entry(const Entry & ref)
{
   this->value = ref.value;
   input = new char[std::strlen(ref.input) + 1];
   message = new char[std::strlen(ref.message) + 1];
   strcpy(input, ref.input);
   strcpy(message, ref.message);
}
//---------------------------------------------------------------------------------------------------------------------
///Assignment operator
/// @param r the reference to the second obj, with with the addition will be performed
Entry & Entry::operator=(const Entry & r)
{
   if(this == &r)
      return *this;
   delete [] input;
   delete [] message;
   this->value = r.value;
   this->input = new char[strlen(r.input) + 1];
   this->message = new char[strlen(r.message) + 1];
   strcpy(message, r.message);
   strcpy(input, r.input);
   return *this;
}
//---------------------------------------------------------------------------------------------------------------------
///function display the information about the Entry class
//
void Entry::show(void) const 
{
   using std::cout, std::endl;
   cout << "\nIncome type: " << this->input;
   cout << "\nMessage: " << message;
   cout << "\nValue: " << value << endl;
}