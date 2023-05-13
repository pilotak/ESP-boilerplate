void buttonLoop() {
    button.read();

    if (button.pressedFor(LONG_PRESS)) {
        // TODO
    }
}

void buttonSetup() {
    button.begin();
}
