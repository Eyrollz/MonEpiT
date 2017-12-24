#pragma once

#include "Entite.h"


using namespace std;

class Ville
{
public:
	Ville(int largeur, int hauteur, string titre);
	void Action();
	float PlusBas(vector <sf::Vector2f> &points);
	void Trier(vector <sf::Vector2f> &points);
	int  Orient(vector <sf::Vector2f> &points, int i, int j, int k);
	void MajEnvSup(vector <sf::Vector2f> &points, vector<int> &es, int i);
	void MajEnvInf(vector <sf::Vector2f> &points, vector<int> &ei, int i);
	void Tracer(int indice);
	void DeplacerCamera(sf::Event &event);
	void NouvelleEntite(sf::Event &event);
	void CreationEnvConvxe(sf::Event &event);
	void AjoutVille(sf::Event &event);
	vector <int> ConvGraham(vector <sf::Vector2f> &points);

	~Ville();

private :
	sf::RenderWindow *m_window;
	vector<int> m_envSup;
	vector<int> m_envInf;
	string m_mode;
	sf::Text m_texte;
	sf::Font m_font;
	vector <Entite> m_entites;

	vector <sf::Vector2f> m_posVilles;
	vector<sf::CircleShape> m_villes;

	sf::View m_vue;

	float m_fpsCount;
	float m_switchFps;
	float m_fpsSpeed ;
	int m_indiceGraphe;
	sf::Clock clock;
	bool m_updateFps ;
};

