#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;
    constexpr float BALL_SIZE = 40;

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Sin Loop");
    sf::Clock clock;
    sf::Clock clockForSin;

    sf::Vector2f position = {10, 350};
    float speedX = 100.f;

    sf::CircleShape ball(BALL_SIZE);
    ball.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));

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

        constexpr float amplitudeY = 80.f;
        constexpr float periodY = 2;

        const float dt = clock.restart().asSeconds();
        const float time = clockForSin.getElapsedTime().asSeconds();
        const float wavePhase = time * float(2 * M_PI);
        const float y = 350 + amplitudeY * std::sin(wavePhase / periodY);
        position.x += speedX * dt;
        position.y = y;

        if ((position.x + 2 * BALL_SIZE >= WINDOW_WIDTH) && (speedX > 0))
        {
            speedX = -speedX;
        }
        if ((position.x <= 0) && (speedX < 0))
        {
            speedX = -speedX;
        }

        ball.setPosition(position);

        window.clear();
        window.draw(ball);
        window.display();
    }
}