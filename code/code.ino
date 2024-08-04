#include "config.h"
#include "TFTExtended.h"

#define LED 7       // 7 DIGIT LED SIM FONT TYPE IDENTIFIER
#define GHOST "888" // GHOST LED TEXT

TFT_eSPI tft = TFT_eSPI();
TFTExtended sprite = TFTExtended(&tft);

int number = 0;

// PINS
const int backLight = 25; // GPIO25

// VIEWPORT CALCULATIONS
const int viewportWidth   = tft.getViewportWidth();
const int viewportHeight  = tft.getViewportHeight();
const int viewportCenterX = tft.getViewportWidth() / 2;
const int viewportCenterY = tft.getViewportHeight() / 2;
const int LEDWidth        = tft.textWidth(GHOST, LED);
const int LEDHeight       = tft.fontHeight(LED);

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

    // INIT PINS
    pinMode(backLight, OUTPUT);

    // INIT TFT
    tft.init();
    tft.setRotation(0);
    tft.setOrigin(0, 0);
    tft.fillScreen(GUI_BACKGROUND);

    // CALC 7 SEG VERTICAL AND HORIZONTAL POSITION
    vPos = calcVerticalCenter(viewportHeight, LEDHeight);
    hPos = calcHorizontalCenter(viewportWidth, LEDWidth);

    // INIT SPRITE
    sprite.setColorDepth(16);
    sprite.createSprite(viewportWidth, viewportHeight);
    sprite.fillSprite(GUI_BACKGROUND);

    // DRAW GHOST SCREEN
    drawGhostScreen(sprite);

    // SET BACKLIGHT BRIGHTNESS
    analogWrite(backLight, BRIGHTNESS);

    // INIT SCALE ANIMATION
    for (int angle = startAngle; angle <= endAngle; angle += 10) {
        sprite.drawSmoothArc(viewportCenterX, viewportCenterY, 116, 110, startAngle, angle + 1, GUI_ACCENT, GUI_BACKGROUND, true);
        sprite.pushSprite(0, 0);
        delay(1);
    }

    delay(1000);
}

void loop() {

    if (millis() - last > 10) {
        // number = random(55, 58);

        // CLEAR SPRITE
        sprite.fillSprite(GUI_BACKGROUND);

        // DRAW GHOST SCREEN AGAIN
        drawGhostScreen(sprite);

        // DEFINE TEXT COLOR
        sprite.setTextColor(GUI_ACCENT);

        // CALC ANGLE BASED ON MAX-SCALE
        int angle
            = startAngle + (number * (endAngle - startAngle) / maxScale);

        // DON'T DRAW ARC IF NUMBER IS 0
        if (angle != startAngle) {
            sprite.drawSmoothArc(viewportCenterX, viewportCenterY, 116, 110, startAngle, angle, GUI_ACCENT, GUI_BACKGROUND, true);
        }

        // DRAW 3 x 7 SEGMENT NUMBER
        int numberTextWidth = tft.textWidth(String(number), LED);
        int horizontalPos = calcHorizontalOffset(viewportWidth, numberTextWidth, LEDWidth);
        sprite.drawString(String(number), horizontalPos, vPos, LED);

        // DRAW SCALE
        sprite.drawScale(startAngle, endAngle, 104, 100, GUI_ACCENT, GUI_BACKGROUND, maxScale);
        sprite.drawScale(angle, angle, 90, 60, TFT_RED, GUI_BACKGROUND, maxScale, 1, 3);

        int width, height;
        sprite.dotMatrixDimensions("KMH", 1, width, height);
        sprite.drawDotMatrix("KMH", viewportCenterX - (width / 2), 155, GUI_ACCENT, GUI_BACKGROUND, GUI_GHOST, 1);

        sprite.drawDotMatrix("50", 60, 50, GUI_ACCENT, GUI_BACKGROUND, GUI_GHOST, 1);

        // PUSH SPRITE
        sprite.pushSprite(0, 0);

        // RUN DISPLAY TEST
        displayTest(TEST_ENABLED);

        last = millis();
    }
}
