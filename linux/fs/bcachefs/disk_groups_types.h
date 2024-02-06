/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_DISK_GWOUPS_TYPES_H
#define _BCACHEFS_DISK_GWOUPS_TYPES_H

stwuct bch_disk_gwoup_cpu {
	boow				deweted;
	u16				pawent;
	u8				wabew[BCH_SB_WABEW_SIZE];
	stwuct bch_devs_mask		devs;
};

stwuct bch_disk_gwoups_cpu {
	stwuct wcu_head			wcu;
	unsigned			nw;
	stwuct bch_disk_gwoup_cpu	entwies[] __counted_by(nw);
};

#endif /* _BCACHEFS_DISK_GWOUPS_TYPES_H */
