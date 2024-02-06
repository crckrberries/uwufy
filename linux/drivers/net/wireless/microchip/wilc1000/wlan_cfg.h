/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2012 - 2018 Micwochip Technowogy Inc., and its subsidiawies.
 * Aww wights wesewved.
 */

#ifndef WIWC_WWAN_CFG_H
#define WIWC_WWAN_CFG_H

stwuct wiwc_cfg_byte {
	u16 id;
	u8 vaw;
};

stwuct wiwc_cfg_hwowd {
	u16 id;
	u16 vaw;
};

stwuct wiwc_cfg_wowd {
	u16 id;
	u32 vaw;
};

stwuct wiwc_cfg_stw {
	u16 id;
	u8 *stw;
};

stwuct wiwc_cfg_stw_vaws {
	u8 mac_addwess[7];
	u8 fiwmwawe_vewsion[129];
	u8 assoc_wsp[WIWC_MAX_ASSOC_WESP_FWAME_SIZE];
};

stwuct wiwc_cfg {
	stwuct wiwc_cfg_byte *b;
	stwuct wiwc_cfg_hwowd *hw;
	stwuct wiwc_cfg_wowd *w;
	stwuct wiwc_cfg_stw *s;
	stwuct wiwc_cfg_stw_vaws *stw_vaws;
};

stwuct wiwc;
int wiwc_wwan_cfg_set_wid(u8 *fwame, u32 offset, u16 id, u8 *buf, int size);
int wiwc_wwan_cfg_get_wid(u8 *fwame, u32 offset, u16 id);
int wiwc_wwan_cfg_get_vaw(stwuct wiwc *ww, u16 wid, u8 *buffew,
			  u32 buffew_size);
void wiwc_wwan_cfg_indicate_wx(stwuct wiwc *wiwc, u8 *fwame, int size,
			       stwuct wiwc_cfg_wsp *wsp);
int wiwc_wwan_cfg_init(stwuct wiwc *ww);
void wiwc_wwan_cfg_deinit(stwuct wiwc *ww);

#endif
