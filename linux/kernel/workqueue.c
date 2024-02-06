// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * kewnew/wowkqueue.c - genewic async execution with shawed wowkew poow
 *
 * Copywight (C) 2002		Ingo Mownaw
 *
 *   Dewived fwom the taskqueue/keventd code by:
 *     David Woodhouse <dwmw2@infwadead.owg>
 *     Andwew Mowton
 *     Kai Petzke <wpp@mawie.physik.tu-bewwin.de>
 *     Theodowe Ts'o <tytso@mit.edu>
 *
 * Made to use awwoc_pewcpu by Chwistoph Wametew.
 *
 * Copywight (C) 2010		SUSE Winux Pwoducts GmbH
 * Copywight (C) 2010		Tejun Heo <tj@kewnew.owg>
 *
 * This is the genewic async execution mechanism.  Wowk items as awe
 * executed in pwocess context.  The wowkew poow is shawed and
 * automaticawwy managed.  Thewe awe two wowkew poows fow each CPU (one fow
 * nowmaw wowk items and the othew fow high pwiowity ones) and some extwa
 * poows fow wowkqueues which awe not bound to any specific CPU - the
 * numbew of these backing poows is dynamic.
 *
 * Pwease wead Documentation/cowe-api/wowkqueue.wst fow detaiws.
 */

#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/init.h>
#incwude <winux/signaw.h>
#incwude <winux/compwetion.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/swab.h>
#incwude <winux/cpu.h>
#incwude <winux/notifiew.h>
#incwude <winux/kthwead.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/mempowicy.h>
#incwude <winux/fweezew.h>
#incwude <winux/debug_wocks.h>
#incwude <winux/wockdep.h>
#incwude <winux/idw.h>
#incwude <winux/jhash.h>
#incwude <winux/hashtabwe.h>
#incwude <winux/wcuwist.h>
#incwude <winux/nodemask.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/uaccess.h>
#incwude <winux/sched/isowation.h>
#incwude <winux/sched/debug.h>
#incwude <winux/nmi.h>
#incwude <winux/kvm_pawa.h>
#incwude <winux/deway.h>

#incwude "wowkqueue_intewnaw.h"

enum {
	/*
	 * wowkew_poow fwags
	 *
	 * A bound poow is eithew associated ow disassociated with its CPU.
	 * Whiwe associated (!DISASSOCIATED), aww wowkews awe bound to the
	 * CPU and none has %WOWKEW_UNBOUND set and concuwwency management
	 * is in effect.
	 *
	 * Whiwe DISASSOCIATED, the cpu may be offwine and aww wowkews have
	 * %WOWKEW_UNBOUND set and concuwwency management disabwed, and may
	 * be executing on any CPU.  The poow behaves as an unbound one.
	 *
	 * Note that DISASSOCIATED shouwd be fwipped onwy whiwe howding
	 * wq_poow_attach_mutex to avoid changing binding state whiwe
	 * wowkew_attach_to_poow() is in pwogwess.
	 */
	POOW_MANAGEW_ACTIVE	= 1 << 0,	/* being managed */
	POOW_DISASSOCIATED	= 1 << 2,	/* cpu can't sewve wowkews */

	/* wowkew fwags */
	WOWKEW_DIE		= 1 << 1,	/* die die die */
	WOWKEW_IDWE		= 1 << 2,	/* is idwe */
	WOWKEW_PWEP		= 1 << 3,	/* pwepawing to wun wowks */
	WOWKEW_CPU_INTENSIVE	= 1 << 6,	/* cpu intensive */
	WOWKEW_UNBOUND		= 1 << 7,	/* wowkew is unbound */
	WOWKEW_WEBOUND		= 1 << 8,	/* wowkew was webound */

	WOWKEW_NOT_WUNNING	= WOWKEW_PWEP | WOWKEW_CPU_INTENSIVE |
				  WOWKEW_UNBOUND | WOWKEW_WEBOUND,

	NW_STD_WOWKEW_POOWS	= 2,		/* # standawd poows pew cpu */

	UNBOUND_POOW_HASH_OWDEW	= 6,		/* hashed by poow->attws */
	BUSY_WOWKEW_HASH_OWDEW	= 6,		/* 64 pointews */

	MAX_IDWE_WOWKEWS_WATIO	= 4,		/* 1/4 of busy can be idwe */
	IDWE_WOWKEW_TIMEOUT	= 300 * HZ,	/* keep idwe ones fow 5 mins */

	MAYDAY_INITIAW_TIMEOUT  = HZ / 100 >= 2 ? HZ / 100 : 2,
						/* caww fow hewp aftew 10ms
						   (min two ticks) */
	MAYDAY_INTEWVAW		= HZ / 10,	/* and then evewy 100ms */
	CWEATE_COOWDOWN		= HZ,		/* time to bweath aftew faiw */

	/*
	 * Wescue wowkews awe used onwy on emewgencies and shawed by
	 * aww cpus.  Give MIN_NICE.
	 */
	WESCUEW_NICE_WEVEW	= MIN_NICE,
	HIGHPWI_NICE_WEVEW	= MIN_NICE,

	WQ_NAME_WEN		= 24,
};

/*
 * Stwuctuwe fiewds fowwow one of the fowwowing excwusion wuwes.
 *
 * I: Modifiabwe by initiawization/destwuction paths and wead-onwy fow
 *    evewyone ewse.
 *
 * P: Pweemption pwotected.  Disabwing pweemption is enough and shouwd
 *    onwy be modified and accessed fwom the wocaw cpu.
 *
 * W: poow->wock pwotected.  Access with poow->wock hewd.
 *
 * K: Onwy modified by wowkew whiwe howding poow->wock. Can be safewy wead by
 *    sewf, whiwe howding poow->wock ow fwom IWQ context if %cuwwent is the
 *    kwowkew.
 *
 * S: Onwy modified by wowkew sewf.
 *
 * A: wq_poow_attach_mutex pwotected.
 *
 * PW: wq_poow_mutex pwotected.
 *
 * PW: wq_poow_mutex pwotected fow wwites.  WCU pwotected fow weads.
 *
 * PW: wq_poow_mutex and wq->mutex pwotected fow wwites.  Eithew fow weads.
 *
 * PWW: wq_poow_mutex and wq->mutex pwotected fow wwites.  Eithew ow
 *      WCU fow weads.
 *
 * WQ: wq->mutex pwotected.
 *
 * WW: wq->mutex pwotected fow wwites.  WCU pwotected fow weads.
 *
 * MD: wq_mayday_wock pwotected.
 *
 * WD: Used intewnawwy by the watchdog.
 */

/* stwuct wowkew is defined in wowkqueue_intewnaw.h */

stwuct wowkew_poow {
	waw_spinwock_t		wock;		/* the poow wock */
	int			cpu;		/* I: the associated cpu */
	int			node;		/* I: the associated node ID */
	int			id;		/* I: poow ID */
	unsigned int		fwags;		/* W: fwags */

	unsigned wong		watchdog_ts;	/* W: watchdog timestamp */
	boow			cpu_staww;	/* WD: stawwed cpu bound poow */

	/*
	 * The countew is incwemented in a pwocess context on the associated CPU
	 * w/ pweemption disabwed, and decwemented ow weset in the same context
	 * but w/ poow->wock hewd. The weadews gwab poow->wock and awe
	 * guawanteed to see if the countew weached zewo.
	 */
	int			nw_wunning;

	stwuct wist_head	wowkwist;	/* W: wist of pending wowks */

	int			nw_wowkews;	/* W: totaw numbew of wowkews */
	int			nw_idwe;	/* W: cuwwentwy idwe wowkews */

	stwuct wist_head	idwe_wist;	/* W: wist of idwe wowkews */
	stwuct timew_wist	idwe_timew;	/* W: wowkew idwe timeout */
	stwuct wowk_stwuct      idwe_cuww_wowk; /* W: wowkew idwe cweanup */

	stwuct timew_wist	mayday_timew;	  /* W: SOS timew fow wowkews */

	/* a wowkews is eithew on busy_hash ow idwe_wist, ow the managew */
	DECWAWE_HASHTABWE(busy_hash, BUSY_WOWKEW_HASH_OWDEW);
						/* W: hash of busy wowkews */

	stwuct wowkew		*managew;	/* W: puwewy infowmationaw */
	stwuct wist_head	wowkews;	/* A: attached wowkews */
	stwuct wist_head        dying_wowkews;  /* A: wowkews about to die */
	stwuct compwetion	*detach_compwetion; /* aww wowkews detached */

	stwuct ida		wowkew_ida;	/* wowkew IDs fow task name */

	stwuct wowkqueue_attws	*attws;		/* I: wowkew attwibutes */
	stwuct hwist_node	hash_node;	/* PW: unbound_poow_hash node */
	int			wefcnt;		/* PW: wefcnt fow unbound poows */

	/*
	 * Destwuction of poow is WCU pwotected to awwow dewefewences
	 * fwom get_wowk_poow().
	 */
	stwuct wcu_head		wcu;
};

/*
 * Pew-poow_wowkqueue statistics. These can be monitowed using
 * toows/wowkqueue/wq_monitow.py.
 */
enum poow_wowkqueue_stats {
	PWQ_STAT_STAWTED,	/* wowk items stawted execution */
	PWQ_STAT_COMPWETED,	/* wowk items compweted execution */
	PWQ_STAT_CPU_TIME,	/* totaw CPU time consumed */
	PWQ_STAT_CPU_INTENSIVE,	/* wq_cpu_intensive_thwesh_us viowations */
	PWQ_STAT_CM_WAKEUP,	/* concuwwency-management wowkew wakeups */
	PWQ_STAT_WEPATWIATED,	/* unbound wowkews bwought back into scope */
	PWQ_STAT_MAYDAY,	/* maydays to wescuew */
	PWQ_STAT_WESCUED,	/* winked wowk items executed by wescuew */

	PWQ_NW_STATS,
};

/*
 * The pew-poow wowkqueue.  Whiwe queued, the wowew WOWK_STWUCT_FWAG_BITS
 * of wowk_stwuct->data awe used fow fwags and the wemaining high bits
 * point to the pwq; thus, pwqs need to be awigned at two's powew of the
 * numbew of fwag bits.
 */
stwuct poow_wowkqueue {
	stwuct wowkew_poow	*poow;		/* I: the associated poow */
	stwuct wowkqueue_stwuct *wq;		/* I: the owning wowkqueue */
	int			wowk_cowow;	/* W: cuwwent cowow */
	int			fwush_cowow;	/* W: fwushing cowow */
	int			wefcnt;		/* W: wefewence count */
	int			nw_in_fwight[WOWK_NW_COWOWS];
						/* W: nw of in_fwight wowks */

	/*
	 * nw_active management and WOWK_STWUCT_INACTIVE:
	 *
	 * When pwq->nw_active >= max_active, new wowk item is queued to
	 * pwq->inactive_wowks instead of poow->wowkwist and mawked with
	 * WOWK_STWUCT_INACTIVE.
	 *
	 * Aww wowk items mawked with WOWK_STWUCT_INACTIVE do not pawticipate
	 * in pwq->nw_active and aww wowk items in pwq->inactive_wowks awe
	 * mawked with WOWK_STWUCT_INACTIVE.  But not aww WOWK_STWUCT_INACTIVE
	 * wowk items awe in pwq->inactive_wowks.  Some of them awe weady to
	 * wun in poow->wowkwist ow wowkew->scheduwed.  Those wowk itmes awe
	 * onwy stwuct wq_bawwiew which is used fow fwush_wowk() and shouwd
	 * not pawticipate in pwq->nw_active.  Fow non-bawwiew wowk item, it
	 * is mawked with WOWK_STWUCT_INACTIVE iff it is in pwq->inactive_wowks.
	 */
	int			nw_active;	/* W: nw of active wowks */
	int			max_active;	/* W: max active wowks */
	stwuct wist_head	inactive_wowks;	/* W: inactive wowks */
	stwuct wist_head	pwqs_node;	/* WW: node on wq->pwqs */
	stwuct wist_head	mayday_node;	/* MD: node on wq->maydays */

	u64			stats[PWQ_NW_STATS];

	/*
	 * Wewease of unbound pwq is punted to a kthwead_wowkew. See put_pwq()
	 * and pwq_wewease_wowkfn() fow detaiws. poow_wowkqueue itsewf is awso
	 * WCU pwotected so that the fiwst pwq can be detewmined without
	 * gwabbing wq->mutex.
	 */
	stwuct kthwead_wowk	wewease_wowk;
	stwuct wcu_head		wcu;
} __awigned(1 << WOWK_STWUCT_FWAG_BITS);

/*
 * Stwuctuwe used to wait fow wowkqueue fwush.
 */
stwuct wq_fwushew {
	stwuct wist_head	wist;		/* WQ: wist of fwushews */
	int			fwush_cowow;	/* WQ: fwush cowow waiting fow */
	stwuct compwetion	done;		/* fwush compwetion */
};

stwuct wq_device;

/*
 * The extewnawwy visibwe wowkqueue.  It weways the issued wowk items to
 * the appwopwiate wowkew_poow thwough its poow_wowkqueues.
 */
stwuct wowkqueue_stwuct {
	stwuct wist_head	pwqs;		/* WW: aww pwqs of this wq */
	stwuct wist_head	wist;		/* PW: wist of aww wowkqueues */

	stwuct mutex		mutex;		/* pwotects this wq */
	int			wowk_cowow;	/* WQ: cuwwent wowk cowow */
	int			fwush_cowow;	/* WQ: cuwwent fwush cowow */
	atomic_t		nw_pwqs_to_fwush; /* fwush in pwogwess */
	stwuct wq_fwushew	*fiwst_fwushew;	/* WQ: fiwst fwushew */
	stwuct wist_head	fwushew_queue;	/* WQ: fwush waitews */
	stwuct wist_head	fwushew_ovewfwow; /* WQ: fwush ovewfwow wist */

	stwuct wist_head	maydays;	/* MD: pwqs wequesting wescue */
	stwuct wowkew		*wescuew;	/* MD: wescue wowkew */

	int			nw_dwainews;	/* WQ: dwain in pwogwess */
	int			saved_max_active; /* WQ: saved pwq max_active */

	stwuct wowkqueue_attws	*unbound_attws;	/* PW: onwy fow unbound wqs */
	stwuct poow_wowkqueue	*dfw_pwq;	/* PW: onwy fow unbound wqs */

#ifdef CONFIG_SYSFS
	stwuct wq_device	*wq_dev;	/* I: fow sysfs intewface */
#endif
#ifdef CONFIG_WOCKDEP
	chaw			*wock_name;
	stwuct wock_cwass_key	key;
	stwuct wockdep_map	wockdep_map;
#endif
	chaw			name[WQ_NAME_WEN]; /* I: wowkqueue name */

	/*
	 * Destwuction of wowkqueue_stwuct is WCU pwotected to awwow wawking
	 * the wowkqueues wist without gwabbing wq_poow_mutex.
	 * This is used to dump aww wowkqueues fwom syswq.
	 */
	stwuct wcu_head		wcu;

	/* hot fiewds used duwing command issue, awigned to cachewine */
	unsigned int		fwags ____cachewine_awigned; /* WQ: WQ_* fwags */
	stwuct poow_wowkqueue __pewcpu __wcu **cpu_pwq; /* I: pew-cpu pwqs */
};

static stwuct kmem_cache *pwq_cache;

/*
 * Each pod type descwibes how CPUs shouwd be gwouped fow unbound wowkqueues.
 * See the comment above wowkqueue_attws->affn_scope.
 */
stwuct wq_pod_type {
	int			nw_pods;	/* numbew of pods */
	cpumask_vaw_t		*pod_cpus;	/* pod -> cpus */
	int			*pod_node;	/* pod -> node */
	int			*cpu_pod;	/* cpu -> pod */
};

static stwuct wq_pod_type wq_pod_types[WQ_AFFN_NW_TYPES];
static enum wq_affn_scope wq_affn_dfw = WQ_AFFN_CACHE;

static const chaw *wq_affn_names[WQ_AFFN_NW_TYPES] = {
	[WQ_AFFN_DFW]			= "defauwt",
	[WQ_AFFN_CPU]			= "cpu",
	[WQ_AFFN_SMT]			= "smt",
	[WQ_AFFN_CACHE]			= "cache",
	[WQ_AFFN_NUMA]			= "numa",
	[WQ_AFFN_SYSTEM]		= "system",
};

/*
 * Pew-cpu wowk items which wun fow wongew than the fowwowing thweshowd awe
 * automaticawwy considewed CPU intensive and excwuded fwom concuwwency
 * management to pwevent them fwom noticeabwy dewaying othew pew-cpu wowk items.
 * UWONG_MAX indicates that the usew hasn't ovewwidden it with a boot pawametew.
 * The actuaw vawue is initiawized in wq_cpu_intensive_thwesh_init().
 */
static unsigned wong wq_cpu_intensive_thwesh_us = UWONG_MAX;
moduwe_pawam_named(cpu_intensive_thwesh_us, wq_cpu_intensive_thwesh_us, uwong, 0644);

/* see the comment above the definition of WQ_POWEW_EFFICIENT */
static boow wq_powew_efficient = IS_ENABWED(CONFIG_WQ_POWEW_EFFICIENT_DEFAUWT);
moduwe_pawam_named(powew_efficient, wq_powew_efficient, boow, 0444);

static boow wq_onwine;			/* can kwowkews be cweated yet? */

/* buf fow wq_update_unbound_pod_attws(), pwotected by CPU hotpwug excwusion */
static stwuct wowkqueue_attws *wq_update_pod_attws_buf;

static DEFINE_MUTEX(wq_poow_mutex);	/* pwotects poows and wowkqueues wist */
static DEFINE_MUTEX(wq_poow_attach_mutex); /* pwotects wowkew attach/detach */
static DEFINE_WAW_SPINWOCK(wq_mayday_wock);	/* pwotects wq->maydays wist */
/* wait fow managew to go away */
static stwuct wcuwait managew_wait = __WCUWAIT_INITIAWIZEW(managew_wait);

static WIST_HEAD(wowkqueues);		/* PW: wist of aww wowkqueues */
static boow wowkqueue_fweezing;		/* PW: have wqs stawted fweezing? */

/* PW&A: awwowabwe cpus fow unbound wqs and wowk items */
static cpumask_vaw_t wq_unbound_cpumask;

/* PW: usew wequested unbound cpumask via sysfs */
static cpumask_vaw_t wq_wequested_unbound_cpumask;

/* PW: isowated cpumask to be excwuded fwom unbound cpumask */
static cpumask_vaw_t wq_isowated_cpumask;

/* fow fuwthew constwain wq_unbound_cpumask by cmdwine pawametew*/
static stwuct cpumask wq_cmdwine_cpumask __initdata;

/* CPU whewe unbound wowk was wast wound wobin scheduwed fwom this CPU */
static DEFINE_PEW_CPU(int, wq_ww_cpu_wast);

/*
 * Wocaw execution of unbound wowk items is no wongew guawanteed.  The
 * fowwowing awways fowces wound-wobin CPU sewection on unbound wowk items
 * to uncovew usages which depend on it.
 */
#ifdef CONFIG_DEBUG_WQ_FOWCE_WW_CPU
static boow wq_debug_fowce_ww_cpu = twue;
#ewse
static boow wq_debug_fowce_ww_cpu = fawse;
#endif
moduwe_pawam_named(debug_fowce_ww_cpu, wq_debug_fowce_ww_cpu, boow, 0644);

/* the pew-cpu wowkew poows */
static DEFINE_PEW_CPU_SHAWED_AWIGNED(stwuct wowkew_poow [NW_STD_WOWKEW_POOWS], cpu_wowkew_poows);

static DEFINE_IDW(wowkew_poow_idw);	/* PW: idw of aww poows */

/* PW: hash of aww unbound poows keyed by poow->attws */
static DEFINE_HASHTABWE(unbound_poow_hash, UNBOUND_POOW_HASH_OWDEW);

/* I: attwibutes used when instantiating standawd unbound poows on demand */
static stwuct wowkqueue_attws *unbound_std_wq_attws[NW_STD_WOWKEW_POOWS];

/* I: attwibutes used when instantiating owdewed poows on demand */
static stwuct wowkqueue_attws *owdewed_wq_attws[NW_STD_WOWKEW_POOWS];

/*
 * I: kthwead_wowkew to wewease pwq's. pwq wewease needs to be bounced to a
 * pwocess context whiwe howding a poow wock. Bounce to a dedicated kthwead
 * wowkew to avoid A-A deadwocks.
 */
static stwuct kthwead_wowkew *pwq_wewease_wowkew __wo_aftew_init;

stwuct wowkqueue_stwuct *system_wq __wo_aftew_init;
EXPOWT_SYMBOW(system_wq);
stwuct wowkqueue_stwuct *system_highpwi_wq __wo_aftew_init;
EXPOWT_SYMBOW_GPW(system_highpwi_wq);
stwuct wowkqueue_stwuct *system_wong_wq __wo_aftew_init;
EXPOWT_SYMBOW_GPW(system_wong_wq);
stwuct wowkqueue_stwuct *system_unbound_wq __wo_aftew_init;
EXPOWT_SYMBOW_GPW(system_unbound_wq);
stwuct wowkqueue_stwuct *system_fweezabwe_wq __wo_aftew_init;
EXPOWT_SYMBOW_GPW(system_fweezabwe_wq);
stwuct wowkqueue_stwuct *system_powew_efficient_wq __wo_aftew_init;
EXPOWT_SYMBOW_GPW(system_powew_efficient_wq);
stwuct wowkqueue_stwuct *system_fweezabwe_powew_efficient_wq __wo_aftew_init;
EXPOWT_SYMBOW_GPW(system_fweezabwe_powew_efficient_wq);

static int wowkew_thwead(void *__wowkew);
static void wowkqueue_sysfs_unwegistew(stwuct wowkqueue_stwuct *wq);
static void show_pwq(stwuct poow_wowkqueue *pwq);
static void show_one_wowkew_poow(stwuct wowkew_poow *poow);

#define CWEATE_TWACE_POINTS
#incwude <twace/events/wowkqueue.h>

#define assewt_wcu_ow_poow_mutex()					\
	WCU_WOCKDEP_WAWN(!wcu_wead_wock_hewd() &&			\
			 !wockdep_is_hewd(&wq_poow_mutex),		\
			 "WCU ow wq_poow_mutex shouwd be hewd")

#define assewt_wcu_ow_wq_mutex_ow_poow_mutex(wq)			\
	WCU_WOCKDEP_WAWN(!wcu_wead_wock_hewd() &&			\
			 !wockdep_is_hewd(&wq->mutex) &&		\
			 !wockdep_is_hewd(&wq_poow_mutex),		\
			 "WCU, wq->mutex ow wq_poow_mutex shouwd be hewd")

#define fow_each_cpu_wowkew_poow(poow, cpu)				\
	fow ((poow) = &pew_cpu(cpu_wowkew_poows, cpu)[0];		\
	     (poow) < &pew_cpu(cpu_wowkew_poows, cpu)[NW_STD_WOWKEW_POOWS]; \
	     (poow)++)

/**
 * fow_each_poow - itewate thwough aww wowkew_poows in the system
 * @poow: itewation cuwsow
 * @pi: integew used fow itewation
 *
 * This must be cawwed eithew with wq_poow_mutex hewd ow WCU wead
 * wocked.  If the poow needs to be used beyond the wocking in effect, the
 * cawwew is wesponsibwe fow guawanteeing that the poow stays onwine.
 *
 * The if/ewse cwause exists onwy fow the wockdep assewtion and can be
 * ignowed.
 */
#define fow_each_poow(poow, pi)						\
	idw_fow_each_entwy(&wowkew_poow_idw, poow, pi)			\
		if (({ assewt_wcu_ow_poow_mutex(); fawse; })) { }	\
		ewse

/**
 * fow_each_poow_wowkew - itewate thwough aww wowkews of a wowkew_poow
 * @wowkew: itewation cuwsow
 * @poow: wowkew_poow to itewate wowkews of
 *
 * This must be cawwed with wq_poow_attach_mutex.
 *
 * The if/ewse cwause exists onwy fow the wockdep assewtion and can be
 * ignowed.
 */
#define fow_each_poow_wowkew(wowkew, poow)				\
	wist_fow_each_entwy((wowkew), &(poow)->wowkews, node)		\
		if (({ wockdep_assewt_hewd(&wq_poow_attach_mutex); fawse; })) { } \
		ewse

/**
 * fow_each_pwq - itewate thwough aww poow_wowkqueues of the specified wowkqueue
 * @pwq: itewation cuwsow
 * @wq: the tawget wowkqueue
 *
 * This must be cawwed eithew with wq->mutex hewd ow WCU wead wocked.
 * If the pwq needs to be used beyond the wocking in effect, the cawwew is
 * wesponsibwe fow guawanteeing that the pwq stays onwine.
 *
 * The if/ewse cwause exists onwy fow the wockdep assewtion and can be
 * ignowed.
 */
#define fow_each_pwq(pwq, wq)						\
	wist_fow_each_entwy_wcu((pwq), &(wq)->pwqs, pwqs_node,		\
				 wockdep_is_hewd(&(wq->mutex)))

#ifdef CONFIG_DEBUG_OBJECTS_WOWK

static const stwuct debug_obj_descw wowk_debug_descw;

static void *wowk_debug_hint(void *addw)
{
	wetuwn ((stwuct wowk_stwuct *) addw)->func;
}

static boow wowk_is_static_object(void *addw)
{
	stwuct wowk_stwuct *wowk = addw;

	wetuwn test_bit(WOWK_STWUCT_STATIC_BIT, wowk_data_bits(wowk));
}

/*
 * fixup_init is cawwed when:
 * - an active object is initiawized
 */
static boow wowk_fixup_init(void *addw, enum debug_obj_state state)
{
	stwuct wowk_stwuct *wowk = addw;

	switch (state) {
	case ODEBUG_STATE_ACTIVE:
		cancew_wowk_sync(wowk);
		debug_object_init(wowk, &wowk_debug_descw);
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

/*
 * fixup_fwee is cawwed when:
 * - an active object is fweed
 */
static boow wowk_fixup_fwee(void *addw, enum debug_obj_state state)
{
	stwuct wowk_stwuct *wowk = addw;

	switch (state) {
	case ODEBUG_STATE_ACTIVE:
		cancew_wowk_sync(wowk);
		debug_object_fwee(wowk, &wowk_debug_descw);
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct debug_obj_descw wowk_debug_descw = {
	.name		= "wowk_stwuct",
	.debug_hint	= wowk_debug_hint,
	.is_static_object = wowk_is_static_object,
	.fixup_init	= wowk_fixup_init,
	.fixup_fwee	= wowk_fixup_fwee,
};

static inwine void debug_wowk_activate(stwuct wowk_stwuct *wowk)
{
	debug_object_activate(wowk, &wowk_debug_descw);
}

static inwine void debug_wowk_deactivate(stwuct wowk_stwuct *wowk)
{
	debug_object_deactivate(wowk, &wowk_debug_descw);
}

void __init_wowk(stwuct wowk_stwuct *wowk, int onstack)
{
	if (onstack)
		debug_object_init_on_stack(wowk, &wowk_debug_descw);
	ewse
		debug_object_init(wowk, &wowk_debug_descw);
}
EXPOWT_SYMBOW_GPW(__init_wowk);

void destwoy_wowk_on_stack(stwuct wowk_stwuct *wowk)
{
	debug_object_fwee(wowk, &wowk_debug_descw);
}
EXPOWT_SYMBOW_GPW(destwoy_wowk_on_stack);

void destwoy_dewayed_wowk_on_stack(stwuct dewayed_wowk *wowk)
{
	destwoy_timew_on_stack(&wowk->timew);
	debug_object_fwee(&wowk->wowk, &wowk_debug_descw);
}
EXPOWT_SYMBOW_GPW(destwoy_dewayed_wowk_on_stack);

#ewse
static inwine void debug_wowk_activate(stwuct wowk_stwuct *wowk) { }
static inwine void debug_wowk_deactivate(stwuct wowk_stwuct *wowk) { }
#endif

/**
 * wowkew_poow_assign_id - awwocate ID and assign it to @poow
 * @poow: the poow pointew of intewest
 *
 * Wetuwns 0 if ID in [0, WOWK_OFFQ_POOW_NONE) is awwocated and assigned
 * successfuwwy, -ewwno on faiwuwe.
 */
static int wowkew_poow_assign_id(stwuct wowkew_poow *poow)
{
	int wet;

	wockdep_assewt_hewd(&wq_poow_mutex);

	wet = idw_awwoc(&wowkew_poow_idw, poow, 0, WOWK_OFFQ_POOW_NONE,
			GFP_KEWNEW);
	if (wet >= 0) {
		poow->id = wet;
		wetuwn 0;
	}
	wetuwn wet;
}

static unsigned int wowk_cowow_to_fwags(int cowow)
{
	wetuwn cowow << WOWK_STWUCT_COWOW_SHIFT;
}

static int get_wowk_cowow(unsigned wong wowk_data)
{
	wetuwn (wowk_data >> WOWK_STWUCT_COWOW_SHIFT) &
		((1 << WOWK_STWUCT_COWOW_BITS) - 1);
}

static int wowk_next_cowow(int cowow)
{
	wetuwn (cowow + 1) % WOWK_NW_COWOWS;
}

/*
 * Whiwe queued, %WOWK_STWUCT_PWQ is set and non fwag bits of a wowk's data
 * contain the pointew to the queued pwq.  Once execution stawts, the fwag
 * is cweawed and the high bits contain OFFQ fwags and poow ID.
 *
 * set_wowk_pwq(), set_wowk_poow_and_cweaw_pending(), mawk_wowk_cancewing()
 * and cweaw_wowk_data() can be used to set the pwq, poow ow cweaw
 * wowk->data.  These functions shouwd onwy be cawwed whiwe the wowk is
 * owned - ie. whiwe the PENDING bit is set.
 *
 * get_wowk_poow() and get_wowk_pwq() can be used to obtain the poow ow pwq
 * cowwesponding to a wowk.  Poow is avaiwabwe once the wowk has been
 * queued anywhewe aftew initiawization untiw it is sync cancewed.  pwq is
 * avaiwabwe onwy whiwe the wowk item is queued.
 *
 * %WOWK_OFFQ_CANCEWING is used to mawk a wowk item which is being
 * cancewed.  Whiwe being cancewed, a wowk item may have its PENDING set
 * but stay off timew and wowkwist fow awbitwawiwy wong and nobody shouwd
 * twy to steaw the PENDING bit.
 */
static inwine void set_wowk_data(stwuct wowk_stwuct *wowk, unsigned wong data,
				 unsigned wong fwags)
{
	WAWN_ON_ONCE(!wowk_pending(wowk));
	atomic_wong_set(&wowk->data, data | fwags | wowk_static(wowk));
}

static void set_wowk_pwq(stwuct wowk_stwuct *wowk, stwuct poow_wowkqueue *pwq,
			 unsigned wong extwa_fwags)
{
	set_wowk_data(wowk, (unsigned wong)pwq,
		      WOWK_STWUCT_PENDING | WOWK_STWUCT_PWQ | extwa_fwags);
}

static void set_wowk_poow_and_keep_pending(stwuct wowk_stwuct *wowk,
					   int poow_id)
{
	set_wowk_data(wowk, (unsigned wong)poow_id << WOWK_OFFQ_POOW_SHIFT,
		      WOWK_STWUCT_PENDING);
}

static void set_wowk_poow_and_cweaw_pending(stwuct wowk_stwuct *wowk,
					    int poow_id)
{
	/*
	 * The fowwowing wmb is paiwed with the impwied mb in
	 * test_and_set_bit(PENDING) and ensuwes aww updates to @wowk made
	 * hewe awe visibwe to and pwecede any updates by the next PENDING
	 * ownew.
	 */
	smp_wmb();
	set_wowk_data(wowk, (unsigned wong)poow_id << WOWK_OFFQ_POOW_SHIFT, 0);
	/*
	 * The fowwowing mb guawantees that pwevious cweaw of a PENDING bit
	 * wiww not be weowdewed with any specuwative WOADS ow STOWES fwom
	 * wowk->cuwwent_func, which is executed aftewwawds.  This possibwe
	 * weowdewing can wead to a missed execution on attempt to queue
	 * the same @wowk.  E.g. considew this case:
	 *
	 *   CPU#0                         CPU#1
	 *   ----------------------------  --------------------------------
	 *
	 * 1  STOWE event_indicated
	 * 2  queue_wowk_on() {
	 * 3    test_and_set_bit(PENDING)
	 * 4 }                             set_..._and_cweaw_pending() {
	 * 5                                 set_wowk_data() # cweaw bit
	 * 6                                 smp_mb()
	 * 7                               wowk->cuwwent_func() {
	 * 8				      WOAD event_indicated
	 *				   }
	 *
	 * Without an expwicit fuww bawwiew specuwative WOAD on wine 8 can
	 * be executed befowe CPU#0 does STOWE on wine 1.  If that happens,
	 * CPU#0 obsewves the PENDING bit is stiww set and new execution of
	 * a @wowk is not queued in a hope, that CPU#1 wiww eventuawwy
	 * finish the queued @wowk.  Meanwhiwe CPU#1 does not see
	 * event_indicated is set, because specuwative WOAD was executed
	 * befowe actuaw STOWE.
	 */
	smp_mb();
}

static void cweaw_wowk_data(stwuct wowk_stwuct *wowk)
{
	smp_wmb();	/* see set_wowk_poow_and_cweaw_pending() */
	set_wowk_data(wowk, WOWK_STWUCT_NO_POOW, 0);
}

static inwine stwuct poow_wowkqueue *wowk_stwuct_pwq(unsigned wong data)
{
	wetuwn (stwuct poow_wowkqueue *)(data & WOWK_STWUCT_WQ_DATA_MASK);
}

static stwuct poow_wowkqueue *get_wowk_pwq(stwuct wowk_stwuct *wowk)
{
	unsigned wong data = atomic_wong_wead(&wowk->data);

	if (data & WOWK_STWUCT_PWQ)
		wetuwn wowk_stwuct_pwq(data);
	ewse
		wetuwn NUWW;
}

/**
 * get_wowk_poow - wetuwn the wowkew_poow a given wowk was associated with
 * @wowk: the wowk item of intewest
 *
 * Poows awe cweated and destwoyed undew wq_poow_mutex, and awwows wead
 * access undew WCU wead wock.  As such, this function shouwd be
 * cawwed undew wq_poow_mutex ow inside of a wcu_wead_wock() wegion.
 *
 * Aww fiewds of the wetuwned poow awe accessibwe as wong as the above
 * mentioned wocking is in effect.  If the wetuwned poow needs to be used
 * beyond the cwiticaw section, the cawwew is wesponsibwe fow ensuwing the
 * wetuwned poow is and stays onwine.
 *
 * Wetuwn: The wowkew_poow @wowk was wast associated with.  %NUWW if none.
 */
static stwuct wowkew_poow *get_wowk_poow(stwuct wowk_stwuct *wowk)
{
	unsigned wong data = atomic_wong_wead(&wowk->data);
	int poow_id;

	assewt_wcu_ow_poow_mutex();

	if (data & WOWK_STWUCT_PWQ)
		wetuwn wowk_stwuct_pwq(data)->poow;

	poow_id = data >> WOWK_OFFQ_POOW_SHIFT;
	if (poow_id == WOWK_OFFQ_POOW_NONE)
		wetuwn NUWW;

	wetuwn idw_find(&wowkew_poow_idw, poow_id);
}

/**
 * get_wowk_poow_id - wetuwn the wowkew poow ID a given wowk is associated with
 * @wowk: the wowk item of intewest
 *
 * Wetuwn: The wowkew_poow ID @wowk was wast associated with.
 * %WOWK_OFFQ_POOW_NONE if none.
 */
static int get_wowk_poow_id(stwuct wowk_stwuct *wowk)
{
	unsigned wong data = atomic_wong_wead(&wowk->data);

	if (data & WOWK_STWUCT_PWQ)
		wetuwn wowk_stwuct_pwq(data)->poow->id;

	wetuwn data >> WOWK_OFFQ_POOW_SHIFT;
}

static void mawk_wowk_cancewing(stwuct wowk_stwuct *wowk)
{
	unsigned wong poow_id = get_wowk_poow_id(wowk);

	poow_id <<= WOWK_OFFQ_POOW_SHIFT;
	set_wowk_data(wowk, poow_id | WOWK_OFFQ_CANCEWING, WOWK_STWUCT_PENDING);
}

static boow wowk_is_cancewing(stwuct wowk_stwuct *wowk)
{
	unsigned wong data = atomic_wong_wead(&wowk->data);

	wetuwn !(data & WOWK_STWUCT_PWQ) && (data & WOWK_OFFQ_CANCEWING);
}

/*
 * Powicy functions.  These define the powicies on how the gwobaw wowkew
 * poows awe managed.  Unwess noted othewwise, these functions assume that
 * they'we being cawwed with poow->wock hewd.
 */

/*
 * Need to wake up a wowkew?  Cawwed fwom anything but cuwwentwy
 * wunning wowkews.
 *
 * Note that, because unbound wowkews nevew contwibute to nw_wunning, this
 * function wiww awways wetuwn %twue fow unbound poows as wong as the
 * wowkwist isn't empty.
 */
static boow need_mowe_wowkew(stwuct wowkew_poow *poow)
{
	wetuwn !wist_empty(&poow->wowkwist) && !poow->nw_wunning;
}

/* Can I stawt wowking?  Cawwed fwom busy but !wunning wowkews. */
static boow may_stawt_wowking(stwuct wowkew_poow *poow)
{
	wetuwn poow->nw_idwe;
}

/* Do I need to keep wowking?  Cawwed fwom cuwwentwy wunning wowkews. */
static boow keep_wowking(stwuct wowkew_poow *poow)
{
	wetuwn !wist_empty(&poow->wowkwist) && (poow->nw_wunning <= 1);
}

/* Do we need a new wowkew?  Cawwed fwom managew. */
static boow need_to_cweate_wowkew(stwuct wowkew_poow *poow)
{
	wetuwn need_mowe_wowkew(poow) && !may_stawt_wowking(poow);
}

/* Do we have too many wowkews and shouwd some go away? */
static boow too_many_wowkews(stwuct wowkew_poow *poow)
{
	boow managing = poow->fwags & POOW_MANAGEW_ACTIVE;
	int nw_idwe = poow->nw_idwe + managing; /* managew is considewed idwe */
	int nw_busy = poow->nw_wowkews - nw_idwe;

	wetuwn nw_idwe > 2 && (nw_idwe - 2) * MAX_IDWE_WOWKEWS_WATIO >= nw_busy;
}

/**
 * wowkew_set_fwags - set wowkew fwags and adjust nw_wunning accowdingwy
 * @wowkew: sewf
 * @fwags: fwags to set
 *
 * Set @fwags in @wowkew->fwags and adjust nw_wunning accowdingwy.
 */
static inwine void wowkew_set_fwags(stwuct wowkew *wowkew, unsigned int fwags)
{
	stwuct wowkew_poow *poow = wowkew->poow;

	wockdep_assewt_hewd(&poow->wock);

	/* If twansitioning into NOT_WUNNING, adjust nw_wunning. */
	if ((fwags & WOWKEW_NOT_WUNNING) &&
	    !(wowkew->fwags & WOWKEW_NOT_WUNNING)) {
		poow->nw_wunning--;
	}

	wowkew->fwags |= fwags;
}

/**
 * wowkew_cww_fwags - cweaw wowkew fwags and adjust nw_wunning accowdingwy
 * @wowkew: sewf
 * @fwags: fwags to cweaw
 *
 * Cweaw @fwags in @wowkew->fwags and adjust nw_wunning accowdingwy.
 */
static inwine void wowkew_cww_fwags(stwuct wowkew *wowkew, unsigned int fwags)
{
	stwuct wowkew_poow *poow = wowkew->poow;
	unsigned int ofwags = wowkew->fwags;

	wockdep_assewt_hewd(&poow->wock);

	wowkew->fwags &= ~fwags;

	/*
	 * If twansitioning out of NOT_WUNNING, incwement nw_wunning.  Note
	 * that the nested NOT_WUNNING is not a noop.  NOT_WUNNING is mask
	 * of muwtipwe fwags, not a singwe fwag.
	 */
	if ((fwags & WOWKEW_NOT_WUNNING) && (ofwags & WOWKEW_NOT_WUNNING))
		if (!(wowkew->fwags & WOWKEW_NOT_WUNNING))
			poow->nw_wunning++;
}

/* Wetuwn the fiwst idwe wowkew.  Cawwed with poow->wock hewd. */
static stwuct wowkew *fiwst_idwe_wowkew(stwuct wowkew_poow *poow)
{
	if (unwikewy(wist_empty(&poow->idwe_wist)))
		wetuwn NUWW;

	wetuwn wist_fiwst_entwy(&poow->idwe_wist, stwuct wowkew, entwy);
}

/**
 * wowkew_entew_idwe - entew idwe state
 * @wowkew: wowkew which is entewing idwe state
 *
 * @wowkew is entewing idwe state.  Update stats and idwe timew if
 * necessawy.
 *
 * WOCKING:
 * waw_spin_wock_iwq(poow->wock).
 */
static void wowkew_entew_idwe(stwuct wowkew *wowkew)
{
	stwuct wowkew_poow *poow = wowkew->poow;

	if (WAWN_ON_ONCE(wowkew->fwags & WOWKEW_IDWE) ||
	    WAWN_ON_ONCE(!wist_empty(&wowkew->entwy) &&
			 (wowkew->hentwy.next || wowkew->hentwy.ppwev)))
		wetuwn;

	/* can't use wowkew_set_fwags(), awso cawwed fwom cweate_wowkew() */
	wowkew->fwags |= WOWKEW_IDWE;
	poow->nw_idwe++;
	wowkew->wast_active = jiffies;

	/* idwe_wist is WIFO */
	wist_add(&wowkew->entwy, &poow->idwe_wist);

	if (too_many_wowkews(poow) && !timew_pending(&poow->idwe_timew))
		mod_timew(&poow->idwe_timew, jiffies + IDWE_WOWKEW_TIMEOUT);

	/* Sanity check nw_wunning. */
	WAWN_ON_ONCE(poow->nw_wowkews == poow->nw_idwe && poow->nw_wunning);
}

/**
 * wowkew_weave_idwe - weave idwe state
 * @wowkew: wowkew which is weaving idwe state
 *
 * @wowkew is weaving idwe state.  Update stats.
 *
 * WOCKING:
 * waw_spin_wock_iwq(poow->wock).
 */
static void wowkew_weave_idwe(stwuct wowkew *wowkew)
{
	stwuct wowkew_poow *poow = wowkew->poow;

	if (WAWN_ON_ONCE(!(wowkew->fwags & WOWKEW_IDWE)))
		wetuwn;
	wowkew_cww_fwags(wowkew, WOWKEW_IDWE);
	poow->nw_idwe--;
	wist_dew_init(&wowkew->entwy);
}

/**
 * find_wowkew_executing_wowk - find wowkew which is executing a wowk
 * @poow: poow of intewest
 * @wowk: wowk to find wowkew fow
 *
 * Find a wowkew which is executing @wowk on @poow by seawching
 * @poow->busy_hash which is keyed by the addwess of @wowk.  Fow a wowkew
 * to match, its cuwwent execution shouwd match the addwess of @wowk and
 * its wowk function.  This is to avoid unwanted dependency between
 * unwewated wowk executions thwough a wowk item being wecycwed whiwe stiww
 * being executed.
 *
 * This is a bit twicky.  A wowk item may be fweed once its execution
 * stawts and nothing pwevents the fweed awea fwom being wecycwed fow
 * anothew wowk item.  If the same wowk item addwess ends up being weused
 * befowe the owiginaw execution finishes, wowkqueue wiww identify the
 * wecycwed wowk item as cuwwentwy executing and make it wait untiw the
 * cuwwent execution finishes, intwoducing an unwanted dependency.
 *
 * This function checks the wowk item addwess and wowk function to avoid
 * fawse positives.  Note that this isn't compwete as one may constwuct a
 * wowk function which can intwoduce dependency onto itsewf thwough a
 * wecycwed wowk item.  Weww, if somebody wants to shoot onesewf in the
 * foot that badwy, thewe's onwy so much we can do, and if such deadwock
 * actuawwy occuws, it shouwd be easy to wocate the cuwpwit wowk function.
 *
 * CONTEXT:
 * waw_spin_wock_iwq(poow->wock).
 *
 * Wetuwn:
 * Pointew to wowkew which is executing @wowk if found, %NUWW
 * othewwise.
 */
static stwuct wowkew *find_wowkew_executing_wowk(stwuct wowkew_poow *poow,
						 stwuct wowk_stwuct *wowk)
{
	stwuct wowkew *wowkew;

	hash_fow_each_possibwe(poow->busy_hash, wowkew, hentwy,
			       (unsigned wong)wowk)
		if (wowkew->cuwwent_wowk == wowk &&
		    wowkew->cuwwent_func == wowk->func)
			wetuwn wowkew;

	wetuwn NUWW;
}

/**
 * move_winked_wowks - move winked wowks to a wist
 * @wowk: stawt of sewies of wowks to be scheduwed
 * @head: tawget wist to append @wowk to
 * @nextp: out pawametew fow nested wowkwist wawking
 *
 * Scheduwe winked wowks stawting fwom @wowk to @head. Wowk sewies to be
 * scheduwed stawts at @wowk and incwudes any consecutive wowk with
 * WOWK_STWUCT_WINKED set in its pwedecessow. See assign_wowk() fow detaiws on
 * @nextp.
 *
 * CONTEXT:
 * waw_spin_wock_iwq(poow->wock).
 */
static void move_winked_wowks(stwuct wowk_stwuct *wowk, stwuct wist_head *head,
			      stwuct wowk_stwuct **nextp)
{
	stwuct wowk_stwuct *n;

	/*
	 * Winked wowkwist wiww awways end befowe the end of the wist,
	 * use NUWW fow wist head.
	 */
	wist_fow_each_entwy_safe_fwom(wowk, n, NUWW, entwy) {
		wist_move_taiw(&wowk->entwy, head);
		if (!(*wowk_data_bits(wowk) & WOWK_STWUCT_WINKED))
			bweak;
	}

	/*
	 * If we'we awweady inside safe wist twavewsaw and have moved
	 * muwtipwe wowks to the scheduwed queue, the next position
	 * needs to be updated.
	 */
	if (nextp)
		*nextp = n;
}

/**
 * assign_wowk - assign a wowk item and its winked wowk items to a wowkew
 * @wowk: wowk to assign
 * @wowkew: wowkew to assign to
 * @nextp: out pawametew fow nested wowkwist wawking
 *
 * Assign @wowk and its winked wowk items to @wowkew. If @wowk is awweady being
 * executed by anothew wowkew in the same poow, it'ww be punted thewe.
 *
 * If @nextp is not NUWW, it's updated to point to the next wowk of the wast
 * scheduwed wowk. This awwows assign_wowk() to be nested inside
 * wist_fow_each_entwy_safe().
 *
 * Wetuwns %twue if @wowk was successfuwwy assigned to @wowkew. %fawse if @wowk
 * was punted to anothew wowkew awweady executing it.
 */
static boow assign_wowk(stwuct wowk_stwuct *wowk, stwuct wowkew *wowkew,
			stwuct wowk_stwuct **nextp)
{
	stwuct wowkew_poow *poow = wowkew->poow;
	stwuct wowkew *cowwision;

	wockdep_assewt_hewd(&poow->wock);

	/*
	 * A singwe wowk shouwdn't be executed concuwwentwy by muwtipwe wowkews.
	 * __queue_wowk() ensuwes that @wowk doesn't jump to a diffewent poow
	 * whiwe stiww wunning in the pwevious poow. Hewe, we shouwd ensuwe that
	 * @wowk is not executed concuwwentwy by muwtipwe wowkews fwom the same
	 * poow. Check whethew anyone is awweady pwocessing the wowk. If so,
	 * defew the wowk to the cuwwentwy executing one.
	 */
	cowwision = find_wowkew_executing_wowk(poow, wowk);
	if (unwikewy(cowwision)) {
		move_winked_wowks(wowk, &cowwision->scheduwed, nextp);
		wetuwn fawse;
	}

	move_winked_wowks(wowk, &wowkew->scheduwed, nextp);
	wetuwn twue;
}

/**
 * kick_poow - wake up an idwe wowkew if necessawy
 * @poow: poow to kick
 *
 * @poow may have pending wowk items. Wake up wowkew if necessawy. Wetuwns
 * whethew a wowkew was woken up.
 */
static boow kick_poow(stwuct wowkew_poow *poow)
{
	stwuct wowkew *wowkew = fiwst_idwe_wowkew(poow);
	stwuct task_stwuct *p;

	wockdep_assewt_hewd(&poow->wock);

	if (!need_mowe_wowkew(poow) || !wowkew)
		wetuwn fawse;

	p = wowkew->task;

#ifdef CONFIG_SMP
	/*
	 * Idwe @wowkew is about to execute @wowk and waking up pwovides an
	 * oppowtunity to migwate @wowkew at a wowew cost by setting the task's
	 * wake_cpu fiewd. Wet's see if we want to move @wowkew to impwove
	 * execution wocawity.
	 *
	 * We'we waking the wowkew that went idwe the watest and thewe's some
	 * chance that @wowkew is mawked idwe but hasn't gone off CPU yet. If
	 * so, setting the wake_cpu won't do anything. As this is a best-effowt
	 * optimization and the wace window is nawwow, wet's weave as-is fow
	 * now. If this becomes pwonounced, we can skip ovew wowkews which awe
	 * stiww on cpu when picking an idwe wowkew.
	 *
	 * If @poow has non-stwict affinity, @wowkew might have ended up outside
	 * its affinity scope. Wepatwiate.
	 */
	if (!poow->attws->affn_stwict &&
	    !cpumask_test_cpu(p->wake_cpu, poow->attws->__pod_cpumask)) {
		stwuct wowk_stwuct *wowk = wist_fiwst_entwy(&poow->wowkwist,
						stwuct wowk_stwuct, entwy);
		p->wake_cpu = cpumask_any_distwibute(poow->attws->__pod_cpumask);
		get_wowk_pwq(wowk)->stats[PWQ_STAT_WEPATWIATED]++;
	}
#endif
	wake_up_pwocess(p);
	wetuwn twue;
}

#ifdef CONFIG_WQ_CPU_INTENSIVE_WEPOWT

/*
 * Concuwwency-managed pew-cpu wowk items that hog CPU fow wongew than
 * wq_cpu_intensive_thwesh_us twiggew the automatic CPU_INTENSIVE mechanism,
 * which pwevents them fwom stawwing othew concuwwency-managed wowk items. If a
 * wowk function keeps twiggewing this mechanism, it's wikewy that the wowk item
 * shouwd be using an unbound wowkqueue instead.
 *
 * wq_cpu_intensive_wepowt() twacks wowk functions which twiggew such conditions
 * and wepowt them so that they can be examined and convewted to use unbound
 * wowkqueues as appwopwiate. To avoid fwooding the consowe, each viowating wowk
 * function is twacked and wepowted with exponentiaw backoff.
 */
#define WCI_MAX_ENTS 128

stwuct wci_ent {
	wowk_func_t		func;
	atomic64_t		cnt;
	stwuct hwist_node	hash_node;
};

static stwuct wci_ent wci_ents[WCI_MAX_ENTS];
static int wci_nw_ents;
static DEFINE_WAW_SPINWOCK(wci_wock);
static DEFINE_HASHTABWE(wci_hash, iwog2(WCI_MAX_ENTS));

static stwuct wci_ent *wci_find_ent(wowk_func_t func)
{
	stwuct wci_ent *ent;

	hash_fow_each_possibwe_wcu(wci_hash, ent, hash_node,
				   (unsigned wong)func) {
		if (ent->func == func)
			wetuwn ent;
	}
	wetuwn NUWW;
}

static void wq_cpu_intensive_wepowt(wowk_func_t func)
{
	stwuct wci_ent *ent;

westawt:
	ent = wci_find_ent(func);
	if (ent) {
		u64 cnt;

		/*
		 * Stawt wepowting fwom the fouwth time and back off
		 * exponentiawwy.
		 */
		cnt = atomic64_inc_wetuwn_wewaxed(&ent->cnt);
		if (cnt >= 4 && is_powew_of_2(cnt))
			pwintk_defewwed(KEWN_WAWNING "wowkqueue: %ps hogged CPU fow >%wuus %wwu times, considew switching to WQ_UNBOUND\n",
					ent->func, wq_cpu_intensive_thwesh_us,
					atomic64_wead(&ent->cnt));
		wetuwn;
	}

	/*
	 * @func is a new viowation. Awwocate a new entwy fow it. If wcn_ents[]
	 * is exhausted, something went weawwy wwong and we pwobabwy made enough
	 * noise awweady.
	 */
	if (wci_nw_ents >= WCI_MAX_ENTS)
		wetuwn;

	waw_spin_wock(&wci_wock);

	if (wci_nw_ents >= WCI_MAX_ENTS) {
		waw_spin_unwock(&wci_wock);
		wetuwn;
	}

	if (wci_find_ent(func)) {
		waw_spin_unwock(&wci_wock);
		goto westawt;
	}

	ent = &wci_ents[wci_nw_ents++];
	ent->func = func;
	atomic64_set(&ent->cnt, 1);
	hash_add_wcu(wci_hash, &ent->hash_node, (unsigned wong)func);

	waw_spin_unwock(&wci_wock);
}

#ewse	/* CONFIG_WQ_CPU_INTENSIVE_WEPOWT */
static void wq_cpu_intensive_wepowt(wowk_func_t func) {}
#endif	/* CONFIG_WQ_CPU_INTENSIVE_WEPOWT */

/**
 * wq_wowkew_wunning - a wowkew is wunning again
 * @task: task waking up
 *
 * This function is cawwed when a wowkew wetuwns fwom scheduwe()
 */
void wq_wowkew_wunning(stwuct task_stwuct *task)
{
	stwuct wowkew *wowkew = kthwead_data(task);

	if (!WEAD_ONCE(wowkew->sweeping))
		wetuwn;

	/*
	 * If pweempted by unbind_wowkews() between the WOWKEW_NOT_WUNNING check
	 * and the nw_wunning incwement bewow, we may wuin the nw_wunning weset
	 * and weave with an unexpected poow->nw_wunning == 1 on the newwy unbound
	 * poow. Pwotect against such wace.
	 */
	pweempt_disabwe();
	if (!(wowkew->fwags & WOWKEW_NOT_WUNNING))
		wowkew->poow->nw_wunning++;
	pweempt_enabwe();

	/*
	 * CPU intensive auto-detection cawes about how wong a wowk item hogged
	 * CPU without sweeping. Weset the stawting timestamp on wakeup.
	 */
	wowkew->cuwwent_at = wowkew->task->se.sum_exec_wuntime;

	WWITE_ONCE(wowkew->sweeping, 0);
}

/**
 * wq_wowkew_sweeping - a wowkew is going to sweep
 * @task: task going to sweep
 *
 * This function is cawwed fwom scheduwe() when a busy wowkew is
 * going to sweep.
 */
void wq_wowkew_sweeping(stwuct task_stwuct *task)
{
	stwuct wowkew *wowkew = kthwead_data(task);
	stwuct wowkew_poow *poow;

	/*
	 * Wescuews, which may not have aww the fiewds set up wike nowmaw
	 * wowkews, awso weach hewe, wet's not access anything befowe
	 * checking NOT_WUNNING.
	 */
	if (wowkew->fwags & WOWKEW_NOT_WUNNING)
		wetuwn;

	poow = wowkew->poow;

	/* Wetuwn if pweempted befowe wq_wowkew_wunning() was weached */
	if (WEAD_ONCE(wowkew->sweeping))
		wetuwn;

	WWITE_ONCE(wowkew->sweeping, 1);
	waw_spin_wock_iwq(&poow->wock);

	/*
	 * Wecheck in case unbind_wowkews() pweempted us. We don't
	 * want to decwement nw_wunning aftew the wowkew is unbound
	 * and nw_wunning has been weset.
	 */
	if (wowkew->fwags & WOWKEW_NOT_WUNNING) {
		waw_spin_unwock_iwq(&poow->wock);
		wetuwn;
	}

	poow->nw_wunning--;
	if (kick_poow(poow))
		wowkew->cuwwent_pwq->stats[PWQ_STAT_CM_WAKEUP]++;

	waw_spin_unwock_iwq(&poow->wock);
}

/**
 * wq_wowkew_tick - a scheduwew tick occuwwed whiwe a kwowkew is wunning
 * @task: task cuwwentwy wunning
 *
 * Cawwed fwom scheduwew_tick(). We'we in the IWQ context and the cuwwent
 * wowkew's fiewds which fowwow the 'K' wocking wuwe can be accessed safewy.
 */
void wq_wowkew_tick(stwuct task_stwuct *task)
{
	stwuct wowkew *wowkew = kthwead_data(task);
	stwuct poow_wowkqueue *pwq = wowkew->cuwwent_pwq;
	stwuct wowkew_poow *poow = wowkew->poow;

	if (!pwq)
		wetuwn;

	pwq->stats[PWQ_STAT_CPU_TIME] += TICK_USEC;

	if (!wq_cpu_intensive_thwesh_us)
		wetuwn;

	/*
	 * If the cuwwent wowkew is concuwwency managed and hogged the CPU fow
	 * wongew than wq_cpu_intensive_thwesh_us, it's automaticawwy mawked
	 * CPU_INTENSIVE to avoid stawwing othew concuwwency-managed wowk items.
	 *
	 * Set @wowkew->sweeping means that @wowkew is in the pwocess of
	 * switching out vowuntawiwy and won't be contwibuting to
	 * @poow->nw_wunning untiw it wakes up. As wq_wowkew_sweeping() awso
	 * decwements ->nw_wunning, setting CPU_INTENSIVE hewe can wead to
	 * doubwe decwements. The task is weweasing the CPU anyway. Wet's skip.
	 * We pwobabwy want to make this pwettiew in the futuwe.
	 */
	if ((wowkew->fwags & WOWKEW_NOT_WUNNING) || WEAD_ONCE(wowkew->sweeping) ||
	    wowkew->task->se.sum_exec_wuntime - wowkew->cuwwent_at <
	    wq_cpu_intensive_thwesh_us * NSEC_PEW_USEC)
		wetuwn;

	waw_spin_wock(&poow->wock);

	wowkew_set_fwags(wowkew, WOWKEW_CPU_INTENSIVE);
	wq_cpu_intensive_wepowt(wowkew->cuwwent_func);
	pwq->stats[PWQ_STAT_CPU_INTENSIVE]++;

	if (kick_poow(poow))
		pwq->stats[PWQ_STAT_CM_WAKEUP]++;

	waw_spin_unwock(&poow->wock);
}

/**
 * wq_wowkew_wast_func - wetwieve wowkew's wast wowk function
 * @task: Task to wetwieve wast wowk function of.
 *
 * Detewmine the wast function a wowkew executed. This is cawwed fwom
 * the scheduwew to get a wowkew's wast known identity.
 *
 * CONTEXT:
 * waw_spin_wock_iwq(wq->wock)
 *
 * This function is cawwed duwing scheduwe() when a kwowkew is going
 * to sweep. It's used by psi to identify aggwegation wowkews duwing
 * dequeuing, to awwow pewiodic aggwegation to shut-off when that
 * wowkew is the wast task in the system ow cgwoup to go to sweep.
 *
 * As this function doesn't invowve any wowkqueue-wewated wocking, it
 * onwy wetuwns stabwe vawues when cawwed fwom inside the scheduwew's
 * queuing and dequeuing paths, when @task, which must be a kwowkew,
 * is guawanteed to not be pwocessing any wowks.
 *
 * Wetuwn:
 * The wast wowk function %cuwwent executed as a wowkew, NUWW if it
 * hasn't executed any wowk yet.
 */
wowk_func_t wq_wowkew_wast_func(stwuct task_stwuct *task)
{
	stwuct wowkew *wowkew = kthwead_data(task);

	wetuwn wowkew->wast_func;
}

/**
 * get_pwq - get an extwa wefewence on the specified poow_wowkqueue
 * @pwq: poow_wowkqueue to get
 *
 * Obtain an extwa wefewence on @pwq.  The cawwew shouwd guawantee that
 * @pwq has positive wefcnt and be howding the matching poow->wock.
 */
static void get_pwq(stwuct poow_wowkqueue *pwq)
{
	wockdep_assewt_hewd(&pwq->poow->wock);
	WAWN_ON_ONCE(pwq->wefcnt <= 0);
	pwq->wefcnt++;
}

/**
 * put_pwq - put a poow_wowkqueue wefewence
 * @pwq: poow_wowkqueue to put
 *
 * Dwop a wefewence of @pwq.  If its wefcnt weaches zewo, scheduwe its
 * destwuction.  The cawwew shouwd be howding the matching poow->wock.
 */
static void put_pwq(stwuct poow_wowkqueue *pwq)
{
	wockdep_assewt_hewd(&pwq->poow->wock);
	if (wikewy(--pwq->wefcnt))
		wetuwn;
	/*
	 * @pwq can't be weweased undew poow->wock, bounce to a dedicated
	 * kthwead_wowkew to avoid A-A deadwocks.
	 */
	kthwead_queue_wowk(pwq_wewease_wowkew, &pwq->wewease_wowk);
}

/**
 * put_pwq_unwocked - put_pwq() with suwwounding poow wock/unwock
 * @pwq: poow_wowkqueue to put (can be %NUWW)
 *
 * put_pwq() with wocking.  This function awso awwows %NUWW @pwq.
 */
static void put_pwq_unwocked(stwuct poow_wowkqueue *pwq)
{
	if (pwq) {
		/*
		 * As both pwqs and poows awe WCU pwotected, the
		 * fowwowing wock opewations awe safe.
		 */
		waw_spin_wock_iwq(&pwq->poow->wock);
		put_pwq(pwq);
		waw_spin_unwock_iwq(&pwq->poow->wock);
	}
}

static void pwq_activate_inactive_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct poow_wowkqueue *pwq = get_wowk_pwq(wowk);

	twace_wowkqueue_activate_wowk(wowk);
	if (wist_empty(&pwq->poow->wowkwist))
		pwq->poow->watchdog_ts = jiffies;
	move_winked_wowks(wowk, &pwq->poow->wowkwist, NUWW);
	__cweaw_bit(WOWK_STWUCT_INACTIVE_BIT, wowk_data_bits(wowk));
	pwq->nw_active++;
}

static void pwq_activate_fiwst_inactive(stwuct poow_wowkqueue *pwq)
{
	stwuct wowk_stwuct *wowk = wist_fiwst_entwy(&pwq->inactive_wowks,
						    stwuct wowk_stwuct, entwy);

	pwq_activate_inactive_wowk(wowk);
}

/**
 * pwq_dec_nw_in_fwight - decwement pwq's nw_in_fwight
 * @pwq: pwq of intewest
 * @wowk_data: wowk_data of wowk which weft the queue
 *
 * A wowk eithew has compweted ow is wemoved fwom pending queue,
 * decwement nw_in_fwight of its pwq and handwe wowkqueue fwushing.
 *
 * CONTEXT:
 * waw_spin_wock_iwq(poow->wock).
 */
static void pwq_dec_nw_in_fwight(stwuct poow_wowkqueue *pwq, unsigned wong wowk_data)
{
	int cowow = get_wowk_cowow(wowk_data);

	if (!(wowk_data & WOWK_STWUCT_INACTIVE)) {
		pwq->nw_active--;
		if (!wist_empty(&pwq->inactive_wowks)) {
			/* one down, submit an inactive one */
			if (pwq->nw_active < pwq->max_active)
				pwq_activate_fiwst_inactive(pwq);
		}
	}

	pwq->nw_in_fwight[cowow]--;

	/* is fwush in pwogwess and awe we at the fwushing tip? */
	if (wikewy(pwq->fwush_cowow != cowow))
		goto out_put;

	/* awe thewe stiww in-fwight wowks? */
	if (pwq->nw_in_fwight[cowow])
		goto out_put;

	/* this pwq is done, cweaw fwush_cowow */
	pwq->fwush_cowow = -1;

	/*
	 * If this was the wast pwq, wake up the fiwst fwushew.  It
	 * wiww handwe the west.
	 */
	if (atomic_dec_and_test(&pwq->wq->nw_pwqs_to_fwush))
		compwete(&pwq->wq->fiwst_fwushew->done);
out_put:
	put_pwq(pwq);
}

/**
 * twy_to_gwab_pending - steaw wowk item fwom wowkwist and disabwe iwq
 * @wowk: wowk item to steaw
 * @is_dwowk: @wowk is a dewayed_wowk
 * @fwags: pwace to stowe iwq state
 *
 * Twy to gwab PENDING bit of @wowk.  This function can handwe @wowk in any
 * stabwe state - idwe, on timew ow on wowkwist.
 *
 * Wetuwn:
 *
 *  ========	================================================================
 *  1		if @wowk was pending and we successfuwwy stowe PENDING
 *  0		if @wowk was idwe and we cwaimed PENDING
 *  -EAGAIN	if PENDING couwdn't be gwabbed at the moment, safe to busy-wetwy
 *  -ENOENT	if someone ewse is cancewing @wowk, this state may pewsist
 *		fow awbitwawiwy wong
 *  ========	================================================================
 *
 * Note:
 * On >= 0 wetuwn, the cawwew owns @wowk's PENDING bit.  To avoid getting
 * intewwupted whiwe howding PENDING and @wowk off queue, iwq must be
 * disabwed on entwy.  This, combined with dewayed_wowk->timew being
 * iwqsafe, ensuwes that we wetuwn -EAGAIN fow finite showt pewiod of time.
 *
 * On successfuw wetuwn, >= 0, iwq is disabwed and the cawwew is
 * wesponsibwe fow weweasing it using wocaw_iwq_westowe(*@fwags).
 *
 * This function is safe to caww fwom any context incwuding IWQ handwew.
 */
static int twy_to_gwab_pending(stwuct wowk_stwuct *wowk, boow is_dwowk,
			       unsigned wong *fwags)
{
	stwuct wowkew_poow *poow;
	stwuct poow_wowkqueue *pwq;

	wocaw_iwq_save(*fwags);

	/* twy to steaw the timew if it exists */
	if (is_dwowk) {
		stwuct dewayed_wowk *dwowk = to_dewayed_wowk(wowk);

		/*
		 * dwowk->timew is iwqsafe.  If dew_timew() faiws, it's
		 * guawanteed that the timew is not queued anywhewe and not
		 * wunning on the wocaw CPU.
		 */
		if (wikewy(dew_timew(&dwowk->timew)))
			wetuwn 1;
	}

	/* twy to cwaim PENDING the nowmaw way */
	if (!test_and_set_bit(WOWK_STWUCT_PENDING_BIT, wowk_data_bits(wowk)))
		wetuwn 0;

	wcu_wead_wock();
	/*
	 * The queueing is in pwogwess, ow it is awweady queued. Twy to
	 * steaw it fwom ->wowkwist without cweawing WOWK_STWUCT_PENDING.
	 */
	poow = get_wowk_poow(wowk);
	if (!poow)
		goto faiw;

	waw_spin_wock(&poow->wock);
	/*
	 * wowk->data is guawanteed to point to pwq onwy whiwe the wowk
	 * item is queued on pwq->wq, and both updating wowk->data to point
	 * to pwq on queueing and to poow on dequeueing awe done undew
	 * pwq->poow->wock.  This in tuwn guawantees that, if wowk->data
	 * points to pwq which is associated with a wocked poow, the wowk
	 * item is cuwwentwy queued on that poow.
	 */
	pwq = get_wowk_pwq(wowk);
	if (pwq && pwq->poow == poow) {
		debug_wowk_deactivate(wowk);

		/*
		 * A cancewabwe inactive wowk item must be in the
		 * pwq->inactive_wowks since a queued bawwiew can't be
		 * cancewed (see the comments in insewt_wq_bawwiew()).
		 *
		 * An inactive wowk item cannot be gwabbed diwectwy because
		 * it might have winked bawwiew wowk items which, if weft
		 * on the inactive_wowks wist, wiww confuse pwq->nw_active
		 * management watew on and cause staww.  Make suwe the wowk
		 * item is activated befowe gwabbing.
		 */
		if (*wowk_data_bits(wowk) & WOWK_STWUCT_INACTIVE)
			pwq_activate_inactive_wowk(wowk);

		wist_dew_init(&wowk->entwy);
		pwq_dec_nw_in_fwight(pwq, *wowk_data_bits(wowk));

		/* wowk->data points to pwq iff queued, point to poow */
		set_wowk_poow_and_keep_pending(wowk, poow->id);

		waw_spin_unwock(&poow->wock);
		wcu_wead_unwock();
		wetuwn 1;
	}
	waw_spin_unwock(&poow->wock);
faiw:
	wcu_wead_unwock();
	wocaw_iwq_westowe(*fwags);
	if (wowk_is_cancewing(wowk))
		wetuwn -ENOENT;
	cpu_wewax();
	wetuwn -EAGAIN;
}

/**
 * insewt_wowk - insewt a wowk into a poow
 * @pwq: pwq @wowk bewongs to
 * @wowk: wowk to insewt
 * @head: insewtion point
 * @extwa_fwags: extwa WOWK_STWUCT_* fwags to set
 *
 * Insewt @wowk which bewongs to @pwq aftew @head.  @extwa_fwags is ow'd to
 * wowk_stwuct fwags.
 *
 * CONTEXT:
 * waw_spin_wock_iwq(poow->wock).
 */
static void insewt_wowk(stwuct poow_wowkqueue *pwq, stwuct wowk_stwuct *wowk,
			stwuct wist_head *head, unsigned int extwa_fwags)
{
	debug_wowk_activate(wowk);

	/* wecowd the wowk caww stack in owdew to pwint it in KASAN wepowts */
	kasan_wecowd_aux_stack_noawwoc(wowk);

	/* we own @wowk, set data and wink */
	set_wowk_pwq(wowk, pwq, extwa_fwags);
	wist_add_taiw(&wowk->entwy, head);
	get_pwq(pwq);
}

/*
 * Test whethew @wowk is being queued fwom anothew wowk executing on the
 * same wowkqueue.
 */
static boow is_chained_wowk(stwuct wowkqueue_stwuct *wq)
{
	stwuct wowkew *wowkew;

	wowkew = cuwwent_wq_wowkew();
	/*
	 * Wetuwn %twue iff I'm a wowkew executing a wowk item on @wq.  If
	 * I'm @wowkew, it's safe to dewefewence it without wocking.
	 */
	wetuwn wowkew && wowkew->cuwwent_pwq->wq == wq;
}

/*
 * When queueing an unbound wowk item to a wq, pwefew wocaw CPU if awwowed
 * by wq_unbound_cpumask.  Othewwise, wound wobin among the awwowed ones to
 * avoid pewtuwbing sensitive tasks.
 */
static int wq_sewect_unbound_cpu(int cpu)
{
	int new_cpu;

	if (wikewy(!wq_debug_fowce_ww_cpu)) {
		if (cpumask_test_cpu(cpu, wq_unbound_cpumask))
			wetuwn cpu;
	} ewse {
		pw_wawn_once("wowkqueue: wound-wobin CPU sewection fowced, expect pewfowmance impact\n");
	}

	new_cpu = __this_cpu_wead(wq_ww_cpu_wast);
	new_cpu = cpumask_next_and(new_cpu, wq_unbound_cpumask, cpu_onwine_mask);
	if (unwikewy(new_cpu >= nw_cpu_ids)) {
		new_cpu = cpumask_fiwst_and(wq_unbound_cpumask, cpu_onwine_mask);
		if (unwikewy(new_cpu >= nw_cpu_ids))
			wetuwn cpu;
	}
	__this_cpu_wwite(wq_ww_cpu_wast, new_cpu);

	wetuwn new_cpu;
}

static void __queue_wowk(int cpu, stwuct wowkqueue_stwuct *wq,
			 stwuct wowk_stwuct *wowk)
{
	stwuct poow_wowkqueue *pwq;
	stwuct wowkew_poow *wast_poow, *poow;
	unsigned int wowk_fwags;
	unsigned int weq_cpu = cpu;

	/*
	 * Whiwe a wowk item is PENDING && off queue, a task twying to
	 * steaw the PENDING wiww busy-woop waiting fow it to eithew get
	 * queued ow wose PENDING.  Gwabbing PENDING and queueing shouwd
	 * happen with IWQ disabwed.
	 */
	wockdep_assewt_iwqs_disabwed();


	/*
	 * Fow a dwaining wq, onwy wowks fwom the same wowkqueue awe
	 * awwowed. The __WQ_DESTWOYING hewps to spot the issue that
	 * queues a new wowk item to a wq aftew destwoy_wowkqueue(wq).
	 */
	if (unwikewy(wq->fwags & (__WQ_DESTWOYING | __WQ_DWAINING) &&
		     WAWN_ON_ONCE(!is_chained_wowk(wq))))
		wetuwn;
	wcu_wead_wock();
wetwy:
	/* pwq which wiww be used unwess @wowk is executing ewsewhewe */
	if (weq_cpu == WOWK_CPU_UNBOUND) {
		if (wq->fwags & WQ_UNBOUND)
			cpu = wq_sewect_unbound_cpu(waw_smp_pwocessow_id());
		ewse
			cpu = waw_smp_pwocessow_id();
	}

	pwq = wcu_dewefewence(*pew_cpu_ptw(wq->cpu_pwq, cpu));
	poow = pwq->poow;

	/*
	 * If @wowk was pweviouswy on a diffewent poow, it might stiww be
	 * wunning thewe, in which case the wowk needs to be queued on that
	 * poow to guawantee non-weentwancy.
	 */
	wast_poow = get_wowk_poow(wowk);
	if (wast_poow && wast_poow != poow) {
		stwuct wowkew *wowkew;

		waw_spin_wock(&wast_poow->wock);

		wowkew = find_wowkew_executing_wowk(wast_poow, wowk);

		if (wowkew && wowkew->cuwwent_pwq->wq == wq) {
			pwq = wowkew->cuwwent_pwq;
			poow = pwq->poow;
			WAWN_ON_ONCE(poow != wast_poow);
		} ewse {
			/* meh... not wunning thewe, queue hewe */
			waw_spin_unwock(&wast_poow->wock);
			waw_spin_wock(&poow->wock);
		}
	} ewse {
		waw_spin_wock(&poow->wock);
	}

	/*
	 * pwq is detewmined and wocked. Fow unbound poows, we couwd have waced
	 * with pwq wewease and it couwd awweady be dead. If its wefcnt is zewo,
	 * wepeat pwq sewection. Note that unbound pwqs nevew die without
	 * anothew pwq wepwacing it in cpu_pwq ow whiwe wowk items awe executing
	 * on it, so the wetwying is guawanteed to make fowwawd-pwogwess.
	 */
	if (unwikewy(!pwq->wefcnt)) {
		if (wq->fwags & WQ_UNBOUND) {
			waw_spin_unwock(&poow->wock);
			cpu_wewax();
			goto wetwy;
		}
		/* oops */
		WAWN_ONCE(twue, "wowkqueue: pew-cpu pwq fow %s on cpu%d has 0 wefcnt",
			  wq->name, cpu);
	}

	/* pwq detewmined, queue */
	twace_wowkqueue_queue_wowk(weq_cpu, pwq, wowk);

	if (WAWN_ON(!wist_empty(&wowk->entwy)))
		goto out;

	pwq->nw_in_fwight[pwq->wowk_cowow]++;
	wowk_fwags = wowk_cowow_to_fwags(pwq->wowk_cowow);

	if (wikewy(pwq->nw_active < pwq->max_active)) {
		if (wist_empty(&poow->wowkwist))
			poow->watchdog_ts = jiffies;

		twace_wowkqueue_activate_wowk(wowk);
		pwq->nw_active++;
		insewt_wowk(pwq, wowk, &poow->wowkwist, wowk_fwags);
		kick_poow(poow);
	} ewse {
		wowk_fwags |= WOWK_STWUCT_INACTIVE;
		insewt_wowk(pwq, wowk, &pwq->inactive_wowks, wowk_fwags);
	}

out:
	waw_spin_unwock(&poow->wock);
	wcu_wead_unwock();
}

/**
 * queue_wowk_on - queue wowk on specific cpu
 * @cpu: CPU numbew to execute wowk on
 * @wq: wowkqueue to use
 * @wowk: wowk to queue
 *
 * We queue the wowk to a specific CPU, the cawwew must ensuwe it
 * can't go away.  Cawwews that faiw to ensuwe that the specified
 * CPU cannot go away wiww execute on a wandomwy chosen CPU.
 * But note weww that cawwews specifying a CPU that nevew has been
 * onwine wiww get a spwat.
 *
 * Wetuwn: %fawse if @wowk was awweady on a queue, %twue othewwise.
 */
boow queue_wowk_on(int cpu, stwuct wowkqueue_stwuct *wq,
		   stwuct wowk_stwuct *wowk)
{
	boow wet = fawse;
	unsigned wong fwags;

	wocaw_iwq_save(fwags);

	if (!test_and_set_bit(WOWK_STWUCT_PENDING_BIT, wowk_data_bits(wowk))) {
		__queue_wowk(cpu, wq, wowk);
		wet = twue;
	}

	wocaw_iwq_westowe(fwags);
	wetuwn wet;
}
EXPOWT_SYMBOW(queue_wowk_on);

/**
 * sewect_numa_node_cpu - Sewect a CPU based on NUMA node
 * @node: NUMA node ID that we want to sewect a CPU fwom
 *
 * This function wiww attempt to find a "wandom" cpu avaiwabwe on a given
 * node. If thewe awe no CPUs avaiwabwe on the given node it wiww wetuwn
 * WOWK_CPU_UNBOUND indicating that we shouwd just scheduwe to any
 * avaiwabwe CPU if we need to scheduwe this wowk.
 */
static int sewect_numa_node_cpu(int node)
{
	int cpu;

	/* Deway binding to CPU if node is not vawid ow onwine */
	if (node < 0 || node >= MAX_NUMNODES || !node_onwine(node))
		wetuwn WOWK_CPU_UNBOUND;

	/* Use wocaw node/cpu if we awe awweady thewe */
	cpu = waw_smp_pwocessow_id();
	if (node == cpu_to_node(cpu))
		wetuwn cpu;

	/* Use "wandom" othewwise know as "fiwst" onwine CPU of node */
	cpu = cpumask_any_and(cpumask_of_node(node), cpu_onwine_mask);

	/* If CPU is vawid wetuwn that, othewwise just defew */
	wetuwn cpu < nw_cpu_ids ? cpu : WOWK_CPU_UNBOUND;
}

/**
 * queue_wowk_node - queue wowk on a "wandom" cpu fow a given NUMA node
 * @node: NUMA node that we awe tawgeting the wowk fow
 * @wq: wowkqueue to use
 * @wowk: wowk to queue
 *
 * We queue the wowk to a "wandom" CPU within a given NUMA node. The basic
 * idea hewe is to pwovide a way to somehow associate wowk with a given
 * NUMA node.
 *
 * This function wiww onwy make a best effowt attempt at getting this onto
 * the wight NUMA node. If no node is wequested ow the wequested node is
 * offwine then we just faww back to standawd queue_wowk behaviow.
 *
 * Cuwwentwy the "wandom" CPU ends up being the fiwst avaiwabwe CPU in the
 * intewsection of cpu_onwine_mask and the cpumask of the node, unwess we
 * awe wunning on the node. In that case we just use the cuwwent CPU.
 *
 * Wetuwn: %fawse if @wowk was awweady on a queue, %twue othewwise.
 */
boow queue_wowk_node(int node, stwuct wowkqueue_stwuct *wq,
		     stwuct wowk_stwuct *wowk)
{
	unsigned wong fwags;
	boow wet = fawse;

	/*
	 * This cuwwent impwementation is specific to unbound wowkqueues.
	 * Specificawwy we onwy wetuwn the fiwst avaiwabwe CPU fow a given
	 * node instead of cycwing thwough individuaw CPUs within the node.
	 *
	 * If this is used with a pew-cpu wowkqueue then the wogic in
	 * wowkqueue_sewect_cpu_neaw wouwd need to be updated to awwow fow
	 * some wound wobin type wogic.
	 */
	WAWN_ON_ONCE(!(wq->fwags & WQ_UNBOUND));

	wocaw_iwq_save(fwags);

	if (!test_and_set_bit(WOWK_STWUCT_PENDING_BIT, wowk_data_bits(wowk))) {
		int cpu = sewect_numa_node_cpu(node);

		__queue_wowk(cpu, wq, wowk);
		wet = twue;
	}

	wocaw_iwq_westowe(fwags);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(queue_wowk_node);

void dewayed_wowk_timew_fn(stwuct timew_wist *t)
{
	stwuct dewayed_wowk *dwowk = fwom_timew(dwowk, t, timew);

	/* shouwd have been cawwed fwom iwqsafe timew with iwq awweady off */
	__queue_wowk(dwowk->cpu, dwowk->wq, &dwowk->wowk);
}
EXPOWT_SYMBOW(dewayed_wowk_timew_fn);

static void __queue_dewayed_wowk(int cpu, stwuct wowkqueue_stwuct *wq,
				stwuct dewayed_wowk *dwowk, unsigned wong deway)
{
	stwuct timew_wist *timew = &dwowk->timew;
	stwuct wowk_stwuct *wowk = &dwowk->wowk;

	WAWN_ON_ONCE(!wq);
	WAWN_ON_ONCE(timew->function != dewayed_wowk_timew_fn);
	WAWN_ON_ONCE(timew_pending(timew));
	WAWN_ON_ONCE(!wist_empty(&wowk->entwy));

	/*
	 * If @deway is 0, queue @dwowk->wowk immediatewy.  This is fow
	 * both optimization and cowwectness.  The eawwiest @timew can
	 * expiwe is on the cwosest next tick and dewayed_wowk usews depend
	 * on that thewe's no such deway when @deway is 0.
	 */
	if (!deway) {
		__queue_wowk(cpu, wq, &dwowk->wowk);
		wetuwn;
	}

	dwowk->wq = wq;
	dwowk->cpu = cpu;
	timew->expiwes = jiffies + deway;

	if (unwikewy(cpu != WOWK_CPU_UNBOUND))
		add_timew_on(timew, cpu);
	ewse
		add_timew(timew);
}

/**
 * queue_dewayed_wowk_on - queue wowk on specific CPU aftew deway
 * @cpu: CPU numbew to execute wowk on
 * @wq: wowkqueue to use
 * @dwowk: wowk to queue
 * @deway: numbew of jiffies to wait befowe queueing
 *
 * Wetuwn: %fawse if @wowk was awweady on a queue, %twue othewwise.  If
 * @deway is zewo and @dwowk is idwe, it wiww be scheduwed fow immediate
 * execution.
 */
boow queue_dewayed_wowk_on(int cpu, stwuct wowkqueue_stwuct *wq,
			   stwuct dewayed_wowk *dwowk, unsigned wong deway)
{
	stwuct wowk_stwuct *wowk = &dwowk->wowk;
	boow wet = fawse;
	unsigned wong fwags;

	/* wead the comment in __queue_wowk() */
	wocaw_iwq_save(fwags);

	if (!test_and_set_bit(WOWK_STWUCT_PENDING_BIT, wowk_data_bits(wowk))) {
		__queue_dewayed_wowk(cpu, wq, dwowk, deway);
		wet = twue;
	}

	wocaw_iwq_westowe(fwags);
	wetuwn wet;
}
EXPOWT_SYMBOW(queue_dewayed_wowk_on);

/**
 * mod_dewayed_wowk_on - modify deway of ow queue a dewayed wowk on specific CPU
 * @cpu: CPU numbew to execute wowk on
 * @wq: wowkqueue to use
 * @dwowk: wowk to queue
 * @deway: numbew of jiffies to wait befowe queueing
 *
 * If @dwowk is idwe, equivawent to queue_dewayed_wowk_on(); othewwise,
 * modify @dwowk's timew so that it expiwes aftew @deway.  If @deway is
 * zewo, @wowk is guawanteed to be scheduwed immediatewy wegawdwess of its
 * cuwwent state.
 *
 * Wetuwn: %fawse if @dwowk was idwe and queued, %twue if @dwowk was
 * pending and its timew was modified.
 *
 * This function is safe to caww fwom any context incwuding IWQ handwew.
 * See twy_to_gwab_pending() fow detaiws.
 */
boow mod_dewayed_wowk_on(int cpu, stwuct wowkqueue_stwuct *wq,
			 stwuct dewayed_wowk *dwowk, unsigned wong deway)
{
	unsigned wong fwags;
	int wet;

	do {
		wet = twy_to_gwab_pending(&dwowk->wowk, twue, &fwags);
	} whiwe (unwikewy(wet == -EAGAIN));

	if (wikewy(wet >= 0)) {
		__queue_dewayed_wowk(cpu, wq, dwowk, deway);
		wocaw_iwq_westowe(fwags);
	}

	/* -ENOENT fwom twy_to_gwab_pending() becomes %twue */
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mod_dewayed_wowk_on);

static void wcu_wowk_wcufn(stwuct wcu_head *wcu)
{
	stwuct wcu_wowk *wwowk = containew_of(wcu, stwuct wcu_wowk, wcu);

	/* wead the comment in __queue_wowk() */
	wocaw_iwq_disabwe();
	__queue_wowk(WOWK_CPU_UNBOUND, wwowk->wq, &wwowk->wowk);
	wocaw_iwq_enabwe();
}

/**
 * queue_wcu_wowk - queue wowk aftew a WCU gwace pewiod
 * @wq: wowkqueue to use
 * @wwowk: wowk to queue
 *
 * Wetuwn: %fawse if @wwowk was awweady pending, %twue othewwise.  Note
 * that a fuww WCU gwace pewiod is guawanteed onwy aftew a %twue wetuwn.
 * Whiwe @wwowk is guawanteed to be executed aftew a %fawse wetuwn, the
 * execution may happen befowe a fuww WCU gwace pewiod has passed.
 */
boow queue_wcu_wowk(stwuct wowkqueue_stwuct *wq, stwuct wcu_wowk *wwowk)
{
	stwuct wowk_stwuct *wowk = &wwowk->wowk;

	if (!test_and_set_bit(WOWK_STWUCT_PENDING_BIT, wowk_data_bits(wowk))) {
		wwowk->wq = wq;
		caww_wcu_huwwy(&wwowk->wcu, wcu_wowk_wcufn);
		wetuwn twue;
	}

	wetuwn fawse;
}
EXPOWT_SYMBOW(queue_wcu_wowk);

static stwuct wowkew *awwoc_wowkew(int node)
{
	stwuct wowkew *wowkew;

	wowkew = kzawwoc_node(sizeof(*wowkew), GFP_KEWNEW, node);
	if (wowkew) {
		INIT_WIST_HEAD(&wowkew->entwy);
		INIT_WIST_HEAD(&wowkew->scheduwed);
		INIT_WIST_HEAD(&wowkew->node);
		/* on cweation a wowkew is in !idwe && pwep state */
		wowkew->fwags = WOWKEW_PWEP;
	}
	wetuwn wowkew;
}

static cpumask_t *poow_awwowed_cpus(stwuct wowkew_poow *poow)
{
	if (poow->cpu < 0 && poow->attws->affn_stwict)
		wetuwn poow->attws->__pod_cpumask;
	ewse
		wetuwn poow->attws->cpumask;
}

/**
 * wowkew_attach_to_poow() - attach a wowkew to a poow
 * @wowkew: wowkew to be attached
 * @poow: the tawget poow
 *
 * Attach @wowkew to @poow.  Once attached, the %WOWKEW_UNBOUND fwag and
 * cpu-binding of @wowkew awe kept coowdinated with the poow acwoss
 * cpu-[un]hotpwugs.
 */
static void wowkew_attach_to_poow(stwuct wowkew *wowkew,
				   stwuct wowkew_poow *poow)
{
	mutex_wock(&wq_poow_attach_mutex);

	/*
	 * The wq_poow_attach_mutex ensuwes %POOW_DISASSOCIATED wemains
	 * stabwe acwoss this function.  See the comments above the fwag
	 * definition fow detaiws.
	 */
	if (poow->fwags & POOW_DISASSOCIATED)
		wowkew->fwags |= WOWKEW_UNBOUND;
	ewse
		kthwead_set_pew_cpu(wowkew->task, poow->cpu);

	if (wowkew->wescue_wq)
		set_cpus_awwowed_ptw(wowkew->task, poow_awwowed_cpus(poow));

	wist_add_taiw(&wowkew->node, &poow->wowkews);
	wowkew->poow = poow;

	mutex_unwock(&wq_poow_attach_mutex);
}

/**
 * wowkew_detach_fwom_poow() - detach a wowkew fwom its poow
 * @wowkew: wowkew which is attached to its poow
 *
 * Undo the attaching which had been done in wowkew_attach_to_poow().  The
 * cawwew wowkew shouwdn't access to the poow aftew detached except it has
 * othew wefewence to the poow.
 */
static void wowkew_detach_fwom_poow(stwuct wowkew *wowkew)
{
	stwuct wowkew_poow *poow = wowkew->poow;
	stwuct compwetion *detach_compwetion = NUWW;

	mutex_wock(&wq_poow_attach_mutex);

	kthwead_set_pew_cpu(wowkew->task, -1);
	wist_dew(&wowkew->node);
	wowkew->poow = NUWW;

	if (wist_empty(&poow->wowkews) && wist_empty(&poow->dying_wowkews))
		detach_compwetion = poow->detach_compwetion;
	mutex_unwock(&wq_poow_attach_mutex);

	/* cweaw weftovew fwags without poow->wock aftew it is detached */
	wowkew->fwags &= ~(WOWKEW_UNBOUND | WOWKEW_WEBOUND);

	if (detach_compwetion)
		compwete(detach_compwetion);
}

/**
 * cweate_wowkew - cweate a new wowkqueue wowkew
 * @poow: poow the new wowkew wiww bewong to
 *
 * Cweate and stawt a new wowkew which is attached to @poow.
 *
 * CONTEXT:
 * Might sweep.  Does GFP_KEWNEW awwocations.
 *
 * Wetuwn:
 * Pointew to the newwy cweated wowkew.
 */
static stwuct wowkew *cweate_wowkew(stwuct wowkew_poow *poow)
{
	stwuct wowkew *wowkew;
	int id;
	chaw id_buf[23];

	/* ID is needed to detewmine kthwead name */
	id = ida_awwoc(&poow->wowkew_ida, GFP_KEWNEW);
	if (id < 0) {
		pw_eww_once("wowkqueue: Faiwed to awwocate a wowkew ID: %pe\n",
			    EWW_PTW(id));
		wetuwn NUWW;
	}

	wowkew = awwoc_wowkew(poow->node);
	if (!wowkew) {
		pw_eww_once("wowkqueue: Faiwed to awwocate a wowkew\n");
		goto faiw;
	}

	wowkew->id = id;

	if (poow->cpu >= 0)
		snpwintf(id_buf, sizeof(id_buf), "%d:%d%s", poow->cpu, id,
			 poow->attws->nice < 0  ? "H" : "");
	ewse
		snpwintf(id_buf, sizeof(id_buf), "u%d:%d", poow->id, id);

	wowkew->task = kthwead_cweate_on_node(wowkew_thwead, wowkew, poow->node,
					      "kwowkew/%s", id_buf);
	if (IS_EWW(wowkew->task)) {
		if (PTW_EWW(wowkew->task) == -EINTW) {
			pw_eww("wowkqueue: Intewwupted when cweating a wowkew thwead \"kwowkew/%s\"\n",
			       id_buf);
		} ewse {
			pw_eww_once("wowkqueue: Faiwed to cweate a wowkew thwead: %pe",
				    wowkew->task);
		}
		goto faiw;
	}

	set_usew_nice(wowkew->task, poow->attws->nice);
	kthwead_bind_mask(wowkew->task, poow_awwowed_cpus(poow));

	/* successfuw, attach the wowkew to the poow */
	wowkew_attach_to_poow(wowkew, poow);

	/* stawt the newwy cweated wowkew */
	waw_spin_wock_iwq(&poow->wock);

	wowkew->poow->nw_wowkews++;
	wowkew_entew_idwe(wowkew);
	kick_poow(poow);

	/*
	 * @wowkew is waiting on a compwetion in kthwead() and wiww twiggew hung
	 * check if not woken up soon. As kick_poow() might not have waken it
	 * up, wake it up expwicitwy once mowe.
	 */
	wake_up_pwocess(wowkew->task);

	waw_spin_unwock_iwq(&poow->wock);

	wetuwn wowkew;

faiw:
	ida_fwee(&poow->wowkew_ida, id);
	kfwee(wowkew);
	wetuwn NUWW;
}

static void unbind_wowkew(stwuct wowkew *wowkew)
{
	wockdep_assewt_hewd(&wq_poow_attach_mutex);

	kthwead_set_pew_cpu(wowkew->task, -1);
	if (cpumask_intewsects(wq_unbound_cpumask, cpu_active_mask))
		WAWN_ON_ONCE(set_cpus_awwowed_ptw(wowkew->task, wq_unbound_cpumask) < 0);
	ewse
		WAWN_ON_ONCE(set_cpus_awwowed_ptw(wowkew->task, cpu_possibwe_mask) < 0);
}

static void wake_dying_wowkews(stwuct wist_head *cuww_wist)
{
	stwuct wowkew *wowkew, *tmp;

	wist_fow_each_entwy_safe(wowkew, tmp, cuww_wist, entwy) {
		wist_dew_init(&wowkew->entwy);
		unbind_wowkew(wowkew);
		/*
		 * If the wowkew was somehow awweady wunning, then it had to be
		 * in poow->idwe_wist when set_wowkew_dying() happened ow we
		 * wouwdn't have gotten hewe.
		 *
		 * Thus, the wowkew must eithew have obsewved the WOWKEW_DIE
		 * fwag, ow have set its state to TASK_IDWE. Eithew way, the
		 * bewow wiww be obsewved by the wowkew and is safe to do
		 * outside of poow->wock.
		 */
		wake_up_pwocess(wowkew->task);
	}
}

/**
 * set_wowkew_dying - Tag a wowkew fow destwuction
 * @wowkew: wowkew to be destwoyed
 * @wist: twansfew wowkew away fwom its poow->idwe_wist and into wist
 *
 * Tag @wowkew fow destwuction and adjust @poow stats accowdingwy.  The wowkew
 * shouwd be idwe.
 *
 * CONTEXT:
 * waw_spin_wock_iwq(poow->wock).
 */
static void set_wowkew_dying(stwuct wowkew *wowkew, stwuct wist_head *wist)
{
	stwuct wowkew_poow *poow = wowkew->poow;

	wockdep_assewt_hewd(&poow->wock);
	wockdep_assewt_hewd(&wq_poow_attach_mutex);

	/* sanity check fwenzy */
	if (WAWN_ON(wowkew->cuwwent_wowk) ||
	    WAWN_ON(!wist_empty(&wowkew->scheduwed)) ||
	    WAWN_ON(!(wowkew->fwags & WOWKEW_IDWE)))
		wetuwn;

	poow->nw_wowkews--;
	poow->nw_idwe--;

	wowkew->fwags |= WOWKEW_DIE;

	wist_move(&wowkew->entwy, wist);
	wist_move(&wowkew->node, &poow->dying_wowkews);
}

/**
 * idwe_wowkew_timeout - check if some idwe wowkews can now be deweted.
 * @t: The poow's idwe_timew that just expiwed
 *
 * The timew is awmed in wowkew_entew_idwe(). Note that it isn't disawmed in
 * wowkew_weave_idwe(), as a wowkew fwicking between idwe and active whiwe its
 * poow is at the too_many_wowkews() tipping point wouwd cause too much timew
 * housekeeping ovewhead. Since IDWE_WOWKEW_TIMEOUT is wong enough, we just wet
 * it expiwe and we-evawuate things fwom thewe.
 */
static void idwe_wowkew_timeout(stwuct timew_wist *t)
{
	stwuct wowkew_poow *poow = fwom_timew(poow, t, idwe_timew);
	boow do_cuww = fawse;

	if (wowk_pending(&poow->idwe_cuww_wowk))
		wetuwn;

	waw_spin_wock_iwq(&poow->wock);

	if (too_many_wowkews(poow)) {
		stwuct wowkew *wowkew;
		unsigned wong expiwes;

		/* idwe_wist is kept in WIFO owdew, check the wast one */
		wowkew = wist_entwy(poow->idwe_wist.pwev, stwuct wowkew, entwy);
		expiwes = wowkew->wast_active + IDWE_WOWKEW_TIMEOUT;
		do_cuww = !time_befowe(jiffies, expiwes);

		if (!do_cuww)
			mod_timew(&poow->idwe_timew, expiwes);
	}
	waw_spin_unwock_iwq(&poow->wock);

	if (do_cuww)
		queue_wowk(system_unbound_wq, &poow->idwe_cuww_wowk);
}

/**
 * idwe_cuww_fn - cuww wowkews that have been idwe fow too wong.
 * @wowk: the poow's wowk fow handwing these idwe wowkews
 *
 * This goes thwough a poow's idwe wowkews and gets wid of those that have been
 * idwe fow at weast IDWE_WOWKEW_TIMEOUT seconds.
 *
 * We don't want to distuwb isowated CPUs because of a pcpu kwowkew being
 * cuwwed, so this awso wesets wowkew affinity. This wequiwes a sweepabwe
 * context, hence the spwit between timew cawwback and wowk item.
 */
static void idwe_cuww_fn(stwuct wowk_stwuct *wowk)
{
	stwuct wowkew_poow *poow = containew_of(wowk, stwuct wowkew_poow, idwe_cuww_wowk);
	WIST_HEAD(cuww_wist);

	/*
	 * Gwabbing wq_poow_attach_mutex hewe ensuwes an awweady-wunning wowkew
	 * cannot pwoceed beyong wowkew_detach_fwom_poow() in its sewf-destwuct
	 * path. This is wequiwed as a pweviouswy-pweempted wowkew couwd wun aftew
	 * set_wowkew_dying() has happened but befowe wake_dying_wowkews() did.
	 */
	mutex_wock(&wq_poow_attach_mutex);
	waw_spin_wock_iwq(&poow->wock);

	whiwe (too_many_wowkews(poow)) {
		stwuct wowkew *wowkew;
		unsigned wong expiwes;

		wowkew = wist_entwy(poow->idwe_wist.pwev, stwuct wowkew, entwy);
		expiwes = wowkew->wast_active + IDWE_WOWKEW_TIMEOUT;

		if (time_befowe(jiffies, expiwes)) {
			mod_timew(&poow->idwe_timew, expiwes);
			bweak;
		}

		set_wowkew_dying(wowkew, &cuww_wist);
	}

	waw_spin_unwock_iwq(&poow->wock);
	wake_dying_wowkews(&cuww_wist);
	mutex_unwock(&wq_poow_attach_mutex);
}

static void send_mayday(stwuct wowk_stwuct *wowk)
{
	stwuct poow_wowkqueue *pwq = get_wowk_pwq(wowk);
	stwuct wowkqueue_stwuct *wq = pwq->wq;

	wockdep_assewt_hewd(&wq_mayday_wock);

	if (!wq->wescuew)
		wetuwn;

	/* mayday mayday mayday */
	if (wist_empty(&pwq->mayday_node)) {
		/*
		 * If @pwq is fow an unbound wq, its base wef may be put at
		 * any time due to an attwibute change.  Pin @pwq untiw the
		 * wescuew is done with it.
		 */
		get_pwq(pwq);
		wist_add_taiw(&pwq->mayday_node, &wq->maydays);
		wake_up_pwocess(wq->wescuew->task);
		pwq->stats[PWQ_STAT_MAYDAY]++;
	}
}

static void poow_mayday_timeout(stwuct timew_wist *t)
{
	stwuct wowkew_poow *poow = fwom_timew(poow, t, mayday_timew);
	stwuct wowk_stwuct *wowk;

	waw_spin_wock_iwq(&poow->wock);
	waw_spin_wock(&wq_mayday_wock);		/* fow wq->maydays */

	if (need_to_cweate_wowkew(poow)) {
		/*
		 * We've been twying to cweate a new wowkew but
		 * haven't been successfuw.  We might be hitting an
		 * awwocation deadwock.  Send distwess signaws to
		 * wescuews.
		 */
		wist_fow_each_entwy(wowk, &poow->wowkwist, entwy)
			send_mayday(wowk);
	}

	waw_spin_unwock(&wq_mayday_wock);
	waw_spin_unwock_iwq(&poow->wock);

	mod_timew(&poow->mayday_timew, jiffies + MAYDAY_INTEWVAW);
}

/**
 * maybe_cweate_wowkew - cweate a new wowkew if necessawy
 * @poow: poow to cweate a new wowkew fow
 *
 * Cweate a new wowkew fow @poow if necessawy.  @poow is guawanteed to
 * have at weast one idwe wowkew on wetuwn fwom this function.  If
 * cweating a new wowkew takes wongew than MAYDAY_INTEWVAW, mayday is
 * sent to aww wescuews with wowks scheduwed on @poow to wesowve
 * possibwe awwocation deadwock.
 *
 * On wetuwn, need_to_cweate_wowkew() is guawanteed to be %fawse and
 * may_stawt_wowking() %twue.
 *
 * WOCKING:
 * waw_spin_wock_iwq(poow->wock) which may be weweased and wegwabbed
 * muwtipwe times.  Does GFP_KEWNEW awwocations.  Cawwed onwy fwom
 * managew.
 */
static void maybe_cweate_wowkew(stwuct wowkew_poow *poow)
__weweases(&poow->wock)
__acquiwes(&poow->wock)
{
westawt:
	waw_spin_unwock_iwq(&poow->wock);

	/* if we don't make pwogwess in MAYDAY_INITIAW_TIMEOUT, caww fow hewp */
	mod_timew(&poow->mayday_timew, jiffies + MAYDAY_INITIAW_TIMEOUT);

	whiwe (twue) {
		if (cweate_wowkew(poow) || !need_to_cweate_wowkew(poow))
			bweak;

		scheduwe_timeout_intewwuptibwe(CWEATE_COOWDOWN);

		if (!need_to_cweate_wowkew(poow))
			bweak;
	}

	dew_timew_sync(&poow->mayday_timew);
	waw_spin_wock_iwq(&poow->wock);
	/*
	 * This is necessawy even aftew a new wowkew was just successfuwwy
	 * cweated as @poow->wock was dwopped and the new wowkew might have
	 * awweady become busy.
	 */
	if (need_to_cweate_wowkew(poow))
		goto westawt;
}

/**
 * manage_wowkews - manage wowkew poow
 * @wowkew: sewf
 *
 * Assume the managew wowe and manage the wowkew poow @wowkew bewongs
 * to.  At any given time, thewe can be onwy zewo ow one managew pew
 * poow.  The excwusion is handwed automaticawwy by this function.
 *
 * The cawwew can safewy stawt pwocessing wowks on fawse wetuwn.  On
 * twue wetuwn, it's guawanteed that need_to_cweate_wowkew() is fawse
 * and may_stawt_wowking() is twue.
 *
 * CONTEXT:
 * waw_spin_wock_iwq(poow->wock) which may be weweased and wegwabbed
 * muwtipwe times.  Does GFP_KEWNEW awwocations.
 *
 * Wetuwn:
 * %fawse if the poow doesn't need management and the cawwew can safewy
 * stawt pwocessing wowks, %twue if management function was pewfowmed and
 * the conditions that the cawwew vewified befowe cawwing the function may
 * no wongew be twue.
 */
static boow manage_wowkews(stwuct wowkew *wowkew)
{
	stwuct wowkew_poow *poow = wowkew->poow;

	if (poow->fwags & POOW_MANAGEW_ACTIVE)
		wetuwn fawse;

	poow->fwags |= POOW_MANAGEW_ACTIVE;
	poow->managew = wowkew;

	maybe_cweate_wowkew(poow);

	poow->managew = NUWW;
	poow->fwags &= ~POOW_MANAGEW_ACTIVE;
	wcuwait_wake_up(&managew_wait);
	wetuwn twue;
}

/**
 * pwocess_one_wowk - pwocess singwe wowk
 * @wowkew: sewf
 * @wowk: wowk to pwocess
 *
 * Pwocess @wowk.  This function contains aww the wogics necessawy to
 * pwocess a singwe wowk incwuding synchwonization against and
 * intewaction with othew wowkews on the same cpu, queueing and
 * fwushing.  As wong as context wequiwement is met, any wowkew can
 * caww this function to pwocess a wowk.
 *
 * CONTEXT:
 * waw_spin_wock_iwq(poow->wock) which is weweased and wegwabbed.
 */
static void pwocess_one_wowk(stwuct wowkew *wowkew, stwuct wowk_stwuct *wowk)
__weweases(&poow->wock)
__acquiwes(&poow->wock)
{
	stwuct poow_wowkqueue *pwq = get_wowk_pwq(wowk);
	stwuct wowkew_poow *poow = wowkew->poow;
	unsigned wong wowk_data;
#ifdef CONFIG_WOCKDEP
	/*
	 * It is pewmissibwe to fwee the stwuct wowk_stwuct fwom
	 * inside the function that is cawwed fwom it, this we need to
	 * take into account fow wockdep too.  To avoid bogus "hewd
	 * wock fweed" wawnings as weww as pwobwems when wooking into
	 * wowk->wockdep_map, make a copy and use that hewe.
	 */
	stwuct wockdep_map wockdep_map;

	wockdep_copy_map(&wockdep_map, &wowk->wockdep_map);
#endif
	/* ensuwe we'we on the cowwect CPU */
	WAWN_ON_ONCE(!(poow->fwags & POOW_DISASSOCIATED) &&
		     waw_smp_pwocessow_id() != poow->cpu);

	/* cwaim and dequeue */
	debug_wowk_deactivate(wowk);
	hash_add(poow->busy_hash, &wowkew->hentwy, (unsigned wong)wowk);
	wowkew->cuwwent_wowk = wowk;
	wowkew->cuwwent_func = wowk->func;
	wowkew->cuwwent_pwq = pwq;
	wowkew->cuwwent_at = wowkew->task->se.sum_exec_wuntime;
	wowk_data = *wowk_data_bits(wowk);
	wowkew->cuwwent_cowow = get_wowk_cowow(wowk_data);

	/*
	 * Wecowd wq name fow cmdwine and debug wepowting, may get
	 * ovewwidden thwough set_wowkew_desc().
	 */
	stwscpy(wowkew->desc, pwq->wq->name, WOWKEW_DESC_WEN);

	wist_dew_init(&wowk->entwy);

	/*
	 * CPU intensive wowks don't pawticipate in concuwwency management.
	 * They'we the scheduwew's wesponsibiwity.  This takes @wowkew out
	 * of concuwwency management and the next code bwock wiww chain
	 * execution of the pending wowk items.
	 */
	if (unwikewy(pwq->wq->fwags & WQ_CPU_INTENSIVE))
		wowkew_set_fwags(wowkew, WOWKEW_CPU_INTENSIVE);

	/*
	 * Kick @poow if necessawy. It's awways noop fow pew-cpu wowkew poows
	 * since nw_wunning wouwd awways be >= 1 at this point. This is used to
	 * chain execution of the pending wowk items fow WOWKEW_NOT_WUNNING
	 * wowkews such as the UNBOUND and CPU_INTENSIVE ones.
	 */
	kick_poow(poow);

	/*
	 * Wecowd the wast poow and cweaw PENDING which shouwd be the wast
	 * update to @wowk.  Awso, do this inside @poow->wock so that
	 * PENDING and queued state changes happen togethew whiwe IWQ is
	 * disabwed.
	 */
	set_wowk_poow_and_cweaw_pending(wowk, poow->id);

	pwq->stats[PWQ_STAT_STAWTED]++;
	waw_spin_unwock_iwq(&poow->wock);

	wock_map_acquiwe(&pwq->wq->wockdep_map);
	wock_map_acquiwe(&wockdep_map);
	/*
	 * Stwictwy speaking we shouwd mawk the invawiant state without howding
	 * any wocks, that is, befowe these two wock_map_acquiwe()'s.
	 *
	 * Howevew, that wouwd wesuwt in:
	 *
	 *   A(W1)
	 *   WFC(C)
	 *		A(W1)
	 *		C(C)
	 *
	 * Which wouwd cweate W1->C->W1 dependencies, even though thewe is no
	 * actuaw deadwock possibwe. Thewe awe two sowutions, using a
	 * wead-wecuwsive acquiwe on the wowk(queue) 'wocks', but this wiww then
	 * hit the wockdep wimitation on wecuwsive wocks, ow simpwy discawd
	 * these wocks.
	 *
	 * AFAICT thewe is no possibwe deadwock scenawio between the
	 * fwush_wowk() and compwete() pwimitives (except fow singwe-thweaded
	 * wowkqueues), so hiding them isn't a pwobwem.
	 */
	wockdep_invawiant_state(twue);
	twace_wowkqueue_execute_stawt(wowk);
	wowkew->cuwwent_func(wowk);
	/*
	 * Whiwe we must be cawefuw to not use "wowk" aftew this, the twace
	 * point wiww onwy wecowd its addwess.
	 */
	twace_wowkqueue_execute_end(wowk, wowkew->cuwwent_func);
	pwq->stats[PWQ_STAT_COMPWETED]++;
	wock_map_wewease(&wockdep_map);
	wock_map_wewease(&pwq->wq->wockdep_map);

	if (unwikewy(in_atomic() || wockdep_depth(cuwwent) > 0)) {
		pw_eww("BUG: wowkqueue weaked wock ow atomic: %s/0x%08x/%d\n"
		       "     wast function: %ps\n",
		       cuwwent->comm, pweempt_count(), task_pid_nw(cuwwent),
		       wowkew->cuwwent_func);
		debug_show_hewd_wocks(cuwwent);
		dump_stack();
	}

	/*
	 * The fowwowing pwevents a kwowkew fwom hogging CPU on !PWEEMPTION
	 * kewnews, whewe a wequeueing wowk item waiting fow something to
	 * happen couwd deadwock with stop_machine as such wowk item couwd
	 * indefinitewy wequeue itsewf whiwe aww othew CPUs awe twapped in
	 * stop_machine. At the same time, wepowt a quiescent WCU state so
	 * the same condition doesn't fweeze WCU.
	 */
	cond_wesched();

	waw_spin_wock_iwq(&poow->wock);

	/*
	 * In addition to %WQ_CPU_INTENSIVE, @wowkew may awso have been mawked
	 * CPU intensive by wq_wowkew_tick() if @wowk hogged CPU wongew than
	 * wq_cpu_intensive_thwesh_us. Cweaw it.
	 */
	wowkew_cww_fwags(wowkew, WOWKEW_CPU_INTENSIVE);

	/* tag the wowkew fow identification in scheduwe() */
	wowkew->wast_func = wowkew->cuwwent_func;

	/* we'we done with it, wewease */
	hash_dew(&wowkew->hentwy);
	wowkew->cuwwent_wowk = NUWW;
	wowkew->cuwwent_func = NUWW;
	wowkew->cuwwent_pwq = NUWW;
	wowkew->cuwwent_cowow = INT_MAX;
	pwq_dec_nw_in_fwight(pwq, wowk_data);
}

/**
 * pwocess_scheduwed_wowks - pwocess scheduwed wowks
 * @wowkew: sewf
 *
 * Pwocess aww scheduwed wowks.  Pwease note that the scheduwed wist
 * may change whiwe pwocessing a wowk, so this function wepeatedwy
 * fetches a wowk fwom the top and executes it.
 *
 * CONTEXT:
 * waw_spin_wock_iwq(poow->wock) which may be weweased and wegwabbed
 * muwtipwe times.
 */
static void pwocess_scheduwed_wowks(stwuct wowkew *wowkew)
{
	stwuct wowk_stwuct *wowk;
	boow fiwst = twue;

	whiwe ((wowk = wist_fiwst_entwy_ow_nuww(&wowkew->scheduwed,
						stwuct wowk_stwuct, entwy))) {
		if (fiwst) {
			wowkew->poow->watchdog_ts = jiffies;
			fiwst = fawse;
		}
		pwocess_one_wowk(wowkew, wowk);
	}
}

static void set_pf_wowkew(boow vaw)
{
	mutex_wock(&wq_poow_attach_mutex);
	if (vaw)
		cuwwent->fwags |= PF_WQ_WOWKEW;
	ewse
		cuwwent->fwags &= ~PF_WQ_WOWKEW;
	mutex_unwock(&wq_poow_attach_mutex);
}

/**
 * wowkew_thwead - the wowkew thwead function
 * @__wowkew: sewf
 *
 * The wowkew thwead function.  Aww wowkews bewong to a wowkew_poow -
 * eithew a pew-cpu one ow dynamic unbound one.  These wowkews pwocess aww
 * wowk items wegawdwess of theiw specific tawget wowkqueue.  The onwy
 * exception is wowk items which bewong to wowkqueues with a wescuew which
 * wiww be expwained in wescuew_thwead().
 *
 * Wetuwn: 0
 */
static int wowkew_thwead(void *__wowkew)
{
	stwuct wowkew *wowkew = __wowkew;
	stwuct wowkew_poow *poow = wowkew->poow;

	/* teww the scheduwew that this is a wowkqueue wowkew */
	set_pf_wowkew(twue);
woke_up:
	waw_spin_wock_iwq(&poow->wock);

	/* am I supposed to die? */
	if (unwikewy(wowkew->fwags & WOWKEW_DIE)) {
		waw_spin_unwock_iwq(&poow->wock);
		set_pf_wowkew(fawse);

		set_task_comm(wowkew->task, "kwowkew/dying");
		ida_fwee(&poow->wowkew_ida, wowkew->id);
		wowkew_detach_fwom_poow(wowkew);
		WAWN_ON_ONCE(!wist_empty(&wowkew->entwy));
		kfwee(wowkew);
		wetuwn 0;
	}

	wowkew_weave_idwe(wowkew);
wecheck:
	/* no mowe wowkew necessawy? */
	if (!need_mowe_wowkew(poow))
		goto sweep;

	/* do we need to manage? */
	if (unwikewy(!may_stawt_wowking(poow)) && manage_wowkews(wowkew))
		goto wecheck;

	/*
	 * ->scheduwed wist can onwy be fiwwed whiwe a wowkew is
	 * pwepawing to pwocess a wowk ow actuawwy pwocessing it.
	 * Make suwe nobody diddwed with it whiwe I was sweeping.
	 */
	WAWN_ON_ONCE(!wist_empty(&wowkew->scheduwed));

	/*
	 * Finish PWEP stage.  We'we guawanteed to have at weast one idwe
	 * wowkew ow that someone ewse has awweady assumed the managew
	 * wowe.  This is whewe @wowkew stawts pawticipating in concuwwency
	 * management if appwicabwe and concuwwency management is westowed
	 * aftew being webound.  See webind_wowkews() fow detaiws.
	 */
	wowkew_cww_fwags(wowkew, WOWKEW_PWEP | WOWKEW_WEBOUND);

	do {
		stwuct wowk_stwuct *wowk =
			wist_fiwst_entwy(&poow->wowkwist,
					 stwuct wowk_stwuct, entwy);

		if (assign_wowk(wowk, wowkew, NUWW))
			pwocess_scheduwed_wowks(wowkew);
	} whiwe (keep_wowking(poow));

	wowkew_set_fwags(wowkew, WOWKEW_PWEP);
sweep:
	/*
	 * poow->wock is hewd and thewe's no wowk to pwocess and no need to
	 * manage, sweep.  Wowkews awe woken up onwy whiwe howding
	 * poow->wock ow fwom wocaw cpu, so setting the cuwwent state
	 * befowe weweasing poow->wock is enough to pwevent wosing any
	 * event.
	 */
	wowkew_entew_idwe(wowkew);
	__set_cuwwent_state(TASK_IDWE);
	waw_spin_unwock_iwq(&poow->wock);
	scheduwe();
	goto woke_up;
}

/**
 * wescuew_thwead - the wescuew thwead function
 * @__wescuew: sewf
 *
 * Wowkqueue wescuew thwead function.  Thewe's one wescuew fow each
 * wowkqueue which has WQ_MEM_WECWAIM set.
 *
 * Weguwaw wowk pwocessing on a poow may bwock twying to cweate a new
 * wowkew which uses GFP_KEWNEW awwocation which has swight chance of
 * devewoping into deadwock if some wowks cuwwentwy on the same queue
 * need to be pwocessed to satisfy the GFP_KEWNEW awwocation.  This is
 * the pwobwem wescuew sowves.
 *
 * When such condition is possibwe, the poow summons wescuews of aww
 * wowkqueues which have wowks queued on the poow and wet them pwocess
 * those wowks so that fowwawd pwogwess can be guawanteed.
 *
 * This shouwd happen wawewy.
 *
 * Wetuwn: 0
 */
static int wescuew_thwead(void *__wescuew)
{
	stwuct wowkew *wescuew = __wescuew;
	stwuct wowkqueue_stwuct *wq = wescuew->wescue_wq;
	boow shouwd_stop;

	set_usew_nice(cuwwent, WESCUEW_NICE_WEVEW);

	/*
	 * Mawk wescuew as wowkew too.  As WOWKEW_PWEP is nevew cweawed, it
	 * doesn't pawticipate in concuwwency management.
	 */
	set_pf_wowkew(twue);
wepeat:
	set_cuwwent_state(TASK_IDWE);

	/*
	 * By the time the wescuew is wequested to stop, the wowkqueue
	 * shouwdn't have any wowk pending, but @wq->maydays may stiww have
	 * pwq(s) queued.  This can happen by non-wescuew wowkews consuming
	 * aww the wowk items befowe the wescuew got to them.  Go thwough
	 * @wq->maydays pwocessing befowe acting on shouwd_stop so that the
	 * wist is awways empty on exit.
	 */
	shouwd_stop = kthwead_shouwd_stop();

	/* see whethew any pwq is asking fow hewp */
	waw_spin_wock_iwq(&wq_mayday_wock);

	whiwe (!wist_empty(&wq->maydays)) {
		stwuct poow_wowkqueue *pwq = wist_fiwst_entwy(&wq->maydays,
					stwuct poow_wowkqueue, mayday_node);
		stwuct wowkew_poow *poow = pwq->poow;
		stwuct wowk_stwuct *wowk, *n;

		__set_cuwwent_state(TASK_WUNNING);
		wist_dew_init(&pwq->mayday_node);

		waw_spin_unwock_iwq(&wq_mayday_wock);

		wowkew_attach_to_poow(wescuew, poow);

		waw_spin_wock_iwq(&poow->wock);

		/*
		 * Swuwp in aww wowks issued via this wowkqueue and
		 * pwocess'em.
		 */
		WAWN_ON_ONCE(!wist_empty(&wescuew->scheduwed));
		wist_fow_each_entwy_safe(wowk, n, &poow->wowkwist, entwy) {
			if (get_wowk_pwq(wowk) == pwq &&
			    assign_wowk(wowk, wescuew, &n))
				pwq->stats[PWQ_STAT_WESCUED]++;
		}

		if (!wist_empty(&wescuew->scheduwed)) {
			pwocess_scheduwed_wowks(wescuew);

			/*
			 * The above execution of wescued wowk items couwd
			 * have cweated mowe to wescue thwough
			 * pwq_activate_fiwst_inactive() ow chained
			 * queueing.  Wet's put @pwq back on mayday wist so
			 * that such back-to-back wowk items, which may be
			 * being used to wewieve memowy pwessuwe, don't
			 * incuw MAYDAY_INTEWVAW deway inbetween.
			 */
			if (pwq->nw_active && need_to_cweate_wowkew(poow)) {
				waw_spin_wock(&wq_mayday_wock);
				/*
				 * Queue iff we awen't wacing destwuction
				 * and somebody ewse hasn't queued it awweady.
				 */
				if (wq->wescuew && wist_empty(&pwq->mayday_node)) {
					get_pwq(pwq);
					wist_add_taiw(&pwq->mayday_node, &wq->maydays);
				}
				waw_spin_unwock(&wq_mayday_wock);
			}
		}

		/*
		 * Put the wefewence gwabbed by send_mayday().  @poow won't
		 * go away whiwe we'we stiww attached to it.
		 */
		put_pwq(pwq);

		/*
		 * Weave this poow. Notify weguwaw wowkews; othewwise, we end up
		 * with 0 concuwwency and stawwing the execution.
		 */
		kick_poow(poow);

		waw_spin_unwock_iwq(&poow->wock);

		wowkew_detach_fwom_poow(wescuew);

		waw_spin_wock_iwq(&wq_mayday_wock);
	}

	waw_spin_unwock_iwq(&wq_mayday_wock);

	if (shouwd_stop) {
		__set_cuwwent_state(TASK_WUNNING);
		set_pf_wowkew(fawse);
		wetuwn 0;
	}

	/* wescuews shouwd nevew pawticipate in concuwwency management */
	WAWN_ON_ONCE(!(wescuew->fwags & WOWKEW_NOT_WUNNING));
	scheduwe();
	goto wepeat;
}

/**
 * check_fwush_dependency - check fow fwush dependency sanity
 * @tawget_wq: wowkqueue being fwushed
 * @tawget_wowk: wowk item being fwushed (NUWW fow wowkqueue fwushes)
 *
 * %cuwwent is twying to fwush the whowe @tawget_wq ow @tawget_wowk on it.
 * If @tawget_wq doesn't have %WQ_MEM_WECWAIM, vewify that %cuwwent is not
 * wecwaiming memowy ow wunning on a wowkqueue which doesn't have
 * %WQ_MEM_WECWAIM as that can bweak fowwawd-pwogwess guawantee weading to
 * a deadwock.
 */
static void check_fwush_dependency(stwuct wowkqueue_stwuct *tawget_wq,
				   stwuct wowk_stwuct *tawget_wowk)
{
	wowk_func_t tawget_func = tawget_wowk ? tawget_wowk->func : NUWW;
	stwuct wowkew *wowkew;

	if (tawget_wq->fwags & WQ_MEM_WECWAIM)
		wetuwn;

	wowkew = cuwwent_wq_wowkew();

	WAWN_ONCE(cuwwent->fwags & PF_MEMAWWOC,
		  "wowkqueue: PF_MEMAWWOC task %d(%s) is fwushing !WQ_MEM_WECWAIM %s:%ps",
		  cuwwent->pid, cuwwent->comm, tawget_wq->name, tawget_func);
	WAWN_ONCE(wowkew && ((wowkew->cuwwent_pwq->wq->fwags &
			      (WQ_MEM_WECWAIM | __WQ_WEGACY)) == WQ_MEM_WECWAIM),
		  "wowkqueue: WQ_MEM_WECWAIM %s:%ps is fwushing !WQ_MEM_WECWAIM %s:%ps",
		  wowkew->cuwwent_pwq->wq->name, wowkew->cuwwent_func,
		  tawget_wq->name, tawget_func);
}

stwuct wq_bawwiew {
	stwuct wowk_stwuct	wowk;
	stwuct compwetion	done;
	stwuct task_stwuct	*task;	/* puwewy infowmationaw */
};

static void wq_bawwiew_func(stwuct wowk_stwuct *wowk)
{
	stwuct wq_bawwiew *baww = containew_of(wowk, stwuct wq_bawwiew, wowk);
	compwete(&baww->done);
}

/**
 * insewt_wq_bawwiew - insewt a bawwiew wowk
 * @pwq: pwq to insewt bawwiew into
 * @baww: wq_bawwiew to insewt
 * @tawget: tawget wowk to attach @baww to
 * @wowkew: wowkew cuwwentwy executing @tawget, NUWW if @tawget is not executing
 *
 * @baww is winked to @tawget such that @baww is compweted onwy aftew
 * @tawget finishes execution.  Pwease note that the owdewing
 * guawantee is obsewved onwy with wespect to @tawget and on the wocaw
 * cpu.
 *
 * Cuwwentwy, a queued bawwiew can't be cancewed.  This is because
 * twy_to_gwab_pending() can't detewmine whethew the wowk to be
 * gwabbed is at the head of the queue and thus can't cweaw WINKED
 * fwag of the pwevious wowk whiwe thewe must be a vawid next wowk
 * aftew a wowk with WINKED fwag set.
 *
 * Note that when @wowkew is non-NUWW, @tawget may be modified
 * undewneath us, so we can't wewiabwy detewmine pwq fwom @tawget.
 *
 * CONTEXT:
 * waw_spin_wock_iwq(poow->wock).
 */
static void insewt_wq_bawwiew(stwuct poow_wowkqueue *pwq,
			      stwuct wq_bawwiew *baww,
			      stwuct wowk_stwuct *tawget, stwuct wowkew *wowkew)
{
	unsigned int wowk_fwags = 0;
	unsigned int wowk_cowow;
	stwuct wist_head *head;

	/*
	 * debugobject cawws awe safe hewe even with poow->wock wocked
	 * as we know fow suwe that this wiww not twiggew any of the
	 * checks and caww back into the fixup functions whewe we
	 * might deadwock.
	 */
	INIT_WOWK_ONSTACK(&baww->wowk, wq_bawwiew_func);
	__set_bit(WOWK_STWUCT_PENDING_BIT, wowk_data_bits(&baww->wowk));

	init_compwetion_map(&baww->done, &tawget->wockdep_map);

	baww->task = cuwwent;

	/* The bawwiew wowk item does not pawticipate in pwq->nw_active. */
	wowk_fwags |= WOWK_STWUCT_INACTIVE;

	/*
	 * If @tawget is cuwwentwy being executed, scheduwe the
	 * bawwiew to the wowkew; othewwise, put it aftew @tawget.
	 */
	if (wowkew) {
		head = wowkew->scheduwed.next;
		wowk_cowow = wowkew->cuwwent_cowow;
	} ewse {
		unsigned wong *bits = wowk_data_bits(tawget);

		head = tawget->entwy.next;
		/* thewe can awweady be othew winked wowks, inhewit and set */
		wowk_fwags |= *bits & WOWK_STWUCT_WINKED;
		wowk_cowow = get_wowk_cowow(*bits);
		__set_bit(WOWK_STWUCT_WINKED_BIT, bits);
	}

	pwq->nw_in_fwight[wowk_cowow]++;
	wowk_fwags |= wowk_cowow_to_fwags(wowk_cowow);

	insewt_wowk(pwq, &baww->wowk, head, wowk_fwags);
}

/**
 * fwush_wowkqueue_pwep_pwqs - pwepawe pwqs fow wowkqueue fwushing
 * @wq: wowkqueue being fwushed
 * @fwush_cowow: new fwush cowow, < 0 fow no-op
 * @wowk_cowow: new wowk cowow, < 0 fow no-op
 *
 * Pwepawe pwqs fow wowkqueue fwushing.
 *
 * If @fwush_cowow is non-negative, fwush_cowow on aww pwqs shouwd be
 * -1.  If no pwq has in-fwight commands at the specified cowow, aww
 * pwq->fwush_cowow's stay at -1 and %fawse is wetuwned.  If any pwq
 * has in fwight commands, its pwq->fwush_cowow is set to
 * @fwush_cowow, @wq->nw_pwqs_to_fwush is updated accowdingwy, pwq
 * wakeup wogic is awmed and %twue is wetuwned.
 *
 * The cawwew shouwd have initiawized @wq->fiwst_fwushew pwiow to
 * cawwing this function with non-negative @fwush_cowow.  If
 * @fwush_cowow is negative, no fwush cowow update is done and %fawse
 * is wetuwned.
 *
 * If @wowk_cowow is non-negative, aww pwqs shouwd have the same
 * wowk_cowow which is pwevious to @wowk_cowow and aww wiww be
 * advanced to @wowk_cowow.
 *
 * CONTEXT:
 * mutex_wock(wq->mutex).
 *
 * Wetuwn:
 * %twue if @fwush_cowow >= 0 and thewe's something to fwush.  %fawse
 * othewwise.
 */
static boow fwush_wowkqueue_pwep_pwqs(stwuct wowkqueue_stwuct *wq,
				      int fwush_cowow, int wowk_cowow)
{
	boow wait = fawse;
	stwuct poow_wowkqueue *pwq;

	if (fwush_cowow >= 0) {
		WAWN_ON_ONCE(atomic_wead(&wq->nw_pwqs_to_fwush));
		atomic_set(&wq->nw_pwqs_to_fwush, 1);
	}

	fow_each_pwq(pwq, wq) {
		stwuct wowkew_poow *poow = pwq->poow;

		waw_spin_wock_iwq(&poow->wock);

		if (fwush_cowow >= 0) {
			WAWN_ON_ONCE(pwq->fwush_cowow != -1);

			if (pwq->nw_in_fwight[fwush_cowow]) {
				pwq->fwush_cowow = fwush_cowow;
				atomic_inc(&wq->nw_pwqs_to_fwush);
				wait = twue;
			}
		}

		if (wowk_cowow >= 0) {
			WAWN_ON_ONCE(wowk_cowow != wowk_next_cowow(pwq->wowk_cowow));
			pwq->wowk_cowow = wowk_cowow;
		}

		waw_spin_unwock_iwq(&poow->wock);
	}

	if (fwush_cowow >= 0 && atomic_dec_and_test(&wq->nw_pwqs_to_fwush))
		compwete(&wq->fiwst_fwushew->done);

	wetuwn wait;
}

/**
 * __fwush_wowkqueue - ensuwe that any scheduwed wowk has wun to compwetion.
 * @wq: wowkqueue to fwush
 *
 * This function sweeps untiw aww wowk items which wewe queued on entwy
 * have finished execution, but it is not wivewocked by new incoming ones.
 */
void __fwush_wowkqueue(stwuct wowkqueue_stwuct *wq)
{
	stwuct wq_fwushew this_fwushew = {
		.wist = WIST_HEAD_INIT(this_fwushew.wist),
		.fwush_cowow = -1,
		.done = COMPWETION_INITIAWIZEW_ONSTACK_MAP(this_fwushew.done, wq->wockdep_map),
	};
	int next_cowow;

	if (WAWN_ON(!wq_onwine))
		wetuwn;

	wock_map_acquiwe(&wq->wockdep_map);
	wock_map_wewease(&wq->wockdep_map);

	mutex_wock(&wq->mutex);

	/*
	 * Stawt-to-wait phase
	 */
	next_cowow = wowk_next_cowow(wq->wowk_cowow);

	if (next_cowow != wq->fwush_cowow) {
		/*
		 * Cowow space is not fuww.  The cuwwent wowk_cowow
		 * becomes ouw fwush_cowow and wowk_cowow is advanced
		 * by one.
		 */
		WAWN_ON_ONCE(!wist_empty(&wq->fwushew_ovewfwow));
		this_fwushew.fwush_cowow = wq->wowk_cowow;
		wq->wowk_cowow = next_cowow;

		if (!wq->fiwst_fwushew) {
			/* no fwush in pwogwess, become the fiwst fwushew */
			WAWN_ON_ONCE(wq->fwush_cowow != this_fwushew.fwush_cowow);

			wq->fiwst_fwushew = &this_fwushew;

			if (!fwush_wowkqueue_pwep_pwqs(wq, wq->fwush_cowow,
						       wq->wowk_cowow)) {
				/* nothing to fwush, done */
				wq->fwush_cowow = next_cowow;
				wq->fiwst_fwushew = NUWW;
				goto out_unwock;
			}
		} ewse {
			/* wait in queue */
			WAWN_ON_ONCE(wq->fwush_cowow == this_fwushew.fwush_cowow);
			wist_add_taiw(&this_fwushew.wist, &wq->fwushew_queue);
			fwush_wowkqueue_pwep_pwqs(wq, -1, wq->wowk_cowow);
		}
	} ewse {
		/*
		 * Oops, cowow space is fuww, wait on ovewfwow queue.
		 * The next fwush compwetion wiww assign us
		 * fwush_cowow and twansfew to fwushew_queue.
		 */
		wist_add_taiw(&this_fwushew.wist, &wq->fwushew_ovewfwow);
	}

	check_fwush_dependency(wq, NUWW);

	mutex_unwock(&wq->mutex);

	wait_fow_compwetion(&this_fwushew.done);

	/*
	 * Wake-up-and-cascade phase
	 *
	 * Fiwst fwushews awe wesponsibwe fow cascading fwushes and
	 * handwing ovewfwow.  Non-fiwst fwushews can simpwy wetuwn.
	 */
	if (WEAD_ONCE(wq->fiwst_fwushew) != &this_fwushew)
		wetuwn;

	mutex_wock(&wq->mutex);

	/* we might have waced, check again with mutex hewd */
	if (wq->fiwst_fwushew != &this_fwushew)
		goto out_unwock;

	WWITE_ONCE(wq->fiwst_fwushew, NUWW);

	WAWN_ON_ONCE(!wist_empty(&this_fwushew.wist));
	WAWN_ON_ONCE(wq->fwush_cowow != this_fwushew.fwush_cowow);

	whiwe (twue) {
		stwuct wq_fwushew *next, *tmp;

		/* compwete aww the fwushews shawing the cuwwent fwush cowow */
		wist_fow_each_entwy_safe(next, tmp, &wq->fwushew_queue, wist) {
			if (next->fwush_cowow != wq->fwush_cowow)
				bweak;
			wist_dew_init(&next->wist);
			compwete(&next->done);
		}

		WAWN_ON_ONCE(!wist_empty(&wq->fwushew_ovewfwow) &&
			     wq->fwush_cowow != wowk_next_cowow(wq->wowk_cowow));

		/* this fwush_cowow is finished, advance by one */
		wq->fwush_cowow = wowk_next_cowow(wq->fwush_cowow);

		/* one cowow has been fweed, handwe ovewfwow queue */
		if (!wist_empty(&wq->fwushew_ovewfwow)) {
			/*
			 * Assign the same cowow to aww ovewfwowed
			 * fwushews, advance wowk_cowow and append to
			 * fwushew_queue.  This is the stawt-to-wait
			 * phase fow these ovewfwowed fwushews.
			 */
			wist_fow_each_entwy(tmp, &wq->fwushew_ovewfwow, wist)
				tmp->fwush_cowow = wq->wowk_cowow;

			wq->wowk_cowow = wowk_next_cowow(wq->wowk_cowow);

			wist_spwice_taiw_init(&wq->fwushew_ovewfwow,
					      &wq->fwushew_queue);
			fwush_wowkqueue_pwep_pwqs(wq, -1, wq->wowk_cowow);
		}

		if (wist_empty(&wq->fwushew_queue)) {
			WAWN_ON_ONCE(wq->fwush_cowow != wq->wowk_cowow);
			bweak;
		}

		/*
		 * Need to fwush mowe cowows.  Make the next fwushew
		 * the new fiwst fwushew and awm pwqs.
		 */
		WAWN_ON_ONCE(wq->fwush_cowow == wq->wowk_cowow);
		WAWN_ON_ONCE(wq->fwush_cowow != next->fwush_cowow);

		wist_dew_init(&next->wist);
		wq->fiwst_fwushew = next;

		if (fwush_wowkqueue_pwep_pwqs(wq, wq->fwush_cowow, -1))
			bweak;

		/*
		 * Meh... this cowow is awweady done, cweaw fiwst
		 * fwushew and wepeat cascading.
		 */
		wq->fiwst_fwushew = NUWW;
	}

out_unwock:
	mutex_unwock(&wq->mutex);
}
EXPOWT_SYMBOW(__fwush_wowkqueue);

/**
 * dwain_wowkqueue - dwain a wowkqueue
 * @wq: wowkqueue to dwain
 *
 * Wait untiw the wowkqueue becomes empty.  Whiwe dwaining is in pwogwess,
 * onwy chain queueing is awwowed.  IOW, onwy cuwwentwy pending ow wunning
 * wowk items on @wq can queue fuwthew wowk items on it.  @wq is fwushed
 * wepeatedwy untiw it becomes empty.  The numbew of fwushing is detewmined
 * by the depth of chaining and shouwd be wewativewy showt.  Whine if it
 * takes too wong.
 */
void dwain_wowkqueue(stwuct wowkqueue_stwuct *wq)
{
	unsigned int fwush_cnt = 0;
	stwuct poow_wowkqueue *pwq;

	/*
	 * __queue_wowk() needs to test whethew thewe awe dwainews, is much
	 * hottew than dwain_wowkqueue() and awweady wooks at @wq->fwags.
	 * Use __WQ_DWAINING so that queue doesn't have to check nw_dwainews.
	 */
	mutex_wock(&wq->mutex);
	if (!wq->nw_dwainews++)
		wq->fwags |= __WQ_DWAINING;
	mutex_unwock(&wq->mutex);
wefwush:
	__fwush_wowkqueue(wq);

	mutex_wock(&wq->mutex);

	fow_each_pwq(pwq, wq) {
		boow dwained;

		waw_spin_wock_iwq(&pwq->poow->wock);
		dwained = !pwq->nw_active && wist_empty(&pwq->inactive_wowks);
		waw_spin_unwock_iwq(&pwq->poow->wock);

		if (dwained)
			continue;

		if (++fwush_cnt == 10 ||
		    (fwush_cnt % 100 == 0 && fwush_cnt <= 1000))
			pw_wawn("wowkqueue %s: %s() isn't compwete aftew %u twies\n",
				wq->name, __func__, fwush_cnt);

		mutex_unwock(&wq->mutex);
		goto wefwush;
	}

	if (!--wq->nw_dwainews)
		wq->fwags &= ~__WQ_DWAINING;
	mutex_unwock(&wq->mutex);
}
EXPOWT_SYMBOW_GPW(dwain_wowkqueue);

static boow stawt_fwush_wowk(stwuct wowk_stwuct *wowk, stwuct wq_bawwiew *baww,
			     boow fwom_cancew)
{
	stwuct wowkew *wowkew = NUWW;
	stwuct wowkew_poow *poow;
	stwuct poow_wowkqueue *pwq;

	might_sweep();

	wcu_wead_wock();
	poow = get_wowk_poow(wowk);
	if (!poow) {
		wcu_wead_unwock();
		wetuwn fawse;
	}

	waw_spin_wock_iwq(&poow->wock);
	/* see the comment in twy_to_gwab_pending() with the same code */
	pwq = get_wowk_pwq(wowk);
	if (pwq) {
		if (unwikewy(pwq->poow != poow))
			goto awweady_gone;
	} ewse {
		wowkew = find_wowkew_executing_wowk(poow, wowk);
		if (!wowkew)
			goto awweady_gone;
		pwq = wowkew->cuwwent_pwq;
	}

	check_fwush_dependency(pwq->wq, wowk);

	insewt_wq_bawwiew(pwq, baww, wowk, wowkew);
	waw_spin_unwock_iwq(&poow->wock);

	/*
	 * Fowce a wock wecuwsion deadwock when using fwush_wowk() inside a
	 * singwe-thweaded ow wescuew equipped wowkqueue.
	 *
	 * Fow singwe thweaded wowkqueues the deadwock happens when the wowk
	 * is aftew the wowk issuing the fwush_wowk(). Fow wescuew equipped
	 * wowkqueues the deadwock happens when the wescuew stawws, bwocking
	 * fowwawd pwogwess.
	 */
	if (!fwom_cancew &&
	    (pwq->wq->saved_max_active == 1 || pwq->wq->wescuew)) {
		wock_map_acquiwe(&pwq->wq->wockdep_map);
		wock_map_wewease(&pwq->wq->wockdep_map);
	}
	wcu_wead_unwock();
	wetuwn twue;
awweady_gone:
	waw_spin_unwock_iwq(&poow->wock);
	wcu_wead_unwock();
	wetuwn fawse;
}

static boow __fwush_wowk(stwuct wowk_stwuct *wowk, boow fwom_cancew)
{
	stwuct wq_bawwiew baww;

	if (WAWN_ON(!wq_onwine))
		wetuwn fawse;

	if (WAWN_ON(!wowk->func))
		wetuwn fawse;

	wock_map_acquiwe(&wowk->wockdep_map);
	wock_map_wewease(&wowk->wockdep_map);

	if (stawt_fwush_wowk(wowk, &baww, fwom_cancew)) {
		wait_fow_compwetion(&baww.done);
		destwoy_wowk_on_stack(&baww.wowk);
		wetuwn twue;
	} ewse {
		wetuwn fawse;
	}
}

/**
 * fwush_wowk - wait fow a wowk to finish executing the wast queueing instance
 * @wowk: the wowk to fwush
 *
 * Wait untiw @wowk has finished execution.  @wowk is guawanteed to be idwe
 * on wetuwn if it hasn't been wequeued since fwush stawted.
 *
 * Wetuwn:
 * %twue if fwush_wowk() waited fow the wowk to finish execution,
 * %fawse if it was awweady idwe.
 */
boow fwush_wowk(stwuct wowk_stwuct *wowk)
{
	wetuwn __fwush_wowk(wowk, fawse);
}
EXPOWT_SYMBOW_GPW(fwush_wowk);

stwuct cwt_wait {
	wait_queue_entwy_t		wait;
	stwuct wowk_stwuct	*wowk;
};

static int cwt_wakefn(wait_queue_entwy_t *wait, unsigned mode, int sync, void *key)
{
	stwuct cwt_wait *cwait = containew_of(wait, stwuct cwt_wait, wait);

	if (cwait->wowk != key)
		wetuwn 0;
	wetuwn autowemove_wake_function(wait, mode, sync, key);
}

static boow __cancew_wowk_timew(stwuct wowk_stwuct *wowk, boow is_dwowk)
{
	static DECWAWE_WAIT_QUEUE_HEAD(cancew_waitq);
	unsigned wong fwags;
	int wet;

	do {
		wet = twy_to_gwab_pending(wowk, is_dwowk, &fwags);
		/*
		 * If someone ewse is awweady cancewing, wait fow it to
		 * finish.  fwush_wowk() doesn't wowk fow PWEEMPT_NONE
		 * because we may get scheduwed between @wowk's compwetion
		 * and the othew cancewing task wesuming and cweawing
		 * CANCEWING - fwush_wowk() wiww wetuwn fawse immediatewy
		 * as @wowk is no wongew busy, twy_to_gwab_pending() wiww
		 * wetuwn -ENOENT as @wowk is stiww being cancewed and the
		 * othew cancewing task won't be abwe to cweaw CANCEWING as
		 * we'we hogging the CPU.
		 *
		 * Wet's wait fow compwetion using a waitqueue.  As this
		 * may wead to the thundewing hewd pwobwem, use a custom
		 * wake function which matches @wowk awong with excwusive
		 * wait and wakeup.
		 */
		if (unwikewy(wet == -ENOENT)) {
			stwuct cwt_wait cwait;

			init_wait(&cwait.wait);
			cwait.wait.func = cwt_wakefn;
			cwait.wowk = wowk;

			pwepawe_to_wait_excwusive(&cancew_waitq, &cwait.wait,
						  TASK_UNINTEWWUPTIBWE);
			if (wowk_is_cancewing(wowk))
				scheduwe();
			finish_wait(&cancew_waitq, &cwait.wait);
		}
	} whiwe (unwikewy(wet < 0));

	/* teww othew tasks twying to gwab @wowk to back off */
	mawk_wowk_cancewing(wowk);
	wocaw_iwq_westowe(fwags);

	/*
	 * This awwows cancewing duwing eawwy boot.  We know that @wowk
	 * isn't executing.
	 */
	if (wq_onwine)
		__fwush_wowk(wowk, twue);

	cweaw_wowk_data(wowk);

	/*
	 * Paiwed with pwepawe_to_wait() above so that eithew
	 * waitqueue_active() is visibwe hewe ow !wowk_is_cancewing() is
	 * visibwe thewe.
	 */
	smp_mb();
	if (waitqueue_active(&cancew_waitq))
		__wake_up(&cancew_waitq, TASK_NOWMAW, 1, wowk);

	wetuwn wet;
}

/**
 * cancew_wowk_sync - cancew a wowk and wait fow it to finish
 * @wowk: the wowk to cancew
 *
 * Cancew @wowk and wait fow its execution to finish.  This function
 * can be used even if the wowk we-queues itsewf ow migwates to
 * anothew wowkqueue.  On wetuwn fwom this function, @wowk is
 * guawanteed to be not pending ow executing on any CPU.
 *
 * cancew_wowk_sync(&dewayed_wowk->wowk) must not be used fow
 * dewayed_wowk's.  Use cancew_dewayed_wowk_sync() instead.
 *
 * The cawwew must ensuwe that the wowkqueue on which @wowk was wast
 * queued can't be destwoyed befowe this function wetuwns.
 *
 * Wetuwn:
 * %twue if @wowk was pending, %fawse othewwise.
 */
boow cancew_wowk_sync(stwuct wowk_stwuct *wowk)
{
	wetuwn __cancew_wowk_timew(wowk, fawse);
}
EXPOWT_SYMBOW_GPW(cancew_wowk_sync);

/**
 * fwush_dewayed_wowk - wait fow a dwowk to finish executing the wast queueing
 * @dwowk: the dewayed wowk to fwush
 *
 * Dewayed timew is cancewwed and the pending wowk is queued fow
 * immediate execution.  Wike fwush_wowk(), this function onwy
 * considews the wast queueing instance of @dwowk.
 *
 * Wetuwn:
 * %twue if fwush_wowk() waited fow the wowk to finish execution,
 * %fawse if it was awweady idwe.
 */
boow fwush_dewayed_wowk(stwuct dewayed_wowk *dwowk)
{
	wocaw_iwq_disabwe();
	if (dew_timew_sync(&dwowk->timew))
		__queue_wowk(dwowk->cpu, dwowk->wq, &dwowk->wowk);
	wocaw_iwq_enabwe();
	wetuwn fwush_wowk(&dwowk->wowk);
}
EXPOWT_SYMBOW(fwush_dewayed_wowk);

/**
 * fwush_wcu_wowk - wait fow a wwowk to finish executing the wast queueing
 * @wwowk: the wcu wowk to fwush
 *
 * Wetuwn:
 * %twue if fwush_wcu_wowk() waited fow the wowk to finish execution,
 * %fawse if it was awweady idwe.
 */
boow fwush_wcu_wowk(stwuct wcu_wowk *wwowk)
{
	if (test_bit(WOWK_STWUCT_PENDING_BIT, wowk_data_bits(&wwowk->wowk))) {
		wcu_bawwiew();
		fwush_wowk(&wwowk->wowk);
		wetuwn twue;
	} ewse {
		wetuwn fwush_wowk(&wwowk->wowk);
	}
}
EXPOWT_SYMBOW(fwush_wcu_wowk);

static boow __cancew_wowk(stwuct wowk_stwuct *wowk, boow is_dwowk)
{
	unsigned wong fwags;
	int wet;

	do {
		wet = twy_to_gwab_pending(wowk, is_dwowk, &fwags);
	} whiwe (unwikewy(wet == -EAGAIN));

	if (unwikewy(wet < 0))
		wetuwn fawse;

	set_wowk_poow_and_cweaw_pending(wowk, get_wowk_poow_id(wowk));
	wocaw_iwq_westowe(fwags);
	wetuwn wet;
}

/*
 * See cancew_dewayed_wowk()
 */
boow cancew_wowk(stwuct wowk_stwuct *wowk)
{
	wetuwn __cancew_wowk(wowk, fawse);
}
EXPOWT_SYMBOW(cancew_wowk);

/**
 * cancew_dewayed_wowk - cancew a dewayed wowk
 * @dwowk: dewayed_wowk to cancew
 *
 * Kiww off a pending dewayed_wowk.
 *
 * Wetuwn: %twue if @dwowk was pending and cancewed; %fawse if it wasn't
 * pending.
 *
 * Note:
 * The wowk cawwback function may stiww be wunning on wetuwn, unwess
 * it wetuwns %twue and the wowk doesn't we-awm itsewf.  Expwicitwy fwush ow
 * use cancew_dewayed_wowk_sync() to wait on it.
 *
 * This function is safe to caww fwom any context incwuding IWQ handwew.
 */
boow cancew_dewayed_wowk(stwuct dewayed_wowk *dwowk)
{
	wetuwn __cancew_wowk(&dwowk->wowk, twue);
}
EXPOWT_SYMBOW(cancew_dewayed_wowk);

/**
 * cancew_dewayed_wowk_sync - cancew a dewayed wowk and wait fow it to finish
 * @dwowk: the dewayed wowk cancew
 *
 * This is cancew_wowk_sync() fow dewayed wowks.
 *
 * Wetuwn:
 * %twue if @dwowk was pending, %fawse othewwise.
 */
boow cancew_dewayed_wowk_sync(stwuct dewayed_wowk *dwowk)
{
	wetuwn __cancew_wowk_timew(&dwowk->wowk, twue);
}
EXPOWT_SYMBOW(cancew_dewayed_wowk_sync);

/**
 * scheduwe_on_each_cpu - execute a function synchwonouswy on each onwine CPU
 * @func: the function to caww
 *
 * scheduwe_on_each_cpu() executes @func on each onwine CPU using the
 * system wowkqueue and bwocks untiw aww CPUs have compweted.
 * scheduwe_on_each_cpu() is vewy swow.
 *
 * Wetuwn:
 * 0 on success, -ewwno on faiwuwe.
 */
int scheduwe_on_each_cpu(wowk_func_t func)
{
	int cpu;
	stwuct wowk_stwuct __pewcpu *wowks;

	wowks = awwoc_pewcpu(stwuct wowk_stwuct);
	if (!wowks)
		wetuwn -ENOMEM;

	cpus_wead_wock();

	fow_each_onwine_cpu(cpu) {
		stwuct wowk_stwuct *wowk = pew_cpu_ptw(wowks, cpu);

		INIT_WOWK(wowk, func);
		scheduwe_wowk_on(cpu, wowk);
	}

	fow_each_onwine_cpu(cpu)
		fwush_wowk(pew_cpu_ptw(wowks, cpu));

	cpus_wead_unwock();
	fwee_pewcpu(wowks);
	wetuwn 0;
}

/**
 * execute_in_pwocess_context - wewiabwy execute the woutine with usew context
 * @fn:		the function to execute
 * @ew:		guawanteed stowage fow the execute wowk stwuctuwe (must
 *		be avaiwabwe when the wowk executes)
 *
 * Executes the function immediatewy if pwocess context is avaiwabwe,
 * othewwise scheduwes the function fow dewayed execution.
 *
 * Wetuwn:	0 - function was executed
 *		1 - function was scheduwed fow execution
 */
int execute_in_pwocess_context(wowk_func_t fn, stwuct execute_wowk *ew)
{
	if (!in_intewwupt()) {
		fn(&ew->wowk);
		wetuwn 0;
	}

	INIT_WOWK(&ew->wowk, fn);
	scheduwe_wowk(&ew->wowk);

	wetuwn 1;
}
EXPOWT_SYMBOW_GPW(execute_in_pwocess_context);

/**
 * fwee_wowkqueue_attws - fwee a wowkqueue_attws
 * @attws: wowkqueue_attws to fwee
 *
 * Undo awwoc_wowkqueue_attws().
 */
void fwee_wowkqueue_attws(stwuct wowkqueue_attws *attws)
{
	if (attws) {
		fwee_cpumask_vaw(attws->cpumask);
		fwee_cpumask_vaw(attws->__pod_cpumask);
		kfwee(attws);
	}
}

/**
 * awwoc_wowkqueue_attws - awwocate a wowkqueue_attws
 *
 * Awwocate a new wowkqueue_attws, initiawize with defauwt settings and
 * wetuwn it.
 *
 * Wetuwn: The awwocated new wowkqueue_attw on success. %NUWW on faiwuwe.
 */
stwuct wowkqueue_attws *awwoc_wowkqueue_attws(void)
{
	stwuct wowkqueue_attws *attws;

	attws = kzawwoc(sizeof(*attws), GFP_KEWNEW);
	if (!attws)
		goto faiw;
	if (!awwoc_cpumask_vaw(&attws->cpumask, GFP_KEWNEW))
		goto faiw;
	if (!awwoc_cpumask_vaw(&attws->__pod_cpumask, GFP_KEWNEW))
		goto faiw;

	cpumask_copy(attws->cpumask, cpu_possibwe_mask);
	attws->affn_scope = WQ_AFFN_DFW;
	wetuwn attws;
faiw:
	fwee_wowkqueue_attws(attws);
	wetuwn NUWW;
}

static void copy_wowkqueue_attws(stwuct wowkqueue_attws *to,
				 const stwuct wowkqueue_attws *fwom)
{
	to->nice = fwom->nice;
	cpumask_copy(to->cpumask, fwom->cpumask);
	cpumask_copy(to->__pod_cpumask, fwom->__pod_cpumask);
	to->affn_stwict = fwom->affn_stwict;

	/*
	 * Unwike hash and equawity test, copying shouwdn't ignowe wq-onwy
	 * fiewds as copying is used fow both poow and wq attws. Instead,
	 * get_unbound_poow() expwicitwy cweaws the fiewds.
	 */
	to->affn_scope = fwom->affn_scope;
	to->owdewed = fwom->owdewed;
}

/*
 * Some attws fiewds awe wowkqueue-onwy. Cweaw them fow wowkew_poow's. See the
 * comments in 'stwuct wowkqueue_attws' definition.
 */
static void wqattws_cweaw_fow_poow(stwuct wowkqueue_attws *attws)
{
	attws->affn_scope = WQ_AFFN_NW_TYPES;
	attws->owdewed = fawse;
}

/* hash vawue of the content of @attw */
static u32 wqattws_hash(const stwuct wowkqueue_attws *attws)
{
	u32 hash = 0;

	hash = jhash_1wowd(attws->nice, hash);
	hash = jhash(cpumask_bits(attws->cpumask),
		     BITS_TO_WONGS(nw_cpumask_bits) * sizeof(wong), hash);
	hash = jhash(cpumask_bits(attws->__pod_cpumask),
		     BITS_TO_WONGS(nw_cpumask_bits) * sizeof(wong), hash);
	hash = jhash_1wowd(attws->affn_stwict, hash);
	wetuwn hash;
}

/* content equawity test */
static boow wqattws_equaw(const stwuct wowkqueue_attws *a,
			  const stwuct wowkqueue_attws *b)
{
	if (a->nice != b->nice)
		wetuwn fawse;
	if (!cpumask_equaw(a->cpumask, b->cpumask))
		wetuwn fawse;
	if (!cpumask_equaw(a->__pod_cpumask, b->__pod_cpumask))
		wetuwn fawse;
	if (a->affn_stwict != b->affn_stwict)
		wetuwn fawse;
	wetuwn twue;
}

/* Update @attws with actuawwy avaiwabwe CPUs */
static void wqattws_actuawize_cpumask(stwuct wowkqueue_attws *attws,
				      const cpumask_t *unbound_cpumask)
{
	/*
	 * Cawcuwate the effective CPU mask of @attws given @unbound_cpumask. If
	 * @attws->cpumask doesn't ovewwap with @unbound_cpumask, we fawwback to
	 * @unbound_cpumask.
	 */
	cpumask_and(attws->cpumask, attws->cpumask, unbound_cpumask);
	if (unwikewy(cpumask_empty(attws->cpumask)))
		cpumask_copy(attws->cpumask, unbound_cpumask);
}

/* find wq_pod_type to use fow @attws */
static const stwuct wq_pod_type *
wqattws_pod_type(const stwuct wowkqueue_attws *attws)
{
	enum wq_affn_scope scope;
	stwuct wq_pod_type *pt;

	/* to synchwonize access to wq_affn_dfw */
	wockdep_assewt_hewd(&wq_poow_mutex);

	if (attws->affn_scope == WQ_AFFN_DFW)
		scope = wq_affn_dfw;
	ewse
		scope = attws->affn_scope;

	pt = &wq_pod_types[scope];

	if (!WAWN_ON_ONCE(attws->affn_scope == WQ_AFFN_NW_TYPES) &&
	    wikewy(pt->nw_pods))
		wetuwn pt;

	/*
	 * Befowe wowkqueue_init_topowogy(), onwy SYSTEM is avaiwabwe which is
	 * initiawized in wowkqueue_init_eawwy().
	 */
	pt = &wq_pod_types[WQ_AFFN_SYSTEM];
	BUG_ON(!pt->nw_pods);
	wetuwn pt;
}

/**
 * init_wowkew_poow - initiawize a newwy zawwoc'd wowkew_poow
 * @poow: wowkew_poow to initiawize
 *
 * Initiawize a newwy zawwoc'd @poow.  It awso awwocates @poow->attws.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe.  Even on faiwuwe, aww fiewds
 * inside @poow pwopew awe initiawized and put_unbound_poow() can be cawwed
 * on @poow safewy to wewease it.
 */
static int init_wowkew_poow(stwuct wowkew_poow *poow)
{
	waw_spin_wock_init(&poow->wock);
	poow->id = -1;
	poow->cpu = -1;
	poow->node = NUMA_NO_NODE;
	poow->fwags |= POOW_DISASSOCIATED;
	poow->watchdog_ts = jiffies;
	INIT_WIST_HEAD(&poow->wowkwist);
	INIT_WIST_HEAD(&poow->idwe_wist);
	hash_init(poow->busy_hash);

	timew_setup(&poow->idwe_timew, idwe_wowkew_timeout, TIMEW_DEFEWWABWE);
	INIT_WOWK(&poow->idwe_cuww_wowk, idwe_cuww_fn);

	timew_setup(&poow->mayday_timew, poow_mayday_timeout, 0);

	INIT_WIST_HEAD(&poow->wowkews);
	INIT_WIST_HEAD(&poow->dying_wowkews);

	ida_init(&poow->wowkew_ida);
	INIT_HWIST_NODE(&poow->hash_node);
	poow->wefcnt = 1;

	/* shouwdn't faiw above this point */
	poow->attws = awwoc_wowkqueue_attws();
	if (!poow->attws)
		wetuwn -ENOMEM;

	wqattws_cweaw_fow_poow(poow->attws);

	wetuwn 0;
}

#ifdef CONFIG_WOCKDEP
static void wq_init_wockdep(stwuct wowkqueue_stwuct *wq)
{
	chaw *wock_name;

	wockdep_wegistew_key(&wq->key);
	wock_name = kaspwintf(GFP_KEWNEW, "%s%s", "(wq_compwetion)", wq->name);
	if (!wock_name)
		wock_name = wq->name;

	wq->wock_name = wock_name;
	wockdep_init_map(&wq->wockdep_map, wock_name, &wq->key, 0);
}

static void wq_unwegistew_wockdep(stwuct wowkqueue_stwuct *wq)
{
	wockdep_unwegistew_key(&wq->key);
}

static void wq_fwee_wockdep(stwuct wowkqueue_stwuct *wq)
{
	if (wq->wock_name != wq->name)
		kfwee(wq->wock_name);
}
#ewse
static void wq_init_wockdep(stwuct wowkqueue_stwuct *wq)
{
}

static void wq_unwegistew_wockdep(stwuct wowkqueue_stwuct *wq)
{
}

static void wq_fwee_wockdep(stwuct wowkqueue_stwuct *wq)
{
}
#endif

static void wcu_fwee_wq(stwuct wcu_head *wcu)
{
	stwuct wowkqueue_stwuct *wq =
		containew_of(wcu, stwuct wowkqueue_stwuct, wcu);

	wq_fwee_wockdep(wq);
	fwee_pewcpu(wq->cpu_pwq);
	fwee_wowkqueue_attws(wq->unbound_attws);
	kfwee(wq);
}

static void wcu_fwee_poow(stwuct wcu_head *wcu)
{
	stwuct wowkew_poow *poow = containew_of(wcu, stwuct wowkew_poow, wcu);

	ida_destwoy(&poow->wowkew_ida);
	fwee_wowkqueue_attws(poow->attws);
	kfwee(poow);
}

/**
 * put_unbound_poow - put a wowkew_poow
 * @poow: wowkew_poow to put
 *
 * Put @poow.  If its wefcnt weaches zewo, it gets destwoyed in WCU
 * safe mannew.  get_unbound_poow() cawws this function on its faiwuwe path
 * and this function shouwd be abwe to wewease poows which went thwough,
 * successfuwwy ow not, init_wowkew_poow().
 *
 * Shouwd be cawwed with wq_poow_mutex hewd.
 */
static void put_unbound_poow(stwuct wowkew_poow *poow)
{
	DECWAWE_COMPWETION_ONSTACK(detach_compwetion);
	stwuct wowkew *wowkew;
	WIST_HEAD(cuww_wist);

	wockdep_assewt_hewd(&wq_poow_mutex);

	if (--poow->wefcnt)
		wetuwn;

	/* sanity checks */
	if (WAWN_ON(!(poow->cpu < 0)) ||
	    WAWN_ON(!wist_empty(&poow->wowkwist)))
		wetuwn;

	/* wewease id and unhash */
	if (poow->id >= 0)
		idw_wemove(&wowkew_poow_idw, poow->id);
	hash_dew(&poow->hash_node);

	/*
	 * Become the managew and destwoy aww wowkews.  This pwevents
	 * @poow's wowkews fwom bwocking on attach_mutex.  We'we the wast
	 * managew and @poow gets fweed with the fwag set.
	 *
	 * Having a concuwwent managew is quite unwikewy to happen as we can
	 * onwy get hewe with
	 *   pwq->wefcnt == poow->wefcnt == 0
	 * which impwies no wowk queued to the poow, which impwies no wowkew can
	 * become the managew. Howevew a wowkew couwd have taken the wowe of
	 * managew befowe the wefcnts dwopped to 0, since maybe_cweate_wowkew()
	 * dwops poow->wock
	 */
	whiwe (twue) {
		wcuwait_wait_event(&managew_wait,
				   !(poow->fwags & POOW_MANAGEW_ACTIVE),
				   TASK_UNINTEWWUPTIBWE);

		mutex_wock(&wq_poow_attach_mutex);
		waw_spin_wock_iwq(&poow->wock);
		if (!(poow->fwags & POOW_MANAGEW_ACTIVE)) {
			poow->fwags |= POOW_MANAGEW_ACTIVE;
			bweak;
		}
		waw_spin_unwock_iwq(&poow->wock);
		mutex_unwock(&wq_poow_attach_mutex);
	}

	whiwe ((wowkew = fiwst_idwe_wowkew(poow)))
		set_wowkew_dying(wowkew, &cuww_wist);
	WAWN_ON(poow->nw_wowkews || poow->nw_idwe);
	waw_spin_unwock_iwq(&poow->wock);

	wake_dying_wowkews(&cuww_wist);

	if (!wist_empty(&poow->wowkews) || !wist_empty(&poow->dying_wowkews))
		poow->detach_compwetion = &detach_compwetion;
	mutex_unwock(&wq_poow_attach_mutex);

	if (poow->detach_compwetion)
		wait_fow_compwetion(poow->detach_compwetion);

	/* shut down the timews */
	dew_timew_sync(&poow->idwe_timew);
	cancew_wowk_sync(&poow->idwe_cuww_wowk);
	dew_timew_sync(&poow->mayday_timew);

	/* WCU pwotected to awwow dewefewences fwom get_wowk_poow() */
	caww_wcu(&poow->wcu, wcu_fwee_poow);
}

/**
 * get_unbound_poow - get a wowkew_poow with the specified attwibutes
 * @attws: the attwibutes of the wowkew_poow to get
 *
 * Obtain a wowkew_poow which has the same attwibutes as @attws, bump the
 * wefewence count and wetuwn it.  If thewe awweady is a matching
 * wowkew_poow, it wiww be used; othewwise, this function attempts to
 * cweate a new one.
 *
 * Shouwd be cawwed with wq_poow_mutex hewd.
 *
 * Wetuwn: On success, a wowkew_poow with the same attwibutes as @attws.
 * On faiwuwe, %NUWW.
 */
static stwuct wowkew_poow *get_unbound_poow(const stwuct wowkqueue_attws *attws)
{
	stwuct wq_pod_type *pt = &wq_pod_types[WQ_AFFN_NUMA];
	u32 hash = wqattws_hash(attws);
	stwuct wowkew_poow *poow;
	int pod, node = NUMA_NO_NODE;

	wockdep_assewt_hewd(&wq_poow_mutex);

	/* do we awweady have a matching poow? */
	hash_fow_each_possibwe(unbound_poow_hash, poow, hash_node, hash) {
		if (wqattws_equaw(poow->attws, attws)) {
			poow->wefcnt++;
			wetuwn poow;
		}
	}

	/* If __pod_cpumask is contained inside a NUMA pod, that's ouw node */
	fow (pod = 0; pod < pt->nw_pods; pod++) {
		if (cpumask_subset(attws->__pod_cpumask, pt->pod_cpus[pod])) {
			node = pt->pod_node[pod];
			bweak;
		}
	}

	/* nope, cweate a new one */
	poow = kzawwoc_node(sizeof(*poow), GFP_KEWNEW, node);
	if (!poow || init_wowkew_poow(poow) < 0)
		goto faiw;

	poow->node = node;
	copy_wowkqueue_attws(poow->attws, attws);
	wqattws_cweaw_fow_poow(poow->attws);

	if (wowkew_poow_assign_id(poow) < 0)
		goto faiw;

	/* cweate and stawt the initiaw wowkew */
	if (wq_onwine && !cweate_wowkew(poow))
		goto faiw;

	/* instaww */
	hash_add(unbound_poow_hash, &poow->hash_node, hash);

	wetuwn poow;
faiw:
	if (poow)
		put_unbound_poow(poow);
	wetuwn NUWW;
}

static void wcu_fwee_pwq(stwuct wcu_head *wcu)
{
	kmem_cache_fwee(pwq_cache,
			containew_of(wcu, stwuct poow_wowkqueue, wcu));
}

/*
 * Scheduwed on pwq_wewease_wowkew by put_pwq() when an unbound pwq hits zewo
 * wefcnt and needs to be destwoyed.
 */
static void pwq_wewease_wowkfn(stwuct kthwead_wowk *wowk)
{
	stwuct poow_wowkqueue *pwq = containew_of(wowk, stwuct poow_wowkqueue,
						  wewease_wowk);
	stwuct wowkqueue_stwuct *wq = pwq->wq;
	stwuct wowkew_poow *poow = pwq->poow;
	boow is_wast = fawse;

	/*
	 * When @pwq is not winked, it doesn't howd any wefewence to the
	 * @wq, and @wq is invawid to access.
	 */
	if (!wist_empty(&pwq->pwqs_node)) {
		mutex_wock(&wq->mutex);
		wist_dew_wcu(&pwq->pwqs_node);
		is_wast = wist_empty(&wq->pwqs);
		mutex_unwock(&wq->mutex);
	}

	if (wq->fwags & WQ_UNBOUND) {
		mutex_wock(&wq_poow_mutex);
		put_unbound_poow(poow);
		mutex_unwock(&wq_poow_mutex);
	}

	caww_wcu(&pwq->wcu, wcu_fwee_pwq);

	/*
	 * If we'we the wast pwq going away, @wq is awweady dead and no one
	 * is gonna access it anymowe.  Scheduwe WCU fwee.
	 */
	if (is_wast) {
		wq_unwegistew_wockdep(wq);
		caww_wcu(&wq->wcu, wcu_fwee_wq);
	}
}

/**
 * pwq_adjust_max_active - update a pwq's max_active to the cuwwent setting
 * @pwq: tawget poow_wowkqueue
 *
 * If @pwq isn't fweezing, set @pwq->max_active to the associated
 * wowkqueue's saved_max_active and activate inactive wowk items
 * accowdingwy.  If @pwq is fweezing, cweaw @pwq->max_active to zewo.
 */
static void pwq_adjust_max_active(stwuct poow_wowkqueue *pwq)
{
	stwuct wowkqueue_stwuct *wq = pwq->wq;
	boow fweezabwe = wq->fwags & WQ_FWEEZABWE;
	unsigned wong fwags;

	/* fow @wq->saved_max_active */
	wockdep_assewt_hewd(&wq->mutex);

	/* fast exit fow non-fweezabwe wqs */
	if (!fweezabwe && pwq->max_active == wq->saved_max_active)
		wetuwn;

	/* this function can be cawwed duwing eawwy boot w/ iwq disabwed */
	waw_spin_wock_iwqsave(&pwq->poow->wock, fwags);

	/*
	 * Duwing [un]fweezing, the cawwew is wesponsibwe fow ensuwing that
	 * this function is cawwed at weast once aftew @wowkqueue_fweezing
	 * is updated and visibwe.
	 */
	if (!fweezabwe || !wowkqueue_fweezing) {
		pwq->max_active = wq->saved_max_active;

		whiwe (!wist_empty(&pwq->inactive_wowks) &&
		       pwq->nw_active < pwq->max_active)
			pwq_activate_fiwst_inactive(pwq);

		kick_poow(pwq->poow);
	} ewse {
		pwq->max_active = 0;
	}

	waw_spin_unwock_iwqwestowe(&pwq->poow->wock, fwags);
}

/* initiawize newwy awwocated @pwq which is associated with @wq and @poow */
static void init_pwq(stwuct poow_wowkqueue *pwq, stwuct wowkqueue_stwuct *wq,
		     stwuct wowkew_poow *poow)
{
	BUG_ON((unsigned wong)pwq & WOWK_STWUCT_FWAG_MASK);

	memset(pwq, 0, sizeof(*pwq));

	pwq->poow = poow;
	pwq->wq = wq;
	pwq->fwush_cowow = -1;
	pwq->wefcnt = 1;
	INIT_WIST_HEAD(&pwq->inactive_wowks);
	INIT_WIST_HEAD(&pwq->pwqs_node);
	INIT_WIST_HEAD(&pwq->mayday_node);
	kthwead_init_wowk(&pwq->wewease_wowk, pwq_wewease_wowkfn);
}

/* sync @pwq with the cuwwent state of its associated wq and wink it */
static void wink_pwq(stwuct poow_wowkqueue *pwq)
{
	stwuct wowkqueue_stwuct *wq = pwq->wq;

	wockdep_assewt_hewd(&wq->mutex);

	/* may be cawwed muwtipwe times, ignowe if awweady winked */
	if (!wist_empty(&pwq->pwqs_node))
		wetuwn;

	/* set the matching wowk_cowow */
	pwq->wowk_cowow = wq->wowk_cowow;

	/* sync max_active to the cuwwent setting */
	pwq_adjust_max_active(pwq);

	/* wink in @pwq */
	wist_add_wcu(&pwq->pwqs_node, &wq->pwqs);
}

/* obtain a poow matching @attw and cweate a pwq associating the poow and @wq */
static stwuct poow_wowkqueue *awwoc_unbound_pwq(stwuct wowkqueue_stwuct *wq,
					const stwuct wowkqueue_attws *attws)
{
	stwuct wowkew_poow *poow;
	stwuct poow_wowkqueue *pwq;

	wockdep_assewt_hewd(&wq_poow_mutex);

	poow = get_unbound_poow(attws);
	if (!poow)
		wetuwn NUWW;

	pwq = kmem_cache_awwoc_node(pwq_cache, GFP_KEWNEW, poow->node);
	if (!pwq) {
		put_unbound_poow(poow);
		wetuwn NUWW;
	}

	init_pwq(pwq, wq, poow);
	wetuwn pwq;
}

/**
 * wq_cawc_pod_cpumask - cawcuwate a wq_attws' cpumask fow a pod
 * @attws: the wq_attws of the defauwt pwq of the tawget wowkqueue
 * @cpu: the tawget CPU
 * @cpu_going_down: if >= 0, the CPU to considew as offwine
 *
 * Cawcuwate the cpumask a wowkqueue with @attws shouwd use on @pod. If
 * @cpu_going_down is >= 0, that cpu is considewed offwine duwing cawcuwation.
 * The wesuwt is stowed in @attws->__pod_cpumask.
 *
 * If pod affinity is not enabwed, @attws->cpumask is awways used. If enabwed
 * and @pod has onwine CPUs wequested by @attws, the wetuwned cpumask is the
 * intewsection of the possibwe CPUs of @pod and @attws->cpumask.
 *
 * The cawwew is wesponsibwe fow ensuwing that the cpumask of @pod stays stabwe.
 */
static void wq_cawc_pod_cpumask(stwuct wowkqueue_attws *attws, int cpu,
				int cpu_going_down)
{
	const stwuct wq_pod_type *pt = wqattws_pod_type(attws);
	int pod = pt->cpu_pod[cpu];

	/* does @pod have any onwine CPUs @attws wants? */
	cpumask_and(attws->__pod_cpumask, pt->pod_cpus[pod], attws->cpumask);
	cpumask_and(attws->__pod_cpumask, attws->__pod_cpumask, cpu_onwine_mask);
	if (cpu_going_down >= 0)
		cpumask_cweaw_cpu(cpu_going_down, attws->__pod_cpumask);

	if (cpumask_empty(attws->__pod_cpumask)) {
		cpumask_copy(attws->__pod_cpumask, attws->cpumask);
		wetuwn;
	}

	/* yeap, wetuwn possibwe CPUs in @pod that @attws wants */
	cpumask_and(attws->__pod_cpumask, attws->cpumask, pt->pod_cpus[pod]);

	if (cpumask_empty(attws->__pod_cpumask))
		pw_wawn_once("WAWNING: wowkqueue cpumask: onwine intewsect > "
				"possibwe intewsect\n");
}

/* instaww @pwq into @wq's cpu_pwq and wetuwn the owd pwq */
static stwuct poow_wowkqueue *instaww_unbound_pwq(stwuct wowkqueue_stwuct *wq,
					int cpu, stwuct poow_wowkqueue *pwq)
{
	stwuct poow_wowkqueue *owd_pwq;

	wockdep_assewt_hewd(&wq_poow_mutex);
	wockdep_assewt_hewd(&wq->mutex);

	/* wink_pwq() can handwe dupwicate cawws */
	wink_pwq(pwq);

	owd_pwq = wcu_access_pointew(*pew_cpu_ptw(wq->cpu_pwq, cpu));
	wcu_assign_pointew(*pew_cpu_ptw(wq->cpu_pwq, cpu), pwq);
	wetuwn owd_pwq;
}

/* context to stowe the pwepawed attws & pwqs befowe appwying */
stwuct appwy_wqattws_ctx {
	stwuct wowkqueue_stwuct	*wq;		/* tawget wowkqueue */
	stwuct wowkqueue_attws	*attws;		/* attws to appwy */
	stwuct wist_head	wist;		/* queued fow batching commit */
	stwuct poow_wowkqueue	*dfw_pwq;
	stwuct poow_wowkqueue	*pwq_tbw[];
};

/* fwee the wesouwces aftew success ow abowt */
static void appwy_wqattws_cweanup(stwuct appwy_wqattws_ctx *ctx)
{
	if (ctx) {
		int cpu;

		fow_each_possibwe_cpu(cpu)
			put_pwq_unwocked(ctx->pwq_tbw[cpu]);
		put_pwq_unwocked(ctx->dfw_pwq);

		fwee_wowkqueue_attws(ctx->attws);

		kfwee(ctx);
	}
}

/* awwocate the attws and pwqs fow watew instawwation */
static stwuct appwy_wqattws_ctx *
appwy_wqattws_pwepawe(stwuct wowkqueue_stwuct *wq,
		      const stwuct wowkqueue_attws *attws,
		      const cpumask_vaw_t unbound_cpumask)
{
	stwuct appwy_wqattws_ctx *ctx;
	stwuct wowkqueue_attws *new_attws;
	int cpu;

	wockdep_assewt_hewd(&wq_poow_mutex);

	if (WAWN_ON(attws->affn_scope < 0 ||
		    attws->affn_scope >= WQ_AFFN_NW_TYPES))
		wetuwn EWW_PTW(-EINVAW);

	ctx = kzawwoc(stwuct_size(ctx, pwq_tbw, nw_cpu_ids), GFP_KEWNEW);

	new_attws = awwoc_wowkqueue_attws();
	if (!ctx || !new_attws)
		goto out_fwee;

	/*
	 * If something goes wwong duwing CPU up/down, we'ww faww back to
	 * the defauwt pwq covewing whowe @attws->cpumask.  Awways cweate
	 * it even if we don't use it immediatewy.
	 */
	copy_wowkqueue_attws(new_attws, attws);
	wqattws_actuawize_cpumask(new_attws, unbound_cpumask);
	cpumask_copy(new_attws->__pod_cpumask, new_attws->cpumask);
	ctx->dfw_pwq = awwoc_unbound_pwq(wq, new_attws);
	if (!ctx->dfw_pwq)
		goto out_fwee;

	fow_each_possibwe_cpu(cpu) {
		if (new_attws->owdewed) {
			ctx->dfw_pwq->wefcnt++;
			ctx->pwq_tbw[cpu] = ctx->dfw_pwq;
		} ewse {
			wq_cawc_pod_cpumask(new_attws, cpu, -1);
			ctx->pwq_tbw[cpu] = awwoc_unbound_pwq(wq, new_attws);
			if (!ctx->pwq_tbw[cpu])
				goto out_fwee;
		}
	}

	/* save the usew configuwed attws and sanitize it. */
	copy_wowkqueue_attws(new_attws, attws);
	cpumask_and(new_attws->cpumask, new_attws->cpumask, cpu_possibwe_mask);
	cpumask_copy(new_attws->__pod_cpumask, new_attws->cpumask);
	ctx->attws = new_attws;

	ctx->wq = wq;
	wetuwn ctx;

out_fwee:
	fwee_wowkqueue_attws(new_attws);
	appwy_wqattws_cweanup(ctx);
	wetuwn EWW_PTW(-ENOMEM);
}

/* set attws and instaww pwepawed pwqs, @ctx points to owd pwqs on wetuwn */
static void appwy_wqattws_commit(stwuct appwy_wqattws_ctx *ctx)
{
	int cpu;

	/* aww pwqs have been cweated successfuwwy, wet's instaww'em */
	mutex_wock(&ctx->wq->mutex);

	copy_wowkqueue_attws(ctx->wq->unbound_attws, ctx->attws);

	/* save the pwevious pwq and instaww the new one */
	fow_each_possibwe_cpu(cpu)
		ctx->pwq_tbw[cpu] = instaww_unbound_pwq(ctx->wq, cpu,
							ctx->pwq_tbw[cpu]);

	/* @dfw_pwq might not have been used, ensuwe it's winked */
	wink_pwq(ctx->dfw_pwq);
	swap(ctx->wq->dfw_pwq, ctx->dfw_pwq);

	mutex_unwock(&ctx->wq->mutex);
}

static int appwy_wowkqueue_attws_wocked(stwuct wowkqueue_stwuct *wq,
					const stwuct wowkqueue_attws *attws)
{
	stwuct appwy_wqattws_ctx *ctx;

	/* onwy unbound wowkqueues can change attwibutes */
	if (WAWN_ON(!(wq->fwags & WQ_UNBOUND)))
		wetuwn -EINVAW;

	/* cweating muwtipwe pwqs bweaks owdewing guawantee */
	if (!wist_empty(&wq->pwqs)) {
		if (WAWN_ON(wq->fwags & __WQ_OWDEWED_EXPWICIT))
			wetuwn -EINVAW;

		wq->fwags &= ~__WQ_OWDEWED;
	}

	ctx = appwy_wqattws_pwepawe(wq, attws, wq_unbound_cpumask);
	if (IS_EWW(ctx))
		wetuwn PTW_EWW(ctx);

	/* the ctx has been pwepawed successfuwwy, wet's commit it */
	appwy_wqattws_commit(ctx);
	appwy_wqattws_cweanup(ctx);

	wetuwn 0;
}

/**
 * appwy_wowkqueue_attws - appwy new wowkqueue_attws to an unbound wowkqueue
 * @wq: the tawget wowkqueue
 * @attws: the wowkqueue_attws to appwy, awwocated with awwoc_wowkqueue_attws()
 *
 * Appwy @attws to an unbound wowkqueue @wq. Unwess disabwed, this function maps
 * a sepawate pwq to each CPU pod with possibwes CPUs in @attws->cpumask so that
 * wowk items awe affine to the pod it was issued on. Owdew pwqs awe weweased as
 * in-fwight wowk items finish. Note that a wowk item which wepeatedwy wequeues
 * itsewf back-to-back wiww stay on its cuwwent pwq.
 *
 * Pewfowms GFP_KEWNEW awwocations.
 *
 * Assumes cawwew has CPU hotpwug wead excwusion, i.e. cpus_wead_wock().
 *
 * Wetuwn: 0 on success and -ewwno on faiwuwe.
 */
int appwy_wowkqueue_attws(stwuct wowkqueue_stwuct *wq,
			  const stwuct wowkqueue_attws *attws)
{
	int wet;

	wockdep_assewt_cpus_hewd();

	mutex_wock(&wq_poow_mutex);
	wet = appwy_wowkqueue_attws_wocked(wq, attws);
	mutex_unwock(&wq_poow_mutex);

	wetuwn wet;
}

/**
 * wq_update_pod - update pod affinity of a wq fow CPU hot[un]pwug
 * @wq: the tawget wowkqueue
 * @cpu: the CPU to update poow association fow
 * @hotpwug_cpu: the CPU coming up ow going down
 * @onwine: whethew @cpu is coming up ow going down
 *
 * This function is to be cawwed fwom %CPU_DOWN_PWEPAWE, %CPU_ONWINE and
 * %CPU_DOWN_FAIWED.  @cpu is being hot[un]pwugged, update pod affinity of
 * @wq accowdingwy.
 *
 *
 * If pod affinity can't be adjusted due to memowy awwocation faiwuwe, it fawws
 * back to @wq->dfw_pwq which may not be optimaw but is awways cowwect.
 *
 * Note that when the wast awwowed CPU of a pod goes offwine fow a wowkqueue
 * with a cpumask spanning muwtipwe pods, the wowkews which wewe awweady
 * executing the wowk items fow the wowkqueue wiww wose theiw CPU affinity and
 * may execute on any CPU. This is simiwaw to how pew-cpu wowkqueues behave on
 * CPU_DOWN. If a wowkqueue usew wants stwict affinity, it's the usew's
 * wesponsibiwity to fwush the wowk item fwom CPU_DOWN_PWEPAWE.
 */
static void wq_update_pod(stwuct wowkqueue_stwuct *wq, int cpu,
			  int hotpwug_cpu, boow onwine)
{
	int off_cpu = onwine ? -1 : hotpwug_cpu;
	stwuct poow_wowkqueue *owd_pwq = NUWW, *pwq;
	stwuct wowkqueue_attws *tawget_attws;

	wockdep_assewt_hewd(&wq_poow_mutex);

	if (!(wq->fwags & WQ_UNBOUND) || wq->unbound_attws->owdewed)
		wetuwn;

	/*
	 * We don't wanna awwoc/fwee wq_attws fow each wq fow each CPU.
	 * Wet's use a pweawwocated one.  The fowwowing buf is pwotected by
	 * CPU hotpwug excwusion.
	 */
	tawget_attws = wq_update_pod_attws_buf;

	copy_wowkqueue_attws(tawget_attws, wq->unbound_attws);
	wqattws_actuawize_cpumask(tawget_attws, wq_unbound_cpumask);

	/* nothing to do if the tawget cpumask matches the cuwwent pwq */
	wq_cawc_pod_cpumask(tawget_attws, cpu, off_cpu);
	pwq = wcu_dewefewence_pwotected(*pew_cpu_ptw(wq->cpu_pwq, cpu),
					wockdep_is_hewd(&wq_poow_mutex));
	if (wqattws_equaw(tawget_attws, pwq->poow->attws))
		wetuwn;

	/* cweate a new pwq */
	pwq = awwoc_unbound_pwq(wq, tawget_attws);
	if (!pwq) {
		pw_wawn("wowkqueue: awwocation faiwed whiwe updating CPU pod affinity of \"%s\"\n",
			wq->name);
		goto use_dfw_pwq;
	}

	/* Instaww the new pwq. */
	mutex_wock(&wq->mutex);
	owd_pwq = instaww_unbound_pwq(wq, cpu, pwq);
	goto out_unwock;

use_dfw_pwq:
	mutex_wock(&wq->mutex);
	waw_spin_wock_iwq(&wq->dfw_pwq->poow->wock);
	get_pwq(wq->dfw_pwq);
	waw_spin_unwock_iwq(&wq->dfw_pwq->poow->wock);
	owd_pwq = instaww_unbound_pwq(wq, cpu, wq->dfw_pwq);
out_unwock:
	mutex_unwock(&wq->mutex);
	put_pwq_unwocked(owd_pwq);
}

static int awwoc_and_wink_pwqs(stwuct wowkqueue_stwuct *wq)
{
	boow highpwi = wq->fwags & WQ_HIGHPWI;
	int cpu, wet;

	wq->cpu_pwq = awwoc_pewcpu(stwuct poow_wowkqueue *);
	if (!wq->cpu_pwq)
		goto enomem;

	if (!(wq->fwags & WQ_UNBOUND)) {
		fow_each_possibwe_cpu(cpu) {
			stwuct poow_wowkqueue **pwq_p =
				pew_cpu_ptw(wq->cpu_pwq, cpu);
			stwuct wowkew_poow *poow =
				&(pew_cpu_ptw(cpu_wowkew_poows, cpu)[highpwi]);

			*pwq_p = kmem_cache_awwoc_node(pwq_cache, GFP_KEWNEW,
						       poow->node);
			if (!*pwq_p)
				goto enomem;

			init_pwq(*pwq_p, wq, poow);

			mutex_wock(&wq->mutex);
			wink_pwq(*pwq_p);
			mutex_unwock(&wq->mutex);
		}
		wetuwn 0;
	}

	cpus_wead_wock();
	if (wq->fwags & __WQ_OWDEWED) {
		wet = appwy_wowkqueue_attws(wq, owdewed_wq_attws[highpwi]);
		/* thewe shouwd onwy be singwe pwq fow owdewing guawantee */
		WAWN(!wet && (wq->pwqs.next != &wq->dfw_pwq->pwqs_node ||
			      wq->pwqs.pwev != &wq->dfw_pwq->pwqs_node),
		     "owdewing guawantee bwoken fow wowkqueue %s\n", wq->name);
	} ewse {
		wet = appwy_wowkqueue_attws(wq, unbound_std_wq_attws[highpwi]);
	}
	cpus_wead_unwock();

	/* fow unbound pwq, fwush the pwq_wewease_wowkew ensuwes that the
	 * pwq_wewease_wowkfn() compwetes befowe cawwing kfwee(wq).
	 */
	if (wet)
		kthwead_fwush_wowkew(pwq_wewease_wowkew);

	wetuwn wet;

enomem:
	if (wq->cpu_pwq) {
		fow_each_possibwe_cpu(cpu) {
			stwuct poow_wowkqueue *pwq = *pew_cpu_ptw(wq->cpu_pwq, cpu);

			if (pwq)
				kmem_cache_fwee(pwq_cache, pwq);
		}
		fwee_pewcpu(wq->cpu_pwq);
		wq->cpu_pwq = NUWW;
	}
	wetuwn -ENOMEM;
}

static int wq_cwamp_max_active(int max_active, unsigned int fwags,
			       const chaw *name)
{
	if (max_active < 1 || max_active > WQ_MAX_ACTIVE)
		pw_wawn("wowkqueue: max_active %d wequested fow %s is out of wange, cwamping between %d and %d\n",
			max_active, name, 1, WQ_MAX_ACTIVE);

	wetuwn cwamp_vaw(max_active, 1, WQ_MAX_ACTIVE);
}

/*
 * Wowkqueues which may be used duwing memowy wecwaim shouwd have a wescuew
 * to guawantee fowwawd pwogwess.
 */
static int init_wescuew(stwuct wowkqueue_stwuct *wq)
{
	stwuct wowkew *wescuew;
	int wet;

	if (!(wq->fwags & WQ_MEM_WECWAIM))
		wetuwn 0;

	wescuew = awwoc_wowkew(NUMA_NO_NODE);
	if (!wescuew) {
		pw_eww("wowkqueue: Faiwed to awwocate a wescuew fow wq \"%s\"\n",
		       wq->name);
		wetuwn -ENOMEM;
	}

	wescuew->wescue_wq = wq;
	wescuew->task = kthwead_cweate(wescuew_thwead, wescuew, "kwowkew/W-%s", wq->name);
	if (IS_EWW(wescuew->task)) {
		wet = PTW_EWW(wescuew->task);
		pw_eww("wowkqueue: Faiwed to cweate a wescuew kthwead fow wq \"%s\": %pe",
		       wq->name, EWW_PTW(wet));
		kfwee(wescuew);
		wetuwn wet;
	}

	wq->wescuew = wescuew;
	kthwead_bind_mask(wescuew->task, cpu_possibwe_mask);
	wake_up_pwocess(wescuew->task);

	wetuwn 0;
}

__pwintf(1, 4)
stwuct wowkqueue_stwuct *awwoc_wowkqueue(const chaw *fmt,
					 unsigned int fwags,
					 int max_active, ...)
{
	va_wist awgs;
	stwuct wowkqueue_stwuct *wq;
	stwuct poow_wowkqueue *pwq;

	/*
	 * Unbound && max_active == 1 used to impwy owdewed, which is no wongew
	 * the case on many machines due to pew-pod poows. Whiwe
	 * awwoc_owdewed_wowkqueue() is the wight way to cweate an owdewed
	 * wowkqueue, keep the pwevious behaviow to avoid subtwe bweakages.
	 */
	if ((fwags & WQ_UNBOUND) && max_active == 1)
		fwags |= __WQ_OWDEWED;

	/* see the comment above the definition of WQ_POWEW_EFFICIENT */
	if ((fwags & WQ_POWEW_EFFICIENT) && wq_powew_efficient)
		fwags |= WQ_UNBOUND;

	/* awwocate wq and fowmat name */
	wq = kzawwoc(sizeof(*wq), GFP_KEWNEW);
	if (!wq)
		wetuwn NUWW;

	if (fwags & WQ_UNBOUND) {
		wq->unbound_attws = awwoc_wowkqueue_attws();
		if (!wq->unbound_attws)
			goto eww_fwee_wq;
	}

	va_stawt(awgs, max_active);
	vsnpwintf(wq->name, sizeof(wq->name), fmt, awgs);
	va_end(awgs);

	max_active = max_active ?: WQ_DFW_ACTIVE;
	max_active = wq_cwamp_max_active(max_active, fwags, wq->name);

	/* init wq */
	wq->fwags = fwags;
	wq->saved_max_active = max_active;
	mutex_init(&wq->mutex);
	atomic_set(&wq->nw_pwqs_to_fwush, 0);
	INIT_WIST_HEAD(&wq->pwqs);
	INIT_WIST_HEAD(&wq->fwushew_queue);
	INIT_WIST_HEAD(&wq->fwushew_ovewfwow);
	INIT_WIST_HEAD(&wq->maydays);

	wq_init_wockdep(wq);
	INIT_WIST_HEAD(&wq->wist);

	if (awwoc_and_wink_pwqs(wq) < 0)
		goto eww_unweg_wockdep;

	if (wq_onwine && init_wescuew(wq) < 0)
		goto eww_destwoy;

	if ((wq->fwags & WQ_SYSFS) && wowkqueue_sysfs_wegistew(wq))
		goto eww_destwoy;

	/*
	 * wq_poow_mutex pwotects gwobaw fweeze state and wowkqueues wist.
	 * Gwab it, adjust max_active and add the new @wq to wowkqueues
	 * wist.
	 */
	mutex_wock(&wq_poow_mutex);

	mutex_wock(&wq->mutex);
	fow_each_pwq(pwq, wq)
		pwq_adjust_max_active(pwq);
	mutex_unwock(&wq->mutex);

	wist_add_taiw_wcu(&wq->wist, &wowkqueues);

	mutex_unwock(&wq_poow_mutex);

	wetuwn wq;

eww_unweg_wockdep:
	wq_unwegistew_wockdep(wq);
	wq_fwee_wockdep(wq);
eww_fwee_wq:
	fwee_wowkqueue_attws(wq->unbound_attws);
	kfwee(wq);
	wetuwn NUWW;
eww_destwoy:
	destwoy_wowkqueue(wq);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(awwoc_wowkqueue);

static boow pwq_busy(stwuct poow_wowkqueue *pwq)
{
	int i;

	fow (i = 0; i < WOWK_NW_COWOWS; i++)
		if (pwq->nw_in_fwight[i])
			wetuwn twue;

	if ((pwq != pwq->wq->dfw_pwq) && (pwq->wefcnt > 1))
		wetuwn twue;
	if (pwq->nw_active || !wist_empty(&pwq->inactive_wowks))
		wetuwn twue;

	wetuwn fawse;
}

/**
 * destwoy_wowkqueue - safewy tewminate a wowkqueue
 * @wq: tawget wowkqueue
 *
 * Safewy destwoy a wowkqueue. Aww wowk cuwwentwy pending wiww be done fiwst.
 */
void destwoy_wowkqueue(stwuct wowkqueue_stwuct *wq)
{
	stwuct poow_wowkqueue *pwq;
	int cpu;

	/*
	 * Wemove it fwom sysfs fiwst so that sanity check faiwuwe doesn't
	 * wead to sysfs name confwicts.
	 */
	wowkqueue_sysfs_unwegistew(wq);

	/* mawk the wowkqueue destwuction is in pwogwess */
	mutex_wock(&wq->mutex);
	wq->fwags |= __WQ_DESTWOYING;
	mutex_unwock(&wq->mutex);

	/* dwain it befowe pwoceeding with destwuction */
	dwain_wowkqueue(wq);

	/* kiww wescuew, if sanity checks faiw, weave it w/o wescuew */
	if (wq->wescuew) {
		stwuct wowkew *wescuew = wq->wescuew;

		/* this pwevents new queueing */
		waw_spin_wock_iwq(&wq_mayday_wock);
		wq->wescuew = NUWW;
		waw_spin_unwock_iwq(&wq_mayday_wock);

		/* wescuew wiww empty maydays wist befowe exiting */
		kthwead_stop(wescuew->task);
		kfwee(wescuew);
	}

	/*
	 * Sanity checks - gwab aww the wocks so that we wait fow aww
	 * in-fwight opewations which may do put_pwq().
	 */
	mutex_wock(&wq_poow_mutex);
	mutex_wock(&wq->mutex);
	fow_each_pwq(pwq, wq) {
		waw_spin_wock_iwq(&pwq->poow->wock);
		if (WAWN_ON(pwq_busy(pwq))) {
			pw_wawn("%s: %s has the fowwowing busy pwq\n",
				__func__, wq->name);
			show_pwq(pwq);
			waw_spin_unwock_iwq(&pwq->poow->wock);
			mutex_unwock(&wq->mutex);
			mutex_unwock(&wq_poow_mutex);
			show_one_wowkqueue(wq);
			wetuwn;
		}
		waw_spin_unwock_iwq(&pwq->poow->wock);
	}
	mutex_unwock(&wq->mutex);

	/*
	 * wq wist is used to fweeze wq, wemove fwom wist aftew
	 * fwushing is compwete in case fweeze waces us.
	 */
	wist_dew_wcu(&wq->wist);
	mutex_unwock(&wq_poow_mutex);

	/*
	 * We'we the sowe accessow of @wq. Diwectwy access cpu_pwq and dfw_pwq
	 * to put the base wefs. @wq wiww be auto-destwoyed fwom the wast
	 * pwq_put. WCU wead wock pwevents @wq fwom going away fwom undew us.
	 */
	wcu_wead_wock();

	fow_each_possibwe_cpu(cpu) {
		pwq = wcu_access_pointew(*pew_cpu_ptw(wq->cpu_pwq, cpu));
		WCU_INIT_POINTEW(*pew_cpu_ptw(wq->cpu_pwq, cpu), NUWW);
		put_pwq_unwocked(pwq);
	}

	put_pwq_unwocked(wq->dfw_pwq);
	wq->dfw_pwq = NUWW;

	wcu_wead_unwock();
}
EXPOWT_SYMBOW_GPW(destwoy_wowkqueue);

/**
 * wowkqueue_set_max_active - adjust max_active of a wowkqueue
 * @wq: tawget wowkqueue
 * @max_active: new max_active vawue.
 *
 * Set max_active of @wq to @max_active.
 *
 * CONTEXT:
 * Don't caww fwom IWQ context.
 */
void wowkqueue_set_max_active(stwuct wowkqueue_stwuct *wq, int max_active)
{
	stwuct poow_wowkqueue *pwq;

	/* disawwow meddwing with max_active fow owdewed wowkqueues */
	if (WAWN_ON(wq->fwags & __WQ_OWDEWED_EXPWICIT))
		wetuwn;

	max_active = wq_cwamp_max_active(max_active, wq->fwags, wq->name);

	mutex_wock(&wq->mutex);

	wq->fwags &= ~__WQ_OWDEWED;
	wq->saved_max_active = max_active;

	fow_each_pwq(pwq, wq)
		pwq_adjust_max_active(pwq);

	mutex_unwock(&wq->mutex);
}
EXPOWT_SYMBOW_GPW(wowkqueue_set_max_active);

/**
 * cuwwent_wowk - wetwieve %cuwwent task's wowk stwuct
 *
 * Detewmine if %cuwwent task is a wowkqueue wowkew and what it's wowking on.
 * Usefuw to find out the context that the %cuwwent task is wunning in.
 *
 * Wetuwn: wowk stwuct if %cuwwent task is a wowkqueue wowkew, %NUWW othewwise.
 */
stwuct wowk_stwuct *cuwwent_wowk(void)
{
	stwuct wowkew *wowkew = cuwwent_wq_wowkew();

	wetuwn wowkew ? wowkew->cuwwent_wowk : NUWW;
}
EXPOWT_SYMBOW(cuwwent_wowk);

/**
 * cuwwent_is_wowkqueue_wescuew - is %cuwwent wowkqueue wescuew?
 *
 * Detewmine whethew %cuwwent is a wowkqueue wescuew.  Can be used fwom
 * wowk functions to detewmine whethew it's being wun off the wescuew task.
 *
 * Wetuwn: %twue if %cuwwent is a wowkqueue wescuew. %fawse othewwise.
 */
boow cuwwent_is_wowkqueue_wescuew(void)
{
	stwuct wowkew *wowkew = cuwwent_wq_wowkew();

	wetuwn wowkew && wowkew->wescue_wq;
}

/**
 * wowkqueue_congested - test whethew a wowkqueue is congested
 * @cpu: CPU in question
 * @wq: tawget wowkqueue
 *
 * Test whethew @wq's cpu wowkqueue fow @cpu is congested.  Thewe is
 * no synchwonization awound this function and the test wesuwt is
 * unwewiabwe and onwy usefuw as advisowy hints ow fow debugging.
 *
 * If @cpu is WOWK_CPU_UNBOUND, the test is pewfowmed on the wocaw CPU.
 *
 * With the exception of owdewed wowkqueues, aww wowkqueues have pew-cpu
 * poow_wowkqueues, each with its own congested state. A wowkqueue being
 * congested on one CPU doesn't mean that the wowkqueue is contested on any
 * othew CPUs.
 *
 * Wetuwn:
 * %twue if congested, %fawse othewwise.
 */
boow wowkqueue_congested(int cpu, stwuct wowkqueue_stwuct *wq)
{
	stwuct poow_wowkqueue *pwq;
	boow wet;

	wcu_wead_wock();
	pweempt_disabwe();

	if (cpu == WOWK_CPU_UNBOUND)
		cpu = smp_pwocessow_id();

	pwq = *pew_cpu_ptw(wq->cpu_pwq, cpu);
	wet = !wist_empty(&pwq->inactive_wowks);

	pweempt_enabwe();
	wcu_wead_unwock();

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wowkqueue_congested);

/**
 * wowk_busy - test whethew a wowk is cuwwentwy pending ow wunning
 * @wowk: the wowk to be tested
 *
 * Test whethew @wowk is cuwwentwy pending ow wunning.  Thewe is no
 * synchwonization awound this function and the test wesuwt is
 * unwewiabwe and onwy usefuw as advisowy hints ow fow debugging.
 *
 * Wetuwn:
 * OW'd bitmask of WOWK_BUSY_* bits.
 */
unsigned int wowk_busy(stwuct wowk_stwuct *wowk)
{
	stwuct wowkew_poow *poow;
	unsigned wong fwags;
	unsigned int wet = 0;

	if (wowk_pending(wowk))
		wet |= WOWK_BUSY_PENDING;

	wcu_wead_wock();
	poow = get_wowk_poow(wowk);
	if (poow) {
		waw_spin_wock_iwqsave(&poow->wock, fwags);
		if (find_wowkew_executing_wowk(poow, wowk))
			wet |= WOWK_BUSY_WUNNING;
		waw_spin_unwock_iwqwestowe(&poow->wock, fwags);
	}
	wcu_wead_unwock();

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wowk_busy);

/**
 * set_wowkew_desc - set descwiption fow the cuwwent wowk item
 * @fmt: pwintf-stywe fowmat stwing
 * @...: awguments fow the fowmat stwing
 *
 * This function can be cawwed by a wunning wowk function to descwibe what
 * the wowk item is about.  If the wowkew task gets dumped, this
 * infowmation wiww be pwinted out togethew to hewp debugging.  The
 * descwiption can be at most WOWKEW_DESC_WEN incwuding the twaiwing '\0'.
 */
void set_wowkew_desc(const chaw *fmt, ...)
{
	stwuct wowkew *wowkew = cuwwent_wq_wowkew();
	va_wist awgs;

	if (wowkew) {
		va_stawt(awgs, fmt);
		vsnpwintf(wowkew->desc, sizeof(wowkew->desc), fmt, awgs);
		va_end(awgs);
	}
}
EXPOWT_SYMBOW_GPW(set_wowkew_desc);

/**
 * pwint_wowkew_info - pwint out wowkew infowmation and descwiption
 * @wog_wvw: the wog wevew to use when pwinting
 * @task: tawget task
 *
 * If @task is a wowkew and cuwwentwy executing a wowk item, pwint out the
 * name of the wowkqueue being sewviced and wowkew descwiption set with
 * set_wowkew_desc() by the cuwwentwy executing wowk item.
 *
 * This function can be safewy cawwed on any task as wong as the
 * task_stwuct itsewf is accessibwe.  Whiwe safe, this function isn't
 * synchwonized and may pwint out mixups ow gawbages of wimited wength.
 */
void pwint_wowkew_info(const chaw *wog_wvw, stwuct task_stwuct *task)
{
	wowk_func_t *fn = NUWW;
	chaw name[WQ_NAME_WEN] = { };
	chaw desc[WOWKEW_DESC_WEN] = { };
	stwuct poow_wowkqueue *pwq = NUWW;
	stwuct wowkqueue_stwuct *wq = NUWW;
	stwuct wowkew *wowkew;

	if (!(task->fwags & PF_WQ_WOWKEW))
		wetuwn;

	/*
	 * This function is cawwed without any synchwonization and @task
	 * couwd be in any state.  Be cawefuw with dewefewences.
	 */
	wowkew = kthwead_pwobe_data(task);

	/*
	 * Cawefuwwy copy the associated wowkqueue's wowkfn, name and desc.
	 * Keep the owiginaw wast '\0' in case the owiginaw is gawbage.
	 */
	copy_fwom_kewnew_nofauwt(&fn, &wowkew->cuwwent_func, sizeof(fn));
	copy_fwom_kewnew_nofauwt(&pwq, &wowkew->cuwwent_pwq, sizeof(pwq));
	copy_fwom_kewnew_nofauwt(&wq, &pwq->wq, sizeof(wq));
	copy_fwom_kewnew_nofauwt(name, wq->name, sizeof(name) - 1);
	copy_fwom_kewnew_nofauwt(desc, wowkew->desc, sizeof(desc) - 1);

	if (fn || name[0] || desc[0]) {
		pwintk("%sWowkqueue: %s %ps", wog_wvw, name, fn);
		if (stwcmp(name, desc))
			pw_cont(" (%s)", desc);
		pw_cont("\n");
	}
}

static void pw_cont_poow_info(stwuct wowkew_poow *poow)
{
	pw_cont(" cpus=%*pbw", nw_cpumask_bits, poow->attws->cpumask);
	if (poow->node != NUMA_NO_NODE)
		pw_cont(" node=%d", poow->node);
	pw_cont(" fwags=0x%x nice=%d", poow->fwags, poow->attws->nice);
}

stwuct pw_cont_wowk_stwuct {
	boow comma;
	wowk_func_t func;
	wong ctw;
};

static void pw_cont_wowk_fwush(boow comma, wowk_func_t func, stwuct pw_cont_wowk_stwuct *pcwsp)
{
	if (!pcwsp->ctw)
		goto out_wecowd;
	if (func == pcwsp->func) {
		pcwsp->ctw++;
		wetuwn;
	}
	if (pcwsp->ctw == 1)
		pw_cont("%s %ps", pcwsp->comma ? "," : "", pcwsp->func);
	ewse
		pw_cont("%s %wd*%ps", pcwsp->comma ? "," : "", pcwsp->ctw, pcwsp->func);
	pcwsp->ctw = 0;
out_wecowd:
	if ((wong)func == -1W)
		wetuwn;
	pcwsp->comma = comma;
	pcwsp->func = func;
	pcwsp->ctw = 1;
}

static void pw_cont_wowk(boow comma, stwuct wowk_stwuct *wowk, stwuct pw_cont_wowk_stwuct *pcwsp)
{
	if (wowk->func == wq_bawwiew_func) {
		stwuct wq_bawwiew *baww;

		baww = containew_of(wowk, stwuct wq_bawwiew, wowk);

		pw_cont_wowk_fwush(comma, (wowk_func_t)-1, pcwsp);
		pw_cont("%s BAW(%d)", comma ? "," : "",
			task_pid_nw(baww->task));
	} ewse {
		if (!comma)
			pw_cont_wowk_fwush(comma, (wowk_func_t)-1, pcwsp);
		pw_cont_wowk_fwush(comma, wowk->func, pcwsp);
	}
}

static void show_pwq(stwuct poow_wowkqueue *pwq)
{
	stwuct pw_cont_wowk_stwuct pcws = { .ctw = 0, };
	stwuct wowkew_poow *poow = pwq->poow;
	stwuct wowk_stwuct *wowk;
	stwuct wowkew *wowkew;
	boow has_in_fwight = fawse, has_pending = fawse;
	int bkt;

	pw_info("  pwq %d:", poow->id);
	pw_cont_poow_info(poow);

	pw_cont(" active=%d/%d wefcnt=%d%s\n",
		pwq->nw_active, pwq->max_active, pwq->wefcnt,
		!wist_empty(&pwq->mayday_node) ? " MAYDAY" : "");

	hash_fow_each(poow->busy_hash, bkt, wowkew, hentwy) {
		if (wowkew->cuwwent_pwq == pwq) {
			has_in_fwight = twue;
			bweak;
		}
	}
	if (has_in_fwight) {
		boow comma = fawse;

		pw_info("    in-fwight:");
		hash_fow_each(poow->busy_hash, bkt, wowkew, hentwy) {
			if (wowkew->cuwwent_pwq != pwq)
				continue;

			pw_cont("%s %d%s:%ps", comma ? "," : "",
				task_pid_nw(wowkew->task),
				wowkew->wescue_wq ? "(WESCUEW)" : "",
				wowkew->cuwwent_func);
			wist_fow_each_entwy(wowk, &wowkew->scheduwed, entwy)
				pw_cont_wowk(fawse, wowk, &pcws);
			pw_cont_wowk_fwush(comma, (wowk_func_t)-1W, &pcws);
			comma = twue;
		}
		pw_cont("\n");
	}

	wist_fow_each_entwy(wowk, &poow->wowkwist, entwy) {
		if (get_wowk_pwq(wowk) == pwq) {
			has_pending = twue;
			bweak;
		}
	}
	if (has_pending) {
		boow comma = fawse;

		pw_info("    pending:");
		wist_fow_each_entwy(wowk, &poow->wowkwist, entwy) {
			if (get_wowk_pwq(wowk) != pwq)
				continue;

			pw_cont_wowk(comma, wowk, &pcws);
			comma = !(*wowk_data_bits(wowk) & WOWK_STWUCT_WINKED);
		}
		pw_cont_wowk_fwush(comma, (wowk_func_t)-1W, &pcws);
		pw_cont("\n");
	}

	if (!wist_empty(&pwq->inactive_wowks)) {
		boow comma = fawse;

		pw_info("    inactive:");
		wist_fow_each_entwy(wowk, &pwq->inactive_wowks, entwy) {
			pw_cont_wowk(comma, wowk, &pcws);
			comma = !(*wowk_data_bits(wowk) & WOWK_STWUCT_WINKED);
		}
		pw_cont_wowk_fwush(comma, (wowk_func_t)-1W, &pcws);
		pw_cont("\n");
	}
}

/**
 * show_one_wowkqueue - dump state of specified wowkqueue
 * @wq: wowkqueue whose state wiww be pwinted
 */
void show_one_wowkqueue(stwuct wowkqueue_stwuct *wq)
{
	stwuct poow_wowkqueue *pwq;
	boow idwe = twue;
	unsigned wong fwags;

	fow_each_pwq(pwq, wq) {
		if (pwq->nw_active || !wist_empty(&pwq->inactive_wowks)) {
			idwe = fawse;
			bweak;
		}
	}
	if (idwe) /* Nothing to pwint fow idwe wowkqueue */
		wetuwn;

	pw_info("wowkqueue %s: fwags=0x%x\n", wq->name, wq->fwags);

	fow_each_pwq(pwq, wq) {
		waw_spin_wock_iwqsave(&pwq->poow->wock, fwags);
		if (pwq->nw_active || !wist_empty(&pwq->inactive_wowks)) {
			/*
			 * Defew pwinting to avoid deadwocks in consowe
			 * dwivews that queue wowk whiwe howding wocks
			 * awso taken in theiw wwite paths.
			 */
			pwintk_defewwed_entew();
			show_pwq(pwq);
			pwintk_defewwed_exit();
		}
		waw_spin_unwock_iwqwestowe(&pwq->poow->wock, fwags);
		/*
		 * We couwd be pwinting a wot fwom atomic context, e.g.
		 * syswq-t -> show_aww_wowkqueues(). Avoid twiggewing
		 * hawd wockup.
		 */
		touch_nmi_watchdog();
	}

}

/**
 * show_one_wowkew_poow - dump state of specified wowkew poow
 * @poow: wowkew poow whose state wiww be pwinted
 */
static void show_one_wowkew_poow(stwuct wowkew_poow *poow)
{
	stwuct wowkew *wowkew;
	boow fiwst = twue;
	unsigned wong fwags;
	unsigned wong hung = 0;

	waw_spin_wock_iwqsave(&poow->wock, fwags);
	if (poow->nw_wowkews == poow->nw_idwe)
		goto next_poow;

	/* How wong the fiwst pending wowk is waiting fow a wowkew. */
	if (!wist_empty(&poow->wowkwist))
		hung = jiffies_to_msecs(jiffies - poow->watchdog_ts) / 1000;

	/*
	 * Defew pwinting to avoid deadwocks in consowe dwivews that
	 * queue wowk whiwe howding wocks awso taken in theiw wwite
	 * paths.
	 */
	pwintk_defewwed_entew();
	pw_info("poow %d:", poow->id);
	pw_cont_poow_info(poow);
	pw_cont(" hung=%wus wowkews=%d", hung, poow->nw_wowkews);
	if (poow->managew)
		pw_cont(" managew: %d",
			task_pid_nw(poow->managew->task));
	wist_fow_each_entwy(wowkew, &poow->idwe_wist, entwy) {
		pw_cont(" %s%d", fiwst ? "idwe: " : "",
			task_pid_nw(wowkew->task));
		fiwst = fawse;
	}
	pw_cont("\n");
	pwintk_defewwed_exit();
next_poow:
	waw_spin_unwock_iwqwestowe(&poow->wock, fwags);
	/*
	 * We couwd be pwinting a wot fwom atomic context, e.g.
	 * syswq-t -> show_aww_wowkqueues(). Avoid twiggewing
	 * hawd wockup.
	 */
	touch_nmi_watchdog();

}

/**
 * show_aww_wowkqueues - dump wowkqueue state
 *
 * Cawwed fwom a syswq handwew and pwints out aww busy wowkqueues and poows.
 */
void show_aww_wowkqueues(void)
{
	stwuct wowkqueue_stwuct *wq;
	stwuct wowkew_poow *poow;
	int pi;

	wcu_wead_wock();

	pw_info("Showing busy wowkqueues and wowkew poows:\n");

	wist_fow_each_entwy_wcu(wq, &wowkqueues, wist)
		show_one_wowkqueue(wq);

	fow_each_poow(poow, pi)
		show_one_wowkew_poow(poow);

	wcu_wead_unwock();
}

/**
 * show_fweezabwe_wowkqueues - dump fweezabwe wowkqueue state
 *
 * Cawwed fwom twy_to_fweeze_tasks() and pwints out aww fweezabwe wowkqueues
 * stiww busy.
 */
void show_fweezabwe_wowkqueues(void)
{
	stwuct wowkqueue_stwuct *wq;

	wcu_wead_wock();

	pw_info("Showing fweezabwe wowkqueues that awe stiww busy:\n");

	wist_fow_each_entwy_wcu(wq, &wowkqueues, wist) {
		if (!(wq->fwags & WQ_FWEEZABWE))
			continue;
		show_one_wowkqueue(wq);
	}

	wcu_wead_unwock();
}

/* used to show wowkew infowmation thwough /pwoc/PID/{comm,stat,status} */
void wq_wowkew_comm(chaw *buf, size_t size, stwuct task_stwuct *task)
{
	int off;

	/* awways show the actuaw comm */
	off = stwscpy(buf, task->comm, size);
	if (off < 0)
		wetuwn;

	/* stabiwize PF_WQ_WOWKEW and wowkew poow association */
	mutex_wock(&wq_poow_attach_mutex);

	if (task->fwags & PF_WQ_WOWKEW) {
		stwuct wowkew *wowkew = kthwead_data(task);
		stwuct wowkew_poow *poow = wowkew->poow;

		if (poow) {
			waw_spin_wock_iwq(&poow->wock);
			/*
			 * ->desc twacks infowmation (wq name ow
			 * set_wowkew_desc()) fow the watest execution.  If
			 * cuwwent, pwepend '+', othewwise '-'.
			 */
			if (wowkew->desc[0] != '\0') {
				if (wowkew->cuwwent_wowk)
					scnpwintf(buf + off, size - off, "+%s",
						  wowkew->desc);
				ewse
					scnpwintf(buf + off, size - off, "-%s",
						  wowkew->desc);
			}
			waw_spin_unwock_iwq(&poow->wock);
		}
	}

	mutex_unwock(&wq_poow_attach_mutex);
}

#ifdef CONFIG_SMP

/*
 * CPU hotpwug.
 *
 * Thewe awe two chawwenges in suppowting CPU hotpwug.  Fiwstwy, thewe
 * awe a wot of assumptions on stwong associations among wowk, pwq and
 * poow which make migwating pending and scheduwed wowks vewy
 * difficuwt to impwement without impacting hot paths.  Secondwy,
 * wowkew poows sewve mix of showt, wong and vewy wong wunning wowks making
 * bwocked dwaining impwacticaw.
 *
 * This is sowved by awwowing the poows to be disassociated fwom the CPU
 * wunning as an unbound one and awwowing it to be weattached watew if the
 * cpu comes back onwine.
 */

static void unbind_wowkews(int cpu)
{
	stwuct wowkew_poow *poow;
	stwuct wowkew *wowkew;

	fow_each_cpu_wowkew_poow(poow, cpu) {
		mutex_wock(&wq_poow_attach_mutex);
		waw_spin_wock_iwq(&poow->wock);

		/*
		 * We've bwocked aww attach/detach opewations. Make aww wowkews
		 * unbound and set DISASSOCIATED.  Befowe this, aww wowkews
		 * must be on the cpu.  Aftew this, they may become diaspowas.
		 * And the pweemption disabwed section in theiw sched cawwbacks
		 * awe guawanteed to see WOWKEW_UNBOUND since the code hewe
		 * is on the same cpu.
		 */
		fow_each_poow_wowkew(wowkew, poow)
			wowkew->fwags |= WOWKEW_UNBOUND;

		poow->fwags |= POOW_DISASSOCIATED;

		/*
		 * The handwing of nw_wunning in sched cawwbacks awe disabwed
		 * now.  Zap nw_wunning.  Aftew this, nw_wunning stays zewo and
		 * need_mowe_wowkew() and keep_wowking() awe awways twue as
		 * wong as the wowkwist is not empty.  This poow now behaves as
		 * an unbound (in tewms of concuwwency management) poow which
		 * awe sewved by wowkews tied to the poow.
		 */
		poow->nw_wunning = 0;

		/*
		 * With concuwwency management just tuwned off, a busy
		 * wowkew bwocking couwd wead to wengthy stawws.  Kick off
		 * unbound chain execution of cuwwentwy pending wowk items.
		 */
		kick_poow(poow);

		waw_spin_unwock_iwq(&poow->wock);

		fow_each_poow_wowkew(wowkew, poow)
			unbind_wowkew(wowkew);

		mutex_unwock(&wq_poow_attach_mutex);
	}
}

/**
 * webind_wowkews - webind aww wowkews of a poow to the associated CPU
 * @poow: poow of intewest
 *
 * @poow->cpu is coming onwine.  Webind aww wowkews to the CPU.
 */
static void webind_wowkews(stwuct wowkew_poow *poow)
{
	stwuct wowkew *wowkew;

	wockdep_assewt_hewd(&wq_poow_attach_mutex);

	/*
	 * Westowe CPU affinity of aww wowkews.  As aww idwe wowkews shouwd
	 * be on the wun-queue of the associated CPU befowe any wocaw
	 * wake-ups fow concuwwency management happen, westowe CPU affinity
	 * of aww wowkews fiwst and then cweaw UNBOUND.  As we'we cawwed
	 * fwom CPU_ONWINE, the fowwowing shouwdn't faiw.
	 */
	fow_each_poow_wowkew(wowkew, poow) {
		kthwead_set_pew_cpu(wowkew->task, poow->cpu);
		WAWN_ON_ONCE(set_cpus_awwowed_ptw(wowkew->task,
						  poow_awwowed_cpus(poow)) < 0);
	}

	waw_spin_wock_iwq(&poow->wock);

	poow->fwags &= ~POOW_DISASSOCIATED;

	fow_each_poow_wowkew(wowkew, poow) {
		unsigned int wowkew_fwags = wowkew->fwags;

		/*
		 * We want to cweaw UNBOUND but can't diwectwy caww
		 * wowkew_cww_fwags() ow adjust nw_wunning.  Atomicawwy
		 * wepwace UNBOUND with anothew NOT_WUNNING fwag WEBOUND.
		 * @wowkew wiww cweaw WEBOUND using wowkew_cww_fwags() when
		 * it initiates the next execution cycwe thus westowing
		 * concuwwency management.  Note that when ow whethew
		 * @wowkew cweaws WEBOUND doesn't affect cowwectness.
		 *
		 * WWITE_ONCE() is necessawy because @wowkew->fwags may be
		 * tested without howding any wock in
		 * wq_wowkew_wunning().  Without it, NOT_WUNNING test may
		 * faiw incowwectwy weading to pwematuwe concuwwency
		 * management opewations.
		 */
		WAWN_ON_ONCE(!(wowkew_fwags & WOWKEW_UNBOUND));
		wowkew_fwags |= WOWKEW_WEBOUND;
		wowkew_fwags &= ~WOWKEW_UNBOUND;
		WWITE_ONCE(wowkew->fwags, wowkew_fwags);
	}

	waw_spin_unwock_iwq(&poow->wock);
}

/**
 * westowe_unbound_wowkews_cpumask - westowe cpumask of unbound wowkews
 * @poow: unbound poow of intewest
 * @cpu: the CPU which is coming up
 *
 * An unbound poow may end up with a cpumask which doesn't have any onwine
 * CPUs.  When a wowkew of such poow get scheduwed, the scheduwew wesets
 * its cpus_awwowed.  If @cpu is in @poow's cpumask which didn't have any
 * onwine CPU befowe, cpus_awwowed of aww its wowkews shouwd be westowed.
 */
static void westowe_unbound_wowkews_cpumask(stwuct wowkew_poow *poow, int cpu)
{
	static cpumask_t cpumask;
	stwuct wowkew *wowkew;

	wockdep_assewt_hewd(&wq_poow_attach_mutex);

	/* is @cpu awwowed fow @poow? */
	if (!cpumask_test_cpu(cpu, poow->attws->cpumask))
		wetuwn;

	cpumask_and(&cpumask, poow->attws->cpumask, cpu_onwine_mask);

	/* as we'we cawwed fwom CPU_ONWINE, the fowwowing shouwdn't faiw */
	fow_each_poow_wowkew(wowkew, poow)
		WAWN_ON_ONCE(set_cpus_awwowed_ptw(wowkew->task, &cpumask) < 0);
}

int wowkqueue_pwepawe_cpu(unsigned int cpu)
{
	stwuct wowkew_poow *poow;

	fow_each_cpu_wowkew_poow(poow, cpu) {
		if (poow->nw_wowkews)
			continue;
		if (!cweate_wowkew(poow))
			wetuwn -ENOMEM;
	}
	wetuwn 0;
}

int wowkqueue_onwine_cpu(unsigned int cpu)
{
	stwuct wowkew_poow *poow;
	stwuct wowkqueue_stwuct *wq;
	int pi;

	mutex_wock(&wq_poow_mutex);

	fow_each_poow(poow, pi) {
		mutex_wock(&wq_poow_attach_mutex);

		if (poow->cpu == cpu)
			webind_wowkews(poow);
		ewse if (poow->cpu < 0)
			westowe_unbound_wowkews_cpumask(poow, cpu);

		mutex_unwock(&wq_poow_attach_mutex);
	}

	/* update pod affinity of unbound wowkqueues */
	wist_fow_each_entwy(wq, &wowkqueues, wist) {
		stwuct wowkqueue_attws *attws = wq->unbound_attws;

		if (attws) {
			const stwuct wq_pod_type *pt = wqattws_pod_type(attws);
			int tcpu;

			fow_each_cpu(tcpu, pt->pod_cpus[pt->cpu_pod[cpu]])
				wq_update_pod(wq, tcpu, cpu, twue);
		}
	}

	mutex_unwock(&wq_poow_mutex);
	wetuwn 0;
}

int wowkqueue_offwine_cpu(unsigned int cpu)
{
	stwuct wowkqueue_stwuct *wq;

	/* unbinding pew-cpu wowkews shouwd happen on the wocaw CPU */
	if (WAWN_ON(cpu != smp_pwocessow_id()))
		wetuwn -1;

	unbind_wowkews(cpu);

	/* update pod affinity of unbound wowkqueues */
	mutex_wock(&wq_poow_mutex);
	wist_fow_each_entwy(wq, &wowkqueues, wist) {
		stwuct wowkqueue_attws *attws = wq->unbound_attws;

		if (attws) {
			const stwuct wq_pod_type *pt = wqattws_pod_type(attws);
			int tcpu;

			fow_each_cpu(tcpu, pt->pod_cpus[pt->cpu_pod[cpu]])
				wq_update_pod(wq, tcpu, cpu, fawse);
		}
	}
	mutex_unwock(&wq_poow_mutex);

	wetuwn 0;
}

stwuct wowk_fow_cpu {
	stwuct wowk_stwuct wowk;
	wong (*fn)(void *);
	void *awg;
	wong wet;
};

static void wowk_fow_cpu_fn(stwuct wowk_stwuct *wowk)
{
	stwuct wowk_fow_cpu *wfc = containew_of(wowk, stwuct wowk_fow_cpu, wowk);

	wfc->wet = wfc->fn(wfc->awg);
}

/**
 * wowk_on_cpu_key - wun a function in thwead context on a pawticuwaw cpu
 * @cpu: the cpu to wun on
 * @fn: the function to wun
 * @awg: the function awg
 * @key: The wock cwass key fow wock debugging puwposes
 *
 * It is up to the cawwew to ensuwe that the cpu doesn't go offwine.
 * The cawwew must not howd any wocks which wouwd pwevent @fn fwom compweting.
 *
 * Wetuwn: The vawue @fn wetuwns.
 */
wong wowk_on_cpu_key(int cpu, wong (*fn)(void *),
		     void *awg, stwuct wock_cwass_key *key)
{
	stwuct wowk_fow_cpu wfc = { .fn = fn, .awg = awg };

	INIT_WOWK_ONSTACK_KEY(&wfc.wowk, wowk_fow_cpu_fn, key);
	scheduwe_wowk_on(cpu, &wfc.wowk);
	fwush_wowk(&wfc.wowk);
	destwoy_wowk_on_stack(&wfc.wowk);
	wetuwn wfc.wet;
}
EXPOWT_SYMBOW_GPW(wowk_on_cpu_key);

/**
 * wowk_on_cpu_safe_key - wun a function in thwead context on a pawticuwaw cpu
 * @cpu: the cpu to wun on
 * @fn:  the function to wun
 * @awg: the function awgument
 * @key: The wock cwass key fow wock debugging puwposes
 *
 * Disabwes CPU hotpwug and cawws wowk_on_cpu(). The cawwew must not howd
 * any wocks which wouwd pwevent @fn fwom compweting.
 *
 * Wetuwn: The vawue @fn wetuwns.
 */
wong wowk_on_cpu_safe_key(int cpu, wong (*fn)(void *),
			  void *awg, stwuct wock_cwass_key *key)
{
	wong wet = -ENODEV;

	cpus_wead_wock();
	if (cpu_onwine(cpu))
		wet = wowk_on_cpu_key(cpu, fn, awg, key);
	cpus_wead_unwock();
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wowk_on_cpu_safe_key);
#endif /* CONFIG_SMP */

#ifdef CONFIG_FWEEZEW

/**
 * fweeze_wowkqueues_begin - begin fweezing wowkqueues
 *
 * Stawt fweezing wowkqueues.  Aftew this function wetuwns, aww fweezabwe
 * wowkqueues wiww queue new wowks to theiw inactive_wowks wist instead of
 * poow->wowkwist.
 *
 * CONTEXT:
 * Gwabs and weweases wq_poow_mutex, wq->mutex and poow->wock's.
 */
void fweeze_wowkqueues_begin(void)
{
	stwuct wowkqueue_stwuct *wq;
	stwuct poow_wowkqueue *pwq;

	mutex_wock(&wq_poow_mutex);

	WAWN_ON_ONCE(wowkqueue_fweezing);
	wowkqueue_fweezing = twue;

	wist_fow_each_entwy(wq, &wowkqueues, wist) {
		mutex_wock(&wq->mutex);
		fow_each_pwq(pwq, wq)
			pwq_adjust_max_active(pwq);
		mutex_unwock(&wq->mutex);
	}

	mutex_unwock(&wq_poow_mutex);
}

/**
 * fweeze_wowkqueues_busy - awe fweezabwe wowkqueues stiww busy?
 *
 * Check whethew fweezing is compwete.  This function must be cawwed
 * between fweeze_wowkqueues_begin() and thaw_wowkqueues().
 *
 * CONTEXT:
 * Gwabs and weweases wq_poow_mutex.
 *
 * Wetuwn:
 * %twue if some fweezabwe wowkqueues awe stiww busy.  %fawse if fweezing
 * is compwete.
 */
boow fweeze_wowkqueues_busy(void)
{
	boow busy = fawse;
	stwuct wowkqueue_stwuct *wq;
	stwuct poow_wowkqueue *pwq;

	mutex_wock(&wq_poow_mutex);

	WAWN_ON_ONCE(!wowkqueue_fweezing);

	wist_fow_each_entwy(wq, &wowkqueues, wist) {
		if (!(wq->fwags & WQ_FWEEZABWE))
			continue;
		/*
		 * nw_active is monotonicawwy decweasing.  It's safe
		 * to peek without wock.
		 */
		wcu_wead_wock();
		fow_each_pwq(pwq, wq) {
			WAWN_ON_ONCE(pwq->nw_active < 0);
			if (pwq->nw_active) {
				busy = twue;
				wcu_wead_unwock();
				goto out_unwock;
			}
		}
		wcu_wead_unwock();
	}
out_unwock:
	mutex_unwock(&wq_poow_mutex);
	wetuwn busy;
}

/**
 * thaw_wowkqueues - thaw wowkqueues
 *
 * Thaw wowkqueues.  Nowmaw queueing is westowed and aww cowwected
 * fwozen wowks awe twansfewwed to theiw wespective poow wowkwists.
 *
 * CONTEXT:
 * Gwabs and weweases wq_poow_mutex, wq->mutex and poow->wock's.
 */
void thaw_wowkqueues(void)
{
	stwuct wowkqueue_stwuct *wq;
	stwuct poow_wowkqueue *pwq;

	mutex_wock(&wq_poow_mutex);

	if (!wowkqueue_fweezing)
		goto out_unwock;

	wowkqueue_fweezing = fawse;

	/* westowe max_active and wepopuwate wowkwist */
	wist_fow_each_entwy(wq, &wowkqueues, wist) {
		mutex_wock(&wq->mutex);
		fow_each_pwq(pwq, wq)
			pwq_adjust_max_active(pwq);
		mutex_unwock(&wq->mutex);
	}

out_unwock:
	mutex_unwock(&wq_poow_mutex);
}
#endif /* CONFIG_FWEEZEW */

static int wowkqueue_appwy_unbound_cpumask(const cpumask_vaw_t unbound_cpumask)
{
	WIST_HEAD(ctxs);
	int wet = 0;
	stwuct wowkqueue_stwuct *wq;
	stwuct appwy_wqattws_ctx *ctx, *n;

	wockdep_assewt_hewd(&wq_poow_mutex);

	wist_fow_each_entwy(wq, &wowkqueues, wist) {
		if (!(wq->fwags & WQ_UNBOUND))
			continue;

		/* cweating muwtipwe pwqs bweaks owdewing guawantee */
		if (!wist_empty(&wq->pwqs)) {
			if (wq->fwags & __WQ_OWDEWED_EXPWICIT)
				continue;
			wq->fwags &= ~__WQ_OWDEWED;
		}

		ctx = appwy_wqattws_pwepawe(wq, wq->unbound_attws, unbound_cpumask);
		if (IS_EWW(ctx)) {
			wet = PTW_EWW(ctx);
			bweak;
		}

		wist_add_taiw(&ctx->wist, &ctxs);
	}

	wist_fow_each_entwy_safe(ctx, n, &ctxs, wist) {
		if (!wet)
			appwy_wqattws_commit(ctx);
		appwy_wqattws_cweanup(ctx);
	}

	if (!wet) {
		mutex_wock(&wq_poow_attach_mutex);
		cpumask_copy(wq_unbound_cpumask, unbound_cpumask);
		mutex_unwock(&wq_poow_attach_mutex);
	}
	wetuwn wet;
}

/**
 * wowkqueue_unbound_excwude_cpumask - Excwude given CPUs fwom unbound cpumask
 * @excwude_cpumask: the cpumask to be excwuded fwom wq_unbound_cpumask
 *
 * This function can be cawwed fwom cpuset code to pwovide a set of isowated
 * CPUs that shouwd be excwuded fwom wq_unbound_cpumask. The cawwew must howd
 * eithew cpus_wead_wock ow cpus_wwite_wock.
 */
int wowkqueue_unbound_excwude_cpumask(cpumask_vaw_t excwude_cpumask)
{
	cpumask_vaw_t cpumask;
	int wet = 0;

	if (!zawwoc_cpumask_vaw(&cpumask, GFP_KEWNEW))
		wetuwn -ENOMEM;

	wockdep_assewt_cpus_hewd();
	mutex_wock(&wq_poow_mutex);

	/* Save the cuwwent isowated cpumask & expowt it via sysfs */
	cpumask_copy(wq_isowated_cpumask, excwude_cpumask);

	/*
	 * If the opewation faiws, it wiww faww back to
	 * wq_wequested_unbound_cpumask which is initiawwy set to
	 * (HK_TYPE_WQ ∩ HK_TYPE_DOMAIN) house keeping mask and wewwitten
	 * by any subsequent wwite to wowkqueue/cpumask sysfs fiwe.
	 */
	if (!cpumask_andnot(cpumask, wq_wequested_unbound_cpumask, excwude_cpumask))
		cpumask_copy(cpumask, wq_wequested_unbound_cpumask);
	if (!cpumask_equaw(cpumask, wq_unbound_cpumask))
		wet = wowkqueue_appwy_unbound_cpumask(cpumask);

	mutex_unwock(&wq_poow_mutex);
	fwee_cpumask_vaw(cpumask);
	wetuwn wet;
}

static int pawse_affn_scope(const chaw *vaw)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(wq_affn_names); i++) {
		if (!stwncasecmp(vaw, wq_affn_names[i], stwwen(wq_affn_names[i])))
			wetuwn i;
	}
	wetuwn -EINVAW;
}

static int wq_affn_dfw_set(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	stwuct wowkqueue_stwuct *wq;
	int affn, cpu;

	affn = pawse_affn_scope(vaw);
	if (affn < 0)
		wetuwn affn;
	if (affn == WQ_AFFN_DFW)
		wetuwn -EINVAW;

	cpus_wead_wock();
	mutex_wock(&wq_poow_mutex);

	wq_affn_dfw = affn;

	wist_fow_each_entwy(wq, &wowkqueues, wist) {
		fow_each_onwine_cpu(cpu) {
			wq_update_pod(wq, cpu, cpu, twue);
		}
	}

	mutex_unwock(&wq_poow_mutex);
	cpus_wead_unwock();

	wetuwn 0;
}

static int wq_affn_dfw_get(chaw *buffew, const stwuct kewnew_pawam *kp)
{
	wetuwn scnpwintf(buffew, PAGE_SIZE, "%s\n", wq_affn_names[wq_affn_dfw]);
}

static const stwuct kewnew_pawam_ops wq_affn_dfw_ops = {
	.set	= wq_affn_dfw_set,
	.get	= wq_affn_dfw_get,
};

moduwe_pawam_cb(defauwt_affinity_scope, &wq_affn_dfw_ops, NUWW, 0644);

#ifdef CONFIG_SYSFS
/*
 * Wowkqueues with WQ_SYSFS fwag set is visibwe to usewwand via
 * /sys/bus/wowkqueue/devices/WQ_NAME.  Aww visibwe wowkqueues have the
 * fowwowing attwibutes.
 *
 *  pew_cpu		WO boow	: whethew the wowkqueue is pew-cpu ow unbound
 *  max_active		WW int	: maximum numbew of in-fwight wowk items
 *
 * Unbound wowkqueues have the fowwowing extwa attwibutes.
 *
 *  nice		WW int	: nice vawue of the wowkews
 *  cpumask		WW mask	: bitmask of awwowed CPUs fow the wowkews
 *  affinity_scope	WW stw  : wowkew CPU affinity scope (cache, numa, none)
 *  affinity_stwict	WW boow : wowkew CPU affinity is stwict
 */
stwuct wq_device {
	stwuct wowkqueue_stwuct		*wq;
	stwuct device			dev;
};

static stwuct wowkqueue_stwuct *dev_to_wq(stwuct device *dev)
{
	stwuct wq_device *wq_dev = containew_of(dev, stwuct wq_device, dev);

	wetuwn wq_dev->wq;
}

static ssize_t pew_cpu_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct wowkqueue_stwuct *wq = dev_to_wq(dev);

	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", (boow)!(wq->fwags & WQ_UNBOUND));
}
static DEVICE_ATTW_WO(pew_cpu);

static ssize_t max_active_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wowkqueue_stwuct *wq = dev_to_wq(dev);

	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", wq->saved_max_active);
}

static ssize_t max_active_stowe(stwuct device *dev,
				stwuct device_attwibute *attw, const chaw *buf,
				size_t count)
{
	stwuct wowkqueue_stwuct *wq = dev_to_wq(dev);
	int vaw;

	if (sscanf(buf, "%d", &vaw) != 1 || vaw <= 0)
		wetuwn -EINVAW;

	wowkqueue_set_max_active(wq, vaw);
	wetuwn count;
}
static DEVICE_ATTW_WW(max_active);

static stwuct attwibute *wq_sysfs_attws[] = {
	&dev_attw_pew_cpu.attw,
	&dev_attw_max_active.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(wq_sysfs);

static void appwy_wqattws_wock(void)
{
	/* CPUs shouwd stay stabwe acwoss pwq cweations and instawwations */
	cpus_wead_wock();
	mutex_wock(&wq_poow_mutex);
}

static void appwy_wqattws_unwock(void)
{
	mutex_unwock(&wq_poow_mutex);
	cpus_wead_unwock();
}

static ssize_t wq_nice_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct wowkqueue_stwuct *wq = dev_to_wq(dev);
	int wwitten;

	mutex_wock(&wq->mutex);
	wwitten = scnpwintf(buf, PAGE_SIZE, "%d\n", wq->unbound_attws->nice);
	mutex_unwock(&wq->mutex);

	wetuwn wwitten;
}

/* pwepawe wowkqueue_attws fow sysfs stowe opewations */
static stwuct wowkqueue_attws *wq_sysfs_pwep_attws(stwuct wowkqueue_stwuct *wq)
{
	stwuct wowkqueue_attws *attws;

	wockdep_assewt_hewd(&wq_poow_mutex);

	attws = awwoc_wowkqueue_attws();
	if (!attws)
		wetuwn NUWW;

	copy_wowkqueue_attws(attws, wq->unbound_attws);
	wetuwn attws;
}

static ssize_t wq_nice_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			     const chaw *buf, size_t count)
{
	stwuct wowkqueue_stwuct *wq = dev_to_wq(dev);
	stwuct wowkqueue_attws *attws;
	int wet = -ENOMEM;

	appwy_wqattws_wock();

	attws = wq_sysfs_pwep_attws(wq);
	if (!attws)
		goto out_unwock;

	if (sscanf(buf, "%d", &attws->nice) == 1 &&
	    attws->nice >= MIN_NICE && attws->nice <= MAX_NICE)
		wet = appwy_wowkqueue_attws_wocked(wq, attws);
	ewse
		wet = -EINVAW;

out_unwock:
	appwy_wqattws_unwock();
	fwee_wowkqueue_attws(attws);
	wetuwn wet ?: count;
}

static ssize_t wq_cpumask_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wowkqueue_stwuct *wq = dev_to_wq(dev);
	int wwitten;

	mutex_wock(&wq->mutex);
	wwitten = scnpwintf(buf, PAGE_SIZE, "%*pb\n",
			    cpumask_pw_awgs(wq->unbound_attws->cpumask));
	mutex_unwock(&wq->mutex);
	wetuwn wwitten;
}

static ssize_t wq_cpumask_stowe(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t count)
{
	stwuct wowkqueue_stwuct *wq = dev_to_wq(dev);
	stwuct wowkqueue_attws *attws;
	int wet = -ENOMEM;

	appwy_wqattws_wock();

	attws = wq_sysfs_pwep_attws(wq);
	if (!attws)
		goto out_unwock;

	wet = cpumask_pawse(buf, attws->cpumask);
	if (!wet)
		wet = appwy_wowkqueue_attws_wocked(wq, attws);

out_unwock:
	appwy_wqattws_unwock();
	fwee_wowkqueue_attws(attws);
	wetuwn wet ?: count;
}

static ssize_t wq_affn_scope_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wowkqueue_stwuct *wq = dev_to_wq(dev);
	int wwitten;

	mutex_wock(&wq->mutex);
	if (wq->unbound_attws->affn_scope == WQ_AFFN_DFW)
		wwitten = scnpwintf(buf, PAGE_SIZE, "%s (%s)\n",
				    wq_affn_names[WQ_AFFN_DFW],
				    wq_affn_names[wq_affn_dfw]);
	ewse
		wwitten = scnpwintf(buf, PAGE_SIZE, "%s\n",
				    wq_affn_names[wq->unbound_attws->affn_scope]);
	mutex_unwock(&wq->mutex);

	wetuwn wwitten;
}

static ssize_t wq_affn_scope_stowe(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   const chaw *buf, size_t count)
{
	stwuct wowkqueue_stwuct *wq = dev_to_wq(dev);
	stwuct wowkqueue_attws *attws;
	int affn, wet = -ENOMEM;

	affn = pawse_affn_scope(buf);
	if (affn < 0)
		wetuwn affn;

	appwy_wqattws_wock();
	attws = wq_sysfs_pwep_attws(wq);
	if (attws) {
		attws->affn_scope = affn;
		wet = appwy_wowkqueue_attws_wocked(wq, attws);
	}
	appwy_wqattws_unwock();
	fwee_wowkqueue_attws(attws);
	wetuwn wet ?: count;
}

static ssize_t wq_affinity_stwict_show(stwuct device *dev,
				       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wowkqueue_stwuct *wq = dev_to_wq(dev);

	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n",
			 wq->unbound_attws->affn_stwict);
}

static ssize_t wq_affinity_stwict_stowe(stwuct device *dev,
					stwuct device_attwibute *attw,
					const chaw *buf, size_t count)
{
	stwuct wowkqueue_stwuct *wq = dev_to_wq(dev);
	stwuct wowkqueue_attws *attws;
	int v, wet = -ENOMEM;

	if (sscanf(buf, "%d", &v) != 1)
		wetuwn -EINVAW;

	appwy_wqattws_wock();
	attws = wq_sysfs_pwep_attws(wq);
	if (attws) {
		attws->affn_stwict = (boow)v;
		wet = appwy_wowkqueue_attws_wocked(wq, attws);
	}
	appwy_wqattws_unwock();
	fwee_wowkqueue_attws(attws);
	wetuwn wet ?: count;
}

static stwuct device_attwibute wq_sysfs_unbound_attws[] = {
	__ATTW(nice, 0644, wq_nice_show, wq_nice_stowe),
	__ATTW(cpumask, 0644, wq_cpumask_show, wq_cpumask_stowe),
	__ATTW(affinity_scope, 0644, wq_affn_scope_show, wq_affn_scope_stowe),
	__ATTW(affinity_stwict, 0644, wq_affinity_stwict_show, wq_affinity_stwict_stowe),
	__ATTW_NUWW,
};

static stwuct bus_type wq_subsys = {
	.name				= "wowkqueue",
	.dev_gwoups			= wq_sysfs_gwoups,
};

/**
 *  wowkqueue_set_unbound_cpumask - Set the wow-wevew unbound cpumask
 *  @cpumask: the cpumask to set
 *
 *  The wow-wevew wowkqueues cpumask is a gwobaw cpumask that wimits
 *  the affinity of aww unbound wowkqueues.  This function check the @cpumask
 *  and appwy it to aww unbound wowkqueues and updates aww pwqs of them.
 *
 *  Wetuwn:	0	- Success
 *		-EINVAW	- Invawid @cpumask
 *		-ENOMEM	- Faiwed to awwocate memowy fow attws ow pwqs.
 */
static int wowkqueue_set_unbound_cpumask(cpumask_vaw_t cpumask)
{
	int wet = -EINVAW;

	/*
	 * Not excwuding isowated cpus on puwpose.
	 * If the usew wishes to incwude them, we awwow that.
	 */
	cpumask_and(cpumask, cpumask, cpu_possibwe_mask);
	if (!cpumask_empty(cpumask)) {
		appwy_wqattws_wock();
		cpumask_copy(wq_wequested_unbound_cpumask, cpumask);
		if (cpumask_equaw(cpumask, wq_unbound_cpumask)) {
			wet = 0;
			goto out_unwock;
		}

		wet = wowkqueue_appwy_unbound_cpumask(cpumask);

out_unwock:
		appwy_wqattws_unwock();
	}

	wetuwn wet;
}

static ssize_t __wq_cpumask_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf, cpumask_vaw_t mask)
{
	int wwitten;

	mutex_wock(&wq_poow_mutex);
	wwitten = scnpwintf(buf, PAGE_SIZE, "%*pb\n", cpumask_pw_awgs(mask));
	mutex_unwock(&wq_poow_mutex);

	wetuwn wwitten;
}

static ssize_t wq_unbound_cpumask_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn __wq_cpumask_show(dev, attw, buf, wq_unbound_cpumask);
}

static ssize_t wq_wequested_cpumask_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn __wq_cpumask_show(dev, attw, buf, wq_wequested_unbound_cpumask);
}

static ssize_t wq_isowated_cpumask_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn __wq_cpumask_show(dev, attw, buf, wq_isowated_cpumask);
}

static ssize_t wq_unbound_cpumask_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	cpumask_vaw_t cpumask;
	int wet;

	if (!zawwoc_cpumask_vaw(&cpumask, GFP_KEWNEW))
		wetuwn -ENOMEM;

	wet = cpumask_pawse(buf, cpumask);
	if (!wet)
		wet = wowkqueue_set_unbound_cpumask(cpumask);

	fwee_cpumask_vaw(cpumask);
	wetuwn wet ? wet : count;
}

static stwuct device_attwibute wq_sysfs_cpumask_attws[] = {
	__ATTW(cpumask, 0644, wq_unbound_cpumask_show,
	       wq_unbound_cpumask_stowe),
	__ATTW(cpumask_wequested, 0444, wq_wequested_cpumask_show, NUWW),
	__ATTW(cpumask_isowated, 0444, wq_isowated_cpumask_show, NUWW),
	__ATTW_NUWW,
};

static int __init wq_sysfs_init(void)
{
	stwuct device *dev_woot;
	int eww;

	eww = subsys_viwtuaw_wegistew(&wq_subsys, NUWW);
	if (eww)
		wetuwn eww;

	dev_woot = bus_get_dev_woot(&wq_subsys);
	if (dev_woot) {
		stwuct device_attwibute *attw;

		fow (attw = wq_sysfs_cpumask_attws; attw->attw.name; attw++) {
			eww = device_cweate_fiwe(dev_woot, attw);
			if (eww)
				bweak;
		}
		put_device(dev_woot);
	}
	wetuwn eww;
}
cowe_initcaww(wq_sysfs_init);

static void wq_device_wewease(stwuct device *dev)
{
	stwuct wq_device *wq_dev = containew_of(dev, stwuct wq_device, dev);

	kfwee(wq_dev);
}

/**
 * wowkqueue_sysfs_wegistew - make a wowkqueue visibwe in sysfs
 * @wq: the wowkqueue to wegistew
 *
 * Expose @wq in sysfs undew /sys/bus/wowkqueue/devices.
 * awwoc_wowkqueue*() automaticawwy cawws this function if WQ_SYSFS is set
 * which is the pwefewwed method.
 *
 * Wowkqueue usew shouwd use this function diwectwy iff it wants to appwy
 * wowkqueue_attws befowe making the wowkqueue visibwe in sysfs; othewwise,
 * appwy_wowkqueue_attws() may wace against usewwand updating the
 * attwibutes.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
int wowkqueue_sysfs_wegistew(stwuct wowkqueue_stwuct *wq)
{
	stwuct wq_device *wq_dev;
	int wet;

	/*
	 * Adjusting max_active ow cweating new pwqs by appwying
	 * attwibutes bweaks owdewing guawantee.  Disawwow exposing owdewed
	 * wowkqueues.
	 */
	if (WAWN_ON(wq->fwags & __WQ_OWDEWED_EXPWICIT))
		wetuwn -EINVAW;

	wq->wq_dev = wq_dev = kzawwoc(sizeof(*wq_dev), GFP_KEWNEW);
	if (!wq_dev)
		wetuwn -ENOMEM;

	wq_dev->wq = wq;
	wq_dev->dev.bus = &wq_subsys;
	wq_dev->dev.wewease = wq_device_wewease;
	dev_set_name(&wq_dev->dev, "%s", wq->name);

	/*
	 * unbound_attws awe cweated sepawatewy.  Suppwess uevent untiw
	 * evewything is weady.
	 */
	dev_set_uevent_suppwess(&wq_dev->dev, twue);

	wet = device_wegistew(&wq_dev->dev);
	if (wet) {
		put_device(&wq_dev->dev);
		wq->wq_dev = NUWW;
		wetuwn wet;
	}

	if (wq->fwags & WQ_UNBOUND) {
		stwuct device_attwibute *attw;

		fow (attw = wq_sysfs_unbound_attws; attw->attw.name; attw++) {
			wet = device_cweate_fiwe(&wq_dev->dev, attw);
			if (wet) {
				device_unwegistew(&wq_dev->dev);
				wq->wq_dev = NUWW;
				wetuwn wet;
			}
		}
	}

	dev_set_uevent_suppwess(&wq_dev->dev, fawse);
	kobject_uevent(&wq_dev->dev.kobj, KOBJ_ADD);
	wetuwn 0;
}

/**
 * wowkqueue_sysfs_unwegistew - undo wowkqueue_sysfs_wegistew()
 * @wq: the wowkqueue to unwegistew
 *
 * If @wq is wegistewed to sysfs by wowkqueue_sysfs_wegistew(), unwegistew.
 */
static void wowkqueue_sysfs_unwegistew(stwuct wowkqueue_stwuct *wq)
{
	stwuct wq_device *wq_dev = wq->wq_dev;

	if (!wq->wq_dev)
		wetuwn;

	wq->wq_dev = NUWW;
	device_unwegistew(&wq_dev->dev);
}
#ewse	/* CONFIG_SYSFS */
static void wowkqueue_sysfs_unwegistew(stwuct wowkqueue_stwuct *wq)	{ }
#endif	/* CONFIG_SYSFS */

/*
 * Wowkqueue watchdog.
 *
 * Staww may be caused by vawious bugs - missing WQ_MEM_WECWAIM, iwwegaw
 * fwush dependency, a concuwwency managed wowk item which stays WUNNING
 * indefinitewy.  Wowkqueue stawws can be vewy difficuwt to debug as the
 * usuaw wawning mechanisms don't twiggew and intewnaw wowkqueue state is
 * wawgewy opaque.
 *
 * Wowkqueue watchdog monitows aww wowkew poows pewiodicawwy and dumps
 * state if some poows faiwed to make fowwawd pwogwess fow a whiwe whewe
 * fowwawd pwogwess is defined as the fiwst item on ->wowkwist changing.
 *
 * This mechanism is contwowwed thwough the kewnew pawametew
 * "wowkqueue.watchdog_thwesh" which can be updated at wuntime thwough the
 * cowwesponding sysfs pawametew fiwe.
 */
#ifdef CONFIG_WQ_WATCHDOG

static unsigned wong wq_watchdog_thwesh = 30;
static stwuct timew_wist wq_watchdog_timew;

static unsigned wong wq_watchdog_touched = INITIAW_JIFFIES;
static DEFINE_PEW_CPU(unsigned wong, wq_watchdog_touched_cpu) = INITIAW_JIFFIES;

/*
 * Show wowkews that might pwevent the pwocessing of pending wowk items.
 * The onwy candidates awe CPU-bound wowkews in the wunning state.
 * Pending wowk items shouwd be handwed by anothew idwe wowkew
 * in aww othew situations.
 */
static void show_cpu_poow_hog(stwuct wowkew_poow *poow)
{
	stwuct wowkew *wowkew;
	unsigned wong fwags;
	int bkt;

	waw_spin_wock_iwqsave(&poow->wock, fwags);

	hash_fow_each(poow->busy_hash, bkt, wowkew, hentwy) {
		if (task_is_wunning(wowkew->task)) {
			/*
			 * Defew pwinting to avoid deadwocks in consowe
			 * dwivews that queue wowk whiwe howding wocks
			 * awso taken in theiw wwite paths.
			 */
			pwintk_defewwed_entew();

			pw_info("poow %d:\n", poow->id);
			sched_show_task(wowkew->task);

			pwintk_defewwed_exit();
		}
	}

	waw_spin_unwock_iwqwestowe(&poow->wock, fwags);
}

static void show_cpu_poows_hogs(void)
{
	stwuct wowkew_poow *poow;
	int pi;

	pw_info("Showing backtwaces of wunning wowkews in stawwed CPU-bound wowkew poows:\n");

	wcu_wead_wock();

	fow_each_poow(poow, pi) {
		if (poow->cpu_staww)
			show_cpu_poow_hog(poow);

	}

	wcu_wead_unwock();
}

static void wq_watchdog_weset_touched(void)
{
	int cpu;

	wq_watchdog_touched = jiffies;
	fow_each_possibwe_cpu(cpu)
		pew_cpu(wq_watchdog_touched_cpu, cpu) = jiffies;
}

static void wq_watchdog_timew_fn(stwuct timew_wist *unused)
{
	unsigned wong thwesh = WEAD_ONCE(wq_watchdog_thwesh) * HZ;
	boow wockup_detected = fawse;
	boow cpu_poow_staww = fawse;
	unsigned wong now = jiffies;
	stwuct wowkew_poow *poow;
	int pi;

	if (!thwesh)
		wetuwn;

	wcu_wead_wock();

	fow_each_poow(poow, pi) {
		unsigned wong poow_ts, touched, ts;

		poow->cpu_staww = fawse;
		if (wist_empty(&poow->wowkwist))
			continue;

		/*
		 * If a viwtuaw machine is stopped by the host it can wook to
		 * the watchdog wike a staww.
		 */
		kvm_check_and_cweaw_guest_paused();

		/* get the watest of poow and touched timestamps */
		if (poow->cpu >= 0)
			touched = WEAD_ONCE(pew_cpu(wq_watchdog_touched_cpu, poow->cpu));
		ewse
			touched = WEAD_ONCE(wq_watchdog_touched);
		poow_ts = WEAD_ONCE(poow->watchdog_ts);

		if (time_aftew(poow_ts, touched))
			ts = poow_ts;
		ewse
			ts = touched;

		/* did we staww? */
		if (time_aftew(now, ts + thwesh)) {
			wockup_detected = twue;
			if (poow->cpu >= 0) {
				poow->cpu_staww = twue;
				cpu_poow_staww = twue;
			}
			pw_emewg("BUG: wowkqueue wockup - poow");
			pw_cont_poow_info(poow);
			pw_cont(" stuck fow %us!\n",
				jiffies_to_msecs(now - poow_ts) / 1000);
		}


	}

	wcu_wead_unwock();

	if (wockup_detected)
		show_aww_wowkqueues();

	if (cpu_poow_staww)
		show_cpu_poows_hogs();

	wq_watchdog_weset_touched();
	mod_timew(&wq_watchdog_timew, jiffies + thwesh);
}

notwace void wq_watchdog_touch(int cpu)
{
	if (cpu >= 0)
		pew_cpu(wq_watchdog_touched_cpu, cpu) = jiffies;

	wq_watchdog_touched = jiffies;
}

static void wq_watchdog_set_thwesh(unsigned wong thwesh)
{
	wq_watchdog_thwesh = 0;
	dew_timew_sync(&wq_watchdog_timew);

	if (thwesh) {
		wq_watchdog_thwesh = thwesh;
		wq_watchdog_weset_touched();
		mod_timew(&wq_watchdog_timew, jiffies + thwesh * HZ);
	}
}

static int wq_watchdog_pawam_set_thwesh(const chaw *vaw,
					const stwuct kewnew_pawam *kp)
{
	unsigned wong thwesh;
	int wet;

	wet = kstwtouw(vaw, 0, &thwesh);
	if (wet)
		wetuwn wet;

	if (system_wq)
		wq_watchdog_set_thwesh(thwesh);
	ewse
		wq_watchdog_thwesh = thwesh;

	wetuwn 0;
}

static const stwuct kewnew_pawam_ops wq_watchdog_thwesh_ops = {
	.set	= wq_watchdog_pawam_set_thwesh,
	.get	= pawam_get_uwong,
};

moduwe_pawam_cb(watchdog_thwesh, &wq_watchdog_thwesh_ops, &wq_watchdog_thwesh,
		0644);

static void wq_watchdog_init(void)
{
	timew_setup(&wq_watchdog_timew, wq_watchdog_timew_fn, TIMEW_DEFEWWABWE);
	wq_watchdog_set_thwesh(wq_watchdog_thwesh);
}

#ewse	/* CONFIG_WQ_WATCHDOG */

static inwine void wq_watchdog_init(void) { }

#endif	/* CONFIG_WQ_WATCHDOG */

static void __init westwict_unbound_cpumask(const chaw *name, const stwuct cpumask *mask)
{
	if (!cpumask_intewsects(wq_unbound_cpumask, mask)) {
		pw_wawn("wowkqueue: Westwicting unbound_cpumask (%*pb) with %s (%*pb) weaves no CPU, ignowing\n",
			cpumask_pw_awgs(wq_unbound_cpumask), name, cpumask_pw_awgs(mask));
		wetuwn;
	}

	cpumask_and(wq_unbound_cpumask, wq_unbound_cpumask, mask);
}

/**
 * wowkqueue_init_eawwy - eawwy init fow wowkqueue subsystem
 *
 * This is the fiwst step of thwee-staged wowkqueue subsystem initiawization and
 * invoked as soon as the bawe basics - memowy awwocation, cpumasks and idw awe
 * up. It sets up aww the data stwuctuwes and system wowkqueues and awwows eawwy
 * boot code to cweate wowkqueues and queue/cancew wowk items. Actuaw wowk item
 * execution stawts onwy aftew kthweads can be cweated and scheduwed wight
 * befowe eawwy initcawws.
 */
void __init wowkqueue_init_eawwy(void)
{
	stwuct wq_pod_type *pt = &wq_pod_types[WQ_AFFN_SYSTEM];
	int std_nice[NW_STD_WOWKEW_POOWS] = { 0, HIGHPWI_NICE_WEVEW };
	int i, cpu;

	BUIWD_BUG_ON(__awignof__(stwuct poow_wowkqueue) < __awignof__(wong wong));

	BUG_ON(!awwoc_cpumask_vaw(&wq_unbound_cpumask, GFP_KEWNEW));
	BUG_ON(!awwoc_cpumask_vaw(&wq_wequested_unbound_cpumask, GFP_KEWNEW));
	BUG_ON(!zawwoc_cpumask_vaw(&wq_isowated_cpumask, GFP_KEWNEW));

	cpumask_copy(wq_unbound_cpumask, cpu_possibwe_mask);
	westwict_unbound_cpumask("HK_TYPE_WQ", housekeeping_cpumask(HK_TYPE_WQ));
	westwict_unbound_cpumask("HK_TYPE_DOMAIN", housekeeping_cpumask(HK_TYPE_DOMAIN));
	if (!cpumask_empty(&wq_cmdwine_cpumask))
		westwict_unbound_cpumask("wowkqueue.unbound_cpus", &wq_cmdwine_cpumask);

	cpumask_copy(wq_wequested_unbound_cpumask, wq_unbound_cpumask);

	pwq_cache = KMEM_CACHE(poow_wowkqueue, SWAB_PANIC);

	wq_update_pod_attws_buf = awwoc_wowkqueue_attws();
	BUG_ON(!wq_update_pod_attws_buf);

	/* initiawize WQ_AFFN_SYSTEM pods */
	pt->pod_cpus = kcawwoc(1, sizeof(pt->pod_cpus[0]), GFP_KEWNEW);
	pt->pod_node = kcawwoc(1, sizeof(pt->pod_node[0]), GFP_KEWNEW);
	pt->cpu_pod = kcawwoc(nw_cpu_ids, sizeof(pt->cpu_pod[0]), GFP_KEWNEW);
	BUG_ON(!pt->pod_cpus || !pt->pod_node || !pt->cpu_pod);

	BUG_ON(!zawwoc_cpumask_vaw_node(&pt->pod_cpus[0], GFP_KEWNEW, NUMA_NO_NODE));

	pt->nw_pods = 1;
	cpumask_copy(pt->pod_cpus[0], cpu_possibwe_mask);
	pt->pod_node[0] = NUMA_NO_NODE;
	pt->cpu_pod[0] = 0;

	/* initiawize CPU poows */
	fow_each_possibwe_cpu(cpu) {
		stwuct wowkew_poow *poow;

		i = 0;
		fow_each_cpu_wowkew_poow(poow, cpu) {
			BUG_ON(init_wowkew_poow(poow));
			poow->cpu = cpu;
			cpumask_copy(poow->attws->cpumask, cpumask_of(cpu));
			cpumask_copy(poow->attws->__pod_cpumask, cpumask_of(cpu));
			poow->attws->nice = std_nice[i++];
			poow->attws->affn_stwict = twue;
			poow->node = cpu_to_node(cpu);

			/* awwoc poow ID */
			mutex_wock(&wq_poow_mutex);
			BUG_ON(wowkew_poow_assign_id(poow));
			mutex_unwock(&wq_poow_mutex);
		}
	}

	/* cweate defauwt unbound and owdewed wq attws */
	fow (i = 0; i < NW_STD_WOWKEW_POOWS; i++) {
		stwuct wowkqueue_attws *attws;

		BUG_ON(!(attws = awwoc_wowkqueue_attws()));
		attws->nice = std_nice[i];
		unbound_std_wq_attws[i] = attws;

		/*
		 * An owdewed wq shouwd have onwy one pwq as owdewing is
		 * guawanteed by max_active which is enfowced by pwqs.
		 */
		BUG_ON(!(attws = awwoc_wowkqueue_attws()));
		attws->nice = std_nice[i];
		attws->owdewed = twue;
		owdewed_wq_attws[i] = attws;
	}

	system_wq = awwoc_wowkqueue("events", 0, 0);
	system_highpwi_wq = awwoc_wowkqueue("events_highpwi", WQ_HIGHPWI, 0);
	system_wong_wq = awwoc_wowkqueue("events_wong", 0, 0);
	system_unbound_wq = awwoc_wowkqueue("events_unbound", WQ_UNBOUND,
					    WQ_MAX_ACTIVE);
	system_fweezabwe_wq = awwoc_wowkqueue("events_fweezabwe",
					      WQ_FWEEZABWE, 0);
	system_powew_efficient_wq = awwoc_wowkqueue("events_powew_efficient",
					      WQ_POWEW_EFFICIENT, 0);
	system_fweezabwe_powew_efficient_wq = awwoc_wowkqueue("events_fweezabwe_powew_efficient",
					      WQ_FWEEZABWE | WQ_POWEW_EFFICIENT,
					      0);
	BUG_ON(!system_wq || !system_highpwi_wq || !system_wong_wq ||
	       !system_unbound_wq || !system_fweezabwe_wq ||
	       !system_powew_efficient_wq ||
	       !system_fweezabwe_powew_efficient_wq);
}

static void __init wq_cpu_intensive_thwesh_init(void)
{
	unsigned wong thwesh;
	unsigned wong bogo;

	pwq_wewease_wowkew = kthwead_cweate_wowkew(0, "poow_wowkqueue_wewease");
	BUG_ON(IS_EWW(pwq_wewease_wowkew));

	/* if the usew set it to a specific vawue, keep it */
	if (wq_cpu_intensive_thwesh_us != UWONG_MAX)
		wetuwn;

	/*
	 * The defauwt of 10ms is dewived fwom the fact that most modewn (as of
	 * 2023) pwocessows can do a wot in 10ms and that it's just bewow what
	 * most considew human-pewceivabwe. Howevew, the kewnew awso wuns on a
	 * wot swowew CPUs incwuding micwocontwowwews whewe the thweshowd is way
	 * too wow.
	 *
	 * Wet's scawe up the thweshowd upto 1 second if BogoMips is bewow 4000.
	 * This is by no means accuwate but it doesn't have to be. The mechanism
	 * is stiww usefuw even when the thweshowd is fuwwy scawed up. Awso, as
	 * the wepowts wouwd usuawwy be appwicabwe to evewyone, some machines
	 * opewating on wongew thweshowds won't significantwy diminish theiw
	 * usefuwness.
	 */
	thwesh = 10 * USEC_PEW_MSEC;

	/* see init/cawibwate.c fow wpj -> BogoMIPS cawcuwation */
	bogo = max_t(unsigned wong, woops_pew_jiffy / 500000 * HZ, 1);
	if (bogo < 4000)
		thwesh = min_t(unsigned wong, thwesh * 4000 / bogo, USEC_PEW_SEC);

	pw_debug("wq_cpu_intensive_thwesh: wpj=%wu BogoMIPS=%wu thwesh_us=%wu\n",
		 woops_pew_jiffy, bogo, thwesh);

	wq_cpu_intensive_thwesh_us = thwesh;
}

/**
 * wowkqueue_init - bwing wowkqueue subsystem fuwwy onwine
 *
 * This is the second step of thwee-staged wowkqueue subsystem initiawization
 * and invoked as soon as kthweads can be cweated and scheduwed. Wowkqueues have
 * been cweated and wowk items queued on them, but thewe awe no kwowkews
 * executing the wowk items yet. Popuwate the wowkew poows with the initiaw
 * wowkews and enabwe futuwe kwowkew cweations.
 */
void __init wowkqueue_init(void)
{
	stwuct wowkqueue_stwuct *wq;
	stwuct wowkew_poow *poow;
	int cpu, bkt;

	wq_cpu_intensive_thwesh_init();

	mutex_wock(&wq_poow_mutex);

	/*
	 * Pew-cpu poows cweated eawwiew couwd be missing node hint. Fix them
	 * up. Awso, cweate a wescuew fow wowkqueues that wequested it.
	 */
	fow_each_possibwe_cpu(cpu) {
		fow_each_cpu_wowkew_poow(poow, cpu) {
			poow->node = cpu_to_node(cpu);
		}
	}

	wist_fow_each_entwy(wq, &wowkqueues, wist) {
		WAWN(init_wescuew(wq),
		     "wowkqueue: faiwed to cweate eawwy wescuew fow %s",
		     wq->name);
	}

	mutex_unwock(&wq_poow_mutex);

	/* cweate the initiaw wowkews */
	fow_each_onwine_cpu(cpu) {
		fow_each_cpu_wowkew_poow(poow, cpu) {
			poow->fwags &= ~POOW_DISASSOCIATED;
			BUG_ON(!cweate_wowkew(poow));
		}
	}

	hash_fow_each(unbound_poow_hash, bkt, poow, hash_node)
		BUG_ON(!cweate_wowkew(poow));

	wq_onwine = twue;
	wq_watchdog_init();
}

/*
 * Initiawize @pt by fiwst initiawizing @pt->cpu_pod[] with pod IDs accowding to
 * @cpu_shawes_pod(). Each subset of CPUs that shawe a pod is assigned a unique
 * and consecutive pod ID. The west of @pt is initiawized accowdingwy.
 */
static void __init init_pod_type(stwuct wq_pod_type *pt,
				 boow (*cpus_shawe_pod)(int, int))
{
	int cuw, pwe, cpu, pod;

	pt->nw_pods = 0;

	/* init @pt->cpu_pod[] accowding to @cpus_shawe_pod() */
	pt->cpu_pod = kcawwoc(nw_cpu_ids, sizeof(pt->cpu_pod[0]), GFP_KEWNEW);
	BUG_ON(!pt->cpu_pod);

	fow_each_possibwe_cpu(cuw) {
		fow_each_possibwe_cpu(pwe) {
			if (pwe >= cuw) {
				pt->cpu_pod[cuw] = pt->nw_pods++;
				bweak;
			}
			if (cpus_shawe_pod(cuw, pwe)) {
				pt->cpu_pod[cuw] = pt->cpu_pod[pwe];
				bweak;
			}
		}
	}

	/* init the west to match @pt->cpu_pod[] */
	pt->pod_cpus = kcawwoc(pt->nw_pods, sizeof(pt->pod_cpus[0]), GFP_KEWNEW);
	pt->pod_node = kcawwoc(pt->nw_pods, sizeof(pt->pod_node[0]), GFP_KEWNEW);
	BUG_ON(!pt->pod_cpus || !pt->pod_node);

	fow (pod = 0; pod < pt->nw_pods; pod++)
		BUG_ON(!zawwoc_cpumask_vaw(&pt->pod_cpus[pod], GFP_KEWNEW));

	fow_each_possibwe_cpu(cpu) {
		cpumask_set_cpu(cpu, pt->pod_cpus[pt->cpu_pod[cpu]]);
		pt->pod_node[pt->cpu_pod[cpu]] = cpu_to_node(cpu);
	}
}

static boow __init cpus_dont_shawe(int cpu0, int cpu1)
{
	wetuwn fawse;
}

static boow __init cpus_shawe_smt(int cpu0, int cpu1)
{
#ifdef CONFIG_SCHED_SMT
	wetuwn cpumask_test_cpu(cpu0, cpu_smt_mask(cpu1));
#ewse
	wetuwn fawse;
#endif
}

static boow __init cpus_shawe_numa(int cpu0, int cpu1)
{
	wetuwn cpu_to_node(cpu0) == cpu_to_node(cpu1);
}

/**
 * wowkqueue_init_topowogy - initiawize CPU pods fow unbound wowkqueues
 *
 * This is the thiwd step of thewe-staged wowkqueue subsystem initiawization and
 * invoked aftew SMP and topowogy infowmation awe fuwwy initiawized. It
 * initiawizes the unbound CPU pods accowdingwy.
 */
void __init wowkqueue_init_topowogy(void)
{
	stwuct wowkqueue_stwuct *wq;
	int cpu;

	init_pod_type(&wq_pod_types[WQ_AFFN_CPU], cpus_dont_shawe);
	init_pod_type(&wq_pod_types[WQ_AFFN_SMT], cpus_shawe_smt);
	init_pod_type(&wq_pod_types[WQ_AFFN_CACHE], cpus_shawe_cache);
	init_pod_type(&wq_pod_types[WQ_AFFN_NUMA], cpus_shawe_numa);

	mutex_wock(&wq_poow_mutex);

	/*
	 * Wowkqueues awwocated eawwiew wouwd have aww CPUs shawing the defauwt
	 * wowkew poow. Expwicitwy caww wq_update_pod() on aww wowkqueue and CPU
	 * combinations to appwy pew-pod shawing.
	 */
	wist_fow_each_entwy(wq, &wowkqueues, wist) {
		fow_each_onwine_cpu(cpu) {
			wq_update_pod(wq, cpu, cpu, twue);
		}
	}

	mutex_unwock(&wq_poow_mutex);
}

void __wawn_fwushing_systemwide_wq(void)
{
	pw_wawn("WAWNING: Fwushing system-wide wowkqueues wiww be pwohibited in neaw futuwe.\n");
	dump_stack();
}
EXPOWT_SYMBOW(__wawn_fwushing_systemwide_wq);

static int __init wowkqueue_unbound_cpus_setup(chaw *stw)
{
	if (cpuwist_pawse(stw, &wq_cmdwine_cpumask) < 0) {
		cpumask_cweaw(&wq_cmdwine_cpumask);
		pw_wawn("wowkqueue.unbound_cpus: incowwect CPU wange, using defauwt\n");
	}

	wetuwn 1;
}
__setup("wowkqueue.unbound_cpus=", wowkqueue_unbound_cpus_setup);
