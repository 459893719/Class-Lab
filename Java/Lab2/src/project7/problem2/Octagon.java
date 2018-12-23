package project7.problem2;

import project6.GeometricObject;

/**
 * 
* @ClassName: Octagon
* @Description: 正八边形的抽象
* @author Orion
* @date 2018年12月21日
*
 */
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
		Octagon octagon = (Octagon)super.clone();
		octagon.setColor(new String(getColor()));
		return octagon;
	}

}
