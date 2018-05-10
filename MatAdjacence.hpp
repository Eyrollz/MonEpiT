//
//  MatAdjacence.hpp
//  MonTipe
//
//  Created by macbook on 25/12/2017.
//  Copyright © 2017 Kabeche. All rights reserved.
//

#ifndef MatAdjacence_hpp
#define MatAdjacence_hpp

#include "Entite.hpp"


using namespace std;

class MatriceAdj
{
public:
    
    MatriceAdj(int n);
    ~MatriceAdj();
    void Afficher();
    void Ajouter(int i, int j);
    void Supprimer(int i, int j);
    bool EstValide();
    
    // Le principe d'encapsualtion n'est pas respeccté dans ce cas
    int m_taille;
    vector<vector <int>> m_mat;
};

#endif /* MatAdjacence_hpp */
