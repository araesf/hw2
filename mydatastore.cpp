#include "mydatastore.h"

MyDataStore::MyDataStore() {}

MyDataStore::~MyDataStore() {
  // delete products
  for (Product* product : products) {
    delete product;
  }

  // delete users
  std::vector<User*>::iterator it;
  for (it = user_list.begin(); it != user_list.end(); it++) {
    delete *it;
  }

  products.clear();
  user_list.clear();
  last_search.clear();
  mapped_words.clear();
}


// Add Product to Map
void MyDataStore::addProduct(Product* p) {

  // add to products vector
  products.push_back(p);

  // also add to keywords
  std::set<std::string> uniques = p->keywords();
  for (std::string s : uniques) {
    std::string lower_s = convToLower(s);
    mapped_words[lower_s].insert(p);

    // DEBUG
    // std::cout << "Product " << s << " added to map as: " << lower_s << std::endl;
  }
}

// Search Function
/* convert terms to indiviual keywords to search with
- if it is an AND search, check if the keyword has multiple keys.
- if it has multiple keys, check to see if the values (products) of the keys are the same
- if value is seen in both keys, return the value. 
*/
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
  std::vector<std::set<Product*>> temp;

  if (terms.empty() || type > 1 || type < 0) {
    return {};
  }

  for (std::string& term : terms) {
    std::string lower_term = convToLower(term);
    std::map<std::string, std::set<Product*>>::iterator it = mapped_words.find(lower_term);

    if (it == mapped_words.end()) {
      // if it is an AND search, return
      if (type == 0 && temp.empty()) {
        return {};
      }
        continue;
    }

    temp.push_back(it->second);
  }

  if (temp.empty()) {
    return {};
  }

  std::set<Product*> preconvert_result = temp[0];
  if (temp.size() > 1) {
    // do a union of temp
    if (type == 1) {
      for (int i = 1; i < temp.size(); i++) {
        preconvert_result = setUnion(preconvert_result, temp[i]);
      }
    }

    // do an intersection of temp
    else if (type == 0) {
      for (int i = 1; i < temp.size(); i++) {
        preconvert_result = setIntersection(preconvert_result, temp[i]);
      }
    }
  }

  // insert the intersection/union set (must convert) into last_search vector and return
  last_search = std::vector<Product*>(preconvert_result.begin(), preconvert_result.end());
  return last_search;
}

// Adding to Cart
void MyDataStore::addToCart(User* u, size_t hit_order_index) {
  if ((hit_order_index <= 0) || (last_search.size() < hit_order_index) || (last_search.empty())) {
    std::cout << "Invalid request" << std::endl;
    return;
  }

  Product* prod = last_search[hit_order_index - 1];
  user_cart[u].push_back(prod);
}

// Adding User
void MyDataStore::addUser(User* u) {
  user_list.push_back(u);
  user_cart[u] = {};
}

// View Cart
void MyDataStore::viewCart(User* u) {
  if (user_cart.find(u) == user_cart.end()) {
    std::cout << "Invalid username" << std::endl;
    return;
  }

  // return if there are no items in this user's cart
  else if (user_cart[u].size() < 1) {
    return;
  }

  else {
    // std::cout << "User's Products: ";
    for (int i = 0; i < user_cart[u].size(); i++) {
      std::cout << "Item: " << (i + 1) << std::endl;
      std::cout << user_cart[u][i]->displayString() << std::endl;
      std::cout << std::endl;
    }
  }
}

// Buy the Cart
void MyDataStore::buyCart(User* u) {

  std::map<User*, std::vector<Product*>>::iterator cart_it = user_cart.find(u);

  if (cart_it == user_cart.end()) {
    std::cout << "Invalid username" << std::endl;
    return;
  }

  // return if there are no items in this user's cart
  else if (cart_it->second.size() < 1) {
    return;
  }

  std::vector<Product*>::iterator product_it = cart_it->second.begin();
  while (product_it != cart_it->second.end()) {
    Product* current_product = *product_it;
    double price_of_item = current_product->getPrice();
    int quantity = current_product->getQty();
    double user_balance = u->getBalance();
    
    if ((quantity > 0) && (user_balance >= price_of_item)) {
      u->deductAmount(price_of_item);
      current_product->subtractQty(1);
      product_it = cart_it->second.erase(product_it);
    }
    else {
      product_it++;
    }
  }
}

// DUMP/QUIT Function
void MyDataStore::dump(std::ostream& ofile) {
  // matching database.txt formatting
  ofile << "<products>" << std::endl;
  for (int i = 0; i < products.size(); i++) {
    products[i]->dump(ofile);
  }

  ofile << "</products>" << std::endl;
  ofile << "<users>" << std::endl;

  for (int i = 0; i < user_list.size(); i++) {
    user_list[i]->dump(ofile);
  }

  ofile << "</users>" << std::endl;
}

User* MyDataStore::getUser(std::string user_string) {
  // create iterator to iterate through USER_LIST. return the user

  for (int i = 0; i < user_list.size(); i++) {
    // since case insensitive
    if (convToLower(user_list[i]->getName()) == convToLower(user_string)) {
      return user_list[i];
    }
  }

  return nullptr;
}



  

