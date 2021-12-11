package classa;

import java.util.ArrayList;
import java.util.Collections;

public class Teams {
	ArrayList<Pokaimone> liste;

	public Teams(Pokaimone ens) {
		this.liste = new ArrayList<Pokaimone>();
		this.liste.add(ens);

	}
	
	public Pokaimone firstElement() {
		return this.liste.get(0);
	}
	public boolean ajoutInTeam(Pokaimone pok) {
		if(this.liste.size() >= 3) {
			return false;
		}
		this.liste.add(pok);
		return true;
	}
	public boolean  echanger(int posA,int posB) {
		boolean estEchange = false;
		if(posA <0  || posA> this.liste.size() -1 || posB<0 || posB>this.liste.size()-1) {
		}
		else {
			Collections.swap(liste, posA, posB);
			estEchange = true;
		}
		return estEchange;
		
	}
}
