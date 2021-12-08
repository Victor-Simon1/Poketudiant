package classa;



import java.io.IOException;

import java.util.ArrayList;
import java.util.Random;
import java.util.Arrays;
public class Game {
    
	private String name; //Nom de la game
	private int max_player;// Nb de joueur max

	private int nb_player;// nb de player actuellement dans la game
	private ArrayList<Players> listPlayers;//liste des joueurs


	private boolean isReady; //si la game est pretre


	
	private Map map;
	//Constructeur
    public Game(String name){
    	this.max_player = 4;
    	this.name = name;
    	this.listPlayers = new ArrayList<Players>();
		this.isReady = false;
		this.nb_player = 0;
    }
	


	public boolean gameIsReady(Players cli){//Dit si la game est prete
		System.out.println("Nb " + max_player + " " + nb_player);
        if(max_player == nb_player){
			cli.writeClient("Game ready");
			isReady = true;
        }
		cli.writeClient("game not ready,waiting ...");
		
		return isReady;
    }
    
    public boolean joinGame(Players c) {// Verifie si un client peut rejoibdre ou non la game et l'ajoute si il peut
    	if(this.listPlayers.size()<this.max_player) {
    		this.listPlayers.add(c);
        	//this.listPlayers.get(this.listPlayers.size()-1).writeClient("game joined"); //ecrit 
            //c.writeClient("Game joined");
    		return true;
        }
    	else {
    		//c.writeClient("cannot joined game"); //ecrit 
    		return false;
    	}
    	
    }
    
    public void movePlayer(Players p,char move) {
    	if(move == 'L') {
    		if(p.getX()-1<map.nb_colonnes ) { 
    			p.setX(p.getX()-1);
    			for(int nbP = 0;nbP <this.nb_player ;nbP++) {
    				if(p.collidePlayer(this.listPlayers.get(nbP)) && p!=this.listPlayers.get(nbP)) {
        				Combat c = new Combat(p,this.listPlayers.get(nbP));
        				p.setCombat(c);
        				this.listPlayers.get(nbP).setCombat(c);
        				p.writeClient("encounter new rival " + 1 );
        				this.listPlayers.get(nbP).writeClient("encounter new rival " + 1 );
        			}
    			}
    			
    		}
    	}
    	if(move == 'R') {
    		if(p.getX()+1<map.nb_colonnes ) { 
    			p.setX(p.getX()+1);
    			for(int nbP = 0;nbP <this.nb_player ;nbP++) {
    				if(p.collidePlayer(this.listPlayers.get(nbP)) && p!=this.listPlayers.get(nbP)) {
        				Combat c = new Combat(p,this.listPlayers.get(nbP));
        				p.setCombat(c);
        				this.listPlayers.get(nbP).setCombat(c);
        				p.writeClient("encounter new rival " + 1 );
        				this.listPlayers.get(nbP).writeClient("encounter new rival " + 1 );
        			}
    			}
    		}
    	}
    	if(move == 'D') {
    		if(p.getY()+1<map.nb_colonnes ) { 
    			p.setY(p.getY()+1);
    			for(int nbP = 0;nbP <this.nb_player ;nbP++) {
    				if(p.collidePlayer(this.listPlayers.get(nbP)) && p!=this.listPlayers.get(nbP)) {
        				Combat c = new Combat(p,this.listPlayers.get(nbP));
        				p.setCombat(c);
        				this.listPlayers.get(nbP).setCombat(c);
        				p.writeClient("encounter new rival " + 1 );
        				this.listPlayers.get(nbP).writeClient("encounter new rival " + 1 );
        			}
    			}
    		}
    	}
    	if(move == 'U') {
    		if(p.getY()-1<map.nb_colonnes ) { 
    			p.setY(p.getY()-1);
    			for(int nbP = 0;nbP <this.nb_player ;nbP++) {
    				if(p.collidePlayer(this.listPlayers.get(nbP)) && p!=this.listPlayers.get(nbP)) {
        				Combat c = new Combat(p,this.listPlayers.get(nbP));
        				p.setCombat(c);
        				this.listPlayers.get(nbP).setCombat(c);
        				p.writeClient("encounter new rival " + 1 );
        				this.listPlayers.get(nbP).writeClient("encounter new rival " + 1 );
        			}
    			}
    		}
    	}
    	
    
    }
   
    public String toString(){//toString
        return this.getName() + " " + this.nb_player + "\n";
	}
	
	
	public int getMaxPlayer(){
		return this.max_player;
	}
	public int getNbPlayer(){
		return this.nb_player;
	}
	public void setNbPlayer(int nb){
		this.nb_player = nb;
	}
	public String getName() {
		return this.name;
	}
	
	public Map getMap() {
		return this.map;
	}
}
