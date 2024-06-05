#pragma once

#include "Circle.h"

const int CIRCLE_RADIUS = 100;
const int MAX_CIRCLES_IN_CELL = 15;

struct Cell
{
	unsigned int CirclesCount = 0;
	Circle* Circles[MAX_CIRCLES_IN_CELL];

	void CheckCollisionsWith(Cell& neighbour, float dt);
};

class Grid
{
public:
	Grid();
	~Grid();
	
	Cell* GetCellAtPosition(unsigned int x, unsigned int y);
	void Update(Circle* allCircles, unsigned int numCircles);
	void HandleCollisions(float dt);

public:
	static const unsigned int ROWS = WORLD_SIZE_X / (4 * CIRCLE_RADIUS);
	static const unsigned int COLUMNS = WORLD_SIZE_Y / (4 * CIRCLE_RADIUS);
	static const unsigned int CELL_COUNT = Grid::ROWS * Grid::COLUMNS;

private:
	Cell* m_Cells;
};
