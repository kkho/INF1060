


#ifndef ENGINE_H
#define ENGINE_H


struct screen_t
{

	int width;
	int height;
	int delay;
};


/** The global screen structure */
extern struct screen_t screen;


void draw_background ();
void draw_borders ();
void draw_fruit ();
void draw_fruit_bonus ();
void draw_player ();
void draw_score ();

void engine_exit ();
void engine_init ();
void engine_show_game_over ();
void engine_show_main_menu ();
void engine_show_pause ();
void engine_show_screen ();

int  get_main_menu_input (int* current_option);
void engine_get_game_input ();
void get_game_over_input ();
void get_pause_input ();


#endif
