import java.io.*;
import java.math.*;
import java.security.*;
import java.text.*;
import java.util.*;
import java.util.concurrent.*;
import java.util.regex.*;

public class Solution {

    // Complete the checkMagazine function below.
    static void checkMagazine(String[] magazine, String[] note) {
        HashMap<String, Integer> numbers = new HashMap<String, Integer>();
        for (int i = 0; i < magazine.length; i++) {
            String n = magazine[i];
            if (numbers.containsKey(n)) {
                int val = numbers.get(magazine[i]);
                val++;
                numbers.put(n, val);
            } else {
                numbers.put(n, 0);
            }
        }
        for (int i = 0; i < note.length; i++) {
            String n = note[i];
            if (!numbers.containsKey(n)) {
                System.out.println("No");
                return;
            } else {
                int v = numbers.get(n);
                if (v == 0) {
                    numbers.remove(n);
                } else {
                    v--;
                    numbers.put(n, v);
                }
            }
        }
        System.out.println("Yes");
    }

    private static final Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        String[] mn = scanner.nextLine().split(" ");

        int m = Integer.parseInt(mn[0]);

        int n = Integer.parseInt(mn[1]);

        String[] magazine = new String[m];

        String[] magazineItems = scanner.nextLine().split(" ");
        scanner.skip("(\r\n|[\n\r\u2028\u2029\u0085])?");

        for (int i = 0; i < m; i++) {
            String magazineItem = magazineItems[i];
            magazine[i] = magazineItem;
        }

        String[] note = new String[n];

        String[] noteItems = scanner.nextLine().split(" ");
        scanner.skip("(\r\n|[\n\r\u2028\u2029\u0085])?");

        for (int i = 0; i < n; i++) {
            String noteItem = noteItems[i];
            note[i] = noteItem;
        }

        checkMagazine(magazine, note);

        scanner.close();
    }
}