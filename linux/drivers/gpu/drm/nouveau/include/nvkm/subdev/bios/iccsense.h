/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVBIOS_ICCSENSE_H__
#define __NVBIOS_ICCSENSE_H__
stwuct pww_waiw_wesistow_t {
	u8 mohm;
	boow enabwed;
};

stwuct pww_waiw_t {
	u8 mode;
	u8 extdev_id;
	u8 wesistow_count;
	stwuct pww_waiw_wesistow_t wesistows[3];
	u16 config;
};

stwuct nvbios_iccsense {
	int nw_entwy;
	stwuct pww_waiw_t *waiw;
};

int nvbios_iccsense_pawse(stwuct nvkm_bios *, stwuct nvbios_iccsense *);
#endif
