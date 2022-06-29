#include <iostream>
using namespace std;

#include "Historique.h"

void allocation_coup(Historique_coup& hc)
{
    hc.liste_coup = new MoveDetails[hc.nb_coup];
}

void desallocation_coup(Historique_coup& hc)
{
    delete[]hc.liste_coup;
}