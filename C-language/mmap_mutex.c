#include <sys/mman.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

#define TAB_LENGTH 10
#define LOCATION_FILE "/home/u335775/Pulpit/digits.txt"

typedef struct shared
{
    char tab[TAB_LENGTH];
    pthread_mutex_t mutex;
    shared_t;

};

char* read_file(const char* filename, size_t* length)
{
    int fd=open(filename, O_RDONLY);
    if (fd== -1) 
    {
        perror("Błąd podczas otwierania pliku");
        _exit(EXIT_FAILURE);
    }

*length = lseek(fd, 0, SEEK_END);
lseek(fd, 0, SEEK_SET);






int main() {
    int prot = PROT_READ | PROT_WRITE;
    int vis = MAP_SHARED | MAP_ANONYMOUS;
    shared_t *shr = (shared_t*)mmap(NULL, sizeof(shared_t), prot, vis, -1, 0);
    if (shr == NULL)
        return -1;

    pthread_mutexattr_t mutexattr;
    if (pthread_mutexattr_init(&mutexattr) != 0)
        return -2;
    if (pthread_mutexattr_setpshared(&mutexattr, PTHREAD_PROCESS_SHARED) != 0)
        return -3;
    if (pthread_mutex_init(&shr->mutex, &mutexattr) != 0)
        return -4;

    pid_t pid = fork();
    switch (pid) {
        case -1: 
            return -5;
        case 0: 
            child(shr);
            break;
        default: 
            parent(shr);
            break;
    }

    pthread_mutex_destroy(&shr->mutex);
    munmap(shr, sizeof(shared_t));
    return 0;
}