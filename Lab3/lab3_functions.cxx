#include <SFML/Graphics.hpp>
//#include <iostream>
#include <algorithm>
#include <cmath>
#include "lab3_functions.hxx"
#include "lab3_line.hxx"

void drawDot(sf::RenderWindow& window, sf::Vertex dot){
    sf::CircleShape shape(radius);
    shape.setPosition(sf::Vector2f(dot.position.x - radius, dot.position.y - radius));
    shape.setFillColor(sf::Color::Black);
    window.draw(shape);
}

sf::VertexArray generateDots(){
    srand(time(0));
    sf::VertexArray dot(sf::Points, amount);
    for(int i = 0; i < amount; ++i){
        float a = static_cast<float>(100+rand()%800);
        float b = static_cast<float>(100+rand()%400);
        dot[i].position = sf::Vector2f(a, b);
    }
    return dot;
}

void sortVertexArray(sf::VertexArray& dot0, const int dotN){
    sf::Vertex temp;
    for (int i = 0; i < dotN - 1; ++i) {
        for (int j = 0; j < dotN - i - 1; ++j) {
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
    sortVertexArray(dot0, amount);
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
                ++ans0N;
            }
        }
        --counter;
    }

    sf::VertexArray ans1(sf::LineStrip, amount);
    int ans1N = 1;
    ans1[0].position = sf::Vector2f(lowerSubset[0].position.x,  lowerSubset[0].position.y);
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

float triangleArea(sf::Vertex p1, sf::Vertex p2, sf::Vertex p3){
    float a = sqrt(pow(p2.position.x-p1.position.x, 2)+pow(p2.position.y-p1.position.y, 2));
    float b = sqrt(pow(p3.position.x-p2.position.x, 2)+pow(p3.position.y-p2.position.y, 2));
    float c = sqrt(pow(p1.position.x-p3.position.x, 2)+pow(p1.position.y-p3.position.y, 2));
    float p = (a+b+c)/2;
    return sqrt(p*(p-a)*(p-b)*(p-c));
}
float cosA(sf::Vertex p1, sf::Vertex p2, sf::Vertex p3){
    float c = sqrt(pow(p2.position.x-p1.position.x, 2)+pow(p2.position.y-p1.position.y, 2));
    float a = sqrt(pow(p3.position.x-p2.position.x, 2)+pow(p3.position.y-p2.position.y, 2));
    float b = sqrt(pow(p1.position.x-p3.position.x, 2)+pow(p1.position.y-p3.position.y, 2));
    return (c*c+b*b-a*a)/(2*b*c);
}

void recursive0(const sf::VertexArray dot, const int dotN, sf::VertexArray& ans, int& ansN, const bool checker){
    if(dotN > 2){
        int h = -1;
        float tempArea = -1;
        float biggestArea = -1;
        for(int i = 1; i < dotN - 1; ++i){
            tempArea = triangleArea(dot[0], dot[i], dot[dotN-1]);
            if(biggestArea < tempArea){
                h = i;
                biggestArea = tempArea;
            }
            else if(biggestArea == tempArea){
                float a = cosA(dot[0], dot[h], dot[dotN-1]);
                float b = cosA(dot[0], dot[i], dot[dotN-1]);
                if(a > b){
                    h = i;
                    biggestArea = tempArea;
                }
            }
        }
        ans[ansN].position = dot[h].position;
        ++ansN;

        Line line0(dot[0], dot[h]);
        sf::VertexArray subset0(sf::Points, dotN);
        int sub0N;
        if(checker){
            sub0N = 0;
            for(int i = 0; i < dotN; ++i){
                if(line0.isPointIsAbove(dot[i])){
                    subset0[sub0N] = dot[i];
                    ++sub0N;
                }
            }
        }
        else{
            subset0[0] = dot[0];
            sub0N = 1;
            for(int i = 0; i < dotN; ++i){
                if(!(line0.isPointIsAbove(dot[i]))){
                    subset0[sub0N] = dot[i];
                    ++sub0N;
                }
            }
            subset0[sub0N] = dot[dotN-1];
            ++sub0N;
        }
        recursive0(subset0, sub0N, ans, ansN, checker);

        Line line1(dot[h], dot[dotN-1]);
        sf::VertexArray subset1(sf::Points, dotN);
        int sub1N;
        if(checker){
            sub1N = 0;
            for(int i = 0; i < dotN; ++i){
                if(line1.isPointIsAbove(dot[i])){
                    subset1[sub1N] = dot[i];
                    ++sub1N;
                }
            }
        }
        else{
            subset1[0] = dot[0];
            sub1N = 1;
            for(int i = 0; i < dotN; ++i){
                if(!(line1.isPointIsAbove(dot[i]))){
                    subset1[sub1N] = dot[i];
                    ++sub1N;
                }
            }
            subset1[sub1N] = dot[dotN-1];
            ++sub1N;
        }
        recursive0(subset1, sub1N, ans, ansN, checker);
    }
}
sf::VertexArray recursive(const sf::VertexArray dot){
    sf::VertexArray dot0(sf::Points, amount);
    for(int i = 0; i < amount; ++i)
        dot0[i].position = dot[i].position;
    sortVertexArray(dot0, amount);
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
    recursive0(upperSubset, upperN, ans0, ans0N, true);
    ans0[ans0N].position = sf::Vector2f(upperSubset[upperN-1].position.x,  upperSubset[upperN-1].position.y);
    ++ans0N;

    sf::VertexArray ans1(sf::LineStrip, amount);
    int ans1N = 1;
    ans1[0].position = sf::Vector2f(lowerSubset[0].position.x,  lowerSubset[0].position.y);
    recursive0(lowerSubset, lowerN, ans1, ans1N, false);
    ans1[ans1N].position = sf::Vector2f(lowerSubset[lowerN-1].position.x,  lowerSubset[lowerN-1].position.y);
    ++ans1N;

    sortVertexArray(ans0, ans0N);
    sortVertexArray(ans1, ans1N);

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

void andrewJarvisAnimate(sf::RenderWindow& window, sf::VertexArray dot){
    sf::VertexArray dot0(sf::Points, amount);
    for(int i = 0; i< amount; ++i)
        dot0[i].position = dot[i].position;
    sortVertexArray(dot0, amount);
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
                ++ans0N;
            }
        }
        --counter;
    }

    sf::VertexArray ans1(sf::LineStrip, amount);
    int ans1N = 1;
    ans1[0].position = sf::Vector2f(lowerSubset[0].position.x,  lowerSubset[0].position.y);
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
}
