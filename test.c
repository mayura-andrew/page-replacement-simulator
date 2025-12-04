/*
==============================================================================
  PAGE REPLACEMENT SIMULATOR - STANDALONE VERSION
  Student ID: 722516877
  Group B - Page Replacement Algorithm Simulator
  
  This is a standalone single-file version for testing purposes
  For modular version, use main.c with the separate module files
  
  Uses Borland Graphics Interface (BGI) for GUI in Turbo C
  Compatible with: Turbo C/C++ 3.0 in DOSBox
==============================================================================
*/

#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

/* Constants */
#define MAX_PAGES 10
#define MIN_FRAMES 3
#define MAX_FRAMES 5
#define BUTTON_WIDTH 150
#define BUTTON_HEIGHT 40

/* Colors */
#define HEADER_COLOR LIGHTBLUE
#define BUTTON_COLOR LIGHTGREEN
#define BUTTON_TEXT COLOR BLACK
#define FRAME_COLOR YELLOW
#define FAULT_COLOR RED
#define HIT_COLOR GREEN

/* Structures */
struct Button {
    int x1, y1, x2, y2;
    char text[30];
    int color;
};

struct SimResult {
    int refString[MAX_PAGES];
    int refLength;
    int frames[MAX_PAGES][MAX_FRAMES];
    int frameCounts[MAX_PAGES];
    int faults[MAX_PAGES];
    int totalFaults;
    float hitRatio;
    char algorithm[10];
};

/* Global variables */
int gdriver = DETECT, gmode;
int screenWidth, screenHeight;

/* Function prototypes */
void initGraphics(void);
void closeGraphics(void);
void drawMainMenu(void);
void drawButton(struct Button btn);
int isInsideButton(struct Button btn, int x, int y);
void drawHeader(char *title);
void drawInputScreen(int *refString, int *refLength, int *numFrames);
void drawResultsScreen(struct SimResult *result);
void simulateFIFO(int *refString, int length, int numFrames, 
                  struct SimResult *result);
void simulateLRU(int *refString, int length, int numFrames, 
                 struct SimResult *result);
int isPageInFrames(int page, int *frames, int count);
void showMessage(char *msg);
void drawInputBox(int x, int y, int w, int h, char *label, char *value);
void drawFrameBox(int x, int y, int frame);
void waitForClick(int *x, int *y);

/*
==============================================================================
  MAIN FUNCTION
==============================================================================
*/
int main(void) {
    int choice;
    int refString[MAX_PAGES];
    int refLength;
    int numFrames;
    struct SimResult result;
    int clickX, clickY;
    struct Button btn1, btn2, btn3, btn4;
    
    initGraphics();
    
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
        drawButton(btn1);
        drawButton(btn2);
        drawButton(btn3);
        drawButton(btn4);
        
        /* Wait for click */
        waitForClick(&clickX, &clickY);
        
        /* Check which button was clicked */
        if(isInsideButton(btn1, clickX, clickY)) {
            /* FIFO */
            drawInputScreen(refString, &refLength, &numFrames);
            simulateFIFO(refString, refLength, numFrames, &result);
            drawResultsScreen(&result);
            getch();
        }
        else if(isInsideButton(btn2, clickX, clickY)) {
            /* LRU */
            drawInputScreen(refString, &refLength, &numFrames);
            simulateLRU(refString, refLength, numFrames, &result);
            drawResultsScreen(&result);
            getch();
        }
        else if(isInsideButton(btn3, clickX, clickY)) {
            /* Compare */
            struct SimResult result2;
            drawInputScreen(refString, &refLength, &numFrames);
            
            /* FIFO */
            simulateFIFO(refString, refLength, numFrames, &result);
            drawResultsScreen(&result);
            showMessage("Press any key for LRU results...");
            getch();
            
            /* LRU */
            simulateLRU(refString, refLength, numFrames, &result2);
            drawResultsScreen(&result2);
            getch();
        }
        else if(isInsideButton(btn4, clickX, clickY)) {
            /* Exit */
            break;
        }
    }
    
    closeGraphics();
    return 0;
}

/*
==============================================================================
  GRAPHICS INITIALIZATION
==============================================================================
*/
void initGraphics(void) {
    initgraph(&gdriver, &gmode, "C:\\TURBOC3\\BGI");
    
    if(graphresult() != grOk) {
        printf("Graphics initialization failed!\n");
        printf("Make sure BGI drivers are in C:\\TC\\BGI\n");
        exit(1);
    }
    
    screenWidth = getmaxx();
    screenHeight = getmaxy();
}

void closeGraphics(void) {
    closegraph();
}

/*
==============================================================================
  MAIN MENU SCREEN
==============================================================================
*/
void drawMainMenu(void) {
    drawHeader("PAGE REPLACEMENT SIMULATOR");
    
    /* Draw subtitle */
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    setcolor(WHITE);
    outtextxy(180, 140, "Student ID: 722516877");
    outtextxy(130, 160, "EEX5564 - Computer Architecture & OS");
    
    /* Instructions */
    setcolor(YELLOW);
    outtextxy(200, 450, "Click on a button to continue");
}

/*
==============================================================================
  DRAWING FUNCTIONS
==============================================================================
*/
void drawHeader(char *title) {
    int x, y;
    
    /* Draw header bar */
    setfillstyle(SOLID_FILL, HEADER_COLOR);
    bar(0, 0, screenWidth, 80);
    
    /* Draw border */
    setcolor(WHITE);
    rectangle(0, 0, screenWidth, 80);
    
    /* Draw title */
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
    setcolor(BLUE);
    x = (screenWidth - textwidth(title)) / 2;
    y = 30;
    outtextxy(x, y, title);
}

void drawButton(struct Button btn) {
    int textX, textY;
    
    /* Draw button background */
    setfillstyle(SOLID_FILL, btn.color);
    bar(btn.x1, btn.y1, btn.x2, btn.y2);
    
    /* Draw button border */
    setcolor(BLACK);
    rectangle(btn.x1, btn.y1, btn.x2, btn.y2);
    
    /* Draw 3D effect */
    setcolor(WHITE);
    line(btn.x1, btn.y1, btn.x2, btn.y1);
    line(btn.x1, btn.y1, btn.x1, btn.y2);
    setcolor(DARKGRAY);
    line(btn.x2, btn.y1, btn.x2, btn.y2);
    line(btn.x1, btn.y2, btn.x2, btn.y2);
    
    /* Draw text centered */
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    setcolor(BLACK);
    textX = btn.x1 + (BUTTON_WIDTH - textwidth(btn.text)) / 2;
    textY = btn.y1 + (BUTTON_HEIGHT - textheight(btn.text)) / 2;
    outtextxy(textX, textY, btn.text);
}

int isInsideButton(struct Button btn, int x, int y) {
    return (x >= btn.x1 && x <= btn.x2 && y >= btn.y1 && y <= btn.y2);
}

void drawFrameBox(int x, int y, int frame) {
    char str[10];
    
    /* Draw box */
    setfillstyle(SOLID_FILL, FRAME_COLOR);
    bar(x, y, x + 40, y + 30);
    setcolor(BLACK);
    rectangle(x, y, x + 40, y + 30);
    
    /* Draw frame number */
    if(frame >= 0) {
        sprintf(str, "%d", frame);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
        outtextxy(x + 15, y + 10, str);
    }
}

void showMessage(char *msg) {
    int x, y;
    
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    setcolor(WHITE);
    x = (screenWidth - textwidth(msg)) / 2;
    y = screenHeight - 30;
    outtextxy(x, y, msg);
}

/*
==============================================================================
  INPUT SCREEN (Simplified - uses console for input)
==============================================================================
*/
void drawInputScreen(int *refString, int *refLength, int *numFrames) {
    int i;
    
    cleardevice();
    drawHeader("INPUT PARAMETERS");
    
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    setcolor(WHITE);
    outtextxy(150, 150, "Enter values in console window...");
    outtextxy(150, 200, "Then click anywhere to continue");
    
    /* Switch to text mode for input */
    closegraph();
    
    /* Console input */
    printf("\n\n");
    printf("  ===== INPUT PARAMETERS =====\n\n");
    
    printf("  Enter number of page references (1-%d): ", MAX_PAGES);
    scanf("%d", refLength);
    
    if(*refLength < 1 || *refLength > MAX_PAGES) {
        printf("  Invalid! Using 10.\n");
        *refLength = 10;
    }
    
    printf("\n  Enter %d page numbers (space-separated):\n  ", *refLength);
    for(i = 0; i < *refLength; i++) {
        scanf("%d", &refString[i]);
    }
    
    printf("\n  Enter number of frames (%d-%d): ", MIN_FRAMES, MAX_FRAMES);
    scanf("%d", numFrames);
    
    if(*numFrames < MIN_FRAMES || *numFrames > MAX_FRAMES) {
        printf("  Invalid! Using 3.\n");
        *numFrames = 3;
    }
    
    printf("\n  Input accepted! Press any key...");
    getch();
    
    /* Return to graphics mode */
    initgraph(&gdriver, &gmode, "C:\\TURBOC3\\BGI");
}

/*
==============================================================================
  RESULTS SCREEN
==============================================================================
*/
void drawResultsScreen(struct SimResult *result) {
    int i, j;
    int x, y;
    char str[50];
    
    cleardevice();
    
    /* Header */
    sprintf(str, "%s ALGORITHM RESULTS", result->algorithm);
    drawHeader(str);
    
    /* Reference string */
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    setcolor(WHITE);
    outtextxy(20, 100, "Reference String:");
    x = 200;
    for(i = 0; i < result->refLength; i++) {
        sprintf(str, "%d", result->refString[i]);
        outtextxy(x, 100, str);
        x += 30;
    }
    
    /* Step-by-step visualization */
    setcolor(YELLOW);
    outtextxy(20, 130, "Step-by-Step Execution:");
    
    y = 160;
    for(i = 0; i < result->refLength && i < 8; i++) {
        /* Step number */
        sprintf(str, "%d.", i + 1);
        setcolor(WHITE);
        outtextxy(20, y, str);
        
        /* Page reference */
        sprintf(str, "Page %d", result->refString[i]);
        outtextxy(50, y, str);
        
        /* Frame boxes */
        x = 150;
        for(j = 0; j < result->frameCounts[i]; j++) {
            drawFrameBox(x, y - 5, result->frames[i][j]);
            x += 50;
        }
        
        /* Fault/Hit indicator */
        x = 400;
        if(result->faults[i]) {
            setcolor(FAULT_COLOR);
            outtextxy(x, y, "FAULT");
        } else {
            setcolor(HIT_COLOR);
            outtextxy(x, y, "HIT");
        }
        
        y += 35;
    }
    
    /* Summary statistics */
    y = 420;
    setfillstyle(SOLID_FILL, BLUE);
    bar(20, y, screenWidth - 20, y + 60);
    setcolor(WHITE);
    rectangle(20, y, screenWidth - 20, y + 60);
    
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    sprintf(str, "Total Page Faults: %d", result->totalFaults);
    outtextxy(40, y + 15, str);
    
    sprintf(str, "Hit Ratio: %.2f%%", result->hitRatio);
    outtextxy(300, y + 15, str);
    
    showMessage("Press any key to continue...");
}

/*
==============================================================================
  MOUSE/CLICK HANDLING (Simplified)
==============================================================================
*/
void waitForClick(int *x, int *y) {
    /* In Turbo C, mouse handling is complex */
    /* This simplified version uses keyboard */
    int ch;
    
    showMessage("Use arrow keys and Enter to select");
    
    ch = getch();
    
    /* Simulate click at button positions */
    if(ch == '1') {
        *x = 325; *y = 220;  /* FIFO button */
    } else if(ch == '2') {
        *x = 325; *y = 280;  /* LRU button */
    } else if(ch == '3') {
        *x = 325; *y = 340;  /* Compare button */
    } else if(ch == '4' || ch == 27) {  /* 4 or ESC */
        *x = 325; *y = 400;  /* Exit button */
    } else {
        *x = 325; *y = 220;  /* Default to FIFO */
    }
}

/*
==============================================================================
  UTILITY FUNCTIONS
==============================================================================
*/
int isPageInFrames(int page, int *frames, int count) {
    int i;
    for(i = 0; i < count; i++) {
        if(frames[i] == page) {
            return 1;
        }
    }
    return 0;
}

/*
==============================================================================
  FIFO ALGORITHM
==============================================================================
*/
void simulateFIFO(int *refString, int length, int numFrames, 
                  struct SimResult *result) {
    int frames[MAX_FRAMES];
    int queue[MAX_FRAMES];
    int frameCount = 0;
    int queueFront = 0, queueRear = 0;
    int pageFaults = 0;
    int i, j;
    
    strcpy(result->algorithm, "FIFO");
    result->refLength = length;
    
    /* Initialize */
    for(i = 0; i < MAX_FRAMES; i++) {
        frames[i] = -1;
    }
    
    /* Copy reference string */
    for(i = 0; i < length; i++) {
        result->refString[i] = refString[i];
    }
    
    /* Simulate */
    for(i = 0; i < length; i++) {
        int page = refString[i];
        int found = isPageInFrames(page, frames, frameCount);
        
        if(!found) {
            pageFaults++;
            result->faults[i] = 1;
            
            if(frameCount < numFrames) {
                frames[frameCount++] = page;
                queue[queueRear++] = page;
            } else {
                int oldest = queue[queueFront];
                queueFront = (queueFront + 1) % numFrames;
                
                for(j = 0; j < frameCount; j++) {
                    if(frames[j] == oldest) {
                        frames[j] = page;
                        break;
                    }
                }
                queue[queueRear] = page;
                queueRear = (queueRear + 1) % numFrames;
            }
        } else {
            result->faults[i] = 0;
        }
        
        /* Copy current frame state */
        result->frameCounts[i] = frameCount;
        for(j = 0; j < frameCount; j++) {
            result->frames[i][j] = frames[j];
        }
    }
    
    result->totalFaults = pageFaults;
    result->hitRatio = ((float)(length - pageFaults) / length) * 100.0;
}

/*
==============================================================================
  LRU ALGORITHM
==============================================================================
*/
void simulateLRU(int *refString, int length, int numFrames, 
                 struct SimResult *result) {
    int frames[MAX_FRAMES];
    int lastUsed[MAX_FRAMES];
    int frameCount = 0;
    int pageFaults = 0;
    int i, j;
    
    strcpy(result->algorithm, "LRU");
    result->refLength = length;
    
    /* Initialize */
    for(i = 0; i < MAX_FRAMES; i++) {
        frames[i] = -1;
        lastUsed[i] = -1;
    }
    
    /* Copy reference string */
    for(i = 0; i < length; i++) {
        result->refString[i] = refString[i];
    }
    
    /* Simulate */
    for(i = 0; i < length; i++) {
        int page = refString[i];
        int found = 0;
        
        /* Check if page in frames */
        for(j = 0; j < frameCount; j++) {
            if(frames[j] == page) {
                found = 1;
                lastUsed[j] = i;
                break;
            }
        }
        
        if(!found) {
            pageFaults++;
            result->faults[i] = 1;
            
            if(frameCount < numFrames) {
                frames[frameCount] = page;
                lastUsed[frameCount] = i;
                frameCount++;
            } else {
                int lruIndex = 0;
                int lruTime = lastUsed[0];
                
                for(j = 1; j < frameCount; j++) {
                    if(lastUsed[j] < lruTime) {
                        lruTime = lastUsed[j];
                        lruIndex = j;
                    }
                }
                
                frames[lruIndex] = page;
                lastUsed[lruIndex] = i;
            }
        } else {
            result->faults[i] = 0;
        }
        
        /* Copy current frame state */
        result->frameCounts[i] = frameCount;
        for(j = 0; j < frameCount; j++) {
            result->frames[i][j] = frames[j];
        }
    }
    
    result->totalFaults = pageFaults;
    result->hitRatio = ((float)(length - pageFaults) / length) * 100.0;
}

/*
==============================================================================
  END OF PROGRAM
==============================================================================
*/