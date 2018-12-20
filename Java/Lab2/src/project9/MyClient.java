package project9;

import java.io.DataInputStream;
import java.io.DataOutput;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.Socket;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.util.Arrays;
import java.util.Random;
import java.util.Scanner;

public class MyClient {
	public static void main(String[] args) {
		new Thread(new ThreadA()).start();
		new Thread(new ThreadB()).start();
	}
}

class ThreadA implements Runnable{

	@Override
	public void run() {
		// TODO Auto-generated method stub
		try {
			Socket socket = new Socket("localhost", 8888);
			Random random = new Random();
			while(true){
				DataInputStream in = new DataInputStream(socket.getInputStream());
				int isEnd = in.readInt();
				System.out.println(isEnd);
				if(isEnd == 1) {
					break;
				}
				
				int sleepTimeA = random.nextInt(1001);
				Thread.sleep(sleepTimeA);
				int selectionA = random.nextInt(3);
				DataOutputStream out = new DataOutputStream(socket.getOutputStream());
				out.writeInt(sleepTimeA);
				out.writeInt(selectionA);
				
			}
			socket.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}

class ThreadB implements Runnable{

	@Override
	public void run() {
		// TODO Auto-generated method stub
		try {
			DatagramSocket socket = new DatagramSocket();
			byte[] buf = new byte[256];
			DatagramPacket rcvPacket = new DatagramPacket(buf, buf.length);
			InetAddress address = InetAddress.getByName("localhost");
			DatagramPacket sndPacket = new DatagramPacket(buf, buf.length, address, 8000);
			Random random = new Random();
			
			buf = "ready".getBytes();
			sndPacket.setData(buf);
			socket.send(sndPacket);
			
			while(true) {
				Arrays.fill(buf, (byte)0);
				rcvPacket.setData(buf);
				socket.receive(rcvPacket);
				
				if(buf[0] == 1) {
					break;
				}
				
				
				
				//发送数据
				int sleepTimeB = random.nextInt(1001);
				Thread.sleep(sleepTimeB);
				int selectionB = random.nextInt(3);
				String content = sleepTimeB + " " + selectionB + " ";
//				System.out.println(content);
				buf = content.getBytes();
				sndPacket.setData(buf);
				socket.send(sndPacket);
				
			}
			socket.close();
		} catch (SocketException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (UnknownHostException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
}