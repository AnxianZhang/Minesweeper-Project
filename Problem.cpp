/****************************************
 Nom---------: Problem.cpp
 Role--------: Composant du problème
 Auteurs-----: Anxian Zhang, Ye vick
 Version-----: V2 du 31/12/2021
****************************************/

#include <iostream>
using namespace std;

#include "Problem.h"

/***************************** DEBUT COMMANDE 1 ******************************/
void saisie_problem(Problem& p)
{
    cin >> p.lignes >> p.colonnes >> p.bombes;
}

void allocation_bombe(Problem& p)
{
    p.pos_bombe = new unsigned int[p.bombes];
}

void desallocation_bombe(Problem& p)
{
    delete[]p.pos_bombe;
}

void affichage_problem(const Problem& p)
{
    cout << p.lignes << " ";
    cout << p.colonnes << " ";
    cout << p.bombes << " ";
    for (unsigned int i = 0; i < p.bombes; ++i)
    {
        cout << p.pos_bombe[i] << " ";
    }
}
/***************************** FIN COMMANDE 1 ********************************/