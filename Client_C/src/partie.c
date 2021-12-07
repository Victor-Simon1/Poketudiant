#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "gui.h"
#include "game.h"
#include "partie.h"
#include "serveur.h"
#include "client.h"


void refreshGame(){

    int nbGame = 0, i=0, cpt = 0;
    char subtext[500];
    char *sep = "\n", *p;
    ssize_t n = 0;

    // detruit la liste de texte
    listeTexte = destroyTextes(listeTexte);

    // demande la lite des games
    strcpy(clientTCP->buffer_send, "require game list\n");
    clientTCP->client_send(clientTCP, clientTCP->buffer_send);
    printf("========== send : %s\n", clientTCP->buffer_send);

    // recois le nb de games
    n = clientTCP->client_receive(clientTCP, clientTCP->buffer_recv, SIZE);
    clientTCP->buffer_recv[n]='\0';
    printf("========== receive : %s\n", clientTCP->buffer_recv);

    if(strncmp(clientTCP->buffer_recv,"number of games",15) == 0){
        strncpy(subtext,&(clientTCP->buffer_recv[16]),1);
        nbGame = atoi(subtext);
        printf("il y a %d game(s)", nbGame);
    }

    // liste des games
    if(nbGame > 0){
        n = clientTCP->client_receive(clientTCP, clientTCP->buffer_recv, SIZE);
        clientTCP->buffer_recv[n]='\0';
        printf("========== receive : %s\n", clientTCP->buffer_recv);
        p = strtok(clientTCP->buffer_recv, sep);
        for(i = 0; i<nbGame; i++){
            cpt = 0;
            while(p[cpt] != ' ' ){
                cpt++;
            }
            strncpy(subtext,&p[0],cpt);
            printf("il y a %d joueurs ", atoi(subtext));
            strncpy(subtext,&p[cpt+1], (sizeof(p)/sizeof(char))-cpt-1);
            //("nb %d", sizeof(p)/sizeof(char));
            printf("dans la partie %s\nici", subtext);
            printf("for");
            if(i < nbGame-1){
                printf("ici");
                p = strtok(NULL, sep);
            }
        }
        listeTexte = ajouterTeteTexte(listeTexte, createTexte(clientTCP->buffer_recv, 50, 200));
    }
    
}

// crée une nouvelle partie et informe le serveur
void newPartie(char text[50]){
    char nom[50];

    printf("donnez un nom de partie :\n");
    scanf("%s", nom);

    //envoie au serveur 


}

// rejoins une partie et informe le serveur
void joinPartie(char[50]){

}

Parties createPartie(){

    Parties game = (Partie*)malloc(sizeof(Partie));

    strcpy(game->nom, "game_name");
    game->nbJoueur = 0;
    game->maxJoueur = 0;
    game->nbLigne = 0;
    game->nbColonne = 0;
    game->suiv = NULL;

    return game;
}

Parties ajouterTeteTexte(Parties liste, Parties p){  // ajoute un texte a une liste de texte

    p->suiv = liste;
    liste = p;

    return p;
}

// libère l'espace mémoire d'une liste de parties
void destroyParties(Parties p){
    Parties temp = p, suivant = NULL;

    while(temp){
        suivant = temp->suiv;
        free(temp);
        temp = temp->suiv;
    }
}


int loadPartie(){

    choix = 0;

    // Titre
    textPartie = CreateFont(game.ecran.renderer, policeTitre, "Partie(s)", game.couleur.jaune);   

    // ============================== GUI ==============================
    groupePartie = creerGroupe();
    groupePartie->actif = false;
    
    // bouton refresh
    Buttons ButtonRefresh = creerBouton("src/gfx/button_default.png", "src/gfx/button_pressed.png", "src/gfx/button_hover.png", 
                                                                                                game.ecran.camera.w/2 , 
                                                                                                game.ecran.camera.h/2 , 
                                                                                                150, 50, 
                                                                                                &refreshGame,
                                                                                                "");
    
    ButtonRefresh->box.x -= ButtonRefresh->box.w/2;
    ButtonRefresh->box.y -= ButtonRefresh->box.h/2;
    
    groupePartie->listeButtons = ajouter_teteButton(groupePartie->listeButtons , ButtonRefresh);// ajoute le bouton refresh au groupe
    
    // bouton menu
    Buttons ButtonCreate = creerBouton("src/gfx/button_default.png", "src/gfx/button_pressed.png", "src/gfx/button_hover.png", 
                                                                                                game.ecran.camera.w/2 , 
                                                                                                game.ecran.camera.h/2 +100, 
                                                                                                150, 50, 
                                                                                                &newPartie,
                                                                                                "");
    
    ButtonCreate->box.x -= ButtonCreate->box.w/2;
    ButtonCreate->box.y -= ButtonCreate->box.h/2;
    
    groupePartie->listeButtons = ajouter_teteButton(groupePartie->listeButtons , ButtonCreate);// ajoute le bouton serveur au groupe

    // bouton join
    Buttons ButtonJoin = creerBouton("src/gfx/button_default.png", "src/gfx/button_pressed.png", "src/gfx/button_hover.png", 
                                                                                                game.ecran.camera.w/2 , 
                                                                                                game.ecran.camera.h/2 , 
                                                                                                350, 50, 
                                                                                                &joinPartie,
                                                                                                "");
    
    ButtonJoin->box.x -= ButtonJoin->box.w/2;
    ButtonJoin->box.y -= ButtonJoin->box.h/2;
    
    groupePartie->listeButtons = ajouter_teteButton(groupePartie->listeButtons , ButtonJoin);// ajoute le bouton join au groupe


    listeGroupes = ajouter_teteGroupes(listeGroupes, groupePartie);// ajout le groupe serveur


    return 1;
}

int updatePartie(){

    // =========================== Gestion des events (clavier) ===============================

    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_UP]){ // HAUT
       if(choix > 0){
           choix--;
       }
       else{
           choix = nbPartie;
       }
    }
    if (state[SDL_SCANCODE_DOWN]){ // BAS
        if(choix < nbPartie-1){
            choix++;
        }
        else{
            choix = 0;
        }
    }

    updateGui();

    return 1;   
}

int drawPartie(){

    SDL_RenderClear(game.ecran.renderer); // Efface l'écran 

    SDL_Rect rect2 = {game.ecran.camera.w/2 - 75, 2, 150, 20}; // titre
    SDL_RenderCopy(game.ecran.renderer, textPartie, NULL, &rect2); 

    // liste des parties
    Textes temp = listeTexte;
    int cpt = 0;
    while(temp){
        if(cpt == choix){
            SDL_Rect Rect = {temp->x-50, temp->y-10, 94, 171}; // fleche
            SDL_RenderCopy(game.ecran.renderer, imgFleche, NULL, &Rect);
        }
                
        SDL_Rect rect3 = {temp->x, temp->y, 150, 20}; // nom de la partie
        SDL_RenderCopy(game.ecran.renderer, temp->texte, NULL, &rect3);
        temp = temp->suiv;
        cpt++;
    }
    
    drawGui();

    SDL_RenderPresent(game.ecran.renderer); // Présente l'écran
    return 1;   
}

void liberePartie(){
    destroyTextes(textPartie);
    textPartie = NULL;
}