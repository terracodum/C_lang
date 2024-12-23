#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main() {
    HANDLE hFile;
    char buffer[256];
    DWORD bytesWritten;

    // Открываем файл для записи (создаем, если не существует)
    hFile = CreateFile("output.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        perror("Ошибка открытия файла");
        return 1;
    }

    // Чтение данных из стандартного ввода
    printf("Введите текст: ");
    fflush(stdout);
    fgets(buffer, sizeof(buffer), stdin);

    // Запись в файл
    WriteFile(hFile, buffer, strlen(buffer), &bytesWritten, NULL);
    CloseHandle(hFile); // Закрываем файл

    return 0;
}