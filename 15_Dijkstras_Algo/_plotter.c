#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

int count = 0;

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

        count++;
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

    while (n > 1 && ++count && heap[n]->distance < heap[parent(n)]->distance) {
        Info *temp = heap[n];
        heap[n] =  heap[parent(n)];
        heap[parent(n)] = temp;

        n = parent(n);
    }
}

bool isEmpty(MinHeap *minHeap) {
    return minHeap->size == 0;
}

void dijkstrasMinimumDistance(int n, int **graph, int source, FILE *output) {
    MinHeap *minHeap = newMinHeap(n * (n - 1));
    bool *vis = (bool *)malloc(n * sizeof(bool));
    int *dist = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        vis[i] = false;
        dist[i] = INT_MAX;
    }

    insertToMinHeap(minHeap, newInfo(source, dist[source] = 0));

    while (!isEmpty(minHeap)) {
        Info *info = removeFromMinHeap(minHeap);
        int src = info->vertex;
        int distance = info->distance;

        if (!vis[src]) {
            vis[src] = true;
            for (int dest = 0; dest < n; dest++) {
                count++;

                int weight = graph[src][dest];
                if (weight != 0 && distance + weight < dist[dest]) {
                    dist[dest] = distance + weight;
                    insertToMinHeap(minHeap, newInfo(dest, dist[dest]));
                }
            }
        }
    }

    fprintf(output, "\nSingle source shortest path:\n");
    for (int i = 0; i < n; i++) {
        fprintf(output, "%d ---- %d: %d\n", source, i, dist[i]);
    }

    fprintf(output, "----------------------------------------------------------------------\n");

    free(vis), free(dist), free(minHeap->heap), free(minHeap);
}

void plotter() {
    FILE *fpOutput = fopen("dijkstras_output.txt", "w");
    FILE *fpPlot = fopen("dijkstras_plot.txt", "w");

    for (int i = 0; i < 4; i++) {
        int source, n;

        printf("\nEnter the number of vertices: ");
        fprintf(fpOutput, "\nEnter the number of vertices: ");
        scanf("%d", &n);
        fprintf(fpOutput, "%d\n", n);

        int **graph = (int **)malloc(n * sizeof(int *));

        for (int i = 0; i < n; i++) {
            graph[i] = (int *)malloc(n * sizeof(int));
        }

        printf("\nEnter the adjacency matrix [Note: Enter 0 to indicate no edge]:\n");
        fprintf(fpOutput, "\nEnter the adjacency matrix [Note: Enter 0 to indicate no edge]:\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%d", &graph[i][j]);
                fprintf(fpOutput, "%d ", graph[i][j]);
            }

            fprintf(fpOutput, "\n");
        }

        printf("\nEnter the source vertex: ");
        fprintf(fpOutput, "\nEnter the source vertex: ");
        scanf("%d", &source);
        fprintf(fpOutput, "%d\n", source);

        count = 0;
        dijkstrasMinimumDistance(n, graph, source, fpOutput);
        fprintf(fpPlot, "%d\t%d\n", n, count);

        for (int i = 0; i < n; i++) {
            free(graph[i]);
        }

        free(graph);
    }

    fclose(fpOutput), fclose(fpPlot);
}

void main() {
    plotter();
}
