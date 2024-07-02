//---------------------------------------------------------------------------------------------------------------------
// c++.cc
//
// <Finance managment system>
// Manages Add, edit, and delete income and expense entries.
// Categorize expenses (e.g., food, transport, entertainment).
// Generate reports and summaries for different time periods.
// Save and load data from a file.

//
//---------------------------------------------------------------------------------------------------------------------
//


#include "c++.h"

//---------------------------------------------------------------------------------------------------------------------
///
/// @param numbers an array to check
/// @param length The length of the array. If this text is too long you can
///
/// @return the highest number
//
int main(void)
{
  using namespace std;
  initialize();

  Entry entry1("Something", "Anty", 22.3), entry2;
  entry2 = entry1;

  
  return 0;
}
void initialize(void)
{
  char buff[100];
  bool wrong_input = true;
  print::print_welcome();
  while(wrong_input)
  {
    wrong_input = true;
    wrong_input = !std::cin.getline(buff, 100);
    
    //reset the wrong input;
    //since cin inherits from ios_base and ios_base class has a bool template overloading, 
    //we can cast the cin class to bool type
    if(same_strings(buff, arr_input[0]))
    {
      add_income_tax();
    }
    else if(same_strings(buff, arr_input[1]))
    {
      // add_expense_entries();
    } 
    else if(same_strings(buff, arr_input[2]))
    {
       //edit_entry();
    }
    else if(same_strings(buff, arr_input[3]))
    {
      //delete entry();
    }
    else
      wrong_input = true;
    {
      std::cin.clear();//reset the failed bits
      print::clear_cin();
      std::cout << "\nPlease try again!!";
      continue;//try next input
    }
  };
}

