#include <SFML/Graphics.hpp>
#include <vector>

enum class CellType
{
	Sand,
	Air
};

struct Cell
{
	CellType type;

};

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
	std::vector<Cell> m_grid;

	sf::Vector2i m_previousMouseCell;
};