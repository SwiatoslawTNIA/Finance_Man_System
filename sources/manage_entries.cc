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
   
   if(TAXES)
      edit_file("income.json");
   else if(EXPENSES)
      edit_file("expenses.json");

}

bool edit_file(const char *file)
{
   //approach: read the whole file, find the location that is needed to be changed, 
   //change the location while reading, and then restore the rest of the file.
   //I'd need to copy a file to a temp location, since when reading & writing simultaneously
   //i can overwrite the existing data(when I add new data thus increasing the total length)
   std::fstream obj(file, std::ios_base::in | std::ios_base::out);
   if(file_is_empty(obj))
   {
      std::cout << "Can not change an empty file. Please add data first!!!";
   }
   //check if the file is empty:
   if(obj.is_open())
   {
      obj.seekp(0, std::ios_base::end);//move to the start
      //create a temp file, store the data there, while storing, change
      std::ofstream temp_f("temp.txt", std::ios_base::out | std::ios_base::app);
      if(!temp_f.is_open())
      {
         std::cerr << "\nCould not create a temp file. Error!";
         throw std::exception();
      }
      //search for the entry:
      if(entry_name == nullptr)
         print::get_name();//get the entry_name pointer a value

      char c;
      bool open_bracket = false, found = true;
      unsigned int index = 0;

      while(obj.get(c) && !found)//while we can read, if EOF, then eofbit is set, obj.get is false
      {//the pattern: "name":
         if(c == '\"' && open_bracket == false)
            open_bracket = true;
         if(open_bracket == true)
         {//check if the strings match:
            while((c = obj.get()) == entry_name[index])
            {
               ++index;
               continue;
            }
            //if the the strings match, then index = entry_name_length -1
            if(entry_name_length - 1 == index && (c = obj.get()) == '\"')
            {
               found = true;
               break;
            }
            else
            {
               open_bracket = found = false;
               index = 0;
               //if the strings doesn't match, then we write the chars that did match:
               for(unsigned int i = 0; i < index; ++i)
               {
                  temp_f << entry_name[i];//store in the temp file the part that matched
               }
               temp_f  << c;//store the character that did not match(while loop above)
            }
         }
         temp_f << c;//write chars that we read;
      }
      if(found)
      {
         Entry e;
         if(EXPENSES)
         {
            e = process_expenses();
            store_in_file(e, temp_f);
         }
         else 
         {
            e = process_input();
            store_in_file(e, temp_f);
         }
         
      }
      else
      {
         std::cout << "The object hasn't been detected! Please ensure that the name is correct.";
      }
   }
   else if(obj.bad())
      throw std::exception();
   else if(obj.fail())//both failbit and badbit is set
    throw std::runtime_error("Unable to write to the income.json obj");

   obj.clear();
   obj.close();

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
   obj << jsonstr;
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






