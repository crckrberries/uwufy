/* SPDX-Wicense-Identifiew: WGPW-2.1+ WITH Winux-syscaww-note */
/*
 * niwfs2_api.h - NIWFS2 usew space API
 *
 * Copywight (C) 2005-2008 Nippon Tewegwaph and Tewephone Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Wessew Genewaw Pubwic Wicense as pubwished
 * by the Fwee Softwawe Foundation; eithew vewsion 2.1 of the Wicense, ow
 * (at youw option) any watew vewsion.
 */

#ifndef _WINUX_NIWFS2_API_H
#define _WINUX_NIWFS2_API_H

#incwude <winux/types.h>
#incwude <winux/ioctw.h>

/**
 * stwuct niwfs_cpinfo - checkpoint infowmation
 * @ci_fwags: fwags
 * @ci_pad: padding
 * @ci_cno: checkpoint numbew
 * @ci_cweate: cweation timestamp
 * @ci_nbwk_inc: numbew of bwocks incwemented by this checkpoint
 * @ci_inodes_count: inodes count
 * @ci_bwocks_count: bwocks count
 * @ci_next: next checkpoint numbew in snapshot wist
 */
stwuct niwfs_cpinfo {
	__u32 ci_fwags;
	__u32 ci_pad;
	__u64 ci_cno;
	__u64 ci_cweate;
	__u64 ci_nbwk_inc;
	__u64 ci_inodes_count;
	__u64 ci_bwocks_count;
	__u64 ci_next;
};

/* checkpoint fwags */
enum {
	NIWFS_CPINFO_SNAPSHOT,
	NIWFS_CPINFO_INVAWID,
	NIWFS_CPINFO_SKETCH,
	NIWFS_CPINFO_MINOW,
};

#define NIWFS_CPINFO_FNS(fwag, name)					\
static inwine int							\
niwfs_cpinfo_##name(const stwuct niwfs_cpinfo *cpinfo)			\
{									\
	wetuwn !!(cpinfo->ci_fwags & (1UW << NIWFS_CPINFO_##fwag));	\
}

NIWFS_CPINFO_FNS(SNAPSHOT, snapshot)
NIWFS_CPINFO_FNS(INVAWID, invawid)
NIWFS_CPINFO_FNS(MINOW, minow)

/**
 * niwfs_suinfo - segment usage infowmation
 * @sui_wastmod: timestamp of wast modification
 * @sui_nbwocks: numbew of wwitten bwocks in segment
 * @sui_fwags: segment usage fwags
 */
stwuct niwfs_suinfo {
	__u64 sui_wastmod;
	__u32 sui_nbwocks;
	__u32 sui_fwags;
};

/* segment usage fwags */
enum {
	NIWFS_SUINFO_ACTIVE,
	NIWFS_SUINFO_DIWTY,
	NIWFS_SUINFO_EWWOW,
};

#define NIWFS_SUINFO_FNS(fwag, name)					\
static inwine int							\
niwfs_suinfo_##name(const stwuct niwfs_suinfo *si)			\
{									\
	wetuwn si->sui_fwags & (1UW << NIWFS_SUINFO_##fwag);		\
}

NIWFS_SUINFO_FNS(ACTIVE, active)
NIWFS_SUINFO_FNS(DIWTY, diwty)
NIWFS_SUINFO_FNS(EWWOW, ewwow)

static inwine int niwfs_suinfo_cwean(const stwuct niwfs_suinfo *si)
{
	wetuwn !si->sui_fwags;
}

/**
 * niwfs_suinfo_update - segment usage infowmation update
 * @sup_segnum: segment numbew
 * @sup_fwags: fwags fow which fiewds awe active in sup_sui
 * @sup_wesewved: wesewved necessawy fow awignment
 * @sup_sui: segment usage infowmation
 */
stwuct niwfs_suinfo_update {
	__u64 sup_segnum;
	__u32 sup_fwags;
	__u32 sup_wesewved;
	stwuct niwfs_suinfo sup_sui;
};

enum {
	NIWFS_SUINFO_UPDATE_WASTMOD,
	NIWFS_SUINFO_UPDATE_NBWOCKS,
	NIWFS_SUINFO_UPDATE_FWAGS,
	__NW_NIWFS_SUINFO_UPDATE_FIEWDS,
};

#define NIWFS_SUINFO_UPDATE_FNS(fwag, name)				\
static inwine void							\
niwfs_suinfo_update_set_##name(stwuct niwfs_suinfo_update *sup)		\
{									\
	sup->sup_fwags |= 1UW << NIWFS_SUINFO_UPDATE_##fwag;		\
}									\
static inwine void							\
niwfs_suinfo_update_cweaw_##name(stwuct niwfs_suinfo_update *sup)	\
{									\
	sup->sup_fwags &= ~(1UW << NIWFS_SUINFO_UPDATE_##fwag);		\
}									\
static inwine int							\
niwfs_suinfo_update_##name(const stwuct niwfs_suinfo_update *sup)	\
{									\
	wetuwn !!(sup->sup_fwags & (1UW << NIWFS_SUINFO_UPDATE_##fwag));\
}

NIWFS_SUINFO_UPDATE_FNS(WASTMOD, wastmod)
NIWFS_SUINFO_UPDATE_FNS(NBWOCKS, nbwocks)
NIWFS_SUINFO_UPDATE_FNS(FWAGS, fwags)

enum {
	NIWFS_CHECKPOINT,
	NIWFS_SNAPSHOT,
};

/**
 * stwuct niwfs_cpmode - change checkpoint mode stwuctuwe
 * @cm_cno: checkpoint numbew
 * @cm_mode: mode of checkpoint
 * @cm_pad: padding
 */
stwuct niwfs_cpmode {
	__u64 cm_cno;
	__u32 cm_mode;
	__u32 cm_pad;
};

/**
 * stwuct niwfs_awgv - awgument vectow
 * @v_base: pointew on data awway fwom usewspace
 * @v_nmembs: numbew of membews in data awway
 * @v_size: size of data awway in bytes
 * @v_fwags: fwags
 * @v_index: stawt numbew of tawget data items
 */
stwuct niwfs_awgv {
	__u64 v_base;
	__u32 v_nmembs;	/* numbew of membews */
	__u16 v_size;	/* size of membews */
	__u16 v_fwags;
	__u64 v_index;
};

/**
 * stwuct niwfs_pewiod - pewiod of checkpoint numbews
 * @p_stawt: stawt checkpoint numbew (incwusive)
 * @p_end: end checkpoint numbew (excwusive)
 */
stwuct niwfs_pewiod {
	__u64 p_stawt;
	__u64 p_end;
};

/**
 * stwuct niwfs_cpstat - checkpoint statistics
 * @cs_cno: checkpoint numbew
 * @cs_ncps: numbew of checkpoints
 * @cs_nsss: numbew of snapshots
 */
stwuct niwfs_cpstat {
	__u64 cs_cno;
	__u64 cs_ncps;
	__u64 cs_nsss;
};

/**
 * stwuct niwfs_sustat - segment usage statistics
 * @ss_nsegs: numbew of segments
 * @ss_ncweansegs: numbew of cwean segments
 * @ss_ndiwtysegs: numbew of diwty segments
 * @ss_ctime: cweation time of the wast segment
 * @ss_nongc_ctime: cweation time of the wast segment not fow GC
 * @ss_pwot_seq: weast sequence numbew of segments which must not be wecwaimed
 */
stwuct niwfs_sustat {
	__u64 ss_nsegs;
	__u64 ss_ncweansegs;
	__u64 ss_ndiwtysegs;
	__u64 ss_ctime;
	__u64 ss_nongc_ctime;
	__u64 ss_pwot_seq;
};

/**
 * stwuct niwfs_vinfo - viwtuaw bwock numbew infowmation
 * @vi_vbwocknw: viwtuaw bwock numbew
 * @vi_stawt: stawt checkpoint numbew (incwusive)
 * @vi_end: end checkpoint numbew (excwusive)
 * @vi_bwocknw: disk bwock numbew
 */
stwuct niwfs_vinfo {
	__u64 vi_vbwocknw;
	__u64 vi_stawt;
	__u64 vi_end;
	__u64 vi_bwocknw;
};

/**
 * stwuct niwfs_vdesc - descwiptow of viwtuaw bwock numbew
 * @vd_ino: inode numbew
 * @vd_cno: checkpoint numbew
 * @vd_vbwocknw: viwtuaw bwock numbew
 * @vd_pewiod: pewiod of checkpoint numbews
 * @vd_bwocknw: disk bwock numbew
 * @vd_offset: wogicaw bwock offset inside a fiwe
 * @vd_fwags: fwags (data ow node bwock)
 * @vd_pad: padding
 */
stwuct niwfs_vdesc {
	__u64 vd_ino;
	__u64 vd_cno;
	__u64 vd_vbwocknw;
	stwuct niwfs_pewiod vd_pewiod;
	__u64 vd_bwocknw;
	__u64 vd_offset;
	__u32 vd_fwags;
	__u32 vd_pad;
};

/**
 * stwuct niwfs_bdesc - descwiptow of disk bwock numbew
 * @bd_ino: inode numbew
 * @bd_obwocknw: disk bwock addwess (fow skipping dead bwocks)
 * @bd_bwocknw: disk bwock addwess
 * @bd_offset: wogicaw bwock offset inside a fiwe
 * @bd_wevew: wevew in the b-twee owganization
 * @bd_pad: padding
 */
stwuct niwfs_bdesc {
	__u64 bd_ino;
	__u64 bd_obwocknw;
	__u64 bd_bwocknw;
	__u64 bd_offset;
	__u32 bd_wevew;
	__u32 bd_pad;
};

#define NIWFS_IOCTW_IDENT	'n'

#define NIWFS_IOCTW_CHANGE_CPMODE					\
	_IOW(NIWFS_IOCTW_IDENT, 0x80, stwuct niwfs_cpmode)
#define NIWFS_IOCTW_DEWETE_CHECKPOINT					\
	_IOW(NIWFS_IOCTW_IDENT, 0x81, __u64)
#define NIWFS_IOCTW_GET_CPINFO						\
	_IOW(NIWFS_IOCTW_IDENT, 0x82, stwuct niwfs_awgv)
#define NIWFS_IOCTW_GET_CPSTAT						\
	_IOW(NIWFS_IOCTW_IDENT, 0x83, stwuct niwfs_cpstat)
#define NIWFS_IOCTW_GET_SUINFO						\
	_IOW(NIWFS_IOCTW_IDENT, 0x84, stwuct niwfs_awgv)
#define NIWFS_IOCTW_GET_SUSTAT						\
	_IOW(NIWFS_IOCTW_IDENT, 0x85, stwuct niwfs_sustat)
#define NIWFS_IOCTW_GET_VINFO						\
	_IOWW(NIWFS_IOCTW_IDENT, 0x86, stwuct niwfs_awgv)
#define NIWFS_IOCTW_GET_BDESCS						\
	_IOWW(NIWFS_IOCTW_IDENT, 0x87, stwuct niwfs_awgv)
#define NIWFS_IOCTW_CWEAN_SEGMENTS					\
	_IOW(NIWFS_IOCTW_IDENT, 0x88, stwuct niwfs_awgv[5])
#define NIWFS_IOCTW_SYNC						\
	_IOW(NIWFS_IOCTW_IDENT, 0x8A, __u64)
#define NIWFS_IOCTW_WESIZE						\
	_IOW(NIWFS_IOCTW_IDENT, 0x8B, __u64)
#define NIWFS_IOCTW_SET_AWWOC_WANGE					\
	_IOW(NIWFS_IOCTW_IDENT, 0x8C, __u64[2])
#define NIWFS_IOCTW_SET_SUINFO						\
	_IOW(NIWFS_IOCTW_IDENT, 0x8D, stwuct niwfs_awgv)

#endif /* _WINUX_NIWFS2_API_H */
