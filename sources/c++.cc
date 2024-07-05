//---------------------------------------------------------------------------------------------------------------------
// c++.cc
//
// <Finance managment system>
// Manages Add, edit, and delete income and expense entries.
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
  try
  {
    initialize();
  }
  catch(std::exception & r)
  {
    cout << "Problem: " << r.what();
  }
  Entry entry1("Something", "Anty", 22.3), entry2;
  entry2 = entry1;
  return 0;
}
void initialize(void)
{
  std::cout << "Welcome to the finance managment system" << std::endl;
  char buff[DEF_BUFF_SIZE];
  while(true)//always run the loop
  {
    print::print_welcome();
    bool correct_input = (bool)std::cin.get(buff, DEF_BUFF_SIZE), correct_value = true;//reset the wrong input;
    //since cin inherits from ios_base and ios_base class has a bool template overloading, 
    //we can cast the cin class to bool type
    
    if(same_strings(buff, arr_input[0]))
    {
      add_income_tax();
    }
    else if(same_strings(buff, arr_input[1]))
    {
      add_expense_entries();
    } 
    else if(same_strings(buff, arr_input[2]))
    {
      edit_existing_entries();
    }
    else if(same_strings(buff, arr_input[3]))
    {
      delete_entry();
    }
    else if(same_strings(buff, arr_input[4]))
      display_all();
    else if(same_strings(buff, "quit") || same_strings(buff, "exit"))
      break;//quit
    else if(same_strings(buff, "clear"))
      system("clear");
    else
      correct_value = false;//set the input to false
    if(!(correct_value && correct_input))
    {
      std::cin.clear();//clera the failbits
      print::error_message();
    }
    print::clear_cin();
  };
}

