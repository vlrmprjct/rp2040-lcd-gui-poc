#include "TFT_eSPI.h"
#include "TFTExtended.h"

#define LED 7       // 7 DIGIT LED SIM FONT TYPE IDENTIFIER
#define GHOST "888" // GHOST LED TEXT

TFT_eSPI tft = TFT_eSPI();
TFTExtended sprite = TFTExtended(&tft);

int number = 0;

// TEST SETTINGS
const bool testEnabled = true;

// VIEWPORT CALCULATIONS
const int viewportWidth  = tft.getViewportWidth();
const int viewportHeight = tft.getViewportHeight();
const int LEDWidth       = tft.textWidth(GHOST, LED);
const int LEDHeight      = tft.fontHeight(LED);

// SCALE SETTINGS
const int startAngle = 50;
const int endAngle   = 270;
const int maxScale   = 120;

// DYNAMIC HORIZONTAL AND VERTICAL POSITION
int vPos;
int hPos;

// TIME SETTINGS
unsigned long last = 0UL;

bool maxScaleReached = false;

void setup(void) {

    // INIT TFT
    tft.init();
    tft.setRotation(0);
    tft.setOrigin(0, 0);
    tft.fillScreen(TFT_BLACK);

    // CALC 7 SEG VERTICAL AND HORIZONTAL POSITION
    vPos = calcVerticalCenter(viewportHeight, LEDHeight);
    hPos = calcHorizontalCenter(viewportWidth, LEDWidth);

    // INIT SPRITE
    sprite.setColorDepth(16);
    sprite.createSprite(viewportWidth, viewportHeight);
    sprite.fillSprite(TFT_BLACK);

    // DRAW GHOST SCREEN
    drawGhostScreen(sprite);

    // INIT SCALE ANIMATION
    for (int angle = startAngle; angle <= endAngle; angle += 10) {
        sprite.drawSmoothArc(viewportWidth / 2, viewportHeight / 2, 116, 110, startAngle, angle + 1, TFT_AMBER, TFT_BLACK, true);
        sprite.pushSprite(0, 0);
        delay(1);
    }

    delay(1000);
}

void loop() {

    if (millis() - last > 10) {
        // number = random(55, 58);

        // CLEAR SPRITE
        sprite.fillSprite(TFT_BLACK);

        // DRAW GHOST SCREEN AGAIN
        drawGhostScreen(sprite);

        // DEFINE TEXT COLOR
        sprite.setTextColor(TFT_AMBER);

        // CALC ANGLE BASED ON MAX-SCALE
        int angle
            = startAngle + (number * (endAngle - startAngle) / maxScale);

        // DON'T DRAW ARC IF NUMBER IS 0
        if (angle != startAngle) {
            sprite.drawSmoothArc(viewportWidth / 2, viewportHeight / 2, 116, 110, startAngle, angle, TFT_AMBER, TFT_BLACK, true);
        }

        // DRAW 3 x 7 SEGMENT NUMBER
        int numberTextWidth = tft.textWidth(String(number), LED);
        int horizontalPos = calcHorizontalOffset(viewportWidth, numberTextWidth, LEDWidth);
        sprite.drawString(String(number), horizontalPos, vPos, LED);

        // DRAW SCALE
        sprite.drawScale(startAngle, endAngle, 104, 100, TFT_AMBER, TFT_BLACK, maxScale);
        sprite.drawScale(angle, angle, 90, 60, TFT_RED, TFT_BLACK, maxScale, 1);
        sprite.drawDotMatrix("KMH", 105, 155, TFT_AMBER, TFT_BLACK, TFT_GHOST, 1);
        sprite.drawDotMatrix("50", 60, 50, TFT_AMBER, TFT_BLACK, TFT_GHOST, 1);

        // PUSH SPRITE
        sprite.pushSprite(0, 0);

        // RUN DISPLAY TEST
        displayTest(testEnabled);

        last = millis();
    }
}
