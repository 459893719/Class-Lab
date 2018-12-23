package project8;

import java.util.Random;

/**
 * 
* @ClassName: ThreadB
* @Description: 线程B对应的线程类, 继承Thread类
* @author Orion
* @date 2018年12月22日
*
 */
public class ThreadB extends Thread {

	private PlayerData PlayerB;       //线程B的数据
	private SharingData sharingdata;  //线程间共享的数据
	private Thread threadC;           //线程C的引用
	
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
				
				//线程B睡眠和产生字母的过程中, 没有其他线程执行
				synchronized (sharingdata.lock) {
					//保证线程B在线程C结束打印结果这一过程之后, 才开始新一回合
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
			//线程B阻塞, 等待线程C结束
			threadC.join();
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
