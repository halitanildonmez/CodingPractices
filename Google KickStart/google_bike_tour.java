import java.util.*;
import java.io.*;
    
public class Solution {
    
    public static void main(String[] args) {
        
        Scanner sc = new Scanner(new BufferedReader(new InputStreamReader(System.in)));
        int T = sc.nextInt();
        
        for (int testCase = 1; testCase <= T; testCase++) {
            int N = sc.nextInt();
            int [] houses = new int[N];
            for (int i = 0; i < N; i++) {
                int ai = sc.nextInt();
                houses[i] = ai;
            }
            int peaks = 0;
            for (int i = 1; i < N - 1; i++) {
                int cur = houses[i];
                if (cur > houses[i-1] && cur > houses[i+1])
                    peaks++;
            }
            System.out.println("Case #" + testCase + ": " + peaks);
        }
    }
}