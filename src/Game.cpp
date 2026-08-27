#pragma once
#include <headers/Game.h>
#include <config.hpp>
#include <helperFunctions.hpp>

Game::Game()
	:m_window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_WIDTH }), TITLE)
{
	m_window.setFramerateLimit(60);

	m_grid.resize(ROWS* COLS);
	for (int row = 0; row < ROWS; ++row)
	{
		for (int col = 0; col < COLS; ++col)
		{
			int index = getVectorIndex(row, col);
			m_grid[index].setSize({ CELL_SIZE, CELL_SIZE });
			m_grid[index].setPosition({(float)col * CELL_SIZE, (float)row * CELL_SIZE});
			m_grid[index].setFillColor(sf::Color::White);
			m_grid[index].setOutlineColor(sf::Color::Black);
			m_grid[index].setOutlineThickness(1.f);
		}
	}
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

	for (auto& cell : m_grid)
	{
		m_window.draw(cell);
	}

	m_window.display();
}

void Game::update()
{}
