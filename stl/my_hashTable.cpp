#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <list>
#include <utility>
#include <vector>
#include <sstream>
#include <string>

template <typename Key, typename Value, typename Hash = std::hash<Key>>

class HashTable
{
    class HashNode {
    public:
        Key key;
        Value value;

        //从Key构造节点，Value使用默认构造
        explicit HashNode(const Key& key) : key(key), value() {}

        //从Key和Value构造节点
        HashNode(const Key& key, const Value& value) : key(key), value(value) {}

        //比较算符重载，只按照key进行比较
        bool operator==(const HashNode& other) const { return key == other.key; }
        bool operator!=(const HashNode& other) const { return key != other.key; }
        bool operator<(const HashNode& other) const { return key < other.key; }
        bool operator>(const HashNode& other) const { return key > other.key; }
        bool operator==(const Key& key_) const { return key == key_; }

        void print() const {
            std::cout << key << " " << value << " ";
        }
    };

private:
    using Bucket = std::list<HashNode>; // 定义桶的类型为存储键的链表
    std::vector<Bucket> buckets;        // 存储所有桶的动态数组
    Hash hashFunction;                  // 哈希函数对象
    size_t tableSize;                   // 哈希表的大小，即桶的数量
    size_t numElements;                 // 哈希表中元素的数量

    float maxLoadFactor = 0.75;         // 默认的最大负载因子

    // 计算建的哈希值，并将其映射到桶的索引
    size_t hash(const Key& key) const { return hashFunction(key) % tableSize; }

    void rehash(size_t newSize) {
        std::vector<Bucket> newBuckets(newSize); // 创建新的桶数组

        for (Bucket& bucket : buckets) {
            for (HashNode& hashNode : bucket) {
                size_t newIndex = hashFunction(hashNode.key) % newSize; // 为键计算新的索引
                newBuckets[newIndex].push_back(hashNode);               // 将键添加到新桶中
            }
        }
        buckets = std::move(newBuckets); //移动语义更新桶数组
        tableSize = newSize;
    }

public:
    //构造函数初始化哈希表
    HashTable(size_t size = 10, const Hash& hashFunc = Hash())
        : buckets(size), hashFunction(hashFunc), tableSize(size), numElements(0) {
    }

    //插入键到哈希表中
    void insert(const Key& key, const Value& value) {
        if ((numElements + 1) > maxLoadFactor * tableSize) { //检查是否需要重哈希
            //处理clear后再次插入元素时tableSize = 0的情况
            if (tableSize == 0) tableSize = 1;
            rehash(tableSize * 2); // 重哈希，桶数量翻倍

        }
        size_t index = hash(key);
        std::list<HashNode>& bucket = buckets[index]; //获取对应的桶
        // 如果键不在桶中，则添加到桶中
        if (std::find(bucket.begin(), bucket.end(), key) == bucket.end()) {
            bucket.push_back(HashNode(key, value));
            ++numElements; //增加元素数量
        }
    }

    void insertKey(const Key& key) {
        insert(key, Value{});
    }

    //从哈希表中移除键
    void erase(const Key& key) {
        size_t index = hash(key);       //计算键索引
        auto& bucket = buckets[index];  //获取对应的桶
        auto it = std::find(bucket.begin(), bucket.end(), key);
        if (it != bucket.end()) { // 找到键
            bucket.erase(it);  // 从桶中移除键
            numElements--;
        }
    }

    //查找键对应的值(返回值的指针)
    Value* find(const Key& key) {
        size_t index = hash(key);       //计算键索引
        auto& bucket = buckets[index];  //获取对应的桶
        //返回键是否在桶中
        auto ans = std::find(bucket.begin(), bucket.end(), key);
        if (ans != bucket.end()) {    //找到了
            return &ans->value;
        };
        return nullptr;
    }

    //获取哈希表中元素的数量
    size_t size() const { return numElements; }

    //打印哈希表元素
    void print() const {
        for (size_t i = 0; i < buckets.size(); ++i) {
            for (const HashNode& element : buckets[i]) {
                element.print();
            }
        }
        std::cout << std::endl;
    }

    void clear() {
        this->buckets.clear();
        this->numElements = 0;
        this->tableSize = 0;
    }
};

int main() {
    HashTable<int, int> hashTable;

    int N;
    std::cin >> N;
    getchar();

    std::string line;
    for (int i = 0; i < N; ++i) {
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::string command;
        iss >> command;

        int key;
        int value;

        if (command == "insert") {
            iss >> key >> value;
            hashTable.insert(key, value);
        }

        if (command == "erase") {
            if (hashTable.size() == 0) {
                continue;
            }
            iss >> key;
            hashTable.erase(key);
        }

        if (command == "find") {
            if (hashTable.size() == 0) {
                std::cout << "not exist" << std::endl;
                continue;
            }
            iss >> key;
            if (hashTable.find(key)) {
                std::cout << *hashTable.find(key) << std::endl;
            }
            else {
                std::cout << "not exist" << std::endl;
            }
        }

        if (command == "size") {
            std::cout << hashTable.size() << std::endl;
        }

        if (command == "print") {
            if (hashTable.size() != 0) {
                hashTable.print();
            }
            else {
                std::cout << "empty" << std::endl;
            }
        }

        if (command == "clear") {
            hashTable.clear();
        }
    }

    return 0;
}