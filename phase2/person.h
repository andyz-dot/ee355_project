
#ifndef PERSON_H
#define PERSON_H

#include "date.h"
#include "contact.h"
#include "fstream"
#include <vector> // Phase 2 Part 2, needed for the myfriends vector 
class Person{
    friend class Network;

private:
	string f_name;
	string l_name;
	Date *birthdate;
    Email *email;
    Phone *phone;
    // the following to attributes are used in the linked list.
    Person* next;
    Person* prev;
    // list of this person's friends stored as pointers so two people can link to each other without copying Person objects
    vector<Person*> myfriends;

public:
    Person();
    ~Person();
    Person(string filename);
    Person(string f_name, string l_name, string b_date, string email, string phone);
	void print_person();
	void set_person();
	void set_person(string filename);
    bool operator==(const Person& rhs);
    bool operator!=(const Person& rhs);
    // adds newFriend to this person's myfriends vector
    void makeFriend(Person* newFriend);
    // prints this person then their friends sorted by code
    void print_friends();
};


#endif