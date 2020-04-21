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
    int num1, num2, num3;
    std::string nomRue;
    for(int i=0; i<taille; i++){
        ifs >> num1 >> num2 >> num3 >> nomRue;
        if(ifs.fail()){
            throw std::runtime_error("Problème de lecture d'un arc/arrete et poids"); ///Execute au moment de l execution
        }
        m_sommets[num1]->addSuccesseur(m_sommets[num2]); ///num1 successeur de num2
        if(!m_estOriente && num1 < num2) {
            m_sommets[num2]->addSuccesseur(m_sommets[num1]);
        }
        m_arete.push_back(new Aretes(num1,num2,num3,nomRue)); /// ajout de rue/avenue
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

void::Graphe::Tri() {

    for (int i = 0; i != m_arete.size(); i++) {
        for (int a = 0; a != (m_arete.size() - 1); a++) {
            if (m_arete[a]->Getpoids() > m_arete[a + 1]->Getpoids())
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


}

void Graphe::Allegro(ALLEGRO_FONT *font) {


    ALLEGRO_DISPLAY*display= nullptr;
    ALLEGRO_MOUSE_STATE mouse;
    ALLEGRO_BITMAP* map ;
    ALLEGRO_EVENT_QUEUE *Queue;
    bool isEnd;


    al_set_target_backbuffer(display);
    ALLEGRO_EVENT event={0};
    display= al_create_display(1600,800);
    std::cout<<"coucou"<<std::endl;
    map = al_load_bitmap("../map.JPG");
    font = al_load_ttf_font("../police.TTF", 30, 0);
    Queue = al_create_event_queue();
    al_set_target_backbuffer(display);
    al_register_event_source(Queue,al_get_display_event_source(display));


    while(isEnd != TRUE) {


        al_draw_bitmap(map, 10, 0, 0);
        al_draw_textf(font, al_map_rgb(255, 0, 127), 1200,100 / 2 - al_get_font_ascent(font),
                ALLEGRO_ALIGN_CENTER, "Fete des lumieres 2021: ");
        al_draw_textf(font, al_map_rgb(255, 255, 255), 900,200 / 2 - al_get_font_ascent(font),
                      ALLEGRO_ALIGN_CENTER, "LIEUX: ");

        for (int i = 1; i != m_sommets.size(); i++) {

            al_draw_filled_circle(m_sommets[i]->GetX(),m_sommets[i]->GetY(),10,al_map_rgb(0,0,0));
            al_draw_textf(font, al_map_rgb(255, 255, 255), 950,(200 +i*50) / 2 - al_get_font_ascent(font),
                          ALLEGRO_ALIGN_CENTER, "%s", m_sommets[i]->GetName().c_str());

        }

        al_draw_textf(font, al_map_rgb(255, 255, 255), 1000,500 / 2 - al_get_font_ascent(font),
                      ALLEGRO_ALIGN_CENTER, "VOIES DE PASSAGE : ");

        for (int i = 0; i != m_arete.size(); i++) {


            al_draw_textf(font, al_map_rgb(255, 0, 0), 1050, (550 + (i * 50)) / 2 - al_get_font_ascent(font),
                          ALLEGRO_ALIGN_CENTER, "%s", m_arete[i]->GetName().c_str());

            al_draw_line(m_sommets[m_arete[i]->Getm_D()]->GetX(),m_sommets[m_arete[i]->Getm_D()]->GetY(),
                         m_sommets[m_arete[i]->Getm_A()]->GetX(),m_sommets[m_arete[i]->Getm_A()]->GetY(),
                         al_map_rgb(0,0,0),10.0);

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
    al_destroy_bitmap(map);
    al_destroy_font(font);
}