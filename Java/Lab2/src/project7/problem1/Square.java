package project7.problem1;

import project6.GeometricObject;

/**
 * 
* @ClassName: Square
* @Description: 正方形的抽象
* @author Orion
* @date 2018年12月21日
*
 */
public class Square extends GeometricObject implements Colorable {
	private double side;
	
	public Square() {
		side = 1.0;
	}
	
	public Square(double side) {
		this.side = side;
	}
	
	@Override
	public void howToColor() {
		// TODO Auto-generated method stub
		System.out.println("fill the square with " + getColor());
	}

	public double getSide() {
		return side;
	}

	@Override
	public double getArea() {
		// TODO Auto-generated method stub
		return side * side;
	}

	@Override
	public double getPerimeter() {
		// TODO Auto-generated method stub
		return 4.0 * side;
	}

}
