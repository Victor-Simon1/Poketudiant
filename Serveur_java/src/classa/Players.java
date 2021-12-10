package classa;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
public class Players  extends Thread implements Runnable{
    Socket s ;//= new Socket();
    Server serv;//serveur ou le cliebt a git
    private PrintWriter writer;//ecrire au serveur
    private BufferedReader reader;//recoit du serveur 
    private boolean inGame;//dans une game
    private Game game;// game ou est le client
    private Pokaimone pokPrinc;

    private Combat combat;

    //Constructeur
    public Players(Socket player,Server serv){
        this.s = player;
        this.serv = serv;
        this.inGame = false;
        this.game = null;

        //this.pokPrinc = new Pokaimone("name",Type.TEACHER,false,"No",100,100,100);

        try {
			this.writer = new PrintWriter(this.s.getOutputStream(), true);
			this.reader = new BufferedReader(new InputStreamReader(this.s.getInputStream()));
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
    }


    public Combat getCombat() {
  		return combat;
  	}
  	public void setCombat(Combat combat) {
  		this.combat = combat;
  	}
    // fonction publiques
    public void writeClient(String str) {//ecrit au client
    	System.out.println("SEND \n" + str);
    	this.writer.println(str);
    }
    public String receiveClient() {//recoit du client
    	try {
			return reader.readLine();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return null;
		}
    }
    
    public BufferedReader getReader() {
    	return reader;
    }


    public boolean compareString(String s1 , String s2){//comapre les string
        boolean same = false;
        if(s1.length() != s2.length())same = false;
        for(int i =0;i<s1.length();i++){
            if(s1.charAt(i) != s2.charAt(i)){
                same =  false;
            }
        }
        same =  true;
        System.out.println("Same ? : " + same);
        return same;
    }
    public void run(){//fonction du thread
        System.out.println("ICI");
        String str = new String();
        String game_info = new String();
        String info[];
  
        try {
           /// writer.println("Connect");
            for(;;){
            
                //System.out.println("DEBUG : " + str);
                str = reader.readLine();
                
                if(str != null) {
                	System.out.println("DEBUG1 : " + str);
                    if(str.contains("require game list")){//demande le nombre de game
                       // System.out.println("number of games 1");
                        this.writeClient("number of games "+this.serv.getListGame().size());
                        for(int nbgame = 0;nbgame <this.serv.getListGame().size();nbgame++){
                            game_info = game_info + this.serv.getListGame().get(nbgame).getNbPlayer() + " " +  this.serv.getListGame().get(nbgame).getName() + "\n"; 
                        }
                   // game_info = game_info + "3 12345678\n"; 
                    //game_info = game_info + "7 game2\n"; 
                    if(this.serv.getListGame().size()>0)writer.println(game_info);
                     System.out.println(game_info);
                    
                    }

                    else if(str.contains("create game")){
                    	info = str.split(" ");
                        Game g = new Game(info[2]);
                        //System.out.println(g.toString());
                        if(g != null) {
                        	//System.out.println("g");
                        	g.start();
                            this.game = g;
                            if(g.joinGame(this)) {
                            	
                            	 this.game.setNbPlayer(this.game.getNbPlayer()+1);
                            	 	
                                 this.serv.setListGame(g);
                                
                                 this.inGame = true;
                                 this.pokPrinc = new Pokaimone("name",Type.TEACHER,false,"No",100,100,100);

                                 this.writeClient("game created");
                           
                                 this.writeClient("map "+ this.game.getMap().getLine()+ " "+ this.game.getMap().getColumn() );
                                 this.writeClient(this.game.getMap().getTab(this));
                             		
                                // System.out.println("game created");
                            }
                            else {
                            	this.writeClient("cannot create game");
                            }
                           
                        }
                        else {
                        	//System.out.println("pa g");
                            writer.println("cannot create game");
                        }
                   
                    }

                    else if(str.contains("join game")){
                        
                       
                        info = str.split(",");
                        for(int i=0; i < this.serv.getListGame().size();i++){
                            System.out.println(info[1]  + " " +info[1].length());
                            System.out.println(this.serv.getListGame().get(i).getName() + " " + this.serv.getListGame().get(i).getName().length());
                            if(compareString(info[1],this.serv.getListGame().get(i).getName()) == true){
                                this.game =  this.serv.getListGame().get(i);
                                if(this.game != null) {
                                	this.serv.getListGame().get(i).joinGame(this);
                                	this.game.setNbPlayer(this.game.getNbPlayer()+1);
                                    this.inGame = true;
                                    writer.println("game joined");
                                }
                                else {
                                	 writer.println("cannot join game");
                                }
                            }
                            
                        }
                    }
                    else if(str.contains("map move")) {
                    	str = str.substring("map move".length());
                    	if(str.contains("left")) {
                    		this.game.movePlayer(this,'L');
                    	}
                    	else if(str.contains("right")) {
                    		this.game.movePlayer(this,'R');
                    	}
                    	else if(str.contains("down")) {
                    		this.game.movePlayer(this,'D');
                    	}
                    	else if(str.contains("up")) {
                    		this.game.movePlayer(this,'U');
                    	}
                    }
                    else if(str.contains("poketudiant")&& str.contains("move up")) {
                    	
                    }
                    else if(str.contains("poketudiant")&& str.contains("move down")) {
                    	
                    }
                    else if(str.contains("poketudiant")&& str.contains("free")) {
                    	
                    }
                    else if(str.contains("encounter action attack1")) {
                    	if(this.getPokPrinc() == this.combat.getP1()) {
                    		this.combat.setActionP1("attack1");
                    	}
                    	else {
                    		this.combat.setActionp2("attack1");
                    	}
                    }
                    else if(str.contains("encounter action attack2")) {
                    	if(this.getPokPrinc() == this.combat.getP1()) {
                    		this.combat.setActionP1("attack2");
                    	}
                    	else {
                    		this.combat.setActionp2("attack2");
                    	}
                    }
                    else if(str.contains("ecounter action switch")) {
                    	if(this.getPokPrinc() == this.combat.getP1()) {
                    		this.combat.setActionP1("switch");
                    	}
                    	else {
                    		this.combat.setActionp2("switch");
                    	}
                    }
                    else if(str.contains("encounter action catch")) {
                    	if(this.getPokPrinc() == this.combat.getP1()) {
                    		this.combat.setActionP1("catch");
                    	}
                    	else {
                    		this.combat.setActionp2("catch");
                    	}
                    }
                    else if(str.contains("encounter action leave")) {
                    	if(this.getPokPrinc() == this.combat.getP1()) {
                    		this.combat.setActionP1("leave");
                    	}
                    	else {
                    		this.combat.setActionp2("leave");
                    	}
                    }
                    else if(str.contains("encounter poketudiant index")) {
                    	if(this.getPokPrinc() == this.combat.getP1()) {
                    		this.combat.setActionP1("switch");
                    	}
                    	else {
                    		this.combat.setActionP1("switch");
                    	}
                    }
                    
                    else if(true){//contenu equipe
                    	
                    }
                    /*
                    else if(str.contains("encounter new wild")) {
                    	
                    }
                    else if(str.contains("encounter new rival")) {
                    	
                    }
                    else if(str.contains("encounter KO opponent")) {
                    	
                    }
                    else if(str.contains("encounter KO player")) {
                    	
                    }
                    else if(str.contains("encounter win")) {
                    	
                    }
                    else if(str.contains("encounter lose")) {
    	
                    }
                    else if(str.contains("encounter catch ok")) {
    	
                    }
                    else if(str.contains("encounter catch fail")) {
                    	
                    }
                    else if(str.contains("encounter escape ok")) {
    	
                    }
                    else if(str.contains("encounter escape fail")) {
                    	
                    }
                    else if(str.contains("encounter poketudiant xp ")) {
                    	
                    }
                    else if(str.contains("encounter poketudiant ok")) {
                    	
                    }
                    */
                }
                else {
                //	System.out.println(str);
                }

            }
            
        }
        catch (IOException e) {
            // TODO Auto-generated catch block
             e.printStackTrace();
        }
        
        /*
        else if(){//envoie la carte
            writer.println("map "+ game.getMap().getNbLines() );
        }*/
        /*
        try {
            if(this.serv.getListGame().size()  == 0){
                writer.println("no game\n");
            }
            else{
                //writer.println(nb_games + " games");
                game_name += ( "games "+ this.serv.getListGame().size() + "\n");
                for(int j = 0;j<this.serv.getListGame().size();j++){
                    game_name += this.serv.getListGame().get(j).getName();
                    game_name += "\n";
                    game_name += this.serv.getListGame().get(j).getNbPlayer();
                    game_name += "\n";
                
                }
                System.out.println("Envoie :" + game_name);
                writer.println(game_name);
            }
            String str = new String();
            for(;;){
                str = reader.readLine();
                System.out.println("Receive d " + str);
                if(str.contains("created game")){
                    writer.println("game created");
                    info = str.split(",");
                    Game g = new Game(info[1],Integer.parseInt(info[2]),Integer.parseInt(info[3]));
                    this.game = g;
                    this.game.setNbPlayer(this.game.getNbPlayer()+1);
                    g.joinGame(this);
                    this.serv.setListGame(g);
                    this.inGame = true;
                    
                }
                else if (str.contains("join game")){
                    //str = str.substring("join game ".length(), str.length());
                    info = str.split(",");
                    for(int i=0; i < this.serv.getListGame().size();i++){
                        System.out.println(info[1]  + " " +info[1].length());
                        System.out.println(this.serv.getListGame().get(i).getName() + " " + this.serv.getListGame().get(i).getName().length());
                        if(compareString(info[1],this.serv.getListGame().get(i).getName()) == true){
                            this.game =  this.serv.getListGame().get(i);
                            this.game.setNbPlayer(this.game.getNbPlayer()+1);
                            this.serv.getListGame().get(i).joinGame(this); 
                            this.inGame = true;
                            
                        }
                    }
                }
    
                if(inGame && game.gameIsReady(this) && game.roundIsReady()){
                    System.out.println("Ready");
                    game.protocolGamePlayer(this);
                }
                else  System.out.println("Not Ready");
            }
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
       */
    }
	public Pokaimone getPokPrinc() {
		return pokPrinc;
	}
	public void setPokPrinc(Pokaimone pokPrinc) {
		this.pokPrinc = pokPrinc;
	}



    //getters


    //setters
}
