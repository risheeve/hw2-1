#ifndef MOVIE_H
#define MOVIE_H

#include "product.h"
#include "util.h"
#include <string>
#include <set>

class Movie : public Product {
public:
    Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating);
    ~Movie();
/**
* Returns the appropriate keywords that this product should be associated with
*/
    std::set<std::string> keywords() const;
    std::string displayString() const;
    void dump(std::ostream& os) const;

private:
    std::string genre_;
    std::string rating_;
};

#endif
