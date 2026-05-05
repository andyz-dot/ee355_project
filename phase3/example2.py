import pandas as pd
from datetime import datetime
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import accuracy_score

#convert birthdate string into age
def get_age(birthdate):
    date = datetime.strptime(birthdate, "%m/%d/%Y") #parse string into datetime obj
    today = datetime.today()
    return today.year - date.year - ((today.month, today.day) < (date.month, date.day)) #compute age


#get email domain (after @)
def get_email_domain(email):
    return email.split("@")[1].lower()


#get area code - first 3 digits of phone num
def get_area_code(phone):
    return str(phone)[:3]


#count shared interest words btw two interest strings
def shared_interest_count(interest1, interest2):
    words1 = set(str(interest1).lower().split()) #convert to lowercase, split to words, turn into sets
    words2 = set(str(interest2).lower().split())
    return len(words1.intersection(words2)) #return num of overlapping words


#build feature row for two people
def build_features(person1, person2):
    age1 = get_age(person1["birthdate"]) #compute ages
    age2 = get_age(person2["birthdate"])

    #construct feature dictionary
    features = {
        "age_difference": abs(age1 - age2), #absolute age diff
        "same_area_code": int(get_area_code(person1["phone"]) == get_area_code(person2["phone"])), # 1 if same area code, else 0
        "same_email_domain": int(get_email_domain(person1["email"]) == get_email_domain(person2["email"])), # 1 if same email domain, else 0
        "same_college": int(person1["college"] == person2["college"]), # 1 if same college, else 0
        "same_major": int(person1["major"] == person2["major"]), # 1 if same major, else 0
        "same_state": int(person1["state"] == person2["state"]), # 1 if same state, else 0
        "same_zip": int(str(person1["zip"]) == str(person2["zip"])), # 1 if same zip code, else 0
        "shared_interests": shared_interest_count(person1["interest"], person2["interest"]) #num of shared interest words
    }

    return features


#convert friendship pairs into ML dataset
def create_training_data(people, friendships):
    rows = []

    for _, pair in friendships.iterrows(): #loop through each friendship pair
    	#retrieve person row from people dataset
        person1 = people[people["id"] == pair["person1_id"]].iloc[0]
        person2 = people[people["id"] == pair["person2_id"]].iloc[0]

        features = build_features(person1, person2) #feature vector for the pair
        features["friends"] = pair["friends"] #add label, 1=friends 0=not friends 

        rows.append(features)

    return pd.DataFrame(rows) #convert list of dicts into dataframe


#recommend connections for one person
def recommend_connections(target_id, people, model):
    #get target user data
    target = people[people["id"] == target_id].iloc[0]
    recommendations = []
    
    #compare target with every other user
    for _, other in people.iterrows():
        if other["id"] == target_id:
            continue #skip self

	#build features btw target and another person
        features = build_features(target, other)
        feature_df = pd.DataFrame([features])

        prediction = model.predict(feature_df)[0] #predict friendship 1 or 0
        probability = model.predict_proba(feature_df)[0][1] #prob of being friends 

        if prediction == 1: #only positive predictions
            recommendations.append((probability, other))

    recommendations.sort(reverse=True, key=lambda x: x[0]) #sort recs by highest probabliity first
    return recommendations


def main():
    people = pd.read_csv("phase3_people.csv")
    friendships = pd.read_csv("phase3_friendships.csv")

    dataset = create_training_data(people, friendships) #training dataset

    print("TRAINING DATA")
    print("====================")
    print(dataset)

    #seperate features (X) and labels (Y)
    X = dataset.drop("friends", axis=1)
    y = dataset["friends"]

    X_train, X_test, y_train, y_test = train_test_split( #split train and test sets
        X,
        y,
        test_size=0.1, #10% for testing 
        random_state=1
    )

    model = LogisticRegression() #log regression model
    model.fit(X_train, y_train) #train model on training data

    predictions = model.predict(X_test) #predict on test data
    accuracy = accuracy_score(y_test, predictions)

    print()
    print("MODEL EVALUATION")
    print("====================")
    print("Accuracy:", accuracy)

    print()
    print("RECOMMEND CONNECTIONS")
    print("====================")

    target_id = int(input("Enter user id: ")) #get user input from target user ID
    recommendations = recommend_connections(target_id, people, model) #generate recs
    
    #print results
    if len(recommendations) == 0:
        print("No recommended connections found")
    else:
        for probability, person in recommendations:
            print(
                person["first_name"],
                person["last_name"],
                "- recommendation score:",
                round(probability, 2)
            )


if __name__ == "__main__":
    main()
