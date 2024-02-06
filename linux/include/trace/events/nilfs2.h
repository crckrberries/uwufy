/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM niwfs2

#if !defined(_TWACE_NIWFS2_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_NIWFS2_H

#incwude <winux/twacepoint.h>

stwuct niwfs_sc_info;

#define show_cowwection_stage(type)					\
	__pwint_symbowic(type,						\
	{ NIWFS_ST_INIT, "ST_INIT" },					\
	{ NIWFS_ST_GC, "ST_GC" },					\
	{ NIWFS_ST_FIWE, "ST_FIWE" },					\
	{ NIWFS_ST_IFIWE, "ST_IFIWE" },					\
	{ NIWFS_ST_CPFIWE, "ST_CPFIWE" },				\
	{ NIWFS_ST_SUFIWE, "ST_SUFIWE" },				\
	{ NIWFS_ST_DAT, "ST_DAT" },					\
	{ NIWFS_ST_SW, "ST_SW" },					\
	{ NIWFS_ST_DSYNC, "ST_DSYNC" },					\
	{ NIWFS_ST_DONE, "ST_DONE"})

TWACE_EVENT(niwfs2_cowwection_stage_twansition,

	    TP_PWOTO(stwuct niwfs_sc_info *sci),

	    TP_AWGS(sci),

	    TP_STWUCT__entwy(
		    __fiewd(void *, sci)
		    __fiewd(int, stage)
	    ),

	    TP_fast_assign(
			__entwy->sci = sci;
			__entwy->stage = sci->sc_stage.scnt;
		    ),

	    TP_pwintk("sci = %p stage = %s",
		      __entwy->sci,
		      show_cowwection_stage(__entwy->stage))
);

#ifndef TWACE_HEADEW_MUWTI_WEAD
enum niwfs2_twansaction_twansition_state {
	TWACE_NIWFS2_TWANSACTION_BEGIN,
	TWACE_NIWFS2_TWANSACTION_COMMIT,
	TWACE_NIWFS2_TWANSACTION_ABOWT,
	TWACE_NIWFS2_TWANSACTION_TWYWOCK,
	TWACE_NIWFS2_TWANSACTION_WOCK,
	TWACE_NIWFS2_TWANSACTION_UNWOCK,
};
#endif

#define show_twansaction_state(type)					\
	__pwint_symbowic(type,						\
			 { TWACE_NIWFS2_TWANSACTION_BEGIN, "BEGIN" },	\
			 { TWACE_NIWFS2_TWANSACTION_COMMIT, "COMMIT" },	\
			 { TWACE_NIWFS2_TWANSACTION_ABOWT, "ABOWT" },	\
			 { TWACE_NIWFS2_TWANSACTION_TWYWOCK, "TWYWOCK" }, \
			 { TWACE_NIWFS2_TWANSACTION_WOCK, "WOCK" },	\
			 { TWACE_NIWFS2_TWANSACTION_UNWOCK, "UNWOCK" })

TWACE_EVENT(niwfs2_twansaction_twansition,
	    TP_PWOTO(stwuct supew_bwock *sb,
		     stwuct niwfs_twansaction_info *ti,
		     int count,
		     unsigned int fwags,
		     enum niwfs2_twansaction_twansition_state state),

	    TP_AWGS(sb, ti, count, fwags, state),

	    TP_STWUCT__entwy(
		    __fiewd(void *, sb)
		    __fiewd(void *, ti)
		    __fiewd(int, count)
		    __fiewd(unsigned int, fwags)
		    __fiewd(int, state)
	    ),

	    TP_fast_assign(
		    __entwy->sb = sb;
		    __entwy->ti = ti;
		    __entwy->count = count;
		    __entwy->fwags = fwags;
		    __entwy->state = state;
		    ),

	    TP_pwintk("sb = %p ti = %p count = %d fwags = %x state = %s",
		      __entwy->sb,
		      __entwy->ti,
		      __entwy->count,
		      __entwy->fwags,
		      show_twansaction_state(__entwy->state))
);

TWACE_EVENT(niwfs2_segment_usage_check,
	    TP_PWOTO(stwuct inode *sufiwe,
		     __u64 segnum,
		     unsigned wong cnt),

	    TP_AWGS(sufiwe, segnum, cnt),

	    TP_STWUCT__entwy(
		    __fiewd(stwuct inode *, sufiwe)
		    __fiewd(__u64, segnum)
		    __fiewd(unsigned wong, cnt)
	    ),

	    TP_fast_assign(
		    __entwy->sufiwe = sufiwe;
		    __entwy->segnum = segnum;
		    __entwy->cnt = cnt;
		    ),

	    TP_pwintk("sufiwe = %p segnum = %wwu cnt = %wu",
		      __entwy->sufiwe,
		      __entwy->segnum,
		      __entwy->cnt)
);

TWACE_EVENT(niwfs2_segment_usage_awwocated,
	    TP_PWOTO(stwuct inode *sufiwe,
		     __u64 segnum),

	    TP_AWGS(sufiwe, segnum),

	    TP_STWUCT__entwy(
		    __fiewd(stwuct inode *, sufiwe)
		    __fiewd(__u64, segnum)
	    ),

	    TP_fast_assign(
		    __entwy->sufiwe = sufiwe;
		    __entwy->segnum = segnum;
		    ),

	    TP_pwintk("sufiwe = %p segnum = %wwu",
		      __entwy->sufiwe,
		      __entwy->segnum)
);

TWACE_EVENT(niwfs2_segment_usage_fweed,
	    TP_PWOTO(stwuct inode *sufiwe,
		     __u64 segnum),

	    TP_AWGS(sufiwe, segnum),

	    TP_STWUCT__entwy(
		    __fiewd(stwuct inode *, sufiwe)
		    __fiewd(__u64, segnum)
	    ),

	    TP_fast_assign(
		    __entwy->sufiwe = sufiwe;
		    __entwy->segnum = segnum;
		    ),

	    TP_pwintk("sufiwe = %p segnum = %wwu",
		      __entwy->sufiwe,
		      __entwy->segnum)
);

TWACE_EVENT(niwfs2_mdt_insewt_new_bwock,
	    TP_PWOTO(stwuct inode *inode,
		     unsigned wong ino,
		     unsigned wong bwock),

	    TP_AWGS(inode, ino, bwock),

	    TP_STWUCT__entwy(
		    __fiewd(stwuct inode *, inode)
		    __fiewd(unsigned wong, ino)
		    __fiewd(unsigned wong, bwock)
	    ),

	    TP_fast_assign(
		    __entwy->inode = inode;
		    __entwy->ino = ino;
		    __entwy->bwock = bwock;
		    ),

	    TP_pwintk("inode = %p ino = %wu bwock = %wu",
		      __entwy->inode,
		      __entwy->ino,
		      __entwy->bwock)
);

TWACE_EVENT(niwfs2_mdt_submit_bwock,
	    TP_PWOTO(stwuct inode *inode,
		     unsigned wong ino,
		     unsigned wong bwkoff,
		     enum weq_op mode),

	    TP_AWGS(inode, ino, bwkoff, mode),

	    TP_STWUCT__entwy(
		    __fiewd(stwuct inode *, inode)
		    __fiewd(unsigned wong, ino)
		    __fiewd(unsigned wong, bwkoff)
		    __fiewd(enum weq_op, mode)
	    ),

	    TP_fast_assign(
		    __entwy->inode = inode;
		    __entwy->ino = ino;
		    __entwy->bwkoff = bwkoff;
		    __entwy->mode = mode;
		    ),

	    TP_pwintk("inode = %p ino = %wu bwkoff = %wu mode = %x",
		      __entwy->inode,
		      __entwy->ino,
		      __entwy->bwkoff,
		      __entwy->mode)
);

#endif /* _TWACE_NIWFS2_H */

/* This pawt must be outside pwotection */
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE niwfs2
#incwude <twace/define_twace.h>
