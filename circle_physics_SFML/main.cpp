#include "SFML/Graphics.hpp"
#include "Circle.h"
#include <iostream>

bool isSpawning = 1;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Circle Physics", sf::Style::Titlebar | sf::Style::Close);

    int lowFPSbuffer = 0;

    sf::CircleShape scircle(10, 32);
    scircle.setFillColor(sf::Color::White);
    sf::Clock deltaClock;

    Circle allCircles[5000];
    int numCircles = 0;

    while (window.isOpen())
    {
        sf::Time dt = deltaClock.restart();
        sf::Event e;
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
            {
                window.close();
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                CollisionNoSelf(allCircles, numCircles, dt.asSeconds() * 1000,
                    { ((sf::Mouse::getPosition(window).x) * 1.0f / (window.getSize().x * 1.0f)) * worldSizeX,
                    ((sf::Mouse::getPosition(window).y) * 1.0f / (window.getSize().y) * 1.0f)* worldSizeY },
                    500);
            }
        }

       window.clear();

       if (numCircles < 5000 and dt.asMilliseconds() < 18 and isSpawning)
       {
           Circle newCircle({ 500, 520 }, { 2, 0 }, 100);
           allCircles[numCircles] = newCircle;
           numCircles++;
           lowFPSbuffer = 0;
       }

       if (dt.asMilliseconds() > 18 and isSpawning)
       { 
           lowFPSbuffer++;
           if (lowFPSbuffer > 10)
           {
               isSpawning = 0;
           }
       }

       for (int i = 0; i < numCircles; i++)
       {
           allCircles[i].Update(allCircles, numCircles, dt.asMilliseconds());
       }
       for (int i = 0; i < numCircles; i++)
       {
           scircle.setPosition((allCircles[i].pos.x / worldSizeX) * 800, (allCircles[i].pos.y / worldSizeY) * 800);
           scircle.setRadius(((allCircles[i].rad) * 1.0f / worldSizeX * 1.0f) * 800.0f);
           scircle.setFillColor(sf::Color((allCircles[i].pos.x / worldSizeX) * 255, (allCircles[i].pos.y / worldSizeY) * 255, 255));
           window.draw(scircle);
       }
       window.display();
    }

    return 0;
}