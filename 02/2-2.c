#include <stdio.h>

int length(int a) {
    int len = 0;
    if (a) {
        while (a) {
            a /= 10;
            len++;
        }
    } else
        len++;
    return len;
}

void add(int a, int b) {
    int max = length(a + b);
    printf("%*d\n+%*d\n", max + 2, a, max + 1, b);
    for (int i = 0; i < max + 2; i++)
        printf("-");
    printf("\n%*d", max + 2, a + b);
}

void subtract(int a, int b) {
    int len_a = length(a);
    int len_b = length(b);
    int len_s = (a - b >= 0) ? length(a - b) : length(a - b) + 1;
    int max = len_a;
    max = (len_b > max) ? len_b : max;
    max = (len_s > max) ? len_s : max;
    printf("%*d\n-%*d\n", max + 2, a, max + 1, b);
    for (int i = 0; i < max + 2; i++)
        printf("-");
    printf("\n%*d", max + 2, a - b);
}

void multiply(int a, int b) {
    int m = b, n = 0;
    int max = length(a * b);
    printf("%*d\nx%*d\n", max + 2, a, max + 1, b);
    for (int i = 0; i < max + 2; i++)
        printf("-");
    printf("\n");
    while (m) {
        if (m % 10) {
            printf("%*d\n", max + 2 - n, a * (m % 10));
        }
        m /= 10;
        n++;
    }
    for (int i = 0; i < max + 2; i++)
        printf("-");
    printf("\n%*d", max + 2, a * b);
}

//int maxLen(int a, int b, int c) {
//    int max = a;
//    max = (b > max) ? b : max;
//    max = (c > max) ? c : max;
//    return max;
//}
//
//void add(int a, int b) {
//    int len_a = length(a);
//    int len_b = length(b);
//    int len_s = length(a + b);
//    int max = maxLen(len_a, len_b, len_s);
//    for (int i = 0; i < max + 2 - len_a; i++)
//        printf(" ");
//    printf("%d\n+", a);
//    for (int i = 0; i < max + 1 - len_b; i++)
//        printf(" ");
//    printf("%d\n", b);
//    for (int i = 0; i < max + 2; i++)
//        printf("-");
//    printf("\n");
//    for (int i = 0; i < max + 2 - len_s; i++)
//        printf(" ");
//    printf("%d\n", a + b);
//
//void subtract(int a, int b) {
//    int len_a = length(a);
//    int len_b = length(b);
//    int len_s = (a - b >= 0) ? length(a - b) : length(a - b) + 1;
//    int max = maxLen(len_a, len_b, len_c);
//    for (int i = 0; i < max + 2 - len_a; i++)
//        printf(" ");
//    printf("%d\n-", a);
//    for (int i = 0; i < max + 1 - len_b; i++)
//        printf(" ");
//    printf("%d\n", b);
//    for (int i = 0; i < max + 2; i++)
//        printf("-");
//    printf("\n");
//    for (int i = 0; i < max + 2 - len_s; i++)
//        printf(" ");
//    printf("%d\n", a - b);
//
//void multiply(int a, int b) {
//    int dig[12], len[12];
//    int m = b, n = 0, d;
//    int len_a = length(a);
//    int len_b = length(b);
//    int len_m = length(a * b);
//    int max = maxLen(len_a, len_b, len_m);
//    while (m) {
//        dig[n] = m - m / 10 * 10;
//        m /= 10;
//        d = ++n;
//    }
//    for (int i = 0; i < d; i++) {
//        len[i] = i + length(a * dig[i]);
//        max = (len[i] > max) ? len[i] : max;
//    }
//    for (int i = 0; i < max + 2 - len_a; i++)
//        printf(" ");
//    printf("%d\nx", a);
//    for (int i = 0; i < max + 1 - len_b; i++)
//        printf(" ");
//    printf("%d\n", b);
//    for (int i = 0; i < max + 2; i++)
//        printf("-");
//    printf("\n");
//    for (int i = 0; i < d; i++) {
//        if (a * dig[i]) {
//            for (int j = 0; j < max + 2 - len[i]; j++)
//                printf(" ");
//            printf("%d\n", a * dig[i]);
//        }
//    }
//    for (int i = 0; i < max + 2; i++)
//        printf("-");
//    printf("\n");
//    for (int i = 0; i < max + 2 - len_m; i++)
//        printf(" ");
//    printf("%d\n", a * b);

int main() {
    int a, b;
    char op;
    scanf("%d %c %d", &a, &op, &b);
    switch (op) {
        case '+':
            add(a, b);
            break;
        case '-':
            subtract(a, b);
            break;
        case 'x':
            multiply(a, b);
            break;
        default:
            printf("Sample input: 12 + 34");
    }
    return 0;
}