#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <time.h>

using namespace std;
class Entite
{
public:
	Entite();
	~Entite();

	// Le principe d'encapsualtion n'est pas respeccté dans ce cas
	vector <sf::Vector2f> m_posVilles;
	vector <sf::CircleShape> m_ronds;
	sf::ConvexShape m_envConv;
};

