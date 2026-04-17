# Trojan-Book

EE355 project - a contact manager using a doubly linked list in C++. Phase 2 extends it into a small social network so people can be friends with each other and be searched by more than just name.

## Files

- `network.h / network.cpp` - Network class, stores Person nodes in a doubly linked list. Has load/save to file, add/remove, search, and an interactive menu. Phase 2 adds Connect (option 6) and Wise Search (option 7).
- `person.h / person.cpp` - Person class with name, birthday, email, phone. Supports == and != comparison. Phase 2 adds a `myfriends` vector, `makeFriend`, and `print_friends`.
- `date.h / date.cpp` - Date class, parses M/D/YYYY strings.
- `contact.h / contact.cpp` - Base Contact class, with Email and Phone subclasses.
- `misc.h / misc.cpp` - prints the ascii banner. Phase 2 adds the `codeName` helper.
- `networkDB.txt` - sample database with 3 people.
- `test_network.cpp` - main driver, runs the menu.
- `test_person_eq.cpp` - quick test for person == and != operators.

## Compiling

Phase 1, run from `part1/`:

```
g++ -o test_network test_network.cpp network.cpp person.cpp date.cpp contact.cpp misc.cpp
./test_network
```

Phase 2, run from `phase2/`:

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

## Phase 2

### Part 1 - Connect menu option

- NEW: option 6 "Connect" in `network.cpp`.
- Clears screen, prints "Make friends:", reads first + last name for person 1 and person 2
- Uses the existing private `search(fname, lname)` to look each one up
- If either is missing, prints "Person not found" and bails to the menu. If both exist, prints them in order using `print_person`

### Part 2 - myfriends vector + makeFriend

- ADDED: `vector<Person*>` called `myfriends` as a private attribute on Person. Pointers so two people can link to each other without deep copying
- `makeFriend(Person* newFriend)` is a one-line `push_back` onto that vector
- Connect now calls `makeFriend` on both sides after printing, since the spec says Connect is double sided

### Part 3 - codeName helper

- ADDED: `string codeName(string str1, string str2)` to `misc`
- Concatenates the two strings, skips spaces, lowercases with a manual `c - 'A' + 'a'` shift so we do not need `<algorithm>` or `<cctype>`
- Example: `codeName("Enania", "Mordak Young")` returns `"enaniamordakyoung"`

### Part 4 - print_person lists friends

- After the existing name / date / phone / email block, `print_person` loops over `myfriends` and prints each line as `<code> (First Last)`
- Empty friend list prints nothing exra, so phase 1 behavior still holds for people with no friends

### Part 5 - print_friends sorted output

- NEW: `Person::print_friends`
- Header is "First, Last" (intentionally different from `print_person`, which uses "Last, First" - the spec sample shows both)
- Sort key: first letter of the code, then second letter as tiebreaker. Bubble sort since the list is relatively small

### Part 6 - Wise Search

- NEW: option 7 "Wise Search" in `network.cpp`
- Prompts "Search By:" then walks the linked list looking for a match on phone (formatted or digits only), email address, or birthday
- Birthday match only attempted when the query contains a `/`, so we do not build a Date out of random input
- Prints the matched person with `print_person` (so their friends show up too), or "Person not found" if nothing hits

## Things that tripped me up

- ChatGPT and Google search AI was used for errors that would pop up in terminal and syntax errors.

* Newline left in the input buffer after `cin >> opt` kept getting swallowed by the next `getline`, so the first prompt always read an empty string. Had to add `cin.ignore` right after reading the option
* First attempt at `myfriends` was `vector<Person>` not `vector<Person*>`. That copies the object, so when I connected A and B, B's copy of A was not the same A in the linked list. Swapping to pointers fixed it but took a while to notice since nothing crashed
* Forgot to `#include <vector>` in `person.h` the first time and got a wall of template errors that did not point at the actual line
* Bubble sort inner loop was `j < size - i` instead of `j < size - 1 - i`, which ran one past the end on the last pass. Found it when a small test case printed a garbage friend
* Got confused between `print_person` ("Last, First") and `print_friends` ("First, Last").
* First version of Wise Search always matched the first person when the query was not a date, because `Date(query)` left the fields uninitialized and compared equal to whoever happened to be first. Fixed with a `query.find('/')` check.
* On the Connect flow I only called `makeFriend` on one side at first, so only one person "knew" they were friends. Had to remember the relationship is double sided and call it on both.
* Forgot to include `misc.h` in `person.cpp` after using `codeName` inside `print_person`. Compiler caught it but took a second to notice the error was not about Person itself.
