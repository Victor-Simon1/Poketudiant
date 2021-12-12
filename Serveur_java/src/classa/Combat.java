package classa;



public class Combat {
    private Players player1;
    private Players player2;
    private String actionP1;
    private String actionp2;
    private Pokaimone pok;
    private int XpTotal;
    private int[] changePok;
    public Combat(Players pokaimone, Players pokaimone2) {
		// TODO Auto-generated constructor stub
		this.player1 = pokaimone;
		this.player2 = pokaimone2;
		this.changePok = new int[4];
	}
    public Combat(Players pokaimone, Pokaimone  pokaimone2) {
		// TODO Auto-generated constructor stub
		this.player1 = pokaimone;
		this.pok= pokaimone2;
		this.XpTotal = 25;
		this.changePok = new int[2];
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
		int count = 0;
		String atk[];
		if(this.actionP1 != ""&& this.actionp2 != "") {
			if(this.actionP1.contains("attack") && this.actionp2.contains("attack")) {
				 this.player2.getTeam().firstElement().setPv( this.player2.getTeam().firstElement().getPv() -this.player1.getTeam().firstElement().makeDamage(this.player2.getTeam().firstElement().make_attack1(this.player2.getTeam().firstElement().getType()),this.player2.getTeam().firstElement()));
				 this.player1.getTeam().firstElement().setPv( this.player1.getTeam().firstElement().getPv() -this.player2.getTeam().firstElement().makeDamage(this.player1.getTeam().firstElement().make_attack1(this.player1.getTeam().firstElement().getType()),this.player1.getTeam().firstElement()));
			}
			else if(this.actionP1.contains("switch") && this.actionp2.contains("attack")) {
				if(this.changePok[0] == -1) {
					this.player1.writeClient("encounter enter action");
				}
				else {
					if(this.changePok[1] == -1) {
						this.player1.writeClient("encounter enter action");
					}
					else {
						this.player1.getTeam().echanger(this.changePok[0], this.changePok[1]);
						this.changePok[0] = -1;
						this.changePok[1] = -1;
						this.actionP1 = "";
						atk = this.actionp2.split(" ");
						this.player2.getTeam().firstElement().makeDamage(atk[1].charAt(0), this.player1.getTeam().firstElement());
					}
				}
			}
			else if(this.actionP1.contains("attack") && this.actionp2.contains("switch")) {
			
				if(this.changePok[2] == -1) {
					this.player2.writeClient("encounter enter action");
				}
				else {
					if(this.changePok[3] == -1) {
						this.player2.writeClient("encounter enter action");
					}
					else {
						this.player2.getTeam().echanger(this.changePok[2], this.changePok[3]);
						this.changePok[2] = -1;
						this.changePok[3] = -1;
						this.actionp2 = "";
					}
				}
			}
			else if(this.actionP1.contains("switch") && this.actionp2.contains("switch")) {
				if(this.changePok[0] == -1) {
					this.player1.writeClient("encounter enter action");
				}
				else {
					if(this.changePok[1] == -1) {
						this.player1.writeClient("encounter enter action");
					}
					else {
						this.player1.getTeam().echanger(this.changePok[0], this.changePok[1]);
						this.changePok[0] = -1;
						this.changePok[1] = -1;
						this.actionP1 = "";
					}
				}
				if(this.changePok[2] == -1) {
					this.player2.writeClient("encounter enter action");
				}
				else {
					if(this.changePok[3] == -1) {
						this.player2.writeClient("encounter enter action");
					}
					else {
						this.player2.getTeam().echanger(this.changePok[2], this.changePok[3]);
						this.changePok[2] = -1;
						this.changePok[3] = -1;
						this.actionp2 = "";
					}
				}
				
			}
			
		}
		else if(this.actionP1 == ""&& this.actionp2 == "") {
			this.player1.writeClient("encounter enter action");
			this.player2.writeClient("encounter enter action");
		}
		
		for(Pokaimone  l :this.player1.getTeam().getListe()) {
			if(l.isKO())count++;
		}
		if(count == this.player1.getTeam().getListe().size()) {
			this.player1.writeClient("encounter win");
			this.player2.writeClient("encounter lose");
			for(Pokaimone  l :this.player1.getTeam().getListe()) {
				l.setPv(l.getPvMax());
				l.setXp(l.getXp() - 0.2 * l.getXp());
			}
			
		}
		
		for(Pokaimone  l :this.player2.getTeam().getListe()) {
			if(l.isKO())count++;
		}
		if(count == this.player2.getTeam().getListe().size()) {
			this.player2.writeClient("encounter win");
			this.player1.writeClient("encounter lose");
			for(Pokaimone  l :this.player2.getTeam().getListe()) {
				l.setPv(l.getPvMax());
				l.setXp(l.getXp() - 0.2 * l.getXp());
			}
		}
		
	}
	
	public void deroulementCombat1Pok() {
		String info[];
		if(this.actionP1 != "") {
			if(this.actionP1.contains("attack") ) {
				//this.player1.getTeam().firstElement().setPv( this.player1.getTeam().firstElement().getPv() -this.player2.getTeam().firstElement().makeDamage(this.player1.getTeam().firstElement().make_attack1(this.player1.getTeam().firstElement().getType()),this.player1.getTeam().firstElement()));
				info =this.actionP1.split(" ");
				if(info[1].charAt(0) == 1) {
					this.pok.setPv(this.player1.getTeam().firstElement().makeDamage(1, this.pok));
				}
				else {
					this.pok.setPv(this.player1.getTeam().firstElement().makeDamage(2, this.pok));
				}
				this.actionP1 = "";
				
			}
			else if(this.actionP1.contains("switch")) {
				if(this.changePok[0] == -1) {
					this.player1.writeClient("encounter enter action");
				}
				else {
					if(this.changePok[1] == -1) {
						this.player1.writeClient("encounter enter action");
					}
					else {
						this.player1.getTeam().echanger(this.changePok[0], this.changePok[1]);
					}
				}
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
		if(random < 50)courant.setPv(courant.getPv() - this.pok.makeDamage(1,courant));
		else courant.setPv(courant.getPv() -  this.pok.makeDamage(2,courant));
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
