package project6;

/**
 * 
* @ClassName: Triangle
* @Description: 三角形的抽象类, 继承GeometricObject类
* @author Orion
* @date 2018年12月21日
*
 */
public class Triangle extends GeometricObject{
	//三个属性对应三角形的三个边
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
		//使用海伦公式求得三角形的面积
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
		//返回具有三角形三条边信息的字符串
		return "Triangle: side1 = " + side1 + " side2 = " + side2 +  " side3 = " + side3;
	}
}
