#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

typedef struct {
    int vertex;
    int distance;
} Info;

typedef struct {
    int size;
    Info **heap;
} MinHeap;

Info *newInfo(int vertex, int distance) {
    Info *info = (Info *)malloc(sizeof(Info));

    if (info == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    info->vertex = vertex;
    info->distance = distance;

    return info;
}

MinHeap *newMinHeap(int capacity) {
    MinHeap *priorityQueue = (MinHeap *)malloc(sizeof(MinHeap));

    if (priorityQueue == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    priorityQueue->size = 0;
    priorityQueue->heap = (Info **)malloc(capacity * sizeof(Info *));

    return priorityQueue;
}

void heapify(MinHeap *minHeap, int i) {
    if (minHeap->size == 0) {
        return;
    }

    int n = minHeap->size;
    Info **heap = minHeap->heap;
    Info *info = heap[i];
    bool isHeap = false;

    while (!isHeap && 2 * i <= n) {
        int j = 2 * i;
        if (j < n && heap[j + 1]->distance < heap[j]->distance) {
            j++;
        }

        if (info->distance < heap[j]->distance) {
            isHeap = true;
        } else {
            heap[i] = heap[j];
            i = j;
        }
    }

    heap[i] = info;
}

Info *removeFromMinHeap(MinHeap *minHeap) {
    int n = minHeap->size;
    Info *minInfo = minHeap->heap[1];

    minHeap->heap[1] = minHeap->heap[n];
    minHeap->size--;
    heapify(minHeap, 1);

    return minInfo;
}

int parent(int n) {
    return n / 2;
}

void insertToMinHeap(MinHeap *minHeap, Info *info) {
    int n = ++minHeap->size;
    Info **heap = minHeap->heap;
    heap[n] = info;

    while (n > 1 && heap[n]->distance < heap[parent(n)]->distance) {
        Info *temp = heap[n];
        heap[n] =  heap[parent(n)];
        heap[parent(n)] = temp;

        n = parent(n);
    }
}

bool isEmpty(MinHeap *minHeap) {
    return minHeap->size == 0;
}

void dijkstrasMinimumDistance(int n, int **graph, int source) {
    MinHeap *minHeap = newMinHeap(n * (n - 1));
    bool *vis = (bool *)malloc(n * sizeof(bool));
    int *dist = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        vis[i] = false;
        dist[i] = INT_MAX;
    }

    insertToMinHeap(minHeap, newInfo(source, 0));
    dist[source] = 0;

    while (!isEmpty(minHeap)) {
        Info *info = removeFromMinHeap(minHeap);
        int src = info->vertex;
        int distance = info->distance;

        if (!vis[src]) {
            vis[src] = true;
            for (int dest = 0; dest < n; dest++) {
                if (graph[src][dest] != 0 && distance + graph[src][dest] < dist[dest]) {
                    dist[dest] = distance + graph[src][dest];
                    insertToMinHeap(minHeap, newInfo(dest, dist[dest]));
                }
            }
        }
    }

    printf("\nSingle source shortest path:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ---- %d: %d\n", source, i, dist[i]);
    }

    free(vis), free(dist), free(minHeap->heap), free(minHeap);
}

void main() {
    int n, source;

    printf("\nEnter the number of vertices: ");
    scanf("%d", &n);

    int **graph = (int **)malloc(n * sizeof(int *));

    for (int i = 0; i < n; i++) {
        graph[i] = (int *)malloc(n * sizeof(int));
    }

    printf("\nEnter the adjacency matrix [Note: Enter 0 to indicate no edge]:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("\nEnter the source vertex: ");
    scanf("%d", &source);

    dijkstrasMinimumDistance(n, graph, source);

    for (int i = 0; i < n; i++) {
        free(graph[i]);
    }

    free(graph);
}
