package project6;

public class TestTriangle {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
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
