#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "types.h"

/*
==============================================================================
  ALGORITHM FUNCTIONS
  Declarations for page replacement algorithms
==============================================================================
*/

/* Page replacement algorithms */
void simulateFIFO(int *refString, int length, int numFrames, 
                  SimulationResult *result);
void simulateLRU(int *refString, int length, int numFrames, 
                 SimulationResult *result);

/* Utility functions */
Boolean isPageInFrames(int page, int *frames, int count);

#endif /* ALGORITHM_H */
