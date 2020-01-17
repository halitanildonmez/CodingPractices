import java.util.*;

/**
 * Kattis does not allow import javafx.util.Pair; package for some reason.
 *
 * So in order to use pairs I created this class. Hastily written since I wanted to
 * move fast
 * */
class CustomPair {
    // I should add getters and setters but that would take too long
    Integer a, b;
    public CustomPair(int a, int b) {
        this.a = a;
        this.b = b;
    }
    /**
     * Needs to be overridden to be used as a key
     * */
    @Override
    public boolean equals(Object o) {
        if (this == o)
            return true;
        if (o == null || getClass() != o.getClass())
            return false;
        CustomPair c = (CustomPair)o;
        if (c.a == a && c.b == b)
            return true;
        return false;
    }
    /**
     * Needs to be overridden to be used as a key. I used a tutorial to come up with this
     * */
    @Override
    public int hashCode() {
        int result = (int) (a ^ (a >>> 32));
        result = 31 * result + (b != null ? b.hashCode() : 0);
        result = 31 * result + (a != null ? a.hashCode() : 0);
        result = 31 * result + (b != null ? b.hashCode() : 0);
        return result;
    }
}

public class Main {
    // Fixed size to accommodate all potential sizes
    private static final int N = 110;
    // trick to get 4 neighbours for a given point
    private static final int[] X_NEIG_INDEX = {1,-1,0,0};
    private static final int[] Y_NEIG_INDEX = {0,0,1,-1};
    /**
     * Checks the number for being a prime number
     * */
    private static boolean isPrime(int n) {
        if (n == 2)
            return true;
        if (n <= 1 || n % 2 == 0)
            return false;
        for (int i = 3; i <= Math.sqrt(n); i+=2) {
            if (n % i == 0)
                return false;
        }
        return true;
    }
    /**
     * Enum is for keeping track of the direction
     * */
    enum Direction{
        RIGHT, UP, LEFT, DOWN;
    }
    public static void main(String[] args) {
        // map would not have been necessary but I used it to keep track of iterated places.
        // Not good to keep here but due to time I will just keep it.
        int[][] map = new int[N][N];
        // 1D to 2D index map
        CustomPair[] indToVal = new CustomPair[(N * N) + 1];
        // 2D to value map
        Map<CustomPair, Integer> gridToValue = new HashMap<>();
        // Direction to start
        Direction dir = Direction.RIGHT;
        int j = 1;
        int y = N / 2;
        // shift left for even n's
        int x = (N % 2 == 0) ? y - 1 : y;
        /**
         * We use y, x here because the grid is sort of turned around.
         * */
        while(j <= ((N * N))) {
            CustomPair currentIndex = new CustomPair(y, x);
            // if the number is not prime it is traversable
            if (!isPrime(j)) {
                map[y][x] = 1;
                gridToValue.put(currentIndex, j);
            } else {
                map[y][x] = -1;
            }
            // add the value to 1d to 2d index values
            indToVal[j] = currentIndex;
            switch(dir){
                case RIGHT:
                    if(x <= (N - 1) && map[y - 1][x] == 0 && j > 1)
                        dir = Direction.UP;
                    break;
                case UP:
                    if(map[y][x - 1] == 0)
                        dir = Direction.LEFT;
                    break;
                case LEFT:
                    if(x == 0 || map[y + 1][x] == 0)
                        dir = Direction.DOWN;
                    break;
                case DOWN:
                    if(map[y][x + 1] == 0)
                        dir = Direction.RIGHT;
                    break;
            }
            // update the grid index
            switch(dir){
                case RIGHT:
                    x++;
                    break;
                case UP:
                    y--;
                    break;
                case LEFT:
                    x--;
                    break;
                case DOWN:
                    y++;
                    break;
            }
            // update 1D index
            j++;
        }

        Scanner sc = new Scanner(System.in);
        int caseNum = 1;
        while (sc.hasNextInt()) {
            int start = sc.nextInt();
            int goal = sc.nextInt();
            // find the shortest path
            Queue<CustomPair> q = new LinkedList<>();
            // 2D grid to distance values
            Map<CustomPair, Integer> distMap = new HashMap<>();
            // start is 0
            distMap.put(indToVal[start], 0);
            q.add(indToVal[start]);
            while (!q.isEmpty()) {
                CustomPair cur = q.remove();
                // for each neighbour (4 potential moves)
                for (int i = 0; i < 4; i++) {
                    int nx = cur.a + X_NEIG_INDEX[i];
                    int ny = cur.b + Y_NEIG_INDEX[i];
                    CustomPair neighP = new CustomPair(nx, ny);
                    // if the value is not in the grid
                    if (!gridToValue.containsKey(neighP))
                        continue;
                    // if the value is already visited
                    if (distMap.containsKey(neighP))
                        continue;
                    distMap.put(neighP, distMap.get(cur) + 1);
                    q.add(neighP);
                }
            }
            // print for Kattis reasons
            String msg = "Case " + caseNum + ": ";
            if (!distMap.containsKey(indToVal[goal]) ||
                    distMap.getOrDefault(indToVal[goal], -1) == -1 && start != goal)
                System.out.println(msg + " impossible");
            else
                System.out.println(msg + "" + distMap.get(indToVal[goal]));
            caseNum++;
        }
    }
}
