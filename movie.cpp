
#include "movie.h"
#include <cctype>
//
Movie::Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating) : Product("movie", name, price, qty)
{
    genre_ = genre;
    rating_ = rating;

}

Movie::~Movie() {

}

/**
 * Returns the appropriate keywords that this product should be associated with
 */
std::set<std::string> Movie::keywords() const
{
    // DOUBLE CHECK TO ADD INDIV WORDS OF AUTHOR & PROD OR TOTAL STRING

    std::set<std::string> keys;
    std::set<std::string> name_words = parseStringToWords(name_);
    keys.insert(name_words.begin(), name_words.end());
    
    keys.insert(convToLower(genre_));
    keys.insert(convToLower(rating_));

    return keys;
}

/**
 * Returns a string to display the product info for hits of the search
 */
std::string Movie::displayString() const
{

    std::string display = name_ + "\n" + "Genre: " + genre_ + " Rating: " + rating_ + "\n" + std::to_string(price_) + " " + std::to_string(qty_) + " left." + "\n";

    return display;
}

/**
 * Outputs the product info in the database format
 */
void Movie::dump(std::ostream &os) const
{
    Product::dump(os);
    os << genre_ << "\n" << rating_ << "\n";
}