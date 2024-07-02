//file must be in text mode
#include "manage_entries.h"


void add_income_tax(void)
{
   //process the input
   //store the structure in the file
   Entry new_entry = process_input();
   new_entry.show();
   if(!save_in_file(new_entry))
   {
      std::cout << "Sorry, could not save the data in file. Please try again!!!";
      //throw exception
   }

}  



Entry process_input(void) //func has internal linkage
{
   using std::cout, std::cin, std::endl;
   using namespace print;
   system("clear");
   Entry e1;
   std::cout << "\t\t\t\tEnter the income type: (max 150 chars): \n> ";
   char income_type[151];
   while(!cin.get(income_type, 151))//if it encounters new line, then it sets failbit to false
   {
      cout << "\nPlease enter valid input type. Try again!!!\n> ";
      cin.clear();//reset the failbits
      clear_cin();
   }
   clear_cin();
   system("clear");

   std::cout << "\t\t\t\tEnter the income value: \n> ";
   double temp_val = 0.0;
   while(!(cin >> temp_val))
   {
      cout << "\nPlease enter valid input type. Try again!!!\n> ";
      cin.clear();//reset the failbits
      clear_cin();
   }
   clear_cin();
   system("clear");
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
bool save_in_file(const Entry & entry)
{
   rapidjson::Document doc;
   doc.SetObject();//create an obj

   //add data to the document:
   rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
   //proper value wrapping:
   rapidjson::Value income_value;
   income_value.SetString(entry.get_income(), allocator);
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
   std::ofstream obj;
   obj.open("data.json", std::ios_base::out |std::ios_base::in);
   if(obj.is_open())
   {
      std::cout << "Opened a json file.";
      //move to the end position:
      obj.seekp(0, std::ios_base::end);
      //if file is empty, we don't add a comma, otherwise we do:
      if(obj.tellp() != 0)
         obj << ",";
      obj << jsonstr;//write
      std::cout << "Wrote. Terminating.";
   }
   else if(obj.bad())
   {
      throw std::exception();
      std::cout << "Bad bit set.";
   }
   else if(obj.fail())//both failbit and badbit is set
   {
      throw std::exception();
   }
   //store the information to the file:

   obj.clear();
   obj.close();
   return true;
}


