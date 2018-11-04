package Project1;



import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.image.ImageView;
import javafx.scene.input.KeyCode;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.shape.Line;
import javafx.stage.Stage;

public class CarRace extends Application{
	
	private final int CARNUM = 4;
	ImageView[] car = new ImageView[CARNUM]; 

	@Override
	public void start(Stage primaryStage) throws Exception {
		// TODO Auto-generated method stub
		
		//顶端输入框的布局设计
		Label[] labels = new Label[CARNUM];
		TextField[] speedinput = new TextField[CARNUM];
		HBox hbox1 = new HBox(10);
		hbox1.setPadding(new Insets(10));
		for(int i=0;i<CARNUM;i++) {
			labels[i] = new Label("Car " + String.valueOf(i+1) + ": ");
			speedinput[i]= new TextField(); 
			hbox1.getChildren().addAll(labels[i], speedinput[i]);
		}
		
		//输入框与跑道的分割线
		HBox hbox2 = new HBox();
		Line line = new Line(0,0,800,0);
		hbox2.getChildren().add(line);
		
		
		//下面的四个跑道布局
		HBox[] hbox = new HBox[CARNUM*2];
		Line[] lines = new Line[CARNUM];
		Car[] cars = new Car[CARNUM];
		for(int i=0;i<CARNUM;i++) {
			hbox[2*i] = new HBox();
			hbox[2*i].setPadding(new Insets(10));
			hbox[2*i+1] = new HBox();
			
			lines[i] = new Line(0,0,800,0); 
			cars[i] = new Car();
			hbox[2*i].getChildren().add(cars[i]);
			hbox[2*i+1].getChildren().add(lines[i]);
		}
		
		for(int i=0;i<CARNUM;i++) {
			cars[i].play();
		}
		
		
		
		
		
		VBox vbox = new VBox();
		vbox.getChildren().add(hbox2);
		for(int i=0;i<CARNUM*2;i++) {
			vbox.getChildren().add(hbox[i]);
		}
		
		
		BorderPane bpane = new BorderPane();
		bpane.setCenter(vbox);
		bpane.setTop(hbox1);
		
		bpane.setOnKeyPressed(e->{
			if(e.getCode() == KeyCode.ENTER) {
				for(int i=0;i<CARNUM;i++) {
					int speed = Integer.parseInt(speedinput[i].getText());
					if(speed < 1 || speed > 100) {
						speedinput[i].setText("1");
						speed = 1;
					}
					
					cars[i].changeSpeed(speed);
				}
			}
		});
		
		Scene scene = new Scene(bpane);
		primaryStage.setScene(scene);
		primaryStage.show();
		
		
		
	}
	
	public static void main(String[] args) {
		Application.launch();
	}

}



