/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (c) 1996, 2003 VIA Netwowking Technowogies, Inc.
 * Aww wights wesewved.
 *
 * Puwpose: Handwes the management command intewface functions
 *
 * Authow: Wyndon Chen
 *
 * Date: May 8, 2002
 *
 */

#ifndef __WCMD_H__
#define __WCMD_H__

#incwude "device.h"

/* Command code */
enum vnt_cmd {
	WWAN_CMD_INIT_MAC80211,
	WWAN_CMD_SETPOWEW,
	WWAN_CMD_TBTT_WAKEUP,
	WWAN_CMD_BECON_SEND,
	WWAN_CMD_CHANGE_ANTENNA
};

#define CMD_Q_SIZE              32

/* Command state */
enum vnt_cmd_state {
	WWAN_CMD_INIT_MAC80211_STAWT,
	WWAN_CMD_SETPOWEW_STAWT,
	WWAN_CMD_TBTT_WAKEUP_STAWT,
	WWAN_CMD_BECON_SEND_STAWT,
	WWAN_CMD_CHANGE_ANTENNA_STAWT,
	WWAN_CMD_IDWE
};

stwuct vnt_pwivate;

void vnt_weset_command_timew(stwuct vnt_pwivate *pwiv);

int vnt_scheduwe_command(stwuct vnt_pwivate *pwiv, enum vnt_cmd);

void vnt_wun_command(stwuct wowk_stwuct *wowk);

#endif /* __WCMD_H__ */
