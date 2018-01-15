import java.util.*;

class TestClass {
    
    static boolean isAttacked (int x, int y, int board[][], int N) {
        for (int i = 0; i < N; i++) {
            if (board[x][i] == 1 || board [i][y] == 1) {
                return true;
            }
                
        }
        
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (i + j == x + y || i - j == x - y) {
                    if (board[i][j] == 1) {
                        return true;   
                    }
               }
            }
        }
       
       return false;
    }
    
    static boolean NQueens (int board[][], int N, int queens) {
        if (queens == 0)
            return true;
            
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (isAttacked (i, j, board, N)) {
                    continue;
                } 
                
                board[i][j] = 1;
                
                if (NQueens (board, N, queens-1)) {
                    return true;
                }
                
                board [i][j] = 0;
            }
        }
        return false;
    }
    
    public static void main(String args[] ) throws Exception {
        int N = 0;
        Scanner s = new Scanner(System.in);
        N = s.nextInt ();
        int board[][] = new int [N][N];
    
        if (!NQueens (board, N, N))
            System.out.println ("Not possible");
        else {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    System.out.print (board[i][j] + " ");
                }
                System.out.println ();
            }
        }
    }
}
