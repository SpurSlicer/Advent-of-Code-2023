#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#define LINE_MAX_LEN 256
typedef struct s {
    char* row;
    struct s* next;
    struct s* prev;
} s;
int check(char c) {
    if (c !=  46) {
        if (((c < 48) && (c > 32)) || ((c < 65) && (c > 57))) return 1;
    }
    return 0;
}
s* fileinfo (FILE* f) {
    s* head = (s*)malloc(sizeof(s));
    head->prev = NULL;
    s* curr = head;
    int flag = 1;
    while (flag) {
        char str[LINE_MAX_LEN];
        memset(str, '\0', LINE_MAX_LEN);
        fgets(str, LINE_MAX_LEN, f);
        int len = 0;
        if (!feof(f)) len = strlen(str);
        else {
            len = strlen(str)+1;
            flag = 0;
        }
        char* m = (char*)malloc(len);
        strncpy(m, str, len);
        m[len-1] = '\0';
        curr->row = m;
        s* next = (s*)malloc(sizeof(s));
        curr->next = next;
        curr->next->prev = curr;
        curr = curr->next;
    }
    curr = curr->prev;
    free(curr->next);
    curr->next = NULL;
    return head;
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
        s* schematic = fileinfo(f);
        s* temp = schematic;
        int thing = 1;
        while (temp) {
            int len = strlen(temp->row) + 1;
            for (int i = 0; i < len; i++) {
                if ((temp->row[i] > 47) && (temp->row[i] < 58)) {
                    int start = i, end = i, status = 0;
                    if (end-1 > -1) {
                        if (!temp->next) {
                            if (check(temp->prev->row[end-1])) status = 1;
                            if (check(temp->row[end-1])) status = 1;
                        } else if (!temp->prev) {
                            if (check(temp->next->row[end-1])) status = 1;
                            if (check(temp->row[end-1])) status = 1;
                        } else {
                            if (check(temp->prev->row[end-1])) status = 1;
                            if (check(temp->next->row[end-1])) status = 1;
                            if (check(temp->row[end-1])) status = 1;
                        }
                    }
                    while ((temp->row[end] > 47) && (temp->row[end] < 58)) {
                        if (!temp->next) {
                            if (check(temp->prev->row[end])) status = 1;
                        } else if (!temp->prev) {
                            if (check(temp->next->row[end])) status = 1;
                        } else {
                            if (check(temp->prev->row[end])) status = 1;
                            if (check(temp->next->row[end])) status = 1;
                        }
                        end++;
                    }
                    if (temp->row[end] != '\0') {
                        if (!temp->next) {
                            if (check(temp->prev->row[end])) status = 1;
                            if (check(temp->row[end])) status = 1;
                        } else if (!temp->prev) {
                            if (check(temp->next->row[end])) status = 1;
                            if (check(temp->row[end])) status = 1;
                        } else {
                            if (check(temp->prev->row[end])) status = 1;
                            if (check(temp->next->row[end])) status = 1;
                            if (check(temp->row[end])) status = 1;
                        }
                    }
                    i = end;
                    end--;
                    if (status) {
                        int size = end - start;
                        int temp_start = start, temp_end = end;
                        int temp_val = 0;
                        for (; temp_start <= temp_end; temp_start++) {
                            temp_val += (temp->row[temp_start]-48)*pow(10, (size));
                            size--;
                        }
                        //printf("Number %d[%d:%d] amnt: %d is valid.\n", thing, start, end, temp_val);
                        sum += temp_val;
                    }
                }
            }
            thing ++;
            temp = temp->next;
        }
        while (schematic) {
            free(schematic->row);
            s* temp = schematic->next;
            free(schematic);
            schematic = temp;
        }
        fclose(f);
    }
    printf("The sum of valid part numbers is: %d :3\n", sum);

}