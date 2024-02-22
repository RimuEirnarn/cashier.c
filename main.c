#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include "common.h"


typedef struct {
    int counter;
    int cleanup_pts;
} state;

typedef int (*fn)(state*);

typedef struct {
    char* name;
    uint64_t price;
} Item;

typedef struct {
    char* name;
    fn callback;
} Action;


int exit_callback(state *_) {
    printf("Goodbye~\n");
    return -1;
}

int count1(state *st) {
    st->counter += 1;
    return 0;
}

int print1(state *st) {
    printf("-> %d\n", st->counter);
    return 1;
}

void cleanup(int cleanupts) {
    if (cleanupts == 0) return;
    for (int i=0; i<=cleanupts; i++) {
        printf("\033[1A\r\033[2K\r");
        fflush(stdout);
    }
}

int _n(state *_){
    return 0;
}

int main() {
    char inp;
    int act;
    int rt;
    int s;
    state st = {0, 0};
    printf("Welcome to RimuCashier :3\n");
    Action actions[] = {
        {"Count", &count1},
        {"Print", &print1},
        {"Exit", &exit_callback},
        {NULL, &_n}
    };
    st.counter = 0;
    while (1) {
        printf("Cleanup -> %d\n", st.cleanup_pts);
        st.cleanup_pts = 1;
        int s = 0;
        while (actions[s].name != NULL) {

            printf("%d. %s\n", s+1, actions[s].name);
            fflush(stdout);
            st.cleanup_pts++;
            s++;
        }
        printf("<- ");
        fflush(stdout);
        inp = getchar() - '0';
        if ((inp > s+1) || (inp <= 0)) {
            cleanup(s);
            continue;
        }
        act = inp -1;
        rt = actions[act].callback(&st);
        if (rt == -1) {
            return 0;
        }
        st.cleanup_pts += rt;
        sleep(1);
        cleanup(st.cleanup_pts);
    }
    return 0;
}
