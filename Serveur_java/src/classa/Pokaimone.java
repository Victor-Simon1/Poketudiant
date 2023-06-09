package classa;



public class Pokaimone {

	private String name;
	private Type type;
	private boolean isCatchable;
	private String evolution;
	private Teams team;
	private int attaque;
	private int defense;
	private int pvMax;
	private int pv;
	private boolean isKO;
	private double xp;
	private double xpMax;
	private int lvl;
	private Attack attack1;
	private Attack attack2;
	private Combat combat;
	protected int timer;
	private int x;
	private int y;

	public Pokaimone(String pName,Type pType,boolean pIsCatchable,String pEvolution
			,int pAttaque,int pDefense, int pPvMax) {
		
		
		this.name = pName;
		this.type = pType;
		this.isCatchable = pIsCatchable;
		this.evolution = pEvolution;
		this.isKO = false;
		//this.team = new Teams(this);
		this.attaque = applyCoeff(pAttaque);
		this.defense = applyCoeff(pDefense);
		this.pvMax = applyCoeff(pPvMax);
		this.pv = this.pvMax;
		this.chooseattack1();
		this.chooseattack2();
		
		this.lvl = 1;
		this.xp = 0;
		this.xpMax = setXPMax();
	
		

	}
	
	public Teams getTeam() {
		return team;
	}

	public void setTeam(Teams team) {
		this.team = team;
	}

	public boolean isKO() {
		return isKO;
	}

	public void setKO(boolean isKO) {
		this.isKO = isKO;
	}

	public boolean isCatchable() {
		return isCatchable;
	}

	public void setCatchable(boolean isCatchable) {
		this.isCatchable = isCatchable;
	}

	public String getEvolution() {
		return evolution;
	}

	public void setEvolution(String evolution) {
		this.evolution = evolution;
	}

	public Attack getAttack1() {
		return attack1;
	}

	public void setAttack1(Attack attack1) {
		this.attack1 = attack1;
	}

	public Attack getAttack2() {
		return attack2;
	}

	public void setAttack2(Attack attack2) {
		this.attack2 = attack2;
	}

	public Combat getCombat() {
		return combat;
	}


	public void passLvl() {
		this.attaque += (int)(this.attaque *0.1);
		this.defense += (int)(this.defense *0.1);
		this.pvMax += (int)(this.pvMax *0.1);
		this.pv = this.pvMax;
	}
	private int applyCoeff(int stats){
		return (int)(0.9 + Math.random() *(1.1 -0.9)) * stats;
	}
	
	public boolean collidePoketudiant(Pokaimone p) {
		boolean collide = false;
		if(p.getX() == this.getX() && p.getY() == this.getY()) {
			collide = true;
		}
		return collide;
	}
	public String infoPok(int i) {
		return this.team.liste.get(i).getName() + this.team.liste.get(i).getType() +
				this.team.liste.get(i).getLvl() + this.team.liste.get(i).getXp() +
				this.team.liste.get(i).getXpMax() + this.team.liste.get(i).getPv() + 
				this.team.liste.get(i).getPvMax() + this.team.liste.get(i).getAttaque() + 
				this.team.liste.get(i).getDefense() + this.team.liste.get(i).getAttack1().name()+ 
				this.team.liste.get(i).getAttack1().name(); 
	}
	
	public String infoPokOpponent(Pokaimone p) {
		return "encounter poketudiant opponent " + p.getName() + " " + p.getLvl() + " " + (p.getPv() / p.getPvMax());
	}
	private void capturePokaimone(Pokaimone p) {
		if(this.team.ajoutInTeam(p));
		/*if(this.type == Type.TEACHER) {
			if(this.team.pok1 == null) {
				this.team.pok1 = p;
			}
			else if(this.team.pok2 == null) {
				this.team.pok1 = p;
			}
		}*/
	}
	private void chooseattack1() {
		int random = 0;
		//for(int i=0;i<attack1.ordinal();i++) {
			if(this.type == Type.NOISY) {
				random = (int) (0 + Math.random() * (2 -0)) ;
			}
			else if(this.type == Type.LAZY) {
				random = (int) (3 + Math.random() * (6 -3)) ;
			}
			else if(this.type == Type.MOTIVATED) {
				random = (int) (7 + Math.random() * (9 -7)) ;
			}
			else if(this.type == Type.TEACHER) {
				random = (int) (10 + Math.random() * (12 -10)) ;
			}
		//}
		this.attack1 = Attack.values()[random];
	}
	private void chooseattack2(){
		int random = 0;
		random = (int) (0 + Math.random() * (attack1.ordinal() -0)) ;
		
		if(this.type != Type.TEACHER) {
			while(this.type == Attack.values()[random].type ) {
				random = (int) (0 + Math.random() * (attack1.ordinal() -0)) ;
				//System.out.println("BOUVLE PTN");
			}
		}
		
		this.attack1 = Attack.values()[random];
	}
	
	public int makeDamage(int power,Pokaimone p){
		return (int) ((float)(Function.myRandom(90,101)/100) * this.getAttaque() / p.getDefense() * power);
	}
	public int make_attack1(Type def) {
		if(this.attack1.type == Type.NOISY && def == Type.LAZY) {
			return this.attack1.power *2;
		}
		if(this.attack1.type == Type.LAZY && def == Type.MOTIVATED) {
			return this.attack1.power *2;
		}
		if(this.attack1.type == Type.MOTIVATED && def == Type.NOISY) {
			return this.attack1.power *2;
		}
		if(this.attack1.type == Type.TEACHER && def == Type.LAZY
				|| this.attack1.type == Type.TEACHER && def == Type.NOISY
			||	this.attack1.type == Type.TEACHER && def == Type.MOTIVATED) {
			return this.attack1.power *2;
		}
		return this.attack1.power;
	}
	
	public int make_attack2(Type def) {
		if(this.attack1.type == Type.NOISY && def == Type.LAZY) {
			return this.attack1.power *2;
		}
		if(this.attack1.type == Type.LAZY && def == Type.MOTIVATED) {
			return this.attack1.power *2;
		}
		if(this.attack1.type == Type.MOTIVATED && def == Type.NOISY) {
			return this.attack1.power *2;
		}
		if(this.attack1.type == Type.TEACHER && def == Type.LAZY
				|| this.attack1.type == Type.TEACHER && def == Type.NOISY
			||	this.attack1.type == Type.TEACHER && def == Type.MOTIVATED) {
			return this.attack1.power *2;
		}
		return this.attack1.power;
	}
	
	private float make_damage(int att,Pokaimone def) {
		float k = (float) (0.9 + Math.random() * (1.1 -0.9)) ;
		if(att == 1) {//si attack 1
			return k *(this.attaque / def.defense ) * make_attack1(def.type);
		}
		else { //attak 2
			return k *(this.attaque / def.defense ) * make_attack2(def.type);
		}
	}
	public void setXp(double Xp){
		this.xp = Xp;
		if(this.xp > this.xpMax){
			this.xp = this.xp - this.xpMax;
			this.lvl++;
		}

	}
	public double getXp(){
		return this.xp;
	}

	private double setXPMax(){
		return 500 * ((1+ this.lvl) /2);
	}
	
	public boolean attemptCatch(Pokaimone p){
		int random = Function.myRandom(0,100);
		int probaCatch = (int) (2 * Math.max(0.5 - p.getPv()/p.getPvMax(),0));

		return random <probaCatch;
	}
	
	public boolean tentativeFuite(Pokaimone p){
		boolean fuite = true;
		int probaFuite = Function.myRandom(0,100);
		if(this.lvl< p.getLvl()-3)fuite = false;
		else if(this.lvl< p.getLvl()-2)if(probaFuite<25)fuite = false;
		else if(this.lvl< p.getLvl()-2)if(probaFuite<40)fuite = false;
		else if(probaFuite<50)fuite = false;

		return fuite;
	}
	public int getX() {
		return x;
	}

	public void setX(int x) {
		this.x = x;
	}

	public int getY() {
		return y;
	}

	public void setY(int y) {
		this.y = y;
	}

	public void setCombat(Combat c) {
		// TODO Auto-generated method stub
		this.combat = c;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public Type getType() {
		return type;
	}

	public void setType(Type type) {
		this.type = type;
	}

	public int getAttaque() {
		return attaque;
	}

	public void setAttaque(int attaque) {
		this.attaque = attaque;
	}

	public int getDefense() {
		return defense;
	}

	public void setDefense(int defense) {
		this.defense = defense;
	}

	public int getPvMax() {
		return pvMax;
	}

	public void setPvMax(int pvMax) {
		this.pvMax = pvMax;
	}

	public int getPv() {
		return pv;
	}

	public void setPv(int pv) {
		if(pv <= 0) {
			this.pv = 0;
			this.isKO = true;
		}
		else this.pv = pv;
	}

	public double getXpMax() {
		return xpMax;
	}

	public void setXpMax(double xpMax) {
		this.xpMax = xpMax;
	}

	public int getLvl() {
		return lvl;
	}

	public void setLvl(int lvl) {
		this.lvl = lvl;
	}

	public int getTimer() {
		return timer;
	}

	public void setTimer(int timer) {
		this.timer = timer;
	}
}
