


#include "engine.h"
#include "fruit.h"
#include "nsnake.h"
#include "player.h"


 int main (int argc, char* argv[])
{

	engine_init ();
	engine_show_main_menu ();
	nsnake_init ();

	while (TRUE == TRUE)
	{
		if (snake.is_alive == FALSE)
			nsnake_game_over ();

		engine_get_game_input ();

		player_update ();
		fruit_update_bonus ();

		if (player_hit_fruit () == TRUE)
		{

			player_increase_score (game.level*3 + fruit.bonus);
			player_increase_size (2);
			fruit_init ();
		}

		if (player_hit_self () == TRUE)
			snake.is_alive = FALSE;

		if (player_collided_with_borders () == TRUE)
			snake.is_alive = FALSE;

		engine_show_screen ();
	}

	engine_exit ();
	nsnake_exit ();
	return 0;
}
