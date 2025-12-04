/*
==============================================================================
  PAGE REPLACEMENT SIMULATOR - MAIN PROGRAM
  Student ID: 722516877
  Group B - Page Replacement Algorithm Simulator
  
  Uses Borland Graphics Interface (BGI) for GUI in Turbo C
  Compatible with: Turbo C/C++ 3.0 in DOSBox
==============================================================================
*/

#include <conio.h>
#include <string.h>
#include "config.h"
#include "types.h"
#include "graphics.h"
#include "algorithm.h"

/*
 * Main program entry point
 */
int main(void) {
    InputParameters params;
    SimulationResult result, result2;
    int clickX, clickY;
    Button btn1, btn2, btn3, btn4;
    
    if(!initGraphicsSystem()) {
        return 1;
    }
    
    while(1) {
        cleardevice();
        drawMainMenu();
        
        /* Define buttons */
        btn1.x1 = 250; btn1.y1 = 200;
        btn1.x2 = btn1.x1 + BUTTON_WIDTH;
        btn1.y2 = btn1.y1 + BUTTON_HEIGHT;
        strcpy(btn1.text, "FIFO Algorithm");
        btn1.color = LIGHTGREEN;
        
        btn2.x1 = 250; btn2.y1 = 260;
        btn2.x2 = btn2.x1 + BUTTON_WIDTH;
        btn2.y2 = btn2.y1 + BUTTON_HEIGHT;
        strcpy(btn2.text, "LRU Algorithm");
        btn2.color = LIGHTCYAN;
        
        btn3.x1 = 250; btn3.y1 = 320;
        btn3.x2 = btn3.x1 + BUTTON_WIDTH;
        btn3.y2 = btn3.y1 + BUTTON_HEIGHT;
        strcpy(btn3.text, "Compare Both");
        btn3.color = LIGHTMAGENTA;
        
        btn4.x1 = 250; btn4.y1 = 380;
        btn4.x2 = btn4.x1 + BUTTON_WIDTH;
        btn4.y2 = btn4.y1 + BUTTON_HEIGHT;
        strcpy(btn4.text, "Exit");
        btn4.color = LIGHTRED;
        
        /* Draw buttons */
        drawButton(&btn1);
        drawButton(&btn2);
        drawButton(&btn3);
        drawButton(&btn4);
        
        /* Wait for user selection */
        waitForUserInput(&clickX, &clickY);
        
        /* Process selection */
        if(isInsideButton(&btn1, clickX, clickY)) {
            /* FIFO Algorithm */
            getInputParameters(&params);
            simulateFIFO(params.refString, params.refLength, params.numFrames, &result);
            drawResultsScreen(&result);
            getch();
        }
        else if(isInsideButton(&btn2, clickX, clickY)) {
            /* LRU Algorithm */
            getInputParameters(&params);
            simulateLRU(params.refString, params.refLength, params.numFrames, &result);
            drawResultsScreen(&result);
            getch();
        }
        else if(isInsideButton(&btn3, clickX, clickY)) {
            /* Compare Both Algorithms */
            getInputParameters(&params);
            
            /* Run FIFO */
            simulateFIFO(params.refString, params.refLength, params.numFrames, &result);
            drawResultsScreen(&result);
            showMessage("Press any key for LRU results...");
            getch();
            
            /* Run LRU */
            simulateLRU(params.refString, params.refLength, params.numFrames, &result2);
            drawResultsScreen(&result2);
            getch();
        }
        else if(isInsideButton(&btn4, clickX, clickY)) {
            /* Exit */
            break;
        }
    }
    
    closeGraphicsSystem();
    return 0;
}
