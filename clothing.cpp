#include "clothing.h"
#include "util.h"
#include <sstream>

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand)
    : Product("clothing", name, price, qty){
        size_ = size;
        brand_ = brand;
    }

Clothing::~Clothing() {}

std::set<std::string> Clothing::keywords() const {
    std::set<std::string> words = parseStringToWords(name_);
    std::set<std::string> brandWords = parseStringToWords(brand_);
    words.insert(brandWords.begin(), brandWords.end());
    return words;
}

std::string Clothing::displayString() const {
    std::stringstream ss;
    ss << name_ << "\n" << "Size: " << size_ << " Brand: " << brand_ << "\n" << std::to_string(price_) << " " << std::to_string(qty_) << " left."<<std::endl;
    return ss.str();
}

void Clothing::dump(std::ostream& os) const {
    Product::dump(os);
    os << size_ << "\n" << brand_ << "\n";
  }
