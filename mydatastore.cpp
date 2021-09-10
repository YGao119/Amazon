#include "mydatastore.h"

#include "util.h"
#include <stdexcept>

MyDataStore::~MyDataStore() {

    for (unsigned int i = 0; i < all_users_.size(); i++) {
        delete all_users_[i];
    }
    for (unsigned int i = 0; i < all_products_.size(); i++) {
        delete all_products_[i];
    }
}
void MyDataStore::addProduct(Product* p) {

    all_products_.push_back(p);

    std::set<std::string> temp = p->keywords();

    for (std::set<std::string>::iterator it = temp.begin(); it != temp.end(); ++it) {
        if (products_.find(*it) == products_.end()) {
            std::set<Product*> val;
            val.insert(p);
            products_.insert(std::pair<std::string, std::set<Product*>>(*it, val));
        } else {
            products_[*it].insert(p);
        }
    }
}

void MyDataStore::addUser(User* u) {

    std::deque<Product*> cart;
    carts_.insert(std::pair<std::string, std::deque<Product*>>(convToLower(u->getName()), cart));
    users_.insert(std::pair<std::string, User*>(convToLower(u->getName()), u));
    all_users_.push_back(u);
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {

    std::set<Product*> hits = products_[terms[0]];

    for (std::vector<std::string>::iterator it = terms.begin(); it != terms.end(); ++it) {
        if (products_.find(*it) != products_.end()) {
            std::set<Product*> temp = products_[*it];
            if (type == 0) {
                hits = setIntersection(hits, temp);
            } else {
                hits = setUnion(hits, temp);
            }
        }
    }

    std::vector<Product*> vec(hits.begin(), hits.end());
    most_recent_search_ = vec;
    return vec;
}

void MyDataStore::addToCart(std::string username, int hit_number) {

    if (carts_.find(convToLower(username)) == carts_.end() || (unsigned)hit_number > most_recent_search_.size()) {
        std::cout << convToLower(username) << hit_number << most_recent_search_.size();
        throw std::invalid_argument("invalid request");
    }

    carts_[convToLower(username)].push_back(most_recent_search_[hit_number - 1]);
}

void MyDataStore::viewCart(std::string username) {

    if (carts_.find(convToLower(username)) == carts_.end()) {
        throw std::invalid_argument("invalid request");
    }

    int count = 1;
    std::deque<Product*> temp = carts_[convToLower(username)];
    for (std::deque<Product*>::iterator it = temp.begin(); it != temp.end(); ++it) {
        std::cout << "Item " << count << std::endl;
        std::cout << (*it)->displayString() << std::endl;
        std::cout << std::endl;
        count++;
    }
}

void MyDataStore::buyCart(std::string username) {

    if (users_.find(convToLower(username)) == users_.end()) {
        throw std::invalid_argument("invalid request");
    }

    std::deque<Product*>::iterator it = carts_[convToLower(username)].begin();
    while (it != carts_[convToLower(username)].end()) {
        if ((*it)->getQty() >= 1 && users_[convToLower(username)]->getBalance() >= (*it)->getPrice()) {
            carts_[convToLower(username)].pop_front();
            (*it)->subtractQty(1);
            (users_[convToLower(username)])->deductAmount((*it)->getPrice());
            it = carts_[convToLower(username)].begin();
        } else {
            ++it;
        }
    }
}

void MyDataStore::dump(std::ostream& ofile) {

    ofile << "<products>" << '\n';
    for (std::vector<Product*>::iterator it = all_products_.begin(); it != all_products_.end(); ++it) {

        (*it)->dump(ofile);
    }
    ofile << "</products>" << '\n';
    ofile << "<users>" << '\n';
    for (std::vector<User*>::iterator it = all_users_.begin(); it != all_users_.end(); ++it) {

        (*it)->dump(ofile);
    }
    ofile << "</users>" << '\n';
}

void MyDataStore::setHits(std::vector<Product*>& hits) { most_recent_search_ = hits; }
