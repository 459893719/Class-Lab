package Project5;

import java.util.Arrays;
import java.util.Stack;


public class ExprVerify {

	private static int[] deckArray;
	
	public final static int RESULT_ERROR = 1;
	public final static int EXPR_ERROR = 2;
	public final static int NOT_USE_CARDS = 3;
	
	public ExprVerify(int[] card) {
		deckArray = card;
	}
	
	public int verify(String infix) {
		
		try {
			//����׺���ʽ��ת�ɺ�׺���ʽ
			String postfix = inToPost(infix);
			
			if(!isUseCards(postfix)) {
				return 3;
			}
			
			//�����׺���ʽ
			int result = exprCalculate(postfix);
			
			//�ж����
			if(result == 24) {
				return 0;
			}
			else {
				return 1;
			}
		}
		catch(Exception e) {
//			e.printStackTrace();
			return 2;
		}
	}
	public static String inToPost(String infix) throws Exception {
		
		//��׺���ʽת��char����
		char[] inarray = infix.toCharArray();
		char[] postarray = new char[100];
		
		Stack<Character> stack = new Stack<Character>();
		
		int cur = 0;
		boolean flag = false;
		for(int i=0;i<inarray.length;i++) {
			if(inarray[i] >= '0' && inarray[i] <= '9' ) {
				
				if(!flag) {
					postarray[cur++] = ' ';
					flag = true;
				}
				
				postarray[cur++] = inarray[i];
			}
			//�����), ��ջ�������������������ʽ��
			else if(inarray[i] == ')') {
				flag = false;
				while(stack.peek() != '(') {
					postarray[cur++] = ' ';
					postarray[cur++] = stack.pop();
				}
				stack.pop();
				
			}
			else if(inarray[i] >= '(' && inarray[i] <= '/') {
				flag = false;
				if(stack.empty() || comparePriority(inarray[i], stack.peek())) {
					stack.push(inarray[i]);
				}
				else {
					while(!stack.empty() && !comparePriority(inarray[i], stack.peek())) {
						postarray[cur++] = ' ';
						postarray[cur++] = stack.pop();
					}
					stack.push(inarray[i]);
				}
			}
			else {
				throw new Exception();
			}
		}
		
		while(!stack.empty()) {
			postarray[cur++] = ' ';
			postarray[cur++] = stack.pop();
		}
		
		
//		System.out.println(String.valueOf(postarray));
		
		return String.valueOf(postarray);
		
	}
	
	/**
	 * �ж��û�����ı��ʽ�е����Ƿ���������һ��
	 * @param postfix
	 * @return
	 */
	public static boolean isUseCards(String postfix) throws Exception {
		String[] op = postfix.split(" ");
		int[] numArray = new int[4];
		int cur = 0;
		for(int i=1;i<op.length;i++) {
			if(Character.isDigit(op[i].charAt(0))) {
				numArray[cur++] = Integer.parseInt(op[i]);
			}
		}
		
		Arrays.sort(numArray);
		Arrays.sort(deckArray);
		return Arrays.equals(numArray, deckArray);
			
	}
	
	public static int exprCalculate(String postfix) throws Exception{
		
		String[] op = postfix.split(" ");
		Stack<Integer> stack = new Stack<Integer>();
		
		for(int i=1;i<op.length;i++) {
			
			int num2;
			int num1;
			int num3;
			
			switch(op[i].charAt(0)) {
			case '+':{
				num2 = stack.pop();
				num1 = stack.pop();
				num3 = num1 + num2;
				stack.push(num3);
				break;
			}
			case '-':{
				num2 = stack.pop();
				num1 = stack.pop();
				num3 = num1 - num2;
				stack.push(num3);
				break;
			}
			case '*':{
				num2 = stack.pop();
				num1 = stack.pop();
				num3 = num1 * num2;
				stack.push(num3);
				break;
			}
			case '/':{
				num2 = stack.pop();
				num1 = stack.pop();
				num3 = num1 / num2;
				stack.push(num3);
				break;
			}
			case '(':{
				throw new Exception();
			}
			default:{
				int num = Integer.parseInt(op[i]);
				
				//���
				
				stack.push(num);
			}
			}
			
		}
		int result = stack.pop();	
		
//		System.out.println(result);
		
		return result;
	}
	public static boolean comparePriority(char optr1, char optr2) throws Exception {
		if(optr1 == '(' || optr2 == '(') {
			return true;
		}
		switch (optr1){
		
		case '+':
		case '-':{
			if(optr2 == '+' || optr2 == '-' || optr2 == '*' || optr2 == '/') {
				return false;
			}
			else {
				throw new Exception();
			}
		}
		case '*':
		case '/':{
			if(optr2 == '*' || optr2 == '/') {
				return false;
			}
			else if(optr2 == '+' || optr2 == '-') {
				return true;
			}
			else {
				throw new Exception();
			}
		}
		
			
		}
		return true;
		
	}
}
