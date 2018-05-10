//
//  MatAdjacence.cpp
//  MonTipe
//
//  Created by macbook on 25/12/2017.
//  Copyright © 2017 Kabeche. All rights reserved.
//

#include "MatAdjacence.hpp"



MatriceAdj::MatriceAdj(int n )
{
    m_taille = n;
    vector<int> temp (n,0);
    for (int i=0; i<n;i++)
    {
        m_mat.push_back(temp);
        
    }
}
void MatriceAdj::Ajouter(int i, int j)
{
    m_mat[i][j] = 1;
    m_mat[j][i] = 1;
}
void MatriceAdj::Supprimer(int i, int j)
{
    m_mat[i][j] = 0;
    m_mat[j][i] = 0;
}
bool MatriceAdj::EstValide()
{
    vector<bool> test (m_taille,false);
    
    for (int j=0; j<m_taille;j++)
    {
        for (int i=0; i<m_taille;i++)
        {
            
            if( m_mat[i][j] == 1)
                test[j] = true;
        }
        
    }
    for (int k=0; k<m_taille;k++)
    {
        if ( test[k] == false)
            return false;
        else if (k == m_taille -1)
        {
            if (test[m_taille-1] == true)
                return true;
        }
    }
}

void MatriceAdj::Afficher()
{
    for (int i=0; i<m_taille;i++)
    {
        cout<<" \n";
        for (int j=0; j<m_taille;j++)
        {
            cout<<m_mat[i][j];
            
        }
        
    }
    cout<<" \n";
}



MatriceAdj::~MatriceAdj()
{
    
}

