#include <SFML/Graphics.hpp>
#include "lab3_line.hxx"
#include "lab3_functions.hxx"

Line::Line(float k, float b):Line(){
    setK(k);
    setB(b);
}
Line::Line(sf::Vertex p, sf::Vertex q):Line(){
    float x1 = p.position.x;
    float y1 = p.position.y;
    float x2 = q.position.x;
    float y2 = q.position.y;
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

bool Line::isPointIsAbove(sf::Vertex p){
    return getK()*(p.position.x) + getB() - p.position.y > -eps;
}
