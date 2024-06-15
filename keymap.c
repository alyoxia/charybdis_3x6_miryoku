/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H


/**
 * Alyoxia:
 *
 * Main changes to antonkis' layout:
 * - Remove top row
 * - Remove lower 2 left thumb keys
 * - Remove lower 1 right thumb key
 * - Remove function layer (due to missing right thumb key)
 * - Swap right hand BTN1 and BTN2
 */

enum charybdis_keymap_layers {
    LAYER_BASE = 0,
    LAYER_NAVIGATION,
    LAYER_POINTER,
    LAYER_NUMERAL,
    LAYER_SYMBOLS
};

#define SPC_NAV LT(LAYER_NAVIGATION, KC_SPC)
#define TAB_PTR LT(LAYER_POINTER, KC_TAB)
#define LA2_PTR LT(LAYER_POINTER, KC_COMM)
#define BSP_NUM LT(LAYER_NUMERAL, KC_BSPC)
#define ENT_SYM LT(LAYER_SYMBOLS, KC_ENT)

#define ALT_SCL MT(MOD_RALT, KC_SCLN)
#define CTL_EQL MT(MOD_RCTL, KC_EQL)

#ifdef COMBO_ENABLE
const uint16_t PROGMEM combo_layer_lock_med[] = {ESC_MED, CW_TOGG, COMBO_END};
const uint16_t PROGMEM combo_layer_lock_nav[] = {SPC_NAV, CW_TOGG, COMBO_END};
const uint16_t PROGMEM combo_layer_lock_ptr[] = {TAB_PTR, CW_TOGG, COMBO_END};
const uint16_t PROGMEM combo_layer_lock_fun[] = {DEL_FUN, KC_CAPS, COMBO_END};
const uint16_t PROGMEM combo_layer_lock_num[] = {BSP_NUM, KC_CAPS, COMBO_END};
const uint16_t PROGMEM combo_layer_lock_sym[] = {ENT_SYM, KC_CAPS, COMBO_END};
#endif

#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_NO
#    define S_D_MOD KC_NO
#    define SNIPING KC_NO
#endif // !POINTING_DEVICE_ENABLE

#define KC_UNDO LCTL(KC_Z)
#define KC_AGIN LCTL(KC_Y)
#define KC_CUT LCTL(KC_X)
#define KC_COPY LCTL(KC_C)
#define KC_PSTE LCTL(KC_V)

// clang-format off
/**
 * \brief NUM+ColemakDH+miryoku hold-n-tap thumbs (4 rows, 2x6 columns, 5+3 thumbs)
 *
 * - Put F-keys in place of number-keys (top non-miryoku row) to facilitate
 *   app shortcuts with one hand, eg. *midnight commander*, *vscode*.
 *   Besides, a non-char key is handy in Esc's position ;-)
 *
 * - Put F-keys in place of number-keys (top non-miryoku row) to facilitate
 *   app shortcuts with one hand, eg. *midnight commander*, *vscode*.
 *   Besides, a non-char key is handy in Esc's position ;-)
 *
 * **Deviation from Miryoku:**
 *
 * - Swap `,` with `-`, the former being much usefull in programming, the latter's place
 *   in the num+left thumb rhymes with `.`, both there when num-typing.
 */
#define LAYOUT_LAYER_BASE                                                                              \
     KC_APP,   KC_Q,   KC_W,   KC_F,   KC_P,   KC_B,     KC_J,   KC_L,   KC_U,   KC_Y,KC_QUOT,KC_DEL, \
    KC_F5,   KC_A,   KC_R,   KC_S,   KC_T,   KC_G,     KC_M,   KC_N,   KC_E,   KC_I,   KC_O,KC_SCLN, \
    XXXXXXX,   KC_Z,   KC_X,   KC_C,   KC_D,   KC_V,     KC_K,   KC_H,KC_MINS,LA2_PTR,KC_DOT,CW_TOGG, \
                            KC_ESC,SPC_NAV,TAB_PTR,                                  ENT_SYM,BSP_NUM

/** Convenience row shorthands. */
#define _________________DEAD_HALF_ROW_________________  XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX
#define _________________TRNS_HALF_ROW_________________  _______,_______,_______,_______,_______,_______
#define ________________HOME_ROW_GACS_L________________  _______,KC_LGUI,KC_LALT,KC_LCTL,KC_LSFT,XXXXXXX
#define ________________HOME_ROW_GACS_R________________  XXXXXXX,KC_LSFT,KC_LCTL,KC_LALT,KC_LGUI,_______

/*
 * Layers used on the Charybdis 4x6.
 *
 * These layers started off heavily inspired by the Miryoku layout, but trimmed
 * down for 3x5 and then enhanced for 4x6.
 *
 * See https://github.com/manna-harbour/miryoku for the original layout.
 */


/** \brief Mouse layer featuring common editing keys with *all other right layers*.
 *
 * All mouse buttons & layer activator are located close and around the right trackball,
 * along with copy, paste, undo and redo keys, to facilitate one-hand editing & browsing.
 *
 * Right thumb keys are duplicated from the base layer to avoid having to change layer
 * mid edit just to press Enter or delete a char, and to enable auto-repeat.
 *
 * Without mouse emulation (useless with trackball).
 *
 * **Rational:** with the right-thumb occupied on the trackball, it's easier
 * placing the x3 *mouse buttons* on the primary keys (vs on the right thumb-cluster).
 * And to allow using trackball single-handedly (eg. when browsing),
 * the *ring finger* is chosen as layer activator, as it provides better versasility vs
 * pinning the "short" pinky, which would make the top-alphas row harder to reach and
 * anything on the 5th column unreachable (the original *charybdis 4x6 uses the pinky).
 */
#define LAYOUT_LAYER_POINTER                                                                           \
    _________________DEAD_HALF_ROW_________________,  KC_AGIN,KC_UNDO,KC_BTN3,KC_BTN5,DPI_MOD, KC_TAB, \
    ________________HOME_ROW_GACS_L________________,  KC_PSTE,KC_BTN1,KC_BTN2,KC_BTN4,S_D_MOD, KC_SPC, \
    _______,XXXXXXX,XXXXXXX,SNIPING,DRGSCRL,XXXXXXX,   KC_CUT,KC_COPY,DRGSCRL,SNIPING,_______,_______, \
                             KC_ESC,KC_BTN1,_______,                                   KC_ENT,KC_BSPC

/**
 * \brief Navigation layer featuring common editing keys with *all other right layers*.
 *
 * Primary right-hand layer activated by left home thumb & right pinky is for navigation and
 * editing. Cursor keys and line and page movement are on a "cross" centered around
 * home position, while clipboard, undos and other editing keys on prinary & thumbs
 * *mimic the pointer layer*.
 * Practically, with alternating right ring & pinky pinning, single-handed
 * editing & mouse is possible.
 */
#define LAYOUT_LAYER_NAVIGATION                                                                        \
    _________________DEAD_HALF_ROW_________________,  KC_AGIN,KC_UNDO,  KC_UP,KC_HOME,KC_PGUP, KC_TAB, \
    ________________HOME_ROW_GACS_L________________,  KC_PSTE,KC_LEFT,KC_DOWN,KC_RGHT,KC_PGDN, KC_SPC, \
    _______,KC_UNDO, KC_CUT,KC_COPY,XXXXXXX,KC_PSTE,   KC_CUT,KC_COPY, KC_INS,KC_END,_______,_______, \
                             KC_ESC,_______,_______,                                   KC_ENT,KC_BSPC

/**
 * \brief Numeral layout.
 *
 * Primary left-hand layer (right home thumb) is numerals and symbols. Numerals
 * are in the standard numpad locations with symbols in the remaining positions.
 *
 * Editing keys (copy-paste, undo) shared with all other right layers.
 * The `-,.` punctuations on the other side (right) are preserved from the base layer.
 */
#define LAYOUT_LAYER_NUMERAL                                                                           \
    _______,KC_LBRC,   KC_7,   KC_8,   KC_9,KC_RBRC,  KC_AGIN,KC_UNDO, KC_EQL,KC_SLSH,KC_BSLS, KC_TAB, \
    _______,KC_SCLN,   KC_4,   KC_5,   KC_6, KC_EQL,  KC_PSTE,KC_LSFT,KC_LCTL,KC_LALT,KC_LGUI, KC_SPC, \
    KC_BSPC, KC_GRV,   KC_1,   KC_2,   KC_3,KC_BSLS,   KC_CUT,KC_COPY,KC_MINS,KC_COMM, KC_DOT,_______, \
                             KC_DOT,   KC_0,KC_X,                                      KC_ENT,_______


/**
 * \brief Symbols layer.
 *
 * Secondary left-hand layer has shifted symbols in the same locations to reduce
 * chording when using mods with shifted symbols. `KC_LPRN` is duplicated next to
 * `KC_RPRN`.
 *
 * Editing keys (copy-paste, undo) shared with all other right layers.
  * The `-,.` punctuations on the other side (right) are preserved from the base layer.
*/
#define LAYOUT_LAYER_SYMBOLS                                                                           \
    _______,KC_LCBR,KC_AMPR,KC_ASTR,KC_LPRN,KC_RCBR,  KC_AGIN,KC_UNDO, KC_PLUS,KC_QUESTION,KC_PIPE, KC_TAB, \
    _______,KC_COLN, KC_DLR,KC_PERC,KC_CIRC,KC_PLUS,  KC_PSTE,KC_LSFT,KC_LCTL,KC_LALT,KC_LGUI, KC_SPC, \
    _______,KC_TILD,KC_EXLM,  KC_AT,KC_HASH,KC_PIPE,   KC_CUT,KC_COPY,KC_UNDERSCORE,KC_LEFT_ANGLE_BRACKET, KC_RIGHT_ANGLE_BRACKET,_______, \
                            KC_LPRN,KC_RPRN,KC_QUES,                                  _______,KC_BSPC

/**
 * \brief Add Home Row mod to a layout.
 *
 * Expects a 12-key per row layout, at least x3 rows (at least 36 keycodes).
 * Adds support for GACS (Gui, Alt, Ctl, Shift) home row.
 *
 * This is meant to be used with `LAYER_ALPHAS_QWERTY` defined above, eg.:
 *
 *     HOME_ROW_MOD_GACS(LAYER_ALPHAS_QWERTY)
 */
#define _HOME_ROW_MOD_GACS(                                                     \
    L00, L01, L02, L03, L04, L05, R06, R07, R08, R09, R10, R11,                 \
    L12, L13, L14, L15, L16, L17, R18, R19, R20, R21, R22, R23,                 \
    L24, L25, L26, L27, L28, L29, R30, R31, R32, R33, R34, R35,                 \
    ...)                                                                        \
          L00,         L01,         L02,         L03,         L04,         L05, \
          R06,         R07,         R08,         R09,         R10,         R11, \
          L12,         L13,         L14,         L15,         L16,         L17, \
          R18,         R19,         R20,         R21,         R22,         R23, \
          L24, LGUI_T(L25), LALT_T(L26), LCTL_T(L27), LSFT_T(L28),         L29, \
          R30, RSFT_T(R31), RCTL_T(R32),         R33, LALT_T(R34),         R35, \
    __VA_ARGS__
#define HOME_ROW_MOD_GACS(...) _HOME_ROW_MOD_GACS(__VA_ARGS__)

#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

//const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//  [LAYER_BASE] = LAYOUT_wrapper(HOME_ROW_MOD_GACS(LAYOUT_LAYER_BASE)),
//  [LAYER_FUNCTION] = LAYOUT_wrapper(LAYOUT_LAYER_FUNCTION),
//  [LAYER_NAVIGATION] = LAYOUT_wrapper(LAYOUT_LAYER_NAVIGATION),
//  [LAYER_NUMERAL] = LAYOUT_wrapper(LAYOUT_LAYER_NUMERAL),
//  [LAYER_POINTER] = LAYOUT_wrapper(LAYOUT_LAYER_POINTER),
//  [LAYER_SYMBOLS] = LAYOUT_wrapper(LAYOUT_LAYER_SYMBOLS),
//};
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT_wrapper(HOME_ROW_MOD_GACS(LAYOUT_LAYER_BASE)),
  [LAYER_NAVIGATION] = LAYOUT_wrapper(LAYOUT_LAYER_NAVIGATION),
  [LAYER_NUMERAL] = LAYOUT_wrapper(LAYOUT_LAYER_NUMERAL),
  [LAYER_POINTER] = LAYOUT_wrapper(LAYOUT_LAYER_POINTER),
  [LAYER_SYMBOLS] = LAYOUT_wrapper(LAYOUT_LAYER_SYMBOLS),
};
// clang-format on

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LGUI_T(KC_A):
        case RGUI_T(KC_O):
            // Compensate for weaker little fingers
            return TAPPING_TERM+130;
        case LALT_T(KC_R):
        case LCTL_T(KC_S):
        case LSFT_T(KC_T):
        case RALT_T(KC_I):
        case RCTL_T(KC_E):
        case RSFT_T(KC_N):
            // Compensate for homerow mods
            return TAPPING_TERM+20;
        default:
            return TAPPING_TERM;
    }
}

// Enable debugging
// https://github.com/qmk/qmk_firmware/blob/master/docs/faq_debug.md
void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=false;
  debug_matrix=false;
  debug_keyboard=false;
  //debug_mouse=true;
#ifdef MACCEL_ENABLE
    keyboard_post_init_maccel();
#endif
}

#ifdef COMBO_ENABLE
/*
combo_t key_combos[] = {
    COMBO(combo_layer_lock_nav, TG(LAYER_NAVIGATION)),
    COMBO(combo_layer_lock_ptr, TG(LAYER_POINTER)),
    COMBO(combo_layer_lock_fun, TG(LAYER_FUNCTION)),
    COMBO(combo_layer_lock_num, TG(LAYER_NUMERAL)),
    COMBO(combo_layer_lock_sym, TG(LAYER_SYMBOLS)),
};
*/
combo_t key_combos[] = {
    COMBO(combo_layer_lock_nav, TG(LAYER_NAVIGATION)),
    COMBO(combo_layer_lock_ptr, TG(LAYER_POINTER)),
    COMBO(combo_layer_lock_num, TG(LAYER_NUMERAL)),
    COMBO(combo_layer_lock_sym, TG(LAYER_SYMBOLS)),
};
#endif

/*
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case KC_MINS:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
        // extra from defaults
        case KC_SLSH:
        case KC_LEFT:
        case KC_RGHT:
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}
*/


#ifdef MACCEL_ENABLE
//// MACCEL configs
//
// Design: https://www.desmos.com/calculator/p0etbmee57
// Design: https://www.desmos.com/calculator/fjjli56gow
// Mine butters with slow gnome-moute+accel
// #define MACCEL_TAKEOFF     0.7   // --/++ curve starts rising smoothlier/abruptlier
// #define MACCEL_GROWTH      0.25  // --/++ curve reaches max limit slower/faster
// #define MACCEL_OFFSET      4.7   // --/++ growth kicks in earlier/later
// #define MACCEL_LIMIT       9.0   // maximum acceleration factor

// #define MACCEL_TAKEOFF     1.0   // --/++ curve starts rising smoothlier/abruptlier
// #define MACCEL_GROWTH      0.56  // --/++ curve reaches max limit slower/faster
// #define MACCEL_OFFSET      4.8   // --/++ growth kicks in earlier/later
// #define MACCEL_LIMIT       8.0   // maximum acceleration factor

// #define MACCEL_TAKEOFF     1.07  // --/++ curve starts rising smoothlier/abruptlier
// #define MACCEL_GROWTH      0.56  // --/++ curve reaches max limit slower/faster
// #define MACCEL_OFFSET      4.5   // --/++ growth kicks in earlier/later
// #define MACCEL_LIMIT       8.0   // maximum acceleration factor

// Mine with Gnome-mouse: mid-speed + no-accel, 400DPI both mouse/scroll
#define MACCEL_TAKEOFF     1.18  // --/++ curve starts rising smoothlier/abruptlier
#define MACCEL_GROWTH      0.56  // --/++ curve reaches max limit slower/faster
#define MACCEL_OFFSET      3.6   //--/++ growth kicks in earlier/later
#define MACCEL_LIMIT       9.0   //maximum acceleration factor

// Wimads, old https://www.desmos.com/calculator/p0etbmee57
// New-letters: https://www.desmos.com/calculator/4ajz8f7bqb
// #define MACCEL_TAKEOFF  2.0   // --/++ curve starts rising smoothlier/abruptlier
// #define MACCEL_GROWTH   0.25  // --/++ curve reaches max limit slower/faster
// #define MACCEL_OFFSET   2.2   // --/++ growth kicks in earlier/later
// #define MACCEL_LIMIT    6.0   // maximum acceleration factor

// To view mouse's distance/velocity while configuring maccel,
// set `CONSOLE_ENABLE = yes` in `rules.mk` and uncomment the lines below,
// and run `qmk console` in the shell:
// #define MACCEL_DEBUG
// #undef PRINTF_SUPPORT_DECIMAL_SPECIFIERS
// #define PRINTF_SUPPORT_DECIMAL_SPECIFIERS 1


#   include "maccel/maccel.h"

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    return pointing_device_task_maccel(mouse_report);
}

enum my_keycodes {
    MA_TAKEOFF = QK_USER,   // mouse acceleration curve takeoff (initial acceleration) step key
    MA_GROWTH_RATE,              // mouse acceleration curve growth rate step key
    MA_OFFSET,              // mouse acceleration curve offset step key
    MA_LIMIT,               // mouse acceleration curve limit step key
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_maccel(keycode, record, MA_TAKEOFF, MA_GROWTH_RATE, MA_OFFSET, MA_LIMIT)) {
        return false;
    }
    /* insert your own macros here */
    return true;
}
#endif  // MACCEL_ENABLE


#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in
// rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);

/**
 *
 * Led indices for RGBs.
 * C-strings so 0 cannot set the color of the 1st led.
 *
 * Indicate *caps-states* with top-inner keys
 * (left-side works only if `SPLIT_LAYER_STATE_ENABLE`)
 */
const int8_t caps_lock_leds[] = {
    20, // right-inner-top
    49, // right-inner-top
    -1
};
const int8_t caps_word_leds[] = {
    //21, // NOT WORKING, caps-word state not shared!
    50, // left-inner-2nd
    51, // left-inner-3rd
    -1
};

const int8_t mod_shift_leds[] = {
    28, // left-3rd-thumb
    54, // right-2nd-thumb
    -1
};
const int8_t mod_ctrl_leds[] = {
    27, // left-2nd-thumb
    53, // right-1st-thumb
    -1
};
const int8_t mod_alt_leds[] = {
    26, // left-1st-thumb
    55, // right-bottom-thumb
    -1
};

bool inarray(const int8_t *arr, int8_t led) {
    while (*arr != -1 && *arr != led) arr++;
    return *arr == led;
}

void rgb_matrix_colorify_led(uint8_t led, uint8_t mods, bool caps_lock, bool caps_word) {
    RGB color = { 0, 0, 0 };
    bool color_set = false;

    void set_color(int r, int g, int b) {
        color.r = r;
        color.g = g;
        color.b = b;
        color_set = true;
    }

    if (led == 7 || led == 36) {  // 2nd top-outers combine mod colors
        if (mods & MOD_MASK_SHIFT) {
            color.g = 0xff;
            color_set = true;
        }
        if (mods & MOD_MASK_CTRL) {
            color.r = 0xff;
            color_set = true;
        }
        if (mods & MOD_MASK_ALT) {
            color.b = 0xff;
            color_set = true;
        }
    } else if (caps_lock && inarray(caps_lock_leds, led)) {
        set_color(RGB_WHITE);
    }
    else if (caps_word && inarray(caps_word_leds, led)) {
        set_color(RGB_WHITE);
    }
    else if ((mods & (MOD_MASK_SHIFT | MOD_MASK_GUI)) && inarray(mod_shift_leds, led)) {
        set_color(RGB_GREEN);
    }
    else if ((mods & (MOD_MASK_CTRL | MOD_MASK_GUI)) && inarray(mod_ctrl_leds, led)) {
        set_color(RGB_RED);
    }
    else if ((mods & (MOD_MASK_ALT | MOD_MASK_GUI)) && inarray(mod_alt_leds, led)) {
        set_color(RGB_BLUE);
    }
    else {
        switch (get_highest_layer(layer_state | default_layer_state)) {
        case LAYER_POINTER:
            set_color(RGB_YELLOW);
            break;
        //case LAYER_FUNCTION:
        //    set_color(RGB_MAGENTA);
        //    break;
        case LAYER_NAVIGATION:
            set_color(RGB_CYAN);
            break;
        case LAYER_NUMERAL:
            set_color(RGB_BLUE);
            break;
        case LAYER_SYMBOLS:
            set_color(RGB_CORAL);
            break;
        default:
            break;
        }
    }

    if (color_set) {
        rgb_matrix_set_color(led, color.r, color.g, color.b);
    }
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t mods = get_mods();
    bool caps_lock = host_keyboard_led_state().caps_lock;
    bool caps_word = is_caps_word_on();

    for (uint8_t led = led_min; led <= led_max; led++) {
        rgb_matrix_colorify_led(led, mods, caps_lock, caps_word);
    }

    return false;
}
#endif // RGB_MATRIX_ENABLE
