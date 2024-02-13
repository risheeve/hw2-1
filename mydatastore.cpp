#include "mydatastore.h"
#include "util.h"
#include <iomanip>
#include <queue>

MyDataStore::~MyDataStore() {
    // Delete all users
    for (User* user : users) {
        delete user;
    }
    users.clear(); // Clear the set after deleting all users

    // Delete all products
    for (Product* product : prod_set) {
        delete product;
    }
    prod_set.clear(); // Clear the set after deleting all products
}


void MyDataStore::addProduct(Product* p) {

    // iterate through the keywords for the product provided
    std::set<std::string>::iterator it;
    std::set<std::string> temp = p->keywords();
    for(it = temp.begin(); it != temp.end(); ++it) {
        // if the keywords from the current product already exists in the map of products, then add
        products[(*it)].insert(p);
    }
    prod_set.insert(p);
}   


void MyDataStore::addUser(User* u) {
    users.insert(u);
}
 /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
    
    std::set<Product*> final = products[convToLower(terms[0])];

    if(type == 0) {
        for (size_t i = 1; i < terms.size(); i++) {
            final = setIntersection(final, products[convToLower(terms[i])]);
        }
    }
    else if (type == 1) {
        for (size_t i = 1; i < terms.size(); i++) {
            final = setUnion(final, products[convToLower(terms[i])]);
        }
    }

    std::vector<Product*> vec(final.begin(), final.end());

    return vec;
    
}

/**
     * Reproduce the database file from the current Products and User values
     */
void MyDataStore::dump(std::ostream& ofile) {

    std::set<Product*>::iterator it;
    
    ofile << "<products>" << std::endl;

    for(it = prod_set.begin(); it != prod_set.end(); ++it) {
        // ofile << (*it)->displayString();
        (*it)->dump(ofile);
    }

    ofile << "</products>" << std::endl;

    ofile << "<users>" << std::endl;
    std::set<User*>::iterator it2;
    for(it2 = users.begin(); it2 != users.end(); ++it2) {
        (*it2)->dump(ofile);
    }
    ofile << "</users>" << std::endl;
}


void MyDataStore::addCart(const std::string& username, Product* prod) {

    bool found = false;
    std::set<User*>::iterator it;

    for(it = users.begin(); it != users.end(); ++it) {
        if((*it)->getName() == username) {
            found = true;
            if(cart.find(username) != cart.end()) {
                // std::cout << "Pushing a 2nd product" << std::endl;
                cart[username].push(prod);
                // std::cout << "Size of cart: " << cart[username].size() << std::endl;
            }
            else {
                std::queue<Product*> prod_queue;
                prod_queue.push(prod);
                cart.insert(make_pair(username, prod_queue));
            }   
        }
    }
    
    if(found == false) {
        std::cout << "Invalid request" << std::endl;
    }
}


void MyDataStore::viewCart(const std::string& username) {
    // checks is username exists in set of users
    bool found = false;
    int index = 1;
    std::set<User*>::iterator it;

    for(it = users.begin(); it != users.end(); ++it) { 
        if((*it)->getName() == username) {
            found = true;
             // access the cart of the user
            std::queue<Product*> curr_cart = cart[username];
            // display products
            if(curr_cart.empty()) {
                std::cout << "Empty Cart" << std::endl;
            }
            else {
                // std::cout << "Cart size: " << curr_cart.size() << std::endl;
                size_t cartSize = curr_cart.size();
                for(size_t i = 0; i < cartSize; i++) {
                    // create temp product that stores the first product in cart
                    Product* temp = curr_cart.front();
                    // print temp product details
                    std::cout << "Item " << index << std::endl;
                    std::cout << temp->displayString() << std::endl;
                    // pop the first term that's been printed from the current cart
                    curr_cart.pop();
                    index++;
                }
            }
        }
    } 

    if(found == false) {
        std::cout << "Invalid username" << std::endl;
    }
}


void MyDataStore::buyCart(const std::string& username) {

    // Check if the user exists
    std::set<User*>::iterator userIt;
    User* user;
    bool found = false;

    for(userIt = users.begin(); userIt != users.end(); ++userIt) {
        if((*userIt)->getName() == username) {
            user = *userIt;
            found = true;
            break;
        }
    }

    if (found == false) {
        std::cout << "Invalid username" << std::endl;
        return;
    }

    std::queue<Product*> user_cart = cart[username];
    std::queue<Product*> temp;
    
    while (!user_cart.empty()) {
        Product* product = user_cart.front();
    
        // Check if the product is in stock and the user has enough credit
        if (product->getQty() > 0 && user->getBalance() >= product->getPrice()) {
            // Deduct the price from the user's credit
            user->deductAmount(product->getPrice());
            // Reduce the stock quantity by 1
            product->subtractQty(1);
    
        } else {
            // If the product can't be bought, add it to the temp cart
            temp.push(product);
        }

        user_cart.pop();
    }

    // Replace the user's cart with the temp cart containing only the items that weren't bought
    cart[username] = temp;
}