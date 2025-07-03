#include <iostream>
#include <cstring>

#include "Circle.h"
#include "Rectangle.h"
#include "config.h"

int main(int argc, char* argv[]) {
    std::cout << "VERSION: " << MYPROJECT_VERSION_MAJOR << "." << MYPROJECT_VERSION_MINOR << std::endl;
    //* std::cout << argc << " " << argv[0] << " " << argv[1] << " " << argv[2] << std::endl;

    if (argc < 2) {
        std::cout << "return 0" << std::endl;
        return 0;
    }
    if (strcmp(argv[1], "c") == 0 && argc == 3) {
        //* std::cout << "build circle" << std::endl;
        Circle c(std::stod(argv[2]));
        std::cout << "circle area: " << c.area() << std::endl;
        std::cout << "circle perimeter: " << c.perimeter() << std::endl;
    }
    return 0;
}