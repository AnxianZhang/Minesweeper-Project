/****************************************
 Nom---------: Grille.h
 Role--------: Composant de la grille
 Auteurs-----: Anxian Zhang, Ye vick
 Version-----: V7 du 31/12/2021
****************************************/

#ifndef _GRILLE_
#define _GRILLE_

#include "Case.h"
#include "Problem.h"
#include "Historique.h"
#include "Etat_partie.h"

/**
 * @brief Type structuré de la grille de jeu
 *
 */
struct Grille {
    Case** grille_jeu;
    unsigned int lignes;
    unsigned int colonnes;
    Etat_Partie etatj; // état du jeu
};
/***************************** DEBUT COMMANDE 1 ******************************/
/**
 * @brief Créer le problème
 *
 * @param [in] g: la grille qui va être généré avec le problème donné
 * @param [in] p: le problème
 */
void creation_problem(Grille& g, Problem& p);

/**
 * @brief Alloue dynamiquement un tableau à deux
 *        avec les dimensions donnés
 *
 * @see allocation_grille: désalloue le tableau à
 *                         2 dimensions
 *
 * @param [out] g: la grille
 */
void allocation_grille(Grille& g);

/**
 * @brief Désalloue le tableau à deux
 *        dimensions
 *
 * @param [out] g: la grille
 */
void desallocation_grille(Grille& g);

/**
 * @brief Initialise toutes les cases du tableau
 *        l'état CACHER et son contenue à 0
 *
 * @param [out] g: la grille
 * @param [in] p: le problème
 */
void initialisation_grille(Grille& g, const Problem& p);

/**
 * @brief Place le nombre de bombe indiquée en entré
 *        au début du tableau
 *
 * @see rand_bombes: mélange le tableau pour les placer
 *                   alléatoirement
 *
 * @param [out] g: la grille de jeu
 * @param [in] p: le problème
 * @pre p.bombes <= p.lignes * p.colonnes
 */
void place_bombes_debut(Grille& g, const Problem& p);

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
void rand_bombes(Grille& g, const Problem& p);

/**
 * @brief Cherche toute les bombes qui se trouvent
 *        dans la grille pour ensuite stocker
 *        leurs positions dans le tableau de bombes
 *        crée dynamiquement
 *
 * @param [in] g: la grille de jeu
 * @param [in, out] p: le problème
 */
void get_pos_bombes(const Grille& g, Problem& p);
/***************************** FIN COMMANDE 1 ********************************/
/**************************** DEBUT COMMANDE 2 *******************************/

/**
 * @brief Saisit les données necessaires
 *
 * @param [out] g: la grille
 * @param [out] p: le problème
 * @param [out] hc: l'historique des coups
 */
void saisie_grille(Grille& g, Problem& p, Historique_coup& hc);

/**
 * @brief Initalise les positions des bombes donnée en entré
 *        dans la grille de jeu (sont toujours à l'état CACHER)
 *
 * @param [out] g: le grille
 * @param [in] p: le problème
 */
void initialisation_bombe(Grille& g, const Problem& p);

/**
 * @brief Affiche une grille avec son contenue en fonction
 *        le l'état des cases
 *
 * @param [in] g: la grille de jeu
 * @param [in] p: le problème
 */
void affichage_grille(const Grille& g, const Problem& p);

/**
 * @brief Affecte les bombes à leurs position respective
 *        et met toutes les cases contenant des bombes
 *        à l'etat DEMASQUER si le dernier coup
 *        joué met fin à la partie
 *
 * @param [out] g: la grille
 * @param [in] p: le problème
 */
void attribution_bombe_perdu(Grille& g, const Problem& p);

/**
 * @brief Verifie si la position du coup joué
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
 * @see attribution_bombe_perdu: met toute les bombes à l'état DEMASQUER
 *                               dans le cas contraire
 *
 * @param [out] g: la grille
 * @param [in] p: le problème
 * @param [in] posc: position du coup joué
 * @param [in] lc: ligne du coup joué
 * @param [in] cc: colonne du coup joué
 */
void marquer(Grille& g, const Problem& p, const unsigned int posc,
    const unsigned int lc, const unsigned int cc);

/**
 * @brief Démasque une ou plusieurs cases 
          si celle-ci n'est pas une bombe
 *
 * @see attribution_bombe_perdu: met toute les bombes à l'état DEMASQUER
 *                               dans le cas contraire
 * @see recurrence: se charge du démasquage si le coup joué n'est pas à la
 *                  position d'un bombe
 *
 * @param [out] g: la grille
 * @param [in] p: le problème
 * @param [in] posc: position du coup joué
 * @param [in] lc: ligne du coup joué
 * @param [in] cc: colonne du coup joué
 */
void demasquer(Grille& g, const Problem& p, const unsigned int posc,
    const unsigned int lc, const unsigned int cc);

/**
* @brief Met qu'une case à l'état DEMASQUER si la case à démasquer contient
*        un chiffre mais si la case de départ est vide et que ces cases ajdacentes
*        sont elles aussi vide la fonction démasquera ces case,
*        l'opération se répète jusqu'à que la zone soit entouré par des chiffres
*
* @param [out] g: la grille
* @param [in] p: le problème
* @param [in] pos: la postion du coup
*/
void recurrence(Grille& g, const Problem& p, const unsigned int pos);

/**
 * @brief Indique le nombre de bombe dans les cases adjacentes
 *
 * @param [out] g: la grille de jeu
 * @param [in] p: le problème
 */
void give_value_adjacent(Grille& g, const Problem& p);

/**
 * @brief Traite les coups joué pour savoir s'il faut
 *        marquer ou démasqer
 *
 * @see demasquer: démasque les cases indiquées
 * @see marquer: marque les cases indiquées
 *
 * @param [in] g: la grille de jeu
 * @param [in] p: le problème
 * @param [in] hc: l'historique de coup
 */
void reconnaissance_coup(Grille& g, const Problem& p, const Historique_coup hc);

/**
 * @brief Créer la grille pour ensuite exploiter
 *        les données lors de l'affichage
 *
 * @param [in] g: la grille de jeu
 * @param [in] p: le problème
 * @param [in] hc: l'historique de coup
 */
void creation_grille(Grille& g, Problem& p, Historique_coup hc);
/***************************** FIN COMMANDE 2 ********************************/
/**************************** DEBUT COMMANDE 3 *******************************/
/**
 * @brief Fait des testes sur l'ensemble de la grille
 *        pour déterminer si la partie est gagné ou pas
 *        en affectant GAME_WON ou GAME_NOT_WON à l'etatj
 *
 * @param [in, out] g: la grille de jeu
 * @param [in] p: le problème
 */
void test_won(Grille& g, const Problem& p);

/**
 * @brief Affiche une ligne "game won" ou "game not won" en
 *        fonction de l'etatj de la grille
 *
 * @param [in] g: la grille de jeu
 */
void affichage_won(const Grille& g);
/***************************** FIN COMMANDE 3 ********************************/
/**************************** DEBUT COMMANDE 4 *******************************/
/**
 * @brief Fait des testes en comparant le dernier coup (car
 *        on ne peut que perde sur le dernier coup joué)
 *        avec les positions des bombes, en fonction du coup
 *        (M ou D) GAME_LOST ou GAME_NOT_LOST sera 
 *        attrituer à l'etatj
 *
 * @param [in, out] g: la grille de jeu
 * @param [in] p: le problème
 * @param [in] hc: l'historique des coups
 */
void test_lost(Grille& g, const Problem& p, const Historique_coup& hc);

/**
 * @brief Affiche une ligne "game lost" ou "games not lost"
 *        fonction de l'etatj de la grille
 *
 * @param [in] g: la grille de jeu
 */
void affichage_lost(const Grille& g);
/***************************** FIN COMMANDE 4 ********************************/
/**************************** DEBUT COMMANDE 5 *******************************/

/**
 * @brief Initialise le nombre de lignes et colonnes dans
 *        la stucture de donnée
 *
 * @param [out] g: la grille
 */
void saisie_dimension_grille(Grille& g);

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
 * @brief Analyse la grille en entré et le stock
 *        les données en fonction des valeurs lu
 * 
 * @see val_adja: convertit un chiffre ASCCI en entier naturel
 *
 * @param [in,out] g: la grille
 */
void traitement_grille(Grille& g);

/**
 * @brief Compte le nombre de case qui sont
 *        à l'état CACHER
 *
 * @param [in] g: la grille
 * @return unsigned int: le totale de case CACHER
 */
unsigned int count_hidden(const Grille& g);

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
void choice_move(const Grille& g, Details_coups& nw, const unsigned int nb_cacher);

/**
 * @brief Créer un nouveau coup en fonction de
 *        la grille donnée
 *
 * @param [in] g: la grille
 * @param [in] nw: le nouveau coup
 */
void creat_new_move(Grille& g, Details_coups& nw);
/***************************** FIN COMMANDE 5 ********************************/

#endif // !_GRILLE_
