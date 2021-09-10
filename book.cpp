#include "book.h"

#include "util.h"
#include <sstream>

Book::Book(const std::string name, double price, int quantity, const std::string isbn, const std::string author)
        : Product("book", name, price, quantity) {
    ISBN_ = isbn;
    author_ = author;
}
std::set<std::string> Book::keywords() const {

    std::set<std::string> keys_name = parseStringToWords(getName());
    std::set<std::string> keys_author = parseStringToWords(author_);
    std::set<std::string> allkeys = setUnion(keys_name, keys_author);
    allkeys.insert(ISBN_);

    return allkeys;
}

std::string Book::displayString() const {

    /* FORMAT
     <name>
     Author: <author> ISBN: <isbn>
     <price> <quantity> left. */
    std::stringstream ss;
    ss << getName() << "\n"
       << "Author: " << author_ << " ISBN: " << ISBN_ << "\n"
       << getPrice() << " " << getQty() << " left.";

    return ss.str();
}

void Book::dump(std::ostream& os) const {

    os << "book" << std::endl;
    os << getName() << std::endl;
    os << getPrice() << std::endl;
    os << getQty() << std::endl;
    os << ISBN_ << std::endl;
    os << author_ << std::endl;
}
