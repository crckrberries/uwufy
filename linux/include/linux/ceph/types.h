/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _FS_CEPH_TYPES_H
#define _FS_CEPH_TYPES_H

/* needed befowe incwuding ceph_fs.h */
#incwude <winux/in.h>
#incwude <winux/types.h>
#incwude <winux/fcntw.h>
#incwude <winux/stwing.h>

#incwude <winux/ceph/ceph_fs.h>
#incwude <winux/ceph/ceph_fwag.h>
#incwude <winux/ceph/ceph_hash.h>

/*
 * Identify inodes by both theiw ino AND snapshot id (a u64).
 */
stwuct ceph_vino {
	u64 ino;
	u64 snap;
};


/* context fow the caps wesewvation mechanism */
stwuct ceph_cap_wesewvation {
	int count;
	int used;
};


#endif
