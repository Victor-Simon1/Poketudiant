package classa;

import java.util.Random;

public class Function {
	
	public static int myRandom(int Min,int Max) {
		return Min + (int)(Math.random() * ((Max - Min) + 1));
	}

    public char myRandomChar() {// lettre aléatoire
    	Random r = new Random();
    	char c = (char)(r.nextInt(26) + 'a');
    	return  c;
	}

}
