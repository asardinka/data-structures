#include <list>
#include <iostream>
using namespace std;

// Вариант 16

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

class EmptyListException : public exception {
public:
    const char* what()  {
        return "List is empty";
    }
};

template <class T>
void push(list<T> &l, const T value) {
    typename list<T>::const_iterator it = l.begin();
    while (it != l.end() && value > *it) it++;
    l.insert(it, value);
}
template <class T>
T pop(list<T> &l, const T value){
    if (l.empty()) throw EmptyListException();
	l.remove(value);
    return value;
}
template <class T>
T pop(list<T> &l){
    if (l.empty()) throw EmptyListException();
    T ans = l.back();
    l.pop_back();
    return ans;
}
template<class T>
void print(const list<T> &lst){
    typename list<T>::const_iterator it = lst.begin();
    while (it != lst.end()){
        cout << *it++ << " ";
    }
    cout << endl << endl;
}

// Только согласные
bool isConsonant(char c){
    list<char> consonants = {'q','w','r','t','p','s','d','f','g','h','j','k','l','z','x','c','v','b','n','m'};
    for (list<char>::iterator it = consonants.begin(); it != consonants.end(); it++)
        if (*it == c)
        	return true;
    return false;
} 
template<class T>
list<T> filter(const list<T> &lst, bool (*func)(T)){
	list<T> result;
    for (typename list<T>::const_iterator it = lst.begin(); it != lst.end(); it++) {
        if (func(*it)) {
            push(result,*it);
        }
    }
	return result;
}



int main() {
	// 1.1
    try{
    	list<char> letters;
    	for (int i = 0; i < 6; i++){
            letters.push_back('a' + i);
    	}
    	cout << "letters: ";print(letters);

    	cout << "push A, c, x : \n"; 
    	push(letters, 'A');push(letters,'c');push(letters, 'x');
    	cout << "letters: ";print(letters);

    	cout << "pop d : \n"; 
    	pop(letters, 'd');
    	cout << "letters: ";print(letters);

    	cout << "Only consonants : \n"; 
    	list<char> cons_letters = filter(letters, &isConsonant);
    	cout << "cons_letters: ";print(cons_letters);

    	/*---------------------------------------------*/
    	// 1.2

    	Patient<PriorityBloodGroup> patient1("Nikolaev", "Pavel", 16, 5, 2003, "89112345678", "Chelyabinsk, Sverdlovsk", 1234567801, 3, '+');
        Patient<PriorityBloodGroup> patient2("Sidorova", "Natalia", 22, 9, 1993, "89123456789", "Vladivostok, Admiral", 1234567802, 1, '-');
        Patient<PriorityBloodGroup> patient3("Zaytsev", "Andrey", 10, 12, 1977, "89134567890", "Perm, Komsolskaya", 1234567803, 4, '+');
        Patient<PriorityBloodGroup> patient4("Kozlova", "Lyudmila", 8, 11, 1989, "89145678901", "Tyumen, Turgenev", 1234567804, 2, '+');
        Patient<PriorityBloodGroup> patient5("Vorobiev", "Oleg", 27, 2, 1982, "89156789012", "Khabarovsk, Muravyov", 1234567805, 3, '-');
        Patient<PriorityBloodGroup> patient6("Kovaleva", "Svetlana", 14, 7, 2006, "89167890123", "Krasnodar, Kubanskaya", 1234567806, 1, '+');
        Patient<PriorityBloodGroup> patient7("Lebedev", "Roman", 11, 1, 1991, "89178901234", "Sochi, Lenin", 1234567807, 2, '-');
        Patient<PriorityBloodGroup> patient8("Ivanov", "Sergey", 30, 4, 1985, "89189012345", "Moscow, Tverskaya", 1234567808, 3, '+');


    	list<Patient<PriorityBloodGroup>> Patients;
    	push(Patients, patient1);push(Patients, patient2);push(Patients, patient3);push(Patients, patient4);
        push(Patients, patient5);push(Patients, patient6);push(Patients, patient7);push(Patients, patient8);
        cout << "Patients:" << endl; print(Patients);

        Patient<PriorityBloodGroup> p = pop(Patients);
        cout << "pop element:"<< endl << p;

    }
    catch(EmptyListException ex)
    {cout << "exception has been caught "; ex.what();}
    catch(exception ex)
    {cout << "exception has been caught "; ex.what();}
    catch(...)
    {cout <<"Something has been caught ";}







    return 0;
}
