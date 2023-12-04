#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#define LINE_MAX_LEN 256
#define MAX_GEARS 128
typedef struct s {
    char* row;
    struct s* next;
    struct s* prev;
} s;
typedef struct gear {
    int gear_index_1;
    int gear_index_2;
    int gear;
    int valid;
    struct gear* next;
} gear;
int check(char c) {
    if (c ==  42) return 1;
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
    gear* g = NULL;
    int max_size = 0;
    for (int i = 1; i < argc; i++) {
        FILE* f = NULL;
        if (!(f = fopen(argv[i], "r"))) {
            printf("Couldn't open this file: %s\n", argv[i]);
            continue;
        }
        s* schematic = fileinfo(f);
        s* temp = schematic;
        int thing = 0;
        while (temp) {
            int len = strlen(temp->row) + 1;
            for (int i = 0; i < len; i++) {
                int indices[16] = {-1, -1, -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1, -1, -1, -1, -1};
                int curr = 0;
                if ((temp->row[i] > 47) && (temp->row[i] < 58)) {
                    int start = i, end = i, status = 0;
                    if (end-1 > -1) {
                        if (!temp->next) {
                            if (check(temp->prev->row[end-1])) {indices[curr] = thing-1; indices[curr+1] = end-1; curr += 2;}
                            if (check(temp->row[end-1])) {indices[curr] = thing; indices[curr+1] = end-1; curr += 2;}
                        } else if (!temp->prev) {
                            if (check(temp->next->row[end-1])) {indices[curr] = thing+1; indices[curr+1] = end-1; curr += 2;}
                            if (check(temp->row[end-1])) {indices[curr] = thing; indices[curr+1] = end-1; curr += 2;}
                        } else {
                            if (check(temp->prev->row[end-1])) {indices[curr] = thing-1; indices[curr+1] = end-1; curr += 2;}
                            if (check(temp->next->row[end-1])) {indices[curr] = thing+1; indices[curr+1] = end-1; curr += 2;}
                            if (check(temp->row[end-1])) {indices[curr] = thing; indices[curr+1] = end-1; curr += 2;}
                        }
                    }
                    while ((temp->row[end] > 47) && (temp->row[end] < 58)) {
                        if (!temp->next) {
                            if (check(temp->prev->row[end])) {indices[curr] = thing-1; indices[curr+1] = end; curr += 2;}
                        } else if (!temp->prev) {
                            if (check(temp->next->row[end])) {indices[curr] = thing+1; indices[curr+1] = end; curr += 2;}
                        } else {
                            if (check(temp->prev->row[end])) {indices[curr] = thing-1; indices[curr+1] = end; curr += 2;}
                            if (check(temp->next->row[end])) {indices[curr] = thing+1; indices[curr+1] = end; curr += 2;}
                        }
                        end++;
                    }
                    if (temp->row[end] != '\0') {
                        if (!temp->next) {
                            if (check(temp->prev->row[end])) {indices[curr] = thing-1; indices[curr+1] = end; curr += 2;}
                            if (check(temp->row[end])) {indices[curr] = thing; indices[curr+1] = end; curr += 2;}
                        } else if (!temp->prev) {
                            if (check(temp->next->row[end])) {indices[curr] = thing+1; indices[curr+1] = end; curr += 2;}
                            if (check(temp->row[end])) {indices[curr] = thing; indices[curr+1] = end; curr += 2;}
                        } else {
                            if (check(temp->prev->row[end])) {indices[curr] = thing-1; indices[curr+1] = end; curr += 2;}
                            if (check(temp->next->row[end])) {indices[curr] = thing+1; indices[curr+1] = end; curr += 2;}
                            if (check(temp->row[end])) {indices[curr] = thing; indices[curr+1] = end; curr += 2;}
                        }
                    }
                    i = end;
                    end--;
                    int size = end - start;
                    int temp_start = start, temp_end = end;
                    int temp_val = 0;
                    for (; temp_start <= temp_end; temp_start++) {
                        temp_val += (temp->row[temp_start]-48)*pow(10, (size));
                        size--;
                    }
                    //printf("Number %d[%d:%d] amnt: %d is valid.\n", thing, start, end, temp_val);
                    for (int i = 0; (indices[i] != -1) && (i < 16); i+=2) {
                        gear* gt = g;
                        gear* new_gear = (gear*)malloc(sizeof(gear));
                        new_gear->gear = temp_val;
                        new_gear->gear_index_1 = indices[i];
                        new_gear->gear_index_2 = indices[i+1];
                        new_gear->valid = 1;
                        new_gear->next = NULL;
                        if (!g) g = new_gear;
                        else {
                            while (gt->next) gt = gt->next;
                            gt->next = new_gear;
                        }
                        max_size++;
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
    int mult = 0;
    while (1) {
        int count = 0, indices[2] = {-1, -1}, nums[2] = {-1, -1};
        gear* gt = g;
        while (gt) {
            if (gt->valid) {
                if ((indices[0] == -1) && (indices[1] == -1)) {
                    indices[0] = gt->gear_index_1;
                    indices[1] = gt->gear_index_2;
                    nums[count] = gt->gear;
                    count++;
                    gt->valid = 0;
                } else if ((indices[0] == gt->gear_index_1) && (indices[1] == gt->gear_index_2)) {
                    if (count < 2) {
                        nums[count] = gt->gear;
                    }
                    count++;
                    gt->valid = 0;
                }
            }
            //printf("Gear info: gear %d, [%d,%d] with validity %d in nums\n", gt->gear, gt->gear_index_1, gt->gear_index_2, gt->valid);
            gt = gt->next;
        }
        if (count == 2) {
            mult += nums[0] * nums[1];
        }
        if ((indices[0] == -1) && (indices[1] == -1)) break;
    }
    while (g) {
        gear* temp = g->next;
        free(g);
        g = g->next;
    }

}