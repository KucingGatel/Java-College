#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// nilai vertex dan infinite
#define V 9
#define INF 99999

// struct untuk menyimpan informasi setiap vertex
struct Vertex {
    int dist;
    int prev;
    bool visited;
};

// algoritma dijkstra
void dijkstra(int graph[V][V], int start) {

    // Atur default jarak setiap vertex dari start
    struct Vertex v[V];
    for(int i = 0; i < V; i++) {
        v[i].dist = INF;
        v[i].visited = false;
        v[i].prev = -1;
    }
    v[start].dist = 0;
    v[start].visited = true;
    v[start].prev = 0;

    // perulangan sejumlah vertex untuk mencari jarak terpendek
    printf("\nProses Algoritma : \n\n");
    for(int h = 0; h < V; h++) {

        // atur variabel awal
        int index, min = INF;

        // iterasi setiap vertex 
        for(int i = 0; i < V; i++) {
            if(v[i].visited) {

                // update nilai jarak pada dist
                for(int j = 0; j < V; j++) {
                    if(graph[i][j] != 0 && v[i].dist + graph[i][j] < v[j].dist) {
                        v[j].dist = v[i].dist + graph[i][j];
                        v[j].prev = i;
                        graph[i][j] = 0;
                    }
                }
            }

            // mencari jarak minimun dari vertex pada dist
            for(int k = 0; k < V; k++) {
                if(v[k].dist < min && !v[k].visited) {
                    min = v[k].dist;
                    index = k;
                }
            }
        }

        // tandai vertex telah dikunjungi
        v[index].visited = true;

        // proses algoritma dijkstra
        for(int k = 0; k < V; k++) printf("%-6d", v[k].dist);
        printf("\n");
    }

    // print hasil dijkstra
    printf("\nHasil Algoritma Dijkstra : \n");
    printf("\n------------------\n");
    printf("| Vertex | Jarak |");
    printf("\n------------------\n");
    for(int i = 0; i < V; i++) {
        printf("| %d\t | %-6d|\n", i, v[i].dist);
    }
    printf("------------------\n\n");

    // print hasil rute dijkstra
    for(int i = 0; i < V; i++) {
        printf("Jalur dari vertex %d ke %d : ", start, i);
        if(i == start) printf("%d -> %d\n", start, start);
        else {

            // atur variabel awal
            int path[V];
            int top = -1;
            int x = i;

            // menelurusi jalur dari x menuju start
            while(x != start) {
                if(v[x].prev == -1) x = start;
                else {
                    path[++top] = x;
                    x = v[x].prev;
                }
            }
            path[++top] = start;

            // print jalur dari start menuju x
            while(top > 0) printf("%d -> ", path[top--]);
            printf("%d\n", path[top]);
        }
    }
    printf("\n");
}

int main() {
    // system("cls");

    // deklarasi graph tidak berarah
    int UD_GRAPH[V][V] = {
        {0, 4, 0, 0, 0, 0, 0, 8, 0},
        {4, 0, 8, 0, 0, 0, 0,11, 0},
        {0, 8, 0, 7, 0, 4, 0, 0, 2},
        {0, 0, 7, 0, 9,14, 0, 0, 0},
        {0, 0, 0, 9, 0,10, 0, 0, 0},
        {0, 0, 4,14,10, 0, 2, 0, 0},
        {0, 0, 0, 0, 0, 2, 0, 1, 6},
        {8,11, 0, 0, 0, 0, 1, 0, 7},
        {0, 0, 2, 0, 0, 0, 6, 7, 0}
    };
    // deklarasi graph berarah
    int D_GRAPH[V][V] = {
        {0, 4, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 8, 0, 0, 0, 0,11, 0},
        {0, 0, 0, 0, 0, 4, 0, 0, 2},
        {0, 0, 7, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 9, 0, 0, 0, 0, 0},
        {0, 0, 0,14,10, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 2, 0, 0, 0},
        {8, 0, 0, 0, 0, 0, 1, 0, 7},
        {0, 0, 0, 0, 0, 0, 6, 0, 0}
    };

    // Memulai program
    printf("===========================\n");
    printf("  Program Jalur Terpendek\n");
    printf("===========================\n");

    // Memilih titik awal algoritma
    int start;
    printf("\nPilih vertex awal (0-8) : ");
    scanf("%d", &start);

    // Memilih program graph berarah atau tidak
    int choice;
    printf("\nMenu : \n");
    printf("1. Graf tak berarah\n");
    printf("2. Graf berarah\n");
    printf("\nPilih : ");
    scanf("%d", &choice);

    // switch case pilihan program
    switch (choice) {
    case 1:
        dijkstra(UD_GRAPH, start);
        break;
    case 2:
        dijkstra(D_GRAPH, start);
        break;
    default:
        printf("\nProgram tidak tersedia.\n");
        break;
    }

    return 0;
}