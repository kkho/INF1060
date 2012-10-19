#ifndef HELLO_H
#define HELLO_H
/*
Include guards.
Once the header is included, it checks if a unique value is defined. Then if it's not defined,
 * it defines it and continues to the rest of the page.
When the code is included again, the first ifndef fails, resulting in a blank file.
That prevent double declaration of any identifiers such as types, enums and static variables.*/
void print_world();
/*
omits the function body but does specify the function's return type, name, arity and argument types. 
While a function definition specifies what a function does, a function prototype can be thought of as specifying its interface.
 */

#endif
