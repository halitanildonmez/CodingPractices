import java.io.*;
import java.math.*;
import java.security.*;
import java.text.*;
import java.util.*;
import java.util.concurrent.*;
import java.util.regex.*;

public class Solution {

    // Complete the minimumSwaps function below.
    static int minimumSwaps(int[] arr) {
        HashMap<Integer, Integer> nodeToNode = new HashMap<>();
        int cycle = 0;
        for (int i = 0; i < arr.length; i++) {
            int key = arr[i];
            int value = arr[key - 1];
            if (key != value)
                nodeToNode.put(key, value);
        }
        if (nodeToNode.isEmpty())
            return cycle;
        // start with the first key
        int key = nodeToNode.keySet().iterator().next();
        while (!nodeToNode.isEmpty()) {
            int value = nodeToNode.get(key);
            if (nodeToNode.containsKey(value)) {
                nodeToNode.remove(key);
                key = value;
                cycle++;
            } else {
                nodeToNode.remove(key);
                if (!nodeToNode.keySet().isEmpty())
                    key = nodeToNode.keySet().iterator().next();
            }
        }
        return cycle;

    }

    private static final Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) throws IOException {
        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(System.getenv("OUTPUT_PATH")));

        int n = scanner.nextInt();
        scanner.skip("(\r\n|[\n\r\u2028\u2029\u0085])?");

        int[] arr = new int[n];

        String[] arrItems = scanner.nextLine().split(" ");
        scanner.skip("(\r\n|[\n\r\u2028\u2029\u0085])?");

        for (int i = 0; i < n; i++) {
            int arrItem = Integer.parseInt(arrItems[i]);
            arr[i] = arrItem;
        }

        int res = minimumSwaps(arr);

        bufferedWriter.write(String.valueOf(res));
        bufferedWriter.newLine();

        bufferedWriter.close();

        scanner.close();
    }
}