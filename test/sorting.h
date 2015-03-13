#ifndef SORTING_H
#define SORTING_H

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include"book.h"
#include"date.h"

using namespace std;

bool sortByQuantity(const book &one, const book &two) {return one.quantity>two.quantity;} 
//returns true if the first book has more copies than the second
bool sortByCost(const book &one, const book &two) {return one.ourPrice>two.ourPrice;}
//returns true of the first book is more costly than the second
bool sortByAge(const book &one, const book &two)
{
  bool later=false;
  if (one.added.year>two.added.year)
    later=true;
  else if(one.added.year==two.added.year)
  {
    if (one.added.month>two.added.month)
      later=true;
    else if(one.added.month==two.added.month)
    {
      if (one.added.day>two.added.day)
        later=true;
    }
  }
  return later;
}
//first compares years of books. If they're different, return true. If true, then compare
//months. If different, return true. Else, compare days. Etc.

#endif
