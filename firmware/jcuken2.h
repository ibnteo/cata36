#define HID_KEYBOARD_LAYER_FN 0xFF
#define HID_KEYBOARD_LAYER_FN2 0xFE
#define HID_KEYBOARD_LAYER_EN 0xFD
#define HID_KEYBOARD_LAYER_RU 0xFC
#define HID_KEYBOARD_LAYER_MOU 0xFB

// Modificators
const uint8_t Layer_Mods[12] PROGMEM = {
    HID_KEYBOARD_SC_LEFT_GUI,     // Alt+AltGr
    0,                            // Alt+Ctrl
    0,                            // Ctrl+Shift
    0,                            // Shift+Space
    HID_KEYBOARD_LAYER_FN2,       // Space+Fn
    0,                            // Fn+AltGr
    HID_KEYBOARD_SC_LEFT_ALT,     // Alt
    HID_KEYBOARD_SC_LEFT_CONTROL, // Ctrl
    HID_KEYBOARD_SC_LEFT_SHIFT,   // Shift
    HID_KEYBOARD_SC_SPACE,        // Space
    HID_KEYBOARD_LAYER_FN,        // Fn
    HID_KEYBOARD_SC_RIGHT_ALT     // AltGr
};

// QWERTY
const uint8_t Layer_Lang1[6][9] PROGMEM = {
    {
        HID_KEYBOARD_SC_TAB, // QW
        0,                   // WE
        0,                   // ER
        0,                   // RT
        HID_KEYBOARD_SC_Q,   // Q
        HID_KEYBOARD_SC_W,   // W
        HID_KEYBOARD_SC_E,   // E
        HID_KEYBOARD_SC_R,   // R
        HID_KEYBOARD_SC_T,   // T
    },
    {
        0,                 // AS
        0,                 // SD
        0,                 // DF
        0,                 // FG
        HID_KEYBOARD_SC_A, // A
        HID_KEYBOARD_SC_S, // S
        HID_KEYBOARD_SC_D, // D
        HID_KEYBOARD_SC_F, // F
        HID_KEYBOARD_SC_G, // G
    },
    {
        HID_KEYBOARD_LAYER_RU, // ZX
        0,                     // XC
        0,                     // CV
        0,                     // VB
        HID_KEYBOARD_SC_Z,     // Z
        HID_KEYBOARD_SC_X,     // X
        HID_KEYBOARD_SC_C,     // C
        HID_KEYBOARD_SC_V,     // V
        HID_KEYBOARD_SC_B,     // B
    },
    {
        0,                                                 // YU
        0,                                                 // UI
        HID_KEYBOARD_SC_OPENING_BRACKET_AND_OPENING_BRACE, // IO
        HID_KEYBOARD_SC_CLOSING_BRACKET_AND_CLOSING_BRACE, // OP
        HID_KEYBOARD_SC_Y,                                 // Y
        HID_KEYBOARD_SC_U,                                 // U
        HID_KEYBOARD_SC_I,                                 // I
        HID_KEYBOARD_SC_O,                                 // O
        HID_KEYBOARD_SC_P,                                 // P
    },
    {
        0,                                    // HJ
        0,                                    // JK
        HID_KEYBOARD_SC_APOSTROPHE_AND_QUOTE, // KL
        HID_KEYBOARD_SC_BACKSLASH_AND_PIPE,   // L;
        HID_KEYBOARD_SC_H,                    // H
        HID_KEYBOARD_SC_J,                    // J
        HID_KEYBOARD_SC_K,                    // K
        HID_KEYBOARD_SC_L,                    // L
        HID_KEYBOARD_SC_SEMICOLON_AND_COLON,  // ;
    },
    {
        0,                                         // NM
        0,                                         // M,
        0,                                         // ,.
        0,                                         // ./
        HID_KEYBOARD_SC_N,                         // N
        HID_KEYBOARD_SC_M,                         // M
        HID_KEYBOARD_SC_COMMA_AND_LESS_THAN_SIGN,  // ,<
        HID_KEYBOARD_SC_DOT_AND_GREATER_THAN_SIGN, // .>
        HID_KEYBOARD_SC_SLASH_AND_QUESTION_MARK,   // /?
    }};

// JCUKEN
const uint8_t Layer_Lang2[6][9] PROGMEM = {
    {
        HID_KEYBOARD_SC_TAB, // JC
        0,                   // CU
        0,                   // UK
        0,                   // KE
        HID_KEYBOARD_SC_J,   // J
        HID_KEYBOARD_SC_C,   // C
        HID_KEYBOARD_SC_U,   // U
        HID_KEYBOARD_SC_K,   // K
        HID_KEYBOARD_SC_E,   // E
    },
    {
        0,                 // FY
        0,                 // YW
        0,                 // WA
        0,                 // AP
        HID_KEYBOARD_SC_F, // F
        HID_KEYBOARD_SC_Y, // Y
        HID_KEYBOARD_SC_W, // W
        HID_KEYBOARD_SC_A, // A
        HID_KEYBOARD_SC_P, // P
    },
    {
        0,                                       // Q/
        0,                                       // /S
        0,                                       // SM
        0,                                       // MI
        HID_KEYBOARD_SC_Q,                       // Q
        HID_KEYBOARD_SC_SLASH_AND_QUESTION_MARK, // /
        HID_KEYBOARD_SC_S,                       // S
        HID_KEYBOARD_SC_M,                       // M
        HID_KEYBOARD_SC_I,                       // I
    },
    {
        0,                                                 // NG
        0,                                                 // GH
        HID_KEYBOARD_SC_OPENING_BRACKET_AND_OPENING_BRACE, // HV
        HID_KEYBOARD_SC_CLOSING_BRACKET_AND_CLOSING_BRACE, // VZ
        HID_KEYBOARD_SC_N,                                 // N
        HID_KEYBOARD_SC_G,                                 // G
        HID_KEYBOARD_SC_H,                                 // H
        HID_KEYBOARD_SC_V,                                 // V
        HID_KEYBOARD_SC_Z,                                 // Z
    },
    {
        0,                                    // RO
        0,                                    // OL
        HID_KEYBOARD_SC_APOSTROPHE_AND_QUOTE, // LD
        HID_KEYBOARD_SC_BACKSLASH_AND_PIPE,   // D;
        HID_KEYBOARD_SC_R,                    // R
        HID_KEYBOARD_SC_O,                    // O
        HID_KEYBOARD_SC_L,                    // L
        HID_KEYBOARD_SC_D,                    // D
        HID_KEYBOARD_SC_SEMICOLON_AND_COLON,  // ;
    },
    {
        0,                                         // TX
        0,                                         // XB
        0,                                         // B,
        HID_KEYBOARD_LAYER_EN,                     // ,.
        HID_KEYBOARD_SC_T,                         // T
        HID_KEYBOARD_SC_X,                         // X
        HID_KEYBOARD_SC_B,                         // B
        HID_KEYBOARD_SC_COMMA_AND_LESS_THAN_SIGN,  // ,
        HID_KEYBOARD_SC_DOT_AND_GREATER_THAN_SIGN, // .
    }};

// Navigation and Numbers
const uint8_t Layer_Fn[6][9] PROGMEM = {
    {
        0,                                         // QW
        0,                                         // WE
        0,                                         // ER
        0,                                         // RT
        HID_KEYBOARD_SC_GRAVE_ACCENT_AND_TILDE,    // Q
        HID_KEYBOARD_SC_7_AND_AND_AMPERSAND,       // W
        HID_KEYBOARD_SC_8_AND_ASTERISK,            // E
        HID_KEYBOARD_SC_9_AND_OPENING_PARENTHESIS, // R
        HID_KEYBOARD_SC_MINUS_AND_UNDERSCORE,      // T
    },
    {
        0,                                       // AS
        0,                                       // SD
        0,                                       // DF
        0,                                       // FG
        HID_KEYBOARD_SC_SLASH_AND_QUESTION_MARK, // A
        HID_KEYBOARD_SC_4_AND_DOLLAR,            // S
        HID_KEYBOARD_SC_5_AND_PERCENTAGE,        // D
        HID_KEYBOARD_SC_6_AND_CARET,             // F
        HID_KEYBOARD_SC_EQUAL_AND_PLUS,          // G
    },
    {
        0,                                         // ZX
        0,                                         // XC
        0,                                         // CV
        0,                                         // VB
        HID_KEYBOARD_SC_DOT_AND_GREATER_THAN_SIGN, // Z
        HID_KEYBOARD_SC_1_AND_EXCLAMATION,         // X
        HID_KEYBOARD_SC_2_AND_AT,                  // C
        HID_KEYBOARD_SC_3_AND_HASHMARK,            // V
        HID_KEYBOARD_SC_0_AND_CLOSING_PARENTHESIS, // B
    },
    {
        HID_KEYBOARD_LAYER_MOU,    // YU
        0,                         // UI
        0,                         // IO
        0,                         // OP
        HID_KEYBOARD_SC_ESCAPE,    // Y
        HID_KEYBOARD_SC_INSERT,    // U
        HID_KEYBOARD_SC_UP_ARROW,  // I
        HID_KEYBOARD_SC_DELETE,    // O
        HID_KEYBOARD_SC_BACKSPACE, // P
    },
    {
        0,                           // HJ
        0,                           // JK
        0,                           // KL
        0,                           // L;
        HID_KEYBOARD_SC_PAGE_UP,     // H
        HID_KEYBOARD_SC_LEFT_ARROW,  // J
        HID_KEYBOARD_SC_DOWN_ARROW,  // K
        HID_KEYBOARD_SC_RIGHT_ARROW, // L
        HID_KEYBOARD_SC_ENTER,       // ;
    },
    {
        0,                             // NM
        0,                             // M,
        0,                             // ,.
        0,                             // ./
        HID_KEYBOARD_SC_PAGE_DOWN,     // N
        HID_KEYBOARD_SC_HOME,          // M
        HID_KEYBOARD_SC_TAB,           // ,<
        HID_KEYBOARD_SC_END,           // .>
        HID_KEYBOARD_SC_RIGHT_CONTROL, // /?
    }};

// Function and Number block
const uint8_t Layer_Fn2[6][9] PROGMEM = {
    {
        HID_KEYBOARD_SC_PAUSE,    // QW
        0,                        // WE
        0,                        // ER
        0,                        // RT
        HID_KEYBOARD_SC_NUM_LOCK, // Q
        HID_KEYBOARD_SC_F7,       // W
        HID_KEYBOARD_SC_F8,       // E
        HID_KEYBOARD_SC_F9,       // R
        HID_KEYBOARD_SC_F12,      // T
    },
    {
        HID_KEYBOARD_SC_PRINT_SCREEN, // AS
        0,                            // SD
        0,                            // DF
        0,                            // FG
        HID_KEYBOARD_SC_CAPS_LOCK,    // A
        HID_KEYBOARD_SC_F4,           // S
        HID_KEYBOARD_SC_F5,           // D
        HID_KEYBOARD_SC_F6,           // F
        HID_KEYBOARD_SC_F11,          // G
    },
    {
        0,                           // ZX
        0,                           // XC
        0,                           // CV
        0,                           // VB
        HID_KEYBOARD_SC_SCROLL_LOCK, // Z
        HID_KEYBOARD_SC_F1,          // X
        HID_KEYBOARD_SC_F2,          // C
        HID_KEYBOARD_SC_F3,          // V
        HID_KEYBOARD_SC_F10,         // B
    },
    {
        0,                                     // YU
        0,                                     // UI
        0,                                     // IO
        0,                                     // OP
        HID_KEYBOARD_SC_KEYPAD_ASTERISK,       // Y
        HID_KEYBOARD_SC_KEYPAD_7_AND_HOME,     // U
        HID_KEYBOARD_SC_KEYPAD_8_AND_UP_ARROW, // I
        HID_KEYBOARD_SC_KEYPAD_9_AND_PAGE_UP,  // O
        HID_KEYBOARD_SC_KEYPAD_MINUS,          // P
    },
    {
        0,                                        // HJ
        0,                                        // JK
        0,                                        // KL
        0,                                        // L;
        HID_KEYBOARD_SC_KEYPAD_SLASH,             // H
        HID_KEYBOARD_SC_KEYPAD_4_AND_LEFT_ARROW,  // J
        HID_KEYBOARD_SC_KEYPAD_5,                 // K
        HID_KEYBOARD_SC_KEYPAD_6_AND_RIGHT_ARROW, // L
        HID_KEYBOARD_SC_KEYPAD_PLUS,              // ;
    },
    {
        0,                                       // NM
        0,                                       // M,
        0,                                       // ,.
        HID_KEYBOARD_SC_KEYPAD_ENTER,            // ./
        HID_KEYBOARD_SC_KEYPAD_0_AND_INSERT,     // N
        HID_KEYBOARD_SC_KEYPAD_1_AND_END,        // M
        HID_KEYBOARD_SC_KEYPAD_2_AND_DOWN_ARROW, // ,<
        HID_KEYBOARD_SC_KEYPAD_3_AND_PAGE_DOWN,  // .>
        HID_KEYBOARD_SC_KEYPAD_DOT_AND_DELETE,   // /?
    }};
