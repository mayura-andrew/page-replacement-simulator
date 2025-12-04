# Quick Reference Guide - Page Replacement Simulator

## Quick Start

### Compile and Run (Modular Version)
```bash
# In Turbo C IDE:
# 1. Open project
# 2. Add: main.c, graphics.c, algorithm.c
# 3. Press F9 (Make)
# 4. Press Ctrl+F9 (Run)
```

### Compile and Run (Standalone Version)
```bash
# In Turbo C IDE:
# 1. Open test.c
# 2. Press Alt+F9 (Compile)
# 3. Press Ctrl+F9 (Run)
```

## Menu Options

| Key | Action          | Description                           |
|-----|-----------------|---------------------------------------|
| 1   | FIFO Algorithm  | Run First-In-First-Out algorithm      |
| 2   | LRU Algorithm   | Run Least Recently Used algorithm     |
| 3   | Compare Both    | Run both algorithms on same input     |
| 4   | Exit            | Close the program                     |
| ESC | Exit            | Alternative exit key                  |

## Sample Test Cases

### Test Case 1: Basic FIFO vs LRU
```
Pages: 7 0 1 2 0 3 0 4 2 3
Frames: 3
Expected FIFO Faults: 6
Expected LRU Faults: 6
```

### Test Case 2: Belady's Anomaly Example
```
Pages: 1 2 3 4 1 2 5 1 2 3 4 5
Frames: 3 vs 4
FIFO with 3 frames may have fewer faults than with 4 frames
```

### Test Case 3: Sequential Access
```
Pages: 1 2 3 4 5 1 2 3 4 5
Frames: 3
Tests sequential page access pattern
```

### Test Case 4: Repeated Reference
```
Pages: 1 2 1 2 1 2 1 2
Frames: 2
Expected: Very low fault rate (optimal for 2 frames)
```

## File Structure

```
Header Files (.h):
├── config.h     → Constants & configuration
├── types.h      → Data structures
├── graphics.h   → UI function declarations
└── algorithm.h  → Algorithm function declarations

Implementation Files (.c):
├── main.c       → Program entry point
├── graphics.c   → UI implementation
├── algorithm.c  → FIFO & LRU implementations
└── test.c       → Standalone version

Documentation:
├── README.md    → Full documentation
└── QUICKREF.md  → This file
```

## Common Issues & Solutions

| Problem                      | Solution                                |
|------------------------------|-----------------------------------------|
| Graphics init failed         | Check BGI path in config.h              |
| Can't compile modular        | Ensure all .c files are in project      |
| Input not accepted           | Use console window, not graphics window |
| Wrong output values          | Verify input is space-separated         |

## Algorithm Comparison

| Aspect          | FIFO                  | LRU                      |
|-----------------|-----------------------|--------------------------|
| Complexity      | Simple (Queue)        | Moderate (Tracking time) |
| Performance     | May suffer anomaly    | Generally better         |
| Implementation  | Queue-based           | Timestamp-based          |
| Best Use        | Simple scenarios      | Real-world systems       |

## Keyboard Shortcuts (in Turbo C IDE)

| Key       | Action              |
|-----------|---------------------|
| F9        | Make/Compile all    |
| Alt+F9    | Compile current     |
| Ctrl+F9   | Run program         |
| F5        | Zoom window         |
| Alt+F5    | View user screen    |
| Alt+X     | Exit Turbo C        |

## Configuration Options (config.h)

```c
MAX_PAGES          // Max page references (default: 10)
MIN_FRAMES         // Min frames (default: 3)
MAX_FRAMES         // Max frames (default: 5)
BGI_PATH           // Graphics driver path
BUTTON_WIDTH       // UI button width
BUTTON_HEIGHT      // UI button height
```

## Color Codes

```c
HEADER_COLOR      = LIGHTBLUE
BUTTON_COLOR      = LIGHTGREEN
FRAME_COLOR       = YELLOW
FAULT_COLOR       = RED (Page Fault)
HIT_COLOR         = GREEN (Page Hit)
SUMMARY_BG_COLOR  = BLUE
```

## Tips for Best Results

1. **Input Range**: Keep page numbers reasonable (0-20)
2. **Frame Count**: Use 3-5 frames for best visualization
3. **Page Count**: Use 8-10 pages (screen limit is 8 visible steps)
4. **Test Patterns**: Try sequential, random, and repeated patterns
5. **Comparison**: Use Compare mode to see both algorithms side-by-side

## Expected Behavior

### FIFO Algorithm:
- Replaces the oldest page in memory
- May experience Belady's Anomaly
- Simpler but not always optimal

### LRU Algorithm:
- Replaces least recently used page
- Generally better performance
- More realistic to actual OS behavior

## Student Info

**Student ID**: 722516877  
**Course**: EEX5564 - Computer Architecture & OS  
**Group**: B  
**Project**: Page Replacement Algorithm Simulator
