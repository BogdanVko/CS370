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
