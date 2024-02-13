#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <map>
#include <queue>
#include "datastore.h"

class MyDataStore : public DataStore {
public:
     virtual ~MyDataStore();

    /**
     * Adds a product to the data store
     */
     void addProduct(Product* p);

    /**
     * Adds a user to the data store
     */
     void addUser(User* u);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
     std::vector<Product*> search(std::vector<std::string>& terms, int type);

    /**
     * Reproduce the database file from the current Products and User values
     */
     void dump(std::ostream& ofile);


    void buyCart(const std::string& username);

    void viewCart(const std::string& username);

    void addCart(const std::string& username, Product* prod);

private:
//include map
    std::map<std::string, std::set<Product*>> products;
    std::set<User*> users;
    std::set<Product*> prod_set;
    std::map<std::string, std::queue<Product*>> cart;

};
#endif