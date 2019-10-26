import java.util.Arrays;
import java.util.Scanner;

public class NQueenBNB {

	static int N;

	public void printsol(int board[][])
	{
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
					if(board[i][j]==1){
						System.out.print("x \t");
					}
					else{
						System.out.print("0 \t");
					}
			}

			System.out.println();
		}
	}
	public void solve(){
		int board[][] = new int[N][N];
		int slash[][]= new int[N][N];
		int backslash[][]= new int[N][N];
		boolean backslashlookup[]= new boolean[2*N-1];
		boolean slashlookup[]= new boolean[2*N-1];
		boolean rowlookup[]= new boolean[N];

		Arrays.fill(rowlookup, false);//tells which rows are occupied
		Arrays.fill(slashlookup, false);//
		Arrays.fill(backslashlookup, false);

		//initialize helper matrices
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				slash[i][j] = i+j;
				backslash[i][j] = i-j+(N-1);
			}
		}
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				System.out.print(slash[i][j]+" ");
			}
			System.out.println("");
		}
		if(solveproblem(board, 0, slash, backslash, backslashlookup,slashlookup,rowlookup) == true){
			printsol(board);
		}
		else{
			System.out.println("Solution Not possible!!");
		}
	}

	public boolean solveproblem(int board[][],int  col, int slash[][], int backslash[][], boolean backslashlookup[],boolean slashlookup[],boolean rowlookup[] )
	{
		if(col>=N)
		{
			return true;
		}
		for(int i=0;i<N;i++)
		{
			if(isSafe(board, col, i, slash, backslash, backslashlookup, slashlookup, rowlookup)){
				board[i][col]=1;
				slashlookup[slash[i][col]]=true;
				backslashlookup[backslash[i][col]] = true;
				rowlookup[i] = true;
				if(solveproblem(board, col+1, slash, backslash, backslashlookup,slashlookup,rowlookup)){
					return true;
				}

				board[i][col]=0;
				slashlookup[slash[i][col]]=false;
				backslashlookup[backslash[i][col]] = false;
				rowlookup[i] = false;
			}
		}
		return false;
	}


//return true if queen can be placed at row,col
//-------------------------------------------
	boolean isSafe(int board[][], int col, int row,int slash[][], int backslash[][], boolean backslashlookup[], boolean slashlookup[], boolean rowlookup[]){
		if(backslashlookup[backslash[row][col]] ||slashlookup[slash[row][col]] || rowlookup[row]){
				return false;
		}
		return true;
	}
//----------------------------------------

	public static void main(String[] args) {
		NQueenBNB qbnb = new NQueenBNB();
		Scanner obj = new Scanner(System.in);
		System.out.println("Enter value of N-: ");
		N = obj.nextInt();
		qbnb.solve();

	}


}
