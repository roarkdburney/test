//Copyright Chrysanthemum Industries
// Roarke Burney, Zachary Prince
// Abdollah Kasraie, Chris Yu 

#include<iostream>
#include<iomanip>
#include<fstream>
#include<string> // Needed for string operations
#include<vector> // Needed for vectors
#include<algorithm> // Needed for sort function
#include"book.h"
#include"date.h"
#include"sorting.h"

using namespace std;

string filepath="Inventory.csv";

void report_message()
{
  cout << "The book list will be given in the following format: \n\n";
  cout << "ISBN        :\n";
  cout << "TITLE       :\n";
  cout << "AUTHOR      :\n";
  cout << "PUBLISHER   :\n";
  cout << "QUANTITY    :\n";
  cout << "DATE ADDED  :\n";
  cout << "\nPress any key to continue.\n";
  cin.get();cin.get(); //Mac equivalent of doing "system("Pause")"
}

void cashier() //Cashier module
{
}

void inventory(vector<book>& pink) //Inventory module
{
  int choice, book_to_delete,c=0;
  char choice_2;
  string choice_3;
  while (1)
  {
    cout << endl;
    cout << "       Welcome to the inventory module.     " << endl;
    cout << "      What would you like to accomplish?    " << endl;
    cout << "###############################################\n";
    cout << "# 1: Add a book                               #\n";
    cout << "# 2: Remove a book                            #\n";
    cout << "# 3: Edit a book                              #\n";
    cout << "# 4: Save current inventory to disk           #\n";
    cout << "# 5: Return to Main Menu                      #\n";
    cout << "###############################################\n";
    cin >> choice;
    cout << endl;

    if (choice==1) //Adding a book
    {
      string title,author,publisher;
      int ISBN,quantity;
      date added;
      float ourPrice,theirPrice;
      
      //Prompting user for book info
      cout << "First, enter in this book's ISBN number: ";
      cin >> ISBN;
      cout << endl << "Now, its title: ";
      cin >> title;
      cout << endl << "Author: ";
      cin >> author;
      cout << endl << "Publisher: "; 
      cin >> publisher;
      cout << endl << "Quantity on hand: ";
      cin >> quantity;
      cout << endl << "Wholesale price: ";
      cin >> ourPrice;
      cout << endl << "Retail price: ";
      cin >> theirPrice;
      cout << endl << "Year added to inventory: ";
      cin >> added.year;
      cout << endl << "Month added to inventory: ";
      cin >> added.month;
      cout << endl << "Day added to inventory: ";
      cin >> added.day;

      //Creating new book object with the above info
      book blue(title,author,publisher,ourPrice,theirPrice,ISBN,added,quantity);
      
      //Pushing object into vector of books
      pink.push_back(blue);
    }
    else if (choice==2) //Deleting a book
    {
      for (int a=0;a<book::n;a+=10)
      {
        cout << endl;
        cout << "###############################################\n";
        cout << "Now displaying books " << a << " through " << (a+9) << endl;
        cout << "If the book you wish to delete is listed here," << endl;
        cout << "type 'delete'. Otherwise, type 'next' for the" << endl;
        cout << "next selection of books. To exit, type 'exit'.\n";
        cout << "###############################################\n";
        cout << endl;
        for (int b=0; b<10; b++)
        {
          cout << c << ": " << pink[c].title << endl;
          c++;
        }
        cout << endl;
        cout << "Choice: ";
        cin >> choice_3;

        if (choice_3=="delete")
        {
          cout << "###############################################\n";
          cout << "#  Enter in the integer number corresponding  #\n";
          cout << "#    to the book that you wish to delete.     #\n";
          cout << "###############################################\n";
          cin >> book_to_delete;

          if (book_to_delete>-1&&book_to_delete<book::n)
          {
            pink.erase(pink.begin()+book_to_delete); //Clear desired book from vector
            cout << endl;
            cout << "###############################################\n";
            cout << "# All data relating to said book has been     #\n";
            cout << "# removed. (Remember to save your changes.)   #\n";
            cout << "###############################################\n";
            cout << endl; 
            c=0; //Reset counter to zero
            break;
          }
          else
          {
            cout << "Invalid selection. Returning to main menu...\n";
            break;
          }
        }
        else if (choice_3=="exit")
          break;
        else if (choice_3=="next")
          continue;
        else
          cout << "Invalid choice. Continuing...\n";
      }
      cout << endl;
      cout << "###############################################\n";
      cout << "# End of list reached. Exiting to main menu...#\n";
      cout << "###############################################\n";
    }
    else if (choice==4) // Implement save function here
    {
      cout << "###############################################\n";
      cout << "# Saving...                                   #\n";
      save(pink,book::n,filepath); //Saves vectors to file
      cout << "# Saved!                                      #\n";
      cout << "###############################################\n";
      cout << endl;
    }
    else if (choice==3) // Implement search and editing of vectors here
    {
    }
    else if (choice==5) // Quits inventory module
      break;
    else
    {
      cout << "Invalid entry. Try again?\n";
      cout << "('Y' key for yes; any other key to exit.)\n";
      cin >> choice_2;
      if(choice_2=='Y')
        continue;
      else
        break;
    }
  }
}

void reports(vector<book>& pink) // Report module 
{
  int choice;
  char choice_2;
  float total_wholesale=0;
  float total_retail=0;
  vector<int> dates_to_sort(book::n);

  while(1)
  {
    cout << "\n        Welcome to the report module.\n";
    cout << "What kind of report would you like to generate?\n";
    cout << "###############################################\n";
    cout << "# 1: Inventory List                           #\n";
    cout << "# 2: Sort and list by Quantity                #\n";
    cout << "# 3: Sort and list by Cost                    #\n";
    cout << "# 4: Sort and list by Age                     #\n";
    cout << "# 5: Return to Main Menu                      #\n";
    cout << "###############################################\n";
    cin >> choice;
    cout << endl;

    if (choice==1) // list
    {
      report_message();
      for (int a=0; a<book::n; a++)
      {
        cout << "ISBN        :   " << pink[a].ISBN << endl;
        cout << "TITLE       :   " << pink[a].title << endl;
        cout << "AUTHOR      :   " << pink[a].author << endl;
        cout << "PUBLISHER   :   " << pink[a].publisher << endl;
        cout << "QUANTITY    :   " << pink[a].quantity << endl;
        cout << "WHOLESALE   :   $" << pink[a].ourPrice << endl;
        cout << "RETAIL      :   $" << pink[a].theirPrice << endl;
        cout << "DATE ADDED  :   " << pink[a].added.month << "/" << pink[a].added.day << "/";
        cout << pink[a].added.year << endl;
        cout << endl;

        //Keep running totals of wholesale and retail prices for the report
        total_wholesale+=pink[a].ourPrice; 
        total_retail+=pink[a].theirPrice;
      }
      cout << "TOTAL WHOLESALE VALUE  :  $" << total_wholesale << endl;
      cout << "TOTAL RETAIL VALUE     :  $" << total_retail << endl;
      total_wholesale=0;
      total_retail=0; //reset for next invocation
    }
    
    else if (choice==2) // quantity
    {
      report_message();
      cout << "Press enter to step through each book.\n";
      cout << endl;
      sort(pink.begin(),pink.end(),sortByQuantity); //sorts vector by quantity
      for (int b=0; b<book::n; b++)
      {
        cout << "ISBN        :   " << pink[b].ISBN << endl;
        cout << "TITLE       :   " << pink[b].title << endl;
        cout << "AUTHOR      :   " << pink[b].author << endl;
        cout << "PUBLISHER   :   " << pink[b].publisher << endl;
        cout << "QUANTITY    :   " << pink[b].quantity << endl;
        cout << "WHOLESALE   :   $" << pink[b].ourPrice << endl;
        cout << "RETAIL      :   $" << pink[b].theirPrice << endl;
        cout << "DATE ADDED  :   " << pink[b].added.month << "/" << pink[b].added.day << "/";
        cout << pink[b].added.year << endl;
        cout << endl;
        getchar();
      }
    }

    else if (choice==3) // cost
    {
      cout << "Press enter to step through each book.\n";
      cout << endl;
      sort(pink.begin(),pink.end(),sortByCost); //sorts vector by cost
      for (int c=0; c<book::n; c++)
      {
        cout << "ISBN        :   " << pink[c].ISBN << endl;
        cout << "TITLE       :   " << pink[c].title << endl;
        cout << "AUTHOR      :   " << pink[c].author << endl;
        cout << "PUBLISHER   :   " << pink[c].publisher << endl;
        cout << "QUANTITY    :   " << pink[c].quantity << endl;
        cout << "WHOLESALE   :   $" << pink[c].ourPrice << endl;
        cout << "RETAIL      :   $" << pink[c].theirPrice << endl;
        cout << "DATE ADDED  :   " << pink[c].added.month << "/" << pink[c].added.day << "/";
        cout << pink[c].added.year << endl;
        cout << endl;
        getchar();
      }
    }
    else if (choice==4) // sorts vector by date
    {
      cout << "Press enter to step through each book.\n";
      cout << endl;
      sort(pink.begin(),pink.end(),sortByAge);
      for (int d=0; d<book::n; d++)
      {
        cout << "ISBN        :   " << pink[d].ISBN << endl;
        cout << "TITLE       :   " << pink[d].title << endl;
        cout << "AUTHOR      :   " << pink[d].author << endl;
        cout << "PUBLISHER   :   " << pink[d].publisher << endl;
        cout << "QUANTITY    :   " << pink[d].quantity << endl;
        cout << "WHOLESALE   :   $" << pink[d].ourPrice << endl;
        cout << "RETAIL      :   $" << pink[d].theirPrice << endl;
        cout << "DATE ADDED  :   " << pink[d].added.month << "/" << pink[d].added.day << "/";
        cout << pink[d].added.year << endl;
        cout << endl;
        getchar();
      }
    }
    else if (choice==5)
      break;
    else
    {
      cout << "Invalid entry. Try again?\n";
      cout << "('Y' key for yes; any other key to exit.)\n";
      cin >> choice_2;
      if(choice_2=='Y')
        continue;
      else
        break;
    }
  }
}


int main() //Used for reading in file, and for selecting the appropriate module
{
  string titlein,authorin,publisherin;
  int monthhold,dayhold,yearhold,ISBNin,quantityin,choice,return_value;
  float ourprice,theirprice;
  date addedin;
  int allocate; //for reading in from file
  char throwaway;
  fstream source;

  cout << endl << endl;
  cout << "         ╔═════════════════════════╗         " << endl;
  cout << "           SERENDIPITY BOOKSELLERS           " << endl;
  cout << "         ╚═════════════════════════╝         " << endl << endl;
  cout << "***********************************************\n";
  cout << "*                                             *\n";
  cout << "*    dBBBBBBBBBBBBBBBBBBBBBBBBb               *\n";
  cout << "*   BP YBBBBBBBBBBBBBBBBBBBBBBBb              *\n";
  cout << "*  dB   YBb                 YBBBb             *\n";
  cout << "*  dB    YBBBBBBBBBBBBBBBBBBBBBBBb            *\n";
  cout << "*   Yb    YBBBBBBBBBBBBBBBBBBBBBBBb           *\n";
  cout << "*    Yb    YBBBBBBBBBBBBBBBBBBBBBBBb          *\n";
  cout << "*     Yb    YBBBBBBBBBBBBBBBBBBBBBBBb         *\n";
  cout << "*      Yb    YBBBBBBBBBBBBBBBBBBBBBBBb        *\n";
  cout << "*       Yb    YBBBBBBBBBBBBBBBBBBBBBBBb       *\n";
  cout << "*        Yb   dBBBBBBBBBBBBBBBBBBBBBBBBb      *\n";
  cout << "*         Yb dP=======================/       *\n";
  cout << "*          YbB=======================(        *\n";
  cout << "*           Ybb=======================\\       *"<< endl;
  cout << "*            Y888888888888888888DSI8888b      *\n";
  cout << "*                                             *\n";
  cout << "***********************************************\n";
  cout << endl << endl;

  source.open(filepath);
  source>>allocate;
  getline(source, titlein);
  getline(source, titlein);
  vector<book> pink(allocate); //Reads from file and creates a vector to store book information in
  
  for (int x=0; x<allocate; x++) 
  {
    source>>pink[x].ISBN;
    source>>throwaway;
    getline(source, pink[x].title, ',');
    getline(source, pink[x].author, ',');
    getline(source, pink[x].publisher, ',');
    source>>pink[x].added.month>>throwaway>>pink[x].added.day>>throwaway>>pink[x].added.year>>throwaway;
    source>>pink[x].quantity>>throwaway>>pink[x].ourPrice>>throwaway>>pink[x].theirPrice;
  }

  while(1)
  {
    cout << "     Which module would you like to load?\n";
    cout << "###############################################\n";
    cout << "# 1: Cashier Module                           #\n";
    cout << "# 2: Inventory Module                         #\n";
    cout << "# 3: Report Module                            #\n";
    cout << "# 4: Exit                                     #\n";
    cout << "# 5: Credits                                  #\n";
    cout << "###############################################\n";
    cin >> choice;

    if(choice==1)
      cashier();

    else if(choice==2)
      inventory(pink);

    else if(choice==3)
      reports(pink); // call report module and pass it the vector with all of the book objects

    else if(choice==4)
    {
      cout << "Thank you for using [program name]\n\n";
      break;
    }

    else if(choice==5)
    {
      cout << "\n[software name] copyright 2015, ";
      cout << "Chrysanthemum Industries.\n";
      cout << "Chrssanthemum Industries are:\n";
      cout << "Roark Burney, Zachary Prince, Abdollah Kasraie, and\n";
      cout << "Chris Yu.\n";
      cout << "ASCII book made by unknown patron of the internet.\n\n";
      cout << "(Press any key to continue.)\n\n";
      cin.get();cin.get();
      continue;
    }

    else 
    {
      cout << "Invalid choice. Restarting...\n\n";
      continue;
    }
  }
}

/*
void cashier(vector<book>& pink) //Cashier module
{
	fstream receipt;
	int choice, titlecounter, pquantity, totalprice;
	int checkoutcounter = 0;
	string titlechoice, authorchoice, cochoice;
	int isbnchoice;

	do
	{
		cout << "Welcome to the Cash Register Module!" << endl;
		cout << "Please look at the Menu Below" << endl << endl;
		cout << "###############################################\n";
		cout << "# 1: Purchase a book by Title                 #\n";
		cout << "# 2: Purchase a book by ISBN                  #\n";
		cout << "# 3: Purchase a book by Author(WIP)           *\n";
		cout << "# 4: Return to Main Menu                      #\n";
		cout << "###############################################\n";
		cin >> choice;
		cout << endl;
		// Title Searching
		if (choice == 1)
		{
			bool exists = false;

			cout << "Please Input the title of the book you want" << endl;
			cin >> titlechoice;
			
				for (int a = 0; a < book::n; a++)
				{
					titlecounter++;
					if (titlechoice == pink[a].title) exists = true;
				}
				if (exists = true)
				{
					cout << "We are pleased to have your book in our selection" << endl;
					cout << "Would you like to add the book to Check out? (Y or N)" << endl;
					cin >> cochoice;
					if (cochoice == "y")
					{
						checkoutcounter++;
						//reduce pink[titlecounter].quantity by integer. ///////////////WIP//////////////////////
						cout << "How many copies would you like to buy? " << endl;
						cin >> pquantity;
						pink[titlecounter].quantity = pink[titlecounter].quantity - pquantity;
						totalprice += pink[titlecounter].theirPrice * pquantity;
						// add book into vector then read them out.
						cochoice = "n";
					}
				}
			else cout << "We are sorry, we do not have your book in our selection. " << endl;
		}
		// ISBN Searching
		if (choice == 2)
		{
			bool exists = false;

			cout << "Please Input the ISBN of the book you want" << endl;
			cin >> isbnchoice;

			for (int a = 0; a < book::n; a++)
			{
				titlecounter++;
				if (isbnchoice == pink[a].ISBN) exists = true;
			}
			if (exists = true)
			{
				cout << "We are pleased to have your book in our selection" << endl;
				cout << "Would you like to add the book to Check out? (Y or N)" << endl;
				cin >> cochoice;
				if (cochoice == "y")
				{
					checkoutcounter++;
					//reduce pink[titlecounter].quantity by integer.
					cout << "How many copies would you like to buy? " << endl;
					cin >> pquantity;
					pink[titlecounter].quantity = pink[titlecounter].quantity - pquantity;
					totalprice += pink[titlecounter].theirPrice * pquantity;
					// add book into vector then read them out.
					cochoice = "n";
				}
			}
			else cout << "We are sorry, we do not have your book in our selection. " << endl;
		}
		// Author Search
		if (choice == 3)
		{
			bool exists = false;

			cout << "Please Input the Author of the book you want" << endl;
			cin >> authorchoice;

			for (int a = 0; a < book::n; a++)
			{
				titlecounter++;
				if (authorchoice == pink[a].author) exists = true;
			}
			if (exists = true)
			{
				cout << "We are pleased to have your book in our selection" << endl;
				cout << "Would you like to add the book to Check out? (Y or N)" << endl;
				cin >> cochoice;
				if (cochoice == "y")
				{
					checkoutcounter++;
					//reduce pink[titlecounter].quantity by integer.
					cout << "How many copies would you like to buy? " << endl;
					cin >> pquantity;
					pink[titlecounter].quantity = pink[titlecounter].quantity - pquantity;
					totalprice += pink[titlecounter].theirPrice * pquantity;
					// add book into vector then read them out.
					cochoice = "n";
				}
			}
			else cout << "We are sorry, we do not have your book in our selection. " << endl;
		}

	} while (choice != 4);

	// cout vector contents AKA receipt part
	cout << "Your total balance is: " << totalprice << endl;
}
*/
