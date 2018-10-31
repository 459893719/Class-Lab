package Project2;

public class TaxTable {
	

	private static int[][] limit = {
			{0, 7300, 29700, 71950, 150150, 326450},
			{0, 14600, 59400, 119950, 182800, 326450},
			{0, 7300, 29700, 59975, 91400, 163225},
			{0, 10450, 39800, 102800, 166450, 326450}
	};
	private static double[] rate= {0.1, 0.15, 0.25, 0.28, 0.33, 0.35};
	
	
	/**
	 * 根据人的收入和身份计算税款
	 * @param income  收入
	 * @param status  身份
	 * @return        该身份的公民应交税款
	 */
	public static int calculateTax(int income, int status) {
		
		double tax = 0;
		for(int i=0;i<limit[status].length;i++) {
			
			if(i == limit[status].length -1 || income <= limit[status][i+1]) {
				tax += rate[i] * (double)(income - limit[status][i]);
				break;
			}
			else if(income > limit[status][i]) {
				tax += rate[i] * (double) (limit[status][i+1] - limit[status][i]);
			}
		}
		
		return (int)tax;
	}
	
	
	/**
	 * 在控制台上打印税表
	 * @param begin  最低收入
	 * @param end    最高收入
	 * @param gap    两个条目之间的收入间隔
	 */
	public static void showTable(int begin, int end, int gap) {
		System.out.println("Taxable\t\tSingle\t\tMarried\t\tMarried\t\tHead of");
		System.out.println("Income\t\t\t\tJoint\t\tSeparate\ta House");
		System.out.println("-----------------------------------------------------------------------");
		
		for(int income = begin; income <=end; income += gap) {
			System.out.println(income + "\t\t" + calculateTax(income, 0) + "\t\t" + 
								calculateTax(income, 1) + "\t\t" + calculateTax(income, 2) + 
								"\t\t" + calculateTax(income, 3));
		}
	}
	
	
	
	public static void main(String[] args) {
		showTable(50000, 60000, 50);
	}
}
