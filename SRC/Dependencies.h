#pragma once
#include <iostream>
#include <thread>
#include <string>

#ifdef _WIN32
    #define _WIN32_WINNT 0x0500  //should've made this comment earlier cuz now i forgot what this is for lol
    #include <windows.h>
#endif

#ifdef linux
    #include <unistd.h>
    #include <cstring> //used in center_text() for strlen, might be removed later
#endif

////////////////////////////////////////commands////////////////////////////////////////
#ifdef _WIN32
    //changes window size
    void windowResize_XY(int x, int y)
    {
        HWND console = GetConsoleWindow();
        RECT r;
        GetWindowRect(console, &r);
        MoveWindow(console, r.left, r.top, x, y, TRUE);
        for (int j = 0; j < 100; ++j)
        {
            for (int i = 0x41; i < 0x5B; ++i) {}
        }
    }

    //waits for x amount of milliseconds
    int wait(const int sec)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(sec));
        return sec;
    }

    //writes text in a type writting effect
    //usage: log([milliseconds between characters], [milliseconds before changing line], [changes line if true], [the string that will be displayed]);
    void log(const int milsec, const int lb, bool nlb, const char* message)
    {
        if (NULL == message)
            return;

        while (*message)
        {
            printf("%c", *message++);
            wait(milsec);
        }
        wait(lb);
        if (nlb == true)
        {
            printf("\n");
        }
        else { return; }
    }

    //changes cursor position
    void gotoxy(int column, int line)
    {
        COORD coord;
        coord.X = column;
        coord.Y = line;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

    //turns on/off the cursor (true=on ; false=off)
    void cursor(bool c)
    {
        HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO info;
        info.dwSize = 10;
        info.bVisible = c;
        SetConsoleCursorInfo(consoleHandle, &info);
    }

    //displays centered text on the screen
    void centerText(const char*s)
    {
        int l = strlen(s);
        int pos = (int)((114 - l) / 2);
        for (int i = 0; i < pos; i++)
        {
            std::cout << " ";
        }
        std::cout << s;

    }
#endif


#ifdef linux
    //waits for x amount of milliseconds
    int wait(const int sec)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(sec));
        return sec;
    }

    //writes text in a type writting effect
    //usage: log([milliseconds between characters], [milliseconds before changing line], [changes line if true], [the string that will be displayed]);
    //this version fixes a bug where all log calls get pilled up and display all at once, thanks std::flush!
    void log(const int milsec, const int lb, bool nlb, const char* message)
    {
        if (NULL == message)
            return;

        while (*message)
        {
            std::cout << *message++;
            std::cout << std::flush;
            wait(milsec);
        }
        wait(lb);
        if (nlb == true)
        {
            std::cout << std::endl;
        }
        else { return; }
    }

    //changes cursor position, it's necessary to offset the x & y values by +1... for some reason
    void gotoxy(int column, int line)
    {
        column = column + 1;
        line = line + 1;
        printf("\033[%d;%dH", line, column);
    }

    //turns on/off the cursor (true=on ; false=off)
    void cursor(bool c)
    {
        if (c == false)
        {
            printf("\e[?25l"); //hides cursor
        }
        else
        {
            printf("\e[?25h"); //shows cursor
        }
    }

    //displays centered text on the screen
    //yes, this is the same command on windows; yes, i could just use the same implementation for both OSes; no i won't cuz im lazy xd
    void centerText(const char*s)
    {
        int l = strlen(s);
        int pos = (int)((114 - l) / 2);
        for (int i = 0; i < pos; i++)
        {
            std::cout << " ";
        }
        std::cout << s;

    }

    //changes the colour of text and background, values range from 0 (default text colour of OS) to 17, all other values change text colour to default
    void colour(int colour)
    {
        switch(colour)
        {
            case 0:
                printf("\033[39m"); //default text
                break;

            case 1:
                printf("\033[49m"); //default background
                break;

            case 2:
                printf("\033[30m"); //black text
                break;

            case 3:
                printf("\033[31m"); //red text
                break;

            case 4:
                printf("\033[32m"); //green text
                break;

            case 5:
                printf("\033[33m"); //orange text
                break;

            case 6:
                printf("\033[34m"); //blue text
                break;

            case 7:
                printf("\033[35m"); //magenta text
                break;

            case 8:
                printf("\033[36m"); //cyan text
                break;

            case 9:
                printf("\033[37m"); //light grey text
                break;

            case 10:
                printf("\033[40m"); //black background
                break;

            case 11:
                printf("\033[41m"); //red background
                break;

            case 12:
                printf("\033[42m"); //green background
                break;

            case 13:
                printf("\033[43m"); //orange background
                break;

            case 14:
                printf("\033[44m"); //blue background
                break;

            case 15:
                printf("\033[45m"); //magenta background
                break;

            case 16:
                printf("\033[46m"); //cyan background
                break;

            case 17:
                printf("\033[47m"); //light grey background
                break;

            default:
                printf("\033[39m"); //default text
                break;
        }
    }

    //quick function to test if all colours work | usage: colour_test();
    void colour_test()
    {
        gotoxy(0, 0); colour(0); printf("default text");
        gotoxy(0, 1); colour(1); printf("default background"); colour(17);
        gotoxy(0, 3); colour(2); printf("black text"); colour(1);
        gotoxy(0, 4); colour(3); printf("red text");
        gotoxy(0, 5); colour(4); printf("green text");
        gotoxy(0, 6); colour(5); printf("orange text");
        gotoxy(0, 7); colour(6); printf("blue text");
        gotoxy(0, 8); colour(7); printf("magenta text");
        gotoxy(0, 9); colour(8); printf("cyan text");
        gotoxy(0, 10); colour(9); printf("light grey text");
        gotoxy(0, 12); colour(10); printf("black background"); colour(0);
        gotoxy(0, 13); colour(11); printf("red background");
        gotoxy(0, 14); colour(12); printf("green background");
        gotoxy(0, 15); colour(13); printf("orange background");
        gotoxy(0, 16); colour(14); printf("blue background");
        gotoxy(0, 17); colour(15); printf("magenta background");
        gotoxy(0, 18); colour(16); printf("cyan background"); colour(2);
        gotoxy(0, 19); colour(17); printf("light grey background"); colour(0); colour(1);
        gotoxy(0, 21); colour(18); printf("default text (default value)");
        gotoxy(0, 22); colour(20); printf("default text (default value)");
        gotoxy(0, 30); colour(0);
        colour(1);
    }
#endif
