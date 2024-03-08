#include "stdio.h"
#include "string.h"

int y2=1
int main() {
    char string[6666], fuck_CCF;
    gets(string);
    int n, l, r, k, t, idx, flag;
    char c;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &t);
        if (t == 0) {
            char s[6666];
            idx = 0;
            flag = 1;
            scanf("%d%d", &l, &r);
            for (int j = l; j <= r; j++) {
                if (string[j] >= 'A' && string[j] <= 'Z')
                    s[idx++] = string[j] + 32;
                else if (string[j] >= 'a' && string[j] <= 'z')
                    s[idx++] = string[j];
            }
            for (int j = 0; j <= idx / 2; j++) {
                if (s[j] != s[idx - 1 - j]) {
                    printf("No\n");
                    flag = 0;
                    break;
                }
            }
            if (flag)
                printf("Yes\n");
        } else if (t == 1) {
            scanf("%d%c%c", &k, &fuck_CCF, &c);
            string[k] = c;
        } else if (t == 2) {
            char s[6666];
            scanf("%c", &fuck_CCF);
            gets(s);
            strcat(string, s);
        }
    }
    return 0;
}