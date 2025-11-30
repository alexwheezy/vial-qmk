#include QMK_KEYBOARD_H
#include "ergohaven_ruen.h"

#define INACTIVITY_TIMEOUT 30000 // 30 seconds

#define EN    0
#define RU    1
#define NAV   2
#define NUM   3
#define SYM   4
#define MOUSE 5
#define MEDIA 6
#define FN    7

static uint32_t layer_timer = 0;
static bool english_word = false;

enum keycodes {
    RBT_DWM = SAFE_RANGE,
    RBT,
    SLANG,
    C_WORD,
};

void lang_toggle(void);

// I don't need OLED feature so I disabled it
bool oled_task_user(void){
    oled_clear();
    return false;
}

void switch_lang_and_layer(void) {
    layer_invert(1);
    lang_toggle();
}

void matrix_scan_user(void) {
    if (get_highest_layer(layer_state) != 0 && timer_elapsed32(layer_timer) > INACTIVITY_TIMEOUT) {
        switch_lang_and_layer();
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    layer_timer = timer_read32();
    return state;
}

bool pre_process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) return true;

    if (english_word) {
        switch (keycode & 0xFF) {
            case KC_SPACE:
            case KC_ENTER:
            case KC_ESCAPE:
            case KC_MINUS:
                english_word = false;
                caps_word_off();
                switch_lang_and_layer();
                break;
            default:
                break;
        }
    }
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) layer_timer = timer_read32();

    switch (keycode) {
    case RBT:
        SEND_STRING(SS_DOWN(X_LGUI) SS_TAP(X_P) SS_UP(X_LGUI));
        SEND_STRING(SS_DELAY(25));
        SEND_STRING("reboot");
        SEND_STRING(SS_TAP(X_ENT));
        return false;
    case RBT_DWM:
        SEND_STRING(SS_DOWN(X_RGUI) SS_DOWN(X_RSFT));
        SEND_STRING(SS_TAP(X_Q));
        SEND_STRING(SS_UP(X_RGUI) SS_UP(X_RSFT));
        return false;
    case SLANG:
        if (record->event.pressed) {
            english_word = false;
            switch_lang_and_layer();
        }
        return false;
    case C_WORD:
        if (get_cur_lang() == LANG_RU && !english_word) {
            english_word = true;
            bool shift = (get_mods() | get_oneshot_mods() | get_weak_mods()) & MOD_MASK_SHIFT;
            if (get_oneshot_mods() & MOD_MASK_SHIFT) clear_oneshot_mods();
            switch_lang_and_layer();
            if (shift) caps_word_on();
        }
        return false;
    }
    return true;
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    return TAPPING_TERM;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        [EN] = LAYOUT(
         TG(7),   KC_B,         KC_L,         KC_D,         KC_C,         KC_V,                     KC_J,    KC_Y,           KC_O,          KC_U,         KC_NO,         TG(7),
         SLANG,   LGUI_T(KC_N), LALT_T(KC_R), LSFT_T(KC_T), LCTL_T(KC_S), KC_G,                     KC_P,    RCTL_T(KC_H),   RSFT_T(KC_A),  RALT_T(KC_E), RGUI_T(KC_I),  KC_NO,
         KC_NO,   KC_X,         KC_Q,         KC_M,         KC_W,         KC_Z,                     KC_K,    KC_F,           KC_NO,         KC_NO,        KC_NO,         KC_NO,
                                    LT(5, KC_ESC), LT(3, KC_SPC), LT(2, KC_TAB), KC_NO,    KC_NO, LT(6, KC_ENT), LT(4, KC_BSPC), KC_NO
        ),

        [RU] = LAYOUT(
         KC_GRV,  KC_Q,         KC_W,         KC_E,         KC_R,         KC_T,                     KC_Y,    KC_U,           KC_I,          KC_O,         KC_P,          KC_LBRC,
         _______, LGUI_T(KC_A), LALT_T(KC_S), LSFT_T(KC_D), LCTL_T(KC_F), KC_G,                     KC_H,    RCTL_T(KC_J),   RSFT_T(KC_K),  RALT_T(KC_L), RGUI_T(KC_SCLN), KC_QUOT,
         C_WORD,  KC_Z,         KC_X,         KC_C,         KC_V,         KC_B,                     KC_N,    KC_M,           KC_COMM,       KC_DOT,       KC_RBRC,       KC_NO,
                                                      _______, _______, _______, KC_NO,    KC_NO, _______, _______, _______
        ),

        [NAV] = LAYOUT(
         KC_NO,   KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,                    PREVWRD, KC_NO,          KC_NO,         NEXTWRD,      KC_NO,         KC_NO,
         KC_NO,   KC_LGUI,      KC_LALT,      KC_LSFT,      KC_LCTL,      KC_NO,                    KC_LEFT, KC_DOWN,        KC_UP,         KC_RIGHT,     KC_NO,         KC_NO,
         KC_NO,   KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,                    KC_HOME, KC_NO,          KC_NO,         KC_END,       KC_NO,         KC_NO,
                                                            KC_NO, KC_NO, KC_NO, KC_NO,    KC_NO, _______, _______, _______
        ),

        [NUM] = LAYOUT(
         KC_NO,    KC_0,        KC_1,         KC_2,         KC_3,         KC_4,                     KC_NO,   LG_PERC,        LSFT(KC_8),    LG_AT,        LG_DLR,        KC_NO,
         KC_NO,    KC_5,        KC_6,         KC_7,         KC_8,         KC_9,                     KC_NO,   KC_MINS,        KC_EQL,        LSFT(KC_EQL), LG_CIRC,       LG_NUM,
         KC_NO,    KC_NO,       KC_NO,        KC_NO,        KC_NO,        KC_NO,                    KC_NO,   KC_NO,          LG_COMMA,      LG_DOT,       KC_NO,         KC_NO,
                                                            KC_NO, KC_NO, KC_NO, KC_NO,    KC_NO, _______, _______, _______
       ),

        [SYM] = LAYOUT(
         KC_NO,    KC_NO,       LG_SLASH,     LG_PIPE,      KC_BSLS,      KC_NO,                    KC_NO,   LSFT(KC_9),     LSFT(KC_8),    LSFT(KC_0),   KC_NO,         KC_NO,
         KC_NO,    LG_GRAVE,    LG_LT,        KC_MINS,      LG_GT,        KC_NO,                    KC_NO,   LG_LBR,         LG_AMPR,       LG_RBR,       LG_SCLN,       LG_QUOTE,
         KC_NO,    KC_NO,       LSFT(KC_1),   LG_HASH,      LG_QUES,      KC_NO,                    KC_NO,   KC_NO,          KC_NO,         KC_NO,        KC_NO,         KC_NO,
                                                            KC_NO, KC_NO, KC_NO, KC_NO,    KC_NO, _______, _______, _______
        ),

        [MOUSE] = LAYOUT(
         KC_NO,    KC_NO,       KC_NO,        KC_NO,       KC_NO,         KC_NO,                    KC_NO,   KC_NO,          KC_NO,         KC_NO,        KC_NO,         KC_NO,
         KC_NO,    KC_NO,       KC_NO,        KC_NO,       KC_NO,         KC_NO,                    KC_MS_L, KC_MS_D,        KC_MS_U,       KC_MS_R,      KC_NO,         KC_NO,
         KC_NO,    KC_NO,       KC_NO,        KC_NO,       KC_NO,         KC_NO,                    KC_WH_L, KC_WH_D,        KC_WH_U,       KC_WH_R,      KC_NO,         KC_NO,
                                                            KC_NO, KC_NO, KC_NO, KC_NO,    KC_NO, KC_BTN1, KC_BTN2, KC_BTN3
        ),

        [MEDIA] = LAYOUT(
         KC_NO,    KC_NO,       KC_NO,        KC_NO,       RBT_DWM,       KC_NO,                    KC_NO,   KC_NO,          KC_NO,         KC_NO,        KC_NO,         KC_NO,
         KC_NO,    KC_LGUI,     KC_LALT,      KC_LSFT,     KC_LCTL,       KC_NO,                    KC_NO,   KC_VOLD,        KC_MUTE,       KC_VOLU,      KC_PSCR,       KC_NO,
         KC_NO,    KC_PWR,      KC_WAKE,      KC_SLEP,     RBT,           KC_NO,                    KC_NO,   KC_NO,          KC_NO,         KC_NO,        KC_NO,         KC_NO,
                                                            KC_NO, KC_NO, KC_NO, KC_NO,    KC_NO, KC_NO, KC_NO, KC_NO
        ),

        [FN] = LAYOUT(
         _______,  KC_NO,       KC_NO,        KC_NO,       KC_NO,         QK_BOOT,                  QK_BOOT, KC_F1,          KC_F2,         KC_F3,        KC_F4,         _______,
         KC_NO,    KC_LGUI,     KC_LALT,      KC_LSFT,     KC_LCTL,       KC_NO,                    KC_NO,   KC_F5,          KC_F6,         KC_F7,        KC_F8,         KC_NO,
         KC_NO,    KC_NO,       KC_NO,        KC_NO,       KC_NO,         KC_NO,                    KC_NO,   KC_F9,          KC_F10,        KC_F11,       KC_F12,        KC_NO,
                                                            KC_NO, KC_NO, KC_NO, KC_NO,    KC_NO, KC_NO, KC_NO, KC_NO
        ),
};
