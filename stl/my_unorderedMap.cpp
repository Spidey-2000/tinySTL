#include"hashTable.h"

template<typename Key, typename Value>  class Unordered_map {
private:
    HashTable<Key, Value> hashtable;

public:
    Unordered_map() : hashtable() {};
    ~Unordered_map() {}

    bool empty() const noexcept { return hashtable.size() == 0; }

    size_t size() const noexcept { return hashtable.size(); }

    void clear() noexcept { hashtable.clear(); }

    void insert(const Key& key, const Value& value) {
        hashtable.insert(key, value);
    }

    void erase(const Key& key) { hashtable.erase(key); }

    bool find(const Key& key) { return hashtable.find(key) != nullptr; }

    Value& operator[](const Key& key) {
        Value* ans = hashtable.find(key);
        if (ans != nullptr) {
            return *ans;
        }
        hashtable.insertKey(key);
        ans = hashtable.find(key);
        return *ans;
    }
};

int main() {
    Unordered_map<int, int> map;
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

        if (command == "find") {
            iss >> key;
            if (map.find(key)) {
                std::cout << "true" << std::endl;
            }
            else {
                std::cout << "false" << std::endl;
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