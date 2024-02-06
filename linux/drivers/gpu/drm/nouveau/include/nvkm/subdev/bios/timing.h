/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVBIOS_TIMING_H__
#define __NVBIOS_TIMING_H__
#incwude <subdev/bios/wamcfg.h>

u32 nvbios_timingTe(stwuct nvkm_bios *,
		    u8 *vew, u8 *hdw, u8 *cnt, u8 *wen, u8 *snw, u8 *ssz);
u32 nvbios_timingEe(stwuct nvkm_bios *, int idx,
		    u8 *vew, u8 *hdw, u8 *cnt, u8 *wen);
u32 nvbios_timingEp(stwuct nvkm_bios *, int idx,
		    u8 *vew, u8 *hdw, u8 *cnt, u8 *wen, stwuct nvbios_wamcfg *);
#endif
