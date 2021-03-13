#include <iostream>  //for c++
#include <conio.h>   //_kbhit() and _getch();
#include <windows.h> //for Sleep();
using namespace std;

//for border
#define width 50
#define height 20

//for gameover signal
bool gameover = false;
//x and y for snake traveling purpose
//snakefoodx and snakefoody for keeping the food of snake
int x, y, snakefoodx, snakefoody, score;

//user defined datatype
//note : enum replace uppercase with number
enum position
{
    stop = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
position dir;

//body snake
int tailx[100], taily[100];
int ntail;

int set()
{

    gameover = false;
    dir = stop;
    x = width / 2;
    y = height / 2;
    snakefoodx = rand() % width;
    snakefoody = rand() % height;
    score = 0;
}

//for all the diagram like boundry ,snak body and food;
void draw(string name)
{

    system("cls");

    for (int i = 0; i < width; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0 or j == width - 1) //leftmost and rightmost wall
                cout << "#";
            else if (i == y and j == x)
                cout << "O";
            else if (i == snakefoody and j == snakefoodx)
                cout << "@";

            else
            {
                bool print = false;
                for (int k = 0; k < ntail; k++)
                {
                    if (tailx[k] == j and taily[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (print == 0)
                    cout << " ";
            }
        }
        cout << endl;
    }

    for (int i = 0; i < width; i++)
        cout << "#";
    cout << endl;

    cout << name << " score: " << score << endl;
}
int input()
{

    //using _kbhit from conio header file to check if any number is hit
    if (_kbhit())
    {
        //using _getch from conio header file to take single charector from the console
        switch (_getch())
        {

        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'q':
            gameover = true;
            break;

        default:
            break;
        }
    }
}
//movement logic of snake
int logic()
{
    //logic of body movement of snake
    int prevx = tailx[0];
    int prevy = taily[0];
    int prev2x, prev2y;
    tailx[0] = x;
    taily[0] = y;
    for (int i = 1; i < ntail; i++)
    {
        prev2x = tailx[i];
        prev2y = taily[i];

        tailx[i] = prevx;
        taily[i] = prevy;

        prevx = prev2x;
        prevy = prev2y;
    }

    //direction given
    switch (dir)
    {
    case LEFT:
        x--;
        break;

    case RIGHT:
        x++;
        break;

    case UP:
        y--;
        break;

    case DOWN:
        y++;
        break;
    }

    //making logic snake can cross the wall and come out from opposite wall
    if (x > width)
        x = 0;
    else if (x < 0)
        x = width - 1;

    if (y > height)
        y = 0;
    else if (y < 0)
        y = height - 1;

    //logic = snake cannot eat its own tail
    for (int i = 0; i < ntail; i++)
    {
        if (tailx[i] == x and taily[i] == y)
               gameover = true;
        
    }

    if (x == snakefoodx and y == snakefoody)
    {
        score += 10;
        snakefoodx = rand() % width;
        snakefoody = rand() % height;
        ntail += 3;
    }
}

//driver code
int main()
{

    string name;
    cout << "your name: ";
    cin >> name;
    set();
    while (gameover == 0)
    {
        draw(name);
        input();
        logic();
        Sleep(30);
    }
    if(gameover==1){
            system("cls");
             cout<<"GAME OVER! "<<endl;
            cout<<"score: "<<score<<endl;
            Sleep(500);
    }
}
