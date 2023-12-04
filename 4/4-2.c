#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#define LINE_MAX_LEN 256
#define MAX_ARR_LEN 256

typedef struct l {
    char* str;
    int len;
    struct l* next;
} l;

void strshift(char* str, int amt, int len) {
    for (int i = 0; i < amt; i++) {
        for (int j = 0; (j < (len-1)) && (str[j] != '\0'); j++) {
            str[j] = str[j+1];
        }
        if (str[len-1]) str[len-1] = '\0';
    }
    return;
}
int search(int* w, int n) {
    for (int i = 0; (i < MAX_ARR_LEN) && (w[i] != -1); i++) {
        if (w[i] == n) return 1;
    }
    return 0;
}
void routine(int* arr, l* ll, int arr_len) {
    int pos = 0;
    l* temp = ll;
    while (temp) {
        //printf("Card %d", (pos+1));
        int winning_numbers[MAX_ARR_LEN], wn_i = 0;
        memset(winning_numbers, -1, MAX_ARR_LEN);
        int selected_numbers[MAX_ARR_LEN], sn_i = 0;
        memset(selected_numbers, -1, MAX_ARR_LEN);
        int card_number = 0;
        char* str = temp->str;
        int len = temp->len; 
        int start = 0, end = 0, size = 0;
        while ((str[end] < '0') || (str[end] > '9')) strshift(str, 1, len);
        for (;;end++) {
            if ((str[end] < '0') || (str[end] > '9')) break;
        }
        size = (end-start)-1;
        for (; start < end; start++) {
            card_number += (str[start]-48)*pow(10, (size));
            size--;
        } 
        strshift(str, (end+2), len);
        while ((str[0] != '|') && (str[0] != '\0')) {
            if ((str[0] < '0') || (str[0] > '9')) strshift(str, 1, len);
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
                strshift(str, end, len);
            }
        }
        strshift(str, 2, len);
        while (str[0] != '\0') {
            if ((str[0] < '0') || (str[0] > '9')) strshift(str, 1, len);
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
                strshift(str, end, len);
            }
        }
        int thing = pos;
        arr[pos] += 1;
        for (int i = 1; i <= sn_i; i++) {
            if ((i + thing) >= arr_len) {
                sn_i = sn_i - i;
                i = 1;
            }
            arr[i+thing] += arr[thing];
        }
        //printf(" Made %d calls\n", arr[pos]);
        temp = temp->next;
        pos++;
    }
    return;
}
int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Please enter some file names in the cmd line!\n");
        return -1;
    }
    FILE* f = NULL;
    l* head = NULL;
    int* arr = NULL;
    int sum = 0;
    int cnt = 0;
    for (int i = 1; i < argc; i++) {
        if (!(f = fopen(argv[i], "r"))) {
            printf("Couldn't open this file: %s\n", argv[i]);
            continue;
        }
        while (!feof(f)) {
            cnt++;
            char str[LINE_MAX_LEN];
            memset(str, '\0', LINE_MAX_LEN);
            fgets(str, LINE_MAX_LEN, f);
            int len = 0;
            if (feof(f)) len = strlen(str) + 1;
            else len = strlen(str); 
            char* c = (char*)malloc(len);
            memset(c, '\0', len);
            strncpy(c, str, len);
            for (int j = 0; j < len; j++) {
                if ((c[j] == '\n') || (c[j] == EOF)) c[j] = '\0';
            }
            l* new_l = (l*)malloc(sizeof(l));
            new_l->next = NULL;
            new_l->str = c;
            new_l->len = len;
            l* temp = head;
            if (!head) head = new_l;
            else {
                while (temp->next) temp = temp->next;
                temp->next = new_l;
            }
        }
        arr = (int*)malloc(sizeof(int)*cnt);
        memset(arr, 0, cnt*sizeof(int));
        routine(arr, head, cnt);
        for (int i = 0; i < cnt; i++) {
            sum += arr[i];
        }
        free(arr);
        while (head) {
            l* d = head->next;
            free(head->str);
            free(head);
            head = d;
        }
        fclose(f);
    }

    printf("Calibration Sum is: %d :3\n", sum);
    return 0;
}