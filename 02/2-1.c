#include <stdio.h>
#include <stdlib.h>

void FindSecondMaxAndMin(int numbers[], int size, int *secondMax, int *secondMin) {
    int max = numbers[0], min = max;
    *secondMax = numbers[1];
    *secondMin = numbers[1];
    for (int i = 1; i < size; i++) {
        if (numbers[i] > max) {
            *secondMax = max;
            max = numbers[i];
        } else if (numbers[i] > *secondMax) {
            *secondMax = numbers[i];
        }
        if (numbers[i] < min) {
            *secondMin = min;
            min = numbers[i];
        } else if (numbers[i] < *secondMin) {
            *secondMin = numbers[i];
        }
    }
}

#define SIZE 8

int main() {
    int secondMax, secondMin;
    int numbers[SIZE] = {2, 3, 4, 7, 6, 10, 9, 8};
    FindSecondMaxAndMin(numbers, SIZE, &secondMax, &secondMin);
    printf("%d %d\n", secondMax, secondMin);
    return 0;
}