#include <sys/mman.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#define DIGIT_COUNT 10

typedef struct context {
    unsigned long count[DIGIT_COUNT];
    pthread_mutex_t mutex;
} context_t;

char* map_file(const char* filename, size_t* length) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Błąd otwarcia pliku");
        exit(EXIT_FAILURE);
    }

    *length = lseek(fd, 0, SEEK_END);
    char* data = mmap(NULL, *length, PROT_READ, MAP_PRIVATE, fd, 0);
    if (data == MAP_FAILED) {
        perror("Błąd mmap pliku");
        close(fd);
        exit(EXIT_FAILURE);
    }
    close(fd);
    return data;
}

void count_digits(context_t* ctx, const char* data, size_t start, size_t end) {
    unsigned long local_count[DIGIT_COUNT] = {0};

    for (size_t i = start; i < end; i++) {
        if (data[i] >= '0' && data[i] <= '9') {
            local_count[data[i] - '0']++;
        }
    }

    pthread_mutex_lock(&ctx->mutex);
    for (int i = 0; i < DIGIT_COUNT; i++) {
        ctx->count[i] += local_count[i];
    }
    pthread_mutex_unlock(&ctx->mutex);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Użycie: %s <ścieżka_do_pliku> <liczba_procesów>\n", argv[0]);
        return 1;
    }

    const char* FILE_PATH = argv[1];
    int process_count = atoi(argv[2]);

    if (process_count < 1) {
        fprintf(stderr, "Liczba procesów musi być >= 1\n");
        return 1;
    }

    size_t file_length;
    char* file_data = map_file(FILE_PATH, &file_length);

    context_t* ctx = mmap(NULL, sizeof(context_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (ctx == MAP_FAILED) {
        perror("Błąd mmap");
        return -1;
    }

    memset(ctx->count, 0, sizeof(ctx->count));
    pthread_mutexattr_t mutexattr;
    pthread_mutexattr_init(&mutexattr);
    pthread_mutexattr_setpshared(&mutexattr, PTHREAD_PROCESS_SHARED);
    pthread_mutex_init(&ctx->mutex, &mutexattr);

    size_t chunk_size = (file_length + process_count - 1) / process_count;
    pid_t pids[process_count];

    for (int i = 0; i < process_count; i++) {
        size_t start = i * chunk_size;
        size_t end = (i + 1) * chunk_size;
        if (end > file_length) {
            end = file_length;
        }

        if ((pids[i] = fork()) == 0) {
            count_digits(ctx, file_data, start, end);
            exit(0);
        } else if (pids[i] == -1) {
            perror("Błąd fork");
            return -1;
        }
    }

    for (int i = 0; i < process_count; i++) {
        waitpid(pids[i], NULL, 0);
    }

    printf("Stan liczników cyfr:\n");
    for (int i = 0; i < DIGIT_COUNT; i++) {
        printf("Cyfra %d: %lu\n", i, ctx->count[i]);
    }

    pthread_mutex_destroy(&ctx->mutex);
    pthread_mutexattr_destroy(&mutexattr);
    munmap(ctx, sizeof(context_t));
    munmap(file_data, file_length);

    return 0;
}
