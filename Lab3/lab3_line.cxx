#include <SFML/Graphics.hpp>
#include "lab3_line.hxx"

Line::Line(float k, float b):Line(){
    setK(k);
    setB(b);
}
Line::Line(sf::Vector2f p, sf::Vector2f q):Line(){
    float x1 = p.x;
    float y1 = p.y;
    float x2 = q.x;
    float y2 = q.y;
    float k = (y2-y1)/(x2-x1);
    float b = y1-k*x1;
    setK(k);
    setB(b);
}

float Line::getK(){
    return k;
}
float Line::getB(){
    return b;
}
void Line::setK(float k0){
    k = k0;
}
void Line::setB(float b0){
    b = b0;
}

bool Line::ifPointIsAbove(sf::Vector2f v){
    return getK()*v.x + getB() < v.y;
}
