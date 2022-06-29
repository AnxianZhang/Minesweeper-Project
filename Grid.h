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
 * @brief Type structur� de la grille de jeu
 *
 */
struct Grille {
    Case** grille_jeu;
    unsigned int lignes;
    unsigned int colonnes;
    Etat_Partie etatj; // �tat du jeu
};
/***************************** DEBUT COMMANDE 1 ******************************/
/**
 * @brief Cr�er le probl�me
 *
 * @param [in] g: la grille qui va �tre g�n�r� avec le probl�me donn�
 * @param [in] p: le probl�me
 */
void creation_problem(Grille& g, Problem& p);

/**
 * @brief Alloue dynamiquement un tableau � deux
 *        avec les dimensions donn�s
 *
 * @see allocation_grille: d�salloue le tableau �
 *                         2 dimensions
 *
 * @param [out] g: la grille
 */
void allocation_grille(Grille& g);

/**
 * @brief D�salloue le tableau � deux
 *        dimensions
 *
 * @param [out] g: la grille
 */
void desallocation_grille(Grille& g);

/**
 * @brief Initialise toutes les cases du tableau
 *        l'�tat CACHER et son contenue � 0
 *
 * @param [out] g: la grille
 * @param [in] p: le probl�me
 */
void initialisation_grille(Grille& g, const Problem& p);

/**
 * @brief Place le nombre de bombe indiqu�e en entr�
 *        au d�but du tableau
 *
 * @see rand_bombes: m�lange le tableau pour les placer
 *                   all�atoirement
 *
 * @param [out] g: la grille de jeu
 * @param [in] p: le probl�me
 * @pre p.bombes <= p.lignes * p.colonnes
 */
void place_bombes_debut(Grille& g, const Problem& p);

/**
 * @brief M�lange les cases du tableau pour placer
 *        all�atoirement les bombes qui sont initialement au
 *        debut de ce-dernier
 *
 * @see get_pos_bombes: cherche les positions des bombes
 *
 * @param [out] g: la grille de jeu
 * @param [in] p: le probl�me
 */
void rand_bombes(Grille& g, const Problem& p);

/**
 * @brief Cherche toute les bombes qui se trouvent
 *        dans la grille pour ensuite stocker
 *        leurs positions dans le tableau de bombes
 *        cr�e dynamiquement
 *
 * @param [in] g: la grille de jeu
 * @param [in, out] p: le probl�me
 */
void get_pos_bombes(const Grille& g, Problem& p);
/***************************** FIN COMMANDE 1 ********************************/
/**************************** DEBUT COMMANDE 2 *******************************/

/**
 * @brief Saisit les donn�es necessaires
 *
 * @param [out] g: la grille
 * @param [out] p: le probl�me
 * @param [out] hc: l'historique des coups
 */
void saisie_grille(Grille& g, Problem& p, Historique_coup& hc);

/**
 * @brief Initalise les positions des bombes donn�e en entr�
 *        dans la grille de jeu (sont toujours � l'�tat CACHER)
 *
 * @param [out] g: le grille
 * @param [in] p: le probl�me
 */
void initialisation_bombe(Grille& g, const Problem& p);

/**
 * @brief Affiche une grille avec son contenue en fonction
 *        le l'�tat des cases
 *
 * @param [in] g: la grille de jeu
 * @param [in] p: le probl�me
 */
void affichage_grille(const Grille& g, const Problem& p);

/**
 * @brief Affecte les bombes � leurs position respective
 *        et met toutes les cases contenant des bombes
 *        � l'etat DEMASQUER si le dernier coup
 *        jou� met fin � la partie
 *
 * @param [out] g: la grille
 * @param [in] p: le probl�me
 */
void attribution_bombe_perdu(Grille& g, const Problem& p);

/**
 * @brief Verifie si la position du coup jou�
 *        corespond � celle d'une bombes
 *
 * @param [in] p: le probl�me
 * @param [in] pos_coup: la position du coup
 * @return int 1 si c'est vrais, 0 si c'est faux
 */
int verification(const Problem& p, const unsigned int pos_coup);

/**
 * @brief Marque une case donn�e que si elle ne pas
 *        corespond � celle d'une bombe
 *
 * @see attribution_bombe_perdu: met toute les bombes � l'�tat DEMASQUER
 *                               dans le cas contraire
 *
 * @param [out] g: la grille
 * @param [in] p: le probl�me
 * @param [in] posc: position du coup jou�
 * @param [in] lc: ligne du coup jou�
 * @param [in] cc: colonne du coup jou�
 */
void mark(Grille& g, const Problem& p, const unsigned int posc,
    const unsigned int lc, const unsigned int cc);

/**
 * @brief D�masque une ou plusieurs cases 
          si celle-ci n'est pas une bombe
 *
 * @see attribution_bombe_perdu: met toute les bombes � l'�tat DEMASQUER
 *                               dans le cas contraire
 * @see recurrence: se charge du d�masquage si le coup jou� n'est pas � la
 *                  position d'un bombe
 *
 * @param [out] g: la grille
 * @param [in] p: le probl�me
 * @param [in] posc: position du coup jou�
 * @param [in] lc: ligne du coup jou�
 * @param [in] cc: colonne du coup jou�
 */
void unmask(Grille& g, const Problem& p, const unsigned int posc,
    const unsigned int lc, const unsigned int cc);

/**
* @brief Met qu'une case � l'�tat DEMASQUER si la case � d�masquer contient
*        un chiffre mais si la case de d�part est vide et que ces cases ajdacentes
*        sont elles aussi vide la fonction d�masquera ces case,
*        l'op�ration se r�p�te jusqu'� que la zone soit entour� par des chiffres
*
* @param [out] g: la grille
* @param [in] p: le probl�me
* @param [in] pos: la postion du coup
*/
void recurrence(Grille& g, const Problem& p, const unsigned int pos);

/**
 * @brief Indique le nombre de bombe dans les cases adjacentes
 *
 * @param [out] g: la grille de jeu
 * @param [in] p: le probl�me
 */
void give_value_adjacent(Grille& g, const Problem& p);

/**
 * @brief Traite les coups jou� pour savoir s'il faut
 *        marquer ou d�masqer
 *
 * @see demasquer: d�masque les cases indiqu�es
 * @see marquer: marque les cases indiqu�es
 *
 * @param [in] g: la grille de jeu
 * @param [in] p: le probl�me
 * @param [in] hc: l'historique de coup
 */
void reconnaissance_coup(Grille& g, const Problem& p, const Historique_coup hc);

/**
 * @brief Cr�er la grille pour ensuite exploiter
 *        les donn�es lors de l'affichage
 *
 * @param [in] g: la grille de jeu
 * @param [in] p: le probl�me
 * @param [in] hc: l'historique de coup
 */
void creation_grille(Grille& g, Problem& p, Historique_coup hc);
/***************************** FIN COMMANDE 2 ********************************/
/**************************** DEBUT COMMANDE 3 *******************************/
/**
 * @brief Fait des testes sur l'ensemble de la grille
 *        pour d�terminer si la partie est gagn� ou pas
 *        en affectant GAME_WON ou GAME_NOT_WON � l'etatj
 *
 * @param [in, out] g: la grille de jeu
 * @param [in] p: le probl�me
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
 *        on ne peut que perde sur le dernier coup jou�)
 *        avec les positions des bombes, en fonction du coup
 *        (M ou D) GAME_LOST ou GAME_NOT_LOST sera 
 *        attrituer � l'etatj
 *
 * @param [in, out] g: la grille de jeu
 * @param [in] p: le probl�me
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
 *        la stucture de donn�e
 *
 * @param [out] g: la grille
 */
void saisie_dimension_grille(Grille& g);

/**
 * @brief Convertit un chiffre de type char en unsigned int
 *        grace au calcul storage - '0' avec 0 = 48
 *
 * @param [in] storage: le chiffre � convertir
 * @return unsigned int: la valeur convertit
 * @pre storage >= '1' && storage <= '8'
 */
unsigned int val_adja(char storage);

/**
 * @brief Analyse la grille en entr� et le stock
 *        les donn�es en fonction des valeurs lu
 * 
 * @see val_adja: convertit un chiffre ASCCI en entier naturel
 *
 * @param [in,out] g: la grille
 */
void traitement_grille(Grille& g);

/**
 * @brief Compte le nombre de case qui sont
 *        � l'�tat CACHER
 *
 * @param [in] g: la grille
 * @return unsigned int: le totale de case CACHER
 */
unsigned int count_hidden(const Grille& g);

/**
 * @brief Choisie un coups parmis les cases
 *        � l'�tat CACHER
 * 
 * @see count_hidden: compte le nombre totale de case cach�
 *
 * @param [in] g: la grille
 * @param [out] nw: la nouvelle position
 * @param [in] nb_cacher: nombre de case � l'�tat CACHER
 */
void choice_move(const Grille& g, MoveDetails& nw, const unsigned int nb_cacher);

/**
 * @brief Cr�er un nouveau coup en fonction de
 *        la grille donn�e
 *
 * @param [in] g: la grille
 * @param [in] nw: le nouveau coup
 */
void creat_new_move(Grille& g, MoveDetails& nw);
/***************************** FIN COMMANDE 5 ********************************/

#endif // !_GRILLE_
