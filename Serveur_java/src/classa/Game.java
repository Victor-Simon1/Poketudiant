package classa;



import java.io.IOException;

import java.util.ArrayList;
import java.util.Random;
import java.util.Arrays;
public class Game extends Thread {
    
	private String name; //Nom de la game
	private int max_player;// Nb de joueur max

	private int nb_player;// nb de player actuellement dans la game
	private ArrayList<Players> listPlayers;//liste des joueurs
	private ArrayList<Pokaimone> listPokaimone;

	private boolean isReady; //si la game est pretre
	private int nbMaxPokaimone;
	
	
	private Map map;
	//Constructeur
    public Game(String name){
    	this.max_player = 4;
    	this.name = name;
    	this.listPlayers = new ArrayList<Players>();
    	this.listPokaimone = new ArrayList<Pokaimone>();
		this.isReady = false;
		this.nb_player = 0;
		this.map = new Map();
		this.nbMaxPokaimone = (int)(this.map.nbHighGrass /3);
    }
	public void run() {
		this.verifyPokaimone();
	}
 

    public void verifyPokaimone() {
    	//verifie si un pokaimone peut disparaite
    	this.listPokaimone.forEach(n -> {
    		if(n.timer>20000) {
    			this.listPokaimone.remove(n);
    		}
    	});
    	if(this.listPokaimone.size() < this.nbMaxPokaimone) {
    		if(Function.myRandom(0, 100)<10) {
    			Poketudiant rand = Poketudiant.values()[new Random().nextInt(Poketudiant.values().length)];;
    			this.listPokaimone.add(new Pokaimone(rand.name, rand.type, rand.isCapturable, rand.evolution.name,rand.atk ,rand.def, rand.pv));
    		}
    			
    		
    	}
    	
    	this.listPokaimone.forEach(n -> n.timer++);
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
    		if(p.getPokPrinc().getX()-1<map.nb_colonnes ) { 
    			p.getPokPrinc().setX(p.getPokPrinc().getX()-1);
    			for(int nbP = 0;nbP <this.nb_player ;nbP++) {
    				if(p.getPokPrinc().collidePoketudiant((this.listPlayers.get(nbP).getPokPrinc())) && p!=this.listPlayers.get(nbP)) {
        				Combat c = new Combat(p.getPokPrinc(),this.listPlayers.get(nbP).getPokPrinc());
        				p.setCombat(c);
        				this.listPlayers.get(nbP).setCombat(c);
        				p.writeClient("encounter new rival " + 1 );
        				this.listPlayers.get(nbP).writeClient("encounter new rival " + 1 );
        			}
    			}
    			for(int nbPok=0;nbPok<this.listPokaimone.size();nbPok++) {
    				if(p.getPokPrinc().collidePoketudiant((this.listPokaimone.get(nbPok)))&& p!=this.listPlayers.get(nbPok)) {
        				Combat c = new Combat(p.getPokPrinc(),this.listPokaimone.get(nbPok));
        				p.setCombat(c);
        				this.listPokaimone.get(nbPok).setCombat(c);
        				p.writeClient("encounter new wild " + 1 );
        		
        			}
    			}
    		}
    	}
    	if(move == 'R') {
    		if(p.getPokPrinc().getX()+1<map.nb_colonnes ) { 
    			p.getPokPrinc().setX(p.getPokPrinc().getX()+1);
    			for(int nbP = 0;nbP <this.nb_player ;nbP++) {
    				if(p.getPokPrinc().collidePoketudiant((this.listPlayers.get(nbP).getPokPrinc())) && p!=this.listPlayers.get(nbP)) {
        				Combat c = new Combat(p.getPokPrinc(),this.listPlayers.get(nbP).getPokPrinc());
        				p.setCombat(c);
        				this.listPlayers.get(nbP).setCombat(c);
        				p.writeClient("encounter new rival " + 1 );
        				this.listPlayers.get(nbP).writeClient("encounter new rival " + 1 );
        			}
    			}
    			for(int nbPok=0;nbPok<this.listPokaimone.size();nbPok++) {
    				if(p.getPokPrinc().collidePoketudiant((this.listPokaimone.get(nbPok)))&& p!=this.listPlayers.get(nbPok)) {
        				Combat c = new Combat(p.getPokPrinc(),this.listPokaimone.get(nbPok));
        				p.setCombat(c);
        				this.listPokaimone.get(nbPok).setCombat(c);
        				p.writeClient("encounter new wild " + 1 );
        		
        			}
    			}
    		}
    	}
    	if(move == 'D') {
    		if(p.getPokPrinc().getY()+1<map.nb_colonnes ) { 
    			p.getPokPrinc().setY(p.getPokPrinc().getY()+1);
    			for(int nbP = 0;nbP <this.nb_player ;nbP++) {
    				if(p.getPokPrinc().collidePoketudiant((this.listPlayers.get(nbP).getPokPrinc())) && p!=this.listPlayers.get(nbP)) {
        				Combat c = new Combat(p.getPokPrinc(),this.listPlayers.get(nbP).getPokPrinc());
        				p.setCombat(c);
        				this.listPlayers.get(nbP).setCombat(c);
        				p.writeClient("encounter new rival " + 1 );
        				this.listPlayers.get(nbP).writeClient("encounter new rival " + 1 );
        			}
    			}
    			for(int nbPok=0;nbPok<this.listPokaimone.size();nbPok++) {
    				if(p.getPokPrinc().collidePoketudiant((this.listPokaimone.get(nbPok)))&& p!=this.listPlayers.get(nbPok)) {
        				Combat c = new Combat(p.getPokPrinc(),this.listPokaimone.get(nbPok));
        				p.setCombat(c);
        				this.listPokaimone.get(nbPok).setCombat(c);
        				p.writeClient("encounter new wild " + 1 );
        		
        			}
    			}
    		}
    	}
    	if(move == 'U') {
    		if(p.getPokPrinc().getY()-1<map.nb_colonnes ) { 
    			p.getPokPrinc().setY(p.getPokPrinc().getY()-1);
    			for(int nbP = 0;nbP <this.nb_player ;nbP++) {
    				if(p.getPokPrinc().collidePoketudiant((this.listPlayers.get(nbP).getPokPrinc())) && p!=this.listPlayers.get(nbP)) {
        				Combat c = new Combat(p.getPokPrinc(),this.listPlayers.get(nbP).getPokPrinc());
        				p.setCombat(c);
        				this.listPlayers.get(nbP).setCombat(c);
        				p.writeClient("encounter new rival " + 1 );
        				this.listPlayers.get(nbP).writeClient("encounter new rival " + 1 );
        			}
    			}
    			for(int nbPok=0;nbPok<this.listPokaimone.size();nbPok++) {
    				if(p.getPokPrinc().collidePoketudiant((this.listPokaimone.get(nbPok)))&& p!=this.listPlayers.get(nbPok)) {
        				Combat c = new Combat(p.getPokPrinc(),this.listPokaimone.get(nbPok));
        				p.setCombat(c);
        				this.listPokaimone.get(nbPok).setCombat(c);
        				p.writeClient("encounter new wild " + 1 );
        		
        			}
    			}
    		}
    	}
    	
    	this.listPlayers.forEach(n -> {
    		n.writeClient("map "+this.map.nb_lignes + " " + this.map.nb_colonnes + "\n");
    		n.writeClient(this.map.getTab(n));
    	} );
    
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
	public String getNameGame() {
		return this.name;
	}
	
	public Map getMap() {
		return this.map;
	}



	public ArrayList<Pokaimone> getListPokaimone() {
		return listPokaimone;
	}



	public void setListPokaimone(ArrayList<Pokaimone> listPokaimone) {
		this.listPokaimone = listPokaimone;
	}
}
