#include <iostream>
#include <math.h>
#include <conio.h>
#include <SDL.h>

#define SHIFT_VALUE 10
#define ROTATE_VALUE double(20) / 180 * M_PI
#define ADD_SCALE 0.2

struct line {
	int x1;
	int y1;
	int x2;
	int y2;
};

void rerenderLines(SDL_Renderer* ren, line* line1, line* line2);
void shiftLeft(line* line);
void shiftRight(line* line);
void shiftUp(line* line);
void shiftDown(line* line);
void rotateClockwise(line* line);
void rotateCounterclockwise(line* line);
void increaseScale(line* line);
void decreaseScale(line* line);
void drawBresenhamLine(SDL_Renderer* ren, line* line);
void renderLetterA(SDL_Renderer* ren, int pointCoordX, int pointCoordY);
void renderLetterB(SDL_Renderer* ren, int pointCoordX, int pointCoordY);
void renderLetterC(SDL_Renderer* ren, int pointCoordX, int pointCoordY);
void renderLetterD(SDL_Renderer* ren, int pointCoordX, int pointCoordY);

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

	SDL_Window* win = SDL_CreateWindow("lab1", 20, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	if (win == NULL)
		std::cout << "Error with window";
	SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == NULL)
		std::cout << "Error with renderer";

	struct line* line1 = new struct line;
	struct line* line2 = new struct line;

	/*basic values*/
	line1->x1 = 100;
	line1->y1 = 100;
	line1->x2 = 100;
	line1->y2 = 300;

	line2->x1 = 300;
	line2->y1 = 100;
	line2->x2 = 300;
	line2->y2 = 300;

	rerenderLines(ren, line1, line2);

	while (1) {
		char c = _getch();
		std::cout << c;
		switch (c) {
		case 'w':
			shiftUp(line1);
			rerenderLines(ren, line1, line2);
			break;
		case 's':
			shiftDown(line1);
			rerenderLines(ren, line1, line2);
			break;
		case 'd':
			shiftRight(line1);
			rerenderLines(ren, line1, line2);
			break;
		case 'a':
			shiftLeft(line1);
			rerenderLines(ren, line1, line2);
			break;
		case 'e':
			rotateClockwise(line1);
			rerenderLines(ren, line1, line2);
			break;
		case 'q':
			rotateCounterclockwise(line1);
			rerenderLines(ren, line1, line2);
			break;
		case 'x':
			increaseScale(line1);
			rerenderLines(ren, line1, line2);
			break;
		case 'z':
			decreaseScale(line1);
			rerenderLines(ren, line1, line2);
			break;


		case 'i':
			shiftUp(line2);
			rerenderLines(ren, line1, line2);
			break;
		case 'j':
			shiftLeft(line2);
			rerenderLines(ren, line1, line2);
			break;
		case 'k':
			shiftDown(line2);
			rerenderLines(ren, line1, line2);
			break;
		case 'l':
			shiftRight(line2);
			rerenderLines(ren, line1, line2);
			break;
		case 'o':
			rotateClockwise(line2);
			rerenderLines(ren, line1, line2);
			break;
		case 'u':
			rotateCounterclockwise(line2);
			rerenderLines(ren, line1, line2);
			break;
		case 'm':
			increaseScale(line2);
			rerenderLines(ren, line1, line2);
			break;
		case 'n':
			decreaseScale(line2);
			rerenderLines(ren, line1, line2);
			break;

		case '1':
			return 0;
		default:
			std::cout << "Wrong key!" << std::endl;
		}
	}


	return 0;
}

void rerenderLines(SDL_Renderer* ren, line* line1, line* line2) {

	SDL_RenderClear(ren);
	
	SDL_SetRenderDrawColor(ren, 0, 255, 255, 255);
	SDL_RenderDrawLine(ren, line1->x1, line1->y1, line1->x2, line1->y2);

	SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
	renderLetterA(ren, line1->x1, line1->y1);
	renderLetterB(ren, line1->x2, line1->y2);
	renderLetterC(ren, line2->x1, line2->y1);
	renderLetterD(ren, line2->x2, line2->y2);

	SDL_SetRenderDrawColor(ren, 255, 255, 0, 255);
	drawBresenhamLine(ren, line2);

	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);

	SDL_RenderPresent(ren);

	return;
}

void shiftLeft(line* line) {
	line->x1 = line->x1 - SHIFT_VALUE;
	line->x2 = line->x2 - SHIFT_VALUE;
	return;
}

void shiftRight(line* line) {
	line->x1 = line->x1 + SHIFT_VALUE;
	line->x2 = line->x2 + SHIFT_VALUE;
	return;
}

void shiftUp(line* line) {
	line->y1 = line->y1 - SHIFT_VALUE;
	line->y2 = line->y2 - SHIFT_VALUE;
	return;
}

void shiftDown(line* line) {
	line->y1 = line->y1 + SHIFT_VALUE;
	line->y2 = line->y2 + SHIFT_VALUE;
	return;
}

void rotateClockwise(line* line) {
	int deltaX = line->x2 - line->x1;
	int deltaY = line->y2 - line->y1;
	line->x2 = round(deltaX * cos(ROTATE_VALUE) - deltaY * sin(ROTATE_VALUE) + line->x1);
	line->y2 = round(deltaX * sin(ROTATE_VALUE) + deltaY * cos(ROTATE_VALUE) + line->y1);
	return;
}

void rotateCounterclockwise(line* line) {
	int deltaX = line->x2 - line->x1;
	int deltaY = line->y2 - line->y1;
	line->x2 = round(deltaX * cos(ROTATE_VALUE) + deltaY * sin(ROTATE_VALUE) + line->x1);
	line->y2 = round(- deltaX * sin(ROTATE_VALUE) + deltaY * cos(ROTATE_VALUE) + line->y1);
	return;
}

void increaseScale(line* line) {
	int centerX = (line->x1 + line->x2) / 2;
	int centerY = (line->y1 + line->y2) / 2;

	line->x1 = (line->x1 - centerX) * (1 + ADD_SCALE) + centerX;
	line->x2 = (line->x2 - centerX) * (1 + ADD_SCALE) + centerX;
	line->y1 = (line->y1 - centerY) * (1 + ADD_SCALE) + centerY;
	line->y2 = (line->y2 - centerY) * (1 + ADD_SCALE) + centerY;

	return;
}

void decreaseScale(line* line) {
	int centerX = (line->x1 + line->x2) / 2;
	int centerY = (line->y1 + line->y2) / 2;

	line->x1 = (line->x1 - centerX) * (1 - ADD_SCALE) + centerX;
	line->x2 = (line->x2 - centerX) * (1 - ADD_SCALE) + centerX;
	line->y1 = (line->y1 - centerY) * (1 - ADD_SCALE) + centerY;
	line->y2 = (line->y2 - centerY) * (1 - ADD_SCALE) + centerY;

	return;
}

/*draw line using Bresenham alorythm*/
void drawBresenhamLine(SDL_Renderer* ren, line* line) {

	int startX, startY, endX, endY;

	/*find start and end point*/
	if (line->x1 < line->x2) {
		startX = line->x1;
		startY = line->y1;
		endX = line->x2;
		endY = line->y2;
	}
	else if (line->x2 < line->x1) {
		startX = line->x2;
		startY = line->y2;
		endX = line->x1;
		endY = line->y1;
	}
	else{
		if (line->y1 < line->y2) {
			startX = line->x1;
			startY = line->y1;
			endX = line->x2;
			endY = line->y2;
		}
		else {
			startX = line->x2;
			startY = line->y2;
			endX = line->x1;
			endY = line->y1;
		}
	}

	int deltaX = endX - startX;
	int deltaY = endY - startY;

	double tang = 0; // tan of angle
	double mistake = 0;

	SDL_RenderDrawPoint(ren, startX, startY);
	/*draw line*/
	if (abs(deltaY) < abs(deltaX)) {

		tang = (double)deltaY / (double)deltaX;

		for (int x = startX, y = startY; x < endX; x++) {
			SDL_RenderDrawPoint(ren, x, y);
			mistake += tang;
			if (tang > 0){
				if (mistake > 0.5) {
					y++;
					mistake -= 1;
				}
			}
			else {
				if (mistake < -0.5) {
					y--;
					mistake += 1;
				}
			}
		}
	}
	else {

		tang = (double)deltaX / (double)deltaY;
		if (startY < endY)
			for (int y = startY, x = startX; y < endY; y++) {
				SDL_RenderDrawPoint(ren, x, y);
				mistake += tang;
				if (mistake > 0.5) {
						x++;
						mistake -= 1;
				}
			}
		else
			for (int y = startY, x = startX; y > endY; y--) {
				SDL_RenderDrawPoint(ren, x, y);
				mistake += tang;
				if (mistake < -0.5) {
					x++;
					mistake += 1;
				}
			}
	}
	
	return;
}

/*render letter left from the point*/
void renderLetterA(SDL_Renderer* ren, int pointCoordX, int pointCoordY) {

	SDL_RenderDrawLine(ren, pointCoordX - 15, pointCoordY + 7, pointCoordX - 10, pointCoordY - 7);
	SDL_RenderDrawLine(ren, pointCoordX - 5, pointCoordY + 7, pointCoordX - 10, pointCoordY - 7);
	SDL_RenderDrawLine(ren, pointCoordX - 12, pointCoordY + 1, pointCoordX - 8, pointCoordY + 1);

	return;
}

void renderLetterB(SDL_Renderer* ren, int pointCoordX, int pointCoordY) {

	SDL_RenderDrawLine(ren, pointCoordX - 15, pointCoordY + 7, pointCoordX - 15, pointCoordY - 7);
	SDL_RenderDrawLine(ren, pointCoordX - 15, pointCoordY - 7, pointCoordX - 7, pointCoordY - 7);
	SDL_RenderDrawLine(ren, pointCoordX - 7, pointCoordY - 7, pointCoordX - 5, pointCoordY - 5);
	SDL_RenderDrawLine(ren, pointCoordX - 5, pointCoordY - 5, pointCoordX - 5, pointCoordY - 2);
	SDL_RenderDrawLine(ren, pointCoordX - 5, pointCoordY - 2, pointCoordX - 7, pointCoordY);
	SDL_RenderDrawLine(ren, pointCoordX - 15, pointCoordY, pointCoordX - 7, pointCoordY);
	SDL_RenderDrawLine(ren, pointCoordX - 7, pointCoordY, pointCoordX - 5, pointCoordY + 2);
	SDL_RenderDrawLine(ren, pointCoordX - 5, pointCoordY + 2, pointCoordX - 5, pointCoordY + 5);
	SDL_RenderDrawLine(ren, pointCoordX - 5, pointCoordY + 5, pointCoordX - 7, pointCoordY + 7);
	SDL_RenderDrawLine(ren, pointCoordX - 15, pointCoordY + 7, pointCoordX - 7, pointCoordY + 7);

	return;
}

void renderLetterC(SDL_Renderer* ren, int pointCoordX, int pointCoordY) {

	SDL_RenderDrawLine(ren, pointCoordX - 5, pointCoordY - 7, pointCoordX - 10, pointCoordY - 7);
	SDL_RenderDrawLine(ren, pointCoordX - 10, pointCoordY - 7, pointCoordX - 15, pointCoordY - 3);
	SDL_RenderDrawLine(ren, pointCoordX - 15, pointCoordY + 3, pointCoordX - 15, pointCoordY - 3);
	SDL_RenderDrawLine(ren, pointCoordX - 15, pointCoordY + 3, pointCoordX - 10, pointCoordY + 7);
	SDL_RenderDrawLine(ren, pointCoordX - 5, pointCoordY + 7, pointCoordX - 10, pointCoordY + 7);

	return;
}
void renderLetterD(SDL_Renderer* ren, int pointCoordX, int pointCoordY) {

	SDL_RenderDrawLine(ren, pointCoordX - 15, pointCoordY + 7, pointCoordX - 15, pointCoordY - 7);
	SDL_RenderDrawLine(ren, pointCoordX - 15, pointCoordY - 7, pointCoordX - 8, pointCoordY - 7);
	SDL_RenderDrawLine(ren, pointCoordX - 8, pointCoordY - 7, pointCoordX - 5, pointCoordY - 3);
	SDL_RenderDrawLine(ren, pointCoordX - 5, pointCoordY - 3, pointCoordX - 5, pointCoordY + 3);
	SDL_RenderDrawLine(ren, pointCoordX - 5, pointCoordY + 3, pointCoordX - 8, pointCoordY + 7);
	SDL_RenderDrawLine(ren, pointCoordX - 15, pointCoordY + 7, pointCoordX - 8, pointCoordY + 7);

	return;
}