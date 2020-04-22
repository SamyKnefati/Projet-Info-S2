#include "Graphe.h"

#include <fstream>
#include <queue>
#include <stack>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>


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
    int num1, num2, num3, type;
    std::string nomRue;
    for(int i=0; i<taille; i++){
        ifs >> num1 >> num2 >> num3 >> nomRue>> type;
        if(ifs.fail()){
            throw std::runtime_error("Problème de lecture d'un arc/arrete et poids"); ///Execute au moment de l execution
        }
        m_sommets[num1]->addSuccesseur(m_sommets[num2]); ///num1 successeur de num2
        if(!m_estOriente && num1 < num2) {
            m_sommets[num2]->addSuccesseur(m_sommets[num1]);
        }
        m_arete.push_back(new Aretes(num1,num2,num3,nomRue, type)); /// ajout de rue/avenue
    }

    std::string name;
    int x,y;
    for(int i=1; i<ordre+1; i++){
        ifs >> name >> x >> y;


        if(ifs.fail()){
            throw std::runtime_error("Problème de lecture du nom du lieu"); ///Execute au moment de l execution
        }
        m_sommets[i]->addName(name);
        m_sommets[i]->addCoor(x,y);
    }

}

Graphe::~Graphe() {
    for (auto addSommet: m_sommets) { ///chaque cases possèdes une adresse de sommets qui seront detruit
        delete addSommet;
    }
    for (auto addArretes: m_arete) {
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
    for (auto addrArretes : m_arete){
        addrArretes->afficherA();
        std::cout << std::endl;
    }
}


void Graphe::kruskal()  {
    /// on trie les aretes

    for (int i = 0; i != m_arete.size(); i++) {
        for (int a = 0; a != (m_arete.size() - 1); a++) {
            if (m_arete[a]->GetCapacite() > m_arete[a + 1]->GetCapacite())
            {
                Aretes *inter;

                inter = m_arete[a];

                m_arete[a] = m_arete[a + 1];

                m_arete[a + 1] = inter;

            }

        }

    }

    std::cout<<std::endl<<"TRI PAR ORDRE CROISSANT"<<std::endl;
    for(int i=0; i!=m_arete.size();i++)
    {

        m_arete[i]->afficherA();
        std::cout<<std::endl;

    }

    ///tri effectue, on finalise kruskal

    std::vector<const Aretes*>MST;
    const Aretes* Arr;
    int D,A;
    m_capaciteChemin=0;

    for(int i=0; i!=m_arete.size();i++)
    {
        Arr=m_arete[i];

        m_sommets[Arr->Getm_D()]->Setutiliser();
        m_sommets[Arr->Getm_A()]->Setutiliser();


        D=m_sommets[Arr->Getm_D()]->Getutiliser();
        A=m_sommets[Arr->Getm_A()]->Getutiliser();


        if(A<=2 && D<=2){

            MST.push_back(m_arete[i]);
            m_capaciteChemin+=Arr->GetCapacite();

        }
        if( (A>2 && D<2) || (D>2 && A<2)){
            MST.push_back(m_arete[i]);
            m_capaciteChemin+=Arr->GetCapacite();
        }
    }
    m_kruskal=MST;

    std::cout<<std::endl<<" Algorithme de Kruskal : "<<std::endl;

    for(int i=0; i!=MST.size();i++)
    {

        MST[i]->afficherA();
        std::cout<<std::endl;

    }

    std::cout<<std::endl;
    std::cout<<" capacite Total : "<<m_capaciteChemin<<std::endl;
}



void Graphe::Allegro(std::vector< const Aretes*>&  kruskal ) {


    ALLEGRO_DISPLAY*display= nullptr;
    ALLEGRO_MOUSE_STATE mouse;
    //ALLEGRO_BITMAP* map ;
    ALLEGRO_EVENT_QUEUE *Queue;
    ALLEGRO_FONT *font;
    ALLEGRO_FONT *font2;
    bool isEnd;


    al_set_target_backbuffer(display);
    ALLEGRO_EVENT event={0};


    display= al_create_display(1600,800);
   // map = al_load_bitmap("../map.JPG");
    font = al_load_ttf_font("../police.TTF", 30, 0);
    font2 = al_load_ttf_font("../police.TTF", 60, 0);
    Queue = al_create_event_queue();
    al_set_target_backbuffer(display);
    al_register_event_source(Queue,al_get_display_event_source(display));


    while(isEnd != TRUE) {


       // al_draw_bitmap(map, 10, 0, 0);
        al_draw_textf(font2, al_map_rgb(255, 255, 255), 1200,100 / 2 - al_get_font_ascent(font),
                ALLEGRO_ALIGN_CENTER, "Fete des lumieres 2021: ");
        al_draw_textf(font, al_map_rgb(255, 255, 255), 1400,200,
                      ALLEGRO_ALIGN_CENTER, " : LIEUX ");
        al_draw_filled_circle(1330,213,10,al_map_rgb(255,255,255));
        al_draw_textf(font, al_map_rgb(255, 0, 0), 1400,250,
                      ALLEGRO_ALIGN_CENTER, " ---: TRANSPORTS EN COMMUN ");
        al_draw_textf(font, al_map_rgb(0, 255, 0), 1400,300,
                      ALLEGRO_ALIGN_CENTER, " ---: RUES ");
        al_draw_textf(font, al_map_rgb(0, 0, 255), 1400,350,
                      ALLEGRO_ALIGN_CENTER, " ---: PONTS ");



        for (int i = 1; i != m_sommets.size(); i++) {


            al_draw_filled_circle(m_sommets[i]->GetX(),m_sommets[i]->GetY(),10,al_map_rgb(255,255,255));


            al_draw_textf(font, al_map_rgb(255, 255, 255), m_sommets[i]->GetX()+110,m_sommets[i]->GetY() ,
                          ALLEGRO_ALIGN_CENTER, "%s", m_sommets[i]->GetName().c_str());

        }


        for (int i = 0; i != m_arete.size(); i++) {



            switch(m_arete[i]->GetmType())

            {

                case 0:


                    al_draw_line(m_sommets[m_arete[i]->Getm_D()]->GetX(),m_sommets[m_arete[i]->Getm_D()]->GetY(),
                                 m_sommets[m_arete[i]->Getm_A()]->GetX(),m_sommets[m_arete[i]->Getm_A()]->GetY(),
                                 al_map_rgb(255,0,0),5.0);
                    break;
                case 1:
                    al_draw_line(m_sommets[m_arete[i]->Getm_D()]->GetX(),m_sommets[m_arete[i]->Getm_D()]->GetY(),
                                 m_sommets[m_arete[i]->Getm_A()]->GetX(),m_sommets[m_arete[i]->Getm_A()]->GetY(),
                                 al_map_rgb(0,255,0),5.0);
                    break;
                case 2:
                    al_draw_line(m_sommets[m_arete[i]->Getm_D()]->GetX(),m_sommets[m_arete[i]->Getm_D()]->GetY(),
                                 m_sommets[m_arete[i]->Getm_A()]->GetX(),m_sommets[m_arete[i]->Getm_A()]->GetY(),
                                 al_map_rgb(0,0,255),5.0);
                    break;


            }


        }


       for(int i=0; i != kruskal.size(); i++)
        {

            al_draw_line((m_sommets[kruskal[i]->Getm_D()]->GetX()),m_sommets[kruskal[i]->Getm_D()]->GetY(),
                         (m_sommets[kruskal[i]->Getm_A()]->GetX()),m_sommets[kruskal[i]->Getm_A()]->GetY(),
                         al_map_rgb(255,0,255),3.0);


        }


        al_flip_display();

        al_wait_for_event(Queue,&event);

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            isEnd=TRUE;
        }



    }

    al_destroy_display(display);
    al_destroy_event_queue(Queue);
    //al_destroy_bitmap(map);
    al_destroy_font(font);
    al_destroy_font(font2);
}

std::vector<int> Graphe::BFS(int numero_S0) const {
    ///Tous les sommets sont blancs nn decouverts
    std::vector<int > couleurs((int) m_sommets.size(), 0);
    ///Creer une file vide
    std::queue<const Sommet*> file;
    std::vector<int > predecesseurs((int) m_sommets.size(), -1);
    ///Enfiler s0; s0 deviens gris
    file.push(m_sommets[numero_S0]);
    couleurs[numero_S0] = 1; // gris
    const Sommet* s; /// On ne modifie pas l'adresse de s.
    ///Tant que la file n'est pas vide
    while(!file.empty()){
        ///Defiler le prochain sommet s de la file
        s = file.front();
        file.pop();
        ///Pour chaque successeur s' blanc non decourt de s:
        for(auto succ: s->getSuccesseur()){
            if(couleurs[succ->getNumero()] == 0){
                ///Enfiler s'; s' deviens gris
                file.push(succ);
                couleurs[succ->getNumero()] = 1; // gris
                ///Noter s est le predecesseur de s'
                predecesseurs[succ->getNumero()] = s->getNumero();
            }
        }
        couleurs[s-> getNumero()] = 2; //noir

    }
    return predecesseurs;
}

/*void Graphe::ford_fulkerson(int depart, int arrivee) {


}*/


void Graphe::DFS(int numero_S0,int &chaine) const {

    static int date = 0;
    static std::vector<int > couleurs((int) m_sommets.size(), 0);
    static std::stack<const Sommet*> pile;
    static std::vector<int> cc;
    pile.push(m_sommets[numero_S0]); // est le sommet s
    couleurs[numero_S0]=1;
    std::cout<<numero_S0;
    for (auto succ: m_sommets[numero_S0]->getSuccesseur()) {

        if(couleurs[succ->getNumero()] == 1){
            chaine = 1;
        }

        if (couleurs[succ->getNumero()] == 0) {
            std::cout << " ----> ";
            pile.push(m_sommets[succ->getNumero()]);
            date += 1;
            DFS(succ->getNumero(),chaine);
        }
    }
    couleurs[numero_S0] = 2;
}

int Graphe::getMarque(int num) const {
    return m_sommets[num]->m_marque;
}

bool Graphe::getOriente() const {
    return m_estOriente;
}