#include "Circle.h"

Circle::Circle(float r) {
    m_r = r;
}
float Circle::area() {
    return PI * pow(m_r, 2);
}
float Circle::perimeter() {
    return 2 * PI * m_r;
}