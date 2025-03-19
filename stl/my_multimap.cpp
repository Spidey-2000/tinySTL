#include "rbTree.h"

template <typename Key, typename Value> class MultiMap {

public:
    using ValueType = std::list<Value>;

    MultiMap() : rbTree(), size(0) {}

    void insert(const Key& key, const Value& value) {
        ValueType* existingValues = rbTree.at(key);
        if (existingValues) {
            existingValues->push_back(value);
        }
        else {
            ValueType values;
            values.push_back(value);
            rbTree.insert(key, values);
        }
        size++;
    }

    void remove(const Key& key) {
        ValueType* existingValues = rbTree.at(key);
        if (existingValues) {
            size -= existingValues->size();
            rbTree.remove(key);
        }
    }

    void remove(const Key& key, const Value& value) {
        ValueType* existingValues = rbTree.at(key);
        if (existingValues) {
            existingValues->remove(value);
            size--;
            if (existingValues->empty()) {
                rbTree.remove(key);
            }
        }
    }

    ValueType* at(const Key& key) {
        // 获取键对应的所有值的列表
        return rbTree.at(key);
    }

    int getSize() { return size; }

    bool empty() { return size == 0; }

private:
    RedBlackTree<Key, ValueType> rbTree;
    size_t size;

};

int main() {
    MultiMap<int, int> myMultiMap;

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
            myMultiMap.insert(key, value);
        }

        if (command == "remove") {
            iss >> key >> value;
            myMultiMap.remove(key, value);
        }

        if (command == "remove_all") {
            iss >> key;
            myMultiMap.remove(key);
        }

        if (command == "size") {
            std::cout << myMultiMap.getSize() << std::endl;
        }

        if (command == "empty") {
            std::cout << (myMultiMap.empty() ? "true" : "false") << std::endl;
        }

        if (command == "at") {
            iss >> key;
            auto valueList = myMultiMap.at(key);
            if (valueList) {
                for (auto value : *valueList) {
                    std::cout << value << " ";
                }
                std::cout << std::endl;
            }
            else {
                std::cout << "not exist" << std::endl;
            }
        }
    }

    return 0;
}