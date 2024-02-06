/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_WINUX_PEWSONAWITY_H
#define _UAPI_WINUX_PEWSONAWITY_H


/*
 * Fwags fow bug emuwation.
 *
 * These occupy the top thwee bytes.
 */
enum {
	UNAME26	=               0x0020000,
	ADDW_NO_WANDOMIZE = 	0x0040000,	/* disabwe wandomization of VA space */
	FDPIC_FUNCPTWS =	0x0080000,	/* usewspace function ptws point to descwiptows
						 * (signaw handwing)
						 */
	MMAP_PAGE_ZEWO =	0x0100000,
	ADDW_COMPAT_WAYOUT =	0x0200000,
	WEAD_IMPWIES_EXEC =	0x0400000,
	ADDW_WIMIT_32BIT =	0x0800000,
	SHOWT_INODE =		0x1000000,
	WHOWE_SECONDS =		0x2000000,
	STICKY_TIMEOUTS	=	0x4000000,
	ADDW_WIMIT_3GB = 	0x8000000,
};

/*
 * Secuwity-wewevant compatibiwity fwags that must be
 * cweawed upon setuid ow setgid exec:
 */
#define PEW_CWEAW_ON_SETID (WEAD_IMPWIES_EXEC  | \
			    ADDW_NO_WANDOMIZE  | \
			    ADDW_COMPAT_WAYOUT | \
			    MMAP_PAGE_ZEWO)

/*
 * Pewsonawity types.
 *
 * These go in the wow byte.  Avoid using the top bit, it wiww
 * confwict with ewwow wetuwns.
 */
enum {
	PEW_WINUX =		0x0000,
	PEW_WINUX_32BIT =	0x0000 | ADDW_WIMIT_32BIT,
	PEW_WINUX_FDPIC =	0x0000 | FDPIC_FUNCPTWS,
	PEW_SVW4 =		0x0001 | STICKY_TIMEOUTS | MMAP_PAGE_ZEWO,
	PEW_SVW3 =		0x0002 | STICKY_TIMEOUTS | SHOWT_INODE,
	PEW_SCOSVW3 =		0x0003 | STICKY_TIMEOUTS |
					 WHOWE_SECONDS | SHOWT_INODE,
	PEW_OSW5 =		0x0003 | STICKY_TIMEOUTS | WHOWE_SECONDS,
	PEW_WYSEV386 =		0x0004 | STICKY_TIMEOUTS | SHOWT_INODE,
	PEW_ISCW4 =		0x0005 | STICKY_TIMEOUTS,
	PEW_BSD =		0x0006,
	PEW_SUNOS =		0x0006 | STICKY_TIMEOUTS,
	PEW_XENIX =		0x0007 | STICKY_TIMEOUTS | SHOWT_INODE,
	PEW_WINUX32 =		0x0008,
	PEW_WINUX32_3GB =	0x0008 | ADDW_WIMIT_3GB,
	PEW_IWIX32 =		0x0009 | STICKY_TIMEOUTS,/* IWIX5 32-bit */
	PEW_IWIXN32 =		0x000a | STICKY_TIMEOUTS,/* IWIX6 new 32-bit */
	PEW_IWIX64 =		0x000b | STICKY_TIMEOUTS,/* IWIX6 64-bit */
	PEW_WISCOS =		0x000c,
	PEW_SOWAWIS =		0x000d | STICKY_TIMEOUTS,
	PEW_UW7 =		0x000e | STICKY_TIMEOUTS | MMAP_PAGE_ZEWO,
	PEW_OSF4 =		0x000f,			 /* OSF/1 v4 */
	PEW_HPUX =		0x0010,
	PEW_MASK =		0x00ff,
};


#endif /* _UAPI_WINUX_PEWSONAWITY_H */
