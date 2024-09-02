#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int binarySearch(int *arr, int key, int low, int high) {
    int mid = (low + high) >> 1;
    if (low > high) {
        // Key not found
        return 0;
    } else if (arr[mid] == key) {
        // Key Found
        return 1;
    } else if (arr[mid] > key) {
        // Search in the left half
        return binarySearch(arr, key, low, mid - 1) + 1;
    } else {
        // Search in the right half
        return binarySearch(arr, key, mid + 1, high) + 1;
    }
}

void plotter() {
    FILE *fpBest = fopen("best_case.txt", "w");
    FILE *fpAvg = fopen("avg_case.txt", "w");
    FILE *fpWorst = fopen("worst_case.txt", "w");

    srand(time(NULL));
    for (int n = 2; n < 10000; n *= 2) {
        int *arr = (int *)malloc(n * sizeof(int));

        // Data Generation
        for (int i = 0; i < n; i++) {
            arr[i] = i;
        }

        // Best Case => key = arr[0];
        fprintf(fpBest, "%d\t%d\n", n, binarySearch(arr, arr[(n - 1) >> 1], 0, n - 1));

        // Average Case => key = rand() % n
        fprintf(fpAvg, "%d\t%d\n", n, binarySearch(arr, rand() % n, 0, n - 1));

        // Worst Case => key = n + 1 => Element which is not present in the Array.
        fprintf(fpWorst, "%d\t%d\n", n, binarySearch(arr, n, 0, n - 1));

        free(arr);
    }

    fclose(fpBest), fclose(fpAvg), fclose(fpWorst);
}


void main() {
    plotter();
}
