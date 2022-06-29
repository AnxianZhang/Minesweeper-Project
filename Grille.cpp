/****************************************
 Nom---------: Grille.cpp
 Role--------: Composant de la grille
 Auteurs-----: Anxian Zhang, Ye vick
 Version-----: V7 du 31/12/2021
****************************************/

#include <iostream>
#include <cstring>
#include <cassert>
#include <ctime>
using namespace std;

#include "Grille.h"

/***************************** DEBUT COMMANDE 1 ******************************/
void allocation_grille(Grille& g)
{
    g.grille_jeu = new Case * [g.lignes];
    for (unsigned int i = 0; i < g.lignes; ++i)
    {
        g.grille_jeu[i] = new Case[g.colonnes];
    }
}

void desallocation_grille(Grille& g)
{
    for (unsigned int i = 0; i < g.lignes; ++i)
    {
        delete[]g.grille_jeu[i];
    }
    delete[]g.grille_jeu;
}

void initialisation_grille(Grille& g, const Problem& p)
{
    for (unsigned int i = 0; i < p.lignes; ++i)
    {
        for (unsigned int j = 0; j < p.colonnes; ++j)
        {
            g.grille_jeu[i][j].contenue = 0;
            g.grille_jeu[i][j].etat = CACHER;
        }
    }
}

void rand_bombes(Grille& g, const Problem& p)
{
    Case temps;
    unsigned int randl, randc; // respectivement ligne et colonne

    for (unsigned int i = 0; i < p.lignes; ++i)
    {
        for (unsigned int j = 0; j < p.colonnes; ++j)
        {
            randl = rand() % p.lignes;
            randc = rand() % p.colonnes;

            temps = g.grille_jeu[i][j];
            g.grille_jeu[i][j] = g.grille_jeu[randl][randc];
            g.grille_jeu[randl][randc] = temps;
        }
    }
}

void place_bombes_debut(Grille& g, const Problem& p)
{
    assert(p.bombes <= p.lignes * p.colonnes);

    /* indiqu� le nombre de bombe qu'on � deja plac�
    sert aussi d'indice */
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
                g.grille_jeu[j][k].contenue = 9; // '9' indique une bombe
                ++indice_bombe;
                if (indice_bombe == p.bombes)
                {
                    rand_bombes(g, p);
                    return; // sort quand toute les bombes sont plac�
                }
            }
        }
    }
}

void get_pos_bombes(const Grille& g, Problem& p)
{
    unsigned int valeur;
    unsigned int position;
    int indice_bombe = 0;

    for (unsigned int i = 0; i < p.lignes; ++i)
    {
        for (unsigned int j = 0; j < p.colonnes; ++j)
        {
            valeur = g.grille_jeu[i][j].contenue;
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

void creation_problem(Grille& g, Problem& p)
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
void affichage_grille(const Grille& g, const Problem& p)
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
            Etat_case etat = g.grille_jeu[j][k].etat;
            unsigned int contenue = g.grille_jeu[j][k].contenue;

            if (etat == MARQUER)
            {
                cout << "|" << " x ";
            }
            else if (etat == DEMASQUER)
            {
                if (contenue == 0)
                {
                    cout << "|" << "   ";
                }
                else if (contenue >= 1 && contenue <= 8)
                {
                    cout << "|" << " " << contenue << " ";
                }
                else
                {
                    cout << "|" << " m ";
                }
            }
            else // si etat = CACHER
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

void saisie_grille(Grille& g, Problem& p, Historique_coup& hc)
{
    // r�colte du probl�me
    saisie_problem(p);
    allocation_bombe(p);
    for (unsigned int i = 0; i < p.bombes; ++i)
    {
        cin >> p.pos_bombe[i];
    }

    g.lignes = p.lignes;
    g.colonnes = p.colonnes;
    allocation_grille(g);

    // r�colte de l'historique des coups
    cin >> hc.nb_coup;
    allocation_coup(hc);
    for (unsigned int j = 0; j < hc.nb_coup; ++j)
    {
        cin >> hc.liste_coup[j].lettre;
        cin >> hc.liste_coup[j].position;
    }
}

void attribution_bombe_perdu(Grille& g, const Problem& p)
{
    unsigned int pos_bombe;
    unsigned int ligne, colonne;

    for (unsigned int i = 0; i < p.bombes; ++i)
    {
        pos_bombe = p.pos_bombe[i];
        ligne = pos_bombe / p.colonnes;
        colonne = pos_bombe % p.colonnes;

        g.grille_jeu[ligne][colonne].etat = DEMASQUER;
    }
}

void initialisation_bombe(Grille& g, const Problem& p)
{
    unsigned int pos_bombe;
    unsigned int ligne, colonne;

    for (unsigned int i = 0; i < p.bombes; ++i)
    {
        pos_bombe = p.pos_bombe[i];
        ligne = pos_bombe / p.colonnes;
        colonne = pos_bombe % p.colonnes;
        g.grille_jeu[ligne][colonne].contenue = 9;
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

void marquer(Grille& g, const Problem& p, const unsigned int posc,
    const unsigned int lc, const unsigned int cc)
{
    int etat;
    etat = verification(p, posc);

    if (etat == 1) // coup juste
    {
        g.grille_jeu[lc][cc].etat = MARQUER;
    }
    else // mauvais coup
    {
        g.grille_jeu[lc][cc].etat = MARQUER;
        attribution_bombe_perdu(g, p);
    }
}

void recurrence(Grille& g, const Problem& p, const unsigned int pos)
{
    unsigned int position_case = pos;
    unsigned int ligne = position_case / p.colonnes;
    unsigned int colonne = position_case % p.colonnes;

    if (g.grille_jeu[ligne][colonne].etat == DEMASQUER)
    {
        return;
    }

    g.grille_jeu[ligne][colonne].etat = DEMASQUER;

    if (g.grille_jeu[ligne][colonne].contenue >= 1
        && g.grille_jeu[ligne][colonne].contenue <= 8)
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
                if (g.grille_jeu[ligne + j][colonne + k].etat == CACHER)
                {
                    // nouvelle position � trait�
                    position_case = ((ligne + j) * p.colonnes) + (colonne + k);
                    recurrence(g, p, position_case);
                }
            }
        }
    }
}

void demasquer(Grille& g, const Problem& p, const unsigned int posc,
    unsigned int lc, unsigned int cc)
{
    int etat = verification(p, posc);

    if (etat == 1) // mauvais coup
    {
        attribution_bombe_perdu(g, p);
    }
    else // coups juste
    {
        recurrence(g, p, posc);
    }
}

void give_value_adjacent(Grille& g, const Problem& p)
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
                    unsigned int contient = g.grille_jeu[ligne + j][colonne + k].contenue;
                    if (contient >= 0 && contient <= 7)
                    {
                        ++g.grille_jeu[ligne + j][colonne + k].contenue;
                    }
                }
            }
        }
    }
}

void reconnaissance_coup(Grille& g, const Problem& p, const Historique_coup hc)
{
    unsigned int position;
    unsigned int ligne, colonne;
    char lettre;

    for (unsigned int i = 0; i < hc.nb_coup; ++i)
    {
        lettre = hc.liste_coup[i].lettre;
        position = hc.liste_coup[i].position;
        ligne = position / p.colonnes;
        colonne = position % p.colonnes;

        if (lettre == 'D')
        {
            demasquer(g, p, position, ligne, colonne);
        }
        if (lettre == 'M')
        {
            marquer(g, p, position, ligne, colonne);
        }
    }
}

void creation_grille(Grille& g, Problem& p, Historique_coup hc)
{
    initialisation_grille(g, p);
    initialisation_bombe(g, p); 
    give_value_adjacent(g, p);
    reconnaissance_coup(g, p, hc);
}
/***************************** FIN COMMANDE 2 ********************************/
/**************************** DEBUT COMMANDE 3 *******************************/
void test_won(Grille& g, const Problem& p)
{
    unsigned int compteur_bombe_marquer = 0;
    unsigned int compteur_case_demasquer = 0;
    int teste = 0;
    unsigned int total_case = p.lignes * p.colonnes;

    for (unsigned int i = 0; i < p.lignes; ++i)
    {
        for (unsigned int j = 0; j < p.colonnes; ++j)
        {
            if (g.grille_jeu[i][j].etat == MARQUER &&
                g.grille_jeu[i][j].contenue == 9)
            {
                ++compteur_bombe_marquer;
            }
            else if (g.grille_jeu[i][j].etat == DEMASQUER &&
                (g.grille_jeu[i][j].contenue <= 8 &&
                    g.grille_jeu[i][j].contenue >= 0))
            {
                ++compteur_case_demasquer;
            }
        }
    }

    if (compteur_bombe_marquer == p.bombes ||
        compteur_case_demasquer == total_case - p.bombes)
        /*total_case - p.bombes d�singne le nombre total de case CACHER*/
    {
        g.etatj = GAME_WON;
    }
    else
    {
        g.etatj = GAME_NOT_WON;
    }
}

void affichage_won(const Grille& g)
{
    if (g.etatj == GAME_WON)
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
void test_lost(Grille& g, const Problem& p, const Historique_coup& hc)
{
    int i = 0; // prends les valeurs 1 et -1

    if (hc.liste_coup[hc.nb_coup - 1].lettre == 'M')
    {

        for (unsigned int j = 0; j < p.bombes; ++j)
        {
            if (p.pos_bombe[j] == hc.liste_coup[hc.nb_coup - 1].position)
            {
                i = 1;
            }
        }
        /*si i = 0 alors le dernier coup jou� est un marquage sur
        une case vide donc i = -1 pour indique que la partie est perdu*/
        if (i == 0)
        {
            i = -1;
        }
    }
    if (hc.liste_coup[hc.nb_coup - 1].lettre == 'D')
    {
        for (unsigned int k = 0; k < p.bombes; ++k)
        {
            if (p.pos_bombe[k] == hc.liste_coup[hc.nb_coup - 1].position)
            {
                i = -1;
            }
        }
        /*si i = 0 alors le dernier coup jou� est un d�masquage sur
        une case vide donc i = 1 pour indique que la partie n'est pas perdu*/
        if (i == 0)
        {
            i = 1;
        }
    }

    (i == 1) ? g.etatj = GAME_NOT_LOST : g.etatj = GAME_LOST;
}

void affichage_lost(const Grille& g)
{
    if (g.etatj == GAME_LOST)
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
void saisie_dimension_grille(Grille& g)
{
    cin >> g.lignes >> g.colonnes;
}

unsigned int val_adja(char storage)
{
    assert(storage >= '1' && storage <= '8');
    return storage - '0';
}

void traitement_grille(Grille& g)
{
    unsigned int num_ligne = 0; // n�ligne dans les entr�s lu
    unsigned int num_colonne = 0; // n�colonne dans les entr�s lu
    int i = 0, j = 0; // nombre de '|' lu
    char storage;

    do
    {   
        cin >> storage;
        if (storage != '_') // prend tout les caract�re sauf '_'
        {
            if (storage == '|')
            {
                ++i; // incr�mentation du nombre de '|'
                if (i == 2)
                {
                    g.grille_jeu[num_ligne][num_colonne].contenue = 0;
                    g.grille_jeu[num_ligne][num_colonne].etat = DEMASQUER;
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
                g.grille_jeu[num_ligne][num_colonne].contenue = val_adja(storage);
                g.grille_jeu[num_ligne][num_colonne].etat = DEMASQUER;
                ++num_colonne;
                //initialise � 0 � chaque fois qu'on a une valeur != de '|'
                i = 0;
                j = 0;
            }
            else if (storage == 'm')
            {
                g.grille_jeu[num_ligne][num_colonne].contenue = 9;
                g.grille_jeu[num_ligne][num_colonne].etat = DEMASQUER;
                ++num_colonne;
                i = 0;
                j = 0;
            }
            else if (storage == 'x')
            {
                g.grille_jeu[num_ligne][num_colonne].contenue = 0;
                g.grille_jeu[num_ligne][num_colonne].etat = MARQUER;
                ++num_colonne;
                i = 0;
                j = 0;
            }
            else
            {
                g.grille_jeu[num_ligne][num_colonne].contenue = 0;
                g.grille_jeu[num_ligne][num_colonne].etat = CACHER;
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

unsigned int count_hidden(const Grille& g)
{
    unsigned int nb_cacher = 0; //nombre de case cach�
    for (unsigned int i = 0; i < g.lignes; ++i)
    {
        for (unsigned int j = 0; j < g.colonnes; ++j)
        {
            if (g.grille_jeu[i][j].etat == CACHER)
            {
                ++nb_cacher;
            }
        }
    }
    return nb_cacher;// 44
}

void choice_move(const Grille& g, Details_coups& nw, const unsigned int nb_cacher)
{
    // choisit un num�ros parmis tout les cases cach�s sauf 0
    unsigned int num_case = rand() % (nb_cacher - 1) + 1;

    int k = 0; // indice qui va �tre incr�ment� jusqu'� que k = num_case

    for (unsigned int i = 0; i < g.lignes; ++i){
        for (unsigned int j = 0; j < g.colonnes; ++j){
            if (g.grille_jeu[i][j].etat == CACHER){ 
                ++k;

                /*prendre un valeur dans l'interval [1;10]
                qui va d�terminer si le coup sera M ou D*/
                unsigned int number = rand() % (10 - 1) + 1;
                if (k == num_case){
                    nw.position = (i * g.colonnes) + j;
                    if (number <= 5) // choix de D ou M{
                        nw.lettre = 'D';
                    else
                        nw.lettre = 'M';
                    return; // sort de la fonction car k = num_case
                }
            }
        }
    }
}

void creat_new_move(Grille& g, Details_coups& nw)
{
    allocation_grille(g);
    traitement_grille(g);
    choice_move(g, nw, count_hidden(g));
}
/***************************** FIN COMMANDE 5 ********************************/