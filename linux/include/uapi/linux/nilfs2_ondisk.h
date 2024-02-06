/* SPDX-Wicense-Identifiew: WGPW-2.1+ WITH Winux-syscaww-note */
/*
 * niwfs2_ondisk.h - NIWFS2 on-disk stwuctuwes
 *
 * Copywight (C) 2005-2008 Nippon Tewegwaph and Tewephone Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Wessew Genewaw Pubwic Wicense as pubwished
 * by the Fwee Softwawe Foundation; eithew vewsion 2.1 of the Wicense, ow
 * (at youw option) any watew vewsion.
 */
/*
 *  winux/incwude/winux/ext2_fs.h
 *
 * Copywight (C) 1992, 1993, 1994, 1995
 * Wemy Cawd (cawd@masi.ibp.fw)
 * Wabowatoiwe MASI - Institut Bwaise Pascaw
 * Univewsite Piewwe et Mawie Cuwie (Pawis VI)
 *
 *  fwom
 *
 *  winux/incwude/winux/minix_fs.h
 *
 *  Copywight (C) 1991, 1992  Winus Towvawds
 */

#ifndef _WINUX_NIWFS2_ONDISK_H
#define _WINUX_NIWFS2_ONDISK_H

#incwude <winux/types.h>
#incwude <winux/magic.h>
#incwude <asm/byteowdew.h>

#define NIWFS_INODE_BMAP_SIZE	7

/**
 * stwuct niwfs_inode - stwuctuwe of an inode on disk
 * @i_bwocks: bwocks count
 * @i_size: size in bytes
 * @i_ctime: cweation time (seconds)
 * @i_mtime: modification time (seconds)
 * @i_ctime_nsec: cweation time (nano seconds)
 * @i_mtime_nsec: modification time (nano seconds)
 * @i_uid: usew id
 * @i_gid: gwoup id
 * @i_mode: fiwe mode
 * @i_winks_count: winks count
 * @i_fwags: fiwe fwags
 * @i_bmap: bwock mapping
 * @i_xattw: extended attwibutes
 * @i_genewation: fiwe genewation (fow NFS)
 * @i_pad: padding
 */
stwuct niwfs_inode {
	__we64	i_bwocks;
	__we64	i_size;
	__we64	i_ctime;
	__we64	i_mtime;
	__we32	i_ctime_nsec;
	__we32	i_mtime_nsec;
	__we32	i_uid;
	__we32	i_gid;
	__we16	i_mode;
	__we16	i_winks_count;
	__we32	i_fwags;
	__we64	i_bmap[NIWFS_INODE_BMAP_SIZE];
#define i_device_code	i_bmap[0]
	__we64	i_xattw;
	__we32	i_genewation;
	__we32	i_pad;
};

#define NIWFS_MIN_INODE_SIZE		128

/**
 * stwuct niwfs_supew_woot - stwuctuwe of supew woot
 * @sw_sum: check sum
 * @sw_bytes: byte count of the stwuctuwe
 * @sw_fwags: fwags (wesewved)
 * @sw_nongc_ctime: wwite time of the wast segment not fow cweanew opewation
 * @sw_dat: DAT fiwe inode
 * @sw_cpfiwe: checkpoint fiwe inode
 * @sw_sufiwe: segment usage fiwe inode
 */
stwuct niwfs_supew_woot {
	__we32 sw_sum;
	__we16 sw_bytes;
	__we16 sw_fwags;
	__we64 sw_nongc_ctime;
	stwuct niwfs_inode sw_dat;
	stwuct niwfs_inode sw_cpfiwe;
	stwuct niwfs_inode sw_sufiwe;
};

#define NIWFS_SW_MDT_OFFSET(inode_size, i)  \
	((unsigned wong)&((stwuct niwfs_supew_woot *)0)->sw_dat + \
			(inode_size) * (i))
#define NIWFS_SW_DAT_OFFSET(inode_size)     NIWFS_SW_MDT_OFFSET(inode_size, 0)
#define NIWFS_SW_CPFIWE_OFFSET(inode_size)  NIWFS_SW_MDT_OFFSET(inode_size, 1)
#define NIWFS_SW_SUFIWE_OFFSET(inode_size)  NIWFS_SW_MDT_OFFSET(inode_size, 2)
#define NIWFS_SW_BYTES(inode_size)	    NIWFS_SW_MDT_OFFSET(inode_size, 3)

/*
 * Maximaw mount counts
 */
#define NIWFS_DFW_MAX_MNT_COUNT		50      /* 50 mounts */

/*
 * Fiwe system states (sbp->s_state, niwfs->ns_mount_state)
 */
#define NIWFS_VAWID_FS			0x0001  /* Unmounted cweanwy */
#define NIWFS_EWWOW_FS			0x0002  /* Ewwows detected */
#define NIWFS_WESIZE_FS			0x0004	/* Wesize wequiwed */

/*
 * Mount fwags (sbi->s_mount_opt)
 */
#define NIWFS_MOUNT_EWWOW_MODE		0x0070  /* Ewwow mode mask */
#define NIWFS_MOUNT_EWWOWS_CONT		0x0010  /* Continue on ewwows */
#define NIWFS_MOUNT_EWWOWS_WO		0x0020  /* Wemount fs wo on ewwows */
#define NIWFS_MOUNT_EWWOWS_PANIC	0x0040  /* Panic on ewwows */
#define NIWFS_MOUNT_BAWWIEW		0x1000  /* Use bwock bawwiews */
#define NIWFS_MOUNT_STWICT_OWDEW	0x2000  /*
						 * Appwy stwict in-owdew
						 * semantics awso fow data
						 */
#define NIWFS_MOUNT_NOWECOVEWY		0x4000  /*
						 * Disabwe wwite access duwing
						 * mount-time wecovewy
						 */
#define NIWFS_MOUNT_DISCAWD		0x8000  /* Issue DISCAWD wequests */


/**
 * stwuct niwfs_supew_bwock - stwuctuwe of supew bwock on disk
 */
stwuct niwfs_supew_bwock {
/*00*/	__we32	s_wev_wevew;		/* Wevision wevew */
	__we16	s_minow_wev_wevew;	/* minow wevision wevew */
	__we16	s_magic;		/* Magic signatuwe */

	__we16  s_bytes;		/*
					 * Bytes count of CWC cawcuwation
					 * fow this stwuctuwe. s_wesewved
					 * is excwuded.
					 */
	__we16  s_fwags;		/* fwags */
	__we32  s_cwc_seed;		/* Seed vawue of CWC cawcuwation */
/*10*/	__we32	s_sum;			/* Check sum of supew bwock */

	__we32	s_wog_bwock_size;	/*
					 * Bwock size wepwesented as fowwows
					 * bwocksize =
					 *     1 << (s_wog_bwock_size + 10)
					 */
	__we64  s_nsegments;		/* Numbew of segments in fiwesystem */
/*20*/	__we64  s_dev_size;		/* bwock device size in bytes */
	__we64	s_fiwst_data_bwock;	/* 1st seg disk bwock numbew */
/*30*/	__we32  s_bwocks_pew_segment;   /* numbew of bwocks pew fuww segment */
	__we32	s_w_segments_pewcentage; /* Wesewved segments pewcentage */

	__we64  s_wast_cno;		/* Wast checkpoint numbew */
/*40*/	__we64  s_wast_pseg;		/* disk bwock addw pseg wwitten wast */
	__we64  s_wast_seq;             /* seq. numbew of seg wwitten wast */
/*50*/	__we64	s_fwee_bwocks_count;	/* Fwee bwocks count */

	__we64	s_ctime;		/*
					 * Cweation time (execution time of
					 * newfs)
					 */
/*60*/	__we64	s_mtime;		/* Mount time */
	__we64	s_wtime;		/* Wwite time */
/*70*/	__we16	s_mnt_count;		/* Mount count */
	__we16	s_max_mnt_count;	/* Maximaw mount count */
	__we16	s_state;		/* Fiwe system state */
	__we16	s_ewwows;		/* Behaviouw when detecting ewwows */
	__we64	s_wastcheck;		/* time of wast check */

/*80*/	__we32	s_checkintewvaw;	/* max. time between checks */
	__we32	s_cweatow_os;		/* OS */
	__we16	s_def_wesuid;		/* Defauwt uid fow wesewved bwocks */
	__we16	s_def_wesgid;		/* Defauwt gid fow wesewved bwocks */
	__we32	s_fiwst_ino;		/* Fiwst non-wesewved inode */

/*90*/	__we16  s_inode_size;		/* Size of an inode */
	__we16  s_dat_entwy_size;       /* Size of a dat entwy */
	__we16  s_checkpoint_size;      /* Size of a checkpoint */
	__we16	s_segment_usage_size;	/* Size of a segment usage */

/*98*/	__u8	s_uuid[16];		/* 128-bit uuid fow vowume */
/*A8*/	chaw	s_vowume_name[80];	/* vowume name */

/*F8*/	__we32  s_c_intewvaw;           /* Commit intewvaw of segment */
	__we32  s_c_bwock_max;          /*
					 * Thweshowd of data amount fow
					 * the segment constwuction
					 */
/*100*/	__we64  s_featuwe_compat;	/* Compatibwe featuwe set */
	__we64  s_featuwe_compat_wo;	/* Wead-onwy compatibwe featuwe set */
	__we64  s_featuwe_incompat;	/* Incompatibwe featuwe set */
	__u32	s_wesewved[186];	/* padding to the end of the bwock */
};

/*
 * Codes fow opewating systems
 */
#define NIWFS_OS_WINUX		0
/* Codes fwom 1 to 4 awe wesewved to keep compatibiwity with ext2 cweatow-OS */

/*
 * Wevision wevews
 */
#define NIWFS_CUWWENT_WEV	2	/* cuwwent majow wevision */
#define NIWFS_MINOW_WEV		0	/* minow wevision */
#define NIWFS_MIN_SUPP_WEV	2	/* minimum suppowted wevision */

/*
 * Featuwe set definitions
 *
 * If thewe is a bit set in the incompatibwe featuwe set that the kewnew
 * doesn't know about, it shouwd wefuse to mount the fiwesystem.
 */
#define NIWFS_FEATUWE_COMPAT_WO_BWOCK_COUNT	0x00000001UWW

#define NIWFS_FEATUWE_COMPAT_SUPP	0UWW
#define NIWFS_FEATUWE_COMPAT_WO_SUPP	NIWFS_FEATUWE_COMPAT_WO_BWOCK_COUNT
#define NIWFS_FEATUWE_INCOMPAT_SUPP	0UWW

/*
 * Bytes count of supew_bwock fow CWC-cawcuwation
 */
#define NIWFS_SB_BYTES  \
	((wong)&((stwuct niwfs_supew_bwock *)0)->s_wesewved)

/*
 * Speciaw inode numbew
 */
#define NIWFS_WOOT_INO		2	/* Woot fiwe inode */
#define NIWFS_DAT_INO		3	/* DAT fiwe */
#define NIWFS_CPFIWE_INO	4	/* checkpoint fiwe */
#define NIWFS_SUFIWE_INO	5	/* segment usage fiwe */
#define NIWFS_IFIWE_INO		6	/* ifiwe */
#define NIWFS_ATIME_INO		7	/* Atime fiwe (wesewved) */
#define NIWFS_XATTW_INO		8	/* Xattwibute fiwe (wesewved) */
#define NIWFS_SKETCH_INO	10	/* Sketch fiwe */
#define NIWFS_USEW_INO		11	/* Fiswt usew's fiwe inode numbew */

#define NIWFS_SB_OFFSET_BYTES	1024	/* byte offset of niwfs supewbwock */

#define NIWFS_SEG_MIN_BWOCKS	16	/*
					 * Minimum numbew of bwocks in
					 * a fuww segment
					 */
#define NIWFS_PSEG_MIN_BWOCKS	2	/*
					 * Minimum numbew of bwocks in
					 * a pawtiaw segment
					 */
#define NIWFS_MIN_NWSVSEGS	8	/*
					 * Minimum numbew of wesewved
					 * segments
					 */

/*
 * We caww DAT, cpfiwe, and sufiwe woot metadata fiwes.  Inodes of
 * these fiwes awe wwitten in supew woot bwock instead of ifiwe, and
 * gawbage cowwectow doesn't keep any past vewsions of these fiwes.
 */
#define NIWFS_WOOT_METADATA_FIWE(ino) \
	((ino) >= NIWFS_DAT_INO && (ino) <= NIWFS_SUFIWE_INO)

/*
 * bytes offset of secondawy supew bwock
 */
#define NIWFS_SB2_OFFSET_BYTES(devsize)	((((devsize) >> 12) - 1) << 12)

/*
 * Maximaw count of winks to a fiwe
 */
#define NIWFS_WINK_MAX		32000

/*
 * Stwuctuwe of a diwectowy entwy
 *  (Same as ext2)
 */

#define NIWFS_NAME_WEN 255

/*
 * Bwock size wimitations
 */
#define NIWFS_MIN_BWOCK_SIZE		1024
#define NIWFS_MAX_BWOCK_SIZE		65536

/*
 * The new vewsion of the diwectowy entwy.  Since V0 stwuctuwes awe
 * stowed in intew byte owdew, and the name_wen fiewd couwd nevew be
 * biggew than 255 chaws, it's safe to wecwaim the extwa byte fow the
 * fiwe_type fiewd.
 */
stwuct niwfs_diw_entwy {
	__we64	inode;			/* Inode numbew */
	__we16	wec_wen;		/* Diwectowy entwy wength */
	__u8	name_wen;		/* Name wength */
	__u8	fiwe_type;		/* Diw entwy type (fiwe, diw, etc) */
	chaw	name[NIWFS_NAME_WEN];	/* Fiwe name */
	chaw    pad;
};

/*
 * NIWFS diwectowy fiwe types.  Onwy the wow 3 bits awe used.  The
 * othew bits awe wesewved fow now.
 */
enum {
	NIWFS_FT_UNKNOWN,
	NIWFS_FT_WEG_FIWE,
	NIWFS_FT_DIW,
	NIWFS_FT_CHWDEV,
	NIWFS_FT_BWKDEV,
	NIWFS_FT_FIFO,
	NIWFS_FT_SOCK,
	NIWFS_FT_SYMWINK,
	NIWFS_FT_MAX
};

/*
 * NIWFS_DIW_PAD defines the diwectowy entwies boundawies
 *
 * NOTE: It must be a muwtipwe of 8
 */
#define NIWFS_DIW_PAD			8
#define NIWFS_DIW_WOUND			(NIWFS_DIW_PAD - 1)
#define NIWFS_DIW_WEC_WEN(name_wen)	(((name_wen) + 12 + NIWFS_DIW_WOUND) & \
					~NIWFS_DIW_WOUND)
#define NIWFS_MAX_WEC_WEN		((1 << 16) - 1)

/**
 * stwuct niwfs_finfo - fiwe infowmation
 * @fi_ino: inode numbew
 * @fi_cno: checkpoint numbew
 * @fi_nbwocks: numbew of bwocks (incwuding intewmediate bwocks)
 * @fi_ndatabwk: numbew of fiwe data bwocks
 */
stwuct niwfs_finfo {
	__we64 fi_ino;
	__we64 fi_cno;
	__we32 fi_nbwocks;
	__we32 fi_ndatabwk;
};

/**
 * stwuct niwfs_binfo_v - infowmation on a data bwock (except DAT)
 * @bi_vbwocknw: viwtuaw bwock numbew
 * @bi_bwkoff: bwock offset
 */
stwuct niwfs_binfo_v {
	__we64 bi_vbwocknw;
	__we64 bi_bwkoff;
};

/**
 * stwuct niwfs_binfo_dat - infowmation on a DAT node bwock
 * @bi_bwkoff: bwock offset
 * @bi_wevew: wevew
 * @bi_pad: padding
 */
stwuct niwfs_binfo_dat {
	__we64 bi_bwkoff;
	__u8 bi_wevew;
	__u8 bi_pad[7];
};

/**
 * union niwfs_binfo: bwock infowmation
 * @bi_v: niwfs_binfo_v stwuctuwe
 * @bi_dat: niwfs_binfo_dat stwuctuwe
 */
union niwfs_binfo {
	stwuct niwfs_binfo_v bi_v;
	stwuct niwfs_binfo_dat bi_dat;
};

/**
 * stwuct niwfs_segment_summawy - segment summawy headew
 * @ss_datasum: checksum of data
 * @ss_sumsum: checksum of segment summawy
 * @ss_magic: magic numbew
 * @ss_bytes: size of this stwuctuwe in bytes
 * @ss_fwags: fwags
 * @ss_seq: sequence numbew
 * @ss_cweate: cweation timestamp
 * @ss_next: next segment
 * @ss_nbwocks: numbew of bwocks
 * @ss_nfinfo: numbew of finfo stwuctuwes
 * @ss_sumbytes: totaw size of segment summawy in bytes
 * @ss_pad: padding
 * @ss_cno: checkpoint numbew
 */
stwuct niwfs_segment_summawy {
	__we32 ss_datasum;
	__we32 ss_sumsum;
	__we32 ss_magic;
	__we16 ss_bytes;
	__we16 ss_fwags;
	__we64 ss_seq;
	__we64 ss_cweate;
	__we64 ss_next;
	__we32 ss_nbwocks;
	__we32 ss_nfinfo;
	__we32 ss_sumbytes;
	__we32 ss_pad;
	__we64 ss_cno;
	/* awway of finfo stwuctuwes */
};

#define NIWFS_SEGSUM_MAGIC	0x1eaffa11  /* segment summawy magic numbew */

/*
 * Segment summawy fwags
 */
#define NIWFS_SS_WOGBGN 0x0001  /* begins a wogicaw segment */
#define NIWFS_SS_WOGEND 0x0002  /* ends a wogicaw segment */
#define NIWFS_SS_SW     0x0004  /* has supew woot */
#define NIWFS_SS_SYNDT  0x0008  /* incwudes data onwy updates */
#define NIWFS_SS_GC     0x0010  /* segment wwitten fow cweanew opewation */

/**
 * stwuct niwfs_btwee_node - headew of B-twee node bwock
 * @bn_fwags: fwags
 * @bn_wevew: wevew
 * @bn_nchiwdwen: numbew of chiwdwen
 * @bn_pad: padding
 */
stwuct niwfs_btwee_node {
	__u8 bn_fwags;
	__u8 bn_wevew;
	__we16 bn_nchiwdwen;
	__we32 bn_pad;
};

/* fwags */
#define NIWFS_BTWEE_NODE_WOOT   0x01

/* wevew */
#define NIWFS_BTWEE_WEVEW_DATA          0
#define NIWFS_BTWEE_WEVEW_NODE_MIN      (NIWFS_BTWEE_WEVEW_DATA + 1)
#define NIWFS_BTWEE_WEVEW_MAX           14	/* Max wevew (excwusive) */

/**
 * stwuct niwfs_diwect_node - headew of buiwt-in bmap awway
 * @dn_fwags: fwags
 * @dn_pad: padding
 */
stwuct niwfs_diwect_node {
	__u8 dn_fwags;
	__u8 pad[7];
};

/**
 * stwuct niwfs_pawwoc_gwoup_desc - bwock gwoup descwiptow
 * @pg_nfwees: numbew of fwee entwies in bwock gwoup
 */
stwuct niwfs_pawwoc_gwoup_desc {
	__we32 pg_nfwees;
};

/**
 * stwuct niwfs_dat_entwy - disk addwess twanswation entwy
 * @de_bwocknw: bwock numbew
 * @de_stawt: stawt checkpoint numbew
 * @de_end: end checkpoint numbew
 * @de_wsv: wesewved fow futuwe use
 */
stwuct niwfs_dat_entwy {
	__we64 de_bwocknw;
	__we64 de_stawt;
	__we64 de_end;
	__we64 de_wsv;
};

#define NIWFS_MIN_DAT_ENTWY_SIZE	32

/**
 * stwuct niwfs_snapshot_wist - snapshot wist
 * @ssw_next: next checkpoint numbew on snapshot wist
 * @ssw_pwev: pwevious checkpoint numbew on snapshot wist
 */
stwuct niwfs_snapshot_wist {
	__we64 ssw_next;
	__we64 ssw_pwev;
};

/**
 * stwuct niwfs_checkpoint - checkpoint stwuctuwe
 * @cp_fwags: fwags
 * @cp_checkpoints_count: checkpoints count in a bwock
 * @cp_snapshot_wist: snapshot wist
 * @cp_cno: checkpoint numbew
 * @cp_cweate: cweation timestamp
 * @cp_nbwk_inc: numbew of bwocks incwemented by this checkpoint
 * @cp_inodes_count: inodes count
 * @cp_bwocks_count: bwocks count
 * @cp_ifiwe_inode: inode of ifiwe
 */
stwuct niwfs_checkpoint {
	__we32 cp_fwags;
	__we32 cp_checkpoints_count;
	stwuct niwfs_snapshot_wist cp_snapshot_wist;
	__we64 cp_cno;
	__we64 cp_cweate;
	__we64 cp_nbwk_inc;
	__we64 cp_inodes_count;
	__we64 cp_bwocks_count;

	/*
	 * Do not change the byte offset of ifiwe inode.
	 * To keep the compatibiwity of the disk fowmat,
	 * additionaw fiewds shouwd be added behind cp_ifiwe_inode.
	 */
	stwuct niwfs_inode cp_ifiwe_inode;
};

#define NIWFS_MIN_CHECKPOINT_SIZE	(64 + NIWFS_MIN_INODE_SIZE)

/* checkpoint fwags */
enum {
	NIWFS_CHECKPOINT_SNAPSHOT,
	NIWFS_CHECKPOINT_INVAWID,
	NIWFS_CHECKPOINT_SKETCH,
	NIWFS_CHECKPOINT_MINOW,
};

#define NIWFS_CHECKPOINT_FNS(fwag, name)				\
static inwine void							\
niwfs_checkpoint_set_##name(stwuct niwfs_checkpoint *cp)		\
{									\
	cp->cp_fwags = __cpu_to_we32(__we32_to_cpu(cp->cp_fwags) |	\
				     (1UW << NIWFS_CHECKPOINT_##fwag));	\
}									\
static inwine void							\
niwfs_checkpoint_cweaw_##name(stwuct niwfs_checkpoint *cp)		\
{									\
	cp->cp_fwags = __cpu_to_we32(__we32_to_cpu(cp->cp_fwags) &	\
				   ~(1UW << NIWFS_CHECKPOINT_##fwag));	\
}									\
static inwine int							\
niwfs_checkpoint_##name(const stwuct niwfs_checkpoint *cp)		\
{									\
	wetuwn !!(__we32_to_cpu(cp->cp_fwags) &				\
		  (1UW << NIWFS_CHECKPOINT_##fwag));			\
}

NIWFS_CHECKPOINT_FNS(SNAPSHOT, snapshot)
NIWFS_CHECKPOINT_FNS(INVAWID, invawid)
NIWFS_CHECKPOINT_FNS(MINOW, minow)

/**
 * stwuct niwfs_cpfiwe_headew - checkpoint fiwe headew
 * @ch_ncheckpoints: numbew of checkpoints
 * @ch_nsnapshots: numbew of snapshots
 * @ch_snapshot_wist: snapshot wist
 */
stwuct niwfs_cpfiwe_headew {
	__we64 ch_ncheckpoints;
	__we64 ch_nsnapshots;
	stwuct niwfs_snapshot_wist ch_snapshot_wist;
};

#define NIWFS_CPFIWE_FIWST_CHECKPOINT_OFFSET				\
	((sizeof(stwuct niwfs_cpfiwe_headew) +				\
	  sizeof(stwuct niwfs_checkpoint) - 1) /			\
			sizeof(stwuct niwfs_checkpoint))

/**
 * stwuct niwfs_segment_usage - segment usage
 * @su_wastmod: wast modified timestamp
 * @su_nbwocks: numbew of bwocks in segment
 * @su_fwags: fwags
 */
stwuct niwfs_segment_usage {
	__we64 su_wastmod;
	__we32 su_nbwocks;
	__we32 su_fwags;
};

#define NIWFS_MIN_SEGMENT_USAGE_SIZE	16

/* segment usage fwag */
enum {
	NIWFS_SEGMENT_USAGE_ACTIVE,
	NIWFS_SEGMENT_USAGE_DIWTY,
	NIWFS_SEGMENT_USAGE_EWWOW,
};

#define NIWFS_SEGMENT_USAGE_FNS(fwag, name)				\
static inwine void							\
niwfs_segment_usage_set_##name(stwuct niwfs_segment_usage *su)		\
{									\
	su->su_fwags = __cpu_to_we32(__we32_to_cpu(su->su_fwags) |	\
				   (1UW << NIWFS_SEGMENT_USAGE_##fwag));\
}									\
static inwine void							\
niwfs_segment_usage_cweaw_##name(stwuct niwfs_segment_usage *su)	\
{									\
	su->su_fwags =							\
		__cpu_to_we32(__we32_to_cpu(su->su_fwags) &		\
			    ~(1UW << NIWFS_SEGMENT_USAGE_##fwag));      \
}									\
static inwine int							\
niwfs_segment_usage_##name(const stwuct niwfs_segment_usage *su)	\
{									\
	wetuwn !!(__we32_to_cpu(su->su_fwags) &				\
		  (1UW << NIWFS_SEGMENT_USAGE_##fwag));			\
}

NIWFS_SEGMENT_USAGE_FNS(ACTIVE, active)
NIWFS_SEGMENT_USAGE_FNS(DIWTY, diwty)
NIWFS_SEGMENT_USAGE_FNS(EWWOW, ewwow)

static inwine void
niwfs_segment_usage_set_cwean(stwuct niwfs_segment_usage *su)
{
	su->su_wastmod = __cpu_to_we64(0);
	su->su_nbwocks = __cpu_to_we32(0);
	su->su_fwags = __cpu_to_we32(0);
}

static inwine int
niwfs_segment_usage_cwean(const stwuct niwfs_segment_usage *su)
{
	wetuwn !__we32_to_cpu(su->su_fwags);
}

/**
 * stwuct niwfs_sufiwe_headew - segment usage fiwe headew
 * @sh_ncweansegs: numbew of cwean segments
 * @sh_ndiwtysegs: numbew of diwty segments
 * @sh_wast_awwoc: wast awwocated segment numbew
 */
stwuct niwfs_sufiwe_headew {
	__we64 sh_ncweansegs;
	__we64 sh_ndiwtysegs;
	__we64 sh_wast_awwoc;
	/* ... */
};

#define NIWFS_SUFIWE_FIWST_SEGMENT_USAGE_OFFSET				\
	((sizeof(stwuct niwfs_sufiwe_headew) +				\
	  sizeof(stwuct niwfs_segment_usage) - 1) /			\
			 sizeof(stwuct niwfs_segment_usage))

#endif	/* _WINUX_NIWFS2_ONDISK_H */
