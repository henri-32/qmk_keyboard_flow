#include QMK_KEYBOARD_H
#include "quantum/keymap_extras/keymap_german.h"
#include "version.h"

enum layer_names {
    base,
    custom_signs,
    navigation,
};

enum custom_keycodes { 
  MO_CUSTOM_F = SAFE_RANGE,
  MO_CUSTOM_J,
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) { 
  switch (keycode) { 
    case MT(MOD_LALT, KC_A): 
	  return 300; 

    case MT(MOD_LCTL, KC_S): 
      return 250; 

    case LT(navigation, KC_D): 
      return 200; 

    case LT(custom_signs, KC_F): 
      return 170; 

    case LT(custom_signs, KC_J): 
      return 170; 

    case LT(navigation, KC_K): 
      return 200; 

    case MT(MOD_LCTL, KC_L): 
      return 250; 

    case MT(MOD_LALT, DE_ODIA): 
      return 300; 

    default: 
      return 200; 
  }
}



bool caps_word_press_user(uint16_t keycode) {
  switch (keycode) {
    case KC_A ... KC_Z:
      add_weak_mods(MOD_BIT(KC_LSFT));
      return true; 

    case DE_MINS:
      add_weak_mods(MOD_BIT(KC_LSFT));
      return true;

    case KC_BSPC:
      return true;

    default: 
      return false; 
  }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[base] = LAYOUT_ergodox_pretty(
    KC_DOT,  KC_1, KC_2, KC_3, KC_4, KC_5, KC_PSCR,              KC_NO,  KC_6, KC_7, KC_8, KC_9, KC_0, DE_SS,
    KC_TAB,  KC_Q, KC_W, KC_E, KC_R, KC_T, KC_NO,                  KC_NO,  KC_Y, KC_U, KC_I, KC_O, KC_P, DE_UDIA,
    KC_ESC,  MT(MOD_LALT, KC_A), MT(MOD_LCTL, KC_S), LT(navigation, KC_D), MO_CUSTOM_F, KC_G,                          KC_H,  MO_CUSTOM_J, LT(navigation, KC_K), MT(MOD_LCTL, KC_L), MT(MOD_LALT, DE_ODIA), DE_ADIA,
    KC_LGUI, MT(MOD_LCTL, KC_Z), KC_X, KC_C, KC_V, KC_B, KC_NO,   KC_NO, KC_N, KC_M, KC_COMMA, KC_DOT, MT(MOD_LCTL, DE_MINS), KC_LGUI,

    KC_LALT, KC_GRAVE, KC_QUOTE, KC_NO, KC_NO,          KC_NO, KC_NO, KC_NO, KC_NO, KC_RALT,

                                MT(MOD_LALT, KC_APP), KC_LGUI,
                                KC_LALT, MT(MOD_LCTL, KC_ESC),

                                        KC_HOME, KC_PGUP,

    OSM(MOD_LSFT), KC_BSPC, KC_DEL, KC_PGDN, KC_ENT, KC_SPC
),

[custom_signs] = LAYOUT_ergodox_pretty(
    KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_TRNS,             KC_TRNS, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11,
    KC_TRNS, DE_QUES, S(DE_HASH), KC_TRNS, DE_AMPR, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, DE_LCBR, DE_RCBR, DE_DQUO, DE_PLUS, DE_ASTR,
    KC_TRNS, DE_AT, DE_DLR, DE_PERC, DE_SLSH, DE_HASH,              DE_LABK, DE_LPRN, DE_RPRN, DE_RABK, DE_EQL, KC_SLASH,
    KC_TRNS, KC_TRNS, KC_TRNS, DE_BSLS, DE_TILD, KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS, DE_LBRC, DE_RBRC, DE_PIPE, DE_EXLM,KC_TRNS,

    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

                                KC_NO, KC_NO,
                                KC_NO, KC_NO,

                                        KC_NO, KC_NO,

    CW_TOGG, KC_BSPC, KC_DEL, KC_PGDN, KC_ENT, KC_SPC
),

[navigation] = LAYOUT_ergodox_pretty(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, QK_BOOT,
    KC_TRNS, C(KC_W), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_LALT, C(KC_PGUP), C(KC_PGDN), LALT(KC_TAB), KC_TRNS,  KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_F11, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, C(KC_T), KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS, KC_TRNS,

    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,           KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,

                                KC_TRNS, KC_TRNS,
                                KC_TRNS, KC_TRNS,

                                        KC_TRNS, KC_TRNS,

    KC_TRNS, KC_DEL, KC_TRNS, KC_TRNS, KC_TRNS, KC_WBAK
)

};
// --- SAFE VERSION (no RGB, no crash) ---

static bool layer_used = false; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) { 
  if (record->event.pressed && layer_state_is(custom_signs)) { 
    layer_used = true; 
  }

  switch (keycode) { 
    case MO_CUSTOM_F: 
      if (record->event.pressed) { 
        layer_used = false; 
        layer_on(custom_signs); 
      } else { 
          layer_off(custom_signs); 
          if (!layer_used) { 
            tap_code(KC_F); 
          }
      }
      return false; 

  case MO_CUSTOM_J: 
    if (record->event.pressed) {
      layer_used = false; 
      layer_on(custom_signs); 
    } else {
        layer_off(custom_signs); 
        if (!layer_used) { 
          tap_code(KC_J); 
        }
    }
    return false; 
  }
  return true; 
}

layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t layer = biton32(state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();

    switch (layer) {
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        case 3:
            ergodox_right_led_3_on();
            break;
    }

    return state;
};
