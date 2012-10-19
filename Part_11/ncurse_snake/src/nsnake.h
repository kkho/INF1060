

#ifndef NSNAKE_H
#define NSNAKE_H


#ifndef TRUE
  /** Boolean type TRUE - this will make things easier to read */
  #define TRUE  1
#endif

#ifndef FALSE
  /** Boolean type FALSE - this will make things easier to read */
  #define FALSE 0
#endif


/** Global definitions related to the game in general.
 */
struct game_t
{
	/** The collision mode of the game */
	int mode;
	/** Tells how fast will the snake move */
	int level;

	/** Flag that tells if we could open the highscores file */
	int cant_open_hscore_file;
};


/** The global game structure */
extern struct game_t game;


/** The possible Game Modes.
 *
 *  In Normal Mode, the snake dies by colliding with itself or the borders. @n
 *  In Teleport Mode, the snake only dies by colliding with itself. @n
 */
enum modes { FREE_MODE, BORDERS_ON, BORDERS_OFF };


void nsnake_abort (char* error_msg);
void nsnake_exit ();
void nsnake_game_over ();
void nsnake_init ();
void nsnake_pause ();


#endif
