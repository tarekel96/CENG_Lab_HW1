# CENG_Lab_HW1

### NOTE: Collaboration project between Tavid Terzian and Tarek El-Hajjaoui.

## Description of Program:
- A C Program that creates 100 RECORD struct instances and writes them to a file, "records.dat". The program takes 2 console arguments (otherwise prompted) from the user. The first argument is record number that want to update and second argument is the record number value you want to update with. After executing, the program prints out the strings of the 100 RECORD struct instances so the user can see that the records.dat file was updated accordingly.
- The program has error checking conditions that utilize errno to give the programmers more information in case they run into any errors with opening or reading/writing to a file.

## Instructions to run the program:
- Compile with gcc: gcc recfile.c
- Run the prgoram with the command containing 2 args: ./a.out arg1 arg2

## Source Files:
- recfile.c
- records.dat
- README.md
- .gitignore
## Sources referred to:
- C Error Handling: https://www.tutorialspoint.com/cprogramming/c_error_handling.htm
- C read method: https://man7.org/linux/man-pages/man2/read.2.html
- C open method: https://man7.org/linux/man-pages/man2/open.2.html
- C write method: https://www.man7.org/linux/man-pages/man2/write.2.html
- C fseek method: http://www.cplusplus.com/reference/cstdio/fseek/
- C fpsrintf method: http://www.cplusplus.com/reference/cstdio/sprintf/
- C Input/Output: https://www.geeksforgeeks.org/input-output-system-calls-c-create-open-close-read-write/
