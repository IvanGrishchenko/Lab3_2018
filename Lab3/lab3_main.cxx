//developed by Oleksandr Maystrenko K-22, 2018
#include <SFML/Graphics.hpp>
#include "lab3_functions.hxx"
#include "lab3_line.hxx"
#include <ctime>
#include <cstdlib>

using namespace std;

void drawDot(sf::RenderWindow& window, sf::Vertex dot){
    sf::CircleShape shape(radius);
    shape.setPosition(sf::Vector2f(dot.position.x - radius, dot.position.y - radius));
    shape.setFillColor(sf::Color::Black);
    window.draw(shape);
}

void drawInfo(sf::RenderWindow& window, const unsigned int x){
    sf::Font font;
    font.loadFromFile("times.ttf");
    sf::Text text("seed = " + to_string(x), font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);
    text.setPosition(10,10);
    window.draw(text);
}

sf::VertexArray generateDots(){
    sf::VertexArray dot(sf::Points, amount);
    for(int i = 0; i < amount; ++i){
        float a = static_cast<float>(100+rand()%800);
        float b = static_cast<float>(100+rand()%400);
        dot[i].position = sf::Vector2f(a, b);
    }
    return dot;
}
int main(){
    sf::RenderWindow window(sf::VideoMode(1000, 600), "Lab3");
    unsigned int x = time(0);
    srand(x);
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
                x = time(0);
                srand(x);
                dot = generateDots();
                //lines = andrewJarvis(dot);
                //lines = fortune(dot);
                lines = recursive(dot);
            }

        }
        window.clear(sf::Color::White);
        drawInfo(window, x);
        window.draw(lines);
        for(int i = 0; i< amount; ++i)
            drawDot(window, dot[i]);
        window.display();
    }
    return 0;
}
