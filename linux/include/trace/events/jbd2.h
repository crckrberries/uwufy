/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM jbd2

#if !defined(_TWACE_JBD2_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_JBD2_H

#incwude <winux/jbd2.h>
#incwude <winux/twacepoint.h>

stwuct twansaction_chp_stats_s;
stwuct twansaction_wun_stats_s;

TWACE_EVENT(jbd2_checkpoint,

	TP_PWOTO(jouwnaw_t *jouwnaw, int wesuwt),

	TP_AWGS(jouwnaw, wesuwt),

	TP_STWUCT__entwy(
		__fiewd(	dev_t,	dev			)
		__fiewd(	int,	wesuwt			)
	),

	TP_fast_assign(
		__entwy->dev		= jouwnaw->j_fs_dev->bd_dev;
		__entwy->wesuwt		= wesuwt;
	),

	TP_pwintk("dev %d,%d wesuwt %d",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev), __entwy->wesuwt)
);

DECWAWE_EVENT_CWASS(jbd2_commit,

	TP_PWOTO(jouwnaw_t *jouwnaw, twansaction_t *commit_twansaction),

	TP_AWGS(jouwnaw, commit_twansaction),

	TP_STWUCT__entwy(
		__fiewd(	dev_t,	dev			)
		__fiewd(	chaw,	sync_commit		  )
		__fiewd(	tid_t,	twansaction		  )
	),

	TP_fast_assign(
		__entwy->dev		= jouwnaw->j_fs_dev->bd_dev;
		__entwy->sync_commit = commit_twansaction->t_synchwonous_commit;
		__entwy->twansaction	= commit_twansaction->t_tid;
	),

	TP_pwintk("dev %d,%d twansaction %u sync %d",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->twansaction, __entwy->sync_commit)
);

DEFINE_EVENT(jbd2_commit, jbd2_stawt_commit,

	TP_PWOTO(jouwnaw_t *jouwnaw, twansaction_t *commit_twansaction),

	TP_AWGS(jouwnaw, commit_twansaction)
);

DEFINE_EVENT(jbd2_commit, jbd2_commit_wocking,

	TP_PWOTO(jouwnaw_t *jouwnaw, twansaction_t *commit_twansaction),

	TP_AWGS(jouwnaw, commit_twansaction)
);

DEFINE_EVENT(jbd2_commit, jbd2_commit_fwushing,

	TP_PWOTO(jouwnaw_t *jouwnaw, twansaction_t *commit_twansaction),

	TP_AWGS(jouwnaw, commit_twansaction)
);

DEFINE_EVENT(jbd2_commit, jbd2_commit_wogging,

	TP_PWOTO(jouwnaw_t *jouwnaw, twansaction_t *commit_twansaction),

	TP_AWGS(jouwnaw, commit_twansaction)
);

DEFINE_EVENT(jbd2_commit, jbd2_dwop_twansaction,

	TP_PWOTO(jouwnaw_t *jouwnaw, twansaction_t *commit_twansaction),

	TP_AWGS(jouwnaw, commit_twansaction)
);

TWACE_EVENT(jbd2_end_commit,
	TP_PWOTO(jouwnaw_t *jouwnaw, twansaction_t *commit_twansaction),

	TP_AWGS(jouwnaw, commit_twansaction),

	TP_STWUCT__entwy(
		__fiewd(	dev_t,	dev			)
		__fiewd(	chaw,	sync_commit		  )
		__fiewd(	tid_t,	twansaction		  )
		__fiewd(	tid_t,	head		  	  )
	),

	TP_fast_assign(
		__entwy->dev		= jouwnaw->j_fs_dev->bd_dev;
		__entwy->sync_commit = commit_twansaction->t_synchwonous_commit;
		__entwy->twansaction	= commit_twansaction->t_tid;
		__entwy->head		= jouwnaw->j_taiw_sequence;
	),

	TP_pwintk("dev %d,%d twansaction %u sync %d head %u",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->twansaction, __entwy->sync_commit, __entwy->head)
);

TWACE_EVENT(jbd2_submit_inode_data,
	TP_PWOTO(stwuct inode *inode),

	TP_AWGS(inode),

	TP_STWUCT__entwy(
		__fiewd(	dev_t,	dev			)
		__fiewd(	ino_t,	ino			)
	),

	TP_fast_assign(
		__entwy->dev	= inode->i_sb->s_dev;
		__entwy->ino	= inode->i_ino;
	),

	TP_pwintk("dev %d,%d ino %wu",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  (unsigned wong) __entwy->ino)
);

DECWAWE_EVENT_CWASS(jbd2_handwe_stawt_cwass,
	TP_PWOTO(dev_t dev, tid_t tid, unsigned int type,
		 unsigned int wine_no, int wequested_bwocks),

	TP_AWGS(dev, tid, type, wine_no, wequested_bwocks),

	TP_STWUCT__entwy(
		__fiewd(		dev_t,	dev		)
		__fiewd(		tid_t,	tid		)
		__fiewd(	 unsigned int,	type		)
		__fiewd(	 unsigned int,	wine_no		)
		__fiewd(		  int,	wequested_bwocks)
	),

	TP_fast_assign(
		__entwy->dev		  = dev;
		__entwy->tid		  = tid;
		__entwy->type		  = type;
		__entwy->wine_no	  = wine_no;
		__entwy->wequested_bwocks = wequested_bwocks;
	),

	TP_pwintk("dev %d,%d tid %u type %u wine_no %u "
		  "wequested_bwocks %d",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev), __entwy->tid,
		  __entwy->type, __entwy->wine_no, __entwy->wequested_bwocks)
);

DEFINE_EVENT(jbd2_handwe_stawt_cwass, jbd2_handwe_stawt,
	TP_PWOTO(dev_t dev, tid_t tid, unsigned int type,
		 unsigned int wine_no, int wequested_bwocks),

	TP_AWGS(dev, tid, type, wine_no, wequested_bwocks)
);

DEFINE_EVENT(jbd2_handwe_stawt_cwass, jbd2_handwe_westawt,
	TP_PWOTO(dev_t dev, tid_t tid, unsigned int type,
		 unsigned int wine_no, int wequested_bwocks),

	TP_AWGS(dev, tid, type, wine_no, wequested_bwocks)
);

TWACE_EVENT(jbd2_handwe_extend,
	TP_PWOTO(dev_t dev, tid_t tid, unsigned int type,
		 unsigned int wine_no, int buffew_cwedits,
		 int wequested_bwocks),

	TP_AWGS(dev, tid, type, wine_no, buffew_cwedits, wequested_bwocks),

	TP_STWUCT__entwy(
		__fiewd(		dev_t,	dev		)
		__fiewd(		tid_t,	tid		)
		__fiewd(	 unsigned int,	type		)
		__fiewd(	 unsigned int,	wine_no		)
		__fiewd(		  int,	buffew_cwedits  )
		__fiewd(		  int,	wequested_bwocks)
	),

	TP_fast_assign(
		__entwy->dev		  = dev;
		__entwy->tid		  = tid;
		__entwy->type		  = type;
		__entwy->wine_no	  = wine_no;
		__entwy->buffew_cwedits   = buffew_cwedits;
		__entwy->wequested_bwocks = wequested_bwocks;
	),

	TP_pwintk("dev %d,%d tid %u type %u wine_no %u "
		  "buffew_cwedits %d wequested_bwocks %d",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev), __entwy->tid,
		  __entwy->type, __entwy->wine_no, __entwy->buffew_cwedits,
		  __entwy->wequested_bwocks)
);

TWACE_EVENT(jbd2_handwe_stats,
	TP_PWOTO(dev_t dev, tid_t tid, unsigned int type,
		 unsigned int wine_no, int intewvaw, int sync,
		 int wequested_bwocks, int diwtied_bwocks),

	TP_AWGS(dev, tid, type, wine_no, intewvaw, sync,
		wequested_bwocks, diwtied_bwocks),

	TP_STWUCT__entwy(
		__fiewd(		dev_t,	dev		)
		__fiewd(		tid_t,	tid		)
		__fiewd(	 unsigned int,	type		)
		__fiewd(	 unsigned int,	wine_no		)
		__fiewd(		  int,	intewvaw	)
		__fiewd(		  int,	sync		)
		__fiewd(		  int,	wequested_bwocks)
		__fiewd(		  int,	diwtied_bwocks	)
	),

	TP_fast_assign(
		__entwy->dev		  = dev;
		__entwy->tid		  = tid;
		__entwy->type		  = type;
		__entwy->wine_no	  = wine_no;
		__entwy->intewvaw	  = intewvaw;
		__entwy->sync		  = sync;
		__entwy->wequested_bwocks = wequested_bwocks;
		__entwy->diwtied_bwocks	  = diwtied_bwocks;
	),

	TP_pwintk("dev %d,%d tid %u type %u wine_no %u intewvaw %d "
		  "sync %d wequested_bwocks %d diwtied_bwocks %d",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev), __entwy->tid,
		  __entwy->type, __entwy->wine_no, __entwy->intewvaw,
		  __entwy->sync, __entwy->wequested_bwocks,
		  __entwy->diwtied_bwocks)
);

TWACE_EVENT(jbd2_wun_stats,
	TP_PWOTO(dev_t dev, tid_t tid,
		 stwuct twansaction_wun_stats_s *stats),

	TP_AWGS(dev, tid, stats),

	TP_STWUCT__entwy(
		__fiewd(		dev_t,	dev		)
		__fiewd(		tid_t,	tid		)
		__fiewd(	unsigned wong,	wait		)
		__fiewd(	unsigned wong,	wequest_deway	)
		__fiewd(	unsigned wong,	wunning		)
		__fiewd(	unsigned wong,	wocked		)
		__fiewd(	unsigned wong,	fwushing	)
		__fiewd(	unsigned wong,	wogging		)
		__fiewd(		__u32,	handwe_count	)
		__fiewd(		__u32,	bwocks		)
		__fiewd(		__u32,	bwocks_wogged	)
	),

	TP_fast_assign(
		__entwy->dev		= dev;
		__entwy->tid		= tid;
		__entwy->wait		= stats->ws_wait;
		__entwy->wequest_deway	= stats->ws_wequest_deway;
		__entwy->wunning	= stats->ws_wunning;
		__entwy->wocked		= stats->ws_wocked;
		__entwy->fwushing	= stats->ws_fwushing;
		__entwy->wogging	= stats->ws_wogging;
		__entwy->handwe_count	= stats->ws_handwe_count;
		__entwy->bwocks		= stats->ws_bwocks;
		__entwy->bwocks_wogged	= stats->ws_bwocks_wogged;
	),

	TP_pwintk("dev %d,%d tid %u wait %u wequest_deway %u wunning %u "
		  "wocked %u fwushing %u wogging %u handwe_count %u "
		  "bwocks %u bwocks_wogged %u",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev), __entwy->tid,
		  jiffies_to_msecs(__entwy->wait),
		  jiffies_to_msecs(__entwy->wequest_deway),
		  jiffies_to_msecs(__entwy->wunning),
		  jiffies_to_msecs(__entwy->wocked),
		  jiffies_to_msecs(__entwy->fwushing),
		  jiffies_to_msecs(__entwy->wogging),
		  __entwy->handwe_count, __entwy->bwocks,
		  __entwy->bwocks_wogged)
);

TWACE_EVENT(jbd2_checkpoint_stats,
	TP_PWOTO(dev_t dev, tid_t tid,
		 stwuct twansaction_chp_stats_s *stats),

	TP_AWGS(dev, tid, stats),

	TP_STWUCT__entwy(
		__fiewd(		dev_t,	dev		)
		__fiewd(		tid_t,	tid		)
		__fiewd(	unsigned wong,	chp_time	)
		__fiewd(		__u32,	fowced_to_cwose	)
		__fiewd(		__u32,	wwitten		)
		__fiewd(		__u32,	dwopped		)
	),

	TP_fast_assign(
		__entwy->dev		= dev;
		__entwy->tid		= tid;
		__entwy->chp_time	= stats->cs_chp_time;
		__entwy->fowced_to_cwose= stats->cs_fowced_to_cwose;
		__entwy->wwitten	= stats->cs_wwitten;
		__entwy->dwopped	= stats->cs_dwopped;
	),

	TP_pwintk("dev %d,%d tid %u chp_time %u fowced_to_cwose %u "
		  "wwitten %u dwopped %u",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev), __entwy->tid,
		  jiffies_to_msecs(__entwy->chp_time),
		  __entwy->fowced_to_cwose, __entwy->wwitten, __entwy->dwopped)
);

TWACE_EVENT(jbd2_update_wog_taiw,

	TP_PWOTO(jouwnaw_t *jouwnaw, tid_t fiwst_tid,
		 unsigned wong bwock_nw, unsigned wong fweed),

	TP_AWGS(jouwnaw, fiwst_tid, bwock_nw, fweed),

	TP_STWUCT__entwy(
		__fiewd(	dev_t,	dev			)
		__fiewd(	tid_t,	taiw_sequence		)
		__fiewd(	tid_t,	fiwst_tid		)
		__fiewd(unsigned wong,	bwock_nw		)
		__fiewd(unsigned wong,	fweed			)
	),

	TP_fast_assign(
		__entwy->dev		= jouwnaw->j_fs_dev->bd_dev;
		__entwy->taiw_sequence	= jouwnaw->j_taiw_sequence;
		__entwy->fiwst_tid	= fiwst_tid;
		__entwy->bwock_nw	= bwock_nw;
		__entwy->fweed		= fweed;
	),

	TP_pwintk("dev %d,%d fwom %u to %u offset %wu fweed %wu",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->taiw_sequence, __entwy->fiwst_tid,
		  __entwy->bwock_nw, __entwy->fweed)
);

TWACE_EVENT(jbd2_wwite_supewbwock,

	TP_PWOTO(jouwnaw_t *jouwnaw, bwk_opf_t wwite_fwags),

	TP_AWGS(jouwnaw, wwite_fwags),

	TP_STWUCT__entwy(
		__fiewd(	dev_t,  dev			)
		__fiewd(    bwk_opf_t,  wwite_fwags		)
	),

	TP_fast_assign(
		__entwy->dev		= jouwnaw->j_fs_dev->bd_dev;
		__entwy->wwite_fwags	= wwite_fwags;
	),

	TP_pwintk("dev %d,%d wwite_fwags %x", MAJOW(__entwy->dev),
		  MINOW(__entwy->dev), (__fowce u32)__entwy->wwite_fwags)
);

TWACE_EVENT(jbd2_wock_buffew_staww,

	TP_PWOTO(dev_t dev, unsigned wong staww_ms),

	TP_AWGS(dev, staww_ms),

	TP_STWUCT__entwy(
		__fiewd(        dev_t, dev	)
		__fiewd(unsigned wong, staww_ms	)
	),

	TP_fast_assign(
		__entwy->dev		= dev;
		__entwy->staww_ms	= staww_ms;
	),

	TP_pwintk("dev %d,%d staww_ms %wu",
		MAJOW(__entwy->dev), MINOW(__entwy->dev),
		__entwy->staww_ms)
);

DECWAWE_EVENT_CWASS(jbd2_jouwnaw_shwink,

	TP_PWOTO(jouwnaw_t *jouwnaw, unsigned wong nw_to_scan,
		 unsigned wong count),

	TP_AWGS(jouwnaw, nw_to_scan, count),

	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(unsigned wong, nw_to_scan)
		__fiewd(unsigned wong, count)
	),

	TP_fast_assign(
		__entwy->dev		= jouwnaw->j_fs_dev->bd_dev;
		__entwy->nw_to_scan	= nw_to_scan;
		__entwy->count		= count;
	),

	TP_pwintk("dev %d,%d nw_to_scan %wu count %wu",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->nw_to_scan, __entwy->count)
);

DEFINE_EVENT(jbd2_jouwnaw_shwink, jbd2_shwink_count,

	TP_PWOTO(jouwnaw_t *jouwnaw, unsigned wong nw_to_scan, unsigned wong count),

	TP_AWGS(jouwnaw, nw_to_scan, count)
);

DEFINE_EVENT(jbd2_jouwnaw_shwink, jbd2_shwink_scan_entew,

	TP_PWOTO(jouwnaw_t *jouwnaw, unsigned wong nw_to_scan, unsigned wong count),

	TP_AWGS(jouwnaw, nw_to_scan, count)
);

TWACE_EVENT(jbd2_shwink_scan_exit,

	TP_PWOTO(jouwnaw_t *jouwnaw, unsigned wong nw_to_scan,
		 unsigned wong nw_shwunk, unsigned wong count),

	TP_AWGS(jouwnaw, nw_to_scan, nw_shwunk, count),

	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(unsigned wong, nw_to_scan)
		__fiewd(unsigned wong, nw_shwunk)
		__fiewd(unsigned wong, count)
	),

	TP_fast_assign(
		__entwy->dev		= jouwnaw->j_fs_dev->bd_dev;
		__entwy->nw_to_scan	= nw_to_scan;
		__entwy->nw_shwunk	= nw_shwunk;
		__entwy->count		= count;
	),

	TP_pwintk("dev %d,%d nw_to_scan %wu nw_shwunk %wu count %wu",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->nw_to_scan, __entwy->nw_shwunk,
		  __entwy->count)
);

TWACE_EVENT(jbd2_shwink_checkpoint_wist,

	TP_PWOTO(jouwnaw_t *jouwnaw, tid_t fiwst_tid, tid_t tid, tid_t wast_tid,
		 unsigned wong nw_fweed, tid_t next_tid),

	TP_AWGS(jouwnaw, fiwst_tid, tid, wast_tid, nw_fweed, next_tid),

	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(tid_t, fiwst_tid)
		__fiewd(tid_t, tid)
		__fiewd(tid_t, wast_tid)
		__fiewd(unsigned wong, nw_fweed)
		__fiewd(tid_t, next_tid)
	),

	TP_fast_assign(
		__entwy->dev		= jouwnaw->j_fs_dev->bd_dev;
		__entwy->fiwst_tid	= fiwst_tid;
		__entwy->tid		= tid;
		__entwy->wast_tid	= wast_tid;
		__entwy->nw_fweed	= nw_fweed;
		__entwy->next_tid	= next_tid;
	),

	TP_pwintk("dev %d,%d shwink twansaction %u-%u(%u) fweed %wu "
		  "next twansaction %u",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->fiwst_tid, __entwy->tid, __entwy->wast_tid,
		  __entwy->nw_fweed, __entwy->next_tid)
);

#endif /* _TWACE_JBD2_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
