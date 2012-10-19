
#ifndef FRUIT_H
#define FRUIT_H


struct fruit_t
{

	int x;
	int y;
	int bonus;

};


/** One global copy of the fruit */
extern struct fruit_t fruit;


void fruit_init ();
void fruit_update_bonus ();


#endif
