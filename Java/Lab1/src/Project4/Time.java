package Project4;

import java.util.Calendar;
import java.util.Date;

public class Time {
	private int hour;
	private int minute;
	private int second;
	
	public Time() {
		Calendar c = Calendar.getInstance();
		hour = c.get(Calendar.HOUR_OF_DAY);
		minute = c.get(Calendar.MINUTE);
		second = c.get(Calendar.SECOND);
	}
	public Time(long millisecond) {
		Date date = new Date(millisecond);
		Calendar c = Calendar.getInstance();
		c.setTime(date);
		
		hour = c.get(Calendar.HOUR_OF_DAY);
		minute = c.get(Calendar.MINUTE);
		second = c.get(Calendar.SECOND);
	}
	public int getHour() {
		return hour;
	}
	public int getMinute() {
		return minute;
	}
	public int getSecond() {
		return second;
	}
	
}
