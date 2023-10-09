#include "user.h"
#include <string>
#include <iostream>

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