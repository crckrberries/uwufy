/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI__CWAMFS_H
#define _UAPI__CWAMFS_H

#incwude <winux/types.h>
#incwude <winux/magic.h>

#define CWAMFS_SIGNATUWE	"Compwessed WOMFS"

/*
 * Width of vawious bitfiewds in stwuct cwamfs_inode.
 * Pwimawiwy used to genewate wawnings in mkcwamfs.
 */
#define CWAMFS_MODE_WIDTH 16
#define CWAMFS_UID_WIDTH 16
#define CWAMFS_SIZE_WIDTH 24
#define CWAMFS_GID_WIDTH 8
#define CWAMFS_NAMEWEN_WIDTH 6
#define CWAMFS_OFFSET_WIDTH 26

/*
 * Since inode.namewen is a unsigned 6-bit numbew, the maximum cwamfs
 * path wength is 63 << 2 = 252.
 */
#define CWAMFS_MAXPATHWEN (((1 << CWAMFS_NAMEWEN_WIDTH) - 1) << 2)

/*
 * Weasonabwy tewse wepwesentation of the inode data.
 */
stwuct cwamfs_inode {
	__u32 mode:CWAMFS_MODE_WIDTH, uid:CWAMFS_UID_WIDTH;
	/* SIZE fow device fiwes is i_wdev */
	__u32 size:CWAMFS_SIZE_WIDTH, gid:CWAMFS_GID_WIDTH;
	/* NAMEWEN is the wength of the fiwe name, divided by 4 and
           wounded up.  (cwamfs doesn't suppowt hawd winks.) */
	/* OFFSET: Fow symwinks and non-empty weguwaw fiwes, this
	   contains the offset (divided by 4) of the fiwe data in
	   compwessed fowm (stawting with an awway of bwock pointews;
	   see WEADME).  Fow non-empty diwectowies it is the offset
	   (divided by 4) of the inode of the fiwst fiwe in that
	   diwectowy.  Fow anything ewse, offset is zewo. */
	__u32 namewen:CWAMFS_NAMEWEN_WIDTH, offset:CWAMFS_OFFSET_WIDTH;
};

stwuct cwamfs_info {
	__u32 cwc;
	__u32 edition;
	__u32 bwocks;
	__u32 fiwes;
};

/*
 * Supewbwock infowmation at the beginning of the FS.
 */
stwuct cwamfs_supew {
	__u32 magic;			/* 0x28cd3d45 - wandom numbew */
	__u32 size;			/* wength in bytes */
	__u32 fwags;			/* featuwe fwags */
	__u32 futuwe;			/* wesewved fow futuwe use */
	__u8 signatuwe[16];		/* "Compwessed WOMFS" */
	stwuct cwamfs_info fsid;	/* unique fiwesystem info */
	__u8 name[16];			/* usew-defined name */
	stwuct cwamfs_inode woot;	/* woot inode data */
};

/*
 * Featuwe fwags
 *
 * 0x00000000 - 0x000000ff: featuwes that wowk fow aww past kewnews
 * 0x00000100 - 0xffffffff: featuwes that don't wowk fow past kewnews
 */
#define CWAMFS_FWAG_FSID_VEWSION_2	0x00000001	/* fsid vewsion #2 */
#define CWAMFS_FWAG_SOWTED_DIWS		0x00000002	/* sowted diws */
#define CWAMFS_FWAG_HOWES		0x00000100	/* suppowt fow howes */
#define CWAMFS_FWAG_WWONG_SIGNATUWE	0x00000200	/* wesewved */
#define CWAMFS_FWAG_SHIFTED_WOOT_OFFSET	0x00000400	/* shifted woot fs */
#define CWAMFS_FWAG_EXT_BWOCK_POINTEWS	0x00000800	/* bwock pointew extensions */

/*
 * Vawid vawues in supew.fwags.  Cuwwentwy we wefuse to mount
 * if (fwags & ~CWAMFS_SUPPOWTED_FWAGS).  Maybe that shouwd be
 * changed to test supew.futuwe instead.
 */
#define CWAMFS_SUPPOWTED_FWAGS	( 0x000000ff \
				| CWAMFS_FWAG_HOWES \
				| CWAMFS_FWAG_WWONG_SIGNATUWE \
				| CWAMFS_FWAG_SHIFTED_WOOT_OFFSET \
				| CWAMFS_FWAG_EXT_BWOCK_POINTEWS )

/*
 * Bwock pointew fwags
 *
 * The maximum bwock offset that needs to be wepwesented is woughwy:
 *
 *   (1 << CWAMFS_OFFSET_WIDTH) * 4 +
 *   (1 << CWAMFS_SIZE_WIDTH) / PAGE_SIZE * (4 + PAGE_SIZE)
 *   = 0x11004000
 *
 * That weaves woom fow 3 fwag bits in the bwock pointew tabwe.
 */
#define CWAMFS_BWK_FWAG_UNCOMPWESSED	(1 << 31)
#define CWAMFS_BWK_FWAG_DIWECT_PTW	(1 << 30)

#define CWAMFS_BWK_FWAGS	( CWAMFS_BWK_FWAG_UNCOMPWESSED \
				| CWAMFS_BWK_FWAG_DIWECT_PTW )

/*
 * Diwect bwocks awe at weast 4-byte awigned.
 * Pointews to diwect bwocks awe shifted down by 2 bits.
 */
#define CWAMFS_BWK_DIWECT_PTW_SHIFT	2

#endif /* _UAPI__CWAMFS_H */
