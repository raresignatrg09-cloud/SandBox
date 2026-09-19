#pragma once
#include <string>
#include <config.hpp>

enum class CellType
{
	Sand,
	Stone,
	Water,
	Acid,
	Lava,
	Mercury,
	Wood,
	Sawdust,
	Salt,
    Coal,
	Smoke,
	Fire,
	Ice,
	Air
};

inline std::string getCellTypeName(CellType type)
{
    switch (type)
    {
        case CellType::Sand:    return "Sand";
        case CellType::Stone:   return "Stone";
        case CellType::Water:   return "Water";
        case CellType::Acid:    return "Acid";
        case CellType::Air:     return "Air";
	    case CellType::Lava:    return "Lava";
	    case CellType::Mercury: return "Mercury";
	    case CellType::Wood:    return "Wood";
	    case CellType::Sawdust: return "Sawdust";
	    case CellType::Salt:    return "Salt";
	    case CellType::Coal:    return "Coal";
		case CellType::Smoke:   return "Smoke";
		case CellType::Fire:    return "Fire";
		case CellType::Ice:     return "Ice";
    }

    return "Unknown";
}

struct Cell
{
    CellType type = CellType::Air;
    sf::Color color = sf::Color::Black;
	float temperature = 20.0f; // Default temperature in Celsius

    Cell() = default;

    Cell(CellType t) : type(t) {}

    void setType(CellType t)
    {
        type = t;

		using namespace ColorPalette;

		switch (type)
		{
		case CellType::Sand:
			color=sandColorPalette[std::rand() % sandColorPalette.size()];
			temperature = 20.0f; // Reset temperature for sand
			break;
		case CellType::Stone:
			color=stoneColorPalette[std::rand() % stoneColorPalette.size()];
			temperature = 20.0f; // Reset temperature for stone
			break;
		case CellType::Water:
			color=waterColorPalette[std::rand() % waterColorPalette.size()];
			temperature = 20.0f; // Reset temperature for water
			break;
		case CellType::Acid:
			color=acidColorPalette[std::rand() % acidColorPalette.size()];
			temperature = 20.0f; // Reset temperature for acid
			break;
		case CellType::Lava:
			color=lavaColorPalette[std::rand() % lavaColorPalette.size()];
			temperature = 2000.0f; // Set high temperature for lava
			break;
		case CellType::Mercury:
			color=mercuryColorPalette[std::rand() % mercuryColorPalette.size()];
			temperature = 20.0f; // Reset temperature for mercury
			break;
		case CellType::Wood:
			color=woodColorPalette[std::rand() % woodColorPalette.size()];
			temperature = 20.0f; // Reset temperature for wood
			break;
		case CellType::Sawdust:
			color=sawdustColorPalette[std::rand() % sawdustColorPalette.size()];
			temperature = 20.0f; // Reset temperature for sawdust
			break;
		case CellType::Salt:
			color=saltColorPalette[std::rand() % saltColorPalette.size()];
			temperature = 20.0f; // Reset temperature for salt
			break;
		case CellType::Coal:
			color=coalColorPalette[std::rand() % coalColorPalette.size()];
			temperature = 20.0f; // Reset temperature for coal
			break;
		case CellType::Smoke:
			color = sf::Color(128, 128, 128, 128);
			temperature = 20.0f; // Reset temperature for smoke
			break;
		case CellType::Fire:
			color = fireColorPalette[std::rand() % fireColorPalette.size()];
			temperature = 800.0f; 
			break;
		case CellType::Ice:
			color = iceColorPalette[std::rand() % iceColorPalette.size()];
			temperature = -20.0f; // Set low temperature for ice
			break;
		default:
			color=sf::Color::Black;
			break;
		}
    }
};