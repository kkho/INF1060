#include "macros.h"

int main() {
int pos_max = 999;
int min_num = -999;
int increase = 0;

char *h = "Hello World";
char *h2 = "Hello World";


if(compare_to(h,h2)) {
	printf("equals\n");
}

printf("the number before: %d\n",increase);
inc(increase);
printf("the number now: %d\n",increase);

int value = 1000;
printf("The max number: %d\n",max(value,pos_max));
int min_value = -10000;
printf("The min value: %d\n",min(min_value,min_num));

/*try out yourself :)*/


return 0;
}
