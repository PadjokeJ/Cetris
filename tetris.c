#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <stdbool.h>

#define pieces 6

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

char* colors[] = 
{
    RED,
    GRN,
    YEL,
    BLU,
    MAG,
    CYN
};

char ARROW_LEFT = 37;
char ARROW_UP = 38;
char ARROW_RIGHT = 39;
char ARROW_DOWN = 40;
char SPACE = 32;



struct piece
{
    int xOffset[4];
    int yOffset[4];
};

struct Board
{
    int square[200];
};


int main()
{
    srand(time(NULL));

    struct Board board;
    for (int r = 0; r < 200; r++)
    {
        board.square[r] = -1;
    }

    struct piece lPiece1;
    lPiece1.xOffset[0] = 1;     lPiece1.yOffset[0] = 0;
    lPiece1.xOffset[1] = 0;     lPiece1.yOffset[1] = 0;
    lPiece1.xOffset[2] = -1;    lPiece1.yOffset[2] = 0;
    lPiece1.xOffset[3] = 1;     lPiece1.yOffset[3] = -1;

    struct piece lPiece2;
    lPiece2.xOffset[0] = 1;     lPiece2.yOffset[0] = 0;
    lPiece2.xOffset[1] = 0;     lPiece2.yOffset[1] = 0;
    lPiece2.xOffset[2] = -1;    lPiece2.yOffset[2] = 0;
    lPiece2.xOffset[3] = 1;     lPiece2.yOffset[3] = 1;

    struct piece iPiece;
    iPiece.xOffset[0] = 1;      iPiece.yOffset[0] = 0;
    iPiece.xOffset[1] = 0;      iPiece.yOffset[1] = 0;
    iPiece.xOffset[2] = -1;     iPiece.yOffset[2] = 0;
    iPiece.xOffset[3] = 2;      iPiece.yOffset[3] = 0;

    struct piece tPiece;
    tPiece.xOffset[0] = 1;      tPiece.yOffset[0] = 0;
    tPiece.xOffset[1] = 0;      tPiece.yOffset[1] = 0;
    tPiece.xOffset[2] = -1;     tPiece.yOffset[2] = 0;
    tPiece.xOffset[3] = 0;      tPiece.yOffset[3] = -1;

    struct piece sPiece;
    sPiece.xOffset[0] = 1;      sPiece.yOffset[0] = 0;
    sPiece.xOffset[1] = 0;      sPiece.yOffset[1] = 0;
    sPiece.xOffset[2] = 0;      sPiece.yOffset[2] = -1;
    sPiece.xOffset[3] = -1;     sPiece.yOffset[3] = -1;

    struct piece zPiece;
    zPiece.xOffset[0] = 1;      zPiece.yOffset[0] = 0;
    zPiece.xOffset[1] = 0;      zPiece.yOffset[1] = 0;
    zPiece.xOffset[2] = 1;      zPiece.yOffset[2] = -1;
    zPiece.xOffset[3] = 2;      zPiece.yOffset[3] = -1;
    
    struct piece listOfPieces[pieces];
    listOfPieces[0] = lPiece1;
    listOfPieces[1] = lPiece2;
    listOfPieces[2] = iPiece;
    listOfPieces[3] = tPiece;
    listOfPieces[4] = sPiece;
    listOfPieces[5] = zPiece;

    struct piece _piece;
    int color;

    int pX = 0;
    int pY = 0;
    bool game = true;
    int ticker = 0;
    int maxTick = 3;

    int width = 10;
    int height = 20;

    bool generatePiece = true;

    while(game)
    {
        system("cls");
        //get player input
        //char ch[10];

        if (generatePiece)
        {
            int pX = 5;
            int pY = 0;
            color = rand() % 6;
            _piece = listOfPieces[color];
            generatePiece = false;
        }

        
        if (GetAsyncKeyState(ARROW_LEFT) & 0x8000)
        {
            pX--;
        }
        if (GetAsyncKeyState(ARROW_UP) & 0x8000)
        {
            int foo;
            for (int i = 0; i < 4; i++)
            {
                foo = _piece.xOffset[i];
                _piece.xOffset[i] = -_piece.yOffset[i];
                _piece.yOffset[i] = foo;
            }
        }
        if (GetAsyncKeyState(ARROW_RIGHT) & 0x8000)
        {
            pX++;
        }
        if (GetAsyncKeyState(ARROW_DOWN) & 0x8000)
        {
            pY++;
        }
        if (GetAsyncKeyState(SPACE) & 0x8000)
        {
            //fall down
        }
        ticker++;
        if(ticker > maxTick)
        {
            ticker = 0;
            pY++;
        }

        for (int i = 0; i < 4; i++)
        {
            if(pX + _piece.xOffset[i] >= width)
                pX--;
            if(pX + _piece.xOffset[i] < 0)
                pX++;
        }
        for (int i = 0; i < 4; i++)
        {
            if(pY + _piece.yOffset[i] >= height)
                pY--;
            if(pY + _piece.yOffset[i] >= height - 1
            || 
            (board.square[(pY + _piece.yOffset[i])*10 + _piece.xOffset[i] + pX + 10] >= 0 
            && 
            (pY + _piece.yOffset[i])*10 + _piece.xOffset[i] + pX + 10 > 0) 
            ){
                generatePiece = true;
                for(int j = 0; j < 4; j++)
                {
                    board.square[(_piece.yOffset[j] + pY) * 10 + _piece.xOffset[j] + pX] = 1;
                }
                pX = 0;
                pY = 0;

                for(int row = 0; row < 20; row++)
                {
                    bool delRow = true;
                    for(int col = 0; col < 10; col++)
                    {
                        if (board.square[row * 10 + col] <= 0)
                        {
                            delRow = false;
                            break;
                        }
                    }
                    if (delRow)
                    {
                        for(int col = 0; col < 10; col++)
                        {
                            board.square[row * 10 + col] = -1;
                        }
                        for(int col = 0; col < 10; col++)
                        {
                            for(int _row = row; _row > 1; _row--)
                            {
                                board.square[_row * 10 + col] = board.square[_row * 10 + col -10];
                                board.square[_row * 10 + col -10] = -1;
                            }
                        }
                    }
                }
                for(int row = 19; row > 1; row--)
                {
                    bool fallRow = true;
                    for(int col = 0; col < 10; col++)
                    {
                        if (board.square[row * 10 + col] > 0)
                        {
                            fallRow = false;
                            break;
                        }
                    }
                    if (fallRow)
                    {
                        for(int col = 0; col < 10; col++)
                        {
                            for(int _row = row; _row > 1; _row--)
                            {
                                board.square[_row * 10 + col] = board.square[_row * 10 + col -10];
                                board.square[_row * 10 + col -10] = -1;
                            }
                        }
                    }
                break;
                }
            }
        }

        int pos;
        putchar('\n');
        for (int y = 0; y < 20; y++)
        {
            putchar('\t');
            putchar('|');
            for (int x = 0; x < width; x++)
            {
                bool renderO = false;
                for (int i = 0; i < 4; i++)
                {
                    if (x == pX + _piece.xOffset[i])
                    {
                        if (y == pY + _piece.yOffset[i])
                        {
                            renderO = true;
                            break;
                        }
                    }
                }
                if (renderO)
                {
                    printf("%s", colors[color]);
                    putchar('0');
                    printf(RESET);
                }
                else
                {
                    printf(RESET);
                    pos = y * 10 + x;
                    if(board.square[pos] > 0)
                        putchar('z');
                    else
                        putchar('.');
                }
            }
            putchar('|');
            printf("\n");
            
        }

        printf(RESET);
        for(int i = 0; i < 4; i++)
        {
            printf("%d, %d\n", _piece.xOffset[i], _piece.yOffset[i]);
        }
        printf("%d, %d\n", pX, pY);

        Sleep(1000/10);

    }
    return 0;
}