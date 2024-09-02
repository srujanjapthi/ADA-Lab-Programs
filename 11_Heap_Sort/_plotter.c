#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int heapify(int n, int *heap, int k) {
    int val = heap[k];
    bool isHeap = false;
    int count = 0;

    while (!isHeap && 2 * k <= n) {
        int j = 2 * k;

        count++;
        if (j < n && ++count && heap[j + 1] > heap[j]) {
            j++;
        }

        if (val > heap[j]) {
            isHeap = true;
        } else {
            heap[k] = heap[j];
            k = j;
        }
    }

    heap[k] = val;

    return count;
}

int heapSort(int n, int *heap) {
    int count1 = 0, count2 = 0;

    for (int i = n / 2; i >= 1; i--) {
        count1 += heapify(n, heap, i);
    }

    for (int i = n; i > 1; i--) {
        int temp = heap[1];
        heap[1] = heap[i];
        heap[i] = temp;

        count2 += heapify(i - 1, heap, 1);
    }

    return count1 > count2 ? count1 : count2;
}

void plotter() {
    FILE *fpBest = fopen("best_case.txt", "w");
    FILE *fpWorst = fopen("worst_case.txt", "w");

    for (int n = 10; n <= 100; n += 10) {
        int *arr = (int *)malloc((n + 1) * sizeof(int));

        // Best Case Data Generation
        for (int i = 1; i <= n; i++) {
            arr[i] = n - i;
        }

        fprintf(fpBest, "%d\t%d\n", n, heapSort(n, arr));

        // Worst Case Data Generation
        for (int i = 1; i <= n; i++) {
            arr[i] = i;
        }

        fprintf(fpWorst, "%d\t%d\n", n, heapSort(n, arr));

        free(arr);
    }

    fclose(fpBest), fclose(fpWorst);
}

void main() {
    plotter();
}
