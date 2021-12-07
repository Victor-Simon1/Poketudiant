
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "gui.h"
#include "game.h"
#include "menu.h"
#include "fonctions.h"
#include "serveur.h"
#include "client.h"


/*

    ================================================ GESTION DES ECRANS DE SELECTION DE SERVEURS/PARTIES ================================================

*/


// fait un appel broadcast pour rafraichir la liste des serveurs disponible
int refresh(char texte[20]){

    SDL_Log("refresh");

/*
    Client clt = client_create_udp("", 9000); 
    strcpy(clt->buffer_send, "looking for poketudiant servers");

    ssize_t n = 0;
    int ret;
    char hostbuffer[SIZE];
    memset(hostbuffer, 0, sizeof(char) * SIZE);
    struct hostent *host;
    struct in_addr **adr;
    fd_set rdfs;
    FD_ZERO(&rdfs);
    FD_SET(clt->socket, &rdfs);

    if((ret = select((clt->socket + 1, &readfs, NULL, NULL, NULL)) < 0){ // attente de réponse des serveurs
        perror("select()");
        exit(errno);
    }
    
    if(ret == 0){// temps écoulé
        SDL_Log("temps écoulé");
    }    
   
   if(FD_ISSET((clt->socket, readfs)){// données recu
        n = clt->client_receive(clt, clt->buffer_recv, SIZE-1);
        clt->buffer_recv[n] = '\0';

        if(n == 0)
            SDL_Log("serveur down");
        else{
            if(strncmp(clt->buffer_recv,"i'm a poketudiant server",24) == 0){
                if(gethostname(hostbuffer, sizeof(hostbuffer)) == -1){ //récupère le nom du seveur
                    perror("gethostname");
                    exit(EXIT_FAILURE);
                }
            }
            if ((host = gethostbyname(hostbuffer)) != NULL){
                for (adr = (struct in_addr **)host->h_addr_list; *adr; adr++)
                    printf("IP : %s\n", inet_ntoa(**adr)); 
                    nbServeur++;               
            }

        }


        printf("-----------receive : %s\n", buffer_recv);
   }


   client_close_and_free(clt);







*/
    nbServeur = 0;

    // reset la liste des serveurs
    destroyServeurs(listeServeur);
    listeServeur = createServeur("172.31.129.186");
    listeServeur = createServeur("172.31.129.187");

    listeTexte = destroyTextes(listeTexte);
    listeTexte = ajouterTeteTexte(listeTexte, createTexte("172.31.129.186", 50, 200));
    listeTexte = ajouterTeteTexte(listeTexte, createTexte("172.31.129.187", 50, 250));
    nbServeur = 2;
    return 1;
}



// ============================================= TEXTE =============================================
Textes createTexte(char text[50], int p_x, int p_y){// cree un texte
    Textes my_text = (Texte*)malloc(sizeof(Texte));

    my_text->x = p_x;
    my_text->y = p_y;
    my_text->texte = CreateFont(game.ecran.renderer, police, text, game.couleur.rouge);    
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
        temp = temp->suiv;
    }
    return temp;
}

// ============================================= SERVEUR =============================================

// rejoin un serveur
void joinServeur(){  
    Serveurs temp = listeServeur;
    int cpt = 0;
    char ipTemp[30];

    while(temp){
        if(cpt == choix){
            strcpy(ipTemp, temp->ip);  
            break;          
        }
        temp = temp->suiv;
    }

    destroyServeurs(listeServeur);
    
    listeServeur = createServeur(ipTemp);
 
    choix = 0;
    changeAffichage("PARTIE");

    
    
    refreshGame();

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

Serveurs ajouterTeteTexte(Serveurs liste, Serveurs s){  // ajoute un serveur à une liste de serveur

    s->suiv = liste;
    liste = s;

    return s;
}

// libère l'espace mémoire d'une liste de parties
void destroyServeurs(Serveurs s){
    Serveurs temp = s, suivant = NULL;

    while(temp){
        suivant = temp->suiv;
        destroyParties(temp->listePartie);
        free(temp);
        temp = temp->suiv;
    }
}


int loadServeur(){

    listeServeur = NULL;
    choix = 0;


    // ============================== GUI ==============================
    groupeServeur = creerGroupe();
    groupeServeur->actif = false;
    
    // bouton refresh
    Buttons ButtonRefresh = creerBouton("src/gfx/button_default.png", "src/gfx/button_pressed.png", "src/gfx/button_hover.png", 
                                                                                                game.ecran.camera.w/2 , 
                                                                                                game.ecran.camera.h/2 , 
                                                                                                150, 50, 
                                                                                                &refresh,
                                                                                                "SERVEUR");
    
   ButtonRefresh->box.x -= ButtonRefresh->box.w/2;
   ButtonRefresh->box.y -= ButtonRefresh->box.h/2;
    
    groupeServeur->listeButtons = ajouter_teteButton(groupeServeur->listeButtons , ButtonRefresh);// ajoute le bouton refresh au groupe
    
    // bouton menu
    Buttons ButtonMenu = creerBouton("src/gfx/button_default.png", "src/gfx/button_pressed.png", "src/gfx/button_hover.png", 
                                                                                                game.ecran.camera.w/2 , 
                                                                                                game.ecran.camera.h/2 +100, 
                                                                                                150, 50, 
                                                                                                &changeAffichage,
                                                                                                "MENU");
    
    ButtonMenu->box.x -= ButtonMenu->box.w/2;
    ButtonMenu->box.y -= ButtonMenu->box.h/2;
    
    groupeServeur->listeButtons = ajouter_teteButton(groupeServeur->listeButtons , ButtonMenu);// ajoute le bouton serveur au groupe

    // bouton join
    Buttons ButtonJoin = creerBouton("src/gfx/button_default.png", "src/gfx/button_pressed.png", "src/gfx/button_hover.png", 
                                                                                                game.ecran.camera.w/2 , 
                                                                                                game.ecran.camera.h/2 , 
                                                                                                350, 50, 
                                                                                                &joinServeur,
                                                                                                "");
    
    ButtonJoin->box.x -= ButtonJoin->box.w/2;
    ButtonJoin->box.y -= ButtonJoin->box.h/2;
    
    groupeServeur->listeButtons = ajouter_teteButton(groupeServeur->listeButtons , ButtonJoin);// ajoute le bouton join au groupe


    listeGroupes = ajouter_teteGroupes(listeGroupes, groupeServeur);// ajout le groupe serveur


    return 1;
}

int updateServeur(){

    // =========================== Gestion des events (clavier) ===============================

    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_UP]){ // HAUT
       if(choix > 0){
           choix--;
       }
       else{
           choix = nbServeur;
       }
    }
    if (state[SDL_SCANCODE_DOWN]){ // BAS
        if(choix < nbServeur-1){
            choix++;
        }
        else{
            choix = 0;
        }
    }

    updateGui();

    return 1;   
}

int drawServeur(){

    SDL_RenderClear(game.ecran.renderer); // Efface l'écran 

    SDL_Rect rect2 = {game.ecran.camera.w/2 - 75, 2, 150, 20};//titre
    SDL_RenderCopy(game.ecran.renderer, textTitre, NULL, &rect2); 

    // liste des serveurs
    Textes temp = listeTexte;
    int cpt = 0;
    while(temp){
        if(cpt == choix){
            SDL_Rect Rect = {temp->x-50, temp->y-10, 94, 171}; // fleche
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