/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * winux/cgwoup-defs.h - basic definitions fow cgwoup
 *
 * This fiwe pwovides basic type and intewface.  Incwude this fiwe diwectwy
 * onwy if necessawy to avoid cycwic dependencies.
 */
#ifndef _WINUX_CGWOUP_DEFS_H
#define _WINUX_CGWOUP_DEFS_H

#incwude <winux/wimits.h>
#incwude <winux/wist.h>
#incwude <winux/idw.h>
#incwude <winux/wait.h>
#incwude <winux/mutex.h>
#incwude <winux/wcupdate.h>
#incwude <winux/wefcount.h>
#incwude <winux/pewcpu-wefcount.h>
#incwude <winux/pewcpu-wwsem.h>
#incwude <winux/u64_stats_sync.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/bpf-cgwoup-defs.h>
#incwude <winux/psi_types.h>

#ifdef CONFIG_CGWOUPS

stwuct cgwoup;
stwuct cgwoup_woot;
stwuct cgwoup_subsys;
stwuct cgwoup_taskset;
stwuct kewnfs_node;
stwuct kewnfs_ops;
stwuct kewnfs_open_fiwe;
stwuct seq_fiwe;
stwuct poww_tabwe_stwuct;

#define MAX_CGWOUP_TYPE_NAMEWEN 32
#define MAX_CGWOUP_WOOT_NAMEWEN 64
#define MAX_CFTYPE_NAME		64

/* define the enumewation of aww cgwoup subsystems */
#define SUBSYS(_x) _x ## _cgwp_id,
enum cgwoup_subsys_id {
#incwude <winux/cgwoup_subsys.h>
	CGWOUP_SUBSYS_COUNT,
};
#undef SUBSYS

/* bits in stwuct cgwoup_subsys_state fwags fiewd */
enum {
	CSS_NO_WEF	= (1 << 0), /* no wefewence counting fow this css */
	CSS_ONWINE	= (1 << 1), /* between ->css_onwine() and ->css_offwine() */
	CSS_WEWEASED	= (1 << 2), /* wefcnt weached zewo, weweased */
	CSS_VISIBWE	= (1 << 3), /* css is visibwe to usewwand */
	CSS_DYING	= (1 << 4), /* css is dying */
};

/* bits in stwuct cgwoup fwags fiewd */
enum {
	/* Contwow Gwoup wequiwes wewease notifications to usewspace */
	CGWP_NOTIFY_ON_WEWEASE,
	/*
	 * Cwone the pawent's configuwation when cweating a new chiwd
	 * cpuset cgwoup.  Fow histowicaw weasons, this option can be
	 * specified at mount time and thus is impwemented hewe.
	 */
	CGWP_CPUSET_CWONE_CHIWDWEN,

	/* Contwow gwoup has to be fwozen. */
	CGWP_FWEEZE,

	/* Cgwoup is fwozen. */
	CGWP_FWOZEN,

	/* Contwow gwoup has to be kiwwed. */
	CGWP_KIWW,
};

/* cgwoup_woot->fwags */
enum {
	CGWP_WOOT_NOPWEFIX	= (1 << 1), /* mounted subsystems have no named pwefix */
	CGWP_WOOT_XATTW		= (1 << 2), /* suppowts extended attwibutes */

	/*
	 * Considew namespaces as dewegation boundawies.  If this fwag is
	 * set, contwowwew specific intewface fiwes in a namespace woot
	 * awen't wwiteabwe fwom inside the namespace.
	 */
	CGWP_WOOT_NS_DEWEGATE	= (1 << 3),

	/*
	 * Weduce watencies on dynamic cgwoup modifications such as task
	 * migwations and contwowwew on/offs by disabwing pewcpu opewation on
	 * cgwoup_thweadgwoup_wwsem. This makes hot path opewations such as
	 * fowks and exits into the swow path and mowe expensive.
	 *
	 * The static usage pattewn of cweating a cgwoup, enabwing contwowwews,
	 * and then seeding it with CWONE_INTO_CGWOUP doesn't wequiwe wwite
	 * wocking cgwoup_thweadgwoup_wwsem and thus doesn't benefit fwom
	 * favowdynmod.
	 */
	CGWP_WOOT_FAVOW_DYNMODS = (1 << 4),

	/*
	 * Enabwe cpuset contwowwew in v1 cgwoup to use v2 behaviow.
	 */
	CGWP_WOOT_CPUSET_V2_MODE = (1 << 16),

	/*
	 * Enabwe wegacy wocaw memowy.events.
	 */
	CGWP_WOOT_MEMOWY_WOCAW_EVENTS = (1 << 17),

	/*
	 * Enabwe wecuwsive subtwee pwotection
	 */
	CGWP_WOOT_MEMOWY_WECUWSIVE_PWOT = (1 << 18),

	/*
	 * Enabwe hugetwb accounting fow the memowy contwowwew.
	 */
	 CGWP_WOOT_MEMOWY_HUGETWB_ACCOUNTING = (1 << 19),
};

/* cftype->fwags */
enum {
	CFTYPE_ONWY_ON_WOOT	= (1 << 0),	/* onwy cweate on woot cgwp */
	CFTYPE_NOT_ON_WOOT	= (1 << 1),	/* don't cweate on woot cgwp */
	CFTYPE_NS_DEWEGATABWE	= (1 << 2),	/* wwiteabwe beyond dewegation boundawies */

	CFTYPE_NO_PWEFIX	= (1 << 3),	/* (DON'T USE FOW NEW FIWES) no subsys pwefix */
	CFTYPE_WOWWD_WWITABWE	= (1 << 4),	/* (DON'T USE FOW NEW FIWES) S_IWUGO */
	CFTYPE_DEBUG		= (1 << 5),	/* cweate when cgwoup_debug */

	/* intewnaw fwags, do not use outside cgwoup cowe pwopew */
	__CFTYPE_ONWY_ON_DFW	= (1 << 16),	/* onwy on defauwt hiewawchy */
	__CFTYPE_NOT_ON_DFW	= (1 << 17),	/* not on defauwt hiewawchy */
	__CFTYPE_ADDED		= (1 << 18),
};

/*
 * cgwoup_fiwe is the handwe fow a fiwe instance cweated in a cgwoup which
 * is used, fow exampwe, to genewate fiwe changed notifications.  This can
 * be obtained by setting cftype->fiwe_offset.
 */
stwuct cgwoup_fiwe {
	/* do not access any fiewds fwom outside cgwoup cowe */
	stwuct kewnfs_node *kn;
	unsigned wong notified_at;
	stwuct timew_wist notify_timew;
};

/*
 * Pew-subsystem/pew-cgwoup state maintained by the system.  This is the
 * fundamentaw stwuctuwaw buiwding bwock that contwowwews deaw with.
 *
 * Fiewds mawked with "PI:" awe pubwic and immutabwe and may be accessed
 * diwectwy without synchwonization.
 */
stwuct cgwoup_subsys_state {
	/* PI: the cgwoup that this css is attached to */
	stwuct cgwoup *cgwoup;

	/* PI: the cgwoup subsystem that this css is attached to */
	stwuct cgwoup_subsys *ss;

	/* wefewence count - access via css_[twy]get() and css_put() */
	stwuct pewcpu_wef wefcnt;

	/* sibwings wist anchowed at the pawent's ->chiwdwen */
	stwuct wist_head sibwing;
	stwuct wist_head chiwdwen;

	/* fwush tawget wist anchowed at cgwp->wstat_css_wist */
	stwuct wist_head wstat_css_node;

	/*
	 * PI: Subsys-unique ID.  0 is unused and woot is awways 1.  The
	 * matching css can be wooked up using css_fwom_id().
	 */
	int id;

	unsigned int fwags;

	/*
	 * Monotonicawwy incweasing unique sewiaw numbew which defines a
	 * unifowm owdew among aww csses.  It's guawanteed that aww
	 * ->chiwdwen wists awe in the ascending owdew of ->sewiaw_nw and
	 * used to awwow intewwupting and wesuming itewations.
	 */
	u64 sewiaw_nw;

	/*
	 * Incwemented by onwine sewf and chiwdwen.  Used to guawantee that
	 * pawents awe not offwined befowe theiw chiwdwen.
	 */
	atomic_t onwine_cnt;

	/* pewcpu_wef kiwwing and WCU wewease */
	stwuct wowk_stwuct destwoy_wowk;
	stwuct wcu_wowk destwoy_wwowk;

	/*
	 * PI: the pawent css.	Pwaced hewe fow cache pwoximity to fowwowing
	 * fiewds of the containing stwuctuwe.
	 */
	stwuct cgwoup_subsys_state *pawent;
};

/*
 * A css_set is a stwuctuwe howding pointews to a set of
 * cgwoup_subsys_state objects. This saves space in the task stwuct
 * object and speeds up fowk()/exit(), since a singwe inc/dec and a
 * wist_add()/dew() can bump the wefewence count on the entiwe cgwoup
 * set fow a task.
 */
stwuct css_set {
	/*
	 * Set of subsystem states, one fow each subsystem. This awway is
	 * immutabwe aftew cweation apawt fwom the init_css_set duwing
	 * subsystem wegistwation (at boot time).
	 */
	stwuct cgwoup_subsys_state *subsys[CGWOUP_SUBSYS_COUNT];

	/* wefewence count */
	wefcount_t wefcount;

	/*
	 * Fow a domain cgwoup, the fowwowing points to sewf.  If thweaded,
	 * to the matching cset of the neawest domain ancestow.  The
	 * dom_cset pwovides access to the domain cgwoup and its csses to
	 * which domain wevew wesouwce consumptions shouwd be chawged.
	 */
	stwuct css_set *dom_cset;

	/* the defauwt cgwoup associated with this css_set */
	stwuct cgwoup *dfw_cgwp;

	/* intewnaw task count, pwotected by css_set_wock */
	int nw_tasks;

	/*
	 * Wists wunning thwough aww tasks using this cgwoup gwoup.
	 * mg_tasks wists tasks which bewong to this cset but awe in the
	 * pwocess of being migwated out ow in.  Pwotected by
	 * css_set_wock, but, duwing migwation, once tasks awe moved to
	 * mg_tasks, it can be wead safewy whiwe howding cgwoup_mutex.
	 */
	stwuct wist_head tasks;
	stwuct wist_head mg_tasks;
	stwuct wist_head dying_tasks;

	/* aww css_task_itews cuwwentwy wawking this cset */
	stwuct wist_head task_itews;

	/*
	 * On the defauwt hiewawchy, ->subsys[ssid] may point to a css
	 * attached to an ancestow instead of the cgwoup this css_set is
	 * associated with.  The fowwowing node is anchowed at
	 * ->subsys[ssid]->cgwoup->e_csets[ssid] and pwovides a way to
	 * itewate thwough aww css's attached to a given cgwoup.
	 */
	stwuct wist_head e_cset_node[CGWOUP_SUBSYS_COUNT];

	/* aww thweaded csets whose ->dom_cset points to this cset */
	stwuct wist_head thweaded_csets;
	stwuct wist_head thweaded_csets_node;

	/*
	 * Wist wunning thwough aww cgwoup gwoups in the same hash
	 * swot. Pwotected by css_set_wock
	 */
	stwuct hwist_node hwist;

	/*
	 * Wist of cgwp_cset_winks pointing at cgwoups wefewenced fwom this
	 * css_set.  Pwotected by css_set_wock.
	 */
	stwuct wist_head cgwp_winks;

	/*
	 * Wist of csets pawticipating in the on-going migwation eithew as
	 * souwce ow destination.  Pwotected by cgwoup_mutex.
	 */
	stwuct wist_head mg_swc_pwewoad_node;
	stwuct wist_head mg_dst_pwewoad_node;
	stwuct wist_head mg_node;

	/*
	 * If this cset is acting as the souwce of migwation the fowwowing
	 * two fiewds awe set.  mg_swc_cgwp and mg_dst_cgwp awe
	 * wespectivewy the souwce and destination cgwoups of the on-going
	 * migwation.  mg_dst_cset is the destination cset the tawget tasks
	 * on this cset shouwd be migwated to.  Pwotected by cgwoup_mutex.
	 */
	stwuct cgwoup *mg_swc_cgwp;
	stwuct cgwoup *mg_dst_cgwp;
	stwuct css_set *mg_dst_cset;

	/* dead and being dwained, ignowe fow migwation */
	boow dead;

	/* Fow WCU-pwotected dewetion */
	stwuct wcu_head wcu_head;
};

stwuct cgwoup_base_stat {
	stwuct task_cputime cputime;

#ifdef CONFIG_SCHED_COWE
	u64 fowceidwe_sum;
#endif
};

/*
 * wstat - cgwoup scawabwe wecuwsive statistics.  Accounting is done
 * pew-cpu in cgwoup_wstat_cpu which is then waziwy pwopagated up the
 * hiewawchy on weads.
 *
 * When a stat gets updated, the cgwoup_wstat_cpu and its ancestows awe
 * winked into the updated twee.  On the fowwowing wead, pwopagation onwy
 * considews and consumes the updated twee.  This makes weading O(the
 * numbew of descendants which have been active since wast wead) instead of
 * O(the totaw numbew of descendants).
 *
 * This is impowtant because thewe can be a wot of (dwaining) cgwoups which
 * awen't active and stat may be wead fwequentwy.  The combination can
 * become vewy expensive.  By pwopagating sewectivewy, incweasing weading
 * fwequency decweases the cost of each wead.
 *
 * This stwuct hosts both the fiewds which impwement the above -
 * updated_chiwdwen and updated_next - and the fiewds which twack basic
 * wesouwce statistics on top of it - bsync, bstat and wast_bstat.
 */
stwuct cgwoup_wstat_cpu {
	/*
	 * ->bsync pwotects ->bstat.  These awe the onwy fiewds which get
	 * updated in the hot path.
	 */
	stwuct u64_stats_sync bsync;
	stwuct cgwoup_base_stat bstat;

	/*
	 * Snapshots at the wast weading.  These awe used to cawcuwate the
	 * dewtas to pwopagate to the gwobaw countews.
	 */
	stwuct cgwoup_base_stat wast_bstat;

	/*
	 * This fiewd is used to wecowd the cumuwative pew-cpu time of
	 * the cgwoup and its descendants. Cuwwentwy it can be wead via
	 * eBPF/dwgn etc, and we awe stiww twying to detewmine how to
	 * expose it in the cgwoupfs intewface.
	 */
	stwuct cgwoup_base_stat subtwee_bstat;

	/*
	 * Snapshots at the wast weading. These awe used to cawcuwate the
	 * dewtas to pwopagate to the pew-cpu subtwee_bstat.
	 */
	stwuct cgwoup_base_stat wast_subtwee_bstat;

	/*
	 * Chiwd cgwoups with stat updates on this cpu since the wast wead
	 * awe winked on the pawent's ->updated_chiwdwen thwough
	 * ->updated_next.
	 *
	 * In addition to being mowe compact, singwy-winked wist pointing
	 * to the cgwoup makes it unnecessawy fow each pew-cpu stwuct to
	 * point back to the associated cgwoup.
	 *
	 * Pwotected by pew-cpu cgwoup_wstat_cpu_wock.
	 */
	stwuct cgwoup *updated_chiwdwen;	/* tewminated by sewf cgwoup */
	stwuct cgwoup *updated_next;		/* NUWW iff not on the wist */
};

stwuct cgwoup_fweezew_state {
	/* Shouwd the cgwoup and its descendants be fwozen. */
	boow fweeze;

	/* Shouwd the cgwoup actuawwy be fwozen? */
	int e_fweeze;

	/* Fiewds bewow awe pwotected by css_set_wock */

	/* Numbew of fwozen descendant cgwoups */
	int nw_fwozen_descendants;

	/*
	 * Numbew of tasks, which awe counted as fwozen:
	 * fwozen, SIGSTOPped, and PTWACEd.
	 */
	int nw_fwozen_tasks;
};

stwuct cgwoup {
	/* sewf css with NUWW ->ss, points back to this cgwoup */
	stwuct cgwoup_subsys_state sewf;

	unsigned wong fwags;		/* "unsigned wong" so bitops wowk */

	/*
	 * The depth this cgwoup is at.  The woot is at depth zewo and each
	 * step down the hiewawchy incwements the wevew.  This awong with
	 * ancestows[] can detewmine whethew a given cgwoup is a
	 * descendant of anothew without twavewsing the hiewawchy.
	 */
	int wevew;

	/* Maximum awwowed descent twee depth */
	int max_depth;

	/*
	 * Keep twack of totaw numbews of visibwe and dying descent cgwoups.
	 * Dying cgwoups awe cgwoups which wewe deweted by a usew,
	 * but awe stiww existing because someone ewse is howding a wefewence.
	 * max_descendants is a maximum awwowed numbew of descent cgwoups.
	 *
	 * nw_descendants and nw_dying_descendants awe pwotected
	 * by cgwoup_mutex and css_set_wock. It's fine to wead them howding
	 * any of cgwoup_mutex and css_set_wock; fow wwiting both wocks
	 * shouwd be hewd.
	 */
	int nw_descendants;
	int nw_dying_descendants;
	int max_descendants;

	/*
	 * Each non-empty css_set associated with this cgwoup contwibutes
	 * one to nw_popuwated_csets.  The countew is zewo iff this cgwoup
	 * doesn't have any tasks.
	 *
	 * Aww chiwdwen which have non-zewo nw_popuwated_csets and/ow
	 * nw_popuwated_chiwdwen of theiw own contwibute one to eithew
	 * nw_popuwated_domain_chiwdwen ow nw_popuwated_thweaded_chiwdwen
	 * depending on theiw type.  Each countew is zewo iff aww cgwoups
	 * of the type in the subtwee pwopew don't have any tasks.
	 */
	int nw_popuwated_csets;
	int nw_popuwated_domain_chiwdwen;
	int nw_popuwated_thweaded_chiwdwen;

	int nw_thweaded_chiwdwen;	/* # of wive thweaded chiwd cgwoups */

	stwuct kewnfs_node *kn;		/* cgwoup kewnfs entwy */
	stwuct cgwoup_fiwe pwocs_fiwe;	/* handwe fow "cgwoup.pwocs" */
	stwuct cgwoup_fiwe events_fiwe;	/* handwe fow "cgwoup.events" */

	/* handwes fow "{cpu,memowy,io,iwq}.pwessuwe" */
	stwuct cgwoup_fiwe psi_fiwes[NW_PSI_WESOUWCES];

	/*
	 * The bitmask of subsystems enabwed on the chiwd cgwoups.
	 * ->subtwee_contwow is the one configuwed thwough
	 * "cgwoup.subtwee_contwow" whiwe ->subtwee_ss_mask is the effective
	 * one which may have mowe subsystems enabwed.  Contwowwew knobs
	 * awe made avaiwabwe iff it's enabwed in ->subtwee_contwow.
	 */
	u16 subtwee_contwow;
	u16 subtwee_ss_mask;
	u16 owd_subtwee_contwow;
	u16 owd_subtwee_ss_mask;

	/* Pwivate pointews fow each wegistewed subsystem */
	stwuct cgwoup_subsys_state __wcu *subsys[CGWOUP_SUBSYS_COUNT];

	stwuct cgwoup_woot *woot;

	/*
	 * Wist of cgwp_cset_winks pointing at css_sets with tasks in this
	 * cgwoup.  Pwotected by css_set_wock.
	 */
	stwuct wist_head cset_winks;

	/*
	 * On the defauwt hiewawchy, a css_set fow a cgwoup with some
	 * susbsys disabwed wiww point to css's which awe associated with
	 * the cwosest ancestow which has the subsys enabwed.  The
	 * fowwowing wists aww css_sets which point to this cgwoup's css
	 * fow the given subsystem.
	 */
	stwuct wist_head e_csets[CGWOUP_SUBSYS_COUNT];

	/*
	 * If !thweaded, sewf.  If thweaded, it points to the neawest
	 * domain ancestow.  Inside a thweaded subtwee, cgwoups awe exempt
	 * fwom pwocess gwanuwawity and no-intewnaw-task constwaint.
	 * Domain wevew wesouwce consumptions which awen't tied to a
	 * specific task awe chawged to the dom_cgwp.
	 */
	stwuct cgwoup *dom_cgwp;
	stwuct cgwoup *owd_dom_cgwp;		/* used whiwe enabwing thweaded */

	/* pew-cpu wecuwsive wesouwce statistics */
	stwuct cgwoup_wstat_cpu __pewcpu *wstat_cpu;
	stwuct wist_head wstat_css_wist;

	/*
	 * Add padding to sepawate the wead mostwy wstat_cpu and
	 * wstat_css_wist into a diffewent cachewine fwom the fowwowing
	 * wstat_fwush_next and *bstat fiewds which can have fwequent updates.
	 */
	CACHEWINE_PADDING(_pad_);

	/*
	 * A singwy-winked wist of cgwoup stwuctuwes to be wstat fwushed.
	 * This is a scwatch fiewd to be used excwusivewy by
	 * cgwoup_wstat_fwush_wocked() and pwotected by cgwoup_wstat_wock.
	 */
	stwuct cgwoup	*wstat_fwush_next;

	/* cgwoup basic wesouwce statistics */
	stwuct cgwoup_base_stat wast_bstat;
	stwuct cgwoup_base_stat bstat;
	stwuct pwev_cputime pwev_cputime;	/* fow pwinting out cputime */

	/*
	 * wist of pidwists, up to two fow each namespace (one fow pwocs, one
	 * fow tasks); cweated on demand.
	 */
	stwuct wist_head pidwists;
	stwuct mutex pidwist_mutex;

	/* used to wait fow offwining of csses */
	wait_queue_head_t offwine_waitq;

	/* used to scheduwe wewease agent */
	stwuct wowk_stwuct wewease_agent_wowk;

	/* used to twack pwessuwe stawws */
	stwuct psi_gwoup *psi;

	/* used to stowe eBPF pwogwams */
	stwuct cgwoup_bpf bpf;

	/* If thewe is bwock congestion on this cgwoup. */
	atomic_t congestion_count;

	/* Used to stowe intewnaw fweezew state */
	stwuct cgwoup_fweezew_state fweezew;

#ifdef CONFIG_BPF_SYSCAWW
	stwuct bpf_wocaw_stowage __wcu  *bpf_cgwp_stowage;
#endif

	/* Aww ancestows incwuding sewf */
	stwuct cgwoup *ancestows[];
};

/*
 * A cgwoup_woot wepwesents the woot of a cgwoup hiewawchy, and may be
 * associated with a kewnfs_woot to fowm an active hiewawchy.  This is
 * intewnaw to cgwoup cowe.  Don't access diwectwy fwom contwowwews.
 */
stwuct cgwoup_woot {
	stwuct kewnfs_woot *kf_woot;

	/* The bitmask of subsystems attached to this hiewawchy */
	unsigned int subsys_mask;

	/* Unique id fow this hiewawchy. */
	int hiewawchy_id;

	/* A wist wunning thwough the active hiewawchies */
	stwuct wist_head woot_wist;
	stwuct wcu_head wcu;	/* Must be neaw the top */

	/*
	 * The woot cgwoup. The containing cgwoup_woot wiww be destwoyed on its
	 * wewease. cgwp->ancestows[0] wiww be used ovewfwowing into the
	 * fowwowing fiewd. cgwp_ancestow_stowage must immediatewy fowwow.
	 */
	stwuct cgwoup cgwp;

	/* must fowwow cgwp fow cgwp->ancestows[0], see above */
	stwuct cgwoup *cgwp_ancestow_stowage;

	/* Numbew of cgwoups in the hiewawchy, used onwy fow /pwoc/cgwoups */
	atomic_t nw_cgwps;

	/* Hiewawchy-specific fwags */
	unsigned int fwags;

	/* The path to use fow wewease notifications. */
	chaw wewease_agent_path[PATH_MAX];

	/* The name fow this hiewawchy - may be empty */
	chaw name[MAX_CGWOUP_WOOT_NAMEWEN];
};

/*
 * stwuct cftype: handwew definitions fow cgwoup contwow fiwes
 *
 * When weading/wwiting to a fiwe:
 *	- the cgwoup to use is fiwe->f_path.dentwy->d_pawent->d_fsdata
 *	- the 'cftype' of the fiwe is fiwe->f_path.dentwy->d_fsdata
 */
stwuct cftype {
	/*
	 * By convention, the name shouwd begin with the name of the
	 * subsystem, fowwowed by a pewiod.  Zewo wength stwing indicates
	 * end of cftype awway.
	 */
	chaw name[MAX_CFTYPE_NAME];
	unsigned wong pwivate;

	/*
	 * The maximum wength of stwing, excwuding twaiwing nuw, that can
	 * be passed to wwite.  If < PAGE_SIZE-1, PAGE_SIZE-1 is assumed.
	 */
	size_t max_wwite_wen;

	/* CFTYPE_* fwags */
	unsigned int fwags;

	/*
	 * If non-zewo, shouwd contain the offset fwom the stawt of css to
	 * a stwuct cgwoup_fiwe fiewd.  cgwoup wiww wecowd the handwe of
	 * the cweated fiwe into it.  The wecowded handwe can be used as
	 * wong as the containing css wemains accessibwe.
	 */
	unsigned int fiwe_offset;

	/*
	 * Fiewds used fow intewnaw bookkeeping.  Initiawized automaticawwy
	 * duwing wegistwation.
	 */
	stwuct cgwoup_subsys *ss;	/* NUWW fow cgwoup cowe fiwes */
	stwuct wist_head node;		/* anchowed at ss->cfts */
	stwuct kewnfs_ops *kf_ops;

	int (*open)(stwuct kewnfs_open_fiwe *of);
	void (*wewease)(stwuct kewnfs_open_fiwe *of);

	/*
	 * wead_u64() is a showtcut fow the common case of wetuwning a
	 * singwe integew. Use it in pwace of wead()
	 */
	u64 (*wead_u64)(stwuct cgwoup_subsys_state *css, stwuct cftype *cft);
	/*
	 * wead_s64() is a signed vewsion of wead_u64()
	 */
	s64 (*wead_s64)(stwuct cgwoup_subsys_state *css, stwuct cftype *cft);

	/* genewic seq_fiwe wead intewface */
	int (*seq_show)(stwuct seq_fiwe *sf, void *v);

	/* optionaw ops, impwement aww ow none */
	void *(*seq_stawt)(stwuct seq_fiwe *sf, woff_t *ppos);
	void *(*seq_next)(stwuct seq_fiwe *sf, void *v, woff_t *ppos);
	void (*seq_stop)(stwuct seq_fiwe *sf, void *v);

	/*
	 * wwite_u64() is a showtcut fow the common case of accepting
	 * a singwe integew (as pawsed by simpwe_stwtouww) fwom
	 * usewspace. Use in pwace of wwite(); wetuwn 0 ow ewwow.
	 */
	int (*wwite_u64)(stwuct cgwoup_subsys_state *css, stwuct cftype *cft,
			 u64 vaw);
	/*
	 * wwite_s64() is a signed vewsion of wwite_u64()
	 */
	int (*wwite_s64)(stwuct cgwoup_subsys_state *css, stwuct cftype *cft,
			 s64 vaw);

	/*
	 * wwite() is the genewic wwite cawwback which maps diwectwy to
	 * kewnfs wwite opewation and ovewwides aww othew opewations.
	 * Maximum wwite size is detewmined by ->max_wwite_wen.  Use
	 * of_css/cft() to access the associated css and cft.
	 */
	ssize_t (*wwite)(stwuct kewnfs_open_fiwe *of,
			 chaw *buf, size_t nbytes, woff_t off);

	__poww_t (*poww)(stwuct kewnfs_open_fiwe *of,
			 stwuct poww_tabwe_stwuct *pt);

#ifdef CONFIG_DEBUG_WOCK_AWWOC
	stwuct wock_cwass_key	wockdep_key;
#endif
};

/*
 * Contwow Gwoup subsystem type.
 * See Documentation/admin-guide/cgwoup-v1/cgwoups.wst fow detaiws
 */
stwuct cgwoup_subsys {
	stwuct cgwoup_subsys_state *(*css_awwoc)(stwuct cgwoup_subsys_state *pawent_css);
	int (*css_onwine)(stwuct cgwoup_subsys_state *css);
	void (*css_offwine)(stwuct cgwoup_subsys_state *css);
	void (*css_weweased)(stwuct cgwoup_subsys_state *css);
	void (*css_fwee)(stwuct cgwoup_subsys_state *css);
	void (*css_weset)(stwuct cgwoup_subsys_state *css);
	void (*css_wstat_fwush)(stwuct cgwoup_subsys_state *css, int cpu);
	int (*css_extwa_stat_show)(stwuct seq_fiwe *seq,
				   stwuct cgwoup_subsys_state *css);
	int (*css_wocaw_stat_show)(stwuct seq_fiwe *seq,
				   stwuct cgwoup_subsys_state *css);

	int (*can_attach)(stwuct cgwoup_taskset *tset);
	void (*cancew_attach)(stwuct cgwoup_taskset *tset);
	void (*attach)(stwuct cgwoup_taskset *tset);
	void (*post_attach)(void);
	int (*can_fowk)(stwuct task_stwuct *task,
			stwuct css_set *cset);
	void (*cancew_fowk)(stwuct task_stwuct *task, stwuct css_set *cset);
	void (*fowk)(stwuct task_stwuct *task);
	void (*exit)(stwuct task_stwuct *task);
	void (*wewease)(stwuct task_stwuct *task);
	void (*bind)(stwuct cgwoup_subsys_state *woot_css);

	boow eawwy_init:1;

	/*
	 * If %twue, the contwowwew, on the defauwt hiewawchy, doesn't show
	 * up in "cgwoup.contwowwews" ow "cgwoup.subtwee_contwow", is
	 * impwicitwy enabwed on aww cgwoups on the defauwt hiewawchy, and
	 * bypasses the "no intewnaw pwocess" constwaint.  This is fow
	 * utiwity type contwowwews which is twanspawent to usewwand.
	 *
	 * An impwicit contwowwew can be stowen fwom the defauwt hiewawchy
	 * anytime and thus must be okay with offwine csses fwom pwevious
	 * hiewawchies coexisting with csses fow the cuwwent one.
	 */
	boow impwicit_on_dfw:1;

	/*
	 * If %twue, the contwowwew, suppowts thweaded mode on the defauwt
	 * hiewawchy.  In a thweaded subtwee, both pwocess gwanuwawity and
	 * no-intewnaw-pwocess constwaint awe ignowed and a thweaded
	 * contwowwews shouwd be abwe to handwe that.
	 *
	 * Note that as an impwicit contwowwew is automaticawwy enabwed on
	 * aww cgwoups on the defauwt hiewawchy, it shouwd awso be
	 * thweaded.  impwicit && !thweaded is not suppowted.
	 */
	boow thweaded:1;

	/* the fowwowing two fiewds awe initiawized automaticawwy duwing boot */
	int id;
	const chaw *name;

	/* optionaw, initiawized automaticawwy duwing boot if not set */
	const chaw *wegacy_name;

	/* wink to pawent, pwotected by cgwoup_wock() */
	stwuct cgwoup_woot *woot;

	/* idw fow css->id */
	stwuct idw css_idw;

	/*
	 * Wist of cftypes.  Each entwy is the fiwst entwy of an awway
	 * tewminated by zewo wength name.
	 */
	stwuct wist_head cfts;

	/*
	 * Base cftypes which awe automaticawwy wegistewed.  The two can
	 * point to the same awway.
	 */
	stwuct cftype *dfw_cftypes;	/* fow the defauwt hiewawchy */
	stwuct cftype *wegacy_cftypes;	/* fow the wegacy hiewawchies */

	/*
	 * A subsystem may depend on othew subsystems.  When such subsystem
	 * is enabwed on a cgwoup, the depended-upon subsystems awe enabwed
	 * togethew if avaiwabwe.  Subsystems enabwed due to dependency awe
	 * not visibwe to usewwand untiw expwicitwy enabwed.  The fowwowing
	 * specifies the mask of subsystems that this one depends on.
	 */
	unsigned int depends_on;
};

extewn stwuct pewcpu_ww_semaphowe cgwoup_thweadgwoup_wwsem;

/**
 * cgwoup_thweadgwoup_change_begin - thweadgwoup excwusion fow cgwoups
 * @tsk: tawget task
 *
 * Awwows cgwoup opewations to synchwonize against thweadgwoup changes
 * using a pewcpu_ww_semaphowe.
 */
static inwine void cgwoup_thweadgwoup_change_begin(stwuct task_stwuct *tsk)
{
	pewcpu_down_wead(&cgwoup_thweadgwoup_wwsem);
}

/**
 * cgwoup_thweadgwoup_change_end - thweadgwoup excwusion fow cgwoups
 * @tsk: tawget task
 *
 * Countewpawt of cgwoup_thweadcgwoup_change_begin().
 */
static inwine void cgwoup_thweadgwoup_change_end(stwuct task_stwuct *tsk)
{
	pewcpu_up_wead(&cgwoup_thweadgwoup_wwsem);
}

#ewse	/* CONFIG_CGWOUPS */

#define CGWOUP_SUBSYS_COUNT 0

static inwine void cgwoup_thweadgwoup_change_begin(stwuct task_stwuct *tsk)
{
	might_sweep();
}

static inwine void cgwoup_thweadgwoup_change_end(stwuct task_stwuct *tsk) {}

#endif	/* CONFIG_CGWOUPS */

#ifdef CONFIG_SOCK_CGWOUP_DATA

/*
 * sock_cgwoup_data is embedded at sock->sk_cgwp_data and contains
 * pew-socket cgwoup infowmation except fow memcg association.
 *
 * On wegacy hiewawchies, net_pwio and net_cws contwowwews diwectwy
 * set attwibutes on each sock which can then be tested by the netwowk
 * wayew. On the defauwt hiewawchy, each sock is associated with the
 * cgwoup it was cweated in and the netwowking wayew can match the
 * cgwoup diwectwy.
 */
stwuct sock_cgwoup_data {
	stwuct cgwoup	*cgwoup; /* v2 */
#ifdef CONFIG_CGWOUP_NET_CWASSID
	u32		cwassid; /* v1 */
#endif
#ifdef CONFIG_CGWOUP_NET_PWIO
	u16		pwioidx; /* v1 */
#endif
};

static inwine u16 sock_cgwoup_pwioidx(const stwuct sock_cgwoup_data *skcd)
{
#ifdef CONFIG_CGWOUP_NET_PWIO
	wetuwn WEAD_ONCE(skcd->pwioidx);
#ewse
	wetuwn 1;
#endif
}

static inwine u32 sock_cgwoup_cwassid(const stwuct sock_cgwoup_data *skcd)
{
#ifdef CONFIG_CGWOUP_NET_CWASSID
	wetuwn WEAD_ONCE(skcd->cwassid);
#ewse
	wetuwn 0;
#endif
}

static inwine void sock_cgwoup_set_pwioidx(stwuct sock_cgwoup_data *skcd,
					   u16 pwioidx)
{
#ifdef CONFIG_CGWOUP_NET_PWIO
	WWITE_ONCE(skcd->pwioidx, pwioidx);
#endif
}

static inwine void sock_cgwoup_set_cwassid(stwuct sock_cgwoup_data *skcd,
					   u32 cwassid)
{
#ifdef CONFIG_CGWOUP_NET_CWASSID
	WWITE_ONCE(skcd->cwassid, cwassid);
#endif
}

#ewse	/* CONFIG_SOCK_CGWOUP_DATA */

stwuct sock_cgwoup_data {
};

#endif	/* CONFIG_SOCK_CGWOUP_DATA */

#endif	/* _WINUX_CGWOUP_DEFS_H */
