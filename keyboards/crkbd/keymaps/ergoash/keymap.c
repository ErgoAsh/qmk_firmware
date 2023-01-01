/*
Copyright 2022 @ErgoAsh

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include QMK_KEYBOARD_H
#include "keycode.h"
#include "process_key_override.h"

#define _QWERTY 0
#define _ENGRAM 1
#define _GAMING 2
#define _NAV 3
#define _NUM_QWERTY 4
#define _NUM_ENGRAM 5
#define _ADJUST 6
#define _FUNCTION 7

// Custom codes shortcuts
#define CC_NAVF LT(_NAV, KC_F)
#define CC_NAVA LT(_ADJUST, KC_A)

#define CC_ADJB LT(_ADJUST, KC_B)
#define CC_ADJM LT(_ADJUST, KC_MINS)

#define CC_FUNQ LT(_FUNCTION, KC_QUES)
#define CC_FUNN LT(_FUNCTION, KC_N)

#define CC_ALTZ LALT_T(KC_Z)
#define CC_GUIE LGUI_T(KC_ENT)
#define CC_MONQ MO(_NUM_QWERTY)
#define CC_MONE MO(_NUM_ENGRAM)

#define CC_DFQW DF(_QWERTY)
#define CC_DFEN DF(_ENGRAM)
#define CC_DFGA DF(_GAMING)

// TODO replace KC_PMNS with something else 
// Maybe change place with CC_GUIE and put _NAV layer there

// TODO move OLED stuff to a different file

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_ESC,    KC_A,    KC_S,    KC_D, CC_NAVF,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V, CC_ADJB,                      CC_FUNN,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, CC_ALTZ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         KC_PMNS,  CC_GUIE, KC_RSFT,    CC_MONQ,  KC_SPC, KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

  [_ENGRAM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_B,    KC_Y,    KC_O,    KC_U, KC_QUOT,                      KC_DQUO,    KC_L,    KC_D,    KC_W,   KC_V,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_ESC,    KC_C,    KC_I,    KC_E,    KC_A, KC_COMM,                       KC_DOT,    KC_H,    KC_T,    KC_S,    KC_N,    KC_Q,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_G,    KC_X,    KC_J,    KC_K, CC_ADJM,                      CC_FUNQ,    KC_R,   KC_M,    KC_F,    KC_P,  CC_ALTZ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         KC_PMNS,  CC_GUIE, KC_RSFT,    CC_MONE,  KC_SPC, KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

  [_GAMING] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_ESC,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V, CC_ADJB,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LCTL, _______,  KC_SPC,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_NAV] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, KC_WH_D, KC_MS_U, KC_WH_U, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_PGDN, KC_PGUP, XXXXXXX, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX, XXXXXXX,                      KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, XXXXXXX, XXXXXXX, 
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_HOME,  KC_END, XXXXXXX, XXXXXXX, KC_LALT, 
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, KC_BTN1, KC_BTN2,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_NUM_QWERTY] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_GRV, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______, 
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_PEQL, 
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_SLSH, KC_BSLS, KC_LBRC, KC_RBRC, KC_MINS,                       KC_EQL,    KC_U,    KC_I,    KC_O,    KC_P, KC_LALT, 
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_NUM_ENGRAM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_LBRC, KC_PIPE,  KC_EQL, KC_HASH, KC_PLUS, KC_LABK,                      KC_RABK, KC_CIRC, KC_AMPR, KC_PERC, KC_ASTR, KC_RBRC, 
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCBR,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_RCBR, 
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,  KC_GRV, KC_TILD,  KC_DLR,   KC_AT, KC_SLSH,                      KC_PSLS,    KC_U,    KC_I,    KC_O,    KC_P, KC_LALT, 
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_ADJUST] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_VOLD, KC_VOLU, XXXXXXX, CC_DFQW,  QK_RBT, 
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX,                      KC_MPLY, KC_MPRV, KC_MNXT, XXXXXXX, CC_DFEN, KC_PSCR, 
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX,                      XXXXXXX, KC_BRID, KC_BRIU, XXXXXXX, CC_DFGA, KC_LALT, 
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_FUNCTION] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, 
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,   KC_F5,   KC_F6,   KC_F7,   KC_F8, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,   KC_F9,  KC_F10,  KC_F11,  KC_F12, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LALT, 
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  )
};

// Replace Shift+Backspace with Delete key
const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);

const key_override_t T_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_QUOT, KC_LPRN, ~(1 << _ENGRAM)); // ' -> (
const key_override_t Y_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_DQUO, KC_RPRN, ~(1 << _ENGRAM)); // " -> ^

const key_override_t G_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_COMM, KC_SCLN, ~(1 << _ENGRAM)); // , -> ;
const key_override_t H_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_DOT,  KC_COLN, ~(1 << _ENGRAM)); // . -> :

const key_override_t B_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_MINS, KC_UNDS, ~(1 << _ENGRAM)); // - -> _
const key_override_t N_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_QUES, KC_EXLM, ~(1 << _ENGRAM)); // ? -> !

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
    &delete_key_override,
    &T_override, &Y_override,
    &G_override, &H_override,
    &B_override, &N_override,
    NULL // Null terminate the array of overrides!
};

