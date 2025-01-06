#include "types.h"
#include "stat.h"
#include "user.h"


#define MAX_PROCS 64

struct procinfo {
    int pid;
    int ppid;
    int state;
    uint sz;        // Memory size
    char name[16];  // Process name
};

int main(void) {
    struct procinfo pinfo[MAX_PROCS];
    int num_procs = mycall(sizeof(pinfo), pinfo);

    if (num_procs < 0) {
        printf(1, "Failed to fetch process information.\n");
        exit();
    }

    printf(1, "PID\tPPID\tSTATE\tSIZE\tNAME\n");
    for (int i = 0; i < num_procs; i++) {
        printf(1, "%d\t%d\t%d\t%d\t%s\n",
               pinfo[i].pid,
               pinfo[i].ppid,
               pinfo[i].state,
               pinfo[i].sz,
               pinfo[i].name);
    }

    exit();
}

