#pragma once
#include <string>

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
    }

    return "Unknown";
}

struct Cell
{
    CellType type = CellType::Air;

    Cell() = default;

    Cell(CellType t) : type(t) {}

    void setType(CellType t)
    {
        type = t;
    }
};