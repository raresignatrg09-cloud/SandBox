#include <headers/Game.h>
#include <print>
#include <imgui.h>
#include <imgui-SFML.h>

Game::Game()
	:m_window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), TITLE),
	m_grid(ROWS, COLS)
{
	m_window.setFramerateLimit(60);

	if (!ImGui::SFML::Init(m_window))
		throw std::runtime_error("Failed to initialize ImGui-SFML");
}

void Game::run()
{
	while (m_window.isOpen())
	{
		eventHandling();

		// Update ImGui
		ImGui::SFML::Update(m_window, deltaClock.restart());

		update();
		draw();
	}

	ImGui::SFML::Shutdown();
}

void Game::eventHandling()
{
	while (auto event = m_window.pollEvent())
	{
		ImGui::SFML::ProcessEvent(m_window, *event);

		if (event->is<sf::Event::Closed>())
			m_window.close();

		if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
		{
			switch (keyPressed->code)
			{
			case sf::Keyboard::Key::Escape:
				m_window.close();
				break;
			case sf::Keyboard::Key::C:
				m_grid.clearGrid();
				break;
			case sf::Keyboard::Key::Num1:
				currentCellType = CellType::Sand;
				break;
			case sf::Keyboard::Key::Num2:
				currentCellType = CellType::Water;
				break;
			case sf::Keyboard::Key::Num3:
				currentCellType = CellType::Stone;
				break;
			case sf::Keyboard::Key::Num4:
				currentCellType = CellType::Air;
				break;
			case sf::Keyboard::Key::Num5:
				currentCellType = CellType::Acid;
				break;
			case sf::Keyboard::Key::Num6:
				currentCellType = CellType::Lava;
				break;
			}

			std::println("Current Cell Type: {}", getCellTypeName(currentCellType));

			m_grid.setCurrentCellType(currentCellType);
		}
	}
}

void Game::draw()
{
	m_window.clear();

	m_grid.draw(m_window);

#pragma region ImGui
	ImGui::Begin("SandBox");

	ImGui::Text(
		"Current Cell: %s",
		getCellTypeName(currentCellType).c_str()
	);

	ImGui::Separator();

	if (ImGui::Button("Sand"))
	{
		currentCellType = CellType::Sand;
		m_grid.setCurrentCellType(currentCellType);
	}

	 

	if (ImGui::Button("Water"))
	{
		currentCellType = CellType::Water;
		m_grid.setCurrentCellType(currentCellType);
	}

	if (ImGui::Button("Stone"))
	{
		currentCellType = CellType::Stone;
		m_grid.setCurrentCellType(currentCellType);
	}

	if (ImGui::Button("Air"))
	{
		currentCellType = CellType::Air;
		m_grid.setCurrentCellType(currentCellType);
	}

	if (ImGui::Button("Acid"))
	{
		currentCellType = CellType::Acid;
		m_grid.setCurrentCellType(currentCellType);
	}

	if (ImGui::Button("Lava"))
	{
		currentCellType = CellType::Lava;
		m_grid.setCurrentCellType(currentCellType);
	}

	if (ImGui::Button("Mercury"))
	{
		currentCellType = CellType::Mercury;
		m_grid.setCurrentCellType(currentCellType);
	}

	if (ImGui::Button("Wood"))
	{
		currentCellType = CellType::Wood;
		m_grid.setCurrentCellType(currentCellType);
	}

	if (ImGui::Button("Sawdust"))
	{
		currentCellType = CellType::Sawdust;
		m_grid.setCurrentCellType(currentCellType);
	}

	if (ImGui::Button("Salt"))
	{
		currentCellType = CellType::Salt;
		m_grid.setCurrentCellType(currentCellType);
	}
	if (ImGui::Button("Coal"))
	{
		currentCellType = CellType::Coal;
		m_grid.setCurrentCellType(currentCellType);
	}
	if (ImGui::Button("Clear Grid"))
	{
		m_grid.clearGrid();
	}
	if (ImGui::SliderInt("Brush Size", &brushSize, 1, 10))
	{
		m_grid.setBrushSize(brushSize);
	}

	ImGui::End();

	// Render ImGui
	ImGui::SFML::Render(m_window);
#pragma endregion

	m_window.display();
}

void Game::update()
{
	m_grid.update(m_window);
}