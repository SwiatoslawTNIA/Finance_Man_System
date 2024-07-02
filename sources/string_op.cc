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