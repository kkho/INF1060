#include "timestamp.h"
#include "linkedlist.h"
#include "common.h"
#include <signal.h>
#define BUF_LEN 100

char *command_line;
void command_read(char *read);
void exit_signal();

int main() {
    command_line = malloc(STDIN_LEN);

    while (1) {
        signal(SIGINT, exit_signal);

        time_shell();

        fgets(command_line, STDIN_LEN, stdin);
        char *readline = strtok(command_line, "\n");
        command_read(readline);
        memset(command_line, 0, STDIN_LEN); // reset the buffer, make sure it doesn't have any data while reading input

    }
    return 0;

}

/**
 * reads input from given stdin, and compares the content of the string
 * @param read
 *
 */
void command_read(char *read) {
    int id = -1;
    person *pers = NULL;
    char name[BUF_LEN]; /*static allocation of username*/
    memset(name, 0, sizeof (name));

    if (strcmp(read, "exit") == 0) {
        puts("to exit");
        free(command_line);

        if (!is_empty()) {
            free_memory();
        }

        exit(1);
    } else if (strstr(read, "add") != NULL) {
        if (sscanf(read, "add %d %[^\t\n]", &id, name) == 2) {
            pers = (person *) stack_malloc(sizeof (person));
            pers->id = id;
            strcpy(pers->name, name);
            enqueue(pers);
        }
    } else if (strcmp(read, "print") == 0) {
        print_q();
    } else if (strstr(read, "find") != NULL) {
        if (sscanf(read, "find %s", name) == 1) {
            if (search(name) > -1) {
                printf("found person: %s\n", name);
            } else {
                puts("person not found, try to type in full name");
            }
        }
    } else if (strstr(read, "remove") != NULL) {
        if (sscanf(read, "remove %s", name) == 1) {
            if (remove_node(name) > -1) {
                printf("removed: %s\n", name);
            } else {
                puts("person not found, try to type in full name or it doesn't exists");
            }
        }
    }

}

/**
 * when exiting the main function, we want to use signal handling for freeing memory
 * allocation from the linkedlist.
 */
void exit_signal() {

    puts("signal ctrl-c accepted and freeing allocated memories in heap");
    signal(SIGINT, SIG_DFL);
    free(command_line);

    if (!is_empty()) {
        free_memory();
    }
    exit(1);

}
