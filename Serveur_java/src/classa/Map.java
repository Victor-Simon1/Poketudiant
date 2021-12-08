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
	public Map() {
		this.nb_colonnes = 0;
		this.nb_lignes = 0;
		this.fileMap = new File("map"+Function.myRandom(0,4)+".txt");
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
	public int getLine() {
		return this.nb_lignes;
		
	}
	public int getColumn() {
		return this.nb_colonnes;
		
	}
	public String getTab() {
		String tab = "";
		for(int line =0;line<this.nb_lignes;line++) {
			for(int col =0;col<this.nb_colonnes;col++) {
				tab += Map[line][col];
			}
			tab += '\n';
		}
		
		return tab;
	}
	
	void readMap(File file) throws IOException {
		  FileReader fr = new FileReader(file);       
	      BufferedReader br = new BufferedReader(fr);  
	      StringBuffer sb = new StringBuffer();    
	      String line;

	      while((line = br.readLine()) != null)
	      {
	        
	        sb.append(line);
	       this.nb_lignes = line.length() /2;
	        this.nb_colonnes++;
	        sb.append("\n");     
	      }
	      fr.close();    
	      System.out.println("Contenu du fichier: ");
	      System.out.println(sb.toString());  
	}
}
