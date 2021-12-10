package classa;

public enum Attack {
	BAVARDAGE(Type.NOISY,10),GROBOUCAN(Type.NOISY,15),MEGAPHONE_VOCAL(Type.NOISY,20),
	BAILLEMENT(Type.LAZY,10),PTI_SOMME(Type.LAZY,15),SUPERDODO(Type.LAZY,20),RATELETTRAIN(Type.LAZY,15),
	OBOULO(Type.MOTIVATED,10),EXO_MAISON(Type.MOTIVATED,15),MAX_REVIZ(Type.MOTIVATED,20),
	TIT_QUESTION(Type.TEACHER,10),POSER_COLLE(Type.TEACHER,15),FATAL_INTERRO(Type.TEACHER,20);
	
	Type type =null;
	int power = -1;
	Attack(Type pType, int pPower) {
		this.type = pType;
		this.power = pPower;
	}
}
