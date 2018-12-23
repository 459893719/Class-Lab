package project9;

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
	private final SimpleStringProperty ARandomSelection;
	private final SimpleStringProperty APoints;
	private final SimpleStringProperty BSleepTime;
	private final SimpleStringProperty BRandomSelection;
	private final SimpleStringProperty BPoints;
	
	public Round(String roundnum, String ASleepTime, String ARandomSelection, String APoints, 
			String BSleepTime, String BRandomSelection, String BPoints) {
		this.roundNum = new SimpleStringProperty(roundnum);
		this.ASleepTime = new SimpleStringProperty(ASleepTime);
		this.APoints = new SimpleStringProperty(APoints);
		this.ARandomSelection = new SimpleStringProperty(ARandomSelection);
		this.BPoints = new SimpleStringProperty(BPoints);
		this.BRandomSelection = new SimpleStringProperty(BRandomSelection);
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

	public String getARandomSelection() {
		return ARandomSelection.get();
	}
	
	public void setARandomSelection(String ARandomSelection) {
		this.ARandomSelection.set(ARandomSelection);
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

	public String getBRandomSelection() {
		return BRandomSelection.get();
	}
	
	public void setBRandomSelection(String BRandomSelection) {
		this.BSleepTime.set(BRandomSelection);
	}

	public String getBPoints() {
		return BPoints.get();
	}
	
	public void setBPoints(String BPoints) {
		this.BPoints.set(BPoints);
	}
}
