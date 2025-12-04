#ifndef CONFIG_H
#define CONFIG_H

/*
==============================================================================
  CONFIGURATION HEADER
  Contains all constants and configuration parameters
==============================================================================
*/

/* Graphics Driver Path */
#define BGI_PATH "C:\\TURBOC3\\BGI"

/* Display Configuration */
#define BUTTON_WIDTH 150
#define BUTTON_HEIGHT 40

/* Algorithm Constants */
#define MAX_PAGES 10
#define MIN_FRAMES 3
#define MAX_FRAMES 5
#define MAX_REFERENCE_STRING 50
#define MAX_ALGORITHM_NAME 20

/* Menu Options */
#define MENU_FIFO 1
#define MENU_LRU 2
#define MENU_COMPARE 3
#define MENU_EXIT 4

/* Color Definitions */
#define HEADER_COLOR LIGHTBLUE
#define BUTTON_COLOR LIGHTGREEN
#define FRAME_COLOR YELLOW
#define FAULT_COLOR RED
#define HIT_COLOR GREEN
#define SUMMARY_BG_COLOR BLUE

#endif /* CONFIG_H */

