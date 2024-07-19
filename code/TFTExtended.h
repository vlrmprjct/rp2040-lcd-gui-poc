#ifndef TFT_EXTENDED_H
#define TFT_EXTENDED_H

#include "TFT_eSPI.h"
#include "DotMatrix.h"

// ADDITIONAL COLORS
#define TFT_GHOST 0x2124 // #212421 / RGB(4, 9, 4)
#define TFT_VDF   0x0EDB // #08DADB / RGB(1, 54, 27)
#define TFT_AMBER 0xFBE0 // #FF7D00 / RGB(31, 31, 0)

class TFTExtended : public TFT_eSprite {

public:

    using TFT_eSprite::TFT_eSprite;

    /**
     * Draws a scale on the given sprite.
     *
     * @param startAngle The starting angle of the scale.
     * @param endAngle The ending angle of the scale.
     * @param outerRadius The outer radius of the scale.
     * @param innerRadius The inner radius of the scale.
     * @param foregroundColor The color of the scale markers.
     * @param backgroundColor The background color of the scale.
     * @param steps The number of steps between each marker.
     * @param maxScale The maximum speed value for the scale.
     */
    void drawScale(int startAngle, int endAngle, int outerRadius, int innerRadius, uint16_t foregroundColor, uint16_t backgroundColor, int steps, int maxScale) {
        for (int i = 0; i <= maxScale; i += steps) {
            int markerAngle = startAngle + (i * (endAngle - startAngle) / maxScale);
            int xStart, yStart, xEnd, yEnd;

            calcLinePositions(markerAngle, outerRadius, innerRadius, xStart, yStart, xEnd, yEnd);
            drawWideLine(xStart, yStart, xEnd, yEnd, 3, foregroundColor, backgroundColor);
        }
    }

    /**
     * Draws a dot matrix representation of the given text on the sprite.
     *
     * @param text The text to be displayed.
     * @param x The x-coordinate of the top-left corner of the dot matrix.
     * @param y The y-coordinate of the top-left corner of the dot matrix.
     * @param color The color of the dots representing the text.
     * @param bgColor The background color of the dot matrix.
     * @param disableColor The color of the dots representing disabled parts of the text.
     * @param dotSize The size of each dot in the dot matrix.
     */
    void drawDotMatrix(const char* text, int x, int y, uint16_t color, uint16_t bgColor, uint16_t disableColor, int dotSize) {
        int len = strlen(text);
        int matrixWidth = 5;
        int matrixHeight = 7;

        for (int i = 0; i < len; i++) {
            char c = text[i];
            int index;

            if (c >= '0' && c <= '9') {
                index = c - '0';
            } else if (c >= 'A' && c <= 'Z') {
                index = c - 'A' + 10;
            } else {
                continue;
            }

            for (int row = 0; row < matrixHeight; row++) {
                for (int col = 0; col < matrixWidth; col++) {
                    int xOffset = col * (dotSize + 1);
                    int yOffset = row * (dotSize + 1);
                    if (dotMatrix[index][row] & (1 << (matrixWidth - 1 - col))) {
                        fillSmoothRoundRect(x + xOffset, y + yOffset, dotSize, dotSize, 0, color, color);
                    } else {
                        fillSmoothRoundRect(x + xOffset, y + yOffset, dotSize, dotSize, 0, disableColor, bgColor);
                    }
                }
            }

            x += (matrixWidth * (dotSize + 1)) + 2;
        }
    }

private:

    /**
     * Calculates the start and end positions of a line based on the given angle and radii.
     *
     * @param angle The angle of the line.
     * @param outerRadius The outer radius of the line.
     * @param innerRadius The inner radius of the line.
     * @param xStart The x-coordinate of the starting point of the line.
     * @param yStart The y-coordinate of the starting point of the line.
     * @param xEnd The x-coordinate of the ending point of the line.
     * @param yEnd The y-coordinate of the ending point of the line.
     */
    void calcLinePositions(int angle, int outerRadius, int innerRadius, int& xStart, int& yStart, int& xEnd, int& yEnd) {
        float rad = degToRad(angle + 90);
        int cx = getViewportWidth() / 2;
        int cy = getViewportWidth() / 2;

        xStart = cx + cos(rad) * innerRadius;
        yStart = cy + sin(rad) * innerRadius;
        xEnd = cx + cos(rad) * outerRadius;
        yEnd = cy + sin(rad) * outerRadius;
    }

    /**
     * Converts degrees to radians.
     *
     * @param deg The angle in degrees.
     * @return The angle in radians.
     */
    float degToRad(int deg) {
        return deg * PI / 180.0;
    }
};

#endif
