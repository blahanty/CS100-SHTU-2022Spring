#include <stdio.h>
#include "string.h"


//1
int main() {
    int n, ind = 0;
    scanf("%d\n", &n);
    for (int i = 0; i < n; i++) {
        char code[90];
        int j = 0, k, bra = 0;
        gets(code);
        if (code[0] == ' ') {
            j = 1;
            while (code[j] == ' ')
                j++;
        }
        if (code[j] != '}')
            for (int l = 0; l < ind; l++)
                printf("    ");
        while (j < strlen(code)) {
            if (code[j] == '(') {
                printf("(");
                bra++;
                j++;
            } else if (code[j] == ')') {
                printf(")");
                bra--;
                j++;
            } else if (code[j] == ';') {
                if (bra == 0) {
                    printf(";\n");
                    k = j + 1;
                    while (code[k] == ' ')
                        k++;
                    if (k >= strlen(code))
                        break;
                    else {
                        j = k;
                        for (int l = 0; l < ind; l++)
                            printf("    ");
                    }
                } else {
                    printf(";");
                    j++;
                }
            } else if (code[j] == '{') {
                printf(" {\n");
                ind++;
                break;
            } else if (code[j] == '}') {
                ind--;
                for (int l = 0; l < ind; l++)
                    printf("    ");
                printf("}\n");
                break;
            } else if (code[j] == ' ') {
                k = j + 1;
                while (code[k] == ' ')
                    k++;
                if ((code[k] != ';' || bra != 0) && (code[k] != '{'))
                    printf("%c", code[j++]);
                else
                    j = k;
            } else
                printf("%c", code[j++]);
        }
    }
    return 0;
}

//2
//int main() {
//    int n, s = 0;
//    char all_code[114514];
//    scanf("%d\n", &n);
//    for (int i = 0; i < n; i++) {
//        char code[100];
//        gets(code);
//        strcat(all_code, code);
//    }
//    int i = 0, j;
//    while (all_code[i] != '\0') {
//        j = i + 1;
//        if (all_code[i] == ' ') {
//            while (all_code[j] == ' ') {
//                j++;
//            }
//            if (all_code[j] == '{' || all_code[j] == '}' || all_code[j] == ';')
//                i = j;
//            else
//                printf("%c", all_code[i++]);
//        } else if (all_code[i] == '(') {
//            int k = 1;
//            printf("(");
//            while (k) {
//                printf("%c", all_code[j]);
//                if (all_code[j] == ')')
//                    k--;
//                if (all_code[j] == '(')
//                    k++;
//                j++;
//            }
//            i = j;
//        } else if (all_code[i] == '{') {
//            s++;
//            printf(" {\n");
//            for (int k = 0; k < s; k++)
//                printf("    ");
//            j = i + 1;
//            while (all_code[j] == ' ') {
//                j++;
//            }
//            i = j;
//        } else if (all_code[i] == '}') {
//            s--;
//            j = i - 1;
//            while (all_code[j] == ' ')
//                j--;
//            if (all_code[j] != '}')
//                printf("\n");
//            for (int k = 0; k < s; k++)
//                printf("    ");
//            printf("}\n");
//            j = i + 1;
//            while (all_code[j] == ' ')
//                j++;
//            if (all_code[j] != '}') {
//                for (int k = 0; k < s; k++)
//                    printf("    ");
//            }
//            i = j;
//        } else if (all_code[i] == ';') {
//            printf(";");
//            j = i + 1;
//            while (all_code[j] == ' ') {
//                j++;
//            }
//            i = j;
//            if (all_code[i] != '}') {
//                printf("\n");
//                for (int k = 0; k < s; k++)
//                    printf("    ");
//            }
//        } else
//            printf("%c", all_code[i++]);
//    }
//    return 0;
//}