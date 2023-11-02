#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

struct Cat
{
    int direction = 1;
    sf::Texture texture;
    sf::Sprite img;
    sf::Vector2u size;
    sf::Vector2f position = {300, 300};
};

struct Pointer
{
    sf::Texture texture;
    sf::Sprite img;
    sf::Vector2u size;
    sf::Vector2f position = {600, 400};
};

float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

void initCatTexture(sf::Texture &texture)
{
    if (!texture.loadFromFile("images/cat.png"))
    {
        // error...
        std::cout << "Fail to load image" << std::endl;
        return;
    }
}

void initPointTexture(sf::Texture &texture)
{
    if (!texture.loadFromFile("images/red_pointer.png"))
    {
        // error...
        std::cout << "Fail to load image" << std::endl;
        return;
    }
}

void init(Cat &cat, Pointer &pointer)
{
    initCatTexture(cat.texture);
    cat.img.setTexture(cat.texture);
    cat.size = cat.texture.getSize();
    cat.img.setPosition(cat.position);

    initPointTexture(pointer.texture);
    pointer.img.setTexture(pointer.texture);
    pointer.size = pointer.texture.getSize();
    pointer.img.setPosition({pointer.position.x + pointer.size.x / 2,
                             pointer.position.y + pointer.size.y / 2});
}

void updatePointerPosition(sf::Vector2f mousePosition, Pointer &pointer)
{
    mousePosition.x -= pointer.size.x / 2;
    mousePosition.y -= pointer.size.y / 2;
    pointer.position = mousePosition;
    pointer.img.setPosition(mousePosition);
}

void updateCatPosition(sf::Vector2f catPosition, Cat &cat)
{
    if (cat.direction == -1)
    {
        catPosition.x += cat.size.x / 2;
    }
    else
    {
        catPosition.x -= cat.size.x / 2;
    }
    catPosition.y -= cat.size.y / 2;
    cat.img.setPosition(catPosition);
}

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition, Pointer &pointer)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseButtonReleased:
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                mousePosition = {float(event.mouseButton.x), float(event.mouseButton.y)};
                updatePointerPosition(mousePosition, pointer);
            }
            break;
        default:
            break;
        }
    }
}

void updateRotation(Cat &cat, Pointer pointer)
{
    sf::Vector2f delta;
    if (cat.direction == -1)
    {
        delta = {pointer.position.x - cat.position.x - cat.size.x / 2,
                 pointer.position.y - cat.position.y + cat.size.y / 2};
    }
    else
    {
        delta = {pointer.position.x - cat.position.x + cat.size.x / 2,
                 pointer.position.y - cat.position.y + cat.size.y / 2};
    }
    const float angle = toDegrees(atan2(delta.y, delta.x));
    if (angle < 90 && angle > -90)
    {
        std::cout << cat.direction << std::endl;
        if (cat.direction == -1)
        {
            cat.img.setScale(1, 1);
            cat.position.x += cat.size.x;
            cat.direction = 1;
        }
    }
    else
    {

        if (cat.direction == 1)
        {
            cat.img.setScale(-1, 1);
            cat.position.x -= cat.size.x;
            cat.direction = -1;
        }
    }
}

void updatePosition(Cat &cat, Pointer &pointer, float time)
{
    const int speedPerFrame = 20;
    sf::Vector2f motion = {pointer.position.x - cat.position.x,
                           pointer.position.y - cat.position.y};
    const int motionAbs = std::sqrt(motion.x * motion.x + motion.y * motion.y);
    if (motionAbs >= speedPerFrame)
    {
        motion.x /= motionAbs;
        motion.y /= motionAbs;
        const float speed = speedPerFrame * time;
        cat.position += motion * speed;
        updateCatPosition(cat.position, cat);
    }
}

void update(Cat &cat, Pointer pointer, float time)
{
    updateRotation(cat, pointer);
    updatePosition(cat, pointer, time);
}

void redrawFrame(sf::RenderWindow &window, Cat cat, Pointer pointer)
{
    window.clear(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(pointer.img);
    window.draw(cat.img);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "cat and red pointer", sf::Style::Default, settings);

    sf::Clock clock;
    Cat cat;
    Pointer pointer;
    sf::Vector2f mousePosition;

    init(cat, pointer);

    while (window.isOpen())
    {
        const float time = clock.restart().asSeconds();
        pollEvents(window, mousePosition, pointer);
        update(cat, pointer, time);
        redrawFrame(window, cat, pointer);
    }
}