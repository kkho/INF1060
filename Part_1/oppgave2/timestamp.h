#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <sys/time.h>
#include <string.h>
#define STDIN_LEN 100

char time_line[STDIN_LEN];


char *modify_time2();
void file_name(char *namefile);
void time_shell();





#endif
