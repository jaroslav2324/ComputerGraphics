
#include "BresenhamAndFillingFunctions.h"

void drawBresenhamLine(SDL_Renderer* ren, int x1, int y1, int x2, int y2, ArrayOfPoints* arr) {

	int startX, startY, endX, endY;

	/*find start and end point*/
	if (x1 < x2) {
		startX = x1;
		startY = y1;
		endX = x2;
		endY = y2;
	}
	else if (x2 < x1) {
		startX = x2;
		startY = y2;
		endX = x1;
		endY = y1;
	}
	else {
		if (y1 < y2) {
			startX = x1;
			startY = y1;
			endX = x2;
			endY = y2;
		}
		else {
			startX = x2;
			startY = y2;
			endX = x1;
			endY = y1;
		}
	}

	int deltaX = endX - startX;
	int deltaY = endY - startY;

	double tang = 0; // tan of angle
	double mistake = 0;

	SDL_RenderDrawPoint(ren, startX, startY);
	if (arr->amountPoints == arr->sizeArr - 1)
		arr->resizePointArr();


	if (!arr->ifPointInArr(startX, startY)) {
		arr->addPointToArr(startX, startY);
		++arr->amountPoints;
	}

	//SDL_RenderPresent(ren);
	/*draw line*/
	if (abs(deltaY) < abs(deltaX)) {

		tang = (double)deltaY / (double)deltaX;

		for (int x = startX, y = startY; x <= endX; x++) {
			SDL_RenderDrawPoint(ren, x, y);
			//SDL_RenderPresent(ren);

			if (arr->amountPoints == arr->sizeArr - 1)
				arr->resizePointArr();


			if (!arr->ifPointInArr(x, y)) {
				arr->addPointToArr(x, y);
				++arr->amountPoints;
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
			for (int y = startY, x = startX; y <= endY; y++) {
				SDL_RenderDrawPoint(ren, x, y);
				//SDL_RenderPresent(ren);

				if (arr->amountPoints == arr->sizeArr - 1)
					arr->resizePointArr();


				if (!arr->ifPointInArr(x, y)) {
					arr->addPointToArr(x, y);
					++arr->amountPoints;
				}

				mistake += tang;
				if (mistake > 0.5) {
					x++;
					mistake -= 1;
				}
			}
		else
			for (int y = startY, x = startX; y >= endY; y--) {
				SDL_RenderDrawPoint(ren, x, y);
				//SDL_RenderPresent(ren);

				if (arr->amountPoints == arr->sizeArr - 1)
					arr->resizePointArr();


				if (!arr->ifPointInArr(x, y)) {
					arr->addPointToArr(x, y);
					++arr->amountPoints;
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

void fillParallelepiped(SDL_Renderer* ren, ParallelepipedSurface* surface, ArrayOfPoints* arr) {

	double centerX = 0, centerY = 0;

	centerX = (surface->point1->x + surface->point2->x + surface->point3->x + surface->point4->x) / 4;
	centerY = (surface->point1->y + surface->point2->y + surface->point3->y + surface->point4->y) / 4;

	int X = centerX;
	int Y = centerY;

	recursiveFilling(ren, arr, X, Y);

	return;
}

void recursiveFilling(SDL_Renderer* ren, ArrayOfPoints* arr, int x, int y) {

	if (arr->ifPointInArr(x, y))
		return;
	else {
		if (arr->amountPoints == arr->sizeArr - 1)
			arr->resizePointArr();

		arr->addPointToArr(x, y);
		++arr->amountPoints;
	}

	SDL_RenderDrawPoint(ren, x, y);
	//SDL_RenderPresent(ren);

	if (!(arr->ifPointInArr(x + 1, y)))
		recursiveFilling(ren, arr, x + 1, y);

	if (!(arr->ifPointInArr(x, y + 1)))
		recursiveFilling(ren, arr, x, y + 1);

	if (!(arr->ifPointInArr(x, y - 1)))
		recursiveFilling(ren, arr, x, y - 1);

	if (!(arr->ifPointInArr(x - 1, y)))
		recursiveFilling(ren, arr, x - 1, y);

	return;
}