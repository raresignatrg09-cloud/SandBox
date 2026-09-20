#pragma once

#include <SFML/Graphics.hpp>
#include <Cell.hpp>

class Grid
{
public:
	Grid(int rows, int cols);
	void draw(sf::RenderWindow& window);
	void update(sf::RenderWindow& window);
	
	void brushCell(sf::RenderWindow& window);
	void updateCell();
	void updateSand(int row, int col);
	void updateWater(int row, int col);
	void updateAcid(int row, int col);
	void updateSmoke(int row, int col);
	void updateTemperature();
	void updateReactions();
	void updateCurrentCell(Cell& currentCell, int row, int col);

	bool applyGravity(int row, int col);
	void placeCell(int row, int col);
	void clearGrid();

	void setCurrentCellType(CellType type) { currentCellType = type; }
	void setSeeTemperature(bool see) { seeTemperature = see; }
	void setBrushSize(int size) { brushSize = size; }

	Cell& getCell(int row, int col);
	bool getSeeTemperature() const { return seeTemperature; }

	bool tryMove(int row, int col, int dRow, int dCol);

	bool tryAcidEat(int row, int col);
	bool canMoveInto(const Cell& moving, const Cell& target);

private:
	int rows;
	int cols;
	std::vector<Cell> m_grid;
	CellType currentCellType = CellType::Sand;
	int brushSize = 3;
	bool seeTemperature = false;
	sf::VertexArray m_vertices;
};