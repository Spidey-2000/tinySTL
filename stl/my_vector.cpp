#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <stdexcept>

template <typename T>

class Vector
{
private:
    T* elements;      //ָ��̬�����ָ��
    size_t capacity;  //���������
    size_t size;      //������Ԫ�صĸ���

public:
    //���캯��
    Vector() : elements(nullptr), capacity(0), size(0) {}

    //��������
    ~Vector() {
        delete[] elements;
    }

    //�������캯��
    Vector(const Vector& other) : capacity(other.capacity), size(other.size) {
        elements = new T[capacity];
        std::copy(other.elements, other.elements + size, elements);
    }

    //������ֵ����
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] elements;
            capacity = other.capacity;
            size = other.size;
            elements = new T[capacity];
            std::copy(other.elements, other.elements + size, elements);
        }
        return *this;
    }

    //���Ԫ�ص�����ĩβ
    void push_back(const T& value) {
        if (size == capacity) {
            //���������������չ����
            reserve(capacity == 0 ? 1 : capacity * 2);
        }
        elements[size++] = value;
    }

    //��ȡ������Ԫ�صĸ���
    size_t getSize() const {
        return size;
    }

    //��ȡ���������
    size_t getCapacity() const {
        return capacity;
    }

    //���������е�Ԫ��
    T& operator[](size_t index) {
        //��������Ƿ�Խ��
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return elements[index];
    }

    //��ָ��λ�ò���Ԫ��
    void insert(size_t index, const T& value) {
        if (index > size) {
            throw std::out_of_range("Index out of range");
        }
        if (size == capacity) {
            //���������������չ����
            reserve(capacity == 0 ? 1 : capacity * 2);
        }
        for (size_t i = size; i > index; --i) {
            elements[i] = elements[i - 1];
        }
        elements[index] = value;
        ++size;
    }

    //ɾ������ĩβԪ��
    void pop_back() {
        if (size > 0) {
            --size;
        }
    }

    //�������
    void clear() {
        size = 0;
    }

    //ʹ�õ�������������Ŀ�ʼλ��
    T* begin() {
        return elements;
    }

    //ʹ�õ�������������Ľ���λ��
    T* end() {
        return elements + size;
    }

    //��ӡ�����е�Ԫ��
    void printElements() const {
        for (size_t i = 0; i < size; ++i) {
            std::cout << elements[i] << " ";
        }
        std::cout << std::endl;
    }

private:
    //��չ��������
    void reserve(size_t newCapacity) {
        if (newCapacity > capacity) {
            T* newElements = new T[newCapacity];
            std::copy(elements, elements + size, newElements);
            delete[] elements;
            elements = newElements;
            capacity = newCapacity;
        }
    }

};

int main() {
    //����һ��Vector����
    Vector<int> myVector;

    int N;
    std::cin >> N;
    //���߻س�
    getchar();

    std::string line;
    for (int i = 0; i < N; i++) {
        //��ȡ����
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::string command;
        iss >> command;

        if (command == "push") {
            int value;
            iss >> value;
            myVector.push_back(value);
        }
        else if (command == "size") {
            std::cout << myVector.getSize() << std::endl;
        }
        else if (command == "get") {
            int index;
            iss >> index;
            std::cout << myVector[index] << std::endl;
        }
        else if (command == "insert") {
            int index, value;
            iss >> index >> value;
            myVector.insert(index, value);
        }
        else if (command == "pop") {
            myVector.pop_back();
        }
        else if (command == "clear") {
            myVector.clear();
        }
        else if (command == "print") {
            if (myVector.getSize() == 0) {
                std::cout << "empty" << std::endl;
                continue;
            }
            myVector.printElements();
        }
        else if (command == "iterator") {
            if (myVector.getSize() == 0) {
                std::cout << "empty" << std::endl;
                continue;
            }
            for (auto it = myVector.begin(); it != myVector.end(); ++it) {
                std::cout << *it << " ";
            }
            std::cout << std::endl;
        }
        else if (command == "foreach") {
            if (myVector.getSize() == 0) {
                std::cout << "empty" << std::endl;
                continue;
            }
            for (const auto& element : myVector) {
                std::cout << element << " ";
            }
            std::cout << std::endl;
        }

    }
    return 0;
};