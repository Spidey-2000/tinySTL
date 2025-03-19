#include "rbTree.h"

template<typename Key, typename Value> class Map {
private:
    RedBlackTree<Key, Value> rbTree;

public:
    Map() : rbTree() {}

    void insert(const Key& key, const Value& value) { rbTree.insert(key, value); }

    void erase(const Key& key) { rbTree.remove(key); }

    size_t size() { return rbTree.getSize(); }

    bool empty() const { return rbTree.empty(); }

    bool contains(const Key& key) { return rbTree.at(key) != nullptr; }

    Value& at(const Key& key) {
        Value* foundVal = rbTree.at(key);
        if (foundVal) {
            return *foundVal;
        }
        else {
            throw std::out_of_range("Key not found");
        }
    }

    Value& operator[](const Key& key) {
        Value* foundVal = rbTree.at(key);
        if (foundVal) {
            return *foundVal;
        }
        else {
            // 如果键不存在，插入新键值对，并返回新插入的值的引用
            Value defaultValue;
            rbTree.insert(key, defaultValue);
            return *rbTree.at(key);
        }
    }
};

int main() {
    Map<int, int> map;

    int N;
    std::cin >> N;
    getchar();

    std::string line;
    for (int i = 0; i < N; i++) {
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::string command;
        iss >> command;

        int key;
        int value;

        if (command == "insert") {
            iss >> key >> value;
            map.insert(key, value);
        }

        if (command == "erase") {
            iss >> key;
            map.erase(key);
        }

        if (command == "contains") {
            iss >> key;
            if (map.contains(key)) {
                std::cout << "true" << std::endl;
            }
            else {
                std::cout << "false" << std::endl;
            }
        }

        if (command == "at") {
            iss >> key;
            try {
                std::cout << map.at(key) << std::endl;
            }
            catch (const std::out_of_range& e) {
                std::cout << "not exist" << std::endl;
            }
        }

        if (command == "size") {
            std::cout << map.size() << std::endl;
        }

        if (command == "empty") {
            if (map.empty()) {
                std::cout << "true" << std::endl;
            }
            else {
                std::cout << "false" << std::endl;
            }
        }
    }
    return 0;
}