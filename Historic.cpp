/**
 * @file Historic.cpp
 * @author Anxian Zhang (gadanxianzhang@gmail.com.com)
           Vick Ye (vickye2908@gmail.com)
 * @brief Composant de l'historique
 * @version 1
 * @date 2021-12-31
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
using namespace std;

#include "Historic.h"

void allocation_coup(MoveHistoric& hc)
{
    hc.list = new MoveDetails[hc.nbMove];
}

void desallocation_coup(MoveHistoric& hc)
{
    delete[]hc.list;
}