package classa;


/**
 * 
 */


import java.io.BufferedReader;
import java.io.Closeable;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Server implements Communicate, Runnable, Closeable {
	private final static int PORTUDP = 9000;
	private final static int PORTTCP = 9001;
	private ServerSocket sockettcp;
   

	private DatagramSocket socketudp;
	private InetSocketAddress addr;
    private byte[] receiveData = new byte[1024];
	private ArrayList<Game> listGame;

	private Players[] listPlayers;
	private int index; 
	

	private ServerUDP serverUDP;
	

	
	public Server() {
		try {
			sockettcp = new ServerSocket(PORTTCP);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	
		//this.serverTCP = new ServerTCP();
		this.serverUDP = new ServerUDP();
		index = 0;
		listGame = new ArrayList<Game>();
		listPlayers = new Players[10];
	}

	public Socket accept() throws IOException {
		return sockettcp.accept();
	}

	@Override
	public void close() throws IOException {
        sockettcp.close();
       // socketudp.close();
	}
    

	/**
	 * @param args
	 */
	
	public static void main(String[] args) {
		int nb = 0;
		
		try (Server s = new Server()) {
			//s.run();
			
			System.out.println("DEBUG :SERVER START TCP");
			int i=0;
			s.serverUDP.start();
			for(;;){
				
				Socket client = s.accept();
				if(client != null){
					
					
					s.listPlayers[i] = new Players(client,s);
					System.out.println("slt");
					s.listPlayers[i].start();
					System.out.println("New Players");
					i++;
					nb++;
					/*
					for(int j=0;j<i;j++){
						if(s.listPlayers[j].isAlive())nb++;;
					}*/
					if(nb == 0)break;
				}
			}
			//for(;;){

           	s.close();
           	System.out.println("DEBUG :SERVER CLOSE");
            
		} catch (IOException e) {
			e.printStackTrace();
		}
		//Map map = new Map();
	

	}

	@Override
	public void run() {
		// TODO Auto-generated method stub
		
	}

	public ArrayList<Game> getListGame() {
		return this.listGame;
	}

	public void setListGame(Game g){
		this.listGame.add(g);
	}

	@Override
	public String receive() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public void send(String msg) {
		// TODO Auto-generated method stub
		
	}


}