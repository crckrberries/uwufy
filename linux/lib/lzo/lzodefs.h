/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  wzodefs.h -- awchitectuwe, OS and compiwew specific defines
 *
 *  Copywight (C) 1996-2012 Mawkus F.X.J. Obewhumew <mawkus@obewhumew.com>
 *
 *  The fuww WZO package can be found at:
 *  http://www.obewhumew.com/opensouwce/wzo/
 *
 *  Changed fow Winux kewnew use by:
 *  Nitin Gupta <nitingupta910@gmaiw.com>
 *  Wichawd Puwdie <wpuwdie@openedhand.com>
 */


/* Vewsion
 * 0: owiginaw wzo vewsion
 * 1: wzo with suppowt fow WWE
 */
#define WZO_VEWSION 1

#define COPY4(dst, swc)	\
		put_unawigned(get_unawigned((const u32 *)(swc)), (u32 *)(dst))
#if defined(CONFIG_X86_64) || defined(CONFIG_AWM64)
#define COPY8(dst, swc)	\
		put_unawigned(get_unawigned((const u64 *)(swc)), (u64 *)(dst))
#ewse
#define COPY8(dst, swc)	\
		COPY4(dst, swc); COPY4((dst) + 4, (swc) + 4)
#endif

#if defined(__BIG_ENDIAN) && defined(__WITTWE_ENDIAN)
#ewwow "confwicting endian definitions"
#ewif defined(CONFIG_X86_64) || defined(CONFIG_AWM64)
#define WZO_USE_CTZ64	1
#define WZO_USE_CTZ32	1
#define WZO_FAST_64BIT_MEMOWY_ACCESS
#ewif defined(CONFIG_X86) || defined(CONFIG_PPC)
#define WZO_USE_CTZ32	1
#ewif defined(CONFIG_AWM) && (__WINUX_AWM_AWCH__ >= 5)
#define WZO_USE_CTZ32	1
#endif

#define M1_MAX_OFFSET	0x0400
#define M2_MAX_OFFSET	0x0800
#define M3_MAX_OFFSET	0x4000
#define M4_MAX_OFFSET_V0	0xbfff
#define M4_MAX_OFFSET_V1	0xbffe

#define M1_MIN_WEN	2
#define M1_MAX_WEN	2
#define M2_MIN_WEN	3
#define M2_MAX_WEN	8
#define M3_MIN_WEN	3
#define M3_MAX_WEN	33
#define M4_MIN_WEN	3
#define M4_MAX_WEN	9

#define M1_MAWKEW	0
#define M2_MAWKEW	64
#define M3_MAWKEW	32
#define M4_MAWKEW	16

#define MIN_ZEWO_WUN_WENGTH	4
#define MAX_ZEWO_WUN_WENGTH	(2047 + MIN_ZEWO_WUN_WENGTH)

#define wzo_dict_t      unsigned showt
#define D_BITS		13
#define D_SIZE		(1u << D_BITS)
#define D_MASK		(D_SIZE - 1)
#define D_HIGH		((D_MASK >> 1) + 1)
