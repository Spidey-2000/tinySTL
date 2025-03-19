#include <iostream>
#include <vector>
#include <list>
#include <stdexcept> // 用于异常处理
#include <sstream>
#include <string>

//队列deque也可以模拟stack
//template <typename T, typename Container = std::deque<T>>
template <typename T, typename Container = std::vector<T>>

class MyStack {
private:
    Container data;

public:
    void push(const T& value) {
        data.push_back(value);
    }

    void pop() {
        if (!empty()) {
            data.pop_back();
        }
        else {
            throw std::runtime_error("Stack is empty.");
        }
    }

    T& top() {
        if (!empty()) {
            return data.back();
        }
        else {
            throw std::runtime_error("Stack is empty.");
        }
    }

    bool empty() const {
        return data.empty();
    }

    size_t size() const {
        return data.size();
    }
};

int main() {
    MyStack<int> stack;

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
            stack.push(element);
        }
        if (command == "pop") {
            try {
                stack.pop();
            }
            catch (const std::runtime_error& e) {
                // 不做任何处理
                continue;
            }
        }
        if (command == "top") {
            try {
                std::cout << stack.top() << std::endl;
            }
            catch (const std::runtime_error& e) {
                std::cout << "null" << std::endl;
            }
        }
        if (command == "empty") {
            std::cout << (stack.empty() ? "true" : "false") << std::endl;
        }
        if (command == "size") {
            std::cout << stack.size() << std::endl;
        }
    }
    return 0;
}











