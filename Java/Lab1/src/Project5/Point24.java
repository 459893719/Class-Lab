package Project5;


import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.image.ImageView;
import javafx.scene.layout.HBox;
import javafx.scene.layout.StackPane;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

public class Point24 extends Application{

	@Override
	public void start(Stage primaryStage) throws Exception {
		// TODO Auto-generated method stub
		Button btSolution = new Button("Find a Solution");
		TextField textfield = new TextField();
		Button btRefresh = new Button("Refresh");
		
		HBox hbox1 = new HBox(5);
		hbox1.getChildren().addAll(btSolution, textfield, btRefresh);
		hbox1.setPadding(new Insets(10));
		
		ImageView[] image = new ImageView[4];
		
		HBox hbox2 = new HBox(10);
		hbox2.setPadding(new Insets(10));
		
		for(int i=0;i<4;i++) {
			image[i] = new ImageView("file:./card/1.png"); 
			hbox2.getChildren().add(image[i]);
		}
		
		
		Label text = new Label("Enter an expression:");
		TextField textfield1 = new TextField();
		Button btVerify = new Button("Verify");
		
		HBox hbox3 = new HBox(5);
		hbox3.getChildren().addAll(text, textfield1, btVerify);
		hbox3.setPadding(new Insets(10));
		
		VBox vbox = new VBox(10);
		vbox.getChildren().addAll(hbox1, hbox2, hbox3);
		vbox.setPadding(new Insets(10));

		
		Scene scene = new Scene(vbox);
		scene.getStylesheets().add(this.getClass().getResource("style.css").toExternalForm());
		primaryStage.setScene(scene);
		primaryStage.show();
		
	}
	
	public static void main(String[] args) {
		Application.launch();
	}

}
