package project7.problem1;

import project6.GeometricObject;
import project6.Triangle;

/**
 * 
* @ClassName: TestSquare
* @Description: 对Square类进行测试
* @author Orion
* @date 2018年12月21日
*
 */
public class TestSquare {

	public static void main(String[] args) {
		GeometricObject[] geoArray = {new Square(), new Square(), new Square(),
				new Triangle(), new Triangle()};
		
		for(int i=0;i<geoArray.length;i++) {
			System.out.println("shape" + (i+1));
			if(geoArray[i] instanceof Colorable) {
				((Colorable)geoArray[i]).howToColor();
			}
			else {
				System.out.println("cannot color");
			}
		}
	
	}

}
