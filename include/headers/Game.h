#include <SFML/Graphics.hpp>
#include <vector>

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
	std::vector<sf::RectangleShape> m_grid;
};