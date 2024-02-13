#include "mydatastore.h"
#include "util.h"
#include <iostream>
#include <algorithm>
#include <iterator>

MyDataStore::MyDataStore() {}

MyDataStore::~MyDataStore() {
    // Properly deallocate memory for products
    for(std::vector<Product*>::iterator it = products.begin(); it != products.end(); ++it) {
        delete *it;
    }
    // Properly deallocate memory for users
    for(std::vector<User*>::iterator it = users.begin(); it != users.end(); ++it) {
        delete *it;
    }
}

void MyDataStore::addProduct(Product* p) {
    products.push_back(p);
    std::set<std::string> keywords = p->keywords();
    for(std::set<std::string>::iterator keyword_it = keywords.begin(); keyword_it != keywords.end(); ++keyword_it) {
        keywordToProductMap[*keyword_it].insert(p);
    }
}

void MyDataStore::addUser(User* u) {
    users.push_back(u);
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
    std::set<Product*> resultSet;
    if(type == 0) { // AND search
        bool firstTerm = true;
        for(std::vector<std::string>::iterator term_it = terms.begin(); term_it != terms.end(); ++term_it) {
            if(keywordToProductMap.find(*term_it) != keywordToProductMap.end()) {
                if(firstTerm) {
                    resultSet = keywordToProductMap[*term_it];
                    firstTerm = false;
                } else {
                    std::set<Product*> tempSet;
                    std::set_intersection(resultSet.begin(), resultSet.end(),
                                          keywordToProductMap[*term_it].begin(), keywordToProductMap[*term_it].end(),
                                          std::inserter(tempSet, tempSet.begin()));
                    resultSet = tempSet;
                }
            } else {
                resultSet.clear();
                break;
            }
        }
    } else if(type == 1) { 
        for(std::vector<std::string>::iterator term_it = terms.begin(); term_it != terms.end(); ++term_it) {
            if(keywordToProductMap.find(*term_it) != keywordToProductMap.end()) {
                std::set<Product*>& tempSet = keywordToProductMap[*term_it];
                resultSet.insert(tempSet.begin(), tempSet.end());
            }
        }
    }

    return std::vector<Product*>(resultSet.begin(), resultSet.end());
}

void MyDataStore::dump(std::ostream& ofile) {
    ofile << "<products>" << std::endl;
    for(std::vector<Product*>::iterator it = products.begin(); it != products.end(); ++it) {
        (*it)->dump(ofile);
    }
    ofile << "</products>" << std::endl;

    ofile << "<users>" << std::endl;
    for(std::vector<User*>::iterator it = users.begin(); it != users.end(); ++it) {
        (*it)->dump(ofile);
    }
    ofile << "</users>" << std::endl;
}
void MyDataStore::addToCart(const std::string& username, Product* p) {
    userCarts[username].push_back(p);
}

void MyDataStore::viewCart(const std::string& username) {
    if (userCarts.find(username) != userCarts.end()) {
        for (std::vector<Product*>::iterator it = userCarts[username].begin(); it != userCarts[username].end(); ++it) {
            std::cout << (*it)->displayString() << std::endl;
        }
    } else {
        std::cout << "No cart found for user: " << username << std::endl;
    }
}

void MyDataStore::buyCart(const std::string& username) {
    if (userCarts.find(username) != userCarts.end()) {
        std::vector<Product*>& cart = userCarts[username];
        for (std::vector<Product*>::iterator it = cart.begin(); it != cart.end();) {
            if ((*it)->getQty() > 0) {
                std::cout << "Purchased: " << (*it)->displayString() << std::endl;
                (*it)->subtractQty(1);
                it = cart.erase(it); // Successfully purchased, remove from cart
            } else {
                ++it; // Skip, cannot purchase
            }
        }
    } else {
        std::cout << "No cart found for user: " << username << std::endl;
    }
}