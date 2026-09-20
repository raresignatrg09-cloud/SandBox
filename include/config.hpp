#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

inline constexpr unsigned int CELL_SIZE = 10;
inline constexpr unsigned int ROWS = 80;
inline constexpr unsigned int COLS = 100;
inline constexpr unsigned int WINDOW_HEIGHT = ROWS * CELL_SIZE;
inline constexpr unsigned int WINDOW_WIDTH  = COLS * CELL_SIZE;
inline const char* TITLE = "SandBox";

namespace ColorPalette
{
    inline const std::vector<sf::Color> sandColorPalette = {
        sf::Color(200, 200, 100),
        sf::Color(180, 180, 80),
        sf::Color(220, 220, 120)
    };

	inline const std::vector<sf::Color> waterColorPalette = {
		sf::Color(0, 0, 255),
		sf::Color(0, 100, 255),
		sf::Color(0, 150, 255)
	};

	inline const std::vector<sf::Color> acidColorPalette = {
		sf::Color(0, 255, 0),
		sf::Color(0, 200, 0),
		sf::Color(0, 150, 0)
	};

	inline const std::vector<sf::Color> lavaColorPalette = {
		sf::Color(255, 100, 0),
		sf::Color(255, 50, 0),
		sf::Color(200, 50, 0)
	};

	inline const std::vector<sf::Color> magmaColorPalette = {
		sf::Color(255, 80, 0),
		sf::Color(255, 40, 0),
		sf::Color(200, 30, 0)
	};

	inline const std::vector<sf::Color> mercuryColorPalette = {
		sf::Color(150, 150, 255),
		sf::Color(100, 100, 200),
		sf::Color(50, 50, 150)
	};

	inline const std::vector<sf::Color> woodColorPalette = {
		sf::Color(139, 69, 19),
		sf::Color(160, 82, 45),
		sf::Color(205, 133, 63)
	};

	inline const std::vector<sf::Color> sawdustColorPalette = {
		sf::Color(222, 184, 135),
		sf::Color(210, 180, 140),
		sf::Color(244, 164, 96)
	};

	inline const std::vector<sf::Color> saltColorPalette = {
		sf::Color(255, 255, 255),
		sf::Color(240, 240, 240),
		sf::Color(220, 220, 220)
	};

	inline const std::vector<sf::Color> coalColorPalette = {
		sf::Color(50, 50, 50),
		sf::Color(30, 30, 30),
		sf::Color(10, 10, 10)
	};

	inline const std::vector<sf::Color> stoneColorPalette = {
		sf::Color(120, 120, 120),
		sf::Color(100, 100, 100),
		sf::Color(80, 80, 80)
	};

	inline const std::vector<sf::Color> smokeColorPalette = {
		sf::Color(200, 200, 200),
		sf::Color(150, 150, 150),
		sf::Color(100, 100, 100)
	};
	inline const std::vector<sf::Color> fireColorPalette = {
		sf::Color(240,127,19),
		sf::Color(242,125,12),
		sf::Color(255,191,0)
	};
	inline const std::vector<sf::Color> iceColorPalette = {
		sf::Color(200, 200, 255),
		sf::Color(150, 150, 200),
		sf::Color(100, 100, 150)
	};
}
