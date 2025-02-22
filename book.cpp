#include "book.h"

using namespace std;

// Instantiate a book type that has a name, price, qty, idbn, and author.
Book::Book(const string& name, double price, int qty, const string& isbn, const string& author) 
: Product("book", name, price, qty) {
  isbn_ = isbn;
  author_ = author;
}

// Keywords are the isbn and author of the book
std::set<std::string> Book::keywords() const {
  std::set<std::string> kwords;
  std::set<std::string> keys_name = parseStringToWords(name_);
  std::set<std::string> keys_author = parseStringToWords(author_);
  kwords.insert(keys_name.begin(), keys_name.end());
  kwords.insert(isbn_);
  // kwords.insert(convToLower(author_));
  kwords.insert(keys_author.begin(), keys_author.end());
  return kwords;
}

// Displays all items as a string
std::string Book::displayString() const {
  std::ostringstream os;

  os << name_ << endl;
  os << "Author: " << author_ << " ISBN: " << isbn_ << endl;
  os << price_ << " " << qty_ << " left." << std::endl;

  return os.str();
}

// Output all book attributes in the format of database
void Book::dump(std::ostream& os) const {
  os << "book" << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << std::endl;
}