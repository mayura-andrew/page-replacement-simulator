#ifndef TYPES_H
#define TYPES_H

#include "config.h"

/*
==============================================================================
  TYPE DEFINITIONS
  Contains all structure and type definitions
==============================================================================
*/

/* Boolean type for Turbo C */
#define TRUE 1
#define FALSE 0
typedef int Boolean;

/* Button structure for GUI */
typedef struct {
    int x1, y1;
    int x2, y2;
    char text[30];
    int color;
} Button;

/* Input parameters structure */
typedef struct {
    int refString[MAX_PAGES];
    int refLength;
    int numFrames;
} InputParameters;

/* Simulation result structure */
typedef struct {
    int refString[MAX_PAGES];
    int refLength;
    int frames[MAX_PAGES][MAX_FRAMES];
    int frameCounts[MAX_PAGES];
    int faults[MAX_PAGES];
    int totalFaults;
    float hitRatio;
    char algorithm[MAX_ALGORITHM_NAME];
} SimulationResult;

#endif /* TYPES_H */
