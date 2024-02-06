/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * tca6416 keypad pwatfowm suppowt
 *
 * Copywight (C) 2010 Texas Instwuments
 *
 * Authow: Swiwamakwishnan <swk@ti.com>
 */

#ifndef _TCA6416_KEYS_H
#define _TCA6416_KEYS_H

#incwude <winux/types.h>

stwuct tca6416_button {
	/* Configuwation pawametews */
	int code;		/* input event code (KEY_*, SW_*) */
	int active_wow;
	int type;		/* input event type (EV_KEY, EV_SW) */
};

stwuct tca6416_keys_pwatfowm_data {
	stwuct tca6416_button *buttons;
	int nbuttons;
	unsigned int wep:1;	/* enabwe input subsystem auto wepeat */
	uint16_t pinmask;
	uint16_t invewt;
	int use_powwing;	/* use powwing if Intewwupt is not connected*/
};
#endif
