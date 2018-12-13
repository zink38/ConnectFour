#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<time.h>

int board[7][6] = {0};


struct position
{
    int x;
    int y;
};

void reset()
{
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            board[i][j] = 0;
        }
    }
}

struct position dropPiece(int id, int col)
{
    struct position pos;
    bool dropped = false;
    int i = 0;
    while (!dropped && i < 6)
    {
        if (board[col][i] == 0)
        {
            board[col][i] = id;
            dropped = true;
        }
        if (!dropped)
        {
            i++;
        }
    }
    pos.x = col;
    pos.y = i;
    return pos;
}

void printBoard()
{
    for (int i = 5; i >= 0; i--)
    {
        for (int j = 0; j < 7; j++)
        {
            printf("%d ", board[j][i]);
        }
        printf("\n");
    }
}

bool isConnectFour(struct position pos)
{
    bool found = false;
    int id = board[pos.x][pos.y];
    //printf("%d\n",id);
    //printf("%d,%d\n",pos.x,pos.y);
    int count = 0;
    if (pos.y > 2)
    {
        for (int i = 1; i < 4; i++)
        {
            
            if (id != board[pos.x][pos.y - i])
            {
                break;
            }
            else
            {
                found = true;
                printf("vertical connect\n");
                return found;
            }
        }
    }
    for (int i = -3; i < 4; i++)
    {
        //printf("%d,%d\n", id, board[pos.x + i][pos.y]);
        if (id == board[pos.x + i][pos.y])
        {
            //printf("incrementing \n");
            count++;
            if (count == 4)
            {
                found = true;
                printf("horizontal connect\n");
                return found;
            }
        }
        else
        {
            count = 0;
        }
    }
    count = 0;
    for (int i = -3; i < 4; i++)
    {

        if (id == board[pos.x + i][pos.y + i])
        {
            count++;
            if (count == 4)
            {
                found = true;
                printf("diangle 1 connect\n");
                return found;
            }
        }
        else
        {
            count = 0;
        }
    }
    count = 0;
    for (int i = -3; i < 4; i++)
    {

        if (id == board[pos.x + i][pos.y - i])
        {
            count++;
            if (count == 4)
            {
                found = true;
                printf("diangle 2 connect\n");
                return found;
            }
        }
        else
        {
            count = 0;
        }
    }
    return found;
}

int main()
{
    srand(time(NULL));
    for (int i = 0; i < 3; i++)
    {
        bool gameover = false;
        struct position pos;
        int id = 1;
        int turn = 0;
        int shifter = 1;
        while (!gameover && turn < 42)
        {
            
            pos = dropPiece(id, (rand() % 6));
            gameover = isConnectFour(pos);
            turn++;
            id = id + shifter;
            shifter *= -1;
        }
        printBoard();
        printf("%d wins! \n", board[pos.x][pos.y]);
        reset();
    }

    return 0;
}