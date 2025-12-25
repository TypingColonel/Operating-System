#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

/**
 * There are some apis that work only in linux based systems sooo yk the drill
 */

int main() {
    const int SIZE = 4096;
    const char *name = "Shared Memory";
    const char *first_message = "Hiiii";
    const char *second_message = "Sanjay";
    int shm_file_discriptor;
    char *ptr;
    shm_file_discriptor = shm_open(name, O_CREAT | O_RDWR, 0666);

    if (shm_file_discriptor == -1) return 1;

    ftruncate(shm_file_discriptor, SIZE);
    ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_file_discriptor, 0);

    if (ptr == MAP_FAILED) return 1;

    sprintf(ptr, "%s", first_message);
    ptr += strlen(first_message);
    
    sprintf(ptr, "%s", second_message);
    return 0;
}  