#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

char *buffer = NULL;
char *where_file = NULL;
int running_flag =1;

void load_file() 
{
    if (!where_file) return;

    FILE *file = fopen(where_file, "r");
    if (!file)
        {
            print("Unable to open file:%s\n.",where_file);
            return;
        }

    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    rewind(file);

    free(buffer);
    buffer = malloc(size + 1);
    if (buffer)
        {
            fread (buffer, 1, size, file);
            buffer[size] = "\0";
            printf("File was loaded.\n");
        } else {
            printf("Error in allocation.\n");
        }

        fclose(file);

}

void clear_buffer()
{
    free(buffer);
    buffer = NULL;
    printf ("Buffer has cleared.\n");
}

void handler1(int signo)
{
    printf("\nSIGUSR1 Caught signal1 %d (%s)\n"); 
	(void)signo;
	load_file();
}

void handler2(int signo) 
{
    printf("\nSIGUSR2 Caught signal2 %d (%s)\n");
    (void)signo;
    clear_buffer();
}

void handler3(int signo) {
    (void)signo;
    printf("\nSIGINT received (CTRL+C). Do you want to exit? (y/n): ");
    char response = getchar();
    if (response == 'y' || response == 'Y') {
        running_flag = 0;
    } else {
        printf("Continuing program...\n");
    }
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <file_path>\n", argv[0]);
        return -1;
    }

    where_file = argv[1];

    signal(SIGUSR1, handler1); 
    signal(SIGUSR2, handler2); 
    signal(SIGINT, handler3); 

    load_file();

    while (running_flag) {
        if (buffer) {
            printf("Buffer content:\n%s\n", buffer);
        } else {
            printf("Buffer is empty.\n");
        }
        sleep(1);
    }

    clear_buffer();
    printf("Program terminated.\n");
    return 0;
}