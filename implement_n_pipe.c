#include"main.h"
void implement_n_pipe(char **argv)
{
    int i, j;

    /* ---------- PIPE VALIDATIONS ---------- */

    if (argv[0] == NULL) {
        printf("Error: Empty command\n");
        return;
    }

    /* Pipe cannot be first */
    if (strcmp(argv[0], "|") == 0) {
        printf("Error: Pipe at beginning\n");
        return;
    }

    int num_pipes = 0;

    for (i = 0; argv[i] != NULL; i++) {

        if (strcmp(argv[i], "|") == 0) {

            num_pipes++;

            /* Consecutive pipes */
            if (argv[i + 1] == NULL || strcmp(argv[i + 1], "|") == 0) {
                printf("Error: Invalid pipe usage\n");
                return;
            }
        }
    }

    /* Pipe cannot be last */
    if (strcmp(argv[i - 1], "|") == 0) {
        printf("Error: Pipe at end\n");
        return;
    }

    if (num_pipes == 0) {
        printf("Error: No pipe found\n");
        return;
    }

    /* ---------- PIPE CREATION ---------- */

    int pipefd[2 * num_pipes];

    for (i = 0; i < num_pipes; i++) {
        if (pipe(pipefd + i * 2) < 0) {
            perror("pipe");
            return;
        }
    }

    /* ---------- PIPE EXECUTION ---------- */

    int cmd_start = 0;

    for (i = 0; i < num_pipes + 1; i++) {

        int pid = fork();

        if (pid == 0) {

            signal(SIGINT, SIG_DFL);
            signal(SIGTSTP, SIG_DFL);

            /* Read from previous pipe */
            if (i > 0) {
                dup2(pipefd[(i - 1) * 2], 0);
            }

            /* Write to next pipe */
            if (i < num_pipes) {
                dup2(pipefd[i * 2 + 1], 1);
            }

            /* Close all pipe fds */
            for (j = 0; j < 2 * num_pipes; j++)
                close(pipefd[j]);

            /* Prepare argv for exec */
            int k = cmd_start;
            while (argv[k] && strcmp(argv[k], "|") != 0)
                k++;

            argv[k] = NULL;
            execvp(argv[cmd_start], &argv[cmd_start]);
            perror("execvp");
            exit(1);
        }

        /* Move to next command */
        while (argv[cmd_start] && strcmp(argv[cmd_start], "|") != 0)
            cmd_start++;
        cmd_start++;
    }

    /* ---------- PARENT ---------- */

    for (i = 0; i < 2 * num_pipes; i++)
        close(pipefd[i]);

    for (i = 0; i < num_pipes + 1; i++)
        wait(NULL);
}

