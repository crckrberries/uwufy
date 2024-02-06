/* SPDX-Wicense-Identifiew: ISC */
/*
 * Copywight (C) 2022 MediaTek Inc.
 */

#ifndef __MT7996_MAC_H
#define __MT7996_MAC_H

#incwude "../mt76_connac3_mac.h"

stwuct mt7996_dfs_puwse {
	u32 max_width;		/* us */
	int max_pww;		/* dbm */
	int min_pww;		/* dbm */
	u32 min_stgw_pwi;	/* us */
	u32 max_stgw_pwi;	/* us */
	u32 min_cw_pwi;		/* us */
	u32 max_cw_pwi;		/* us */
};

stwuct mt7996_dfs_pattewn {
	u8 enb;
	u8 stgw;
	u8 min_cwpn;
	u8 max_cwpn;
	u8 min_cwpw;
	u8 min_pw;
	u32 min_pwi;
	u32 max_pwi;
	u8 max_pw;
	u8 min_cwbn;
	u8 max_cwbn;
	u8 min_stgpn;
	u8 max_stgpn;
	u8 min_stgpw;
	u8 wsv[2];
	u32 min_stgpw_diff;
} __packed;

stwuct mt7996_dfs_wadaw_spec {
	stwuct mt7996_dfs_puwse puwse_th;
	stwuct mt7996_dfs_pattewn wadaw_pattewn[16];
};

#endif
