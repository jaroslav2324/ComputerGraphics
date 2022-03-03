#include <iostream>
#include <math.h>
#include <conio.h>
#include <cstring>
#include <SDL.h>

#define SHIFT_VALUE 10
#define ROTATE_VALUE double(3) / 180 * M_PI
#define ADD_SCALE 0.2
#define REALLOC_VAL 50

struct line {
	double x1;
	double y1;
	double x2;
	double y2;
};

struct point {
	int x;
	int y;
};

class Pentagon {
public:
	Pentagon();
	~Pentagon();
	friend void rerenderPentagon(SDL_Renderer* ren, class Pentagon* pentagon, point* pointArr, int currentArrPointsAmount, int arrSize);
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
	friend void fillPentagon(SDL_Renderer* ren, Pentagon* pentagon, point* pointArr, int pointsAmount);
	friend void recursiveFilling(SDL_Renderer* ren, point* pointArr, int pointsAmount, int x, int y);

private:
	line* lines = new struct line[5];
};

void rerenderPentagon(SDL_Renderer* ren, class Pentagon* pentagon, point* pointArr, int currentArrPointsAmount, int arrSize);
void shiftLeft(class Pentagon* pentagon);
void shiftRight(class Pentagon* pentagon);
void shiftUp(class Pentagon* pentagon);
void shiftDown(class Pentagon* pentagon);
void rotate(class Pentagon* pentagon, bool directionFlag);
void changeScale(class Pentagon* pentagon, bool scaleFlag);
bool ifPointInArr(point* pointArr, int pointsAmount, int x, int y);
void addPointToArr(point* pointArr, int pointsAmount, int x, int y);
point* resizePointArr(point* pointArr, int prevSize);
void drawBresenhamLine(SDL_Renderer* ren, line* line, point* pointArr, int currentArrPointsAmount, int arrSize);
void recursiveFilling(SDL_Renderer* ren, point* pointArr, int pointsAmount, int x, int y);


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

	SDL_Window* win = SDL_CreateWindow("lab3", 20, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	if (win == NULL)
		std::cout << "Error with window";
	SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == NULL)
		std::cout << "Error with renderer";

	Pentagon* pentagon = new class Pentagon;

	point* pointArr = new point[REALLOC_VAL];
	static int currentSizeArrPoints = REALLOC_VAL;
	static int currentAmountPoints = 0;

	rerenderPentagon(ren, pentagon, pointArr, currentAmountPoints, currentSizeArrPoints);

	while (1) {
		char c = _getch();
		std::cout << c;

		switch (c) {
		case 'w':
			shiftUp(pentagon);
			rerenderPentagon(ren, pentagon, pointArr, currentAmountPoints, currentSizeArrPoints);
			break;
		case 's':
			shiftDown(pentagon);
			rerenderPentagon(ren, pentagon, pointArr, currentAmountPoints, currentSizeArrPoints);
			break;
		case 'd':
			shiftRight(pentagon);
			rerenderPentagon(ren, pentagon, pointArr, currentAmountPoints, currentSizeArrPoints);
			break;
		case 'a':
			shiftLeft(pentagon);
			rerenderPentagon(ren, pentagon, pointArr, currentAmountPoints, currentSizeArrPoints);
			break;
		case 'e':
			rotate(pentagon, 1);
			rerenderPentagon(ren, pentagon, pointArr, currentAmountPoints, currentSizeArrPoints);
			break;
		case 'q':
			rotate(pentagon, 0);
			rerenderPentagon(ren, pentagon, pointArr, currentAmountPoints, currentSizeArrPoints);
			break;
		case 'x':
			changeScale(pentagon, 1);
			rerenderPentagon(ren, pentagon, pointArr, currentAmountPoints, currentSizeArrPoints);
			break;
		case 'z':
			changeScale(pentagon, 0);
			rerenderPentagon(ren, pentagon, pointArr, currentAmountPoints, currentSizeArrPoints);
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
point* resizePointArr(point* pointArr, int prevSize) {

	prevSize += REALLOC_VAL;
	point* newArr = new point[prevSize];
	memset(newArr, 0, prevSize * sizeof(point));
	memcpy(newArr, pointArr, (prevSize - REALLOC_VAL) * sizeof(point));
	delete pointArr;
	return newArr;
}

void addPointToArr(point* pointArr, int pointsAmount, int x, int y) {
	for (int i = 0; i < pointsAmount; i++) {
		if (pointArr[i].x == x && pointArr[i].y == y)
			return;
	}
	point* newPoint = new point;
	newPoint->x = x;
	newPoint->y = y;
	pointArr[pointsAmount] = *newPoint;
	return;
}

bool ifPointInArr(point* pointArr, int pointsAmount, int x, int y) {
	for (int i = 0; i < pointsAmount; i++) {
		if (pointArr[i].x == x && pointArr[i].y == y)
			return true;
	}
	return false;
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

void rerenderPentagon(SDL_Renderer* ren, class Pentagon* pentagon, point* pointArr, int currentArrPointsAmount, int arrSize) {

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
		drawBresenhamLine(ren, &(pentagon->lines[i]), pointArr, currentArrPointsAmount, arrSize);
		/*
		SDL_RenderDrawLine(ren, round(pentagon->lines[i].x1), round(pentagon->lines[i].y1),
			round(pentagon->lines[i].x2), round(pentagon->lines[i].y2));
			*/
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

void drawBresenhamLine(SDL_Renderer* ren, line* line, point* pointArr, int currentArrPointsAmount, int arrSize) {

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
	else {
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
	if (currentArrPointsAmount == arrSize - 1)
		resizePointArr(pointArr, arrSize);

	if (!ifPointInArr(pointArr, currentArrPointsAmount, startX, startY)) {
		addPointToArr(pointArr, currentArrPointsAmount, startX, startY);
		++currentArrPointsAmount;
	}
	/*draw line*/
	if (abs(deltaY) < abs(deltaX)) {

		tang = (double)deltaY / (double)deltaX;

		for (int x = startX, y = startY; x < endX; x++) {
			SDL_RenderDrawPoint(ren, x, y);

			if (currentArrPointsAmount == arrSize - 1)
				resizePointArr(pointArr, arrSize);

			if (!ifPointInArr(pointArr, currentArrPointsAmount, x, y)) {
				addPointToArr(pointArr, currentArrPointsAmount, x, y);
				++currentArrPointsAmount;
			}

			mistake += tang;
			if (tang > 0) {
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

				if (currentArrPointsAmount == arrSize - 1)
					resizePointArr(pointArr, arrSize);

				if (!ifPointInArr(pointArr, currentArrPointsAmount, x, y)) {
					addPointToArr(pointArr, currentArrPointsAmount, x, y);
					++currentArrPointsAmount;
				}

				mistake += tang;
				if (mistake > 0.5) {
					x++;
					mistake -= 1;
				}
			}
		else
			for (int y = startY, x = startX; y > endY; y--) {
				SDL_RenderDrawPoint(ren, x, y);

				if (currentArrPointsAmount == arrSize - 1)
					resizePointArr(pointArr, arrSize);

				if (!ifPointInArr(pointArr, currentArrPointsAmount, x, y)) {
					addPointToArr(pointArr, currentArrPointsAmount, x, y);
					++currentArrPointsAmount;
				}

				mistake += tang;
				if (mistake < -0.5) {
					x++;
					mistake += 1;
				}
			}
	}

	return;
}

void fillPentagon(SDL_Renderer* ren, Pentagon* pentagon, point* pointArr, int pointsAmount) {

	double centerX = 0, centerY = 0;

	for (int i = 0; i < 5; i++) {
		centerX += pentagon->lines[i].x1 + pentagon->lines[i].x2;
		centerY += pentagon->lines[i].y1 + pentagon->lines[i].y2;
	}

	centerX /= 10;
	centerY /= 10;

	int X = centerX;
	int Y = centerY;

	recursiveFilling(ren, pointArr, pointsAmount, X, Y);

	return;
}

void recursiveFilling(SDL_Renderer* ren, point* pointArr, int pointsAmount,  int x, int y) {

	if (ifPointInArr(pointArr, pointsAmount, x, y))
		return;

	recursiveFilling(ren, pointArr, pointsAmount, x, y + 1);
	recursiveFilling(ren, pointArr, pointsAmount, x, y - 1);
	recursiveFilling(ren, pointArr, pointsAmount, x + 1, y);
	recursiveFilling(ren, pointArr, pointsAmount, x - 1, y);
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
