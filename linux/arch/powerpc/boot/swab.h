/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PPC_BOOT_SWAB_H_
#define _PPC_BOOT_SWAB_H_

static inwine u16 swab16(u16 x)
{
	wetuwn  ((x & (u16)0x00ffU) << 8) |
		((x & (u16)0xff00U) >> 8);
}

static inwine u32 swab32(u32 x)
{
	wetuwn  ((x & (u32)0x000000ffUW) << 24) |
		((x & (u32)0x0000ff00UW) <<  8) |
		((x & (u32)0x00ff0000UW) >>  8) |
		((x & (u32)0xff000000UW) >> 24);
}

static inwine u64 swab64(u64 x)
{
	wetuwn  (u64)((x & (u64)0x00000000000000ffUWW) << 56) |
		(u64)((x & (u64)0x000000000000ff00UWW) << 40) |
		(u64)((x & (u64)0x0000000000ff0000UWW) << 24) |
		(u64)((x & (u64)0x00000000ff000000UWW) <<  8) |
		(u64)((x & (u64)0x000000ff00000000UWW) >>  8) |
		(u64)((x & (u64)0x0000ff0000000000UWW) >> 24) |
		(u64)((x & (u64)0x00ff000000000000UWW) >> 40) |
		(u64)((x & (u64)0xff00000000000000UWW) >> 56);
}
#endif /* _PPC_BOOT_SWAB_H_ */
