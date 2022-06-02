#include <iostream>
#include <conio.h>

#include "Definitions.h"
#include "Parallelepiped.h"

using namespace std;



int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "SDL initialization failed. SDL Error: " << SDL_GetError();
	}
	else
	{
		std::cout << "SDL initialization succeeded!";
	}

	SDL_Window* win = SDL_CreateWindow("lab5", 20, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	if (win == NULL)
		std::cout << "Error with window";
	SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == NULL)
		std::cout << "Error with renderer";

	Parallelepiped par;
	Parallelepiped* isPar;

	while (1) {

		isPar = par.createParallelepipedWithIsometricalProjection();
		isPar->rerenderParallelepipiped(ren);
		delete(isPar);

		char c = _getch();
		std::cout << c;

		switch (c) {
		case 'w':
			par.moveReverseAxis('y');
			break;
		case 's':
			par.moveAlongAxis('y');
			break;
		case 'd':
			par.moveAlongAxis('x');
			break;
		case 'a':
			par.moveReverseAxis('x');
			break;
		case 'e':
			par.moveReverseAxis('z');
			par.printCenterCoordZ();
			break;
		case 'q':
			par.moveAlongAxis('z');
			par.printCenterCoordZ();
			break;
		case 'x':
			par.incraseScale();
			break;
		case 'z':
			par.decreaseScale();
			break;
		case 'i':
			par.rotateCounterclockwise('x');
			break;
		case 'o':
			par.rotateClockwise('x');
			break;
		case 'k':
			par.rotateCounterclockwise('y');
			break;
		case 'l':
			par.rotateClockwise('y');
			break;
		case 'n':
			par.rotateClockwise('z');
			break;
		case 'm':
			par.rotateCounterclockwise('z');
			break;
		case '1':
			return 0;
		default:
			std::cout << std::endl << "Wrong key!" << std::endl;
		}
	}

	return 0;
}

