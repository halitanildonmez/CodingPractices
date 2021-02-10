import java.util.Scanner;

public class Solution {
    public static String bitsToString(int[] arr) {
        StringBuilder out = new StringBuilder(arr.length);
        for (int a : arr) {
            out.append(a);
        }
        return out.toString();
    }
    
    private static int readBit(Scanner scanner, int bitIndex) {
        System.out.println(bitIndex);
        System.out.flush();
        int next = scanner.nextInt();
        return next;
    }

    private static int[] reversed(int[] arr) {
        int[] output = new int[arr.length];
        for (int i = 0; i < arr.length; i++) {
            output[i] = arr[arr.length - 1 - i];
        }
        return output;
    }

    private static int[] negated(int[] arr) {
        int[] output = new int[arr.length];
        for (int i = 0; i < arr.length; i++) {
            if (arr[i] == 1)
                output[i] = 0;
            else
                output[i] = 1;
        }
        return output;
    }

    public static boolean findBits(Scanner scanner, int B) {
        int[] bits = new int[B];

        if (B == 10) {
            // No need to do something complex
            for (int i = 0; i < B; i++) {
                int bit = readBit(scanner, i + 1);
                bits[i] = bit;
            }
        } else {
            int moveNum = 0;
            int actualBitIndex = 0;
            int sameBitIndex = -1;
            int diffBitIndex = -1;
            while (actualBitIndex < (B / 2)) {
                if (moveNum % 10 == 0) {
                    boolean sameChanged = false;
                    boolean oppositeChanged = false;
                    if (sameBitIndex != -1) {
                        int sameTest = readBit(scanner, sameBitIndex);
                        int siOrig = bits[sameBitIndex - 1];
                        if (sameTest != siOrig) {
                            sameChanged = true;
                        }
                    } else {
                        // have to make a move
                        readBit(scanner, 1);
                    }
                    if (diffBitIndex != -1) {
                        int diffTest = readBit(scanner, diffBitIndex);
                        int dOrig = bits[diffBitIndex - 1];
                        if (dOrig != diffTest) {
                            oppositeChanged = true;
                        }
                    } else {
                        // have to make a move
                        readBit(scanner, 1);
                    }

                    if (!sameChanged && oppositeChanged) {
                        bits = reversed(bits);
                    } else if (sameChanged && !oppositeChanged) {
                        bits = reversed(negated(bits));
                    } else if (sameChanged && oppositeChanged) {
                        bits = negated(bits);
                    }
                } else {
                    int startBit = readBit(scanner, actualBitIndex + 1);
                    int endBit = readBit(scanner, B - actualBitIndex);
                    if (startBit == endBit && sameBitIndex == -1) {
                        sameBitIndex = actualBitIndex + 1;
                    } else if (startBit != endBit && diffBitIndex == -1){
                        diffBitIndex = actualBitIndex + 1;
                    }
                    bits[actualBitIndex] = startBit;
                    bits[B - actualBitIndex - 1] = endBit;
                    actualBitIndex++;
                }
                moveNum += 2;
            }
        }

        String res = bitsToString(bits);
        System.out.println(res);
        System.out.flush();

        char response = scanner.next().charAt(0);
        return response == 'Y';
    }

    public static void main(String[] args) {
        try (Scanner in = new Scanner(System.in)) {
            int T = in.nextInt();
            int B = in.nextInt();
            for (int i = 1; i <= T; i++) {
                boolean r = findBits(in, B);
                if (!r) {
                    break;
                }
            }
        }
    }
}
