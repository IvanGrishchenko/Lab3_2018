//developed by Oleksandr Maystrenko K-22, 2018
#include <SFML/Graphics.hpp>
#include "lab3_functions.hxx"
#include "lab3_line.hxx"

int main(){
    sf::RenderWindow window(sf::VideoMode(1000, 600), "Lab3");

    sf::CircleShape dot[amount];
    for(int i = 0; i < amount; ++i){
        sf::CircleShape temp(radius);
        temp.setFillColor(sf::Color::Black);
        float a = static_cast<float>(100+rand()%800);
        float b = static_cast<float>(100+rand()%400);
        temp.setPosition(a, b);
        dot[i] = temp;
    }

    sf::VertexArray lines = andrewJarvis(dot);

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::White);
        window.draw(lines);
        for(int i = 0; i< amount; ++i)
            window.draw(dot[i]);
        window.display();
    }
    return 0;
}
