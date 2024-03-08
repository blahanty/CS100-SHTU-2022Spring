#include "stdio.h"
#include "string.h"

enum JumpType {
    T, S, Lo, F, Lz, A
};

static double scoreTable[4][6] = {{0.4, 0.4, 0.5,  0.5,  0.6,  1.1},
                                  {1.3, 1.3, 1.7,  1.8,  2.1,  3.3},
                                  {4.2, 4.3, 4.9,  5.3,  5.9,  8.0},
                                  {9.5, 9.7, 10.5, 11.0, 11.5, 12.5}};

double Score(int rotations, enum JumpType type) {
    return scoreTable[rotations - 1][type];
}


double Sco(int rotations, enum JumpType type, char err_1, char err_2) {
    double sco = (rotations == 0) ? 0 : Score(rotations, type);
    if (err_1 == 'e')
        sco *= 0.7;
    if (err_2 == '<')
        sco *= 0.7;
    return sco;
}

int main() {
    char seq[30];
    int rotations;
    enum JumpType type;
    for (int i = 0; i < 3; i++) {
        gets(seq);
        double score = 0;
        int j = 0, flag = 0, n = 0;
        while (j < strlen(seq)) {
            char err_1 = ' ', err_2 = ' ';
            n++;
            if (n > 3) {
                flag = 1;
                break;
            }
            if (seq[j] < '1' || seq[j] > '4') {
                flag = 1;
                break;
            }
            rotations = (int) (seq[j++] - 48);
            if (j >= strlen(seq)) {
                flag = 1;
                break;
            }
            if (seq[j] == 'L') {
                j++;
                if (j >= strlen(seq)) {
                    flag = 1;
                    break;
                }
                if (seq[j] == 'o')
                    type = Lo;
                else if (seq[j] == 'z')
                    type = Lz;
                else {
                    flag = 1;
                    break;
                }
            } else {
                switch (seq[j]) {
                    case 'T':
                        type = T;
                        break;
                    case 'S':
                        type = S;
                        break;
                    case 'F':
                        type = F;
                        break;
                    case 'A':
                        type = A;
                        break;
                    default:
                        flag = 1;
                        break;
                }
                if (flag)
                    break;
            }
            j++;
            if (j >= strlen(seq)) {
                score += Sco(rotations, type, err_1, err_2);
                break;
            }
            if (type == F || type == Lz) {
                if (seq[j] == '!' || seq[j] == 'e') {
                    err_1 = seq[j++];
                    if (j >= strlen(seq)) {
                        score += Sco(rotations, type, err_1, err_2);
                        break;
                    }
                }
            }
            if (seq[j] == 'q') {
                j++;
                if (j >= strlen(seq)) {
                    score += Sco(rotations, type, err_1, err_2);
                    break;
                }
            } else if (seq[j] == '<') {
                j++;
                err_2 = '<';
                if (j >= strlen(seq)) {
                    score += Sco(rotations, type, err_1, err_2);
                    break;
                }
                if (seq[j] == '<') {
                    rotations--;
                    err_2 = ' ';
                    j++;
                    if (j >= strlen(seq)) {
                        score += Sco(rotations, type, err_1, err_2);
                        break;
                    }
                }
            }
            if (seq[j] == 'x') {
                score += Sco(rotations, type, err_1, err_2);
                score *= 1.1;
                j++;
                if (j < strlen(seq)) {
                    flag = 1;
                    break;
                }
            } else if (seq[j] == '+') {
                score += Sco(rotations, type, err_1, err_2);
                j++;
                if (j >= strlen(seq)) {
                    flag = 1;
                    break;
                }
            } else {
                flag = 1;
                break;
            }
        }
        if (flag)
            printf("0.00\n");
        else
            printf("%.2f\n", score);
    }
    return 0;
}