package project7.problem1;

public class Triangle extends GeometricObject{
	private double side1;
	private double side2;
	private double side3;
	
	public Triangle() {
		side1 = 1.0;
		side2 = 1.0;
		side3 = 1.0;
	}
	
	public Triangle(double side1, double side2, double side3) {
		this.side1 = side1;
		this.side2 = side2;
		this.side3 = side3;
	}

	public double getSide1() {
		return side1;
	}

	public double getSide2() {
		return side2;
	}

	public double getSide3() {
		return side3;
	}
	
	@Override
	public double getArea() {		
		double p = (side1 + side2 + side3) / 2;
		double area = Math.sqrt(p*(p-side1)*(p-side2)*(p-side3));
		return area;
	}
	
	@Override
	public double getPerimeter() {
		return side1 + side2 + side3;
	}
	
	@Override
	public String toString() {
		return "Triangle: side1 = " + side1 + " side2 = " + side2 +  " side3 = " + side3;
	}
}
