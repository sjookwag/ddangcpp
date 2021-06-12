#include<iostream>
#include<string>
#include<fstream>
#include<bits/stdc++.h>
#include<vector>
#include<iterator>
#include<conio.h>
#include<sstream>

struct Book
{
    int id;    
    std::string title;    
    std::string author;
    std::string year;
    std::string genre;
    int times_given;
    int available;
};

std::string& replace(std::string& s, const std::string& from, const std::string& to)
{
  if(!from.empty())
    for(size_t pos = 0; (pos = s.find(from, pos)) != std::string::npos; pos += to.size())
      s.replace(pos, from.size(), to);

  return s;
}

void split(const std::string &s, const char delim, std::vector<std::string> &elems) 
{
  std::stringstream ss;
  std::string item;
  
  ss.str(s);
  
  while (std::getline(ss, item, delim)) 
    elems.push_back(item);
}

std::vector<Book> readBooks()
{
  std::vector<Book> book_list;
  std::ifstream book_input_stream("Books.txt");	
  std::string line;
  
  while(std::getline(book_input_stream, line))
  {
    std::vector<std::string> row_values;
    Book b;
    
    split(line, '\t', row_values);
    
    b.id          = std::stoi(row_values[0]);
    b.title       = row_values[1]; 
    b.author      = row_values[2]; 
    b.year        = row_values[3]; 
    b.genre       = row_values[4]; 
    b.times_given = std::stoi(row_values[5]); 
    b.available   = std::stoi(row_values[6]);
    book_list.push_back(b);  
  }
  book_input_stream.close();
	
  return book_list;
}

void writeBooks(std::vector<Book> &book_list)
{
  std::ofstream book_output_stream("Books.txt", std::ofstream::out);	

  for(std::vector<Book>::iterator ptr=book_list.begin();ptr<book_list.end();++ptr){
    book_output_stream << (*ptr).id << "\t" << (*ptr).title << "\t" << (*ptr).author << "\t" << (*ptr).year << "\t" << (*ptr).genre << "\t" << (*ptr).times_given << "\t" << (*ptr).available << std::endl;
  }
  book_output_stream.close();	
}

void showBooks(std::vector<Book> &book_list)
{
  std::cout << std::endl;
  for(std::vector<Book>::iterator ptr=book_list.begin();ptr<book_list.end();++ptr)
  {
    std::cout << (*ptr).id << " " << (*ptr).title << "\t" << (*ptr).author << "\t" << (*ptr).year << "\t" << (*ptr).genre << "\t" << (*ptr).times_given << "\t" << (*ptr).available << std::endl;
  }
  std::cout << " * Sum of Books : " << book_list.size() << std::endl; 
	
}

void deleteBook(std::vector<Book> &book_list)
{
  int id;
  
  if(book_list.empty())
  {
    std::cout << "Sorry, The book list Empty" << std::endl;
    return;
  }
  
  showBooks(book_list);
  
  std::cout << "[Delete] Plz enter book number. [Enter 0 On Exit]" << std::endl;
  std::cin >> id;
  
  if(id==0) return;
  
  if(id<=book_list.size())
  {
    book_list.erase(book_list.begin()+(--id));		
  }
}

void addBook(std::vector<Book> &book_list)
{
  std::cin.ignore(1, '\n');
	
  Book b;

  b.id = ( *( --book_list.end() ) ).id + 1; 
  std::cout << "1. Title       : "; std::getline(std::cin, b.title );
  std::cout << "2. Author      : "; std::getline(std::cin, b.author);
  std::cout << "3. Year        : "; std::getline(std::cin, b.year  );
  std::cout << "4. Genre       : "; std::getline(std::cin, b.genre );
  std::cout << "5. Times Given : "; std::cin >> b.times_given;
  std::cout << "6. Available   : "; std::cin >> b.available;
		
  book_list.push_back(b);
  std::cout << b.title <<" Added!"<< std::endl; 	
}

void searchBook(std::vector<Book> &book_list)
{
  std::string search;
  
  std::cin.ignore(1, '\n');
  std::cout << "Enter title/ author that you want [Enter to cancel ]: "; std::getline(std::cin, search);
  
  if(search.length()!=0)
  {
    for(int i=0; i<search.length(); i++)
      search[i] = std::tolower(search[i]);
    
    for(std::vector<Book>::iterator ptr=book_list.begin();ptr<book_list.end();++ptr)
    {
      std::string strTitle = (*ptr).title, strAuthor = (*ptr).author;
      
      for(int i=0; i<strTitle.length(); i++)
        strTitle[i] = std::tolower(strTitle[i]);
      
      for(int i=0; i<strAuthor.length(); i++)
        strAuthor[i] = std::tolower(strAuthor[i]);
        
      if( strTitle.find(search) != std::string::npos )
        std::cout << "\n\tID: " << (*ptr).id << "\n\tTITLE: " << (*ptr).title << "\n\tAUTHOR: " << (*ptr).author << "\n\tYEAR: " << (*ptr).year << "\n\tGENRE: " << (*ptr).genre << "\n\tTIMES GIVEN: " << (*ptr).times_given << "\n\tAVAILABLE: " << (*ptr).available << std::endl;
        
      if( strAuthor.find(search) != std::string::npos )
        std::cout << "\n\tID: " << (*ptr).id << "\n\tTITLE: " << (*ptr).title << "\n\tAUTHOR: " << (*ptr).author << "\n\tYEAR: " << (*ptr).year << "\n\tGENRE: " << (*ptr).genre << "\n\tTIMES GIVEN: " << (*ptr).times_given << "\n\tAVAILABLE: " << (*ptr).available << std::endl;  
        
    } 
  }
}

void updateBook(std::vector<Book> &book_list)
{  
  int id;
  
  if(book_list.empty())
  {
    std::cout << "Sorry, There is no book to update becasuse the book list Empty" << std::endl;
    return ;
  }
  
  std::cout << "[Update] Plz enter book number. [0 On Exit, Enter For Next] " << std::endl;  
  std::cin >> id;
  
  if(id==0) return;
  
  if(id<=book_list.size())
  {	  
    std::string title, author, genre, year, times_given, available;
    
    Book &b = book_list[--id];
    	  
    std::cin.ignore(1, '\n');
    
    std::cout << "1. Title       : " << b.title       << " <- "; std::getline(std::cin, title);        		
    std::cout << "2. Author      : " << b.author      << " <- "; std::getline(std::cin, author);    
    std::cout << "3. Year        : " << b.year        << " <- "; std::getline(std::cin, year);         // = 2021;    
    std::cout << "4. Genre       : " << b.genre       << " <- "; std::getline(std::cin, genre);        // = "Thriller";     
    std::cout << "5. Times Given : " << b.times_given << " <- "; std::getline(std::cin, times_given);  // = 23;     
    std::cout << "6. Available   : " << b.available   << " <- "; std::getline(std::cin, available);    // = 5;
    
    if(title.length()!=0)   b.title = title;
    if(author.length()!=0)  b.author = author;
    if(genre.length()!=0)   b.genre = genre;
    if(year.length()!=0)    b.year = year;    
    
    if(times_given.length()!=0) 
    {
      try
      {
        b.times_given = std::stoi(times_given);
      }
      catch(const std::invalid_argument& e)   
      {        
        std::cerr << "[Times given] Input Error: " << e.what() << ", You entered " << times_given << std::endl;                
      }
    }
    
    if(available.length()!=0) 
    {
      try
      {
        b.available = std::stoi(available);
      }
      catch(const std::invalid_argument& e)   
      {        
        std::cerr << "[Available] Input Error: " << e.what() << ", You entered " << available << std::endl;                
      }
    }
  }
}

void showLogo()
{
  std::cout << "______________________________________________________________________" << std::endl;
  std::cout << "    _______                        " << std::endl;
  std::cout << "   /      /,                       " << std::endl;
  std::cout << "  /      // DDang's Book STORE     " << std::endl;
  std::cout << " /______//                         " << std::endl;
  std::cout << "(______(/ Please make a selection: " << std::endl;
  std::cout << "______________________________________________________________________" << std::endl;  
  std::cout << std::endl;
}

enum{ LIST=1, ADD, DELETE, UPDATE, SEARCH, SAVE, EXIT };

int main(int argc, char** argv) {
  
  std::vector<Book> book_list = readBooks();
  int selection { 0 }; 
  bool invalid  { true }; // new variable just to gate the loop

  showLogo();
  while (invalid)
  {
    std::cout << "1) List\n";
    std::cout << "2) Add a book\n";
    std::cout << "3) Delete a book\n";
    std::cout << "4) Update a book\n";
    std::cout << "5) Search books by title and author\n";    
    std::cout << "6) Save List\n";    
    std::cout << "9) Exit : ";

    std::cin >> selection;
    invalid = !( true
       && selection != 1 
       && selection != 2 
       && selection != 3 
       && selection != 4
       && selection != 5
       && selection != 6
    );
    
    switch(selection)
    {
      case LIST:
        std::cout << "1) List\n";
        showBooks(book_list);
        break;
      case ADD:
        std::cout << "2) Add a book\n";
        addBook(book_list);
        break;
      case DELETE:
        std::cout << "3) Delete a book\n";
        deleteBook(book_list);
        break;
      case UPDATE:
        std::cout << "4) Update a book\n";
        updateBook(book_list);
        break;
      case SEARCH:
        std::cout << "5) Update a book\n";
        searchBook(book_list);
        break;  
      case SAVE:
        std::cout << "6) Save list\n";
        writeBooks(book_list);
        break;
      case EXIT:
        return 0; 
    }
    std::cout << std::endl << std::endl;  
  }
  return 0;
}
