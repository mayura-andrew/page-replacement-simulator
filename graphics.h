#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "types.h"

/*
==============================================================================
  GRAPHICS FUNCTIONS
  Declarations for all graphics and UI functions
==============================================================================
*/

/* Graphics system management */
Boolean initGraphicsSystem(void);
void closeGraphicsSystem(void);

/* Screen drawing functions */
void drawMainMenu(void);
void drawHeader(char *title);
void drawButton(Button *btn);
void drawResultsScreen(SimulationResult *result);
void drawFrameBox(int x, int y, int frame);
void showMessage(char *msg);

/* Input handling */
void waitForUserInput(int *x, int *y);
Boolean isInsideButton(Button *btn, int x, int y);
void getInputParameters(InputParameters *params);

#endif /* GRAPHICS_H */
