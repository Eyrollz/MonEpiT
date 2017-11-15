#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Ville
{
public:
	Ville(int largeur, int hauteur, string titre);
	void Action();
	float PlusBas(vector <sf::Vector2f> &points);
	void Trier(vector <sf::Vector2f> &points);
	int Orient(vector <sf::Vector2f> &points, int i, int j, int k);
	void MajEnvSup(vector <sf::Vector2f> &points, vector<int> &es, int i);
	void MajEnvInf(vector <sf::Vector2f> &points, vector<int> &ei, int i);
	vector <int> ConvGraham(vector <sf::Vector2f> &points);

	~Ville();

private :
	sf::RenderWindow *m_window;
	vector<int> m_envSup;
	vector<int> m_envInf;
	vector <sf::Vector2f> m_posVilles;
	vector<sf::CircleShape> m_villes;

};

