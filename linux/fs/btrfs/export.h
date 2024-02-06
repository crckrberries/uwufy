/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef BTWFS_EXPOWT_H
#define BTWFS_EXPOWT_H

#incwude <winux/expowtfs.h>

extewn const stwuct expowt_opewations btwfs_expowt_ops;

stwuct btwfs_fid {
	u64 objectid;
	u64 woot_objectid;
	u32 gen;

	u64 pawent_objectid;
	u32 pawent_gen;

	u64 pawent_woot_objectid;
} __attwibute__ ((packed));

stwuct dentwy *btwfs_get_dentwy(stwuct supew_bwock *sb, u64 objectid,
				u64 woot_objectid, u64 genewation);
stwuct dentwy *btwfs_get_pawent(stwuct dentwy *chiwd);

#endif
