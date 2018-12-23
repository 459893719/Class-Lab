package project6;
/**
 * 
* @ClassName: TestTriangle
* @Description: 对Triangle类进行测试
* @author Orion
* @date 2018年12月21日
*
 */
public class TestTriangle {

	public static void main(String[] args) {
		Triangle tri = new Triangle(1.0, 1.5, 1.0);
		
		tri.setColor("yellow");
		tri.setFilled(true);
		
		System.out.println(tri.toString());
		System.out.println("Area: " + tri.getArea() + 
				" Perimeter: " + tri.getPerimeter() + 
				" Color: " + tri.getColor() +
				" Filled: " + tri.isFilled());
	}

}
