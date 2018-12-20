package project8;

import javafx.application.Platform;
import javafx.collections.ObservableList;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;

public class ThreadC implements Runnable{
	
	private SharingData sharingdata;
	private PlayerData PlayerA, PlayerB;
	private ObservableList<Round> data;
	
	public ThreadC(SharingData sharingData, PlayerData PlayerA, PlayerData PlayerB, ObservableList<Round> data) {
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
					
					int pointa, pointb;
					//开始进行judge, 得到A和B在本回合中所得分数
					if(PlayerA.getResult() > PlayerB.getResult()) {
						pointa = 2; pointb = 0;
					}
					else if(PlayerA.getResult() < PlayerB.getResult()) {
						pointa = 0; pointb = 2;
					}
					else {
						pointa = pointb = 1;
					}
					PlayerA.setTotalPoints(PlayerA.getTotalPoints() + pointa);
					PlayerB.setTotalPoints(PlayerB.getTotalPoints() + pointb);
					
					//将表格信息打印出来
					data.add(new Round(
							String.valueOf(sharingdata.round), 
							String.valueOf(PlayerA.getSleepTime()) + "ms", 
							String.valueOf(PlayerA.getResult()), 
							String.valueOf(pointa),
							String.valueOf(PlayerB.getSleepTime()) + "ms", 
							String.valueOf(PlayerB.getResult()), 
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
