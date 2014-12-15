#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include "Timer.h"

int main(int argc, char* argv[])
{
	// chiedo tempo di refresh
	std::cout << "Tempo di refresh (in secondi):" << std::endl;
	int secondi;
	std::cin >> secondi;

	Timer t = Timer(secondi);
	t.Start();
	
	while (t.Going())
	{
		if (getchar() == 'S' || getchar() == 's')
			t.Stop();
	}
	
	return 0;
}