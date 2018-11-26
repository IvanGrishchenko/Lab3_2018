#ifndef LAB3_FUNCTIONS_HXX_INCLUDED
#define LAB3_FUNCTIONS_HXX_INCLUDED

const int amount = 12;
const float radius = 4;
const float eps = 0.0005;
const unsigned int tests = 10;

void drawDot(sf::RenderWindow& window, sf::Vertex dot, int type);
sf::VertexArray generateDots();

sf::VertexArray andrewJarvis(const sf::VertexArray dot);
void andrewJarvisAnimate(sf::RenderWindow& window, sf::VertexArray dot);

sf::VertexArray recursive(const sf::VertexArray dot);
void recursiveAnimate(sf::RenderWindow& window, sf::VertexArray dot);

#endif // LAB3_FUNCTIONS_HXX_INCLUDED
