import java.util.*;
import java.io.*;
    
public class Solution {
    public static void main(String[] args) {
        
        Scanner sc = 
            new Scanner(new BufferedReader(new InputStreamReader(System.in)));
        int T = sc.nextInt();
        
        for (int testCase = 1; testCase <= T; testCase++) {
            int N = sc.nextInt();
            int K = sc.nextInt();
            int P = sc.nextInt();
            
            int[][] sum = new int[N+1][K+1];
            int[][] dp = new int[N+1][P+1];
            
            for (int i = 1; i <= N; i++) {
                for (int j = 1; j <= K; j++) {
                    int ai = sc.nextInt();
                    sum[i][j] = ai + sum[i][j-1];
                }
            }
            
            
            for (int i = 1; i <= N; i++) {
                for (int j = 0; j <= P; j++) {
                    dp[i][j] = 0;
                    for (int x = 0, isum = 0; x <= Math.min(j, K); x++) {
                        dp[i][j] = Math.max(dp[i][j], sum[i][x] + dp[i-1][j-x]);
                    }
                }
            }
            System.out.println("Case #" + testCase + ": " + dp[N][P]);
        }
    }
}