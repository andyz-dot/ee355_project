def load_database(filename):
    users = []

    with open(filename, "r") as file:
        blocks = file.read().split("--------------------") #split each person by seperator 

    for block in blocks: #process person block
        lines = [line.strip() for line in block.strip().splitlines()]
        
        #skip empty or incomplete blocks
        if len(lines) < 5:
            continue

	#first 5 lines from previous phase format
        user = { 
            "first_name": lines[0],
            "last_name": lines[1],
            "birthdate": lines[2],
            "email": lines[3],
            "phone": lines[4],
            "extra": {} #phase 3 addition, key value storage
        }
	#remaining lines after 5 is phase3 extra fields
        for line in lines[5:]:
            if ":" in line:
                key, value = line.split(":", 1)
                user["extra"][key.strip().lower()] = value.strip() #storing in lowercase so search is not case sensitive 

        users.append(user)

    return users


def print_user(user):
    print(user["last_name"] + ", " + user["first_name"])
    print(user["birthdate"])
    print(user["email"])
    print(user["phone"])

    for key, value in user["extra"].items():
        print(key.capitalize() + ": " + value)

    print("--------------------")

#search in both original and extra fields
def extensive_search(users, query):
    query = query.lower()
    results = []

    for user in users:
        if ( #search in original fields 
            query in user["first_name"].lower()
            or query in user["last_name"].lower()
            or query in user["birthdate"].lower()
            or query in user["email"].lower()
            or query in user["phone"].lower()
        ):
            results.append(user)
            continue
	#search in extra fields 
        for value in user["extra"].values():
            if query in value.lower():
                results.append(user)
                break

    return results


def main():
    users = load_database("phase3networkDB.txt") #enlarged database load 

    while True:
        print()
        print("1. Print all users")
        print("2. Search")
        print("3. Exit")

        choice = input("Select an option: ")

        if choice == "1":
            print()
            print("ALL USERS")
            print("====================")

            for user in users:
                print_user(user)

        elif choice == "2":
            print()
            print("SEARCH")
            print("====================")

            query = input("Search anything: ")
            results = extensive_search(users, query)

            if len(results) == 0:
                print("No users found")
            else:
                for user in results:
                    print_user(user)

        elif choice == "3":
            break

        else:
            print("Invalid option")

#start the program
if __name__ == "__main__":
    main()
