#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <algorithm>

struct Eye
{
    const int eyeRadius = 20;
    sf::ConvexShape eye;
    sf::Vector2f position;
    sf::Vector2f pathway;
    sf::Vector2f eyeCenter;
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

float getLengthOfVector(sf::Vector2f vector)
{
    return sqrt(std::pow(vector.x, 2) + std::pow(vector.y, 2));
}

float getLengthOfChange(sf::Vector2f position, sf::Vector2f change)
{
    return sqrt(std::pow(position.x - change.x, 2) + std::pow(position.y - change.y, 2));
}

void updateEyeElement(Eye &eye, sf::Vector2f mousePosition)
{
    const int difBetweenEyeAndEyeBorder = 10;
    const sf::Vector2f eyeOffset = toEuclidean(eye.pathway, eye.rotation);
    eye.eye.setPosition(eye.eyeCenter + eyeOffset);
    if ((getLengthOfChange(eye.eyeCenter, mousePosition) + eye.eyeRadius + difBetweenEyeAndEyeBorder) > getLengthOfVector(eyeOffset))
    {
        eye.eye.setPosition(eye.eyeCenter + eyeOffset);
    }
    else
    {
        eye.eye.setPosition(mousePosition);
    }
}

void initEye(Eye &eye)
{
    constexpr int pointCount = 200;
    const sf::Vector2f eyeRadius = {(float)eye.eyeRadius, (float)eye.eyeRadius};

    eye.pathway = {60.f, 170.f};
    eye.position = eye.eyeCenter;

    eye.eye.setFillColor(sf::Color(0xFF, 0x00, 0x00));
    eye.eye.setPosition(eye.eyeCenter);
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
    const sf::Vector2f deltaEye1 = mousePosition - eye1.eyeCenter;
    const sf::Vector2f deltaEye2 = mousePosition - eye2.eyeCenter;
    eye1.rotation = atan2(deltaEye1.y, deltaEye1.x);
    eye2.rotation = atan2(deltaEye2.y, deltaEye2.x);
    updateEyeElement(eye1, mousePosition);
    updateEyeElement(eye2, mousePosition);
    // const sf::Vector2f eyeOffset = toEuclidean(eye1.pathway, eye1.rotation);
    // std::cout << getLengthOfChange(eye1.eyeCenter, mousePosition) << " " << getLengthOfVector(eyeOffset) << std::endl;
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

    eye1.eyeCenter = {350, 400};
    initEye(eye1);
    eye2.eyeCenter = {650, 400};
    initEye(eye2);
    while (window.isOpen())
    {
        sf::Event event;
        pollEvents(window, mousePosition);
        update(mousePosition, eye1, eye2);
        redrawFrame(window, eye1, eye2);
    }
}