package classa;


public class Teams {
	
	Pokaimone courant;
	Pokaimone enseignant;
	Pokaimone pok1;
	Pokaimone pok2;
	
	public Teams(Pokaimone ens) {
		this.enseignant = ens;
		this.pok1 = null;
		this.pok2 = null;
		this.courant = this.enseignant;
	}
}
