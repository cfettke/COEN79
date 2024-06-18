
#include <stdlib.h>
#include "mystring.h"
#include <string.h>
#include <assert.h>
using namespace std;
using namespace coen79_lab5;




namespace coen79_lab5
{  

  string::string(const char str[])
  {
      current_length = strlen(str);
      characters = new char[current_length + 1];
      strcpy(characters, str);
  }

  string::string(char c)
  {
      current_length = 1;
      characters = new char[current_length + 1];
      characters[0] = c;
      characters[1] = '\0';
  }

  string::string(const string &source)
  {
      current_length = source.current_length;
      characters = new char[source.allocated];
      strcpy(characters, source.characters);
  }

  string::~string()
  {
      delete[] characters;
  }


  void string::operator+=(const string &addend)
  {
      reserve(addend.current_length + current_length + 1);
      strncat(characters, addend.characters, addend.current_length);
      current_length += addend.current_length;
  }

  void string::operator+=(const char addend[])
  {
      reserve(current_length + strlen(addend) + 1);
      strncat(characters, addend, strlen(addend));
      current_length += strlen(addend);
  }

  void string::operator+=(char addend)
  {
      reserve(current_length + 2);
      characters[current_length] = addend;
      characters[current_length + 1] = '\0';
      current_length++;
  }

  void string::reserve(size_t n)
  {
      if (n > allocated)
      {
          char *char_space = new char[n];
          strncpy(char_space, characters, current_length + 1);
          delete[] characters;
          characters = char_space;
          allocated = n;
      }
  }

  string &string::operator=(const string &source)
  {
      if (this == &source)
      {
          return * this;
      }
      reserve(source.current_length + 1);
      strncpy(characters, source.characters, source.current_length + 1);
      current_length = source.current_length;
      return * this;
  }

  void string::insert(const string &source, unsigned int position)
  {
      assert(position <= current_length);
      reserve(current_length + source.current_length + 1);
      for (size_t i = current_length; i > position; --i)
      {
          characters[i + source.current_length - 1] = characters[i - 1];
      }
      strncpy(characters + position, source.characters, source.current_length);
      current_length += source.current_length;
      characters[current_length] = '\0';
  }

  void string::dlt(unsigned int position, unsigned int num)
  {
      assert(position + num <= current_length);
      for (size_t i = position; i < current_length - num; ++i)
      {
          characters[i] = characters[i + num];
      }
      current_length = current_length - num;
      characters[current_length] = '\0';
  }

  void string::replace(char c, unsigned int position)
  {
      assert(position < current_length);
      characters[position] = c;
  }
  void string::replace(const string &source, unsigned int position)
  {
      assert(position + source.current_length <= current_length);
      strncpy(characters + position, source.characters, source.current_length);
  }
  char string::operator[](size_t position) const
  {
      assert(position < length());
      return characters[position];
  }

  int string::search(char c) const
  {
      for (size_t i = 0; i < length(); i++)
      {
          if (characters[i] == c)
              return i;
      }
      return -1;
  }


  int string::search(const string &substring) const
  {
      for (size_t i = 0; i <= length() - substring.length(); i++)
      {
          bool flag = true;
          for (size_t j = 0; j < substring.length(); j++)
          {
              if (characters[i + j] != substring.characters[j])
              {
                  flag = false;
                  break;
              }
          }
          if (flag == true)
              return i;
      }
      return -1;
  }

                                                  
  unsigned int string::count(char c) const
  {
      int count = 0;
      for (size_t i = 0; i < length(); i++)
      {
          if (characters[i] == c)
              count++;
      }
      return count;
  }
                                
  std::ostream &operator<<(std::ostream &outs, const string &source)
  {
      outs << source.characters;
      return outs;
  }


  bool operator==(const string &s1, const string &s2)
  {
      return (strncmp(s1.characters, s2.characters, s1.length() + 1) == 0);
  }


  bool operator!=(const string &s1, const string &s2)
  {
      return (strncmp(s1.characters, s2.characters, s1.length() + 1) != 0);
  }


  bool operator>(const string &s1, const string &s2)
  {
      return (strncmp(s1.characters, s2.characters, s1.length() + 1) > 0);
  }


  bool operator < (const string &s1, const string &s2)
  {
      return (strncmp(s1.characters, s2.characters, s1.length() + 1) < 0);
  }

  bool operator>=(const string &s1, const string &s2)
  {
      return (strncmp(s1.characters, s2.characters, s1.length() + 1) >= 0);
  }

  bool operator<=(const string &s1, const string &s2)
  {
      return (strncmp(s1.characters, s2.characters, s1.length() + 1) <= 0);
  }

  string operator+(const string &s1, const string &s2)
  {
      string stringAdd;
      stringAdd += s1;
      stringAdd += s2;
      return stringAdd;
  }

  string operator+(const string &s1, const char addend[])
  {
      string stringAdd;
      stringAdd += s1;
      stringAdd += addend;
      return stringAdd;
  }

  std::istream &operator>>(std::istream &ins, string &target)
  {
      char stringIn;
      while (!ins.eof() && isspace(ins.peek())) {}
      target = "";
      while (!ins.eof() && !isspace(ins.peek()))
      {
          ins >> stringIn;
          target += stringIn;
      }




      return ins;
  }
}




