package project9;

public class StringMap {
	public static String[] stringmap = {"rock", "paper", "scissors"};
	//一个剪刀石头布的得分表, pointmap[a][b]表示的是我方选择a, 对方选择b时我方所得到的分数
	public static int[][] pointmap = {
			{1, 0, 2},
			{2, 1, 0},
			{0, 2, 1}
	};
}
