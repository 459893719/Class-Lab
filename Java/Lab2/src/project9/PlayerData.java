package project9;

/**
 * 
* @ClassName: PlayerData
* @Description: 存放线程A,B独有的一些数据
* @author Orion
* @date 2018年12月23日
*
 */
public class PlayerData {
	private boolean isReady;  //是否已经结束本回合, 方便线程同步
	private int result;       //产生的选择
	private int sleepTime;    //本次睡眠时间
	private int totalPoints;  //线程的总得分
	
	public PlayerData() {
		isReady = false;
		totalPoints = 0;
	}
	public int getSleepTime() {
		return sleepTime;
	}
	public int getResult() {
		return result;
	}
	public void setResult(int result) {
		this.result = result;
	}
	public void setSleepTime(int sleepTime) {
		this.sleepTime = sleepTime;
	}
	public int getTotalPoints() {
		return totalPoints;
	}
	public void setTotalPoints(int totalPoints) {
		this.totalPoints = totalPoints;
	}
	public boolean isReady() {
		return isReady;
	}
	public void setReady(boolean isReady) {
		this.isReady = isReady;
	}
}
