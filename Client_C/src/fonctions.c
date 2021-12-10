
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



/*
  _   _   ____    ____       _      _____   _____  
 | | | | |  _ \  |  _ \     / \    |_   _| | ____| 
 | | | | | |_) | | | | |   / _ \     | |   |  _|   
 | |_| | |  __/  | |_| |  / ___ \    | |   | |___  
  \___/  |_|     |____/  /_/   \_\   |_|   |_____| 
                                                  
*/


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


int update(){
    
    struct timeval time;
    time.tv_sec = 0;
    time.tv_usec = 1;
    ssize_t n = 0;
    int ret;

    fd_set rdfs;
    FD_ZERO(&rdfs);
    FD_SET(clientTCP->socket, &rdfs);
    
    // reception
    if((ret = select(clientTCP->socket + 1, &rdfs, NULL, NULL, &time)) < 0){ // attente de réponse des serveurs
        perror("select()");
        //exit(errno);
    }
    
    if(ret == 0){// temps écoulé
        SDL_Log("temps écoulé");
    }    

    if(FD_ISSET(clientTCP->socket, &rdfs)){// données recu
            n = clientTCP->client_receive(clientTCP, clientTCP->buffer_recv, SIZE-1);
            clientTCP->buffer_recv[n] = '\0';
            //printf("-----------receive : %s\n", clientTCP->buffer_recv);
                    
        }
        else{
            //SDL_Log("pas de msg");
        }

    

    // =========================== recoit un msg ===========================
    char *sep = "\n", *p, tempChar[150], *line, **tab, **tab2;
    int i=0, j=0, cpt=0;
    bool isMap = false;

   // n = clientTCP->client_receive(clientTCP, clientTCP->buffer_recv, SIZE);
    //clientTCP->buffer_recv[n]='\0';
    //printf("---------------- receive : %s\n", clientTCP->buffer_recv);
    
    line = strtok(clientTCP->buffer_recv, sep);
    tab2 = split(clientTCP->buffer_recv, "\n", 0);//split le buffer entier
    //int tailleTab = (sizeof(tab2)/sizeof(tab2[0]));
    
    while(line){
        if(strlen(line) > 0){
            //SDL_Log("taille : %d", strlen(line));

        strcpy(tempChar, line); // save la ligne
       // SDL_Log("==== ligne lu : %s", tempChar);

        if(i >= listeServeur->listePartie->nbLigne){
            isMap = false;
            //SDL_Log("fin");
        }

        if(isMap){ // on recois un map
            for(j=0; j<listeServeur->listePartie->nbColonne; j++){ // lecture de la ligne
                //SDL_Log("ligne : %d, colonne : %d", i, j);
                //SDL_Log("%c : ", tempChar[j]);
                listeServeur->listePartie->map[i][j] = tempChar[j];
            }
            i++;
        }
        else{ // si autre message
           // SDL_Log("autre");
            tab = split(tempChar, " ", 0);//split la ligne

            if(strncmp(tab[0],"map",3) == 0){ // reception de la map
                listeServeur->listePartie->nbLigne = atoi(tab[1]); // ligne
                listeServeur->listePartie->nbColonne = atoi(tab[2]); // nb de colonne
               // SDL_Log("nb ligne : %d", listeServeur->listePartie->nbLigne);
                //SDL_Log("nb colonne : %d", listeServeur->listePartie->nbColonne);       
                isMap = true;
            }
            else if(strncmp(tab[0],"team",4) == 0){// recoit ma liste de poketudiant
                //SDL_Log("team");
                // récupère le nombre de poketudiant


                // récupère les poketudiants


            }
            else  if(strncmp(tab[0],"encounter new",13) == 0){
                //SDL_Log("encounter");
        
                

            }
            else  if(strncmp(tab[0]," ",3) == 0){
                // récupère le nombre de poketudiant
                   // SDL_Log("rien");

                // récupère les poketudiants
        

            }       
        
            free(tab);
            tab = NULL;

        }

        //int len = strlen(line);
        //SDL_Log("%d : ", len);
        cpt++;
        line = strtok(NULL, sep);
        }

    }


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

                    }
                    x += SIZE_TILE;
                }
                y += SIZE_TILE;
            }
        }
        else{
            printf("no map\n");
        }

        

    
    
   
        drawGui();
    SDL_RenderPresent(game.ecran.renderer); // Présente l'écran
    return 1;
}