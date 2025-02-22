#include "movie.h"

using namespace std;

Movie::Movie(const std::string name, double price, int qty, std::string genre, std::string rating) : Product("movie", name, price, qty){
    genre_ = genre;
    rating_ = rating;
  }

// Keywords are the name and genre of the clothing
std::set<std::string> Movie::keywords() const {
  std::set<std::string> kwords;
  std::set<std::string> keys_name = parseStringToWords(name_);
  kwords.insert(keys_name.begin(), keys_name.end());
  kwords.insert(convToLower(genre_));
  return kwords;
}

// Displays all items as a string
std::string Movie::displayString() const {
  std::ostringstream os;
  os << name_ << endl;
  os << "Genre: " << genre_ << " Rating: " << rating_ << endl;
  os << price_ << " " << qty_ << " left." << std::endl;

  return os.str();
}

// Output all movie attributes in the format of database
void Movie::dump(std::ostream& os) const {
  os << "movie" << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << std::endl;
}