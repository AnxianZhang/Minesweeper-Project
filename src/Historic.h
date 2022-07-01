/**
 * @file Historic.h
 * @author Anxian Zhang (gadanxianzhang@gmail.com.com)
           Vick Ye (vickye2908@gmail.com)
 * @brief Composant de l'historique
 * @version 1
 * @date 2021-12-31
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _HISTORIC_
#define _HISTORIC_

#include "Details.h"

struct MoveHistoric {
    unsigned int nbMove;
    MoveDetails* list;
};

/**
 * @brief Alloue un tableau en fonction du nombre
 *        de coup donné en entrée
 *
 * @see desallocation_coup: Desalloue le tableau
 *
 * @param [out] hc: l'historique de coups
 */
void allocation_coup(MoveHistoric& hc);

/**
 * @brief Desalloue le tableau des coups
 *
 * @param [out] hc: l'historique de coups
 */
void desallocation_coup(MoveHistoric& hc);

#endif // !_HISTORIC_
