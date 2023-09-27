#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>

int main()
{
    constexpr int pointCount = 200;
    sf::Vector2f roseRadius = {200.f, 200.f};
    sf::Vector2f roseRoadRadius = {200.f, 100.f};
    sf::Vector2f roseStartPoint = {400.f, 300.f};
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({800, 600}), "Polar Rose",
        sf::Style::Default, settings);

    sf::ConvexShape rose;
    rose.setFillColor(sf::Color(0xAA, 0xAA, 0x80));

    rose.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = sf::Vector2f{
            roseRadius.x * std::cos(6 * angle) * std::cos(angle),
            roseRadius.y * std::cos(6 * angle) * std::sin(angle)};
        rose.setPoint(pointNo, point);
    }

    float pointRoad = 0;
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
        float angle = float(2 * M_PI * pointRoad) / float(pointCount);
        rose.setPosition({roseStartPoint.x + roseRoadRadius.x * std::cos(angle),
                          roseStartPoint.y + roseRoadRadius.y * std::sin(angle)});
        pointRoad += 0.1;

        window.clear();
        window.draw(rose);
        window.display();
    }
}