#include "product.h"

class Clothing : public Product {
public:
    Clothing(const std::string name, double price, int quantity, const std::string size, const std::string brand);

    std::set<std::string> keywords() const;

    std::string displayString() const;

    void dump(std::ostream& os) const;

private:
    std::string size_;
    std::string brand_;
};
