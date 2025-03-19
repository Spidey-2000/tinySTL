#include <iostream>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>

template <typename T>
class Deque {
private:
    T* elements;       //循环一维数组
    size_t capacity;   //数组总容量
    size_t frontIndex; //deque的前端索引
    size_t backIndex;  //deque的后端索引
    size_t size;       //deque的元素数量

public:
    //构造函数
    Deque() : elements(nullptr), capacity(0), frontIndex(0), backIndex(0), size(0) {}

    //析构函数
    ~Deque() {
        clear();
        delete[] elements;
    }

    //在前端插入元素
    void push_front(const T& value) {
        //检查是否需要扩容
        if (size == capacity) {
            resize();
        }

        //循环数组，计算新的前端索引
        frontIndex = (frontIndex - 1 + capacity) % capacity;

        //在新的前端插入元素
        elements[frontIndex] = value;

        ++size;
    }

    //在后端插入元素
    void push_back(const T& value) {
        //检查是否需要扩容
        if (size == capacity) {
            resize();
        }

        //在后端插入元素
        elements[backIndex] = value;

        //循环数组，计算新的后端索引
        backIndex = (backIndex + 1) % capacity;

        ++size;
    }

    //在前端移除元素
    void pop_front() {
        //检查deque是否非空
        if (size == 0) {
            throw std::out_of_range("Deque is empty");
        }

        //删除元素不需要显式地删除，以后新追加元素会自动覆盖
        //计算新的前端索引
        frontIndex = (frontIndex + 1) % capacity;

        --size;
    }

    //在后端移除元素
    void pop_back() {
        //检查deque是否非空
        if (size == 0) {
            throw std::out_of_range("Deque is empty");
        }

        //计算新的后端索引
        backIndex = (backIndex - 1 + capacity) % capacity;

        --size;
    }

    //随机访问元素
    T& operator[](int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return elements[(frontIndex + index) % capacity];
    }

    //获取deque中的元素数量
    size_t getSize() {
        return size;
    }

    //清空deque
    void clear() {
        while (size > 0) {
            pop_front();
        }
    }

    //打印元素
    void printElements() const {
        size_t index = frontIndex;
        for (size_t i = 0; i < size; i++) {
            std::cout << elements[index] << " ";
            index = (index + 1) % capacity;
        }
        std::cout << std::endl;
    }

private:
    //拓展数组容量
    void resize() {
        size_t newCapacity = (capacity == 0) ? 1 : capacity * 2;

        //创建新的数组
        T* newElements = new T[newCapacity];

        //复制
        size_t index = frontIndex;
        for (size_t i = 0; i < size; ++i) {
            newElements[i] = elements[index];
            index = (index + 1) % capacity;
        }

        delete[] elements;

        //更新变量
        elements = newElements;
        capacity = newCapacity;
        frontIndex = 0;
        backIndex = size;
    }
};

int main() {
    //创建一个Deque对象
    Deque<int> myDeque;

    int N;
    std::cin >> N;
    //读走回车
    getchar();
    std::string line;
    //接收指令
    for (int i = 0; i < N; ++i) {
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::string command;
        iss >> command;
        int value;

        if (command == "push_back") {
            iss >> value;
            myDeque.push_back(value);
        }
        if (command == "push_front") {
            iss >> value;
            myDeque.push_front(value);
        }

        if (command == "pop_back") {
            if (myDeque.getSize() == 0) {
                continue;
            }
            myDeque.pop_back();
        }
        if (command == "pop_front") {
            if (myDeque.getSize() == 0) {
                continue;
            }
            myDeque.pop_front();
        }

        if (command == "clear") {
            myDeque.clear();
        }

        if (command == "size") {
            std::cout << myDeque.getSize() << std::endl;
        }

        if (command == "get") {
            iss >> value;
            std::cout << myDeque[value] << std::endl;
        }

        if (command == "print") {
            if (myDeque.getSize() == 0) {
                std::cout << "empty" << std::endl;
            }
            else {
                myDeque.printElements();
            }
        }
    }

    return 0;
}