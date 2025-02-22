#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
  std::set<T> inter;

  typename std::set<T>::iterator it_s1 = s1.begin();
  typename std::set<T>::iterator it_s2 = s2.begin();

  // compare the values of s1 and s2
  while (it_s1 != s1.end() && it_s2 != s2.end()) {
    if (*it_s1 < *it_s2) {
      it_s1++;
    }

    else if (*it_s1 > *it_s2) {
      it_s2++;
    }

    else if (*it_s1 == *it_s2) {
      inter.insert(*it_s1);
      it_s1++;
      it_s2++;
    }

  }

  return inter;
}

template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
std::set<T> unionSet;

typename std::set<T>::iterator it_s1 = s1.begin();
typename std::set<T>::iterator it_s2 = s2.begin();

while (it_s1 != s1.end() && it_s2 != s2.end()) {
  // if iterators vary in value, append
  if (*it_s1 < *it_s2) {
    unionSet.insert(*it_s1);
    it_s1++;
  }

  else if (*it_s2 < *it_s1) {
    unionSet.insert(*it_s2);
    it_s2++;
  }

  // choose one element to append if iterators both point to the same value
  else if (*it_s1 == *it_s2) {
    unionSet.insert(*it_s1);
    it_s1++;
    it_s2++;
  }
}

// append any remaining elements in s1
while (it_s1 != s1.end()) {
  unionSet.insert(*it_s1);
  it_s1++;
}

// append any remaining elements in s2
while ((it_s2) != s2.end()) {
  unionSet.insert(*it_s2);
  it_s2++;
}

return unionSet;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
