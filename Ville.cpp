#include "Ville.h"


Ville::Ville(int largeur, int hauteur, string titre)
{

	m_window = new sf::RenderWindow(sf::VideoMode(largeur, hauteur), titre);
	
	m_envSup.push_back(0);
	m_envInf.push_back(0);
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


void Ville::Action()
{
	
	sf::CircleShape temp = sf::CircleShape(10.f);
	temp.setFillColor(sf::Color::Blue);

	sf::ConvexShape convex;

	while (m_window->isOpen())
	{
		sf::Event event;
		while (m_window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_window->close();
			
			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Left) // Clic Gauche pour ajouter une ville
				{
					cout << "Ville x :  " << event.mouseButton.x<< " y :  " << event.mouseButton.y << " ajoutee avec succee !"<<endl;
					m_posVilles.push_back(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
					m_villes.push_back(temp);
				}

				if (event.mouseButton.button == sf::Mouse::Right) // Clic Droit pour les consulter
				{
					for (int i = 0; i < m_posVilles.size() ;i++)
					{
						cout << i + 1 << ") en x : " << m_posVilles[i].x << " en y :" << m_posVilles[i].y << endl;
					}

				}
				
			}

			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::A)
				{

					cout << " Conv : " << endl;
					
					
					vector <int> temp = ConvGraham(m_posVilles);
					convex.setPointCount(temp.size());
					for (int i = 0; i < temp.size(); i++)
					{
						cout << " oh " << temp[i] << " ";
						convex.setPoint(i, m_posVilles[temp[i]]);
						
					}
					cout<<endl;
				}
				if (event.key.code == sf::Keyboard::T)
				{
					cout << (1 == 10) << endl;
					Trier(m_posVilles);
					cout << " Tri effectue avec succee ! " <<endl;
					
					
				}
			}

			

		}
		
		m_window->clear();//entre ici 
		m_window->draw(convex);
		for (int i = 0; i < m_posVilles.size(); i++)
		{
			m_villes[i].setPosition(m_posVilles[i]);
			m_window->draw(m_villes[i]);
		}

		
		
		m_window->display();// et l¨¤
	}

}


Ville::~Ville()
{
}
