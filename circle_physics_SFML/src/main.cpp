#include "SFML/Graphics.hpp"
#include "Circle.h"

#include <array>

bool isSpawning = 1;

#ifdef CONFIG_DIST // Defined only in distrobution configuration!
#include <Windows.h>
#define EntryPoint int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
#else
#define EntryPoint int main()
#endif

EntryPoint
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Circle Physics", sf::Style::Titlebar | sf::Style::Close);

    int lowFPSbuffer = 0;

    sf::CircleShape scircle(10, 32);
    scircle.setFillColor(sf::Color::White);

    sf::RectangleShape rectanglebg(sf::Vector2f(800, 800));
    rectanglebg.setFillColor(sf::Color(0, 0, 0, 100));

    sf::Clock deltaClock;

    Circle* allCircles = new Circle[MAX_CIRCLES];
    int numCircles = 0;

    while (window.isOpen())
    {
        sf::Time dt = deltaClock.restart();
        sf::Event e;
        while (window.pollEvent(e))
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                CollisionNoSelf(allCircles, numCircles, dt.asSeconds() * 1000,
                    { ((float)sf::Mouse::getPosition(window).x / window.getSize().x) * WORLD_SIZE_X,
                      ((float)sf::Mouse::getPosition(window).y / window.getSize().y) * WORLD_SIZE_Y },
                    1000);

            if (e.type == sf::Event::Closed)
            {
                window.close();
                break;
            }
        }

        window.draw(rectanglebg);

        if (numCircles < MAX_CIRCLES && dt.asMilliseconds() < 18 && isSpawning)
        {
            allCircles[numCircles] = Circle({ 500, 520 }, { 2, 0 }, 100);
            numCircles++;
        }

        isSpawning = true || (dt.asMilliseconds() < 100);

        for (int i = 0; i < numCircles; i++)
            allCircles[i].Update(allCircles, numCircles, (float)dt.asMilliseconds());

        for (int i = 0; i < numCircles; i++)
        {
            scircle.setPosition(
                (allCircles[i].Position.x / WORLD_SIZE_X) * 800,
                (allCircles[i].Position.y / WORLD_SIZE_Y) * 800
            );
            scircle.setRadius(((float)allCircles[i].Radius / WORLD_SIZE_X) * 800);
            scircle.setFillColor(sf::Color(
                (int)((allCircles[i].Position.x / WORLD_SIZE_X) * 255),
                (int)((allCircles[i].Position.y / WORLD_SIZE_Y) * 255),
                255
            ));

            window.draw(scircle);
        }

        window.display();
    }

    delete[] allCircles;
    return 0;
}
