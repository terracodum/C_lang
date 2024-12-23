#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd1 = open("output.txt", O_RDONLY);
    if (fd1 < 0) {
        perror("Ошибка открытия файла");
        return 1;
    }

    int fd2 = dup(fd1);
    if (fd2 < 0) {
        perror("Ошибка дублирования хэндла");
        close(fd1);
        return 1;
    }

    int fd3 = open("output.txt", O_RDONLY);
    if (fd3 < 0) {
        perror("Ошибка повторного открытия файла");
        close(fd1);
        close(fd2);
        return 1;
    }

    lseek(fd1, 10, SEEK_SET);

    printf("Хэндлы:\nfd1: %d\nfd2: %d\nfd3: %d\n", fd1, fd2, fd3);

    char buffer[8];

    for (int i = 0; i < 3; i++) {
        int current_fd = (i == 0) ? fd1 : (i == 1) ? fd2 : fd3;
        ssize_t bytesRead = read(current_fd, buffer, 7);
        buffer[bytesRead] = '\0';
        printf("Чтение из fd%d: %s\n", i + 1, buffer);
    }


    close(fd1);
    close(fd2);
    close(fd3);

    return 0;
}
