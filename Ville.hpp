#pragma once

#include "Entite.hpp"
#include "MatAdjacence.hpp"

using namespace std;

class Ville
{
public:
    Ville(int largeur, int hauteur, string titre);
    void Action();
    float PlusBas(vector <sf::Vector2f> &points);
    void Trier(vector <sf::Vector2f> &points); // Tri les points par abscisses croissantes
    int  Orient(vector <sf::Vector2f> &points, int i, int j, int k);
    void Distance(int pointA,int pointB); // Donne la distance entre deux points
    void DistanceTotale(int i); // Donne la distance totale du trajet
    void RemplirParComb(int taille);
    void MajEnvSup(vector <sf::Vector2f> &points, vector<int> &es, int i);
    void MajEnvInf(vector <sf::Vector2f> &points, vector<int> &ei, int i);
    void Tracer(int indice);
    void DeplacerCamera(sf::Event &event);
    void NouvelleEntite(sf::Event &event);
    void CreationEnvConvxe(sf::Event &event);
    void AjoutVille(sf::Event &event);
    void Combinaisons(int n, int r);
    vector<int> Parcours(MatriceAdj &matrice, int debut, vector<int> &resultat);
    vector <int> ConvGraham(vector <sf::Vector2f> &points);
    int VerifierConnexe(int n);
    bool EstDedans( vector<int> &tab, int x);
    
    ~Ville();
    
    private :
    sf::RenderWindow *m_window;
    vector<int> m_envSup;
    vector<int> m_envInf;
    vector<vector<int>> m_combinaisons;
    string m_mode;
    sf::Text m_texte;
    sf::Font m_font;
    vector <Entite> m_entites;
    
    vector<sf::CircleShape> m_villes;
    vector<MatriceAdj> m_chemins;       // Matrice avec les différents tous les différents chemins possible ( connexe ?)
    vector<MatriceAdj> m_connexions;    // Matrice d'adjacen des liens entre les différents points.
    
    sf::View m_vue;
    
    float m_fpsCount;
    float m_switchFps;
    float m_fpsSpeed ;
    int m_indiceGraphe;
    sf::Clock clock;
    bool m_updateFps ;
};
