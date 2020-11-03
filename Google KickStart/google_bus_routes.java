import java.util.*;
import java.io.*;
    
public class Solution {
    
    public static void main(String[] args) {
        
        Scanner sc = new Scanner(new BufferedReader(new InputStreamReader(System.in)));
        int T = sc.nextInt();
        
        for (int testCase = 1; testCase <= T; testCase++) {
            int N = sc.nextInt();
            long D = sc.nextLong();
            long [] busTimes = new long[N];
            for (int i = 0; i < N; i++) {
                long ai = sc.nextLong();
                busTimes[i] = ai;
            }
            long ans = D;
            for (int i = N - 1; i >= 0; i--) {
                long xi = busTimes[i];
                ans = ans - (ans % xi);
            }
            System.out.println("Case #" + 
                testCase + ": " + ans);
        }
    }
}