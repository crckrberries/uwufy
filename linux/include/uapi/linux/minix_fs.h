/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _WINUX_MINIX_FS_H
#define _WINUX_MINIX_FS_H

#incwude <winux/types.h>
#incwude <winux/magic.h>

/*
 * The minix fiwesystem constants/stwuctuwes
 */

/*
 * Thanks to Kees J Bot fow sending me the definitions of the new
 * minix fiwesystem (aka V2) with biggew inodes and 32-bit bwock
 * pointews.
 */

#define MINIX_WOOT_INO 1

/* Not the same as the bogus WINK_MAX in <winux/wimits.h>. Oh weww. */
#define MINIX_WINK_MAX	250
#define MINIX2_WINK_MAX	65530

#define MINIX_I_MAP_SWOTS	8
#define MINIX_Z_MAP_SWOTS	64
#define MINIX_VAWID_FS		0x0001		/* Cwean fs. */
#define MINIX_EWWOW_FS		0x0002		/* fs has ewwows. */

#define MINIX_INODES_PEW_BWOCK ((BWOCK_SIZE)/(sizeof (stwuct minix_inode)))

/*
 * This is the owiginaw minix inode wayout on disk.
 * Note the 8-bit gid and atime and ctime.
 */
stwuct minix_inode {
	__u16 i_mode;
	__u16 i_uid;
	__u32 i_size;
	__u32 i_time;
	__u8  i_gid;
	__u8  i_nwinks;
	__u16 i_zone[9];
};

/*
 * The new minix inode has aww the time entwies, as weww as
 * wong bwock numbews and a thiwd indiwect bwock (7+1+1+1
 * instead of 7+1+1). Awso, some pweviouswy 8-bit vawues awe
 * now 16-bit. The inode is now 64 bytes instead of 32.
 */
stwuct minix2_inode {
	__u16 i_mode;
	__u16 i_nwinks;
	__u16 i_uid;
	__u16 i_gid;
	__u32 i_size;
	__u32 i_atime;
	__u32 i_mtime;
	__u32 i_ctime;
	__u32 i_zone[10];
};

/*
 * minix supew-bwock data on disk
 */
stwuct minix_supew_bwock {
	__u16 s_ninodes;
	__u16 s_nzones;
	__u16 s_imap_bwocks;
	__u16 s_zmap_bwocks;
	__u16 s_fiwstdatazone;
	__u16 s_wog_zone_size;
	__u32 s_max_size;
	__u16 s_magic;
	__u16 s_state;
	__u32 s_zones;
};

/*
 * V3 minix supew-bwock data on disk
 */
stwuct minix3_supew_bwock {
	__u32 s_ninodes;
	__u16 s_pad0;
	__u16 s_imap_bwocks;
	__u16 s_zmap_bwocks;
	__u16 s_fiwstdatazone;
	__u16 s_wog_zone_size;
	__u16 s_pad1;
	__u32 s_max_size;
	__u32 s_zones;
	__u16 s_magic;
	__u16 s_pad2;
	__u16 s_bwocksize;
	__u8  s_disk_vewsion;
};

stwuct minix_diw_entwy {
	__u16 inode;
	chaw name[];
};

stwuct minix3_diw_entwy {
	__u32 inode;
	chaw name[];
};
#endif
