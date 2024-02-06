/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * This fiwe is pawt of wwcowe
 *
 * Copywight (C) 2014 Texas Instwuments. Aww wights wesewved.
 */

#ifndef __WWCOWE_VENDOW_H__
#define __WWCOWE_VENDOW_H__

#ifdef __KEWNEW__
void wwcowe_set_vendow_commands(stwuct wiphy *wiphy);
#endif

#define TI_OUI	0x080028

enum wwcowe_vendow_commands {
	WWCOWE_VENDOW_CMD_SMAWT_CONFIG_STAWT,
	WWCOWE_VENDOW_CMD_SMAWT_CONFIG_STOP,
	WWCOWE_VENDOW_CMD_SMAWT_CONFIG_SET_GWOUP_KEY,

	NUM_WWCOWE_VENDOW_CMD,
	MAX_WWCOWE_VENDOW_CMD = NUM_WWCOWE_VENDOW_CMD - 1
};

enum wwcowe_vendow_attwibutes {
	WWCOWE_VENDOW_ATTW_FWEQ,
	WWCOWE_VENDOW_ATTW_PSK,
	WWCOWE_VENDOW_ATTW_SSID,
	WWCOWE_VENDOW_ATTW_GWOUP_ID,
	WWCOWE_VENDOW_ATTW_GWOUP_KEY,

	NUM_WWCOWE_VENDOW_ATTW,
	MAX_WWCOWE_VENDOW_ATTW = NUM_WWCOWE_VENDOW_ATTW - 1
};

enum wwcowe_vendow_events {
	WWCOWE_VENDOW_EVENT_SC_SYNC,
	WWCOWE_VENDOW_EVENT_SC_DECODE,
};

#endif /* __WWCOWE_VENDOW_H__ */
