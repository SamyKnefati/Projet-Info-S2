
#include <iostream>
#include "Sommet.h"

class Arete {
private:
    int m_poids;
    Sommet m_sommet1;
    Sommet m_sommet2;
public:
    Arete(int poids, Sommet sommet1, Sommet sommet2);
    int getPoids() const;
    int getNumSommet1() const;
    int getNumSommet2() const;
    void afficher() const;
};


#endif //TP5_ARETE_H
