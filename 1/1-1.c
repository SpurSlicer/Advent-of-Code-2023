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
                if ((str[j] > '0') && (str[j] <= '9')) {
                    if (!tens_place) tens_place = (str[j]-'0');
                    ones_place = (str[j]-'0');
                }
                if (str[j] == '\0') break;
            }
            int val = ((tens_place*10) + ones_place);
            sum += val;
        }
        fclose(f);
    }
    printf("Calibration Sum is: %d :3\n", sum);
    return 0;
}