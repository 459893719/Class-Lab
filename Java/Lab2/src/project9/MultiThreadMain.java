package project9;

import java.util.Optional;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

import javafx.application.Application;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextInputDialog;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.VBox;
import javafx.scene.text.Font;
import javafx.stage.Stage;

//类似于结构体, 将多线程之间共享的数据封装起来, 便于相互传递
class SharingData{
	public int totalRound;
	public int round;
	public Lock lock;
	public SharingData() {
		// TODO Auto-generated constructor stub
		totalRound = 9;
		round = 0;
		lock = new ReentrantLock();
	}
}

public class MultiThreadMain extends Application{
	SharingData sharingdata = new SharingData();
	private PlayerData PlayerA = new PlayerData(), PlayerB = new PlayerData();
	
	private final TableView<Round> table = new TableView<Round>();
	private final ObservableList<Round> data = FXCollections.observableArrayList();
	
	@SuppressWarnings({ "unchecked", "rawtypes" })
	@Override
	public void start(Stage primaryStage) throws Exception {
		// TODO Auto-generated method stub
		
		TextInputDialog dialog = new TextInputDialog();
		dialog.setTitle("比大小程序");
		dialog.setContentText("本局比赛共有几个回合(不小于3)?");
		dialog.setHeaderText(null);
		Optional<String> result;
		while(true) {
			result =  dialog.showAndWait();
			if (result.isPresent()){
			    String input = result.get();
			    //输入的回合数要是大于3的整数, 如果输入错误的话, 要求用户再输入一遍
			    if(!input.matches("[0-9]{1,}")) {
			    	continue;
			    }
			    sharingdata.totalRound = Integer.parseInt(input);
			    if(sharingdata.totalRound >= 3) {
			    	break;
			    }
			}
			else {
				break;
			}
		}
		if(result.isPresent()) {
			//主窗口, 显示每回合的结果
			Label title = new Label("线上猜拳");
			title.setFont(new Font("微软雅黑", 40));
			
			table.setEditable(false);
			TableColumn roundCol = new TableColumn("Round");
			roundCol.setCellValueFactory(new PropertyValueFactory<>("roundNum"));
			TableColumn threadACol = new TableColumn("Thread A");
			TableColumn threadBCol = new TableColumn("Thread B");
			
			TableColumn ASleepTimeCol = new TableColumn("Sleep time");
			ASleepTimeCol.setCellValueFactory(new PropertyValueFactory<>("ASleepTime"));
			TableColumn ARandomSelectionCol = new TableColumn("Random selection");
			ARandomSelectionCol.setMinWidth(60);
			ARandomSelectionCol.setCellValueFactory(new PropertyValueFactory<>("ARandomSelection"));
			TableColumn APointsCol = new TableColumn("Points obtained");
			APointsCol.setMinWidth(50);
			APointsCol.setCellValueFactory(new PropertyValueFactory<>("APoints"));
			threadACol.getColumns().addAll(ASleepTimeCol, ARandomSelectionCol, APointsCol);
	
			
			TableColumn BSleepTimeCol = new TableColumn("Sleep time");
			BSleepTimeCol.setCellValueFactory(new PropertyValueFactory<>("BSleepTime"));
			TableColumn BRandomSelectionCol = new TableColumn("Random selection");
			BRandomSelectionCol.setMinWidth(60);
			BRandomSelectionCol.setCellValueFactory(new PropertyValueFactory<>("BRandomSelection"));
			TableColumn BPointsCol = new TableColumn("Points obtained");
			BPointsCol.setMinWidth(50);
			BPointsCol.setCellValueFactory(new PropertyValueFactory<>("BPoints"));
			threadBCol.getColumns().addAll(BSleepTimeCol, BRandomSelectionCol, BPointsCol);
			
			table.setItems(data);
			table.getColumns().addAll(roundCol, threadACol, threadBCol);
			table.setColumnResizePolicy(TableView.CONSTRAINED_RESIZE_POLICY);
			
			
	        VBox vbox = new VBox();
	        vbox.setSpacing(5);
	        vbox.setPadding(new Insets(10, 0, 0, 10));
	        vbox.setAlignment(Pos.TOP_CENTER);
	        vbox.getChildren().addAll(title, table);
	        
	        Scene scene = new Scene(vbox, 700, 500);
	        primaryStage.setScene(scene);
	        primaryStage.show();
				
			new Thread(new Server(sharingdata, PlayerA, PlayerB, data)).start();
			new Thread(new TCPHandler(sharingdata, PlayerA)).start();
			new Thread(new UDPHandler(sharingdata, PlayerB)).start();
		}
	}
	
	public static void main(String[] args) {
		Application.launch();
	}

	
}
