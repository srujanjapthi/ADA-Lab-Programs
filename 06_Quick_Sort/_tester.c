#include <stdio.h>
#include <stdlib.h>

int partition(int *arr, int start, int end) {
    int pivot = arr[start];
    int left = start, right = end + 1;

    do {
        do {
            left++;
        } while (left <= end && arr[left] < pivot);

        do {
            right--;
        } while (arr[right] > pivot);

        if (left < right && arr[left] != arr[right]) {
            int temp = arr[left];
            arr[left] = arr[right];
            arr[right] = temp;
        }
    } while (left < right);


    if (arr[right] != pivot) {
        arr[start] = arr[right];
        arr[right] = pivot;
    }

    return right;
}

void quickSort(int *arr, int start, int end) {
    if (start < end) {
        int split = partition(arr, start, end);
        quickSort(arr, start, split - 1);
        quickSort(arr, split + 1, end);
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

    quickSort(arr, 0, n - 1);

    printf("\nArray After Sorting: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
