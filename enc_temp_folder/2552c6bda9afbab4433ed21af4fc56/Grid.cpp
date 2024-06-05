#include "Grid.h"

void Cell::CheckCollisionsWith(Cell& neighbour, float dt)
{
	for (int i = 0; i < CirclesCount; i++)
	{
		for (int j = 0; j < neighbour.CirclesCount; j++)
		{
			Circles[i]->Collision(neighbour.Circles[j], dt);
		}
	}
}

Grid::Grid()
{
	m_Cells = new Cell[Grid::CELL_COUNT];
}

Grid::~Grid()
{
	delete[] m_Cells;
}

Cell* Grid::GetCellAtPosition(unsigned int x, unsigned int y)
{
	if (x > WORLD_SIZE_X || y > WORLD_SIZE_Y) return nullptr;

	unsigned int i = floor(((float)x / WORLD_SIZE_X) * Grid::ROWS);
	unsigned int j = floor(((float)y / WORLD_SIZE_Y) * Grid::COLUMNS);

	return &m_Cells[i + j * Grid::ROWS];
}

void Grid::Update(Circle* allCircles, unsigned int numCircles)
{
	for (int i = 0; i < numCircles; i++)
	{
		Circle* circle = &allCircles[i];
		Cell* cell = GetCellAtPosition(circle->Position.x, circle->Position.y);

		if (!cell) continue;
		if (cell->CirclesCount >= MAX_CIRCLES_IN_CELL) continue;

		cell->Circles[cell->CirclesCount] = circle;
		cell->CirclesCount++;
	}
}

void Grid::HandleCollisions(float dt)
{
	for (int i = 0; i < Grid::CELL_COUNT; i++)
	{
#define INEFFICIENT 0
#if INEFFICIENT
		if (i < ROWS || i > ROWS * (COLUMNS - 1) || i % ROWS == 0 || (i + 1) % ROWS == 0)
			continue;

		m_Cells[i].CheckCollisionsWith(m_Cells[i], dt);

		m_Cells[i].CheckCollisionsWith(m_Cells[i + 1], dt);
		m_Cells[i].CheckCollisionsWith(m_Cells[i - 1], dt);
		m_Cells[i].CheckCollisionsWith(m_Cells[i + ROWS], dt);
		m_Cells[i].CheckCollisionsWith(m_Cells[i - ROWS], dt);

		m_Cells[i].CheckCollisionsWith(m_Cells[i + ROWS + 1], dt);
		m_Cells[i].CheckCollisionsWith(m_Cells[i + ROWS - 1], dt);
		m_Cells[i].CheckCollisionsWith(m_Cells[i - ROWS + 1], dt);
		m_Cells[i].CheckCollisionsWith(m_Cells[i - ROWS - 1], dt);

#else
		m_Cells[i].CheckCollisionsWith(m_Cells[i], dt);

		if ((i + 1) % ROWS != 0) 
			m_Cells[i].CheckCollisionsWith(m_Cells[i + 1], dt);

		if (i >= ROWS)
			m_Cells[i].CheckCollisionsWith(m_Cells[i - ROWS + 1], dt);

		if (i < ROWS * (COLUMNS - 1))
		{
			m_Cells[i].CheckCollisionsWith(m_Cells[i + ROWS], dt);
			if ((i + 1) % ROWS != 0)
				m_Cells[i].CheckCollisionsWith(m_Cells[i + ROWS + 1], dt);
		}
#endif

		m_Cells[i].CirclesCount = 0;
	}
}
