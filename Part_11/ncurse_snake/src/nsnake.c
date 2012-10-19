

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nsnake.h"
#include "engine.h"
#include "fruit.h"
#include "player.h"
#include "hscores.h"


struct game_t game;


/**	Aborts the game and displays the error message
 *
 */
void nsnake_abort (char* error_msg)
{
	engine_exit ();
	printf ("%s", error_msg);
	exit (EXIT_FAILURE);
}


/**	Interrupts the game and quits to the terminal.
 *
 */
void nsnake_exit ()
{
	if (snake.body != NULL)
	{
		free (snake.body);
		snake.body = NULL;
	}

	if (game.cant_open_hscore_file == 1)
		printf ("* Couldn't open Highscore file! Make sure the game is installed.\n  Please see 'man nsnake' for bug reports\n");

	exit (EXIT_SUCCESS);
}


/**	Finish the game after the snake have lost a life.
 *
 * 	@see	engine_show_game_over()
 * 	@see	get_game_over_input()
 */
void nsnake_game_over ()
{
	if (game.mode == BORDERS_ON)
	{
		if (snake.score > HIGH_SCORE_BORDERS)
			hscore_store ();
	}
	else if (game.mode == BORDERS_OFF)
	{
		if (snake.score > HIGH_SCORE_BORDERS_OFF)
			hscore_store ();
	}

	engine_show_game_over ();
	get_game_over_input ();

	nsnake_init ();
}


/**	Starts all the necessairy stuff.
 *
 *	Sets all the global variables and call the initial functions so the
 *	game may start.
 * 	@see	hscore_init()
 * 	@see	player_init()
 * 	@see	fruit_init()
 * 	@see	engine_show_screen()
 */
void nsnake_init ()
{
	player_init ();
	fruit_init ();
	hscore_init ();
	engine_show_screen ();
}


/**	It, umm, pauses the game, i guess
 */
void nsnake_pause ()
{
	engine_show_pause ();
}


/*------------------------------END-------------------------------------------*/
