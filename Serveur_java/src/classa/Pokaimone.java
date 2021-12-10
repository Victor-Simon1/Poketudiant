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
	private double xp;
	private double xpMax;
	private int lvl;
	private Attack attack1;
	private Attack attack2;
	private Combat combat;
	protected int timer;
	private int x;
	private int y;
	private Pokaimone[] pok;
	public Pokaimone(String pName,Type pType,boolean pIsCatchable,String pEvolution
			,int pAttaque,int pDefense, int pPvMax) {
		
		
		this.name = pName;
		this.type = pType;
		this.isCatchable = pIsCatchable;
		this.evolution = pEvolution;
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
		this.pok = new Pokaimone[2];

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
	private void capturePokaimone(Pokaimone p) {
		if(this.type == Type.TEACHER) {
			if(this.team.pok1 == null) {
				this.team.pok1 = p;
			}
			else if(this.team.pok2 == null) {
				this.team.pok1 = p;
			}
		}
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
		
		if(if(this.type != Type.TEACHER) {
			while(this.type == Attack.values()[random].type ) {
				random = (int) (0 + Math.random() * (attack1.ordinal() -0)) ;
				//System.out.println("BOUVLE PTN");
			}
		}
		
		this.attack1 = Attack.values()[random];
	}
	
	public int makeDamage(int power,Pokaimone p){
		return (float)(myRandom(90,101)/100) * this.att / p.getDef() * power;
	}
	private int make_attack1(Type def) {
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
	
	private int make_attack2(Type def) {
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
		this.Xp = Xp
		if(this.Xp > this.xpMax){
			this.Xp = this.Xp - this.xpMax;
			this.lvl++;
		}

	}
	public double getXp(){
		return this.Xp;
	}

	private double setXPMax(){
		return 500 * ((1+ this.lvl) /2);
	}
	public boolean attemptCatch(Pokaimone p){
		int random = myRandom(0,100);
		int probaCatch = 2 * Math.max(0.5 -P.getPv()/p.getpvMax(),0);

		return random <probaCatch;
	}
	
	public boolean tentativeFuite(Pokaimone p){
		boolean fuite = true;
		int probaFuite = myRandom(0,100);
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
}
