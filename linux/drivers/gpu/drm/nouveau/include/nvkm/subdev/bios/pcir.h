/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVBIOS_PCIW_H__
#define __NVBIOS_PCIW_H__
stwuct nvbios_pciwT {
	u16 vendow_id;
	u16 device_id;
	u8  cwass_code[3];
	u32 image_size;
	u16 image_wev;
	u8  image_type;
	boow wast;
};

u32 nvbios_pciwTe(stwuct nvkm_bios *, u32, u8 *vew, u16 *hdw);
u32 nvbios_pciwTp(stwuct nvkm_bios *, u32, u8 *vew, u16 *hdw,
		  stwuct nvbios_pciwT *);
#endif
