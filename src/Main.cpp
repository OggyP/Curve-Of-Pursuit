#include "Platform/Platform.hpp"
#include "Vectors.hpp"

int main()
{
	util::Platform platform;

#if defined(_DEBUG)
	std::cout << "Hello World!" << std::endl;
#endif

	sf::RenderWindow window;
	window.create(sf::VideoMode(1000, 1000), "SFML works!");
	platform.setIcon(window.getSystemHandle());
	window.setFramerateLimit(60);

	const u_int radius = 10;

	sf::CircleShape shape(radius);
	shape.setOrigin(radius, radius);
	shape.setFillColor(sf::Color::White);

	const u_int fadeSpeed = 60;
	u_int currentFade = fadeSpeed;
	sf::RectangleShape fadeRect;
	fadeRect.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
	fadeRect.setFillColor(sf::Color(0, 0, 0, 10));
	fadeRect.setPosition(sf::Vector2f(0, 0));

	u_int num = 5;

	double angle = (2 * M_PI) / num;

	std::vector<Vector2f> agents;

	for (u_int i = 0; i < num; i++)
	{
		auto centre = window.getSize();
		std::cout << centre.x << std::endl;
		Vector2f agent;
		agent.setVector(i * angle, 0.9 * centre.x / 2);
		agent.x += centre.x / 2;
		agent.y += centre.y / 2;
		agents.push_back(agent);
	}

	sf::Event event;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		currentFade--;
		if (currentFade == 0)
		{
			window.draw(fadeRect);
			currentFade = fadeSpeed;
		}

		std::vector<Vector2f> oldAgents(agents);
		for (u_int i = 0; i < agents.size(); i++)
		{
			auto& agent = agents[i];
			int nextAgentIndex = (i + 1 < agents.size()) ? i + 1 : 0;
			auto& nextAgent = oldAgents[nextAgentIndex];
			Vector2f dir;
			dir.x = nextAgent.x - agent.x;
			dir.y = nextAgent.y - agent.y;
			dir.normaliseVector(1);
			agent.x += dir.x;
			agent.y += dir.y;

			shape.setPosition(agent.x, agent.y);
			window.draw(shape);
		}
		window.display();
	}

	return 0;
}
