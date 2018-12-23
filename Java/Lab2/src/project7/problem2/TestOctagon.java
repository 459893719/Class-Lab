package project7.problem2;


/**
 * 
* @ClassName: TestOctagon
* @Description: Octagon类的测试
* @author Orion
* @date 2018年12月21日
*
 */
public class TestOctagon {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Octagon octagon = new Octagon(5.0);
		System.out.println("Area: " + octagon.getArea() + " Perimeter: " + octagon.getPerimeter());
		Octagon octagon2;
		try {
			octagon2 = (Octagon)octagon.clone();
			if(octagon.compareTo(octagon2) == 0) {
				System.out.println("octagon == octagon2");
			}
			else {
				System.out.println("octagon != octagon2");
			}
		} catch (CloneNotSupportedException e) {
			e.printStackTrace();
		}
	}

}
