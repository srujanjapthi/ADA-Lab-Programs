#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int knapsackTopDownMemo(int n, int w, int weights[n], int values[n], int **memo) {
    if (memo[n][w] != -1) {
        return memo[n][w];
    } else if (weights[n - 1] <= w) {
        int pick = values[n - 1] + knapsackTopDownMemo(n - 1, w - weights[n - 1], weights, values, memo);
        int notPick = knapsackTopDownMemo(n - 1, w, weights, values, memo);

        return memo[n][w] = max(pick, notPick);
    } else {
        return memo[n][w] = knapsackTopDownMemo(n - 1, w, weights, values, memo);
    }
}

void composition(int n, int w, int weights[n], int **memo) {
    int remCapacity = w, item = n;

    printf("\nComposition: ");
    while (remCapacity != 0 && item > 0) {
        if (memo[item][remCapacity] != memo[item - 1][remCapacity]) {
            printf("%d ", item);
            remCapacity -= weights[item - 1];
        }

        item--;
    }

    printf("\n");
}

int main() {
    int n, w;

    printf("Enter the number of Items: ");
    scanf("%d", &n);
    printf("Enter the knapsack capacity: ");
    scanf("%d", &w);

    int weights[n], values[n];
    int **memo = (int **)malloc((n + 1) * sizeof(int *));

    for (int i = 0; i <= n; i++) {
        memo[i] = (int *)malloc((w + 1) * sizeof(int));
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= w; j++) {
            memo[i][j] = (i == 0 || j == 0) ? 0 : -1;
        }
    }

    printf("\nEnter weight and value of each item:\n");
    for (int i = 0; i < n; i++) {
        printf("Item %d: ", i + 1);
        scanf("%d%d", &weights[i], &values[i]);
    }

    int maxValue = knapsackTopDownMemo(n, w, weights, values, memo);

    printf("\nKnapsack Table:\n");
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= w; j++) {
            if (memo[i][j] == -1) {
                printf("NA ");
            } else {
                printf("%-2d ", memo[i][j]);
            }
        }

        printf("\n");
    }

    printf("\nMaximum profit: %d", maxValue);
    composition(n, w, weights, memo);

    for (int i = 0; i <= n; i++) {
        free(memo[i]);
    }

    free(memo);

    return 0;
}
