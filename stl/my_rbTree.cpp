#include <iostream>
#include <sstream>
#include <string>

enum class Color { RED, BLACK };

template <typename Key, typename Value> class RedBlackTree {
    struct Node {
        Key key;
        Value value;
        Color color;
        Node* left;
        Node* right;
        Node* parent;

        //构造函数
        Node(const Key& k, const Value& v, Color c, Node* p = nullptr)
            : key(k), value(v), color(c), left(nullptr), right(nullptr), parent(p) {}
        Node()
            : color(Color::BLACK), left(nullptr), right(nullptr), parent(nullptr) {}
    };

private:
    Node* root;
    size_t size;
    Node* Nil;

    // 查询某节点
    Node* lookUp(Key key) {
        Node* cmpNode = root;

        while (cmpNode) {
            if (key < cmpNode->key) {
                cmpNode = cmpNode->left;
            }
            else if (key > cmpNode->key) {
                cmpNode = cmpNode->right;
            }
            else {
                return cmpNode;
            }
        }
        return cmpNode;
    }

    // 右旋函数
    void rightRotate(Node* node) {
        Node* l_son = node->left; //获取当前节点的左子节点

        node->left = l_son->right; //当前节点的左子树变成原左子节点的右子树

        //如果左子节点的右子数非空，更新其父指针
        if (l_son->right) {
            l_son->right->parent = node;
        }

        //原左子节点替换当前节点位置,处理当前节点的父节点关系
        l_son->parent = node->parent;
        if (!node->parent) {
            root = l_son;
        }//如果当前节点为其父节点的左子节点
        else if (node == node->parent->left) {
            node->parent->left = l_son;
        }//如果当前节点为其父节点的右子节点
        else {
            node->parent->right = l_son;
        }

        //最后将当前节点设为左子节点的右子节点
        node->parent = l_son;
        l_son->right = node;
    }

    //左旋函数
    void leftRotate(Node* node) {
        Node* r_son = node->right; //获取当前节点的右子节点

        node->right = r_son->left; //当前节点的右子树变成原右子节点的左子树

        //如果右子节点的左子数非空，更新其父指针
        if (r_son->left) {
            r_son->left->parent = node;
        }

        //原右子节点替换当前节点位置,处理当前节点的父节点关系
        r_son->parent = node->parent;
        if (!node->parent) {
            root = r_son;
        }//如果当前节点为其父节点的右子节点
        else if (node == node->parent->right) {
            node->parent->right = r_son;
        }//如果当前节点为其父节点的左子节点
        else {
            node->parent->left = r_son;
        }

        //最后将当前节点设为右子节点的左子节点
        node->parent = r_son;
        r_son->left = node;
    }

    // 插入修复函数
    void insertFixup(Node* target) {
        // 当目标节点父节点存在且为红色时，需要修复
        while (target->parent && target->parent->color == Color::RED) {
            // 当目标节点的父节点是祖父节点的左子节点时
            if (target->parent == target->parent->parent->left) {
                Node* uncle = target->parent->parent->right; // 叔叔节点
                // 如果叔叔节点存在且为红色
                if (uncle && uncle->color == Color::RED) {
                    target->parent->color = Color::BLACK; // 父节点设为黑色
                    uncle->color = Color::BLACK;          // 叔叔节点设为黑色
                    target->parent->parent->color = Color::RED; // 祖父节点设为红色
                    target = target->parent->parent;     // 祖父节点设为下一个目标节点
                }
                else {
                    // 如果目标节点是父节点的右子节点，左旋
                    if (target == target->parent->right) {
                        target = target->parent; // 更新目标节点为父节点
                        leftRotate(target);      // 对目标节点进行左旋
                    }
                    // 调整父节点和祖父节点颜色，右旋
                    target->parent->color = Color::BLACK;
                    target->parent->parent->color = Color::RED;
                    rightRotate(target->parent->parent);
                }
            }
            else {
                // 当目标节点的父节点是祖父节点的右子节点时
                Node* uncle = target->parent->parent->left; // 叔叔节点
                // 如果叔叔节点存在且为红色
                if (uncle && uncle->color == Color::RED) {
                    target->parent->color = Color::BLACK; // 父节点设为黑色
                    uncle->color = Color::BLACK;          // 叔叔节点设为黑色
                    target->parent->parent->color = Color::RED; // 祖父节点设为红色
                    target = target->parent->parent;     // 祖父节点设为下一个目标节点
                }
                else {
                    // 如果目标节点是父节点的左子节点，右旋
                    if (target == target->parent->left) {
                        target = target->parent; // 更新目标节点为父节点
                        rightRotate(target);      // 对目标节点进行右旋
                    }
                    // 调整父节点和祖父节点颜色，左旋
                    target->parent->color = Color::BLACK;
                    target->parent->parent->color = Color::RED;
                    leftRotate(target->parent->parent);
                }
            }
        }
        // 确保根节点始终为黑色
        root->color = Color::BLACK;
    }

    // 插入节点函数
    void insertNode(const Key& key, const Value& value) {
        // 创建一个新节点，节点的颜色初始化为红色
        Node* newNode = new Node(key, value, Color::RED);
        Node* parent = nullptr; // 新节点的父节点指针
        Node* cmpNode = root;   // 用于比较的节点，初始为根节点

        while (cmpNode) {
            parent = cmpNode; // 保留当前节点作为新节点的潜在父节点
            // 如果新节点的键小于当前比较节点的键，则向左子树移动
            if (newNode->key < cmpNode->key) {
                cmpNode = cmpNode->left;
            }
            else if (newNode->key > cmpNode->key) {
                cmpNode = cmpNode->right;
            }
            else {
                // 如果键值相等，说明数中已有相同键节点，删除新节点返回
                delete newNode;
                return;
            }
        }

        //树大小增加
        size++;

        // 将新节点的父节点设为找到的父节点位置
        newNode->parent = parent;
        //如果父节点为空，说明树是空的，新节点成为根节点
        if (!parent) {
            root = newNode;
        }
        // 新节点放在哪边子树
        else if (newNode->key < parent->key) {
            parent->left = newNode;
        }
        else {
            parent->right = newNode;
        }

        //插入新节点后，调用修复函数修复可能破坏的红黑树性质
        insertFixup(newNode);
    }

    // 中序遍历
    void inorderTraversal(Node* node) const {
        if (node) {
            inorderTraversal(node->left);
            std::cout << node->key << " ";
            std::cout << node->value << " ";
            inorderTraversal(node->right);
        }
    }

    // 辅助函数，用新节点替换旧节点
    void replaceNode(Node* targetNode, Node* newNode) {
        if (!targetNode->parent) {
            root = newNode;
        }
        else if (targetNode == targetNode->parent->left) {
            targetNode->parent->left = newNode;
        }
        else {
            targetNode->parent->right = newNode;
        }
        if (newNode) {
            newNode->parent = targetNode->parent;
        }
    }

    // 寻找以某个节点为根节点的子树中的最小节点
    Node* findMinimumNode(Node* node) {
        while (node->left) {
            node = node->left;
        }
        return node;
    }

    //removeFixup函数用于删除节点后恢复红黑树的性质
    void removeFixup(Node* node) {
        // 如果节点为Nil并且没有父节点，说明它是唯一的节点，直接返回
        if (node == Nil && node->parent == nullptr) {
            return;
        }

        //一直循环检查到根节点为止
        while (node != root) {
            //如果节点是其父节点的左子节点
            if (node == node->parent->left) {
                // 兄弟节点是节点父亲的右子节点
                Node* sibling = node->parent->right;

                // 情况1: 节点的兄弟节点是红色
                if (getColor(sibling) == Color::RED) {
                    // 重新着色兄弟节点和父节点，再左旋
                    setColor(sibling, Color::BLACK);
                    setColor(node->parent, Color::RED);
                    leftRotate(node->parent);
                    // 旋转后更新兄弟节点
                    sibling = node->parent->right;

                }

                //情况2：兄弟节点的两个子节点都是黑色
                if (getColor(sibling->left) == Color::BLACK &&
                    getColor(sibling->right) == Color::BLACK) {
                    //重新着色兄弟节点并向上移动
                    setColor(sibling, Color::RED);
                    node = node->parent;
                    // 如果父节点是红色，将其改为黑色
                    if (node->color == Color::RED) {
                        node->color = Color::BLACK;
                        node = root;
                    }
                }
                else {
                    // 情况3：兄弟节点的右子节点是黑色
                    if (getColor(sibling->right) == Color::BLACK) {
                        // 重新着色兄弟节点和兄弟节点的左子节点，并右旋
                        setColor(sibling->left, Color::BLACK);
                        setColor(sibling, Color::RED);
                        rightRotate(sibling);
                        // 旋转后更新兄弟节点
                        sibling = node->parent->right;
                    }

                    // 情况4：兄弟节点的右子节点是红色
                    setColor(sibling, getColor(node->parent));
                    setColor(node->parent, Color::BLACK);
                    setColor(sibling->right, Color::BLACK);
                    leftRotate(node->parent);
                    // 移动到根节点结束
                    node = root;
                }
            }
            else {
                // 当节点是其父节点的右子节点时，对称的情况
                Node* sibling = node->parent->left;

                if (getColor(sibling) == Color::RED) {
                    setColor(sibling, Color::BLACK);
                    setColor(node->parent, Color::RED);
                    rightRotate(node->parent);
                    sibling = node->parent->left;
                }

                if (getColor(sibling->right) == Color::BLACK &&
                    getColor(sibling->left) == Color::BLACK) {
                    setColor(sibling, Color::RED);
                    node = node->parent;
                    if (node->color == Color::RED) {
                        node->color = Color::BLACK;
                        node = root;
                    }
                }
                else {
                    if (getColor(sibling->left) == Color::BLACK) {
                        setColor(sibling->right, Color::BLACK);
                        setColor(sibling, Color::RED);
                        leftRotate(sibling);
                        sibling = node->parent->left;
                    }
                    setColor(sibling, getColor(node->parent));
                    setColor(node->parent, Color::BLACK);
                    setColor(sibling->left, Color::BLACK);
                    rightRotate(node->parent);
                    node = root;
                }
            }
        }

        // 确保当前节点为黑色
        setColor(node, Color::BLACK);
    }

    // 获取颜色，空指针为黑色
    Color getColor(Node* node) {
        if (node == nullptr) {
            return Color::BLACK;
        }
        return node->color;
    }

    void setColor(Node* node, Color color) {
        if (node == nullptr) {
            return;
        }
        node->color = color;
    }

    //  取消Nil哨兵的连接
    void dieConnectNil() {
        if (Nil == nullptr) {
            return;
        }
        if (Nil->parent != nullptr) {
            if (Nil == Nil->parent->left) {
                Nil->parent->left = nullptr;
            }
            else {
                Nil->parent->right = nullptr;
            }
        }
    }

    // 删除节点
    void deleteNode(Node* del) {
        Node* rep = del; // rep(替代节点)初始指向要删除的节点
        Node* child = nullptr;      // 要删除节点的孩子节点
        Node* parentRP;             // 替代节点的父节点
        Color origCol = rep->color; // 保存要删除节点的原始颜色

        // 如果删除节点没有左孩子
        if (!del->left) {
            rep = del->right;        // 替代节点指向删除节点的右孩子
            parentRP = del->parent;  // 更新替代节点的父节点
            origCol = getColor(rep); // 获取替代节点的颜色
            replaceNode(del, rep);   // 用替换节点替换删除节点

        }
        // 如果删除节点没有右孩子
        else if (!del->right) {
            rep = del->left;        // 替代节点指向删除节点的左孩子
            parentRP = del->parent;  // 更新替代节点的父节点
            origCol = getColor(rep); // 获取替代节点的颜色
            replaceNode(del, rep);   // 用替换节点替换删除节点

        }
        // 如果删除节点有两个孩子
        else {
            // 找到删除节点右子树中的最小节点作为替代节点
            rep = findMinimumNode(del->right);
            origCol = rep->color; // 保存替代节点原始颜色
            // 如果替代节点不是删除节点的直接右孩子
            if (rep != del->right) {
                parentRP = rep->parent;// 更新替代节点的父节点
                child = rep->right;    // 替代节点的右孩子变成要处理的孩子节点
                parentRP->left = child;  // 替代节点的父节点的左孩子指向替代节点的孩子
                //（因为替代节点是最小节点，所以不可能有左孩子）
                if (child != nullptr) {
                    child->parent = parentRP; // 如果替代节点的孩子存在，则更新其父节点
                }
                // 将替代节点放到删除节点的位置
                del->left->parent = rep;
                del->right->parent = rep;
                rep->left = del->left;
                rep->right = del->right;
                // 如果删除节点有父节点，更新父节点的孩子指向
                if (del->parent != nullptr) {
                    if (del == del->parent->left) {
                        del->parent->left = rep;
                        rep->parent = del->parent;
                    }
                    else {
                        del->parent->right = rep;
                        rep->parent = del->parent;
                    }
                }
                else {
                    root = rep;
                    root->parent = nullptr;
                }
            }
            else {
                // 如果替代节点是删除节点的直接右孩子
                child = rep->right;     // 孩子节点指向替代节点的右孩子
                rep->left = del->left;  // 替代节点的左孩子指向删除节点的左孩子
                del->left->parent = rep;// 更新左孩子的父节点
                // 更新删除节点父节点的孩子指向
                if (del->parent != nullptr) {
                    if (del == del->parent->left) {
                        del->parent->left = rep;
                        rep->parent = del->parent;
                    }
                    else {
                        del->parent->right = rep;
                        rep->parent = del->parent;
                    }
                }
                else {
                    // 如果删除节点是根节点
                    root = rep;
                    root->parent = nullptr;
                }
                parentRP = rep;   // 更新替代节点的父节点  
            }
        }

        // 如果替代节点存在，更新其颜色为删除节点的颜色
        if (rep != nullptr) {
            rep->color = del->color;
        }
        // 如果替代节点不存在，将删除节点的颜色赋给origCol变量
        else {
            origCol = del->color;
        }
        // 如果原始颜色是黑色，需要进行额外的修复操作，
        // 因为黑色节点的删除可能会破坏红黑树的性质
        if (origCol == Color::BLACK) {
            // 如果存在孩子节点，修复
            if (child != nullptr) {
                removeFixup(child);
            }
            // 如果不存在孩子节点，将Nil节点（代表空节点）
            //的父节点设置为替代节点的父节点
            else {
                Nil->parent = parentRP;
                // 如果替代节点的父节点存在，设置其对应的孩子指针为Nil节点
                if (parentRP != nullptr) {
                    if (parentRP->left == nullptr) {
                        parentRP->left = Nil;
                    }
                    else {
                        parentRP->right = Nil;
                    }
                }
                // 修复操作
                removeFixup(Nil);
                // 断开Nil节点与树的连接，因为在红黑树中Nil节点通常是单独存在的
                dieConnectNil();
            }
        }

        //删除节点
        delete del;
    }

public:
    // 构造函数
    RedBlackTree() : root(nullptr), size(0), Nil(new Node()) {
        Nil->color = Color::BLACK;
    }

    // 插入
    void insert(const Key& key, const Value& value) {
        insertNode(key, value);
    }

    // 删除
    void remove(const Key& key) {
        Node* nodeToBeRemoved = lookUp(key);
        if (nodeToBeRemoved != nullptr) {
            deleteNode(nodeToBeRemoved);
            size--;
        }
    }

    Value* at(const Key& key) {
        auto ans = lookUp(key);
        if (ans != nullptr) {
            return &ans->value;
        }
        return nullptr;
    }

    int getSize() {
        return size;
    }

    bool empty() { return size == 0; }

    // 中序遍历打印
    void print() {
        inorderTraversal(root);
        std::cout << std::endl;
    }

    void clear() {
        deleteNode(root);
        size = 0;
    }

    // 析构函数
    ~RedBlackTree() {
        // 释放节点内存
        deleteTree(root);
    }

private:
    // 递归释放节点内存
    void deleteTree(Node* node) {
        if (node) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

};

int main() {
    // 创建红黑树实例
    RedBlackTree<int, int> rbTree;

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
            rbTree.insert(key, value);
        }

        if (command == "size") {
            std::cout << rbTree.getSize() << std::endl;
        }

        if (command == "at") {
            iss >> key;
            int* res = rbTree.at(key);
            if (res == nullptr) {
                std::cout << "not exist" << std::endl;
            }
            else {
                std::cout << *res << std::endl;
            }
        }

        if (command == "remove") {
            iss >> key;
            rbTree.remove(key);
        }

        if (command == "print") {
            if (rbTree.empty()) {
                std::cout << "empty" << std::endl;
            }
            else {
                rbTree.print();
            }
        }
    }

    return 0;
}