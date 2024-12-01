#include <iostream>
#include <math.h>
#include <time.h>

using namespace std;

class Node
{
private:
    int key;
    int priority;
    int size;
    double sum;
    double promise;
    Node* left;
    Node* right;
    Node* parent;
public:
    int getKey() { return key; }
    int getPriority() { return priority; }
    int getSize() { return size; }
    double getPromise() { return promise; }
    double getSum() { return sum + promise; }

    Node* getLeft() { return left; }
    Node* getRight() { return right; }
    Node* getParent() { return parent; }

    void setLeft(Node* N) { left = N; }
    void setRight(Node* N) { right = N; }
    void setSum(double value){ sum = value;}
    void updateSize() {size = 1 + (left ? left->getSize() : 0) + (right ? right->getSize() : 0); }
    void updateSum() { sum = (left ? left->getSum() : 0) + (right ? right->getSum() : 0); }
    void setSize(int value) { size = value; }
    void setPromise(double value) { promise = value; }
    void FulfillPromise() {
        if (promise != 0) {
            if (left) left->setPromise(left->getPromise() + promise);
            if (right) right->setPromise(right->getPromise() + promise);

            sum += promise * size;
            promise = 0;
        }
    }
    void setParent(Node* N) { parent = N; }
    Node(int k, int p, double prom)
    {
        key = k;
        priority = p;
        left = right = NULL;
        sum = key; 
        size = 1;
        promise = prom;
        parent = NULL;
    }
    Node(int k)
    {
        key = k;
        srand(time(NULL));
        priority = rand();
        left = right = NULL;
        sum = key; 
        size = 1;
        promise = 0;
        parent = NULL;
    }
    Node()
    {
        left = right = NULL;
        sum = 0;
        size = 1;
        promise = 0;
        parent = NULL;
    }
    Node* Min() {
        Node* current = this;
        while (current->left != NULL)
            current = current->left;
        return current;
    }
    Node* Max() {
        Node* current = this;
        while (current->right != NULL)
            current = current->right;
        return current;
    }
    Node* successor() {
        if (right != NULL)
            return right->Min();

        Node* current = this;
        Node* parent = current->parent;
        while (parent != NULL && current == parent->right) {
            current = parent;
            parent = parent->parent;
        }
        return parent;
    }
    Node* predecessor() {
        if (left != NULL)
            return left->Max();
        Node* current = this;
        Node* parent = current->parent;
        while (parent != NULL && current == parent->left) {
            current = parent;
            parent = parent->parent;
        }
        return parent;
    }
    friend ostream& operator<<(ostream& stream, Node& N)
    {
        stream << N.key << "; " << N.priority << ";\tpromise: " << N.promise << ",\tf: " << N.getSum() << ", size: "<<N.size<<"\n";
        if (N.getLeft() != NULL)
            stream << *N.getLeft();
        if (N.getRight() != NULL)
            stream << *N.getRight();
        return stream;
    }
};

class Treap
{
protected:
    Node* root;

    Node* merge(Node* L, Node* R) {
        if (L->getPriority() > R->getPriority()) {
            if (L->getRight() != NULL) {
                L->setRight(merge(L->getRight(), R));
            } else {
                L->setRight(R);
            }
            L->updateSize();
            L->updateSum();
            return L;
        } else {
            if (R->getLeft() != NULL) {
                R->setLeft(merge(L, R->getLeft()));
            } else {
                R->setLeft(L);
            }
            R->updateSize();
            R->updateSum();
            return R;
        }
    }
    Node* merge_in_split(Node* L, Node* R)
    {
        Node* corrected_left = L; Node* corrected_right = R;
        bool bRootIsMoved = false;

        if (L->getKey() > R->getKey())
        {
            corrected_right = L;
            corrected_left = R;
            bRootIsMoved = true;
        }
        if (corrected_left->getPriority() > corrected_right->getPriority())
        {
            if (corrected_left->getRight() != NULL)
                corrected_left->setRight(merge_in_split(corrected_left->getRight(), corrected_right));
            else
                corrected_left->setRight(corrected_right);
            corrected_left->setSize((corrected_right != NULL ? corrected_right->getSize() : 0) + (corrected_left->getLeft() != NULL ? corrected_right->getLeft()->getSize() : 0) + 1);
            corrected_left->updateSum();
            return corrected_left;
        }
        else
        {
            if (corrected_right->getLeft() != NULL)
            {
                corrected_left = merge_in_split(corrected_left, corrected_right->getLeft());
                corrected_right->setLeft(NULL);
                corrected_right->setSize((corrected_right->getRight() != NULL ? corrected_right->getRight()->getSize() : 0) + 1);
                corrected_right->updateSum();
                corrected_left = merge_in_split(corrected_left, corrected_right);
            }
            else
            {
                corrected_right->setLeft(corrected_left);
                corrected_right->setSize((corrected_left != NULL ? corrected_left->getSize() : 0) + (corrected_right->getRight() != NULL ? corrected_right->getSize() : 0) + 1);
                corrected_right->updateSum();
                corrected_left = corrected_right;
            }
            return corrected_left;
        }
    }

public:
    void Split(int splitKey, Treap* Left, Treap* Right) {
        if (root == nullptr) {
            *Left = Treap();
            *Right = Treap();
            return;
        }
        *Left = Treap();
        *Right = Treap();
        for (Treap::Iterator it = this->begin(); it != this->end(); ++it) {
            if ((*it).getKey() < splitKey) {
                Left->insert((*it).getKey(), (*it).getPriority());
            } else {
                Right->insert((*it).getKey(), (*it).getPriority());
            }
        }
    }

    Node* getRoot() { return root; }
    Treap() { root = NULL; }
    Treap(int root_key, int root_prior, Treap* Left, Treap* Right)
    {
        root = new Node(root_key, root_prior, 0);
        root->setLeft(Left->root);
        root->setRight(Right->root);
        root->updateSum();
        root->setSize((root != NULL ? root->getLeft()->getSize() : 0) + (root->getRight() != NULL ? root->getRight()->getSize() : 0) + 1);
    }
    Treap(Node* N, Treap* Left, Treap* Right)
    {
        root = N;
        root->setLeft(Left->root);
        root->setRight(Right->root);
        root->updateSum();
        root->setSize((root != NULL ? root->getLeft()->getSize() : 0) + (root->getRight() != NULL ? root->getRight()->getSize() : 0) + 1);
    }
    Treap(Node* N){ root = N; }
    void PreOrder(Node* N, void (*f)(Node*))
    {
        if (N != NULL)
            f(N);
        if (N != NULL && N->getLeft() != NULL)
            PreOrder(N->getLeft(), f);
        if (N != NULL && N->getRight() != NULL)
            PreOrder(N->getRight(), f);
    }
    void Merge(Node* N)
    {
        Treap* R = new Treap();
        R->root = N;
        Merge(R);
    }
    void Merge(int key, int prior, int prom)
    {
        Node* N = new Node(key, prior, prom);
        Merge(N);
    }
    void MergeInSplit(Node* N)
    {
        Treap* R = new Treap();
        R->root = N;
        MergeInSplit(R);
    }
    void MergeInSplit(int key, int prior, int prom)
    {
        Node* N = new Node(key, prior, prom);
        MergeInSplit(N);
    }
    void Merge(Treap* R)
    {
        if (root == NULL) { root = R->root; return; }
        if (R->root == NULL) return;

        if (root->getPriority() > R->root->getPriority())
        {
            if (root->getRight() != NULL)
                root->setRight(merge(root->getRight(), R->root));
            else
                root->setRight(R->root);
            root->setSize((root->getLeft() != NULL ? root->getLeft()->getSize() : 0) + (root->getRight() != NULL ? root->getRight()->getSize() : 0) + 1);
            root->updateSum();

        }
        else
        {
            if (R->root->getLeft() != NULL)
            {
                root = merge(root, R->root->getLeft());
                R->root->setLeft(root);
                R->root->setSize((R->root->getLeft() != NULL ? R->root->getLeft()->getSize() : 0) + (R->root->getRight() != NULL ? R->root->getRight()->getSize() : 0) + 1);
                R->root->updateSum();
                root = R->root;
            }
            else
            {
                R->root->setLeft(root);
                R->root->setSize((R->root->getLeft() != NULL ? R->root->getLeft()->getSize() : 0) + (R->root->getRight() != NULL ? R->root->getRight()->getSize() : 0) + 1);
                R->root->updateSum();
                root = R->root;
            }
        }
    }
    void MergeInSplit(Treap* R)
    {
        if (root == NULL) { root = R->root; return; }
        if (R->root == NULL) return;

        Node* corrected_right_root = R->root;
        Node* corrected_root = root;
        bool bRootIsMoved = false;

        if (root->getKey() > R->root->getKey())
        {
            corrected_right_root = root;
            corrected_root = R->root;
            bRootIsMoved = true;
        }
        if (corrected_root->getPriority() > corrected_right_root->getPriority())
        {
            if (corrected_root->getRight() != NULL)
                corrected_root->setRight(merge_in_split(corrected_root->getRight(), corrected_right_root));
            else
                corrected_root->setRight(corrected_right_root);
            corrected_root->setSize((corrected_root->getLeft() != NULL ? corrected_root->getRight()->getSize() : 0) + (corrected_root->getRight() != NULL ? corrected_root->getRight()->getSize() : 0) + 1);
            corrected_root->updateSum();
        }
        else
        {
            if (corrected_right_root->getLeft() != NULL)
            {
                corrected_root = merge_in_split(corrected_root, corrected_right_root->getLeft());
                corrected_right_root->setLeft(corrected_root);
                corrected_right_root->setSize((corrected_right_root->getLeft() != NULL ? corrected_right_root->getLeft()->getSize() : 0) + (corrected_right_root->getRight() != NULL ? corrected_right_root->getRight()->getSize() : 0) + 1);
                corrected_right_root->updateSum();
                corrected_root = corrected_right_root;
            }
            else
            {
                corrected_right_root->setLeft(corrected_root);
                corrected_right_root->setSize((corrected_right_root->getLeft() != NULL ? corrected_right_root->getLeft()->getSize() : 0) + (corrected_right_root->getRight() != NULL ? corrected_right_root->getRight()->getSize() : 0) + 1);
                corrected_right_root->updateSum();
                corrected_root = corrected_right_root;
            }
        }
        root = corrected_root;
    }
    friend ostream& operator<<(ostream& stream, Treap& T)
    {
        if (T.root != NULL)
            stream << *T.root;
        return stream;
    }
    void insert(int key, int prior = -1) {
        Node* N;
        if (prior == -1) N = new Node(key);
        else N = new Node(key, prior, 0);
        Treap* L = new Treap;
        Treap* R = new Treap;
        Split(key, L, R);
        if (L->root == NULL && R->root == NULL) {
            root = N;
        } else {
            Treap* KeyTreap = new Treap(); 
            KeyTreap->Merge(N);
            
            if (L->root != NULL) {
                L->Merge(KeyTreap);
                L->Merge(R);
                root = L->root;
            } else {
                R->Merge(KeyTreap);
                root = R->root;
            }
        }
        if (root != NULL) {
            setParentPointers(root, NULL);
        }
    }
    void setParentPointers(Node* node, Node* parent) {
        if (node != NULL) {
            node->setParent(parent);
            setParentPointers(node->getLeft(), node);
            setParentPointers(node->getRight(), node);
        }
    }
    void Remove(int key)
    {
        Treap L, R;
        Split(key, &L, &R);
        L.Merge(&R);
        *this = L;
    }
    void MultipleAdd(int add, int left = -1, int right = -1) {
        if (root == nullptr) return;
        if (left == -1 && right == -1) {
            root->setPromise(root->getPromise() + add);
            return;
        }
        Treap L, M, R;
        Split(right, &M, &R);
        if (M.root != nullptr) {
            M.Split(left - 1, &L, &M);
        }
        if (M.root != nullptr) {
            M.root->setPromise(M.root->getPromise() + add);
        }
        L.Merge(&M);
        L.Merge(&R);
        *this = L;
    }

    class Iterator {
        Node* current;
    public:
        Iterator(Node* node) : current(node) {}

        Node& operator*() { return *current; }

        Iterator& operator++() {
            if (current != NULL) current = current->successor();
            return *this;
        }
        Iterator operator++(int) {
            Iterator current = *this;
            ++(*this);
            return current;
        }
        Iterator& operator--() {
            if (current != NULL) current = current->predecessor();
            return *this;
        }
        Iterator operator--(int) {
            Iterator current = *this;
            --(*this);
            return current;
        }
        bool operator==(const Iterator& other) const {
            return current == other.current;
        }
        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
    };
    Iterator begin() {
        return root ? Iterator(root->Min()) : Iterator(nullptr);
    }

    Iterator end() {
        return Iterator(nullptr);
    }
};

void print(Node* N) { cout << N->getKey() << "; " << N->getPriority(); }

class ImplicitTreap : protected Treap {
public:
    ImplicitTreap() : Treap() {}

    int size() {
        return (root != NULL) ? root->getSize() : 0;
    }
    double getSum() {
        return (root != NULL) ? root->getSum() : 0.0;
    }
    void Merge(ImplicitTreap* R) {
        if (root == NULL) {
            root = R->root;
            return;
        }
        if (R->root == NULL) {
            return;
        }

        if (root->getPriority() > R->root->getPriority()) {
            if (root->getRight() == NULL) {
                root->setRight(R->root);
            } else {
                root->setRight(merge(root->getRight(), R->root));
            }
            root->updateSize();
            root->updateSum();
        } else {
            if (R->root->getLeft() == NULL) {
                R->root->setLeft(root);
            } else {
                R->root->setLeft(merge(root, R->root->getLeft()));
            }
            R->root->updateSize();
            R->root->updateSum();
            root = R->root;
        }
    }
    void Merge(Node* N) { 
        ImplicitTreap* newTreap = new ImplicitTreap(); 
        newTreap->root = N; 
        Merge(newTreap); 
    }
    void Merge(int priority, int promise) { 
        Node* N = new Node(0, priority, promise); 
        Merge(N); 
    }
    void Split(int splitKey, Treap* Left, Treap* Right) {
        if (root == nullptr) {
            *Left = Treap();
            *Right = Treap();
            return;
        }
        *Left = Treap();
        *Right = Treap();

        for (Treap::Iterator it = this->begin(); it != this->end(); ++it) {
            Node* current = new Node((*it).getKey(), (*it).getPriority(), (*it).getPromise());
            if (current->getKey() < splitKey) {
                Left->Merge(current); 
            } else {
                Right->Merge(current);
            }
            current->updateSize();
            current->updateSum();
        }
        

    }
    void insert(int key, int priority, double promise) {
        Node* N = new Node(key, priority, promise);

        ImplicitTreap* L = new ImplicitTreap;
        ImplicitTreap* R = new ImplicitTreap;
        Split(key, L, R);

        if (L->root == NULL && R->root == NULL) {
            root = N;
        } else {
            ImplicitTreap* KeyTreap = new ImplicitTreap();
            KeyTreap->Merge(N);
            if (L->root != NULL) {
                L->Merge(KeyTreap);
                L->Merge(R);
                root = L->root;
            } else {
                R->Merge(KeyTreap);
                root = R->root;
            }
        }
        if (root != NULL) {
            setParentPointers(root, NULL);
        }
    }
    void Remove(int index) {
        ImplicitTreap L, R;
        Split(index, &L, &R);
        L.Merge(&R);
        *this = L;
    }
    double sum(int a, int b) {
        ImplicitTreap* left = new ImplicitTreap();
        ImplicitTreap* right = new ImplicitTreap();
        Split(b + 1, left, right);
        double sumB = left->getSum();
        ImplicitTreap* leftA = new ImplicitTreap();
        ImplicitTreap* rightA = new ImplicitTreap();
        Split(a, leftA, rightA);
        double sumA = leftA->getSum();
        return sumB - sumA;
    }

    friend ostream& operator<<(ostream& stream, ImplicitTreap& T);
};

ostream& operator<<(ostream& stream, ImplicitTreap& T) {
    if (T.root != NULL)
        stream << *T.root;
    return stream;
}


int main() {
    // 4.1 
    
    Treap T;

    T.insert(1, 2);
    T.insert(3, 3);
    T.insert(4, 5);
    T.insert(6, 4);
    T.insert(9, 1);

    cout << T << endl;

    cout << "Keys of tree elements by iterator:" << endl;
    Treap::Iterator it = T.begin();
    for (it; it != T.end(); ++it) {
       cout << (*it).getKey() << " ";
    }

    // Функции min и max
    Node* minNode = T.getRoot()->Min();
    Node* maxNode = T.getRoot()->Max();
    cout << "Min: " << minNode->getKey() << ", Max: " << maxNode->getKey() << endl << endl;


    // Split 
    Treap Left, Right;
    T.Split(6, &Left, &Right);
    cout << "Split Treap at key 6:" << endl;
    cout << "Left Treap:" << endl;
    cout << Left << endl;
    cout << "Right Treap:" << endl;
    cout << Right << endl;

    // Слияние деревьев
    Right.Merge(&Left);
    cout << "Merged Treap:" << endl;
    cout << Right << endl << endl << endl;

    //----------------------------------------------------------------------
    // 4.2
    cout << "ImplicitTreap:" << endl;
    ImplicitTreap tree;
    tree.insert(1, 1, 1);
    tree.insert(2, 2, 2);
    tree.insert(3, 3, 3.3);
    tree.insert(4, 4, 4);
    tree.insert(5, 5, 5);
    tree.insert(6, 6, 6.6);
    tree.insert(7, 7, 7);
    
    cout << tree << endl;

    // Сумма на отрезке [2,7]
    double sum = tree.sum(2,7);
    cout << "sum on [2,7]: " << sum<< endl;

    return 0;
}


