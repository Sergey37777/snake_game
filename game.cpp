//
// Created by Сергей Ляпин on 10.01.2022.
//
#include <iostream>
#include <ncurses.h>


using namespace std;

bool game_over;

const int width = 20;
const int height = 20;
int x, y, fruit_x, fruit_y, score;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;
int kbhit(void)
{
    int ch = getch();

    if (ch != ERR) {
        ungetch(ch);
        return 1;
    } else {
        return 0;
    }
}

void Setup()
{
    game_over = false;
    dir = STOP;
    x = width / 2 - 1;
    y = height / 2 - 1;
    fruit_x = rand() % width;
    fruit_y = rand() % height;
    score = 0;
}

void Draw()
{
    system("clear");
    for (int i = 0; i < width + 1; i++)
        cout << '#';
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0 || j == width-1) {
                cout << '#';
            }
            if (i == y && j == x)
                cout << '0';
            else if (i == fruit_y && j == fruit_x)
            {
                cout << 'F';
            }
            else
                cout << ' ';
        }
        cout << endl;
    }

    for (int i = 0; i < width + 1; i++)
        cout << '#';
    cout << endl;
    cout << "Score: " << score << endl;
}

void Input()
{
    initscr();
    refresh();
    if (kbhit())
    {
        switch (getch())
        {
            case 'a':
                dir = LEFT;
                endwin();
                break;
            case 'd':
                dir = RIGHT;
                endwin();
                break;
            case 'w':
                dir = UP;
                endwin();
                break;
            case 's':
                dir = DOWN;
                endwin();
                break;
            case 'x':
                game_over = true;
                endwin();
                break;
        }
    }
}

void Logic()
{
    switch (dir)
    {
        case LEFT:
            x-=1;
            cout << x;
            break;
        case RIGHT:
            x+=1;
            break;
        case UP:
            y-=1;
            break;
        case DOWN:
            y+=1;
            break;
    }

    if (x > width || x < 0 || y > height || y < 0)
        game_over = true;
    if (x == fruit_x && y == fruit_y)
    {
        score += 10;
        fruit_x = rand() % width;
        fruit_y = rand() % height;
    }
}

int main()
{
    Setup();
    while (!game_over)
    {
        Draw();
        Input();
        Logic();
    }

    return 0;
}