
#include "network.h"
#include <limits>
#include "misc.h"
#include <fstream>
#include <sstream>

Network::Network(){
    head = NULL;
    tail = NULL;
    count = 0;
}


Network::Network(string fileName){
    head = NULL; tail = NULL; count = 0; loadDB(fileName);
}

Network::~Network(){ 
    Person* ptr = head;
    while (ptr != NULL) {
        Person* temp = ptr;
        ptr = ptr->next;
        delete temp;
    }
}

Person* Network::search(Person* searchEntry){
    Person* ptr = head;
    while (ptr != NULL) {
        if (*ptr == *searchEntry)
            return ptr;
        ptr = ptr->next;
    }
    return NULL;
}


Person* Network::search(string fname, string lname){
    Person* ptr = head;
    while (ptr != NULL) {
        if (ptr->f_name == fname && ptr->l_name == lname)
            return ptr;
        ptr = ptr->next;
    }
    return NULL;
}


void Network::loadDB(string filename){
    ifstream infile(filename.c_str());
    if (!infile.is_open()) return;

    Person* ptr = head;
    while (ptr != NULL) {
        Person* temp = ptr;
        ptr = ptr->next;
        delete temp;
    }
    head = NULL;
    tail = NULL;
    count = 0;

    string fname, lname, bdate, emailStr, phoneStr, separator;
    while (getline(infile, fname)) {
        if (fname.empty() || fname[0] == '-') continue;
        if (!getline(infile, lname)) break;
        if (!getline(infile, bdate)) break;
        if (!getline(infile, emailStr)) break;
        if (!getline(infile, phoneStr)) break;
        getline(infile, separator);

        Person* p = new Person(fname, lname, bdate, emailStr, phoneStr);
        push_back(p);
    }
    infile.close();
}

void Network::saveDB(string filename){
    ofstream outfile(filename.c_str());
    Person* ptr = head;
    while (ptr != NULL) {
        outfile << ptr->f_name << endl;
        outfile << ptr->l_name << endl;

        ostringstream oss;
        streambuf* oldBuf = cout.rdbuf(oss.rdbuf());
        ptr->birthdate->print_date();
        cout.rdbuf(oldBuf);
        string dateStr = oss.str();

        string months[] = {"January", "February", "March", "April", "May", "June",
                           "July", "August", "September", "October", "November", "December"};
        stringstream ds(dateStr);
        string monthName;
        int day, year;
        char comma;
        ds >> monthName >> day >> comma >> year;
        int monthNum = 0;
        for (int i = 0; i < 12; i++) {
            if (months[i] == monthName) {
                monthNum = i + 1;
                break;
            }
        }
        outfile << monthNum << "/" << day << "/" << year << endl;

        string emailFull = ptr->email->get_contact("full");
        outfile << emailFull.substr(6) << endl;

        string phoneFull = ptr->phone->get_contact("full");
        outfile << phoneFull.substr(6) << endl;

        outfile << "--------------------" << endl;
        ptr = ptr->next;
    }
    outfile.close();
}


void Network::printDB(){
    cout << "Number of people: " << count << endl;
    cout << "------------------------------" << endl;
    Person* ptr = head;
    while(ptr != NULL){
        ptr->print_person();
        cout << "------------------------------" << endl;
        ptr = ptr->next;
    }
}



void Network::push_front(Person* newEntry){
    newEntry->prev = NULL;
    newEntry->next = head;

    if (head != NULL)
        head->prev = newEntry;
    else
        tail = newEntry;
    
    head = newEntry;
    count++;
}


void Network::push_back(Person* newEntry){
    newEntry->next = NULL;
    newEntry->prev = tail;

    if (tail != NULL)
        tail->next = newEntry;
    else
        head = newEntry;

    tail = newEntry;
    count++;
}


bool Network::remove(string fname, string lname){
    Person* ptr = search(fname, lname);
    if (ptr == NULL) return false;

    if (ptr->prev != NULL)
        ptr->prev->next = ptr->next;
    else
        head = ptr->next;

    if (ptr->next != NULL)
        ptr->next->prev = ptr->prev;
    else
        tail = ptr->prev;

    delete ptr;
    count--;
    return true;
}


void Network::showMenu(){
    // TODO: Complete this method!
    // All the prompts are given to you, 
    // You should add code before, between and after prompts!

    int opt;
    while(1){
        cout << "\033[2J\033[1;1H";
        printMe("banner"); // from misc library

        cout << "Select from below: \n";
        cout << "1. Save network database \n";
        cout << "2. Load network database \n";
        cout << "3. Add a new person \n";
        cout << "4. Remove a person \n";
        cout << "5. Print people with last name  \n";
        cout << "\nSelect an option ... ";
        
        if (cin >> opt) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Wrong option! " << endl;
            return;
        }
        
        string fname, lname, fileName, bdate;
        cout << "\033[2J\033[1;1H";

        if (opt==1){
            cout << "Saving network database \n";
            cout << "Enter the name of the save file: ";
            getline(cin, fileName);
            saveDB(fileName);
            cout << "Network saved in " << fileName << endl;
        }
        else if (opt==2){
            cout << "Loading network database \n";
            system("ls *.txt 2>/dev/null");
            cout << "Enter the name of the load file: "; 
            getline(cin, fileName);
            ifstream testFile(fileName.c_str());
            if (!testFile.good()) {
                cout << "File " << fileName << " does not exist!" << endl;
            } else {
                testFile.close();
                loadDB(fileName);
                cout << "Network loaded from " << fileName << " with " << count << " people \n";
            }
        }
        else if (opt == 3){
            cout << "Adding a new person \n";
            Person* p = new Person();
            if (search(p) == NULL) {
                push_front(p);
            } else {
                cout << "Person already exists! \n";
                delete p;
            }
        }
        else if (opt == 4){
            cout << "Removing a person \n";
            cout << "First name: ";
            getline(cin, fname);
            cout << "Last name: ";
            getline(cin, lname);
            if (remove(fname, lname)) {
                cout << "Remove Successful! \n";
            } else {
                cout << "Person not found! \n";
            }
        }
        else if (opt==5){
            cout << "Print people with last name \n";
            cout << "Last name: ";
            getline(cin, lname);
            bool found = false;
            Person* ptr = head;
            while (ptr != NULL) {
                if (ptr->l_name == lname) {
                    ptr->print_person();
                    cout << endl;
                    found = true;
                }
                ptr = ptr->next;
            }
            if (!found) {
                cout << "Person not found! \n";
            }
        }
        
        else
            cout << "Nothing matched!\n";
        
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "\n\nPress Enter key to go back to main menu ... ";
        string temp;
        std::getline (std::cin, temp);
        cout << "\033[2J\033[1;1H";
    }
}
