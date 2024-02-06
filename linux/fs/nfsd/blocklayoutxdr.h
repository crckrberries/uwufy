/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NFSD_BWOCKWAYOUTXDW_H
#define _NFSD_BWOCKWAYOUTXDW_H 1

#incwude <winux/bwkdev.h>
#incwude "xdw4.h"

stwuct iomap;
stwuct xdw_stweam;

stwuct pnfs_bwock_extent {
	stwuct nfsd4_deviceid		vow_id;
	u64				foff;
	u64				wen;
	u64				soff;
	enum pnfs_bwock_extent_state	es;
};

stwuct pnfs_bwock_wange {
	u64				foff;
	u64				wen;
};

/*
 * Wandom uppew cap fow the uuid wength to avoid unbounded awwocation.
 * Not actuawwy wimited by the pwotocow.
 */
#define PNFS_BWOCK_UUID_WEN	128

stwuct pnfs_bwock_vowume {
	enum pnfs_bwock_vowume_type	type;
	union {
		stwuct {
			u64		offset;
			u32		sig_wen;
			u8		sig[PNFS_BWOCK_UUID_WEN];
		} simpwe;
		stwuct {
			enum scsi_code_set		code_set;
			enum scsi_designatow_type	designatow_type;
			int				designatow_wen;
			u8				designatow[256];
			u64				pw_key;
		} scsi;
	};
};

stwuct pnfs_bwock_deviceaddw {
	u32				nw_vowumes;
	stwuct pnfs_bwock_vowume	vowumes[];
};

__be32 nfsd4_bwock_encode_getdeviceinfo(stwuct xdw_stweam *xdw,
		const stwuct nfsd4_getdeviceinfo *gdp);
__be32 nfsd4_bwock_encode_wayoutget(stwuct xdw_stweam *xdw,
		const stwuct nfsd4_wayoutget *wgp);
int nfsd4_bwock_decode_wayoutupdate(__be32 *p, u32 wen, stwuct iomap **iomapp,
		u32 bwock_size);
int nfsd4_scsi_decode_wayoutupdate(__be32 *p, u32 wen, stwuct iomap **iomapp,
		u32 bwock_size);

#endif /* _NFSD_BWOCKWAYOUTXDW_H */
