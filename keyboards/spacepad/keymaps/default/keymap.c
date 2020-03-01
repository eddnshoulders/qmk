/*
Copyright 2018 Sekigon

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

#include QMK_KEYBOARD_H
#include "app_ble_func.h"
#include "nrf_log.h"
#include "nrf_gpio.h"

extern keymap_config_t keymap_config;

/*
enum spacepad_layers {
  _QWERTY,
  _ISO,
  _LOWER,
  _RAISE,
  _ADJUST,
  _THUMB_ALT,
};
*/

enum custom_keycodes {
  AD_WO_L = SAFE_RANGE, /* Start advertising without whitelist  */
  BLE_DIS,              /* Disable BLE HID sending              */
  BLE_EN,               /* Enable BLE HID sending               */
  USB_DIS,              /* Disable USB HID sending              */
  USB_EN,               /* Enable USB HID sending               */
  DELBNDS,              /* Delete all bonding                   */
  ADV_ID0,              /* Start advertising to PeerID 0        */
  ADV_ID1,              /* Start advertising to PeerID 1        */
  ADV_ID2,              /* Start advertising to PeerID 2        */
  ADV_ID3,              /* Start advertising to PeerID 3        */
  ADV_ID4,              /* Start advertising to PeerID 4        */
  BATT_LV,              /* Display battery level in milli volts */
  DEL_ID0,              /* Delete bonding of PeerID 0           */
  DEL_ID1,              /* Delete bonding of PeerID 1           */
  DEL_ID2,              /* Delete bonding of PeerID 2           */
  DEL_ID3,              /* Delete bonding of PeerID 3           */
  DEL_ID4,              /* Delete bonding of PeerID 4           */
  ENT_DFU,              /* Start bootloader                     */
  ENT_SLP,              /* Deep sleep mode                      */

  // jian keycodes
  QWERTY,
  PLOVER,
  EXT_PLV,
  SH_TG, // not implemented
  BLE_DBG,
};



#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

#define TG_ISO  TG(_ISO)
#define TG_THMB TG(_THUMB_ALT)

#define RBR_RGU MT(MOD_RGUI, KC_RBRC)
#define F12_RGU MT(MOD_RGUI, KC_F12)
#define PLS_LCT MT(MOD_LCTL, KC_PPLS)
#define EQL_LCT MT(MOD_LCTL, KC_PEQL)
#define APP_LCT MT(MOD_LCTL, KC_APP)
#define EQL_RCT MT(MOD_RCTL, KC_PEQL)
#define QUO_RCT MT(MOD_RCTL, KC_QUOT)
#define APP_RCT MT(MOD_RCTL, KC_APP)
#define MIN_RCT MT(MOD_RCTL, KC_MINS)
#define EQL_LAL MT(MOD_LALT, KC_EQL)
#define BSL_RAL MT(MOD_RALT, KC_BSLS)

#define NBS_LCT MT(MOD_LCTL, KC_NUBS)
#define BSH_LAL MT(MOD_LALT, KC_BSLS)
#define APP_RAL MT(MOD_RALT, KC_APP)

#define BSP_LSH MT(MOD_LSFT, KC_BSPC)
#define SPC_RSH MT(MOD_RSFT, KC_SPC)
#define DEL_RSE LT(_RAISE, KC_DEL)
#define TAB_RSE LT(_RAISE, KC_TAB)
#define ENT_LWR LT(_LOWER, KC_ENT)
#define ESC_LWR LT(_LOWER, KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT(
  KC_ESC, KC_LSHIFT, KC_DEL, \
  KC_LCTRL, KC_SPACE, KC_HOME, \
                               KC_RETURN)
};

/*
uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
*/

// adafruit bootloader
#define DFU_DBL_RESET_MAGIC             0x5A1AD5
#define DFU_DBL_RESET_MEM               0x20007F7C
#define DFU_MAGIC_UF2_RESET             0x57
uint32_t* dbl_reset_mem = ((uint32_t*)  DFU_DBL_RESET_MEM );
void uf2_jump(void) {
  NRF_POWER->GPREGRET = DFU_MAGIC_UF2_RESET;
  *dbl_reset_mem = DFU_DBL_RESET_MAGIC;
  NRF_POWER->RESETREAS |= POWER_RESETREAS_RESETPIN_Msk;
  NVIC_SystemReset();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  char str[16];
  if (record->event.pressed) {
    switch (keycode) {
    case DELBNDS:
      delete_bonds();
      return false;
    case AD_WO_L:
      restart_advertising_wo_whitelist();
      return false;
    case USB_EN:
      set_usb_enabled(true);
      return false;
      break;
    case USB_DIS:
      set_usb_enabled(false);
      return false;
      break;
    case BLE_EN:
      set_ble_enabled(true);
      return false;
      break;
    case BLE_DIS:
      set_ble_enabled(false);
      return false;
      break;
    case ADV_ID0:
      NRF_LOG_INFO("Restart advertising ID: %d", 0);
      restart_advertising_id(0);
      return false;
    case ADV_ID1:
      NRF_LOG_INFO("Restart advertising ID: %d", 1);
      restart_advertising_id(1);
      return false;
    case ADV_ID2:
      NRF_LOG_INFO("Restart advertising ID: %d", 2);
      restart_advertising_id(2);
      return false;
    case ADV_ID3:
      NRF_LOG_INFO("Restart advertising ID: %d", 3);
      restart_advertising_id(3);
      return false;
    case ADV_ID4:
      restart_advertising_id(4);
      return false;
    case DEL_ID0:
      delete_bond_id(0);
      return false;
    case DEL_ID1:
      delete_bond_id(1);
      return false;
    case DEL_ID2:
      delete_bond_id(2);
      return false;
    case DEL_ID3:
      delete_bond_id(3);
      return false;
    case BATT_LV:
      sprintf(str, "%4dmV", get_vcc());
      send_string(str);
      return false;
    case ENT_DFU: case RESET:
      bootloader_jump();
      return false;
    case DEBUG:
      uf2_jump();
      return false;
    case BLE_DBG:
      set_ble_enabled(true);
      //delete_bonds(); // causes reset
      restart_advertising_wo_whitelist();
      return false;
    #ifdef BACKLIGHT_PIN
    case BL_INC:
      nrf_gpio_pin_set(BACKLIGHT_PIN);
      return false;
    case BL_DEC:
      nrf_gpio_pin_clear(BACKLIGHT_PIN);
      return false;
    #endif
    }
  }
  else if (!record->event.pressed) {
    switch (keycode) {
    case ENT_SLP:
      sleep_mode_enter();
      return false;
    }

  }
  return true;
}
;
