package project7.problem2;

public class Octagon extends GeometricObject implements Cloneable, Comparable<Octagon>{

	private double side;
	
	public Octagon() {
		side = 1.0;
	}
	
	public Octagon(double side) {
		this.side = side;
	}
	
	@Override
	public int compareTo(Octagon octagon1) {
		// TODO Auto-generated method stub
		if(this.side > octagon1.side) {
			return 1;
		}
		else if(this.side == octagon1.side) {
			return 0;
		}
		else {
			return -1;
		}
	}

	@Override
	public double getArea() {
		// TODO Auto-generated method stub
		return (2 + 2 * Math.sqrt(2)) * side * side;
	}

	@Override
	public double getPerimeter() {
		// TODO Auto-generated method stub
		return 8 * side;
	}

	public double getSide() {
		return side;
	}
	
	public Object clone() throws CloneNotSupportedException {
		return super.clone();
	}

}
