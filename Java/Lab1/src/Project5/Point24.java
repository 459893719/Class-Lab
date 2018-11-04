package Project5;


import java.util.Arrays;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Random;

import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.image.ImageView;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

public class Point24 extends Application{
	
	int[] deckArray = new int[4];
	
	
	public void RandomDeck(ImageView[] image, HBox hbox) {
		
		HashSet <Integer> randomset = new HashSet<Integer>();
		Random random = new Random();
		while(randomset.size() != 4) {
			randomset.add(random.nextInt(52) + 1);
		}

		Iterator iterator = randomset.iterator();
		int i=0;
		while (iterator.hasNext()) {
			hbox.getChildren().remove(image[i]);
			int num = (int)iterator.next();
			deckArray[i] = (num - 1) % 13 + 1; 
			image[i] = new ImageView("file:./card/" + String.valueOf(num) + ".png");
			hbox.getChildren().add(image[i++]);
		}
		
		
//		System.out.println(Arrays.toString(deckArray));
	}

	@Override
	public void start(Stage primaryStage) throws Exception {
		// TODO Auto-generated method stub
		Button btSolution = new Button("Find a Solution");
		TextField textfield = new TextField();
		Button btRefresh = new Button("Refresh");
		
		btSolution.setOnAction(e -> {
			CalculateSum cSum = new CalculateSum();
			cSum.findSolution(deckArray);			
			textfield.setText(cSum.toString());
		});
		
		
		HBox hbox1 = new HBox(5);
		hbox1.getChildren().addAll(btSolution, textfield, btRefresh);
		hbox1.setPadding(new Insets(10));
		
		ImageView[] image = new ImageView[4];
		
		HBox hbox2 = new HBox(10);
		hbox2.setPadding(new Insets(10));
		
		RandomDeck(image, hbox2);
		
		btRefresh.setOnAction(e -> {
			RandomDeck(image, hbox2);
		});
		
		
		Label text = new Label("Enter an expression:");
		TextField textfield1 = new TextField();
		Button btVerify = new Button("Verify");
		
		HBox hbox3 = new HBox(5);
		hbox3.getChildren().addAll(text, textfield1, btVerify);
		hbox3.setPadding(new Insets(10));
		
		VBox vbox = new VBox(10);
		vbox.getChildren().addAll(hbox1, hbox2, hbox3);
		vbox.setPadding(new Insets(10));
		
		btVerify.setOnAction(e -> {
			ExprVerify ev = new ExprVerify(deckArray);
			int result = ev.verify(textfield1.getText());
			
			Alert alert = new Alert(AlertType.INFORMATION);
			alert.setTitle("检测结果");
			alert.setHeaderText(null);
			
			if(result == ExprVerify.EXPR_ERROR) {
				alert.setContentText("表达式输入错误!");
			}
			else if(result == ExprVerify.NOT_USE_CARDS) {
				alert.setContentText("没有使用所给的四张牌!");
			}
			else if(result == ExprVerify.RESULT_ERROR) {
				alert.setContentText("表达式结果不是24!");
			}
			else {
				alert.setContentText("恭喜你找到正确答案!");
			}
			
			alert.showAndWait();
		});
		

		
		Scene scene = new Scene(vbox);
		scene.getStylesheets().add(this.getClass().getResource("style.css").toExternalForm());
		primaryStage.setResizable(false);
		primaryStage.setTitle("24点计算");
		primaryStage.setScene(scene);
		primaryStage.show();
		
	}
	
	public static void main(String[] args) {
		Application.launch();
	}

}
