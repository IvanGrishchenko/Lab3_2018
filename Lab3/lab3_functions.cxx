#include <SFML/Graphics.hpp>
//#include <iostream>
#include <algorithm>
#include <cmath>
#include "lab3_functions.hxx"
#include "lab3_line.hxx"
void sortVertexArray(sf::VertexArray& dot0){
    sf::Vertex temp;
    for (int i = 0; i < amount - 1; ++i) {
        for (int j = 0; j < amount - i - 1; ++j) {
            if (dot0[j].position.x > dot0[j + 1].position.x) {
                temp.position = dot0[j].position;
                dot0[j].position = dot0[j + 1].position;
                dot0[j + 1].position = temp.position;
            }
        }
    }}

sf::VertexArray andrewJarvis(const sf::VertexArray dot){
    sf::VertexArray dot0(sf::Points, amount);
    for(int i = 0; i< amount; ++i)
        dot0[i].position = dot[i].position;
    sortVertexArray(dot0);
    Line line0(dot0[0], dot0[amount-1]);

    sf::VertexArray upperSubset(sf::Points, amount);
    sf::VertexArray lowerSubset(sf::Points, amount);
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
    ans0[0].position = sf::Vector2f(upperSubset[0].position.x,  upperSubset[0].position.y);
    ans0[0].color = sf::Color::Black;
    int current = 0;
    sf::Vertex elem = upperSubset[current];
    int counter = amount;
    while((abs(elem.position.x-dot0[amount-1].position.x) > eps
          ||
          abs(elem.position.y-dot0[amount-1].position.y) > eps) && counter){
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
                    else if(tempLine.isPointIsAbove(upperSubset[j]) != tempInt)
                        checker1 = false;
                }
                ++j;
            }
            if(checker1){
                current = i;
                elem = upperSubset[current];
                ans0[ans0N].position = sf::Vector2f(elem.position.x, elem.position.y);
                ans0[ans0N].color = sf::Color::Black;
                ++ans0N;
            }
        }
        --counter;
    }

    sf::VertexArray ans1(sf::LineStrip, amount);
    int ans1N = 1;
    ans1[0].position = sf::Vector2f(lowerSubset[0].position.x,  lowerSubset[0].position.y);
    ans1[0].color = sf::Color::Black;
    current = 0;
    elem = lowerSubset[current];
    counter = amount;
    while((abs(elem.position.x-dot0[amount-1].position.x) > eps
          ||
          abs(elem.position.y-dot0[amount-1].position.y) > eps) && counter){
        for(int i = current+1; i < lowerN; ++i){
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
                    else if(tempLine.isPointIsAbove(lowerSubset[j]) != tempInt)
                        checker1 = false;
                }
                ++j;
            }
            if(checker1){
                current = i;
                elem = lowerSubset[current];
                ans1[ans1N].position = sf::Vector2f(elem.position.x, elem.position.y);
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
sf::VertexArray fortune(const sf::VertexArray dot){
    sf::VertexArray ans(sf::Lines, 6*amount-4);
    //int ansN = 8;
    for(int i = 0; i < 6*amount-4; ++i)
        ans[i].color = sf::Color::Black;
    ans[0].position = sf::Vector2f(100, 100);
    ans[1].position = sf::Vector2f(900, 100);
    ans[2].position = sf::Vector2f(900, 100);
    ans[3].position = sf::Vector2f(900, 500);
    ans[4].position = sf::Vector2f(900, 500);
    ans[5].position = sf::Vector2f(100, 500);
    ans[6].position = sf::Vector2f(100, 500);
    ans[7].position = sf::Vector2f(100, 100);
    return ans;
}

float triangleArea(sf::Vertex p1, sf::Vertex p2, sf::Vertex p3){
    float a = sqrt(pow(p2.position.x-p1.position.x, 2)+pow(p2.position.y-p1.position.y, 2));
    float b = sqrt(pow(p3.position.x-p2.position.x, 2)+pow(p3.position.y-p2.position.y, 2));
    float c = sqrt(pow(p1.position.x-p3.position.x, 2)+pow(p1.position.y-p3.position.y, 2));
    float p = (a+b+c)/2;
    return sqrt(p*(p-a)*(p-b)*(p-c));
}

void recursive0(const sf::VertexArray dot, sf::VertexArray& ans, int& ansN){

}
sf::VertexArray recursive(const sf::VertexArray dot){
        sf::VertexArray dot0(sf::Points, amount);
    for(int i = 0; i< amount; ++i)
        dot0[i].position = dot[i].position;
    sortVertexArray(dot0);
    Line line0(dot0[0], dot0[amount-1]);

    sf::VertexArray upperSubset(sf::Points, amount);
    sf::VertexArray lowerSubset(sf::Points, amount);
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
    /*
    sf::VertexArray ans0(sf::LineStrip, amount);
    int ans0N = 1;
    ans0[0].position = sf::Vector2f(upperSubset[0].position.x,  upperSubset[0].position.y);
    ans0[0].color = sf::Color::Black;
    recursive0(upperSubset, ans0, ans0N);

    sf::VertexArray ans1(sf::LineStrip, amount);
    int ans1N = 1;
    ans1[0].position = sf::Vector2f(lowerSubset[0].position.x,  lowerSubset[0].position.y);
    ans1[0].color = sf::Color::Black;
    recursive0(upperSubset, ans1, ans1N);

    sortVertexArray(ans0);
    sortVertexArray(ans1);

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
    */
//*
    sf::VertexArray ans(sf::LineStrip, upperN);
    for(int i = 0; i < upperN; ++i){
        ans[i].position = upperSubset[i].position;
        ans[i].color = sf::Color::Black;
    }
//*/
    return ans;
}
