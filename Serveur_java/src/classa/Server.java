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
    private static final String SEARCH_SERVER = "looking for poketudiant servers";
	private static final String ANSWER_SEARCH_SERVER = "i'm a poketudiant server";

	private DatagramSocket socketudp;
	private InetSocketAddress addr;
    private byte[] receiveData = new byte[1024];
	private ArrayList<Game> listGame;

	private Players[] listPlayers;
	private int index; 
	
	private Thread serverUDP;
	private Thread serverTCP;
	
	private class serverUDP extends Thread{

		@Override
		public void run() {
			
			
		}
		
	}
	private class serverTCP extends Thread{

		@Override
		public void run() {
			// TODO Auto-generated method stub
			
		}
		
	}
	
	public Server() {
		try {
			
            sockettcp = new ServerSocket(PORTTCP);
            //socketudp = new DatagramSocket(PORTUDP);
			index = 0;
			listGame = new ArrayList<Game>();
			listPlayers = new Players[10];
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public Socket accept() throws IOException {
		return sockettcp.accept();
	}

	@Override
	public void close() throws IOException {
        sockettcp.close();
       // socketudp.close();
	}

    @Override
	public String receive() {
		DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
		try {
			socketudp.receive(receivePacket);
			addr = new InetSocketAddress(receivePacket.getAddress(), receivePacket.getPort());
			return new String(receivePacket.getData(),0,SEARCH_SERVER.length());
		} catch (IOException e) {
			e.printStackTrace();
			if (!socketudp.isClosed()) {
				socketudp.close();
			}
		}
		return null;

	}

	@Override
	public void send(String msg) {
		try {
			byte[] sendData = msg.getBytes();
			DatagramPacket datagramPacket = new DatagramPacket(sendData, sendData.length, addr.getAddress(),
					addr.getPort());
			socketudp.send(datagramPacket);
		} catch (IOException e) {
			if (!socketudp.isClosed()) {
				socketudp.close();
			}
			e.printStackTrace();
		}
	}
	/**
	 * @param args
	 */
	
	public static void main(String[] args) {
		int nb = 0;
		
		try (Server s = new Server()) {
			//s.run();
			System.out.println("DEBUG :SERVER START");
			int i=0;
			for(;;){
				/*
				String msg = s.receive();
				System.out.println("Message reçu: " + msg);
				if (SEARCH_SERVER.equals(msg)) {
					s.send(ANSWER_SEARCH_SERVER);
				} else {
					s.send("pas un client poketudiant");
				}*/
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


}