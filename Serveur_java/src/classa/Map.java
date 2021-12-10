package classa;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

public class Map {
    
	int nb_lignes;
	int nb_colonnes;
	char Map[][];
	File fileMap;
	int nbHighGrass;
	int nbHeal;
	public Map() {
		this.nb_colonnes = 0;
		this.nb_lignes = 0;
		this.nbHighGrass = 0;
		this.nbHeal = 0;
		//this.fileMap = new File("file/map"+Function.myRandom(1,4)+".txt");
		this.fileMap = new File("Serveur_java/file/map4.txt");
		try {
			this.readMap(fileMap);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		//this.nb_lignes = Function.myRandom(10, 50);PAS RANDOM MAIS FICHIER
		//this.nb_colonnes = Function.myRandom(10, 50);
		//this.Map = new int[]
	}
	public Map(Map map) {
		this.Map = map.Map;
		this.nb_colonnes =map.nb_colonnes;
		this.nb_lignes = map.nb_lignes;
		this.nbHighGrass = map.nbHighGrass;
		this.nbHeal = map.nbHeal;
	}
	public int getLine() {
		return this.nb_lignes;
		
	}
	public int getColumn() {
		return this.nb_colonnes;
		
	}
	public String getTab(Players p) {
		String tab = "";
		for(int line =0;line<this.nb_lignes;line++) {
			for(int col =0;col<this.nb_colonnes;col++) {
				//System.out.println(line+" " + col+" " + this.Map[line][col]);
				if(p.getPokPrinc().getX() == line && p.getPokPrinc().getY( )== col) {
					tab += '0';
				}
				else {
					tab += Map[line][col];
				}
					
			}
			tab += '\n';
		}
		
		return tab;
	}
	public void afficherMap() {
		System.out.println("Lignes : "+ this.nb_lignes + "\nColonnes : "+ this.nb_colonnes);
		for(int nbLine = 0;nbLine <this.nb_lignes;nbLine++) {
			for(int nbCol = 0;nbCol <this.nb_colonnes;nbCol++) {
				System.out.print(this.Map[nbLine][nbCol]);
			}
			System.out.println();
		}
	}
	void readMap(File file) throws IOException {
		  FileReader fr = new FileReader(file);       
	      BufferedReader br = new BufferedReader(fr);  
	      StringBuffer sb = new StringBuffer();    
	      String line;

	      while((line = br.readLine()) != null)
	      {
	        line = line + '\n';
	        sb.append(line);
	        //sb.append("\n");  
	       this.nb_colonnes = line.length()-1;
	        this.nb_lignes++;
	           
	      }
	      fr.close();    
	      Map = new char[this.nb_lignes][this.nb_colonnes];
	      //System.out.println(nb_colonnes +"+"+ nb_lignes);
	      int cpt = 0;
	      int lines = 0;
	      int column = 0;
	      
	      while(cpt < sb.length()) {
	    	  if(sb.charAt(cpt) == '\n') {
	    		  lines++;
	    		  column = 0;
	    	  }
	    	  else {
	    		 // System.out.println(lines + " "+ column);
	    		  this.Map[lines][column] = sb.charAt(cpt);
	    		  if(sb.charAt(cpt) == '*')this.nbHighGrass++;
	    		  else if(sb.charAt(cpt) == '+')this.nbHeal++;
	    		  column++;
	    	  }
	    	  cpt++;
	      }
	      //System.out.println("Contenu du fichier: ");
	     // System.out.println(sb.toString());  
	      //this.afficherMap();
	}
}
