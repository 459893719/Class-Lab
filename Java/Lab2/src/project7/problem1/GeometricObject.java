package project7.problem1;

public abstract class GeometricObject {
	  private String color;
	  private boolean filled;
	  
	  protected GeometricObject() {
	    color = "white";
	  }

	  protected GeometricObject(String color, boolean filled) {
	    this.color = color;
	    this.filled = filled;
	  }

	  public String getColor() {
	    return color;
	  }

	  public void setColor(String color) {
	    this.color = color;
	  }

	  public boolean isFilled() {
	    return filled;
	  }

	  public void setFilled(boolean filled) {
	    this.filled = filled;
	  }

	  public String toString() {
	    return "color: " + color +
	      " and filled: " + filled;
	  }

	  public abstract double getArea();

	  public abstract double getPerimeter();
}
