

#ifndef HSCORES_H
#define HSCORES_H


/** HighScore of the game mode with borders */
extern int HIGH_SCORE_BORDERS;
/** HighScore of the game mode without borders */
extern int HIGH_SCORE_BORDERS_OFF;


void hscore_clean ();
void hscore_init ();
void hscore_store ();

 #endif
