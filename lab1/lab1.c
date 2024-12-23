#include <windows.h>
#include <stdio.h>

int main() {
    HANDLE stdInput = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE stdOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    printf("Хэндл стандартного ввода: %p\n", stdInput);
    printf("Хэндл стандартного вывода: %p\n", stdOutput);

    char buffer[256];
    DWORD bytesRead, bytesWritten;

    const char* prompt = "Введите текст: ";
    WriteFile(stdOutput, prompt, strlen(prompt), &bytesWritten, NULL);

    ReadFile(stdInput, buffer, sizeof(buffer) - 1, &bytesRead, NULL);
    buffer[bytesRead] = '\0';

    const char* outputMessage = "Вы ввели: ";
    WriteFile(stdOutput, outputMessage, strlen(outputMessage), &bytesWritten, NULL);
    WriteFile(stdOutput, buffer, bytesRead, &bytesWritten, NULL);

    return 0;
}