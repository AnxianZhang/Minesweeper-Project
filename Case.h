/****************************************
 Nom---------: Case.h
 Role--------: Composant de(s) case(s)
 Auteurs-----: Anxian Zhang, Ye vick
 Version-----: V1 du 31/12/2021
****************************************/

#ifndef _CASE_
#define _CASE_

/**
 * @brief Type enumeré pour connaitre l'état d'une case
 *
 */
enum Etat_case { DEMASQUER, MARQUER, CACHER };

/**
 * @brief Type structuré contient les informations nessessaire
 *        pour une case donnée
 *
 */
struct Case {
    unsigned int contenue;
    Etat_case etat;
};

#endif // !_CASE_
