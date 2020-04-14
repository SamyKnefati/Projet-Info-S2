#include "Graphe.h"

Graphe::Graphe(const std::string cheminFichierGraphe) {
    std::ifstream ifs{cheminFichierGraphe};
    if (!ifs){
        throw std::runtime_error("Impossible d'ouvrir " + cheminFichierGraphe);
    }
    int ordre;
    ifs >> ordre;
    if(ifs.fail()){
        throw std::runtime_error("Problème de lecture de l'ordre du graphe."); ///Execute au moment de l execution
    }
    int taille;
    ifs >> taille;
    if(ifs.fail()){
        throw std::runtime_error("Problème de lecture de la taille du graphe."); ///Execute au moment de l execution
    }
    for(int i=0 ; i<ordre ; i++){
        m_sommets.push_back(new Sommet(i)); ///Prend en compte le nombre de sommets dans le graphe
    }
    int num1, num2, num3;
    for(int i=0 ; i<taille ; i++){
        ifs >> num1 >> num2 >> num3;
        num1 = num1 - 1;
        num2 = num2 - 1;
        if(ifs.fail()){
            throw std::runtime_error("Problème de lecture d'un arc/arrete."); ///Execute au moment de l execution
        }
        m_sommets[num1]->addSuccesseur(m_sommets[num2]);
        if(num1 < num2) {
            m_sommets[num2]->addSuccesseur(m_sommets[num1]);
        }
        m_aretes.push_back(new Arete(num3, *m_sommets[num1], *m_sommets[num2]));
    }
}

Graphe::~Graphe() {
    for (auto addSommet: m_sommets) { ///chaque case possède une adresse de sommet qui sera detruite
        delete addSommet;
    }
    for (auto addArete: m_aretes){ ///chaque case possède une adresse d'arete qui sera detruite
        delete addArete;
    }
}

void Graphe::afficher() const {
    std::cout << std::endl <<"--------     Graphe TP5     --------" << std::endl;
    std::cout << "Ordre : " << m_sommets.size() << std::endl;
    std::cout << "Taille : " << m_aretes.size() << std::endl;
    std::cout << "Liste des sommets avec leur adjacence : " << std::endl;
    for(auto iSommet : m_sommets){
        iSommet->afficher();
        std::cout << std::endl;
    }
    std::cout << "Liste des arêtes avec leur poids : " << std::endl;
    for(auto iArete : m_aretes){
        iArete->afficher();
        std::cout << std::endl;
    }
}

void Graphe::triPoidsAretes(){
    for(int i=0 ; i!=m_aretes.size() ; ++i){
        for(int j=0 ; j!=(m_aretes.size()-1) ; j++){
            if(m_aretes[j]->getPoids() > m_aretes[j+1]->getPoids()) {
                Arete *ar;
                ar = m_aretes[j];
                m_aretes[j] = m_aretes[j+1];
                m_aretes[j+1] = ar;
            }
        }
    }
    std::cout << "Affichage arêtes par poids croissant :" << std::endl;
    for(auto iAretes : m_aretes){
        iAretes->afficher();
        std::cout << std::endl;
    }
}

void Graphe::algoKruskal(){
    std::vector<Arete*> areteKruskal;
    int poidsKruskal = 0;
    std::vector<int> num_CC;
    for(int i=0 ; i<m_sommets.size()-1 ; ++i){
        num_CC.push_back(i); /// Attribution des numéros de composantes connexes
    }
    triPoidsAretes();
    for(int i=0 ; i<m_aretes.size() ; ++i){
            if(areteKruskal.size() < m_sommets.size()-1) {
                if (num_CC[m_aretes[i]->getNumSommet1()-1] != num_CC[m_aretes[i]->getNumSommet2()-1]) {
                    for(int j=0 ; j<m_sommets.size()-1 ; ++j){
                        if(num_CC[j] == num_CC[m_aretes[i]->getNumSommet2()-1] && j != m_aretes[i]->getNumSommet2()-1){
                            num_CC[j] = num_CC[m_aretes[i]->getNumSommet1()-1];
                        }
                    }
                    areteKruskal.push_back(m_aretes[i]);
                    num_CC[m_aretes[i]->getNumSommet2()-1] = num_CC[m_aretes[i]->getNumSommet1()-1];
                    poidsKruskal += m_aretes[i]->getPoids();
                }
            }
    }
    std::cout << "Affichage de l'arbre couvrant : " << std::endl;
    for(auto iArete : areteKruskal){
        std::cout << "     Arete    : " << iArete->getNumSommet1() + 1 << "<->" << iArete->getNumSommet2() + 1 << " : " << iArete->getPoids() << std::endl;
    }
    std::cout << "Nombre d'arêtes : " << areteKruskal.size() << " arêtes et poids total : " << poidsKruskal << std::endl;
}

