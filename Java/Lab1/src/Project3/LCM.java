package Project3;

import java.util.ArrayList;
import java.util.Scanner;

public final class LCM {
	
	public static ArrayList<Factor> getPrimeFactors(int number){
		ArrayList<Factor> table = new ArrayList<Factor>();
		
		
		int i = 2;
		int count = 0;
		
		while(true) {
			if(number % i == 0) {
				number /= i;
				count++;
			}
			else {
				if(count > 0) {
					table.add(new Factor(i, count));
				}
				count = 0;
				i++;
			}
			
			if(number == 1) {
				if(count > 0) {
					table.add(new Factor(i, count));
				}
				break;
			}
		}
		
		return table;
		
	}
	
	public static int getLCM(int number1, int number2) {
		ArrayList<Factor> table1 = getPrimeFactors(number1);
		ArrayList<Factor> table2 = getPrimeFactors(number2);
		
		int i = 0;
		int j = 0;
		
		int lcm = 1;
		
		while(i < table1.size() && j < table2.size()) {
			int value1 = table1.get(i).value;
			int num1 = table1.get(i).num;
			int value2 = table2.get(j).value;
			int num2 = table2.get(j).num;
			
			if(value1 < value2) {
				for(int k=0;k<num1;k++) {
					lcm *= value1;
				}
				i++;
			}
			else if(value1 > value2) {
				for(int k=0;k<num2;k++) {
					lcm *= value2;
				}
				j++;
			}
			else {
				for(int k=0;k<Math.max(num1, num2);k++) {
					lcm *= value1;
				}
				i++;
				j++;
			}
		}
		while(i < table1.size()) {
			int value1 = table1.get(i).value;
			int num1 = table1.get(i).num;
			for(int k=0;k<num1;k++) {
				lcm *= value1;
			}
			i++;
		}
		
		while(j < table2.size()) {
			int value2 = table2.get(j).value;
			int num2 = table2.get(j).num;
			for(int k=0;k<num2;k++) {
				lcm *= value2;
			}
			j++;
		}
		return lcm;
	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub

		int num1;
		int num2;
			
		Scanner in = new Scanner(System.in);
		
		num1 = in.nextInt();
		num2 = in.nextInt();

		System.out.println(getLCM(num1, num2));
		
		in.close();
	
		

	}

}


class Factor{
	public int value;
	public int num;
	
	Factor(int value, int num){
		this.value = value;
		this.num = num;
	}
}