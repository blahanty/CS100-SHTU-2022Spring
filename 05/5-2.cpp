#include <cstdlib>
#include <iostream>
#include <cmath>
#include <string>
#include <list>
#include <iomanip>

const double PI = 3.14159;

/***********************************************************************
* Declaration/Definition of the base-class Shape *
***********************************************************************/
class Shape {
public:
    // constructors and destructor
    virtual ~Shape() = default;

    // Accessors; you should decide which should be virtual or pure virtual.
    virtual double CalculateArea() const {
        return 114514;
    };

    virtual double CalculatePerimeter() const {
        return 1919810;
    };

    virtual int NumberCorners() const = 0;

private:
    // member variables;

};


/***********************************************************************
* Declaration/Definition of the child-classes *
***********************************************************************/
class Rectangle; // ...
class Square; // ...
class Triangle; // ...
class Circle; // ...

class Rectangle : public Shape {
public:
    Rectangle(double len1, double len2) {
        width = len1;
        height = len2;
    }

    ~Rectangle() override {
        std::cout << "A Rectangle has been destroyed." << std::endl;
    }

    double CalculateArea() const override {
        return width * height;
    }

    double CalculatePerimeter() const override {
        return (width + height) * 2;
    }

    int NumberCorners() const override {
        return 4;
    }

private:
    double width, height;
};

class Square : public Shape {
public:
    explicit Square(double len) {
        side_length = len;
    }

    ~Square() override {
        std::cout << "A Square has been destroyed." << std::endl;
    }

    double CalculateArea() const override {
        return side_length * side_length;
    }

    double CalculatePerimeter() const override {
        return side_length * 4;
    }

    int NumberCorners() const override {
        return 4;
    }

private:
    double side_length;
};

class Triangle : public Shape {
public:
    Triangle(double len1, double len2) {
        side_length1 = len1;
        side_length2 = len2;
    }

    ~Triangle() override {
        std::cout << "A Triangle has been destroyed." << std::endl;
    }

    double CalculateArea() const override {
        return side_length1 * side_length2 * 0.5;
    }

    double CalculatePerimeter() const override {
        return side_length1 + side_length2 + sqrt(side_length1 * side_length1 + side_length2 * side_length2);
    }

    int NumberCorners() const override {
        return 3;
    };

private:
    double side_length1, side_length2;
};

class Circle : public Shape {
public:
    explicit Circle(double len) {
        radius = len;
    }

    ~Circle() override {
        std::cout << "A Circle has been destroyed." << std::endl;
    }

    double CalculateArea() const override {
        return PI * radius * radius;
    }

    double CalculatePerimeter() const override {
        return 2 * PI * radius;
    }

    int NumberCorners() const override {
        return 0;
    }

private:
    double radius;
};

/************************************************************************
* Main Function which is creating/reporting database (do not change!) *
************************************************************************/
int main() {
    //initialize an empty list of shapes
    std::list<Shape *> shapeDatabase;
    //interact with the user: ask the user to enter shapes one by one
    while (1) {
        //print instructions as to how to enter a shape
        std::cout << "Enter a type (Circle, Triangle, Square, or Rectangle) ";
        std::cout << "and one or two size parameters, ";
        std::cout << "separated with blank spaces:\n";
        double size1;
        double size2;
        //check which shape has been requested and store in the database
        std::string shapeType;
        std::cin >> shapeType;
        if (shapeType == std::string("Circle")) {
            std::cin >> size1;
            shapeDatabase.push_back(new Circle(size1));
        } else if (shapeType == std::string("Triangle")) {
            std::cin >> size1 >> size2;
            shapeDatabase.push_back(new Triangle(size1, size2));
        } else if (shapeType == std::string("Square")) {
            std::cin >> size1;
            shapeDatabase.push_back(new Square(size1));
        } else if (shapeType == std::string("Rectangle")) {
            std::cin >> size1 >> size2;
            shapeDatabase.push_back(new Rectangle(size1, size2));
        } else {
            std::cout << "Unrecognized shape!!\n";
        }
        //check if the user wants to add more shapes
        std::cout << "Do you want to add more shapes? (Enter Y or N)\n";
        std::string answer;
        std::cin >> answer;
        if (answer != std::string("Y"))
            break;
    }
    //iterate through the list and output the area, perimeter,
    //and number of corners of each entered shape
    std::list<Shape *>::iterator it = shapeDatabase.begin();
    int shapeCounter = 0;
    while (it != shapeDatabase.end()) {
        std::cout << "Properties of shape " << shapeCounter++ << ":\n";
        std::cout << "Area: " << std::setprecision(5) << (*it)->CalculateArea() << "\n";
        std::cout << "Perimeter: " << std::setprecision(5) << (*it)->CalculatePerimeter() << "\n";
        std::cout << "Corners: " << (*it)->NumberCorners() << "\n";
        std::cout << std::endl;
        it++;
    }

    it = shapeDatabase.begin();
    while (it != shapeDatabase.end()) {
        delete (*it);
        it = shapeDatabase.erase(it);
    }

    return 0;
}