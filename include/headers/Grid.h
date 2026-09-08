#pragma once

#include <SFML/Graphics.hpp>
#include <Cell.hpp>

class Grid
{
public:
	Grid(int rows, int cols);
	void draw(sf::RenderWindow& window);
	void update(sf::RenderWindow& window);

	void updateSand(int row, int col);
	void updateWater(int row, int col);
	void updateAcid(int row, int col);
	bool applyGravity(int row, int col);
	void updateCurrentCell(Cell& currentCell,int row, int col);
	void placeCell(int row, int col);

	Cell& getCell(int row, int col);
	void setTypeColors(sf::RectangleShape& cellShape, CellType type);
	void setBrushSize(int size) { brushSize = size; }
	void clearGrid();
	void setCurrentCellType(CellType type) { currentCellType = type; }

	bool tryDownLeft(int row, int col, Cell& currentCell);
	bool tryDownRight(int row, int col, Cell& currentCell);
	bool tryLiquidLeft(int row, int col, Cell& currentCell);
	bool tryLiquidRight(int row, int col, Cell& currentCell);
	bool tryAcidEat(int row, int col);

	bool canMoveInto(CellType moving, CellType target);

private:
	int rows;
	int cols;
	std::vector<Cell> m_grid;
	CellType currentCellType = CellType::Sand;
	int brushSize = 3;
};