// TESTING MODE
#define TEST_ENABLED true

// BRIGHTNESS
#define BRIGHTNESS 255

// GUI MODES
#define DARK 1
#define LIGHT 2

// SET GUI MODE
#define GUI_MODE DARK

// ADDITIONAL COLORS
#if GUI_MODE == LIGHT
    #define GUI_ACCENT     0x0EDB // #08DADB / RGB(1, 54, 27) // VDF GREEN
    #define GUI_BACKGROUND 0xFFFF // #FFFFFF / RGB(255, 255, 255)
    #define GUI_GHOST 0xe71c
#else
    #define GUI_ACCENT     0xC2A0 // #C55500 / RGB(24, 21, 0) // AMBER
    #define GUI_BACKGROUND 0x0000 // #000000 / RGB(0, 0, 0)
    #define GUI_GHOST      0x2124 // #212421 / RGB(4, 9, 4)
#endif

