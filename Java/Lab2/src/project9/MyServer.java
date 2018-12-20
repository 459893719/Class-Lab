package project9;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Arrays;



public class MyServer {
	public static void main(String[] args) {
		try {
			ServerSocket serverSocket = new ServerSocket(8888);
			Socket socket = serverSocket.accept();
			DataOutputStream out = null;
			System.out.println("accept");
			DatagramSocket socket2 = new DatagramSocket(8000);
			byte[] buf = new byte[256];
			DatagramPacket sndPacket = new DatagramPacket(buf, buf.length);
			DatagramPacket rcvPacket = new DatagramPacket(buf, buf.length);
			socket2.receive(rcvPacket);
			InetAddress address = rcvPacket.getAddress();
			int port = rcvPacket.getPort();
			sndPacket.setAddress(address);
			sndPacket.setPort(port);
			
			
			for(int i=0;i<9;i++) {
				
				out = new DataOutputStream(socket.getOutputStream());
				out.writeInt(0);
				
				DataInputStream in = new DataInputStream(socket.getInputStream());
				int sleepTimeA = in.readInt();
				int selectionA = in.readInt();
				System.out.println("A: " + sleepTimeA + " " + StringMap.stringmap[selectionA]);
				
				//将内容放到buf中
				Arrays.fill(buf, (byte)0);
				sndPacket.setData(buf, 0, buf.length);
				socket2.send(sndPacket);
				
				rcvPacket.setData(buf);
				socket2.receive(rcvPacket);
				String content = new String(buf);
				String[] contentlist = content.split(" ");
				int sleepTimeB = Integer.parseInt(contentlist[0]);
				int selectionB = Integer.parseInt(contentlist[1]);
				System.out.println("B: " + sleepTimeB + " " + StringMap.stringmap[selectionB]);
				
			}
			out.writeInt(1);
			
			Arrays.fill(buf, (byte)0);
			buf[0] = (byte)1;
			
			
			serverSocket.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
