package classa;



public class Combat {
    private Pokaimone p1;
    private Pokaimone p2;

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

	public Combat(Pokaimone pokaimone, Pokaimone pokaimone2) {
		// TODO Auto-generated constructor stub
		this.p1 = pokaimone;
		this.p2 = pokaimone2;
	}
	public void deroulementCombat() {
		if(this.actionP1 != ""&& this.actionp2 != "") {
			if(this.actionP1.contains("attack") && this.actionp2.contains("attack")) {
				 this.p2.setPv( this.p2.getPv() -this.p1.makeDamage(this.p1.make_attack1(this.p2.getType()),this.p2));
				 this.p1.setPv( this.p1.getPv() -this.p2.makeDamage(this.p2.make_attack1(this.p1.getType()),this.p1));
			}
			else if(this.actionP1.contains("switch") && this.actionp2.contains("attack")) {
				
			}
			else if(this.actionP1.contains("attack") && this.actionp2.contains("switch")) {
				
			}
			else if(this.actionP1.contains("switch") && this.actionp2.contains("switch")) {
				
			}
		}
	}
	public Pokaimone getP1() {
		// TODO Auto-generated method stub
		return p1;
	}

	
	
	
}
