/*#include <string.h>

==============================================================================#include "algorithm.h"

  ALGORITHM IMPLEMENTATION

  Page replacement algorithms: FIFO and LRU/*

============================================================================== * Check if page exists in frames

*/ */

Boolean isPageInFrames(int page, const int *frames, int frameCount) {

#include <string.h>    int i;

#include "algorithm.h"    for(i = 0; i < frameCount; i++) {

#include "config.h"        if(frames[i] == page) {

            return TRUE;

/*        }

 * Check if page exists in frames    }

 */    return FALSE;

Boolean isPageInFrames(int page, int *frames, int count) {}

    int i;

    for(i = 0; i < count; i++) {/*

        if(frames[i] == page) { * Initialize simulation result structure

            return TRUE; */

        }void initializeResult(SimulationResult *result, const InputParameters *params,

    }                     const char *algoName) {

    return FALSE;    int i;

}    

    strcpy(result->algorithm, algoName);

/*    result->refLength = params->refLength;

 * FIFO Page Replacement Algorithm    

 */    for(i = 0; i < params->refLength; i++) {

void simulateFIFO(int *refString, int length, int numFrames,         result->refString[i] = params->refString[i];

                  SimulationResult *result) {        result->faults[i] = FALSE;

    int frames[MAX_FRAMES];        result->frameCounts[i] = 0;

    int queue[MAX_FRAMES];    }

    int frameCount = 0;    

    int queueFront = 0, queueRear = 0;    result->totalFaults = 0;

    int pageFaults = 0;    result->hitRatio = 0.0;

    int i, j;}

    

    strcpy(result->algorithm, "FIFO");/*

    result->refLength = length; * FIFO Page Replacement Algorithm

     */

    /* Initialize frames */void simulateFIFO(const InputParameters *params, SimulationResult *result) {

    for(i = 0; i < MAX_FRAMES; i++) {    int frames[MAX_FRAMES];

        frames[i] = -1;    int queue[MAX_FRAMES];

    }    int frameCount = 0;

        int queueFront = 0, queueRear = 0;

    /* Copy reference string */    int pageFaults = 0;

    for(i = 0; i < length; i++) {    int i, j;

        result->refString[i] = refString[i];    

    }    initializeResult(result, params, "FIFO");

        

    /* Process each page reference */    /* Initialize frames */

    for(i = 0; i < length; i++) {    for(i = 0; i < MAX_FRAMES; i++) {

        int page = refString[i];        frames[i] = -1;

        int found = isPageInFrames(page, frames, frameCount);    }

            

        if(!found) {    /* Process each page reference */

            /* Page fault */    for(i = 0; i < params->refLength; i++) {

            pageFaults++;        int page = params->refString[i];

            result->faults[i] = 1;        Boolean found = isPageInFrames(page, frames, frameCount);

                    

            if(frameCount < numFrames) {        if(!found) {

                /* Add to empty frame */            /* Page fault */

                frames[frameCount++] = page;            pageFaults++;

                queue[queueRear++] = page;            result->faults[i] = TRUE;

            } else {            

                /* Replace oldest page (FIFO) */            if(frameCount < params->numFrames) {

                int oldest = queue[queueFront];                /* Add to empty frame */

                queueFront = (queueFront + 1) % numFrames;                frames[frameCount++] = page;

                                queue[queueRear++] = page;

                for(j = 0; j < frameCount; j++) {            } else {

                    if(frames[j] == oldest) {                /* Replace oldest page (FIFO) */

                        frames[j] = page;                int oldest = queue[queueFront];

                        break;                queueFront = (queueFront + 1) % params->numFrames;

                    }                

                }                for(j = 0; j < frameCount; j++) {

                queue[queueRear] = page;                    if(frames[j] == oldest) {

                queueRear = (queueRear + 1) % numFrames;                        frames[j] = page;

            }                        break;

        } else {                    }

            result->faults[i] = 0;                }

        }                queue[queueRear] = page;

                        queueRear = (queueRear + 1) % params->numFrames;

        /* Save current frame state */            }

        result->frameCounts[i] = frameCount;        }

        for(j = 0; j < frameCount; j++) {        

            result->frames[i][j] = frames[j];        /* Save current frame state */

        }        result->frameCounts[i] = frameCount;

    }        for(j = 0; j < frameCount; j++) {

                result->frames[i][j] = frames[j];

    result->totalFaults = pageFaults;        }

    result->hitRatio = ((float)(length - pageFaults) / length) * 100.0;    }

}    

    result->totalFaults = pageFaults;

/*    result->hitRatio = ((float)(params->refLength - pageFaults) / 

 * LRU Page Replacement Algorithm                        params->refLength) * 100.0;

 */}

void simulateLRU(int *refString, int length, int numFrames, 

                 SimulationResult *result) {/*

    int frames[MAX_FRAMES]; * LRU Page Replacement Algorithm

    int lastUsed[MAX_FRAMES]; */

    int frameCount = 0;void simulateLRU(const InputParameters *params, SimulationResult *result) {

    int pageFaults = 0;    int frames[MAX_FRAMES];

    int i, j;    int lastUsed[MAX_FRAMES];

        int frameCount = 0;

    strcpy(result->algorithm, "LRU");    int pageFaults = 0;

    result->refLength = length;    int i, j;

        

    /* Initialize */    initializeResult(result, params, "LRU");

    for(i = 0; i < MAX_FRAMES; i++) {    

        frames[i] = -1;    /* Initialize */

        lastUsed[i] = -1;    for(i = 0; i < MAX_FRAMES; i++) {

    }        frames[i] = -1;

            lastUsed[i] = -1;

    /* Copy reference string */    }

    for(i = 0; i < length; i++) {    

        result->refString[i] = refString[i];    /* Process each page reference */

    }    for(i = 0; i < params->refLength; i++) {

            int page = params->refString[i];

    /* Process each page reference */        Boolean found = FALSE;

    for(i = 0; i < length; i++) {        

        int page = refString[i];        /* Check if page in frames and update last used */

        int found = 0;        for(j = 0; j < frameCount; j++) {

                    if(frames[j] == page) {

        /* Check if page in frames and update last used */                found = TRUE;

        for(j = 0; j < frameCount; j++) {                lastUsed[j] = i;

            if(frames[j] == page) {                break;

                found = 1;            }

                lastUsed[j] = i;        }

                break;        

            }        if(!found) {

        }            /* Page fault */

                    pageFaults++;

        if(!found) {            result->faults[i] = TRUE;

            /* Page fault */            

            pageFaults++;            if(frameCount < params->numFrames) {

            result->faults[i] = 1;                /* Add to empty frame */

                            frames[frameCount] = page;

            if(frameCount < numFrames) {                lastUsed[frameCount] = i;

                /* Add to empty frame */                frameCount++;

                frames[frameCount] = page;            } else {

                lastUsed[frameCount] = i;                /* Replace least recently used */

                frameCount++;                int lruIndex = 0;

            } else {                int lruTime = lastUsed[0];

                /* Replace least recently used */                

                int lruIndex = 0;                for(j = 1; j < frameCount; j++) {

                int lruTime = lastUsed[0];                    if(lastUsed[j] < lruTime) {

                                        lruTime = lastUsed[j];

                for(j = 1; j < frameCount; j++) {                        lruIndex = j;

                    if(lastUsed[j] < lruTime) {                    }

                        lruTime = lastUsed[j];                }

                        lruIndex = j;                

                    }                frames[lruIndex] = page;

                }                lastUsed[lruIndex] = i;

                            }

                frames[lruIndex] = page;        }

                lastUsed[lruIndex] = i;        

            }        /* Save current frame state */

        } else {        result->frameCounts[i] = frameCount;

            result->faults[i] = 0;        for(j = 0; j < frameCount; j++) {

        }            result->frames[i][j] = frames[j];

                }

        /* Save current frame state */    }

        result->frameCounts[i] = frameCount;    

        for(j = 0; j < frameCount; j++) {    result->totalFaults = pageFaults;

            result->frames[i][j] = frames[j];    result->hitRatio = ((float)(params->refLength - pageFaults) / 

        }                        params->refLength) * 100.0;

    }}

    
    result->totalFaults = pageFaults;
    result->hitRatio = ((float)(length - pageFaults) / length) * 100.0;
}
