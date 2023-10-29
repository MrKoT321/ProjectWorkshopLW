#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

struct Cat
{
    const int WIDTH = 60;
    const int HEIGHT = 55;
    sf::Texture texture;
    sf::Sprite img;
    sf::Vector2f position = {300, 300};
};

struct Pointer
{
    sf::Texture texture;
    sf::Sprite img;
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
    cat.img.setPosition(cat.position);
    initPointTexture(pointer.texture);
    pointer.img.setTexture(pointer.texture);
    pointer.img.setPosition(pointer.position);
}

// void onMouseClick(sf::Event::MouseButtonReleased &event, sf::Vector2f &mousePosition)
// {
//     mousePosition = {float(event.x), float(event.y)};
// }

void updatePointerPosition(sf::Vector2f mousePosition, Pointer &pointer)
{
    mousePosition.x -= 16;
    mousePosition.y -= 16;
    pointer.position = mousePosition;
    pointer.img.setPosition(mousePosition);
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
    const sf::Vector2f catPosition = cat.img.getPosition();
    const sf::Vector2f delta = {pointer.position.x - catPosition.x,
                                pointer.position.y - catPosition.y};
    const float angle = toDegrees(atan2(delta.y, delta.x));
    if (angle < 90 && angle > -90)
    {
        cat.img.setScale(1, 1);
    }
    else
    {
        cat.img.setScale(-1, 1);
    }
}

bool updatePosition(Cat &cat, Pointer &pointer, float time)
{
    const int speed_per_frame = 20;
    sf::Vector2f motion = pointer.position - cat.img.getPosition();
    const int motionAbs = sqrt(motion.x * motion.x + motion.y * motion.y);
    if (motionAbs >= speed_per_frame)
    {
        motion.x /= motionAbs;
        motion.y /= motionAbs;
        const float speed = speed_per_frame * time;
        const sf::Vector2f position = cat.img.getPosition() + motion * speed;
        cat.img.setPosition(position);
        return true;
    }
    cat.img.setPosition(pointer.position);
    return false;
}

// void updateCenterPosition(Cat &cat)
// {
//     const sf::Vector2f currentPosition = cat.img.getPosition();
//     const float angle = cat.img.getRotation() * M_PI / 180;
//     cat.position.x = currentPosition.x + cat.WIDTH * std::cos(angle);
//     cat.position.y = currentPosition.y + cat.HEIGHT * std::sin(angle);
// }

void update(Cat &cat, Pointer pointer, float time)
{
    // updateCenterPosition(cat);
    if (updatePosition(cat, pointer, time))
        updateRotation(cat, pointer);
}

void redrawFrame(sf::RenderWindow &window, Cat cat, Pointer pointer)
{
    window.clear(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(cat.img);
    window.draw(pointer.img);

    // sf::RectangleShape shape;
    // shape.setSize({3, 3});
    // shape.setPosition(cat.position);
    // shape.setFillColor(sf::Color(0x00, 0x00, 0xFF));
    // window.draw(shape);

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
        "cat to mouse", sf::Style::Default, settings);

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