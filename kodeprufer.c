#include <stdio.h>
#include <stdlib.h>

// fungsi kode prufer
void prufer(int nodes, int matrix[nodes][nodes], int length, int code[length], int index, int count) {

    // mengecek derajat vertex
    int degree[nodes];                        // deklarasi array derajat vertex
    for(int i = 0; i < nodes; i++) {
        degree[i] = 0;                        // set default derajat menjadi 0
        for(int j = 0; j < nodes; j++) {
            degree[i] += matrix[i][j];        // tambahkan derajat sesuai banyaknya edge
        }
    }

    // melakukan algoritma kode prufer
    for(int i = 0; i < nodes; i++) {
        if(degree[i] == 1 && count <= length) { // cek vertex berderajat 1
            for(int j = 0; j < nodes; j++) {
                if(matrix[i][j] == 1) {       // cek vertex yang berhubungan
                    matrix[i][j] = 0;         // putuskan hubungannya
                    matrix[j][i] = 0;
                    code[index] = j;          // vertex yang berhubungan menjadi code
                    index++;                  // inisiasi untuk index selanjutnya
                    printf("\nEdge %d %d dihapus.\n", i+1, j+1);
                    printf("Vertex %d ditambahkan pada code.\n", j+1);
                    break;
                }
            }
            count++;
            prufer(nodes, matrix, length, code, index, count); // lakukan fungsi untuk index selanjutnya
            break;
        }
    }
}

int main() {
    system("cls");                            // clear screen terminal

    // input total vertex
    int nodes;                                // deklarasi var total vertex
    printf("Masukkan jumlah vertex : ");
    scanf("%d", &nodes);                      // masukkan total vertex

    // inisialisasi matriks ketetanggaan
    int matrix[nodes][nodes];                 // deklarasi matriks baris=kolom
    for(int i = 0; i < nodes; i++) {
        for(int j = 0; j < nodes; j++) {
            matrix[i][j] = 0;                 // set default nilai matriks menjadi 0
        }
    }

    // tambahkan egdes tree
    int edges = nodes-1;                      // total edge adalah node - 1
    for(int i = 0; i < edges; i++) {
        int v1, v2;                           // deklarasi 2 var vertex berhubungan
        printf("Tambahkan edge dari : ");
        scanf("%d %d", &v1, &v2);             // user input 2 vertex berhubungan
        matrix[v1-1][v2-1] = 1;               // inputkan edge tree pada matriks
        matrix[v2-1][v1-1] = 1;
    }

    // inisialisasi variabel untuk prufer
    int length = nodes-2;                        // panjang code adalah total vertex - 2
    int code[length];                            // deklarasi array prufer code
    int index = 0;                               // deklarasi index awal code

    // print proses pengkodean tree
    printf("\nProses Pengkodean Tree : \n");
    prufer(nodes, matrix, length, code, index, 1);  // panggil fungsi prufer code

    // print hasil pengkodean tree
    printf("\nHasil Pengkodean Tree : \n");
    for(int i = 0; i < length; i++) {
        printf("%d ", code[i]+1);                // print setiap nilai pada array code
    }

    return 0;
}