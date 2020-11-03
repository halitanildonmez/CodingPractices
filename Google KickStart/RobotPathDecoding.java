import java.util.*;
import java.io.*;
import java.util.regex.*;
import java.awt.*;
import java.awt.geom.*;
    
public class Solution {

    
    public static String robotPathDecoder_Stack(String input) {
        Deque<Long> stack = new ArrayDeque<>();
        stack.add(1L);
        long a = 0L;
        long b = 0L;
        long max = 1000000000L;
        for (int i = 0; i < input.length(); i++) {
            char c = input.charAt(i);
            Long denom = stack.peekLast() == null ? 1L :
                    stack.peekLast();
            if (Character.isDigit(c)) {
                stack.add(denom * Integer.parseInt(c + "")%max);
            } else if (c == '(') {
                continue;
            } else if (c == ')') {
                stack.removeLast();
            } else {
                if (c == 'N') {
                    b -= denom;
                    b = ((b % max) + max) % max;
                } else if (c == 'S') {
                    b += denom;
                    b = (b % max);
                } else if (c == 'W') {
                    a -= denom;
                    a = ((a % max) + max) % max;
                } else if (c == 'E') {
                    a += denom;
                    a = (a % max);
                }
            }
        }
        return (a+1) + " " + (b+1);
    }
    
    public static void main(String[] args) {
        
        Scanner sc = new Scanner(new BufferedReader(new InputStreamReader(System.in)));
        int T = sc.nextInt();
        
        for (int testCase = 1; testCase <= T; testCase++) {
            String input = sc.next();
            System.out.println("Case #" + testCase + ": " + 
                robotPathDecoder_Stack(input));
        }
    }
}