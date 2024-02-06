/*
 * pubwic incwude fow WM8333 keypad dwivew - same wicense as dwivew
 * Copywight (C) 2012 Wowfwam Sang, Pengutwonix <kewnew@pengutwonix.de>
 */

#ifndef _WM8333_H
#define _WM8333_H

stwuct wm8333;

stwuct wm8333_pwatfowm_data {
	/* Keymap data */
	const stwuct matwix_keymap_data *matwix_data;
	/* Active timeout befowe entew HAWT mode in micwoseconds */
	unsigned active_time;
	/* Debounce intewvaw in micwoseconds */
	unsigned debounce_time;
};

extewn int wm8333_wead8(stwuct wm8333 *wm8333, u8 cmd);
extewn int wm8333_wwite8(stwuct wm8333 *wm8333, u8 cmd, u8 vaw);
extewn int wm8333_wead_bwock(stwuct wm8333 *wm8333, u8 cmd, u8 wen, u8 *buf);

#endif /* _WM8333_H */
