# Page Replacement Simulator

A graphical page replacement algorithm simulator using Borland Graphics Interface (BGI).
Implements FIFO and LRU page replacement algorithms with step-by-step visualization.

## Student Information
- **Student ID**: 722516877
- **Course**: EEX5564 - Computer Architecture & Operating Systems
- **Group**: B

## Project Structure

```
pagerep/
├── main.c          # Main program entry point (modular version)
├── test.c          # Standalone single-file version for testing
├── config.h        # Configuration constants
├── types.h         # Type definitions and structures
├── graphics.h      # Graphics/UI function declarations
├── graphics.c      # Graphics/UI implementation
├── algorithm.h     # Algorithm function declarations
├── algorithm.c     # Algorithm implementations (FIFO & LRU)
└── README.md       # This file
```

## Features

- **FIFO Algorithm**: First-In-First-Out page replacement
- **LRU Algorithm**: Least Recently Used page replacement
- **Comparison Mode**: Run both algorithms on the same input
- **Visual Results**: Step-by-step visualization with color-coded output
- **Interactive GUI**: Menu-driven interface using BGI graphics
- **Modular Design**: Separated into logical modules for maintainability

## Compilation Instructions

### Option 1: Using Turbo C IDE (Recommended)

#### For Modular Version:
1. Open Turbo C IDE
2. File → New → Project
3. Add these files to the project:
   - `main.c`
   - `graphics.c`
   - `algorithm.c`
4. Build → Make (or press F9)
5. Run → Run (or press Ctrl+F9)

#### For Standalone Version:
1. Open Turbo C IDE
2. File → Open → `test.c`
3. Compile → Compile (or press Alt+F9)
4. Run → Run (or press Ctrl+F9)

### Option 2: Command Line Compilation

#### Modular Version:
```bash
tcc -I. main.c graphics.c algorithm.c -o pagerep.exe
```

#### Standalone Version:
```bash
tcc test.c -o test.exe
```

## Usage Instructions

1. **Start the program**: Run the compiled executable
2. **Main Menu**: You'll see four options:
   - Press `1` for FIFO Algorithm
   - Press `2` for LRU Algorithm
   - Press `3` to Compare Both
   - Press `4` or ESC to Exit

3. **Input Parameters**: When prompted in the console:
   - Enter number of page references (1-10)
   - Enter the page numbers (space-separated)
   - Enter number of frames (3-5)

4. **View Results**: The program displays:
   - Reference string
   - Step-by-step frame allocation
   - Page faults/hits at each step
   - Total page faults and hit ratio

5. **Return to Menu**: Press any key to return to the main menu

## Example Input

```
Number of page references: 10
Page numbers: 7 0 1 2 0 3 0 4 2 3
Number of frames: 3
```

## Configuration

Edit `config.h` to modify:
- `MAX_PAGES`: Maximum number of page references (default: 10)
- `MIN_FRAMES`: Minimum number of frames (default: 3)
- `MAX_FRAMES`: Maximum number of frames (default: 5)
- `BGI_PATH`: Path to BGI drivers (default: "C:\\TURBOC3\\BGI")
- Color schemes and button dimensions

## Important Notes

1. **BGI Path**: Ensure the BGI driver path in `config.h` matches your Turbo C installation
2. **DOSBox**: This program is designed for DOSBox or actual DOS environment
3. **Input Validation**: The program validates inputs and uses defaults for invalid values
4. **Screen Resolution**: Designed for standard VGA resolution (640x480)

## Algorithm Details

### FIFO (First-In-First-Out)
- Replaces the oldest page in memory
- Uses a queue to track page order
- Simple but may not be optimal

### LRU (Least Recently Used)
- Replaces the page that hasn't been used for the longest time
- Tracks last usage time for each page
- Generally performs better than FIFO

## Best Practices Implemented

1. **Separation of Concerns**: UI, algorithms, and utilities in separate files
2. **Header Guards**: All headers protected against multiple inclusion
3. **Constants**: Magic numbers replaced with named constants
4. **Type Safety**: Boolean type and clear type definitions
5. **Documentation**: Functions documented with purpose and parameters
6. **Error Handling**: Input validation and error messages
7. **Naming Conventions**: Descriptive names following C conventions

## Troubleshooting

**Problem**: Graphics initialization failed  
**Solution**: Check that BGI drivers are in the correct path (C:\\TURBOC3\\BGI)

**Problem**: Compilation errors  
**Solution**: Ensure all .c and .h files are in the same directory

**Problem**: Program doesn't respond to input  
**Solution**: Make sure to use the console window for input when prompted

## Author

Student ID: 722516877  
Group B - Page Replacement Algorithm Simulator  
Course: EEX5564 - Computer Architecture & Operating Systems

Student ID: 722516877
Course: EEX5564 - Computer Architecture & OS
