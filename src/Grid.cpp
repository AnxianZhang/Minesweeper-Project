/**
 * @file Grid.cpp
 * @author Anxian Zhang (gadanxianzhang@gmail.com.com)
           Vick Ye (vickye2908@gmail.com)
 * @brief Composant de la grille
 * @version 7
 * @date 2021-12-31
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <cstring>
#include <cassert>
#include <ctime>
using namespace std;

#include "Grid.h"

/***************************** DEBUT COMMANDE 1 ******************************/
void allocation_grille(Grid& g)
{
    g.gameGrid = new Case * [g.lignes];
    for (unsigned int i = 0; i < g.lignes; ++i)
    {
        g.gameGrid[i] = new Case[g.colonnes];
    }
}

void desallocation_grille(Grid& g)
{
    for (unsigned int i = 0; i < g.lignes; ++i)
    {
        delete[]g.gameGrid[i];
    }
    delete[]g.gameGrid;
}

void initialisation_grille(Grid& g, const Problem& p)
{
    for (unsigned int i = 0; i < p.lignes; ++i)
    {
        for (unsigned int j = 0; j < p.colonnes; ++j)
        {
            g.gameGrid[i][j].content = 0;
            g.gameGrid[i][j].state = HIDE;
        }
    }
}

void rand_bombes(Grid& g, const Problem& p)
{
    Case temps;
    unsigned int randl, randc; // respectivement ligne et colonne

    for (unsigned int i = 0; i < p.lignes; ++i)
    {
        for (unsigned int j = 0; j < p.colonnes; ++j)
        {
            randl = rand() % p.lignes;
            randc = rand() % p.colonnes;

            temps = g.gameGrid[i][j];
            g.gameGrid[i][j] = g.gameGrid[randl][randc];
            g.gameGrid[randl][randc] = temps;
        }
    }
}

void place_bombes_debut(Grid& g, const Problem& p)
{
    assert(p.bombes <= p.lignes * p.colonnes);

    /* indique le nombre de bombe qu'on à deja placésert aussi d'indice */
    int indice_bombe = 0;

    // sort de la fonction si le nombre de bombe est null
    if (p.bombes == 0)
    {
        return;
    }
    else
    {
        for (unsigned int j = 0; j < p.lignes; ++j) // ligne
        {
            for (unsigned int k = 0; k < p.colonnes; ++k)// colonne
            {
                g.gameGrid[j][k].content = 9; // '9' indique une bombe
                ++indice_bombe;
                if (indice_bombe == p.bombes)
                {
                    rand_bombes(g, p);
                    return; // sort quand toute les bombes sont placé
                }
            }
        }
    }
}

void get_pos_bombes(const Grid& g, Problem& p)
{
    unsigned int valeur;
    unsigned int position;
    int indice_bombe = 0;

    for (unsigned int i = 0; i < p.lignes; ++i)
    {
        for (unsigned int j = 0; j < p.colonnes; ++j)
        {
            valeur = g.gameGrid[i][j].content;
            if (valeur == 9) // si valeur = mine
            {
                // calcule de la position
                position = (i * p.colonnes) + j;
                p.pos_bombe[indice_bombe] = position;
                ++indice_bombe;
            }
        }
    }
}

void creation_problem(Grid& g, Problem& p)
{
    g.lignes = p.lignes;
    g.colonnes = p.colonnes;

    allocation_bombe(p);
    allocation_grille(g);
    initialisation_grille(g, p);
    place_bombes_debut(g, p);
    get_pos_bombes(g, p);
}
/***************************** FIN COMMANDE 1 ********************************/
/**************************** DEBUT COMMANDE 2 *******************************/
void affichage_grille(const Grid& g, const Problem& p)
{
    cout << p.lignes << " " << p.colonnes << endl;

    for (unsigned int i = 0; i < p.colonnes; ++i)
    {
        cout << " ___";
    }
    cout << endl;

    for (unsigned int j = 0; j < p.lignes; ++j)
    {
        for (unsigned int k = 0; k < p.colonnes; ++k)
        {
            CaseState state = g.gameGrid[j][k].state;
            unsigned int content = g.gameGrid[j][k].content;

            if (state == MARK)
            {
                cout << "|" << " x ";
            }
            else if (state == UNMASK)
            {
                if (content == 0)
                {
                    cout << "|" << "   ";
                }
                else if (content >= 1 && content <= 8)
                {
                    cout << "|" << " " << content << " ";
                }
                else
                {
                    cout << "|" << " m ";
                }
            }
            else // if state = HIDE
            {
                cout << "|" << " . ";
            }
        }
        cout << "|" << endl;

        for (unsigned int l = 0; l < p.colonnes; ++l)
        {
            cout << " ___";
        }
        cout << endl;
    }
}

void saisie_grille(Grid& g, Problem& p, MoveHistoric& hc)
{
    // récolte du problème
    saisie_problem(p);
    allocation_bombe(p);
    for (unsigned int i = 0; i < p.bombes; ++i)
    {
        cin >> p.pos_bombe[i];
    }

    g.lignes = p.lignes;
    g.colonnes = p.colonnes;
    allocation_grille(g);

    // récolte de l'historique des coups
    cin >> hc.nbMove;
    allocation_coup(hc);
    for (unsigned int j = 0; j < hc.nbMove; ++j)
    {
        cin >> hc.list[j].letter;
        cin >> hc.list[j].position;
    }
}

void attribution_bombe_perdu(Grid& g, const Problem& p)
{
    unsigned int pos_bombe;
    unsigned int ligne, colonne;

    for (unsigned int i = 0; i < p.bombes; ++i)
    {
        pos_bombe = p.pos_bombe[i];
        ligne = pos_bombe / p.colonnes;
        colonne = pos_bombe % p.colonnes;

        g.gameGrid[ligne][colonne].state = UNMASK;
    }
}

void initialisation_bombe(Grid& g, const Problem& p)
{
    unsigned int pos_bombe;
    unsigned int ligne, colonne;

    for (unsigned int i = 0; i < p.bombes; ++i)
    {
        pos_bombe = p.pos_bombe[i];
        ligne = pos_bombe / p.colonnes;
        colonne = pos_bombe % p.colonnes;
        g.gameGrid[ligne][colonne].content = 9;
    }
}

int verification(const Problem& p, const unsigned int pos_coup)
{
    unsigned int pos_bombe;

    for (unsigned int i = 0; i < p.bombes; ++i)
    {
        pos_bombe = p.pos_bombe[i];

        if (pos_bombe == pos_coup)
        {
            return 1;
        }
    }
    return -1;
}

void mark(Grid& g, const Problem& p, const unsigned int posc,
    const unsigned int lc, const unsigned int cc)
{
    int state;
    state = verification(p, posc);

    if (state == 1) // coup juste
    {
        g.gameGrid[lc][cc].state = MARK;
    }
    else // mauvais coup
    {
        g.gameGrid[lc][cc].state = MARK;
        attribution_bombe_perdu(g, p);
    }
}

void recurrence(Grid& g, const Problem& p, const unsigned int pos)
{
    unsigned int position_case = pos;
    unsigned int ligne = position_case / p.colonnes;
    unsigned int colonne = position_case % p.colonnes;

    if (g.gameGrid[ligne][colonne].state == UNMASK)
    {
        return;
    }

    g.gameGrid[ligne][colonne].state = UNMASK;

    if (g.gameGrid[ligne][colonne].content >= 1
        && g.gameGrid[ligne][colonne].content <= 8)
    {
        return;
    }

    for (int j = -1; j < 2; ++j)
    {
        for (int k = -1; k < 2; ++k)
        {
            if (ligne + j >= 0 && ligne + j < p.lignes && colonne + k >= 0
                && colonne + k < p.colonnes)
            {
                if (g.gameGrid[ligne + j][colonne + k].state == HIDE)
                {
                    // nouvelle position à traité
                    position_case = ((ligne + j) * p.colonnes) + (colonne + k);
                    recurrence(g, p, position_case);
                }
            }
        }
    }
}

void unmask(Grid& g, const Problem& p, const unsigned int posc,
    unsigned int lc, unsigned int cc)
{
    int state = verification(p, posc);

    if (state == 1) // mauvais coup
    {
        attribution_bombe_perdu(g, p);
    }
    else // coups juste
    {
        recurrence(g, p, posc);
    }
}

void give_value_adjacent(Grid& g, const Problem& p)
{
    unsigned int pos_bombe;
    unsigned int ligne, colonne;

    for (unsigned int i = 0; i < p.bombes; ++i)
    {
        pos_bombe = p.pos_bombe[i];
        ligne = pos_bombe / p.colonnes;
        colonne = pos_bombe % p.colonnes;

        for (int j = -1; j < 2; ++j)
        {
            for (int k = -1; k < 2; ++k)
            {
                if ((ligne + j) < p.lignes && (ligne + j) >= 0 &&
                    ((colonne + k) < p.colonnes && (colonne + k) >= 0))
                {
                    unsigned int contient = g.gameGrid[ligne + j][colonne + k].content;
                    if (contient >= 0 && contient <= 7)
                    {
                        ++g.gameGrid[ligne + j][colonne + k].content;
                    }
                }
            }
        }
    }
}

void reconnaissance_coup(Grid& g, const Problem& p, const MoveHistoric hc)
{
    unsigned int position;
    unsigned int ligne, colonne;
    char letter;

    for (unsigned int i = 0; i < hc.nbMove; ++i)
    {
        letter = hc.list[i].letter;
        position = hc.list[i].position;
        ligne = position / p.colonnes;
        colonne = position % p.colonnes;

        if (letter == 'D')
        {
            unmask(g, p, position, ligne, colonne);
        }
        if (letter == 'M')
        {
            mark(g, p, position, ligne, colonne);
        }
    }
}

void creation_grille(Grid& g, Problem& p, MoveHistoric hc)
{
    initialisation_grille(g, p);
    initialisation_bombe(g, p); 
    give_value_adjacent(g, p);
    reconnaissance_coup(g, p, hc);
}
/***************************** FIN COMMANDE 2 ********************************/
/**************************** DEBUT COMMANDE 3 *******************************/
void test_won(Grid& g, const Problem& p)
{
    unsigned int compteur_bombe_MARK = 0;
    unsigned int compteur_case_UNMARK = 0;
    int teste = 0;
    unsigned int total_case = p.lignes * p.colonnes;

    for (unsigned int i = 0; i < p.lignes; ++i)
    {
        for (unsigned int j = 0; j < p.colonnes; ++j)
        {
            if (g.gameGrid[i][j].state == MARK &&
                g.gameGrid[i][j].content == 9)
            {
                ++compteur_bombe_MARK;
            }
            else if (g.gameGrid[i][j].state == UNMASK &&
                (g.gameGrid[i][j].content <= 8 &&
                    g.gameGrid[i][j].content >= 0))
            {
                ++compteur_case_UNMARK;
            }
        }
    }

    if (compteur_bombe_MARK == p.bombes ||
        compteur_case_UNMARK == total_case - p.bombes)
        /*total_case - p.bombes désingne le nombre total de case HIDE*/
    {
        g.state = GAME_WON;
    }
    else
    {
        g.state = GAME_NOT_WON;
    }
}

void affichage_won(const Grid& g)
{
    if (g.state == GAME_WON)
    {
        cout << "game won" << endl;
    }
    else
    {
        cout << "game not won" << endl;
    }
}
/***************************** FIN COMMANDE 3 ********************************/
/**************************** DEBUT COMMANDE 4 *******************************/
void test_lost(Grid& g, const Problem& p, const MoveHistoric& hc)
{
    int i = 0; // prends les valeurs 1 et -1

    if (hc.list[hc.nbMove - 1].letter == 'M')
    {

        for (unsigned int j = 0; j < p.bombes; ++j)
        {
            if (p.pos_bombe[j] == hc.list[hc.nbMove - 1].position)
            {
                i = 1;
            }
        }
        /*si i = 0 alors le dernier coup joué est un marquage sur
        une case vide donc i = -1 pour indique que la partie est perdu*/
        if (i == 0)
        {
            i = -1;
        }
    }
    if (hc.list[hc.nbMove - 1].letter == 'D')
    {
        for (unsigned int k = 0; k < p.bombes; ++k)
        {
            if (p.pos_bombe[k] == hc.list[hc.nbMove - 1].position)
            {
                i = -1;
            }
        }
        /*si i = 0 alors le dernier coup joué est un démasquage sur
        une case vide donc i = 1 pour indique que la partie n'est pas perdu*/
        if (i == 0)
        {
            i = 1;
        }
    }

    (i == 1) ? g.state = GAME_NOT_LOST : g.state = GAME_LOST;
}

void affichage_lost(const Grid& g)
{
    if (g.state == GAME_LOST)
    {
        cout << "game lost" << endl;
    }
    else
    {
        cout << "game not lost" << endl;
    }
}
/***************************** FIN COMMANDE 4 ********************************/
/**************************** DEBUT COMMANDE 5 *******************************/
void saisie_dimension_grille(Grid& g)
{
    cin >> g.lignes >> g.colonnes;
}

unsigned int val_adja(char storage)
{
    assert(storage >= '1' && storage <= '8');
    return storage - '0';
}

void traitement_grille(Grid& g)
{
    unsigned int num_ligne = 0; // nb ligne dans les entrés lu
    unsigned int num_colonne = 0; // nb colonne dans les entrés lu
    int i = 0, j = 0; // nombre de '|' lu
    char storage;

    do
    {   
        cin >> storage;
        if (storage != '_') // prend tout les caractère sauf '_'
        {
            if (storage == '|')
            {
                ++i; // incrémentation du nombre de '|'
                if (i == 2)
                {
                    g.gameGrid[num_ligne][num_colonne].content = 0;
                    g.gameGrid[num_ligne][num_colonne].state = UNMASK;
                    ++num_colonne;

                    i = 1;
                    ++j;
                    if (num_colonne == g.colonnes)
                    {
                        i = 0;
                        j = 0;
                    }
                }
            }
            else if (storage >= '1' && storage <= '8')
            {
                g.gameGrid[num_ligne][num_colonne].content = val_adja(storage);
                g.gameGrid[num_ligne][num_colonne].state = UNMASK;
                ++num_colonne;
                //initialise ï¿½ 0 ï¿½ chaque fois qu'on a une valeur != de '|'
                i = 0;
                j = 0;
            }
            else if (storage == 'm')
            {
                g.gameGrid[num_ligne][num_colonne].content = 9;
                g.gameGrid[num_ligne][num_colonne].state = UNMASK;
                ++num_colonne;
                i = 0;
                j = 0;
            }
            else if (storage == 'x')
            {
                g.gameGrid[num_ligne][num_colonne].content = 0;
                g.gameGrid[num_ligne][num_colonne].state = MARK;
                ++num_colonne;
                i = 0;
                j = 0;
            }
            else
            {
                g.gameGrid[num_ligne][num_colonne].content = 0;
                g.gameGrid[num_ligne][num_colonne].state = HIDE;
                ++num_colonne;
                i = 0;
                j = 0;
            }
        }

        if (num_colonne == g.colonnes)
        {
            num_colonne = 0;
            ++num_ligne;
            i = -1;
        }

    } while (num_ligne != g.lignes);
}

unsigned int count_hidden(const Grid& g)
{
    unsigned int nb_HIDE = 0; //nombre de case caché
    for (unsigned int i = 0; i < g.lignes; ++i)
    {
        for (unsigned int j = 0; j < g.colonnes; ++j)
        {
            if (g.gameGrid[i][j].state == HIDE)
            {
                ++nb_HIDE;
            }
        }
    }
    return nb_HIDE;// 44
}

void choice_move(const Grid& g, MoveDetails& nw, const unsigned int nb_HIDE)
{
    // choisit un numéros parmis tout les cases cachés sauf 0
    unsigned int num_case = rand() % (nb_HIDE - 1) + 1;

    int k = 0; // indice qui va être incrémenté jusqu'à que k = num_case

    for (unsigned int i = 0; i < g.lignes; ++i){
        for (unsigned int j = 0; j < g.colonnes; ++j){
            if (g.gameGrid[i][j].state == HIDE){ 
                ++k;

                /*prendre un valeur dans l'interval [1;10]
                qui va déterminer si le coup sera M ou D*/
                unsigned int number = rand() % (10 - 1) + 1;
                if (k == num_case){
                    nw.position = (i * g.colonnes) + j;
                    if (number <= 5) // choix de D ou M{
                        nw.letter = 'D';
                    else
                        nw.letter = 'M';
                    return; // sort de la fonction car k = num_case
                }
            }
        }
    }
}

void creat_new_move(Grid& g, MoveDetails& nw)
{
    allocation_grille(g);
    traitement_grille(g);
    choice_move(g, nw, count_hidden(g));
}
/***************************** FIN COMMANDE 5 ********************************/