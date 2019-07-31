// HorseRace.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>

class Horse
{
	float distanceCovered;
public:
	std::string name;
	bool hasWon;

	Horse(std::string name)
		: name(name), distanceCovered(0.0f), hasWon(false)
	{
	}

	void Run()
	{ 
		distanceCovered += (rand() % 10) / 10.f;
		
		if (distanceCovered >= 20.f)
			hasWon = true;

		std::cout << *this;
	}

	int GetDistanceCovered() const { return lroundf(distanceCovered); }

	friend std::ostream& operator<<(std::ostream& os, const Horse& h)
	{
		for (int i = 0; i < h.GetDistanceCovered(); ++i)
			os << "=";

		os << h.name << std::endl;
		return os;
	}
};

void ClearConsole(COORD point)
{
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	DWORD dwWritten;
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hStdout, &cbsi);
	FillConsoleOutputCharacter(hStdout, 0, cbsi.dwSize.X * cbsi.dwSize.Y, point, &dwWritten);
	SetConsoleCursorPosition(hStdout, point);
}

int main()
{
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	std::vector<Horse> horses;
	Horse* winner = nullptr;

	SetConsoleTitle(TEXT("Horse Race"));
	srand(GetTickCount());

	horses.push_back(Horse("Moby Dick"));
	horses.push_back(Horse("Inky"));
	horses.push_back(Horse("Saul"));
	horses.push_back(Horse("Pepe"));
	horses.push_back(Horse("Tiki"));

	std::cout << "+============+" << std::endl;
	std::cout << "+ Horse Race +" << std::endl;
	std::cout << "+============+" << std::endl;
	std::cout << std::endl << std::endl;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cbsi);

	while (!winner)
	{
		ClearConsole(cbsi.dwCursorPosition);
		std::cout << "+===================+" << std::endl;

		for (Horse& it : horses)
		{
			it.Run();

			if (it.hasWon && !winner)
				winner = &it;
		}
		std::cout << "+===================+" << std::endl;
		Sleep(1000);
	}

	std::cout << winner->name << " has won the race!" << std::endl;
	getchar();
}