#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>

int main()
{
    constexpr int pointCount = 100;
    constexpr float circleRadius = 200;

    sf::RenderWindow window(sf::VideoMode({800, 600}), "Ellipse");

    sf::ConvexShape shape;
    shape.setPosition({400, 320});
    shape.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));

    shape.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = sf::Vector2f{
            circleRadius * std::sin(angle),
            circleRadius * std::cos(angle)};
        shape.setPoint(pointNo, point);
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
}