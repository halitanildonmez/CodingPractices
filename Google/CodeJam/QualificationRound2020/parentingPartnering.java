import java.util.*;
import java.io.*;
import java.util.stream.*;

public class Solution {
    static class Pairs {
        private final int start;
        private final int end;
        private final int index;

        public Pairs(int start, int end, int index) {
            this.start = start;
            this.end = end;
            this.index = index;
        }

        public int getStart() {
            return start;
        }

        public int getEnd() {
            return end;
        }

        public int getIndex() {
            return index;
        }
    }
    public static String parentingPartneringReturns(String[] lines) {
        List<Pairs> intervals = new ArrayList<>();
        for(int i = 0; i < lines.length; i++) {
            String line = lines[i];
            String[] s = line.split(" ");
            int start = Integer.parseInt(s[0]);
            int end = Integer.parseInt(s[1]);
            intervals.add(new Pairs(start, end, i));
        }
        intervals.sort(Comparator.comparing(Pairs::getStart));

        Pairs endJ = null;
        Pairs endC = null;
        String[] output = new String[lines.length];
        // greedy interval scheduling problem
        for (int i = 0; i < intervals.size(); i++) {
            Pairs e = intervals.get(i);
            if (endJ == null || (endJ.getEnd() <= e.getStart())) {
                endJ = e;
                output[e.getIndex()] = "J";
            } else if (endC == null || endC.getEnd() <= e.getStart()) {
                endC = e;
                output[e.getIndex()] = "C";
            } else {
                return "IMPOSSIBLE";
            }
        }
        return String.join("", output);     
    }
    
    public static void main(String[] args) {
        Scanner in = new Scanner(new BufferedReader(new InputStreamReader(System.in)));
        int t = Integer.parseInt(in.nextLine());
        for (int i = 1; i <= t; ++i) {
            int N = Integer.parseInt(in.nextLine());
            String[] lines = new String[N];
            for (int j = 0; j < N; j++) {
                lines[j] = in.nextLine();
            }
            String res = parentingPartneringReturns(lines);
            System.out.println("Case #" + i + ": " + res);
        }
    }
}
