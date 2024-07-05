//file must be in text mode
#include "manage_entries.h"


char * entry_name = nullptr;//internal linkage
unsigned int entry_name_length;//is initialized to 0 (SSD)

bool file_is_empty(std::ifstream & s)
{
   return s.peek() == std::ifstream::traits_type::eof();
}
bool file_is_empty(std::fstream & s)
{
   return s.peek() == std::fstream::traits_type::eof();
}


void edit_existing_entries(void)
{
   std::cout << "\tPlease enter the entries type (1 = for income taxes, 2 = expenses):\n> ";
   int n;
   while(!(std::cin >> n) && n != 1 && n != 2)
   {
      std::cout << "\nInvalid Input! Try again:\n> ";
      std::cin.clear();
      print::clear_cin();
   }
   if( n == 1)
   {
      TAXES = 1;
      EXPENSES = 0;
   }
   else if(n == 2)
   {
      EXPENSES  = 1; 
      TAXES = 0;
   }
   (TAXES)? edit_file("income.json"): edit_file("expenses.json");
}

void delete_entry(void)
{
   std::cout << "Please indicate the type of entry to delete: (income tax : 1, expenses: 2)";
   
   int n = 0;
   while(!(std::cin >> n) && n != 1 && n != 2)
   {
      std::cin.clear();
      print::clear_cin();
      std::cout << "\nPlease enter a valid number!";
   }
   (n == 1)? (TAXES = 1,EXPENSES = 0): (EXPENSES = 1, TAXES = 0);
   (TAXES)? delete_from_file("income.json"): delete_from_file("expenses.json");
}


bool delete_from_file(const char *file)
{
   std::fstream obj(file, std::ios_base::in | std::ios_base::out);
   obj.seekp(0);//move to the start
   if(file_is_empty(obj))
   {
      std::cout << "Can not delete from an empty file. Please add data first!!!";
   }

   if(obj.is_open())
   {
      std::ofstream temp_f("temp.json");
      if(!temp_f.is_open())
      {
         std::cerr << "\nCould not create a temp file. Error!";
         throw std::exception();
      }
      print::delete_name();//get the entry_name pointer a value
      bool found = false;
      char buff[1000];
      bool first = false;
      while(obj.getline(buff, 1000, '}') && !found)
      {
         if(search_for_string(buff, entry_name))
            found = true;

         if (first) {
            temp_f << buff << "}";
            first = false;
         } 
         else 
         {
            temp_f << buff << "}";
         }
         if(obj.peek() == ']')
         {
            temp_f << ']';
            break;
         }
      }
      if(found)
      {
         //write the rest of the file to the new file:
         while(obj.getline(buff, 1000, '}'))
         {//while not end of file has been reached
            temp_f << ", " << buff << "}";
         }        
         temp_f << ']';//add the closing bracket
      }
      else
         std::cerr << "The object hasn't been detected! Please ensure that the name is correct.\n";
      temp_f.close();
      obj.clear();
      obj.close();
      if(remove(file) != 0)
         throw std::exception();
      if(rename("temp.json", file) != 0)
         throw std::exception();
      if(found)
         std::cout << "\nYour entry has been successfully stored.\n";
   }
   else if(obj.bad())
      throw std::exception();

   else if(obj.fail())//both failbit and badbit is set
    throw std::runtime_error("Unable to write to the income.json obj");
   //free the global entry_name pointer:
   delete [] entry_name;

   
   return true;
}
//approach: read the whole file, find the location that is needed to be changed, 
   //change the location while reading, store the changes in the temp_file, 
   //delete the real file, rename the temp file to the real one.
bool edit_file(const char *file)
{
   std::fstream obj(file, std::ios_base::in | std::ios_base::out);
   obj.seekp(0);//move to the start
   if(file_is_empty(obj))
   {
      std::cout << "Can not change an empty file. Please add data first!!!";
   }

   if(obj.is_open())
   {
      std::ofstream temp_f("temp.json");
      if(!temp_f.is_open())
      {
         std::cerr << "\nCould not create a temp file. Error!";
         throw std::exception();
      }
      print::get_name();//get the entry_name pointer a value
      bool found = false;
      char buff[1000];
      bool first = false;
      while(obj.getline(buff, 1000, '}') && !found)
      {
         if(search_for_string(buff, entry_name))
         {
            found = true;
            break;
         }

         temp_f << buff << '}';
         if(obj.peek() == ']')
            break;
      }
      if(found)
      {
         Entry e = (EXPENSES)? process_expenses(): process_input();
         store_in_file(e, temp_f); 
         while (obj.getline(buff, 1000, '}')) 
         {
            if(!obj.eof())
               temp_f << buff << "}";
            else
               temp_f << buff;//without the last }
         }   
      }
      else
         std::cerr << "The object hasn't been detected! Please ensure that the name is correct.\n";
   
      if(remove(file) != 0)
         throw std::exception();
      if(rename("temp.json", file) != 0)
         throw std::exception();
      if(found)
         std::cout << "\nYour entry has been successfully stored.\n";
   }
   else if(obj.bad())
      throw std::exception();

   else if(obj.fail())//both failbit and badbit is set
    throw std::runtime_error("Unable to write to the income.json obj");
   //free the global entry_name pointer:
   delete [] entry_name;

   obj.clear();
   obj.close();
   return true;
}  
void create_file(const char * filename)
{
   std::ofstream obj(filename);
   // chmod(filename, 700);//only this app and root can change the files
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
      obj.seekp(0, std::ios_base::end);
      std::streampos pos = obj.tellp();
      if(pos == 0)
         obj << "[";
      else
      {
         obj.seekp(-1, std::ios_base::cur);
         obj << "\n,";
      }
      obj << jsonstr << "]";
   }
   else if(obj.bad())
      throw std::exception();
   else if(obj.fail())//both failbit and badbit is set
    throw std::runtime_error("Unable to write to the income.json obj");

   obj.close();
   return true;
}
//expense methods:
bool store_in_file(const Entry & entry, std::ofstream & obj)
{
   rapidjson::Document doc;
   doc.SetObject();//create an obj
   //add data to the document:
   rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
   //proper value wrapping:
   rapidjson::Value income_value;
   income_value.SetString(entry.get_input(), allocator);
   if(EXPENSES)
   {
      doc.AddMember(rapidjson::StringRef("exp_type"), income_value, allocator);
   }
   else
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
   std::cout << jsonstr;
   if(obj.tellp() == 0)//if it is the first object
   {
      obj << '[' << jsonstr;
   }
   else 
      obj << ",\n" << jsonstr;//add the closing bracket
   return true;
}


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
      obj.seekp(0, std::ios_base::end);//
      std::streampos pos = obj.tellg();//
      if(pos == 0)
         obj << "[";
      else
      {
         obj.seekp(-1, std::ios_base::cur);
         obj << ",\n";
      }
      obj << jsonstr << "]";
   }
   else if(obj.bad())
      throw std::exception();
   else if(obj.fail())//the file doesn't exist
      throw std::runtime_error("Unable to open expenses.json");

   obj.close();
   return true;
}

bool display_all(void)
{
   std::ifstream obj("income.json", std::ios_base::in);//string for the data
   //display information in the file income.json:
   process_print(obj, "Income");
   //display information in the file expenses.json:
   obj.open("expenses.json");
   process_print(obj, "Expenses");
   return true;
}






