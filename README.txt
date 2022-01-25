# File handling assignment for CS F212: Database Systems

### SYSTEM REQUIREMENTS ###

- Requires gcc and GNU make to be installed on the system 
- The operating system must be *nix-type (important for the file and directory paths to work correctly)

### INSTRUCTIONS FOR COMPILATION ###

- In the parent directory, run `make` from the terminal. This will generate two folders, an `obj` folder that will contain the compiled object files from the source files and a `bin` folder that contains the runnable executable.
- To run the executable, `cd` into the `bin` folder and type `./main.exe` to run the program.

### OTHER INFORMATION ###

- The folder `grades` has all the CSV files with the information regarding the courses taken in the various semesters. This folder is scanned by the program and its files are indexed. Thus, any files in this folder must be of type "semX.csv", where X is a number that indicates the semester number. Any deviations from this format will break the program.
- This program uses "Table Formatter v0.1" (https://www.fourthwoods.com/utils/tableformatter/), a small utility whose code is embedded in the source code of this program. This is used for pretty printing tables.

### AUTHOR ###
Abhirath Anand : f20200141@pilani.bits-pilani.ac.in
BITS ID : 2020A7PS0141P
