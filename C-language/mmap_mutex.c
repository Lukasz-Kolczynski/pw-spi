#include <sys/mman.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

#define TAB_LENGTH 10

typedef struct shared {
    char tab[TAB_LENGTH];    
    pthread_mutex_t mutex;
} shared_t;

char* read_file(const char* filename, size_t* length) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Błąd otwarcia pliku");
        exit(EXIT_FAILURE);
    }

    *length = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);

    char* buffer = malloc(*length + 1);
    if (!buffer) {
        perror("Błąd alokacji pamięci");
        close(fd);
        exit(EXIT_FAILURE);
    }

    if (read(fd, buffer, *length) != *length) {
        perror("Błąd odczytu pliku");
        close(fd);
        free(buffer);
        exit(EXIT_FAILURE);
    }
    buffer[*length] = '\0';
    close(fd);
    return buffer;
}

void child(shared_t* shr, char* data, size_t length) {
    size_t index = 0;
    while (1) {
        pthread_mutex_lock(&shr->mutex);
        for (int i = 0; i < TAB_LENGTH; i++) {
            shr->tab[i] = data[index++ % length];
        }
        pthread_mutex_unlock(&shr->mutex);
        usleep(100000);
    }
}

void parent(shared_t* shr) {
    while (1) {
        pthread_mutex_lock(&shr->mutex);
        for (int i = 0; i < TAB_LENGTH; i++) {
            printf("%c", shr->tab[i]);
        }
        pthread_mutex_unlock(&shr->mutex);
        printf("\n");
        usleep(500000);
    }
}

void cleanup(shared_t* shr, char* file_data) {
    pthread_mutex_destroy(&shr->mutex);
    munmap(shr, sizeof(shared_t));
    free(file_data);
}

void handle_signal(int sig) {
    printf("Zamykanie programu...\n");
    exit(0);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Użycie: %s <ścieżka do pliku> <liczba procesów>\n", argv[0]);
        return 1;
    }

    const char* FILE_PATH = argv[1];
    int process_count = atoi(argv[2]);

    signal(SIGINT, handle_signal);

    size_t file_length;
    char* file_data = read_file(FILE_PATH, &file_length);

    int prot = PROT_READ | PROT_WRITE;
    int vis = MAP_SHARED | MAP_ANONYMOUS;
    shared_t *shr = (shared_t*)mmap(NULL, sizeof(shared_t), prot, vis, -1, 0);
    if (shr == MAP_FAILED) {
        perror("Błąd mmap");
        return -1;
    }

    pthread_mutexattr_t mutexattr;
    if (pthread_mutexattr_init(&mutexattr) != 0) return -2;
    if (pthread_mutexattr_setpshared(&mutexattr, PTHREAD_PROCESS_SHARED) != 0) return -3;
    if (pthread_mutex_init(&shr->mutex, &mutexattr) != 0) return -4;

    for (int i = 0; i < process_count; i++) {
        pid_t pid = fork();
        if (pid == -1) {
            perror("Błąd fork");
            return -5;
        } else if (pid == 0) {
            child(shr, file_data, file_length);
            exit(0);
        }
    }

    parent(shr);

    cleanup(shr, file_data);
    return 0;
}
