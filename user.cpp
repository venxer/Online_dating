#include "user.h"
#include <string>

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

    void User::pushBack(User* &head, User* &tail, User* &User)
    {
        if(tail == nullptr)
        {
            head = User;
            tail = User;
            return;
        }
        tail->setNext(User);
        User->setPrev(tail);
        tail = User;
    }
    void User::popBack(User* &head, User* &tail)
    {
        User* temp = tail;
        tail = tail->getPrev();
        tail->setNext(nullptr);
        // delete the original tail
        delete temp;
    }