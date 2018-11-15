#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include <cmath>
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
    ans[0].color = sf::Color::Blue;

    Line line0(dot0[0], dot0[amount-1]);
    sf::CircleShape upperSubset[amount];
    sf::CircleShape lowerSubset[amount];
    int upperN = 0;
    int lowerN = 0;
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

    //for(int i = 0; i < upperN; ++i){
        //ans[i].position = sf::Vector2f(upperSubset[i].getPosition().x+radius,
                                       //upperSubset[i].getPosition().y+radius);
        //ans[i].color = sf::Color::Black;
    //}

    int current = 0;
    sf::CircleShape elem = upperSubset[current];
    /*
    std::cout<<elem.getPosition().x-dot0[amount-1].getPosition().x <<std::endl;
    if(abs(elem.getPosition().x-dot0[amount-1].getPosition().x) > eps)
        std::cout<<"+"<<std::endl;
    else std::cout<<"-"<<std::endl;
    if(i < upperN)
        std::cout<<"+"<<std::endl;
    else std::cout<<"-"<<std::endl;
    if(abs(elem.getPosition().y-dot0[amount-1].getPosition().y) > eps)
        std::cout<<"+"<<std::endl;
    else std::cout<<"-"<<std::endl;
    */
    int myDebug0 = 0;
    while(abs(elem.getPosition().x-dot0[amount-1].getPosition().x) > eps
          && myDebug0 < 10 &&
          abs(elem.getPosition().y-dot0[amount-1].getPosition().y) > eps){
        for(int i = current + 1; i < upperN; ++i){
            Line tempLine(elem,upperSubset[i]);
            int tempInt = -1, j = current;
            bool checker1 = true;
            while(j < upperN && checker1){
                if(j != current && j != i){
                    if(tempInt == -1){
                        if(tempLine.isPointIsAbove(upperSubset[j]))
                            tempInt = 1;
                        else tempInt = 0;
                    }
                    std::cout<<tempInt<<std::endl;
                    if(tempLine.isPointIsAbove(upperSubset[j]))
                        std::cout<<"+"<<std::endl;
                    else std::cout<<"-"<<std::endl;
                    std::cout<<std::endl;
                    std::cout<<std::endl;
                    if((tempInt == 0) && tempLine.isPointIsAbove(upperSubset[j]))
                        checker1 = false;
                    if((tempInt == 1) && !(tempLine.isPointIsAbove(upperSubset[j])))
                        checker1 = false;
                }
                ++j;
            }
            std::cout<<"???"<<std::endl;
            if(checker1){
                current = i;
                elem = upperSubset[current];
                ans[ansN].position = sf::Vector2f(upperSubset[i].getPosition().x+radius,  upperSubset[i].getPosition().y+radius);
                ans[ansN].color = sf::Color::Blue;
                ++ansN;
            }
        }
        myDebug0++;
    }

    //current = 0;
    //while(lowerSubset[current].getPosition().x-dot0[amount - 1].getPosition().x > eps
          //&&
          //lowerSubset[current].getPosition().y-dot0[amount - 1].getPosition().y > eps){

    //}
    //for(int i = 0; i < upperN; ++i){

    //}
    //for(int i = 0; i < lowerN; ++i){

    //}
    return ans;
}
