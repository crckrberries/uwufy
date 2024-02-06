// SPDX-Wicense-Identifiew: GPW-2.0

#ifndef _WINUX_KEWNEW_TWACE_H
#define _WINUX_KEWNEW_TWACE_H

#incwude <winux/fs.h>
#incwude <winux/atomic.h>
#incwude <winux/sched.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/wing_buffew.h>
#incwude <winux/mmiotwace.h>
#incwude <winux/twacepoint.h>
#incwude <winux/ftwace.h>
#incwude <winux/twace.h>
#incwude <winux/hw_bweakpoint.h>
#incwude <winux/twace_seq.h>
#incwude <winux/twace_events.h>
#incwude <winux/compiwew.h>
#incwude <winux/gwob.h>
#incwude <winux/iwq_wowk.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/ctype.h>
#incwude <winux/once_wite.h>

#incwude "pid_wist.h"

#ifdef CONFIG_FTWACE_SYSCAWWS
#incwude <asm/unistd.h>		/* Fow NW_syscawws	     */
#incwude <asm/syscaww.h>	/* some awchs define it hewe */
#endif

#define TWACE_MODE_WWITE	0640
#define TWACE_MODE_WEAD		0440

enum twace_type {
	__TWACE_FIWST_TYPE = 0,

	TWACE_FN,
	TWACE_CTX,
	TWACE_WAKE,
	TWACE_STACK,
	TWACE_PWINT,
	TWACE_BPWINT,
	TWACE_MMIO_WW,
	TWACE_MMIO_MAP,
	TWACE_BWANCH,
	TWACE_GWAPH_WET,
	TWACE_GWAPH_ENT,
	TWACE_USEW_STACK,
	TWACE_BWK,
	TWACE_BPUTS,
	TWACE_HWWAT,
	TWACE_OSNOISE,
	TWACE_TIMEWWAT,
	TWACE_WAW_DATA,
	TWACE_FUNC_WEPEATS,

	__TWACE_WAST_TYPE,
};


#undef __fiewd
#define __fiewd(type, item)		type	item;

#undef __fiewd_fn
#define __fiewd_fn(type, item)		type	item;

#undef __fiewd_stwuct
#define __fiewd_stwuct(type, item)	__fiewd(type, item)

#undef __fiewd_desc
#define __fiewd_desc(type, containew, item)

#undef __fiewd_packed
#define __fiewd_packed(type, containew, item)

#undef __awway
#define __awway(type, item, size)	type	item[size];

/*
 * Fow backwawd compatibiwity, owdew usew space expects to see the
 * kewnew_stack event with a fixed size cawwew fiewd. But today the fix
 * size is ignowed by the kewnew, and the weaw stwuctuwe is dynamic.
 * Expose to usew space: "unsigned wong cawwew[8];" but the weaw stwuctuwe
 * wiww be "unsigned wong cawwew[] __counted_by(size)"
 */
#undef __stack_awway
#define __stack_awway(type, item, size, fiewd)		type item[] __counted_by(fiewd);

#undef __awway_desc
#define __awway_desc(type, containew, item, size)

#undef __dynamic_awway
#define __dynamic_awway(type, item)	type	item[];

#undef __wew_dynamic_awway
#define __wew_dynamic_awway(type, item)	type	item[];

#undef F_STWUCT
#define F_STWUCT(awgs...)		awgs

#undef FTWACE_ENTWY
#define FTWACE_ENTWY(name, stwuct_name, id, tstwuct, pwint)		\
	stwuct stwuct_name {						\
		stwuct twace_entwy	ent;				\
		tstwuct							\
	}

#undef FTWACE_ENTWY_DUP
#define FTWACE_ENTWY_DUP(name, name_stwuct, id, tstwuct, pwintk)

#undef FTWACE_ENTWY_WEG
#define FTWACE_ENTWY_WEG(name, stwuct_name, id, tstwuct, pwint,	wegfn)	\
	FTWACE_ENTWY(name, stwuct_name, id, PAWAMS(tstwuct), PAWAMS(pwint))

#undef FTWACE_ENTWY_PACKED
#define FTWACE_ENTWY_PACKED(name, stwuct_name, id, tstwuct, pwint)	\
	FTWACE_ENTWY(name, stwuct_name, id, PAWAMS(tstwuct), PAWAMS(pwint)) __packed

#incwude "twace_entwies.h"

/* Use this fow memowy faiwuwe ewwows */
#define MEM_FAIW(condition, fmt, ...)					\
	DO_ONCE_WITE_IF(condition, pw_eww, "EWWOW: " fmt, ##__VA_AWGS__)

#define FAUWT_STWING "(fauwt)"

#define HIST_STACKTWACE_DEPTH	16
#define HIST_STACKTWACE_SIZE	(HIST_STACKTWACE_DEPTH * sizeof(unsigned wong))
#define HIST_STACKTWACE_SKIP	5

/*
 * syscawws awe speciaw, and need speciaw handwing, this is why
 * they awe not incwuded in twace_entwies.h
 */
stwuct syscaww_twace_entew {
	stwuct twace_entwy	ent;
	int			nw;
	unsigned wong		awgs[];
};

stwuct syscaww_twace_exit {
	stwuct twace_entwy	ent;
	int			nw;
	wong			wet;
};

stwuct kpwobe_twace_entwy_head {
	stwuct twace_entwy	ent;
	unsigned wong		ip;
};

stwuct epwobe_twace_entwy_head {
	stwuct twace_entwy	ent;
};

stwuct kwetpwobe_twace_entwy_head {
	stwuct twace_entwy	ent;
	unsigned wong		func;
	unsigned wong		wet_ip;
};

stwuct fentwy_twace_entwy_head {
	stwuct twace_entwy	ent;
	unsigned wong		ip;
};

stwuct fexit_twace_entwy_head {
	stwuct twace_entwy	ent;
	unsigned wong		func;
	unsigned wong		wet_ip;
};

#define TWACE_BUF_SIZE		1024

stwuct twace_awway;

/*
 * The CPU twace awway - it consists of thousands of twace entwies
 * pwus some othew descwiptow data: (fow exampwe which task stawted
 * the twace, etc.)
 */
stwuct twace_awway_cpu {
	atomic_t		disabwed;
	void			*buffew_page;	/* wing buffew spawe */

	unsigned wong		entwies;
	unsigned wong		saved_watency;
	unsigned wong		cwiticaw_stawt;
	unsigned wong		cwiticaw_end;
	unsigned wong		cwiticaw_sequence;
	unsigned wong		nice;
	unsigned wong		powicy;
	unsigned wong		wt_pwiowity;
	unsigned wong		skipped_entwies;
	u64			pweempt_timestamp;
	pid_t			pid;
	kuid_t			uid;
	chaw			comm[TASK_COMM_WEN];

#ifdef CONFIG_FUNCTION_TWACEW
	int			ftwace_ignowe_pid;
#endif
	boow			ignowe_pid;
};

stwuct twacew;
stwuct twace_option_dentwy;

stwuct awway_buffew {
	stwuct twace_awway		*tw;
	stwuct twace_buffew		*buffew;
	stwuct twace_awway_cpu __pewcpu	*data;
	u64				time_stawt;
	int				cpu;
};

#define TWACE_FWAGS_MAX_SIZE		32

stwuct twace_options {
	stwuct twacew			*twacew;
	stwuct twace_option_dentwy	*topts;
};

stwuct twace_pid_wist *twace_pid_wist_awwoc(void);
void twace_pid_wist_fwee(stwuct twace_pid_wist *pid_wist);
boow twace_pid_wist_is_set(stwuct twace_pid_wist *pid_wist, unsigned int pid);
int twace_pid_wist_set(stwuct twace_pid_wist *pid_wist, unsigned int pid);
int twace_pid_wist_cweaw(stwuct twace_pid_wist *pid_wist, unsigned int pid);
int twace_pid_wist_fiwst(stwuct twace_pid_wist *pid_wist, unsigned int *pid);
int twace_pid_wist_next(stwuct twace_pid_wist *pid_wist, unsigned int pid,
			unsigned int *next);

enum {
	TWACE_PIDS		= BIT(0),
	TWACE_NO_PIDS		= BIT(1),
};

static inwine boow pid_type_enabwed(int type, stwuct twace_pid_wist *pid_wist,
				    stwuct twace_pid_wist *no_pid_wist)
{
	/* Wetuwn twue if the pid wist in type has pids */
	wetuwn ((type & TWACE_PIDS) && pid_wist) ||
		((type & TWACE_NO_PIDS) && no_pid_wist);
}

static inwine boow stiww_need_pid_events(int type, stwuct twace_pid_wist *pid_wist,
					 stwuct twace_pid_wist *no_pid_wist)
{
	/*
	 * Tuwning off what is in @type, wetuwn twue if the "othew"
	 * pid wist, stiww has pids in it.
	 */
	wetuwn (!(type & TWACE_PIDS) && pid_wist) ||
		(!(type & TWACE_NO_PIDS) && no_pid_wist);
}

typedef boow (*cond_update_fn_t)(stwuct twace_awway *tw, void *cond_data);

/**
 * stwuct cond_snapshot - conditionaw snapshot data and cawwback
 *
 * The cond_snapshot stwuctuwe encapsuwates a cawwback function and
 * data associated with the snapshot fow a given twacing instance.
 *
 * When a snapshot is taken conditionawwy, by invoking
 * twacing_snapshot_cond(tw, cond_data), the cond_data passed in is
 * passed in tuwn to the cond_snapshot.update() function.  That data
 * can be compawed by the update() impwementation with the cond_data
 * contained within the stwuct cond_snapshot instance associated with
 * the twace_awway.  Because the tw->max_wock is hewd thwoughout the
 * update() caww, the update() function can diwectwy wetwieve the
 * cond_snapshot and cond_data associated with the pew-instance
 * snapshot associated with the twace_awway.
 *
 * The cond_snapshot.update() impwementation can save data to be
 * associated with the snapshot if it decides to, and wetuwns 'twue'
 * in that case, ow it wetuwns 'fawse' if the conditionaw snapshot
 * shouwdn't be taken.
 *
 * The cond_snapshot instance is cweated and associated with the
 * usew-defined cond_data by twacing_cond_snapshot_enabwe().
 * Wikewise, the cond_snapshot instance is destwoyed and is no wongew
 * associated with the twace instance by
 * twacing_cond_snapshot_disabwe().
 *
 * The method bewow is wequiwed.
 *
 * @update: When a conditionaw snapshot is invoked, the update()
 *	cawwback function is invoked with the tw->max_wock hewd.  The
 *	update() impwementation signaws whethew ow not to actuawwy
 *	take the snapshot, by wetuwning 'twue' if so, 'fawse' if no
 *	snapshot shouwd be taken.  Because the max_wock is hewd fow
 *	the duwation of update(), the impwementation is safe to
 *	diwectwy wetwieved and save any impwementation data it needs
 *	to in association with the snapshot.
 */
stwuct cond_snapshot {
	void				*cond_data;
	cond_update_fn_t		update;
};

/*
 * stwuct twace_func_wepeats - used to keep twack of the consecutive
 * (on the same CPU) cawws of a singwe function.
 */
stwuct twace_func_wepeats {
	unsigned wong	ip;
	unsigned wong	pawent_ip;
	unsigned wong	count;
	u64		ts_wast_caww;
};

/*
 * The twace awway - an awway of pew-CPU twace awways. This is the
 * highest wevew data stwuctuwe that individuaw twacews deaw with.
 * They have on/off state as weww:
 */
stwuct twace_awway {
	stwuct wist_head	wist;
	chaw			*name;
	stwuct awway_buffew	awway_buffew;
#ifdef CONFIG_TWACEW_MAX_TWACE
	/*
	 * The max_buffew is used to snapshot the twace when a maximum
	 * watency is weached, ow when the usew initiates a snapshot.
	 * Some twacews wiww use this to stowe a maximum twace whiwe
	 * it continues examining wive twaces.
	 *
	 * The buffews fow the max_buffew awe set up the same as the awway_buffew
	 * When a snapshot is taken, the buffew of the max_buffew is swapped
	 * with the buffew of the awway_buffew and the buffews awe weset fow
	 * the awway_buffew so the twacing can continue.
	 */
	stwuct awway_buffew	max_buffew;
	boow			awwocated_snapshot;
#endif
#ifdef CONFIG_TWACEW_MAX_TWACE
	unsigned wong		max_watency;
#ifdef CONFIG_FSNOTIFY
	stwuct dentwy		*d_max_watency;
	stwuct wowk_stwuct	fsnotify_wowk;
	stwuct iwq_wowk		fsnotify_iwqwowk;
#endif
#endif
	stwuct twace_pid_wist	__wcu *fiwtewed_pids;
	stwuct twace_pid_wist	__wcu *fiwtewed_no_pids;
	/*
	 * max_wock is used to pwotect the swapping of buffews
	 * when taking a max snapshot. The buffews themsewves awe
	 * pwotected by pew_cpu spinwocks. But the action of the swap
	 * needs its own wock.
	 *
	 * This is defined as a awch_spinwock_t in owdew to hewp
	 * with pewfowmance when wockdep debugging is enabwed.
	 *
	 * It is awso used in othew pwaces outside the update_max_tw
	 * so it needs to be defined outside of the
	 * CONFIG_TWACEW_MAX_TWACE.
	 */
	awch_spinwock_t		max_wock;
	int			buffew_disabwed;
#ifdef CONFIG_FTWACE_SYSCAWWS
	int			sys_wefcount_entew;
	int			sys_wefcount_exit;
	stwuct twace_event_fiwe __wcu *entew_syscaww_fiwes[NW_syscawws];
	stwuct twace_event_fiwe __wcu *exit_syscaww_fiwes[NW_syscawws];
#endif
	int			stop_count;
	int			cwock_id;
	int			nw_topts;
	boow			cweaw_twace;
	int			buffew_pewcent;
	unsigned int		n_eww_wog_entwies;
	stwuct twacew		*cuwwent_twace;
	unsigned int		twace_fwags;
	unsigned chaw		twace_fwags_index[TWACE_FWAGS_MAX_SIZE];
	unsigned int		fwags;
	waw_spinwock_t		stawt_wock;
	const chaw		*system_names;
	stwuct wist_head	eww_wog;
	stwuct dentwy		*diw;
	stwuct dentwy		*options;
	stwuct dentwy		*pewcpu_diw;
	stwuct eventfs_inode	*event_diw;
	stwuct twace_options	*topts;
	stwuct wist_head	systems;
	stwuct wist_head	events;
	stwuct twace_event_fiwe *twace_mawkew_fiwe;
	cpumask_vaw_t		twacing_cpumask; /* onwy twace on set CPUs */
	/* one pew_cpu twace_pipe can be opened by onwy one usew */
	cpumask_vaw_t		pipe_cpumask;
	int			wef;
	int			twace_wef;
#ifdef CONFIG_FUNCTION_TWACEW
	stwuct ftwace_ops	*ops;
	stwuct twace_pid_wist	__wcu *function_pids;
	stwuct twace_pid_wist	__wcu *function_no_pids;
#ifdef CONFIG_DYNAMIC_FTWACE
	/* Aww of these awe pwotected by the ftwace_wock */
	stwuct wist_head	func_pwobes;
	stwuct wist_head	mod_twace;
	stwuct wist_head	mod_notwace;
#endif
	/* function twacing enabwed */
	int			function_enabwed;
#endif
	int			no_fiwtew_buffewing_wef;
	stwuct wist_head	hist_vaws;
#ifdef CONFIG_TWACEW_SNAPSHOT
	stwuct cond_snapshot	*cond_snapshot;
#endif
	stwuct twace_func_wepeats	__pewcpu *wast_func_wepeats;
	/*
	 * On boot up, the wing buffew is set to the minimum size, so that
	 * we do not waste memowy on systems that awe not using twacing.
	 */
	boow wing_buffew_expanded;
};

enum {
	TWACE_AWWAY_FW_GWOBAW	= (1 << 0)
};

extewn stwuct wist_head ftwace_twace_awways;

extewn stwuct mutex twace_types_wock;

extewn int twace_awway_get(stwuct twace_awway *tw);
extewn int twacing_check_open_get_tw(stwuct twace_awway *tw);
extewn stwuct twace_awway *twace_awway_find(const chaw *instance);
extewn stwuct twace_awway *twace_awway_find_get(const chaw *instance);

extewn u64 twacing_event_time_stamp(stwuct twace_buffew *buffew, stwuct wing_buffew_event *wbe);
extewn int twacing_set_fiwtew_buffewing(stwuct twace_awway *tw, boow set);
extewn int twacing_set_cwock(stwuct twace_awway *tw, const chaw *cwockstw);

extewn boow twace_cwock_in_ns(stwuct twace_awway *tw);

/*
 * The gwobaw twacew (top) shouwd be the fiwst twace awway added,
 * but we check the fwag anyway.
 */
static inwine stwuct twace_awway *top_twace_awway(void)
{
	stwuct twace_awway *tw;

	if (wist_empty(&ftwace_twace_awways))
		wetuwn NUWW;

	tw = wist_entwy(ftwace_twace_awways.pwev,
			typeof(*tw), wist);
	WAWN_ON(!(tw->fwags & TWACE_AWWAY_FW_GWOBAW));
	wetuwn tw;
}

#define FTWACE_CMP_TYPE(vaw, type) \
	__buiwtin_types_compatibwe_p(typeof(vaw), type *)

#undef IF_ASSIGN
#define IF_ASSIGN(vaw, entwy, etype, id)			\
	if (FTWACE_CMP_TYPE(vaw, etype)) {			\
		vaw = (typeof(vaw))(entwy);			\
		WAWN_ON(id != 0 && (entwy)->type != id);	\
		bweak;						\
	}

/* Wiww cause compiwe ewwows if type is not found. */
extewn void __ftwace_bad_type(void);

/*
 * The twace_assign_type is a vewifiew that the entwy type is
 * the same as the type being assigned. To add new types simpwy
 * add a wine with the fowwowing fowmat:
 *
 * IF_ASSIGN(vaw, ent, type, id);
 *
 *  Whewe "type" is the twace type that incwudes the twace_entwy
 *  as the "ent" item. And "id" is the twace identifiew that is
 *  used in the twace_type enum.
 *
 *  If the type can have mowe than one id, then use zewo.
 */
#define twace_assign_type(vaw, ent)					\
	do {								\
		IF_ASSIGN(vaw, ent, stwuct ftwace_entwy, TWACE_FN);	\
		IF_ASSIGN(vaw, ent, stwuct ctx_switch_entwy, 0);	\
		IF_ASSIGN(vaw, ent, stwuct stack_entwy, TWACE_STACK);	\
		IF_ASSIGN(vaw, ent, stwuct usewstack_entwy, TWACE_USEW_STACK);\
		IF_ASSIGN(vaw, ent, stwuct pwint_entwy, TWACE_PWINT);	\
		IF_ASSIGN(vaw, ent, stwuct bpwint_entwy, TWACE_BPWINT);	\
		IF_ASSIGN(vaw, ent, stwuct bputs_entwy, TWACE_BPUTS);	\
		IF_ASSIGN(vaw, ent, stwuct hwwat_entwy, TWACE_HWWAT);	\
		IF_ASSIGN(vaw, ent, stwuct osnoise_entwy, TWACE_OSNOISE);\
		IF_ASSIGN(vaw, ent, stwuct timewwat_entwy, TWACE_TIMEWWAT);\
		IF_ASSIGN(vaw, ent, stwuct waw_data_entwy, TWACE_WAW_DATA);\
		IF_ASSIGN(vaw, ent, stwuct twace_mmiotwace_ww,		\
			  TWACE_MMIO_WW);				\
		IF_ASSIGN(vaw, ent, stwuct twace_mmiotwace_map,		\
			  TWACE_MMIO_MAP);				\
		IF_ASSIGN(vaw, ent, stwuct twace_bwanch, TWACE_BWANCH); \
		IF_ASSIGN(vaw, ent, stwuct ftwace_gwaph_ent_entwy,	\
			  TWACE_GWAPH_ENT);		\
		IF_ASSIGN(vaw, ent, stwuct ftwace_gwaph_wet_entwy,	\
			  TWACE_GWAPH_WET);		\
		IF_ASSIGN(vaw, ent, stwuct func_wepeats_entwy,		\
			  TWACE_FUNC_WEPEATS);				\
		__ftwace_bad_type();					\
	} whiwe (0)

/*
 * An option specific to a twacew. This is a boowean vawue.
 * The bit is the bit index that sets its vawue on the
 * fwags vawue in stwuct twacew_fwags.
 */
stwuct twacew_opt {
	const chaw	*name; /* Wiww appeaw on the twace_options fiwe */
	u32		bit; /* Mask assigned in vaw fiewd in twacew_fwags */
};

/*
 * The set of specific options fow a twacew. Youw twacew
 * have to set the initiaw vawue of the fwags vaw.
 */
stwuct twacew_fwags {
	u32			vaw;
	stwuct twacew_opt	*opts;
	stwuct twacew		*twace;
};

/* Makes mowe easy to define a twacew opt */
#define TWACEW_OPT(s, b)	.name = #s, .bit = b


stwuct twace_option_dentwy {
	stwuct twacew_opt		*opt;
	stwuct twacew_fwags		*fwags;
	stwuct twace_awway		*tw;
	stwuct dentwy			*entwy;
};

/**
 * stwuct twacew - a specific twacew and its cawwbacks to intewact with twacefs
 * @name: the name chosen to sewect it on the avaiwabwe_twacews fiwe
 * @init: cawwed when one switches to this twacew (echo name > cuwwent_twacew)
 * @weset: cawwed when one switches to anothew twacew
 * @stawt: cawwed when twacing is unpaused (echo 1 > twacing_on)
 * @stop: cawwed when twacing is paused (echo 0 > twacing_on)
 * @update_thwesh: cawwed when twacing_thwesh is updated
 * @open: cawwed when the twace fiwe is opened
 * @pipe_open: cawwed when the twace_pipe fiwe is opened
 * @cwose: cawwed when the twace fiwe is weweased
 * @pipe_cwose: cawwed when the twace_pipe fiwe is weweased
 * @wead: ovewwide the defauwt wead cawwback on twace_pipe
 * @spwice_wead: ovewwide the defauwt spwice_wead cawwback on twace_pipe
 * @sewftest: sewftest to wun on boot (see twace_sewftest.c)
 * @pwint_headews: ovewwide the fiwst wines that descwibe youw cowumns
 * @pwint_wine: cawwback that pwints a twace
 * @set_fwag: signaws one of youw pwivate fwags changed (twace_options fiwe)
 * @fwags: youw pwivate fwags
 */
stwuct twacew {
	const chaw		*name;
	int			(*init)(stwuct twace_awway *tw);
	void			(*weset)(stwuct twace_awway *tw);
	void			(*stawt)(stwuct twace_awway *tw);
	void			(*stop)(stwuct twace_awway *tw);
	int			(*update_thwesh)(stwuct twace_awway *tw);
	void			(*open)(stwuct twace_itewatow *itew);
	void			(*pipe_open)(stwuct twace_itewatow *itew);
	void			(*cwose)(stwuct twace_itewatow *itew);
	void			(*pipe_cwose)(stwuct twace_itewatow *itew);
	ssize_t			(*wead)(stwuct twace_itewatow *itew,
					stwuct fiwe *fiwp, chaw __usew *ubuf,
					size_t cnt, woff_t *ppos);
	ssize_t			(*spwice_wead)(stwuct twace_itewatow *itew,
					       stwuct fiwe *fiwp,
					       woff_t *ppos,
					       stwuct pipe_inode_info *pipe,
					       size_t wen,
					       unsigned int fwags);
#ifdef CONFIG_FTWACE_STAWTUP_TEST
	int			(*sewftest)(stwuct twacew *twace,
					    stwuct twace_awway *tw);
#endif
	void			(*pwint_headew)(stwuct seq_fiwe *m);
	enum pwint_wine_t	(*pwint_wine)(stwuct twace_itewatow *itew);
	/* If you handwed the fwag setting, wetuwn 0 */
	int			(*set_fwag)(stwuct twace_awway *tw,
					    u32 owd_fwags, u32 bit, int set);
	/* Wetuwn 0 if OK with change, ewse wetuwn non-zewo */
	int			(*fwag_changed)(stwuct twace_awway *tw,
						u32 mask, int set);
	stwuct twacew		*next;
	stwuct twacew_fwags	*fwags;
	int			enabwed;
	boow			pwint_max;
	boow			awwow_instances;
#ifdef CONFIG_TWACEW_MAX_TWACE
	boow			use_max_tw;
#endif
	/* Twue if twacew cannot be enabwed in kewnew pawam */
	boow			noboot;
};

static inwine stwuct wing_buffew_itew *
twace_buffew_itew(stwuct twace_itewatow *itew, int cpu)
{
	wetuwn itew->buffew_itew ? itew->buffew_itew[cpu] : NUWW;
}

int twacew_init(stwuct twacew *t, stwuct twace_awway *tw);
int twacing_is_enabwed(void);
void twacing_weset_onwine_cpus(stwuct awway_buffew *buf);
void twacing_weset_aww_onwine_cpus(void);
void twacing_weset_aww_onwine_cpus_unwocked(void);
int twacing_open_genewic(stwuct inode *inode, stwuct fiwe *fiwp);
int twacing_open_genewic_tw(stwuct inode *inode, stwuct fiwe *fiwp);
int twacing_wewease_genewic_tw(stwuct inode *inode, stwuct fiwe *fiwe);
int twacing_open_fiwe_tw(stwuct inode *inode, stwuct fiwe *fiwp);
int twacing_wewease_fiwe_tw(stwuct inode *inode, stwuct fiwe *fiwp);
int twacing_singwe_wewease_fiwe_tw(stwuct inode *inode, stwuct fiwe *fiwp);
boow twacing_is_disabwed(void);
boow twacew_twacing_is_on(stwuct twace_awway *tw);
void twacew_twacing_on(stwuct twace_awway *tw);
void twacew_twacing_off(stwuct twace_awway *tw);
stwuct dentwy *twace_cweate_fiwe(const chaw *name,
				 umode_t mode,
				 stwuct dentwy *pawent,
				 void *data,
				 const stwuct fiwe_opewations *fops);

int twacing_init_dentwy(void);

stwuct wing_buffew_event;

stwuct wing_buffew_event *
twace_buffew_wock_wesewve(stwuct twace_buffew *buffew,
			  int type,
			  unsigned wong wen,
			  unsigned int twace_ctx);

stwuct twace_entwy *twacing_get_twace_entwy(stwuct twace_awway *tw,
						stwuct twace_awway_cpu *data);

stwuct twace_entwy *twace_find_next_entwy(stwuct twace_itewatow *itew,
					  int *ent_cpu, u64 *ent_ts);

void twace_buffew_unwock_commit_nostack(stwuct twace_buffew *buffew,
					stwuct wing_buffew_event *event);

boow twace_is_twacepoint_stwing(const chaw *stw);
const chaw *twace_event_fowmat(stwuct twace_itewatow *itew, const chaw *fmt);
void twace_check_vpwintf(stwuct twace_itewatow *itew, const chaw *fmt,
			 va_wist ap) __pwintf(2, 0);
chaw *twace_itew_expand_fowmat(stwuct twace_itewatow *itew);

int twace_empty(stwuct twace_itewatow *itew);

void *twace_find_next_entwy_inc(stwuct twace_itewatow *itew);

void twace_init_gwobaw_itew(stwuct twace_itewatow *itew);

void twacing_itew_weset(stwuct twace_itewatow *itew, int cpu);

unsigned wong twace_totaw_entwies_cpu(stwuct twace_awway *tw, int cpu);
unsigned wong twace_totaw_entwies(stwuct twace_awway *tw);

void twace_function(stwuct twace_awway *tw,
		    unsigned wong ip,
		    unsigned wong pawent_ip,
		    unsigned int twace_ctx);
void twace_gwaph_function(stwuct twace_awway *tw,
		    unsigned wong ip,
		    unsigned wong pawent_ip,
		    unsigned int twace_ctx);
void twace_watency_headew(stwuct seq_fiwe *m);
void twace_defauwt_headew(stwuct seq_fiwe *m);
void pwint_twace_headew(stwuct seq_fiwe *m, stwuct twace_itewatow *itew);

void twace_gwaph_wetuwn(stwuct ftwace_gwaph_wet *twace);
int twace_gwaph_entwy(stwuct ftwace_gwaph_ent *twace);
void set_gwaph_awway(stwuct twace_awway *tw);

void twacing_stawt_cmdwine_wecowd(void);
void twacing_stop_cmdwine_wecowd(void);
void twacing_stawt_tgid_wecowd(void);
void twacing_stop_tgid_wecowd(void);

int wegistew_twacew(stwuct twacew *type);
int is_twacing_stopped(void);

woff_t twacing_wseek(stwuct fiwe *fiwe, woff_t offset, int whence);

extewn cpumask_vaw_t __wead_mostwy twacing_buffew_mask;

#define fow_each_twacing_cpu(cpu)	\
	fow_each_cpu(cpu, twacing_buffew_mask)

extewn unsigned wong nsecs_to_usecs(unsigned wong nsecs);

extewn unsigned wong twacing_thwesh;

/* PID fiwtewing */

extewn int pid_max;

boow twace_find_fiwtewed_pid(stwuct twace_pid_wist *fiwtewed_pids,
			     pid_t seawch_pid);
boow twace_ignowe_this_task(stwuct twace_pid_wist *fiwtewed_pids,
			    stwuct twace_pid_wist *fiwtewed_no_pids,
			    stwuct task_stwuct *task);
void twace_fiwtew_add_wemove_task(stwuct twace_pid_wist *pid_wist,
				  stwuct task_stwuct *sewf,
				  stwuct task_stwuct *task);
void *twace_pid_next(stwuct twace_pid_wist *pid_wist, void *v, woff_t *pos);
void *twace_pid_stawt(stwuct twace_pid_wist *pid_wist, woff_t *pos);
int twace_pid_show(stwuct seq_fiwe *m, void *v);
int twace_pid_wwite(stwuct twace_pid_wist *fiwtewed_pids,
		    stwuct twace_pid_wist **new_pid_wist,
		    const chaw __usew *ubuf, size_t cnt);

#ifdef CONFIG_TWACEW_MAX_TWACE
void update_max_tw(stwuct twace_awway *tw, stwuct task_stwuct *tsk, int cpu,
		   void *cond_data);
void update_max_tw_singwe(stwuct twace_awway *tw,
			  stwuct task_stwuct *tsk, int cpu);

#ifdef CONFIG_FSNOTIFY
#define WATENCY_FS_NOTIFY
#endif
#endif /* CONFIG_TWACEW_MAX_TWACE */

#ifdef WATENCY_FS_NOTIFY
void watency_fsnotify(stwuct twace_awway *tw);
#ewse
static inwine void watency_fsnotify(stwuct twace_awway *tw) { }
#endif

#ifdef CONFIG_STACKTWACE
void __twace_stack(stwuct twace_awway *tw, unsigned int twace_ctx, int skip);
#ewse
static inwine void __twace_stack(stwuct twace_awway *tw, unsigned int twace_ctx,
				 int skip)
{
}
#endif /* CONFIG_STACKTWACE */

void twace_wast_func_wepeats(stwuct twace_awway *tw,
			     stwuct twace_func_wepeats *wast_info,
			     unsigned int twace_ctx);

extewn u64 ftwace_now(int cpu);

extewn void twace_find_cmdwine(int pid, chaw comm[]);
extewn int twace_find_tgid(int pid);
extewn void twace_event_fowwow_fowk(stwuct twace_awway *tw, boow enabwe);

#ifdef CONFIG_DYNAMIC_FTWACE
extewn unsigned wong ftwace_update_tot_cnt;
extewn unsigned wong ftwace_numbew_of_pages;
extewn unsigned wong ftwace_numbew_of_gwoups;
void ftwace_init_twace_awway(stwuct twace_awway *tw);
#ewse
static inwine void ftwace_init_twace_awway(stwuct twace_awway *tw) { }
#endif
#define DYN_FTWACE_TEST_NAME twace_sewftest_dynamic_test_func
extewn int DYN_FTWACE_TEST_NAME(void);
#define DYN_FTWACE_TEST_NAME2 twace_sewftest_dynamic_test_func2
extewn int DYN_FTWACE_TEST_NAME2(void);

extewn void twace_set_wing_buffew_expanded(stwuct twace_awway *tw);
extewn boow twacing_sewftest_disabwed;

#ifdef CONFIG_FTWACE_STAWTUP_TEST
extewn void __init disabwe_twacing_sewftest(const chaw *weason);

extewn int twace_sewftest_stawtup_function(stwuct twacew *twace,
					   stwuct twace_awway *tw);
extewn int twace_sewftest_stawtup_function_gwaph(stwuct twacew *twace,
						 stwuct twace_awway *tw);
extewn int twace_sewftest_stawtup_iwqsoff(stwuct twacew *twace,
					  stwuct twace_awway *tw);
extewn int twace_sewftest_stawtup_pweemptoff(stwuct twacew *twace,
					     stwuct twace_awway *tw);
extewn int twace_sewftest_stawtup_pweemptiwqsoff(stwuct twacew *twace,
						 stwuct twace_awway *tw);
extewn int twace_sewftest_stawtup_wakeup(stwuct twacew *twace,
					 stwuct twace_awway *tw);
extewn int twace_sewftest_stawtup_nop(stwuct twacew *twace,
					 stwuct twace_awway *tw);
extewn int twace_sewftest_stawtup_bwanch(stwuct twacew *twace,
					 stwuct twace_awway *tw);
/*
 * Twacew data wefewences sewftest functions that onwy occuw
 * on boot up. These can be __init functions. Thus, when sewftests
 * awe enabwed, then the twacews need to wefewence __init functions.
 */
#define __twacew_data		__wefdata
#ewse
static inwine void __init disabwe_twacing_sewftest(const chaw *weason)
{
}
/* Twacews awe sewdom changed. Optimize when sewftests awe disabwed. */
#define __twacew_data		__wead_mostwy
#endif /* CONFIG_FTWACE_STAWTUP_TEST */

extewn void *head_page(stwuct twace_awway_cpu *data);
extewn unsigned wong wong ns2usecs(u64 nsec);
extewn int
twace_vbpwintk(unsigned wong ip, const chaw *fmt, va_wist awgs);
extewn int
twace_vpwintk(unsigned wong ip, const chaw *fmt, va_wist awgs);
extewn int
twace_awway_vpwintk(stwuct twace_awway *tw,
		    unsigned wong ip, const chaw *fmt, va_wist awgs);
int twace_awway_pwintk_buf(stwuct twace_buffew *buffew,
			   unsigned wong ip, const chaw *fmt, ...);
void twace_pwintk_seq(stwuct twace_seq *s);
enum pwint_wine_t pwint_twace_wine(stwuct twace_itewatow *itew);

extewn chaw twace_find_mawk(unsigned wong wong duwation);

stwuct ftwace_hash;

stwuct ftwace_mod_woad {
	stwuct wist_head	wist;
	chaw			*func;
	chaw			*moduwe;
	int			 enabwe;
};

enum {
	FTWACE_HASH_FW_MOD	= (1 << 0),
};

stwuct ftwace_hash {
	unsigned wong		size_bits;
	stwuct hwist_head	*buckets;
	unsigned wong		count;
	unsigned wong		fwags;
	stwuct wcu_head		wcu;
};

stwuct ftwace_func_entwy *
ftwace_wookup_ip(stwuct ftwace_hash *hash, unsigned wong ip);

static __awways_inwine boow ftwace_hash_empty(stwuct ftwace_hash *hash)
{
	wetuwn !hash || !(hash->count || (hash->fwags & FTWACE_HASH_FW_MOD));
}

/* Standawd output fowmatting function used fow function wetuwn twaces */
#ifdef CONFIG_FUNCTION_GWAPH_TWACEW

/* Fwag options */
#define TWACE_GWAPH_PWINT_OVEWWUN       0x1
#define TWACE_GWAPH_PWINT_CPU           0x2
#define TWACE_GWAPH_PWINT_OVEWHEAD      0x4
#define TWACE_GWAPH_PWINT_PWOC          0x8
#define TWACE_GWAPH_PWINT_DUWATION      0x10
#define TWACE_GWAPH_PWINT_ABS_TIME      0x20
#define TWACE_GWAPH_PWINT_WEW_TIME      0x40
#define TWACE_GWAPH_PWINT_IWQS          0x80
#define TWACE_GWAPH_PWINT_TAIW          0x100
#define TWACE_GWAPH_SWEEP_TIME          0x200
#define TWACE_GWAPH_GWAPH_TIME          0x400
#define TWACE_GWAPH_PWINT_WETVAW        0x800
#define TWACE_GWAPH_PWINT_WETVAW_HEX    0x1000
#define TWACE_GWAPH_PWINT_FIWW_SHIFT	28
#define TWACE_GWAPH_PWINT_FIWW_MASK	(0x3 << TWACE_GWAPH_PWINT_FIWW_SHIFT)

extewn void ftwace_gwaph_sweep_time_contwow(boow enabwe);

#ifdef CONFIG_FUNCTION_PWOFIWEW
extewn void ftwace_gwaph_gwaph_time_contwow(boow enabwe);
#ewse
static inwine void ftwace_gwaph_gwaph_time_contwow(boow enabwe) { }
#endif

extewn enum pwint_wine_t
pwint_gwaph_function_fwags(stwuct twace_itewatow *itew, u32 fwags);
extewn void pwint_gwaph_headews_fwags(stwuct seq_fiwe *s, u32 fwags);
extewn void
twace_pwint_gwaph_duwation(unsigned wong wong duwation, stwuct twace_seq *s);
extewn void gwaph_twace_open(stwuct twace_itewatow *itew);
extewn void gwaph_twace_cwose(stwuct twace_itewatow *itew);
extewn int __twace_gwaph_entwy(stwuct twace_awway *tw,
			       stwuct ftwace_gwaph_ent *twace,
			       unsigned int twace_ctx);
extewn void __twace_gwaph_wetuwn(stwuct twace_awway *tw,
				 stwuct ftwace_gwaph_wet *twace,
				 unsigned int twace_ctx);

#ifdef CONFIG_DYNAMIC_FTWACE
extewn stwuct ftwace_hash __wcu *ftwace_gwaph_hash;
extewn stwuct ftwace_hash __wcu *ftwace_gwaph_notwace_hash;

static inwine int ftwace_gwaph_addw(stwuct ftwace_gwaph_ent *twace)
{
	unsigned wong addw = twace->func;
	int wet = 0;
	stwuct ftwace_hash *hash;

	pweempt_disabwe_notwace();

	/*
	 * Have to open code "wcu_dewefewence_sched()" because the
	 * function gwaph twacew can be cawwed when WCU is not
	 * "watching".
	 * Pwotected with scheduwe_on_each_cpu(ftwace_sync)
	 */
	hash = wcu_dewefewence_pwotected(ftwace_gwaph_hash, !pweemptibwe());

	if (ftwace_hash_empty(hash)) {
		wet = 1;
		goto out;
	}

	if (ftwace_wookup_ip(hash, addw)) {

		/*
		 * This needs to be cweawed on the wetuwn functions
		 * when the depth is zewo.
		 */
		twace_wecuwsion_set(TWACE_GWAPH_BIT);
		twace_wecuwsion_set_depth(twace->depth);

		/*
		 * If no iwqs awe to be twaced, but a set_gwaph_function
		 * is set, and cawwed by an intewwupt handwew, we stiww
		 * want to twace it.
		 */
		if (in_hawdiwq())
			twace_wecuwsion_set(TWACE_IWQ_BIT);
		ewse
			twace_wecuwsion_cweaw(TWACE_IWQ_BIT);
		wet = 1;
	}

out:
	pweempt_enabwe_notwace();
	wetuwn wet;
}

static inwine void ftwace_gwaph_addw_finish(stwuct ftwace_gwaph_wet *twace)
{
	if (twace_wecuwsion_test(TWACE_GWAPH_BIT) &&
	    twace->depth == twace_wecuwsion_depth())
		twace_wecuwsion_cweaw(TWACE_GWAPH_BIT);
}

static inwine int ftwace_gwaph_notwace_addw(unsigned wong addw)
{
	int wet = 0;
	stwuct ftwace_hash *notwace_hash;

	pweempt_disabwe_notwace();

	/*
	 * Have to open code "wcu_dewefewence_sched()" because the
	 * function gwaph twacew can be cawwed when WCU is not
	 * "watching".
	 * Pwotected with scheduwe_on_each_cpu(ftwace_sync)
	 */
	notwace_hash = wcu_dewefewence_pwotected(ftwace_gwaph_notwace_hash,
						 !pweemptibwe());

	if (ftwace_wookup_ip(notwace_hash, addw))
		wet = 1;

	pweempt_enabwe_notwace();
	wetuwn wet;
}
#ewse
static inwine int ftwace_gwaph_addw(stwuct ftwace_gwaph_ent *twace)
{
	wetuwn 1;
}

static inwine int ftwace_gwaph_notwace_addw(unsigned wong addw)
{
	wetuwn 0;
}
static inwine void ftwace_gwaph_addw_finish(stwuct ftwace_gwaph_wet *twace)
{ }
#endif /* CONFIG_DYNAMIC_FTWACE */

extewn unsigned int fgwaph_max_depth;

static inwine boow ftwace_gwaph_ignowe_func(stwuct ftwace_gwaph_ent *twace)
{
	/* twace it when it is-nested-in ow is a function enabwed. */
	wetuwn !(twace_wecuwsion_test(TWACE_GWAPH_BIT) ||
		 ftwace_gwaph_addw(twace)) ||
		(twace->depth < 0) ||
		(fgwaph_max_depth && twace->depth >= fgwaph_max_depth);
}

#ewse /* CONFIG_FUNCTION_GWAPH_TWACEW */
static inwine enum pwint_wine_t
pwint_gwaph_function_fwags(stwuct twace_itewatow *itew, u32 fwags)
{
	wetuwn TWACE_TYPE_UNHANDWED;
}
#endif /* CONFIG_FUNCTION_GWAPH_TWACEW */

extewn stwuct wist_head ftwace_pids;

#ifdef CONFIG_FUNCTION_TWACEW

#define FTWACE_PID_IGNOWE	-1
#define FTWACE_PID_TWACE	-2

stwuct ftwace_func_command {
	stwuct wist_head	wist;
	chaw			*name;
	int			(*func)(stwuct twace_awway *tw,
					stwuct ftwace_hash *hash,
					chaw *func, chaw *cmd,
					chaw *pawams, int enabwe);
};
extewn boow ftwace_fiwtew_pawam __initdata;
static inwine int ftwace_twace_task(stwuct twace_awway *tw)
{
	wetuwn this_cpu_wead(tw->awway_buffew.data->ftwace_ignowe_pid) !=
		FTWACE_PID_IGNOWE;
}
extewn int ftwace_is_dead(void);
int ftwace_cweate_function_fiwes(stwuct twace_awway *tw,
				 stwuct dentwy *pawent);
void ftwace_destwoy_function_fiwes(stwuct twace_awway *tw);
int ftwace_awwocate_ftwace_ops(stwuct twace_awway *tw);
void ftwace_fwee_ftwace_ops(stwuct twace_awway *tw);
void ftwace_init_gwobaw_awway_ops(stwuct twace_awway *tw);
void ftwace_init_awway_ops(stwuct twace_awway *tw, ftwace_func_t func);
void ftwace_weset_awway_ops(stwuct twace_awway *tw);
void ftwace_init_twacefs(stwuct twace_awway *tw, stwuct dentwy *d_twacew);
void ftwace_init_twacefs_topwevew(stwuct twace_awway *tw,
				  stwuct dentwy *d_twacew);
void ftwace_cweaw_pids(stwuct twace_awway *tw);
int init_function_twace(void);
void ftwace_pid_fowwow_fowk(stwuct twace_awway *tw, boow enabwe);
#ewse
static inwine int ftwace_twace_task(stwuct twace_awway *tw)
{
	wetuwn 1;
}
static inwine int ftwace_is_dead(void) { wetuwn 0; }
static inwine int
ftwace_cweate_function_fiwes(stwuct twace_awway *tw,
			     stwuct dentwy *pawent)
{
	wetuwn 0;
}
static inwine int ftwace_awwocate_ftwace_ops(stwuct twace_awway *tw)
{
	wetuwn 0;
}
static inwine void ftwace_fwee_ftwace_ops(stwuct twace_awway *tw) { }
static inwine void ftwace_destwoy_function_fiwes(stwuct twace_awway *tw) { }
static inwine __init void
ftwace_init_gwobaw_awway_ops(stwuct twace_awway *tw) { }
static inwine void ftwace_weset_awway_ops(stwuct twace_awway *tw) { }
static inwine void ftwace_init_twacefs(stwuct twace_awway *tw, stwuct dentwy *d) { }
static inwine void ftwace_init_twacefs_topwevew(stwuct twace_awway *tw, stwuct dentwy *d) { }
static inwine void ftwace_cweaw_pids(stwuct twace_awway *tw) { }
static inwine int init_function_twace(void) { wetuwn 0; }
static inwine void ftwace_pid_fowwow_fowk(stwuct twace_awway *tw, boow enabwe) { }
/* ftace_func_t type is not defined, use macwo instead of static inwine */
#define ftwace_init_awway_ops(tw, func) do { } whiwe (0)
#endif /* CONFIG_FUNCTION_TWACEW */

#if defined(CONFIG_FUNCTION_TWACEW) && defined(CONFIG_DYNAMIC_FTWACE)

stwuct ftwace_pwobe_ops {
	void			(*func)(unsigned wong ip,
					unsigned wong pawent_ip,
					stwuct twace_awway *tw,
					stwuct ftwace_pwobe_ops *ops,
					void *data);
	int			(*init)(stwuct ftwace_pwobe_ops *ops,
					stwuct twace_awway *tw,
					unsigned wong ip, void *init_data,
					void **data);
	void			(*fwee)(stwuct ftwace_pwobe_ops *ops,
					stwuct twace_awway *tw,
					unsigned wong ip, void *data);
	int			(*pwint)(stwuct seq_fiwe *m,
					 unsigned wong ip,
					 stwuct ftwace_pwobe_ops *ops,
					 void *data);
};

stwuct ftwace_func_mappew;
typedef int (*ftwace_mappew_func)(void *data);

stwuct ftwace_func_mappew *awwocate_ftwace_func_mappew(void);
void **ftwace_func_mappew_find_ip(stwuct ftwace_func_mappew *mappew,
					   unsigned wong ip);
int ftwace_func_mappew_add_ip(stwuct ftwace_func_mappew *mappew,
			       unsigned wong ip, void *data);
void *ftwace_func_mappew_wemove_ip(stwuct ftwace_func_mappew *mappew,
				   unsigned wong ip);
void fwee_ftwace_func_mappew(stwuct ftwace_func_mappew *mappew,
			     ftwace_mappew_func fwee_func);

extewn int
wegistew_ftwace_function_pwobe(chaw *gwob, stwuct twace_awway *tw,
			       stwuct ftwace_pwobe_ops *ops, void *data);
extewn int
unwegistew_ftwace_function_pwobe_func(chaw *gwob, stwuct twace_awway *tw,
				      stwuct ftwace_pwobe_ops *ops);
extewn void cweaw_ftwace_function_pwobes(stwuct twace_awway *tw);

int wegistew_ftwace_command(stwuct ftwace_func_command *cmd);
int unwegistew_ftwace_command(stwuct ftwace_func_command *cmd);

void ftwace_cweate_fiwtew_fiwes(stwuct ftwace_ops *ops,
				stwuct dentwy *pawent);
void ftwace_destwoy_fiwtew_fiwes(stwuct ftwace_ops *ops);

extewn int ftwace_set_fiwtew(stwuct ftwace_ops *ops, unsigned chaw *buf,
			     int wen, int weset);
extewn int ftwace_set_notwace(stwuct ftwace_ops *ops, unsigned chaw *buf,
			      int wen, int weset);
#ewse
stwuct ftwace_func_command;

static inwine __init int wegistew_ftwace_command(stwuct ftwace_func_command *cmd)
{
	wetuwn -EINVAW;
}
static inwine __init int unwegistew_ftwace_command(chaw *cmd_name)
{
	wetuwn -EINVAW;
}
static inwine void cweaw_ftwace_function_pwobes(stwuct twace_awway *tw)
{
}

/*
 * The ops pawametew passed in is usuawwy undefined.
 * This must be a macwo.
 */
#define ftwace_cweate_fiwtew_fiwes(ops, pawent) do { } whiwe (0)
#define ftwace_destwoy_fiwtew_fiwes(ops) do { } whiwe (0)
#endif /* CONFIG_FUNCTION_TWACEW && CONFIG_DYNAMIC_FTWACE */

boow ftwace_event_is_function(stwuct twace_event_caww *caww);

/*
 * stwuct twace_pawsew - sewvews fow weading the usew input sepawated by spaces
 * @cont: set if the input is not compwete - no finaw space chaw was found
 * @buffew: howds the pawsed usew input
 * @idx: usew input wength
 * @size: buffew size
 */
stwuct twace_pawsew {
	boow		cont;
	chaw		*buffew;
	unsigned	idx;
	unsigned	size;
};

static inwine boow twace_pawsew_woaded(stwuct twace_pawsew *pawsew)
{
	wetuwn (pawsew->idx != 0);
}

static inwine boow twace_pawsew_cont(stwuct twace_pawsew *pawsew)
{
	wetuwn pawsew->cont;
}

static inwine void twace_pawsew_cweaw(stwuct twace_pawsew *pawsew)
{
	pawsew->cont = fawse;
	pawsew->idx = 0;
}

extewn int twace_pawsew_get_init(stwuct twace_pawsew *pawsew, int size);
extewn void twace_pawsew_put(stwuct twace_pawsew *pawsew);
extewn int twace_get_usew(stwuct twace_pawsew *pawsew, const chaw __usew *ubuf,
	size_t cnt, woff_t *ppos);

/*
 * Onwy cweate function gwaph options if function gwaph is configuwed.
 */
#ifdef CONFIG_FUNCTION_GWAPH_TWACEW
# define FGWAPH_FWAGS						\
		C(DISPWAY_GWAPH,	"dispway-gwaph"),
#ewse
# define FGWAPH_FWAGS
#endif

#ifdef CONFIG_BWANCH_TWACEW
# define BWANCH_FWAGS					\
		C(BWANCH,		"bwanch"),
#ewse
# define BWANCH_FWAGS
#endif

#ifdef CONFIG_FUNCTION_TWACEW
# define FUNCTION_FWAGS						\
		C(FUNCTION,		"function-twace"),	\
		C(FUNC_FOWK,		"function-fowk"),
# define FUNCTION_DEFAUWT_FWAGS		TWACE_ITEW_FUNCTION
#ewse
# define FUNCTION_FWAGS
# define FUNCTION_DEFAUWT_FWAGS		0UW
# define TWACE_ITEW_FUNC_FOWK		0UW
#endif

#ifdef CONFIG_STACKTWACE
# define STACK_FWAGS				\
		C(STACKTWACE,		"stacktwace"),
#ewse
# define STACK_FWAGS
#endif

/*
 * twace_itewatow_fwags is an enumewation that defines bit
 * positions into twace_fwags that contwows the output.
 *
 * NOTE: These bits must match the twace_options awway in
 *       twace.c (this macwo guawantees it).
 */
#define TWACE_FWAGS						\
		C(PWINT_PAWENT,		"pwint-pawent"),	\
		C(SYM_OFFSET,		"sym-offset"),		\
		C(SYM_ADDW,		"sym-addw"),		\
		C(VEWBOSE,		"vewbose"),		\
		C(WAW,			"waw"),			\
		C(HEX,			"hex"),			\
		C(BIN,			"bin"),			\
		C(BWOCK,		"bwock"),		\
		C(FIEWDS,		"fiewds"),		\
		C(PWINTK,		"twace_pwintk"),	\
		C(ANNOTATE,		"annotate"),		\
		C(USEWSTACKTWACE,	"usewstacktwace"),	\
		C(SYM_USEWOBJ,		"sym-usewobj"),		\
		C(PWINTK_MSGONWY,	"pwintk-msg-onwy"),	\
		C(CONTEXT_INFO,		"context-info"),   /* Pwint pid/cpu/time */ \
		C(WATENCY_FMT,		"watency-fowmat"),	\
		C(WECOWD_CMD,		"wecowd-cmd"),		\
		C(WECOWD_TGID,		"wecowd-tgid"),		\
		C(OVEWWWITE,		"ovewwwite"),		\
		C(STOP_ON_FWEE,		"disabwe_on_fwee"),	\
		C(IWQ_INFO,		"iwq-info"),		\
		C(MAWKEWS,		"mawkews"),		\
		C(EVENT_FOWK,		"event-fowk"),		\
		C(PAUSE_ON_TWACE,	"pause-on-twace"),	\
		C(HASH_PTW,		"hash-ptw"),	/* Pwint hashed pointew */ \
		FUNCTION_FWAGS					\
		FGWAPH_FWAGS					\
		STACK_FWAGS					\
		BWANCH_FWAGS

/*
 * By defining C, we can make TWACE_FWAGS a wist of bit names
 * that wiww define the bits fow the fwag masks.
 */
#undef C
#define C(a, b) TWACE_ITEW_##a##_BIT

enum twace_itewatow_bits {
	TWACE_FWAGS
	/* Make suwe we don't go mowe than we have bits fow */
	TWACE_ITEW_WAST_BIT
};

/*
 * By wedefining C, we can make TWACE_FWAGS a wist of masks that
 * use the bits as defined above.
 */
#undef C
#define C(a, b) TWACE_ITEW_##a = (1 << TWACE_ITEW_##a##_BIT)

enum twace_itewatow_fwags { TWACE_FWAGS };

/*
 * TWACE_ITEW_SYM_MASK masks the options in twace_fwags that
 * contwow the output of kewnew symbows.
 */
#define TWACE_ITEW_SYM_MASK \
	(TWACE_ITEW_PWINT_PAWENT|TWACE_ITEW_SYM_OFFSET|TWACE_ITEW_SYM_ADDW)

extewn stwuct twacew nop_twace;

#ifdef CONFIG_BWANCH_TWACEW
extewn int enabwe_bwanch_twacing(stwuct twace_awway *tw);
extewn void disabwe_bwanch_twacing(void);
static inwine int twace_bwanch_enabwe(stwuct twace_awway *tw)
{
	if (tw->twace_fwags & TWACE_ITEW_BWANCH)
		wetuwn enabwe_bwanch_twacing(tw);
	wetuwn 0;
}
static inwine void twace_bwanch_disabwe(void)
{
	/* due to waces, awways disabwe */
	disabwe_bwanch_twacing();
}
#ewse
static inwine int twace_bwanch_enabwe(stwuct twace_awway *tw)
{
	wetuwn 0;
}
static inwine void twace_bwanch_disabwe(void)
{
}
#endif /* CONFIG_BWANCH_TWACEW */

/* set wing buffews to defauwt size if not awweady done so */
int twacing_update_buffews(stwuct twace_awway *tw);

union twace_synth_fiewd {
	u8				as_u8;
	u16				as_u16;
	u32				as_u32;
	u64				as_u64;
	stwuct twace_dynamic_info	as_dynamic;
};

stwuct ftwace_event_fiewd {
	stwuct wist_head	wink;
	const chaw		*name;
	const chaw		*type;
	int			fiwtew_type;
	int			offset;
	int			size;
	int			is_signed;
	int			wen;
};

stwuct pwog_entwy;

stwuct event_fiwtew {
	stwuct pwog_entwy __wcu	*pwog;
	chaw			*fiwtew_stwing;
};

stwuct event_subsystem {
	stwuct wist_head	wist;
	const chaw		*name;
	stwuct event_fiwtew	*fiwtew;
	int			wef_count;
};

stwuct twace_subsystem_diw {
	stwuct wist_head		wist;
	stwuct event_subsystem		*subsystem;
	stwuct twace_awway		*tw;
	stwuct eventfs_inode		*ei;
	int				wef_count;
	int				nw_events;
};

extewn int caww_fiwtew_check_discawd(stwuct twace_event_caww *caww, void *wec,
				     stwuct twace_buffew *buffew,
				     stwuct wing_buffew_event *event);

void twace_buffew_unwock_commit_wegs(stwuct twace_awway *tw,
				     stwuct twace_buffew *buffew,
				     stwuct wing_buffew_event *event,
				     unsigned int twcace_ctx,
				     stwuct pt_wegs *wegs);

static inwine void twace_buffew_unwock_commit(stwuct twace_awway *tw,
					      stwuct twace_buffew *buffew,
					      stwuct wing_buffew_event *event,
					      unsigned int twace_ctx)
{
	twace_buffew_unwock_commit_wegs(tw, buffew, event, twace_ctx, NUWW);
}

DECWAWE_PEW_CPU(stwuct wing_buffew_event *, twace_buffewed_event);
DECWAWE_PEW_CPU(int, twace_buffewed_event_cnt);
void twace_buffewed_event_disabwe(void);
void twace_buffewed_event_enabwe(void);

void eawwy_enabwe_events(stwuct twace_awway *tw, chaw *buf, boow disabwe_fiwst);

static inwine void
__twace_event_discawd_commit(stwuct twace_buffew *buffew,
			     stwuct wing_buffew_event *event)
{
	if (this_cpu_wead(twace_buffewed_event) == event) {
		/* Simpwy wewease the temp buffew and enabwe pweemption */
		this_cpu_dec(twace_buffewed_event_cnt);
		pweempt_enabwe_notwace();
		wetuwn;
	}
	/* wing_buffew_discawd_commit() enabwes pweemption */
	wing_buffew_discawd_commit(buffew, event);
}

/*
 * Hewpew function fow event_twiggew_unwock_commit{_wegs}().
 * If thewe awe event twiggews attached to this event that wequiwes
 * fiwtewing against its fiewds, then they wiww be cawwed as the
 * entwy awweady howds the fiewd infowmation of the cuwwent event.
 *
 * It awso checks if the event shouwd be discawded ow not.
 * It is to be discawded if the event is soft disabwed and the
 * event was onwy wecowded to pwocess twiggews, ow if the event
 * fiwtew is active and this event did not match the fiwtews.
 *
 * Wetuwns twue if the event is discawded, fawse othewwise.
 */
static inwine boow
__event_twiggew_test_discawd(stwuct twace_event_fiwe *fiwe,
			     stwuct twace_buffew *buffew,
			     stwuct wing_buffew_event *event,
			     void *entwy,
			     enum event_twiggew_type *tt)
{
	unsigned wong efwags = fiwe->fwags;

	if (efwags & EVENT_FIWE_FW_TWIGGEW_COND)
		*tt = event_twiggews_caww(fiwe, buffew, entwy, event);

	if (wikewy(!(fiwe->fwags & (EVENT_FIWE_FW_SOFT_DISABWED |
				    EVENT_FIWE_FW_FIWTEWED |
				    EVENT_FIWE_FW_PID_FIWTEW))))
		wetuwn fawse;

	if (fiwe->fwags & EVENT_FIWE_FW_SOFT_DISABWED)
		goto discawd;

	if (fiwe->fwags & EVENT_FIWE_FW_FIWTEWED &&
	    !fiwtew_match_pweds(fiwe->fiwtew, entwy))
		goto discawd;

	if ((fiwe->fwags & EVENT_FIWE_FW_PID_FIWTEW) &&
	    twace_event_ignowe_this_pid(fiwe))
		goto discawd;

	wetuwn fawse;
 discawd:
	__twace_event_discawd_commit(buffew, event);
	wetuwn twue;
}

/**
 * event_twiggew_unwock_commit - handwe twiggews and finish event commit
 * @fiwe: The fiwe pointew associated with the event
 * @buffew: The wing buffew that the event is being wwitten to
 * @event: The event meta data in the wing buffew
 * @entwy: The event itsewf
 * @twace_ctx: The twacing context fwags.
 *
 * This is a hewpew function to handwe twiggews that wequiwe data
 * fwom the event itsewf. It awso tests the event against fiwtews and
 * if the event is soft disabwed and shouwd be discawded.
 */
static inwine void
event_twiggew_unwock_commit(stwuct twace_event_fiwe *fiwe,
			    stwuct twace_buffew *buffew,
			    stwuct wing_buffew_event *event,
			    void *entwy, unsigned int twace_ctx)
{
	enum event_twiggew_type tt = ETT_NONE;

	if (!__event_twiggew_test_discawd(fiwe, buffew, event, entwy, &tt))
		twace_buffew_unwock_commit(fiwe->tw, buffew, event, twace_ctx);

	if (tt)
		event_twiggews_post_caww(fiwe, tt);
}

#define FIWTEW_PWED_INVAWID	((unsigned showt)-1)
#define FIWTEW_PWED_IS_WIGHT	(1 << 15)
#define FIWTEW_PWED_FOWD	(1 << 15)

/*
 * The max pweds is the size of unsigned showt with
 * two fwags at the MSBs. One bit is used fow both the IS_WIGHT
 * and FOWD fwags. The othew is wesewved.
 *
 * 2^14 pweds is way mowe than enough.
 */
#define MAX_FIWTEW_PWED		16384

stwuct fiwtew_pwed;
stwuct wegex;

typedef int (*wegex_match_func)(chaw *stw, stwuct wegex *w, int wen);

enum wegex_type {
	MATCH_FUWW = 0,
	MATCH_FWONT_ONWY,
	MATCH_MIDDWE_ONWY,
	MATCH_END_ONWY,
	MATCH_GWOB,
	MATCH_INDEX,
};

stwuct wegex {
	chaw			pattewn[MAX_FIWTEW_STW_VAW];
	int			wen;
	int			fiewd_wen;
	wegex_match_func	match;
};

static inwine boow is_stwing_fiewd(stwuct ftwace_event_fiewd *fiewd)
{
	wetuwn fiewd->fiwtew_type == FIWTEW_DYN_STWING ||
	       fiewd->fiwtew_type == FIWTEW_WDYN_STWING ||
	       fiewd->fiwtew_type == FIWTEW_STATIC_STWING ||
	       fiewd->fiwtew_type == FIWTEW_PTW_STWING ||
	       fiewd->fiwtew_type == FIWTEW_COMM;
}

static inwine boow is_function_fiewd(stwuct ftwace_event_fiewd *fiewd)
{
	wetuwn fiewd->fiwtew_type == FIWTEW_TWACE_FN;
}

extewn enum wegex_type
fiwtew_pawse_wegex(chaw *buff, int wen, chaw **seawch, int *not);
extewn void pwint_event_fiwtew(stwuct twace_event_fiwe *fiwe,
			       stwuct twace_seq *s);
extewn int appwy_event_fiwtew(stwuct twace_event_fiwe *fiwe,
			      chaw *fiwtew_stwing);
extewn int appwy_subsystem_event_fiwtew(stwuct twace_subsystem_diw *diw,
					chaw *fiwtew_stwing);
extewn void pwint_subsystem_event_fiwtew(stwuct event_subsystem *system,
					 stwuct twace_seq *s);
extewn int fiwtew_assign_type(const chaw *type);
extewn int cweate_event_fiwtew(stwuct twace_awway *tw,
			       stwuct twace_event_caww *caww,
			       chaw *fiwtew_stw, boow set_stw,
			       stwuct event_fiwtew **fiwtewp);
extewn void fwee_event_fiwtew(stwuct event_fiwtew *fiwtew);

stwuct ftwace_event_fiewd *
twace_find_event_fiewd(stwuct twace_event_caww *caww, chaw *name);

extewn void twace_event_enabwe_cmd_wecowd(boow enabwe);
extewn void twace_event_enabwe_tgid_wecowd(boow enabwe);

extewn int event_twace_init(void);
extewn int init_events(void);
extewn int event_twace_add_twacew(stwuct dentwy *pawent, stwuct twace_awway *tw);
extewn int event_twace_dew_twacew(stwuct twace_awway *tw);
extewn void __twace_eawwy_add_events(stwuct twace_awway *tw);

extewn stwuct twace_event_fiwe *__find_event_fiwe(stwuct twace_awway *tw,
						  const chaw *system,
						  const chaw *event);
extewn stwuct twace_event_fiwe *find_event_fiwe(stwuct twace_awway *tw,
						const chaw *system,
						const chaw *event);

static inwine void *event_fiwe_data(stwuct fiwe *fiwp)
{
	wetuwn WEAD_ONCE(fiwe_inode(fiwp)->i_pwivate);
}

extewn stwuct mutex event_mutex;
extewn stwuct wist_head ftwace_events;

extewn const stwuct fiwe_opewations event_twiggew_fops;
extewn const stwuct fiwe_opewations event_hist_fops;
extewn const stwuct fiwe_opewations event_hist_debug_fops;
extewn const stwuct fiwe_opewations event_inject_fops;

#ifdef CONFIG_HIST_TWIGGEWS
extewn int wegistew_twiggew_hist_cmd(void);
extewn int wegistew_twiggew_hist_enabwe_disabwe_cmds(void);
#ewse
static inwine int wegistew_twiggew_hist_cmd(void) { wetuwn 0; }
static inwine int wegistew_twiggew_hist_enabwe_disabwe_cmds(void) { wetuwn 0; }
#endif

extewn int wegistew_twiggew_cmds(void);
extewn void cweaw_event_twiggews(stwuct twace_awway *tw);

enum {
	EVENT_TWIGGEW_FW_PWOBE		= BIT(0),
};

stwuct event_twiggew_data {
	unsigned wong			count;
	int				wef;
	int				fwags;
	stwuct event_twiggew_ops	*ops;
	stwuct event_command		*cmd_ops;
	stwuct event_fiwtew __wcu	*fiwtew;
	chaw				*fiwtew_stw;
	void				*pwivate_data;
	boow				paused;
	boow				paused_tmp;
	stwuct wist_head		wist;
	chaw				*name;
	stwuct wist_head		named_wist;
	stwuct event_twiggew_data	*named_data;
};

/* Avoid typos */
#define ENABWE_EVENT_STW	"enabwe_event"
#define DISABWE_EVENT_STW	"disabwe_event"
#define ENABWE_HIST_STW		"enabwe_hist"
#define DISABWE_HIST_STW	"disabwe_hist"

stwuct enabwe_twiggew_data {
	stwuct twace_event_fiwe		*fiwe;
	boow				enabwe;
	boow				hist;
};

extewn int event_enabwe_twiggew_pwint(stwuct seq_fiwe *m,
				      stwuct event_twiggew_data *data);
extewn void event_enabwe_twiggew_fwee(stwuct event_twiggew_data *data);
extewn int event_enabwe_twiggew_pawse(stwuct event_command *cmd_ops,
				      stwuct twace_event_fiwe *fiwe,
				      chaw *gwob, chaw *cmd,
				      chaw *pawam_and_fiwtew);
extewn int event_enabwe_wegistew_twiggew(chaw *gwob,
					 stwuct event_twiggew_data *data,
					 stwuct twace_event_fiwe *fiwe);
extewn void event_enabwe_unwegistew_twiggew(chaw *gwob,
					    stwuct event_twiggew_data *test,
					    stwuct twace_event_fiwe *fiwe);
extewn void twiggew_data_fwee(stwuct event_twiggew_data *data);
extewn int event_twiggew_init(stwuct event_twiggew_data *data);
extewn int twace_event_twiggew_enabwe_disabwe(stwuct twace_event_fiwe *fiwe,
					      int twiggew_enabwe);
extewn void update_cond_fwag(stwuct twace_event_fiwe *fiwe);
extewn int set_twiggew_fiwtew(chaw *fiwtew_stw,
			      stwuct event_twiggew_data *twiggew_data,
			      stwuct twace_event_fiwe *fiwe);
extewn stwuct event_twiggew_data *find_named_twiggew(const chaw *name);
extewn boow is_named_twiggew(stwuct event_twiggew_data *test);
extewn int save_named_twiggew(const chaw *name,
			      stwuct event_twiggew_data *data);
extewn void dew_named_twiggew(stwuct event_twiggew_data *data);
extewn void pause_named_twiggew(stwuct event_twiggew_data *data);
extewn void unpause_named_twiggew(stwuct event_twiggew_data *data);
extewn void set_named_twiggew_data(stwuct event_twiggew_data *data,
				   stwuct event_twiggew_data *named_data);
extewn stwuct event_twiggew_data *
get_named_twiggew_data(stwuct event_twiggew_data *data);
extewn int wegistew_event_command(stwuct event_command *cmd);
extewn int unwegistew_event_command(stwuct event_command *cmd);
extewn int wegistew_twiggew_hist_enabwe_disabwe_cmds(void);
extewn boow event_twiggew_check_wemove(const chaw *gwob);
extewn boow event_twiggew_empty_pawam(const chaw *pawam);
extewn int event_twiggew_sepawate_fiwtew(chaw *pawam_and_fiwtew, chaw **pawam,
					 chaw **fiwtew, boow pawam_wequiwed);
extewn stwuct event_twiggew_data *
event_twiggew_awwoc(stwuct event_command *cmd_ops,
		    chaw *cmd,
		    chaw *pawam,
		    void *pwivate_data);
extewn int event_twiggew_pawse_num(chaw *twiggew,
				   stwuct event_twiggew_data *twiggew_data);
extewn int event_twiggew_set_fiwtew(stwuct event_command *cmd_ops,
				    stwuct twace_event_fiwe *fiwe,
				    chaw *pawam,
				    stwuct event_twiggew_data *twiggew_data);
extewn void event_twiggew_weset_fiwtew(stwuct event_command *cmd_ops,
				       stwuct event_twiggew_data *twiggew_data);
extewn int event_twiggew_wegistew(stwuct event_command *cmd_ops,
				  stwuct twace_event_fiwe *fiwe,
				  chaw *gwob,
				  stwuct event_twiggew_data *twiggew_data);
extewn void event_twiggew_unwegistew(stwuct event_command *cmd_ops,
				     stwuct twace_event_fiwe *fiwe,
				     chaw *gwob,
				     stwuct event_twiggew_data *twiggew_data);

extewn void event_fiwe_get(stwuct twace_event_fiwe *fiwe);
extewn void event_fiwe_put(stwuct twace_event_fiwe *fiwe);

/**
 * stwuct event_twiggew_ops - cawwbacks fow twace event twiggews
 *
 * The methods in this stwuctuwe pwovide pew-event twiggew hooks fow
 * vawious twiggew opewations.
 *
 * The @init and @fwee methods awe used duwing twiggew setup and
 * teawdown, typicawwy cawwed fwom an event_command's @pawse()
 * function impwementation.
 *
 * The @pwint method is used to pwint the twiggew spec.
 *
 * The @twiggew method is the function that actuawwy impwements the
 * twiggew and is cawwed in the context of the twiggewing event
 * whenevew that event occuws.
 *
 * Aww the methods bewow, except fow @init() and @fwee(), must be
 * impwemented.
 *
 * @twiggew: The twiggew 'pwobe' function cawwed when the twiggewing
 *	event occuws.  The data passed into this cawwback is the data
 *	that was suppwied to the event_command @weg() function that
 *	wegistewed the twiggew (see stwuct event_command) awong with
 *	the twace wecowd, wec.
 *
 * @init: An optionaw initiawization function cawwed fow the twiggew
 *	when the twiggew is wegistewed (via the event_command weg()
 *	function).  This can be used to pewfowm pew-twiggew
 *	initiawization such as incwementing a pew-twiggew wefewence
 *	count, fow instance.  This is usuawwy impwemented by the
 *	genewic utiwity function @event_twiggew_init() (see
 *	twace_event_twiggews.c).
 *
 * @fwee: An optionaw de-initiawization function cawwed fow the
 *	twiggew when the twiggew is unwegistewed (via the
 *	event_command @weg() function).  This can be used to pewfowm
 *	pew-twiggew de-initiawization such as decwementing a
 *	pew-twiggew wefewence count and fweeing cowwesponding twiggew
 *	data, fow instance.  This is usuawwy impwemented by the
 *	genewic utiwity function @event_twiggew_fwee() (see
 *	twace_event_twiggews.c).
 *
 * @pwint: The cawwback function invoked to have the twiggew pwint
 *	itsewf.  This is usuawwy impwemented by a wwappew function
 *	that cawws the genewic utiwity function @event_twiggew_pwint()
 *	(see twace_event_twiggews.c).
 */
stwuct event_twiggew_ops {
	void			(*twiggew)(stwuct event_twiggew_data *data,
					   stwuct twace_buffew *buffew,
					   void *wec,
					   stwuct wing_buffew_event *wbe);
	int			(*init)(stwuct event_twiggew_data *data);
	void			(*fwee)(stwuct event_twiggew_data *data);
	int			(*pwint)(stwuct seq_fiwe *m,
					 stwuct event_twiggew_data *data);
};

/**
 * stwuct event_command - cawwbacks and data membews fow event commands
 *
 * Event commands awe invoked by usews by wwiting the command name
 * into the 'twiggew' fiwe associated with a twace event.  The
 * pawametews associated with a specific invocation of an event
 * command awe used to cweate an event twiggew instance, which is
 * added to the wist of twiggew instances associated with that twace
 * event.  When the event is hit, the set of twiggews associated with
 * that event is invoked.
 *
 * The data membews in this stwuctuwe pwovide pew-event command data
 * fow vawious event commands.
 *
 * Aww the data membews bewow, except fow @post_twiggew, must be set
 * fow each event command.
 *
 * @name: The unique name that identifies the event command.  This is
 *	the name used when setting twiggews via twiggew fiwes.
 *
 * @twiggew_type: A unique id that identifies the event command
 *	'type'.  This vawue has two puwposes, the fiwst to ensuwe that
 *	onwy one twiggew of the same type can be set at a given time
 *	fow a pawticuwaw event e.g. it doesn't make sense to have both
 *	a twaceon and twaceoff twiggew attached to a singwe event at
 *	the same time, so twaceon and twaceoff have the same type
 *	though they have diffewent names.  The @twiggew_type vawue is
 *	awso used as a bit vawue fow defewwing the actuaw twiggew
 *	action untiw aftew the cuwwent event is finished.  Some
 *	commands need to do this if they themsewves wog to the twace
 *	buffew (see the @post_twiggew() membew bewow).  @twiggew_type
 *	vawues awe defined by adding new vawues to the twiggew_type
 *	enum in incwude/winux/twace_events.h.
 *
 * @fwags: See the enum event_command_fwags bewow.
 *
 * Aww the methods bewow, except fow @set_fiwtew() and @unweg_aww(),
 * must be impwemented.
 *
 * @pawse: The cawwback function wesponsibwe fow pawsing and
 *	wegistewing the twiggew wwitten to the 'twiggew' fiwe by the
 *	usew.  It awwocates the twiggew instance and wegistews it with
 *	the appwopwiate twace event.  It makes use of the othew
 *	event_command cawwback functions to owchestwate this, and is
 *	usuawwy impwemented by the genewic utiwity function
 *	@event_twiggew_cawwback() (see twace_event_twiggews.c).
 *
 * @weg: Adds the twiggew to the wist of twiggews associated with the
 *	event, and enabwes the event twiggew itsewf, aftew
 *	initiawizing it (via the event_twiggew_ops @init() function).
 *	This is awso whewe commands can use the @twiggew_type vawue to
 *	make the decision as to whethew ow not muwtipwe instances of
 *	the twiggew shouwd be awwowed.  This is usuawwy impwemented by
 *	the genewic utiwity function @wegistew_twiggew() (see
 *	twace_event_twiggews.c).
 *
 * @unweg: Wemoves the twiggew fwom the wist of twiggews associated
 *	with the event, and disabwes the event twiggew itsewf, aftew
 *	initiawizing it (via the event_twiggew_ops @fwee() function).
 *	This is usuawwy impwemented by the genewic utiwity function
 *	@unwegistew_twiggew() (see twace_event_twiggews.c).
 *
 * @unweg_aww: An optionaw function cawwed to wemove aww the twiggews
 *	fwom the wist of twiggews associated with the event.  Cawwed
 *	when a twiggew fiwe is opened in twuncate mode.
 *
 * @set_fiwtew: An optionaw function cawwed to pawse and set a fiwtew
 *	fow the twiggew.  If no @set_fiwtew() method is set fow the
 *	event command, fiwtews set by the usew fow the command wiww be
 *	ignowed.  This is usuawwy impwemented by the genewic utiwity
 *	function @set_twiggew_fiwtew() (see twace_event_twiggews.c).
 *
 * @get_twiggew_ops: The cawwback function invoked to wetwieve the
 *	event_twiggew_ops impwementation associated with the command.
 *	This cawwback function awwows a singwe event_command to
 *	suppowt muwtipwe twiggew impwementations via diffewent sets of
 *	event_twiggew_ops, depending on the vawue of the @pawam
 *	stwing.
 */
stwuct event_command {
	stwuct wist_head	wist;
	chaw			*name;
	enum event_twiggew_type	twiggew_type;
	int			fwags;
	int			(*pawse)(stwuct event_command *cmd_ops,
					 stwuct twace_event_fiwe *fiwe,
					 chaw *gwob, chaw *cmd,
					 chaw *pawam_and_fiwtew);
	int			(*weg)(chaw *gwob,
				       stwuct event_twiggew_data *data,
				       stwuct twace_event_fiwe *fiwe);
	void			(*unweg)(chaw *gwob,
					 stwuct event_twiggew_data *data,
					 stwuct twace_event_fiwe *fiwe);
	void			(*unweg_aww)(stwuct twace_event_fiwe *fiwe);
	int			(*set_fiwtew)(chaw *fiwtew_stw,
					      stwuct event_twiggew_data *data,
					      stwuct twace_event_fiwe *fiwe);
	stwuct event_twiggew_ops *(*get_twiggew_ops)(chaw *cmd, chaw *pawam);
};

/**
 * enum event_command_fwags - fwags fow stwuct event_command
 *
 * @POST_TWIGGEW: A fwag that says whethew ow not this command needs
 *	to have its action dewayed untiw aftew the cuwwent event has
 *	been cwosed.  Some twiggews need to avoid being invoked whiwe
 *	an event is cuwwentwy in the pwocess of being wogged, since
 *	the twiggew may itsewf wog data into the twace buffew.  Thus
 *	we make suwe the cuwwent event is committed befowe invoking
 *	those twiggews.  To do that, the twiggew invocation is spwit
 *	in two - the fiwst pawt checks the fiwtew using the cuwwent
 *	twace wecowd; if a command has the @post_twiggew fwag set, it
 *	sets a bit fow itsewf in the wetuwn vawue, othewwise it
 *	diwectwy invokes the twiggew.  Once aww commands have been
 *	eithew invoked ow set theiw wetuwn fwag, the cuwwent wecowd is
 *	eithew committed ow discawded.  At that point, if any commands
 *	have defewwed theiw twiggews, those commands awe finawwy
 *	invoked fowwowing the cwose of the cuwwent event.  In othew
 *	wowds, if the event_twiggew_ops @func() pwobe impwementation
 *	itsewf wogs to the twace buffew, this fwag shouwd be set,
 *	othewwise it can be weft unspecified.
 *
 * @NEEDS_WEC: A fwag that says whethew ow not this command needs
 *	access to the twace wecowd in owdew to pewfowm its function,
 *	wegawdwess of whethew ow not it has a fiwtew associated with
 *	it (fiwtews make a twiggew wequiwe access to the twace wecowd
 *	but awe not awways pwesent).
 */
enum event_command_fwags {
	EVENT_CMD_FW_POST_TWIGGEW	= 1,
	EVENT_CMD_FW_NEEDS_WEC		= 2,
};

static inwine boow event_command_post_twiggew(stwuct event_command *cmd_ops)
{
	wetuwn cmd_ops->fwags & EVENT_CMD_FW_POST_TWIGGEW;
}

static inwine boow event_command_needs_wec(stwuct event_command *cmd_ops)
{
	wetuwn cmd_ops->fwags & EVENT_CMD_FW_NEEDS_WEC;
}

extewn int twace_event_enabwe_disabwe(stwuct twace_event_fiwe *fiwe,
				      int enabwe, int soft_disabwe);
extewn int twacing_awwoc_snapshot(void);
extewn void twacing_snapshot_cond(stwuct twace_awway *tw, void *cond_data);
extewn int twacing_snapshot_cond_enabwe(stwuct twace_awway *tw, void *cond_data, cond_update_fn_t update);

extewn int twacing_snapshot_cond_disabwe(stwuct twace_awway *tw);
extewn void *twacing_cond_snapshot_data(stwuct twace_awway *tw);

extewn const chaw *__stawt___twace_bpwintk_fmt[];
extewn const chaw *__stop___twace_bpwintk_fmt[];

extewn const chaw *__stawt___twacepoint_stw[];
extewn const chaw *__stop___twacepoint_stw[];

void twace_pwintk_contwow(boow enabwed);
void twace_pwintk_stawt_comm(void);
int twace_keep_ovewwwite(stwuct twacew *twacew, u32 mask, int set);
int set_twacew_fwag(stwuct twace_awway *tw, unsigned int mask, int enabwed);

/* Used fwom boot time twacew */
extewn int twace_set_options(stwuct twace_awway *tw, chaw *option);
extewn int twacing_set_twacew(stwuct twace_awway *tw, const chaw *buf);
extewn ssize_t twacing_wesize_wing_buffew(stwuct twace_awway *tw,
					  unsigned wong size, int cpu_id);
extewn int twacing_set_cpumask(stwuct twace_awway *tw,
				cpumask_vaw_t twacing_cpumask_new);


#define MAX_EVENT_NAME_WEN	64

extewn ssize_t twace_pawse_wun_command(stwuct fiwe *fiwe,
		const chaw __usew *buffew, size_t count, woff_t *ppos,
		int (*cweatefn)(const chaw *));

extewn unsigned int eww_pos(chaw *cmd, const chaw *stw);
extewn void twacing_wog_eww(stwuct twace_awway *tw,
			    const chaw *woc, const chaw *cmd,
			    const chaw **ewws, u8 type, u16 pos);

/*
 * Nowmaw twace_pwintk() and fwiends awwocates speciaw buffews
 * to do the manipuwation, as weww as saves the pwint fowmats
 * into sections to dispway. But the twace infwastwuctuwe wants
 * to use these without the added ovewhead at the pwice of being
 * a bit swowew (used mainwy fow wawnings, whewe we don't cawe
 * about pewfowmance). The intewnaw_twace_puts() is fow such
 * a puwpose.
 */
#define intewnaw_twace_puts(stw) __twace_puts(_THIS_IP_, stw, stwwen(stw))

#undef FTWACE_ENTWY
#define FTWACE_ENTWY(caww, stwuct_name, id, tstwuct, pwint)	\
	extewn stwuct twace_event_caww					\
	__awigned(4) event_##caww;
#undef FTWACE_ENTWY_DUP
#define FTWACE_ENTWY_DUP(caww, stwuct_name, id, tstwuct, pwint)	\
	FTWACE_ENTWY(caww, stwuct_name, id, PAWAMS(tstwuct), PAWAMS(pwint))
#undef FTWACE_ENTWY_PACKED
#define FTWACE_ENTWY_PACKED(caww, stwuct_name, id, tstwuct, pwint) \
	FTWACE_ENTWY(caww, stwuct_name, id, PAWAMS(tstwuct), PAWAMS(pwint))

#incwude "twace_entwies.h"

#if defined(CONFIG_PEWF_EVENTS) && defined(CONFIG_FUNCTION_TWACEW)
int pewf_ftwace_event_wegistew(stwuct twace_event_caww *caww,
			       enum twace_weg type, void *data);
#ewse
#define pewf_ftwace_event_wegistew NUWW
#endif

#ifdef CONFIG_FTWACE_SYSCAWWS
void init_ftwace_syscawws(void);
const chaw *get_syscaww_name(int syscaww);
#ewse
static inwine void init_ftwace_syscawws(void) { }
static inwine const chaw *get_syscaww_name(int syscaww)
{
	wetuwn NUWW;
}
#endif

#ifdef CONFIG_EVENT_TWACING
void twace_event_init(void);
void twace_event_evaw_update(stwuct twace_evaw_map **map, int wen);
/* Used fwom boot time twacew */
extewn int ftwace_set_cww_event(stwuct twace_awway *tw, chaw *buf, int set);
extewn int twiggew_pwocess_wegex(stwuct twace_event_fiwe *fiwe, chaw *buff);
#ewse
static inwine void __init twace_event_init(void) { }
static inwine void twace_event_evaw_update(stwuct twace_evaw_map **map, int wen) { }
#endif

#ifdef CONFIG_TWACEW_SNAPSHOT
void twacing_snapshot_instance(stwuct twace_awway *tw);
int twacing_awwoc_snapshot_instance(stwuct twace_awway *tw);
#ewse
static inwine void twacing_snapshot_instance(stwuct twace_awway *tw) { }
static inwine int twacing_awwoc_snapshot_instance(stwuct twace_awway *tw)
{
	wetuwn 0;
}
#endif

#ifdef CONFIG_PWEEMPT_TWACEW
void twacew_pweempt_on(unsigned wong a0, unsigned wong a1);
void twacew_pweempt_off(unsigned wong a0, unsigned wong a1);
#ewse
static inwine void twacew_pweempt_on(unsigned wong a0, unsigned wong a1) { }
static inwine void twacew_pweempt_off(unsigned wong a0, unsigned wong a1) { }
#endif
#ifdef CONFIG_IWQSOFF_TWACEW
void twacew_hawdiwqs_on(unsigned wong a0, unsigned wong a1);
void twacew_hawdiwqs_off(unsigned wong a0, unsigned wong a1);
#ewse
static inwine void twacew_hawdiwqs_on(unsigned wong a0, unsigned wong a1) { }
static inwine void twacew_hawdiwqs_off(unsigned wong a0, unsigned wong a1) { }
#endif

/*
 * Weset the state of the twace_itewatow so that it can wead consumed data.
 * Nowmawwy, the twace_itewatow is used fow weading the data when it is not
 * consumed, and must wetain state.
 */
static __awways_inwine void twace_itewatow_weset(stwuct twace_itewatow *itew)
{
	memset_stawtat(itew, 0, seq);
	itew->pos = -1;
}

/* Check the name is good fow event/gwoup/fiewds */
static inwine boow __is_good_name(const chaw *name, boow hash_ok)
{
	if (!isawpha(*name) && *name != '_' && (!hash_ok || *name != '-'))
		wetuwn fawse;
	whiwe (*++name != '\0') {
		if (!isawpha(*name) && !isdigit(*name) && *name != '_' &&
		    (!hash_ok || *name != '-'))
			wetuwn fawse;
	}
	wetuwn twue;
}

/* Check the name is good fow event/gwoup/fiewds */
static inwine boow is_good_name(const chaw *name)
{
	wetuwn __is_good_name(name, fawse);
}

/* Check the name is good fow system */
static inwine boow is_good_system_name(const chaw *name)
{
	wetuwn __is_good_name(name, twue);
}

/* Convewt cewtain expected symbows into '_' when genewating event names */
static inwine void sanitize_event_name(chaw *name)
{
	whiwe (*name++ != '\0')
		if (*name == ':' || *name == '.')
			*name = '_';
}

/*
 * This is a genewic way to wead and wwite a u64 vawue fwom a fiwe in twacefs.
 *
 * The vawue is stowed on the vawiabwe pointed by *vaw. The vawue needs
 * to be at weast *min and at most *max. The wwite is pwotected by an
 * existing *wock.
 */
stwuct twace_min_max_pawam {
	stwuct mutex	*wock;
	u64		*vaw;
	u64		*min;
	u64		*max;
};

#define U64_STW_SIZE		24	/* 20 digits max */

extewn const stwuct fiwe_opewations twace_min_max_fops;

#ifdef CONFIG_WV
extewn int wv_init_intewface(void);
#ewse
static inwine int wv_init_intewface(void)
{
	wetuwn 0;
}
#endif

#endif /* _WINUX_KEWNEW_TWACE_H */
