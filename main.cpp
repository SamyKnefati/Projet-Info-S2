//
// Created by sam-d on 14/04/2020.
//

#include <iostream>
#include "Graphe.h"

int main ()
{
    std::cout << "test reussi"<<std::endl;
    size_t s0 = 0;
    Graphe g{"../Graphe_NO"};
    std::vector<int> arborescence;
    g.afficher();
    g.Tri();
}