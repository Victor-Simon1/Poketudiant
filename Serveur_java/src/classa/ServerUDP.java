package classa;

import java.io.Closeable;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetSocketAddress;
import java.net.SocketException;

public class ServerUDP extends Thread  implements Communicate,Closeable{
	
	 private static final String SEARCH_SERVER = "looking for poketudiant servers";
	private static final String ANSWER_SEARCH_SERVER = "i'm a poketudiant server";
	private DatagramSocket socketudp;
	  private byte[] receiveData = new byte[1024];
	private int PORTUDP = 9000;
	private InetSocketAddress addr;
	public ServerUDP() {
		try {
			socketudp = new DatagramSocket(PORTUDP);
		} catch (SocketException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public void run() {
		//try(ServerUDP s = new ServerUDP()){
		System.out.println("Debut UDP");
			for(;;) {
				
				String msg = this.receive();
				System.out.println("Message reçu: " + msg);
				if (SEARCH_SERVER.equals(msg)) {
					this.send(ANSWER_SEARCH_SERVER);
				} else {
					this.send("pas un client poketudiant");
				}
				
			}
			//s.close();
			
		//} catch (IOException e) {
			// TODO Auto-generated catch block
		//	e.printStackTrace();
		//}
	//
	}
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

	@Override
	public void close() throws IOException {
		// TODO Auto-generated method stub
		
	}
}
