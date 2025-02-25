#ifndef MOVIE_H
#define MOVIE_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <sstream>

#include "product.h"
#include "util.h"

class Movie : public Product {
  public:
  Movie(const std::string name, double price, int qty, std::string genre, std::string rating);

  std::set<std::string> keywords() const;

  std::string displayString() const;

  void dump(std::ostream& os) const;

  private:
  std::string genre_;
  std::string rating_;

};


#endif