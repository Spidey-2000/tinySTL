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
    //����ڵ�ṹ
    struct Node {
        T data;     //����
        Node* next; //ָ����һ���ڵ��ָ��
        Node* prev; //ָ��ǰһ���ڵ��ָ��

        //���캯��
        Node(const T& value, Node* nextNode = nullptr, Node* prevNode = nullptr)
            : data(value), next(nextNode), prev(prevNode) {}
    };


    Node* head;  //ͷ�ڵ�ָ��
    Node* tail;  //β�ڵ�ָ��
    size_t size; //�����нڵ������

public:
    //���캯��
    List() : head(nullptr), tail(nullptr), size(0) {}

    //��������
    ~List() {
        clear();
    }

    //����б�
    void clear() {
        while (head) {
            //��ͷ�ڵ㿪ʼ������ɾ���ڵ�
            Node* temp = head;
            head = head->next;
            delete temp;
        }

        //����β�ڵ�ָ��������С
        tail = nullptr;
        size = 0;
    }

    //������ĩβ���Ԫ��
    void push_back(const T& value) {
        //�����µĽڵ�
        Node* newNode = new Node(value, nullptr, tail);

        if (tail) {
            //�������ǿգ�β�ڵ�nextָ��ָ���½ڵ�
            tail->next = newNode;
        }
        else {
            //�������Ϊ�գ��½ڵ�ͬʱҲ��ͷ�ڵ�
            head = newNode;
        }

        //����β�ڵ�ָ��������С
        tail = newNode;
        ++size;
    }

    //������ͷ���Ԫ��
    void push_front(const T& value) {
        //�����µĽڵ�
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
        //��ͷ�ڵ㿪ʼ���������ҵ���index���ڵ�
        Node* current = head;
        for (size_t i = 0; i < index; ++i) {
            if (!current) {
                //���index���������ȣ����׳��쳣
                throw std::out_of_range("Index out of range");
            }
            current = current->next;
        }

        return current->data;
    }

    void pop_back() {
        if (size > 0) {
            //��ȡβ�ڵ��ǰһ���ڵ�
            Node* newTail = tail->prev;

            //ɾ��β�ڵ�
            delete tail;

            //����β�ڵ�ָ��������С
            tail = newTail;
            if (tail) {
                tail->next = nullptr;
            }
            else {
                head = nullptr; //�������Ϊ�գ�ͷ�ڵ�Ҳ�ÿ�
            }

            --size;
        }
    }

    void pop_front() {
        if (size > 0) {
            //��ȡͷ�ڵ����һ���ڵ�
            Node* newHead = head->next;

            //ɾ��ͷ�ڵ�
            delete head;

            //����ͷ�ڵ�ָ��������С
            head = newHead;
            if (head) {
                head->prev = nullptr;
            }
            else {
                tail = nullptr; //�������Ϊ�գ�β�ڵ�Ҳ�ÿ�
            }

            --size;
        }
    }

    ////��ȡָ��ֵ�Ľڵ�
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

    //    //����data�ĵ�ַ
    //    return &node->data;
    //}

    //ɾ��ָ��ֵ�Ľڵ�
    void remove(const T& val) {
        Node* node = head;
        while (node != nullptr && node->data != val) {
            node = node->next;
        }

        //û���ҵ�
        if (node == nullptr) {
            return;
        }

        //����ͷ�ڵ�Ҳ��β�ڵ�
        if (node == head && node == tail) {
            head = nullptr;
            tail = nullptr;
        }
        //ͷ�ڵ�
        else if (node == head) {
            head = head->next;
            head->prev = nullptr;
        }
        //β�ڵ�
        else if (node == tail) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        //���м�
        else {
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }

        --size;
        delete node;
        node = nullptr;
    }

    //�ж������Ƿ�Ϊ��
    bool empty() { return size == 0; }

    Node* begin() {
        return head;
    }

    Node* end() {
        return nullptr;
    }

    //��ӡ�����е�Ԫ��
    void printElements() const {
        for (Node* current = head; current; current = current->next) {
            std::cout << current->data << " ";
        }
        std::cout << std::endl;
    }
};

//���� << �����
template <typename T>
std::ostream& operator<<(std::ostream& os, const List<T>& pt) {
    for (typename List<T>::Node* current = pt.head; current; current = current->next) {
        os << " " << current->data;
    }
    os << std::endl;
    return os;
}

int main() {
    //����һ��List����
    List<int> myList;

    int N;
    std::cin >> N;
    //���߻س�
    getchar();
    std::string line;
    //��������
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

