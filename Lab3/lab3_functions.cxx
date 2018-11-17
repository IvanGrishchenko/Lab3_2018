#include <SFML/Graphics.hpp>
//#include <iostream>
#include <algorithm>
#include <cmath>
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
    Line line0(dot0[0], dot0[amount-1]);

    sf::CircleShape upperSubset[amount];
    sf::CircleShape lowerSubset[amount];
    int upperN = 0;
    lowerSubset[0] = dot0[0];
    int lowerN = 1;
    for(int i = 0; i < amount; ++i){
        if(line0.isPointIsAbove(dot0[i])){
            upperSubset[upperN] = dot0[i];
            ++upperN;
        }
        else{
            lowerSubset[lowerN] = dot0[i];
            ++lowerN;
        }
    }
    lowerSubset[lowerN] = dot0[amount-1];
    ++lowerN;

    sf::VertexArray ans0(sf::LineStrip, amount);
    int ans0N = 1;
    ans0[0].position = sf::Vector2f(dot0[0].getPosition().x+radius,  dot0[0].getPosition().y+radius);
    ans0[0].color = sf::Color::Black;
    int current = 0;
    sf::CircleShape elem = upperSubset[current];

    int counter = amount;
    while(abs(elem.getPosition().x-dot0[amount-1].getPosition().x) > eps
          && counter &&
          abs(elem.getPosition().y-dot0[amount-1].getPosition().y) > eps){
        for(int i = current+1; i < upperN; ++i){
            Line tempLine(elem,upperSubset[i]);
            int tempInt = -1, j = 0;
            bool checker1 = true;
            while(j < upperN && checker1){
                if(j != current && j != i){
                    if(tempInt == -1){
                        if(tempLine.isPointIsAbove(upperSubset[j]))
                            tempInt = 1;
                        else tempInt = 0;
                    }
                    if((tempInt == 0) && tempLine.isPointIsAbove(upperSubset[j]))
                        checker1 = false;
                    if((tempInt == 1) && !(tempLine.isPointIsAbove(upperSubset[j])))
                        checker1 = false;
                }
                ++j;
            }
            if(checker1){
                current = i;
                elem = upperSubset[current];
                ans0[ans0N].position = sf::Vector2f(upperSubset[i].getPosition().x+radius,  upperSubset[i].getPosition().y+radius);
                ans0[ans0N].color = sf::Color::Black;
                ++ans0N;
            }
        }
        --counter;
    }

    sf::VertexArray ans1(sf::LineStrip, amount);
    int ans1N = 0;
    ans1[0].position = sf::Vector2f(dot0[0].getPosition().x+radius,  dot0[0].getPosition().y+radius);
    ans1[0].color = sf::Color::Black;
    current = 0;
    elem = lowerSubset[current];
    counter = amount;
    while(abs(elem.getPosition().x-dot0[amount-1].getPosition().x) > eps
          && counter &&
          abs(elem.getPosition().y-dot0[amount-1].getPosition().y) > eps){
        for(int i = current; i < lowerN; ++i){
            Line tempLine(elem,lowerSubset[i]);
            int tempInt = -1, j = 0;
            bool checker1 = true;
            while(j < lowerN && checker1){
                if(j != current && j != i){
                    if(tempInt == -1){
                        if(tempLine.isPointIsAbove(lowerSubset[j]))
                            tempInt = 1;
                        else tempInt = 0;
                    }
                    if((tempInt == 0) && tempLine.isPointIsAbove(lowerSubset[j]))
                        checker1 = false;
                    if((tempInt == 1) && !(tempLine.isPointIsAbove(lowerSubset[j])))
                        checker1 = false;
                }
                ++j;
            }
            if(checker1){
                current = i;
                elem = lowerSubset[current];
                ans1[ans1N].position = sf::Vector2f(lowerSubset[i].getPosition().x+radius,  lowerSubset[i].getPosition().y+radius);
                ans1[ans1N].color = sf::Color::Black;
                ++ans1N;
            }
        }
        --counter;
    }

    sf::VertexArray ans(sf::LineStrip, ans0N+ans1N);
    int ansN = 0;
    for(int i = 0; i < ans0N; ++i){
        ans[i].position = ans0[i].position;
        ans[i].color = sf::Color::Black;
        ++ansN;
    }
    for(int i = 0; i < ans1N; ++i){
        ans[ansN+i].position = ans1[ans1N-1-i].position;
        ans[ansN+i].color = sf::Color::Black;
    }

    return ans;
}
