#ifndef USER_H
#define USER_H

#include <string>

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
        User *next;
        User *prev;
    public:
        User(std::string name = "",
             unsigned int age = 0,
             std::string gender = "",
             std::string phoneNumber = "",
             std::string profession = "",
             std::string school = "",
             double latitude = 0.0,
             double longitude = 0.0,
             bool isPremium = false,
             unsigned int agePrefMin = 0,
             unsigned int agePrefMax = 0,
             unsigned int distancePref = 0,
             std::string genderPref = "",
             std::string likedUsers = "",
             User* next = nullptr,
             User* prev = nullptr);

        std::string getName()          const{return name;}
        unsigned int getAge()          const{return age;}
        std::string getGender()        const{return gender;}
        std::string getPhoneNumber()   const{return phoneNumber;}
        std::string getProfession()    const{return profession;}
        std::string getSchool()        const{return school;}
        double getLatitude()           const{return latitude;}
        double getLongitude()          const{return longitude;}
        bool getIsPremium()            const{return isPremium;}
        unsigned int getAgePrefMin()   const{return agePrefMin;}
        unsigned int getAgePrefMax()   const{return agePrefMax;}
        unsigned int getDistancePref() const{return distancePref;}
        std::string getGenderPref()    const{return genderPref;}
        std::string getLikedUsers()    const{return likedUsers;}
        User* getNext()                const{return next;}
        User* getPrev()                const{return prev;}

        void setNext(User* ptr)             {next = ptr;}
        void setPrev(User* ptr)             {prev = ptr;}
        
};

// void pushBack(User* user);
void pushBack(User* &head, User* &tail, User* &User);
void popBack(User* &head, User* &tail);
#endif