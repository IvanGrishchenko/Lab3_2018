//developed by Oleksandr Maystrenko K-22, 2018
#include <SFML/Graphics.hpp>

int main(){
    const int amount = 20;
    sf::RenderWindow window(sf::VideoMode(1000, 600), "Lab3");
    sf::CircleShape dot[amount];
    for(int i = 0; i< amount; ++i){
        sf::CircleShape temp(3.f);
        temp.setFillColor(sf::Color::Black);
        float a = static_cast<float>(100+rand()%800);
        float b = static_cast<float>(100+rand()%400);
        temp.setPosition(sf::Vector2f(a, b));
        dot[i] = temp;
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        for(int i = 0; i< amount; ++i)
            window.draw(dot[i]);
        window.display();
    }

    return 0;
}
