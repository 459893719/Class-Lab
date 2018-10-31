package Project1;

import java.util.Optional;
import java.util.Random;

import javafx.application.Application;
import javafx.scene.control.Alert;
import javafx.scene.control.TextInputDialog;
import javafx.stage.Stage;

public class AdditionPractice extends Application{
	
	/**
	 * 判断用户的输入是否全都是数字, 使用正则表达式
	 * @param str
	 * @return 判断结果
	 */
	public static boolean isLegal(String str) { 
		if(str.matches("[0-9]+")) {
			return true;
		}
		else {
			return false;
		}
	}
	
	
	/**
	 * 重写Application的start方法, 进行界面的创建
	 */
	@Override
	public void start(Stage primaryStage) throws Exception {
		
		//创建两个随机数,  使用Random类
		Random ran = new Random();
		int num1 = ran.nextInt(10);
		int num2 = ran.nextInt(10);
		
		
		//创建一个具有输入框的对话框, 使用TextInputDialog
		TextInputDialog dialog = new TextInputDialog();
		dialog.setTitle("Input");
		String question = "What is " + String.valueOf(num1) + " + " + String.valueOf(num2) + " ?";
		dialog.setContentText(null);
		dialog.setHeaderText(question);
		
		
		//用户点击确定, 处理用户的输入信息, 返回判断结果
		Optional<String> result = dialog.showAndWait();
		result.ifPresent(input ->{
			
			
			//首先判断用户输入是否合法
			
			
			//判断用户是否没有输入, 是的话弹出警告窗口
			if(input.equals("")) {
				Alert alert = new Alert(Alert.AlertType.ERROR, "错误: 输入为空");
				alert.setHeaderText(null);
				alert.showAndWait();
			}
			//使用正则表达式, 如果用户输入不是全数字, 则弹出警告
			else if(!isLegal(input)) {
				Alert alert = new Alert(Alert.AlertType.ERROR, "错误: 没有正确输入数字");
				alert.setHeaderText(null);
				alert.showAndWait();
			}
			//判断用户的结果是否正确
			else {
				Alert alert = new Alert(Alert.AlertType.INFORMATION, null);
				alert.setHeaderText(null);
				
				String res = String.valueOf(num1) + " + " + String.valueOf(num2)
				 + " = " + input + " is ";
				boolean isRight = (num1 + num2) == Integer.parseInt(input);
				
				res += isRight;
				alert.setContentText(res);
				alert.showAndWait();
			}
		});

	
	}
	
	public static void main(String[] args) {
		Application.launch();
		
	}
}
