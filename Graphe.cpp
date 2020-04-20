#include "Graphe.h"

#include <fstream>
#include <queue>
#include <stack>

Graphe::Graphe(std::string cheminFichierGraphe) {
    std::ifstream ifs{cheminFichierGraphe};
    if (!ifs){
        throw std::runtime_error("Impossible d'ouvrir " + cheminFichierGraphe);
    }
    ifs >> m_estOriente; //m_estOrienté prends soit 0 ou 1
    if(ifs.fail()){
        throw std::runtime_error("Problème de lecture de l'orientation du graphe."); ///Execute au moment de l execution
    }
    int ordre;
    ifs >> ordre;
    if(ifs.fail()){
        throw std::runtime_error("Problème de lecture de l'orientation du graphe."); ///Execute au moment de l execution
    }
    int taille;
    ifs >> taille;
    if(ifs.fail()){
        throw std::runtime_error("Problème de lecture de l'orientation du graphe."); ///Execute au moment de l execution
    }
    for(int i=0; i< ordre+1; i++){
        m_sommets.push_back(new Sommet(i)); ///prends en compte le nombre de sommet dans le graphe
    }
    int num1, num2, num3;
    for(int i=0; i<taille; i++){
        ifs >> num1 >> num2 >> num3;
        if(ifs.fail()){
            throw std::runtime_error("Problème de lecture d'un arc/arrete et poids"); ///Execute au moment de l execution
        }
        m_sommets[num1]->addSuccesseur(m_sommets[num2]); ///num1 successeur de num2
        if(!m_estOriente && num1 < num2) {
            m_sommets[num2]->addSuccesseur(m_sommets[num1]);
        }
        m_arrete.push_back(new Aretes(num1,num2,num3)); /// ajout d'arrete avec leur poids.
    }

}

Graphe::~Graphe() {
    for (auto addSommet: m_sommets) { ///chaque cases possèdes une adresse de sommets qui seront detruit
        delete addSommet;
    }
    for (auto addArretes: m_arrete) {
        delete addArretes;
    }
}


void Graphe::afficher() const {
    std::cout << std::endl <<"Graphe ";
    std::cout << (m_estOriente ? " oriente" : "non oriente") << std::endl;
    std::cout << "Ordre : " << m_sommets.size()-1 << std::endl;
    std::cout << "Liste des Sommets : " << std::endl;
    for(auto addrSommet : m_sommets){
        addrSommet-> afficher();
    }

    std::cout <<std::endl<< "Liste des Arretes : " << std::endl;
    for (auto addrArretes : m_arrete){
        addrArretes->afficherA();
        std::cout << std::endl;
    }
}

void::Graphe::Tri() {

    for (int i = 0; i != m_arrete.size(); i++) {
        for (int a = 0; a != (m_arrete.size() - 1); a++) {
            if (m_arrete[a]->Getpoids() > m_arrete[a + 1]->Getpoids())
            {
                Aretes *inter;

                inter = m_arrete[a];

                m_arrete[a] = m_arrete[a + 1];

                m_arrete[a + 1] = inter;

            }

        }

    }

    std::cout<<std::endl<<"TRI PAR ORDRE CROISSANT"<<std::endl;
    for(int i=0; i!=m_arrete.size();i++)
    {

        m_arrete[i]->afficherA();
        std::cout<<std::endl;

    }


}