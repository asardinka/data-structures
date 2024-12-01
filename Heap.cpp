#include <queue>
#include <list>
#include <iostream>
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

    template <class V>
    void change(V v) {
        Priority::change(*this, v);  
    }
    bool operator<(const Patient& other) const {
        return Priority::compare(*this, other);
    }
    bool operator>(const Patient& other) const {return other < *this;}
    bool operator==(const Patient& other) const {return !(other < *this) && !(*this < other);}

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
    static void change(Patient<PriorityCardNumber>& p, int card){
    	p.set_card(card);
    }
};
struct PriorityBloodGroup {
    static bool compare(const Patient<PriorityBloodGroup>& p1, const Patient<PriorityBloodGroup>& p2) {
        return p1.get_blood() < p2.get_blood();
    }
    static void change(Patient<PriorityBloodGroup>& p, int blood){
    	p.set_blood(blood);
    }
};
struct PriorityName {
    static bool compare(const Patient<PriorityName>& p1, const Patient<PriorityName>& p2) {
        if (p1.get_lastname() == p2.get_lastname()) {
            return p1.get_firstname() < p2.get_firstname();
        }
        return p1.get_firstname() < p2.get_firstname();
    }
    static void change(Patient<PriorityName>& p, string firstName, string lastName){
    	p.set_firstname(firstName);
    	p.set_lastname(lastName);
    }
 
};
template<typename T>
void print_queue(T& q) {
	while (!q.empty()) {
	cout << q.top() << " ";
	q.pop();
	}
	cout << '\n';
}


template <class T>
class Node{
private:
	T value;
public:
	T getValue() { return value; }
	void setValue(T v) { value = v; }

	int operator<(Node N)
	{
		return (value < N.getValue());
	}

	int operator>(Node N)
	{
		return (value > N.getValue());
	}

	void print()
	{
		cout << value;
	}
};

template <class T>
void print(Node<T>* N)
{
	cout << N->getValue() << "\n";
}

template <class T>
class Heap
{
private:
	T* arr;
	int len;
	int size;
protected:
	void SiftUp(int index = -1)
	{
		if (index == -1) index = len - 1;
		int parent_index = GetParentIndex(index);
		if(parent_index < 0) return;
		if(arr[parent_index] < arr[index]){
			Swap(parent_index, index);
			SiftUp(parent_index);
		}
	}
	void Heapify(int index = 0)
	{
		int leftChild;
		int rightChild;
		int largestChild;
		leftChild = (index << 1)  + 1;
		rightChild = (index << 1) + 2;
		if(leftChild >= len) return;
		if (rightChild >= len){
			if (arr[index] < arr[leftChild])
				Swap(index, leftChild);
			return;
		}
		int max_index = arr[leftChild] > arr[rightChild] ? leftChild : rightChild;
		if(arr[max_index] > arr[index]){
			Swap(index, max_index);
			Heapify(max_index);
		}
		
	}
public:
	int getCapacity() { return size; }
	int getCount() { return len; }

	T& operator[](int index)
	{
      	if (index < 0 || index >= len) {
            throw out_of_range("Index out of bounds");
        }
		return arr[index];
	}
	Heap<T>(int MemorySize = 100)
	{
		arr = new T[MemorySize];
		len = 0;
		size = MemorySize;
	}
	~Heap()
    {
        delete[] arr;
    }
	void Swap(int index1, int index2)
	{
        if (index1 < 0 || index1 >= len || index2 < 0 || index2 >= len) {
            throw invalid_argument("Invalid index for Swap");
        }
		T temp;
		temp = arr[index1];
		arr[index1] = arr[index2];
		arr[index2] = temp;
	}
	int GetLeftChildIndex(int index)
	{
        if (index < 0 || index * 2 + 1 >= len) {
            throw out_of_range("No left child exists");
        }
		return (index << 1) + 1;
	}

	int GetRightChildIndex(int index)
	{
        if (index < 0 || index * 2 + 2 >= len) {
            throw out_of_range("No right child exists");
        }

		return (index << 1) + 2;
	}

	int GetParentIndex(int index)
	{
        if (index <= 0 || index >= len) {
            return -1;
        }

		if (index % 2 == 0)
			return (index >> 1) - 1;
		return index >> 1;
	}

	void push(T v)
	{	
		if (len == size) {  
            size *= 2; 
            T* newArr = new T[size];
            for (int i = 0; i < len; ++i) {
                newArr[i] = arr[i];
            }
            delete[] arr;
            arr = newArr;
        }
        arr[len] = v;
        len++;
        SiftUp();
	}
	void remove(int index) {
	    if (index < 0 || index >= len) {
	        throw out_of_range("Index out of bounds");
	    }
	    Swap(index, len - 1);
	    len--;  
	    if (index > 0 && arr[index] > arr[GetParentIndex(index)]) {
	        SiftUp(index); 
	    } else {
	        Heapify(index);
	    }
	}
	template <class V>
	void ChangePriority(int index, V newValue) {
	    if (index < 0 || index >= len) {
	        throw out_of_range("Index out of bounds");
	    }
	    T& value = arr[index];

	    value.change(newValue);

	    if (arr[index] > value) {
	        SiftUp(index);
	    } else {  
	        Heapify(index);
	    }
	}
	T ExtractMax()
	{
        if (len == 0) {
            throw underflow_error("Heap is empty");
        }
        T res = arr[0];
        Swap(0, len - 1);
        len--;
        Heapify();
        return res;
	}
};


// ---------------------------------------------------------------------------------------------------------------------
template <class V> class FibonacciHeap;

template <class V>
struct FNode {
private:
    list<FNode<V>*> children; 
    FNode<V>* parent;
    V priority;
    int degree;
    bool marked;

public:
    friend class FibonacciHeap<V>;

    list<FNode<V>*> getChildren() { return children; }
    FNode<V>* getParent() { return parent; }
    V getPriority() { return priority; }
    bool isMarked() { return marked; }

    bool hasChildren() { return !children.empty(); }
    bool hasParent() { return parent != nullptr; }
};

template <class V>
class FibonacciHeap {
protected:
    FNode<V>* heap;

public:
    FibonacciHeap() {
        heap = _empty();
    }
    virtual ~FibonacciHeap() {
        if (heap) {
            _deleteAll(heap);
        }
    }
    FNode<V>* push(V priority) {
        FNode<V>* ret = _singleton(priority);
        heap = _merge(heap, ret);
        return ret;
    }
    void merge(FibonacciHeap& other) {
        if (other.heap == nullptr) return;
        if (heap == nullptr) {
            heap = other.heap;
            other.heap = nullptr; 
            return;
        }
        heap = _merge(heap, other.heap);
        other.heap = nullptr; 
    }
    bool isEmpty() {
        return heap == nullptr;
    }
    V getMaximum() {
        if (!heap) throw runtime_error("Heap is empty");
        return heap->priority;
    }

    V removeMaximum() {
        if (isEmpty()) throw runtime_error("Heap is empty");
        
        FNode<V>* old = heap;
        heap = _removeMaximum(heap);
        V ret = old->priority;
        delete old;
        return ret;
    }
    V ExtractMax(){
    	return removeMaximum();
    }
private:
    FNode<V>* _empty() {
        return nullptr;
    }
    FNode<V>* _singleton(V priority) {
        FNode<V>* n = new FNode<V>;
        n->priority = priority;
        n->degree = 0;
        n->marked = false;
        n->parent = nullptr;
        return n;
    }
    FNode<V>* _merge(FNode<V>* a, FNode<V>* b) {
        if (a == nullptr) return b;
        if (b == nullptr) return a;

        if (a->priority < b->priority) {
            swap(a, b);
        }

        a->children.push_back(b);
        return a;
    }
    void _deleteAll(FNode<V>* n) {
        if (n != nullptr) {
            for (auto child : n->children) {
                _deleteAll(child);
            }
            delete n;
        }
    }
    void _addChild(FNode<V>* parent, FNode<V>* child) {
        child->parent = parent;
        parent->degree++;
        parent->children.push_back(child);
    }
    void _unMarkAndUnParentAll(FNode<V>* n) {
        if (n == nullptr) return;
        
        for (auto child : n->children) {
            child->marked = false;
            child->parent = nullptr;
        }
    }
    FNode<V>* _removeMaximum(FNode<V>* n) {
        _unMarkAndUnParentAll(n);
        
        FNode<V>* maxChild = nullptr;
        if (!n->children.empty()) {
            for (auto child : n->children) {
                child->parent = nullptr;
                maxChild = _merge(maxChild, child);
            }
        }

        FNode<V>* max = maxChild;
        return max;
    }
};


int main() {
	
	Patient<PriorityCardNumber> p1("Nikolaev", "Pavel", 16, 5, 2003, "89112345678", "Chelyabinsk, Sverdlovsk", 1234567801, 3, '+');
    Patient<PriorityCardNumber> p2("Sidorova", "Natalia", 22, 9, 1993, "89123456789", "Vladivostok, Admiral", 1234567802, 1, '-');
    Patient<PriorityCardNumber> p3("Zaytsev", "Andrey", 10, 12, 1977, "89134567890", "Perm, Komsolskaya", 1234567803, 4, '+');
    Patient<PriorityCardNumber> p4("Kozlova", "Lyudmila", 8, 11, 1989, "89145678901", "Tyumen, Turgenev", 1234567804, 2, '+');
    Patient<PriorityCardNumber> p5("Vorobiev", "Oleg", 27, 2, 1982, "89156789012", "Khabarovsk, Muravyov", 1234567805, 3, '-');
    Patient<PriorityCardNumber> p6("Kovaleva", "Svetlana", 14, 7, 2006, "89167890123", "Krasnodar, Kubanskaya", 1234567806, 1, '+');
    Patient<PriorityCardNumber> p7("Lebedev", "Roman", 11, 1, 1991, "89178901234", "Sochi, Lenin", 1234567807, 2, '-');
    Patient<PriorityCardNumber> p8("Ivanov", "Sergey", 30, 4, 1985, "89189012345", "Moscow, Tverskaya", 1234567808, 3, '+');
    //-----------------------------------------------------------------------------------------------
	// 3.1
	cout << "3.1"<<endl;
	priority_queue<Patient<PriorityCardNumber>> q;
	for (Patient<PriorityCardNumber> n : {p1,p2,p3,p4,p5,p6,p7,p8})
		q.push(n);
	print_queue(q);
	//-----------------------------------------------------------------------------------------------
	// 3.2
	cout <<endl<<endl<<endl<< "3.2"<<endl;
	Heap<Patient<PriorityCardNumber>> H;
	H.push(p1);H.push(p2);H.push(p3);H.push(p4);H.push(p5);H.push(p6);H.push(p7);H.push(p8);

    H.ChangePriority(3,1111111111);

	int i = 0;
	while (i < H.getCount())
	{
		Patient<PriorityCardNumber> p = H.ExtractMax();
		cout << p << endl;
	}

	//-----------------------------------------------------------------------------------------------
	// 3.3
	cout <<endl<<endl<<endl<< "3.3"<<endl;
	FibonacciHeap<Patient<PriorityCardNumber>> tree1;
    tree1.push(p1);
    tree1.push(p2);
    tree1.push(p3);
    tree1.push(p4);

    FibonacciHeap<Patient<PriorityCardNumber>> tree2;
    tree2.push(p5);
    tree2.push(p6);
    tree2.push(p7);
    tree2.push(p8);
    tree1.merge(tree2);

    while (!tree1.isEmpty()) {
        cout << tree1.ExtractMax() << endl;
    }
	


	return 0;
}