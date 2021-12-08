package classa;



public class Combat {
    private Players p1;
    private Players p2;
    private Pokaimone pok1;
    private Pokaimone pok2;
    private String actionP1;
    private String actionp2;
	public String getActionP1() {
		return actionP1;
	}

	public void setActionP1(String actionP1) {
		this.actionP1 = actionP1;
	}

	public String getActionp2() {
		return actionp2;
	}

	public void setActionp2(String actionp2) {
		this.actionp2 = actionp2;
	}

	public Combat(Players p1, Players p2) {
		// TODO Auto-generated constructor stub
		this.p1 = p1;
		this.p2 = p2;
		pok1 = p1.getPokPrinc();
		pok2 = p2.getPokPrinc();
	}

	public Players getP1() {
		// TODO Auto-generated method stub
		return p1;
	}
	
	
}
