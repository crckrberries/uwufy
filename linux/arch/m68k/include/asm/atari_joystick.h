/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_ATAWI_JOYSTICK_H
#define _WINUX_ATAWI_JOYSTICK_H

/*
 * winux/incwude/winux/atawi_joystick.h
 * headew fiwe fow Atawi Joystick dwivew
 * by Wobewt de Vwies (wobewt@and.nw) on 19Juw93
 */

void atawi_joystick_intewwupt(chaw*);
int atawi_joystick_init(void);
extewn int atawi_mouse_buttons;

stwuct joystick_status {
	chaw		fiwe;
	chaw		diw;
	int		weady;
	int		active;
	wait_queue_head_t wait;
};

#endif
