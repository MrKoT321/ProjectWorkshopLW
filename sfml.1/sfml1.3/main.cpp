#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 700}), "House");

    window.clear();

    sf::RectangleShape wall;
    wall.setSize({700, 290});
    wall.setPosition({50, 400});
    wall.setFillColor(sf::Color{0x96, 0x4f, 0x0});
    window.draw(wall);

    sf::RectangleShape door;
    door.setSize({120, 230});
    door.setPosition({140, 460});
    door.setFillColor(sf::Color{0x0, 0x0, 0x0});
    window.draw(door);

    sf::ConvexShape roof;
    roof.setPosition({400, 250});
    roof.setPointCount(4);
    roof.setPoint(0, {-250, 0});
    roof.setPoint(1, {+250, 0});
    roof.setPoint(2, {+400, 150});
    roof.setPoint(3, {-400, 150});
    roof.setFillColor(sf::Color{0x8b, 0x0, 0x0});
    window.draw(roof);

    sf::RectangleShape pipe1;
    pipe1.setSize({80, 125});
    pipe1.setPosition({500, 200});
    pipe1.setFillColor(sf::Color{0x49, 0x42, 0x3b});
    window.draw(pipe1);

    sf::RectangleShape pipe2;
    pipe1.setSize({110, 75});
    pipe1.setPosition({485, 150});
    pipe1.setFillColor(sf::Color{0x49, 0x42, 0x3b});
    window.draw(pipe1);

    sf::CircleShape cloud1(30);
    cloud1.setPosition({530, 95});
    cloud1.setFillColor(sf::Color{0x80, 0x80, 0x80});
    window.draw(cloud1);

    sf::CircleShape cloud2(35);
    cloud2.setPosition({545, 65});
    cloud2.setFillColor(sf::Color{0x80, 0x80, 0x80});
    window.draw(cloud2);

    sf::CircleShape cloud3(40);
    cloud3.setPosition({560, 29});
    cloud3.setFillColor(sf::Color{0x80, 0x80, 0x80});
    window.draw(cloud3);

    sf::CircleShape cloud4(45);
    cloud4.setPosition({575, 0});
    cloud4.setFillColor(sf::Color{0x80, 0x80, 0x80});
    window.draw(cloud4);

    window.display();

    sf::sleep(sf::seconds(3));
}