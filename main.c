#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int board[7][6] = {0};

/*int board[7][6] = {
    {1,2,1,1,1,1},
    {1,2,1,2,1,1},
    {1,1,2,1,1,1},
    {1,2,2,2,1,1},
    {2,1,2,2,1,1},
    {2,2,1,2,2,2},
    {2,1,2,2,2,2}
};*/

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

    int boundX1 = 0;
    int boundX2 = 6;
    int boundY1 = 0;
    int boundY2 = 5;

    if (pos.y > 2)
    {
        for (int i = 1; i < 4; i++)
        {
            if (id == board[pos.x][pos.y - i])
            {
                count++;
                if (count == 3)
                {
                    found = true;
                    //printf("Vertical Connect\n");
                    return found;
                }
            }
            else
            {
                count = 0;
                break;
            }
        }
    }
    for (int i = -3; i < 4; i++)
    {
        //printf("%d,%d\n", pos.x, pos.x + i);
        if (pos.x + i >= boundX1 && pos.x + i <= boundX2)
        {
            //printf("past bound 1\n");
            //printf("%d,%d\n", id, board[pos.x + i][pos.y]);
            if (id == board[pos.x + i][pos.y])
            {
                //printf("incrementing \n");
                //printf("count up\n");
                count++;
                if (count == 4)
                {
                    found = true;
                    //printf("horizontal connect\n");
                    return found;
                }
            }
            else
            {
                //printf("count reset\n");
                count = 0;
            }
        }
    }
    //printf("end of drop\n");
    count = 0;
    for (int i = -3; i < 4; i++)
    {
        if (pos.y + i >= boundY1 && pos.y + i <= boundY2)
        {
            if (pos.x + i >= boundX1 && pos.x + i <= boundX2)
            {
                if (id == board[pos.x + i][pos.y + i])
                {
                    count++;
                    //printf("%d,", count);
                    if (count == 4)
                    {
                        found = true;
                        //printf("diagonal 1 connect\n");
                        return found;
                    }
                }
                else
                {
                    count = 0;
                }
            }
        }
    }

    count = 0;
    for (int i = -3; i < 4; i++)
    {
        if (pos.y - i >= boundY1 && pos.y - i <= boundY2)
        {
            if (pos.x + i >= boundX1 && pos.x + i <= boundX2)
            {
                if (id == board[pos.x + i][pos.y - i])
                {
                    count++;
                    if (count == 4)
                    {
                        found = true;
                        //printf("diagonal 2 connect\n");
                        return found;
                    }
                }
                else
                {
                    count = 0;
                }
            }
        }
    }
    return found;
}

bool validDrop(int col)
{
    bool result = true;
    if (board[col][5] != 0)
    {
        result = false;
    }
    return result;
}

bool isTrap(int id)
{
    bool result = false;
    int count = 0;
    struct position pos;
    for (int i = 0; i < 7; i++)
    {
        if (validDrop(i))
        {
            pos = dropPiece(id, i);
            if (isConnectFour(pos))
            {
                count++;
            }
            board[pos.x][pos.y] = 0;
        }
        if (count > 1)
        {
            //printf("trap found\n");
            result = true;
            return result;
        }
    }
    return result;
}

int KeeganAI()
{
    int id = 2;
    int oppID = 1;
    bool found = false;
    int choice = 0;
    struct position pos;
    for (int i = 0; i < 7; i++)
    {
        if (validDrop(i))
        {
            pos = dropPiece(id, i);
            found = isConnectFour(pos);
            board[pos.x][pos.y] = 0;
            if (found)
            {
                choice = i;
                return choice;
            }
        }
    }
    for (int i = 0; i < 7; i++)
    {
        if (validDrop(i))
        {
            pos = dropPiece(oppID, i);
            found = isConnectFour(pos);
            board[pos.x][pos.y] = 0;
            if (found)
            {
                choice = i;
                return choice;
            }
        }
    }
    for (int i = 0; i < 7; i++)
    {
        if (validDrop(i))
        {
            pos = dropPiece(id, i);
            found = isTrap(id);
            board[pos.x][pos.y] = 0;
            if (found)
            {
                choice = i;
                return choice;
            }
        }
    }
    for (int i = 0; i < 7; i++)
    {
        if (validDrop(i))
        {
            pos = dropPiece(oppID, i);
            found = isTrap(oppID);
            board[pos.x][pos.y] = 0;
            if (found)
            {
                choice = i;
                return choice;
            }
        }
    }
    do
    {
        choice = rand() % 5 + 1;
    } while (!validDrop(choice));

    return choice;
}

int main()
{
    srand(time(NULL));

    bool gameover = false;
    struct position pos;
    int id = 2;
    int shifter = -1;
    int col = 0;
    int sentinel = 1;
    int turn = 0;
    while (sentinel)
    {
        bool gameover = false;
        while (!gameover)
        {
            turn++;
            id = id + shifter;
            shifter *= -1;
            if (turn % 2 == 1)
            {
                do
                {
                    printf("choose a VALID column {0,1,2,3,4,5,6}: ");
                    scanf("%d", &col);

                    //printf("WTF");
                } while (!validDrop(col));
            }
            else
            {
                col = KeeganAI();
            }
            pos = dropPiece(id, col);
            printBoard();
            printf("\n");
            gameover = isConnectFour(pos);
            if (turn >= 42)
            {
                gameover = true;
            }
        }
        reset();
        turn = 0;
        printf("would you like to play again? {0,1}");
        scanf("%d", &sentinel);
    }

    return 0;
}