package project8;

import java.util.Random;
import java.util.concurrent.locks.Lock;

public class ThreadA implements Runnable {

	private PlayerData PlayerA;
	SharingData sharingdata;
	Thread threadC;
	
	public ThreadA(SharingData sharingData, PlayerData PlayerA, Thread threadC) {
		this.PlayerA = PlayerA;
		this.sharingdata = sharingData;
		this.threadC = threadC;
	}
	
	@Override
	public void run() {
		// TODO Auto-generated method stub
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
					PlayerA.setSleepTime(randomtime);
					
					//产生新的character
					PlayerA.setResult((char)('a' + random.nextInt(26)));
					
					//通知线程C该线程已经完成该回合
					PlayerA.setReady(true);
					
					sharingdata.lock.notifyAll();
				}
			}
			threadC.join();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

}
