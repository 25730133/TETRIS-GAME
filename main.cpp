#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>

using namespace std;

#define H 20
#define W 15

char board[H][W];

int x, y, b;

char currentBlock[4][4];

const int minFallSpeed = 100;
const int speedUpStep = 10;
int fallSpeed = 500;

// 7 tetrominoes
char blocks[7][4][4] =
{
    // I
    {
        {' ',' ',' ',' '},
        {'I','I','I','I'},
        {' ',' ',' ',' '},
        {' ',' ',' ',' '}
    },

    // O
    {
        {' ',' ',' ',' '},
        {' ','O','O',' '},
        {' ','O','O',' '},
        {' ',' ',' ',' '}
    },

    // T
    {
        {' ',' ',' ',' '},
        {' ','T',' ',' '},
        {'T','T','T',' '},
        {' ',' ',' ',' '}
    },

    // S
    {
        {' ',' ',' ',' '},
        {' ','S','S',' '},
        {'S','S',' ',' '},
        {' ',' ',' ',' '}
    },

    // Z
    {
        {' ',' ',' ',' '},
        {'Z','Z',' ',' '},
        {' ','Z','Z',' '},
        {' ',' ',' ',' '}
    },

    // J
    {
        {' ',' ',' ',' '},
        {'J',' ',' ',' '},
        {'J','J','J',' '},
        {' ',' ',' ',' '}
    },

    // L
    {
        {' ',' ',' ',' '},
        {' ',' ','L',' '},
        {'L','L','L',' '},
        {' ',' ',' ',' '}
    }
};

void copyBlock(char dest[4][4], char src[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            dest[i][j] = src[i][j];
        }
    }
}

void initBoard()
{
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            if (i == 0 || i == H - 1 ||
                j == 0 || j == W - 1)
            {
                board[i][j] = '#';
            }
            else
            {
                board[i][j] = ' ';
            }
        }
    }
}

// ====================== COLOR ======================

void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int getColor(char c)
{
    if (c == 'I') return 11;
    if (c == 'O') return 14;
    if (c == 'T') return 13;
    if (c == 'S') return 10;
    if (c == 'Z') return 12;
    if (c == 'J') return 9;
    if (c == 'L') return 6;

    return 7;
}

// ====================== SPEED ======================

void updateSpeed()
{
    if (fallSpeed > minFallSpeed)
    {
        fallSpeed -= speedUpStep;
    }
}

// ====================== DRAW ======================

void drawCell(char c)
{
    if (c == '#')
    {
        setColor(8);
        cout << "##";
    }
    else if (c == ' ')
    {
        cout << "  ";
    }
    else
    {
        setColor(getColor(c));
        cout << "[]";
    }

    setColor(7);
}

void drawMainBoard()
{
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            drawCell(board[i][j]);
        }

        cout << endl;
    }
}

void drawNextBlock()
{
    int nextX = 35;
    int nextY = 3;

    setColor(15);

    for (int i = 0; i < 10; i++)
    {
        COORD pos = {(SHORT)nextX, (SHORT)(nextY + i)};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

        if (i == 0 || i == 9)
            cout << "############";
        else
            cout << "#          #";
    }

    for (int i = 0; i < 4; i++)
    {
        COORD pos = {(SHORT)(nextX + 2), (SHORT)(nextY + 2 + i)};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

        for (int j = 0; j < 4; j++)
        {
            char c = blocks[b][i][j];

            if (c == ' ')
            {
                cout << "  ";
            }
            else
            {
                setColor(getColor(c));
                cout << "[]";
                setColor(15);
            }
        }
    }
}

void draw()
{
    COORD pos = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

    drawMainBoard();

    drawNextBlock();

    setColor(15);

    pos = {35, 15};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    cout << "A : LEFT";

    pos = {35, 16};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    cout << "D : RIGHT";

    pos = {35, 17};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    cout << "X : DOWN";

    pos = {35, 18};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    cout << "W : ROTATE";

    pos = {35, 19};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    cout << "Q : QUIT";
}

// ====================== LOGIC ======================

void placeBlock()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (currentBlock[i][j] != ' ')
            {
                board[y + i][x + j] = currentBlock[i][j];
            }
        }
    }
}

void clearBlock()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (currentBlock[i][j] != ' ')
            {
                board[y + i][x + j] = ' ';
            }
        }
    }
}

bool canMove(int dx, int dy)
{
    clearBlock();

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (currentBlock[i][j] != ' ')
            {
                int xt = x + j + dx;
                int yt = y + i + dy;

                if (xt < 1 || xt >= W - 1 ||
                    yt < 1 || yt >= H - 1)
                {
                    placeBlock();
                    return false;
                }

                if (board[yt][xt] != ' ')
                {
                    placeBlock();
                    return false;
                }
            }
        }
    }

    placeBlock();

    return true;
}

void rotateBlock()
{
    char temp[4][4];

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            temp[j][3 - i] = currentBlock[i][j];
        }
    }

    clearBlock();

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (temp[i][j] != ' ')
            {
                int xt = x + j;
                int yt = y + i;

                if (xt < 1 || xt >= W - 1 ||
                    yt < 1 || yt >= H - 1)
                {
                    placeBlock();
                    return;
                }

                if (board[yt][xt] != ' ')
                {
                    placeBlock();
                    return;
                }
            }
        }
    }

    copyBlock(currentBlock, temp);

    placeBlock();
}

void removeLine()
{
    for (int i = H - 2; i > 0; i--)
    {
        bool full = true;

        for (int j = 1; j < W - 1; j++)
        {
            if (board[i][j] == ' ')
            {
                full = false;
                break;
            }
        }

        if (full)
        {
            for (int ii = i; ii > 1; ii--)
            {
                for (int jj = 1; jj < W - 1; jj++)
                {
                    board[ii][jj] = board[ii - 1][jj];
                }
            }

            for (int jj = 1; jj < W - 1; jj++)
            {
                board[1][jj] = ' ';
            }

            updateSpeed();

            draw();

            Sleep(200);

            i++;
        }
    }
}
// ====================== CLASS RENDERER ======================

class Renderer
{
public:
     // Đổi màu chữ trong console
    static void setColor(int color)
    {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }
     // Di chuyển con trỏ console
    static void moveCursor(int x, int y)
    {
        COORD pos = { (SHORT)x, (SHORT)y };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    }
};
// ====================== MAIN ======================

int main()
{
    srand(time(0));

    x = 5;
    y = 1;
    b = rand() % 7;

    copyBlock(currentBlock, blocks[b]);

    initBoard();

    placeBlock();

    while (true)
    {
        // input
        if (kbhit())
        {
            char c = getch();

            if ((c == 'a' || c == 'A') && canMove(-1, 0))
            {
                clearBlock();
                x--;
                placeBlock();
            }

            if ((c == 'd' || c == 'D') && canMove(1, 0))
            {
                clearBlock();
                x++;
                placeBlock();
            }

            if ((c == 'x' || c == 'X') && canMove(0, 1))
            {
                clearBlock();
                y++;
                placeBlock();
            }

            if (c == 'w' || c == 'W')
            {
                rotateBlock();
            }

            if (c == 'q' || c == 'Q')
            {
                break;
            }
        }

        // auto fall
        if (canMove(0, 1))
        {
            clearBlock();
            y++;
            placeBlock();
        }
        else
        {
            removeLine();

            x = 5;
            y = 1;
            b = rand() % 7;

            copyBlock(currentBlock, blocks[b]);

            if (!canMove(0, 0))
            {
                draw();

                COORD pos = {0, H + 1};
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

                cout << "GAME OVER\n";

                break;
            }

            placeBlock();
        }

        draw();

        Sleep(fallSpeed);
    }

    return 0;
}
