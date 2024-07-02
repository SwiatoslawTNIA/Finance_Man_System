#include "entry.h"


Entry::Entry(const char *st, const char *str2,  double val): value(val)
{
   income_type = new char[strlen(st) + 1];
   message = new char[strlen(str2) + 1];
   strcpy(message, str2);
   strcpy(income_type, st);
}

Entry::~Entry()
{
   if(income_type != nullptr)
      delete [] income_type;
   if(message != nullptr)
      delete [] message;
}

Entry::Entry(const Entry & ref)
{
   this->value = ref.value;
   income_type = new char[std::strlen(ref.income_type) + 1];
   message = new char[std::strlen(ref.message) + 1];
   strcpy(income_type, ref.income_type);
   strcpy(message, ref.message);
}

Entry & Entry::operator=(const Entry & r)
{
   if(this == &r)
      return *this;
   delete [] income_type;
   delete [] message;
   this->value = r.value;
   this->income_type = new char[strlen(r.income_type) + 1];
   this->message = new char[strlen(r.message) + 1];
   strcpy(message, r.message);
   strcpy(income_type, r.income_type);
   return *this;
}

void Entry::show(void) const 
{
   using std::cout, std::endl;
   cout << "\nIncome type: " << this->income_type;
   cout << "\nMessage: " << message;
   cout << "\nValue: " << value << endl;
}