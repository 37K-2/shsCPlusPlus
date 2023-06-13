#ifndef NODES_H
#define NODES_H

template <class C>
struct llNode {
    llNode *next;
    C data;

    llNode(C);
};

template <class C>
struct treeNode {
    treeNode *left;
    treeNode *right;
    C data;

    treeNode(C);
    
    bool isOperator();
    bool isNum();
};


// implement

template <class C>
llNode<C>::llNode(C data) {
    this->next = nullptr;
    this->data = data;
}

template <class C>
treeNode<C>::treeNode(C data) {
    this->left = nullptr;
    this->right = nullptr;
    this->data = data;
}

template <class C>
bool treeNode<C>::isOperator() {
    if (this->data == '+' || this->data == '-' || this->data == '*' || this->data == '/' || this->data == '%' || this->data == '^')
        return true;
    return false;
}

template <class C>
bool treeNode<C>::isNum() {
    return this->data >= '0' && this->data <= '9';
}

#endif 