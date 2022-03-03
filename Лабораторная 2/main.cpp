#include <iostream>
#include <math.h>
#include <conio.h>
#include <SDL.h>

#define SHIFT_VALUE 10
#define ROTATE_VALUE double(3) / 180 * M_PI
#define ADD_SCALE 0.2

struct line {
	double x1;
	double y1;
	double x2;
	double y2;
};

class Pentagon {
public:
	Pentagon();
	~Pentagon();
	friend void rerenderPentagon(SDL_Renderer* ren, class Pentagon* pentagon);
	friend void shiftLeft(class Pentagon* pentagon);
	friend void shiftRight(class Pentagon* pentagon);
	friend void shiftUp(class Pentagon* pentagon);
	friend void shiftDown(class Pentagon* pentagon);
	friend void rotate(class Pentagon* pentagon, bool directionFlag);
	friend void changeScale(class Pentagon* pentagon, bool scaleFlag);
	friend void render1(SDL_Renderer* ren, class Pentagon* pentagon);
	friend void render2(SDL_Renderer* ren, class Pentagon* pentagon);
	friend void render3(SDL_Renderer* ren, class Pentagon* pentagon);
	friend void render4(SDL_Renderer* ren, class Pentagon* pentagon);
	friend void render5(SDL_Renderer* ren, class Pentagon* pentagon);
private:
	line* lines = new struct line[5];
};

void rerenderPentagon(SDL_Renderer* ren, class Pentagon* pentagon);
void shiftLeft(class Pentagon* pentagon);
void shiftRight(class Pentagon* pentagon);
void shiftUp(class Pentagon* pentagon);
void shiftDown(class Pentagon* pentagon);
void rotate(class Pentagon* pentagon, bool directionFlag);
void changeScale(class Pentagon* pentagon, bool scaleFlag);


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

	SDL_Window* win = SDL_CreateWindow("lab2", 20, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	if (win == NULL)
		std::cout << "Error with window";
	SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == NULL)
		std::cout << "Error with renderer";

	Pentagon* pentagon = new class Pentagon;

	rerenderPentagon(ren, pentagon);

	while (1) {
		char c = _getch();
		std::cout << c;

		switch (c) {
		case 'w':
			shiftUp(pentagon);
			rerenderPentagon(ren, pentagon);
			break;
		case 's':
			shiftDown(pentagon);
			rerenderPentagon(ren, pentagon);
			break;
		case 'd':
			shiftRight(pentagon);
			rerenderPentagon(ren, pentagon);
			break;
		case 'a':
			shiftLeft(pentagon);
			rerenderPentagon(ren, pentagon);
			break;
		case 'e':
			rotate(pentagon, 1);
			rerenderPentagon(ren, pentagon);
			break;
		case 'q':
			rotate(pentagon, 0);
			rerenderPentagon(ren, pentagon);
			break;
		case 'x':
			changeScale(pentagon, 1);
			rerenderPentagon(ren, pentagon);
			break;
		case 'z':
			changeScale(pentagon, 0);
			rerenderPentagon(ren, pentagon);
			break;

		case '1':
			return 0;
		default:
			std::cout << "Wrong key!" << std::endl;
		}
	}

	delete(pentagon);
	return 0;
}

/*basic values*/
Pentagon::Pentagon() {

	lines[0].x1 = 100;
	lines[0].y1 = 100;
	lines[0].x2 = 100;
	lines[0].y2 = 300;

	lines[1].x1 = 100;
	lines[1].y1 = 100;
	lines[1].x2 = 200;
	lines[1].y2 = 50;

	lines[2].x1 = 200;
	lines[2].y1 = 50;
	lines[2].x2 = 300;
	lines[2].y2 = 100;

	lines[3].x1 = 300;
	lines[3].y1 = 100;
	lines[3].x2 = 300;
	lines[3].y2 = 300;

	lines[4].x1 = 100;
	lines[4].y1 = 300;
	lines[4].x2 = 300;
	lines[4].y2 = 300;

	return;
}

Pentagon::~Pentagon() {
	delete(lines);

	return;
}

void rerenderPentagon(SDL_Renderer* ren, class Pentagon* pentagon) {

	SDL_RenderClear(ren);

	SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
	render1(ren, pentagon);
	render2(ren, pentagon);
	render3(ren, pentagon);
	render4(ren, pentagon);
	render5(ren, pentagon);

	SDL_SetRenderDrawColor(ren, 0, 255, 255, 255);

	for (int i = 0; i < 5; i++)
	{
		SDL_RenderDrawLine(ren, round(pentagon->lines[i].x1), round(pentagon->lines[i].y1),
			round(pentagon->lines[i].x2), round(pentagon->lines[i].y2));
	}

	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);

	SDL_RenderPresent(ren);

	return;
}

void shiftLeft(class Pentagon* pentagon) {

	for (int i = 0; i < 5; i++)
	{
		pentagon->lines[i].x1 -= SHIFT_VALUE;
		pentagon->lines[i].x2 -= SHIFT_VALUE;

		pentagon->lines[i].x1 = pentagon->lines[i].x1;
		pentagon->lines[i].x2 = pentagon->lines[i].x2;
	}
	return;
}

void shiftRight(class Pentagon* pentagon) {

	for (int i = 0; i < 5; i++)
	{
		pentagon->lines[i].x1 += SHIFT_VALUE;
		pentagon->lines[i].x2 += SHIFT_VALUE;

		pentagon->lines[i].x1 = pentagon->lines[i].x1;
		pentagon->lines[i].x2 = pentagon->lines[i].x2;
	}
	return;
}

void shiftUp(class Pentagon* pentagon) {

	for (int i = 0; i < 5; i++)
	{
		pentagon->lines[i].y1 -= SHIFT_VALUE;
		pentagon->lines[i].y2 -= SHIFT_VALUE;

		pentagon->lines[i].y1 = pentagon->lines[i].y1;
		pentagon->lines[i].y2 = pentagon->lines[i].y2;
	}
	return;
}

void shiftDown(class Pentagon* pentagon) {

	for (int i = 0; i < 5; i++)
	{
		pentagon->lines[i].y1 += SHIFT_VALUE;
		pentagon->lines[i].y2 += SHIFT_VALUE;

		pentagon->lines[i].y1 = pentagon->lines[i].y1;
		pentagon->lines[i].y2 = pentagon->lines[i].y2;
	}
	return;
}
/* flag 1 - Counterclockwise, 0 - clockwise*/
void rotate(class Pentagon* pentagon, bool directionFlag) {
	int minusFlag;
	if (directionFlag)
		minusFlag = 1;
	else
		minusFlag = -1;

	//std::cout << std::endl << cos(ROTATE_VALUE) << std::endl << sin(ROTATE_VALUE) << std::endl;

	double centerX = 0, centerY = 0;

	centerX = pentagon->lines[0].x1;
	centerY = pentagon->lines[0].y1;

	for (int i = 0; i < 5; i++) {

		pentagon->lines[i].x1 -= centerX;
		pentagon->lines[i].x2 -= centerX;
		pentagon->lines[i].y1 -= centerY;
		pentagon->lines[i].y2 -= centerY;

		pentagon->lines[i].x1 = pentagon->lines[i].x1 * cos(ROTATE_VALUE) + minusFlag * pentagon->lines[i].y1 * sin(ROTATE_VALUE);
		pentagon->lines[i].y1 = -minusFlag * pentagon->lines[i].x1 * sin(ROTATE_VALUE) + pentagon->lines[i].y1 * cos(ROTATE_VALUE);

		pentagon->lines[i].x2 = pentagon->lines[i].x2 * cos(ROTATE_VALUE) + minusFlag * pentagon->lines[i].y2 * sin(ROTATE_VALUE);
		pentagon->lines[i].y2 = -minusFlag * pentagon->lines[i].x2 * sin(ROTATE_VALUE) + pentagon->lines[i].y2 * cos(ROTATE_VALUE);

		pentagon->lines[i].x1 += centerX;
		pentagon->lines[i].x2 += centerX;
		pentagon->lines[i].y1 += centerY;
		pentagon->lines[i].y2 += centerY;
	}

	return;
}

/*flag 1 - increase scale, flag 0 - decrease scale*/
void changeScale(class Pentagon* pentagon, bool scaleFlag) {
	double changeValue;

	if (scaleFlag) {
		changeValue = 1 + ADD_SCALE;
	}
	else {
		changeValue = 1 - ADD_SCALE;
	}

	double centerX = 0, centerY = 0;

	for (int i = 0; i < 5; i++) {
		centerX += pentagon->lines[i].x1;
		centerY += pentagon->lines[i].y1;
	}

	centerX /= 5;
	centerY /= 5;

	for (int i = 0; i < 5; i++) {
		pentagon->lines[i].x1 = (pentagon->lines[i].x1 - centerX) * changeValue + centerX;
		pentagon->lines[i].x2 = (pentagon->lines[i].x2 - centerX) * changeValue + centerX;
		pentagon->lines[i].y1 = (pentagon->lines[i].y1 - centerX) * changeValue + centerX;
		pentagon->lines[i].y2 = (pentagon->lines[i].y2 - centerX) * changeValue + centerX;
	}
	return;
}

void render1(SDL_Renderer* ren, class Pentagon* pentagon) {

	SDL_RenderDrawLine(ren, pentagon->lines[0].x1 - 10, pentagon->lines[0].y1 + 7, pentagon->lines[0].x1 - 10, pentagon->lines[0].y1 - 7);
	SDL_RenderDrawLine(ren, pentagon->lines[0].x1 - 15, pentagon->lines[0].y1, pentagon->lines[0].x1 - 10, pentagon->lines[0].y1 - 7);
	return;
}

void render2(SDL_Renderer* ren, class Pentagon* pentagon) {

	SDL_RenderDrawLine(ren, pentagon->lines[1].x2 - 15, pentagon->lines[1].y2 + 7, pentagon->lines[1].x2 - 5, pentagon->lines[1].y2 + 7);
	SDL_RenderDrawLine(ren, pentagon->lines[1].x2 - 15, pentagon->lines[1].y2 + 7, pentagon->lines[1].x2 - 5, pentagon->lines[1].y2 - 3);
	SDL_RenderDrawLine(ren, pentagon->lines[1].x2 - 8, pentagon->lines[1].y2 - 7, pentagon->lines[1].x2 - 5, pentagon->lines[1].y2 - 3);
	SDL_RenderDrawLine(ren, pentagon->lines[1].x2 - 13, pentagon->lines[1].y2 - 7, pentagon->lines[1].x2 - 8, pentagon->lines[1].y2 - 7);
	SDL_RenderDrawLine(ren, pentagon->lines[1].x2 - 13, pentagon->lines[1].y2 - 7, pentagon->lines[1].x2 - 15, pentagon->lines[1].y2 - 3);
	return;
}

void render3(SDL_Renderer* ren, class Pentagon* pentagon) {

	SDL_RenderDrawLine(ren, pentagon->lines[2].x2 - 15, pentagon->lines[2].y2 + 7, pentagon->lines[2].x2 - 5, pentagon->lines[2].y2 + 7);
	SDL_RenderDrawLine(ren, pentagon->lines[2].x2 - 15, pentagon->lines[2].y2 - 7, pentagon->lines[2].x2 - 5, pentagon->lines[2].y2 - 7);
	SDL_RenderDrawLine(ren, pentagon->lines[2].x2 - 15, pentagon->lines[2].y2, pentagon->lines[2].x2 - 5, pentagon->lines[2].y2);
	SDL_RenderDrawLine(ren, pentagon->lines[2].x2 - 5, pentagon->lines[2].y2 + 7, pentagon->lines[2].x2 - 5, pentagon->lines[2].y2 - 7);
	return;
}

void render4(SDL_Renderer* ren, class Pentagon* pentagon) {

	SDL_RenderDrawLine(ren, pentagon->lines[3].x2 - 5, pentagon->lines[3].y2 - 7, pentagon->lines[3].x2 - 5, pentagon->lines[3].y2 + 7);
	SDL_RenderDrawLine(ren, pentagon->lines[3].x2 - 15, pentagon->lines[3].y2 - 7, pentagon->lines[3].x2 - 15, pentagon->lines[3].y2);
	SDL_RenderDrawLine(ren, pentagon->lines[3].x2 - 15, pentagon->lines[3].y2, pentagon->lines[3].x2 - 5, pentagon->lines[3].y2);
	return;
}

void render5(SDL_Renderer* ren, class Pentagon* pentagon) {

	SDL_RenderDrawLine(ren, pentagon->lines[4].x1 - 15, pentagon->lines[4].y1 - 7, pentagon->lines[4].x1 - 5, pentagon->lines[4].y1 - 7);
	SDL_RenderDrawLine(ren, pentagon->lines[4].x1 - 15, pentagon->lines[4].y1 - 7, pentagon->lines[4].x1 - 15, pentagon->lines[4].y1);
	SDL_RenderDrawLine(ren, pentagon->lines[4].x1 - 15, pentagon->lines[4].y1, pentagon->lines[4].x1 - 8, pentagon->lines[4].y1);
	SDL_RenderDrawLine(ren, pentagon->lines[4].x1 - 8, pentagon->lines[4].y1, pentagon->lines[4].x1 - 5, pentagon->lines[4].y1 + 2);
	SDL_RenderDrawLine(ren, pentagon->lines[4].x1 - 5, pentagon->lines[4].y1 + 2, pentagon->lines[4].x1 - 5, pentagon->lines[4].y1 + 5);
	SDL_RenderDrawLine(ren, pentagon->lines[4].x1 - 5, pentagon->lines[4].y1 + 5, pentagon->lines[4].x1 - 8, pentagon->lines[4].y1 + 7);
	SDL_RenderDrawLine(ren, pentagon->lines[4].x1 - 8, pentagon->lines[4].y1 + 7, pentagon->lines[4].x1 - 15, pentagon->lines[4].y1 + 7);
	return;
}
