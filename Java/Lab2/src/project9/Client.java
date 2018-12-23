package project9;

import java.io.DataInputStream;
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

/**
 * 
* @ClassName: Client
* @Description: 执行两个客户端的线程
* @author Orion
* @date 2018年12月23日
*
 */
public class Client {
	public static void main(String[] args) {
		try {
			Thread threadA = new Thread(new ThreadA());
			Thread threadB = new Thread(new ThreadB());
			threadA.start();
			threadB.start();
			threadA.join();
			threadB.join();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}
}

/**
 * 
* @ClassName: ThreadA
* @Description: 客户端的线程A, 使用TCP发送数据到服务端
* @author Orion
* @date 2018年12月23日
*
 */
class ThreadA implements Runnable{

	@Override
	public void run() {

		try {
			//客户端与监听8888端口的服务端相连接
			Socket socket = new Socket("localhost", 8888);
			Random random = new Random();
			while(true){
				//获取服务端的确认信息, 以开始新的回合
				DataInputStream in = new DataInputStream(socket.getInputStream());
				int isEnd = in.readInt();
				//如果获得的是结束的信息, 则结束程序
				if(isEnd == 1) {
					break;
				}
				
				//产生随机的睡眠时间和选择
				int sleepTimeA = random.nextInt(1001);
				Thread.sleep(sleepTimeA);
				int selectionA = random.nextInt(3);
				DataOutputStream out = new DataOutputStream(socket.getOutputStream());
				//进行数据传输
				out.writeInt(sleepTimeA);
				out.writeInt(selectionA);
				
			}
			//关闭端口
			socket.close();
		} catch (IOException e) {
			e.printStackTrace();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}
}

/**
 * 
* @ClassName: ThreadB
* @Description: 客户端的线程B, 使用UDP发送数据到服务端
* @author Orion
* @date 2018年12月23日
*
 */
class ThreadB implements Runnable{

	@Override
	public void run() {
		try {
			//创建一个Socket
			DatagramSocket socket = new DatagramSocket();
			//定义数据传输的缓冲区
			byte[] buf = new byte[256];
			DatagramPacket rcvPacket = new DatagramPacket(buf, buf.length);
			//设置发送数据时, 服务端的地址和端口
			InetAddress address = InetAddress.getByName("localhost");
			DatagramPacket sndPacket = new DatagramPacket(buf, buf.length, address, 8000);
			Random random = new Random();
			
			//向服务端发送一段数据, 使服务端获得该客户端的地址和端口
			buf = "ready".getBytes();
			sndPacket.setData(buf);
			socket.send(sndPacket);
			
			while(true) {
				//获取服务端的确认信息, 以开始新的回合
				Arrays.fill(buf, (byte)0);
				rcvPacket.setData(buf);
				socket.receive(rcvPacket);
				
				//如果获得的是结束的信息, 则结束程序
				if(buf[0] == 1) {
					break;
				}
				
				//产生随机的睡眠时间和选择
				int sleepTimeB = random.nextInt(1001);
				Thread.sleep(sleepTimeB);
				int selectionB = random.nextInt(3);
				
				//将两个int值装入一个String中, 进行数据传输
				String content = sleepTimeB + " " + selectionB + " ";
				buf = content.getBytes();
				sndPacket.setData(buf);
				socket.send(sndPacket);
				
			}
			//关闭端口
			socket.close();
		} catch (SocketException e) {
			e.printStackTrace();
		} catch (UnknownHostException e) {
			e.printStackTrace();
		} catch (InterruptedException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
}