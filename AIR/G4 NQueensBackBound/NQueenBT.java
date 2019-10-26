import java.util.Scanner;

public class NQueenBT {

	static int N=0;
	
	void printsol(int board[][])
	{
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)
			{
				if(board[i][j]==1)
				{
					System.out.print("x\t");
				}
				else
				{
					System.out.print("0\t");
				}
			}
			System.out.println();
		}
	}
	boolean isSafe(int board[][], int row, int col)
	{
		for(int i=0;i<col;i++)
		{
			if(board[row][i]==1) //checking if queen is on any sides or not
			{
				return false;
			}
		}
		
		for(int i=row, j=col;i>=0 && j>=0;i--,j--) // checking downward left diagonal
		{ 
			if(board[i][j]==1)
			{
				return false;
			}
		}
		for(int i=row,j=col;i<N && j>=0;i++,j--)  // checking upward left diagonal 
		{
			if(board[i][j]==1)
			{
				return false;
			}
		}
		return true;
	}
	
	boolean solveUtil(int board[][],int col)
	{
		if(col>=N)
		{
			return true;
		}
		for(int i=0;i<N;i++)
		{
			if(isSafe(board,i,col))
			{
				board[i][col]=1;
				if(solveUtil(board,col+1))
				{
					return true;
				}
				
				board[i][col]=0;
			}	
		}
		return false;
	}
	
	void solve(int board[][])
	{
		if(!solveUtil(board,0))
		{
			System.out.println("Solution not possible");
		}
		else
		{
			printsol(board);
		}
	}
	
	public static void main(String[] args) {
		Scanner obj = new Scanner(System.in);
		System.out.println("Enter value of N-: ");
		N = obj.nextInt();
		int board[][] = new int[N][N];
		NQueenBT nqbt = new NQueenBT();
		nqbt.solve(board);
	}
}
