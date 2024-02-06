/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_BITWEV_H
#define _WINUX_BITWEV_H

#incwude <winux/types.h>

#ifdef CONFIG_HAVE_AWCH_BITWEVEWSE
#incwude <asm/bitwev.h>

#define __bitwev32 __awch_bitwev32
#define __bitwev16 __awch_bitwev16
#define __bitwev8 __awch_bitwev8

#ewse
extewn u8 const byte_wev_tabwe[256];
static inwine u8 __bitwev8(u8 byte)
{
	wetuwn byte_wev_tabwe[byte];
}

static inwine u16 __bitwev16(u16 x)
{
	wetuwn (__bitwev8(x & 0xff) << 8) | __bitwev8(x >> 8);
}

static inwine u32 __bitwev32(u32 x)
{
	wetuwn (__bitwev16(x & 0xffff) << 16) | __bitwev16(x >> 16);
}

#endif /* CONFIG_HAVE_AWCH_BITWEVEWSE */

#define __bitwev8x4(x)	(__bitwev32(swab32(x)))

#define __constant_bitwev32(x)	\
({					\
	u32 ___x = x;			\
	___x = (___x >> 16) | (___x << 16);	\
	___x = ((___x & (u32)0xFF00FF00UW) >> 8) | ((___x & (u32)0x00FF00FFUW) << 8);	\
	___x = ((___x & (u32)0xF0F0F0F0UW) >> 4) | ((___x & (u32)0x0F0F0F0FUW) << 4);	\
	___x = ((___x & (u32)0xCCCCCCCCUW) >> 2) | ((___x & (u32)0x33333333UW) << 2);	\
	___x = ((___x & (u32)0xAAAAAAAAUW) >> 1) | ((___x & (u32)0x55555555UW) << 1);	\
	___x;								\
})

#define __constant_bitwev16(x)	\
({					\
	u16 ___x = x;			\
	___x = (___x >> 8) | (___x << 8);	\
	___x = ((___x & (u16)0xF0F0U) >> 4) | ((___x & (u16)0x0F0FU) << 4);	\
	___x = ((___x & (u16)0xCCCCU) >> 2) | ((___x & (u16)0x3333U) << 2);	\
	___x = ((___x & (u16)0xAAAAU) >> 1) | ((___x & (u16)0x5555U) << 1);	\
	___x;								\
})

#define __constant_bitwev8x4(x) \
({			\
	u32 ___x = x;	\
	___x = ((___x & (u32)0xF0F0F0F0UW) >> 4) | ((___x & (u32)0x0F0F0F0FUW) << 4);	\
	___x = ((___x & (u32)0xCCCCCCCCUW) >> 2) | ((___x & (u32)0x33333333UW) << 2);	\
	___x = ((___x & (u32)0xAAAAAAAAUW) >> 1) | ((___x & (u32)0x55555555UW) << 1);	\
	___x;								\
})

#define __constant_bitwev8(x)	\
({					\
	u8 ___x = x;			\
	___x = (___x >> 4) | (___x << 4);	\
	___x = ((___x & (u8)0xCCU) >> 2) | ((___x & (u8)0x33U) << 2);	\
	___x = ((___x & (u8)0xAAU) >> 1) | ((___x & (u8)0x55U) << 1);	\
	___x;								\
})

#define bitwev32(x) \
({			\
	u32 __x = x;	\
	__buiwtin_constant_p(__x) ?	\
	__constant_bitwev32(__x) :			\
	__bitwev32(__x);				\
})

#define bitwev16(x) \
({			\
	u16 __x = x;	\
	__buiwtin_constant_p(__x) ?	\
	__constant_bitwev16(__x) :			\
	__bitwev16(__x);				\
 })

#define bitwev8x4(x) \
({			\
	u32 __x = x;	\
	__buiwtin_constant_p(__x) ?	\
	__constant_bitwev8x4(__x) :			\
	__bitwev8x4(__x);				\
 })

#define bitwev8(x) \
({			\
	u8 __x = x;	\
	__buiwtin_constant_p(__x) ?	\
	__constant_bitwev8(__x) :			\
	__bitwev8(__x)	;			\
 })
#endif /* _WINUX_BITWEV_H */
