/**-------------------------------------------

Program 3: Password Checker

Course: CS 141, Fall 2022, UIC

System: CLION on Windows 11

Author: Sanskar Kalal(651632119), starter code provided by Sara Riazi

------------------------------------------- **/

#include "iomanip"
#include "iostream"
#include "fstream"
#include "string"
#include "vector"
using namespace std;

const string rule_msg_1 = "The selected password must be at least eight characters long.";
const string rule_msg_2 = "The selected password must have at least one uppercase letter.";
const string rule_msg_3 = "The selected password must have at least one lowercase letter.";
const string rule_msg_4 = "The selected password must have at least one digit.";
const string rule_msg_5 = "The selected password must have at least one of special characters: [@,!,#,^,&,*,$]";
const string rule_msg_6 = "The selected password has been leaked.";
const string rule_msg_7 = "The selected password cannot contain a dictionary word.";



/*
Rule 1 checks the length of the password and returns true if the length of the password is less than 8 characters
 which would make it an invalid password and show the error message for rule 1
 */
bool Rule1(string pass){
    bool passSize = false;

    if (pass.size()<8){ //checks if password contains more than or equal to 8 characters
        passSize= true;
    }
    return passSize;
}

/*
Rule 2 checks if the password contains an UpperCase character and returns true if no character is UpperCase
 which would make it an invalid password and show the error message for rule 2
 */
bool Rule2(string pass){
    bool upper=true;

    //Loop through the whole string
    for(int i=0;i<pass.size();i++){
        if (isupper(pass[i])){ //check if the character is UpperCase
            upper = false;
        }

    }
    return upper;

}

/*
Rule 3 checks if the password contains an LowerCase character and returns true if no character is LowerCase
 which would make it an invalid password and show the error message for rule 3
 */
bool Rule3(string pass){
    bool lower = true;

    //Loop through the whole string
    for(int i=0;i<pass.size();i++){
        if (islower(pass[i])){ // check if the character is Lowercase
            lower = false;
        }

    }
    return lower;

}

/*
Rule 4 checks if the password contains a digit and returns true if no digit is found
 which would make it an invalid password and show the error message for rule 4
 */
bool Rule4(string pass){
    bool digit=true;

    //Loop through the whole string
    for(int i=0;i<pass.size();i++){
        if (isdigit(pass[i])){ //check if the character is a digit
            digit = false;
        }

    }
    return digit;

}

/*
Rule 5 checks if the password contains a special character and returns true if no special character is found
 which would make it an invalid password and show the error message for rule 5
 */
bool Rule5(string pass){
    bool special = true;

    //Loop through the whole string
    for(int i=0;i<pass.size();i++){

        //Check if the character is a special character
        if ((pass[i]=='!')||(pass[i]=='#')||(pass[i]=='@')||(pass[i]=='^')
        ||(pass[i]=='&')||(pass[i]=='*')||(pass[i]=='$'))
        {
            special = false;
        }

    }
    return special;

}

/*
 * readFile would take the name of the file and an empty vector as a parameters
 * fill the vector with all the contents of the text file which would make each element easily accesible
 * makes it easier to search the password inside it
 */
int readFile(string file, vector<string> &leakedPassList){
    fstream newfile;
    newfile.open(file);  //Open File
    if (newfile.is_open()){
        
        string leakedPass;
        //Read each line and add it to the vector
        while(getline(newfile, leakedPass)){
            leakedPassList.push_back(leakedPass);

        }

    }
    return 0;

}

/*
lower returns the password into lowercase form so that it can be compared to the text file elements
 */
string lower(string pass){
    string lowerStr = "";
    for(int i =0;i<pass.size();i++){
        lowerStr+= tolower(pass.at(i));

    }

    return lowerStr;
}

/*
compare takes the password as a parameter and returns the password without the special characters
this helps to search for the password in the text file
 */
string compare(string pass){
    pass = lower(pass);
    string temp = "";
    for (int  i=0;i<pass.size();i++){

        if((pass[i]=='!')||(pass[i]=='#')||(pass[i]=='@')||(pass[i]=='^')||(pass[i]=='&')||(pass[i]=='*')||(pass[i]=='$')){
        temp +="";

        }else{
        temp += pass.at(i);
    }

}
    return temp;
}

/*
 * binarySearch using the compare function makes the password and the elements of the file comparable
 * searches for the given password inside the vector and returns the index if it is found or
 * returns -1 if the password is not found
 */
int binarySearch(vector<string> &leakedPasswordList, string target, int low, int high) {
    target = compare(target);
    // Repeat until the pointers low and high meet each other
    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (compare(leakedPasswordList.at(mid)) == target) {
            return mid;
        }
        if (compare(leakedPasswordList.at(mid)) < target) {
            low = mid + 1;
        }
        else{
            high = mid - 1;
         }
    }

    return -1;
}

/*
Rule 6 uses binary search function to find the password inside the leaked password list and returns true if password
 is found which makes it an invalid password and shows the rule 6 message
 */
bool Rule6(string pass, vector<string> &leakedPasswordList){
    int result;

    //search the password using binary search
    result = binarySearch(leakedPasswordList, pass, 0, leakedPasswordList.size() - 1);
    if(result == -1){
        return false;
    }
    else{
        return true;
    }
}

/*
Rule 7 searches each element of the english word list inside the password using the find method
and returns true if the password contains the word which makes it and invalid password and shows the rule 7  error message
 */
bool Rule7(string pass,vector<string> &englishWordsList){
    pass = lower(pass);
    bool found = false;
    int i;
    for(i=0;i<englishWordsList.size();i++){
        //check if the password contains the word
        if(pass.find(englishWordsList.at(i)) != string::npos){
            found = true;
        }

    }
    return found;
}

/****
 * Runs the main part of the program
 ****/
int run(string leaked_password_file, string english_word_file){
    string password;
    cout<< "Enter password: ";
    getline(cin,password);

    //Initializing a vector to store the text file
    vector<string> leakedPassList(0);
    vector <string> englishWordsList(0);

    //Convert the text file to a vector
    readFile(leaked_password_file,leakedPassList);
    readFile(english_word_file,englishWordsList);

    //show messages according to the rules passed
    if(Rule1(password)){
        cout<<rule_msg_1<<endl;
    }
    if(Rule2(password)){
        cout<<rule_msg_2<<endl;
    }
    if(Rule3(password)){
        cout<<rule_msg_3<<endl;
    }
    if(Rule4(password)){
        cout<<rule_msg_4<<endl;
    }
    if(Rule5(password)){
        cout<<rule_msg_5<<endl;
    }

    //Reject the password even if one of the rule is broken
    if ( Rule1(password) ||  Rule2(password) ||  Rule3(password)||  Rule4(password)||  Rule5(password)){
        cout<<"Password rejected!";
    }

    //Do not check rule 6 unless the first rules are passed
    if (not Rule1(password) && not Rule2(password) && not Rule3(password) && not Rule4(password) && not Rule5(password)){
    if(Rule6(password,leakedPassList)){
        cout<<rule_msg_6<<endl;

        cout<<"Password rejected!";

    }

    //Do not check rule 7 before you check rule 6
    else if(Rule7(password,englishWordsList)) {
        cout << rule_msg_7 << endl;
        cout << "Password rejected!";
    }

    //Password is accepted once it passes all rules
    else{
            cout<<"Password accepted!"<<endl;
        }
    }
    return 0;
}

int main() {
	/** Change the address of the files appropriatly based on your local machine.
	 * This main function will be replaced during testing. Do not add any line of code to the main function 
	 **/
	string leaked_password_file = "alleged-gmail-passwords.txt"; //change this based on the location of the file on your machine
	string english_word_file = "words_5.txt"; //change this based on the location of the file on your machine
	run(leaked_password_file, english_word_file);
	return 0;	
}