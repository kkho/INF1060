

#ifndef PLAYER_H
#define PLAYER_H


#include "nsnake.h"

struct player_pieces_t
{
	int x;
	int y;
};


/** A simple enum to make the directions of the player easier to read.
 */
enum directions { UP = 0, LEFT, DOWN, RIGHT };


struct player_t
{

	int is_alive;

	int	speed;

	int	size;

	int score;


	int direction;

	struct player_pieces_t* body;
};


/** The player himself */
extern struct player_t snake;


void player_change_direction (int new_direction);
int player_collided_with_borders ();
void player_exit ();
int  player_hit_borders ();
int  player_hit_fruit ();
int  player_hit_self ();
void player_increase_score (int add);
void player_increase_size (int size);
void player_init ();
void player_teleport_borders ();
void player_update ();


#endif
