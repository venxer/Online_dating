#include "user.h"

#include <string>
#include <iostream>
#include <fstream>

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
std::string removeUnderscore(std::string input)
{
    std::replace(input.begin(), input.end(), '_', ' ');
    return input;
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
void findProfile(User* head, User* user, std::string outputFile)
{
    // Opens and check if outputFile is valid
    std::ofstream out_str(outputFile);
    if(!out_str.good())
    {
        std::cerr << "Invalid Output File" << std::endl; 
        exit(1);
    }

    int matchCount = 0;
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
            // Increase match count + Output info
            matchCount++;
            out_str << *head << std::endl;

        }
        head = head->getNext();
    }
    // If no profiles mathces preferences
    if(matchCount == 0)
    {
        out_str << "There are no users matching with your preference at this moment." << std::endl;
    }
    out_str.close();
}
void findMatch(User* head, User* user, std::string outputFile)
{
        // Opens and check if outputFile is valid
    std::ofstream out_str(outputFile);
    if(!out_str.good())
    {
        std::cerr << "Invalid Output File" << std::endl; 
        exit(1);
    }


    out_str.close();
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