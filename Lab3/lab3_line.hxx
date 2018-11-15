#ifndef LAB3_LINE_HXX_INCLUDED
#define LAB3_LINE_HXX_INCLUDED
#include <SFML/Graphics.hpp>

class Line{
protected:
    sf::Vector2f p;
    sf::Vector2f q;
    float k = 0;
    float b = 0;
public:
    Line() = default;
    Line(sf::CircleShape p, sf::CircleShape q);
    Line(float k, float b);

    float getK();
    float getB();
    void setK(float k0);
    void setB(float b0);

    bool isPointIsAbove(sf::CircleShape p);
};

#endif // LAB3_LINE_HXX_INCLUDED
