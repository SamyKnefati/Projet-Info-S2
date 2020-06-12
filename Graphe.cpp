#include "Graphe.h"

#include <fstream>
#include <queue>
#include <stack>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <limits>
#include <algorithm>
#include <iostream>


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
    std::cout<<ordre<<std::endl;

    int taille;
    ifs >> taille;
    if(ifs.fail()){
        throw std::runtime_error("Problème de lecture de l'orientation du graphe."); ///Execute au moment de l execution
    }
    for(int i=0; i< ordre+1; i++){
        m_sommets.push_back(new Sommet(i)); ///prends en compte le nombre de sommet dans le graphe
    }
    int num1, num2, num3, type, distance, flotTot, flot;
    std::string nomRue;
    for(int i=0; i<taille; i++){
        ifs >> num1 >> num2 >> nomRue>> type >> distance >> flotTot >> flot;
        if(ifs.fail()){
            throw std::runtime_error("Problème de lecture d'un arc/arrete et poids"); ///Execute au moment de l execution
        }
        m_sommets[num1]->addSuccesseur(m_sommets[num2]);
        m_sommets[num1]->addSuccesseuS(m_sommets[num2], distance);
        ///num1 successeur de num2
        if(!m_estOriente && num1 < num2) {
            m_sommets[num2]->addSuccesseur(m_sommets[num1]);
            m_sommets[num2]->addSuccesseuS(m_sommets[num1], distance);
        }
        m_arete.push_back(new Aretes(num1,num2,nomRue, type, distance,flotTot,flot)); /// ajout de rue/avenue
    }

    std::string name;
    int x,y,nbPersMcarre, nbPersMcarreTot, Type;
    for(int i=1; i<ordre+1; i++){
        ifs >> name >> x >> y >> nbPersMcarre >> nbPersMcarreTot>>Type;
        if(ifs.fail()){
            throw std::runtime_error("Problème de lecture du nom du lieu"); ///Execute au moment de l execution
        }
        m_sommets[i]->addName(name);
        m_sommets[i]->addCoor(x,y);
        m_sommets[i]->addNbPersMcarreTot(nbPersMcarreTot);
        m_sommets[i]->addNbPersMcarre(nbPersMcarre);
        m_sommets[i]->addType(Type);
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
    std::cout << std::endl <<"Le graphe est ";
    std::cout << (m_estOriente ? " oriente" : "non oriente") << std::endl;
    std::cout << "Nombre d'attractions : " << m_sommets.size()-1 << std::endl;
    std::cout << "Nombre de chemins  : " << m_arete.size() << std::endl<< std::endl;
    stdw::cout <<"----------------------------------------------------"<<std::endl;
    std::cout << "Liste des Sommets : " << std::endl;
    for(auto addrSommet : m_sommets){
        addrSommet-> afficher();
    }

    std::cout <<std::endl<< "Liste des Arretes : " << std::endl<< std::endl;
    for (auto addrArretes : m_arete){
        addrArretes->afficherA();
        std::cout << std::endl<< std::endl;
    }
}


void Graphe::Kruskal() {

        int total=0;
        std::sort(m_arete.begin(), m_arete.end(), [](Aretes* a1, Aretes* a2) { return a1->getFlotMax() < a2->getFlotMax(); });
        std::vector<int> numCC; /// va nous servir a noter les numero de composantes connexes pour ensuite eviter les cycles
        for(int i=0;i<m_sommets.size();++i){
            numCC.push_back(i);
        }
        std::vector<const Aretes*> arbre;
        int nbre_Arete=0; ///on defini une variable dans laquelle stocker le nombre d'aretes qu'on insere
        int n=0; /// on definie une variable qu'on utilisera comme numero d'arete pour parcourir le vector d'aretes

        while(nbre_Arete<(m_sommets.size()-2)){
            if(numCC[m_sommets[m_arete[n]->Getm_D()]->getNumero()]!= numCC[m_sommets[m_arete[n]->Getm_A()]->getNumero()]){  ///on verifie que l'arete ne cree pas de cycle
                arbre.push_back(m_arete[n]);  /// on l'insere dans le vector d'arete qu'on retournera a la fin
                total += m_arete[n]->getFlotMax(); /// on ajoute a chaque fois le flot max de l'arete en question
                int x=numCC[m_sommets[m_arete[n]->Getm_A()]->getNumero()];/// on met a jour les numeros de composante connexe
                for(int i=0;i<numCC.size();++i)
                {
                    if(numCC[i]==x)
                    {
                        numCC[i]=numCC[m_sommets[m_arete[n]->Getm_D()]->getNumero()];
                    }
                }
                nbre_Arete++;
            }
            n++;
        }
        for(int i=0; i!=arbre.size();i++)
        {
            std::cout<<arbre[i]->Getm_D()<<" - "<<arbre[i]->Getm_A();
            std::cout<<std::endl;

        }
    std::cout<<"le flot total de cet arbre est de " << total << "  personnes" << std::endl;
        m_KruskalCapacite=arbre;
        m_capaciteChemin= total;
    }


void Graphe::Allegro(int s0, int s1) {


    ALLEGRO_DISPLAY*display= nullptr;
    ALLEGRO_MOUSE_STATE mouse;
    ALLEGRO_BITMAP* map = al_load_bitmap("../map.JPG");
    ALLEGRO_EVENT_QUEUE *Queue;
    ALLEGRO_EVENT_QUEUE *queue;
    ALLEGRO_FONT *font = al_load_ttf_font("../police.TTF", 30, 0);
    ALLEGRO_FONT *font2 = al_load_ttf_font("../police.TTF", 60, 0);
    ALLEGRO_FONT *font3 = al_load_ttf_font("../police.TTF", 25, 0);
    bool isEnd;
    int b=0, Y=200, c=0,d=0;


    al_set_target_backbuffer(display);
    ALLEGRO_EVENT event={0};
    ALLEGRO_EVENT Event={0};
    display= al_create_display(1920,1000);
    Queue = al_create_event_queue();
    queue = al_create_event_queue();
    al_set_target_backbuffer(display);
    al_register_event_source(Queue,al_get_display_event_source(display));
    al_register_event_source(Queue,al_get_keyboard_event_source());

    al_register_event_source(queue,al_get_display_event_source(display));
    al_register_event_source(queue,al_get_keyboard_event_source());

    while(isEnd != TRUE) {

        al_draw_textf(font2, al_map_rgb(255, 255, 255), 960,100 / 2 - al_get_font_ascent(font),
                      ALLEGRO_ALIGN_CENTER, "Fete des lumieres 2021: ");
        al_draw_textf(font2, al_map_rgb(255, 255, 255), 960,1000 / 2 - al_get_font_ascent(font),
                      ALLEGRO_ALIGN_CENTER, " [ APPUYER SUR ENTREE POUR DEMARRER LA SIMULATION: ");

        if(event.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch(event.keyboard.keycode)
            {
                case ALLEGRO_KEY_ENTER:
                    b=1;
                    break;
                default:
                    break;
            }
        }

        if(b==1)
        {
            al_clear_to_color(al_map_rgb(0,0,0));
            al_draw_bitmap(map, 10, 0, 0);
            al_draw_textf(font2, al_map_rgb(255, 255, 255), 1280,100 / 2 - al_get_font_ascent(font),
                          ALLEGRO_ALIGN_CENTER, "Fete des lumieres 2021: ");

            al_draw_textf(font2, al_map_rgb(255, 255, 255), 240,800,
                          ALLEGRO_ALIGN_CENTER, "1) INFOS RESEAUX :");

            al_draw_textf(font, al_map_rgb(255, 255, 255), 540,870,
                          ALLEGRO_ALIGN_CENTER, " : LIEUX ");
            al_draw_filled_circle(480,885,10,al_map_rgb(255,255,255));

            al_draw_textf(font, al_map_rgb(255, 0, 0), 240,870,
                          ALLEGRO_ALIGN_CENTER, " ---: TRANSPORTS EN COMMUN ");

            al_draw_textf(font, al_map_rgb(0, 255, 0), 240,940,
                          ALLEGRO_ALIGN_CENTER, " ---: RUES ");

            al_draw_textf(font, al_map_rgb(0, 0, 255), 540,940,
                          ALLEGRO_ALIGN_CENTER, " ---: PONTS ");

            al_draw_textf(font2, al_map_rgb(255, 255, 255), 1050,200,
                          ALLEGRO_ALIGN_CENTER, "2) LOCALISATION :");
            al_draw_textf(font2, al_map_rgb(255, 255, 255), 1000,600,
                          ALLEGRO_ALIGN_CENTER, "3) ANIMATIONS ");

            al_draw_textf(font, al_map_rgb(255, 255, 255), 940,870,
                          ALLEGRO_ALIGN_CENTER, "  Capacite totale d'acceuil  : %d vistieurs ", m_capaciteChemin);

            al_draw_textf(font, al_map_rgb(255, 255, 255), 940,940,
                          ALLEGRO_ALIGN_CENTER, "  Distance cable de communication  : %d m ", m_DistanceCable);
            for (int i = 0; i != m_arete.size(); i++)
            {
                switch(m_arete[i]->GetmType())
                {
                    case 0:
                        al_draw_line(m_sommets[m_arete[i]->Getm_D()]->GetX(),m_sommets[m_arete[i]->Getm_D()]->GetY(),
                                     m_sommets[m_arete[i]->Getm_A()]->GetX(),m_sommets[m_arete[i]->Getm_A()]->GetY(),
                                     al_map_rgb(255,100,100),15.0);
                        break;
                    case 1:
                        al_draw_line(m_sommets[m_arete[i]->Getm_D()]->GetX(),m_sommets[m_arete[i]->Getm_D()]->GetY(),
                                     m_sommets[m_arete[i]->Getm_A()]->GetX(),m_sommets[m_arete[i]->Getm_A()]->GetY(),
                                     al_map_rgb(100,255,100),15.0);
                        break;
                    case 2:
                        al_draw_line(m_sommets[m_arete[i]->Getm_D()]->GetX(),m_sommets[m_arete[i]->Getm_D()]->GetY(),
                                     m_sommets[m_arete[i]->Getm_A()]->GetX(),m_sommets[m_arete[i]->Getm_A()]->GetY(),
                                     al_map_rgb(0,0,255),15.0);
                        break;
                }
            }

            ///Kruskal
            for(int i=0; i != m_KruskalCapacite.size(); i++)
            {
                al_draw_line((m_sommets[m_KruskalCapacite[i]->Getm_D()]->GetX()),m_sommets[m_KruskalCapacite[i]->Getm_D()]->GetY(),
                             (m_sommets[m_KruskalCapacite[i]->Getm_A()]->GetX()),m_sommets[m_KruskalCapacite[i]->Getm_A()]->GetY(),
                             al_map_rgb(255,255,255),10.0);
            }

            for(int i=0; i != m_KruskalDistance.size(); i++)
            {
                al_draw_line((m_sommets[m_KruskalDistance[i]->Getm_D()]->GetX()),m_sommets[m_KruskalDistance[i]->Getm_D()]->GetY(),
                             (m_sommets[m_KruskalDistance[i]->Getm_A()]->GetX()),m_sommets[m_KruskalDistance[i]->Getm_A()]->GetY(),
                             al_map_rgb(0,0,0),5.0);
            }
            ///Dijkstra
            if(s1 != 0)
            {
                al_draw_textf(font, al_map_rgb(255, 255, 255), 1500, 200,
                              ALLEGRO_ALIGN_CENTER, "Vous etes sur l'animation %d", s0);
                for (int i = 1; i != m_Dijkstra.size(); i++)
                {
                    al_draw_textf(font, al_map_rgb(255, 255, 255), 1500,200+i*30 ,
                                  ALLEGRO_ALIGN_CENTER, " - Vous etes a %dm de l'animation %d", m_Dijkstra[i],i);
                }
            }

            ///Sommets
            for (int i = 1; i != m_sommets.size(); i++)
            {
                switch(m_sommets[i]->GetType())
                {
                    case 1 :
                        al_draw_filled_circle(m_sommets[i]->GetX(),m_sommets[i]->GetY(),10,al_map_rgb(255,0,0));
                        al_draw_textf(font3, al_map_rgb(255, 255, 255), 1500, 600+i*30,
                                      ALLEGRO_ALIGN_CENTER, "%s", m_sommets[i]->GetName().c_str());
                        break;
                    case 2 :
                        al_draw_filled_circle(m_sommets[i]->GetX(),m_sommets[i]->GetY(),10,al_map_rgb(0,0,0));
                        break;
                    default:
                        break;
                }
                al_draw_textf(font3, al_map_rgb(0, 0, 0), m_sommets[i]->GetX()-50,m_sommets[i]->GetY() ,
                              ALLEGRO_ALIGN_CENTER, "%s", m_sommets[i]->GetName().c_str());
            }
        }
        al_flip_display();
        al_wait_for_event(Queue,&event);
        al_wait_for_event(queue,&Event);
        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            isEnd=TRUE;
        }
    }
    al_destroy_display(display);
    al_destroy_event_queue(Queue);
    al_destroy_event_queue(queue);
    al_destroy_bitmap(map);
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


void Graphe::DFS(int numero_S0,int &chaine) const {

    static int date = 0;
    static std::vector<int > couleurs((int) m_sommets.size(), 0);
    static std::stack<const Sommet*> pile;
    static std::vector<int> cc;
    pile.push(m_sommets[numero_S0]); // est le sommet s
    couleurs[numero_S0]=1;
    std::cout<<m_sommets[numero_S0]->GetName()<<std::endl;
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

std::vector<int> Graphe::dijkstra(int s0) {
    std::cout << std::endl << std::endl << "LANCEMENT DE DIJKSTRA :" << std::endl;
    // INITIALISATION
    int nbMarques = 0;
    std::vector<int> couleurs(m_sommets.size(), 0); // tous les sommets sont non marqués
    std::vector<int> distances(m_sommets.size(),std::numeric_limits<int>::max());                // tous les sommets sont supposés à une distance infinie de s0;
    distances[s0] = 0; // s0 est à une distance de 0 de lui même.
    std::vector<int> predecesseurs(m_sommets.size(), -1); // nous ne connaissons pas encore les prédécesseurs
    predecesseurs[s0] = 0; // on pourrait laisser -1, s0 n'a pas vraiment de prédécesseur car il s'agit du sommet initial

    do {
        int s = 0;
        int distanceMini = std::numeric_limits<int>::max();
        std::cout << std::endl << std::endl;
        for (size_t i = 1; i < distances.size(); i++) {
            std::cout << couleurs[i] << " "
                      << ((distances[i] == std::numeric_limits<int>::max()) ? "Inf" : std::to_string(
                              distances[i])) << " "
                      << (predecesseurs[i] == -1 ? "?" : std::to_string(
                              predecesseurs[i])) << "    ";
            if (couleurs[i] == 0 && distances[i] < distanceMini) {
                distanceMini = distances[i];
                s = i;
            }
        }
        std::cout << std::endl << std::endl;

        couleurs[s] = 1;
        nbMarques++;
        std::cout << "Sommet choisi : " << s << " (plus petite distance depuis le sommet " << s0 << " (" << distanceMini
                  << ")"
                  << "). Ses successeurs non marqués sont :" << std::endl;
        for (auto successeur: m_sommets[s]->getSuccesseurs()) {
            if (couleurs[successeur.first->getId()] == 0) {
                std::cout << "    - " << successeur.first->getId() << " : "
                          << "Si considéré, la distance deviendrait " << distances[s] << " + "
                          << successeur.second << " = " << distances[s] + successeur.second
                          << ". Ce qui est "
                          << ((distances[s] + successeur.second < distances[successeur.first->getId()]) ? "inférieur"
                                                                                                        : "supérieur")
                          << " à sa distance actuelle de "
                          << distances[successeur.first->getId()] << ". Donc : "
                          << ((distances[s] + successeur.second < distances[successeur.first->getId()]) ? "MAJ"
                                                                                                        : "NON MAJ")
                          << std::endl;
                if (distances[s] + successeur.second < distances[successeur.first->getId()]) {
                    distances[successeur.first->getId()] = distances[s] + successeur.second;
                    predecesseurs[successeur.first->getId()] = s;
                }
            }
        }
    } while (nbMarques < m_sommets.size());

    std::cout << std::endl << "FIN DE DIJKSTRA." << std::endl;
    for(int i=1; i!= predecesseurs.size();i++)
    {
        std::cout<<"vous etes a "<< distances[i]<<"m"<< " de l'animation "<<i<<std::endl;


    }


    m_Dijkstra = distances;
    return predecesseurs;


}

void Graphe::ford_fulkerson() const {
    std::vector<const Aretes*>MST;
    const Aretes* Arr;
    int D,A;
    int flot = 0;
    int flotTot = 0;

    for(int i=0; i!=m_arete.size();i++)
    {
        Arr=m_arete[i];
        int flot2 = 0;
        int flotTot2 = 0;
        int augmentable = 0;///pour savoir si un chemain est augmentant on pourrait essayer de stocker la possibilite d'augmentation dans un tableau et ensuite retourner la plus petite valeur pour laquelle on a pas de flot qui sature
        std::string name;

        name = Arr->GetName();
        flot += Arr->getFlot();
        flotTot += Arr->getFlotMax();

        flot2 = Arr->getFlot();
        flotTot2 = Arr->getFlotMax();

        if(flot2 >= flotTot2){
            std::cout<< name << "est sature" << std::endl;
        }
        if(flot2 < flotTot2){
            augmentable = flotTot2 - flot2;
            std::cout<< name << " est augmentable de : " << augmentable << std::endl;
        }
    }
    std::cout << "dans la zone, le nombre de personnes total pouvant se deplacer sur les routes, avenues ponts ou metro est de :" << flotTot << "personnes" << std::endl;
    std::cout << "le nombre de personnes totale circulant est de :" << flot << std::endl;
}
void Graphe::bloquerArr(){
    int numArrB;
    std::cout << "quelle rue voulez vous bloquer : ";
    std::cin>>numArrB;
    m_arete[numArrB]->changeFlot(0,0);
    std::cout << "l'arete numero : "<< numArrB<< " est desormais bloquee"<< std::endl << std::endl<<std::endl;
}
void Graphe::changerFlotArr() {
    int change;
    int numArr;
    int nouvelleValeur;
    int fin = 0;
    while(fin != 1){
        std::cout << "voulez-vous changer :"<<std::endl<<
                      "1) le flot"<<std::endl<<
                      "2) le flot total" << std::endl;
        std::cin >> change;
        std::cout << std::endl;
        if(change == 1 || change == 2){
            fin = 1;
        }
        else{
            std::cout << "veuillez recommencer : " << std::endl;
        }
    }

    std::cout << "donner le numero de l'arete en question : ";
    std::cin >> numArr;
    while (numArr > m_arete.size()){
        std::cout<< "veuillez saisir une arete valide"<< std::endl;
        std::cin >> numArr;
    }
    std::cout << std::endl;
    std::cout << "entrer la nouvelle valeur a definir" << std::endl;
    std::cin >> nouvelleValeur;
    m_arete[numArr]->changeFlot(change,nouvelleValeur);   ///modifie la valeur du flot total ou du flot actuel en evitant les erreurs

}

void Graphe::changerNbPersMcarreSommet() {
    int change;++
    int numSom;
    int nouvelleValeur;
    int fin = 0;
    while(fin != 1){
        std::cout << "voulez-vous changer : "<<std::endl<<
                     "1) le nombre de personnes presentes au metre carre"<<std::endl<<
                     "2) la limite de personnes au metre carre" << std::endl;
        std::cin >> change;
        std::cout << std::endl;
        if(change == 1 || change == 2){
            fin = 1;
        }
        else{
            std::cout << "veuillez recommencer : " << std::endl;
        }
    }

    std::cout << "donner le numero du sommet en question :";
    std::cin >> numSom;
    while (numSom > m_sommets.size()-1){
        std::cout << "veuillez saisir un sommet valide : "<< std::endl;
        std::cin >> numSom;
    }

    std::cout << std::endl;
    std::cout << "entrer la nouvelle valeur a definir :" << std::endl;
    std::cin >> nouvelleValeur;
    m_sommets[numSom]->changeNbPersMcarre(change,nouvelleValeur);   ///modifie la valeur du nombre de personnes au metre carre(actuel ou total) en evitant les erreurs

}

void Graphe::kruskalKm() {

    int total=0;
    std::sort(m_arete.begin(), m_arete.end(), [](Aretes* a1, Aretes* a2) { return a1->Getdistance() < a2->Getdistance(); });
    std::vector<int> numCC; /// va nous servir a noter les numero de composantes connexes pour ensuite eviter les cycles
    for(int i=0;i<m_sommets.size();++i){
        numCC.push_back(i);
    }
    std::vector<const Aretes*> arbre;
    int nbre_Arete=0; ///on defini une variable dans laquelle stocker le nombre d'aretes qu'on insere
    int n=0; /// on definie une variable qu'on utilisera comme numero d'arete pour parcourir le vector d'aretes

    while(nbre_Arete<(m_sommets.size()-2)){
        if(numCC[m_sommets[m_arete[n]->Getm_D()]->getNumero()]!= numCC[m_sommets[m_arete[n]->Getm_A()]->getNumero()]){  ///on verifie que l'arete ne cree pas de cycle
            arbre.push_back(m_arete[n]);  /// on l'insere dans le vector d'arete qu'on retournera a la fin
            total += m_arete[n]->Getdistance(); /// on ajoute a chaque fois le kilometrage de l'arete en question
            int x=numCC[m_sommets[m_arete[n]->Getm_A()]->getNumero()];/// on met a jour les numeros de composante connexe
            for(int i=0;i<numCC.size();++i)
            {
                if(numCC[i]==x)
                {
                    numCC[i]=numCC[m_sommets[m_arete[n]->Getm_D()]->getNumero()];
                }
            }
            nbre_Arete++;
        }
        n++;
    }
    for(int i=0; i!=arbre.size();i++)
    {
        std::cout<<arbre[i]->Getm_D()<<" - "<<arbre[i]->Getm_A();
        std::cout<<std::endl;

    }
    std::cout<<"le distance totale des cables de communication est de " << total << "  m" << std::endl;
    m_KruskalDistance=arbre;
    m_DistanceCable=total;
}