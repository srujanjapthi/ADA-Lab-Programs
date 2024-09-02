#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int partition(int *arr, int start, int end, int *split) {
    int pivot = arr[start];
    int left = start, right = end + 1;
    int count = 0;

    do {
        do {
            left++, count++;
        } while (left <= end && arr[left] < pivot);

        do {
            right--, count++;
        } while (arr[right] > pivot);

        if (left < right && arr[left] != arr[right]) {
            int temp = arr[left];
            arr[left] = arr[right];
            arr[right] = temp;
        }
    } while (left < right);

    *split = right;
    if (arr[right] != pivot) {
        arr[start] = arr[right];
        arr[right] = pivot;
    }

    return count;
}

int quickSort(int *arr, int start, int end) {
    if (start >= end) {
        return 0;
    } else {
        int split = 0;
        int count = partition(arr, start, end, &split);
        int left = quickSort(arr, start, split - 1);
        int right = quickSort(arr, split + 1, end);
        return left + right + count;
    }
}

void plotter() {
    FILE *fpBest = fopen("best_case.txt", "w");
    FILE *fpAvg = fopen("avg_case.txt", "w");
    FILE *fpWorst = fopen("worst_case.txt", "w");

    srand(time(NULL));
    for (int n = 2; n <= 1024; n *= 2) {
        int *arr = (int *)malloc(n * sizeof(int));

        // Best Case Data Generation
        for (int i = 0; i < n; i++) {
            arr[i] = 7;
        }

        fprintf(fpBest, "%d\t%d\n", n, quickSort(arr, 0, n - 1));

        // Average Case Data Generation
        for (int i = 0; i < n; i++) {
            arr[i] = rand() % 2000;
        }

        fprintf(fpAvg, "%d\t%d\n", n, quickSort(arr, 0, n - 1));

        // Worst Case Data Generation
        for (int i = 0; i < n; i++) {
            arr[i] = i;
        }

        fprintf(fpWorst, "%d\t%d\n", n, quickSort(arr, 0, n - 1));

        free(arr);
    }

    fclose(fpBest), fclose(fpAvg), fclose(fpWorst);
}

void main() {
    plotter();
}