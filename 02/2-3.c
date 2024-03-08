#include "stdio.h"
#include "stdlib.h"

int **MagicSquare(int n) {
    int **ms;
    int row = 0, col = (n - 1) / 2, num = 1;
    ms = (int **) malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        ms[i] = (int *) malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            ms[i][j] = 0;
    ms[row][col] = num++;
    for (int i = 0; i < n * n - 1; i++) {
        row = (row + n - 1) % n;
        col = (col + 1) % n;
        if (ms[row][col]) {
            row = (row + 2) % n;
            col = (col + n - 1) % n;
        }
        ms[row][col] = num++;
    }
    return ms;
}

//int **MagicSquare(int n) {
//    int **ms;
//    int row = 0, col = (n - 1) / 2, num = 2;
//    ms = (int **) malloc(n * sizeof(int *));
//    for (int i = 0; i < n; i++)
//        ms[i] = (int *) malloc(n * sizeof(int));
//    for (int i = 0; i < n; i++) {
//        num--;
//        ms[row][col] = judge(num, n);
//        num = judge(num + n + 1, n);
//        for (int j = 0; j < n - 1; j++) {
//            row = idx(row + 1, n);
//            ms[row][col] = judge(num + (n + 1) * j, n);
//        }
//        row = idx(row + 3, n);
//        col = idx(col - 1, n);
//    }
//    return ms;
//}
//
//int judge(int a, int n) {
//    int ret = (a > n * n) ? a - n * n : a;
//    ret = (ret < 0) ? ret + n * n : ret;
//    return ret;
//}
//
//int idx(int a, int n) {
//    int ret = (a >= n ? a - n : a);
//    ret = (ret < 0) ? ret + n : ret;
//    return ret;
//}

void FreeMagicSquare(int **magicSquare, int n) {
    for (int i = 0; i < n; i++)
        free(magicSquare[i]);
    free(magicSquare);
}

int main() {
    int n;
    scanf("%d", &n); // Please input a positive odd number.
    int **magicSquare = MagicSquare(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%4d", magicSquare[i][j]);
        }
        printf("\n");
    }
    FreeMagicSquare(magicSquare, n);
    return 0;
}
