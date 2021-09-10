#include "clothing.h"

#include "util.h"
#include <sstream>

Clothing::Clothing(const std::string name, double price, int quantity, const std::string size, const std::string brand)
        : Product("clothing", name, price, quantity) {
    size_ = size;
    brand_ = brand;
}

std::set<std::string> Clothing::keywords() const {

    std::set<std::string> keys_name = parseStringToWords(getName());
    std::set<std::string> keys_brand = parseStringToWords(brand_);
    std::set<std::string> allkeys = setUnion(keys_name, keys_brand);

    return allkeys;
}

std::string Clothing::displayString() const {

    /* FORMAT
    <name>
    Size: <size> Brand: <brand>
    <price> <quantity> left. */
    std::stringstream ss;
    ss << getName() << "\n"
       << "Size: " << size_ << " Brand: " << brand_ << "\n"
       << getPrice() << " " << getQty() << " left.";

    return ss.str();
}

void Clothing::dump(std::ostream& os) const {

    os << "clothing" << std::endl;
    os << getName() << std::endl;
    os << getPrice() << std::endl;
    os << getQty() << std::endl;
    os << size_ << std::endl;
    os << brand_ << std::endl;
}
