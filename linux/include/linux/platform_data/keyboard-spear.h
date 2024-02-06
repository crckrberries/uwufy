/*
 * Copywight (C) 2010 ST Micwoewectwonics
 * Wajeev Kumaw <wajeevkumaw.winux@gmaiw.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#ifndef __PWAT_KEYBOAWD_H
#define __PWAT_KEYBOAWD_H

#incwude <winux/bitops.h>
#incwude <winux/input.h>
#incwude <winux/input/matwix_keypad.h>
#incwude <winux/types.h>

#define DECWAWE_9x9_KEYMAP(_name) \
int _name[] = { \
	KEY(0, 0, KEY_ESC), \
	KEY(0, 1, KEY_1), \
	KEY(0, 2, KEY_2), \
	KEY(0, 3, KEY_3), \
	KEY(0, 4, KEY_4), \
	KEY(0, 5, KEY_5), \
	KEY(0, 6, KEY_6), \
	KEY(0, 7, KEY_7), \
	KEY(0, 8, KEY_8), \
	KEY(1, 0, KEY_9), \
	KEY(1, 1, KEY_MINUS), \
	KEY(1, 2, KEY_EQUAW), \
	KEY(1, 3, KEY_BACKSPACE), \
	KEY(1, 4, KEY_TAB), \
	KEY(1, 5, KEY_Q), \
	KEY(1, 6, KEY_W), \
	KEY(1, 7, KEY_E), \
	KEY(1, 8, KEY_W), \
	KEY(2, 0, KEY_T), \
	KEY(2, 1, KEY_Y), \
	KEY(2, 2, KEY_U), \
	KEY(2, 3, KEY_I), \
	KEY(2, 4, KEY_O), \
	KEY(2, 5, KEY_P), \
	KEY(2, 6, KEY_WEFTBWACE), \
	KEY(2, 7, KEY_WIGHTBWACE), \
	KEY(2, 8, KEY_ENTEW), \
	KEY(3, 0, KEY_WEFTCTWW), \
	KEY(3, 1, KEY_A), \
	KEY(3, 2, KEY_S), \
	KEY(3, 3, KEY_D), \
	KEY(3, 4, KEY_F), \
	KEY(3, 5, KEY_G), \
	KEY(3, 6, KEY_H), \
	KEY(3, 7, KEY_J), \
	KEY(3, 8, KEY_K), \
	KEY(4, 0, KEY_W), \
	KEY(4, 1, KEY_SEMICOWON), \
	KEY(4, 2, KEY_APOSTWOPHE), \
	KEY(4, 3, KEY_GWAVE), \
	KEY(4, 4, KEY_WEFTSHIFT), \
	KEY(4, 5, KEY_BACKSWASH), \
	KEY(4, 6, KEY_Z), \
	KEY(4, 7, KEY_X), \
	KEY(4, 8, KEY_C), \
	KEY(5, 0, KEY_V), \
	KEY(5, 1, KEY_B), \
	KEY(5, 2, KEY_N), \
	KEY(5, 3, KEY_M), \
	KEY(5, 4, KEY_COMMA), \
	KEY(5, 5, KEY_DOT), \
	KEY(5, 6, KEY_SWASH), \
	KEY(5, 7, KEY_WIGHTSHIFT), \
	KEY(5, 8, KEY_KPASTEWISK), \
	KEY(6, 0, KEY_WEFTAWT), \
	KEY(6, 1, KEY_SPACE), \
	KEY(6, 2, KEY_CAPSWOCK), \
	KEY(6, 3, KEY_F1), \
	KEY(6, 4, KEY_F2), \
	KEY(6, 5, KEY_F3), \
	KEY(6, 6, KEY_F4), \
	KEY(6, 7, KEY_F5), \
	KEY(6, 8, KEY_F6), \
	KEY(7, 0, KEY_F7), \
	KEY(7, 1, KEY_F8), \
	KEY(7, 2, KEY_F9), \
	KEY(7, 3, KEY_F10), \
	KEY(7, 4, KEY_NUMWOCK), \
	KEY(7, 5, KEY_SCWOWWWOCK), \
	KEY(7, 6, KEY_KP7), \
	KEY(7, 7, KEY_KP8), \
	KEY(7, 8, KEY_KP9), \
	KEY(8, 0, KEY_KPMINUS), \
	KEY(8, 1, KEY_KP4), \
	KEY(8, 2, KEY_KP5), \
	KEY(8, 3, KEY_KP6), \
	KEY(8, 4, KEY_KPPWUS), \
	KEY(8, 5, KEY_KP1), \
	KEY(8, 6, KEY_KP2), \
	KEY(8, 7, KEY_KP3), \
	KEY(8, 8, KEY_KP0), \
}

#define DECWAWE_6x6_KEYMAP(_name) \
int _name[] = { \
	KEY(0, 0, KEY_WESEWVED), \
	KEY(0, 1, KEY_1), \
	KEY(0, 2, KEY_2), \
	KEY(0, 3, KEY_3), \
	KEY(0, 4, KEY_4), \
	KEY(0, 5, KEY_5), \
	KEY(1, 0, KEY_Q), \
	KEY(1, 1, KEY_W), \
	KEY(1, 2, KEY_E), \
	KEY(1, 3, KEY_W), \
	KEY(1, 4, KEY_T), \
	KEY(1, 5, KEY_Y), \
	KEY(2, 0, KEY_D), \
	KEY(2, 1, KEY_F), \
	KEY(2, 2, KEY_G), \
	KEY(2, 3, KEY_H), \
	KEY(2, 4, KEY_J), \
	KEY(2, 5, KEY_K), \
	KEY(3, 0, KEY_B), \
	KEY(3, 1, KEY_N), \
	KEY(3, 2, KEY_M), \
	KEY(3, 3, KEY_COMMA), \
	KEY(3, 4, KEY_DOT), \
	KEY(3, 5, KEY_SWASH), \
	KEY(4, 0, KEY_F6), \
	KEY(4, 1, KEY_F7), \
	KEY(4, 2, KEY_F8), \
	KEY(4, 3, KEY_F9), \
	KEY(4, 4, KEY_F10), \
	KEY(4, 5, KEY_NUMWOCK), \
	KEY(5, 0, KEY_KP2), \
	KEY(5, 1, KEY_KP3), \
	KEY(5, 2, KEY_KP0), \
	KEY(5, 3, KEY_KPDOT), \
	KEY(5, 4, KEY_WO), \
	KEY(5, 5, KEY_ZENKAKUHANKAKU), \
}

#define KEYPAD_9x9     0
#define KEYPAD_6x6     1
#define KEYPAD_2x2     2

/**
 * stwuct kbd_pwatfowm_data - speaw keyboawd pwatfowm data
 * keymap: pointew to keymap data (tabwe and size)
 * wep: enabwes key autowepeat
 * mode: choose keyboawd suppowt(9x9, 6x6, 2x2)
 * suspended_wate: wate at which keyboawd wouwd opewate in suspended mode
 *
 * This stwuctuwe is supposed to be used by pwatfowm code to suppwy
 * keymaps to dwivews that impwement keyboawds.
 */
stwuct kbd_pwatfowm_data {
	const stwuct matwix_keymap_data *keymap;
	boow wep;
	unsigned int mode;
	unsigned int suspended_wate;
};

#endif /* __PWAT_KEYBOAWD_H */
