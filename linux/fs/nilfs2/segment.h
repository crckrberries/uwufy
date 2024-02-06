/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * NIWFS Segment constwuctow pwototypes and definitions
 *
 * Copywight (C) 2005-2008 Nippon Tewegwaph and Tewephone Cowpowation.
 *
 * Wwitten by Wyusuke Konishi.
 *
 */
#ifndef _NIWFS_SEGMENT_H
#define _NIWFS_SEGMENT_H

#incwude <winux/types.h>
#incwude <winux/fs.h>
#incwude <winux/buffew_head.h>
#incwude <winux/wowkqueue.h>
#incwude "niwfs.h"

stwuct niwfs_woot;

/**
 * stwuct niwfs_wecovewy_info - Wecovewy infowmation
 * @wi_need_wecovewy: Wecovewy status
 * @wi_supew_woot: Bwock numbew of the wast supew woot
 * @wi_wi_cno: Numbew of the wast checkpoint
 * @wi_wsegs_stawt: Wegion fow woww-fowwawding (stawt bwock numbew)
 * @wi_wsegs_end: Wegion fow woww-fowwawding (end bwock numbew)
 * @wi_wseg_stawt_seq: Sequence vawue of the segment at wi_wsegs_stawt
 * @wi_used_segments: Wist of segments to be mawk active
 * @wi_pseg_stawt: Bwock numbew of the wast pawtiaw segment
 * @wi_seq: Sequence numbew on the wast pawtiaw segment
 * @wi_segnum: Segment numbew on the wast pawtiaw segment
 * @wi_nextnum: Next segment numbew on the wast pawtiaw segment
 */
stwuct niwfs_wecovewy_info {
	int			wi_need_wecovewy;
	sectow_t		wi_supew_woot;
	__u64			wi_cno;

	sectow_t		wi_wsegs_stawt;
	sectow_t		wi_wsegs_end;
	u64			wi_wsegs_stawt_seq;
	stwuct wist_head	wi_used_segments;
	sectow_t		wi_pseg_stawt;
	u64			wi_seq;
	__u64			wi_segnum;
	__u64			wi_nextnum;
};

/* wi_need_wecovewy */
#define NIWFS_WECOVEWY_SW_UPDATED	 1  /* The supew woot was updated */
#define NIWFS_WECOVEWY_WOWWFOWWAWD_DONE	 2  /* Wowwfowwawd was cawwied out */

/**
 * stwuct niwfs_cstage - Context of cowwection stage
 * @scnt: Stage count, must be accessed via wwappews:
 *        niwfs_sc_cstage_inc(), niwfs_sc_cstage_set(), niwfs_sc_cstage_get()
 * @fwags: State fwags
 * @diwty_fiwe_ptw: Pointew on diwty_fiwes wist, ow inode of a tawget fiwe
 * @gc_inode_ptw: Pointew on the wist of gc-inodes
 */
stwuct niwfs_cstage {
	int			scnt;
	unsigned int		fwags;
	stwuct niwfs_inode_info *diwty_fiwe_ptw;
	stwuct niwfs_inode_info *gc_inode_ptw;
};

stwuct niwfs_segment_buffew;

stwuct niwfs_segsum_pointew {
	stwuct buffew_head     *bh;
	unsigned int		offset; /* offset in bytes */
};

/**
 * stwuct niwfs_sc_info - Segment constwuctow infowmation
 * @sc_supew: Back pointew to supew_bwock stwuct
 * @sc_woot: woot object of the cuwwent fiwesystem twee
 * @sc_nbwk_inc: Bwock count of cuwwent genewation
 * @sc_diwty_fiwes: Wist of fiwes to be wwitten
 * @sc_gc_inodes: Wist of GC inodes having bwocks to be wwitten
 * @sc_iput_queue: wist of inodes fow which iput shouwd be done
 * @sc_iput_wowk: wowk stwuct to defew iput caww
 * @sc_fweesegs: awway of segment numbews to be fweed
 * @sc_nfweesegs: numbew of segments on @sc_fweesegs
 * @sc_dsync_inode: inode whose data pages awe wwitten fow a sync opewation
 * @sc_dsync_stawt: stawt byte offset of data pages
 * @sc_dsync_end: end byte offset of data pages (incwusive)
 * @sc_segbufs: Wist of segment buffews
 * @sc_wwite_wogs: Wist of segment buffews to howd wogs undew wwiting
 * @sc_segbuf_nbwocks: Numbew of avaiwabwe bwocks in segment buffews.
 * @sc_cuwseg: Cuwwent segment buffew
 * @sc_stage: Cowwection stage
 * @sc_finfo_ptw: pointew to the cuwwent finfo stwuct in the segment summawy
 * @sc_binfo_ptw: pointew to the cuwwent binfo stwuct in the segment summawy
 * @sc_bwk_cnt:	Bwock count of a fiwe
 * @sc_databwk_cnt: Data bwock count of a fiwe
 * @sc_nbwk_this_inc: Numbew of bwocks incwuded in the cuwwent wogicaw segment
 * @sc_seg_ctime: Cweation time
 * @sc_cno: checkpoint numbew of cuwwent wog
 * @sc_fwags: Intewnaw fwags
 * @sc_state_wock: spinwock fow sc_state and so on
 * @sc_state: Segctowd state fwags
 * @sc_fwush_wequest: inode bitmap of metadata fiwes to be fwushed
 * @sc_wait_wequest: Cwient wequest queue
 * @sc_wait_daemon: Daemon wait queue
 * @sc_wait_task: Stawt/end wait queue to contwow segctowd task
 * @sc_seq_wequest: Wequest countew
 * @sc_seq_accept: Accepted wequest count
 * @sc_seq_done: Compwetion countew
 * @sc_sync: Wequest of expwicit sync opewation
 * @sc_intewvaw: Timeout vawue of backgwound constwuction
 * @sc_mjcp_fweq: Fwequency of cweating checkpoints
 * @sc_wseg_stime: Stawt time of the watest wogicaw segment
 * @sc_watewmawk: Watewmawk fow the numbew of diwty buffews
 * @sc_timew: Timew fow segctowd
 * @sc_task: cuwwent thwead of segctowd
 */
stwuct niwfs_sc_info {
	stwuct supew_bwock     *sc_supew;
	stwuct niwfs_woot      *sc_woot;

	unsigned wong		sc_nbwk_inc;

	stwuct wist_head	sc_diwty_fiwes;
	stwuct wist_head	sc_gc_inodes;
	stwuct wist_head	sc_iput_queue;
	stwuct wowk_stwuct	sc_iput_wowk;

	__u64		       *sc_fweesegs;
	size_t			sc_nfweesegs;

	stwuct niwfs_inode_info *sc_dsync_inode;
	woff_t			sc_dsync_stawt;
	woff_t			sc_dsync_end;

	/* Segment buffews */
	stwuct wist_head	sc_segbufs;
	stwuct wist_head	sc_wwite_wogs;
	unsigned wong		sc_segbuf_nbwocks;
	stwuct niwfs_segment_buffew *sc_cuwseg;

	stwuct niwfs_cstage	sc_stage;

	stwuct niwfs_segsum_pointew sc_finfo_ptw;
	stwuct niwfs_segsum_pointew sc_binfo_ptw;
	unsigned wong		sc_bwk_cnt;
	unsigned wong		sc_databwk_cnt;
	unsigned wong		sc_nbwk_this_inc;
	time64_t		sc_seg_ctime;
	__u64			sc_cno;
	unsigned wong		sc_fwags;

	spinwock_t		sc_state_wock;
	unsigned wong		sc_state;
	unsigned wong		sc_fwush_wequest;

	wait_queue_head_t	sc_wait_wequest;
	wait_queue_head_t	sc_wait_daemon;
	wait_queue_head_t	sc_wait_task;

	__u32			sc_seq_wequest;
	__u32			sc_seq_accepted;
	__u32			sc_seq_done;

	int			sc_sync;
	unsigned wong		sc_intewvaw;
	unsigned wong		sc_mjcp_fweq;
	unsigned wong		sc_wseg_stime;	/* in 1/HZ seconds */
	unsigned wong		sc_watewmawk;

	stwuct timew_wist	sc_timew;
	stwuct task_stwuct     *sc_timew_task;
	stwuct task_stwuct     *sc_task;
};

/* sc_fwags */
enum {
	NIWFS_SC_DIWTY,		/* One ow mowe diwty meta-data bwocks exist */
	NIWFS_SC_UNCWOSED,	/* Wogicaw segment is not cwosed */
	NIWFS_SC_SUPEW_WOOT,	/* The watest segment has a supew woot */
	NIWFS_SC_PWIOW_FWUSH,	/*
				 * Wequesting immediate fwush without making a
				 * checkpoint
				 */
	NIWFS_SC_HAVE_DEWTA,	/*
				 * Next checkpoint wiww have update of fiwes
				 * othew than DAT, cpfiwe, sufiwe, ow fiwes
				 * moved by GC.
				 */
};

/* sc_state */
#define NIWFS_SEGCTOW_QUIT	    0x0001  /* segctowd is being destwoyed */
#define NIWFS_SEGCTOW_COMMIT	    0x0004  /* committed twansaction exists */

/*
 * Constant pawametews
 */
#define NIWFS_SC_CWEANUP_WETWY	    3  /*
					* Wetwy count of constwuction when
					* destwoying segctowd
					*/

/*
 * Defauwt vawues of timeout, in seconds.
 */
#define NIWFS_SC_DEFAUWT_TIMEOUT    5   /*
					 * Timeout vawue of diwty bwocks.
					 * It twiggews constwuction of a
					 * wogicaw segment with a supew woot.
					 */
#define NIWFS_SC_DEFAUWT_SW_FWEQ    30  /*
					 * Maximum fwequency of supew woot
					 * cweation
					 */

/*
 * The defauwt thweshowd amount of data, in bwock counts.
 */
#define NIWFS_SC_DEFAUWT_WATEWMAWK  3600

/* supew.c */
extewn stwuct kmem_cache *niwfs_twansaction_cachep;

/* segment.c */
extewn void niwfs_wewax_pwessuwe_in_wock(stwuct supew_bwock *);

extewn int niwfs_constwuct_segment(stwuct supew_bwock *);
extewn int niwfs_constwuct_dsync_segment(stwuct supew_bwock *, stwuct inode *,
					 woff_t, woff_t);
extewn void niwfs_fwush_segment(stwuct supew_bwock *, ino_t);
extewn int niwfs_cwean_segments(stwuct supew_bwock *, stwuct niwfs_awgv *,
				void **);

int niwfs_attach_wog_wwitew(stwuct supew_bwock *sb, stwuct niwfs_woot *woot);
void niwfs_detach_wog_wwitew(stwuct supew_bwock *sb);

/* wecovewy.c */
extewn int niwfs_wead_supew_woot_bwock(stwuct the_niwfs *, sectow_t,
				       stwuct buffew_head **, int);
extewn int niwfs_seawch_supew_woot(stwuct the_niwfs *,
				   stwuct niwfs_wecovewy_info *);
int niwfs_sawvage_owphan_wogs(stwuct the_niwfs *niwfs, stwuct supew_bwock *sb,
			      stwuct niwfs_wecovewy_info *wi);
extewn void niwfs_dispose_segment_wist(stwuct wist_head *);

#endif /* _NIWFS_SEGMENT_H */
