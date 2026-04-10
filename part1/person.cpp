
#include "person.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

Person::Person(){
    // I'm already done! 
    set_person();
}


Person::~Person(){
    delete birthdate;
    delete email;
    delete phone;
}


Person::Person(string f_name, string l_name, string b_date, string email, string phone){
    // TODO: Complete this method!
    // phone and email strings are in full version
    this->f_name = f_name;
    this->l_name = l_name;
    this->next = NULL;
    this->prev = NULL;

    birthdate = new Date(b_date);

    string email_type  = email.substr(1, email.find(')') - 1);
    string email_addr  = email.substr(email.find(' ') + 1);
    this->email = new Email(email_type, email_addr);

    string phone_type  = phone.substr(1, phone.find(')') - 1);
    string phone_num   = phone.substr(phone.find(' ') + 1);
    this->phone = new Phone(phone_type, phone_num);
}


Person::Person(string filename){
    set_person(filename);
}


void Person::set_person(){
    // prompts for the information of the user from the terminal
    // first/last name can have spaces!
    // date format must be "M/D/YYYY"
    // We are sure user enters info in correct format.
    // TODO: complete this method!
    
    string temp;
    string type;

    cout << "First Name: ";
    // pay attention to how we read first name, as it can have spaces!
    std::getline(std::cin,f_name);

	cout << "Last Name: ";
    std::getline(std::cin,l_name);

    cout << "Birthdate (M/D/YYYY): ";
    std::getline(std::cin,temp);
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


void Person::set_person(string filename){
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
    string phone_type  = phone_str.substr(1, phone_str.find(')') - 1);
    string phone_num   = phone_str.substr(phone_str.find(' ') + 1);
    phone = new Phone(phone_type, phone_num);

    string email_str;
    getline(infile, email_str);
    string email_type  = email_str.substr(1, email_str.find(')') - 1);
    string email_addr  = email_str.substr(email_str.find(' ') + 1);
    email = new Email(email_type, email_addr);

    infile.close();
}


bool Person::operator==(const Person& rhs){
    // TODO: Complete this method!
    // Note: you should check first name, last name and birthday between two persons
    // refer to bool Date::operator==(const Date& rhs)
    return f_name == rhs.f_name && l_name == rhs.l_name && *birthdate == *rhs.birthdate;
}

bool Person::operator!=(const Person& rhs){ 
    // TODO: Complete this method!
    return !(*this == rhs);
}


void Person::print_person(){
	// Already implemented for you! Do not change!
	cout << l_name <<", " << f_name << endl;
	birthdate->print_date("Month D, YYYY");
    phone->print();
    email->print();
}