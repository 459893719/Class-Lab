package project6;

/*
The class contains: 
1.	Three double data fields named side1, side2, and side3 with default values 1.0 to denote three sides of the triangle.
2.	A no-arg constructor that creates a default triangle.
3.	A constructor that creates a rectangle with the specified side1, side2, and side3.
4.	The accessor methods for all three data fields. 
5.	A method named getArea() that returns the area of this triangle.
6.	A method named getPerimeter() that returns the perimeter of this triangle.
7.	A method named toString() that returns a string description for the triangle. 

For the formula to compute the area of a triangle, see Exercise 5.19. The toString() method is implemented as follows:

return "Triangle: side1 = " + side1 + " side2 = " + side2 +  " side3 = " + side3;

 */
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
