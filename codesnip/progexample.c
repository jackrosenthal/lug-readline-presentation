#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void) {
    char *line = NULL, *expn = NULL;
    int status;
    using_history();
    for (;;) {
        free(line), free(expn);
        line = readline("prompt> ");
        if (!line) return 0; /* ^D to exit */
        int expn_result = history_expand(line, &expn);
        if (expn_result) puts(expn);
        add_history(expn);
        if (expn_result == 0 || expn_result == 1) {
            int pid = fork();
            if (pid < 0) return 1;
            if (pid == 0) {
                char ** arg = history_tokenize(expn);
                execvp(*arg, arg);
                return 1;
            }
            waitpid(pid, &status, 0);
        }
    }
    return 0;
}
