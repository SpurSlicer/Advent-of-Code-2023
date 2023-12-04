#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define LINE_MAX_LEN 128
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
            char str[LINE_MAX_LEN];
            memset(str, '\0', LINE_MAX_LEN);
            fgets(str, LINE_MAX_LEN, f);
            int len = strlen(str); 
            int tens_place = 0, ones_place = 0;
            for (int j = 0; j < len; j++) {
                switch (str[j]) {
                    case 'o':
                        if ((str[j+1] == 'n') && (str[j+2] == 'e')) {
                            if (!tens_place) tens_place = 1;
                            ones_place = 1;
                        }
                        break;
                    case 't':
                        if ((str[j+1] == 'h') && (str[j+2] == 'r') && (str[j+3] == 'e') && (str[j+4] == 'e')) {
                            if (!tens_place) tens_place = 3;
                            ones_place = 3;
                        } else if ((str[j+1] == 'w') && (str[j+2] == 'o')) {
                            if (!tens_place) tens_place = 2;
                            ones_place = 2;
                        }
                        break;
                    case 'f':
                        if ((str[j+1] == 'o') && (str[j+2] == 'u') && (str[j+3] == 'r')) {
                            if (!tens_place) tens_place = 4;
                            ones_place = 4;
                        } else if ((str[j+1] == 'i') && (str[j+2] == 'v') && (str[j+3] == 'e')) {
                            if (!tens_place) tens_place = 5;
                            ones_place = 5;
                        }
                        break;
                    case 's':
                        if ((str[j+1] == 'i') && (str[j+2] == 'x')) {
                            if (!tens_place) tens_place = 6;
                            ones_place = 6;
                        }
                        if ((str[j+1] == 'e') && (str[j+2] == 'v') && (str[j+3] == 'e') && (str[j+4] == 'n')) {
                            if (!tens_place) tens_place = 7;
                            ones_place = 7;
                        }
                        break;
                    case 'e':
                        if ((str[j+1] == 'i') && (str[j+2] == 'g') && (str[j+3] == 'h') && (str[j+4] == 't')) {
                            if (!tens_place) tens_place = 8;
                            ones_place = 8;
                        }
                        break;
                    case 'n':
                        if ((str[j+1] == 'i') && (str[j+2] == 'n') && (str[j+3] == 'e')) {
                            if (!tens_place) tens_place = 9;
                            ones_place = 9;
                        }
                        break;
                    default: 
                        if ((str[j] > '0') && (str[j] <= '9')) {
                            if (!tens_place) tens_place = (str[j]-'0');
                            ones_place = (str[j]-'0');
                        }
                    if (str[j] == '\0') break;
                }
            }
            int val = ((tens_place*10) + ones_place);
            //printf("val is %d\n", val);
            sum += val;
        }
        fclose(f);
    }
    printf("Calibration Sum is: %d :3\n", sum);
    return 0;
}