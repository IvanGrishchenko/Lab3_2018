#include <SFML/Graphics.hpp>
#include <algorithm>
#include "lab3_functions.hxx"
#include "lab3_line.hxx"

sf::VertexArray andrewJarvis(const sf::CircleShape dot[]){
    sf::CircleShape dot0[amount];
    for(int i = 0; i< amount; ++i)
        dot0[i]=dot[i];

    sf::CircleShape temp;
    for (int i = 0; i < amount - 1; ++i) {
        for (int j = 0; j < amount - i - 1; ++j) {
            if (dot0[j].getPosition().x > dot0[j + 1].getPosition().x) {
                temp = dot0[j];
                dot0[j] = dot0[j + 1];
                dot0[j + 1] = temp;
            }
        }
    }

    Line line0(sf::Vector2f(dot0[0].getPosition().x+radius, dot0[0].getPosition().y+radius),
               sf::Vector2f(dot0[amount-1].getPosition().x+radius, dot0[amount-1].getPosition().y+radius));
    sf::CircleShape upperSubset[amount];
    sf::CircleShape lowerSubset[amount];
    int upperN = 0;
    int lowerN = 0;
    for(int i = 0; i < amount; ++i){

    }









    sf::VertexArray ans(sf::LineStrip, 40);
    ans[0].position = sf::Vector2f(dot0[0].getPosition().x+radius,  dot0[0].getPosition().y+radius);
    ans[0].color = sf::Color::Black;
    ans[1].position = sf::Vector2f(200, 10);
    ans[1].color = sf::Color::Black;
    ans[2].position = sf::Vector2f(300, 50);
    ans[2].color = sf::Color::Black;
    ans[3].position = sf::Vector2f(400, 20);
    ans[3].color = sf::Color::Black;
    return ans;
}
