
#include "contact.h"
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

Email::Email(string type, string email_addr){
    // TODO: Complete me!
    this->type = type;
    this->email_addr = email_addr;
}


void Email::set_contact(){
    // TODO: Do not change the prompts!
	
    cout << "Enter the type of email address: ";
    // some code here
    getline(cin, type);
    cout << "Enter email address: ";
    // some code here
    getline(cin, email_addr);
}


string Email::get_contact(string style){
    // Note: We have default argument in declaration and not in definition!
    if (style=="full")
	    return "Email (" + type + ") " + email_addr;
    else 
        return email_addr;
}


void Email::print(){
    // Note: get_contact is called with default argument
	cout << get_contact() << endl;
}


Phone::Phone(string type, string num){
    // TODO: It is possible that num includes "-" or not, manage it!
    // TODO: Complete this method!
    // Note: We don't want to use C++11! stol is not valid!
    this->type = type;
    
    //remove all dashes from the phone number string
    string clean_num = "";
    for (int i = 0; i < num.length(); i++) {
        if (num[i] != '-') {
            clean_num += num[i];
        }
    }
    
    stringstream ss(clean_num);
    ss >> this->phone_num;
}


void Phone::set_contact(){
    // TODO: Complete this method
    // Use the same prompts as given!
	cout <<"Enter the type of phone number: ";
    getline(cin, type);
	cout << "Enter the phone number: ";
    string phone_num;
    getline(cin, phone_num);
    
    //remove dashes and convert to long long
    string clean_num = "";
    for (int i = 0; i < phone_num.length(); i++) {
        if (phone_num[i] != '-') {
            clean_num += phone_num[i];
        }
    }
    
    stringstream ss(clean_num);
    ss >> this->phone_num;
}


string Phone::get_contact(string style){
    // TODO: Complete this method, get hint from Email 
    // Convert phone_num to formatted string (XXX-XXX-XXXX)
    stringstream ss;
    ss << phone_num;
    string phone_str = ss.str();
    
    // Ensure we have 10 digits by padding with leading zeros
    while (phone_str.length() < 10) {
        phone_str = "0" + phone_str;
    }
    
    // Format as XXX-XXX-XXXX
    string formatted = phone_str.substr(0, 3) + "-" + 
                      phone_str.substr(3, 3) + "-" + 
                      phone_str.substr(6, 4);
    
    if (style=="full")
        return "Phone (" + type + ") " + formatted;
    else
        return formatted;
}


void Phone::print(){
    // Note: get_contact is called with default argument
	cout << get_contact() << endl;
}
