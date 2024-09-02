#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void heapify(int n, int *heap, int k) {
    int val = heap[k];
    bool isHeap = false;

    while (!isHeap && 2 * k <= n) {
        int j = 2 * k;
        if (j < n && heap[j + 1] > heap[j]) {
            j++;
        }

        if (val > heap[j]) {
            isHeap = true;
        } else {
            heap[k] = heap[j], k = j;
        }
    }

    heap[k] = val;
}

void heapSort(int n, int *heap) {
    for (int i = n / 2; i >= 1; i--) {
        heapify(n, heap, i);
    }

    for (int i = n; i > 1; i--) {
        int temp = heap[1];
        heap[1] = heap[i];
        heap[i] = temp;

        heapify(i - 1, heap, 1);
    }
}

int main() {
    int n;

    printf("\nEnter the size of the Array: ");
    scanf("%d", &n);

    int *arr = (int *)malloc((n + 1) * sizeof(int));

    printf("Enter %d Elements into the Array: ", n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("\nArray Before Sorting: ");
    for (int i = 1; i <= n; i++) {
        printf("%d ", arr[i]);
    }

    heapSort(n, arr);

    printf("\nArray After Sorting: ");
    for (int i = 1; i <= n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
