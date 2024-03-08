#include <stdio.h>

int min;
int hand[20];


void dfs(int num) {
    if (num >= min)
        return;
    int s = 0;
    for (int i = 3; i < 15; i++) {
        if (hand[i]) {
            if (++s > 4) {
                for (int j = i - s + 1; j <= i; j++)
                    hand[j]--;
                dfs(num + 1);
                for (int j = i - s + 1; j <= i; j++)
                    hand[j]++;
            }
        } else
            s = 0;
    }
    int sp = 0;
    for (int i = 3; i < 15; i++) {
        if (hand[i] > 1) {
            if (++sp > 2) {
                for (int j = i - sp + 1; j <= i; j++)
                    hand[j] -= 2;
                dfs(num + 1);
                for (int j = i - sp + 1; j <= i; j++)
                    hand[j] += 2;
            }
        } else
            sp = 0;
    }
    int st = 0;
    for (int i = 3; i < 15; i++) {
        if (hand[i] > 2) {
            if (++st > 1) {
                for (int j = i - st + 1; j <= i; j++)
                    hand[j] -= 3;
                dfs(num + 1);
                for (int j = i - st + 1; j <= i; j++)
                    hand[j] += 3;
            }
        } else
            st = 0;
    }
    for (int i = 2; i < 15; i++) {
        if (hand[i] >= 3) {
            hand[i] -= 3;
            for (int j = 1; j < 15; j++) {
                if (hand[j]) {
                    hand[j]--;
                    dfs(num + 1);
                    hand[j]++;
                }
            }
            for (int j = 2; j < 15; j++) {
                if (hand[j] > 1) {
                    hand[j] -= 2;
                    dfs(num + 1);
                    hand[j] += 2;
                }
            }
            hand[i] += 3;
            if (hand[i] == 4) {
                hand[i] -= 4;
                for (int j = 1; j < 15; j++) {
                    if (hand[j]) {
                        hand[j]--;
                        for (int k = j + 1; k < 15; k++) {
                            if (hand[k]) {
                                hand[k]--;
                                dfs(num + 1);
                                hand[k]++;
                            }
                        }
                        hand[j]++;
                    }
                }
                for (int j = 2; j < 15; j++) {
                    if (hand[j] > 1) {
                        hand[j] -= 2;
                        for (int k = j + 1; k < 15; k++) {
                            if (hand[k] > 1) {
                                hand[k] -= 2;
                                dfs(num + 1);
                                hand[k] += 2;
                            }
                        }
                        hand[j] += 2;
                    }
                }
                hand[i] += 4;
            }
        }
    }
    for (int i = 1; i < 15; i++) {
        if (hand[i])
            num++;
    }
    min = num < min ? num : min;
}

int main() {
    int n, t, c;
    scanf("%d%d", &t, &n);
    for (int i = 0; i < t; i++) {
        for (int j = 0; j < 20; j++)
            hand[j] = 0;
        for (int j = 0; j < n; j++) {
            scanf("%d", &c);
            if (c == 14)
                hand[1]++;
            else if (c == 1)
                hand[14]++;
            else
                hand[c]++;
        }
        min = 114514;
        dfs(0);
        printf("%d\n", min);
    }
    return 0;
}