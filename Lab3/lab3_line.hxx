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
    Line(sf::Vector2f p, sf::Vector2f q);
    Line(float k, float b);

    float getK();
    float getB();
    void setK(float k0);
    void setB(float b0);

    bool ifPointIsAbove(sf::Vector2f v);
};

#endif // LAB3_LINE_HXX_INCLUDED
