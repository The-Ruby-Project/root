#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    if (geteuid() != 0) {
        fprintf(stderr, "This program must be setuid root to work.\n");
        return 1;
    }

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command>\n", argv[0]);
        return 1;
    }

    // Drop privileges to the invoking user after privilege escalation
    setuid(0);

    // Execute the command passed as an argument
    execvp(argv[1], &argv[1]);

    // If execvp fails
    perror("execvp");
    return 1;
}
