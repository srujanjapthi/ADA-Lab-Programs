#include <stdio.h>
#include <stdlib.h>

void insertionSort(int n, int *arr) {
    for (int i = 1; i < n; i++) {
        int element = arr[i], j = i - 1;
        while (j >= 0 && arr[j] > element) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = element;
    }
}

int main() {
    int n;
    printf("Enter the size of the Array: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));
    printf("Enter Elements of the Array: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("\nArray Before Sorting: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    insertionSort(n, arr);

    printf("\nArray After Sorting: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
