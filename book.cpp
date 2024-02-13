#include "book.h"
#include "util.h"
#include "product.h"
#include <sstream>

Book::Book(const std::string category, const std::string name, double price, int qty, std::string isbn, std::string author) : Product("book", name, price, qty) {
        isbn_ = isbn;
        author_ = author;

    }  

Book::~Book() {}

std::set<std::string> Book::keywords() const {
    std::set<std::string> words = parseStringToWords(name_);
    std::set<std::string> authorWords = parseStringToWords(author_);
    words.insert(isbn_);
    words.insert(authorWords.begin(), authorWords.end());
    return words;
}

std::string Book::displayString() const {
    std::stringstream ss;
    ss << name_ << "\n" << "Author: " << author_ << " ISBN: " << isbn_ << "\n" << std::to_string(price_) << " " << std::to_string(qty_) << " left."<<std::endl;
    return ss.str();
}

void Book::dump(std::ostream& os) const {
    Product::dump(os);
    os << isbn_ << "\n" << author_ << "\n";
  }
