/**
 * @file Grid.h
 * @author Anxian Zhang (gadanxianzhang@gmail.com.com)
           Vick Ye (vickye2908@gmail.com)
 * @brief Composant de la grille
 * @version 7
 * @date 2021-12-31
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _GRID_
#define _GRID_

#include "Case.h"
#include "Problem.h"
#include "Historic.h"
#include "GameState.h"

struct Grid {
    Case** gameGrid;
    unsigned int lignes;
    unsigned int colonnes;
    GameState state; // état du jeu
};
/***************************** DEBUT COMMANDE 1 ******************************/
/**
 * @brief Créer le problème
 *
 * @param [in] g: la grille qui va être généré avec le problème donné
 * @param [in] p: le problème
 */
void creation_problem(Grid& g, Problem& p);

/**
 * @brief Alloue dynamiquement un tableau à deux
 *        avec les dimensions données
 *
 * @see allocation_grille: désalloue le tableau à
 *                         2 dimensions
 *
 * @param [out] g: la grille
 */
void allocation_grille(Grid& g);

/**
 * @brief Désalloue le tableau à deux
 *        dimensions
 *
 * @param [out] g: la grille
 */
void desallocation_grille(Grid& g);

/**
 * @brief Initialise toutes les cases du tableau
 *        l'état HIDE et son contenue à 0
 *
 * @param [out] g: la grille
 * @param [in] p: le problème
 */
void initialisation_grille(Grid& g, const Problem& p);

/**
 * @brief Place le nombre de bombe indiquée en entrée
 *        au début du tableau
 *
 * @see rand_bombes: mélange le tableau pour les placer
 *                   alléatoirement
 *
 * @param [out] g: la grille de jeu
 * @param [in] p: le problème
 * @pre p.bombes <= p.lignes * p.colonnes
 */
void place_bombes_debut(Grid& g, const Problem& p);

/**
 * @brief Mélange les cases du tableau pour placer
 *        alléatoirement les bombes qui sont initialement au
 *        debut de ce-dernier
 *
 * @see get_pos_bombes: cherche les positions des bombes
 *
 * @param [out] g: la grille de jeu
 * @param [in] p: le problème
 */
void rand_bombes(Grid& g, const Problem& p);

/**
 * @brief Cherche toute les bombes qui se trouvent
 *        dans la grille pour ensuite stocker
 *        leurs positions dans le tableau de bombes
 *        crée dynamiquement
 *
 * @param [in] g: la grille de jeu
 * @param [in, out] p: le problème
 */
void get_pos_bombes(const Grid& g, Problem& p);
/***************************** FIN COMMANDE 1 ********************************/
/**************************** DEBUT COMMANDE 2 *******************************/

/**
 * @brief Saisit les données necessaires
 *
 * @param [out] g: la grille
 * @param [out] p: le problème
 * @param [out] hc: l'historique des coups
 */
void saisie_grille(Grid& g, Problem& p, MoveHistoric& hc);

/**
 * @brief Initalise les positions des bombes donnée en entrée
 *        dans la grille de jeu (sont toujours à l'état CACHER)
 *
 * @param [out] g: le grille
 * @param [in] p: le problème
 */
void initialisation_bombe(Grid& g, const Problem& p);

/**
 * @brief Affiche une grille avec son contenue en fonction
 *        le l'état des cases
 *
 * @param [in] g: la grille de jeu
 * @param [in] p: le problème
 */
void affichage_grille(const Grid& g, const Problem& p);

/**
 * @brief Affecte les bombes à leurs position respective
 *        et met toutes les cases contenant des bombes
 *        à l'etat UNMASK si le dernier coup
 *        jouer met fin à la partie
 *
 * @param [out] g: la grille
 * @param [in] p: le problème
 */
void attribution_bombe_perdu(Grid& g, const Problem& p);

/**
 * @brief Verifie si la position du coup jouer
 *        corespond à celle d'une bombes
 *
 * @param [in] p: le problème
 * @param [in] pos_coup: la position du coup
 * @return int 1 si c'est vrais, 0 si c'est faux
 */
int verification(const Problem& p, const unsigned int pos_coup);

/**
 * @brief Marque une case donnée que si elle ne pas
 *        corespond à celle d'une bombe
 *
 * @see attribution_bombe_perdu: met toute les bombes à l'état UNMASK
 *                               dans le cas contraire
 *
 * @param [out] g: la grille
 * @param [in] p: le problème
 * @param [in] posc: position du coup jouer
 * @param [in] lc: ligne du coup jouer
 * @param [in] cc: colonne du coup jouer
 */
void mark(Grid& g, const Problem& p, const unsigned int posc,
    const unsigned int lc, const unsigned int cc);

/**
 * @brief démasque une ou plusieurs cases 
          si celle-ci n'est pas une bombe
 *
 * @see attribution_bombe_perdu: met toute les bombes à l'état UNMASK
 *                               dans le cas contraire
 * @see recurrence: se charge du démasquage si le coup jouer n'est pas à la
 *                  position d'un bombe
 *
 * @param [out] g: la grille
 * @param [in] p: le problème
 * @param [in] posc: position du coup jouer
 * @param [in] lc: ligne du coup jouer
 * @param [in] cc: colonne du coup jouer
 */
void unmask(Grid& g, const Problem& p, const unsigned int posc,
    const unsigned int lc, const unsigned int cc);

/**
* @brief Met qu'une case à l'état UNMASK si la case à démasquer contient
*        un chiffre mais si la case de départ est vide et que ces cases ajdacentes
*        sont elles aussi vide la fonction démasquera ces case,
*        l'opération se répète jusqu'à que la zone soit entouré par des chiffres
*
* @param [out] g: la grille
* @param [in] p: le problème
* @param [in] pos: la postion du coup
*/
void recurrence(Grid& g, const Problem& p, const unsigned int pos);

/**
 * @brief Indique le nombre de bombe dans les cases adjacentes
 *
 * @param [out] g: la grille de jeu
 * @param [in] p: le problème
 */
void give_value_adjacent(Grid& g, const Problem& p);

/**
 * @brief Traite les coups jouer pour savoir s'il faut
 *        marquer ou démasquer
 *
 * @see demasquer: démasque les cases indiqué
 * @see marquer: marque les cases indiqué
 *
 * @param [in] g: la grille de jeu
 * @param [in] p: le problème
 * @param [in] hc: l'historique de coup
 */
void reconnaissance_coup(Grid& g, const Problem& p, const MoveHistoric hc);

/**
 * @brief Créer la grille pour ensuite exploiter
 *        les données lors de l'affichage
 *
 * @param [in] g: la grille de jeu
 * @param [in] p: le problème
 * @param [in] hc: l'historique de coup
 */
void creation_grille(Grid& g, Problem& p, MoveHistoric hc);
/***************************** FIN COMMANDE 2 ********************************/
/**************************** DEBUT COMMANDE 3 *******************************/
/**
 * @brief Fait des testes sur l'ensemble de la grille
 *        pour déterminer si la partie est gagné ou pas
 *        en affectant GAME_WON ou GAME_NOT_WON à  l'état du jeu
 *
 * @param [in, out] g: la grille de jeu
 * @param [in] p: le problème
 */
void test_won(Grid& g, const Problem& p);

/**
 * @brief Affiche une ligne "game won" ou "game not won" en
 *        fonction de l'état de la grille
 *
 * @param [in] g: la grille de jeu
 */
void affichage_won(const Grid& g);
/***************************** FIN COMMANDE 3 ********************************/
/**************************** DEBUT COMMANDE 4 *******************************/
/**
 * @brief Fait des testes en comparant le dernier coup (car
 *        on ne peut que perde sur le dernier coup jouer)
 *        avec les positions des bombes, en fonction du coup
 *        (M ou D) GAME_LOST ou GAME_NOT_LOST sera 
 *        attrituer à  l'état du jeu
 *
 * @param [in, out] g: la grille de jeu
 * @param [in] p: le problème
 * @param [in] hc: l'historique des coups
 */
void test_lost(Grid& g, const Problem& p, const MoveHistoric& hc);

/**
 * @brief Affiche une ligne "game lost" ou "games not lost"
 *        fonction de l'état de jeu de la grille
 *
 * @param [in] g: la grille de jeu
 */
void affichage_lost(const Grid& g);
/***************************** FIN COMMANDE 4 ********************************/
/**************************** DEBUT COMMANDE 5 *******************************/

/**
 * @brief Initialise le nombre de lignes et colonnes dans
 *        la stucture de donnée
 *
 * @param [out] g: la grille
 */
void saisie_dimension_grille(Grid& g);

/**
 * @brief Convertit un chiffre de type char en unsigned int
 *        grace au calcul storage - '0' avec 0 = 48
 *
 * @param [in] storage: le chiffre à convertir
 * @return unsigned int: la valeur convertit
 * @pre storage >= '1' && storage <= '8'
 */
unsigned int val_adja(char storage);

/**
 * @brief Analyse la grille en entrée et le stock
 *        les données en fonction des valeurs lu
 * 
 * @see val_adja: convertit un chiffre ASCCI en entier naturel
 *
 * @param [in,out] g: la grille
 */
void traitement_grille(Grid& g);

/**
 * @brief Compte le nombre de case qui sont
 *        à l'état CACHER
 *
 * @param [in] g: la grille
 * @return unsigned int: le totale de case CACHER
 */
unsigned int count_hidden(const Grid& g);

/**
 * @brief Choisie un coups parmis les cases
 *        à l'état CACHER
 * 
 * @see count_hidden: compte le nombre totale de case caché
 *
 * @param [in] g: la grille
 * @param [out] nw: la nouvelle position
 * @param [in] nb_cacher: nombre de case à l'état CACHER
 */
void choice_move(const Grid& g, MoveDetails& nw, const unsigned int nb_cacher);

/**
 * @brief Créer un nouveau coup en fonction de
 *        la grille donnée
 *
 * @param [in] g: la grille
 * @param [in] nw: le nouveau coup
 */
void creat_new_move(Grid& g, MoveDetails& nw);
/***************************** FIN COMMANDE 5 ********************************/

#endif // !_GRID_
