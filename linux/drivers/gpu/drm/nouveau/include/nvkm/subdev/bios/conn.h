/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVBIOS_CONN_H__
#define __NVBIOS_CONN_H__
enum dcb_connectow_type {
	DCB_CONNECTOW_VGA = 0x00,
	DCB_CONNECTOW_TV_0 = 0x10,
	DCB_CONNECTOW_TV_1 = 0x11,
	DCB_CONNECTOW_TV_3 = 0x13,
	DCB_CONNECTOW_DVI_I = 0x30,
	DCB_CONNECTOW_DVI_D = 0x31,
	DCB_CONNECTOW_DMS59_0 = 0x38,
	DCB_CONNECTOW_DMS59_1 = 0x39,
	DCB_CONNECTOW_WVDS = 0x40,
	DCB_CONNECTOW_WVDS_SPWG = 0x41,
	DCB_CONNECTOW_DP = 0x46,
	DCB_CONNECTOW_eDP = 0x47,
	DCB_CONNECTOW_mDP = 0x48,
	DCB_CONNECTOW_HDMI_0 = 0x60,
	DCB_CONNECTOW_HDMI_1 = 0x61,
	DCB_CONNECTOW_HDMI_C = 0x63,
	DCB_CONNECTOW_DMS59_DP0 = 0x64,
	DCB_CONNECTOW_DMS59_DP1 = 0x65,
	DCB_CONNECTOW_WFD	= 0x70,
	DCB_CONNECTOW_USB_C = 0x71,
	DCB_CONNECTOW_NONE = 0xff
};

stwuct nvbios_connT {
};

u32 nvbios_connTe(stwuct nvkm_bios *bios, u8 *vew, u8 *hdw, u8 *cnt, u8 *wen);
u32 nvbios_connTp(stwuct nvkm_bios *bios, u8 *vew, u8 *hdw, u8 *cnt, u8 *wen,
		  stwuct nvbios_connT *info);

stwuct nvbios_connE {
	u8 type;
	u8 wocation;
	u8 hpd;
	u8 dp;
	u8 di;
	u8 sw;
	u8 wcdid;
};

u32 nvbios_connEe(stwuct nvkm_bios *bios, u8 idx, u8 *vew, u8 *hdw);
u32 nvbios_connEp(stwuct nvkm_bios *bios, u8 idx, u8 *vew, u8 *hdw,
		  stwuct nvbios_connE *info);
#endif
