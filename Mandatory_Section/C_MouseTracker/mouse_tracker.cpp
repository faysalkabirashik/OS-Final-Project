#include <windows.h>
#include <stdio.h>
#include <conio.h>

int main() {
    SetConsoleTitleA("Mouse Position Tracker");

    POINT cursorPos;
    int prevX = -1, prevY = -1;  // Track previous position to avoid duplicate prints

    printf("Tracking mouse position. Press Ctrl+C to exit.\n");
    printf("----------------------------------------\n");

    while (true) {
        if (GetCursorPos(&cursorPos)) {
            if (cursorPos.x != prevX || cursorPos.y != prevY) {
                printf("X: %ld, Y: %ld\n", cursorPos.x, cursorPos.y);
                prevX = cursorPos.x;
                prevY = cursorPos.y;
            }
        }

        Sleep(50);
    }

    return 0;
}