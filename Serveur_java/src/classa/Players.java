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
    private Teams team;
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
    
    
    public void envoieEquipe() {
    	String team = "";
    	this.writeClient("team contains " + this.team.liste.size() );
    	
    	
    	for(int i = 0;i< this.team.liste.size();i++) {
    		team += this.team.liste.get(i).getName() +" " + this.team.liste.get(i).getType() + " "+ 
    				this.team.liste.get(i).getLvl() + " " +this.team.liste.get(i).getXp() + " " +
    				(this.team.liste.get(i).getXpMax() -  this.team.liste.get(i).getXp())+ " "+
    				this.team.liste.get(i).getPv() +  " "+ 
    				this.team.liste.get(i).getPvMax() + " " +this.team.liste.get(i).getAttaque() + " "+
    				this.team.liste.get(i).getDefense() + " " + this.team.liste.get(i).getAttack1().name()+ " " +
    				this.team.liste.get(i).getAttack1().name() + "\n"; 
    	}
    
    	this.writeClient(team);
    }
    public void run(){//fonction du thread
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
                        	
                            this.game = g;
                            this.game.start();
                            if(g.joinGame(this)) {
                            	
                            	 this.game.setNbPlayer(this.game.getNbPlayer()+1);
                            	 	
                                 this.serv.setListGame(g);
                                
                                 this.inGame = true;
                                 this.pokPrinc = new Pokaimone("name",Type.TEACHER,false,"No",100,100,100);
                                 this.team = new Teams(new Pokaimone("name",Type.TEACHER,false,"No",100,100,100));
                              
                                 this.writeClient("game created");
                           
                                 this.writeClient("map "+ this.game.getMap().getLine()+ " "+ this.game.getMap().getColumn() );
                                 this.writeClient(this.game.getMap().getTab(this));
                                 
                                 this.envoieEquipe();
                             		
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
                    	info = str.split(" ");
                    	int x = info[1].charAt(0);
                    	if(this.team.echanger(x, x-1) ) {
                    		this.envoieEquipe();
                    	}
                    
                    	
                    }
                    else if(str.contains("poketudiant")&& str.contains("move down")) {
                    	info = str.split(" ");
                    	int x = info[1].charAt(0);
                    	if(this.team.echanger(x, x+1) ) {
                    		this.envoieEquipe();
                    	}
                    
                    }
                    else if(str.contains("poketudiant")&& str.contains("free")) {
                    	info = str.split(" ");
                    	int x = info[1].charAt(0);
                    	this.team.freePok(x);
                    	this.envoieEquipe();
                    }
                    else if(str.contains("encounter action attack1")) {
                    	if(this == this.combat.getPlayer1()) {
                    		this.combat.setActionP1(str);
                    	}
                    	else {
                    		this.combat.setActionp2(str);
                    	}
                    }
                    else if(str.contains("encounter action attack2")) {
                    	if(this == this.combat.getPlayer1()) {
                    		this.combat.setActionP1(str);
                    	}
                    	else {
                    		this.combat.setActionp2(str);
                    	}
                    }
                    else if(str.contains("ecounter action switch")) {
                    	if(this== this.combat.getPlayer1()) {
                    		this.combat.setActionP1(str);
                    	}
                    	else {
                    		this.combat.setActionp2(str);
                    	}
                    }
                    else if(str.contains("encounter action catch")) {
                    	if(this == this.combat.getPlayer1()) {
                    		this.combat.setActionP1(str);
                    	}
                    	else {
                    		this.combat.setActionp2(str);
                    	}
                    }
                    else if(str.contains("encounter action leave")) {
                    	if(this == this.combat.getPlayer1()) {
                    		this.combat.setActionP1(str);
                    	}
                    	else {
                    		this.combat.setActionp2(str);
                    	}
                    }
                    else if(str.contains("encounter poketudiant index")) {
                    	if(this == this.combat.getPlayer1()) {
                    		this.combat.setActionP1(str);
                    	}
                    	else {
                    		this.combat.setActionP1(str);
                    	}
                    }
                    
                    
                }
                else {
                //	System.out.println(str);
                }

            }
            
        }
        catch (IOException e) {
            // TODO Auto-generated catch block
        	try {
				s.close();
			} catch (IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
            e.printStackTrace();
        }
        
    }
	public Game getGame() {
		return game;
	}


	public void setGame(Game game) {
		this.game = game;
	}


	public Pokaimone getPokPrinc() {
		return pokPrinc;
	}
	public void setPokPrinc(Pokaimone pokPrinc) {
		this.pokPrinc = pokPrinc;
	}


	public Teams getTeam() {
		return team;
	}


	public void setTeam(Teams team) {
		this.team = team;
	}



    //getters


    //setters
}
