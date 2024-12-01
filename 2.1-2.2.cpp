#include <iostream>
#include <map>
#include <set>
#include <string>
#include <stdexcept> 
using namespace std;

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
    return (lastName < other.lastName);
    }

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
template <typename K, typename V>
void insert(map<K, V>& m, const K& key, const V& value) {
    if (m.find(key) != m.end()) {
        throw invalid_argument("Key already exists in the map.");
    }
    m[key] = value;
}
template <typename K, typename V>
pair<K, V> find(const map<K,V>& m, const K& key){
    typename map<K,V>::const_iterator it = m.find(key);
    if (it == m.end()) {
        throw out_of_range("Key not found in the map.");
    }
    return *it;
}
template <typename K, typename V>
pair<K, V> find(const map<K,V>& m,  const V& value){
    typename map<K,V>::const_iterator it = m.begin();
    while(it->second != value && it != m.end()) it++;
    if (it == m.end()) throw out_of_range("Value not found in the map.");
    return *it;
}

/*
template <typename K, typename V>
map<K,V> filter(const map<K,V>& m, const K& threshold, bool greater = true) {
    typename map<K,V>::const_iterator it = m.find(threshold);
    
    if (it == m.end()) {
        throw out_of_range("Key not found in the map.");
    }

    map<K, V> result;
    //result[it->first] = it->second;
    if (greater) {
        for (typename map<K,V>::const_iterator iter = it; iter != m.end(); ++iter) {
            if (iter->first > threshold) {
                result[iter->first] = iter->second;
            }
        }
    } else {
        for (typename map<K,V>::const_iterator iter = it; iter != m.begin(); --iter) {
            if (iter->first < threshold) {
                result[iter->first] = iter->second;
            }
        }
    }

    return result;
}
*/
template <typename K, typename V>
map<K,V> filter(const map<K,V>& m, const K& threshold, bool greater = true) {
    map<K,V> result;
    typename map<K,V>::const_iterator it = m.lower_bound(threshold);
    while (it != m.end()){
        result[it->first] = it->second;
        ++it;
    }

    return result;
}

template <typename K, typename V>
multimap<K,V> filter(const multimap<K,V>& m, const K& threshold, bool greater = true) {
    typename multimap<K,V>::const_iterator it = m.find(threshold);
    
    if (it == m.end()) {
        throw out_of_range("Key not found in the map.");
    }
    multimap<K, V> result;
    if (greater) {
        for (typename multimap<K,V>::const_iterator iter = it; iter != m.end(); ++iter) {
            if (iter->first > threshold) {
                result.insert(std::make_pair(iter->first, iter->second));  
            }
        }
    } else {
        for (typename multimap<K,V>::const_iterator iter = it; iter != m.begin(); --iter) {
            if (iter->first < threshold) {
                result.insert(std::make_pair(iter->first, iter->second));  
            }
        }
    }
    return result;
}


set<int> unique(const map<int,Patient> &m){
	set<int> result;
	for (typename map<int,Patient>::const_iterator it = m.begin(); it != m.end(); it++)
    	result.insert(it->second.get_blood());
	return result;
}
template <typename K, typename V>
set<V> find_all_on_key(const multimap<K, V>& m, const K& k) {
    set<V> result;
    typename multimap<K,V>::const_iterator it = m.find(k);
    while (it->first == k && it != m.end()) {
        result.insert(it->second);
        it++;
    }
    return result;
}
template <typename K, typename V>
void print(map<K, V> m){
	typename map<K, V>::iterator it = m.begin();
	while (it != m.end()){
		cout << "[" << it->first << "] = " << it->second << endl;
		it++;
	}
	cout << endl;
}
template <typename K, typename V>
void print(pair<K, V> p){
	cout << "[" << p.first << "] = " << p.second << endl << endl;
}
template <typename V>
void print(set<V> s){
	typename set<V>::iterator it = s.begin();
	while (it != s.end()){
		cout << *it << " ";
		it++;
	}
	cout << endl;
}
template <typename K, typename V>
void print(multimap<K, V> m){
	typename multimap<K, V>::iterator it = m.begin();
	while (it != m.end()){
		cout << "[" << it->first << "] = " << it->second << endl;
		it++;
	}
	cout << endl;
}
int main(){
	Patient patient1("Nikolaev", "Pavel", 16, 5, 2003, "89112345678", "Chelyabinsk, Sverdlovsk", 1234567800, 4, '+');
    Patient patient2("Sidorova", "Natalia", 22, 9, 1993, "89123456789", "Vladivostok, Admiral", 1234567801, 1, '-');
    Patient patient3("Zaytsev", "Andrey", 10, 12, 1977, "89134567890", "Perm, Komsolskaya", 1234567802, 4, '+');
    Patient patient4("Kozlova", "Lyudmila", 8, 11, 1989, "89145678901", "Tyumen, Turgenev", 1234567803, 2, '+');
    Patient patient5("Vorobiev", "Oleg", 27, 2, 1982, "89156789012", "Khabarovsk, Muravyov", 1234567804, 3, '-');
    Patient patient6("Kovaleva", "Svetlana", 14, 7, 2006, "89167890123", "Krasnodar, Kubanskaya", 1234567806, 1, '+');
    Patient patient7("Lebedev", "Roman", 11, 1, 1991, "89178901234", "Sochi, Lenin", 1234567807, 4, '-');
    Patient patient8("Ivanov", "Sergey", 30, 4, 1985, "89189012345", "Moscow, Tverskaya", 1234567808, 3, '+');

    try {
    
		map<int, Patient> Patients;
		Patients[1234567800] = patient1;Patients[1234567801] = patient2;
		Patients[1234567802] = patient3;Patients[1234567803] = patient4;
		Patients[1234567804] = patient5;Patients[1234567806] = patient6;
		Patients[1234567807] = patient7;Patients[1234567808] = patient8;
		print(Patients);

		pair<int, Patient> p = find(Patients, 1234567806);
		cout << "Patient with card number 1234567805:" << endl; print(p);

		map<int, Patient> Patients_new;
		Patients_new = filter(Patients, 1234567805);
		cout << "Patients with a card number 1234567806 and greater : " << endl; print(Patients_new);

		set<int> non_first_Patients;
		non_first_Patients = unique(Patients_new);
		cout << "Unique blood groups: "; print(non_first_Patients); cout << endl;

		// Добавляем пациента с уже существующим ключом
		insert(Patients,1234567807, patient1);

	} catch (const out_of_range& ex) {
        cerr << "Error: " << ex.what() << endl;
    } catch (const invalid_argument& ex) {
        cerr << "Error: " << ex.what() << endl;
    }
    
    // ----------------------------------- //
    // 2.2

    multimap<int, Patient> Patients;
	Patients.insert(make_pair(1234567801, patient1));Patients.insert(make_pair(1234567802, patient2));
	Patients.insert(make_pair(1234567802, patient3));Patients.insert(make_pair(1234567804, patient4));
	cout << endl << endl << "№x2.2" << endl;print(Patients);

    multimap<int, Patient> new_patients1;
    new_patients1 = filter(Patients, 1234567801);
    cout << " All patietns with card number greater that 1234567801: " << endl;print(new_patients1);

	set<Patient> new_patients2;
	new_patients2 = find_all_on_key(Patients, 1234567802);

	cout << " All patietns with card number 1234567802:" << endl;print(new_patients2);


	return 0;
}