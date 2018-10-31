package Project4;

public class Main {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Time time = new Time();
		System.out.println(time.getHour() + " " + time.getMinute() + " " + time.getSecond());
		Time time1 = new Time(555550000);
		System.out.println(time1.getHour() + " " + time1.getMinute() + " " + time1.getSecond());

	}

}
