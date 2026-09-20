#include <headers/Grid.h>
#include <helperFunctions.hpp>
#include <cmath>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <imgui.h>
#include <print>

Grid::Grid(int rows, int cols) 
	: rows(rows), cols(cols),
	m_vertices(sf::PrimitiveType::Triangles)
{
	m_grid.resize(static_cast<std::vector<Cell, std::allocator<Cell>>::size_type>(rows) * cols);

	std::srand(static_cast<unsigned>(std::time(nullptr)));

	for (int row = 0; row < rows; ++row)
		for (int col = 0; col < cols; ++col)
			m_grid[getVectorIndex(row, col)].type = CellType::Air;
}

void Grid::draw(sf::RenderWindow& window)
{
	m_vertices.clear();
	m_vertices.resize(static_cast<size_t>(rows) * cols * 6);

	for (int row = 0; row < rows; ++row)
	{
		for (int col = 0; col < cols; ++col)
		{
			Cell& cell = getCell(row, col);

			if (cell.type == CellType::Air)
				continue;

			float x = static_cast<float>(col) * CELL_SIZE;
			float y = static_cast<float>(row) * CELL_SIZE;

			sf::Color cellColor;

			if (seeTemperature)
			{
				float heatFactor = std::clamp(
					(cell.temperature - 20.f) / 980.f,
					0.f,
					1.f
				);

				if (heatFactor < 0.5f)
				{
					// Black -> Red
					float t = heatFactor * 2.f;

					cellColor = sf::Color(
						static_cast<std::uint8_t>(255 * t),
						0,
						0
					);
				}
				else
				{
					// Red -> Yellow
					float t = (heatFactor - 0.5f) * 2.f;

					cellColor = sf::Color(
						255,
						static_cast<std::uint8_t>(255 * t),
						0
					);
				}
			}
			else
			{
				cellColor = cell.color;
			}

			m_vertices.append(sf::Vertex({ x, y }, cellColor));
			m_vertices.append(sf::Vertex({ x + CELL_SIZE, y }, cellColor));
			m_vertices.append(sf::Vertex({ x + CELL_SIZE, y + CELL_SIZE }, cellColor));
			m_vertices.append(sf::Vertex({ x, y }, cellColor));
			m_vertices.append(sf::Vertex({ x + CELL_SIZE, y + CELL_SIZE }, cellColor));
			m_vertices.append(sf::Vertex({ x, y + CELL_SIZE }, cellColor));
		}
	}

	window.draw(m_vertices);
}

void Grid::update(sf::RenderWindow& window)
{
	brushCell(window);
	updateCell();
	updateTemperature();
	updateReactions();
}

void Grid::brushCell(sf::RenderWindow& window)
{
	if (!ImGui::GetIO().WantCaptureMouse &&
		sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);

		int mouseRow = mousePos.y / CELL_SIZE;
		int mouseCol = mousePos.x / CELL_SIZE;

		const int radius = brushSize;

		int minRow = std::max(0, mouseRow - radius);
		int maxRow = std::min(rows - 1, mouseRow + radius);

		int minCol = std::max(0, mouseCol - radius);
		int maxCol = std::min(cols - 1, mouseCol + radius);

		for (int row = minRow; row <= maxRow; ++row)
		{
			for (int col = minCol; col <= maxCol; ++col)
			{
				int distance =
					std::abs(mouseRow - row) +
					std::abs(mouseCol - col);

				if (distance <= radius)
					placeCell(row, col);
			}
		}
	}
}

void Grid::updateCell()
{
	for (int row = rows - 2; row >= 0; --row)
	{
		int leftToRight = std::rand() % 2;

		if (leftToRight)
		{
			for (int col = 0; col < cols; ++col)
			{
				Cell& currentCell = getCell(row, col);

				updateCurrentCell(currentCell, row, col);
			}
		}
		else
		{
			for (int col = cols - 1; col >= 0; --col)
			{
				Cell& currentCell = getCell(row, col);

				updateCurrentCell(currentCell, row, col);
			}
		}
	}
}

void Grid::updateSand(int row, int col)
{
	// Down
	if (tryMove(row, col, 1, 0))
		return;

	// Diagonal
	if (std::rand() % 2)
	{
		if (tryMove(row, col, 1, -1))
			return;

		if (tryMove(row, col, 1, 1))
			return;
	}
	else
	{
		if (tryMove(row, col, 1, 1))
			return;

		if (tryMove(row, col, 1, -1))
			return;
	}
}

void Grid::updateWater(int row, int col)
{
	// Down
	if (tryMove(row, col, 1, 0))
		return;

	// Diagonal
	if (std::rand() % 2)
	{
		if (tryMove(row, col, 1, -1))
			return;

		if (tryMove(row, col, 1, 1))
			return;
	}
	else
	{
		if (tryMove(row, col, 1, 1))
			return;

		if (tryMove(row, col, 1, -1))
			return;
	}

	// Horizontal
	if (std::rand() % 2)
	{
		if (tryMove(row, col, 0, -1))
			return;

		if (tryMove(row, col, 0, 1))
			return;
	}
	else
	{
		if (tryMove(row, col, 0, 1))
			return;

		if (tryMove(row, col, 0, -1))
			return;
	}
}

void Grid::updateAcid(int row, int col)
{
	if(tryAcidEat(row, col))
		return;

	updateWater(row, col);
}

void Grid::updateSmoke(int row, int col)
{
    // Up
    if (tryMove(row, col, -1, 0))
        return;

    // Diagonal up
    if (std::rand() % 2)
    {
        if (tryMove(row, col, -1, -1))
            return;

        if (tryMove(row, col, -1, 1))
            return;
    }
    else
    {
        if (tryMove(row, col, -1, 1))
            return;

        if (tryMove(row, col, -1, -1))
            return;
    }

    // Horizontal
    if (std::rand() % 2)
    {
        if (tryMove(row, col, 0, -1))
            return;

        if (tryMove(row, col, 0, 1))
            return;
    }
    else
    {
        if (tryMove(row, col, 0, 1))
            return;

        if (tryMove(row, col, 0, -1))
            return;
    }
}

void Grid::updateTemperature()
{
	for (int row = 0; row < rows; ++row)
	{
		for (int col = 0; col < cols; ++col)
		{
			Cell& cell = getCell(row, col);

			if (cell.temperature > 20.f)
				cell.temperature -= 0.1f; // Cool down over time

			// Right
			if (col < cols - 1)
			{
				Cell& other = getCell(row, col + 1);

				float difference = cell.temperature - other.temperature;
				float transfer = difference * 0.05f;

				cell.temperature -= transfer;
				other.temperature += transfer;
			}

			// Down
			if (row < rows - 1)
			{
				Cell& other = getCell(row + 1, col);

				float difference = cell.temperature - other.temperature;
				float transfer = difference * 0.05f;

				cell.temperature -= transfer;
				other.temperature += transfer;
			}
		}
	}
}

void Grid::updateReactions()
{	
	for (int row = 0; row < rows; ++row)
	{
		for (int col = 0; col < cols; ++col)
		{
			Cell& cell = getCell(row, col);

			if (cell.type == CellType::Lava)
			{
				cell.temperature = 2000.f;
			}

			if (cell.type == CellType::Ice && cell.temperature > 0.f)
			{
				cell.setType(CellType::Water);
			}

			if (cell.type == CellType::Water && cell.temperature < 0.f)
			{
				cell.setType(CellType::Ice);
			}

			if (cell.type == CellType::Water && cell.temperature > 100.f)
			{
				cell.setType(CellType::Smoke);
			}

			if (cell.type == CellType::Lava && cell.temperature < 1000.f)
			{
				cell.setType(CellType::Stone);
			}
		}
	}
}

bool Grid::applyGravity(int row, int col)
{
	Cell& currentCell = getCell(row, col);
	Cell& belowCell = getCell(row + 1, col);

	if (canMoveInto(currentCell, belowCell))
	{
		std::swap(currentCell, belowCell);
		return true;
	}

	return false;
}

void Grid::updateCurrentCell(Cell& currentCell,int row, int col)
{
	switch (currentCell.type)
	{
	case CellType::Sand:
	case CellType::Sawdust:
	case CellType::Salt:
		updateSand(row, col);
		break;
	case CellType::Water:
	case CellType::Mercury:
		updateWater(row, col);
		break;
	case CellType::Smoke:
		updateSmoke(row, col);
		break;
	case CellType::Lava:
		updateWater(row, col);
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
	getCell(row, col).setType(currentCellType);
}

Cell& Grid::getCell(int row, int col)
{
	return m_grid[getVectorIndex(row, col)];
}

void Grid::clearGrid()
{
	for (int row = 0; row < rows; ++row)
	{
		for (int col = 0; col < cols; ++col)
		{
			getCell(row, col).type = CellType::Air;
		}
	}
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

bool Grid::tryMove(int row, int col, int dRow, int dCol)
{
	int newRow = row + dRow;
	int newCol = col + dCol;

	if (newRow < 0 || newRow >= rows || newCol < 0 || newCol >= cols)
		return false;

	Cell& currentCell = getCell(row, col);
	Cell& targetCell  = getCell(newRow, newCol);

	if (canMoveInto(currentCell, targetCell))
	{
		std::swap(currentCell, targetCell);
		return true;
	}

	return false;
}

bool Grid::canMoveInto(const Cell& moving, const Cell& target)
{
	if (target.type == CellType::Air)
		return true;

	if (moving.type == CellType::Sand &&
		(target.type == CellType::Water ||
			target.type == CellType::Acid ||
			target.type == CellType::Lava))
		return true;

	if (moving.type == CellType::Acid &&
		target.type == CellType::Water)
		return true;

	return false;
}