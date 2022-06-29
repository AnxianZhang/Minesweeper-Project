/****************************************
 Nom---------: Historique.h
 Role--------: Composant de l'historique
 Auteurs-----: Anxian Zhang, Ye vick
 Version-----: V1 du 31/12/2021
****************************************/

#ifndef _HISTORIQUE_
#define _HISTORIQUE_

#include "Details.h"

/**
 * @brief Type structur� pour l'historique
 *        des coups jou�s
 *
 */
struct Historique_coup {
    unsigned int nb_coup;
    MoveDetails* liste_coup;
};

/**
 * @brief Alloue un tableau en fonction du nombre
 *        de coup donn� en entr�
 *
 * @see desallocation_coup: Desalloue le tableau
 *
 * @param [out] hc: l'historique de coups
 */
void allocation_coup(Historique_coup& hc);

/**
 * @brief Desalloue le tableau des coups
 *
 * @param [out] hc: l'historique de coups
 */
void desallocation_coup(Historique_coup& hc);

#endif // !_HISTORIQUE_
