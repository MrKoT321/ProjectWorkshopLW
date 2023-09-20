#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Rectangle and Circle");

    window.clear();

    sf::RectangleShape wall;
    wall.setSize({700, 290});
    wall.setPosition({50, 300});
    wall.setFillColor(sf::Color{0x80, 0x80, 0x80});
    window.draw(wall);

    sf::RectangleShape door;
    door.setSize({100, 230});
    door.setPosition({100, 360});
    door.setFillColor(sf::Color{0x0, 0x80, 0x80});
    window.draw(door);

    sf::CircleShape letD2(160);
    letD2.setPosition({330, 150});
    letD2.setFillColor(sf::Color{0x0, 0x0, 0x0});
    window.draw(letD2);

    window.display();

    sf::sleep(sf::seconds(3));
}