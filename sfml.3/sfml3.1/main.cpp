#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <algorithm>

void init(sf::ConvexShape &pointer)
{
    pointer.setPointCount(3);
    pointer.setPoint(0, {40, 0});
    pointer.setPoint(1, {-20, -20});
    pointer.setPoint(2, {-20, 20});
    pointer.setPosition({300, 300});
    pointer.setFillColor(sf::Color(0xFF, 0x80, 0x00));
}

float getDt(sf::Clock &clock)
{
    return clock.getElapsedTime().asSeconds();
}

float toDegrees(float radians)
{
    if (radians < 0)
    {
        return float(double(2 * M_PI + radians) * 180.0 / M_PI);
    }
    return float(double(radians) * 180.0 / M_PI);
}

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    mousePosition = {float(event.x), float(event.y)};
}

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseMoved:
            onMouseMove(event.mouseMove, mousePosition);
            break;
        default:
            break;
        }
    }
}

void update(const sf::Vector2f &mousePosition, sf::ConvexShape &pointer, sf::Clock &clock)
{
    const sf::Vector2f delta = mousePosition - pointer.getPosition();
    const float angle = atan2(delta.y, delta.x);
    const float pointerRotation = pointer.getRotation();
    const float time = clock.restart().asSeconds();

    if (toDegrees(angle) > pointerRotation)
    {
        pointer.setRotation(pointerRotation + std::min(toDegrees(angle) - pointerRotation, (float)15) * time);
    }
    else
    {
        pointer.setRotation(pointerRotation - std::min(pointerRotation - toDegrees(angle), (float)15) * time);
    }
}

void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &pointer)
{
    window.clear();
    window.draw(pointer);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::Clock clock;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Pointer follows mouse", sf::Style::Default, settings);

    sf::ConvexShape pointer;
    sf::Vector2f mousePosition;

    init(pointer);

    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(mousePosition, pointer, clock);
        redrawFrame(window, pointer);
    }
}