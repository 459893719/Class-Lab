package project6;

/**
 * 
* @ClassName: GeometricObject
* @Description: 图形的抽象类
* @author Orion
* @date 2018年12月21日
*
 */
public abstract class GeometricObject {
	  private String color;      //图形的颜色, 用String表示
	  private boolean filled;    //图形是否填充
	  
	  protected GeometricObject() {
		//默认颜色为白色
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

	  //获得图形的面积
	  public abstract double getArea();

	  //获得图形的周长
	  public abstract double getPerimeter();
}
