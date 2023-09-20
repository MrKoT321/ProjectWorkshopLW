#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({720, 600}), "Rectangle and Circle");

    window.clear();

    sf::CircleShape letD1(190);
    letD1.setPosition({300, 120});
    letD1.setFillColor(sf::Color{0x80, 0x80, 0x80});
    window.draw(letD1);

    sf::CircleShape letD2(160);
    letD2.setPosition({330, 150});
    letD2.setFillColor(sf::Color{0x0, 0x0, 0x0});
    window.draw(letD2);

    sf::RectangleShape letD3;
    letD3.setSize({190, 380});
    letD3.setPosition({300, 120});
    letD3.setFillColor(sf::Color{0x0, 0x0, 0x0});
    window.draw(letD3);

    sf::RectangleShape letD4;
    letD4.setSize({30, 380});
    letD4.setPosition({460, 120});
    letD4.setFillColor(sf::Color{0x80, 0x80, 0x80});
    window.draw(letD4);

    sf::RectangleShape letV1;
    letV1.setSize({30, 380});
    letV1.setRotation(-10);
    letV1.setPosition({270, 120});
    letV1.setFillColor(sf::Color{0x80, 0x80, 0x80});
    window.draw(letV1);

    sf::RectangleShape letV2;
    letV2.setSize({30, 380});
    letV2.setRotation(10);
    letV2.setPosition({404, 120});
    letV2.setFillColor(sf::Color{0x80, 0x80, 0x80});
    window.draw(letV2);

    sf::RectangleShape letF1;
    letF1.setSize({30, 380});
    letF1.setPosition({60, 120});
    letF1.setFillColor(sf::Color{0x80, 0x80, 0x80});
    window.draw(letF1);

    sf::RectangleShape letF2;
    letF2.setSize({190, 30});
    letF2.setPosition({60, 120});
    letF2.setFillColor(sf::Color{0x80, 0x80, 0x80});
    window.draw(letF2);

    sf::RectangleShape letF3;
    letF3.setSize({130, 30});
    letF3.setPosition({60, 250});
    letF3.setFillColor(sf::Color{0x80, 0x80, 0x80});
    window.draw(letF3);

    window.display();

    sf::sleep(sf::seconds(3));
}