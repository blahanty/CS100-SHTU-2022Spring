#include <stdio.h>

int main() {
    int n;
    double t0 = 0, t1, d = 0, v0 = 3, v1, dv = 0.2;
    char y;
    scanf("%d", &n);
    if (n == 0)
        d = 22.5;
    else {
        scanf("\n%lf - %c", &t1, &y);
        v1 = 3 - 0.2 * t1;
        if (v1 <= 0) {
            d = 22.5;
            v0 = 0;
        } else {
            d += (v0 + v1) * t1 * 0.5;
            v0 = v1;
            t0 = t1;
            dv = (y == 'H') ? 0.1 : 0.2;
        }
        for (int i = 0; i < n - 1 && v0 > 0; i++) {
            scanf("\n%lf - %c", &t1, &y);
            v1 = v0 - dv * (t1 - t0);
            if (v1 <= 0) {
                d += v0 * v0 / dv * 0.5;
                v0 = 0;
            } else {
                d += (v0 + v1) * (t1 - t0) * 0.5;
                v0 = v1;
                t0 = t1;
                dv = (y == 'H') ? 0.1 : 0.2;
            }
        }
    }
    if (v0 > 0) {
        d += v0 * v0 / dv * 0.5;
    }
    printf("The stone has slided for %.3lfm\n", d);
    return 0;
}