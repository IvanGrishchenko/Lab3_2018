//developed by Oleksandr Maystrenko K-22, 2018
#include <SFML/Graphics.hpp>
#include "lab3_functions.hxx"
#include "lab3_line.hxx"
#include <ctime>
#include <cstdlib>

using namespace std;

int main(){
    sf::RenderWindow window(sf::VideoMode(1000, 600), "Lab3");
    sf::VertexArray dot = generateDots();
    //sf::VertexArray lines = andrewJarvis(dot);
    //sf::VertexArray lines = fortune(dot);
    sf::VertexArray lines = recursive(dot);
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Key::Space){
                dot = generateDots();
                //lines = andrewJarvis(dot);
                andrewJarvisAnimate(window, dot);
                //lines = recursive(dot);
                //recursiveAnimate(window, dot);
            }

        }
        /*
        window.clear(sf::Color::White);
        window.draw(lines);
        for(int i = 0; i< amount; ++i)
            drawDot(window, dot[i], 0);
        window.display();
        */
    }
    return 0;
}
