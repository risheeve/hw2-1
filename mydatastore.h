#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include <map>
#include <set>
#include <vector>
#include <string>
#include "product.h"
#include "user.h"

class MyDataStore : public DataStore {
public:
    MyDataStore();
    virtual ~MyDataStore();

    virtual void addProduct(Product* p);
    virtual void addUser(User* u);
    virtual std::vector<Product*> search(std::vector<std::string>& terms, int type);
    virtual void dump(std::ostream& ofile);
    virtual void addToCart(const std::string& username, Product* p);
    virtual void viewCart(const std::string& username);
    virtual void buyCart(const std::string& username);


private:
    std::vector<User*> users;
    std::vector<Product*> products;
    std::map<std::string, std::set<Product*>> keywordToProductMap;
    std::map<std::string, std::vector<Product*>> userCarts; 
};

#endif // MYDATASTORE_H
