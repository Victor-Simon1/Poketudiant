#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "gui.h"
#include "game.h"
#include "partie.h"
#include "serveur.h"
#include "client.h"
#include "menu.h"

int refreshGame(){

    int nbGame = 0, i=0, cpt = 0, cpt2 = 0;;
    char subtext[500], subtext2[500];
    char *sep = "\n", *p, *pReceive;
    ssize_t n = 0;

    // detruit la liste de texte
    listeTexte = destroyTextes(listeTexte);
    destroyParties(listeServeur->listePartie);

    // demande la liste des games
    strcpy(clientTCP->buffer_send, "require game list\n");
    clientTCP->buffer_send[18] = '\0';
    clientTCP->client_send(clientTCP, clientTCP->buffer_send);
    printf("========== send : %s\n", clientTCP->buffer_send);

    // recoit le nb de games
    n = clientTCP->client_receive(clientTCP, clientTCP->buffer_recv, SIZE);
    clientTCP->buffer_recv[n]='\0';
    printf("========== receive : %s\n", clientTCP->buffer_recv);

    p = strtok(clientTCP->buffer_recv, sep);

    if(strncmp(p,"number of games",15) == 0){
        strncpy(subtext,&(clientTCP->buffer_recv[16]),1);
        nbGame = atoi(subtext);
        SDL_Log("il y a %d game(s)", nbGame);
    }
    
    p = strtok(clientTCP->buffer_recv, sep);
    // liste des games
    if(nbGame > 0){  
        
        if(!p){ // si plusieur msg
            n = clientTCP->client_receive(clientTCP, clientTCP->buffer_recv, SIZE);
            clientTCP->buffer_recv[n]='\0';
            printf("========== receive : %s\n", clientTCP->buffer_recv);
            p = strtok(clientTCP->buffer_recv, sep);
        }
    
        for(i = 0; i<nbGame; i++){
            cpt = 0;
            while(p[cpt] != ' ' ){
                cpt++;
            }
            strncpy(subtext,&p[0],cpt);
            printf("il y a %d joueurs \n", atoi(subtext));

            cpt++;
            cpt2 = 0;
            while(p[cpt] != ' ' && p[cpt] != '\n'){
                subtext2[cpt2] = p[cpt];
                cpt++;
                cpt2++;
            }
            subtext2[cpt2] = '\0';
            printf("dans la partie %s\nici", subtext2);
  
            listeServeur->listePartie = ajouterTetePartie(listeServeur->listePartie, createPartie(subtext2)); // ajoute la partie au serveur
            listeTexte = ajouterTeteTexte(listeTexte, createTexte(clientTCP->buffer_recv, 50, 200)); // ajoute le texte affiché a l'ecran
            p = strtok(NULL, sep);
        }
    }

    strcpy(clientTCP->buffer_recv, "");

    if(p)
        strcpy(clientTCP->buffer_recv, p);

    
    nbPartie = nbGame;
    return 1;
}

// crée une nouvelle partie et informe le serveur
int newPartie(char text[50]){
    char nom[50], *p, *sep = "\n";

    printf("donnez un nom de partie :\n");
    scanf("%s", nom);
    printf("Name : %s\n",nom);
    
    //envoie au serveur 
    strcpy(clientTCP->buffer_send, "create game ");
    strcat(clientTCP->buffer_send, nom);
    strcat(clientTCP->buffer_send, "\n");
    clientTCP->client_send(clientTCP, clientTCP->buffer_send);
    printf("=========== send : %s\n",clientTCP->buffer_send);

    // recoit la confirmation
    ssize_t n = clientTCP->client_receive(clientTCP, clientTCP->buffer_recv, SIZE);
    clientTCP->buffer_recv[n]='\0';
    printf("========== receive : %s\n", clientTCP->buffer_recv);
    
    char tempBuffer[SIZE];
    strcpy(tempBuffer, clientTCP->buffer_recv);
    p = strtok(clientTCP->buffer_recv, sep);

    if(strncmp(clientTCP->buffer_recv,"game created",12) == 0){
        printf("game crée\n");
        changeAffichage("GAME");
    }
    else{
        printf("game non crée\n");
    }
    destroyParties(listeServeur->listePartie);
    listeServeur->listePartie = ajouterTetePartie(listeServeur->listePartie, createPartie(nom)); // ajoute la partie au serveur
    //maPartie = createPartie(nom);
    listeTexte = ajouterTeteTexte(listeTexte, createTexte(clientTCP->buffer_recv, 50, 200)); // ajoute le texte affiché a l'ecran
    
    int nb = strlen(p);
    int nbBuf = strlen(tempBuffer);
    //printf("buffffffffff : %s\n", tempBuffer);
    strcpy(clientTCP->buffer_recv, " ");
    p = strtok(NULL, sep);

    if(p){
        strncpy(clientTCP->buffer_recv, &tempBuffer[nb+1], nbBuf-nb);      
        //printf("char : %c\n", clientTCP->buffer_recv[nb]);
        //printf("nb : %d\n", nbBuf);
    }


        
//printf("buffffffffff : %s\n", clientTCP->buffer_recv);

    return 1;
}

// rejoins une partie et informe le serveur
int joinPartie(char text[50]){
    Parties temp = listeServeur->listePartie;
    int cpt = 0;
    char *pnom;

    while(temp){
        if(cpt == choix){
            strcpy(pnom, temp->nom);
            break;
        }
        cpt++;
        temp = temp->suiv;
    }

    destroyParties(listeServeur->listePartie);
    listeServeur->listePartie = ajouterTetePartie(listeServeur->listePartie, createPartie(pnom));

    //envoie au serveur 
    strcpy(clientTCP->buffer_send, "join game ");
    strcat(clientTCP->buffer_send, pnom);
    strcat(clientTCP->buffer_send, "\n");
    clientTCP->client_send(clientTCP, clientTCP->buffer_send);
    printf("=========== send : %s\n",clientTCP->buffer_send);

    return 1;
}

Parties createPartie(char name[50]){
    int i=0, j=0;
    Parties game = (Partie*)malloc(sizeof(Partie));

    strcpy(game->nom, name);
    game->nbJoueur = 0;
    game->maxJoueur = 0;
    game->nbLigne = 0;
    game->nbColonne = 0;
    game->suiv = NULL;

    for(i=0; i<150; i++){
        for(j=0; j<150; j++){
            game->map[i][j] = ' ';
        }
    }
    return game;
}

Parties ajouterTetePartie(Parties liste, Parties p){  // ajoute un texte a une liste de texte

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
        temp = suivant;
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
    Buttons ButtonRefresh = creerBouton("src/gfx/boutonRefresh.png", "src/gfx/boutonRefreshHover.png", "src/gfx/boutonRefreshHover.png", 
                                                                                                game.ecran.camera.w/3, 
                                                                                                100, 
                                                                                                300, 50, 
                                                                                                &refreshGame,
                                                                                                "");
    
    ButtonRefresh->box.x -= ButtonRefresh->box.w/2;
    ButtonRefresh->box.y -= ButtonRefresh->box.h/2;
    
    groupePartie->listeButtons = ajouter_teteButton(groupePartie->listeButtons , ButtonRefresh);// ajoute le bouton refresh au groupe
    
    // bouton cree
    Buttons ButtonCreate = creerBouton("src/gfx/boutonCreate.png", "src/gfx/boutonCreateHover.png", "src/gfx/boutonCreateHover.png", 
                                                                                                game.ecran.camera.w/4, 
                                                                                                game.ecran.camera.h -100, 
                                                                                                300, 50, 
                                                                                                &newPartie,
                                                                                                "");
    
    ButtonCreate->box.x -= ButtonCreate->box.w/2;
    ButtonCreate->box.y -= ButtonCreate->box.h/2;
    
    groupePartie->listeButtons = ajouter_teteButton(groupePartie->listeButtons , ButtonCreate);// ajoute le bouton serveur au groupe

    // bouton join
    Buttons ButtonJoin = creerBouton("src/gfx/boutonConnect.png", "src/gfx/boutonConnectHover.png", "src/gfx/boutonConnectHover.png", 
                                                                                                game.ecran.camera.w/4 +350, 
                                                                                                game.ecran.camera.h -100, 
                                                                                                300, 50, 
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

    SDL_Rect Rect = {0, 0, game.ecran.camera.w, game.ecran.camera.h};// fond
    SDL_RenderCopy(game.ecran.renderer,menuImg,NULL,&Rect);

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
    SDL_DestroyTexture(textPartie);
    textPartie = NULL;

    //destroyParties(maPartie);
    
}