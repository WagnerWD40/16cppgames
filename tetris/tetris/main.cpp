#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
using namespace sf;

const int M = 20;
const int N = 10;

int field[M][N] = { 0 };

struct Point
{
    int x, y;
} a[4], b[4];

int figures[7][4] =
{
    1, 3, 5, 7, // I
    2, 4, 5, 7, // Z
    3, 5, 4, 6, // S
    3, 5, 4, 7, // T
    2, 3, 5, 7, // L
    3, 5, 7, 6, // J
    2, 3, 4, 5, // O
};

bool check()
{
    for (int i = 0; i < 4; i++)
    {
        if (a[i].x < 0 || a[i].x >= N || a[i].y >= M)
        {
            return false;
        }
        else if (field[a[i].y][a[i].x])
        {
            return false;
        }
    }

    return true;
}

int main()
{
    srand(time(0));

    RenderWindow window(VideoMode(320, 480), "Tetris");

    Texture texture1, texture2, texture3;
    texture1.loadFromFile("images/tiles.png");
    texture2.loadFromFile("images/background.png");
    texture3.loadFromFile("images/frame.png");

    Sprite sprite(texture1);
    Sprite background(texture2);
    Sprite frame(texture3);

    int dx = 0;
    bool rotate = false;
    int colorNum = 1;
    float timer = 0.f;
    float delay = 0.3f;

    Clock clock;

    a[0].x = 0, a[0].y = 1;
    a[1].x = 1, a[1].y = 1;
    a[2].x = 1, a[2].y = 2;
    a[3].x = 1, a[3].y = 3;

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

            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Up)
                {
                    rotate = true;
                }

                else if (event.key.code == Keyboard::Left)
                {
                    dx = -1;
                }

                else if (event.key.code == Keyboard::Right)
                {
                    dx = 1;
                }
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Down))
        {
            delay = 0.05;
        }

        //// <- Move -> ////
        for (int i = 0; i < 4; i++)
        {
            b[i] = a[i];
            a[i].x += dx;
        }

        if (!check())
        {
            for (int i = 0; i < 4; i++)
            {
                a[i] = b[i];
            }
        }

        ////// Rotate //////
        if (rotate)
        {
            Point point = a[1]; // center of rotation

            for (int i = 0; i < 4; i++)
            {
                int x = a[i].y - point.y;
                int y = a[i].x - point.x;

                a[i].x = point.x - x;
                a[i].y = point.y + y;
            }

            if (!check())
            {
                for (int i = 0; i < 4; i++)
                {
                    a[i] = b[i];
                }
            }
        }

        ////// Tick //////
        if (timer > delay)
        {
            for (int i = 0; i < 4; i++)
            {
                b[i] = a[i];
                a[i].y += 1;
            }

            if (!check())
            {
                for (int i = 0; i < 4; i++)
                {
                    field[b[i].y][b[i].x] = colorNum;
                }

                colorNum = 1 + rand() % 7;

                int n = rand() % 7;

                for (int i = 0; i < 4; i++)
                {
                    a[i].x = figures[n][i] % 2;
                    a[i].y = figures[n][i] / 2;
                }
            }

            timer = 0;
        }

        ////// check lines //////

        int k = M - 1;

        for (int i = M - 1; i > 0; i--)
        {
            int count = 0;

            for (int j = 0; j < N; j++)
            {
                if (field[i][j])
                {
                    count++;
                }

                field[k][j] = field[i][j];
            }

            if (count < N)
            {
                k--;
            }
        }
         
        dx = 0;
        rotate = false;
        delay = 0.3;

        ////// draw //////

        window.clear(Color::White);
        window.draw(background);
        std::cout << "lolada";

        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (field[i][j] == 0) {
                    continue;
                }

                sprite.setTextureRect(IntRect(field[i][j] * 18, 0, 18, 18));
                sprite.setPosition(j * 18, i * 18);
                sprite.move(28, 31); // offset
                window.draw(sprite);
            }
        }

        for (int i = 0; i < 4; i++)
        {
            sprite.setTextureRect(IntRect(colorNum * 18, 0, 16, 18));
            sprite.setPosition(a[i].x * 18, a[i].y * 18);
            sprite.move(28, 31); // offset
            window.draw(sprite);
        }

        window.draw(frame);
        window.display();
    }

	return 0;
}