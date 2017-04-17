#ifndef SETTINGS_H
#define SETTINGS_H

/*
* General settings used throughout the code
*/

/*------------------------------ DEBUG & INIT ------------------------------- */
#define DEBUG     0
#define CONSOLE   1
// Macro for checking if debug is on
#define IF_DEBUG if(CONSOLE && DEBUG)
/*------------------------------ DEBUG & INIT ------------------------------- */

/* -------------------------------- WINDOW ---------------------------------- */
#define VIEWPORT_X 800
#define VIEWPORT_Y 450

#define ORTHO_X 300
#define ORTHO_Y 300
/* -------------------------------- WINDOW ---------------------------------- */

#endif
