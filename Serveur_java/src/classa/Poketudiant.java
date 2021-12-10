package classa;


public enum Poketudiant {

	Parlfor("Parlfor",Type.NOISY,true,null,60,40,60),
	
	Rigolamor("Rigolamor",Type.NOISY,true,null,50,30,40),
	Ismar("Ismar",Type.NOISY,true,Poketudiant.Rigolamor,85,30,40),
	Procrastino("Procrastino",Type.LAZY,true,null,40,60,60),
	
	Nuidebou("Parlfor",Type.LAZY,true,null,55,85,40),
	Couchtar("Parlfor",Type.LAZY,true,Poketudiant.Nuidebou,30,50,40),
	Alabarre("Parlfor",Type.LAZY,false,null,75,95,65),
	Buchafon("Parlfor",Type.MOTIVATED,true,null,50,50,60),
	
	Promomajor("Parlfor",Type.MOTIVATED,false,null,70,70,70),
	Belmention("Parlfor",Type.MOTIVATED,true,Poketudiant.Promomajor,30,50,40),
	Enseignant_dresseur("Parlfor",Type.TEACHER,false,null,100,100,100)
	;
	
	String name;
	Type type;
	boolean isCapturable;
	Poketudiant evolution;
	int atk,def,pv;
	Poketudiant(String name, Type type, boolean isCapturable, Poketudiant evolution,int atk,int def,int pvMax) {
		this.name = name;
		this.type = type;
		this.isCapturable = isCapturable;
		this.evolution = evolution;
		this.atk =atk;
		this.def = def;
		this.pv = pvMax;
	}
}
