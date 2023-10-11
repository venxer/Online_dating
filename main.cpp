#include "user.h"

#include <string>
#include <iostream>
#include <fstream>

void parseFile(std::ifstream &in_str, User* &head, User* &tail);
bool stringToBool(std::string input);
void clearUsers(User* head);

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

    std::ifstream in_str(input);
    if(!in_str.good())
    {
        std::cerr << "Invalid Input File" << std::endl; 
        exit(1);
    }
    std::ofstream out_str(output);
    if(!out_str.good())
    {
        std::cerr << "Invalid Output File" << std::endl; 
        exit(1);
    }

    // Parse input file where head and tail are the head and tail
    // of the doubly linked list respectively
    User* head = nullptr;
    User* tail = nullptr;
    parseFile(in_str, head, tail);

    User* user = fetchUser(head, phoneNum);

    if(user == nullptr)
    {
        std::cerr << "User not found" << std::endl;
        exit(1);
    }
    if(head == nullptr)
    {
        exit(1);
    }


    if(mode == "profile")
    {
        findProfile(head, user, out_str);
    }
    else if(mode == "match")
    {
        // Sort Nodes before unmatch since output needs to be sorted
        head = mergeSort(head);
        findMatch(head, user, out_str);
    }
    else if(mode == "like")
    {
        findLike(head, user, out_str);
    }
    else if(mode =="unmatch")
    {
        // Check for otherNum if mode is "unmatch"
        if(argc < 5)
        {
            std::cerr << "Missing Inputs" << std::endl;
            exit(1);   
        }
        otherNum = argv[5];
        // Sort Nodes before unmatch since output needs to be sorted
        head = mergeSort(head);
        unmatch(head, user, otherNum, out_str);
        
    }
    else
    {
        std::cerr << "Invalid Mode" << std::endl;
        exit(1);   
    }

    // Free memory
    clearUsers(head);
    
    return 0;
}

void parseFile(std::ifstream &in_str, User* &head, User* &tail)
{ 
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
}
bool stringToBool(std::string input)
{
    if(input == "true") return true;
    return false;
}

void clearUsers(User* head)
{
    User* next;
    while (head != nullptr) 
    {
        next = head->getNext();
        delete head;
        head = next;
    }
}