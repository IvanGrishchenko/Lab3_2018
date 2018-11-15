#include <SFML/Graphics.hpp>
#include <algorithm>
#include "lab3_functions.hxx"
#include "lab3_line.hxx"

sf::VertexArray andrewJarvis(const sf::CircleShape dot[]){
    sf::VertexArray ans(sf::LineStrip, amount);
    int ansN = 1;

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

    ans[0].position = sf::Vector2f(dot0[0].getPosition().x+radius,  dot0[0].getPosition().y+radius);
    ans[0].color = sf::Color::Black;

    Line line0(dot0[0], dot0[amount-1]);
    sf::CircleShape upperSubset[amount];
    sf::CircleShape lowerSubset[amount];
    int upperN = 0;
    int lowerN = 0;
    for(int i = 0; i < amount; ++i){
        if(line0.isPointIsAbove(dot0[i])){
            lowerSubset[lowerN] = dot0[i];
            ++lowerN;
        }
        else{
            upperSubset[upperN] = dot0[i];
            ++upperN;
        }
    }
    for(int i = 0; i < upperN; ++i){
        ans[i].position = sf::Vector2f(upperSubset[i].getPosition().x+radius, upperSubset[i].getPosition().y+radius);
        ans[i].color = sf::Color::Black;
    }

    int endOfLine = 0;
    bool checker0 = true;
    while(upperSubset[endOfLine].getPosition().x-dot0[amount - 1].getPosition().x >= eps
          && checker0 &&
          upperSubset[endOfLine].getPosition().y-dot0[amount - 1].getPosition().y >= eps){
        for(int i = 0; i < upperN; ++i){
            if(i != endOfLine){
                Line tempLine(upperSubset[endOfLine],upperSubset[i]);
                int tempInt = -1, j = 0;
                bool checker1 = true;
                while(j < upperN && checker1){
                    if(j != endOfLine && j != i){
                        if(tempInt == -1){
                            if(tempLine.isPointIsAbove(upperSubset[j]))
                                tempInt = 1;
                            else tempInt = 0;
                        }
                        //if((tempInt == 0)&&tempLine.isPointIsAbove(upperSubset[j]))
                            //checker1 = false;
                        //if((tempInt == 1)&&!(tempLine.isPointIsAbove(upperSubset[j])))
                            //checker1 = false;
                    }
                    ++j;
                }
                if(checker1){
                    endOfLine = i;
                    ans[ansN].position = sf::Vector2f(upperSubset[i].getPosition().x+radius,  upperSubset[i].getPosition().y+radius);
                    ans[ansN].color = sf::Color::Black;
                    ++ansN;
                }
            }
        }
        checker0 = false;

    }
    //endOfLine = 0;
    //while(lowerSubset[endOfLine].getPosition().x-dot0[amount - 1].getPosition().x >= eps
          //&&
          //lowerSubset[endOfLine].getPosition().y-dot0[amount - 1].getPosition().y >= eps){

    //}
    //for(int i = 0; i < upperN; ++i){

    //}
    //for(int i = 0; i < lowerN; ++i){

    //}



/*
    ans[0].position = sf::Vector2f(dot0[0].getPosition().x+radius, dot0[0].getPosition().y+radius);
    ans[0].color = sf::Color::Black;
    ans[1].position = sf::Vector2f(200, 10);
    ans[1].color = sf::Color::Black;

    ans[2].position = sf::Vector2f(300, 50);
    ans[2].color = sf::Color::Black;
    ans[3].position = sf::Vector2f(400, 20);
    ans[3].color = sf::Color::Black;*/

    return ans;
}
