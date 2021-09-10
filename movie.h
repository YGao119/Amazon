#include "product.h"

class Movie : public Product {
public:
    Movie(const std::string name, double price, int quantity, const std::string genre, const std::string rating);

    std::set<std::string> keywords() const;

    std::string displayString() const;

    void dump(std::ostream& os) const;

private:
    std::string genre_;
    std::string rating_;
};
