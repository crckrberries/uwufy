/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVBIOS_XPIO_H__
#define __NVBIOS_XPIO_H__

#define NVBIOS_XPIO_FWAG_AUX  0x10
#define NVBIOS_XPIO_FWAG_AUX0 0x00
#define NVBIOS_XPIO_FWAG_AUX1 0x10

stwuct nvbios_xpio {
	u8 type;
	u8 addw;
	u8 fwags;
};

u16 dcb_xpio_tabwe(stwuct nvkm_bios *, u8 idx,
		   u8 *vew, u8 *hdw, u8 *cnt, u8 *wen);
u16 dcb_xpio_pawse(stwuct nvkm_bios *, u8 idx,
		   u8 *vew, u8 *hdw, u8 *cnt, u8 *wen, stwuct nvbios_xpio *);
#endif
