#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
	#include <conio.h>
	#include <windows.h>
#endif
#ifdef __unix__
	#include <curses.h>
#endif
#include <stdbool.h>

#define pieces 6

#ifdef _WIN32
    #define RED   "\x1B[31m"
    #define GRN   "\x1B[32m"
    #define YEL   "\x1B[33m"
    #define BLU   "\x1B[34m"
    #define MAG   "\x1B[35m"
    #define CYN   "\x1B[36m"
    #define WHT   "\x1B[37m"
    #define RESET "\x1B[0m"
#endif
#ifdef __unix__
    #define RED 1
    #define GRN 2
    #define YEL 3
    #define BLU 4
    #define MAG 5
    #define CYN 6
    #define WHT 7
#endif

#ifdef _WIN32
    #define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))
    #define clear() (printf("\033[H\033[J"))
    #define bright() (printf("\x1B[1m"))
#endif
#ifdef __unix__
    #define gotoxy(x,y) move((y), (x))
    #define bright() ((void)0)
#endif

#ifdef _WIN32
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
#endif
#ifdef __unix__
int colors[] = {
	RED,
	GRN,
	YEL,
	BLU,
	MAG,
	CYN
};
#endif

struct piece
{
    int xOffset[4];
    int yOffset[4];
};

struct Board
{
    int square[200];
};
#ifdef __unix__
#define Sleep(t) (nanosleep((const struct timespec[]){{0, 1000000L*(t)}}, NULL))
#endif

void print(const char *format, ...){
    va_list args;
    va_start(args, format);
    #ifdef _WIN32
        vprintf(format, args);
    #endif
    #ifdef __unix__
        printw(format, args);
    #endif

    va_end(args);
}

#ifdef _WIN32
void col(const char *str)
{
    printf(str);
}
#endif

#ifdef __unix__
void col(int i)
{
    attron(COLOR_PAIR(i));
}
#endif

#ifdef _WIN32
void reset(const char *str)
{
    printf(RESET);
}
#endif

#ifdef __unix__
void reset(int i)
{
    attroff(COLOR_PAIR(i));
}
#endif



int main()
{
    #ifdef __unix__
    initscr();
    int start_color();
    init_pair(1, COLOR_RED,     COLOR_BLACK);
    init_pair(2, COLOR_GREEN,   COLOR_BLACK);
    init_pair(3, COLOR_YELLOW,  COLOR_BLACK);
    init_pair(4, COLOR_BLUE,    COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN,    COLOR_BLACK);
    init_pair(7, COLOR_WHITE,   COLOR_BLACK);
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    #endif
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
    int maxTick = 2;

    int width = 10;
    int height = 20;

    bool generatePiece = true;

    int score = 0;
    int scores[4] = {40, 100, 300, 1200};

    int next = rand() % 6;

    while(game)
    {
        clock_t t; 
        t = clock();
        //get player input
        //char ch[10];

        if (generatePiece)
        {
            int pX = 5;
            int pY = 0;
            color = next;
            next = rand() % 6;
            _piece = listOfPieces[color];
            generatePiece = false;
        }

	#ifdef _WIN32
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
        #endif
        #ifdef __unix__
	    int ch = getch();
	    if (ch != ERR){
            if (ch == KEY_UP){
	            int foo;
                for (int i = 0; i < 4; i++)
                {
                    foo = _piece.xOffset[i];
                    _piece.xOffset[i] = -_piece.yOffset[i];
                    _piece.yOffset[i] = foo;
                }
	        }
	        if (ch == KEY_LEFT){
                    pX--;
	        }
	        if (ch == KEY_RIGHT){
                    pX++;
	        }
	        if (ch == KEY_DOWN){
                    pY++;
	        }
	    }
        #endif
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
        int lines = 0;
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
                    board.square[(_piece.yOffset[j] + pY) * 10 + _piece.xOffset[j] + pX] = color;
                }
                pX = 4;
                pY = -1;
                
                for(int row = 0; row < 20; row++)
                {
                    bool delRow = true;
                    for(int col = 0; col < 10; col++)
                    {
                        if (board.square[row * 10 + col] < 0)
                        {
                            delRow = false;
                            break;
                        }
                    }
                    if (delRow)
                    {
                        lines++;
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
        if (lines > 0)
        {
            score += scores[lines - 1];
        }
        
        int pos;

        clear();
        
        print("\t|  ");
        bright();
        col(BLU); print("T"); reset(BLU); 
        col(MAG); print("E"); reset(MAG); 
        col(RED); print("T"); reset(RED);
        col(YEL); print("R"); reset(YEL);
        col(GRN); print("I"); reset(GRN);
        col(CYN); print("S"); reset(CYN);
        print("  |");
        for (int y = 0; y < 20; y++)
        {
            print("\n\t|");
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
                    col(colors[color]);
                    print("0");
                    reset(colors[color]);
                }
                else
                {
                    
                    pos = y * 10 + x;
                    if(board.square[pos] >= 0)
                    {
                        col(colors[board.square[y * 10 + x]]);
                        print("&");
                        reset(colors[board.square[y * 10 + x]]);
                    }
                    else
                    {
                        print(".");
                    }
                }
            }
            print("|");
            if(y == 0)
            {
                print("\t");
                bright();
                col(RED);
                print("SCORE");
                reset(RED);
            }
            if(y == 1)
            {
                print("\t");
                bright();
                col(RED);
                print("%d", score);
                reset(RED);
            }
            
            
        }

        // show next piece
        gotoxy(22, 5);
        print("\t");
        bright();
        col(BLU);
        print("NEXT:");
        reset(BLU);
        struct piece nextPiece = listOfPieces[next];
        for(int i = 0; i < 4; i++)
        {
            gotoxy(27 + nextPiece.xOffset[i], 8 + nextPiece.yOffset[i]);
            col(colors[next]);
            print("0");
            reset(colors[next]);
        }

        for (int i = 0; i < 10; i++)
        {
            if(board.square[i] > 0)
            {
                game = false;
                break;
            }
        }
        gotoxy(0, 23);
        t = clock() - t; 
        double time_taken = ((double)t)/CLOCKS_PER_SEC;
        print("\t");
        bright();
        print("fps: %f\n", 1 / time_taken);
        if(1000/10 - (1000*time_taken) >= 0)
            Sleep(1000/10 - (1000*time_taken));
        else
           Sleep(1000/10);
        #ifdef __unix__
        refresh();
        #endif	

    }
    gotoxy(0, 22);
    print("\t| ");
    col(RED);
    print("You lost");
    reset(RED);
    print(" |");
    
    return 0;
}
