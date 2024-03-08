#include <stdio.h>

int main() {
    int a, b, c, max; // Store the number of students in classes A, B, and C.
    printf("How many students are in classes A, B, and C, respectively?\n");
    scanf("%d%d%d", &a, &b, &c);
    if (a >= b && a >= c) {
        max = a;
        printf("Class A has the most students, ");
    } else if (b > a && b >= c) {
        max = b;
        printf("Class B has the most students, ");
    } else if (c > a && c > b) {
        max = c;
        printf("Class C has the most students, ");
    }
    int total = a + b + c;
// A class can accept at most half of all students.
    if (2 * max > total)
        printf("and is overly enrolled!\n");
    else if (2 * max == total)
        printf("and is full!\n");
    else if (2 * max < total)
        printf("and still has open seats!\n");
    return 0;
}