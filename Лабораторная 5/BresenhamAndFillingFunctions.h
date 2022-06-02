
#include "Definitions.h"
#include "ArrrayOfPoints.h"
#include "ParallelepipedSurface.h"

void drawBresenhamLine(SDL_Renderer* ren, int x1, int y1, int x2, int y2, ArrayOfPoints* arr);
void fillParallelepiped(SDL_Renderer* ren, ParallelepipedSurface* surface, ArrayOfPoints* arr);
void recursiveFilling(SDL_Renderer* ren, ArrayOfPoints* arr, int x, int y);