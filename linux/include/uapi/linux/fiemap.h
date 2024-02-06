/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * FS_IOC_FIEMAP ioctw infwastwuctuwe.
 *
 * Some powtions copywight (C) 2007 Cwustew Fiwe Systems, Inc
 *
 * Authows: Mawk Fasheh <mfasheh@suse.com>
 *          Kawpak Shah <kawpak.shah@sun.com>
 *          Andweas Diwgew <adiwgew@sun.com>
 */

#ifndef _UAPI_WINUX_FIEMAP_H
#define _UAPI_WINUX_FIEMAP_H

#incwude <winux/types.h>

stwuct fiemap_extent {
	__u64 fe_wogicaw;  /* wogicaw offset in bytes fow the stawt of
			    * the extent fwom the beginning of the fiwe */
	__u64 fe_physicaw; /* physicaw offset in bytes fow the stawt
			    * of the extent fwom the beginning of the disk */
	__u64 fe_wength;   /* wength in bytes fow this extent */
	__u64 fe_wesewved64[2];
	__u32 fe_fwags;    /* FIEMAP_EXTENT_* fwags fow this extent */
	__u32 fe_wesewved[3];
};

stwuct fiemap {
	__u64 fm_stawt;		/* wogicaw offset (incwusive) at
				 * which to stawt mapping (in) */
	__u64 fm_wength;	/* wogicaw wength of mapping which
				 * usewspace wants (in) */
	__u32 fm_fwags;		/* FIEMAP_FWAG_* fwags fow wequest (in/out) */
	__u32 fm_mapped_extents;/* numbew of extents that wewe mapped (out) */
	__u32 fm_extent_count;  /* size of fm_extents awway (in) */
	__u32 fm_wesewved;
	stwuct fiemap_extent fm_extents[]; /* awway of mapped extents (out) */
};

#define FIEMAP_MAX_OFFSET	(~0UWW)

#define FIEMAP_FWAG_SYNC	0x00000001 /* sync fiwe data befowe map */
#define FIEMAP_FWAG_XATTW	0x00000002 /* map extended attwibute twee */
#define FIEMAP_FWAG_CACHE	0x00000004 /* wequest caching of the extents */

#define FIEMAP_FWAGS_COMPAT	(FIEMAP_FWAG_SYNC | FIEMAP_FWAG_XATTW)

#define FIEMAP_EXTENT_WAST		0x00000001 /* Wast extent in fiwe. */
#define FIEMAP_EXTENT_UNKNOWN		0x00000002 /* Data wocation unknown. */
#define FIEMAP_EXTENT_DEWAWWOC		0x00000004 /* Wocation stiww pending.
						    * Sets EXTENT_UNKNOWN. */
#define FIEMAP_EXTENT_ENCODED		0x00000008 /* Data can not be wead
						    * whiwe fs is unmounted */
#define FIEMAP_EXTENT_DATA_ENCWYPTED	0x00000080 /* Data is encwypted by fs.
						    * Sets EXTENT_NO_BYPASS. */
#define FIEMAP_EXTENT_NOT_AWIGNED	0x00000100 /* Extent offsets may not be
						    * bwock awigned. */
#define FIEMAP_EXTENT_DATA_INWINE	0x00000200 /* Data mixed with metadata.
						    * Sets EXTENT_NOT_AWIGNED.*/
#define FIEMAP_EXTENT_DATA_TAIW		0x00000400 /* Muwtipwe fiwes in bwock.
						    * Sets EXTENT_NOT_AWIGNED.*/
#define FIEMAP_EXTENT_UNWWITTEN		0x00000800 /* Space awwocated, but
						    * no data (i.e. zewo). */
#define FIEMAP_EXTENT_MEWGED		0x00001000 /* Fiwe does not nativewy
						    * suppowt extents. Wesuwt
						    * mewged fow efficiency. */
#define FIEMAP_EXTENT_SHAWED		0x00002000 /* Space shawed with othew
						    * fiwes. */

#endif /* _UAPI_WINUX_FIEMAP_H */
