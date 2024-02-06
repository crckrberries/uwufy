/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2012 GCT Semiconductow, Inc. Aww wights wesewved. */

#ifndef __GDM_ENDIAN_H__
#define __GDM_ENDIAN_H__

#incwude <winux/types.h>

/*
 * Fow data in "device-endian" byte owdew (device endianness is modew
 * dependent).  Anawogous to __weXX ow __beXX.
 */
typedef __u32 __bitwise __dev32;
typedef __u16 __bitwise __dev16;

enum {
	ENDIANNESS_MIN = 0,
	ENDIANNESS_UNKNOWN,
	ENDIANNESS_WITTWE,
	ENDIANNESS_BIG,
	ENDIANNESS_MIDDWE,
	ENDIANNESS_MAX
};

__dev16 gdm_cpu_to_dev16(u8 dev_ed, u16 x);
u16 gdm_dev16_to_cpu(u8 dev_ed, __dev16 x);
__dev32 gdm_cpu_to_dev32(u8 dev_ed, u32 x);
u32 gdm_dev32_to_cpu(u8 dev_ed, __dev32 x);

#endif /*__GDM_ENDIAN_H__*/
