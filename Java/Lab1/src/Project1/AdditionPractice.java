package Project1;

import java.util.Optional;
import java.util.Random;

import javafx.application.Application;
import javafx.scene.control.Alert;
import javafx.scene.control.TextInputDialog;
import javafx.stage.Stage;

public class AdditionPractice extends Application{
	
	/**
	 * �ж��û��������Ƿ�ȫ��������, ʹ��������ʽ
	 * @param str
	 * @return �жϽ��
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
	 * ��дApplication��start����, ���н���Ĵ���
	 */
	@Override
	public void start(Stage primaryStage) throws Exception {
		
		//�������������,  ʹ��Random��
		Random ran = new Random();
		int num1 = ran.nextInt(10);
		int num2 = ran.nextInt(10);
		
		
		//����һ�����������ĶԻ���, ʹ��TextInputDialog
		TextInputDialog dialog = new TextInputDialog();
		dialog.setTitle("Input");
		String question = "What is " + String.valueOf(num1) + " + " + String.valueOf(num2) + " ?";
		dialog.setContentText(null);
		dialog.setHeaderText(question);
		
		
		//�û����ȷ��, �����û���������Ϣ, �����жϽ��
		Optional<String> result = dialog.showAndWait();
		result.ifPresent(input ->{
			
			
			//�����ж��û������Ƿ�Ϸ�
			
			
			//�ж��û��Ƿ�û������, �ǵĻ��������洰��
			if(input.equals("")) {
				Alert alert = new Alert(Alert.AlertType.ERROR, "����: ����Ϊ��");
				alert.setHeaderText(null);
				alert.showAndWait();
			}
			//ʹ��������ʽ, ����û����벻��ȫ����, �򵯳�����
			else if(!isLegal(input)) {
				Alert alert = new Alert(Alert.AlertType.ERROR, "����: û����ȷ��������");
				alert.setHeaderText(null);
				alert.showAndWait();
			}
			//�ж��û��Ľ���Ƿ���ȷ
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
