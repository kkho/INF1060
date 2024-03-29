

#include <stdlib.h>
#include <time.h>

#include "fruit.h"
#include "engine.h"
#include "player.h"


struct fruit_t	fruit;


/**	Creates a fruit in a random place
 *
 */
void fruit_init ()
{
	int top = 50;
	int bottom = 10;
	int valid_fruit = FALSE;


	// Create a seed for generating random numbers based on the time
	srand (time (NULL));

	while (valid_fruit == FALSE)
	{
		// Generate a random number between the screen limits
		fruit.x = rand() % ((screen.width-2) - 1 + 1) + 1;
		fruit.y = rand() % ((screen.height-2) - 2 + 2) + 2;

		// Generates a random value between 'top' and 'bottom'
		fruit.bonus += rand() % (top - bottom + 1) + bottom;

		if (fruit.y != screen.height-1)
			valid_fruit = TRUE;

		// Lets make sure the fruit doesnt start at the snake body
		int i;
		for (i = 0; i < (snake.size-1); i++)
		{
			if ((fruit.x == snake.body[i].x) &&
			    (fruit.y == snake.body[i].y))
			{
				valid_fruit = FALSE;
				break;
			}
		}
	}
}


/**	Drops the bonus value of the fruit for each 'frame'
 */
void fruit_update_bonus ()
{
	if (fruit.bonus > 0)
		fruit.bonus--;
}
