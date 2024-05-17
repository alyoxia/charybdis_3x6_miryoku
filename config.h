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
#pragma once

#ifdef VIA_ENABLE
/* VIA configuration. */
#    define DYNAMIC_KEYMAP_LAYER_COUNT 6
#endif // VIA_ENABLE

#ifndef __arm__
/* Disable unused features. */
#    define NO_ACTION_ONESHOT
#endif // __arm__

#define SPLIT_LAYER_STATE_ENABLE  // comm overhead
#define SPLIT_MODS_ENABLE
#define SPLIT_LED_STATE_ENABLE

#define CAPS_WORD_INVERT_ON_SHIFT

// Home row mods settings
#define TAPPING_TERM 200

/**
 * Prevent normal rollover on alphas from accidentally triggering mods.
 *
 * Ignores key presses that interrupt a mod-tap.  Must-have for Home Row mod.
 *
 * Without `IGNORE_MOD_TAP_INTERRUPT`, within `TAPPING_TERM`:
 *   Mod(a)🠗 e🠗 Mod(a)🠕 e🠕 ➞ Mod+e
 * With `IGNORE_MOD_TAP_INTERRUPT`, within `TAPPING_TERM`:
 *   Mod(a)🠗 e🠗 Mod(a)🠕 e🠕 ➞ ae
 */
#define IGNORE_MOD_TAP_INTERRUPT

/* Charybdis-specific features. */

#ifdef COMBO_ENABLE
    #define COMBO_COUNT 9
    #define COMBO_TERM 20
    #define COMBO_ONLY_FROM_LAYER 0
#endif

#ifdef POINTING_DEVICE_ENABLE

//#define CHARYBDIS_DRAGSCROLL_REVERSE_Y      // mimic up/down movement: scroll towards drag

// Drag-scroll changes DPI on activation, but this causes issues,
// better keep both identical (400).  So have to compensate drag-scroll divider
//  (`CHARYBDIS_DRAGSCROLL_BUFFER_SIZE`)
//
// #define CHARYBDIS_MINIMUM_DEFAULT_DPI 400        // default(400)
// #define CHARYBDIS_MINIMUM_SNIPING_DPI 200        // default(200)
// #define CHARYBDIS_DEFAULT_DPI_CONFIG_STEP 200    // default(200)
// #define CHARYBDIS_SNIPING_DPI_CONFIG_STEP 100    // default(100)
#define CHARYBDIS_DRAGSCROLL_DPI 400                // default(100)
#define CHARYBDIS_DRAGSCROLL_BUFFER_SIZE 20         // default(6)

// Send coalesced events with scroll values above ±1 (vs queueing ±1 events)?
#define CHARYBDIS_DRAGSCROLL_SEND_COALESCE

// If need, reduce mouse events frequency to cope with MCU load;
// note that it delays (but smoothens) drag-scrolling, particularly when
// queued (ie. `CHARYBDIS_DRAGSCROLL_SEND_COALESCE` undefined).
// #undef  POINTING_DEVICE_TASK_THROTTLE_MS
// #define POINTING_DEVICE_TASK_THROTTLE_MS 5

// For "maccel" configs, see `keymap.c` file.

#define EECONFIG_USER_DATA_SIZE 20

#endif // POINTING_DEVICE_ENABLE
