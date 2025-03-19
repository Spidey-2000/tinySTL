#include <iostream>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>

template <typename T>

class List
{
public:
    template <typename L>
    friend std::ostream& operator<<(std::ostream& os, const List<L>& pt);

private:
    //定义节点结构
    struct Node {
        T data;     //数据
        Node* next; //指向下一个节点的指针
        Node* prev; //指向前一个节点的指针

        //构造函数
        Node(const T& value, Node* nextNode = nullptr, Node* prevNode = nullptr)
            : data(value), next(nextNode), prev(prevNode) {}
    };


    Node* head;  //头节点指针
    Node* tail;  //尾节点指针
    size_t size; //链表中节点的数量

public:
    //构造函数
    List() : head(nullptr), tail(nullptr), size(0) {}

    //析构函数
    ~List() {
        clear();
    }

    //清空列表
    void clear() {
        while (head) {
            //从头节点开始，依次删除节点
            Node* temp = head;
            head = head->next;
            delete temp;
        }

        //更新尾节点指针和链表大小
        tail = nullptr;
        size = 0;
    }

    //在链表末尾添加元素
    void push_back(const T& value) {
        //创建新的节点
        Node* newNode = new Node(value, nullptr, tail);

        if (tail) {
            //如果链表非空，尾节点next指针指向新节点
            tail->next = newNode;
        }
        else {
            //如果链表为空，新节点同时也是头节点
            head = newNode;
        }

        //更新尾节点指针和链表大小
        tail = newNode;
        ++size;
    }

    //在链表开头添加元素
    void push_front(const T& value) {
        //创建新的节点
        Node* newNode = new Node(value, head, nullptr);

        if (head) {
            head->prev = newNode;
        }
        else {
            tail = newNode;
        }

        head = newNode;
        ++size;
    }

    size_t getSize() {
        return size;
    }

    T& operator[](size_t index) {
        //从头节点开始遍历链表，找到第index个节点
        Node* current = head;
        for (size_t i = 0; i < index; ++i) {
            if (!current) {
                //如果index超出链表长度，则抛出异常
                throw std::out_of_range("Index out of range");
            }
            current = current->next;
        }

        return current->data;
    }

    void pop_back() {
        if (size > 0) {
            //获取尾节点的前一个节点
            Node* newTail = tail->prev;

            //删除尾节点
            delete tail;

            //更新尾节点指针和链表大小
            tail = newTail;
            if (tail) {
                tail->next = nullptr;
            }
            else {
                head = nullptr; //如果链表为空，头节点也置空
            }

            --size;
        }
    }

    void pop_front() {
        if (size > 0) {
            //获取头节点的下一个节点
            Node* newHead = head->next;

            //删除头节点
            delete head;

            //更新头节点指针和链表大小
            head = newHead;
            if (head) {
                head->prev = nullptr;
            }
            else {
                tail = nullptr; //如果链表为空，尾节点也置空
            }

            --size;
        }
    }

    ////获取指定值的节点
    //Node* getNode(const T& val) {
    //    Node* node = head;
    //    while (node != nullptr && node->data != val) {
    //        node = node->next;
    //    }

    //    return node;
    //}
    //T* find(const T& val) {
    //    Node* node = getNode(val);
    //    if (node == nullptr) {
    //        return nullptr;
    //    }

    //    //返回data的地址
    //    return &node->data;
    //}

    //删除指定值的节点
    void remove(const T& val) {
        Node* node = head;
        while (node != nullptr && node->data != val) {
            node = node->next;
        }

        //没有找到
        if (node == nullptr) {
            return;
        }

        //既是头节点也是尾节点
        if (node == head && node == tail) {
            head = nullptr;
            tail = nullptr;
        }
        //头节点
        else if (node == head) {
            head = head->next;
            head->prev = nullptr;
        }
        //尾节点
        else if (node == tail) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        //在中间
        else {
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }

        --size;
        delete node;
        node = nullptr;
    }

    //判断链表是否为空
    bool empty() { return size == 0; }

    Node* begin() {
        return head;
    }

    Node* end() {
        return nullptr;
    }

    //打印链表中的元素
    void printElements() const {
        for (Node* current = head; current; current = current->next) {
            std::cout << current->data << " ";
        }
        std::cout << std::endl;
    }
};

//重载 << 运算符
template <typename T>
std::ostream& operator<<(std::ostream& os, const List<T>& pt) {
    for (typename List<T>::Node* current = pt.head; current; current = current->next) {
        os << " " << current->data;
    }
    os << std::endl;
    return os;
}

int main() {
    //创建一个List对象
    List<int> myList;

    int N;
    std::cin >> N;
    //读走回车
    getchar();
    std::string line;
    //接收命令
    for (int i = 0; i < N; i++) {
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::string command;
        iss >> command;
        int value;

        if (command == "push_front") {
            iss >> value;
            myList.push_front(value);
        }
        if (command == "push_back") {
            iss >> value;
            myList.push_back(value);
        }

        if (command == "pop_back") {
            myList.pop_back();
        }
        if (command == "pop_front") {
            myList.pop_front();
        }

        if (command == "remove") {
            iss >> value;
            myList.remove(value);
        }

        if (command == "clear") {
            myList.clear();
        }

        if (command == "size") {
            std::cout << myList.getSize() << std::endl;
        }

        if (command == "get") {
            iss >> value;
            std::cout << myList[value] << std::endl;
        }

        if (command == "print") {
            if (myList.getSize() == 0) {
                std::cout << "empty" << std::endl;
            }
            else {
                myList.printElements();
            }
        }

    }
    return 0;
};

