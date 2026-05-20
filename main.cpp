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
char blocks[7][4][4] = {};
const char BLOCK_SHAPES[7][4][4] =
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

class Tetromino
{
public:
    char shape[4][4];

    Tetromino()
    {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                shape[i][j] = ' ';
    }

    explicit Tetromino(int type)
    {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                shape[i][j] = BLOCK_SHAPES[type][i][j];
    }

    Tetromino rotated() const
    {
        Tetromino result;
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                result.shape[j][3 - i] = shape[i][j];
        return result;
    }

    char getLetter() const
    {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                if (shape[i][j] != ' ')
                    return shape[i][j];
        return ' ';
    }
};

class Board
{
public:
    char grid[H][W];
    void init()
    {
        for (int i = 0; i < H; i++)
            for (int j = 0; j < W; j++)
                grid[i][j] = (i == 0 || i == H - 1 || j == 0 || j == W - 1) ? '#' : ' ';
    }
    void place(const Tetromino& t, int x, int y)
    {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                if (t.shape[i][j] != ' ')
                    grid[y + i][x + j] = t.shape[i][j];
    }
    bool canFit(const Tetromino& t, int x, int y) const
    {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                if (t.shape[i][j] != ' ')
                {
                    int nx = x + j, ny = y + i;
                    if (nx < 1 || nx >= W - 1 || ny < 1 || ny >= H - 1)
                        return false;
                    if (grid[ny][nx] != ' ')
                        return false;
                }
        return true;
    }
    int removeLines()
    {
        int cleared = 0;
        for (int i = H - 2; i > 0; i--)
        {
            bool full = true;
            for (int j = 1; j < W - 1; j++)
                if (grid[i][j] == ' ') { full = false; break; }

            if (full)
            {
                for (int ii = i; ii > 1; ii--)
                    for (int jj = 1; jj < W - 1; jj++)
                        grid[ii][jj] = grid[ii - 1][jj];

                for (int jj = 1; jj < W - 1; jj++)
                    grid[1][jj] = ' ';

                cleared++;
                i++; // re-check this row
            }
        }
        return cleared;
    }
    void clear(const Tetromino& t, int x, int y)
    {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                if (t.shape[i][j] != ' ')
                    grid[y + i][x + j] = ' ';
    }
};
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
    // Trả về mã màu tương ứng với từng khối Tetromino
    static int getColor(char c)
    {
        switch (c)
        {
            case 'I': return 11;
            case 'O': return 14;
            case 'T': return 13;
            case 'S': return 10;
            case 'Z': return 12;
            case 'J': return 9;
            case 'L': return 6;
            default:  return 7;
        }
    }
    // Vẽ một ô của board
    static void drawCell(char c)
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
    // Vẽ toàn bộ board
    void drawBoard(const Board& board) const
    {
        moveCursor(0, 0);
        for (int i = 0; i < H; i++)
        {
            for (int j = 0; j < W; j++)
                drawCell(board.grid[i][j]);
            cout << '\n';
        }
    }
     // Vẽ khối Tetromino tiếp theo (Next Block)
    void drawNextBlock(const Tetromino& next) const
    {
        const int nx = 35, ny = 3;
        setColor(15);

        for (int i = 0; i < 10; i++)
        {
            moveCursor(nx, ny + i);
            if (i == 0 || i == 9) cout << "############";
            else                   cout << "#          #";
        }

        for (int i = 0; i < 4; i++)
        {
            moveCursor(nx + 2, ny + 2 + i);
            for (int j = 0; j < 4; j++)
            {
                char c = next.shape[i][j];
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
      // Hiển thị điểm số và hướng dẫn điều khiển
    void drawHUD(int score) const
    {
        setColor(15);
        moveCursor(35, 13); cout << "SCORE: " << score << "      ";
        moveCursor(35, 15); cout << "A : LEFT  ";
        moveCursor(35, 16); cout << "D : RIGHT ";
        moveCursor(35, 17); cout << "X : DOWN  ";
        moveCursor(35, 18); cout << "W : ROTATE";
        moveCursor(35, 19); cout << "Q : QUIT  ";
        setColor(7);
    }
     // Vẽ toàn bộ giao diện game
    void drawAll(const Board& board, const Tetromino& next, int score) const
    {
        drawBoard(board);
        drawNextBlock(next);
        drawHUD(score);
    }
};

class Game
{
private:
    int       fallSpeed;
    int       score;
    bool      running;

    void handleInput()
    {
        if (!kbhit()) return;

        char c = getch();
        switch (c)
        {
            case 'a': case 'A': tryMove(-1, 0); break;
            case 'd': case 'D': tryMove(1,  0); break;
            case 'x': case 'X': tryMove(0,  1); break;
            case 'w': case 'W': tryRotate();    break;
            case 'q': case 'Q': running = false; break;
        }
    }

    void tryMove(int dx, int dy)
    {

    }

    void tryRotate()
    {

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
