#include "string_op.h"

//---------------------------------------------------------------------------------------------------------------------
///The function trims every whitespace char (including \n)
/// @param s1 the first string ffor trimming
///
/// @return void
//
void trim( char * arr)
{
   if(arr == nullptr)
      return;
  size_t i = 0, j = 0;
  while(arr[i] != '\0')
  {
    if(isspace(arr[i]))
    {
      arr[j] = arr[i + 1];
    }
    else
      j++;
    i++;
  }
  arr[j] = '\0';
}
//---------------------------------------------------------------------------------------------------------------------
///The function compares two strings, if nonchars are encountered in each string, 
///they are skiped, case insensitive
/// @param s1 the first string for comparison
/// @param s2 the second string for comparison
///
/// @return the highest number
//
bool same_strings(const char * s1, const char *s2)
{
  if((s1 == nullptr && s2 != nullptr )||( s2 == nullptr && s1 != nullptr))
    return false;
  if(s1 == nullptr && s2 == nullptr)
    return true;

  while(*s1 != '\0' || *s2 != '\0')//the terminate when both reach \0
  {
    if(*s1 != '\0' && !isalpha(*s1)) s1++;//get rid of on nonchar 
    
    if(*s2 != '\0' && !isalpha(*s2)) s2++;

    if(*s1 == '\0' && *s2 == '\0')
      return true;

    if(tolower(*s1) != tolower(*s2))
      return false;

    ++s1;
    ++s2;
  }
  return true;
}

bool process_print(std::ifstream & obj, const char *header_n)
{
  using std::cout, std::endl;//for output
  if(obj.is_open())
   {
      //check if the file is empty, if it is not empty, then display the message, otherwise quit:
      if(obj.peek() == std::ifstream::traits_type::eof())//if eof is the next char
      {
         cout << "\nThere is no information about the " << header_n 
         << ", you have to write data first!!!\n\n";
         obj.clear();
         obj.close();
         return true;//exit
      }
      std::cout << "\n----------------------------------------Displaying " << 
      header_n << ":---------------------"
      << "----------------------------\n";
      while(!obj.eof())
      {
         char c;
         while((c = obj.get()) != ':')
            continue;//move to the first entry
         obj.get();//get the "\"" char
         std::cout << header_n << ":  ";

         while((c = obj.get()) != '\"')
            cout << c;
         std::cout << "\n";

         //second entry:
         while((c = obj.get()) != ':')
            continue;//move to the message entry
         obj.get();//get the "

         char comment[501];//store the message(value will be displayed first)
         int index = 0;
         while((c = obj.get()) != '\"')
            comment[index++] = c;
         comment[index] = '\0';
         //third entry:
         while((c = obj.get()) != ':')
            continue;//move to the message entry

         std::cout << "Value: \t ";
         while((c = obj.get()) != '}')
            cout << c;
         
         index = 0;
         cout << endl << "Comment: ";
         while(comment[index] != '\0')//
            cout << comment[index++];

         std::cout << endl << "-------------------------------------------------------------------------"
         << "---------------------------------\n";
         //we can encounter ]
         if((c = obj.get()) == ']')//if we encouter the end of array, we exit
         {
            cout << endl;//flush the buffer + new_line
            break;//exit the loop;
         }
      }
   }
   else if(obj.bad())
      throw std::logic_error("Unfortunately could not access the file.");
   else if(obj.fail())
      throw std::exception();
   obj.clear();
   obj.close();
   return true;
}
