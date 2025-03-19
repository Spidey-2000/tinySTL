#include <iostream>
#include <deque>
#include <list>
#include <stdexcept> // 用于异常处理
#include <sstream>
#include <string>

template <typename T, typename Container = std::deque<T>>
class MyQueue {
private:
    Container data;
public:
    // 将元素添加到队尾
    void push(const T& value) {
        data.push_back(value);
    }

    // 移除队头元素
    void pop() {
        if (!empty()) {
            data.pop_front();
        }
        else {
            throw std::runtime_error("Queue is empty.");
        }
    }

    // 访问队头元素的引用
    T& front() {
        if (!empty()) {
            return data.front();
        }
        else {
            throw std::runtime_error("Queue is empty.");
        }
    }

    // 访问队尾元素的引用
    T& back() {
        if (!empty()) {
            return data.back();
        }
        else {
            throw std::runtime_error("Queue is empty.");
        }
    }

    // 检查队列是否为空
    bool empty() const {
        return data.empty();
    }

    // 返回队列的大小
    size_t size() const {
        return data.size();
    }
};

int main() {
    MyQueue<int> myQueue;

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

        if (command == "push") {
            iss >> element;
            myQueue.push(element);
        }

        if (command == "pop") {
            try {
                myQueue.pop();
            }
            catch (const std::runtime_error& e) {
                // 不做任何处理
                continue;
            }
        }

        if (command == "front") {
            try {
                std::cout << myQueue.front() << std::endl;
            }
            catch (const std::runtime_error& e) {
                std::cout << "null" << std::endl;
            }
        }

        if (command == "back") {
            try {
                std::cout << myQueue.back() << std::endl;
            }
            catch (const std::runtime_error& e) {
                std::cout << "null" << std::endl;
            }
        }

        if (command == "size") {
            std::cout << myQueue.size() << std::endl;
        }

        if (command == "empty") {
            std::cout << (myQueue.empty() ? "true" : "false") << std::endl;
        }
    }
    return 0;
}











