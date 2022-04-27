#pragma once
#include <iostream>
#include <thread>
#include <string>

#ifdef _WIN32
    #include <windows.h>
    #include "SDL2/SDL2Music.h"

    #include <sstream>
    #include <fstream>
    #include <cstring>
#endif

#ifdef linux
    #include <signal.h>
    #include <unistd.h>
    #include <vector>
    #include <sstream>
    #include <fstream>
    #include <cstring> //used in center_text() for strlen
    #include <sys/types.h> //ALSA
    #include <sys/stat.h> //ALSA
    #include <fcntl.h> //ALSA
    #include "SDL2/SDL2Music.h"
#endif

////////////////////////////////////////Commands - Linux////////////////////////////////////////
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
        if (NULL == message) { return; }
        while (*message)
        {
            std::cout << *message++;
            std::cout << std::flush;
            wait(milsec);
        }
        wait(lb);
        if (nlb == true) { std::cout << std::endl; }
        else { return; }
    }

    //changes cursor position, it's necessary to offset the x & y values by +1... for some reason (true=on ; false=off)
    void gotoxy(int column, int line)
    {
        column = column + 1;
        line = line + 1;
        printf("\033[%d;%dH", line, column);
    }

    //turns on/off the cursor (true=on ; false=off)
    void cursor(bool c)
    {
        if (c == false) { printf("\e[?25l"); } //hides cursor
        else { printf("\e[?25h"); }  //shows cursor
    }

    //displays centered text on the screen
    void centerText(int x, const char* s)
    {
        int str_length = strlen(s);   //we get the length of the string
        str_length = str_length / 2;  //then divide it by 2
        int h = x - str_length;       //and then offset x (middle of screen value) by the divided value of string length

        h = h+1;
        printf("\033[%dG", h);        //move cursor to h (value previously calculated)

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

    //handler for the Ctrl+C catcher
    void my_handler(int s)
    {
        //printf("caught signal %d\n", s);
        cursor(true);
        colour(0);
        colour(1);
        exit(1);
    }

    //catches Ctrl+C events
    void ctrlC_catcher()
    {
        struct sigaction sigIntHandler;
        sigIntHandler.sa_handler = my_handler;
        sigemptyset(&sigIntHandler.sa_mask);
        sigIntHandler.sa_flags = 0;

        sigaction(SIGINT, &sigIntHandler, NULL);
    }

    void musicPlay(const char* path)
    {
        SDL2Music music;
        music.addMusic(path);
        music.playMusic(0);
    }

    void routeALSAErrors() //stop ALSA from spitting errors
    {
        //int saved_stderr = dup(STDERR_FILENO);
        //int devnull = open("/dev/null", O_RDWR);
        //dup2(devnull, STDERR_FILENO); //Replace standard out
        //dup2(saved_stderr, STDERR_FILENO);

        //error checking
        int fd = ::open("/dev/null", O_WRONLY);
        ::dup2(fd, 2);
        ::close(fd);
    }

    int getxy(bool ch, bool div) //ch true = X || ch false = Y  |||  div true = value/2 || div false = value
    {
        struct Coordinate { int X, Y; };
        typedef std::vector<Coordinate> Coordinates;
        system("stty size >> tmp.txt");

        Coordinates coordinates;
        std::ifstream file ("tmp.txt");
        std::string line;

        if (div == true)
        {
            int x_2, y_2; 
            while (std::getline(file, line))
            {
                std::stringstream iss(line);
                Coordinate coord;
                iss >> coord.Y >> coord.X;
                x_2 = coord.X / 2;
                y_2 = coord.Y / 2;
                coordinates.push_back(coord);
            }
            system("rm tmp.txt");

            if (ch == true) { return x_2; }
            else { return y_2; }
        }
        else
        {
            int cX, cY;
            while (std::getline(file, line))
            {
                std::stringstream iss(line);
                Coordinate coord;
                iss >> coord.Y >> coord.X;
                coordinates.push_back(coord);
                cX = coord.X;
                cY = coord.Y;
            }
            system("rm tmp.txt");

            if (ch == true) { return cX; }
            else { return cY; }
        }

        //writes debug messages
        /*for (Coordinates::iterator i = coordinates.begin(); i != coordinates.end(); ++i)
        {
            std::cout << "X: " << i->X << std::endl;
            std::cout << "Y: " << i->Y << std::endl;
            if (div == true)
            {
                std::cout << "X/2: " << x_2 << std::endl;
                std::cout << "Y/2: " << y_2 << std::endl;
            }
        }*/
    }

    void checkScreenSize()
    {
        int x = getxy(true, false);
        int y = getxy(false, false);

        if (x < 112)
        {
            system("clear");
            gotoxy(0, getxy(false, true)-3); centerText(getxy(true, true), "Sorry, your screen is too small");
            gotoxy(0, getxy(false, true)-2); centerText(getxy(true, true), "min character width: 112");
            gotoxy(0, getxy(false, true)-1); centerText(getxy(true, true), "min character height: 35");
            gotoxy(0, getxy(false, true)); centerText(getxy(true, true), "min recommended res: 1280x720");
            gotoxy(0, getxy(false, true)+1); centerText(getxy(true, true), "your character width: "); std::cout << x;
            gotoxy(0, getxy(false, true)+2); centerText(getxy(true, true), "your character width: "); std::cout << y;
            gotoxy(0, getxy(false, true)+3);
            colour(0);
            colour(1);
            cursor(true);
            exit(-1);
        }
        if (y < 35)
        {
            system("clear");
            gotoxy(0, getxy(false, true)-3); centerText(getxy(true, true), "Sorry, your screen is too small");
            gotoxy(0, getxy(false, true)-2); centerText(getxy(true, true), "min character width: 112");
            gotoxy(0, getxy(false, true)-1); centerText(getxy(true, true), "min character height: 35");
            gotoxy(0, getxy(false, true)); centerText(getxy(true, true), "min recommended res: 1280x720");
            gotoxy(0, getxy(false, true)+1); centerText(getxy(true, true), "your character width: "); std::cout << x;
            gotoxy(0, getxy(false, true)+2); centerText(getxy(true, true), "your character width: "); std::cout << y;
            gotoxy(0, getxy(false, true)+3);
            colour(0);
            colour(1);
            cursor(true);
            exit(-1);
        }
    }

    void colourScreen()
    {
        int ccode_t, ccode_b, backX, backY;

        system("clear");
        backY = getxy(false, false);
        //gotoxy(0, 0); log(0, 0, false, "DEBUG: 5");
        gotoxy(0, getxy(false, true)-10); centerText(getxy(true, true), "What Colour do you want the animation to play in? (text)");
        gotoxy(0, getxy(false, true)-4); centerText(getxy(true, true), "Text Colours:");
        gotoxy(0, getxy(false, true)-3); centerText(getxy(true, true), "system default  - 0 |"); colour(1); std::cout << " "; colour(10); std::cout << "|";
        gotoxy(0, getxy(false, true)-2); centerText(getxy(true, true), "black text      - 2 |"); colour(10); std::cout << " "; colour(10); std::cout << "|";
        gotoxy(0, getxy(false, true)-1); centerText(getxy(true, true), "red text        - 3 |"); colour(11); std::cout << " "; colour(10); std::cout << "|";
        gotoxy(0, getxy(false, true)); centerText(getxy(true, true), "green text      - 4 |"); colour(12); std::cout << " "; colour(10); std::cout << "|";
        gotoxy(0, getxy(false, true)+1); centerText(getxy(true, true), "orange text     - 5 |"); colour(13); std::cout << " "; colour(10); std::cout << "|";
        gotoxy(0, getxy(false, true)+2); centerText(getxy(true, true), "blue text       - 6 |"); colour(14); std::cout << " "; colour(10); std::cout << "|";
        gotoxy(0, getxy(false, true)+3); centerText(getxy(true, true), "magenta text    - 7 |"); colour(15); std::cout << " "; colour(10); std::cout << "|";
        gotoxy(0, getxy(false, true)+4); centerText(getxy(true, true), "cyan text       - 8 |"); colour(16); std::cout << " "; colour(10); std::cout << "|";
        gotoxy(0, getxy(false, true)+5); centerText(getxy(true, true), "light grey text - 9 |"); colour(17); std::cout << " "; colour(10); std::cout << "|";
        gotoxy(0, getxy(false, true)+7); centerText(getxy(true, true), "Recommended colour: 5 |"); colour(13); std::cout << " "; colour(10); std::cout << "|";

        gotoxy(0, getxy(false, true)-9); centerText(getxy(true, true), ">");
        cursor(true);
        std::cin >> (ccode_t);

        system("clear");
        backX = getxy(true, false);
        cursor(false);
        //gotoxy(0, 0); log(0, 0, false, "DEBUG: 10");
        gotoxy(0, getxy(false, true)-10); centerText(getxy(true, true), "What Colour do you want the animation to play in? (background)"); //FIX gotoxy Y coordinates not scaling properly to the screen
        gotoxy(0, getxy(false, true)-4); centerText(getxy(true, true), "Text Colours:");
        gotoxy(0, getxy(false, true)-3); centerText(getxy(true, true), "system default         - 1 |"); colour(1); std::cout << " "; colour(10); std::cout << "|";
        gotoxy(0, getxy(false, true)-2); centerText(getxy(true, true), "black background      - 10 |"); colour(10); std::cout << " "; colour(10); std::cout << "|";
        gotoxy(0, getxy(false, true)-1); centerText(getxy(true, true), "red background        - 11 |"); colour(11); std::cout << " "; colour(10); std::cout << "|";
        gotoxy(0, getxy(false, true)); centerText(getxy(true, true), "green background      - 12 |"); colour(12); std::cout << " "; colour(10); std::cout << "|";
        gotoxy(0, getxy(false, true)+1); centerText(getxy(true, true), "orange background     - 13 |"); colour(13); std::cout << " "; colour(10); std::cout << "|";
        gotoxy(0, getxy(false, true)+2); centerText(getxy(true, true), "blue background       - 14 |"); colour(14); std::cout << " "; colour(10); std::cout << "|";
        gotoxy(0, getxy(false, true)+3); centerText(getxy(true, true), "magenta background    - 15 |"); colour(15); std::cout << " "; colour(10); std::cout << "|";
        gotoxy(0, getxy(false, true)+4); centerText(getxy(true, true), "cyan background       - 16 |"); colour(16); std::cout << " "; colour(10); std::cout << "|";
        gotoxy(0, getxy(false, true)+5); centerText(getxy(true, true), "light grey background - 17 |"); colour(17); std::cout << " "; colour(10); std::cout << "|";
        gotoxy(0, getxy(false, true)+7); centerText(getxy(true, true), "Recommended colour: 10 |"); colour(10); std::cout << " "; colour(10); std::cout << "|";

        gotoxy(0, getxy(false, true)-9); centerText(getxy(true, true), ">");
        cursor(true);
        std::cin >> (ccode_b);

        colour(ccode_t); //5
        colour(ccode_b); //10

        system("clear");
        cursor(false);
        gotoxy(0, 0);

        //draw Background
        for (int i=0; i<backY; i++) //Y
        {
            for (int j=0; j<backX; j++) { std::cout << " "; } //X
        }
    }

    bool checkFileExists(const std::string& name)
    {
        std::ifstream f(name.c_str());

        if (f.good() == false)
        {
            system("clear");
            cursor(false);
            const char* msg = "Sorry but you're missing: ";
            std::string temp = msg + name;
            const char* err = temp.c_str();
            gotoxy(0, getxy(false, true)); centerText(getxy(true, true), err);
            std::cin.get();
            cursor(true);
            exit(-1);
        }
        else { return f.good(); }
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

////////////////////////////////////////Commands - Windows////////////////////////////////////////
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
        if (NULL == message) { return; }
        while (*message)
        {
            std::cout << *message++;
            std::cout << std::flush;
            wait(milsec);
        }
        wait(lb);
        if (nlb == true) { std::cout << std::endl; }
        else { return; }
    }

    //changes cursor position, it's necessary to offset the x & y values by +1... for some reason (true=on ; false=off)
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
        if (c == false) { printf("\033[?25l"); } //hides cursor
        else { printf("\033[?25h"); }  //shows cursor
    }

    int getxy(bool ch, bool div) //ch true = X || ch false = Y  |||  div true = value/2 || div false = value
    {
        int coordX, coordY;

        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        coordX = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        coordY = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

        if (div == true)
        {
            int x_2, y_2; 
            x_2 = coordX / 2;
            y_2 = coordY / 2;

            if (ch == true) { return x_2; }
            else { return y_2; }
        }
        else
        {
            int cX, cY;

            cX = coordX;
            cY = coordY;

            if (ch == true) { return cX; }
            else { return cY; }
        }
    }

    //displays centered text on the screen
    void centerText_XY(int x, int y, const char* s)
    {
        int str_length = strlen(s);   //we get the length of the string
        str_length = str_length / 2;  //then divide it by 2
        int h = x - str_length;       //and then offset x (middle of screen value) by the divided value of string length

        h = h+1;

        COORD coord;
        coord.X = h;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);        //move cursor to h (value previously calculated)

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

    void colourScreen()
    {
        int ccode_t, ccode_b, backX, backY;

        system("CLS");
        backY = getxy(false, false);
        //gotoxy(0, 0); log(0, 0, false, "DEBUG: 5");
        centerText_XY(getxy(true, true), getxy(false, true) - 10, "What Colour do you want the animation to play in? (text)");
        centerText_XY(getxy(true, true), getxy(false, true) - 4, "Text Colours:");
        centerText_XY(getxy(true, true), getxy(false, true) - 3, "system default  - 0 |"); colour(1); std::cout << " "; colour(10); std::cout << "|";
        centerText_XY(getxy(true, true), getxy(false, true) - 2, "black text      - 2 |"); colour(10); std::cout << " "; colour(10); std::cout << "|";
        centerText_XY(getxy(true, true), getxy(false, true) - 1, "red text        - 3 |"); colour(11); std::cout << " "; colour(10); std::cout << "|";
        centerText_XY(getxy(true, true), getxy(false, true), "green text      - 4 |"); colour(12); std::cout << " "; colour(10); std::cout << "|";
        centerText_XY(getxy(true, true), getxy(false, true) + 1, "orange text     - 5 |"); colour(13); std::cout << " "; colour(10); std::cout << "|";
        centerText_XY(getxy(true, true), getxy(false, true) + 2, "blue text       - 6 |"); colour(14); std::cout << " "; colour(10); std::cout << "|";
        centerText_XY(getxy(true, true), getxy(false, true) + 3, "magenta text    - 7 |"); colour(15); std::cout << " "; colour(10); std::cout << "|";
        centerText_XY(getxy(true, true), getxy(false, true) + 4, "cyan text       - 8 |"); colour(16); std::cout << " "; colour(10); std::cout << "|";
        centerText_XY(getxy(true, true), getxy(false, true) + 5, "light grey text - 9 |"); colour(17); std::cout << " "; colour(10); std::cout << "|";
        centerText_XY(getxy(true, true), getxy(false, true) + 7, "Recommended colour: 5 |"); colour(13); std::cout << " "; colour(10); std::cout << "|";

        centerText_XY(getxy(true, true), getxy(false, true) - 9, ">");
        cursor(true);
        std::cin >> (ccode_t);

        system("CLS");
        backX = getxy(true, false);
        cursor(false);
        //gotoxy(0, 0); log(0, 0, false, "DEBUG: 10");
        centerText_XY(getxy(true, true), getxy(false, true) - 10, "What Colour do you want the animation to play in? (background)"); //FIX gotoxy Y coordinates not scaling properly to the screen
        centerText_XY(getxy(true, true), getxy(false, true) - 4, "Text Colours:");
        centerText_XY(getxy(true, true), getxy(false, true) - 3, "system default         - 1 |"); colour(1); std::cout << " "; colour(10); std::cout << "|";
        centerText_XY(getxy(true, true), getxy(false, true) - 2, "black background      - 10 |"); colour(10); std::cout << " "; colour(10); std::cout << "|";
        centerText_XY(getxy(true, true), getxy(false, true) - 1, "red background        - 11 |"); colour(11); std::cout << " "; colour(10); std::cout << "|";
        centerText_XY(getxy(true, true), getxy(false, true), "green background      - 12 |"); colour(12); std::cout << " "; colour(10); std::cout << "|";
        centerText_XY(getxy(true, true), getxy(false, true) + 1, "orange background     - 13 |"); colour(13); std::cout << " "; colour(10); std::cout << "|";
        centerText_XY(getxy(true, true), getxy(false, true) + 2, "blue background       - 14 |"); colour(14); std::cout << " "; colour(10); std::cout << "|";
        centerText_XY(getxy(true, true), getxy(false, true) + 3, "magenta background    - 15 |"); colour(15); std::cout << " "; colour(10); std::cout << "|";
        centerText_XY(getxy(true, true), getxy(false, true) + 4, "cyan background       - 16 |"); colour(16); std::cout << " "; colour(10); std::cout << "|";
        centerText_XY(getxy(true, true), getxy(false, true) + 5, "light grey background - 17 |"); colour(17); std::cout << " "; colour(10); std::cout << "|";
        centerText_XY(getxy(true, true), getxy(false, true) + 7, "Recommended colour: 10 |"); colour(10); std::cout << " "; colour(10); std::cout << "|";

        centerText_XY(getxy(true, true), getxy(false, true) - 9, ">");
        cursor(true);
        std::cin >> (ccode_b);

        colour(ccode_t); //5
        colour(ccode_b); //10

        system("CLS");
        cursor(false);
        gotoxy(0, 0);

        //draw Background
        for (int i=0; i<backY; i++) //Y
        {
            for (int j=0; j<backX; j++) { std::cout << " "; } //X
        }
    }

    void musicPlay(const char* path)
    {
        SDL2Music music;
        music.addMusic(path);
        music.playMusic(0);
    }

    void checkScreenSize()
    {
        int x = getxy(true, false);
        int y = getxy(false, false);

        if (x < 112)
        {
            system("CLS");
            centerText_XY(getxy(true, true), getxy(false, true) - 3, "Sorry, your screen is too small");
            centerText_XY(getxy(true, true), getxy(false, true) - 2, "min character width: 112");
            centerText_XY(getxy(true, true), getxy(false, true) - 1, "min character height: 35");
            centerText_XY(getxy(true, true), getxy(false, true), "min recommended res: 1280x720");
            centerText_XY(getxy(true, true), getxy(false, true) + 1, "your character width: "); std::cout << x;
            centerText_XY(getxy(true, true), getxy(false, true) + 2, "your character width: "); std::cout << y;
            gotoxy(0, getxy(false, true)+3);
            colour(0);
            colour(1);
            cursor(true);
            exit(-1);
        }
        if (y < 35)
        {
            system("CLS");
            centerText_XY(getxy(true, true), getxy(false, true) - 3, "Sorry, your screen is too small");
            centerText_XY(getxy(true, true), getxy(false, true) - 2, "min character width: 112");
            centerText_XY(getxy(true, true), getxy(false, true) - 1, "min character height: 35");
            centerText_XY(getxy(true, true), getxy(false, true), "min recommended res: 1280x720");
            centerText_XY(getxy(true, true), getxy(false, true) + 1, "your character width: "); std::cout << x;
            centerText_XY(getxy(true, true), getxy(false, true) + 2, "your character width: "); std::cout << y;
            gotoxy(0, getxy(false, true) + 3);
            colour(0);
            colour(1);
            cursor(true);
            exit(-1);
        }
    }

    bool checkFileExists(const std::string& name)
    {
        std::ifstream f(name.c_str());

        if (f.good() == false)
        {
            system("CLS");
            cursor(false);
            const char* msg = "Sorry but you're missing: ";
            std::string temp = msg + name;
            const char* err = temp.c_str();
            centerText_XY(getxy(true, true), getxy(false, true), err);
            std::cin.get();
            cursor(true);
            exit(-1);
        }
        else { return f.good(); }
    }
#endif
