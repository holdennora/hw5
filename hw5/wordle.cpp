#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void generateCombos(const string& prefix, const string& in, map<char, int> floatingCount, size_t index, 
                   set<string>& validWords, const set<string>& dict, const int dashCount, const string& floating);

bool isValid(const string& word, const set<string>& dict);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<string> validWords;
    map<char, int> floatingCount;
    for(size_t i = 0; i < floating.length(); i++)
    {
      char c = floating[i];
      floatingCount[c]++;
    }

    int dashCount = 0;
    for(size_t i = 0; i < in.size(); i++)
    {
      if(in[i] == '-')
      {
        dashCount++;
      }
    }

    generateCombos("", in, floatingCount, 0, validWords, dict, dashCount, floating);
    return validWords;

}

// Define any helper functions here
void generateCombos(const string& prefix, const string& in, map<char, int> floatingCount, size_t index,
                     set<string>& validWords, const set<string>& dict, const int dashCount, const string& floating)
{
  string newFloating = floating;
  //Base Case
  if(index == in.size())
  {
    if(isValid(prefix, dict))
    {
      validWords.insert(prefix);
    }
    return;
  }

  // A character exists at index
  if(in[index] != '-')
  {
    generateCombos(prefix + in[index], in, floatingCount, index + 1, validWords, dict, dashCount, newFloating);
  }
  // A character does not exists at index
  else
  {
    if(dashCount > newFloating.length())
    {
      for(char c = 'a'; c <= 'z'; ++c)
      {
        newFloating = floating;
        size_t findIndex = newFloating.find(c);
        if(findIndex != string::npos)
        {
          newFloating.erase(newFloating.begin() + findIndex);
        }
        generateCombos(prefix + c, in, floatingCount, index+1, validWords, dict, dashCount-1, newFloating);
        
      }
    }
    else
    {
      for(unsigned int z = 0; z < newFloating.length(); z++)
      {
        newFloating = floating;

        char add = newFloating[z];
        newFloating.erase(newFloating.begin() + z );
        
        generateCombos(prefix + add, in, floatingCount, index+1, validWords, dict, dashCount-1, newFloating);
      }
    }
  }
}

bool isValid(const string& word, const set<string>& dict)
{
  return dict.find(word) != dict.end();
}
