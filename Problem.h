/****************************************
 Nom---------: Problem.h
 Role--------: Composant du problème
 Auteurs-----: Anxian Zhang, Ye vick
 Version-----: V2 du 31/12/2021
****************************************/

#ifndef _PROBLEM_
#define _PROBLEM_

/**
 * @brief Type structuré qui stock toutes les données relatives à
 *        la géneration d'un problème
 *
 */
struct Problem {
    unsigned int lignes;
    unsigned int colonnes;
    unsigned int bombes;
    unsigned int* pos_bombe; // position des bombes
};

/**
 * @brief Permet la saisie d'un problème
 *
 * @param [out] p: problème à créer
 */
void saisie_problem(Problem& p);

/**
 * @brief Alloue dynamiquement un tableau pour le nombre
 *        de bombes donné
 *
 * @see desallocation_bombe: désalloue le tableau de bombe
 *
 * @param [out] p: le problème
 */
void allocation_bombe(Problem& p);

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
 * @brief Désalloue le tableau de bombe
 *
 * @param [out] p: le priblème
 */
void desallocation_bombe(Problem& p);

/**
 * @brief Affiche le problème
 *
 * @param [in] p: le problème
 */
void affichage_problem(const Problem& p);

#endif // !_PROBLEM_
