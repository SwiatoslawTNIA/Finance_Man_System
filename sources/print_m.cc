#include "print_m.h"

extern char *entry_name;
extern unsigned int entry_name_length;
namespace  print
{
   using std::cout, std::cin, std::endl;
   //---------------------------------------------------------------------------------------------------------------------
   ///the func prints the initial messages
   ///
   /// @return void
   //
   void print_welcome(void)
   {

      cout << "What would you like to do? " << endl;
      cout.width(30);
      cout << "\t1.Add income taxes(Type \"add income taxes\")" << endl;
      cout.width(30);
      cout << "\t2.Add expense entries(Type \"add expense entries\")" << endl;
      cout << "\t3.Edit existing entries.(Type \"edit existing entries\")" << endl;
      cout << "\t4.Delete entries.(Type \"delete entries\")" << endl;
      cout << "\t5.Quit(Type \"quit\")" << endl;
      cout << "\t6.Display entry(Type \"display entry\")" << endl;
      cout << "> ";
   }
   void error_message(void)
   {
      cout << "Please try again!\n> " << std::flush;
   }
   //---------------------------------------------------------------------------------------------------------------------
   ///the func clears the input buffer
   ///
   /// @return void
   //
   void clear_cin(void)
   {
       while(std::cin.get() != '\n')
         continue;
   }

   void get_name(void)
   {
      clear_cin();
      std::cout << "\nPlease enter the name of the entry(max 150 chars): \n> ";
      char buff[151];
      while(!(cin.get(buff, 151)))
      {
         cout << "\nPlease try again!!!";
         cin.clear();//clear the error bits
         print::clear_cin();
      }
      entry_name = new char[strlen(buff) + 1];
      strcpy(entry_name, buff);
      entry_name_length = strlen(entry_name);
   }
}