
#include "person.h"
#include "misc.h" // needed for the codeName helper from Part 3
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

Person::Person()
{
    // I'm already done!
    set_person();
}

Person::~Person()
{
    delete birthdate;
    delete email;
    delete phone;
}

Person::Person(string f_name, string l_name, string b_date, string email, string phone)
{
    // TODO: Complete this method!
    // phone and email strings are in full version
    this->f_name = f_name;
    this->l_name = l_name;
    this->next = NULL;
    this->prev = NULL;

    birthdate = new Date(b_date);

    string email_type = email.substr(1, email.find(')') - 1);
    string email_addr = email.substr(email.find(' ') + 1);
    this->email = new Email(email_type, email_addr);

    string phone_type = phone.substr(1, phone.find(')') - 1);
    string phone_num = phone.substr(phone.find(' ') + 1);
    this->phone = new Phone(phone_type, phone_num);
}

Person::Person(string filename)
{
    set_person(filename);
}

void Person::set_person()
{
    // prompts for the information of the user from the terminal
    // first/last name can have spaces!
    // date format must be "M/D/YYYY"
    // We are sure user enters info in correct format.
    // TODO: complete this method!

    string temp;
    string type;

    cout << "First Name: ";
    // pay attention to how we read first name, as it can have spaces!
    std::getline(std::cin, f_name);

    cout << "Last Name: ";
    std::getline(std::cin, l_name);

    cout << "Birthdate (M/D/YYYY): ";
    std::getline(std::cin, temp);
    // pay attention to how we passed argument to the constructor of a new object created dynamically using new command
    birthdate = new Date(temp);

    cout << "Type of email address: ";
    std::getline(std::cin, type);
    cout << "Email address: ";
    std::getline(std::cin, temp);
    email = new Email(type, temp);

    cout << "Type of phone number: ";
    std::getline(std::cin, type);
    cout << "Phone number: ";
    std::getline(std::cin, temp);
    phone = new Phone(type, temp);
}

void Person::set_person(string filename)
{
    // reads a Person from a file
    // Look at person_template files as examples.
    // Phone number in files can have '-' or not.
    // TODO: Complete this method!
    ifstream infile(filename.c_str());

    getline(infile, f_name);
    getline(infile, l_name);

    string b_date;
    getline(infile, b_date);
    birthdate = new Date(b_date);

    string phone_str;
    getline(infile, phone_str);
    string phone_type = phone_str.substr(1, phone_str.find(')') - 1);
    string phone_num = phone_str.substr(phone_str.find(' ') + 1);
    phone = new Phone(phone_type, phone_num);

    string email_str;
    getline(infile, email_str);
    string email_type = email_str.substr(1, email_str.find(')') - 1);
    string email_addr = email_str.substr(email_str.find(' ') + 1);
    email = new Email(email_type, email_addr);

    infile.close();
}

bool Person::operator==(const Person &rhs)
{
    // TODO: Complete this method!
    // Note: you should check first name, last name and birthday between two persons
    // refer to bool Date::operator==(const Date& rhs)
    return f_name == rhs.f_name && l_name == rhs.l_name && *birthdate == *rhs.birthdate;
}

bool Person::operator!=(const Person &rhs)
{
    // TODO: Complete this method!
    return !(*this == rhs);
}

void Person::print_person()
{
    cout << l_name << ", " << f_name << endl;
    birthdate->print_date();
    phone->print();
    email->print();
    // loop over myfriends and print each as: <code> (<First> <Last>)
    for (int i = 0; i < (int)myfriends.size(); i++)
    {
        Person *f = myfriends[i];
        cout << codeName(f->f_name, f->l_name)
             << " (" << f->f_name << " " << f->l_name << ")" << endl;
    }
}

// appends the given Person pointer to this person's myfriends vector so they show up as a friend later
void Person::makeFriend(Person *newFriend)
{
    myfriends.push_back(newFriend);
}

// prints this person and their friends sorted by code: first letter, second letter
void Person::print_friends()
{
    // header line uses First, Last per the spec sample output
    cout << f_name << ", " << l_name << endl;
    cout << "--------------------------------" << endl;

    // work on a copy
    vector<Person *> sorted = myfriends;

    // simple bubble sort
    for (int i = 0; i < (int)sorted.size(); i++)
    {
        for (int j = 0; j < (int)sorted.size() - 1 - i; j++)
        {
            string codeA = codeName(sorted[j]->f_name, sorted[j]->l_name);
            string codeB = codeName(sorted[j + 1]->f_name, sorted[j + 1]->l_name);
            bool swap = false;
            if (codeA[0] > codeB[0])
            {
                swap = true;
            }
            else if (codeA[0] == codeB[0] && codeA[1] > codeB[1])
            {
                swap = true;
            }
            if (swap)
            {
                Person *tmp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = tmp;
            }
        }
    }

    // print friends as First Name comma Last Name
    for (int i = 0; i < (int)sorted.size(); i++)
    {
        cout << sorted[i]->f_name << ", " << sorted[i]->l_name << endl;
    }
}