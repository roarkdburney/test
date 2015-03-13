#ifndef BOOK_H
#define BOOK_H

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include"date.h"

using namespace std;

class book
{
  public:
    static int n; //A counter to keep track of how many book objects have been created
    string title,author,publisher;
    int ISBN;
    int quantity;
    date added;
    float ourPrice,theirPrice;

    book() {n++;};//memory allocation constructor
    
    //Book constructor; title,author,publisher,wholesale,retail,isbn,date,quantity 
    book(string titlein,string authorin,string publisherin,float wholesaleIs,float retailIs,float isbnin,date addedin,int quantityin);//

    vector<book> read(ifstream &source);
    vector<book> remove(vector<book>, int allocate, int location);
};

int book::n=0; //Intitializes static counter in book class to zero

void save(vector<book>& inventory, int allocate, string path)
{
  ofstream output;
  output.open(path);
  output<<allocate<<",,,,,,,"<<endl<<"ISBN,TITLE,AUTHOR,PUBLISHER,Date Added,Quantity On Hand,Wholesale Price,Retail" <<endl;
  for (int x=0; x<allocate; x++) 
  {
    output<<inventory[x].ISBN<<',';
    output<<inventory[x].title<<',';
    output<<inventory[x].author<<',';
    output<<inventory[x].publisher<<',';
    output<<inventory[x].added.month<<'/'<<inventory[x].added.day<<'/'<<inventory[x].added.year<<',';
    output<<inventory[x].quantity<<','<<inventory[x].ourPrice<<','<<inventory[x].theirPrice<<endl;
    
  }
    output.close();
};

#endif
