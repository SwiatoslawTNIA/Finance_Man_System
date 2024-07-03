//file must be in text mode
#include "manage_entries.h"


void create_file(const char * filename)
{
   std::ofstream obj(filename);
   chmod(filename, 700);//only this app and root can change the files
   obj.close();
}


void add_income_tax(void)
{
   Entry entry = process_input();
   entry.show();
   try
   {
      save_in_file_input(entry);
   }
   catch(std::runtime_error & err)
   {
      create_file("income.json");
      save_in_file_input(entry);
   }
}  

Entry process_input(void) //func has internal linkage
{
   using std::cout, std::cin, std::endl;
   using namespace print;
   system("clear");
   Entry e1;
   clear_cin();
   std::cout << "\t\t\tEnter the income type: (max 150 chars): \n> ";
   char income_type[151];
   while(!cin.get(income_type, 151))//if it encounters new line, then it sets failbit to false
   {
      cout << "\nPlease enter valid input type. Try again!!!\n> ";
      cin.clear();//reset the failbits
      clear_cin();
   }
   clear_cin();
   std::cout << "\t\t\tEnter the income value: \n> ";
   double temp_val = 0.0;
   while(!(cin >> temp_val))
   {
      cout << "\nPlease enter valid input type. Try again!!!\n> ";
      cin.clear();//reset the failbits
      clear_cin();
   }
   clear_cin();
   std::cout << "\t\t\tEnter the income type: (max 500 chars): \n> ";
   char message[501];
   while(!cin.get(message, 501))//if it encounters new line, then it sets failbit to false
   {
      cout << "\nPlease enter valid input type. Try again!!!\n> ";
      cin.clear();//reset the failbits
      clear_cin();
   }
   clear_cin();
   Entry e(income_type, message, temp_val);
   return e;
}
bool save_in_file_input(const Entry & entry)
{
   rapidjson::Document doc;
   doc.SetObject();//create an obj

   //add data to the document:
   rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
   //proper value wrapping:
   rapidjson::Value income_value;
   income_value.SetString(entry.get_input(), allocator);
   doc.AddMember(rapidjson::StringRef("income_type"), income_value, allocator);

   rapidjson::Value message;
   message.SetString(entry.get_message(), allocator);
   doc.AddMember(rapidjson::StringRef("message"), message, allocator);

   doc.AddMember(rapidjson::StringRef("value"), rapidjson::Value(entry.get_value()), allocator);
   //convert to json string:
   rapidjson::StringBuffer buff;
   rapidjson::Writer<rapidjson::StringBuffer>writer(buff);
   doc.Accept(writer);
   std::string jsonstr = buff.GetString();//retrieve the string from the buffer

   //write json string to a file:
   std::fstream obj;
   obj.open("income.json", std::ios_base::in | std::ios_base::out);
   if(obj.is_open())
   {
      obj.seekp(0, std::ios_base::end);//move to the start
      std::streampos pos = obj.tellp();//if the next char is not EOF, the file is not empty
      if(pos == 0)
         obj << "[";
      else
      {
         obj.seekp(-1, std::ios_base::cur);
         obj << "\n,";
      }
      obj << jsonstr << "]";
      std::cout << "Wrote. Terminating.";
   }
   else if(obj.bad())
      throw std::exception();
   else if(obj.fail())//both failbit and badbit is set
    throw std::runtime_error("Unable to write to the income.json obj");

   obj.close();
   return true;
}
//expense methods:

void add_expense_entries(void)
{
   Entry entry = process_expenses();
   try
   {
      save_in_file_expenses(entry);
   }
   catch(std::runtime_error & err)
   {
      std::cout << "The expenses error has been caught.";
      create_file("expenses.json");
      save_in_file_expenses(entry);
   }
}

Entry process_expenses(void) //func has internal linkage
{
   using std::cout, std::cin, std::endl;
   using namespace print;
   system("clear");
   Entry e1;
   clear_cin();
   std::cout << "\t\t\tEnter the expenses type: (max 150 chars): \n> ";
   char expense_type[151];
   while(!cin.get(expense_type, 151))//if it encounters new line, then it sets failbit to false
   {
      cout << "\nPlease enter valid expenses type. Try again!!!\n> ";
      cin.clear();//reset the failbits
      clear_cin();
   }
   clear_cin();
   std::cout << "\t\t\tEnter the expenses value: \n> ";
   double temp_val = 0.0;
   while(!(cin >> temp_val))
   {
      cout << "\nPlease enter valid input type. Try again!!!\n> ";
      cin.clear();//reset the failbits
      clear_cin();
   }
   clear_cin();
   std::cout << "\t\t\tEnter the comment: (max 500 chars): \n> ";
   char message[501];
   while(!cin.get(message, 501))//if it encounters new line, then it sets failbit to false
   {
      cout << "\nPlease enter valid comment. Try again!!!\n> ";
      cin.clear();//reset the failbits
      clear_cin();
   }
   clear_cin();
   Entry e(expense_type, message, temp_val);
   return e;
}

bool save_in_file_expenses(const Entry & entry)
{
   rapidjson::Document doc;
   doc.SetObject();//create an obj

   //add data to the document:
   rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
   //proper value wrapping:
   rapidjson::Value income_value;
   income_value.SetString(entry.get_input(), allocator);
   doc.AddMember(rapidjson::StringRef("exp_type"), income_value, allocator);

   rapidjson::Value message;
   message.SetString(entry.get_message(), allocator);
   doc.AddMember(rapidjson::StringRef("message"), message, allocator);

   doc.AddMember(rapidjson::StringRef("value"), rapidjson::Value(entry.get_value()), allocator);
   //convert to json string:
   rapidjson::StringBuffer buff;
   rapidjson::Writer<rapidjson::StringBuffer>writer(buff);
   doc.Accept(writer);
   std::string jsonstr = buff.GetString();//retrieve the string from the buffer

   //write json string to a file:
   std::fstream obj;
   obj.open("expenses.json", std::ios_base::in | std::ios_base::out);
   if(obj.is_open())
   {
      std::cout << "Opened a json file.";
      obj.seekp(0, std::ios_base::end);//move to the start
      std::streampos pos = obj.tellg();//if the next char is not EOF, the file is not empty
      if(pos == 0)
         obj << "[";
      else
      {
         obj.seekp(-1, std::ios_base::cur);
         obj << ",\n";
      }
      obj << jsonstr << "]";
      std::cout << "Wrote. Terminating.";
   }
   else if(obj.bad())
      throw std::exception();
   else if(obj.fail())//the file doesn't exist
      throw std::runtime_error("Unable to open expenses.json");

   obj.close();
   return true;
}









