#include <SFML/Graphics.hpp>
#include "lab3_line.hxx"
#include "lab3_functions.hxx"

Line::Line(float k, float b):Line(){
    setK(k);
    setB(b);
}
Line::Line(sf::CircleShape p, sf::CircleShape q):Line(){
    float x1 = p.getPosition().x+radius;
    float y1 = p.getPosition().y+radius;
    float x2 = q.getPosition().x+radius;
    float y2 = q.getPosition().y+radius;
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

bool Line::isPointIsAbove(sf::CircleShape p){
    return (p.getPosition().y+radius) - getK()*(p.getPosition().x+radius) - getB() > -eps;
}
