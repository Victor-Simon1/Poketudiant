package classa;



public class Combat {
    private Players player1;
    private Players player2;
    private String actionP1;
    private String actionp2;
    private Pokaimone pok;
    private int XpTotal;
    public Combat(Players pokaimone, Players pokaimone2) {
		// TODO Auto-generated constructor stub
		this.player1 = pokaimone;
		this.player2 = pokaimone2;
	}
    public Combat(Players pokaimone, Pokaimone  pokaimone2) {
		// TODO Auto-generated constructor stub
		this.player1 = pokaimone;
		this.pok= pokaimone2;
		this.XpTotal = 25;
	}
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

	
	public void deroulementCombat2Pok() {
		if(this.actionP1 != ""&& this.actionp2 != "") {
			if(this.actionP1.contains("attack") && this.actionp2.contains("attack")) {
				 this.player2.getTeam().firstElement().setPv( this.player2.getTeam().firstElement().getPv() -this.player1.getTeam().firstElement().makeDamage(this.player2.getTeam().firstElement().make_attack1(this.player2.getTeam().firstElement().getType()),this.player2.getTeam().firstElement()));
				 this.player1.getTeam().firstElement().setPv( this.player1.getTeam().firstElement().getPv() -this.player2.getTeam().firstElement().makeDamage(this.player1.getTeam().firstElement().make_attack1(this.player1.getTeam().firstElement().getType()),this.player1.getTeam().firstElement()));
			}
			else if(this.actionP1.contains("switch") && this.actionp2.contains("attack")) {
				
			}
			else if(this.actionP1.contains("attack") && this.actionp2.contains("switch")) {
				
			}
			else if(this.actionP1.contains("switch") && this.actionp2.contains("switch")) {
				
				this.player1.writeClient("encounter enter action");
				this.player2.writeClient("encounter enter action");
				//this.player1.getTeam().echanger(info, posB);
				//this.player2.getTeam().echanger(posA, posB);
			}
			
		}
		else if(this.actionP1 == ""&& this.actionp2 == "") {
			this.player1.writeClient("encounter enter action");
			this.player2.writeClient("encounter enter action");
		}
		
		
		if(player1.getTeam().firstElement().isKO()){
			if(player1.getTeam().getListe().get(1).getPv() == 0 &&player1.getTeam().getListe().get(1).getPv() ==0 ) {
				this.player1.writeClient("encounter lose");
				this.player2.writeClient("encounter win");
			}
			else {
				
			}
		}
		if(player2.getTeam().firstElement().getPv() == 0){
			if(player2.getTeam().getListe().get(1).getPv() == 0 &&player2.getTeam().getListe().get(1).getPv() ==0 ) {
				this.player1.writeClient("encounter win");
				this.player2.writeClient("encounter lose");
			}
			else {
				
			}
		}
	}
	
	public void deroulementCombat1Pok() {
		if(this.actionP1 != "") {
			if(this.actionP1.contains("attack") ) {
				 this.player1.getTeam().firstElement().setPv( this.player1.getTeam().firstElement().getPv() -this.player2.getTeam().firstElement().makeDamage(this.player1.getTeam().firstElement().make_attack1(this.player1.getTeam().firstElement().getType()),this.player1.getTeam().firstElement()));
			}
			else if(this.actionP1.contains("switch")) {
				
			}
			else if(this.actionP1.contains("leave")) {
				boolean leave = false;
				leave = this.player1.getTeam().getListe().get(0).tentativeFuite(this.player2.getTeam().getListe().get(0));
				if(leave) {
					this.player1.getGame().getListCombat().remove(this.player1.getCombat());
					
					this.player1.writeClient("encounter escape ok");
				}
				else {
					this.player1.writeClient("encounter escape fail");
				}
			}
			this.putAttackPoke();
		}
		else if(this.actionP1 == "") {
			this.player1.writeClient("encounter enter action");
		}
		if(this.pok.isKO()) {
			this.player1.writeClient("encounter win");
			this.player1.getTeam().getListe().forEach(n -> {
				n.setXp(n.getXp() +(int)(this.XpTotal /3));
				if(n.getPv() != n.getPvMax()) {
					n.setPv(n.getPvMax());
					n.setXp(n.getXp() - 0.2 * n.getXp());
				}
			});
			
		}
		if(this.player1.getTeam().firstElement().isKO()) {
			if(this.player1.getTeam().getListe().get(1).isKO() &&this.player1.getTeam().getListe().get(2).isKO() ) {
				this.player1.writeClient("encounter lose");
				this.player1.getTeam().getListe().forEach(n ->{
					n.setPv(n.getPvMax());
					n.setXp(n.getXp() - 0.2 * n.getXp());
				});
			
			}
		}
	}
	
	public void putAttackPoke() {
		Pokaimone courant = this.player1.getTeam().firstElement();
		int random = Function.myRandom(0, 100);
		if(random < 50)courant.setPv(courant.getPv() - this.pok.make_attack1(courant.getType()));
		else courant.setPv(courant.getPv() - this.pok.make_attack2(courant.getType()));
	}
	public Players getPlayer1() {
		return player1;
	}
	public void setPlayer1(Players player1) {
		this.player1 = player1;
	}
	public Players getPlayer2() {
		return player2;
	}
	public void setPlayer2(Players player2) {
		this.player2 = player2;
	}
	public Pokaimone getPok() {
		return pok;
	}
	public void setPok(Pokaimone pok) {
		this.pok = pok;
	}

	
	
	
}
