#include "hello.h"

extern void print_world(); //don't need this at all since we include the prototype in hello.h

int main() {
    print_world();
    return 0;
}
