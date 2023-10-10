#include "user.h"

#include <string>
#include <iostream>
#include <fstream>

void parseFile(std::string &inputFile, User* &head, User* &tail);
bool stringToBool(std::string input);
void printNode(User* head);

int main(int argc, char const *argv[])
{
    if(argc < 4)
    {
        std::cerr << "Invalid Inputs" << std::endl;
        exit(1);
    }
    std::string input = argv[1];
    std::string output = argv[2];
    std::string phoneNum = argv[3]; 
    std::string mode = argv[4];
    std::string otherNum;

    User* head = nullptr;
    User* tail = nullptr;
    parseFile(input, head, tail);

    // printNode(head);
    User* user;
    bool userFound = fetchUser(head, phoneNum, user);

    if(!userFound)
    {
        std::cerr << "Invalid Account Number" << std::endl;
        exit(1);   
    }

    if(mode == "profile")
    {
        findProfile(head, user, output);
    }
    else if(mode == "match")
    {
        findMatch(head, user, output);
    }
    else if(mode == "like")
    {

    }
    else if(mode =="unmatch")
    {
        // Check for otherNum if mode is "unmatch"
        if(argv[5] == NULL)
        {
            std::cerr << "Missing Inputs" << std::endl;
            exit(1);   
        }
        else
        {
            otherNum = argv[5];
        }
    }
    else
    {
        std::cerr << "Invalid Mode" << std::endl;
        exit(1);   
    }

    return 0;
}

void parseFile(std::string &inputFile, User* &head, User* &tail)
{
    std::ifstream in_str(inputFile);
    if(!in_str.good())
    {
        std::cerr << "Invalid Input File" << std::endl; 
        exit(1);
    }
    
    std::string name, gender, phoneNumber, profession, 
                school, genderPref, likedUsers, isPremium;
    unsigned int age, agePrefMin, agePrefMax, distancePref;
    double latitude,longitude;

    while(in_str >> name >> age >> gender >> phoneNumber >>
                    profession >> school >> latitude >> longitude >>
                    isPremium >> agePrefMin >> agePrefMax >> distancePref >>
                    genderPref >> likedUsers)
    {

        User* user = new User(name, age, gender, phoneNumber,
                              profession, school, latitude, longitude, 
                 stringToBool(isPremium), agePrefMin, agePrefMax, distancePref, 
                              genderPref, likedUsers);

        pushBack(head, tail, user);
    }
    in_str.close();
}
bool stringToBool(std::string input)
{
    if(input == "true") return true;
    return false;
}
void printNode(User* head)
{
    // Loops till node is null
    while (head != nullptr)
    {
        std::cout << *head << std::endl;

        // Move to the next node
        head = head->getNext();
    }
}