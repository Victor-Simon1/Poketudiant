
#include <stdio.h>
#include <string.h>

#include <SDL.h>
#include "SDL_mixer.h"
#include "SDL_image.h"

#include "game.h"
#include "gui.h"
#include "serveur.h"
#include "client.h"
#include "player.h"



// recupere et gere les evenements clavier
int eventClavier(){ 

    while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_KEYDOWN:                            
                // ============================= apppuie sur une touche =============================
                    switch(event.key.keysym.sym){
                        case SDLK_UP: 
                            if(choose){
                                if(choix > 0){
                                    choix--;
                                }
                                else{
                                    choix = nbServeur-1;
                                }  
                                choose = false;                                 
                            }

                        break;        
                        case SDLK_DOWN: 
                            if(choose){
                                if(choix < nbServeur-1){
                                    choix++;
                                }
                                else{
                                    choix = 0;
                                }   
                                choose = false;                                                         
                            }

                        break;                             
                    }
                    continue;
                // ============================= clique de la souirs =============================
                case SDL_MOUSEBUTTONDOWN:                            
                    if(event.button.button == SDL_BUTTON_LEFT){

                    }
                break;
                // ============================= relachement de la souris =============================
                case SDL_MOUSEBUTTONUP: 
                    if(event.button.button == SDL_BUTTON_LEFT){

                    }      
                break;
                // ============================= relachement d'une touche =============================
                case SDL_KEYUP:  
                    switch(event.key.keysym.sym){
                        case SDLK_UP:
                            choose = true;
                        break; 
                        case SDLK_DOWN:
                            choose = true;
                        break;
                    }
                    continue;
                // ============================= si on bouge la souris =============================
                case SDL_MOUSEMOTION: 

                break;
                case SDL_QUIT: // si on ferme la fenetre
                    running = false;
                    break;
                default:
                    break;
            }
        


    }
    return 1;
}



int lireNB(char *msg){
    int nb = 0, i=0;
    char* subtext;
    while(msg[i] != ' ' && msg[i] != '\n'){
        i++;
    }
    
    strncpy(subtext,&msg[0],i);
    nb = atoi(subtext);
    
    return nb;
}

char* lireChar(char *msg){
    char* subtext;
    int i=0;

    while(msg[i] != ' ' && msg[i] != '\n'){
        i++;
    }
    
    strncpy(subtext,&msg[0],i);
    return subtext;
}

char** split(char* chaine,const char* delim,int vide){
    
    char** tab=NULL;                    //tableau de chaine, tableau resultat
    char *ptr;                     //pointeur sur une partie de
    int sizeStr;                   //taille de la chaine à recupérer
    int sizeTab=0;                 //taille du tableau de chaine
    char* largestring;             //chaine à traiter
    
    int sizeDelim=strlen(delim);   //taille du delimiteur

    largestring = chaine;          //comme ca on ne modifie pas le pointeur d'origine
                                   //(faut ke je verifie si c bien nécessaire)
    

    while( (ptr=strstr(largestring, delim))!=NULL ){
           sizeStr=ptr-largestring;
     
           //si la chaine trouvé n'est pas vide ou si on accepte les chaine vide                   
           if(vide==1 || sizeStr!=0){
               //on alloue une case en plus au tableau de chaines
               sizeTab++;
               tab= (char**) realloc(tab,sizeof(char*)*sizeTab);
                              
               //on alloue la chaine du tableau
               tab[sizeTab-1]=(char*) malloc( sizeof(char)*(sizeStr+1) );
               strncpy(tab[sizeTab-1],largestring,sizeStr);
               tab[sizeTab-1][sizeStr]='\0';
           }
           
           //on decale le pointeur largestring  pour continuer la boucle apres le premier elément traiter
           ptr=ptr+sizeDelim;
           largestring=ptr;
    }
    
    //si la chaine n'est pas vide, on recupere le dernier "morceau"
    if(strlen(largestring)!=0){
           sizeStr=strlen(largestring);
           sizeTab++;
           tab= (char**) realloc(tab,sizeof(char*)*sizeTab);
           tab[sizeTab-1]=(char*) malloc( sizeof(char)*(sizeStr+1) );
           strncpy(tab[sizeTab-1],largestring,sizeStr);
           tab[sizeTab-1][sizeStr]='\0';
    }
    else if(vide==1){ //si on fini sur un delimiteur et si on accepte les mots vides,on ajoute un mot vide
           sizeTab++;
           tab= (char**) realloc(tab,sizeof(char*)*sizeTab);
           tab[sizeTab-1]=(char*) malloc( sizeof(char)*1 );
           tab[sizeTab-1][0]='\0';
           
    }
    
    //on ajoute une case à null pour finir le tableau
    sizeTab++;
    tab= (char**) realloc(tab,sizeof(char*)*sizeTab);
    tab[sizeTab-1]=NULL;

    return tab;
}

void upLvl(int nb, int gain){
    if(nb == 0)
        player->lvl += nb;
    else if(nb == 1)
        player->team[0]->lvl += nb;
    else
        player->team[1]->lvl += nb;
}

void upXp(int nb, int gain){
    if(nb == 0)
        player->lvl += nb;
    else if(nb == 1)
        player->team[0]->lvl += nb;
    else
        player->team[1]->lvl += nb;
}


void upVariete(int nb, char *var){
    if(nb == 0)
        strcpy(player->variete, var);
    else if(nb == 1)
        strcpy(player->team[0]->variete, var);
    else
        strcpy(player->team[1]->variete, var);
}

/*
  _   _   ____    ____       _      _____   _____  
 | | | | |  _ \  |  _ \     / \    |_   _| | ____| 
 | | | | | |_) | | | | |   / _ \     | |   |  _|   
 | |_| | |  __/  | |_| |  / ___ \    | |   | |___  
  \___/  |_|     |____/  /_/   \_\   |_|   |_____| 
                                                  
*/




int update(){
    
    struct timeval time;
    time.tv_sec = 0;
    time.tv_usec = 1;
    ssize_t n = 0;
    int ret;

    fd_set rdfs;
    FD_ZERO(&rdfs);
    FD_SET(clientTCP->socket, &rdfs);
    
    if(strcmp(clientTCP->buffer_recv, " ") == 0){
        // reception
        if((ret = select(clientTCP->socket + 1, &rdfs, NULL, NULL, &time)) < 0){ // attente de réponse des serveurs
            perror("select()");
            //exit(errno);
        }
        
        if(ret == 0){// temps écoulé
            //SDL_Log("temps écoulé");
        }    

        if(FD_ISSET(clientTCP->socket, &rdfs)){// données recu
            n = clientTCP->client_receive(clientTCP, clientTCP->buffer_recv, SIZE-1);
            clientTCP->buffer_recv[n] = '\0';
            printf("-----------receive : %s\n", clientTCP->buffer_recv);
                        
        }
        else{
            SDL_Log("pas de msg");
        }        
    }

    // =========================== recoit un msg ===========================
    char *sep = "\n", *p, tempChar[150], *line, **tab, **tab2;
    int i=0, j=0, cpt=0;
    bool isMap = false;
    
    //line = strtok(clientTCP->buffer_recv, sep); // recup le 1ere ligne
    
   // while(line){
    for(line = strtok(clientTCP->buffer_recv, sep); line; line = strtok(NULL, sep)){
        strcpy(tempChar, line); // save la ligne
        SDL_Log("==== ligne lu : %s", tempChar);
        //SDL_Log("==== ligne lu2 : %s", line[1]);

        if(i >= listeServeur->listePartie->nbLigne){
            isMap = false;
            //SDL_Log("fin");
        }

        if(isMap){ // on recois un map
            if(strlen(tempChar) == listeServeur->listePartie->nbColonne){
                for(j=0; j<listeServeur->listePartie->nbColonne; j++){ // lecture de la ligne
                    //SDL_Log("ligne : %d, colonne : %d", i, j);
                    //SDL_Log("%c : ", tempChar[j]);
                    listeServeur->listePartie->map[i][j] = tempChar[j];
                }
                i++;                
            }
            else{
                //SDL_Log("PROBLEME");
            }

        }
        else{ // si autre message
            //SDL_Log("autre");
            tab = split(tempChar, " ", 0); // split la ligne

            if(strncmp(tab[0],"map",3) == 0){ // reception de la map
                listeServeur->listePartie->nbLigne = atoi(tab[1]); // ligne
                listeServeur->listePartie->nbColonne = atoi(tab[2]); // nb de colonne
               // SDL_Log("nb ligne : %d", listeServeur->listePartie->nbLigne);
                //SDL_Log("nb colonne : %d", listeServeur->listePartie->nbColonne);       
                isMap = true;
            }
            else if(strncmp(tab[0],"team",4) == 0){// recoit ma liste de poketudiant
                
                player->nbPoke = atoi(tab[2]); // récupère le nombre de poketudiant

                // récupère les poketudiants
                line = strtok(NULL, sep);
                strcpy(tempChar, line); // save la ligne
                int i = 0;
                for(i=0; i<player->nbPoke; i++){
                    //SDL_Log("debut");
                    tab = split(tempChar, " ", 0); // split la ligne
                    Poketudiants temp;
                    if(i == 0)
                        temp = player;
                    else if(i == 1)
                        temp = player->team[0];
                    else
                        temp = player->team[1];

                    temp->variete = tab[0];
                    temp->type = tab[1];
                    temp->lvl = atoi(tab[2]);
                    temp->xp = atoi(tab[3]);
                    temp->xpManquant = atoi(tab[4]);
                    temp->maxVie = atoi(tab[5]);
                    temp->atk = atoi(tab[6]);
                    temp->def = atoi(tab[7]);
                    temp->atk1 = tab[8];
                    temp->atk1Type = tab[19];
                    temp->atk2 = tab[10];
                    temp->atk2Type = tab[11];
                    //SDL_Log("fin");
                    line = strtok(NULL, sep);
                    if(line)
                        strcpy(tempChar, line); // save la ligne
                    //SDL_Log("fin2");
                }


            }
            else  if(strncmp(tab[0],"encounter",9) == 0){

                    if(strncmp(tab[1],"KO",2) == 0){
                        player->enCbt = true; // fin du combat
                        if(strncmp(tab[2],"opponent",8) == 0){
                            SDL_Log("pokétudiant adverse KO");
                        }
                        else{
                            SDL_Log("player KO");
                        }
                    }
                    else if(strncmp(tab[1],"win",3) == 0){
                        SDL_Log("victoire");
                    }
                    else if(strncmp(tab[1],"lose",3) == 0){
                        SDL_Log("défaite");
                    }
                    else if(strncmp(tab[1],"win",3) == 0){

                    }
                    else if(strncmp(tab[1],"catch",5) == 0){
                        if(strncmp(tab[2],"ok",2) == 0){
                            SDL_Log("capture réussit");
                        }
                        else{
                            SDL_Log("échec de la capture");
                        }

                    }    
                    else if(strncmp(tab[1],"escape",6) == 0){
                        if(strncmp(tab[2],"ok",2) == 0){
                            SDL_Log("fuite réussite");
                        }
                        else{
                            SDL_Log("échec de la fuite");
                        }
                    }
                    else if(strncmp(tab[1],"poketudiant",11) == 0){
                        if(strncmp(tab[2],"xp",2) == 0){
                            upXp(atoi(tab[3]), atoi(tab[4]));
                        }
                        else if(strncmp(tab[2],"level",5) == 0){
                            upLvl(atoi(tab[3]), atoi(tab[4]));
                        }
                        else{
                            upVariete(atoi(tab[3]), tab[4]);
                        }
                    }
            }
            else  if(strncmp(tab[0]," ",3) == 0){
                // récupère le nombre de poketudiant
                   // SDL_Log("rien");

                // récupère les poketudiants
        

            }       
        
            free(tab);
            tab = NULL;

        }

        

    }

    //strcpy(clientTCP->buffer_recv, " ");
    // =========================== Gestion des events (clavier) ===============================

    if(player->timer > 0){
        player->timer -= game.fps.delta;
        if(player->timer < 0)
            player->timer = 0;
    }

    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if(player->timer <= 0){
        player->timer = 0.5;

        if (state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W]) // HAUT
        {
            //envoie au serveur 
            strcpy(clientTCP->buffer_send, "map move up\n\0");
            clientTCP->client_send(clientTCP, clientTCP->buffer_send);
            printf("=========== send : %s\n",clientTCP->buffer_send);
        
        }
        if (state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S]) // BAS
        {
            //envoie au serveur 
            strcpy(clientTCP->buffer_send, "map move down\n\0");
            clientTCP->client_send(clientTCP, clientTCP->buffer_send);
            printf("=========== send  : %s\n",clientTCP->buffer_send);       
    
        }
        if (state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_D]) /// DROITE
        {
            //envoie au serveur 
            strcpy(clientTCP->buffer_send, "map move right\n\0");
            clientTCP->client_send(clientTCP, clientTCP->buffer_send);
            printf("=========== send  : %s\n",clientTCP->buffer_send);   
        }
        if (state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_A]) // GAUCHE 
        {
            //envoie au serveur 
            strcpy(clientTCP->buffer_send, "map move left\n\0");
            clientTCP->client_send(clientTCP, clientTCP->buffer_send);
            printf("=========== send  : %s\n",clientTCP->buffer_send);
        }
    }
   
    
    // =========================== gestion de la camera ===========================
  //SDL_Log("x : %d", player->x);
    game.ecran.camera.x = ((player->x*SIZE_TILE)+SIZE_TILE/2) -  game.ecran.camera.w/2;
    game.ecran.camera.y = ((player->y*SIZE_TILE)+SIZE_TILE/2) -  game.ecran.camera.h/2;

    if(game.ecran.camera.x < 0)
        game.ecran.camera.x = 0;
    else if(game.ecran.camera.x >= (listeServeur->listePartie->nbColonne*SIZE_TILE) - game.ecran.camera.w)
        game.ecran.camera.x = listeServeur->listePartie->nbColonne*SIZE_TILE - game.ecran.camera.w ;

    if(game.ecran.camera.y < 0)
        game.ecran.camera.y = 0;
    else if(game.ecran.camera.y >= listeServeur->listePartie->nbLigne*SIZE_TILE - game.ecran.camera.h)
        game.ecran.camera.y = listeServeur->listePartie->nbLigne*SIZE_TILE - game.ecran.camera.h;


    
    
    // mise a jour de l'interface graphique
    updateGui();
    return 1;
    
}

/*
  ____    ____       _     __        __
 |  _ \  |  _ \     / \    \ \      / /
 | | | | | |_) |   / _ \    \ \ /\ / / 
 | |_| | |  _ <   / ___ \    \ V  V /  
 |____/  |_| \_\ /_/   \_\    \_/\_/   
                                     
*/

int draw(){ // affichage du jeu
    SDL_RenderClear(game.ecran.renderer); // Efface l'écran
   
    if(player->enCbt == false){
        // =================================== affichage de la map ==============================
            int x=0, y=0;

            if(listeServeur->listePartie->nbLigne > 0 && listeServeur->listePartie->nbColonne > 0){
                int startX = game.ecran.camera.x/SIZE_TILE, startY = game.ecran.camera.y/SIZE_TILE;
                int nbLig = game.ecran.camera.h/SIZE_TILE, nbCol = game.ecran.camera.w/SIZE_TILE, i=0, j=0;

                for(i=startX; i<startX+nbLig; i++){
                    x=0;
                    for(j=startY; j<startY+nbCol; j++){
                        SDL_Rect Rect = {x, y, SIZE_TILE, SIZE_TILE};
                        //SDL_Log("ligne : %d, colonne : %d", i, j);
                        if(listeServeur->listePartie->map[i][j] == ' '){ // herbe
                            SDL_RenderCopy(game.ecran.renderer,herbeImg,NULL,&Rect);
                        }
                        else if(listeServeur->listePartie->map[i][j] == '+'){ // soin
                            SDL_RenderCopy(game.ecran.renderer,soinImg,NULL,&Rect);
                        }
                        else if(listeServeur->listePartie->map[i][j] == '*'){// buisson
                            SDL_RenderCopy(game.ecran.renderer,buissonImg,NULL,&Rect);                        
                        }
                        else{
                            SDL_RenderCopy(game.ecran.renderer,player1Img,NULL,&Rect);
                        }
                        x += SIZE_TILE;
                    }
                    y += SIZE_TILE;
                }
            }
            else{
                printf("no map\n");
            }

    }
    else{ // en combat
        SDL_Rect Rect = {0, 0, game.ecran.camera.w, game.ecran.camera.h};
        SDL_RenderCopy(game.ecran.renderer,imgFondCombat,NULL,&Rect);


    }


        

    
    
   
        drawGui();
    SDL_RenderPresent(game.ecran.renderer); // Présente l'écran
    return 1;
}