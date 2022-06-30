/****************************************
 Nom---------: main.c
 Role--------: Application qui nous
               permet de jouer au 
               démineur de bout en bout
 Auteurs-----: Anxian Zhang, Ye vick
 Version-----: V7 du 31/12/2021
****************************************/

#include <iostream>
#include <cassert>
using namespace std;

#include "Problem.h"
#include "Historique.h"
#include "Grid.h"

int main(void)
{
    srand((unsigned)time(NULL));

    Grid jeu;
    Problem probleme;
    Historique_coup historique;
    MoveDetails new_move;
    unsigned int num_commande;

    do
    {
        cin >> num_commande;
    } while (!(num_commande > 0 && num_commande <= 5));

    switch (num_commande)
    {
    case 1:
        // Génération du problème
        saisie_problem(probleme);
        creation_problem(jeu, probleme);
        affichage_problem(probleme);
        desallocation_bombe(probleme);
        desallocation_grille(jeu);
        break;
    case 2:
        // Génération de la grille
        saisie_grille(jeu, probleme, historique);
        creation_grille(jeu, probleme, historique);
        affichage_grille(jeu, probleme);
        desallocation_coup(historique);
        desallocation_bombe(probleme);
        desallocation_grille(jeu);
        break;
    case 3:
        // Partie gagné ?
        saisie_grille(jeu, probleme, historique);
        creation_grille(jeu, probleme, historique);
        test_won(jeu, probleme);
        affichage_won(jeu);
        desallocation_coup(historique);
        desallocation_bombe(probleme);
        desallocation_grille(jeu);
        break;
    case 4:
        // Partie perdu ?
        saisie_grille(jeu, probleme, historique);
        test_lost(jeu, probleme, historique);
        affichage_lost(jeu);
        desallocation_coup(historique);
        desallocation_bombe(probleme);
        desallocation_grille(jeu);
        break;
    case 5:
        // Création d'un nouveau coup
        saisie_dimension_grille(jeu);
        creat_new_move(jeu, new_move);
        //affichage du nouveau coup
        cout << new_move.letter << new_move.position << endl;
        desallocation_grille(jeu);
        break;
    default:
        break;
    }
    return 0;
}