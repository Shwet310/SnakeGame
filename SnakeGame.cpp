#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
bool gameOver;
const int width = 20;
const int height = 20; 
int x,y, fruitx, fruity, score;
int tailx[100], taily[100];
int nTail;              // for length of the tail
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

void Setup()
{
   gameOver = false;
   dir = STOP;
   x = width / 2;
   y = height / 2;
   fruitx = rand() % width;
   fruity = rand() % height;
   score = 0;
}
 void Draw()
{
  // SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),{0,0});  
  system("cls");
   for (int i = 0; i < width+2; i++)
       cout << "#";
   cout << endl;
   for(int i = 0; i < height ; i++)
   {
        for(int j = 0; j < width; j++)
       {
            if (j == 0)
               cout << "#";
            if(i == y && j == x)
               cout << "O";
            else if (i == fruity && j == fruitx)
               cout << "F";
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                
                    if (tailx[k] == j && taily[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                 
                }
                if (!print)
                    cout << " ";
           
            }
           
             if( j == width - 1)
                cout << "#";
       }
       cout << endl;
    }
    for (int i=0; i < width+2; i++)
        cout << "#";
    cout << endl;
    cout << "Score:" << score << endl;
        

}

 void Input()
 {
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':             /* constant-expression */
            dir = LEFT;                 /* code */
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
        case 'x':
            gameOver = true;
            break;
        }
    }
 }
void Logic()
 {
    int prevx = tailx[0];       // previous x coordinate of the tail
    int prevy = taily[0];
    int prev2x, prev2y;
    tailx[0] = x;
    taily[0] = y;
    for (int i = 1; i< nTail; i++)
    {
        prev2x = tailx[i];
        prev2y = taily[i];
        tailx[i] = prevx;
        taily[i] = prevy;
        prevx = prev2x;
        prevy = prev2y;
    }

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
    
    default:
        break;
    }
    if (x > width || x <0 || y > height || y <0)
      gameOver = true;

    for (int i = 0; i < nTail; i++)
        if (tailx[i] == x && taily[i] == y)
            gameOver = true;
    
    if (x == fruitx && y == fruity)
    {
        score += 10;
        fruitx = rand() % width;
        fruity = rand() % height; 
        nTail++;
    }

 }
 int main()
 {
    Setup();
    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
        Sleep(50);
    }
    return 0;
 }  