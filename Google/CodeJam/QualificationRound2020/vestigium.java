import java.util.*;
import java.io.*;
import java.util.stream.*;

public class Solution {
    public static int[] vestigium(int N, String[] arrayLines) {
        int[][] arr = new int[N][N];
        int duplicateRowNum = 0;
        int duplicateColNum = 0;
        int eigval = 0;
        Set<Integer> set = new HashSet<>();
        
        for (int j = 0; j < arrayLines.length; j++) {
            String line = arrayLines[j];
            String[] s = line.split(" ");
            int[] ints = Arrays.stream(s)
                    .mapToInt(Integer::parseInt)
                    .toArray();
            for (int a : ints){
                if (!set.add(a)) {
                    duplicateRowNum++;
                    set.clear();
                    break;
                }
            }
            System.arraycopy(ints, 0, arr[j], 0, ints.length);
            set.clear();
        }

        for (int col = 0; col < N; col++) {
            set.clear();
            for (int i = 0; i < N; i++) {
                int elem = arr[i][col];
                if (!set.add(elem)) {
                    duplicateColNum++;
                    set.clear();
                    break;
                }
            }
        }
        set.clear();

        for (int i = 0; i < N; i++) {
            eigval += arr[i][i];
        }

        return new int[]{eigval, duplicateRowNum, duplicateColNum};       
    }
    
    public static void main(String[] args) {
        Scanner in = new Scanner(new BufferedReader(new InputStreamReader(System.in)));
        int t = in.nextInt(); // Scanner has functions to read ints, longs, strings, chars, etc.
        for (int i = 1; i <= t; ++i) {
            int N = in.nextInt();
            in.nextLine();
            String[] lines = new String[N];
            for (int j = 0; j < N; j++) {
                String line = in.nextLine();
                lines[j] = line;
            }
            int[] res = vestigium(N, lines);
            System.out.println("Case #" + i + ": " + res[0] + " " + res[1] + " " + res[2]);
        }
    }
}
