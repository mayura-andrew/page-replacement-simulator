/*/*

============================================================================================================================================================

  GRAPHICS IMPLEMENTATION  GRAPHICS IMPLEMENTATION

  All graphics and UI functions for the page replacement simulator  All graphics and UI functions for the page replacement simulator

============================================================================================================================================================

*/*/



#include <graphics.h>#include <graphics.h>

#include <stdio.h>#include <stdio.h>

#include <conio.h>#include <conio.h>

#include <string.h>#include <string.h>

#include <stdlib.h>#include <stdlib.h>

#include "graphics.h"#include "graphics.h"

#include "config.h"#include "config.h"



/* Global graphics state *//* Global graphics state */

static int g_driver = DETECT;static int g_driver = DETECT;

static int g_mode;static int g_mode;

static int g_screenWidth = 0;static int g_screenWidth = 0;

static int g_screenHeight = 0;static int g_screenHeight = 0;



/*/*

 * Initialize graphics system * Initialize graphics system

 */ */

Boolean initGraphicsSystem(void) {Boolean initGraphicsSystem(void) {

    initgraph(&g_driver, &g_mode, BGI_PATH);    initgraph(&g_driver, &g_mode, BGI_PATH);

        

    if(graphresult() != grOk) {    if(graphresult() != grOk) {

        printf("Graphics initialization failed!\n");        printf("Graphics initialization failed!\n");

        printf("Make sure BGI drivers are in %s\n", BGI_PATH);        printf("Make sure BGI drivers are in %s\n", BGI_PATH);

        return FALSE;        return FALSE;

    }    }

        

    g_screenWidth = getmaxx();    g_screenWidth = getmaxx();

    g_screenHeight = getmaxy();    g_screenHeight = getmaxy();

    return TRUE;    return TRUE;

}}



/*/*

 * Close graphics system * Close graphics system

 */ */

void closeGraphicsSystem(void) {void closeGraphicsSystem(void) {

    closegraph();    closegraph();

}}



/*/*

 * Draw header bar with title * Draw header bar with title

 */ */

void drawHeader(char *title) {void drawHeader(char *title) {

    int x, y;    int x, y;

        

    setfillstyle(SOLID_FILL, HEADER_COLOR);    setfillstyle(SOLID_FILL, HEADER_COLOR);

    bar(0, 0, g_screenWidth, 80);    bar(0, 0, g_screenWidth, 80);

        

    setcolor(WHITE);    setcolor(WHITE);

    rectangle(0, 0, g_screenWidth, 80);    rectangle(0, 0, g_screenWidth, 80);

        

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);

    setcolor(BLUE);    setcolor(BLUE);

    x = (g_screenWidth - textwidth(title)) / 2;    x = (g_screenWidth - textwidth(title)) / 2;

    y = 30;    y = 30;

    outtextxy(x, y, title);    outtextxy(x, y, title);

}}



/*/*

 * Draw a button with 3D effect * Draw a button with 3D effect

 */ */

void drawButton(Button *btn) {void drawButton(Button *btn) {

    int textX, textY;    int textX, textY;

        

    /* Background */    /* Background */

    setfillstyle(SOLID_FILL, btn->color);    setfillstyle(SOLID_FILL, btn->color);

    bar(btn->x1, btn->y1, btn->x2, btn->y2);    bar(btn->x1, btn->y1, btn->x2, btn->y2);

        

    /* Border */    /* Border */

    setcolor(BLACK);    setcolor(BLACK);

    rectangle(btn->x1, btn->y1, btn->x2, btn->y2);    rectangle(btn->x1, btn->y1, btn->x2, btn->y2);

        

    /* 3D effect */    /* 3D effect */

    setcolor(WHITE);    setcolor(WHITE);

    line(btn->x1, btn->y1, btn->x2, btn->y1);    line(btn->x1, btn->y1, btn->x2, btn->y1);

    line(btn->x1, btn->y1, btn->x1, btn->y2);    line(btn->x1, btn->y1, btn->x1, btn->y2);

    setcolor(DARKGRAY);    setcolor(DARKGRAY);

    line(btn->x2, btn->y1, btn->x2, btn->y2);    line(btn->x2, btn->y1, btn->x2, btn->y2);

    line(btn->x1, btn->y2, btn->x2, btn->y2);    line(btn->x1, btn->y2, btn->x2, btn->y2);

        

    /* Center text */    /* Center text */

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

    setcolor(BLACK);    setcolor(BLACK);

    textX = btn->x1 + (BUTTON_WIDTH - textwidth(btn->text)) / 2;    textX = btn->x1 + (BUTTON_WIDTH - textwidth(btn->text)) / 2;

    textY = btn->y1 + (BUTTON_HEIGHT - textheight(btn->text)) / 2;    textY = btn->y1 + (BUTTON_HEIGHT - textheight(btn->text)) / 2;

    outtextxy(textX, textY, btn->text);    outtextxy(textX, textY, btn->text);

}}



/*/*

 * Draw a frame box showing page number * Draw a frame box showing page number

 */ */

void drawFrameBox(int x, int y, int frame) {void drawFrameBox(int x, int y, int frame) {

    char str[10];    char str[10];

        

    setfillstyle(SOLID_FILL, FRAME_COLOR);    setfillstyle(SOLID_FILL, FRAME_COLOR);

    bar(x, y, x + 40, y + 30);    bar(x, y, x + 40, y + 30);

    setcolor(BLACK);    setcolor(BLACK);

    rectangle(x, y, x + 40, y + 30);    rectangle(x, y, x + 40, y + 30);

        

    if(frame >= 0) {    if(frame >= 0) {

        sprintf(str, "%d", frame);        sprintf(str, "%d", frame);

        settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);        settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

        outtextxy(x + 15, y + 10, str);        outtextxy(x + 15, y + 10, str);

    }    }

}}



/*/*

 * Display message at bottom of screen * Display message at bottom of screen

 */ */

void showMessage(char *msg) {void showMessage(char *msg) {

    int x, y;    int x, y;

        

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

    setcolor(WHITE);    setcolor(WHITE);

    x = (g_screenWidth - textwidth(msg)) / 2;    x = (g_screenWidth - textwidth(msg)) / 2;

    y = g_screenHeight - 30;    y = g_screenHeight - 30;

    outtextxy(x, y, msg);    outtextxy(x, y, msg);

}}



/*/*

 * Draw main menu screen * Draw main menu screen

 */ */

void drawMainMenu(void) {void drawMainMenu(void) {

    drawHeader("PAGE REPLACEMENT SIMULATOR");    drawHeader("PAGE REPLACEMENT SIMULATOR");

        

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

    setcolor(WHITE);    setcolor(WHITE);

    outtextxy(180, 140, "Student ID: 722516877");    outtextxy(180, 140, "Student ID: 722516877");

    outtextxy(130, 160, "EEX5564 - Computer Architecture & OS");    outtextxy(130, 160, "EEX5564 - Computer Architecture & OS");

        

    setcolor(YELLOW);    setcolor(YELLOW);

    outtextxy(200, 450, "Press 1-4 to select option");    outtextxy(200, 450, "Press 1-4 to select option");

}}



/*/*

 * Check if point is inside button * Check if point is inside button

 */ */

Boolean isInsideButton(Button *btn, int x, int y) {Boolean isInsideButton(const Button *btn, int x, int y) {

    return (x >= btn->x1 && x <= btn->x2 && y >= btn->y1 && y <= btn->y2);    return (x >= btn->x1 && x <= btn->x2 && 

}            y >= btn->y1 && y <= btn->y2) ? TRUE : FALSE;

}

/*

 * Wait for user input (keyboard simulation)/*

 */ * Wait for user input (keyboard simulation)

void waitForUserInput(int *x, int *y) { */

    int ch;void waitForUserInput(int *x, int *y) {

        int ch;

    showMessage("Press 1=FIFO, 2=LRU, 3=Compare, 4=Exit");    

    ch = getch();    showMessage("Press 1=FIFO, 2=LRU, 3=Compare, 4=Exit");

        ch = getch();

    /* Simulate click positions */    

    if(ch == '1') {    /* Simulate click positions */

        *x = 325; *y = 220;    switch(ch) {

    } else if(ch == '2') {        case '1':

        *x = 325; *y = 280;            *x = 325; *y = 220;

    } else if(ch == '3') {            break;

        *x = 325; *y = 340;        case '2':

    } else if(ch == '4' || ch == 27) {            *x = 325; *y = 280;

        *x = 325; *y = 400;            break;

    } else {        case '3':

        *x = 325; *y = 220;            *x = 325; *y = 340;

    }            break;

}        case '4':

        case 27: /* ESC */

/*            *x = 325; *y = 400;

 * Get input parameters from user (console mode)            break;

 */        default:

void getInputParameters(InputParameters *params) {            *x = 325; *y = 220;

    int i;    }

    }

    cleardevice();

    drawHeader("INPUT PARAMETERS");/*

     * Get input parameters from user (console mode)

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2); */

    setcolor(WHITE);Boolean getInputParameters(InputParameters *params) {

    outtextxy(150, 150, "Enter values in console window...");    int i;

    outtextxy(150, 200, "Then press any key to continue");    

        cleardevice();

    closegraph();    drawHeader("INPUT PARAMETERS");

        

    printf("\n\n  ===== INPUT PARAMETERS =====\n\n");    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);

    printf("  Enter number of page references (1-%d): ", MAX_PAGES);    setcolor(WHITE);

    scanf("%d", &params->refLength);    outtextxy(150, 150, "Enter values in console window...");

        

    if(params->refLength < 1 || params->refLength > MAX_PAGES) {    closegraph();

        printf("  Invalid! Using default: %d\n", MAX_PAGES);    

        params->refLength = MAX_PAGES;    printf("\n\n  ===== INPUT PARAMETERS =====\n\n");

    }    printf("  Enter number of page references (1-%d): ", MAX_PAGES);

        scanf("%d", &params->refLength);

    printf("\n  Enter %d page numbers (space-separated):\n  ", params->refLength);    

    for(i = 0; i < params->refLength; i++) {    if(params->refLength < 1 || params->refLength > MAX_PAGES) {

        scanf("%d", &params->refString[i]);        printf("  Invalid! Using default: %d\n", MAX_PAGES);

    }        params->refLength = MAX_PAGES;

        }

    printf("\n  Enter number of frames (%d-%d): ", MIN_FRAMES, MAX_FRAMES);    

    scanf("%d", &params->numFrames);    printf("\n  Enter %d page numbers:\n  ", params->refLength);

        for(i = 0; i < params->refLength; i++) {

    if(params->numFrames < MIN_FRAMES || params->numFrames > MAX_FRAMES) {        scanf("%d", &params->refString[i]);

        printf("  Invalid! Using default: %d\n", MIN_FRAMES);    }

        params->numFrames = MIN_FRAMES;    

    }    printf("\n  Enter number of frames (%d-%d): ", MIN_FRAMES, MAX_FRAMES);

        scanf("%d", &params->numFrames);

    printf("\n  Input accepted! Press any key...");    

    getch();    if(params->numFrames < MIN_FRAMES || params->numFrames > MAX_FRAMES) {

            printf("  Invalid! Using default: %d\n", MIN_FRAMES);

    initgraph(&g_driver, &g_mode, BGI_PATH);        params->numFrames = MIN_FRAMES;

}    }

    

/*    printf("\n  Input accepted! Press any key...");

 * Draw simulation results screen    getch();

 */    

void drawResultsScreen(SimulationResult *result) {    initgraph(&g_driver, &g_mode, BGI_PATH);

    int i, j, x, y;    return TRUE;

    char str[50];}

    

    cleardevice();/*

     * Draw simulation results screen

    sprintf(str, "%s ALGORITHM RESULTS", result->algorithm); */

    drawHeader(str);void drawResultsScreen(const SimulationResult *result) {

        int i, j, x, y;

    /* Reference string */    char str[MAX_STRING_LENGTH];

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);    

    setcolor(WHITE);    cleardevice();

    outtextxy(20, 100, "Reference String:");    

    x = 200;    sprintf(str, "%s ALGORITHM RESULTS", result->algorithm);

    for(i = 0; i < result->refLength; i++) {    drawHeader(str);

        sprintf(str, "%d", result->refString[i]);    

        outtextxy(x, 100, str);    /* Reference string */

        x += 30;    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

    }    setcolor(WHITE);

        outtextxy(20, 100, "Reference String:");

    /* Step execution */    x = 200;

    setcolor(YELLOW);    for(i = 0; i < result->refLength; i++) {

    outtextxy(20, 130, "Step-by-Step Execution:");        sprintf(str, "%d", result->refString[i]);

            outtextxy(x, 100, str);

    y = 160;        x += 30;

    for(i = 0; i < result->refLength && i < 8; i++) {    }

        sprintf(str, "%d.", i + 1);    

        setcolor(WHITE);    /* Step execution */

        outtextxy(20, y, str);    setcolor(YELLOW);

            outtextxy(20, 130, "Step-by-Step Execution:");

        sprintf(str, "Page %d", result->refString[i]);    

        outtextxy(50, y, str);    y = 160;

            for(i = 0; i < result->refLength && i < MAX_VISIBLE_STEPS; i++) {

        x = 150;        sprintf(str, "%d.", i + 1);

        for(j = 0; j < result->frameCounts[i]; j++) {        setcolor(WHITE);

            drawFrameBox(x, y - 5, result->frames[i][j]);        outtextxy(20, y, str);

            x += 50;        

        }        sprintf(str, "Page %d", result->refString[i]);

                outtextxy(50, y, str);

        x = 400;        

        if(result->faults[i]) {        x = 150;

            setcolor(FAULT_COLOR);        for(j = 0; j < result->frameCounts[i]; j++) {

            outtextxy(x, y, "FAULT");            drawFrameBox(x, y - 5, result->frames[i][j]);

        } else {            x += 50;

            setcolor(HIT_COLOR);        }

            outtextxy(x, y, "HIT");        

        }        x = 400;

                if(result->faults[i]) {

        y += 35;            setcolor(FAULT_COLOR);

    }            outtextxy(x, y, "FAULT");

            } else {

    /* Summary */            setcolor(HIT_COLOR);

    y = 420;            outtextxy(x, y, "HIT");

    setfillstyle(SOLID_FILL, SUMMARY_BG_COLOR);        }

    bar(20, y, g_screenWidth - 20, y + 60);        

    setcolor(WHITE);        y += STEP_SPACING;

    rectangle(20, y, g_screenWidth - 20, y + 60);    }

        

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);    /* Summary */

    sprintf(str, "Total Page Faults: %d", result->totalFaults);    y = 420;

    outtextxy(40, y + 15, str);    setfillstyle(SOLID_FILL, SUMMARY_BG_COLOR);

        bar(20, y, g_screenWidth - 20, y + 60);

    sprintf(str, "Hit Ratio: %.2f%%", result->hitRatio);    setcolor(WHITE);

    outtextxy(300, y + 15, str);    rectangle(20, y, g_screenWidth - 20, y + 60);

        

    showMessage("Press any key to continue...");    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

}    sprintf(str, "Total Page Faults: %d", result->totalFaults);

    outtextxy(40, y + 15, str);
    
    sprintf(str, "Hit Ratio: %.2f%%", result->hitRatio);
    outtextxy(300, y + 15, str);
    
    showMessage("Press any key to continue...");
}
