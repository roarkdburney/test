//Copyright Chrysanthemum Industries
// Roarke Burney, Zachary Prince
// Abdollah Kasraie, Chris Yu 
// 03/04/2015

#include<iostream>
#include<iomanip>
#include<fstream>
#include<string> // Needed for string operations
#include<vector> // Needed for vectors
#include<algorithm> // Needed for sort function

using namespace std;

class date
{
  public:
    int day,month,year;
};

class book
{
  public:
    static int n; //A counter to keep track of how many book objects have been created
    string title,author,publisher;
    int ISBN;
    int quantity;
    date added;
    float ourPrice,theirPrice;

    //Constructors 
    book() {n++;};
    book(string titlein,string authorin,string publisherin,float wholesaleIs,float retailIs,float isbnin,date addedin,int quantityin) {n++};

    //Add/read/remove/save prototypes
    vector<book> add(vector<book>,int allocate,string titlein,string authorin,string publisherin,float wholesaleIs,float retailIs,float isbnin,date addedin,int quantityin);
    vector<book> read(ifstream &source);
    vector<book> remove(vector<book>, int allocate, int location);
    void save(vector<book>, int allocate, string path);
    
    //NOTE: Do NOT add the decrement operator, i.e. {n--;} 
    //to a class destructor for the counter of objects here.
    //It fucks up the sort method, for reasons beyond my understanding.
    //It is for this reason that I suggest that the decrement be used solely in the cashier module, not in the class destructor
};

int book::n=0; //Intitializes static counter in book class to zero

string filepath="Inventory.csv";

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

int combine(int a, int b)
{
   int times = 1;
   while (times <= b)
      times *= 10;
   return a*times + b;
} 

void cashier() //Cashier module
{
}

void inventory() //Inventory module
{
}

void reports(vector<book>& pink) // Report module 
{
  //bool sortByQuantity(const book &one, const book &two) {return one.quantity>two.quantity;} 
  //bool sortByCost(const book &one, const book &two) {return one.ourPrice>two.ourPrice;}
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
  cout << "   ╔═════════════════════════╗" << endl;
  cout << "     SERENDIPITY BOOKSELLERS " << endl;
  cout << "   ╚═════════════════════════╝" << endl << endl;
  cout << "  dBBBBBBBBBBBBBBBBBBBBBBBBb\n";
  cout << " BP YBBBBBBBBBBBBBBBBBBBBBBBb\n";
  cout << "dB   YBb                 YBBBb\n";
  cout << "dB    YBBBBBBBBBBBBBBBBBBBBBBBb\n";
  cout << " Yb    YBBBBBBBBBBBBBBBBBBBBBBBb\n";
  cout << "  Yb    YBBBBBBBBBBBBBBBBBBBBBBBb\n";
  cout << "   Yb    YBBBBBBBBBBBBBBBBBBBBBBBb\n";
  cout << "    Yb    YBBBBBBBBBBBBBBBBBBBBBBBb\n";
  cout << "     Yb    YBBBBBBBBBBBBBBBBBBBBBBBb\n";
  cout << "      Yb   dBBBBBBBBBBBBBBBBBBBBBBBBb\n";
  cout << "       Yb dP=======================/\n";
  cout << "        YbB=======================(\n";
  cout << "         Ybb=======================\\ "<< endl;
  cout << "          Y888888888888888888DSI8888b\n";
  cout << endl << endl;

  source.open(filepath);
  source>>allocate;
  getline(source, titlein);
  getline(source, titlein);
  vector<book> pink(allocate); //Reads from file and creates a vector to store book information in
  
  //Note: I've changed it from reading into an array to reading into a vector due to the vector's superior member functions,
  //and ability to be used with the std::sort method
  
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
      inventory();

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

//Book constructor function
book::book(string titlein,string authorin,string publisherin,float ourPriceIs,float theirPriceIs,float isbnin,date addedin,int quantityin){ 
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

//Add function
vector<book> book::add(vector<book> starting,int allocate,string titlein,string authorin,string publisherin,float wholesaleIs,float retailIs,float isbnin,date addedin,int quantityin){
    vector<book> added;
    book addee(titlein,authorin,publisherin,wholesaleIs,retailIs,isbnin,addedin,quantityin);
    added = vector<book>(allocate+1);
    for (int x=0; x<allocate; x++) {
        added[x]=starting[x];
    }
    added[allocate]=addee;
    return added;
};

//Save function
void book::save(vector<book> inventory, int allocate, string path){
    ofstream output;
    output.open(path);
            output<<allocate<<",,,,,,,"<<endl<<"ISBN,TITLE,AUTHOR,PUBLISHER,Date Added,Quantity On Hand,Wholesale Price,Retail" <<endl;
    for (int x=0; x<allocate; x++) {

        output<<inventory[x].ISBN<<',';
        output<<inventory[x].title<<',';
        output<<inventory[x].author<<',';
        output<<inventory[x].publisher<<',';
        output<<inventory[x].added.month<<'/'<<inventory[x].added.day<<'/'<<inventory[x].added.year<<',';
        output<<inventory[x].quantity<<','<<inventory[x].ourPrice<<','<<inventory[x].theirPrice<<endl;
    }
    output.close();
};

//Remove function
vector<book> book::remove(vector<book> inventory, int allocate, int location){
    book star;
    for (int x=location; x<allocate-1; x++) {
        inventory[x]=inventory[x+1];
    }
    date removed;removed.day=0;removed.month=0;removed.year=0;
    inventory[allocate-1].title='\0';
    inventory[allocate-1].author='\0';
    inventory[allocate-1].publisher='\0';
    inventory[allocate-1].ISBN=0;
    inventory[allocate-1].ourPrice=0;
    inventory[allocate-1].theirPrice=0;
    inventory[allocate-1].added=removed;
    inventory[allocate-1].quantity=0;
    return inventory;
}
