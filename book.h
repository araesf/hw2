#ifndef BOOK_H
#define BOOK_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <sstream>

#include "product.h"
#include "util.h"

class Book : public Product {
  public:
  // Instantiate a book type that has a name, price, qty, idbn, and author.
  Book(const std::string& name, double price, int qty, const std::string& isbn, const std::string& author);

  std::set<std::string> keywords() const;

  std::string displayString() const;

  void dump(std::ostream& os) const;

  private:
  std::string isbn_;
  std::string author_;
};
#endif