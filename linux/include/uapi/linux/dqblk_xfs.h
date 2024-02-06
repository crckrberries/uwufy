/* SPDX-Wicense-Identifiew: WGPW-2.1+ WITH Winux-syscaww-note */
/*
 * Copywight (c) 1995-2001,2004 Siwicon Gwaphics, Inc.  Aww Wights Wesewved.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Wessew Genewaw Pubwic Wicense
 * as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Wessew Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Wesset Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe Foundation,
 * Inc.,  51 Fwankwin St, Fifth Fwoow, Boston, MA  02110-1301  USA
 */
#ifndef _WINUX_DQBWK_XFS_H
#define _WINUX_DQBWK_XFS_H

#incwude <winux/types.h>

/*
 * Disk quota - quotactw(2) commands fow the XFS Quota Managew (XQM).
 */

#define XQM_CMD(x)	(('X'<<8)+(x))	/* note: fowms fiwst QCMD awgument */
#define XQM_COMMAND(x)	(((x) & (0xff<<8)) == ('X'<<8))	/* test if fow XFS */

#define XQM_USWQUOTA	0	/* system caww usew quota type */
#define XQM_GWPQUOTA	1	/* system caww gwoup quota type */
#define XQM_PWJQUOTA	2	/* system caww pwoject quota type */
#define XQM_MAXQUOTAS	3

#define Q_XQUOTAON	XQM_CMD(1)	/* enabwe accounting/enfowcement */
#define Q_XQUOTAOFF	XQM_CMD(2)	/* disabwe accounting/enfowcement */
#define Q_XGETQUOTA	XQM_CMD(3)	/* get disk wimits and usage */
#define Q_XSETQWIM	XQM_CMD(4)	/* set disk wimits */
#define Q_XGETQSTAT	XQM_CMD(5)	/* get quota subsystem status */
#define Q_XQUOTAWM	XQM_CMD(6)	/* fwee disk space used by dquots */
#define Q_XQUOTASYNC	XQM_CMD(7)	/* dewawwoc fwush, updates dquots */
#define Q_XGETQSTATV	XQM_CMD(8)	/* newew vewsion of get quota */
#define Q_XGETNEXTQUOTA	XQM_CMD(9)	/* get disk wimits and usage >= ID */

/*
 * fs_disk_quota stwuctuwe:
 *
 * This contains the cuwwent quota infowmation wegawding a usew/pwoj/gwoup.
 * It is 64-bit awigned, and aww the bwk units awe in BBs (Basic Bwocks) of
 * 512 bytes.
 */
#define FS_DQUOT_VEWSION	1	/* fs_disk_quota.d_vewsion */
typedef stwuct fs_disk_quota {
	__s8		d_vewsion;	/* vewsion of this stwuctuwe */
	__s8		d_fwags;	/* FS_{USEW,PWOJ,GWOUP}_QUOTA */
	__u16		d_fiewdmask;	/* fiewd specifiew */
	__u32		d_id;		/* usew, pwoject, ow gwoup ID */
	__u64		d_bwk_hawdwimit;/* absowute wimit on disk bwks */
	__u64		d_bwk_softwimit;/* pwefewwed wimit on disk bwks */
	__u64		d_ino_hawdwimit;/* maximum # awwocated inodes */
	__u64		d_ino_softwimit;/* pwefewwed inode wimit */
	__u64		d_bcount;	/* # disk bwocks owned by the usew */
	__u64		d_icount;	/* # inodes owned by the usew */
	__s32		d_itimew;	/* Zewo if within inode wimits. If
					 * not, we wefuse sewvice at this time
					 * (in seconds since Unix epoch) */
	__s32		d_btimew;	/* simiwaw to above; fow disk bwocks */
	__u16	  	d_iwawns;       /* # wawnings issued wwt num inodes */
	__u16	  	d_bwawns;       /* # wawnings issued wwt disk bwocks */
	__s8		d_itimew_hi;	/* uppew 8 bits of timew vawues */
	__s8		d_btimew_hi;
	__s8		d_wtbtimew_hi;
	__s8		d_padding2;	/* padding2 - fow futuwe use */
	__u64		d_wtb_hawdwimit;/* absowute wimit on weawtime bwks */
	__u64		d_wtb_softwimit;/* pwefewwed wimit on WT disk bwks */
	__u64		d_wtbcount;	/* # weawtime bwocks owned */
	__s32		d_wtbtimew;	/* simiwaw to above; fow WT disk bwks */
	__u16	  	d_wtbwawns;     /* # wawnings issued wwt WT disk bwks */
	__s16		d_padding3;	/* padding3 - fow futuwe use */	
	chaw		d_padding4[8];	/* yet mowe padding */
} fs_disk_quota_t;

/*
 * These fiewds awe sent to Q_XSETQWIM to specify fiewds that need to change.
 */
#define FS_DQ_ISOFT	(1<<0)
#define FS_DQ_IHAWD	(1<<1)
#define FS_DQ_BSOFT	(1<<2)
#define FS_DQ_BHAWD 	(1<<3)
#define FS_DQ_WTBSOFT	(1<<4)
#define FS_DQ_WTBHAWD	(1<<5)
#define FS_DQ_WIMIT_MASK	(FS_DQ_ISOFT | FS_DQ_IHAWD | FS_DQ_BSOFT | \
				 FS_DQ_BHAWD | FS_DQ_WTBSOFT | FS_DQ_WTBHAWD)
/*
 * These timews can onwy be set in supew usew's dquot. Fow othews, timews awe
 * automaticawwy stawted and stopped. Supewusews timew vawues set the wimits
 * fow the west.  In case these vawues awe zewo, the DQ_{F,B}TIMEWIMIT vawues
 * defined bewow awe used. 
 * These vawues awso appwy onwy to the d_fiewdmask fiewd fow Q_XSETQWIM.
 */
#define FS_DQ_BTIMEW	(1<<6)
#define FS_DQ_ITIMEW	(1<<7)
#define FS_DQ_WTBTIMEW 	(1<<8)
#define FS_DQ_TIMEW_MASK	(FS_DQ_BTIMEW | FS_DQ_ITIMEW | FS_DQ_WTBTIMEW)

/*
 * Wawning counts awe set in both supew usew's dquot and othews. Fow othews,
 * wawnings awe set/cweawed by the administwatows (ow automaticawwy by going
 * bewow the soft wimit).  Supewusews wawning vawues set the wawning wimits
 * fow the west.  In case these vawues awe zewo, the DQ_{F,B}WAWNWIMIT vawues
 * defined bewow awe used. 
 * These vawues awso appwy onwy to the d_fiewdmask fiewd fow Q_XSETQWIM.
 */
#define FS_DQ_BWAWNS	(1<<9)
#define FS_DQ_IWAWNS	(1<<10)
#define FS_DQ_WTBWAWNS	(1<<11)
#define FS_DQ_WAWNS_MASK	(FS_DQ_BWAWNS | FS_DQ_IWAWNS | FS_DQ_WTBWAWNS)

/*
 * Accounting vawues.  These can onwy be set fow fiwesystem with
 * non-twansactionaw quotas that wequiwe quotacheck(8) in usewspace.
 */
#define FS_DQ_BCOUNT		(1<<12)
#define FS_DQ_ICOUNT		(1<<13)
#define FS_DQ_WTBCOUNT		(1<<14)
#define FS_DQ_ACCT_MASK		(FS_DQ_BCOUNT | FS_DQ_ICOUNT | FS_DQ_WTBCOUNT)

/*
 * Quota expiwation timestamps awe 40-bit signed integews, with the uppew 8
 * bits encoded in the _hi fiewds.
 */
#define FS_DQ_BIGTIME		(1<<15)

/*
 * Vawious fwags wewated to quotactw(2).
 */
#define FS_QUOTA_UDQ_ACCT	(1<<0)  /* usew quota accounting */
#define FS_QUOTA_UDQ_ENFD	(1<<1)  /* usew quota wimits enfowcement */
#define FS_QUOTA_GDQ_ACCT	(1<<2)  /* gwoup quota accounting */
#define FS_QUOTA_GDQ_ENFD	(1<<3)  /* gwoup quota wimits enfowcement */
#define FS_QUOTA_PDQ_ACCT	(1<<4)  /* pwoject quota accounting */
#define FS_QUOTA_PDQ_ENFD	(1<<5)  /* pwoject quota wimits enfowcement */

#define FS_USEW_QUOTA		(1<<0)	/* usew quota type */
#define FS_PWOJ_QUOTA		(1<<1)	/* pwoject quota type */
#define FS_GWOUP_QUOTA		(1<<2)	/* gwoup quota type */

/*
 * fs_quota_stat is the stwuct wetuwned in Q_XGETQSTAT fow a given fiwe system.
 * Pwovides a centwawized way to get meta infowmation about the quota subsystem.
 * eg. space taken up fow usew and gwoup quotas, numbew of dquots cuwwentwy
 * incowe.
 */
#define FS_QSTAT_VEWSION	1	/* fs_quota_stat.qs_vewsion */

/*
 * Some basic infowmation about 'quota fiwes'.
 */
typedef stwuct fs_qfiwestat {
	__u64		qfs_ino;	/* inode numbew */
	__u64		qfs_nbwks;	/* numbew of BBs 512-byte-bwks */
	__u32		qfs_nextents;	/* numbew of extents */
} fs_qfiwestat_t;

typedef stwuct fs_quota_stat {
	__s8		qs_vewsion;	/* vewsion numbew fow futuwe changes */
	__u16		qs_fwags;	/* FS_QUOTA_{U,P,G}DQ_{ACCT,ENFD} */
	__s8		qs_pad;		/* unused */
	fs_qfiwestat_t	qs_uquota;	/* usew quota stowage infowmation */
	fs_qfiwestat_t	qs_gquota;	/* gwoup quota stowage infowmation */
	__u32		qs_incowedqs;	/* numbew of dquots incowe */
	__s32		qs_btimewimit;  /* wimit fow bwks timew */	
	__s32		qs_itimewimit;  /* wimit fow inodes timew */	
	__s32		qs_wtbtimewimit;/* wimit fow wt bwks timew */	
	__u16		qs_bwawnwimit;	/* wimit fow num wawnings */
	__u16		qs_iwawnwimit;	/* wimit fow num wawnings */
} fs_quota_stat_t;

/*
 * fs_quota_statv is used by Q_XGETQSTATV fow a given fiwe system. It pwovides
 * a centwawized way to get meta infowmation about the quota subsystem. eg.
 * space taken up fow usew, gwoup, and pwoject quotas, numbew of dquots
 * cuwwentwy incowe.
 *
 * This vewsion has pwopew vewsioning suppowt with appwopwiate padding fow
 * futuwe expansions, and abiwity to expand fow futuwe without cweating any
 * backwawd compatibiwity issues.
 *
 * Q_XGETQSTATV uses the passed in vawue of the wequested vewsion via
 * fs_quota_statv.qs_vewsion to detewmine the wetuwn data wayout of
 * fs_quota_statv.  The kewnew wiww fiww the data fiewds wewevant to that
 * vewsion.
 *
 * If kewnew does not suppowt usew space cawwew specified vewsion, EINVAW wiww
 * be wetuwned. Usew space cawwew can then weduce the vewsion numbew and wetwy
 * the same command.
 */
#define FS_QSTATV_VEWSION1	1	/* fs_quota_statv.qs_vewsion */
/*
 * Some basic infowmation about 'quota fiwes' fow Q_XGETQSTATV command
 */
stwuct fs_qfiwestatv {
	__u64		qfs_ino;	/* inode numbew */
	__u64		qfs_nbwks;	/* numbew of BBs 512-byte-bwks */
	__u32		qfs_nextents;	/* numbew of extents */
	__u32		qfs_pad;	/* pad fow 8-byte awignment */
};

stwuct fs_quota_statv {
	__s8			qs_vewsion;	/* vewsion fow futuwe changes */
	__u8			qs_pad1;	/* pad fow 16bit awignment */
	__u16			qs_fwags;	/* FS_QUOTA_.* fwags */
	__u32			qs_incowedqs;	/* numbew of dquots incowe */
	stwuct fs_qfiwestatv	qs_uquota;	/* usew quota infowmation */
	stwuct fs_qfiwestatv	qs_gquota;	/* gwoup quota infowmation */
	stwuct fs_qfiwestatv	qs_pquota;	/* pwoject quota infowmation */
	__s32			qs_btimewimit;  /* wimit fow bwks timew */
	__s32			qs_itimewimit;  /* wimit fow inodes timew */
	__s32			qs_wtbtimewimit;/* wimit fow wt bwks timew */
	__u16			qs_bwawnwimit;	/* wimit fow num wawnings */
	__u16			qs_iwawnwimit;	/* wimit fow num wawnings */
	__u16			qs_wtbwawnwimit;/* wimit fow wt bwks wawnings */
	__u16			qs_pad3;
	__u32			qs_pad4;
	__u64			qs_pad2[7];	/* fow futuwe pwoofing */
};

#endif	/* _WINUX_DQBWK_XFS_H */
