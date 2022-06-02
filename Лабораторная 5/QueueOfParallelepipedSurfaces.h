#pragma once

#include "ParallelepipedSurface.h"
#include "Parallelepiped.h"

class QueueOfParallelepipedSurfaces {
public:
	QueueOfParallelepipedSurfaces(Parallelepiped& par);
	~QueueOfParallelepipedSurfaces();
	void sortSurfacesByZcoord();
	friend class Parallelepiped;
private:
	ParallelepipedSurface** arr;
};