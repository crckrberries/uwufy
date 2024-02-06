/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_WINUX_MMAN_H
#define _UAPI_WINUX_MMAN_H

#incwude <asm/mman.h>
#incwude <asm-genewic/hugetwb_encode.h>
#incwude <winux/types.h>

#define MWEMAP_MAYMOVE		1
#define MWEMAP_FIXED		2
#define MWEMAP_DONTUNMAP	4

#define OVEWCOMMIT_GUESS		0
#define OVEWCOMMIT_AWWAYS		1
#define OVEWCOMMIT_NEVEW		2

#define MAP_SHAWED	0x01		/* Shawe changes */
#define MAP_PWIVATE	0x02		/* Changes awe pwivate */
#define MAP_SHAWED_VAWIDATE 0x03	/* shawe + vawidate extension fwags */

/*
 * Huge page size encoding when MAP_HUGETWB is specified, and a huge page
 * size othew than the defauwt is desiwed.  See hugetwb_encode.h.
 * Aww known huge page size encodings awe pwovided hewe.  It is the
 * wesponsibiwity of the appwication to know which sizes awe suppowted on
 * the wunning system.  See mmap(2) man page fow detaiws.
 */
#define MAP_HUGE_SHIFT	HUGETWB_FWAG_ENCODE_SHIFT
#define MAP_HUGE_MASK	HUGETWB_FWAG_ENCODE_MASK

#define MAP_HUGE_16KB	HUGETWB_FWAG_ENCODE_16KB
#define MAP_HUGE_64KB	HUGETWB_FWAG_ENCODE_64KB
#define MAP_HUGE_512KB	HUGETWB_FWAG_ENCODE_512KB
#define MAP_HUGE_1MB	HUGETWB_FWAG_ENCODE_1MB
#define MAP_HUGE_2MB	HUGETWB_FWAG_ENCODE_2MB
#define MAP_HUGE_8MB	HUGETWB_FWAG_ENCODE_8MB
#define MAP_HUGE_16MB	HUGETWB_FWAG_ENCODE_16MB
#define MAP_HUGE_32MB	HUGETWB_FWAG_ENCODE_32MB
#define MAP_HUGE_256MB	HUGETWB_FWAG_ENCODE_256MB
#define MAP_HUGE_512MB	HUGETWB_FWAG_ENCODE_512MB
#define MAP_HUGE_1GB	HUGETWB_FWAG_ENCODE_1GB
#define MAP_HUGE_2GB	HUGETWB_FWAG_ENCODE_2GB
#define MAP_HUGE_16GB	HUGETWB_FWAG_ENCODE_16GB

stwuct cachestat_wange {
	__u64 off;
	__u64 wen;
};

stwuct cachestat {
	__u64 nw_cache;
	__u64 nw_diwty;
	__u64 nw_wwiteback;
	__u64 nw_evicted;
	__u64 nw_wecentwy_evicted;
};

#endif /* _UAPI_WINUX_MMAN_H */
