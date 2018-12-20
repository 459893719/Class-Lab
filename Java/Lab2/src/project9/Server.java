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

public class Server implements Runnable{
	private SharingData sharingdata;
	private PlayerData PlayerA, PlayerB;
	private ObservableList<Round> data;
	public Server(SharingData sharingData, PlayerData PlayerA, PlayerData PlayerB, ObservableList<Round> data) {
		this.sharingdata = sharingData;
		this.PlayerA = PlayerA;
		this.PlayerB = PlayerB;
		this.data = data;
	}

	@Override
	public void run() {
		// TODO Auto-generated method stub
		try {
			for(int i=1;i<=sharingdata.totalRound;i++) {
				synchronized (sharingdata.lock) {
					//更新Round值
					sharingdata.round = i;
					sharingdata.lock.notifyAll();
					
				}
				
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
					
					PlayerA.setReady(false);
					PlayerB.setReady(false);
					
					sharingdata.lock.notifyAll();
				}
				
			}
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
class TCPHandler implements Runnable{
	private PlayerData PlayerA;
	SharingData sharingdata;
	
	public TCPHandler(SharingData sharingData, PlayerData PlayerA) {
		this.PlayerA = PlayerA;
		this.sharingdata = sharingData;
	}
	@Override
	public void run() {
		// TODO Auto-generated method stub
		try {
			ServerSocket serverSocket = new ServerSocket(8888);
			Socket socket = serverSocket.accept();
			DataOutputStream out = null;
			System.out.println("accept");
			for(int i=1;i<=sharingdata.totalRound;i++) {
				synchronized (sharingdata.lock) {
					while(sharingdata.round != i) {
						sharingdata.lock.wait();
					}
				
					//开始接收数据
					out = new DataOutputStream(socket.getOutputStream());
					out.writeInt(0);
					
					DataInputStream in = new DataInputStream(socket.getInputStream());
					int sleepTimeA = in.readInt();
					int selectionA = in.readInt();
					//记录sleep的时间
					PlayerA.setSleepTime(sleepTimeA);
					
					//设置该回合用户A的选择
					PlayerA.setResult(selectionA);
					
					//通知线程C该线程已经完成该回合
					PlayerA.setReady(true);
					System.out.println("A: " + sleepTimeA + " " + StringMap.stringmap[selectionA]);
					
					sharingdata.lock.notifyAll();
				}
			}
			out.writeInt(1);
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

class UDPHandler implements Runnable{
	private PlayerData PlayerB;
	private SharingData sharingdata;
	
	public UDPHandler(SharingData sharingData, PlayerData PlayerB) {
		this.PlayerB = PlayerB;
		this.sharingdata = sharingData;
	}
	
	@Override
	public void run() {
		// TODO Auto-generated method stub
		try {
			DatagramSocket socket2 = new DatagramSocket(8000);
			byte[] buf = new byte[256];
			DatagramPacket sndPacket = new DatagramPacket(buf, buf.length);
			DatagramPacket rcvPacket = new DatagramPacket(buf, buf.length);
			socket2.receive(rcvPacket);
			InetAddress address = rcvPacket.getAddress();
			int port = rcvPacket.getPort();
			sndPacket.setAddress(address);
			sndPacket.setPort(port);
			
			
			for(int i=1;i<=sharingdata.totalRound;i++) {
				
				synchronized (sharingdata.lock) {
					while(sharingdata.round != i) {
						sharingdata.lock.wait();
					}
					
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
					
					//记录sleep的时间
					PlayerB.setSleepTime(sleepTimeB);
					
					//产生新的character
					PlayerB.setResult(selectionB);
					
					//通知线程C该线程已经完成该回合
					PlayerB.setReady(true);
					
					sharingdata.lock.notifyAll();
				}
				
			}
			Arrays.fill(buf, (byte)0);
			buf[0] = (byte)1;
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
