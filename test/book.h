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
    string ISBN;
    int quantity;
    date added;
    float ourPrice,theirPrice;

    book() {n++;};//memory allocation constructor
    
    //Book constructor; title,author,publisher,wholesale,retail,isbn,date,quantity 
    book(string titlein,string authorin,string publisherin,float wholesaleIs,float retailIs, string isbnin,date addedin,int quantityin);//

    vector<book> read(ifstream &source);
    vector<book> remove(vector<book>, int allocate, int location);
    friend void save(vector<book>&,int,string);
};

int book::n=0; //Intitializes static counter in book class to zero
 
//Book constructor function
book::book(string titlein,string authorin,string publisherin,float ourPriceIs,float theirPriceIs,string isbnin,date addedin,int quantityin){ 
    title=titlein;
    author=authorin;
    publisher=publisherin;
    ourPrice=ourPriceIs;
    theirPrice=theirPriceIs;
    ISBN=isbnin;
    added=addedin;
    quantity+=quantityin;
    n++;
};

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

// To Display the Details of a book:
void displayBook(book disBook)
{
        cout << "###############################################\n";
	cout << "  ISBN        :   " << disBook.ISBN << endl;
	cout << "  TITLE       :   " << disBook.title << endl;
	cout << "  AUTHOR      :   " << disBook.author << endl;
	cout << "  PUBLISHER   :   " << disBook.publisher << endl;
	cout << "  QUANTITY    :   " << disBook.quantity << endl;
	cout << "  WHOLESALE   :   $" << setprecision(2) << fixed << disBook.ourPrice << endl;
	cout << "  RETAIL      :   $" << setprecision(2) << fixed << disBook.theirPrice << endl;
	cout << "  DATE ADDED  :   " << disBook.added.month << "/" << disBook.added.day << "/";
	cout << disBook.added.year << endl;
        cout << "###############################################\n";
};

// To Display the Itemized Details of a book:
void displayItmzBook(book disBook)
{
        cout << "###############################################\n";
	cout << " a. ISBN        :   " << disBook.ISBN << endl;
	cout << " b. TITLE       :   " << disBook.title << endl;
	cout << " c. AUTHOR      :   " << disBook.author << endl;
	cout << " d. PUBLISHER   :   " << disBook.publisher << endl;
	cout << " e. QUANTITY    :   " << disBook.quantity << endl;
	cout << " f. WHOLESALE   :   $" << setprecision(2) << fixed << disBook.ourPrice << endl;
	cout << " g. RETAIL      :   $" << setprecision(2) << fixed << disBook.theirPrice << endl;
	cout << " h. DATE ADDED  :   " << disBook.added.month << "/" << disBook.added.day << "/";
	cout << disBook.added.year << endl;
        cout << "###############################################\n";
};

#endif
