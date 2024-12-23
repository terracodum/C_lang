#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    char buffer[256];
    ssize_t bytesRead;

    // Проверка, если ввод идет из терминала
    if (isatty(STDIN_FILENO)) {
        printf("Введите текст: ");
        fflush(stdout); // Принудительный вывод
    }

    // Чтение данных из стандартного ввода
    bytesRead = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
    if (bytesRead < 0) {
        perror("Ошибка чтения");
        return 1;
    }
    buffer[bytesRead] = '\0'; // Завершение строки

    // Проверка, если вывод идет в терминал
    if (isatty(STDOUT_FILENO)) {
        printf("Вы ввели: %s", buffer);
    } else {
       // Измените на printf для тестирования
        printf("Вы ввели: %s", buffer);
    }

    return 0;
}