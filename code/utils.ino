

/**
 * Converts an integer to a character array.
 *
 * @param number The integer to be converted.
 * @return The character array representation of the integer.
 */
char* intToChar(int number) {
    static char buffer[12]; // Statisch, um sicherzustellen, dass der Speicherbereich erhalten bleibt
    itoa(number, buffer, 10); // Konvertiert die Zahl in eine Zeichenkette im Dezimalsystem (Basis 10)
    return buffer; // Gibt den Zeiger auf den Buffer zurück
}

/**
 * Calculates the vertical center position based on the viewport height and font height.
 *
 * @param viewportHeight The height of the viewport.
 * @param offset The height of the font.
 * @return The vertical center position.
 */
int calcVerticalCenter(int viewportHeight, int offset) {
    return (viewportHeight - offset) / 2;
}

/**
 * Calculates the horizontal center position based on the viewport width and text width.
 *
 * @param viewportWidth The width of the viewport.
 * @param offset The width of the text.
 * @return The horizontal center position.
 */
int calcHorizontalCenter(int viewportWidth, int offset) {
    return (viewportWidth - offset) / 2;
}

/**
 * Calculates the horizontal offset for centering numbers based on the viewport width, text width, and maximum text width.
 *
 * @param viewportWidth The width of the viewport.
 * @param offset The width of the text.
 * @param maxTextWidth The maximum width of the text.
 * @return The horizontal offset for centering numbers.
 */
int calcHorizontalOffset(int viewportWidth, int offset, int maxTextWidth) {
    return (viewportWidth - offset) / 2 + (maxTextWidth - offset) / 2;
}

/**
 * Draws the whole ghost screen.
 *
 * @param ghostSprite The ghost sprite.
 */
void drawGhostScreen(TFTExtended& ghostSprite) {
    int width, height;
    ghostSprite.drawSmoothArc(120, 120, 118, 108, startAngle, endAngle, GUI_GHOST, GUI_BACKGROUND, true);
    ghostSprite.setTextColor(GUI_GHOST, GUI_BACKGROUND);
    ghostSprite.drawString(GHOST, hPos, vPos, LED);
    ghostSprite.drawScale(startAngle, endAngle, 104, 100, GUI_GHOST, GUI_BACKGROUND, maxScale);
    ghostSprite.drawDotMatrix("00", 60, 50, GUI_GHOST, GUI_BACKGROUND, GUI_GHOST, 1);
    ghostSprite.dotMatrixDimensions("000", 1, width, height);
    ghostSprite.drawDotMatrix("000", viewportCenterX - (width / 2), 155, GUI_GHOST, GUI_BACKGROUND, GUI_GHOST, 1);
}

/**
 * Displays the test based on the testEnabled flag.
 *
 * @param testEnabled Flag indicating whether the test is enabled or not.
 */
void displayTest(bool testEnabled) {
    if (testEnabled) {
        if (!maxScaleReached) {
            number += 2;
            if (number >= maxScale) {
                maxScaleReached = true;
            }
        } else {
            number -= 2;
            if (number <= 0) {
                maxScaleReached = false;
            }
        }
    }
}
