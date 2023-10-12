#ifndef USER_H
#define USER_H

#include <string>
#include <algorithm>

class User
{
    private:
        std::string name;
        unsigned int age;
        std::string gender;
        std::string phoneNumber;
        std::string profession;
        std::string school;
        double latitude;
        double longitude;
        bool isPremium;
        unsigned int agePrefMin;
        unsigned int agePrefMax;
        unsigned int distancePref;
        std::string genderPref;
        std::string likedUsers;
        User* next;
        User* prev;
    public:
        User();
        User(std::string name,
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
             std::string likedUsers);

        // Getters
        std::string getName()            const{return name;}
        unsigned int getAge()            const{return age;}
        std::string getGender()          const{return gender;}
        std::string getPhoneNumber()     const{return phoneNumber;}
        std::string getProfession()      const{return profession;}
        std::string getSchool()          const{return school;}
        double getLatitude()             const{return latitude;}
        double getLongitude()            const{return longitude;}
        bool getIsPremium()              const{return isPremium;}
        unsigned int getAgePrefMin()     const{return agePrefMin;}
        unsigned int getAgePrefMax()     const{return agePrefMax;}
        unsigned int getDistancePref()   const{return distancePref;}
        std::string getGenderPref()      const{return genderPref;}
        std::string getLikedUsers()      const{return likedUsers;}
        User* getNext()                  const{return next;}
        User* getPrev()                  const{return prev;}

        // Setters
        void setNext(User* ptr)               {next = ptr;}
        void setPrev(User* ptr)               {prev = ptr;}
        void setLikedUsers(std::string users) {likedUsers = users;}
        
};

// Altering Nodes
void pushBack(User* &head, User* &tail, User* &user);
User* merge(User* first, User* second);
User* mergeSort(User* head);
void clearUsers(User* head);

// String manipulators
std::string removeUnderscore(std::string input);
std::string replaceSubstring(std::string original, std::string remove, std::string replace);

// Helper functions
User* fetchUser(User* head, const std::string phoneNum);
double calculateDistance(double lat1, double lon1, double lat2, double lon2);

// Mode
void findProfile(User* head, User* user, std::ofstream &out_str);
void findMatch(User* head, User* user, std::ofstream &out_str);
void findLike(User* head, User* user, std::ofstream &out_str);
void unmatch(User* head, User* user, const std::string otherNum, std::ofstream &out_str);

// Output
std::ostream &operator<<(std::ostream &out_str, const User &user);

#endif