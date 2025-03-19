#include "rbTree.h" // 之前实现的红黑树
#include <cstddef>
#include <stdexcept>

template<typename Key> class MultiSet {

private:
    RedBlackTree<Key, size_t> rbTree;
    size_t sz;

public:
    MultiSet() : sz(0) {}
    ~MultiSet() {}

    void insert(const Key& key) {
        auto count = rbTree.at(key);
        if (count != nullptr) {
            (*count)++;
            sz++;
            return;
        }
        rbTree.insert(key, 1);
        sz++;
    }

    void erase(const Key& key) {
        auto count = rbTree.at(key);
        if (count == nullptr) { return; }
        sz -= (*count);
        rbTree.remove(key);
    }

    size_t size() const { return sz; }

    bool empty() const { return sz == 0; }

    size_t count(const Key& key) {
        auto num = rbTree.at(key);
        if (num != nullptr) {
            return *num;
        }
        return 0;
    }

    void clear() {
        sz = 0;
        rbTree.clear();
    }
};

int main() {
    MultiSet<int> mySet;
    int N;
    std::cin >> N;
    getchar();

    std::string line;
    for (int i = 0; i < N; i++) {
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::string command;
        iss >> command;
        int element;

        if (command == "insert") {
            iss >> element;
            mySet.insert(element);
        }

        if (command == "erase") {
            iss >> element;
            mySet.erase(element);
        }

        if (command == "count") {
            iss >> element;
            std::cout << mySet.count(element) << std::endl;
        }

        if (command == "size") {
            std::cout << mySet.size() << std::endl;
        }

        if (command == "empty") {
            std::cout << (mySet.empty() ? "true" : "false") << std::endl;
        }
    }
    return 0;
}