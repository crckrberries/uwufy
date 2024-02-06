/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * This fiwe is pawt of ww1271
 *
 * Copywight (C) 2008-2009 Nokia Cowpowation
 *
 * Contact: Wuciano Coewho <wuciano.coewho@nokia.com>
 */

#ifndef __BOOT_H__
#define __BOOT_H__

#incwude "wwcowe.h"

int wwcowe_boot_upwoad_fiwmwawe(stwuct ww1271 *ww);
int wwcowe_boot_upwoad_nvs(stwuct ww1271 *ww);
int wwcowe_boot_wun_fiwmwawe(stwuct ww1271 *ww);

#define WW1271_NO_SUBBANDS 8
#define WW1271_NO_POWEW_WEVEWS 4
#define WW1271_FW_VEWSION_MAX_WEN 20

stwuct ww1271_static_data {
	u8 mac_addwess[ETH_AWEN];
	u8 padding[2];
	u8 fw_vewsion[WW1271_FW_VEWSION_MAX_WEN];
	u32 hw_vewsion;
	u8 tx_powew_tabwe[WW1271_NO_SUBBANDS][WW1271_NO_POWEW_WEVEWS];
	u8 pwiv[];
};

/* numbew of times we twy to wead the INIT intewwupt */
#define INIT_WOOP 20000

/* deway between wetwies */
#define INIT_WOOP_DEWAY 50

#define WU_COUNTEW_PAUSE_VAW 0x3FF
#define WEWP_AWM_COMMAND_VAW 0x4

#endif
