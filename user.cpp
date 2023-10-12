#include "user.h"

#include <string>
#include <iostream>
#include <fstream>
#include <cmath>

// Default Constructor
User::User()
{
    name = "";
    age = 0;
    gender = "";
    phoneNumber = "";
    profession = "";
    school = "";
    latitude = 0.0;
    longitude = 0.0;
    isPremium = false;
    agePrefMin = 0;
    agePrefMax = 0;
    distancePref = 0;
    genderPref = "";
    likedUsers = "";
    next = nullptr;
    prev = nullptr;
}
// Constructor
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
           std::string likedUsers)
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
    next = nullptr;
    prev = nullptr;
}
/**
 * Adds a User object to the end of a doubly linked list
 * 
 * @param head Reference to the head pointer of the doubly linked list
 * @param tail Reference to the tail pointer of the doubly linked list
 * @param user Pointer to the user object to be added to the doubly linked list
 */
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

/**
 * Merges two sorted doubly linked lists based on the phone numbers of User
 * 
 * @param first Pointer to the head of the first sorted doubly linked list
 * @param second Pointer to the head of the second sorted doubly linked list
 * 
 * @return Pointer to the merged sorted doubly linked list 
 */
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

/**
 * Sorts a doubly linked list using merge sort
 * 
 * @param head Pointer to head of the doubly inked list
 * 
 * @return Pointer to the sorted doubly linked list
 */
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

/**
 * Deallocates memory for all nodes in a doubly linked list of User objects
 * 
 * @param head Pointer to the head of the doubly linked list
 */
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

/**
 * Removes all instance of underscore in a string
 * 
 * @param input String from which underscore should be removed from
 * 
 * @return String with no underscore
 */
std::string removeUnderscore(std::string input)
{
    std::replace(input.begin(), input.end(), '_', ' ');
    return input;
}

/**
 * Replace the first occurence of the original string to another string
 * 
 * @param original Original string where replacement will occur
 * @param remove Substring to be replaced
 * @param replace String to take place of the removed string
 * 
 * @return String with specified substring replaced
 */
std::string replaceSubstring(std::string original, std::string remove, std::string replace)
{
    size_t index = original.find(remove);
    // If index exist
    if (index != std::string::npos) 
    {
        original.replace(index, remove.length(), replace);
    }
    return original;
}

/**
 * Finds the user the phone number is linked to
 * 
 * @param head Pointer to the head of the doubly linked list
 * @param phoneNum Phone Number to search for
 * 
 * @return Pointer to the found User object and nullptr if User not found
 */
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

/**
 * Calculate the distance between two coordinates using Haversine formula
 * 
 * @param lat1 Latitude of the first coordinate
 * @param lon1 Longitude of the first coordinate
 * @param lat2 Latitude of the second coordinate
 * @param lon2 Longitude of the second coordinate
 * 
 * @return Distance between the two coordinates in miles.
 */
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

/**
 * Finds and outputs user profiles that match the preferences of the user
 * 
 * @param head Pointer to the head of the doubly linked list
 * @param user Pointer to the user whose preferences are to be matched
 * @param out_str Output stream for writing the matched user profiles
 */
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

/**
 * Finds and outputs mutual matches for the user
 * 
 * @param head Pointer to the head of the doubly linked list
 * @param user Pointer to the user for whose matches are to be found
 * @param out_str Output stream for writing the matched user profiles
 */
void findMatch(User* head, User* user, std::ofstream &out_str)
{
    if(head == nullptr) return;

    int count = 0;
    std::string userLikedUser = user->getLikedUsers();
    std::string userNum = user->getPhoneNumber();

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

/**
 * For premium users, finds and outputs other users that have liked the user
 * 
 * @param head Pointer to the head of the doubly linked list
 * @param user Pointer to the user whom we will find other users that have liked the user
 * @param out_str Output stream for writing the other users profiles
 */
void findLike(User* head, User* user, std::ofstream &out_str)
{
    if(head == nullptr) return;

    // Check if user is a premium user
    if(!user->getIsPremium())
    {
        out_str << "Only premium users can view who liked you.\n" << std::endl;
        return;
    }

    int count = 0;
    std::string userNum = user->getPhoneNumber();
    
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
    // If recieved no likes
    if(count == 0)
    {
        out_str <<  "You have not received any likes so far.\n" << std::endl;
    }
}

/**
 * Unmatch two users and remove them from each other's likedUser list
 * Prints each user's updated mutual matches
 * 
 * @param head Pointer to the head of the doubly linked list
 * @param user Pointer to the user unmatching
 * @param otherNum Phone number of the user to unmatch
 * @param out_str Output stream for writing the updated matches for each user
 */
void unmatch(User* head, User* user, const std::string otherNum, std::ofstream &out_str)
{
    if(head == nullptr) return;

    User* otherUser = fetchUser(head, otherNum);
    std::string userNum = user->getPhoneNumber();
    std::string userLiked = user->getLikedUsers();
    std::string otherUserLiked = otherUser->getLikedUsers();
    
    // Remove number from each other's LikedUsers
    userLiked = replaceSubstring(userLiked, otherNum, "");
    otherUserLiked = replaceSubstring(otherUserLiked, userNum, "");
    // Remove trailing underscores
    userLiked = replaceSubstring(userLiked, "__", "_");
    otherUserLiked = replaceSubstring(otherUserLiked, "__", "_");
    // If no phone numbers in likedUser, set it to null
    if(userLiked == "") userLiked = "null";
    if(otherUserLiked == "") otherUserLiked = "null";
    // Update likedUser list
    otherUser->setLikedUsers(otherUserLiked);
    user->setLikedUsers(userLiked);
    
    /* Print User Output */
    int userCount = 0;    
    out_str << user->getName() << "'s match list:\n" << std::endl;
    // Set start to first node and loop through nodes
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
    // If no matches for User
    if(userCount == 0)
    {
        out_str << "You do not have any matches at this moment.\n" << std::endl;
    }
    out_str << "======\n" << std::endl;
    
    /* Print Other User Output */
    int otherUserCount = 0;
    out_str << otherUser->getName() << "'s match list:\n" << std::endl;
    // Set start to first node and loop through nodes
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
    // If no matches for Other User
    if(otherUserCount == 0)
    {
        out_str << "You do not have any matches at this moment.\n" << std::endl;
    }
}

std::ostream &operator<<(std::ostream &out_str, const User &user)
{
    // Output user's name and age
    out_str << user.getName() << " " << user.getAge() << std::endl;
    
    // Output profession if it is not "Undisclosed"
    if(user.getProfession() != "Undisclosed")
    {
        std::string formattedProfession = removeUnderscore(user.getProfession());
        out_str << formattedProfession << std::endl;
    }

    // Output school if it is not "Undisclosed"
    if(user.getSchool() != "Undisclosed")
    {
        std::string formattedSchool = removeUnderscore(user.getSchool());
        out_str << formattedSchool << std::endl;
    }
    return out_str;
}