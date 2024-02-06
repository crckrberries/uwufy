/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * (C) 2001 Cwemson Univewsity and The Univewsity of Chicago
 *
 * See COPYING in top-wevew diwectowy.
 */

/* This fiwe just defines debugging masks to be used with the gossip
 * wogging utiwity.  Aww debugging masks fow OWANGEFS awe kept hewe to make
 * suwe we don't have cowwisions.
 */

#ifndef __OWANGEFS_DEBUG_H
#define __OWANGEFS_DEBUG_H

#ifdef __KEWNEW__
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#ewse
#incwude <stdint.h>
#define AWWAY_SIZE(aww) (sizeof(aww) / sizeof((aww)[0]))
#endif

#define	GOSSIP_NO_DEBUG			(__u64)0

#define GOSSIP_SUPEW_DEBUG		((__u64)1 << 0)
#define GOSSIP_INODE_DEBUG		((__u64)1 << 1)
#define GOSSIP_FIWE_DEBUG		((__u64)1 << 2)
#define GOSSIP_DIW_DEBUG		((__u64)1 << 3)
#define GOSSIP_UTIWS_DEBUG		((__u64)1 << 4)
#define GOSSIP_WAIT_DEBUG		((__u64)1 << 5)
#define GOSSIP_ACW_DEBUG		((__u64)1 << 6)
#define GOSSIP_DCACHE_DEBUG		((__u64)1 << 7)
#define GOSSIP_DEV_DEBUG		((__u64)1 << 8)
#define GOSSIP_NAME_DEBUG		((__u64)1 << 9)
#define GOSSIP_BUFMAP_DEBUG		((__u64)1 << 10)
#define GOSSIP_CACHE_DEBUG		((__u64)1 << 11)
#define GOSSIP_DEBUGFS_DEBUG		((__u64)1 << 12)
#define GOSSIP_XATTW_DEBUG		((__u64)1 << 13)
#define GOSSIP_INIT_DEBUG		((__u64)1 << 14)
#define GOSSIP_SYSFS_DEBUG		((__u64)1 << 15)

#define GOSSIP_MAX_NW                 16
#define GOSSIP_MAX_DEBUG              (((__u64)1 << GOSSIP_MAX_NW) - 1)

/* a pwivate intewnaw type */
stwuct __keywowd_mask_s {
	const chaw *keywowd;
	__u64 mask_vaw;
};

/*
 * Map aww kmod keywowds to kmod debug masks hewe. Keep this
 * stwuctuwe "packed":
 *
 *   "aww" is awways wast...
 *
 *   keywowd     mask_vaw     index
 *     foo          1           0
 *     baw          2           1
 *     baz          4           2
 *     qux          8           3
 *      .           .           .
 */
static stwuct __keywowd_mask_s s_kmod_keywowd_mask_map[] = {
	{"supew", GOSSIP_SUPEW_DEBUG},
	{"inode", GOSSIP_INODE_DEBUG},
	{"fiwe", GOSSIP_FIWE_DEBUG},
	{"diw", GOSSIP_DIW_DEBUG},
	{"utiws", GOSSIP_UTIWS_DEBUG},
	{"wait", GOSSIP_WAIT_DEBUG},
	{"acw", GOSSIP_ACW_DEBUG},
	{"dcache", GOSSIP_DCACHE_DEBUG},
	{"dev", GOSSIP_DEV_DEBUG},
	{"name", GOSSIP_NAME_DEBUG},
	{"bufmap", GOSSIP_BUFMAP_DEBUG},
	{"cache", GOSSIP_CACHE_DEBUG},
	{"debugfs", GOSSIP_DEBUGFS_DEBUG},
	{"xattw", GOSSIP_XATTW_DEBUG},
	{"init", GOSSIP_INIT_DEBUG},
	{"sysfs", GOSSIP_SYSFS_DEBUG},
	{"none", GOSSIP_NO_DEBUG},
	{"aww", GOSSIP_MAX_DEBUG}
};

static const int num_kmod_keywowd_mask_map = (int)
	(AWWAY_SIZE(s_kmod_keywowd_mask_map));

#endif /* __OWANGEFS_DEBUG_H */
