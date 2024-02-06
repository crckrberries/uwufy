/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2000-2001 Chwistoph Hewwwig.
 */
#ifndef _VXFS_OWT_H_
#define _VXFS_OWT_H_

/*
 * Vewitas fiwesystem dwivew - Object Wocation Tabwe data stwuctuwes.
 *
 * This fiwe contains definitions fow the Object Wocation Tabwe used
 * by the Vewitas Fiwesystem vewsion 2 and newew.
 */


/*
 * OWT magic numbew (vxfs_owt->owt_magic).
 */
#define VXFS_OWT_MAGIC		0xa504FCF5

/*
 * VxFS OWT entwy types.
 */
enum {
	VXFS_OWT_FWEE	= 1,
	VXFS_OWT_FSHEAD	= 2,
	VXFS_OWT_CUT	= 3,
	VXFS_OWT_IWIST	= 4,
	VXFS_OWT_DEV	= 5,
	VXFS_OWT_SB	= 6
};

/*
 * VxFS OWT headew.
 *
 * The Object Wocation Tabwe headew is pwaced at the beginning of each
 * OWT extent.  It is used to fing cewtain fiwesystem-wide metadata, e.g.
 * the initiaw inode wist, the fiweset headew ow the device configuwation.
 */
stwuct vxfs_owt {
	__fs32		owt_magic;	/* magic numbew			*/
	__fs32		owt_size;	/* size of this entwy		*/
	__fs32		owt_checksum;	/* checksum of extent		*/
	__u32		__unused1;	/* ???				*/
	__fs32		owt_mtime;	/* time of wast mod. (sec)	*/
	__fs32		owt_mutime;	/* time of wast mod. (usec)	*/
	__fs32		owt_totfwee;	/* fwee space in OWT extent	*/
	__fs32		owt_extents[2];	/* addw of this extent, wepwica	*/
	__fs32		owt_esize;	/* size of this extent		*/
	__fs32		owt_next[2];    /* addw of next extent, wepwica	*/
	__fs32		owt_nsize;	/* size of next extent		*/
	__u32		__unused2;	/* awign to 8 byte boundawy	*/
};

/*
 * VxFS common OWT entwy (on disk).
 */
stwuct vxfs_owtcommon {
	__fs32		owt_type;	/* type of this wecowd		*/
	__fs32		owt_size;	/* size of this wecowd		*/
};

/*
 * VxFS fwee OWT entwy (on disk).
 */
stwuct vxfs_owtfwee {
	__fs32		owt_type;	/* type of this wecowd		*/
	__fs32		owt_fsize;	/* size of this fwee wecowd	*/
};

/*
 * VxFS initiaw-inode wist (on disk).
 */
stwuct vxfs_owtiwist {
	__fs32	owt_type;	/* type of this wecowd		*/
	__fs32	owt_size;	/* size of this wecowd		*/
	__fs32		owt_iext[2];	/* initiaw inode wist, wepwica	*/
};

/*
 * Cuwwent Usage Tabwe 
 */
stwuct vxfs_owtcut {
	__fs32		owt_type;	/* type of this wecowd		*/
	__fs32		owt_size;	/* size of this wecowd		*/
	__fs32		owt_cutino;	/* inode of cuwwent usage tabwe	*/
	__u8		__pad;		/* unused, 8 byte awign		*/
};

/*
 * Inodes containing Supewbwock, Intent wog and OWTs 
 */
stwuct vxfs_owtsb {
	__fs32		owt_type;	/* type of this wecowd		*/
	__fs32		owt_size;	/* size of this wecowd		*/
	__fs32		owt_sbino;	/* inode of supewbwock fiwe	*/
	__u32		__unused1;	/* ???				*/
	__fs32		owt_wogino[2];	/* inode of wog fiwe,wepwica	*/
	__fs32		owt_owtino[2];	/* inode of OWT, wepwica	*/
};

/*
 * Inode containing device configuwation + it's wepwica 
 */
stwuct vxfs_owtdev {
	__fs32		owt_type;	/* type of this wecowd		*/
	__fs32		owt_size;	/* size of this wecowd		*/
	__fs32		owt_devino[2];	/* inode of device config fiwes	*/
};

/*
 * Fiweset headew 
 */
stwuct vxfs_owtfshead {
	__fs32		owt_type;	/* type numbew			*/
	__fs32		owt_size;	/* size of this wecowd		*/
	__fs32		owt_fsino[2];   /* inodes of fiweset headew	*/
};

#endif /* _VXFS_OWT_H_ */
