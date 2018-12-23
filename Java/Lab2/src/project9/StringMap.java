package project9;

/**
 * 
* @ClassName: StringMap
* @Description: 存放了两个变量, 方便进行数据传输和评分
* @author Orion
* @date 2018年12月23日
*
 */
public class StringMap {
	//将剪刀石头布映射为三个整数, 方便数据的传输
	public static String[] stringmap = {"rock", "paper", "scissors"};
	//一个剪刀石头布的得分表, pointmap[a][b]表示的是我方选择a, 对方选择b时我方所得到的分数
	public static int[][] pointmap = {
			{1, 0, 2},
			{2, 1, 0},
			{0, 2, 1}
	};
}
