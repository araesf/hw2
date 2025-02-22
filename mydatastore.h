#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include "util.h"
#include <map>
#include <vector>
#include <iostream>

class MyDataStore : public DataStore {
public:

  MyDataStore();
  ~MyDataStore();

  void addProduct(Product* p) override;

  /**
    * Adds a user to the data store
    */
  void addUser(User* u) override;

  /**
    * Performs a search of products whose keywords match the given "terms"
    *  type 0 = AND search (intersection of results for each term) while
    *  type 1 = OR search (union of results for each term)
    */
  std::vector<Product*> search(std::vector<std::string>& terms, int type) override;

  /**
    * Reproduce the database file from the current Products and User values
    */
  void dump(std::ostream& ofile) override;

  // Adding to a User Cart
  void addToCart(User* u, size_t hit_order_index);

  // View User Cart
  void viewCart(User* u);

  // Buy User Cart
  void buyCart(User* u);

  // Retrieve Get User Pointer
  User* getUser(std::string username);

private:
  std::map<std::string, std::set<Product*>> mapped_words;
  std::map<User*, std::vector<Product*>> user_cart;
  std::vector<Product*> products;
  std::vector<Product*> last_search;
  std::vector<User*> user_list;
};

#endif