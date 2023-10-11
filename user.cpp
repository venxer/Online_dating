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

void pushBack(User* &head, User* &tail, User* &user)
{
    if(tail == nullptr)
    {
        head = user;
        tail = user;
        return;
    }
    tail->setNext(user);
    user->setPrev(tail);
    tail = user;
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
    // Check if empty
    if (first == nullptr) return second;
    if (second == nullptr) return first;
    
    // Order by PhoneNumber
    if (first->getPhoneNumber() < second->getPhoneNumber()) 
    {
        // Recursively merge the elements after the first node
        first->setNext(merge(first->getNext(), second));
        // Adjust pointers for doubly linked list
        if (first->getNext() != nullptr) 
        {
            first->getNext()->setPrev(first);
        }
        first->setPrev(nullptr);
        return first;
    } 
    else 
    {
        // Recursively merge the elements after the second node
        second->setNext(merge(first, second->getNext()));
        // Adjust pointers for doubly linked list
        if (second->getNext() != nullptr)
        {
            second->getNext()->setPrev(second);
        }
        second->setPrev(nullptr);
        return second;
    }
}
User* mergeSort(User* head)
{
    // Check if only singular Node (already sorted)
    if (head == nullptr || head->getNext() == nullptr) return head;
    
    // Split list into 2
    User* slow = head;
    User* fast = head->getNext();
    while (fast != nullptr) 
    {
        fast = fast->getNext();
        if (fast != nullptr) 
        {
            fast = fast->getNext();
            slow = slow->getNext();
        }
    }

    // Seperate second half from first half
    User* secondHalf = slow->getNext();
    slow->setNext(nullptr);
    if (secondHalf != nullptr) 
    {
        secondHalf->setPrev(nullptr);
    }
    
    // Recursively call mergeSort on each half
    return merge(mergeSort(head), mergeSort(secondHalf));
}

std::string removeUnderscore(std::string input)
{
    std::replace(input.begin(), input.end(), '_', ' ');
    return input;
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

User* fetchUser(User* head, const std::string phoneNum)
{
    while(head != nullptr)
    {
        if(head->getPhoneNumber() == phoneNum)
        {
            return head;
        }
        head = head->getNext();
    }
    return head;
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
    if(head == nullptr) return;
    User* otherUser = fetchUser(head, otherNum);

    std::string userNum = user->getPhoneNumber();
    std::string userLiked = user->getLikedUsers();
    std::string otherUserLiked = otherUser->getLikedUsers();
    
    // Remove number from each other's LikedUsers and remove trailing double underscores
    userLiked = replaceSubstring(removeSubstring(userLiked, otherNum), "__", "_");
    otherUserLiked = replaceSubstring(removeSubstring(otherUserLiked, userNum), "__", "_");
    // If no phone numbers in likedUser, set it to null
    if(userLiked == "") userLiked = "null";
    if(otherUserLiked == "") otherUserLiked = "null";

    otherUser->setLikedUsers(otherUserLiked);
    user->setLikedUsers(userLiked);
    

    int userCount = 0;
    int otherUserCount = 0;
    
    // User
    out_str << user->getName() << "'s match list:\n" << std::endl;
    User* current = head;
    while(current != nullptr)
    {
        if(userLiked.find(current->getPhoneNumber()) != std::string::npos &&
           current->getLikedUsers().find(userNum) != std::string::npos)
        {
            // Increase count + Output info
            userCount++;
            out_str << *current << std::endl;
        }
        current = current->getNext();
    }
    // If no matches
    if(userCount == 0)
    {
        out_str << "You do not have any matches at this moment.\n" << std::endl;
    }
    out_str << "======\n" << std::endl;
    // Other User
    out_str << otherUser->getName() << "'s match list:\n" << std::endl;
    current = head;
    while(current != nullptr)
    {
        if(otherUserLiked.find(current->getPhoneNumber()) != std::string::npos &&
           current->getLikedUsers().find(otherNum) != std::string::npos)
        {
            // Increase count + Output info
            otherUserCount++;
            out_str << *current << std::endl;
        }
        current = current->getNext();
    }
    // If no matches
    if(otherUserCount == 0)
    {
        out_str << "You do not have any matches at this moment.\n" << std::endl;
    }
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