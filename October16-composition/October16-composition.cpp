// October16-composition.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

//class Tail
//{
//    bool isBushy; 
//    int length; 
//};
//
//
//class Animal
//{
//    std::string species; 
//};
//class Dog : public Animal
//{
//    //a dog "has-a" tail: 
//    Tail dogsTail; //composition (a dog is "composed of" a tail) 
//};


using std::cout; 
using std::string; 

struct Student
{
    string studentName;
    string major; 
    int age; 

    void printStudentDeets()
    {
        cout << "Student name: " << studentName << "\n";
        cout << "Major: " << major << "\n";
        cout << "Age: " << age << "\n";
    }
};

class ClassRoom
{
    string roomName; 
    std::vector<Student> students; 

public: 
    //make a constructor 
    ClassRoom(string roomName, std::vector<Student> students)
        :roomName(roomName), students(students)
    {

    }
    
    // print the attributes of the room
    void printRoomDetails()
    {
        cout << "Room name is: " << roomName << "\n";
        
        cout << "Details of all of the students:\n";

        for (auto& theCurrentStudent : students)
        {
            theCurrentStudent.printStudentDeets(); 
        }
    }


};

int main()
{
    //construct an object of type `Room` 
    // (using a parameterized constructor function) 
    
    std::vector<Student> students =
    {
        {"Melany Hernandez", "Game sim major", 21},
        {"Connor Philpot", "CS?", 99},
        {"Daniel (Leyuan) Tang", "CS", 23}
    };

    //"live coding" 
    ClassRoom thisRoom
    {
        "T-240",
        students
    }; 

    Student loneStudent = { "casper", "casper's major", 999 };
    std::vector<Student> theStudentsNextDoor = 
    { 
        loneStudent 
    };


    ClassRoom theRoomNextToUs{ "T-239", theStudentsNextDoor };

    thisRoom.printRoomDetails(); 
    cout << "\n\n\n";
    theRoomNextToUs.printRoomDetails(); 


    //thisRoom.printRoomDetails(32)
    //std::cout << "Hello World!\n";
}
