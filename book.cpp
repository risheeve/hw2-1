
#include "book.h"
#include <cctype>

Book::Book(const std::string category, const std::string name, double price, int qty, std::string isbn, std::string author) : Product("book", name, price, qty)
{
    isbn_ = isbn;
    author_ = author;
}

Book::~Book() {

}

/**
 * Returns the appropriate keywords that this product should be associated with
 * "Books: the words in the author’s name should be searchable keywords as well as the book’s ISBN number"
 * 1. words in author's name
 * 2. isbn
 * 3. product name
 */
std::set<std::string> Book::keywords() const
{
    // DOUBLE CHECK TO ADD INDIV WORDS OF AUTHOR & PROD OR TOTAL STRING

    std::set<std::string> keys;
    std::set<std::string> author_words = parseStringToWords(author_);
    std::set<std::string> name_words = parseStringToWords(name_);
    keys.insert(author_words.begin(), author_words.end());
    keys.insert(name_words.begin(), name_words.end());
    keys.insert(isbn_);

    return keys;
}

/**
 * Returns a string to display the product info for hits of the search
 */
std::string Book::displayString() const
{

    std::string display = name_ + "\n" + "Author: " + author_ + " ISBN: " + isbn_ + "\n" + std::to_string(price_) + " " + std::to_string(qty_) + " left." + "\n";

    return display;
}

/**
 * Outputs the product info in the database format
 */
void Book::dump(std::ostream &os) const
{
    Product::dump(os);
    os << isbn_ << "\n" << author_ << "\n";
}