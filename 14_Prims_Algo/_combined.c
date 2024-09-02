#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

int count = 0;

typedef struct {
    int vertex;
    int parent;
    int weight;
} Info;

typedef struct {
    int size;
    Info **heap;
} MinHeap;

Info *newInfo(int vertex, int parent, int weight) {
    Info *info = (Info *)malloc(sizeof(Info));

    if (info == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    info->vertex = vertex;
    info->parent = parent;
    info->weight = weight;

    return info;
}

MinHeap *newMinHeap(int capacity) {
    MinHeap *minHeap = (MinHeap *)malloc(sizeof(MinHeap));

    if (minHeap == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    minHeap->size = 0;
    minHeap->heap = (Info **)malloc(capacity * sizeof(Info *));

    return minHeap;
}

void heapify(MinHeap *minHeap, int i) {
    int n = minHeap->size;
    Info **heap = minHeap->heap;
    Info *info = heap[i];
    bool isHeap = false;

    while (!isHeap && 2 * i <= n) {
        int j = 2 * i;

        count++;
        if (j < n && heap[j + 1]->weight < heap[j]->weight) {
            j++;
        }

        if (info->weight < heap[j]->weight) {
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
    if (--minHeap->size > 1) {
        heapify(minHeap, 1);
    }

    return minInfo;
}

int parent(int n) {
    return n / 2;
}

void insertToMinHeap(MinHeap *minHeap, Info *info) {
    int n = ++minHeap->size;
    Info **heap = minHeap->heap;
    heap[n] = info;

    while (n > 1 && ++count && heap[n]->weight < heap[parent(n)]->weight) {
        Info *temp = heap[n];
        heap[n] =  heap[parent(n)];
        heap[parent(n)] = temp;

        n = parent(n);
    }
}

bool isEmpty(MinHeap *minHeap) {
    return minHeap->size == 0;
}

void primsMST(int n, int **graph) {
    MinHeap *minHeap = newMinHeap(n * (n - 1));
    Info *mstEdges = (Info *)malloc(n * sizeof(Info));
    bool *vis = (bool *)malloc(n * sizeof(bool));
    int currIdx = 0;

    for (int i = 0; i < n; i++) {
        vis[i] = false;
    }

    insertToMinHeap(minHeap, newInfo(0, -1, 0));

    while (!isEmpty(minHeap)) {
        Info *info = removeFromMinHeap(minHeap);
        int src = info->vertex;
        int weight = info->weight;

        if (!vis[src]) {
            vis[src] = true;
            mstEdges[currIdx++] = *info;

            for (int dest = 0; dest < n; dest++) {
                count++;
                if (graph[src][dest] != 0) {
                    insertToMinHeap(minHeap, newInfo(dest, src, graph[src][dest]));
                }
            }
        }
    }

    printf("\nMST Edges:\n");
    for (int i = 1; i < n; i++) {
        printf(
            "%d ---- %d: weight = %d\n",
            mstEdges[i].parent,
            mstEdges[i].vertex,
            mstEdges[i].weight
        );
    }

    free(vis), free(mstEdges), free(minHeap->heap), free(minHeap);
}

int tester() {
    int n;

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

    primsMST(n, graph);

    for (int i = 0; i < n; i++) {
        free(graph[i]);
    }

    free(graph);

    return n;
}

void plotter() {
    FILE *fp = fopen("prims_plot.txt", "w");

    for (int i = 0; i < 4; i++) {
        count = 0;

        int n = tester();
        fprintf(fp, "%d\t%d\n", n, count);
    }

    fclose(fp);
}

void main() {
    int ch;

    printf("Enter:\n");
    printf("1. Tester\n");
    printf("2. Plotter\n");
    printf("Enter the choice: ");
    scanf("%d", &ch);

    switch (ch) {
        case 1:
            tester();
            break;

        case 2:
            plotter();
            break;
    }
}
