#include "movie.h"
#include "util.h"
#include <sstream>
#include <cctype>

Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating)
    : Product("movie", name, price, qty){
        genre_ = genre;
        rating_ = rating;
    } 

Movie::~Movie() {}

std::set<std::string> Movie::keywords() const {
    std::set<std::string> words = parseStringToWords(name_);
    words.insert(convToLower(genre_));
    words.insert(convToLower(rating_));
    return words;
}

std::string Movie::displayString() const {
    std::stringstream ss;
    ss << name_ << "\n" << "Genre: " << genre_ << " Rating: " << rating_ << "\n" << std::to_string(price_) << " " << std::to_string(qty_) << " left." << std::endl;
    return ss.str();
}

void Movie::dump(std::ostream& os) const {
    Product::dump(os);
    os << genre_ << "\n" << rating_ << "\n";
    }
