# Trojan-Book

EE355 project - a contact manager using a doubly linked list in C++.

## Files

- `network.h / network.cpp` - Network class, stores Person nodes in a doubly linked list. Has load/save to file, add/remove, search, and an interactive menu.
- `person.h / person.cpp` - Person class with name, birthday, email, phone. Supports == and != comparison.
- `date.h / date.cpp` - Date class, parses M/D/YYYY strings.
- `contact.h / contact.cpp` - Base Contact class, with Email and Phone subclasses.
- `misc.h / misc.cpp` - prints the ascii banner.
- `networkDB.txt` - sample database with 3 people.
- `test_network.cpp` - main driver, runs the menu.
- `test_person_eq.cpp` - quick test for person == and != operators.

## Compiling

Run from `part1/`:

```
g++ -o test_network test_network.cpp network.cpp person.cpp date.cpp contact.cpp misc.cpp
./test_network
```

For the person equality test:
```
g++ -o test_person_eq test_person_eq.cpp person.cpp date.cpp contact.cpp
./test_person_eq
```

## DB file format

Each person is 5 lines then a separator:
```
FirstName
LastName
M/D/YYYY
(EmailType) email@example.com
(PhoneType) 1234567890
--------------------
```
