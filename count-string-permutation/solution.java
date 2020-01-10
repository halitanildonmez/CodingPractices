class Solution {
    public int countVowelPermutation(int n) {
        if (n == 1)
            return 5;
        int VOVELS_SIZE = 5;
        long [][] dp = new long[n + 1][VOVELS_SIZE];

        for (int j = 0; j < 2; j++) {
            for (int i = 0; i < VOVELS_SIZE; i++) {
                dp[j][i] = j;
            }
        }

        long mod = 1000000007L;

        for (int i = 2; i < n + 1; i++) {
            // a
            dp[i][0] = dp[i-1][1];
            // e
            dp[i][1] = ((dp[i-1][0] + dp[i-1][2]) % mod);
            // i
            dp[i][2] = dp[i-1][0] + dp[i-1][4] + dp[i-1][1] + dp[i-1][3];
            // o
            dp[i][3] = ((dp[i-1][2] + dp[i-1][4]) % mod);
            // u
            dp[i][4] = dp[i-1][0];
        }
        long result = (dp[n][0] + dp[n][1] + dp[n][2] + dp[n][3] + dp[n][4]) % mod;
        return (int) result;
    }
}