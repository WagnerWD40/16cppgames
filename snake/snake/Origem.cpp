#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

int rows = 30, columns = 20;
int size = 16;
int width = size * rows;
int height = size * columns;

int direction, snakeSize = 4;

struct Snake
{
    int x, y;
} snake[100];

struct Fruit
{
    int x, y;
} fruit;

void Tick()
{
    for (int i = snakeSize; i > 0; --i)
    {
        snake[i].x = snake[i - 1].x;
        snake[i].y = snake[i - 1].y;
    }

    if (direction == 0)
    {
        snake[0].y += 1;

    }

    if (direction == 1)
    {
        snake[0].x -= 1;
    }

    if (direction == 2)
    {
        snake[0].x += 1;
    }

    if (direction == 3)
    {
        snake[0].y -= 1;
    }

    if ((snake[0].x == fruit.x) && (snake[0].y == fruit.y))
    {
        snakeSize++;
        fruit.x = rand() % rows;
        fruit.y = rand() % columns;
    }

    if (snake[0].x > rows)
    {
        snake[0].x = 0;
    }

    if (snake[0].x < 0)
    {
        snake[0].x = rows;
    }

    if (snake[0].y > columns)
    {
        snake[0].y = 0;
    }

    if (snake[0].y < 0)
    {
        snake[0].y = columns;
    }

    for (int i = 1; i < snakeSize; i++)
    {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
        {
            snakeSize = i;
        }
    }
}

int main()
{
    srand(time(0));

    RenderWindow window(VideoMode(width, height), "Snake Game!");

    Texture backgroundTexture, snakeTexture, fruitTexture;

    backgroundTexture.loadFromFile("images/white.png");
    snakeTexture.loadFromFile("images/red.png");
    fruitTexture.loadFromFile("images/green.png");

    Sprite backgroundSprite(backgroundTexture);
    Sprite snakeSprite(snakeTexture);
    Sprite fruitSprite(fruitTexture);

    Clock clock;

    float timer = 0.f, delay = 0.1f;

    fruit.x = 10;
    fruit.y = 10;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            direction = 1;
        }

        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            direction = 2;
        }

        if (Keyboard::isKeyPressed(Keyboard::Up))
        {
            direction = 3;
        }

        if (Keyboard::isKeyPressed(Keyboard::Down))
        {
            direction = 0;
        }

        if (timer > delay)
        {
            timer = 0;
            Tick();
        }

        ///// Draw /////

        window.clear();


        // Draw background
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                backgroundSprite.setPosition(i * size, j * size);
                window.draw(backgroundSprite);
            }
        }

        // Draw the Snake
        for (int i = 0; i < snakeSize; i++)
        {
            snakeSprite.setPosition(snake[i].x * size, snake[i].y * size);
            window.draw(snakeSprite);
        }

        fruitSprite.setPosition(fruit.x * size, fruit.y * size);
        window.draw(fruitSprite);

        window.display();
    }

    return 0;
}