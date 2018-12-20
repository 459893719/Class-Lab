package project9;

public class PlayerData {
	private boolean isReady;
	private int result;
	private int sleepTime;
	private int totalPoints;
	
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
