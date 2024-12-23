#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    char buffer[256];
    ssize_t bytesRead;

    // Открываем файл для записи (создаем, если не существует)
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("Ошибка открытия файла");
        return 1;
    }

    // Чтение данных из стандартного ввода
    printf("Введите текст: ");
    fflush(stdout);
    bytesRead = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
    if (bytesRead < 0) {
        perror("Ошибка чтения");
        close(fd);
        return 1;
    }
    buffer[bytesRead] = '\0'; // Завершение строки

    // Запись в файл
    write(fd, buffer, bytesRead);
    close(fd); // Закрываем файл

    return 0;
}