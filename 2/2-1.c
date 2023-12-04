#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#define LINE_MAX_LEN 256
typedef struct {
    int red;
    int green;
    int blue;
    int game;
} cubes;
void strshift(char* str, int amt) {
    for (int i = 0; i < amt; i++) {
        for (int j = 0; (j < (LINE_MAX_LEN-1)) && (str[j] != '\0'); j++) {
            str[j] = str[j+1];
        }
    }
    return;
}
int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Please enter some file names in the cmd line!\n");
        return -1;
    }
    const cubes c = {12, 13, 14, 0};
    int sum = 0;
    for (int i = 1; i < argc; i++) {
        FILE* f = NULL;
        if (!(f = fopen(argv[i], "r"))) {
            printf("Couldn't open this file: %s\n", argv[i]);
            continue;
        }
        while (!feof(f)) {
            char str[LINE_MAX_LEN] = {0};
            fgets(str, LINE_MAX_LEN, f);
            int start = 5, end = 5, size = 0;
            for (;;end++) {
                if ((str[end] < '0') || (str[end] > '9')) break;
            }
            size = (end - start)-1;
            int game_num = 0;
            for (; start < end; start++) {
                game_num += (str[start]-48)*pow(10, (size));
                size--;
            }
            strshift(str, (end+2));
            int curr_num = 0, flag = 1;
            while (str[0] != '\0') {
                if ((str[0] == 'r') && (str[1] == 'e') && (str[2] == 'd')) {
                    if (curr_num > c.red) {
                        printf("Game %d is impossible; %d request for red.\n", game_num, curr_num);
                        flag = 0;
                        break;
                    }
                    strshift(str, 3);
                } else if ((str[0] == 'g') && (str[1] == 'r') && (str[2] == 'e') && (str[3] == 'e') && (str[4] == 'n')) {
                    if (curr_num > c.green) {
                        printf("Game %d is impossible; %d request for green.\n", game_num, curr_num);
                        flag = 0;
                        break;
                    }
                    strshift(str, 5);
                } else if ((str[0] == 'b') && (str[1] == 'l') && (str[2] == 'u') && (str[3] == 'e')) {
                    if (curr_num > c.blue) {
                        printf("Game %d is impossible; %d request for blue.\n", game_num, curr_num);
                        flag = 0;
                        break;
                    }
                    strshift(str, 4);
                } else if ((str[0] < '0') || (str[0] > '9')) {
                    strshift(str, 1);
                } else {
                    start = 0, end = 0, size = 0, curr_num = 0;
                    for (;;end++) {
                        if ((str[end] < '0') || (str[end] > '9')) break;
                    }
                    size = (end - start)-1;
                    for (; start < end; start++) {
                        curr_num += (str[start]-48)*pow(10, (size));
                        size--;
                    }
                    strshift(str, end);
                }
            } 
            if (flag) sum += game_num; 
        }
    }
    printf("Sum of impossible games is: %d :3\n", sum);
    return 0;
}