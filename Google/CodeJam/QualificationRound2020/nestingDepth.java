import java.util.*;
import java.io.*;
import java.util.stream.*;

public class Solution {
    public static String nestingDepth_inefficient(String line) {
        String o = "";
        for (int i = 0; i < line.length(); i++) {
            int curInt = Integer.parseInt(line.charAt(i) + "");
            String intStr = "(".repeat(curInt) + curInt + ")".repeat(curInt);
            o += intStr;
        }
        while (o.contains(")("))
            o = o.replaceAll("\\)\\(", "");
        return o;
    }
    public static String nestingDepth(String line) {
        if (line.length() == 1) {
            int val = Integer.parseInt(line);
            return val == 0 ? line : "(".repeat(val) + line + ")".repeat(val);
        }
        String o = "";
        String l = "0" + line + "0";
        for (int i = 1; i < l.length(); i++) {
            int current = Integer.parseInt(l.charAt(i) + "");
            int previous = Integer.parseInt(l.charAt(i - 1) + "");
            int diff = current - previous;
            if (current < previous) {
                diff *= -1;
                o += ")".repeat(diff) + current;
            } else if (current == previous) {
                o += current;
            } else {
                o += "(".repeat(diff) + current;
            }
        }
        return o.substring(0, o.length() - 1);
    }
    
    public static void main(String[] args) {
        Scanner in = new Scanner(new BufferedReader(new InputStreamReader(System.in)));
        int t = Integer.parseInt(in.nextLine());
        for (int i = 1; i <= t; ++i) {
            String line = in.nextLine();
            String result = nestingDepth(line);
            System.out.println("Case #" + i + ": " + result);
        }
    }
}
