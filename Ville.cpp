#include "Ville.h"


Ville::Ville(int largeur, int hauteur, string titre)
{

	m_window = new sf::RenderWindow(sf::VideoMode(largeur, hauteur), titre); //1600 x 900
	
	// On insère des éléments pour que les tableaux ne soient pas vides
	m_envSup.push_back(0);
	m_envInf.push_back(0);

	// On introsuit une toute première structure pour ne pas laisser le tableau vide
	m_indiceGraphe = 0;
	m_mode = "Env Convexe";
	

	Entite temp_entite;
	m_entites.push_back(temp_entite);

	
	m_vue.setCenter(sf::Vector2f(800, 450));
	m_vue.setSize(sf::Vector2f(800, 450));
	
	if (!m_font.loadFromFile("cour.ttf"))
	{
		cout << "error !" << endl;
	}

	m_texte.setFont(m_font);
	m_texte.setString(m_mode);
	m_texte.setFillColor(sf::Color(255, 100, 0, 255));

	 m_fpsCount = 0,
		m_switchFps = 10,
		m_fpsSpeed = 350;
	  m_updateFps = true;
}



float Ville::PlusBas(vector <sf::Vector2f> &points)
{	
	float min = points[0].x;
	for (int i = 1; i < points.size(); i++)
	{	
		if (points[i].x < points[i - 1].x)
			min = points[i].x;
	}
	return min;
}
void Ville::Trier(vector <sf::Vector2f> &points)
{
	int i = 0;
	while (i == 0)
	{
		i = 1;
		for (int i = 1; i < points.size(); i++)
		{
			if (points[i].x < points[i - 1].x)
			{
				float tempX = points[i].x;
				float tempY = points[i].y;

				points[i].x = points[i - 1].x;
				points[i].y = points[i - 1].y;

				points[i - 1].x = tempX;
				points[i - 1].y = tempY;
				i = 0;
			}


		}
	}
}
int Ville::Orient(vector <sf::Vector2f> &points, int i, int j, int k)
{
	float y = m_window->getSize().y;
	

	sf::Vector2f pipj = sf::Vector2f(points[j].x - points[i].x, (y-points[j].y) - (y-points[i].y));
	sf::Vector2f pipk = sf::Vector2f(points[k].x - points[i].x, (y-points[k].y) - (y-points[i].y));

	float det = pipj.x*pipk.y - pipj.y*pipk.x;
	//cout << " deto : " << det << endl;
	
	if (det == 0)
		return 0;
	else if (det > 0)
		return 1;
	else
		return -1;
	
}
void Ville::MajEnvInf(vector <sf::Vector2f> &points, vector<int> &ei, int i)
{
	//cout << "inf" << endl;
	int t = ei.size();
	int j = ei[t - 1];

	ei.pop_back();

	if (ei.empty() == false)
	{
		int k = ei[t - 2];
		if (Orient(points, i, j, k) > 0)
		{
			
			return MajEnvInf(points, ei, i);
		}

	}

	ei.push_back(j);
	ei.push_back(i);


}
void Ville::MajEnvSup(vector <sf::Vector2f> &points, vector<int> &es, int i)
{
	//cout << "sup" << endl;
	//cout << " 1 : " << es.size() << endl;
	int t = es.size();
	int j = es[t-1];
	
	es.pop_back();
	//cout << " 2 : " << es.size() << endl;
	if (es.empty() == false)
	{
		int k = es[t - 2];
		
		if (Orient(points, i, j, k) < 0)
		{
			
			return MajEnvSup(points, es, i);
		}

	}
	
	//cout << " sup : " << m_envSup.size() << " val : " << m_envSup[m_envSup.size() - 1] << endl;
	es.push_back(j);
	es.push_back(i);
	
	//cout << " 3 : " << es.size() << endl;


}

void Ville::Tracer(int indice)
{
	for (int i = 0; i < m_entites[indice].m_posVilles.size(); i++)
	{
		m_window->draw(m_entites[indice].m_envConv);
		m_entites[indice].m_ronds[i].setPosition(m_entites[indice].m_posVilles[i]);
		m_window->draw(m_entites[indice].m_ronds[i]);
	}

}

vector <int> Ville::ConvGraham(vector <sf::Vector2f> &points)
{
	
	
	for (int i =1 ; i < points.size(); i++)
	{
		MajEnvSup(points, m_envSup, i);
		MajEnvInf(points, m_envInf, i);
		//cout << " oo : " << i << endl;
	}

	vector <int> res;
	//cout << " inf : "<<m_envInf.size() << " val : "<< m_envInf[m_envInf.size() - 1]<<endl;
	for (int i = 0; i < m_envInf.size(); i++)
	{
		cout << i << endl;
		res.push_back(m_envInf[i]);
	}
	//cout << " sup : " << m_envSup.size() <<" val : "<< m_envSup[m_envSup.size()-1]<< endl;
	for (int i = m_envSup.size()-2; i >0 ; i--)
	{
		cout << i << endl;
		res.push_back(m_envSup[i]);
	}
	
	return res;
}
void Ville::DeplacerCamera(sf::Event &event)
{
	if (event.type == sf::Event::MouseWheelScrolled)
	{
		if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
		{
			if (event.mouseWheelScroll.delta == 1)
				m_vue.zoom(1.25f);
			else
				m_vue.zoom(0.75f);


		}

	}
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Up)
		{

			if (m_updateFps)
			{
				m_fpsCount += m_fpsSpeed *clock.restart().asSeconds();
			}
			else
				m_fpsCount = 0;
			if (m_fpsCount >= m_switchFps)
			{
				m_vue.move(0, -10);
				m_fpsCount = 0;
			}


		}

		if (event.key.code == sf::Keyboard::Down)
		{

			if (m_updateFps)
			{
				m_fpsCount += m_fpsSpeed *clock.restart().asSeconds();
			}
			else
				m_fpsCount = 0;
			if (m_fpsCount >= m_switchFps)
			{
				m_vue.move(0, 10);
				m_fpsCount = 0;
			}


		}

		if (event.key.code == sf::Keyboard::Left)
		{

			if (m_updateFps)
			{
				m_fpsCount += m_fpsSpeed *clock.restart().asSeconds();
			}
			else
				m_fpsCount = 0;
			if (m_fpsCount >= m_switchFps)
			{
				m_vue.move(-10, 0);
				m_fpsCount = 0;
			}


		}

		if (event.key.code == sf::Keyboard::Right)
		{

			if (m_updateFps)
			{
				m_fpsCount += m_fpsSpeed *clock.restart().asSeconds();
			}
			else
				m_fpsCount = 0;
			if (m_fpsCount >= m_switchFps)
			{
				m_vue.move(10, 0);
				m_fpsCount = 0;
			}

			// fin - Déplacement caméra 
		}
	}

}
void Ville::NouvelleEntite(sf::Event &event)
{
	if (event.key.code == sf::Keyboard::P)
	{
		m_indiceGraphe++;
		m_window->setView(m_vue);

		Entite temp_entite;
		m_entites.push_back(temp_entite);

		vector <int> tempo;
		m_envInf = tempo;
		m_envSup = tempo;

		m_envSup.push_back(0);
		m_envInf.push_back(0);
	}

}
void Ville::CreationEnvConvxe(sf::Event &event)
{
	if (event.key.code == sf::Keyboard::A)
	{

		cout << " Conv : " << endl;

		int r = rand() % 255 + 1;
		int v = rand() % 255 + 1;
		int b = rand() % 255 + 1;

		vector <int> temp = ConvGraham(m_entites[m_indiceGraphe].m_posVilles);
		m_entites[m_indiceGraphe].m_envConv.setPointCount(temp.size());
		m_entites[m_indiceGraphe].m_envConv.setFillColor(sf::Color(r, v, b, 50));

		for (int i = 0; i < temp.size(); i++)
		{
		//cout << " oh " << temp[i] << " ";
		m_entites[m_indiceGraphe].m_envConv.setPoint(i, m_entites[m_indiceGraphe].m_posVilles[temp[i]]);


		}
		cout << endl;
	}
}
void Ville::AjoutVille(sf::Event &event)
{
	if (event.mouseButton.button == sf::Mouse::Left) // Clic Gauche pour ajouter une ville
	{
		sf::CircleShape model = sf::CircleShape(3.f);
		model.setFillColor(sf::Color::White);

		//cout << "Ville x :  " << event.mouseButton.x<< " y :  " << event.mouseButton.y << " ajoutee avec succee !"<<endl;
		sf::Vector2i posSouris_global = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);
		sf::Vector2f posSouris_local = m_window->mapPixelToCoords(posSouris_global);

		m_entites[m_indiceGraphe].m_posVilles.push_back(sf::Vector2f(posSouris_local.x, posSouris_local.y));

		m_entites[m_indiceGraphe].m_ronds.push_back(model);

	}

}

void Ville::Action()
{


	sf::Texture texture;
	if (!texture.loadFromFile("TIPE_3.png"))
	{
		cout << "error !" << endl;
	}

	sf::Sprite sprite;
	sprite.setTexture(texture);
	


	sf::VertexArray quad(sf::LineStrip, 5);
	// on le définit comme un rectangle, placé en (10, 10) et de taille 100x100
	quad[0].position = sf::Vector2f(10, 10);
	quad[1].position = sf::Vector2f(110, 10);
	quad[2].position = sf::Vector2f(110, 110);
	quad[3].position = sf::Vector2f(10, 110);
	quad[4].position = sf::Vector2f(10, 10);
	srand(time(NULL));
	
	

	while (m_window->isOpen())
	{
		sf::Event event;
		while (m_window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_window->close();
			
			if (event.type == sf::Event::MouseButtonReleased)
			{
				// Ajouter une ville
				// Clic Gauche de la Souris
				AjoutVille(event);
			}


			if (event.type == sf::Event::KeyReleased)
			{	
				// Création de l'enveloppe convexe 
				// A
				CreationEnvConvxe(event);

				// Tri des points par abscisse croissante
				// T
				if (event.key.code == sf::Keyboard::T)
				{
					Trier(m_entites[m_indiceGraphe].m_posVilles);
					cout << " Tri effectue avec succee ! " <<endl;	
				}
				// Nouvelle entitée créée 
				// P
				NouvelleEntite(event);
			}


			// Déplacement de la caméra + Zoom 
			// Haut - Bas - Gauche - Droite - Molette 
			DeplacerCamera(event);

		}
		


		m_window->clear();//entre ici 
		m_window->setView(m_vue);
		m_window->draw(sprite);
		for (int i = 0; i < m_entites.size(); i++)
		{
			Tracer(i);

		}
		sf::Vector2f posTexte = m_window->mapPixelToCoords(sf::Vector2i(0,0));
		m_texte.setPosition(posTexte);
		m_window->draw(m_texte);
		m_window->draw(quad);

		m_window->display();// et là
	}

}


Ville::~Ville()
{
}
