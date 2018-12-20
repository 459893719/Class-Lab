package project8;

import java.util.Random;

public class ThreadB extends Thread {

	private PlayerData PlayerB;
	private SharingData sharingdata;
	private Thread threadC;
	
	public ThreadB(SharingData sharingData, PlayerData PlayerB, Thread threadC) {
		this.PlayerB = PlayerB;
		this.sharingdata = sharingData;
		this.threadC = threadC;
	}
	
	@Override
	public void run() {
		try {
			Random random = new Random();
			for(int i=1;i<=sharingdata.totalRound;i++) {
				//保证线程A在线程C结束打印结果这一过程之后, 才开始新一回合
				synchronized (sharingdata.lock) {
					
					while(sharingdata.round != i) {
						sharingdata.lock.wait();
					}
					
					//开始新一轮, 首先执行sleep函数
					int randomtime = random.nextInt(1001);
					Thread.sleep(randomtime);
					
					//记录sleep的时间
					PlayerB.setSleepTime(randomtime);
					
					//产生新的character
					PlayerB.setResult((char)('a' + random.nextInt(26)));
					
					//通知线程C该线程已经完成该回合
					PlayerB.setReady(true);
					
					sharingdata.lock.notifyAll();
				}
			}
			threadC.join();
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
