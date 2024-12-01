#include <iostream>
#include <string>
#include <stdexcept> 
#include <list>
using namespace std;


template <class Key>
class Patient {
protected:
    string lastName;
    string firstName;
    short birthDay;
    short birthMonth;
    short birthYear;    
    string phone;
    string address;
    long cardNumber;
    short bloodGroup;
    char rhFactor;

public:
    Patient() {}
    Patient(string ln, string fn, short bd, short bm, short by, string ph, string ad, long cn, short bg, char rh)
        : lastName(ln), firstName(fn), birthDay(bd), birthMonth(bm), birthYear(by), phone(ph), address(ad), cardNumber(cn), bloodGroup(bg), rhFactor(rh) {}
    Patient(string ln, string fn) : lastName(ln), firstName(fn) {}
    ~Patient() {};
    string get_lastname() const { return lastName; }
    string get_firstname() const { return firstName; }
    string get_phone() const { return phone; }
    string get_address() const { return address; }
    short get_birthday() const { return birthDay; }
    short get_birthmonth() const { return birthMonth; }
    short get_birthyear() const { return birthYear; }
    short get_blood() const { return bloodGroup; }
    long get_card() const { return cardNumber; }
    char get_rhfactor() const { return rhFactor; }

    void set_lastname(string input) { lastName = input; }
    void set_firstname(string input) { firstName = input; }
    void set_phone(string input) { phone = input; }
    void set_address(string input) { address = input; }
    void set_birthday(short input) { birthDay = input; }
    void set_birthmonth(short input) { birthMonth = input; }
    void set_birthyear(short input) { birthYear = input; }
    void set_card(long input) { cardNumber = input; }
    void set_blood(short input) { bloodGroup = input; }
    void set_rhfactor(char input) { rhFactor = input; }

    bool operator<(const Patient& other) const {
        return Key::compare(*this, other);
    }
    bool operator>(const Patient& other) const {return other < *this;}
    bool operator==(const Patient& other) const {return !(other < *this) && !(*this < other);}
    bool operator!=(const Patient& other) const {return !(other == *this);}

    friend ostream& operator<<(ostream& s, const Patient& p) 
    {
        s << "Last Name: " << p.lastName << endl
          << "First Name: " << p.firstName << endl
          << "Birth Date: " << p.birthDay << "-" << p.birthMonth << "-" << p.birthYear << endl
          << "Card Number: " << p.cardNumber << endl
          << "Phone number: " << p.phone << endl
          << "Address: " << p.address << endl
          << "Blood group: " << p.bloodGroup << p.rhFactor << endl << endl;
        return s;
    }
};

struct Name {
    static bool compare(const Patient<Name>& p1, const Patient<Name>& p2) {
        if (p1.get_lastname() == p2.get_lastname())
            return p1.get_firstname() < p2.get_firstname();
        return (p1.get_lastname() < p2.get_lastname());
    }
};

template <class K, class V>
struct Pair {
    K key;  
    V value; 

    Pair() : key(K()), value(V()) {}

    Pair(const K& a, const V& b) : key(a), value(b) {}

    Pair(const Pair& p) : key(p.key), value(p.value) {}

    Pair& operator=(const Pair& p) {
        key = p.key;
        value = p.value;
        return *this;
    }

    bool operator==(const Pair& p) const {
        return key == p.key && value == p.value;
    }

    bool operator<(const Pair& p) const {
        return key < p.key || (!(p.key < key) && value < p.value);
    }

    bool operator>(const Pair& p) const {
        return p < *this; 
    }
    template <class T1, class T2>
    friend ostream& operator<<(ostream& s, const Pair<T1,T2>& p){
        s << p.value << endl;
        return s;
    }

};


template<class K, class T>
class Node {
protected:
    Pair<K, T> p;  
    Node<K, T>* left;
    Node<K, T>* right;
    Node<K, T>* parent;
    int height;

public:

    Node(K k, T n) : p(k, n), left(nullptr), right(nullptr), parent(nullptr), height(1) {}

    Node() : left(nullptr), right(nullptr), parent(nullptr), height(1) {}

    virtual void setValue(T d) { p.value = d; } 
    virtual T getValue() const { return p.value; } 
    virtual K getKey() const { return p.key; } 
    int getHeight() const { return height; }

    virtual Node<K, T>* getLeft() const { return left; }
    virtual Node<K, T>* getRight() const { return right; }
    virtual Node<K, T>* getParent() const { return parent; }

    virtual void setLeft(Node<K, T>* N) { left = N; }
    virtual void setRight(Node<K, T>* N) { right = N; }
    virtual void setParent(Node<K, T>* N) { parent = N; }
    virtual void setHeight(int h) { height = h; }

    Node<K, T>* successor() {
        Node<K, T>* Current;
        if (right != nullptr) {
            Current = right;
            while (Current->getLeft() != nullptr) {
                Current = Current->getLeft();
            }
            return Current;
        } 
        else {
            Current = parent;
            while (Current != nullptr && Current->getKey() <= getKey()) {
                Current = Current->getParent();
            }
            return Current;
        }
    }
    Node<K, T>* predecessor() {
        Node<K, T>* Current;
        if (left != nullptr) {
            Current = left;
            while (Current->getRight() != nullptr) {
                Current = Current->getRight();
            }
            return Current;
        } 
        else {
            Current = parent;
            while (Current != nullptr && Current->getKey() >= getKey()) {
                Current = Current->getParent();
            }
            return Current;
        }
    }
    template<class T1, class T2>
    friend ostream& operator<<(ostream& s, const Node<T1, T2>& N) {
        s << N.p.value;
        return s;
    }
};

template<class K, class T>
void print(Node<K, T>* N) {
    cout << "\n" << N->getData();
}

template<class K,class T>
class Tree
{
protected:
    Node<K,T>* root;

    virtual Node<K, T>* push_R(Node<K, T>* N, Node<K, T>* Current) {
        if (N == nullptr) return nullptr;
        if (root == nullptr) { root = N; return N; }

        if (Current->getKey() > N->getKey()) {
            if (Current->getLeft() != nullptr) return push_R(N, Current->getLeft());
            else { Current->setLeft(N); N->setParent(Current); }
        }
        if (Current->getKey() < N->getKey()) {
            if (Current->getRight() != nullptr) return push_R(N, Current->getRight());
            else { Current->setRight(N); N->setParent(Current); }
        }
        return N;
    }

    virtual Node<K, T>* Find_R(K key, Node<K, T>* Current) {
        if (Current == nullptr) return nullptr;
        if (Current->getKey() == key) return Current;
        if (Current->getKey() > key) return Find_R(key, Current->getLeft());
        if (Current->getKey() < key) return Find_R(key, Current->getRight());
        return nullptr;
    }
public:
    virtual Node<K, T>* getRoot() { return root; }

    Tree<K, T>() : root(nullptr) {}

    virtual Node<K, T>* push(Node<K, T>* N) {
        return push_R(N, root);
    }
    
    virtual Node<K, T>* push(K k, T n) {
        Node<K, T>* N = new Node<K, T>(k, n);
        return push(N);
    }

    virtual void Remove(Node<K, T>* N) {
        if (N == NULL) return;

        if (N->getLeft() == NULL && N->getRight() == NULL) {
            if (N == root) {
                root = NULL; 
            } else {
                Node<K, T>* parent = N->getParent();
                if (parent->getLeft() == N) {
                    parent->setLeft(NULL);
                } else {
                    parent->setRight(NULL);
                }
            }
            delete N;
        }
        else if (N->getLeft() == NULL || N->getRight() == NULL) {
            Node<K, T>* child = (N->getLeft() != NULL) ? N->getLeft() : N->getRight();
            if (N == root) {
                root = child; 
            } else {
                Node<K, T>* parent = N->getParent();
                if (parent->getLeft() == N) {
                    parent->setLeft(child);
                } else {
                    parent->setRight(child);
                }
            }
            child->setParent(N->getParent());
            delete N;
        }
        else {
            Node<K, T>* minNode = Min(N->getRight());
            N->setValue(minNode->getValue());
            Remove(minNode); 
        }
    }

    virtual Node<K,T>* Min(Node<K,T>* Current = NULL) const
    {
        if (root == NULL) return NULL;
        if (Current == NULL)
            Current = root;
        for(;Current->getLeft()!=NULL;Current = Current->getLeft());
        return Current;
    }

    virtual Node<K,T>* Max(Node<K,T>* Current = NULL) const
    {
        if (root == NULL) return NULL;
        if (Current == NULL)
            Current = root;
        for(;Current->getRight()!=NULL;Current = Current->getRight());
        return Current;
    }

    virtual Node<K, T>* Find(K key) {
        return Find_R(key, root);
    }

    //три обхода дерева
    virtual void PreOrder(Node<K,T>* N, void (*f)(Node<K,T>*))
    {
        if (N != NULL)
            f(N);
        if (N != NULL && N->getLeft() != NULL)
            PreOrder(N->getLeft(), f);
        if (N != NULL && N->getRight() != NULL)
            PreOrder(N->getRight(), f);
    }

    virtual void InOrder(Node<K,T>* N, void (*f)(Node<K,T>*))
    {
        if (N != NULL && N->getLeft() != NULL)
            InOrder(N->getLeft(), f);
        if (N != NULL)
            f(N);
        if (N != NULL && N->getRight() != NULL)
            InOrder(N->getRight(), f);
    }

    virtual void PostOrder(Node<K,T>* N, void (*f)(Node<K,T>*))
    {
        if (N != NULL && N->getLeft() != NULL)
            PostOrder(N->getLeft(), f);
        if (N != NULL && N->getRight() != NULL)
            PostOrder(N->getRight(), f);
        if (N != NULL)
            f(N);
    }

    void InOrderPrint(Node<K, T>* N) const {
        if (N != NULL) {
            InOrderPrint(N->getLeft());  
            cout << N->getData() << endl;  
            InOrderPrint(N->getRight()); 
        }
    }
    template <class T1, class T2>
    friend ostream& operator<<(ostream& os, const Tree<T1, T2>& tree) {
        tree.InOrderPrint(tree.root); 
        return os;
    }
};

//класс итерируемое дерево поиска
template<class K,class T>
class IteratedTree : public Tree<K,T>
{
public:
    IteratedTree<K,T>() : Tree<K,T>() {}

    //класс итератор по дереву
class iterator {
    private:
        Node<K, T>* ptr;

    public:
        iterator() : ptr(nullptr) {}
        iterator(Node<K, T>* p) : ptr(p) {}
        iterator(const iterator& it) : ptr(it.ptr) {}

        iterator& operator=(const iterator& it) {
            ptr = it.ptr;
            return *this;
        }

        bool operator!=(const iterator& it) const { return ptr != it.ptr; }
        bool operator==(const iterator& it) const { return ptr == it.ptr; }

        Node<K, T>& operator*() {
            if (ptr == nullptr) {
                throw out_of_range("Dereferencing null iterator");
            }
            return *ptr;
        }

        iterator& operator++() {
            if (ptr == nullptr) {
                throw out_of_range("Incrementing null iterator");
            }
            ptr = ptr->successor();
            return *this;
        }

        iterator operator++(int) {
            iterator temp = *this; 
            ++(*this);
            return temp;
        }

        iterator& operator--() {
            if (ptr == nullptr) {
                throw out_of_range("Decrementing null iterator");
            }
            ptr = ptr->predecessor();
            return *this;
        }

        iterator operator--(int) {
            iterator temp = *this;
            --(*this);
            return temp;
        }
    };

    iterator begin() const { return iterator(Tree<K,T>::Min()); }
    iterator end() const { return iterator(Tree<K,T>::Max()); }

    template <class T1, class T2>
    friend ostream& operator<<(ostream& s, const IteratedTree<T1,T2>& tree) 
    {
        typename IteratedTree<T1, T2>::iterator it = tree.begin();
        while (it != tree.end()) {
            s << *it;
            ++it;
        }
        s << *it << endl;
        return s;
    }
};


template<class K, class T>
class AVL_Tree : public IteratedTree<K,T>
{
protected:
    int bfactor(Node<K,T>* p)
    {
        int hl = p->getLeft() ? p->getLeft()->getHeight() : 0;
        int hr = p->getRight() ? p->getRight()->getHeight() : 0;
        return (hr - hl);
    }
    void fixHeight(Node<K, T>* p)
    {
        int hl = p->getLeft() ? p->getLeft()->getHeight() : 0;
        int hr = p->getRight() ? p->getRight()->getHeight() : 0;
        p->setHeight((hl > hr ? hl : hr) + 1);
    }

    Node<K, T>* RotateRight(Node<K, T>* p)
    { 
        Node<K, T>* q = p->getLeft();  
        p->setLeft(q->getRight());  
        if (q->getRight() != nullptr) 
            q->getRight()->setParent(p); 
        q->setRight(p);  
        q->setParent(p->getParent());  
        if (p->getParent() != nullptr) {  
            if (p == p->getParent()->getLeft())
                p->getParent()->setLeft(q);
            else
                p->getParent()->setRight(q);
        } else {
            Tree<K, T>::root = q; 
        }
        p->setParent(q);  
        fixHeight(p);  
        fixHeight(q);
        return q;  
    }

    Node<K, T>* RotateLeft(Node<K, T>* q)
    {
        Node<K, T>* p = q->getRight();  
        q->setRight(p->getLeft());  
        if (p->getLeft() != nullptr) 
            p->getLeft()->setParent(q);  
        p->setLeft(q);  
        p->setParent(q->getParent());  
        if (q->getParent() != nullptr) {  
            if (q == q->getParent()->getLeft())
                q->getParent()->setLeft(p);
            else
                q->getParent()->setRight(p);
        } else {
            Tree<K, T>::root = p;  
        }
        q->setParent(p);  
        fixHeight(q);
        fixHeight(p);
        return p; 
    }


    Node<K, T>* Balance(Node<K, T>* p)
    {
        fixHeight(p);  
        if (bfactor(p) == 2)
        {   
            if (bfactor(p->getLeft()) < 0){
                p->setLeft(RotateLeft(p->getLeft())); 
            }
            return RotateRight(p); 
        }
        if (bfactor(p) == -2)
        {
            if (bfactor(p->getRight()) > 0)
                p->setRight(RotateRight(p->getRight()));  
            return RotateLeft(p);   
        }
        return p;  
    }

    virtual Node<K, T>* push_R(Node<K, T>* N, Node<K, T>* Current) override {
        if (N == nullptr) return nullptr;
        
        if (this->root == nullptr) {
            this->root = N;
            return N;
        }

        if (N->getKey() < Current->getKey()) {
            if (Current->getLeft() != nullptr) {
                return push_R(N, Current->getLeft());
            } else {
                Current->setLeft(N);
                N->setParent(Current);
            }
        } else if (N->getKey() > Current->getKey()) {
            if (Current->getRight() != nullptr) {
                return push_R(N, Current->getRight());
            } else {
                Current->setRight(N);
                N->setParent(Current);
            }
        } else {
            return Current;
        }

        return Balance(Current);
    }

public:
    virtual Node<K, T>* push(K k, T n) override {
        Node<K, T>* N = new Node<K, T>(k, n);
        return push_R(N, this->root);
    }

    void Remove(const K& k) {
        typename IteratedTree<K, T>::iterator it = find(k);
        Node<K, T>* nodeToRemove = &(*it);
        if (nodeToRemove != nullptr) {
            Tree<K, T>::Remove(nodeToRemove); 
            this->root = Balance(this->root); 
        }
    }
    void Remove(const T& v) {
        typename IteratedTree<K, T>::iterator it = find(v);
        Node<K, T>* nodeToRemove = &(*it);
        if (nodeToRemove != nullptr) {
            Tree<K, T>::Remove(nodeToRemove); 
            this->root = Balance(this->root); 
        }
    }

    Node<K, T>* findKey(const K& k, Node<K, T>* Current, bool (*compareFunc)(const K&, const K&)) {
        if (Current == nullptr) {
            return nullptr; 
        }
        if (compareFunc(k, Current->getKey())) {
            return Current; 
        }
        if (k < Current->getKey()) {
            return findKey(k, Current->getLeft(), compareFunc); 
        } else {
            return findKey(k, Current->getRight(), compareFunc); 
        }
    }

    Node<K, T>* findValue(const T& value, Node<K, T>* Current, bool (*compareFunc)(const T&, const T&)) {
        if (Current == nullptr) {
            return nullptr;
        }
        if (compareFunc(value, Current->getValue())) {
            return Current; 
        }
        Node<K, T>* foundNode = findValue(value, Current->getLeft(), compareFunc);
        if (foundNode) {
            return foundNode;
        }
        return findValue(value, Current->getRight(), compareFunc); 
    }

    typename IteratedTree<K, T>::iterator find(const K& k) {
        Node<K, T>* foundNode = findKey(k, this->root, [](const K& a, const K& b) { return a == b; });
        
        if (foundNode != nullptr) {
            return typename IteratedTree<K, T>::iterator(foundNode);  
        }
        return typename IteratedTree<K, T>::iterator(nullptr);  
    }

    typename IteratedTree<K, T>::iterator find(const T& value) {
        Node<K, T>* foundNode = findValue(value, this->root, [](const T& a, const T& b) { return a == b; });
        if (foundNode != nullptr) {
            return typename IteratedTree<K, T>::iterator(foundNode);  
        }
        return typename IteratedTree<K, T>::iterator(nullptr); 
    }
    T operator[](K key){
        typename IteratedTree<K, T>::iterator it = find(key);
        return (*it).getValue();
    }
};

template<class K, class T>
class MultiKeyAVLTree : public AVL_Tree<K, T> {
private:
    virtual Node<K, T>* push_R(Node<K, T>* N, Node<K, T>* Current) override {
        if (N == nullptr) return nullptr;
        
        if (this->root == nullptr) {
            this->root = N;
            return N;
        }

        if (N->getKey() < Current->getKey()) {
            if (Current->getLeft() != nullptr) {
                return push_R(N, Current->getLeft());
            } else {
                Current->setLeft(N);
                N->setParent(Current);
            }
        } else if (N->getKey() >= Current->getKey()) {
            if (Current->getRight() != nullptr) {
                return push_R(N, Current->getRight());
            } else {
                Current->setRight(N);
                N->setParent(Current);
            }
        } else {
            return Current;
        }

        return AVL_Tree<K, T>::Balance(Current);
    }

public:
    virtual Node<K, T>* push(K k, T n) override {
        Node<K, T>* N = new Node<K, T>(k, n);
        return push_R(N, this->root);
    }
    list<T> operator[](K key) {
        list<T> result;
        typename IteratedTree<K, T>::iterator it = AVL_Tree<K, T>::find(key);
        
        // Начнем с текущего узла
        while (it != AVL_Tree<K, T>::end() && (*it).getKey() == key) {
            result.push_back((*it).getValue());
            ++it;  
        }
        return result;
    }
    
};


template<class K, class T>
class SplayTree : public AVL_Tree<K, T> { 
protected:
    void splay(Node<K, T>* node) {
        while (node->getParent() != nullptr) {
            Node<K, T>* parent = node->getParent();
            Node<K, T>* grandparent = parent->getParent();
            if (grandparent == nullptr) {
                if (node == parent->getLeft()) {
                    this->RotateRight(parent);
                } else {
                    this->RotateLeft(parent);
                }
            } else if (node == parent->getLeft() && parent == grandparent->getLeft()) {
                this->RotateRight(grandparent);
                this->RotateRight(parent);
            } else if (node == parent->getRight() && parent == grandparent->getRight()) {
                this->RotateLeft(grandparent);
                this->RotateLeft(parent);
            } else if (node == parent->getLeft() && parent == grandparent->getRight()) {
                this->RotateRight(parent);
                this->RotateLeft(grandparent);
            } else {
                this->RotateLeft(parent);
                this->RotateRight(grandparent);
            }
        }
    }
    typename IteratedTree<K, T>::iterator splay_push_R(Node<K, T>* N, Node<K, T>* Current)  {
        Node<K, T>* insertedNode = AVL_Tree<K, T>::push_R(N, Current); 
        if (insertedNode) {
            splay(insertedNode);
            return typename IteratedTree<K, T>::iterator(insertedNode); 
        }
        return this->end(); 
    }
public:
    typename IteratedTree<K, T>::iterator push_splay(const K& key, const T& value) {
        Node<K, T>* newNode = new Node<K, T>(key, value); 
        typename IteratedTree<K, T>::iterator it = splay_push_R(newNode, this->root);
        return it; 
    }

    T operator[](K key) {
        typename IteratedTree<K, T>::iterator it = this->find(key);
        if (it != this->end()) {
            Node<K, T>* node = &(*it);
            splay(node);
            return node->getValue();
        }
        throw out_of_range("Key not found in the tree.");
    }

    typename IteratedTree<K, T>::iterator find(const K& key, bool (*compareFunc)(const K&, const K&) = nullptr) {
        if (compareFunc == nullptr) {
            compareFunc = [](const K& a, const K& b) { return a == b; }; 
        }
        Node<K, T>* current = this->root;
        while (current != nullptr) {
            if (compareFunc(key, current->getKey())) {
                splay(current);
                return typename IteratedTree<K, T>::iterator(current);
            }
            if (key < current->getKey()) {
                current = current->getLeft();
            } else {
                current = current->getRight();
            }
        }
        return this->end();
    }
};




template<class T>
void print(const list<T> &lst){
    typename list<T>::const_iterator it = lst.begin();
    while (it != lst.end()){
        cout << *it++ << " ";
    }
    cout << endl << endl;
}


int main(){

    Patient<Name> p1("Nikolaev", "Pavel", 16, 5, 2003, "89112345678", "Chelyabinsk, Sverdlovsk", 1234567801, 4, '+');
    Patient<Name> p2("Sidorova", "Natalia", 22, 9, 1993, "89123456789", "Vladivostok, Admiral", 1234567802, 1, '-');
    Patient<Name> p3("Zaytsev", "Andrey", 10, 12, 1977, "89134567890", "Perm, Komsolskaya", 1234567803, 4, '+');
    Patient<Name> p4("Kozlova", "Lyudmila", 8, 11, 1989, "89145678901", "Tyumen, Turgenev", 1234567804, 2, '+');
    Patient<Name> p5("Vorobiev", "Oleg", 27, 2, 1982, "89156789012", "Khabarovsk, Muravyov", 1234567805, 3, '-');
    Patient<Name> p6("Kovaleva", "Svetlana", 14, 7, 2006, "89167890123", "Krasnodar, Kubanskaya", 1234567806, 1, '+');
    Patient<Name> p7("Lebedev", "Roman", 11, 1, 1991, "89178901234", "Sochi, Lenin", 1234567807, 4, '-');
    Patient<Name> p8("Ivanov", "Sergey", 30, 4, 1985, "89189012345", "Moscow, Tverskaya", 1234567808, 3, '+');

    Patient<Name> p9("Lebedev", "Roman", 29, 2, 1992, "89178901111", "Moscow, MIREA", 1234567809,1 , '-');
    Patient<Name> p10("Kozlova", "Lyudmila", 13, 3, 1975, "89189015555", "Kursk, Karl Marks", 1234567810, 2, '+');
    //___________________________________________________________________________________________________
    // 2.3
    AVL_Tree<string, Patient<Name>> patientTree1;
    patientTree1.push("Nikolaev Pavel", p1);
    patientTree1.push("Sidorova Natalia", p2);
    patientTree1.push("Zaytsev Andrey", p3);
    patientTree1.push("Kozlova Lyudmila", p4);
    patientTree1.push("Vorobiev Oleg", p5);
    patientTree1.push("Kovaleva Svetlana",p6);
    patientTree1.push("Lebedev Roman", p7);
    patientTree1.push("Ivanov Sergey", p8);

    cout << patientTree1;

    patientTree1.Remove(p4);
    Patient<Name> foudedPatient = patientTree1["Kovaleva Svetlana"];

    cout << endl << "The patient escaped, but he was found:" << endl;
    cout <<foudedPatient;

    //___________________________________________________________________________________________________
    // 2.4

    MultiKeyAVLTree<string, Patient<Name>> patientTree2;
    patientTree2.push("Nikolaev Pavel", p1);
    patientTree2.push("Sidorova Natalia", p2);
    patientTree2.push("Zaytsev Andrey", p3);
    patientTree2.push("Kozlova Lyudmila", p4);
    patientTree2.push("Vorobiev Oleg", p5);
    patientTree2.push("Kovaleva Svetlana",p6);
    patientTree2.push("Lebedev Roman", p7);
    patientTree2.push("Ivanov Sergey", p8);
    patientTree2.push("Lebedev Roman", p9);
    patientTree2.push("Kozlova Lyudmila", p10);

    cout << endl << endl << "------MultiKeyAVLTree:" << endl << patientTree2 << endl;

    cout << endl << "The patients tried to escape, but they were caught.\nTheir names: 'Lebedev Roman'" << endl;
    list<Patient<Name>> patients_list = patientTree2["Lebedev Roman"];
    cout << endl;  print(patients_list);
    //___________________________________________________________________________________________________
    // 2.5

    SplayTree<string, Patient<Name>> patientTree3;
    patientTree3.push_splay("Nikolaev Pavel", p1);
    patientTree3.push_splay("Sidorova Natalia", p2);
    patientTree3.push_splay("Zaytsev Andrey", p3);
    patientTree3.push_splay("Kozlova Lyudmila", p4);
    patientTree3.push_splay("Vorobiev Oleg", p5);
    patientTree3.push_splay("Kovaleva Svetlana",p6);
    patientTree3.push_splay("Lebedev Roman", p7);
    patientTree3.push_splay("Ivanov Sergey", p8);

    cout << endl << endl << "------SplayTree:" << endl << patientTree3;

    Patient<Name> foudedPatient2 = patientTree3["Vorobiev Oleg"];
    cout << endl << "The patient escaped, but he was found:" << endl;
    cout <<foudedPatient2;


    return 0; 
}

