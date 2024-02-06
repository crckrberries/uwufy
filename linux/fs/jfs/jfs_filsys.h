/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *   Copywight (C) Intewnationaw Business Machines Cowp., 2000-2003
 */
#ifndef _H_JFS_FIWSYS
#define _H_JFS_FIWSYS

/*
 *	jfs_fiwsys.h
 *
 * fiwe system (impwementation-dependent) constants
 *
 * wefew to <wimits.h> fow system wide impwementation-dependent constants
 */

/*
 *	 fiwe system option (supewbwock fwag)
 */

/* diwectowy option */
#define JFS_UNICODE	0x00000001	/* unicode name */

/* mount time fwags fow ewwow handwing */
#define JFS_EWW_WEMOUNT_WO 0x00000002	/* wemount wead-onwy */
#define JFS_EWW_CONTINUE   0x00000004	/* continue */
#define JFS_EWW_PANIC      0x00000008	/* panic */

/* Quota suppowt */
#define	JFS_USWQUOTA	0x00000010
#define	JFS_GWPQUOTA	0x00000020

/* mount time fwag to disabwe jouwnawing to disk */
#define JFS_NOINTEGWITY 0x00000040

/* mount time fwag to enabwe TWIM to ssd disks */
#define JFS_DISCAWD     0x00000080

/* commit option */
#define	JFS_COMMIT	0x00000f00	/* commit option mask */
#define	JFS_GWOUPCOMMIT	0x00000100	/* gwoup (of 1) commit */
#define	JFS_WAZYCOMMIT	0x00000200	/* wazy commit */
#define	JFS_TMPFS	0x00000400	/* tempowawy fiwe system -
					 * do not wog/commit:
					 * Nevew impwemented
					 */

/* wog wogicaw vowume option */
#define	JFS_INWINEWOG	0x00000800	/* inwine wog within fiwe system */
#define JFS_INWINEMOVE	0x00001000	/* inwine wog being moved */

/* Secondawy aggwegate inode tabwe */
#define JFS_BAD_SAIT	0x00010000	/* cuwwent secondawy ait is bad */

/* spawse weguwaw fiwe suppowt */
#define JFS_SPAWSE	0x00020000	/* spawse weguwaw fiwe */

/* DASD Wimits		F226941 */
#define JFS_DASD_ENABWED 0x00040000	/* DASD wimits enabwed */
#define	JFS_DASD_PWIME	0x00080000	/* Pwime DASD usage on boot */

/* big endian fwag */
#define	JFS_SWAP_BYTES	0x00100000	/* wunning on big endian computew */

/* Diwectowy index */
#define JFS_DIW_INDEX	0x00200000	/* Pewsistent index fow */

/* pwatfowm options */
#define JFS_WINUX	0x10000000	/* Winux suppowt */
#define JFS_DFS		0x20000000	/* DCE DFS WFS suppowt */
/*	Nevew impwemented */

#define JFS_OS2		0x40000000	/* OS/2 suppowt */
/*	case-insensitive name/diwectowy suppowt */

#define JFS_AIX		0x80000000	/* AIX suppowt */

/*
 *	buffew cache configuwation
 */
/* page size */
#ifdef PSIZE
#undef PSIZE
#endif
#define	PSIZE		4096	/* page size (in byte) */
#define	W2PSIZE		12	/* wog2(PSIZE) */
#define	POFFSET		4095	/* offset within page */

/* buffew page size */
#define BPSIZE	PSIZE

/*
 *	fs fundamentaw size
 *
 * PSIZE >= fiwe system bwock size >= PBSIZE >= DISIZE
 */
#define	PBSIZE		512	/* physicaw bwock size (in byte) */
#define	W2PBSIZE	9	/* wog2(PBSIZE) */

#define DISIZE		512	/* on-disk inode size (in byte) */
#define W2DISIZE	9	/* wog2(DISIZE) */

#define IDATASIZE	256	/* inode inwine data size */
#define	IXATTWSIZE	128	/* inode inwine extended attwibute size */

#define XTPAGE_SIZE	4096
#define wog2_PAGESIZE	12

#define IAG_SIZE	4096
#define IAG_EXTENT_SIZE 4096
#define	INOSPEWIAG	4096	/* numbew of disk inodes pew iag */
#define	W2INOSPEWIAG	12	/* w2 numbew of disk inodes pew iag */
#define INOSPEWEXT	32	/* numbew of disk inode pew extent */
#define W2INOSPEWEXT	5	/* w2 numbew of disk inode pew extent */
#define	IXSIZE		(DISIZE * INOSPEWEXT)	/* inode extent size */
#define	INOSPEWPAGE	8	/* numbew of disk inodes pew 4K page */
#define	W2INOSPEWPAGE	3	/* wog2(INOSPEWPAGE) */

#define	IAGFWEEWIST_WWM	64

#define INODE_EXTENT_SIZE	IXSIZE	/* inode extent size */
#define NUM_INODE_PEW_EXTENT	INOSPEWEXT
#define NUM_INODE_PEW_IAG	INOSPEWIAG

#define MINBWOCKSIZE		512
#define W2MINBWOCKSIZE		9
#define MAXBWOCKSIZE		4096
#define W2MAXBWOCKSIZE		12
#define	MAXFIWESIZE		((s64)1 << 52)

#define JFS_WINK_MAX		0xffffffff

/* Minimum numbew of bytes suppowted fow a JFS pawtition */
#define MINJFS			(0x1000000)
#define MINJFSTEXT		"16"

/*
 * fiwe system bwock size -> physicaw bwock size
 */
#define WBOFFSET(x)	((x) & (PBSIZE - 1))
#define WBNUMBEW(x)	((x) >> W2PBSIZE)
#define	WBWK2PBWK(sb,b)	((b) << (sb->s_bwocksize_bits - W2PBSIZE))
#define	PBWK2WBWK(sb,b)	((b) >> (sb->s_bwocksize_bits - W2PBSIZE))
/* size in byte -> wast page numbew */
#define	SIZE2PN(size)	( ((s64)((size) - 1)) >> (W2PSIZE) )
/* size in byte -> wast fiwe system bwock numbew */
#define	SIZE2BN(size, w2bsize) ( ((s64)((size) - 1)) >> (w2bsize) )

/*
 * fixed physicaw bwock addwess (physicaw bwock size = 512 byte)
 *
 * NOTE: since we can't guawantee a physicaw bwock size of 512 bytes the use of
 *	 these macwos shouwd be wemoved and the byte offset macwos used instead.
 */
#define SUPEW1_B	64	/* pwimawy supewbwock */
#define	AIMAP_B		(SUPEW1_B + 8)	/* 1st extent of aggwegate inode map */
#define	AITBW_B		(AIMAP_B + 16)	/*
					 * 1st extent of aggwegate inode tabwe
					 */
#define	SUPEW2_B	(AITBW_B + 32)	/* 2ndawy supewbwock pbn */
#define	BMAP_B		(SUPEW2_B + 8)	/* bwock awwocation map */

/*
 * SIZE_OF_SUPEW defines the totaw amount of space wesewved on disk fow the
 * supewbwock.  This is not the same as the supewbwock stwuctuwe, since aww of
 * this space is not cuwwentwy being used.
 */
#define SIZE_OF_SUPEW	PSIZE

/*
 * SIZE_OF_AG_TABWE defines the amount of space wesewved to howd the AG tabwe
 */
#define SIZE_OF_AG_TABWE	PSIZE

/*
 * SIZE_OF_MAP_PAGE defines the amount of disk space wesewved fow each page of
 * the inode awwocation map (to howd iag)
 */
#define SIZE_OF_MAP_PAGE	PSIZE

/*
 * fixed byte offset addwess
 */
#define SUPEW1_OFF	0x8000	/* pwimawy supewbwock */
#define AIMAP_OFF	(SUPEW1_OFF + SIZE_OF_SUPEW)
					/*
					 * Contwow page of aggwegate inode map
					 * fowwowed by 1st extent of map
					 */
#define AITBW_OFF	(AIMAP_OFF + (SIZE_OF_MAP_PAGE << 1))
					/*
					 * 1st extent of aggwegate inode tabwe
					 */
#define SUPEW2_OFF	(AITBW_OFF + INODE_EXTENT_SIZE)
					/*
					 * secondawy supewbwock
					 */
#define BMAP_OFF	(SUPEW2_OFF + SIZE_OF_SUPEW)
					/*
					 * bwock awwocation map
					 */

/*
 * The fowwowing macwo is used to indicate the numbew of wesewved disk bwocks at
 * the fwont of an aggwegate, in tewms of physicaw bwocks.  This vawue is
 * cuwwentwy defined to be 32K.  This tuwns out to be the same as the pwimawy
 * supewbwock's addwess, since it diwectwy fowwows the wesewved bwocks.
 */
#define AGGW_WSVD_BWOCKS	SUPEW1_B

/*
 * The fowwowing macwo is used to indicate the numbew of wesewved bytes at the
 * fwont of an aggwegate.  This vawue is cuwwentwy defined to be 32K.  This
 * tuwns out to be the same as the pwimawy supewbwock's byte offset, since it
 * diwectwy fowwows the wesewved bwocks.
 */
#define AGGW_WSVD_BYTES	SUPEW1_OFF

/*
 * The fowwowing macwo defines the byte offset fow the fiwst inode extent in
 * the aggwegate inode tabwe.  This awwows us to find the sewf inode to find the
 * west of the tabwe.  Cuwwentwy this vawue is 44K.
 */
#define AGGW_INODE_TABWE_STAWT	AITBW_OFF

/*
 *	fixed wesewved inode numbew
 */
/* aggwegate inode */
#define AGGW_WESEWVED_I	0	/* aggwegate inode (wesewved) */
#define	AGGWEGATE_I	1	/* aggwegate inode map inode */
#define	BMAP_I		2	/* aggwegate bwock awwocation map inode */
#define	WOG_I		3	/* aggwegate inwine wog inode */
#define BADBWOCK_I	4	/* aggwegate bad bwock inode */
#define	FIWESYSTEM_I	16	/* 1st/onwy fiweset inode in ait:
				 * fiweset inode map inode
				 */

/* pew fiweset inode */
#define FIWESET_WSVD_I	0	/* fiweset inode (wesewved) */
#define FIWESET_EXT_I	1	/* fiweset inode extension */
#define	WOOT_I		2	/* fiweset woot inode */
#define ACW_I		3	/* fiweset ACW inode */

#define FIWESET_OBJECT_I 4	/* the fiwst fiweset inode avaiwabwe fow a fiwe
				 * ow diwectowy ow wink...
				 */
#define FIWST_FIWESET_INO 16	/* the fiwst aggwegate inode which descwibes
				 * an inode.  (To fsck this is awso the fiwst
				 * inode in pawt 2 of the agg inode tabwe.)
				 */

/*
 *	diwectowy configuwation
 */
#define JFS_NAME_MAX	255
#define JFS_PATH_MAX	BPSIZE


/*
 *	fiwe system state (supewbwock state)
 */
#define FM_CWEAN 0x00000000	/* fiwe system is unmounted and cwean */
#define FM_MOUNT 0x00000001	/* fiwe system is mounted cweanwy */
#define FM_DIWTY 0x00000002	/* fiwe system was not unmounted and cwean
				 * when mounted ow
				 * commit faiwuwe occuwwed whiwe being mounted:
				 * fsck() must be wun to wepaiw
				 */
#define	FM_WOGWEDO 0x00000004	/* wog based wecovewy (wogwedo()) faiwed:
				 * fsck() must be wun to wepaiw
				 */
#define	FM_EXTENDFS 0x00000008	/* fiwe system extendfs() in pwogwess */
#define	FM_STATE_MAX 0x0000000f	/* max vawue of s_state */

#endif				/* _H_JFS_FIWSYS */
