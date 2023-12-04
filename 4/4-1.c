#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#define LINE_MAX_LEN 256
#define MAX_ARR_LEN 256

void strshift(char* str, int amt) {
    for (int i = 0; i < amt; i++) {
        for (int j = 0; (j < (LINE_MAX_LEN-1)) && (str[j] != '\0'); j++) {
            str[j] = str[j+1];
        }
    }
    return;
}
int search(int* w, int n) {
    for (int i = 0; (i < MAX_ARR_LEN) && (w[i] != -1); i++) {
        if (w[i] == n) return 1;
    }
    return 0;
}
int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Please enter some file names in the cmd line!\n");
        return -1;
    }
    int sum = 0;
    for (int i = 1; i < argc; i++) {
        FILE* f = NULL;
        if (!(f = fopen(argv[i], "r"))) {
            printf("Couldn't open this file: %s\n", argv[i]);
            continue;
        }
        while (!feof(f)) {
            int winning_numbers[MAX_ARR_LEN], wn_i = 0;
            memset(winning_numbers, -1, MAX_ARR_LEN);
            int selected_numbers[MAX_ARR_LEN], sn_i = 0;
            memset(selected_numbers, -1, MAX_ARR_LEN);
            int card_number = 0;
            char str[LINE_MAX_LEN];
            memset(str, '\0', LINE_MAX_LEN);
            fgets(str, LINE_MAX_LEN, f);
            int len = strlen(str); 
            int start = 0, end = 0, size = 0;
            while ((str[end] < '0') || (str[end] > '9')) strshift(str, 1);
            for (;;end++) {
                if ((str[end] < '0') || (str[end] > '9')) break;
            }
            size = (end-start)-1;
            for (; start < end; start++) {
                card_number += (str[start]-48)*pow(10, (size));
                size--;
            } 
            strshift(str, (end+2));
            while ((str[0] != '|') && (str[0] != '\0')) {
                if ((str[0] < '0') || (str[0] > '9')) strshift(str, 1);
                else {
                    start = 0, end = 0, size = 0;
                    int temp = 0;
                    for (;;end++) {
                        if ((str[end] < '0') || (str[end] > '9')) break;
                    }
                    size = (end - start)-1;
                    for (; start < end; start++) {
                        temp += (str[start]-48)*pow(10, (size));
                        size--;
                    }
                    winning_numbers[wn_i] = temp;
                    wn_i++;
                    strshift(str, end);
                }
            }
            strshift(str, 2);
            while (str[0] != '\0') {
                if ((str[0] < '0') || (str[0] > '9')) strshift(str, 1);
                else {
                    start = 0, end = 0, size = 0;
                    int temp = 0;
                    for (;;end++) {
                        if ((str[end] < '0') || (str[end] > '9')) break;
                    }
                    size = (end - start)-1;
                    for (; start < end; start++) {
                        temp += (str[start]-48)*pow(10, (size));
                        size--;
                    }
                    if (search(winning_numbers, temp)) {
                        selected_numbers[sn_i] = temp;
                        sn_i++;
                    }
                    strshift(str, end);
                }
            }
            printf("Card %d: ", card_number);
            if (sn_i > 0) {sum += 1; printf("%d ", selected_numbers[0]);}
            for (int i = 1; i < sn_i; i++) {
                sum += pow(2, (i-1));
                printf("%d ", selected_numbers[i]);
            }
            printf("\n");
        }
        fclose(f);
    }
    printf("Calibration Sum is: %d :3\n", sum);
    return 0;
}