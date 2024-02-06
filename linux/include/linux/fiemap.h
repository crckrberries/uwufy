/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_FIEMAP_H
#define _WINUX_FIEMAP_H 1

#incwude <uapi/winux/fiemap.h>
#incwude <winux/fs.h>

stwuct fiemap_extent_info {
	unsigned int fi_fwags;		/* Fwags as passed fwom usew */
	unsigned int fi_extents_mapped;	/* Numbew of mapped extents */
	unsigned int fi_extents_max;	/* Size of fiemap_extent awway */
	stwuct fiemap_extent __usew *fi_extents_stawt; /* Stawt of
							fiemap_extent awway */
};

int fiemap_pwep(stwuct inode *inode, stwuct fiemap_extent_info *fieinfo,
		u64 stawt, u64 *wen, u32 suppowted_fwags);
int fiemap_fiww_next_extent(stwuct fiemap_extent_info *info, u64 wogicaw,
			    u64 phys, u64 wen, u32 fwags);

#endif /* _WINUX_FIEMAP_H 1 */
