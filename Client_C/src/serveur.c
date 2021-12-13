
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/select.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <unistd.h>

#include "gui.h"
#include "game.h"
#include "menu.h"
#include "fonctions.h"
#include "serveur.h"
#include "client.h"
#include "partie.h"

/*

    ================================================ GESTION DES ECRANS DE SELECTION DE SERVEURS/PARTIES ================================================

*/

/*
int refresh(char texte[50]){

    SDL_Log("refresh ...");
    
    // reset
    nbServeur = 0;
    destroyServeurs(listeServeur);
    listeTexte = destroyTextes(listeTexte);

    struct timeval time;
    time.tv_sec = 5;
    time.tv_usec = 0;
    ssize_t n = 0;
    int ret;

    // envoie
    Client clt = client_create_udp("", 9000); 
    strcpy(clt->buffer_send, "looking for poketudiant servers");
    clt->client_send(clt, clt->buffer_send);
    SDL_Log("=========== send : %s \n", clt->buffer_send);

    fd_set rdfs;
    FD_ZERO(&rdfs);
    FD_SET(clt->socket, &rdfs);
    
    // reception
    if((ret = select(clt->socket + 1, &rdfs, NULL, NULL, &time)) < 0){ // attente de réponse des serveurs
        perror("select()");
        exit(errno);
    }
    
    if(ret == 0){// temps écoulé
        SDL_Log("temps écoulé");
    }    
    bool stop = false;
    //if(!stop){
        if(FD_ISSET(clt->socket, &rdfs)){// données recu
            SDL_Log("while");
            struct sockaddr_in *saddr;
            n = clt->client_receiveUDP(clt, clt->buffer_recv, SIZE-1, &saddr);
            clt->buffer_recv[n] = '\0';
            printf("-----------receive : %s\n", clt->buffer_recv);
            
            printf("ip : %s\n", inet_ntoa(saddr->sin_addr));
        
        }
        else{
           // stop = true;
        }

}

*/

// fait un appel broadcast pour rafraichir la liste des serveurs disponible
int refresh(char texte[20]){
   
   // SDL_Log("refresh");
    nbServeur = 0;
    

    // reset la liste des serveurs
    //destroyServeurs(listeServeur);
    //listeServeur = createServeur("172.31.129.187");
    //listeServeur = createServeur("172.31.129.188");
    
    listeServeur = ajouterTeteServeur(listeServeur, createServeur("10.0.2.15"));
    listeServeur = ajouterTeteServeur(listeServeur, createServeur("172.31.129.188"));

    listeTexte = destroyTextes(listeTexte);
    listeTexte = ajouterTeteTexte(listeTexte, createTexte("10.0.2.15", 150, 200));

    listeTexte = ajouterTeteTexte(listeTexte, createTexte("172.31.129.188", 150, 250));
    nbServeur = 2;


    return 1;
}


// ============================================= TEXTE =============================================
Textes createTexte(char text[50], int p_x, int p_y){// cree un texte
    Textes my_text = (Texte*)malloc(sizeof(Texte));

    my_text->x = p_x;
    my_text->y = p_y;
    my_text->texte = CreateFont(game.ecran.renderer, police, text, game.couleur.noir);    
    my_text->suiv = NULL;


    return my_text;
}

Textes ajouterTeteTexte(Textes liste, Textes t){  // ajoute un texte a une liste de texte

    t->suiv = liste;
    liste = t;

    return t;
}

Textes destroyTextes(Textes t){
    Textes temp = t, suivant = NULL;

    while(temp){
        suivant = temp->suiv;
        SDL_DestroyTexture(temp->texte);
        free(temp);
        temp = suivant;
    }
    return temp;
}

// ============================================= SERVEUR =============================================

// rejoin un serveur
int joinServeur(char text[50]){  
    Serveurs temp = listeServeur;
    int cpt = 0;
    char ipTemp[30];

    while(temp){
        //SDL_Log("connecté à : %s", temp->ip);
        if(cpt == choix){
            strcpy(ipTemp, temp->ip);  
            break;          
        }
        temp = temp->suiv;
    }

    destroyServeurs(listeServeur);
    listeServeur = createServeur(ipTemp);

    // création du client TCP
    clientTCP = client_create_tcp(ipTemp, 9001);
    // connexion
    if(connect(clientTCP->socket,&clientTCP->clientAddr,clientTCP->len)==-1){
        printf("pas connecté\n");
        //exit(1);
    }
    SDL_Log("connecté à : %s", ipTemp);
    
    // passe à l'ecran des parties
    choix = 0;
    changeAffichage("PARTIE");
    refreshGame();

    return 1;
}

Serveurs createServeur(char _ip[20]){

    Serveurs serv = (Serveur*)malloc(sizeof(Serveur));

    strcpy(serv->ip, _ip);
    serv->nbClient = 0;
    serv->maxClient = 0;
    serv->listePartie = NULL;
    serv->suiv = NULL;

    return serv;
}

Serveurs ajouterTeteServeur(Serveurs liste, Serveurs s){  // ajoute un serveur à une liste de serveur

    s->suiv = liste;
    liste = s;

    return s;
}

// libère l'espace mémoire d'une liste de parties
void destroyServeurs(Serveurs s){
    Serveurs temp = s, suivant = NULL;

    while(temp){
        suivant = temp->suiv;
        //destroyParties(temp->listePartie);
        //temp->listePartie = NULL;
        free(temp);
        temp = suivant;
    }
}


int loadServeur(){

    listeServeur = NULL;
    choix = 0;
   


    // ============================== GUI ==============================
    groupeServeur = creerGroupe();
    groupeServeur->actif = false;
    
    // bouton refresh
    Buttons ButtonRefresh = creerBouton("src/gfx/boutonRefresh.png", "src/gfx/boutonRefreshHover.png", "src/gfx/boutonRefreshHover.png", 
                                                                                                game.ecran.camera.w/3 , 
                                                                                                100 , 
                                                                                                300, 50, 
                                                                                                &refresh,
                                                                                                "");
    
    ButtonRefresh->box.x -= ButtonRefresh->box.w/2;
    ButtonRefresh->box.y -= ButtonRefresh->box.h/2;
    
    groupeServeur->listeButtons = ajouter_teteButton(groupeServeur->listeButtons , ButtonRefresh);// ajoute le bouton refresh au groupe
    
    // bouton menu
    Buttons ButtonMenu = creerBouton("src/gfx/boutonMenu.png", "src/gfx/boutonMenuHover.png", "src/gfx/boutonMenuHover.png", 
                                                                                                game.ecran.camera.w/4 +350, 
                                                                                                game.ecran.camera.h -300, 
                                                                                                300, 50, 
                                                                                                &changeAffichage,
                                                                                                "MENU");
    
    ButtonMenu->box.x -= ButtonMenu->box.w/2;
    ButtonMenu->box.y -= ButtonMenu->box.h/2;
    
    groupeServeur->listeButtons = ajouter_teteButton(groupeServeur->listeButtons , ButtonMenu);// ajoute le bouton serveur au groupe

    // bouton join
    Buttons ButtonJoin = creerBouton("src/gfx/boutonConnect.png", "src/gfx/boutonConnectHover.png", "src/gfx/boutonConnectHover.png", 
                                                                                                game.ecran.camera.w/4, 
                                                                                                game.ecran.camera.h -300, 
                                                                                                300, 50, 
                                                                                                &joinServeur,
                                                                                                "");
    
    ButtonJoin->box.x -= ButtonJoin->box.w/2;
    ButtonJoin->box.y -= ButtonJoin->box.h/2;
    
    groupeServeur->listeButtons = ajouter_teteButton(groupeServeur->listeButtons , ButtonJoin);// ajoute le bouton join au groupe


    listeGroupes = ajouter_teteGroupes(listeGroupes, groupeServeur);// ajout le groupe serveur


    return 1;
}

int updateServeur(){

    updateGui();

    return 1;   
}

int drawServeur(){

    SDL_RenderClear(game.ecran.renderer); // Efface l'écran 

    SDL_Rect Rect = {0, 0, game.ecran.camera.w, game.ecran.camera.h};// fond
    SDL_RenderCopy(game.ecran.renderer,menuImg,NULL,&Rect);

    SDL_Rect rect2 = {game.ecran.camera.w/2 - 150, 2, 300, 40};// titre
    SDL_RenderCopy(game.ecran.renderer, textTitre, NULL, &rect2); 

    // liste des serveurs
    Textes temp = listeTexte;
    int cpt = 0;
    while(temp){
        if(cpt == choix){
            SDL_Rect Rect = {temp->x-50, temp->y-10, 50, 50}; // fleche
            SDL_RenderCopy(game.ecran.renderer, imgFleche, NULL, &Rect);
        }
                
        SDL_Rect rect3 = {temp->x, temp->y, 150, 20}; // ip du serveur
        SDL_RenderCopy(game.ecran.renderer, temp->texte, NULL, &rect3);
        temp = temp->suiv;
        cpt++;
    }
    
    drawGui();

    SDL_RenderPresent(game.ecran.renderer); // Présente l'écran
    return 1;   
}

void libereServeur(){
    destroyServeurs(listeServeur);
    listeServeur = NULL;

    destroyTextes(listeTexte);
    listeTexte = NULL;
}