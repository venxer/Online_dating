#include "user.h"

#include <string>
#include <iostream>
#include <fstream>
#include <cmath>

User::User(std::string name,
           unsigned int age,
           std::string gender,
           std::string phoneNumber,
           std::string profession,
           std::string school,
           double latitude,
           double longitude,
           bool isPremium,
           unsigned int agePrefMin,
           unsigned int agePrefMax,
           unsigned int distancePref,
           std::string genderPref,
           std::string likedUsers,
           User *next,
           User *prev)
{
    this->name = name;
    this->age = age;
    this->gender = gender;
    this->phoneNumber = phoneNumber;
    this->profession = profession;
    this->school = school;
    this->latitude = latitude;
    this->longitude = longitude;
    this->isPremium = isPremium;
    this->agePrefMin = agePrefMin;
    this->agePrefMax = agePrefMax;
    this->distancePref = distancePref;
    this->genderPref = genderPref;
    this->likedUsers = likedUsers;
}

void pushBack(User* &prev, User* &next, User* &user)
{
    if(next == nullptr)
    {
        prev = user;
        next = user;
        return;
    }
    next->setNext(user);
    user->setPrev(next);
    next = user;
}
void popBack(User* &prev, User* &next)
{
    User* temp = next;
    next = next->getPrev();
    next->setNext(nullptr);
    // delete the original tail
    delete temp;
}
User* merge(User* first, User* second)
{
    if(first == nullptr) return second;
    if(second == nullptr) return first;
    if(first->getPhoneNumber() > second->getPhoneNumber())
    {

    }
}

bool fetchUser(User* head, const std::string phoneNum, User* &user)
{
    while(head != nullptr)
    {
        if(head->getPhoneNumber() == phoneNum)
        {
            user = head;
            return true;
        }
        head = head->getNext();
    }
    user = head;
    return false;
}
std::string removeUnderscore(std::string input)
{
    std::replace(input.begin(), input.end(), '_', ' ');
    return input;
}
// calculate the distance between two coordinates using Haversine formula
double calculateDistance(double lat1, double lon1, double lat2, double lon2)
{
    const double radiusOfEarth = 6371.0; // Earth's radius in kilometers

    // convert latitude and longitude from degrees to radians
    lat1 *= M_PI / 180.0;
    lon1 *= M_PI / 180.0;
    lat2 *= M_PI / 180.0;
    lon2 *= M_PI / 180.0;

    // Haversine formula
    double dLat = lat2 - lat1;
    double dLon = lon2 - lon1;
    double a = sin(dLat / 2.0) * sin(dLat / 2.0) + cos(lat1) * cos(lat2) * sin(dLon / 2.0) * sin(dLon / 2.0);
    double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));
    // distance in kilometers
    double distanceKM = radiusOfEarth * c;
    // convert it to distance in miles
    double distanceMiles = distanceKM * 0.621371;

    return distanceMiles;
}
std::string removeSubstring(std::string original, std::string remove)
{
    size_t index = original.find(remove);
    // If the substring is found, remove substring
    if (index != std::string::npos) 
    {
        original.erase(index, remove.length());
    }
    return original;
}
std::string replaceSubstring(std::string original, std::string remove, std::string replace)
{
    size_t index = original.find(remove);
    if (index != std::string::npos) 
    {
        original.replace(index, remove.length(), replace);
    }
    return original;

}
void findProfile(User* head, User* user, std::ofstream &out_str)
{
    int count = 0;
    // Loop through nodes
    while(head != nullptr)
    {
        bool bothGender = user->getGenderPref() == "Both";
        double distance = calculateDistance(head->getLatitude(), head->getLongitude(),
                                            user->getLatitude(), user->getLongitude());
        // Check preferences + Not user itself
        if((bothGender || head->getGender() == user->getGenderPref()) &&
            head->getAge() >= user->getAgePrefMin() &&
            head->getAge() <= user->getAgePrefMax() &&
            distance <= user->getDistancePref() &&
            head->getPhoneNumber() != user->getPhoneNumber())
        {
            // Increase count + Output info
            count++;
            out_str << *head << std::endl;
        }
        head = head->getNext();
    }
    // If no profiles matches preferences
    if(count == 0)
    {
        out_str << "There are no users matching with your preference at this moment.\n" << std::endl;
    }
}
//NEED TO SORT
void findMatch(User* head, User* user, std::ofstream &out_str)
{
    int count = 0;
    std::string userLikedUser;
    std::string userNum; 
    if(head != nullptr)
    {
        userLikedUser = user->getLikedUsers();
        userNum = user->getPhoneNumber();
    }

    // Loop through nodes
    while(head != nullptr)
    {
        // Check if each other's phone numbers are in each other's likedUsers
        if(userLikedUser.find(head->getPhoneNumber()) != std::string::npos &&
           head->getLikedUsers().find(userNum) != std::string::npos)
        {
            // Increase count + Output info
            count++;
            out_str << *head << std::endl;
        }
        head = head->getNext();
    }
    // If no matches
    if(count == 0)
    {
        out_str << "You do not have any matches at this moment.\n" << std::endl;
    }
}
void findLike(User* head, User* user, std::ofstream &out_str)
{
    if(!user->getIsPremium())
    {
        out_str << "Only premium users can view who liked you.\n" << std::endl;
        return;
    }

    int count = 0;
    std::string userNum;
    if(head != nullptr)
    {
        userNum = user->getPhoneNumber();
    }
    
    // Loop through nodes
    while(head != nullptr)
    {
        if(head->getLikedUsers().find(userNum) != std::string::npos)
        {
            count++;
            out_str << *head << std::endl;
        }
        head = head->getNext();
    }
    if(count == 0)
    {
        out_str <<  "You have not received any likes so far.\n" << std::endl;
    }
}
void unmatch(User* head, User* user, const std::string otherNum, std::ofstream &out_str)
{
    User* otherUser;
    bool otherUserFound = fetchUser(head, otherNum, otherUser);
    if(!otherUserFound)
    {
        std::cerr << "Invalid Unmatch Account Number" << std::endl;
        exit(1);
    }

    std::string userNum; 
    std::string userLiked;
    std::string otherUserLiked;
    if(head != nullptr)
    {
        userNum = user->getPhoneNumber();
        userLiked = user->getLikedUsers();
        otherUserLiked = otherUser->getLikedUsers();
        
        // Remove number from each other's LikedUsers and remove trailing double underscores
        userLiked = replaceSubstring(removeSubstring(userLiked, otherNum), "__", "_");
        otherUserLiked = replaceSubstring(removeSubstring(otherUserLiked, userNum), "__", "_");
        // If no phone numbers in likedUser, set it to null
        if(userLiked == "") userLiked = "null";
        if(otherUserLiked == "") otherUserLiked = "null";

        otherUser->setLikedUsers(otherUserLiked);
        user->setLikedUsers(userLiked);
    }
    std::cout << user->getLikedUsers() << std::endl;
        std::cout << "==========" << std::endl;

    std::cout << otherUser->getLikedUsers() << std::endl;


    // while(head != nullptr)
    // {
        

    //     head = head->getNext();
    // }


}
std::ostream &operator<<(std::ostream &out_str, const User &user)
{
    out_str << user.getName() << " " << user.getAge() << std::endl;
    if(user.getProfession() != "Undisclosed")
    {
        std::string formattedProfession = removeUnderscore(user.getProfession());
        out_str << formattedProfession << std::endl;
    }
    if(user.getSchool() != "Undisclosed")
    {
        std::string formattedSchool = removeUnderscore(user.getSchool());
        out_str << formattedSchool << std::endl;
    }
    return out_str;
}