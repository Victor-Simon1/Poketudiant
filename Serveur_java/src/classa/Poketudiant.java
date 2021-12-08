package classa;


public enum Poketudiant {

	Parlfor("Parlfor",Type.NOISY,true,null),
	
	Rigolamor("Rigolamor",Type.NOISY,true,null),
	Ismar("Ismar",Type.NOISY,true,Poketudiant.Rigolamor),
	Procrastino("Procrastino",Type.LAZY,true,null),
	
	Nuidebou("Parlfor",Type.LAZY,true,null),
	Couchtar("Parlfor",Type.LAZY,true,Poketudiant.Nuidebou),
	Alabarre("Parlfor",Type.LAZY,false,null),
	Buchafon("Parlfor",Type.MOTIVATED,true,null),
	
	Promomajor("Parlfor",Type.MOTIVATED,false,null),
	Belmention("Parlfor",Type.MOTIVATED,true,Poketudiant.Promomajor),
	Enseignant_dresseur("Parlfor",Type.TEACHER,false,null)
	;
	
	String name;
	Type type;
	boolean isCapturable;
	Poketudiant evolution;

	Poketudiant(String name, Type type, boolean isCapturable, Poketudiant evolution) {
		this.name = name;
		this.type = type;
		this.isCapturable = isCapturable;
		this.evolution = evolution;
	}
}
