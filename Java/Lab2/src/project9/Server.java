package project9;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Arrays;

import javafx.application.Platform;
import javafx.collections.ObservableList;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;

/**
 * 
* @ClassName: Server
* @Description: 将客户端产生的数据进行判断比较, 并将结果打印出来
* @author Orion
* @date 2018年12月22日
*
 */
public class Server implements Runnable{
	private SharingData sharingdata;     //线程间的共享数据
	private PlayerData PlayerA, PlayerB; //线程A, B的数据
	private ObservableList<Round> data;  //表格的数据
	public Server(SharingData sharingData, PlayerData PlayerA, PlayerData PlayerB, ObservableList<Round> data) {
		this.sharingdata = sharingData;
		this.PlayerA = PlayerA;
		this.PlayerB = PlayerB;
		this.data = data;
	}

	@Override
	public void run() {
		try {
			for(int i=1;i<=sharingdata.totalRound;i++) {
				//round值是共享变量, 因此要保证互斥访问
				synchronized (sharingdata.lock) {
					//更新Round值
					sharingdata.round = i;
					sharingdata.lock.notifyAll();
					
				}
				//打印结果这一过程是互斥的, 其他两个线程不能访问
				synchronized (sharingdata.lock) {
					//等待线程A和线程B都已经结束回合
					while(!(PlayerA.isReady() && PlayerB.isReady())) {
						sharingdata.lock.wait();
					}
					
					int pointa = 0, pointb = 0;
					//开始进行judge, 得到A和B在本回合中所得分数
					pointa = StringMap.pointmap[PlayerA.getResult()][PlayerB.getResult()];
					pointb = StringMap.pointmap[PlayerB.getResult()][PlayerA.getResult()];
					
					PlayerA.setTotalPoints(PlayerA.getTotalPoints() + pointa);
					PlayerB.setTotalPoints(PlayerB.getTotalPoints() + pointb);
					
					//将表格信息打印出来
					data.add(new Round(
							String.valueOf(sharingdata.round), 
							String.valueOf(PlayerA.getSleepTime()) + "ms", 
							StringMap.stringmap[PlayerA.getResult()], 
							String.valueOf(pointa),
							String.valueOf(PlayerB.getSleepTime()) + "ms", 
							StringMap.stringmap[PlayerB.getResult()], 
							String.valueOf(pointb)));
					
					//开启下一回合, 初始化线程的信号量
					PlayerA.setReady(false);
					PlayerB.setReady(false);
					
					sharingdata.lock.notifyAll();
				}
				
			}
			//所有回合已经结束, 打印最后的结果
			Platform.runLater(() -> {
				
				Alert resultDialog = new Alert(AlertType.INFORMATION);
				resultDialog.setHeaderText(null);
				resultDialog.setTitle("结果");
				String content = "A的得分为:   " + PlayerA.getTotalPoints() 
				+ "\nB的得分为:   " + PlayerB.getTotalPoints();
				if(PlayerA.getTotalPoints() > PlayerB.getTotalPoints()) {
					content += "\nA赢得了比赛!";
				}
				else if(PlayerA.getTotalPoints() < PlayerB.getTotalPoints()) {
					content += "\nB赢得了比赛!";
				}
				else {
					content += "\n两方战成平局!";
				}
				resultDialog.setContentText(content);
				resultDialog.showAndWait();
			});
			
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
}

/**
 * 
* @ClassName: TCPHandler
* @Description: 接收使用TCP协议发送过来的数据
* @author Orion
* @date 2018年12月22日
*
 */
class TCPHandler implements Runnable{
	private PlayerData PlayerA;  //线程A的数据
	SharingData sharingdata;     //线程之间的共享数据
	
	public TCPHandler(SharingData sharingData, PlayerData PlayerA) {
		this.PlayerA = PlayerA;
		this.sharingdata = sharingData;
	}
	@Override
	public void run() {
		// TODO Auto-generated method stub
		try {
			//TCP的服务端监听8888端口, 并等待客户端连接
			ServerSocket serverSocket = new ServerSocket(8888);
			Socket socket = serverSocket.accept();
			DataOutputStream out = null;
			for(int i=1;i<=sharingdata.totalRound;i++) {
				//线程A睡眠和产生选择的过程中, 没有其他线程执行
				synchronized (sharingdata.lock) {
					//保证线程A在线程C结束打印结果这一过程之后, 才开始新一回合 
					while(sharingdata.round != i) {
						sharingdata.lock.wait();
					}
				
					//向客户端发送信息, 通知客户端可以进行该回合
					out = new DataOutputStream(socket.getOutputStream());
					out.writeInt(0);
					
					//开始接收客户端的数据
					DataInputStream in = new DataInputStream(socket.getInputStream());
					int sleepTimeA = in.readInt();
					int selectionA = in.readInt();
					//记录sleep的时间
					PlayerA.setSleepTime(sleepTimeA);
					
					//设置该回合用户A的选择
					PlayerA.setResult(selectionA);
					
					//通知线程C该线程已经完成该回合
					PlayerA.setReady(true);
					sharingdata.lock.notifyAll();
				}
			}
			//向客户端发送消息, 通知所有的回合已经结束, 可以结束程序
			out.writeInt(1);
			//关闭端口
			serverSocket.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
	
}

/**
 * 
* @ClassName: UDPHandler
* @Description: 接收使用UDP协议发送过来的数据
* @author Orion
* @date 2018年12月23日
*
 */
class UDPHandler implements Runnable{
	private PlayerData PlayerB;      //线程B的数据
	private SharingData sharingdata; //线程间共享的数据
	
	public UDPHandler(SharingData sharingData, PlayerData PlayerB) {
		this.PlayerB = PlayerB;
		this.sharingdata = sharingData;
	}
	
	@Override
	public void run() {
		// TODO Auto-generated method stub
		try {
			//UDP的服务端监听8000端口
			DatagramSocket socket2 = new DatagramSocket(8000);
			//定义UDP传输的数据缓冲区
			byte[] buf = new byte[256];
			DatagramPacket sndPacket = new DatagramPacket(buf, buf.length);
			DatagramPacket rcvPacket = new DatagramPacket(buf, buf.length);
			//服务端首先接收一次客户端的数据, 以获得客户端的地址和端口
			socket2.receive(rcvPacket);
			InetAddress address = rcvPacket.getAddress();
			int port = rcvPacket.getPort();
			//设置发送数据包的目标地址和端口
			sndPacket.setAddress(address);
			sndPacket.setPort(port);
			
			
			for(int i=1;i<=sharingdata.totalRound;i++) {
				//线程B睡眠和产生选择的过程中, 没有其他线程执行
				synchronized (sharingdata.lock) {
					//保证线程B在线程C结束打印结果这一过程之后, 才开始新一回合
					while(sharingdata.round != i) {
						sharingdata.lock.wait();
					}
					
					//向客户端发送信息, 通知客户端可以进行该回合, 将要发送的信息放到buf中
					Arrays.fill(buf, (byte)0);
					sndPacket.setData(buf, 0, buf.length);
					socket2.send(sndPacket);
					
					//接收客户端发来的数据
					rcvPacket.setData(buf);
					socket2.receive(rcvPacket);
					//客户端发来的数据是一个存有两个int值的字符串, 将这两个int提取出来
					String content = new String(buf);
					String[] contentlist = content.split(" ");
					int sleepTimeB = Integer.parseInt(contentlist[0]);
					int selectionB = Integer.parseInt(contentlist[1]);
					
					//记录sleep的时间
					PlayerB.setSleepTime(sleepTimeB);
					
					//设置线程B的选择
					PlayerB.setResult(selectionB);
					
					//通知线程C该线程已经完成该回合
					PlayerB.setReady(true);
					sharingdata.lock.notifyAll();
				}
				
			}
			//向客户端发送消息, 通知所有的回合已经结束, 可以结束程序
			Arrays.fill(buf, (byte)0);
			buf[0] = (byte)1;
			socket2.send(sndPacket);
			socket2.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
	
}
