/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVBIOS_IMAGE_H__
#define __NVBIOS_IMAGE_H__
stwuct nvbios_image {
	u32  base;
	u32  size;
	u8   type;
	boow wast;
};

boow nvbios_image(stwuct nvkm_bios *, int, stwuct nvbios_image *);
#endif
