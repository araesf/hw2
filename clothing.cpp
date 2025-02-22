#include "clothing.h"
#include <sstream>

Clothing::Clothing(const std::string& name, double price, int qty, const std::string& size, const std::string& brand) 
: Product("clothing", name, price, qty) {
  size_ = size;
  brand_ = brand;
}

// Keywords are the name, brand, and size of the clothing
std::set<std::string> Clothing::keywords() const {
  std::set<std::string> kwords;
  std::set<std::string> keys_name = parseStringToWords(name_);
  std::set<std::string> keys_brand = parseStringToWords(brand_);
  kwords.insert(keys_name.begin(), keys_name.end());
  kwords.insert(keys_brand.begin(), keys_brand.end());
  return kwords;
}

// Displays all items as a string
std::string Clothing::displayString() const {
  std::ostringstream os;
  os << name_ << std::endl;
  os << "Size: " << size_ << " Brand: " << brand_ << std::endl;
  os << price_ << " " << qty_ << " left.";
  
  return os.str();
}

// Output all clothing attributes in the format of database
void Clothing::dump(std::ostream& os) const {
  os << "clothing" << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << std::endl;
}

  

