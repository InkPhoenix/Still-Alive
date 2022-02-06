#pragma once
#include <iostream>
#include <thread>
#include <string>

#ifdef _WIN32
#define _WIN32_WINNT 0x0500  //should've made this comment earlier cuz now i forgot what this is for lol
#include <windows.h>
#endif

#ifdef linux

#endif

////////////////////////////////////////commands////////////////////////////////////////
#ifdef _WIN32
void windowResize_XY(int x, int y)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, x, y, TRUE);
	for (int j = 0; j < 100; ++j) {
		for (int i = 0x41; i < 0x5B; ++i) {}
	}
}
#endif

int wait(const int sec)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(sec));
	return sec;
}

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

#ifdef _WIN32 //TEMPORARY
void gotoxy(int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void cursor(bool c)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 10;
	info.bVisible = c;
	SetConsoleCursorInfo(consoleHandle, &info);
}
#endif

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