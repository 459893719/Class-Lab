package project8;

import java.util.Random;

/**
 * 
* @ClassName: ThreadA
* @Description: 线程A对应的线程类, 实现了Runnable接口
* @author Orion
* @date 2018年12月22日
*
 */
public class ThreadA implements Runnable {

	private PlayerData PlayerA;   //线程A的数据
	SharingData sharingdata;      //线程之间的共享数据
	Thread threadC;               //线程C的引用
	
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
				//线程A睡眠和产生字母的过程中, 没有其他线程执行
				synchronized (sharingdata.lock) {
					//保证线程A在线程C结束打印结果这一过程之后, 才开始新一回合 
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
			//线程A阻塞, 等待线程C结束
			threadC.join();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

}
