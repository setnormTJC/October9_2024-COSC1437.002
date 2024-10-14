// October9_2024-COSC1437.002.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

#include"iomanip"

using std::cout; 
using std::string; 
using std::setprecision; 

class Person
{
public: 
    string firstName = "first name TBD";
    string lastName = "last name TBD";
    int age = 11;

    void print() const
    {
        //firstName = "adsfasfasdf";
        cout << "first name: " << firstName << "\n";
        cout << "last name: " << lastName << "\n";
        cout << "age: " << age << "\n";
    }

    /*Our implementation of a default Person constructor*/
    Person()
    {
        //firstName;
        //lastName ;
    }
};


//: means "inherits member variables and member functions from" 
class Employee : public Person//, A //; NO! (Maybe multiple inheritance isn't such a good idea (hard to understand) 
{
public: 
    string jobTitle; 
    double salary; 

    //let's write an Employee default constructor and a parameterized constructor 
    Employee()
        :Person() //what is this?
    {
        jobTitle = "Job title to be determined";
        salary = 9.90; 
    }

    void print() const // override -> we will talk about this more when we get to "abstract" classes 
    {
        //jobTitle = "adsfasdf";
       
        Person::print(); //this will print the first three attributes of an Employee 

        cout << "Job title: " << jobTitle << "\n";
        cout << "Salary: $" << std::fixed << setprecision(2) << salary << "\n";

        //print(); //NO! -> this will lead to "infinite recursion"!
    }
};

class RetiredPerson : public Person
{
    double pension; 
};

class Manager : public Employee // a manager "is-a(n)" Employee
{
public: 
    std::vector<Person> peopleManaged; //ex = { "Alice", "Bob", "Carol" };

};


//another very typical example of inheritance: 
class Shape
{
    double area; 
};

class Triangle : public Shape //when inheritance is used, it implies an "is-a" relationship 
{

};

class Tail
{
    int tailWidth; 
    bool isBushy; 
};

class Dog //: public Tail //No! A dog is not a tail -> a dog is COMPOSED of a tail 
{
    Tail tailObject; //this says that a Dog "has-a" tail
};



class Car
{
public: 

};
int main()
{
   
    Person you; 
   
    cout << "Person object attributes:\n";
    you.print(); 

    Employee alsoYou;; 
    cout << "\n\n\nEmployee object attributes (using the default constructor): \n";
    alsoYou.print(); //this function OVERRODE its parent!

}
