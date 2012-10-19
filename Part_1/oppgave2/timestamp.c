#include "timestamp.h"
#define TIME_LINE 150
/**
 * this function will convert given time to local time 
 * in a buffer and return it.
 * @return time_line
 */

char *modify_time2() {
    struct tm * time_it;
    struct timeval tv;
    gettimeofday(&tv, NULL);
    time_t curtime = tv.tv_sec;
    time_it = localtime(&curtime);
    const char dates[] = "%H:%M:%S";
    strftime(time_line, TIME_LINE, dates, time_it);
    return time_line;

}

/**
 * This function is a helper for printint out the user for the computer and the timevalue
 * and use the modify_time2() function to print out the given local time
 */

void time_shell() {

    char *value = getenv("USER");
    printf("%s %s> ", value, modify_time2());
}
