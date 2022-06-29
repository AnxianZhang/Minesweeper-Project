/****************************************
 Nom---------: Problem.h
 Role--------: Composant du probl�me
 Auteurs-----: Anxian Zhang, Ye vick
 Version-----: V2 du 31/12/2021
****************************************/

#ifndef _PROBLEM_
#define _PROBLEM_

/**
 * @brief Type structur� qui stock toutes les donn�es relatives �
 *        la g�neration d'un probl�me
 *
 */
struct Problem {
    unsigned int lignes;
    unsigned int colonnes;
    unsigned int bombes;
    unsigned int* pos_bombe; // position des bombes
};

/**
 * @brief Permet la saisie d'un probl�me
 *
 * @param [out] p: probl�me � cr�er
 */
void saisie_problem(Problem& p);

/**
 * @brief Alloue dynamiquement un tableau pour le nombre
 *        de bombes donn�
 *
 * @see desallocation_bombe: d�salloue le tableau de bombe
 *
 * @param [out] p: le probl�me
 */
void allocation_bombe(Problem& p);

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
 * @brief D�salloue le tableau de bombe
 *
 * @param [out] p: le pribl�me
 */
void desallocation_bombe(Problem& p);

/**
 * @brief Affiche le probl�me
 *
 * @param [in] p: le probl�me
 */
void affichage_problem(const Problem& p);

#endif // !_PROBLEM_
