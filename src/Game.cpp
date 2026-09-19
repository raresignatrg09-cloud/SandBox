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
	}
}

void Game::draw()
{
	m_window.clear(sf::Color::Black);

	m_grid.draw(m_window);

#pragma region ImGui
	ImGui::Begin("SandBox");

	ImGui::Text(
		"Current Cell: %s",
		getCellTypeName(currentCellType).c_str()
	);

	ImGui::Separator();

	auto setButton = [&](const char* label, CellType type)
		{
			if (ImGui::Button(label))
			{
				currentCellType = type;
				m_grid.setCurrentCellType(currentCellType);
			}
		};

	setButton("Sand", CellType::Sand);
	setButton("Water", CellType::Water);
	setButton("Stone", CellType::Stone);
	setButton("Acid", CellType::Acid);
	setButton("Lava", CellType::Lava);
	setButton("Mercury", CellType::Mercury);
	setButton("Wood", CellType::Wood);
	setButton("Sawdust", CellType::Sawdust);
	setButton("Salt", CellType::Salt);
	setButton("Coal", CellType::Coal);
	setButton("Smoke", CellType::Smoke);
	setButton("Fire", CellType::Fire);
	setButton("Ice", CellType::Ice);

	setButton("Eraser", CellType::Air);
	
	bool seeTemperature = m_grid.getSeeTemperature();
	if (ImGui::Checkbox("See Temperature", &seeTemperature))
	{
		m_grid.setSeeTemperature(seeTemperature);
	}
	if (ImGui::SliderInt("Brush Size", &brushSize, 1, 10))
	{
		m_grid.setBrushSize(brushSize);
	}
	if (ImGui::Button("Clear Grid"))
	{
		m_grid.clearGrid();
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