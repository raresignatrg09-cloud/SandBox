#pragma once

#include <SFML/Graphics.hpp>
#include <headers/Grid.h>
#include <config.hpp>

class Game
{
public:
	Game();
	void run();

private:
	void eventHandling();
	void draw();
	void update();

private:
	sf::RenderWindow m_window;
	sf::Clock deltaClock;

	Grid m_grid;
	CellType currentCellType = CellType::Sand;
	int brushSize = 3;
};