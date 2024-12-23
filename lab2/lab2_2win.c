#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void printError(const char *msg) {
    DWORD err = GetLastError();
    fprintf(stderr, "%s. Код ошибки: %lu\n", msg, err);
}

int main() {
    HANDLE hFile1, hFile2, hFile3;
    char buffer[8]; // Буфер для чтения 7 символов + 1 для '\0'
    DWORD bytesRead;

    // Открываем файл для чтения
    hFile1 = CreateFile("output.txt", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile1 == INVALID_HANDLE_VALUE) {
        printError("Ошибка открытия файла");
        return 1;
    }

    // Дублируем хэндл
    if (!DuplicateHandle(GetCurrentProcess(), hFile1, GetCurrentProcess(), &hFile2, 0, FALSE, DUPLICATE_SAME_ACCESS)) {
        printError("Ошибка дублирования хэндла");
        CloseHandle(hFile1);
        return 1;
    }

    // Открываем файл снова для получения третьего хэндла
    hFile3 = CreateFile("output.txt", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile3 == INVALID_HANDLE_VALUE) {
        printError("Ошибка повторного открытия файла");
        CloseHandle(hFile1);
        CloseHandle(hFile2);
        return 1;
    }

    // Позиционируем чтение на 10-й позиции
    if (SetFilePointer(hFile1, 10, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER) {
        printError("Ошибка позиции чтения файла");
        CloseHandle(hFile1);
        CloseHandle(hFile2);
        CloseHandle(hFile3);
        return 1;
    }

    // Выводим значения хэндлов
    printf("Хэндлы:\nhFile1: %p\nhFile2: %p\nhFile3: %p\n", hFile1, hFile2, hFile3);

    // Чтение и вывод данных из файла
    for (int i = 0; i < 3; i++) {
        HANDLE currentHandle = (i == 0) ? hFile1 : (i == 1) ? hFile2 : hFile3;
        if (ReadFile(currentHandle, buffer, 7, &bytesRead, NULL)) {
            buffer[bytesRead] = '\0'; // Завершение строки
            printf("Чтение из hFile%d: %s\n", i + 1, buffer);
        } else {
            printError("Ошибка чтения файла");
        }
    }

    // Закрываем хэндлы
    CloseHandle(hFile1);
    CloseHandle(hFile2);
    CloseHandle(hFile3);

    return 0;
}