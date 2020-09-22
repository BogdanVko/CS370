#include <stdio.h>
#include "MemoryManager.h"
#include <stdlib.h>
#include <sys/resource.h>

int main(int argc, char **argv) 
{
    struct rlimit rl;
    getrlimit (RLIMIT_AS, &rl);
    // Change the limit to 10MB
    rl.rlim_cur = 1024 * 1024 * 10;
    setrlimit (RLIMIT_AS, &rl);
    
    if (argc != 2)
    {
        printf("Incorrect number of arguments.\n");
        return -1;
    }
    else 
    {
        int seed = atoi(argv[1]);
        // set the seed
        srand(seed);
        // invoke the function in MemoryManager
        printf("[Driver] With seed: %d\n", seed);
        int running_count = get_running_count();
        printf("[Driver] Running Count: %d\n\n", running_count);
        return 0;
    }
}
// // # ******************************************************
// # This is the Makefile for Homework 2.
// # Please replace the .zip file name with the appropriate
// # file name per your assignment instructions.
// # ******************************************************

// # List of files
// C_SOURCES = Coordinator.c Checker.c
// C_OBJECTS = Coordinator.o Checker.o
// C_HEADERS = Checker.h

// EXE1 = coordinator
// EXE2 = checker

// # Compiler and loader commands and flags
// GCC = gcc
// GCC_FLAGS = -std=c11 -g -Wall -c -I.
// LD_FLAGS  = -std=c11 -g -Wall -I.

// # Compiles .c files to .o files
// .c.o:
// 	$(GCC) $(GCC_FLAGS) $<

// # Target is the executables: coordinator, checker
// all: coordinator checker

// # Builds coordinator executable
// coordinator: Coordinator.o
// 	$(GCC) $(LD_FLAGS) Coordinator.o -o $(EXE1)

// # Builds checker executable
// checker: Checker.o
// 	$(GCC) $(LD_FLAGS) Checker.o -o $(EXE2)

// # Recompile C objects if header files change
// $(C_OBJECTS): ${C_HEADERS}

// # Cleans up object files and executables
// clean:
// 	rm -f *.o *~ $(EXE1) $(EXE2)

// # Packages directory files into .zip file
// package:
// 	zip -r Bogdan-VASILCHENKO-HW2.zip Coordinator.c Checker.c Checker.h Makefile README.txt
