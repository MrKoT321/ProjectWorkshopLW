#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

void init(sf::ConvexShape &pointer)
{
    pointer.setFillColor(sf::Color(0xFA, 0xC7, 0x48));
    pointer.setPointCount(7);
    pointer.setPoint(0, {40, 0});
    pointer.setPoint(1, {0, -30});
    pointer.setPoint(2, {0, -10});
    pointer.setPoint(3, {-40, -10});
    pointer.setPoint(4, {-40, 10});
    pointer.setPoint(5, {0, 10});
    pointer.setPoint(6, {0, 30});
    pointer.setPosition({300, 300});
}

float toDegrees(float radians)
{
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

void updateRotation(sf::Vector2f mousePosition, sf::ConvexShape &pointer)
{
    const sf::Vector2f delta = mousePosition - pointer.getPosition();
    const float angle = atan2(delta.y, delta.x);
    pointer.setRotation(toDegrees(angle));
}

bool updatePosition(sf::Vector2f mousePosition, sf::ConvexShape &pointer, float time)
{
    const int speed_per_frame = 20;
    sf::Vector2f motion = mousePosition - pointer.getPosition();
    const int motionAbs = sqrt(motion.x * motion.x + motion.y * motion.y);
    if (motionAbs >= speed_per_frame)
    {
        motion.x /= motionAbs;
        motion.y /= motionAbs;
        const float speed = speed_per_frame * time;
        const sf::Vector2f position = pointer.getPosition() + motion * speed;
        pointer.setPosition(position);
        return true;
    }
    pointer.setPosition(mousePosition);
    return false;
}

void update(sf::Vector2f mousePosition, sf::ConvexShape &pointer, float time)
{
    if (updatePosition(mousePosition, pointer, time))
        updateRotation(mousePosition, pointer);
}

void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &pointer)
{
    window.clear(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(pointer);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Pointer to mouse", sf::Style::Default);

    sf::Clock clock;
    sf::ConvexShape pointer;
    sf::Vector2f mousePosition;

    init(pointer);

    while (window.isOpen())
    {
        const float time = clock.restart().asSeconds();
        pollEvents(window, mousePosition);
        update(mousePosition, pointer, time);
        redrawFrame(window, pointer);
    }
}