#include <stdio.h>

int main() {
    double x, y, d, dr[3] = {-1, -1, -1}, dy[3] = {-1, -1, -1};
    int j = 0;
    for (int i = 0; i < 3; i++) {
        scanf("(%lf,%lf)\n", &x, &y);
        d = x * x + y * y;
        if (d < 1.8 * 1.8)
            dr[j++] = d;
    }
    j = 0;
    for (int i = 0; i < 2; i++) {
        scanf("(%lf,%lf)\n", &x, &y);
        if (i==2)
            scanf("\n");
        d = x * x + y * y;
        if (d < 1.8 * 1.8)
            dy[j++] = d;
    }
    if (dr[0] < 0 && dy[0] < 0)
        printf("BLANK END\n");
    else {
        double rmin = 10, ymin = 10;
        int n = 0;
        for (int ri = 0; ri < 3 && dr[ri] != -1; ri++)
            rmin = (dr[ri] < rmin) ? dr[ri] : rmin;
        for (int yi = 0; yi < 3 && dy[yi] != -1; yi++)
            ymin = (dy[yi] < ymin) ? dy[yi] : ymin;
        if (rmin < ymin) {
            printf("RED SCORES ");
            for (int ri = 0; ri < 3 && dr[ri] != -1; ri++) {
                if (dr[ri] < ymin)
                    n++;
            }
        } else {
            printf("YELLOW SCORES ");
            for (int yi = 0; yi < 3 && dy[yi] != -1; yi++) {
                if (dy[yi] < rmin)
                    n++;
            }
        }
        printf("%d\n", n);
    }
    return 0;
}