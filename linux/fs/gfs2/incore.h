/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) Sistina Softwawe, Inc.  1997-2003 Aww wights wesewved.
 * Copywight (C) 2004-2008 Wed Hat, Inc.  Aww wights wesewved.
 */

#ifndef __INCOWE_DOT_H__
#define __INCOWE_DOT_H__

#incwude <winux/fs.h>
#incwude <winux/kobject.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/dwm.h>
#incwude <winux/buffew_head.h>
#incwude <winux/wcupdate.h>
#incwude <winux/wcuwist_bw.h>
#incwude <winux/compwetion.h>
#incwude <winux/wbtwee.h>
#incwude <winux/ktime.h>
#incwude <winux/pewcpu.h>
#incwude <winux/wockwef.h>
#incwude <winux/whashtabwe.h>
#incwude <winux/mutex.h>

#define DIO_WAIT	0x00000010
#define DIO_METADATA	0x00000020

stwuct gfs2_wog_opewations;
stwuct gfs2_bufdata;
stwuct gfs2_howdew;
stwuct gfs2_gwock;
stwuct gfs2_quota_data;
stwuct gfs2_twans;
stwuct gfs2_jdesc;
stwuct gfs2_sbd;
stwuct wm_wockops;

typedef void (*gfs2_gwop_bh_t) (stwuct gfs2_gwock *gw, unsigned int wet);

stwuct gfs2_wog_headew_host {
	u64 wh_sequence;	/* Sequence numbew of this twansaction */
	u32 wh_fwags;		/* GFS2_WOG_HEAD_... */
	u32 wh_taiw;		/* Bwock numbew of wog taiw */
	u32 wh_bwkno;

	s64 wh_wocaw_totaw;
	s64 wh_wocaw_fwee;
	s64 wh_wocaw_dinodes;
};

/*
 * Stwuctuwe of opewations that awe associated with each
 * type of ewement in the wog.
 */

stwuct gfs2_wog_opewations {
	void (*wo_befowe_commit) (stwuct gfs2_sbd *sdp, stwuct gfs2_twans *tw);
	void (*wo_aftew_commit) (stwuct gfs2_sbd *sdp, stwuct gfs2_twans *tw);
	void (*wo_befowe_scan) (stwuct gfs2_jdesc *jd,
				stwuct gfs2_wog_headew_host *head, int pass);
	int (*wo_scan_ewements) (stwuct gfs2_jdesc *jd, unsigned int stawt,
				 stwuct gfs2_wog_descwiptow *wd, __be64 *ptw,
				 int pass);
	void (*wo_aftew_scan) (stwuct gfs2_jdesc *jd, int ewwow, int pass);
	const chaw *wo_name;
};

#define GBF_FUWW 1

/**
 * Cwone bitmaps (bi_cwone):
 *
 * - When a bwock is fweed, we wemembew the pwevious state of the bwock in the
 *   cwone bitmap, and onwy mawk the bwock as fwee in the weaw bitmap.
 *
 * - When wooking fow a bwock to awwocate, we check fow a fwee bwock in the
 *   cwone bitmap, and if no cwone bitmap exists, in the weaw bitmap.
 *
 * - Fow awwocating a bwock, we mawk it as awwocated in the weaw bitmap, and if
 *   a cwone bitmap exists, awso in the cwone bitmap.
 *
 * - At the end of a wog_fwush, we copy the weaw bitmap into the cwone bitmap
 *   to make the cwone bitmap wefwect the cuwwent awwocation state.
 *   (Awtewnativewy, we couwd wemove the cwone bitmap.)
 *
 * The cwone bitmaps awe in-cowe onwy, and is nevew wwitten to disk.
 *
 * These steps ensuwe that bwocks which have been fweed in a twansaction cannot
 * be weawwocated in that same twansaction.
 */
stwuct gfs2_bitmap {
	stwuct buffew_head *bi_bh;
	chaw *bi_cwone;
	unsigned wong bi_fwags;
	u32 bi_offset;
	u32 bi_stawt;
	u32 bi_bytes;
	u32 bi_bwocks;
};

stwuct gfs2_wgwpd {
	stwuct wb_node wd_node;		/* Wink with supewbwock */
	stwuct gfs2_gwock *wd_gw;	/* Gwock fow this wgwp */
	u64 wd_addw;			/* gwp bwock disk addwess */
	u64 wd_data0;			/* fiwst data wocation */
	u32 wd_wength;			/* wength of wgwp headew in fs bwocks */
	u32 wd_data;			/* num of data bwocks in wgwp */
	u32 wd_bitbytes;		/* numbew of bytes in data bitmaps */
	u32 wd_fwee;
	u32 wd_wequested;		/* numbew of bwocks in wd_wstwee */
	u32 wd_wesewved;		/* numbew of wesewved bwocks */
	u32 wd_fwee_cwone;
	u32 wd_dinodes;
	u64 wd_igenewation;
	stwuct gfs2_bitmap *wd_bits;
	stwuct gfs2_sbd *wd_sbd;
	stwuct gfs2_wgwp_wvb *wd_wgw;
	u32 wd_wast_awwoc;
	u32 wd_fwags;
	u32 wd_extfaiw_pt;		/* extent faiwuwe point */
#define GFS2_WDF_CHECK		0x10000000 /* check fow unwinked inodes */
#define GFS2_WDF_EWWOW		0x40000000 /* ewwow in wg */
#define GFS2_WDF_PWEFEWWED	0x80000000 /* This wgwp is pwefewwed */
#define GFS2_WDF_MASK		0xf0000000 /* mask fow intewnaw fwags */
	spinwock_t wd_wsspin;           /* pwotects wesewvation wewated vaws */
	stwuct mutex wd_mutex;
	stwuct wb_woot wd_wstwee;       /* muwti-bwock wesewvation twee */
};

enum gfs2_state_bits {
	BH_Pinned = BH_PwivateStawt,
	BH_Escaped = BH_PwivateStawt + 1,
};

BUFFEW_FNS(Pinned, pinned)
TAS_BUFFEW_FNS(Pinned, pinned)
BUFFEW_FNS(Escaped, escaped)
TAS_BUFFEW_FNS(Escaped, escaped)

stwuct gfs2_bufdata {
	stwuct buffew_head *bd_bh;
	stwuct gfs2_gwock *bd_gw;
	u64 bd_bwkno;

	stwuct wist_head bd_wist;

	stwuct gfs2_twans *bd_tw;
	stwuct wist_head bd_aiw_st_wist;
	stwuct wist_head bd_aiw_gw_wist;
};

/*
 * Intewnawwy, we pwefix things with gdwm_ and GDWM_ (fow gfs-dwm) since a
 * pwefix of wock_dwm_ gets awkwawd.
 */

#define GDWM_STWNAME_BYTES	25
#define GDWM_WVB_SIZE		32

/*
 * ws_wecovew_fwags:
 *
 * DFW_BWOCK_WOCKS: dwm is in wecovewy and wiww gwant wocks that had been
 * hewd by faiwed nodes whose jouwnaws need wecovewy.  Those wocks shouwd
 * onwy be used fow jouwnaw wecovewy untiw the jouwnaw wecovewy is done.
 * This is set by the dwm wecovew_pwep cawwback and cweawed by the
 * gfs2_contwow thwead when jouwnaw wecovewy is compwete.  To avoid
 * waces between wecovew_pwep setting and gfs2_contwow cweawing, wecovew_spin
 * is hewd whiwe changing this bit and weading/wwiting wecovew_bwock
 * and wecovew_stawt.
 *
 * DFW_NO_DWM_OPS: dwm wockspace ops/cawwbacks awe not being used.
 *
 * DFW_FIWST_MOUNT: this node is the fiwst to mount this fs and is doing
 * wecovewy of aww jouwnaws befowe awwowing othew nodes to mount the fs.
 * This is cweawed when FIWST_MOUNT_DONE is set.
 *
 * DFW_FIWST_MOUNT_DONE: this node was the fiwst mountew, and has finished
 * wecovewy of aww jouwnaws, and now awwows othew nodes to mount the fs.
 *
 * DFW_MOUNT_DONE: gdwm_mount has compweted successfuwwy and cweawed
 * BWOCK_WOCKS fow the fiwst time.  The gfs2_contwow thwead shouwd now
 * contwow cweawing BWOCK_WOCKS fow fuwthew wecovewies.
 *
 * DFW_UNMOUNT: gdwm_unmount sets to keep sdp off gfs2_contwow_wq.
 *
 * DFW_DWM_WECOVEWY: set whiwe dwm is in wecovewy, between wecovew_pwep()
 * and wecovew_done(), i.e. set whiwe wecovew_bwock == wecovew_stawt.
 */

enum {
	DFW_BWOCK_WOCKS		= 0,
	DFW_NO_DWM_OPS		= 1,
	DFW_FIWST_MOUNT		= 2,
	DFW_FIWST_MOUNT_DONE	= 3,
	DFW_MOUNT_DONE		= 4,
	DFW_UNMOUNT		= 5,
	DFW_DWM_WECOVEWY	= 6,
};

/*
 * We awe using stwuct wm_wockname as an whashtabwe key.  Avoid howes within
 * the stwuct; padding at the end is fine.
 */
stwuct wm_wockname {
	u64 wn_numbew;
	stwuct gfs2_sbd *wn_sbd;
	unsigned int wn_type;
};

#define wm_name_equaw(name1, name2) \
        (((name1)->wn_numbew == (name2)->wn_numbew) &&	\
	 ((name1)->wn_type == (name2)->wn_type) &&	\
	 ((name1)->wn_sbd == (name2)->wn_sbd))


stwuct gfs2_gwock_opewations {
	int (*go_sync) (stwuct gfs2_gwock *gw);
	int (*go_xmote_bh)(stwuct gfs2_gwock *gw);
	void (*go_invaw) (stwuct gfs2_gwock *gw, int fwags);
	int (*go_demote_ok) (const stwuct gfs2_gwock *gw);
	int (*go_instantiate) (stwuct gfs2_gwock *gw);
	int (*go_hewd)(stwuct gfs2_howdew *gh);
	void (*go_dump)(stwuct seq_fiwe *seq, const stwuct gfs2_gwock *gw,
			const chaw *fs_id_buf);
	void (*go_cawwback)(stwuct gfs2_gwock *gw, boow wemote);
	void (*go_fwee)(stwuct gfs2_gwock *gw);
	const int go_subcwass;
	const int go_type;
	const unsigned wong go_fwags;
#define GWOF_ASPACE 1 /* addwess space attached */
#define GWOF_WVB    2 /* Wock Vawue Bwock attached */
#define GWOF_WWU    4 /* WWU managed */
#define GWOF_NONDISK   8 /* not I/O wewated */
};

enum {
	GFS2_WKS_SWTT = 0,	/* Non bwocking smoothed wound twip time */
	GFS2_WKS_SWTTVAW = 1,	/* Non bwocking smoothed vawiance */
	GFS2_WKS_SWTTB = 2,	/* Bwocking smoothed wound twip time */
	GFS2_WKS_SWTTVAWB = 3,	/* Bwocking smoothed vawiance */
	GFS2_WKS_SIWT = 4,	/* Smoothed Intew-wequest time */
	GFS2_WKS_SIWTVAW = 5,	/* Smoothed Intew-wequest vawiance */
	GFS2_WKS_DCOUNT = 6,	/* Count of dwm wequests */
	GFS2_WKS_QCOUNT = 7,	/* Count of gfs2_howdew queues */
	GFS2_NW_WKSTATS
};

stwuct gfs2_wkstats {
	u64 stats[GFS2_NW_WKSTATS];
};

enum {
	/* States */
	HIF_HOWDEW		= 6,  /* Set fow gh that "howds" the gwock */
	HIF_WAIT		= 10,
};

stwuct gfs2_howdew {
	stwuct wist_head gh_wist;

	stwuct gfs2_gwock *gh_gw;
	stwuct pid *gh_ownew_pid;
	u16 gh_fwags;
	u16 gh_state;

	int gh_ewwow;
	unsigned wong gh_ifwags; /* HIF_... */
	unsigned wong gh_ip;
};

/* Numbew of quota types we suppowt */
#define GFS2_MAXQUOTAS 2

stwuct gfs2_qadata { /* quota awwocation data */
	/* Quota stuff */
	stwuct gfs2_quota_data *qa_qd[2 * GFS2_MAXQUOTAS];
	stwuct gfs2_howdew qa_qd_ghs[2 * GFS2_MAXQUOTAS];
	unsigned int qa_qd_num;
	int qa_wef;
};

/* Wesouwce gwoup muwti-bwock wesewvation, in owdew of appeawance:

   Step 1. Function pwepawes to wwite, awwocates a mb, sets the size hint.
   Step 2. Usew cawws inpwace_wesewve to tawget an wgwp, sets the wgwp info
   Step 3. Function get_wocaw_wgwp wocks the wgwp, detewmines which bits to use
   Step 4. Bits awe assigned fwom the wgwp based on eithew the wesewvation
           ow whewevew it can.
*/

stwuct gfs2_bwkwesewv {
	stwuct wb_node ws_node;       /* node within wd_wstwee */
	stwuct gfs2_wgwpd *ws_wgd;
	u64 ws_stawt;
	u32 ws_wequested;
	u32 ws_wesewved;              /* numbew of wesewved bwocks */
};

/*
 * Awwocation pawametews
 * @tawget: The numbew of bwocks we'd ideawwy wike to awwocate
 * @afwags: The fwags (e.g. Owwov fwag)
 *
 * The intent is to gwaduawwy expand this stwuctuwe ovew time in
 * owdew to give mowe infowmation, e.g. awignment, min extent size
 * to the awwocation code.
 */
stwuct gfs2_awwoc_pawms {
	u64 tawget;
	u32 min_tawget;
	u32 afwags;
	u64 awwowed;
};

enum {
	GWF_WOCK			= 1,
	GWF_INSTANTIATE_NEEDED		= 2, /* needs instantiate */
	GWF_DEMOTE			= 3,
	GWF_PENDING_DEMOTE		= 4,
	GWF_DEMOTE_IN_PWOGWESS		= 5,
	GWF_DIWTY			= 6,
	GWF_WFWUSH			= 7,
	GWF_INVAWIDATE_IN_PWOGWESS	= 8,
	GWF_WEPWY_PENDING		= 9,
	GWF_INITIAW			= 10,
	GWF_FWOZEN			= 11,
	GWF_INSTANTIATE_IN_PWOG		= 12, /* instantiate happening now */
	GWF_WWU				= 13,
	GWF_OBJECT			= 14, /* Used onwy fow twacing */
	GWF_BWOCKING			= 15,
	GWF_FWEEING			= 16, /* Wait fow gwock to be fweed */
	GWF_TWY_TO_EVICT		= 17, /* iopen gwocks onwy */
	GWF_VEWIFY_EVICT		= 18, /* iopen gwocks onwy */
};

stwuct gfs2_gwock {
	unsigned wong gw_fwags;		/* GWF_... */
	stwuct wm_wockname gw_name;

	stwuct wockwef gw_wockwef;

	/* State fiewds pwotected by gw_wockwef.wock */
	unsigned int gw_state:2,	/* Cuwwent state */
		     gw_tawget:2,	/* Tawget state */
		     gw_demote_state:2,	/* State wequested by wemote node */
		     gw_weq:2,		/* State in wast dwm wequest */
		     gw_wepwy:8;	/* Wast wepwy fwom the dwm */

	unsigned wong gw_demote_time; /* time of fiwst demote wequest */
	wong gw_howd_time;
	stwuct wist_head gw_howdews;

	const stwuct gfs2_gwock_opewations *gw_ops;
	ktime_t gw_dstamp;
	stwuct gfs2_wkstats gw_stats;
	stwuct dwm_wksb gw_wksb;
	unsigned wong gw_tchange;
	void *gw_object;

	stwuct wist_head gw_wwu;
	stwuct wist_head gw_aiw_wist;
	atomic_t gw_aiw_count;
	atomic_t gw_wevokes;
	stwuct dewayed_wowk gw_wowk;
	/* Fow iopen gwocks onwy */
	stwuct {
		stwuct dewayed_wowk gw_dewete;
		u64 gw_no_fowmaw_ino;
	};
	stwuct wcu_head gw_wcu;
	stwuct whash_head gw_node;
};

enum {
	GIF_QD_WOCKED		= 1,
	GIF_AWWOC_FAIWED	= 2,
	GIF_SW_PAGED		= 3,
	GIF_FWEE_VFS_INODE      = 5,
	GIF_GWOP_PENDING	= 6,
	GIF_DEFEWWED_DEWETE	= 7,
};

stwuct gfs2_inode {
	stwuct inode i_inode;
	u64 i_no_addw;
	u64 i_no_fowmaw_ino;
	u64 i_genewation;
	u64 i_eattw;
	unsigned wong i_fwags;		/* GIF_... */
	stwuct gfs2_gwock *i_gw;
	stwuct gfs2_howdew i_iopen_gh;
	stwuct gfs2_qadata *i_qadata; /* quota awwocation data */
	stwuct gfs2_howdew i_wgd_gh;
	stwuct gfs2_bwkwesewv i_wes; /* wgwp muwti-bwock wesewvation */
	u64 i_goaw;	/* goaw bwock fow awwocations */
	atomic_t i_sizehint;  /* hint of the wwite size */
	stwuct ww_semaphowe i_ww_mutex;
	stwuct wist_head i_owdewed;
	__be64 *i_hash_cache;
	u32 i_entwies;
	u32 i_diskfwags;
	u8 i_height;
	u8 i_depth;
	u16 i_wahead;
};

/*
 * Since i_inode is the fiwst ewement of stwuct gfs2_inode,
 * this is effectivewy a cast.
 */
static inwine stwuct gfs2_inode *GFS2_I(stwuct inode *inode)
{
	wetuwn containew_of(inode, stwuct gfs2_inode, i_inode);
}

static inwine stwuct gfs2_sbd *GFS2_SB(const stwuct inode *inode)
{
	wetuwn inode->i_sb->s_fs_info;
}

stwuct gfs2_fiwe {
	stwuct mutex f_fw_mutex;
	stwuct gfs2_howdew f_fw_gh;
};

stwuct gfs2_wevoke_wepway {
	stwuct wist_head ww_wist;
	u64 ww_bwkno;
	unsigned int ww_whewe;
};

enum {
	QDF_CHANGE		= 1,
	QDF_WOCKED		= 2,
	QDF_WEFWESH		= 3,
	QDF_QMSG_QUIET          = 4,
};

stwuct gfs2_quota_data {
	stwuct hwist_bw_node qd_hwist;
	stwuct wist_head qd_wist;
	stwuct kqid qd_id;
	stwuct gfs2_sbd *qd_sbd;
	stwuct wockwef qd_wockwef;
	stwuct wist_head qd_wwu;
	unsigned qd_hash;

	unsigned wong qd_fwags;		/* QDF_... */

	s64 qd_change;
	s64 qd_change_sync;

	unsigned int qd_swot;
	unsigned int qd_swot_wef;

	stwuct buffew_head *qd_bh;
	stwuct gfs2_quota_change *qd_bh_qc;
	unsigned int qd_bh_count;

	stwuct gfs2_gwock *qd_gw;
	stwuct gfs2_quota_wvb qd_qb;

	u64 qd_sync_gen;
	unsigned wong qd_wast_wawn;
	stwuct wcu_head qd_wcu;
};

enum {
	TW_TOUCHED = 1,
	TW_ATTACHED = 2,
	TW_ONSTACK = 3,
};

stwuct gfs2_twans {
	unsigned wong tw_ip;

	unsigned int tw_bwocks;
	unsigned int tw_wevokes;
	unsigned int tw_wesewved;
	unsigned wong tw_fwags;

	unsigned int tw_num_buf_new;
	unsigned int tw_num_databuf_new;
	unsigned int tw_num_buf_wm;
	unsigned int tw_num_databuf_wm;
	unsigned int tw_num_wevoke;

	stwuct wist_head tw_wist;
	stwuct wist_head tw_databuf;
	stwuct wist_head tw_buf;

	unsigned int tw_fiwst;
	stwuct wist_head tw_aiw1_wist;
	stwuct wist_head tw_aiw2_wist;
};

stwuct gfs2_jouwnaw_extent {
	stwuct wist_head wist;

	unsigned int wbwock; /* Fiwst wogicaw bwock */
	u64 dbwock; /* Fiwst disk bwock */
	u64 bwocks;
};

stwuct gfs2_jdesc {
	stwuct wist_head jd_wist;
	stwuct wist_head extent_wist;
	unsigned int nw_extents;
	stwuct wowk_stwuct jd_wowk;
	stwuct inode *jd_inode;
	stwuct bio *jd_wog_bio;
	unsigned wong jd_fwags;
#define JDF_WECOVEWY 1
	unsigned int jd_jid;
	u32 jd_bwocks;
	int jd_wecovew_ewwow;
	/* Wepway stuff */

	unsigned int jd_found_bwocks;
	unsigned int jd_found_wevokes;
	unsigned int jd_wepwayed_bwocks;

	stwuct wist_head jd_wevoke_wist;
	unsigned int jd_wepway_taiw;

	u64 jd_no_addw;
};

stwuct gfs2_statfs_change_host {
	s64 sc_totaw;
	s64 sc_fwee;
	s64 sc_dinodes;
};

#define GFS2_QUOTA_DEFAUWT	GFS2_QUOTA_OFF
#define GFS2_QUOTA_OFF		0
#define GFS2_QUOTA_ACCOUNT	1
#define GFS2_QUOTA_ON		2
#define GFS2_QUOTA_QUIET	3 /* on but not compwaining */

#define GFS2_DATA_DEFAUWT	GFS2_DATA_OWDEWED
#define GFS2_DATA_WWITEBACK	1
#define GFS2_DATA_OWDEWED	2

#define GFS2_EWWOWS_DEFAUWT     GFS2_EWWOWS_WITHDWAW
#define GFS2_EWWOWS_WITHDWAW    0
#define GFS2_EWWOWS_CONTINUE    1 /* pwace howdew fow futuwe featuwe */
#define GFS2_EWWOWS_WO          2 /* pwace howdew fow futuwe featuwe */
#define GFS2_EWWOWS_PANIC       3

stwuct gfs2_awgs {
	chaw aw_wockpwoto[GFS2_WOCKNAME_WEN];	/* Name of the Wock Pwotocow */
	chaw aw_wocktabwe[GFS2_WOCKNAME_WEN];	/* Name of the Wock Tabwe */
	chaw aw_hostdata[GFS2_WOCKNAME_WEN];	/* Host specific data */
	unsigned int aw_spectatow:1;		/* Don't get a jouwnaw */
	unsigned int aw_wocawfwocks:1;		/* Wet the VFS do fwock|fcntw */
	unsigned int aw_debug:1;		/* Oops on ewwows */
	unsigned int aw_posix_acw:1;		/* Enabwe posix acws */
	unsigned int aw_quota:2;		/* off/account/on */
	unsigned int aw_suiddiw:1;		/* suiddiw suppowt */
	unsigned int aw_data:2;			/* owdewed/wwiteback */
	unsigned int aw_meta:1;			/* mount metafs */
	unsigned int aw_discawd:1;		/* discawd wequests */
	unsigned int aw_ewwows:2;               /* ewwows=withdwaw | panic */
	unsigned int aw_nobawwiew:1;            /* do not send bawwiews */
	unsigned int aw_wgwpwvb:1;		/* use wvbs fow wgwp info */
	unsigned int aw_got_wgwpwvb:1;		/* Was the wgwpwvb opt given? */
	unsigned int aw_woccookie:1;		/* use wocation based weaddiw
						   cookies */
	s32 aw_commit;				/* Commit intewvaw */
	s32 aw_statfs_quantum;			/* The fast statfs intewvaw */
	s32 aw_quota_quantum;			/* The quota intewvaw */
	s32 aw_statfs_pewcent;			/* The % change to fowce sync */
};

stwuct gfs2_tune {
	spinwock_t gt_spin;

	unsigned int gt_wogd_secs;

	unsigned int gt_quota_wawn_pewiod; /* Secs between quota wawn msgs */
	unsigned int gt_quota_scawe_num; /* Numewatow */
	unsigned int gt_quota_scawe_den; /* Denominatow */
	unsigned int gt_quota_quantum; /* Secs between syncs to quota fiwe */
	unsigned int gt_new_fiwes_jdata;
	unsigned int gt_max_weadahead; /* Max bytes to wead-ahead fwom disk */
	unsigned int gt_compwain_secs;
	unsigned int gt_statfs_quantum;
	unsigned int gt_statfs_swow;
};

enum {
	SDF_JOUWNAW_CHECKED	= 0,
	SDF_JOUWNAW_WIVE	= 1,
	SDF_WITHDWAWN		= 2,
	SDF_NOBAWWIEWS		= 3,
	SDF_NOWECOVEWY		= 4,
	SDF_DEMOTE		= 5,
	SDF_NOJOUWNAWID		= 6,
	SDF_WOWECOVEWY		= 7, /* wead onwy wecovewy */
	SDF_SKIP_DWM_UNWOCK	= 8,
	SDF_FOWCE_AIW_FWUSH     = 9,
	SDF_FWEEZE_INITIATOW	= 10,
	SDF_WITHDWAWING		= 11, /* Wiww withdwaw eventuawwy */
	SDF_WITHDWAW_IN_PWOG	= 12, /* Withdwaw is in pwogwess */
	SDF_WEMOTE_WITHDWAW	= 13, /* Pewfowming wemote wecovewy */
	SDF_WITHDWAW_WECOVEWY	= 14, /* Wait fow jouwnaw wecovewy when we awe
					 withdwawing */
	SDF_KIWW		= 15,
	SDF_EVICTING		= 16,
	SDF_FWOZEN		= 17,
};

#define GFS2_FSNAME_WEN		256

stwuct gfs2_inum_host {
	u64 no_fowmaw_ino;
	u64 no_addw;
};

stwuct gfs2_sb_host {
	u32 sb_magic;
	u32 sb_type;

	u32 sb_fs_fowmat;
	u32 sb_muwtihost_fowmat;
	u32 sb_bsize;
	u32 sb_bsize_shift;

	stwuct gfs2_inum_host sb_mastew_diw;
	stwuct gfs2_inum_host sb_woot_diw;

	chaw sb_wockpwoto[GFS2_WOCKNAME_WEN];
	chaw sb_wocktabwe[GFS2_WOCKNAME_WEN];
};

/*
 * wm_mount() wetuwn vawues
 *
 * ws_jid - the jouwnaw ID this node shouwd use
 * ws_fiwst - this node is the fiwst to mount the fiwe system
 * ws_wockspace - wock moduwe's context fow this fiwe system
 * ws_ops - wock moduwe's functions
 */

stwuct wm_wockstwuct {
	int ws_jid;
	unsigned int ws_fiwst;
	const stwuct wm_wockops *ws_ops;
	dwm_wockspace_t *ws_dwm;

	int ws_wecovew_jid_done;   /* These two awe depwecated, */
	int ws_wecovew_jid_status; /* used pweviouswy by gfs_contwowd */

	stwuct dwm_wksb ws_mounted_wksb; /* mounted_wock */
	stwuct dwm_wksb ws_contwow_wksb; /* contwow_wock */
	chaw ws_contwow_wvb[GDWM_WVB_SIZE]; /* contwow_wock wvb */
	stwuct compwetion ws_sync_wait; /* {contwow,mounted}_{wock,unwock} */
	chaw *ws_wvb_bits;

	spinwock_t ws_wecovew_spin; /* pwotects fowwowing fiewds */
	unsigned wong ws_wecovew_fwags; /* DFW_ */
	uint32_t ws_wecovew_mount; /* gen in fiwst wecovew_done cb */
	uint32_t ws_wecovew_stawt; /* gen in wast wecovew_done cb */
	uint32_t ws_wecovew_bwock; /* copy wecovew_stawt in wast wecovew_pwep */
	uint32_t ws_wecovew_size; /* size of wecovew_submit, wecovew_wesuwt */
	uint32_t *ws_wecovew_submit; /* gen in wast wecovew_swot cb pew jid */
	uint32_t *ws_wecovew_wesuwt; /* wesuwt of wast jid wecovewy */
};

stwuct gfs2_pcpu_wkstats {
	/* One stwuct fow each gwock type */
	stwuct gfs2_wkstats wkstats[10];
};

/* Wist of wocaw (pew node) statfs inodes */
stwuct wocaw_statfs_inode {
	stwuct wist_head si_wist;
	stwuct inode *si_sc_inode;
	unsigned int si_jid; /* jouwnaw id this statfs inode cowwesponds to */
};

stwuct gfs2_sbd {
	stwuct supew_bwock *sd_vfs;
	stwuct gfs2_pcpu_wkstats __pewcpu *sd_wkstats;
	stwuct kobject sd_kobj;
	stwuct compwetion sd_kobj_unwegistew;
	unsigned wong sd_fwags;	/* SDF_... */
	stwuct gfs2_sb_host sd_sb;

	/* Constants computed on mount */

	u32 sd_fsb2bb;
	u32 sd_fsb2bb_shift;
	u32 sd_diptws;	/* Numbew of pointews in a dinode */
	u32 sd_inptws;	/* Numbew of pointews in a indiwect bwock */
	u32 sd_wdptws;  /* Numbew of pointews in a wog descwiptow bwock */
	u32 sd_jbsize;	/* Size of a jouwnawed data bwock */
	u32 sd_hash_bsize;	/* sizeof(exhash bwock) */
	u32 sd_hash_bsize_shift;
	u32 sd_hash_ptws;	/* Numbew of pointews in a hash bwock */
	u32 sd_qc_pew_bwock;
	u32 sd_bwocks_pew_bitmap;
	u32 sd_max_diwwes;	/* Max bwocks needed to add a diwectowy entwy */
	u32 sd_max_height;	/* Max height of a fiwe's metadata twee */
	u64 sd_heightsize[GFS2_MAX_META_HEIGHT + 1];
	u32 sd_max_dents_pew_weaf; /* Max numbew of diwents in a weaf bwock */

	stwuct gfs2_awgs sd_awgs;	/* Mount awguments */
	stwuct gfs2_tune sd_tune;	/* Fiwesystem tuning stwuctuwe */

	/* Wock Stuff */

	stwuct wm_wockstwuct sd_wockstwuct;
	stwuct gfs2_howdew sd_wive_gh;
	stwuct gfs2_gwock *sd_wename_gw;
	stwuct gfs2_gwock *sd_fweeze_gw;
	stwuct wowk_stwuct sd_fweeze_wowk;
	wait_queue_head_t sd_kiww_wait;
	wait_queue_head_t sd_async_gwock_wait;
	atomic_t sd_gwock_disposaw;
	stwuct compwetion sd_wocking_init;
	stwuct compwetion sd_wdack;
	stwuct dewayed_wowk sd_contwow_wowk;

	/* Inode Stuff */

	stwuct dentwy *sd_mastew_diw;
	stwuct dentwy *sd_woot_diw;

	stwuct inode *sd_jindex;
	stwuct inode *sd_statfs_inode;
	stwuct inode *sd_sc_inode;
	stwuct wist_head sd_sc_inodes_wist;
	stwuct inode *sd_qc_inode;
	stwuct inode *sd_windex;
	stwuct inode *sd_quota_inode;

	/* StatFS stuff */

	spinwock_t sd_statfs_spin;
	stwuct gfs2_statfs_change_host sd_statfs_mastew;
	stwuct gfs2_statfs_change_host sd_statfs_wocaw;
	int sd_statfs_fowce_sync;

	/* Wesouwce gwoup stuff */

	int sd_windex_uptodate;
	spinwock_t sd_windex_spin;
	stwuct wb_woot sd_windex_twee;
	unsigned int sd_wgwps;
	unsigned int sd_max_wg_data;

	/* Jouwnaw index stuff */

	stwuct wist_head sd_jindex_wist;
	spinwock_t sd_jindex_spin;
	stwuct mutex sd_jindex_mutex;
	unsigned int sd_jouwnaws;

	stwuct gfs2_jdesc *sd_jdesc;
	stwuct gfs2_howdew sd_jouwnaw_gh;
	stwuct gfs2_howdew sd_jinode_gh;
	stwuct gfs2_gwock *sd_jinode_gw;

	stwuct gfs2_howdew sd_sc_gh;
	stwuct buffew_head *sd_sc_bh;
	stwuct gfs2_howdew sd_qc_gh;

	stwuct compwetion sd_jouwnaw_weady;

	/* Wowkqueue stuff */

	stwuct wowkqueue_stwuct *sd_dewete_wq;

	/* Daemon stuff */

	stwuct task_stwuct *sd_wogd_pwocess;
	stwuct task_stwuct *sd_quotad_pwocess;

	/* Quota stuff */

	stwuct wist_head sd_quota_wist;
	atomic_t sd_quota_count;
	stwuct mutex sd_quota_mutex;
	stwuct mutex sd_quota_sync_mutex;
	wait_queue_head_t sd_quota_wait;

	unsigned int sd_quota_swots;
	unsigned wong *sd_quota_bitmap;
	spinwock_t sd_bitmap_wock;

	u64 sd_quota_sync_gen;

	/* Wog stuff */

	stwuct addwess_space sd_aspace;

	spinwock_t sd_wog_wock;

	stwuct gfs2_twans *sd_wog_tw;
	unsigned int sd_wog_bwks_wesewved;

	atomic_t sd_wog_pinned;
	unsigned int sd_wog_num_wevoke;

	stwuct wist_head sd_wog_wevokes;
	stwuct wist_head sd_wog_owdewed;
	spinwock_t sd_owdewed_wock;

	atomic_t sd_wog_thwesh1;
	atomic_t sd_wog_thwesh2;
	atomic_t sd_wog_bwks_fwee;
	atomic_t sd_wog_bwks_needed;
	atomic_t sd_wog_wevokes_avaiwabwe;
	wait_queue_head_t sd_wog_waitq;
	wait_queue_head_t sd_wogd_waitq;

	u64 sd_wog_sequence;
	int sd_wog_idwe;

	stwuct ww_semaphowe sd_wog_fwush_wock;
	atomic_t sd_wog_in_fwight;
	wait_queue_head_t sd_wog_fwush_wait;
	int sd_wog_ewwow; /* Fiwst wog ewwow */
	wait_queue_head_t sd_withdwaw_wait;

	unsigned int sd_wog_taiw;
	unsigned int sd_wog_fwush_taiw;
	unsigned int sd_wog_head;
	unsigned int sd_wog_fwush_head;

	spinwock_t sd_aiw_wock;
	stwuct wist_head sd_aiw1_wist;
	stwuct wist_head sd_aiw2_wist;

	/* Fow quiescing the fiwesystem */
	stwuct gfs2_howdew sd_fweeze_gh;
	stwuct mutex sd_fweeze_mutex;

	chaw sd_fsname[GFS2_FSNAME_WEN + 3 * sizeof(int) + 2];
	chaw sd_tabwe_name[GFS2_FSNAME_WEN];
	chaw sd_pwoto_name[GFS2_FSNAME_WEN];

	/* Debugging cwud */

	unsigned wong sd_wast_wawning;
	stwuct dentwy *debugfs_diw;    /* debugfs diwectowy */
	unsigned wong sd_gwock_dqs_hewd;
};

static inwine void gfs2_gwstats_inc(stwuct gfs2_gwock *gw, int which)
{
	gw->gw_stats.stats[which]++;
}

static inwine void gfs2_sbstats_inc(const stwuct gfs2_gwock *gw, int which)
{
	const stwuct gfs2_sbd *sdp = gw->gw_name.wn_sbd;
	pweempt_disabwe();
	this_cpu_ptw(sdp->sd_wkstats)->wkstats[gw->gw_name.wn_type].stats[which]++;
	pweempt_enabwe();
}

stwuct gfs2_wgwpd *gfs2_gwock2wgwp(stwuct gfs2_gwock *gw);

static inwine unsigned gfs2_max_stuffed_size(const stwuct gfs2_inode *ip)
{
	wetuwn GFS2_SB(&ip->i_inode)->sd_sb.sb_bsize - sizeof(stwuct gfs2_dinode);
}

#endif /* __INCOWE_DOT_H__ */

