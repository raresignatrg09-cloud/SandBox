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
	void updateSmoke(int row, int col);
	void updateTemperature();
	void updateReactions();

	bool applyGravity(int row, int col);
	void updateCurrentCell(Cell& currentCell,int row, int col);
	void placeCell(int row, int col);

	Cell& getCell(int row, int col);
	void setBrushSize(int size) { brushSize = size; }
	void clearGrid();
	void setCurrentCellType(CellType type) { currentCellType = type; }
	void setSeeTemperature(bool see) { seeTemperature = see; }
	bool getSeeTemperature() const { return seeTemperature; }

	bool tryDownLeft(int row, int col, Cell& currentCell);
	bool tryDownRight(int row, int col, Cell& currentCell);
	bool tryLiquidLeft(int row, int col, Cell& currentCell);
	bool tryLiquidRight(int row, int col, Cell& currentCell);
	bool tryAcidEat(int row, int col);

	bool tryMove(int row, int col, int dRow, int dCol);

	bool canMoveInto(const Cell& moving, const Cell& target);

private:
	int rows;
	int cols;
	std::vector<Cell> m_grid;
	CellType currentCellType = CellType::Sand;
	int brushSize = 3;
	bool seeTemperature = false;
};