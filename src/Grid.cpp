#include <headers/Grid.h>
#include <config.hpp>
#include <helperFunctions.hpp>
#include <cmath>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <imgui.h>
#include <print>

Grid::Grid(int rows, int cols) : rows(rows), cols(cols)
{
	m_grid.resize(ROWS * COLS);

	std::srand(static_cast<unsigned>(std::time(nullptr)));

	for (int row = 0; row < ROWS; ++row)
		for (int col = 0; col < COLS; ++col)
			m_grid[getVectorIndex(row, col)].type = CellType::Air;
}

void Grid::draw(sf::RenderWindow& window)
{
	sf::RectangleShape cellShape({ CELL_SIZE,CELL_SIZE });

	for (int row = 0; row < ROWS; ++row)
	{
		for (int col = 0; col < COLS; ++col)
		{
			CellType tile = getCell(row, col).type;

			float x = static_cast<float>(col) * CELL_SIZE;
			float y = static_cast<float>(row) * CELL_SIZE;

			setTypeColors(cellShape, tile);
			cellShape.setPosition({x,y});
			window.draw(cellShape);
		}
	}
}

void Grid::update(sf::RenderWindow& window)
{
	if (!ImGui::GetIO().WantCaptureMouse && 
		sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);

		int mouseRow = mousePos.y / CELL_SIZE;
		int mouseCol = mousePos.x / CELL_SIZE;

		const int radius = brushSize;
		for (int row = 0; row < ROWS; ++row)
		{
			for (int col = 0; col < COLS; ++col)
			{
				int distance = std::abs(mouseRow - row) + std::abs(mouseCol - col);

				if (distance <= radius)
				{
					placeCell(row, col);
				}
			}
		}
	}

	for (int row = ROWS - 2; row >= 0; --row)
	{
		int leftToRight = std::rand() % 2;

		if (leftToRight)
		{
			for (int col = 0; col < COLS; ++col)
			{
				Cell& currentCell = getCell(row, col);

				updateCurrentCell(currentCell, row, col);
			}
		}
		else
		{
			for (int col = COLS - 1; col >= 0; --col)
			{
				Cell& currentCell = getCell(row, col);

				updateCurrentCell(currentCell, row, col);
			}
		}
	}
}

void Grid::updateSand(int row, int col)
{
	Cell& currentCell = getCell(row, col);

	// Down
	if (applyGravity(row, col))
		return;

	// Diagonal
	if (std::rand() % 2)
	{
		if (tryDownLeft(row, col, currentCell))
			return;

		if (tryDownRight(row, col, currentCell))
			return;
	}
	else
	{
		if (tryDownRight(row, col, currentCell))
			return;

		if (tryDownLeft(row, col, currentCell))
			return;
	}
}

void Grid::updateWater(int row, int col)
{
	Cell& currentCell = getCell(row, col);

	// Down
	if (applyGravity(row, col))
		return;

	// Diagonal
	if (std::rand() % 2)
	{
		if (tryDownLeft(row, col, currentCell))
			return;

		if (tryDownRight(row, col, currentCell))
			return;
	}
	else
	{
		if (tryDownRight(row, col, currentCell))
			return;

		if (tryDownLeft(row, col, currentCell))
			return;
	}

	// Horizontal
	if (std::rand() % 2)
	{
		if (tryLiquidLeft(row, col, currentCell))
			return;

		if (tryLiquidRight(row, col, currentCell))
			return;
	}
	else
	{
		if (tryLiquidRight(row, col, currentCell))
			return;

		if (tryLiquidLeft(row, col, currentCell))
			return;
	}
}

void Grid::updateAcid(int row, int col)
{
	Cell& currentCell = getCell(row, col);

	if(tryAcidEat(row, col))
		return;

	// Down
	if (applyGravity(row, col))
		return;

	// Diagonal
	if (std::rand() % 2)
	{
		if (tryDownLeft(row, col, currentCell))
			return;

		if (tryDownRight(row, col, currentCell))
			return;
	}
	else
	{
		if (tryDownRight(row, col, currentCell))
			return;

		if (tryDownLeft(row, col, currentCell))
			return;
	}

	// Horizontal
	if (std::rand() % 2)
	{
		if (tryLiquidLeft(row, col, currentCell))
			return;

		if (tryLiquidRight(row, col, currentCell))
			return;
	}
	else
	{
		if (tryLiquidRight(row, col, currentCell))
			return;

		if (tryLiquidLeft(row, col, currentCell))
			return;
	}
}

bool Grid::applyGravity(int row, int col)
{
	Cell& currentCell = getCell(row, col);
	Cell& belowCell = getCell(row + 1, col);

	if (canMoveInto(currentCell.type, belowCell.type))
	{
		std::swap(currentCell.type, belowCell.type);
		return true;
	}

	return false;
}

void Grid::updateCurrentCell(Cell& currentCell,int row, int col)
{
	switch (currentCell.type)
	{
	case CellType::Sand:
		updateSand(row, col);
		break;
	case CellType::Water:
	case CellType::Mercury:
	case CellType::Sawdust:
	case CellType::Salt:
		updateWater(row, col);
		break;
	case CellType::Lava:
		updateWater(row, col); // Lava behaves like water for movement
		break;
	case CellType::Acid:
		updateAcid(row, col);
		break;
	case CellType::Stone:
	case CellType::Wood:
	case CellType::Coal:
		break;
	case CellType::Air:
		break;
	}
}

void Grid::placeCell(int row, int col)
{
	std::println("Placing cell at {}, {} type={}",
		row, col, static_cast<int>(currentCellType));

	getCell(row, col).setType(currentCellType);
}

Cell& Grid::getCell(int row, int col)
{
	return m_grid[getVectorIndex(row, col)];
}

void Grid::setTypeColors(sf::RectangleShape& cellShape, CellType type)
{
	switch (type)
	{
	case CellType::Sand:
		cellShape.setFillColor(sf::Color(200, 200, 100));
		break;
	case CellType::Stone:
		cellShape.setFillColor(sf::Color(120, 120, 120));
		break;
	case CellType::Water:
		cellShape.setFillColor(sf::Color(0, 0, 255));
		break;
	case CellType::Acid:
		cellShape.setFillColor(sf::Color(0, 255, 0));
		break;
	case CellType::Lava:
		cellShape.setFillColor(sf::Color(255, 100, 0));
		break;
	case CellType::Mercury:
		cellShape.setFillColor(sf::Color(150, 150, 255));
		break;
	case CellType::Wood:
		cellShape.setFillColor(sf::Color(139, 69, 19));
		break;
	case CellType::Sawdust:
		cellShape.setFillColor(sf::Color(222, 184, 135));
		break;
	case CellType::Salt:
		cellShape.setFillColor(sf::Color(255, 255, 255));
		break;
	case CellType::Coal:
		cellShape.setFillColor(sf::Color(50, 50, 50));
		break;
	default:
		cellShape.setFillColor(sf::Color::Black);
		break;
	}
}

void Grid::clearGrid()
{
	for (int row = 0; row < ROWS; ++row)
		for (int col = 0; col < COLS; ++col)
			getCell(row, col).type = CellType::Air;
}

bool Grid::tryDownLeft(int row, int col, Cell& currentCell)
{
	if (col > 0)
	{
		Cell& target = getCell(row + 1, col - 1);

		if (canMoveInto(currentCell.type, target.type))
		{
			std::swap(currentCell.type, target.type);
			return true;
		}
	}

	return false;
}

bool Grid::tryDownRight(int row, int col, Cell& currentCell)
{
	if (col < COLS - 1)
	{
		Cell& target = getCell(row + 1, col + 1);

		if (canMoveInto(currentCell.type, target.type))
		{
			std::swap(currentCell.type, target.type);
			return true;
		}
	}

	return false;
}

bool Grid::tryLiquidLeft(int row, int col, Cell& currentCell)
{
	const int maxDistance = 4;

	for (int distance = 1; distance <= maxDistance; ++distance)
	{
		int newCol = col - distance;

		if (newCol < 0)
			break;

		Cell& target = getCell(row, newCol);

		if (canMoveInto(currentCell.type, target.type))
		{
			std::swap(currentCell.type, target.type);
			return true;
		}
	}
	return false;
}

bool Grid::tryLiquidRight(int row, int col, Cell& currentCell)
{
	const int maxDistance = 4;

	for (int distance = 1; distance <= maxDistance; ++distance)
	{
		int newCol = col + distance;

		if (newCol >= COLS)
			break;

		Cell& target = getCell(row, newCol);

		if (canMoveInto(currentCell.type, target.type))
		{
			std::swap(currentCell.type, target.type);
			return true;
		}
	}

	return false;
}

bool Grid::tryAcidEat(int row, int col)
{
	Cell& currentCell = getCell(row, col);

	// Below
	Cell& below = getCell(row + 1, col);

	if (below.type != CellType::Air &&
		below.type != CellType::Acid)
	{
		if (std::rand() % 100 < 10) // 10% chance to eat the cell below
		{
			below.type = CellType::Air;
			return true;
		}
	}

	return false;
}

bool Grid::canMoveInto(CellType moving, CellType target)
{
	if (target == CellType::Air)
		return true;

	if (moving == CellType::Sand && (target == CellType::Water || target == CellType::Acid || target == CellType::Lava))
		return true;

	if (moving == CellType::Acid && target == CellType::Water)
		return true;

	return false;
}