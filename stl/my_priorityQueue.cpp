#include <iostream>
#include <vector>
#include <algorithm> // 用于 std::make_heap, std::push_heap, std::pop_heap
#include <stdexcept>
#include <sstream>
#include <string>

template<typename T, typename Container = std::vector<T>>
class MyPriorityQueue {
/*
//使用标准库中的堆函数

private:
    Container data;
public:
    // 默认构造函数
    MyPriorityQueue() {}

    //构造函数，可以指定底层容器
    MyPriorityQueue(const Container& c) : data(c) {
        std::make_heap(data.begin(), data.end());
    }

    void push(const T& value) {
        data.push_back(value);
        std::push_heap(data.begin(), data.end());
    }

    // 弹出优先队列中的最大元素
    void pop() {
        if (!empty()) {
            std::pop_heap(data.begin(), data.end());
            data.pop_back();
        }
        else {
            throw std::runtime_error("priority queue is empty.");
        }
    }

    // 访问优先队列中的最大元素
    T& top() {
        if (!empty()) {
            return data.front();
        }
        else {
            throw std::runtime_error("Priority queue is empty.");
        }
    }

*/

private:
    Container data;

    // 辅助函数：向上调整元素以维护堆性质
    void heapifyUp() {
        int index = data.size() - 1;
        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            if (data[index] > data[parentIndex]) {
                std::swap(data[index], data[parentIndex]);
                index = parentIndex;
            }
            else {
                break;
            }
        }
    }

    // 辅助函数：向下调整元素以维护堆性质
    void heapifyDown() {
        int index = 0;
        int size = data.size();
        while (true) {
            int leftChild = 2 * index + 1;
            int rightChild = 2 * index + 2;
            int largest = index;

            if (leftChild < size && data[leftChild] > data[largest]) {
                largest = leftChild;
            }

            if (rightChild < size && data[rightChild] > data[largest]) {
                largest = rightChild;
            }

            if (largest != index) {
                std::swap(data[index], data[largest]);
                index = largest;
            }
            else {
                break;
            }
        }
    }

public:
    MyPriorityQueue() {}

    MyPriorityQueue(const Container& c) : data(c) {
        // 将底层容器转化为堆
        int size = data.size();
        for (int i = (size / 2) - 1; i >= 0; --i) {
            heapifyDown();
        }
    }

    void push(const T& value) {
        data.push_back(value);
        heapifyUp();
    }

    void pop() {
        if (!empty()) {
            std::swap(data[0], data[data.size() - 1]);
            data.pop_back();
            heapifyDown();
        }
        else {
            throw std::runtime_error("Priority queue is empty.");
        }
    }

    T& top() {
        if (!empty()) {
            return data[0];
        }
        else {
            throw std::runtime_error("Priority queue is empty.");
        }
    }

    // 检查优先队列是否为空
    bool empty() const {
        return data.empty();
    }

    // 返回优先队列的大小
    size_t size() const {
        return data.size();
    }
};

int main() {
    // 使用 std::vector 作为底层容器
    MyPriorityQueue<int> myPriorityQueue;

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
            myPriorityQueue.push(element);
        }

        if (command == "pop") {
            try {
                myPriorityQueue.pop();
            }
            catch (const std::runtime_error& e) {
                // 不做任何处理
                continue;
            }
        }

        if (command == "top") {
            try {
                std::cout << myPriorityQueue.top() << std::endl;
            }
            catch (const std::runtime_error& e) {
                std::cout << "null" << std::endl;
            }
        }

        if (command == "size") {
            std::cout << myPriorityQueue.size() << std::endl;
        }

        if (command == "empty") {
            std::cout << (myPriorityQueue.empty() ? "true" : "false") << std::endl;
        }
    }
    return 0;
}


