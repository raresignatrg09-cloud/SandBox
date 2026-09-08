#pragma once
#include <headers/Game.h>
#include <config.hpp>
#include <helperFunctions.hpp>
#include <cmath>
#include <algorithm>

Game::Game()
	:m_window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_WIDTH }), TITLE)
{
	m_window.setFramerateLimit(60);

	m_grid.resize(ROWS * COLS);

	for (int row = 0; row < ROWS; ++row)
	{
		for (int col = 0; col < COLS; ++col)
		{
			m_grid[getVectorIndex(row, col)].type = CellType::Air;
		}
	}

	m_grid[getVectorIndex(1, 1)].type = CellType::Sand;
}

void Game::run()
{
	while (m_window.isOpen())
	{
		eventHandling();
		update();
		draw();
	}
}

void Game::eventHandling()
{
	while (auto event = m_window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
			m_window.close();

		
	}
}

void Game::draw()
{
	m_window.clear();

	sf::RectangleShape shape({ CELL_SIZE,CELL_SIZE });
	
	for (int row = 0; row < ROWS; ++row)
	{
		for (int col = 0; col < COLS; ++col)
		{
			CellType& tile = m_grid[getVectorIndex(row, col)].type;

			if (tile == CellType::Air) continue;

			switch (tile)
			{
			case CellType::Sand:
				shape.setFillColor(sf::Color::Yellow);
				break;
			default:
				shape.setFillColor(sf::Color::Black);
				break;
			}

			shape.setPosition({ (float)col*CELL_SIZE,(float)row*CELL_SIZE });

			m_window.draw(shape);
		}
	}

	m_window.display();
}

void Game::update()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);

		int mouseRow = mousePos.y / CELL_SIZE;
		int mouseCol = mousePos.x / CELL_SIZE;

		const int radius = 3;
		for (int row = 0; row < ROWS; ++row)
		{
			for (int col = 0; col < COLS; ++col)
			{
				if (row < 0 || row >= ROWS ||
					col < 0 || col >= COLS)
					continue;

				int distance = std::abs(mouseRow - row) + std::abs(mouseCol - col);

				if (distance < radius)
					m_grid[getVectorIndex(row, col)].type = CellType::Sand;
			}
		}
	}
	
	for (int row = ROWS - 2; row >= 0; --row)
	{
		for (int col = 0; col < COLS; ++col)
		{
			Cell& cell = m_grid[getVectorIndex(row, col)];
			Cell& belowCell = m_grid[getVectorIndex(row + 1, col)];

			if (cell.type == CellType::Sand && belowCell.type == CellType::Air)
			{
				std::swap(cell.type, belowCell.type);
			}
		}
	}
}
