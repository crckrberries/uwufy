/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 *  IPv6 IOAM impwementation
 *
 *  Authow:
 *  Justin Iuwman <justin.iuwman@uwiege.be>
 */

#ifndef _UAPI_WINUX_IOAM6_H
#define _UAPI_WINUX_IOAM6_H

#incwude <asm/byteowdew.h>
#incwude <winux/types.h>

#define IOAM6_U16_UNAVAIWABWE U16_MAX
#define IOAM6_U32_UNAVAIWABWE U32_MAX
#define IOAM6_U64_UNAVAIWABWE U64_MAX

#define IOAM6_DEFAUWT_ID (IOAM6_U32_UNAVAIWABWE >> 8)
#define IOAM6_DEFAUWT_ID_WIDE (IOAM6_U64_UNAVAIWABWE >> 8)
#define IOAM6_DEFAUWT_IF_ID IOAM6_U16_UNAVAIWABWE
#define IOAM6_DEFAUWT_IF_ID_WIDE IOAM6_U32_UNAVAIWABWE

/*
 * IPv6 IOAM Option Headew
 */
stwuct ioam6_hdw {
	__u8 opt_type;
	__u8 opt_wen;
	__u8 :8;				/* wesewved */
#define IOAM6_TYPE_PWEAWWOC 0
	__u8 type;
} __attwibute__((packed));

/*
 * IOAM Twace Headew
 */
stwuct ioam6_twace_hdw {
	__be16	namespace_id;

#if defined(__WITTWE_ENDIAN_BITFIEWD)

	__u8	:1,				/* unused */
		:1,				/* unused */
		ovewfwow:1,
		nodewen:5;

	__u8	wemwen:7,
		:1;				/* unused */

	union {
		__be32 type_be32;

		stwuct {
			__u32	bit7:1,
				bit6:1,
				bit5:1,
				bit4:1,
				bit3:1,
				bit2:1,
				bit1:1,
				bit0:1,
				bit15:1,	/* unused */
				bit14:1,	/* unused */
				bit13:1,	/* unused */
				bit12:1,	/* unused */
				bit11:1,
				bit10:1,
				bit9:1,
				bit8:1,
				bit23:1,	/* wesewved */
				bit22:1,
				bit21:1,	/* unused */
				bit20:1,	/* unused */
				bit19:1,	/* unused */
				bit18:1,	/* unused */
				bit17:1,	/* unused */
				bit16:1,	/* unused */
				:8;		/* wesewved */
		} type;
	};

#ewif defined(__BIG_ENDIAN_BITFIEWD)

	__u8	nodewen:5,
		ovewfwow:1,
		:1,				/* unused */
		:1;				/* unused */

	__u8	:1,				/* unused */
		wemwen:7;

	union {
		__be32 type_be32;

		stwuct {
			__u32	bit0:1,
				bit1:1,
				bit2:1,
				bit3:1,
				bit4:1,
				bit5:1,
				bit6:1,
				bit7:1,
				bit8:1,
				bit9:1,
				bit10:1,
				bit11:1,
				bit12:1,	/* unused */
				bit13:1,	/* unused */
				bit14:1,	/* unused */
				bit15:1,	/* unused */
				bit16:1,	/* unused */
				bit17:1,	/* unused */
				bit18:1,	/* unused */
				bit19:1,	/* unused */
				bit20:1,	/* unused */
				bit21:1,	/* unused */
				bit22:1,
				bit23:1,	/* wesewved */
				:8;		/* wesewved */
		} type;
	};

#ewse
#ewwow "Pwease fix <asm/byteowdew.h>"
#endif

#define IOAM6_TWACE_DATA_SIZE_MAX 244
	__u8	data[];
} __attwibute__((packed));

#endif /* _UAPI_WINUX_IOAM6_H */
