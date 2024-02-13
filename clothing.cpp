
#include "clothing.h"
#include <cctype>

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand) : Product("clothing", name, price, qty)
{
    size_ = size;
    brand_ = brand;
}

Clothing::~Clothing() {

}


std::set<std::string> Clothing::keywords() const
{

    std::set<std::string> keys;
    std::set<std::string> brand_words = parseStringToWords(brand_);
    std::set<std::string> name_words = parseStringToWords(name_);
    keys.insert(brand_words.begin(), brand_words.end());
    keys.insert(name_words.begin(), name_words.end());
    keys.insert(convToLower(size_));

    return keys;
}

/**
 * Returns a string to display the product info for hits of the search
 */
std::string Clothing::displayString() const
{

    std::string display = name_ + "\n" + "Size: " + size_ + " Brand: " + brand_ + "\n" + std::to_string(price_) + " " + std::to_string(qty_) + " left." + "\n";

    return display;
}

/**
 * Outputs the product info in the database format
 */
void Clothing::dump(std::ostream &os) const
{
    Product::dump(os);
    os << size_ << "\n" << brand_ << "\n";
}