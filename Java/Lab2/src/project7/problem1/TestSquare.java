package project7.problem1;

public class TestSquare {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		GeometricObject[] geoArray = {new Square(), new Square(), new Square(),
				new Triangle(), new Triangle()};
		
		for(int i=0;i<geoArray.length;i++) {
			System.out.println("shape" + (i+1));
			if(geoArray[i] instanceof Colorable) {
				((Colorable)geoArray[i]).howToColor();
			}
			else {
				System.out.println("cannot color");
			}
		}
	
	}

}
