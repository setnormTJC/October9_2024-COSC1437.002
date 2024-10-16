// October14-continuing inheritance stuff.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

//class Food
//{
//    int numberOfCalories = 0; 
//
//
//};
//
//
//class MealType : public Food
//{
//
//};


namespace MySpace
{
    int a = 23; 
}



using std::cout; 

class Rectangle
{
    //private: 
protected: 

    int x, y; //x is length, y is width

public: 
    void setDimensions(int clientX, int clientY)
    {
        x = clientX; 
        y = clientY;
    }

    void print()
    {
        cout << "Length: " << x << "\nWidth: " << y << "\n";
    }

    Rectangle(int x, int y)
        : x(x), y(y) //"member initializer syntax"
    {

    }

    Rectangle()
    {

    }

};

class Box : public Rectangle
{

    int z{}; //height 

public: 
    void setDimensions(int length, int width, int height);


    /*This print function will override any "print" function defined inside of Rectangle (the parent) */
    void print()// override //we will discuss override keyword when we get to "abstract" classes
    {
        Rectangle::print(); 
        cout << "Height: " << z << "\n";
    }

    Box()
    {

    }
}; //end of Box class def:

void Box::setDimensions(int length, int width, int height)
{
    //Rectangle::setDimensions(length, width);
    Rectangle::x = length;
    Rectangle::y = width; 
    //protected 
    
    Box::z = height;
}

int main()
{

    //cout << MySpace::a << 
    Rectangle theGoldenRectangle{ 10, 22 };
    theGoldenRectangle.setDimensions(1222, 5849);
    theGoldenRectangle.print(); 

    cout << "\n\n\n";

    Box thisRoom; 
    //thisRoom.setDimensions() NOT endline 
    thisRoom.setDimensions(10, 20, 30); 
    thisRoom.print();
    //thisRoom.setDimensions(30, 20, 10);
    //cout << endl 
    //std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
