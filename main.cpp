#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>

using namespace std;

#define H 20
#define W 15

char board[H][W];

int x, y, b;

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

void initBoard()
{
    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
            if (i == 0 || i == H - 1 || j == 0 || j == W - 1)
                board[i][j] = '#';
            else
                board[i][j] = ' ';
}

// ====================== COLOR ======================

void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int getColor(char c)
{
    if (c == 'I') return 11; // cyan
    if (c == 'O') return 14; // yellow
    if (c == 'T') return 13; // purple
    if (c == 'S') return 10; // green
    if (c == 'Z') return 12; // red
    if (c == 'J') return 9;  // blue
    if (c == 'L') return 6;  // orange

    return 7;
}

// ====================== LOGIC ======================
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

    // khung
    for (int i = 0; i < 10; i++)
    {
        COORD pos = {(SHORT)nextX, (SHORT)(nextY+i)};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

        if (i == 0 || i == 9)
            cout << "############";
        else
            cout << "#          #";
    }

    // block preview
    for (int i = 0; i < 4; i++)
    {
        COORD pos = {(SHORT)(nextX+2), (SHORT)(nextY+2+i)};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

        for (int j = 0; j < 4; j++)
        {
            char c = blocks[b][i][j];

            if (c == ' ')
                cout << "  ";
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
    system("cls");

    drawMainBoard();

    drawNextBlock();

    //drawHold();

    setColor(15);

    COORD pos = {35, 15};
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
    cout << "Q : QUIT";
}

bool canMove(int dx, int dy)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (blocks[b][i][j] != ' ')
            {
                int xt = x + j + dx;
                int yt = y + i + dy;
                if (xt < 1 || xt >= W-1 || yt >= H-1 ) return false;
                if (board[yt][xt] != ' ') return false;
            }
    return true;
}

void placeBlock()
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (blocks[b][i][j] != ' ')
                board[y+i][x+j] = blocks[b][i][j];
}

void clearBlock()
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (blocks[b][i][j] != ' ')
                board[y+i][x+j] = ' ';
}
void initBoard(){
    for (int i = 0 ; i < H ; i++)
        for (int j = 0 ; j < W ; j++)
            if (i == 0 || i == H-1 || j ==0 || j == W-1) board[i][j] = '#';
            else board[i][j] = ' ';
}
void draw(){
    system("cls");

// Rotate 90 degree
void rotateBlock()
{
    char temp[4][4];

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            temp[j][3 - i] = blocks[b][i][j];

    // check valid rotation
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (temp[i][j] != ' ')
            {
                int xt = x + j;
                int yt = y + i;

                if (xt <= 0 || xt >= W - 1 || yt >= H - 1)
                    return;

                if (board[yt][xt] != ' ')
                    return;
            }

    // apply rotation
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            blocks[b][i][j] = temp[i][j];
}

int main()
{
    srand(time(0));
    x = 5; y = 0; b = rand()%7;
    initBoard();

    x = 5;
    y = 0;
    b = rand() % 7;

    while (true)
    {
        clearBlock();

        // input
        if (kbhit())
        {
            char c = getch();
            if (c == 'a' && canMove(-1,0)) x--;
            if (c == 'd' && canMove( 1,0)) x++;
            if (c == 'x' && canMove( 0,1)) y++;
            if (c == 'q') break;
        }

        // auto fall
        if (canMove(0, 1))
        {
            y++;
        }
        else
        {
            placeBlock();

            // new block
            x = 5;
            y = 0;
            b = rand() % 7;

            // game over check
            if (!canMove(0, 0))
            {
                draw();
                cout << "\nGAME OVER\n";
                break;
            }
        }
        block2Board();
        draw();
        _sleep(500);
    }
    return 0;
}