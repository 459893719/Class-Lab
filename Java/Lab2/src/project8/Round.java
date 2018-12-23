package project8;

import javafx.beans.property.SimpleStringProperty;

/**
 * 
* @ClassName: Round
* @Description: 存放UI的表格中的表项数据
* @author Orion
* @date 2018年12月23日
*
 */
public class Round {
	private final SimpleStringProperty roundNum;
	private final SimpleStringProperty ASleepTime;
	private final SimpleStringProperty ARandomChar;
	private final SimpleStringProperty APoints;
	private final SimpleStringProperty BSleepTime;
	private final SimpleStringProperty BRandomChar;
	private final SimpleStringProperty BPoints;
	
	public Round(String roundnum, String ASleepTime, String ARandomChar, String APoints, 
			String BSleepTime, String BRandomChar, String BPoints) {
		this.roundNum = new SimpleStringProperty(roundnum);
		this.ASleepTime = new SimpleStringProperty(ASleepTime);
		this.APoints = new SimpleStringProperty(APoints);
		this.ARandomChar = new SimpleStringProperty(ARandomChar);
		this.BPoints = new SimpleStringProperty(BPoints);
		this.BRandomChar = new SimpleStringProperty(BRandomChar);
		this.BSleepTime = new SimpleStringProperty(BSleepTime);
		
		
	}

	public String getRoundNum() {
		return roundNum.get();
	}
	
	public void setRoundNum(String roundnum) {
		this.roundNum.set(roundnum);
	}

	public String getASleepTime() {
		return ASleepTime.get();
	}
	
	public void setASleepTime(String ASleepTime) {
		this.ASleepTime.set(ASleepTime);
	}

	public String getARandomChar() {
		return ARandomChar.get();
	}
	
	public void setARandomChar(String ARandomChar) {
		this.ARandomChar.set(ARandomChar);
	}

	public String getAPoints() {
		return APoints.get();
	}

	public void setAPoints(String APoints) {
		this.APoints.set(APoints);
	}
	
	public String getBSleepTime() {
		return BSleepTime.get();
	}
	
	public void setBSleepTime(String BSleepTime) {
		this.BSleepTime.set(BSleepTime);
	}

	public String getBRandomChar() {
		return BRandomChar.get();
	}
	
	public void setBRandomChar(String BRandomChar) {
		this.BSleepTime.set(BRandomChar);
	}

	public String getBPoints() {
		return BPoints.get();
	}
	
	public void setBPoints(String BPoints) {
		this.BPoints.set(BPoints);
	}
}
