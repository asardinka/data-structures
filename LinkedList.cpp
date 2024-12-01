#include <iostream>
#include <fstream>
#include <list>
using namespace std;

template <class Priority>
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
        return Priority::compare(*this, other);
    }
    bool operator>(const Patient& other) const {return other < *this;}
    bool operator==(const Patient& other) const {return !(other < *this) && !(*this < other);}
    bool operator!=(const Patient& other) const {return (other < *this) || (*this < other);}
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
struct PriorityCardNumber {
    static bool compare(const Patient<PriorityCardNumber>& p1, const Patient<PriorityCardNumber>& p2) {
        return p1.get_card() < p2.get_card();
    }
};
struct PriorityBloodGroup {
    static bool compare(const Patient<PriorityBloodGroup>& p1, const Patient<PriorityBloodGroup>& p2) {
        return p1.get_blood() < p2.get_blood();
    }
};
struct PriorityName {
    static bool compare(const Patient<PriorityName>& p1, const Patient<PriorityName>& p2) {
        if (p1.get_lastname() == p2.get_lastname()) {
            return p1.get_firstname() < p2.get_firstname();
        }
        return p1.get_firstname() < p2.get_firstname();
    }
};
//----------------------------------------------------
//----------------------------------------------------
//----------------------------------------------------

template <class T>
class Element
{
    //элемент связного списка
private:
    //указатель на предыдущий и следующий элемент
    Element* next;
    Element* prev;

    //информация, хранимая в поле
    T field;
public:
    //доступ к полю *next
    virtual Element* getNext() { return next; }
    virtual void setNext(Element* value) { next = value; }

    //доступ к полю *prev
    virtual Element* getPrevious() { return prev; }
    virtual void setPrevious(Element* value) { prev = value; }

    //доступ к полю с хранимой информацией field
    virtual T getValue() { return field; }
    virtual void setValue(T value) { field = value; }

    template<class T1> friend ostream& operator<< (ostream& ustream, Element<T1>& obj);

    Element(T value) {field = value; next = prev = NULL;}
};

template<class T>
ostream& operator << (ostream& ustream, Element<T>& obj)
{
    ustream << obj.field;
    return ustream;
}

template <class T>
class LinkedListParent
{
protected:
    //достаточно хранить начало и конец
    Element<T>* head;
    Element<T>* tail;
    //для удобства храним количество элементов
    int num;
public:
    virtual int Number() { return num; }

    virtual Element<T>* getBegin() { return head; }

    virtual Element<T>* getEnd() { return tail; }

    LinkedListParent()
    {
        //конструктор без параметров
        cout << "\nParent constructor";
        head = NULL; tail = NULL;
        num = 0;
    }

    //чисто виртуальная функция: пока не определимся с типом списка, не сможем реализовать добавление
    virtual Element<T>* push(T value) = 0;

    //чисто виртуальная функция: пока не определимся с типом списка, не сможем реализовать удаление
    virtual Element<T>* pop() = 0;

    virtual ~LinkedListParent()
    {
        //деструктор - освобождение памяти
        cout << "\nParent destructor";
    }

    //получение элемента по индексу - какова асимптотическая оценка этого действия? 
    // ОТВЕТ: O(n) где n — это номер элемента, к которому хотим получить доступ.
    virtual Element<T>* operator[](int i)
    {
        //индексация
        if (i<0 || i>num) return NULL;
        int k = 0;

        //ищем i-й элемент - вставем в начало и отсчитываем i шагов вперед
        Element<T>* cur = head;
        for (k = 0; k < i; k++)
        {
            cur = cur->getNext();
        }
        return cur;
    }

    template<class T1> friend ostream& operator<< (ostream& ustream, LinkedListParent<T1>& obj);
    template<class T1> friend istream& operator>> (istream& ustream, LinkedListParent<T1>& obj);
};

template<class T>
ostream& operator << (ostream& ustream, LinkedListParent<T>& obj)
{
    if (typeid(ustream).name() == typeid(ofstream).name())
    {
        ustream << obj.num << "\n";
        for (Element<T>* current = obj.getBegin(); current != NULL; current = current->getNext())
            ustream << current->getValue() << " ";
        return ustream;
    }

    ustream << "\nLength: " << obj.num << "\n";
    int i = 0;
    for (Element<T>* current = obj.getBegin(); current != NULL; current = current->getNext(), i++)
        ustream << "arr[" << i << "] = " << current->getValue() << "\n";

    return ustream;
}

template<class T>
istream& operator >> (istream& ustream, LinkedListParent<T>& obj)
{
    int len;
    ustream >> len;
    double v = 0;
    for (int i = 0; i < len; i++)
    {
        ustream >> v;
        obj.push(v);
    }
    return ustream;
}

template <class T>
class IteratedLinkedList : public LinkedListParent<T>
{
public:
    IteratedLinkedList() : LinkedListParent<T>() { cout << "\nIteratedLinkedList constructor"; }
    virtual ~IteratedLinkedList() {
        Element<T>* current = LinkedListParent<T>::head;
        while (current != nullptr) {
            Element<T>* next = current->getNext();
            delete current; 
            current = next; 
        }
        cout << "\nIteratedLinkedList destructor";
    }
    class iterator 
    {
    private:
        Element<T>* ptr;
    public:
        
        iterator() { ptr = NULL; }
        iterator(Element<T>* p) { ptr = p; }
        iterator(const iterator& it) { ptr = it.ptr; }
        iterator& operator=(const iterator& it) { ptr = it.ptr; return *this; }
        iterator& operator=(Element<T>* p) { ptr = p; return *this; }

        bool operator!=(iterator const& other) const { return ptr != other.ptr;}
        bool operator==(iterator const& other) const { return ptr == other.ptr;}

        Element<T>& operator*()
        {
            return *ptr;
        }

        iterator& operator++() {
            if (ptr == nullptr) throw out_of_range("iterator out of range"); 
            ptr = ptr->getNext();
            return *this;
        }
        iterator operator++(int v) {
            iterator it = ptr;
            if (ptr == nullptr) throw std::out_of_range("iterator out of range");
            ptr = ptr->getNext();
            return it;
        }
        iterator& operator--() {
            if (ptr == nullptr) throw out_of_range("iterator out of range"); 
            ptr = ptr->getPrevious();
            return *this;
        }
        iterator operator--(int v) {
            iterator it = ptr;
            if (ptr == nullptr) throw std::out_of_range("iterator out of range");
            ptr = ptr->getPrevious();
            return it;
        }
    };

    iterator begin() {return iterator(this->head);}
    iterator end() {return iterator(this->tail); }

};

template <class T>
class Stack: public IteratedLinkedList<T>{
public:
    Stack() : IteratedLinkedList<T>() { cout << "\nStack constuctor"; }

    virtual Element<T>* push(T value){
        // Пустой список
        if(LinkedListParent<T>::head != NULL){
            Element<T>* newElem = new Element<T>(value);
            LinkedListParent<T>::tail -> setNext(newElem);
            newElem->setPrevious(LinkedListParent<T>::tail);
            LinkedListParent<T>::tail = newElem;
        } else {
            LinkedListParent<T>::head = new Element<T>(value);
            LinkedListParent<T>::tail = LinkedListParent<T>::head;
        }
        LinkedListParent<T>::num++;
        return LinkedListParent<T>::tail;
    }

    virtual Element<T>* pop(){
        if (LinkedListParent<T>::head == nullptr) throw std::underflow_error("Stack is empty");

        Element<T>* result = LinkedListParent<T>::tail;

        if (LinkedListParent<T>::head == LinkedListParent<T>::tail){
            LinkedListParent<T>::head = LinkedListParent<T>::tail = NULL;
            LinkedListParent<T>::num--;
            result->setPrevious(NULL);
        }

        LinkedListParent<T>::tail = LinkedListParent<T>::tail->getPrevious();
        LinkedListParent<T>::tail->setNext(NULL);
        result->setPrevious(NULL);
        LinkedListParent<T>::num--;

        return result;
    }

    virtual Element<T>* insert(T value, Element<T>* current = NULL){
        if(current==NULL || LinkedListParent<T>::head == NULL) return push(value);

        Element<T>* newElem = new Element<T>(value);
        newElem->setNext(current->getNext());
        if(current->getNext() != NULL) current->getNext()->setPrevious(newElem);
        current->setNext(newElem);
        newElem->setPrevious(current);
        LinkedListParent<T>::num++;

        if (current == LinkedListParent<T>::tail) LinkedListParent<T>::tail = newElem;

        return newElem;
    }

};
template <class T>
class Queue : public IteratedLinkedList<T>{
public:
    Queue() : IteratedLinkedList<T>() { cout << "\nQueue constructor"; }

    virtual Element<T>* push(T value) {
        Element<T>* newElem = new Element<T>(value);
        if (LinkedListParent<T>::head != nullptr) {
            LinkedListParent<T>::tail->setNext(newElem);
            newElem->setPrevious(LinkedListParent<T>::tail);
            LinkedListParent<T>::tail = newElem;
        }
        else {
            LinkedListParent<T>::head = LinkedListParent<T>::tail = newElem;
        }
        LinkedListParent<T>::num++;
        return LinkedListParent<T>::tail;
    }

    virtual Element<T>* pop() {
        if (LinkedListParent<T>::head == nullptr) throw std::underflow_error("Queue is empty");

        Element<T>* result = LinkedListParent<T>::head;
        LinkedListParent<T>::head = LinkedListParent<T>::head->getNext();
        if (LinkedListParent<T>::head != nullptr) {
            LinkedListParent<T>::head->setPrevious(nullptr);
        } else {
            LinkedListParent<T>::tail = nullptr; 
        }
        LinkedListParent<T>::num--;
        return result;
    }

    virtual Element<T>* insert(T value, Element<T>* current = nullptr) {
        Element<T>* newElem = new Element<T>(value);
        if (LinkedListParent<T>::head == nullptr) {
            LinkedListParent<T>::head = newElem;
            LinkedListParent<T>::tail = newElem;
            LinkedListParent<T>::num++;
            return newElem;
        }
        if (current == nullptr && value < LinkedListParent<T>::head->getValue()) {
            newElem->setNext(LinkedListParent<T>::head);
            LinkedListParent<T>::head->setPrevious(newElem);
            LinkedListParent<T>::head = newElem;
            LinkedListParent<T>::num++;
            return newElem;
        }
        Element<T>* it = LinkedListParent<T>::head;
        while (it != nullptr && it->getValue() < value) {
            it = it->getNext();
        }
        if (it != nullptr) { 
            newElem->setNext(it);
            newElem->setPrevious(it->getPrevious());
            if (it->getPrevious() != nullptr) {
                it->getPrevious()->setNext(newElem);
            } else {
                LinkedListParent<T>::head = newElem; 
            }
            it->setPrevious(newElem);
        } else { 
            LinkedListParent<T>::tail->setNext(newElem);
            newElem->setPrevious(LinkedListParent<T>::tail);
            LinkedListParent<T>::tail = newElem;
        }

        LinkedListParent<T>::num++;
        return newElem;
    }

};

template <typename T>
class OrderedQueue : protected Queue<T> {
public:
    typename Queue<T>::iterator pushOQ(T value) {
        typename Queue<T>::iterator it = Queue<T>::begin();
        while (it != Queue<T>::end() && value > (*it).getValue()) ++it;
        Element<T>* newElem = new Element<T>(value);
        this->insert(value, &(*it));
        return it; 
    }

    Element<T>* pop() {
        typename Queue<T>::iterator it = Queue<T>::begin();
        if (it == Queue<T>::end()) return nullptr; 
        Element<T>* elem = &(*it);
        this->head = elem->getNext();
        this->num--;
        return elem;
    }

    void remove(T value) {
        typename Queue<T>::iterator it = Queue<T>::begin();
        if (it == Queue<T>::end()) return; 

        while((*it).getValue() != value  && it != Queue<T>::end()) ++it;

        if (it != Queue<T>::end()) {
            Element<T>* elem = &(*it); 

            if (elem == this->head) {
                this->pop(); 
            } else {
                Element<T>* prevElem = elem->getPrevious();
                Element<T>* nextElem = elem->getNext();
                if (prevElem != nullptr) {
                    prevElem->setNext(nextElem);
                }
                if (nextElem != nullptr) {
                    nextElem->setPrevious(prevElem);
                }
                delete elem; 
                this->num--; 
            }
        }
    }
    friend std::ostream& operator<<(std::ostream& os, OrderedQueue<T>& pq) {
        typename OrderedQueue<T>::iterator it = pq.begin(); 
        while (it != pq.end()) {
            os << *it << " "; 
            it++; 
        }
        cout << *pq.end();
        return os;
    }

};

bool isConsonant(char c){
    list<char> consonants = {'q','w','r','t','p','s','d','f','g','h','j','k','l','z','x','c','v','b','n','m'};
    for (list<char>::iterator it = consonants.begin(); it != consonants.end(); it++)
        if (*it == c)
            return true;
    return false;
} 
template <typename T>
Queue<T> filter(Queue<T> q, bool (*func)(T)) {
    Queue<T> result;
    for (typename  Queue<T>::iterator it = q.begin(); it != q.end(); ++it) {
        if (func(((*it).getValue()))) {
            result.push((*it).getValue());
        }
    }
    return result;
}

int main()
{
    try {
        cout << "STACK" << endl;
        Stack<int> S;
        S.push(1);
        S.push(2);
        S.push(3);
        cout << S;
        cout << "\n";
        Element<int>* e1 = S.pop();
        cout << "\nPOP Element = " << e1->getValue();
        cout << S;
        cout<<"\nIndex in the Stack class: " << S[1]->getValue();

        cout << S;
        cout << "\nIterators:\n";
        Stack<int>::iterator it = S.begin();
        while (it != S.end())
        {
            cout << *it << " ";
            it++;
        }
        cout << *it << " " << endl;
        
        //-------------------------------------------//
        cout << endl << "QUEUE" << endl;
        Queue<char> Q;
        Q.push('a');Q.push('b');Q.push('d');
        Q.push('e');Q.push('f');Q.push('g');
        cout << Q;

        Element<char>* e2 = Q.pop();
        cout << endl << "POP Element: " << e2->getValue() << endl;
        cout << Q <<  endl;

        Q.insert('c',Q[0]);
        cout << endl<< "INSERT c:"<< endl << Q;

        cout << "Iterators:" << endl;
        Queue<char>::iterator iter = Q.begin();
        while (iter != Q.end())
        {
            cout << *iter << " ";
            iter++;
        }
        cout << *iter << " " << endl;

        Queue<char> Q1 = filter(Q, &isConsonant);
        cout << endl << endl<< "AFTER FILTER"<< endl << Q1;

        //------------------------------------//
        cout << "PRIORITY QUEUE" << endl;
        OrderedQueue<int> OQint;
        OQint.pushOQ(1);OQint.pushOQ(2);OQint.pushOQ(4);OQint.pushOQ(5);OQint.pushOQ(3);
        cout << "OrderedQueue: " << OQint << endl;
        OQint.remove(3);
        cout <<"OrderedQueue after remove 3: "  << OQint << endl;

        // Приоритет по номеру карты
        Patient<PriorityCardNumber> patient1("Nikolaev", "Pavel", 16, 5, 2003, "89112345678", "Chelyabinsk, Sverdlovsk", 1234567801, 3, '+');
        Patient<PriorityCardNumber> patient2("Sidorova", "Natalia", 22, 9, 1993, "89123456789", "Vladivostok, Admiral", 1234567803, 1, '-');
        Patient<PriorityCardNumber> patient3("Zaytsev", "Andrey", 10, 12, 1977, "89134567890", "Perm, Komsolskaya", 1234567805, 4, '+');
        Patient<PriorityCardNumber> patient4("Kozlova", "Lyudmila", 8, 11, 1989, "89145678901", "Tyumen, Turgenev", 1234567802, 2, '+');
        Patient<PriorityCardNumber> patient5("Vorobiev", "Oleg", 27, 2, 1982, "89156789012", "Khabarovsk, Muravyov", 1234567808, 3, '-');
        Patient<PriorityCardNumber> patient6("Kovaleva", "Svetlana", 14, 7, 2006, "89167890123", "Krasnodar, Kubanskaya", 1234567806, 1, '+');
        Patient<PriorityCardNumber> patient7("Lebedev", "Roman", 11, 1, 1991, "89178901234", "Sochi, Lenin", 1234567804, 2, '-');
        Patient<PriorityCardNumber> patient8("Ivanov", "Sergey", 30, 4, 1985, "89189012345", "Moscow, Tverskaya", 1234567807, 3, '+');

        OrderedQueue<Patient<PriorityCardNumber>> OQ;

 

        OQ.pushOQ(patient1);OQ.pushOQ(patient2);OQ.pushOQ(patient3);OQ.pushOQ(patient4);
        OQ.pushOQ(patient5);OQ.pushOQ(patient6);OQ.pushOQ(patient7);OQ.pushOQ(patient8);

        OQ.remove(patient1);
        cout << endl << "PATIENTS:"<< endl << OQ << endl;

        cout << "POP Element :" << endl;
        Patient<PriorityCardNumber> p = OQ.pop()->getValue();
        cout << p;

    } catch (const std::exception& ex) {
        cerr << "Error: " << ex.what() << endl;
    }

    //char c; cin >> c;
    return 0;
}
