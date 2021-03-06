﻿//Copyright Chrysanthemum Industries
// Roarke Burney, Zachary Prince
// Abdollah Kasraie, Chris Yu 
// Final Project: Booksellers

#define _CRT_SECURE_NO_WARNINGS

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
	cin.get(); cin.get(); //Mac equivalent of doing "system("Pause")"
}

string myToLower(string inStr) // Converts the Caps in the Input String to lower case quivalent, made by Abdollah
{
	char c; // The character to be examined
	string outStr = ""; // The resulting string
	for (int i = 0; i<inStr.size(); i++)  // Examining all characters
	{
		c = inStr[i]; // The character to be examined
		if (c >= 'A' && c <= 'Z') c = tolower(c);	// It is an Uppercase -> Convert to Lowercase equivalent
		outStr = outStr + c;  // Append to resulting string (either original or converted char)
	}
	return outStr;	// Result: The input string with all Uppercase chars converted to Lowercase.
}

int toInteger(string inStr, bool& isNumber)
// Qualifies the Input String for being an Integer and returns the equivalent integer, made by Abdollah
{
	char c; // The character to be examined
	int srchNumber = 0; // The final result, if all characters are numerals.
	isNumber = true; // Default: the input has all numerals

	for (int i = 0; i < inStr.size(); i++)  // Examining all characters
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
	for (int index = 0; index<inventory.size(); index++)	// Examining all books in the inventory vector
	{
		indexFound = false;
		if (myToLower(inventory[index].title).find(noCapsStr) < myToLower(inventory[index].title).size() ||
			myToLower(inventory[index].author).find(noCapsStr) < myToLower(inventory[index].author).size() ||
			myToLower(inventory[index].publisher).find(noCapsStr) < myToLower(inventory[index].publisher).size() ||
			srchStr == inventory[index].ISBN)
		{
			indexFound = true;
			/*
			* When the srchStr is found, the indexFound flag is set, the number of found books is incremented,
			* and the index number of the book info in inventory vector is added to the found items array (fndItems[]).
			*/
			fndCount++;
			fndItems[fndCount - 1] = index;
		}
		/*
		*If srchStr is not found among string fields and it is a number, and is equal to ISBN, or year of added date,
		* or month of added date, or day of added date, or integer part of ourPrice, or integer part of theirPrice.
		*/
		if ((!indexFound && isNumeric && inventory[index].added.year == srchNumber) ||
			(!indexFound && isNumeric && inventory[index].added.month == srchNumber) ||
			(!indexFound && isNumeric && inventory[index].added.day == srchNumber) ||
			(!indexFound && isNumeric && int(inventory[index].ourPrice) == srchNumber) ||
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
			fndItems[fndCount - 1] = index;
		}
	}
	retCount = fndCount; // Result: the fndCount is passed to retCount by reference.
}

void cashier(vector<book>& elan) //Cashier module
{
	// initializing variables
	fstream receipt; // used for possible .txt receipt. Might go outside boundaries of cashier module
	int choice = 0; int titlecounter = 0;  int pquantity = 0;
	int totalprice = 0;
	int checkoutcounter = 0; // Array counter for book reference
	string titlechoice, authorchoice, cochoice;
	string isbnchoice;
	string titlelist[100]; // Store receipt/checkout information
	string isbnlist[100];
	string authorlist[100];
	string publisherlist[100];
	double pricelist[100]; // for checkout cart
	double quantitylist[100]; // for checkout cart

	// Start the looping menu.
	do
	{

		cout << endl << "       Welcome to the Cash Register Module!" << endl;
		cout << "         Please look at the Menu Below:" << endl << endl;
		cout << "###############################################\n";
		cout << "#                                             #\n";
		cout << "# 1: Purchase a book by Title                 #\n";
		cout << "# 2: Purchase a book by ISBN                  #\n";
		cout << "# 3: View Checkout Cart                       #\n";
		cout << "# 4: Create Receipt                           #\n";
		cout << "# 5: View Receipt                             #\n";
		cout << "#                                             #\n";
		cout << "# 7: Finish, and return to Main Menu          #\n";
		cout << "#                                             #\n";
		cout << "###############################################\n";
		cin >> choice;
		cout << endl;
		// Title Searching
		if (choice == 1)
		{
			bool exists = false; // The boolean used for the detection of books
			cout << "Please input the title of the book you want below:" << endl << endl;
			cin.ignore();
			getline(cin, titlechoice);
			// Loop to check for book's existence
			for (int a = 0; a < book::n; a++)
			{
				if (titlechoice == elan[a].title) // If user input = any books in the file, then it exists
				{
					exists = true;
					break;
				}
				titlecounter++; // keep track of sought after books
			}
			if (exists == true) // Even if we have the book in store, check to see if we have any in inventory
			{
				if (elan[titlecounter].quantity == 0)
					exists = false;
			}
			// User Input to purchase books
			if (exists == true)
			{
				cout << endl;
				cout << "We are pleased to have your book in our selection." << endl << endl;
				cout << "'" << elan[titlecounter].title << "': " << elan[titlecounter].quantity << " copies in stock."  << endl << endl;
				cout << "Would you like to add the book to Check out? (Y or N)" << endl << endl;
				cin >> cochoice;
				if (cochoice == "Y" || cochoice == "y")
				{
					//reduce pink[titlecounter].quantity by integer. 
					cout << endl;
					cout << "How many copies would you like to buy? " << endl << endl;
					cin >> pquantity;
					do
					{
						if (pquantity <= 0)
						{
							cout << endl << "Invalid amount. Please input a valid amount." << endl;
							cin >> pquantity;
						}
						if (elan[titlecounter].quantity < pquantity)
						{
							cout << endl << "Sorry, we only have " << elan[titlecounter].quantity << " copies in stock." << endl;
							cout << "Please input a valid amount to purchase." << endl;
							cin >> pquantity;
							cout << endl;
						}
					} while (pquantity <= 0 || elan[titlecounter].quantity < pquantity);

					{
						elan[titlecounter].quantity = elan[titlecounter].quantity - pquantity; // Decrement the amount of books in inventory
						totalprice += elan[titlecounter].theirPrice * pquantity; // Keep a running total of the price.
						// add book into vector then read them out.
						titlelist[checkoutcounter] = elan[titlecounter].title; // Store the book's titles
						isbnlist[checkoutcounter] = elan[titlecounter].ISBN; // Store the book's isbn
						authorlist[checkoutcounter] = elan[titlecounter].author; // store the book's author
						publisherlist[checkoutcounter] = elan[titlecounter].publisher; // store the books publisher
						pricelist[checkoutcounter] = elan[titlecounter].theirPrice; // Store the books price
						quantitylist[checkoutcounter] = pquantity; // Store the books quantity
						checkoutcounter++; // Increment for the next book
						cout << "You have added " << elan[titlecounter].title << " to your shopping cart." << endl << endl;
						titlecounter = 0; // Reset for next book
					}


				}
				titlecounter = 0; // Reset the search engine for next book regardless of purchase
			}
			else cout << "We are sorry, we do not have your book in our selection. " << endl;
			titlecounter = 0; // Reset
		}
		// ISBN Searching
		if (choice == 2)
		{
			bool exists = false;
			cout << "Please input the ISBN of the book you want." << endl << endl;
			cin.ignore();
			getline(cin, isbnchoice);

			for (int a = 0; a < book::n; a++)
			{
				if (isbnchoice == elan[a].ISBN)
				{
					exists = true;
					break;
				}
				titlecounter++;
			}
			if (exists == true)
			{
				if (elan[titlecounter].quantity == 0)
					exists = false;
			}
			if (exists == true)
			{
				cout << endl << "We are pleased to have your book in our selection." << endl;
				cout << elan[titlecounter].title << " : " << elan[titlecounter].quantity << " copies in stock." << endl;
				cout << "Would you like to add the book to check out? (Y or N)" << endl << endl;;
				cin >> cochoice;
				if (cochoice == "Y" || cochoice == "y")
				{
					//reduce pink[titlecounter].quantity by integer. 
					cout << "How many copies would you like to buy? " << endl;
					cin >> pquantity;
					do
					{
						if (pquantity <= 0)
						{
							cout << endl << "Invalid amount. Please input a valid amount: ";
							cin >> pquantity;
						}
						if (elan[titlecounter].quantity < pquantity)
						{
							cout << endl;
							cout << "Sorry, we only have " << elan[titlecounter].quantity << " copies in stock.\n";
							cout << "Please input a valid amount: ";
							cin >> pquantity;
							cout << endl;
						}
					} while (pquantity <= 0 || elan[titlecounter].quantity < pquantity);
					{
						// Decrement vector object information
						elan[titlecounter].quantity = elan[titlecounter].quantity - pquantity;
						totalprice += elan[titlecounter].theirPrice * pquantity;
						// add book into vector then read them out.
						titlelist[checkoutcounter] = elan[titlecounter].title;
						isbnlist[checkoutcounter] = elan[titlecounter].ISBN;
						authorlist[checkoutcounter] = elan[titlecounter].author;
						publisherlist[checkoutcounter] = elan[titlecounter].publisher;
						pricelist[checkoutcounter] = elan[titlecounter].theirPrice;
						quantitylist[checkoutcounter] = pquantity;
						// Increment counter
						checkoutcounter++;
						cout << "You have added " << elan[titlecounter].title << " to your shopping cart." << endl << endl;
						// Reset
						titlecounter = 0;

					}
				}
				titlecounter = 0;
			}
			else cout << "We are sorry, we do not have your book in our selection. " << endl;
			titlecounter = 0;
		}
		// Display the recorded array of book information
		if (choice == 3)
		{
			cout << endl << "The books in your current shopping cart are: " << endl << endl;
			cout << "Date : " << __TIMESTAMP__ << endl << endl;

			cout << setw(4) << left << "QTY" << setw(20) << left << "ISBN";
			cout << setw(37) << left << "TITLE" << setw(7) << left << "PRICE"; 
			cout << left << "SUBTTL" << endl;

			cout << "------------------------------------------------------------------------------" << endl;

			for (int i = 0; i < checkoutcounter; i++)
			{
				cout << setw(4) << left << quantitylist[i] << setw(20) << left << isbnlist[i];
				cout << setw(37) << left << titlelist[i] << "$" << setw(6) << left << pricelist[i];
				cout << left << "$" << quantitylist[i] * pricelist[i] << endl;
				cout << endl;
			}

			cout << "Your total balance is: $" << setprecision(2) << fixed << totalprice << endl << endl;

		}
		// Receipt
		if (choice == 4)
		{
			// Create Object
			ofstream receipt;
			receipt.open("receipt.txt");

			// Static Information
			receipt << endl << "Serendipity Bookseller Receipt: " << endl;
			receipt << "Date: " << __TIMESTAMP__ << endl << endl;

			// Loop through the 4 arrays and display their information
			for (int b = 0; b < checkoutcounter; b++)
			{
				receipt << "ISBN        :   " << isbnlist[b] << endl;
				receipt << "TITLE       :   " << titlelist[b] << endl;
				receipt << "AUTHOR      :   " << authorlist[b] << endl;
				receipt << "PUBLISHER   :   " << publisherlist[b] << endl << endl;
			}
			// Static information
			receipt << "Subtotal : $" << totalprice << endl;
			receipt << "Tax      : $" << totalprice *.0975 << endl;
			receipt << "Total    : $" << totalprice * 1.0975 << endl << endl;
			cout << "Your receipt has been created." << endl << endl;
			receipt.close();
		}
		if (choice == 5)
		{
	      cout << "Close the receipt window to continue...\n";
		  system("notepad receipt.txt");
		}
	} while (choice != 7); //End at user input 7
}

void inventory(vector<book>& pink) //Inventory module
{
	int choice, book_to_delete, c = 0, a = 0;
	char choice_2;
	string choice_3, savepath;
	while (1)
	{
		cout << endl;
		cout << "       Welcome to the inventory module.     " << endl;
		cout << "      What would you like to accomplish?    " << endl;
		cout << "###############################################\n";
		cout << "#                                             #\n";
		cout << "# 1: Add a book                               #\n";
		cout << "# 2: Remove a book                            #\n";
		cout << "# 3: Edit a book                              #\n";
		cout << "# 4: Save current inventory to disk           #\n";
		cout << "#                                             #\n";
		cout << "# 7: Return to Main Menu                      #\n";
		cout << "#                                             #\n";
		cout << "###############################################\n";
		cin >> choice;
		cout << endl;

		if (choice == 1) //Adding a book
		{
			string title, author, publisher;
			string ISBN;
			int quantitys;
			date added;
			float ourPrice, theirPrice;

			//Prompting user for book info
			cout << "###############################################\n";
			cout << "#                                             #\n";
			cout << "# Add the information prompted for.           #\n";
			cout << "# (When prompted for prices, leave out the    #\n";
			cout << "# (currency value. i.e. when prompted for     #\n";
			cout << "# (price, enter 5, not $5.)                   #\n";
			cout << "#                                             #\n";
			cout << "###############################################\n" << endl;
			cout << "ISBN (without dashes): ";
			cin >> ISBN;
			cout << "Title: ";
			cin.ignore();
			getline(cin, title);
			//These two getlines are not a typo; odd problems were encountered if I only used one
			cout << "Author: ";
			getline(cin, author);
			cout << "Publisher: ";
			getline(cin, publisher);
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
			book blue(title, author, publisher, ourPrice, theirPrice, ISBN, added, quantitys);
			blue.quantity = quantitys;

			//Pushing object into vector of books
			pink.push_back(blue);
		}
		else if (choice == 2) //Deleting a book
		{
			for (; a<book::n; a += 10)
			{
				cout << endl;
				cout << "###############################################\n";
				cout << endl;
				cout << "Now displaying books " << a << " through " << (a + 9) << endl;
				cout << "If the book you wish to delete is listed here," << endl;
				cout << "type 'delete'. Otherwise, type 'next' for the" << endl;
				cout << "next selection of books. To exit, type 'exit'.\n";
				cout << endl;
				cout << "###############################################\n";
				cout << endl;
				for (int b = 0; b<10; b++)
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

				if (choice_3 == "delete")
				{
					cout << "###############################################\n";
					cout << "#                                             #\n";
					cout << "#  Enter in the integer number corresponding  #\n";
					cout << "#    to the book that you wish to delete.     #\n";
					cout << "#                                             #\n";
					cout << "###############################################\n";
					cin >> book_to_delete;

					if (book_to_delete>-1 && book_to_delete<book::n)
					{
						pink.erase(pink.begin() + book_to_delete); //Clear desired book from vector
						cout << endl;
						cout << "###############################################\n";
						cout << "#                                             #\n";
						cout << "#   All data relating to said book has been   #\n";
						cout << "#   removed. (Remember to save your changes.) #\n";
						cout << "#                                             #\n";
						cout << "###############################################\n";
						cout << endl;
						book::n--; //Decremented book counter 
						c = 0; //Reset counter to zero
						break;
					}
					else
					{
						cout << "Invalid selection. Returning to main menu...\n";
						break;
					}
				}
				else if (choice_3 == "exit")
					break;
				else if (choice_3 == "next")
					continue;
				else
					cout << "Invalid choice. Continuing...\n";
			}
			cout << endl;
			cout << "###############################################\n";
			cout << "#                                             #\n";
			cout << "# End of list reached. Exiting to main menu...#\n";
			cout << "#                                             #\n";
			cout << "###############################################\n";
			a = 0;
			c = 0;
		}
		else if (choice == 4) // Implement save function here
		{
			cout << "###############################################\n";
			cout << "#                                             #\n";
			cout << "# Enter in the filename and or filepath for   #\n";
			cout << "# the updated inventory. Your current direct- #\n";
			cout << "#-ory is shown for convienence. (To overwrite #\n";
			cout << "# the original file, type 'Inventory.csv')    #\n";
			cout << "#                                             #\n";
			cout << "###############################################\n";
			cout << endl;
			system("dir /d /b /on");
			cout << endl;
			cin >> savepath;
			cout << endl;
			cout << "###############################################\n";
			cout << "#                                             #\n";
			save(pink, book::n, savepath); //Saves vectors to file
			//system("afplay start_save.mp3");
			cout << "#                  Saved!                     #\n";
			//system("afplay save.mp3");
			cout << "#                                             #\n";
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
			cout << "#                                             #\n";
			cout << "# Enter in your search term below.            #\n";
			cout << "# The term can be an ISBN, title, author,     #\n";
			cout << "# quantity in the inventory, date added to    #\n";
			cout << "# inventory, or the price of the book.        #\n";
			cout << "#                                             #\n";
			cout << "# Note: Search term is non-case sensitive.    #\n";
			cout << "#                                             #\n";
			cout << "###############################################\n";
			cout << endl;
			getline(cin, schItem); // to ignore the previous line
			getline(cin, schItem);
			schBks(pink, itmsFndArr, bksFnd, schItem);
			if (bksFnd > 0)
			{
				for (int i = 0; i < bksFnd; i++)
				{
					cout << "\n" << i + 1 << ". \n";
					displayBook(pink[itmsFndArr[i]]);
				}
				cout << endl;
				cout << "###############################################\n";
				cout << "#                                             #\n";
				cout << "# Please enter the book number of your choice #\n";
				cout << "# for editing.                                #\n";
				cout << "#                                             #\n";
				cout << "###############################################\n";
				cin >> editItemNo;
				while (editItemNo < 1 || editItemNo > bksFnd)
				{
					cout << "Oops! Please enter a number between 1 and " << bksFnd << ": \n\n";
					cin >> editItemNo;
				}
				editItemNo = itmsFndArr[editItemNo - 1];
				system("cls");
				cout << "The Book to edit:\n"
					<< "-----------------\n";
				displayItmzBook(pink[editItemNo]);
				editField = 'a';
				while (editField >= 'a' && editField <= 'h')
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

		else if (choice == 7) // Quits inventory module
			break;
		else
		{
			cout << "Invalid entry. Try again?\n";
			cout << "('Y' key for yes; any other key to exit.)\n";
			cin >> choice_2;
			if (choice_2 == 'Y')
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
	float total_wholesale = 0;
	float total_retail = 0;
	vector<int> dates_to_sort(book::n);

	while (1)
	{
		cout << endl;
		cout << "\n        Welcome to the report module.\n";
		cout << "What kind of report would you like to generate?\n";
		cout << "###############################################\n";
		cout << "#                                             #\n";
		cout << "# 1: Inventory List                           #\n";
		cout << "# 2: Sort and list by Quantity                #\n";
		cout << "# 3: Sort and list by Cost                    #\n";
		cout << "# 4: Sort and list by Age                     #\n";
		cout << "#                                             #\n";
		cout << "# 7: Return to Main Menu                      #\n";
		cout << "#                                             #\n";
		cout << "###############################################\n";
		cin >> choice;
		cout << endl;

		if (choice == 1) // list
		{
			report_message();
			system("cls");
			//cout << "Press enter to step through each book.\n";
			cout << endl;
			for (int a = 0; a<book::n; a++)
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
				total_wholesale += pink[a].ourPrice;
				total_retail += pink[a].theirPrice;
				getchar();
			}
			cout << endl << endl << "###############################################\n";
			cout << endl;
			cout << "TOTAL WHOLESALE VALUE  :  $" << total_wholesale << endl;
			cout << "TOTAL RETAIL VALUE     :  $" << total_retail << endl;
			cout << endl;
			cout << "###############################################\n";
			total_wholesale = 0;
			total_retail = 0; //reset for next invocation
		}

		else if (choice == 2) // quantity
		{
			report_message();
			system("cls");
			cout << "Press enter to step through each book.\n";
			cout << endl;
			sort(pink.begin(), pink.end(), sortByQuantity); //sorts vector by quantity
			for (int b = 0; b<book::n; b++)
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

		else if (choice == 3) // cost
		{
			report_message();
			system("cls");
			cout << "Press enter to step through each book.\n";
			cout << endl;
			sort(pink.begin(), pink.end(), sortByCost); //sorts vector by cost
			for (int c = 0; c<book::n; c++)
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
		else if (choice == 4) // sorts vector by date
		{
			report_message();
			system("cls");
			cout << "Press enter to step through each book.\n";
			cout << endl;
			sort(pink.begin(), pink.end(), sortByAge);
			for (int d = 0; d<book::n; d++)
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
		else if (choice == 7)
			break;
		else
		{
			cout << "###############################################\n";
			cout << "#                                             #\n";
			cout << "#          Invalid entry. Try again?          #\n";
			cout << "#  ('Y' key for yes; any other key to exit.)  #\n";
			cout << "#                                             #\n";
			cout << "###############################################\n";
			cin >> choice_2;
			if (choice_2 == 'Y')
				continue;
			else
				break;
		}
	}
}

int main() //Used for reading in file, and for selecting the appropriate module
{
	string titlein, authorin, publisherin, filepath, ISBNin;
	int monthhold, dayhold, yearhold, quantityin, choice, return_value;
	float ourprice, theirprice;
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
	cout << "*           Ybb=======================\\       *" << endl;
	cout << "*            Y888888888888888888DSI8888b      *\n";
	cout << "*                                             *\n";
	cout << "***********************************************\n";
	cout << endl << endl << "                 LOADING...                    \n";
	system("ping 1.1.1.1 -n 1 -w 5000 > nul"); // wait for 3 seconds
	system("cls");

	//system("afplay start.mp3"); //Only on Macs

start:
	cout << "###############################################\n";
	cout << "#                                             #\n";
	cout << "# Enter the location of the inventory csv.    #\n";
	cout << "# By default, the file is stored in the same  #\n";
	cout << "# directory as this program, and should be    #\n";
	cout << "# titled 'Inventory.csv'. If you're using a   #\n";
	cout << "# csv file, specifiy the name and or filepath.#\n";
	cout << "# A listing of your current working directory #\n";
	cout << "# has been provided for your convenience.     #\n";
	cout << "#                                             #\n";
	cout << "###############################################\n";
	cout << endl;
	system("dir /d /b /on");
	cout << endl;
	cin >> filepath;
	source.open(filepath);
	try{
		if (source){
			source >> allocate;
			getline(source, titlein);
			getline(source, titlein);
			vector<book> pink(allocate); //Reads from file and creates a vector to store book information in

			for (int x = 0; x<allocate; x++)
			{
				getline(source, pink[x].ISBN, ',');
				getline(source, pink[x].title, ',');
				getline(source, pink[x].author, ',');
				getline(source, pink[x].publisher, ',');
				source >> pink[x].added.month >> throwaway >> pink[x].added.day >> throwaway >> pink[x].added.year >> throwaway;
				source >> pink[x].quantity >> throwaway >> pink[x].ourPrice >> throwaway >> pink[x].theirPrice;
				remove_if(pink[x].ISBN.begin(), pink[x].ISBN.end(), ::isspace);
				book::n++;
			}

			while (1)
			{
				try
				{
					cout << endl;
					cout << "     Which module would you like to load?\n";
					cout << "###############################################\n";
					cout << "#                                             #\n";
					cout << "# 1: Cashier Module                           #\n";
					cout << "# 2: Inventory Module                         #\n";
					cout << "# 3: Report Module                            #\n";
					cout << "# 4: Credits                                  #\n";
					cout << "#                                             #\n";
					cout << "# 8: Exit                                     #\n";
					cout << "#                                             #\n";
					cout << "###############################################\n";
					cin >> choice;

					if (choice == 1)
						cashier(pink);

					else if (choice == 2)
						inventory(pink);

					else if (choice == 3)
						reports(pink); // call report module and pass it the vector with all of the book objects

					else if (choice == 8)
					{
						cout << endl;
						cout << "###############################################\n";
						cout << "#                                             #\n";
						cout << "# WARNING: Any changes made to the inventory  #\n";
						cout << "# file will be lost, if it has not already    #\n";
						cout << "# been saved. Would you like to save now?     #\n";
						cout << "# ('Y' saves, any other key will exit.)       #\n";
						cout << "#                                             #\n";
						cout << "###############################################\n" << endl;
						string save_choice, savepath;
						cin >> save_choice;
						if (save_choice == "Y" || save_choice == "y")
						{
							cout << endl;
							cout << "###############################################\n";
							cout << "#                                             #\n";
							cout << "# Enter in the filename and or filepath for   #\n";
							cout << "# the updated inventory. Your current direct- #\n";
							cout << "#-ory is shown for convienence. (To overwrite #\n";
							cout << "# the original file, type 'Inventory.csv')    #\n";
							cout << "#                                             #\n";
							cout << "###############################################\n";
							cout << endl;
							system("dir /d /b /on");
							cout << endl;
							cin >> savepath;
							cout << endl;
							cout << "###############################################\n";
							cout << "#                                             #\n";
			                cout << "#                  Saved!                     #\n";
							cout << "#                                             #\n";
							cout << "###############################################\n";
							save(pink, book::n, savepath); //Saves vectors to file
							//system("afplay start_save.mp3");
							//system("afplay save.mp3");
						}
						cout << endl;
						cout << "###############################################\n";
						cout << "#                                             #\n";
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

					else if (choice == 4)
					{
						system("cls");
						cout << "***********************************************\n";
						cout << "*                                             *\n";
						cout << "*            ARiA copyrighted 2015            *\n";
						cout << "*           Chrysanthemum Industries          *\n";
						cout << "*                                             *\n";
						cout << "*                  /:.   ,:\\""                  *" << endl;
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
						cin.get(); cin.get();
						system("cls");
						cout << "###############################################\n";
						cout << "#                                             #\n";
						cout << "# Software title: ARiA Business Suite         #\n";
						cout << "#                                             #\n";
						cout << "# Publisher: Chrysanthemum Industries, 2015   #\n";
						cout << "#                                             #\n";
						cout << "# Developers: Roark Burney, Zachary Prince,   #\n";
						cout << "#             Chris Yu, Abdollah Kasraie      #\n";
						cout << "#                                             #\n";
						cout << "# Cashier Module: Chris Yu                    #\n";
						cout << "#                                             #\n";
						cout << "# Reports Module: Zachary Prince              #\n";
						cout << "#                                             #\n";
						cout << "# Inventory Module:                           #\n";
						cout << "#                                             #\n";
						cout << "#   Add function: Zachary Prince              #\n"; 
						cout << "#   Edit function: Abdollah Kasraie           #\n";
						cout << "#   Remove, write, read functions: R. Burney  #\n"; 
						cout << "#                                             #\n";
						cout << "# Aesthetics & Menus: Zachary Prince          #\n";
						cout << "# (except for Cashier: Chris Yu)              #\n";
						cout << "# (and Edit: Abdollah Kasraie)                #\n";
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
					cout << "#                                             #\n";
					cout << "# Exception occurred. Most likely the result  #\n";
					cout << "# of an incorrect number choice. Restarting...#\n";
					cout << "#                                             #\n";
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
		cout << "#                                             #\n";
		cout << "# Exception occurred. File not found. Retry?  #\n";
		cout << "#                                             #\n";
		cout << "# ('N' to exit; any other key to retry.)      #\n";
		cout << "###############################################\n";
		cout << endl;
		cin >> continue_choice;
		if (continue_choice == "N" || continue_choice == "n")
		{
		}
		else
		{
			goto start;
		}
	}
}