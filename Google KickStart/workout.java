import java.util.*;
import java.io.*;
    
public class Solution {
    
    public static void main(String[] args) {
        
        Scanner sc = new Scanner(new BufferedReader(new InputStreamReader(System.in)));
        int T = sc.nextInt();
        
        for (int testCase = 1; testCase <= T; testCase++) {
            int N = sc.nextInt();
            int K = sc.nextInt();
            int [] workouts = new int[N];
            int diff = Integer.MIN_VALUE;
            for (int i = 0; i < N; i++) {
                int ai = sc.nextInt();
                workouts[i] = ai;
                if (i > 0) {
                    int t = ai - workouts[i-1];
                    if (t > diff) {
                        diff = t;
                    }
                }
            }
            
            int low = 1;
            int high = diff;
            while (low < high) {
                int ksum = 0;
                int mid = (low + high) / 2;
                for (int i = 1; i < N; i++) {
                    int ai = workouts[i] - workouts[i-1];
                    double v = Math.ceil((double) ai / mid) - 1;
                    ksum += v;
                }
                if (ksum <= K) {
                    high = mid;
                } else {
                    low = mid+1;
                }
            }            
            System.out.println("Case #" + testCase + ": " + low);
        }
    }
}