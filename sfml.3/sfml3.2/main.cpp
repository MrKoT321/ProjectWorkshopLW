#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

struct Eye
{
    const int eyeRadius = 20;
    sf::ConvexShape eye;
    sf::Vector2f position;
    sf::Vector2f pathway;
    float rotation = 0;
};

sf::Vector2f toEuclidean(sf::Vector2f pathway, float angle)
{
    return {
        pathway.x * cos(angle),
        pathway.y * sin(angle)};
}

float toDegrees(float radius)
{
    return float(double(radius) * 180.0 / M_PI);
}

void updateEyeElement(Eye &eye)
{
    const sf::Vector2f eyeOffset = toEuclidean(eye.pathway, eye.rotation);
    eye.eye.setPosition(eye.position + eyeOffset);
}

void initEye(Eye &eye)
{
    constexpr int pointCount = 200;
    const sf::Vector2f eyeRadius = {(float)eye.eyeRadius, (float)eye.eyeRadius};

    eye.pathway = {60.f, 170.f};

    eye.eye.setFillColor(sf::Color(0xFF, 0x00, 0x00));
    eye.eye.setPosition(eye.position);
    eye.eye.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = sf::Vector2f{
            eyeRadius.x * std::sin(angle),
            eyeRadius.y * std::cos(angle)};
        eye.eye.setPoint(pointNo, point);
    }
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

void update(const sf::Vector2f &mousePosition, Eye &eye1, Eye &eye2)
{
    const sf::Vector2f deltaEye1 = mousePosition - eye1.position;
    const sf::Vector2f deltaEye2 = mousePosition - eye2.position;
    eye1.rotation = atan2(deltaEye1.y, deltaEye1.x);
    eye2.rotation = atan2(deltaEye2.y, deltaEye2.x);
    updateEyeElement(eye1);
    updateEyeElement(eye2);
}

void drawBackground(sf::RenderWindow &window)
{
    constexpr int pointCount = 200;
    const sf::Vector2f eyeRadius = {90.f, 200.f};

    sf::ConvexShape eyeOrb1;
    sf::ConvexShape eyeOrb2;
    eyeOrb1.setPosition({350, 400});
    eyeOrb2.setPosition({650, 400});

    eyeOrb1.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    eyeOrb2.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));

    eyeOrb1.setPointCount(pointCount);
    eyeOrb2.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = sf::Vector2f{
            eyeRadius.x * std::sin(angle),
            eyeRadius.y * std::cos(angle)};
        eyeOrb1.setPoint(pointNo, point);
        eyeOrb2.setPoint(pointNo, point);
    }
    window.draw(eyeOrb1);
    window.draw(eyeOrb2);
}

void redrawFrame(sf::RenderWindow &window, Eye &eye1, Eye &eye2)
{
    window.clear();
    drawBackground(window);
    window.draw(eye1.eye);
    window.draw(eye2.eye);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 1000;
    constexpr unsigned WINDOW_HEIGHT = 800;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Eye Contact", sf::Style::Default, settings);

    Eye eye1, eye2;
    sf::Vector2f mousePosition;

    eye1.position = {350, 400};
    initEye(eye1);
    eye2.position = {650, 400};
    initEye(eye2);
    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(mousePosition, eye1, eye2);
        redrawFrame(window, eye1, eye2);
    }
}