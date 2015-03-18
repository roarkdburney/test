//Copyright Chrysanthemum Industries
// Roarke Burney, Zachary Prince
// Abdollah Kasraie, Chris Yu 

#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<fstream>
#include<string> // Needed for string operations
#include<vector> // Needed for vectors
#include<algorithm> // Needed for sort function
#include"book.h"
#include"date.h"
#include"sorting.h"

using namespace std;

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

void regret_message()
{
  cout << endl;
  cout << "###############################################\n"; 
  cout << "#                                             #\n";
  cout << "# We are sorry, we do not have your book in   #\n"; 
  cout << "# our selection. Returning to main menu...    #\n";
  cout << "#                                             #\n";
  cout << "###############################################\n";
}

string myToLower (string inStr) // Converts the Caps in the Input String to lower case quivalent, made by Abdollah
{
  char c; // The character to be examined
  string outStr = ""; // The resulting string
  for (int i=0 ; i<inStr.size() ; i++)  // Examining all characters
  {
    c = inStr[i]; // The character to be examined
    if (c >= 'A' && c <= 'Z') c = tolower(c);	// It is an Uppercase -> Convert to Lowercase equivalent
    outStr = outStr + c;  // Append to resulting string (either original or converted char)
  }
  return outStr;	// Result: The input string with all Uppercase chars converted to Lowercase.
}

int toInteger (string inStr, bool& isNumber)
  // Qualifies the Input String for being an Integer and returns the equivalent integer, made by Abdollah
{											
  char c; // The character to be examined
  int srchNumber = 0; // The final result, if all characters are numerals.
  isNumber = true; // Default: the input has all numerals

  for (int i=0 ; i < inStr.size() ; i++)  // Examining all characters
  {
    c = inStr[i];
    // check if the srchStr represents a Number
    if (isNumber && c >= '0' && c <= '9')   // The character is a numeral and all previous ones, too.
      srchNumber = srchNumber * 10 + (static_cast<int>(c)-48); // Calculate resulting Integer.
    else
      isNumber = false;	// At least one character has been determined as non-digit.
  }									
  return srchNumber;						// Result: if isNumber is True, the calculated Integer is returned.
}

void schBks(vector<book>& inventory, int fndItems[], int& retCount, string srchStr) // Search function, made by Abdollah
{
  // The Search performs both Numeric and String checks 
  bool isNumeric = false; // Shows whether the Search String srchStr is all digits
  string noCapsStr = myToLower(srchStr);  // Is the input srchStr with all Caps converted to lower chars
  int srchNumber = toInteger(srchStr, isNumeric); // Check if the input is also an Integer by calling toInteger
  bool indexFound; // Checks if the srchStr has been found among string fields of Book
  int fndCount = 0;
  for (int index=0 ; index<inventory.size() ; index++)	// Examining all books in the inventory vector
  {
    indexFound = false;	
    if (myToLower(inventory[index].title).find(noCapsStr) < myToLower(inventory[index].title).size() ||
    	myToLower(inventory[index].author).find(noCapsStr) < myToLower(inventory[index].author).size() ||
	myToLower(inventory[index].publisher).find(noCapsStr) < myToLower(inventory[index].publisher).size() ||
	srchStr==inventory[index].ISBN)
	{
          indexFound = true; 
          /*
           * When the srchStr is found, the indexFound flag is set, the number of found books is incremented,
           * and the index number of the book info in inventory vector is added to the found items array (fndItems[]).
           */
          fndCount++;
          fndItems[fndCount-1] = index;	
        }
    /*
     *If srchStr is not found among string fields and it is a number, and is equal to ISBN, or year of added date, 
     * or month of added date, or day of added date, or integer part of ourPrice, or integer part of theirPrice.
     */
    if((!indexFound && isNumeric && inventory[index].added.year == srchNumber)||
      (!indexFound && isNumeric && inventory[index].added.month == srchNumber)||
      (!indexFound && isNumeric && inventory[index].added.day == srchNumber)||
      (!indexFound && isNumeric && int(inventory[index].ourPrice) == srchNumber)||
      (!indexFound && isNumeric && int(inventory[index].theirPrice) == srchNumber))
      {
        /*
         * This time, the srchStr number was found -> the indexFound flag is 
         * the number of found books is incremented, and the index number of 
         * the book info in the inventory vector is added the the found items
         * array (fndItems[]).
         */
	 indexFound = true;							
         fndCount++;
	 fndItems[fndCount-1] = index;		
      }	
  }
  retCount = fndCount; // Result: the fndCount is passed to retCount by reference.
}

void cashier(vector<book>& pink) //Cashier module
{
  int titlecounter=0;
  int p_quantity=0;
  float total_price=0;
  string isbnchoice;
  int checkoutcounter=0;
  int choice;
  string titlechoice, authorchoice, cochoice, rec_choice;
  string titlelist[100];
  vector<book> magenta(100); //specialized vector specifically for cashier recepit
  do
  {
    cout << endl;
    cout << "     Welcome to the Cash Register Module!     " << endl;
    cout << "         Please look at the menu below:       " << endl; 
    cout << "###############################################\n";
    cout << "# 1: Purchase a book by Title                 #\n";
    cout << "# 2: Purchase a book by ISBN                  #\n";
    cout << "# 3: View Checkout Cart                       #\n";
    cout << "# 4: View Receipt                             #\n";
    cout << "#                                             #\n";
    cout << "# 7: Return to Main Menu                      #\n";
    cout << "###############################################\n";
    cin >> choice;
    cout << endl;
    // Title Searching
    if (choice == 1)
    {
      bool exists = false;
      cout << "###############################################\n";
	  cout << "#                                             #\n";
      cout << "# Enter title below: (case-sensitive)         #\n"; 
      cout << "# (i.e. enter 'Lolita', not 'lOlItA')         #\n"; 
	  cout << "#                                             #\n";
      cout << "###############################################\n";
      cin.ignore();
      getline(cin,titlechoice);
      for (int a = 0; a < book::n; a++)
      {
	if (titlechoice == pink[a].title) 
        {
          exists = true;
          break;
        }
	titlecounter++;
      }

      if (exists == true)
      {
        if (pink[titlecounter].quantity>0) //If there are any books in our inventory at all
        {
          cout << endl;
          cout << "###############################################\n";
		  cout << "#                                             #\n";
          cout << "# We are pleased to have your book in stock.  #\n";
          cout << "# Would you like to add a copy to your cart?  #\n";
          cout << "# ('Y' for yes; any other key to exit to menu)#\n";
		  cout << "#                                             #\n";
          cout << "###############################################\n";
          cout << "Note: There are only " << pink[titlecounter].quantity << " copies left.\n";
          cout << endl;
	      cin >> cochoice;
	      if (cochoice == "Y")
	      {
            cout << endl;
            cout << "###############################################\n" << endl;
            cout << "NOTE: Each copy is $" << pink[titlecounter].theirPrice << ", plus tax.\n";
            cout << "Enter in the amount of copies desired.\n";
            cout << endl << "###############################################\n";
	        cin >> p_quantity;
            if (pink[titlecounter].quantity>=p_quantity)
            {
	          pink[titlecounter].quantity = pink[titlecounter].quantity - p_quantity;
	          total_price += (pink[titlecounter].theirPrice * p_quantity ); 

	      // add book into vector then read them out.
              
              magenta[checkoutcounter].ISBN=pink[titlecounter].ISBN;
              magenta[checkoutcounter].quantity = p_quantity;
              magenta[checkoutcounter].title=pink[titlecounter].title;
              magenta[checkoutcounter].theirPrice=pink[titlecounter].theirPrice;
	          checkoutcounter++;

              cout << endl;
              cout << "###############################################\n"; 
			  cout << "#                                             #\n";
              cout << "#    Books added. For subtotal, view cart.    #\n";
              cout << "#         Returning to main menu...           #\n";
			  cout << "#                                             #\n";
              cout << "###############################################\n" << endl;
            }
            else
            {
              cout << endl;
              cout << "###############################################\n"; 
			  cout << "#                                             #\n";
              cout << "#   Invalid amount selected. Restarting...    #\n";
			  cout << "#                                             #\n";
              cout << "###############################################\n"; 
            }
	  }
          else
          {
            cout << endl;
            cout << "###############################################\n"; 
			cout << "#                                             #\n";
            cout << "# No books added. Returning to main menu...   #\n";
			cout << "#                                             #\n";
            cout << "###############################################\n"; 
          }
        }
        else
          regret_message();
      }
      else  
      {
       regret_message(); 
      }
      titlecounter=0;
    }
      // ISBN Searching
    if (choice == 2)
    {
      bool exists = false;
      cout << "###############################################\n";
	  cout << "#                                             #\n";
      cout << "# Enter ISBN of book below: (without dashes)  #\n";
	  cout << "#                                             #\n";
      cout << "###############################################\n";
      cin >> isbnchoice;

      for (int a = 0; a < book::n; a++)
      {
	if (isbnchoice == pink[a].ISBN) 
        {
          exists = true;
          break;
        }
        titlecounter++;
      }

      if (exists == true)
      {
        if (pink[titlecounter].quantity>0) //If there are any books in our inventory at all
        {
          cout << endl;
          cout << "###############################################\n";
		  cout << "#                                             #\n";
          cout << "# We are pleased to have your book in stock.  #\n";
          cout << "# Would you like to add a copy to your cart?  #\n";
          cout << "# ('Y' for yes; any other key to exit to menu)#\n";
		  cout << "#                                             #\n";
          cout << "###############################################\n";
          cout << "Note: There are only " << pink[titlecounter].quantity << " copies left.\n";
          cout << endl;
	  cin >> cochoice;
	  if (cochoice == "Y")
	  {
            cout << endl;
            cout << "###############################################\n" << endl;
            cout << "NOTE: Each copy is $" << pink[titlecounter].theirPrice << ", plus tax.\n";
            cout << "Enter in the amount of copies desired.\n";
            cout << endl << "###############################################\n";
	    cin >> p_quantity;
            if (pink[titlecounter].quantity>=p_quantity)
            {
	      pink[titlecounter].quantity = pink[titlecounter].quantity - p_quantity;
	      total_price += (pink[titlecounter].theirPrice * p_quantity); // Sales tax is 7.5% 
	      // add book into vector then read them out.
	      //titlelist[checkoutcounter] = pink[titlecounter].title;
              
              magenta[checkoutcounter].quantity = p_quantity;
              magenta[checkoutcounter].ISBN=pink[titlecounter].ISBN;
              magenta[checkoutcounter].title=pink[titlecounter].title;
              magenta[checkoutcounter].theirPrice=pink[titlecounter].theirPrice;
	      checkoutcounter++;

              cout << endl;
              cout << "###############################################\n"; 
              cout << "# Books added. For subtotal, view cart.       #\n";
              cout << "# Returning to main menu...                   #\n";
              cout << "###############################################\n" << endl;
            }
            else
            {
              cout << endl;
              cout << "###############################################\n"; 
              cout << "# Invalid amount selected. Restarting...      #\n";
              cout << "###############################################\n"; 
            }
	  }
          else
          {
            cout << endl;
            cout << "###############################################\n"; 
            cout << "# No books added. Returning to main menu...   #\n";
            cout << "###############################################\n"; 
          }
        }
        else
          regret_message();
      }
      else  
      {
       regret_message(); 
      }
      titlecounter=0;
    }

    if (choice == 3) //View cart
    {
      cout << "************************************************\n" << endl;
	  cout << "DATE: " __TIMESTAMP__ << endl;
      cout << "************************************************\n" << endl;
      for (int i = 0; i < checkoutcounter; i++)
      {
        cout << "************************************************\n";
        cout << "Quantity: \t" << magenta[i].quantity << endl;
        cout << "  ISBN: \t" << magenta[i].ISBN << endl;
        cout << " Title: \t" << magenta[i].title << endl;
        cout << " Price: \t$" << magenta[i].theirPrice << endl;
        cout << "************************************************\n";
        cout << endl;
      }
	
      cout << "************************************************\n";
      cout << "SUBTOTAL: \t$" << total_price << endl;
      cout << "TAX: \t\t$" << total_price * 0.075 << endl;
      cout << "TOTAL: \t\t$" << total_price * 1.075 << endl;
      cout << "************************************************\n";
      cout << endl;
      cout << "###############################################\n";
      cout << "# Would you like a receipt?                   #\n";
      cout << "# ('Y' for yes; any other key for no.)        #\n";
      cout << "###############################################\n";
      cin >> rec_choice;
      if (rec_choice=="Y")
      {
        ofstream redtails;
        redtails.open("receipt.txt");
        redtails << "************************************************\n" << endl;
		redtails << "DATE: " << __TIMESTAMP__ << endl << endl;
        redtails << "************************************************\n" << endl;
        for (int j = 0; j < checkoutcounter; j++)
        {
          redtails << "************************************************\n";
          redtails << "Quantity: \t" << magenta[j].quantity << endl;
          redtails << "  ISBN: \t" << magenta[j].ISBN << endl;
          redtails << " Title: \t" << magenta[j].title << endl;
          redtails << " Price: \t$" << magenta[j].theirPrice << endl;
          redtails << "************************************************\n";
          redtails << endl;
        }
	
        redtails << "************************************************\n";
        redtails << "SUBTOTAL: \t$" << total_price << endl;
        redtails << "TAX: \t\t$" << total_price * 0.075 << endl;
        redtails << "TOTAL: \t\t$" << total_price * 1.075 << endl;
        redtails << "************************************************\n";
        redtails.close();
      }
      else
      {
        cout << endl;
        cout << "###############################################\n";
		cout << "#                                             #\n";
        cout << "#         Returning to main menu...           #\n";
		cout << "#                                             #\n";
        cout << "###############################################\n";
      }
    }
    if (choice == 4)
	{
      system("notepad receipt.txt");
	}
  } while (choice != 7);
}

void inventory(vector<book>& pink) //Inventory module
{
  int choice, book_to_delete,c=0,a=0;
  char choice_2;
  string choice_3, savepath;
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
    cout << "#                                             #\n";
    cout << "# 7: Return to Main Menu                      #\n";
    cout << "###############################################\n";
    cin >> choice;
    cout << endl;

    if (choice==1) //Adding a book
    {
      string title,author,publisher;
      string ISBN;
      int quantitys;
      date added;
      float ourPrice,theirPrice;
      
      //Prompting user for book info
      cout << "###############################################\n";
      cout << "# Add the information prompted for.           #\n";
      cout << "# (When prompted for prices, leave out the    #\n";
      cout << "# (currency value. i.e. when prompted for     #\n";
      cout << "# (price, enter 5, not $5.)                   #\n";
      cout << "###############################################\n" << endl;
      cout << "ISBN (without dashes): ";
      cin >> ISBN;
      cout << "Title: ";
      cin.ignore();
      getline(cin,title); 
      //These two getlines are not a typo; odd problems were encountered if I only used one
      cout << "Author: ";
      getline(cin,author);
      cout << "Publisher: "; 
      getline(cin,publisher);
      cout << "Quantity on hand: ";
      cin >> quantitys;
      cout << "Wholesale price: ";
      cin >> ourPrice;
      cout << "Retail price: ";
      cin >> theirPrice;
      cout << "Year added to inventory: ";
      cin >> added.year;
      cout << "Month added to inventory (as digits): ";
      cin >> added.month;
      cout << "Day added to inventory (as digits): ";
      cin >> added.day;

      //Creating new book object with the above info
	  cout << endl;
      book blue(title,author,publisher,ourPrice,theirPrice,ISBN,added,quantitys);
	  blue.quantity=quantitys;
      
      //Pushing object into vector of books
	  pink.push_back(blue);
    }
    else if (choice==2) //Deleting a book
    {
      for (;a<book::n;a+=10)
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
		  if (c<book::n)
		    continue;
		  else
		    break; 
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
			book::n--; //Decremented book counter 
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
	  a=0;
	  c=0;
    }
    else if (choice==4) // Implement save function here
    {
      cout << "###############################################\n";
      cout << "# Enter in the filename and or filepath for   #\n";
      cout << "# the updated inventory. Your current direct- #\n";
      cout << "#-ory is shown for convienence. (To overwrite #\n";
      cout << "# the original file, type 'Inventory.csv')    #\n"; 
      cout << "###############################################\n";
      cout << endl;
	  system("dir /d /b /on");
      cout << endl;
      cin >> savepath;
      cout << endl;
      cout << "###############################################\n";
      cout << "# Saving...                                   #\n";
      save(pink,book::n,savepath); //Saves vectors to file
      //system("afplay start_save.mp3");
      cout << "# Saved!                                      #\n";
	  //system("afplay save.mp3");
      cout << "###############################################\n";
      cout << endl;
    }
    else if (choice == 3) // Implement Search & Editing functions here
    {
      string schItem = "";	// Base item for Identity to Search in a book's info
      int itmsFndArr[200];	// Array to show and index for a book with schItem in any of its fields
      int bksFnd = 0;		// Number of Books with schItem in their fields
      int editItemNo;		// The selected item for Editing
      char editField;	        // The field (item) to be amended
      system("cls");
      cout << "###############################################\n";
      cout << "# Enter in your search term below.            #\n";
      cout << "# The term can be an ISBN, title, author,     #\n";
      cout << "# quantity in the inventory, date added to    #\n";
      cout << "# inventory, or the price of the book.        #\n";
	  cout << "# Note: Search term is non-case sensitive.    #\n";
      cout << "###############################################\n";
      cout << endl;
      getline(cin, schItem); // to ignore the previous line
      getline(cin, schItem);
      schBks(pink, itmsFndArr, bksFnd, schItem);
      if (bksFnd > 0)
      {
        for (int i = 0; i < bksFnd; i++)
      	{
	  cout << "\n" << i+1 << ". \n";
	  displayBook(pink[itmsFndArr[i]]);
	}
        cout << endl;
        cout << "###############################################\n";
	cout << "# Please enter the book number of your choice #\n";
        cout << "# for editing.                                #\n";
        cout << "###############################################\n";
	cin >> editItemNo;
	while (editItemNo < 1 || editItemNo > bksFnd)
	{
	  cout << "Oops! Please enter a number between 1 and " << bksFnd << ": \n\n" ;
	  cin >> editItemNo;
	}
	editItemNo = itmsFndArr[editItemNo-1];
	system("cls");
	cout << "The Book to edit:\n"
	<< "-----------------\n";
	displayItmzBook(pink[editItemNo]);
	editField = 'a';
	while (editField >= 'a' && editField <= 'h' )
	{
	  cout << "\nPlease enter item to be amended (a to h)\n"
	  << "To exit 'Edit Mode' enter any other character: " << endl;
	  cin >> editField;
	  switch (editField)
	  {
	    case 'a':
	      cout << "Please enter the new ISBN: ";	// ISBN
	      cin >> pink[editItemNo].ISBN;
	      break;
	    case 'b':
	      cout << "Please enter the new Title: \n";	// Title
	      getline(cin, schItem); // To Read the complete line I need this IGNORE line!
	      getline(cin, pink[editItemNo].title);
	      break;
	    case 'c':
	      cout << "Please enter the new Author: \n";		// Author
	      getline(cin, schItem); // To Read the complete line I need this IGNORE line!
	      getline(cin, pink[editItemNo].author);
	      break;
	    case 'd':
	      cout << "Please enter the new Publisher: \n";	// Publisher
	      getline(cin, schItem); // To Read the complete line I need this IGNORE line!
	      getline(cin, pink[editItemNo].publisher);
	      break;
	    case 'e':
	      cout << "Please enter the new Quantity: ";	// Quantity
	      cin >> pink[editItemNo].quantity;
	      break;
	    case 'f':
	      cout << "Please enter the new Wholesale Price: ";	// Wholesale Price
	      cin >> pink[editItemNo].ourPrice;
	      break;
	    case 'g':
	      cout << "Please enter the new Retail Price: ";	// Retail Price
	      cin >> pink[editItemNo].theirPrice;
	      break;
	    case 'h':
	      cout << "Please enter the new Date Added to Inventory: \n";	// Date Added to Inventory
	      cout << "Year: ";
	      cin >> pink[editItemNo].added.year; // Year
	      cout << "Month: ";
	      cin >> pink[editItemNo].added.month; // Month
	      cout << "Day: ";
	      cin >> pink[editItemNo].added.day; // Day
	      break;
           }
         }
	 cout << "\nThe Book after editing:\n";
	 cout << "-----------------------\n";
	 displayBook(pink[editItemNo]);
       }
       else
       {
         cout << endl;
         cout << "###############################################\n";
		 cout << "#                                             #\n";
         cout << "# Sorry, no book was found! Returning to menu.#\n";
		 cout << "#                                             #\n";
         cout << "###############################################\n";
       }
    }

    else if (choice==7) // Quits inventory module
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
    cout << endl;
    cout << "\n        Welcome to the report module.\n";
    cout << "What kind of report would you like to generate?\n";
    cout << "###############################################\n";
    cout << "# 1: Inventory List                           #\n";
    cout << "# 2: Sort and list by Quantity                #\n";
    cout << "# 3: Sort and list by Cost                    #\n";
    cout << "# 4: Sort and list by Age                     #\n";
    cout << "#                                             #\n";
    cout << "# 7: Return to Main Menu                      #\n";
    cout << "###############################################\n";
    cin >> choice;
    cout << endl;

    if (choice==1) // list
    {
      report_message();
      system("cls");
      //cout << "Press enter to step through each book.\n";
      cout << endl;
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
        cout << "###############################################\n";
		cout << endl;

        //Keep running totals of wholesale and retail prices for the report
        total_wholesale+=pink[a].ourPrice; 
        total_retail+=pink[a].theirPrice;
        getchar();
      }
      cout << endl << endl << "###############################################\n";
	  cout << endl;
      cout << "TOTAL WHOLESALE VALUE  :  $" << total_wholesale << endl;
      cout << "TOTAL RETAIL VALUE     :  $" << total_retail << endl;
	  cout << endl;
      cout << "###############################################\n";
      total_wholesale=0;
      total_retail=0; //reset for next invocation
    }
    
    else if (choice==2) // quantity
    {
      report_message();
      system("cls");
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
        cout << "###############################################\n";
        getchar();
      }
    }

    else if (choice==3) // cost
    {
      report_message();
      system("cls");
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
        cout << "###############################################\n";
        cout << endl;
        getchar();
      }
    }
    else if (choice==4) // sorts vector by date
    {
      report_message();
      system("cls");
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
        cout << "###############################################\n";
        getchar();
      }
    }
    else if (choice==7)
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
start:
  string titlein,authorin,publisherin,filepath,ISBNin;
  int monthhold,dayhold,yearhold,quantityin,choice,return_value;
  float ourprice,theirprice;
  date addedin;
  int allocate; //for reading in from file
  char throwaway;
  fstream source;

  cout << endl << endl;
  cout << "         ###########################         " << endl;
  cout << "         #                         #         " << endl;
  cout << "         # SERENDIPITY BOOKSELLERS #         " << endl;
  cout << "         #                         #         " << endl;
  cout << "         ###########################         " << endl << endl;
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
  cout << endl << endl << "                 LOADING...                    \n";
  system("ping 1.1.1.1 -n 1 -w 5000 > nul"); // wait for 3 seconds
  system("cls");

  //system("afplay start.mp3"); //Only on Macs

  cout << "###############################################\n";
  cout << "# Enter the location of the inventory csv.    #\n";
  cout << "# By default, the file is stored in the same  #\n";
  cout << "# directory as this program, and should be    #\n";
  cout << "# titled 'Inventory.csv'. If you're using a   #\n";
  cout << "# csv file, specifiy the name and or filepath.#\n";
  cout << "# A listing of your current working directory #\n";
  cout << "# has been provided for your convenience.     #\n";
  cout << "###############################################\n";
  cout << endl;
  system("dir /d /b /on");
  cout << endl;
  cin >> filepath;
  source.open(filepath);
  try{
  if(source){
  source>>allocate;
  getline(source, titlein);
  getline(source, titlein);
  vector<book> pink(allocate); //Reads from file and creates a vector to store book information in
  
  for (int x=0; x<allocate; x++) 
  {
    getline(source, pink[x].ISBN, ',');
    getline(source, pink[x].title, ',');
    getline(source, pink[x].author, ',');
    getline(source, pink[x].publisher, ',');
    source>>pink[x].added.month>>throwaway>>pink[x].added.day>>throwaway>>pink[x].added.year>>throwaway;
    source>>pink[x].quantity>>throwaway>>pink[x].ourPrice>>throwaway>>pink[x].theirPrice;
    remove_if(pink[x].ISBN.begin(), pink[x].ISBN.end(), ::isspace);
	book::n++;
  }

  while(1)
  {
    try
    {
	cout << endl;
    cout << "     Which module would you like to load?\n";
    cout << "###############################################\n";
    cout << "# 1: Cashier Module                           #\n";
    cout << "# 2: Inventory Module                         #\n";
    cout << "# 3: Report Module                            #\n";
    cout << "# 4: Credits                                  #\n";
    cout << "#                                             #\n";
    cout << "# 8: Exit                                     #\n";
    cout << "###############################################\n";
    cin >> choice;

    if(choice==1)
      cashier(pink);

    else if(choice==2)
      inventory(pink);

    else if(choice==3)
      reports(pink); // call report module and pass it the vector with all of the book objects

    else if(choice==8)
    {
		cout << endl;
      cout << "###############################################\n";
	  cout << "# WARNING: Any changes made to the inventory  #\n";
	  cout << "# file will be lost, if it has not already    #\n";
	  cout << "# been saved. Would you like to save now?     #\n";
	  cout << "# ('Y' saves, any other key will exit.)       #\n";
      cout << "###############################################\n" << endl;
	  string save_choice,savepath;
	  cin >> save_choice;
	  if(save_choice=="Y"||save_choice=="y")
	  {
		cout << endl;
        cout << "###############################################\n";
        cout << "# Enter in the filename and or filepath for   #\n";
        cout << "# the updated inventory. Your current direct- #\n";
        cout << "#-ory is shown for convienence. (To overwrite #\n";
        cout << "# the original file, type 'Inventory.csv')    #\n"; 
        cout << "###############################################\n";
        cout << endl;
	    system("dir /d /b /on");
        cout << endl;
        cin >> savepath;
        cout << endl;
        cout << "###############################################\n";
        cout << "# Saving...                                   #\n";
        save(pink,book::n,savepath); //Saves vectors to file
        //system("afplay start_save.mp3");
        cout << "# Saved!                                      #\n";
	    //system("afplay save.mp3");
        cout << "###############################################\n\n";
	  }
	  cout << endl;
      cout << "###############################################\n";
      cout << "# Thank you for using the ARiA business suite.#\n";
      cout << "#                                             #\n";
      cout << "# Any questions, comments, or feedback can be #\n";
      cout << "# sent to customer_service@chrysanthemum.org  #\n";
      cout << "#                                             #\n";
      cout << "###############################################\n" << endl;
	  system("ping 1.1.1.1 -n 1 -w 5000 > nul"); // wait for 3 seconds
      //system("afplay end.mp3"); //Only on Macs
      system("cls");
      break;
    }

    else if(choice==4)
    {
      system("cls");
      cout << "***********************************************\n";
      cout << "*                                             *\n";
      cout << "*            ARiA copyrighted 2015            *\n";
      cout << "*           Chrysanthemum Industries          *\n"; 
      cout << "*                                             *\n";
      cout << "*                  /:.   ,:\\""                  *"<< endl;
      cout << "*            .~=-./::: u  ::\\,-~=.            *" << endl;
      cout << "*         ___|::  \\\    |    /  ::|___         *" << endl;
      cout << "*        \\\::  `.   \\   |   /   .' :::/        *" << endl;
      cout << "*         \\:    `.  \\  |  /  .'    :/         *" << endl;
      cout << "*       .-: `-._  `.;;;;;;.'   _.-' :-.       *" << endl;
      cout << "*       \\::     `-;;;;;;;;;;;-'     ::/       *" << endl;
      cout << "*        >~------~;;;;;;;;;;;~------~<        *" << endl;
      cout << "*        /::    _.-;;;;;;;;;;;-._    ::\\      *" << endl;
      cout << "*       `-:_.-'   .`;;;;;;;'.   `-._:-'       *" << endl;
      cout << "*          /    .'  /  |  \\  `.   :\\          *" << endl;
      cout << "*         /::_.'   /   |   \\   `._::\\         *" << endl;
      cout << "*             |:: /    |    \\  ::|            *" << endl;
      cout << "*             `=-'\\:::.n.:::/`-=-'            *" << endl;
      cout << "*                  \\:'   `:/                  *" << endl;
      cout << "*                                             *\n";
      cout << "***********************************************\n";
      cout << endl;
      cout << "(Press any key to continue.)\n\n";
      cin.get();cin.get();
      system("cls");
      cout << "###############################################\n";
      cout << "# Software title: ARiA Business Suite         #\n";
      cout << "#                                             #\n";
      cout << "# Publisher: Chrysanthemum Industries, 2015   #\n";
      cout << "#                                             #\n";
      cout << "# Developers: Roark Burney, Zachary Prince,   #\n";
      cout << "#             Chris Yu, Abdollah Kasraie      #\n";
      cout << "#                                             #\n";
      cout << "# ASCII art made by unknown patron of the     #\n";
      cout << "# internet.                                   #\n";
      cout << "#                                             #\n";
      cout << "###############################################\n";

      cout << endl << endl;
      cout << "(Press any key to continue.)\n\n";
      cin.get();
      continue;
    }

    else
      throw 'A';
    } // end try block
    catch (char a)
    {
      cout << endl;
      cout << "###############################################\n";
      cout << "# Exception occurred. Most likely the result  #\n";
      cout << "# of an incorrect number choice. Restarting...#\n";
      cout << "###############################################\n";
      cout << endl;
    }
  }
  }
  else
    throw 'B';
  }
  catch (char b)
  {
	string continue_choice;
    cout << endl;
    cout << "###############################################\n";
    cout << "# Exception occurred. File not found. Retry?  #\n";
	cout << "# ('N' to exit; any other key to retry.)      #\n";
    cout << "###############################################\n";
	cout << endl;
	cin >> continue_choice;
	if (continue_choice=="N" || continue_choice=="n")
	{
	}
	else
	{
      goto start;
	}
  }
}