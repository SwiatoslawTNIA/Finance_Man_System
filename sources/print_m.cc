#include "print_m.h"
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
      using namespace std;
      cout << "Welcome to the finance managment system" << endl;
      cout << "What would you like to do? " << endl;
      cout.width(30);
      cout << "\t1.Add income taxes(Type \"add income taxes\")" << endl;
      cout.width(30);
      cout << "\t2.Add expense entries(Type \"add expense entries\")" << endl;
      cout << "\t3.Edit existing entries.(Type \"add existing entries\")" << endl;
      cout << "\t3.Delete entries.(Type \"delete entries\")" << endl;
      cout << "> ";
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
   void wrong_name(void)
   {
      cout << "What would you like to do? " << endl;
      cout.width(30);
      cout << "\t1.Add income taxes(Type \"add income taxes\")" << endl;
      cout.width(30);
      cout << "\t2.Add expense entries(Type \"add expense entries\")" << endl;
      cout << "\t3.Edit existing entries.(Type \"add existing entries\")" << endl;
      cout << "\t3.Delete entries.(Type \"delete entries\")" << endl;
      cout << "> ";
   }
}