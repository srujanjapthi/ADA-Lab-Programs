#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int linearSearch(int n, int *arr, int key) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        count++;
        if (arr[i] == key) {
            return count;
        }
    }

    return count;
}

void plotter() {
    FILE *fpBest = fopen("linear_best.txt", "w");
    FILE *fpAvg = fopen("linear_avg.txt", "w");
    FILE *fpWorst = fopen("linear_worst.txt", "w");

    srand(time(NULL));
    for (int n = 10; n <= 30000; n = n < 10000 ? n * 10 : n + 10000) {
        int *arr = (int *)malloc(n * sizeof(int));

        // Data Generation
        for (int i = 0; i < n; i++) {
            arr[i] = i;
        }

        // Best Case => key = arr[0];
        fprintf(fpBest, "%d\t%d\n", n, linearSearch(n, arr, arr[0]));

        // Average Case => key = rand() % n
        fprintf(fpAvg, "%d\t%d\n", n, linearSearch(n, arr, rand() % n));

        // Worst Case => key = n + 1 => Element which is not present in the Array.
        fprintf(fpWorst, "%d\t%d\n", n, linearSearch(n, arr, n));

        free(arr);
    }

    fclose(fpBest), fclose(fpAvg), fclose(fpWorst);
}

void main() {
    plotter();
}
