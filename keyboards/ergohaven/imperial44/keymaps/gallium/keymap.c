#include QMK_KEYBOARD_H
#include "ergohaven_ruen.h"

void lang_toggle(void);

enum user_codes {
    // Macros
    RBT_DWM = SAFE_RANGE,
    RBT,
    DEL_WRD,
    SLANG,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case RBT:
        if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LGUI) SS_TAP(X_P) SS_UP(X_LGUI));
            SEND_STRING(SS_DELAY(25));
            SEND_STRING("reboot");
            SEND_STRING(SS_TAP(X_ENT));
        }
        return false;
    case RBT_DWM:
        if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_RGUI) SS_DOWN(X_RSFT));
            SEND_STRING(SS_TAP(X_Q));
            SEND_STRING(SS_UP(X_RGUI) SS_UP(X_RSFT));
        }
        return false;
    case DEL_WRD:
        if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LCTL) SS_TAP(X_BSPC) SS_UP(X_LCTL));
        }
        return false;
    case SLANG:
        if (record->event.pressed) {
            layer_invert(1);
            lang_toggle();
        }
        return false;
    }
    return true;
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        [_BASE] = LAYOUT(
         KC_NO,   KC_B,         KC_L,         KC_D,         KC_C,         KC_V,                      KC_J,    KC_Y,            KC_O,          KC_U,         KC_NO,         KC_NO,
         SLANG,   LGUI_T(KC_N), LALT_T(KC_R), LSFT_T(KC_T), LCTL_T(KC_S), KC_G,                      KC_P,    RCTL_T(KC_H),    RSFT_T(KC_A),  RALT_T(KC_E), RGUI_T(KC_I),  KC_NO,
         KC_NO,   KC_X,         KC_Q,         KC_M,         KC_W,         KC_Z,                      KC_K,    KC_F,            KC_NO,         KC_NO,        KC_NO,         TG(7),
                                    LT(5, KC_ESC), LT(3, KC_SPC), LT(2, KC_TAB), KC_NO,    KC_NO, LT(6, KC_ENT), LT(4, KC_BSPC), DEL_WRD
        ),

        [_LOWER] = LAYOUT(
         KC_GRV,  KC_Q,         KC_W,         KC_E,         KC_R,         KC_T,                      KC_Y,    KC_U,            KC_I,          KC_O,         KC_P,          KC_LBRC,
         _______, LGUI_T(KC_A), LALT_T(KC_S), LSFT_T(KC_D), LCTL_T(KC_F), KC_G,                      KC_H,    RCTL_T(KC_J),    RSFT_T(KC_K),  RALT_T(KC_L), RGUI_T(KC_SCLN), KC_QUOT,
         LG_WORD, KC_Z,         KC_X,         KC_C,         KC_V,         KC_B,                      KC_N,    KC_M,            KC_COMM,       KC_DOT,       KC_RBRC,       _______,
                                                      _______, _______, _______, KC_NO,    KC_NO, _______, _______, _______
        ),

        [_RAISE] = LAYOUT(
         KC_NO,  KC_NO,         KC_NO,        KC_NO,        KC_NO,        KC_NO,                     PREVWRD, KC_NO,           KC_NO,         NEXTWRD,      KC_NO,         KC_NO,
         KC_NO,  KC_LGUI,       KC_LALT,      KC_LSFT,      KC_LCTL,      KC_NO,                     KC_LEFT, KC_DOWN,         KC_UP,         KC_RIGHT,     KC_NO,         KC_NO,
         KC_NO,  KC_NO,         KC_NO,        KC_NO,        KC_NO,        KC_NO,                     KC_HOME, KC_NO,           KC_NO,         KC_END,       KC_NO,         KC_NO,
                                                            KC_NO, KC_NO, KC_NO, KC_NO,    KC_NO, _______, _______, _______
        ),

        [_ADJUST] = LAYOUT(
         KC_NO,    KC_1,       KC_2,         KC_3,         KC_4,         KC_5,                      KC_6,    KC_7,            KC_8,          KC_9,         KC_0,          KC_NO,
         LG_QUOTE, KC_NO,      KC_MINS,      KC_EQL,       LSFT(KC_EQL), KC_NO,                     LG_PERC, LG_CIRC,         LSFT(KC_8),    KC_SLSH,      LG_DLR,        LG_DQUO,
         KC_NO,    KC_NO,      KC_NO,        KC_NO,        KC_NO,        KC_NO,                     KC_NO,   KC_NO,           LG_COMMA,      LG_DOT,       KC_NO,         KC_NO,
                                                            KC_NO, KC_NO, KC_NO, KC_NO,    KC_NO, _______, _______, _______
       ),

        [_FOUR] = LAYOUT(
         KC_NO,    LG_TILD,    LG_LT,        KC_MINS,      LG_GT,        KC_NO,                     KC_NO,   LSFT(KC_9),      LSFT(KC_8),    LSFT(KC_0),   LG_QUES,       KC_NO,
         LG_SCLN,  LG_GRAVE,   LG_SLASH,     LG_PIPE,      KC_BSLS,      KC_NO,                     LG_AT,   LG_LCBR,         LG_AMPR,       LG_RCBR,      LG_HASH,       LG_COLON,
         KC_NO,    KC_NO,      LG_NUM,       LSFT(KC_MINS), LSFT(KC_1),  KC_NO,                     KC_NO,   LG_LBR,          KC_NO,         LG_RBR,       KC_NO,         KC_NO,
                                                            KC_NO, KC_NO, KC_NO, KC_NO,    KC_NO, _______, _______, _______
       ),

        [_FIVE] = LAYOUT(
         KC_NO,    KC_NO,      KC_NO,        KC_NO,       KC_NO,         KC_NO,                     KC_NO,   KC_NO,           KC_NO,         KC_NO,        KC_NO,         KC_NO,
         KC_NO,    KC_NO,      KC_NO,        KC_NO,       KC_NO,         KC_NO,                     KC_MS_L, KC_MS_D,         KC_MS_U,       KC_MS_R,      KC_NO,         KC_NO,
         KC_NO,    KC_NO,      KC_NO,        KC_NO,       KC_NO,         KC_NO,                     KC_WH_L, KC_WH_D,         KC_WH_U,       KC_WH_R,      KC_NO,         KC_NO,
                                                            KC_NO, KC_NO, KC_NO, KC_NO,    KC_NO, KC_BTN1, KC_BTN2, KC_BTN3
       ),

        [_SIX] = LAYOUT(
         KC_NO,    KC_NO,      KC_NO,        KC_NO,       RBT_DWM,       KC_NO,                     KC_NO,   KC_NO,           KC_NO,         KC_NO,        EH_PRINFO,     KC_NO,
         KC_NO,    KC_LGUI,    KC_LALT,      KC_LSFT,     KC_LCTL,       KC_NO,                     KC_NO,   KC_VOLD,         KC_MUTE,       KC_VOLU,      KC_PSCR,       KC_NO,
         KC_NO,    KC_PWR,     KC_WAKE,      KC_SLEP,     RBT,           KC_NO,                     KC_NO,   KC_NO,           KC_NO,         KC_NO,        KC_NO,         KC_NO,
                                                            KC_NO, KC_NO, KC_NO, KC_NO,    KC_NO, KC_NO, KC_NO, KC_NO
       ),

        [_SEVEN] = LAYOUT(
         KC_NO,    KC_NO,      KC_NO,        KC_NO,       KC_NO,         KC_NO,                     KC_NO,   KC_F1,           KC_F2,         KC_F3,        KC_F4,         KC_NO,
         KC_NO,    KC_LGUI,    KC_LALT,      KC_LSFT,     KC_LCTL,       KC_NO,                     KC_NO,   KC_F5,           KC_F6,         KC_F7,        KC_F8,         KC_NO,
         KC_NO,    KC_NO,      KC_NO,        KC_NO,       KC_NO,         KC_NO,                     KC_NO,   KC_F9,           KC_F10,        KC_F11,       KC_F12,        _______,
                                                            KC_NO, KC_NO, KC_NO, KC_NO,    KC_NO, KC_NO, KC_NO, KC_NO
       ),
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
  [1] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)},
  [2] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)},
  [3] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)},
};
#endif
