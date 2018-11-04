package Project1;

import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.Pane;
import javafx.util.Duration;

public class Car extends Pane{
	private ImageView carImage = new ImageView("file:./car/car.png");
	private double x = 0;
	
	private double width = 140;
	private double height = 40;
	private double initRate;
	private Timeline animation;
	
	public Car() {
		carImage.setX(0);
		carImage.setFitHeight(height);
		carImage.setFitWidth(width);
		getChildren().add(carImage);
		
		animation = new Timeline(
				new KeyFrame(Duration.millis(3), e->moveCar()));
		animation.setCycleCount(Timeline.INDEFINITE);
		initRate = animation.getRate();
//		animation.play();
	}
	
	public void changeSpeed(int input) {
		animation.setRate(initRate - (input-1)*0.01);
	}
	
	public void play() {
	    animation.play();
	}

	public void pause() {
	    animation.pause();
	}
	
	protected void moveCar() {
		if(x > getWidth()) {
			x = 0;
		}
		else{
			x += 1;
		}
		carImage.setX(x);
	}
	

}
