#include "hashTable.h" // 之前实现的哈希表

template<typename Key> class Unordered_set {
public:
    Unordered_set() : hashtable() {};

    ~Unordered_set() {}

    bool empty() const noexcept { return hashtable.size() == 0; }

    size_t size() const noexcept { return hashtable.size(); }

    void clear() noexcept { hashtable.clear(); }

    void insert(Key key) { hashtable.insertKey(key); }

    void erase(Key key) { hashtable.erase(key); }

    bool find(const Key& key) { return hashtable.find(key) != nullptr; }

private:
    HashTable<Key, Key> hashtable;
};

int main() {
    Unordered_set<int> mySet;
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

        if (command == "find") {
            iss >> element;
            std::cout << (mySet.find(element) ? "true" : "false") << std::endl;
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