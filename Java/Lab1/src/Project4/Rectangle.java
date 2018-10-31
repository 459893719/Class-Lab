package Project4;

public class Rectangle {

	private double width;
	private double height;
	String color;
	
	public Rectangle() {
		width = 1.0;
		height = 1.0;
		color = "white";
	}
	
	public Rectangle(double width, double height) {
		this.width = width;
		this.height = height;
	}

	public double getWidth() {
		return width;
	}

	public void setWidth(double width) {
		this.width = width;
	}

	public double getHeight() {
		return height;
	}

	public void setHeight(double height) {
		this.height = height;
	}

	public String getColor() {
		return color;
	}

	public void setColor(String color) {
		this.color = color;
	}
	
	
	public double getArea() {
		return height * width;
	}
	public double getPerimeter() {
		return (height + width) * 2;
	}
}
