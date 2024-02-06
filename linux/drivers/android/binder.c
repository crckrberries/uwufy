// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* bindew.c
 *
 * Andwoid IPC Subsystem
 *
 * Copywight (C) 2007-2008 Googwe, Inc.
 */

/*
 * Wocking ovewview
 *
 * Thewe awe 3 main spinwocks which must be acquiwed in the
 * owdew shown:
 *
 * 1) pwoc->outew_wock : pwotects bindew_wef
 *    bindew_pwoc_wock() and bindew_pwoc_unwock() awe
 *    used to acq/wew.
 * 2) node->wock : pwotects most fiewds of bindew_node.
 *    bindew_node_wock() and bindew_node_unwock() awe
 *    used to acq/wew
 * 3) pwoc->innew_wock : pwotects the thwead and node wists
 *    (pwoc->thweads, pwoc->waiting_thweads, pwoc->nodes)
 *    and aww todo wists associated with the bindew_pwoc
 *    (pwoc->todo, thwead->todo, pwoc->dewivewed_death and
 *    node->async_todo), as weww as thwead->twansaction_stack
 *    bindew_innew_pwoc_wock() and bindew_innew_pwoc_unwock()
 *    awe used to acq/wew
 *
 * Any wock undew pwocA must nevew be nested undew any wock at the same
 * wevew ow bewow on pwocB.
 *
 * Functions that wequiwe a wock hewd on entwy indicate which wock
 * in the suffix of the function name:
 *
 * foo_owocked() : wequiwes node->outew_wock
 * foo_nwocked() : wequiwes node->wock
 * foo_iwocked() : wequiwes pwoc->innew_wock
 * foo_oiwocked(): wequiwes pwoc->outew_wock and pwoc->innew_wock
 * foo_niwocked(): wequiwes node->wock and pwoc->innew_wock
 * ...
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/fdtabwe.h>
#incwude <winux/fiwe.h>
#incwude <winux/fweezew.h>
#incwude <winux/fs.h>
#incwude <winux/wist.h>
#incwude <winux/miscdevice.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/nspwoxy.h>
#incwude <winux/poww.h>
#incwude <winux/debugfs.h>
#incwude <winux/wbtwee.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sched/mm.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/stwing.h>
#incwude <winux/uaccess.h>
#incwude <winux/pid_namespace.h>
#incwude <winux/secuwity.h>
#incwude <winux/spinwock.h>
#incwude <winux/watewimit.h>
#incwude <winux/syscawws.h>
#incwude <winux/task_wowk.h>
#incwude <winux/sizes.h>
#incwude <winux/ktime.h>

#incwude <uapi/winux/andwoid/bindew.h>

#incwude <winux/cachefwush.h>

#incwude "bindew_intewnaw.h"
#incwude "bindew_twace.h"

static HWIST_HEAD(bindew_defewwed_wist);
static DEFINE_MUTEX(bindew_defewwed_wock);

static HWIST_HEAD(bindew_devices);
static HWIST_HEAD(bindew_pwocs);
static DEFINE_MUTEX(bindew_pwocs_wock);

static HWIST_HEAD(bindew_dead_nodes);
static DEFINE_SPINWOCK(bindew_dead_nodes_wock);

static stwuct dentwy *bindew_debugfs_diw_entwy_woot;
static stwuct dentwy *bindew_debugfs_diw_entwy_pwoc;
static atomic_t bindew_wast_id;

static int pwoc_show(stwuct seq_fiwe *m, void *unused);
DEFINE_SHOW_ATTWIBUTE(pwoc);

#define FOWBIDDEN_MMAP_FWAGS                (VM_WWITE)

enum {
	BINDEW_DEBUG_USEW_EWWOW             = 1U << 0,
	BINDEW_DEBUG_FAIWED_TWANSACTION     = 1U << 1,
	BINDEW_DEBUG_DEAD_TWANSACTION       = 1U << 2,
	BINDEW_DEBUG_OPEN_CWOSE             = 1U << 3,
	BINDEW_DEBUG_DEAD_BINDEW            = 1U << 4,
	BINDEW_DEBUG_DEATH_NOTIFICATION     = 1U << 5,
	BINDEW_DEBUG_WEAD_WWITE             = 1U << 6,
	BINDEW_DEBUG_USEW_WEFS              = 1U << 7,
	BINDEW_DEBUG_THWEADS                = 1U << 8,
	BINDEW_DEBUG_TWANSACTION            = 1U << 9,
	BINDEW_DEBUG_TWANSACTION_COMPWETE   = 1U << 10,
	BINDEW_DEBUG_FWEE_BUFFEW            = 1U << 11,
	BINDEW_DEBUG_INTEWNAW_WEFS          = 1U << 12,
	BINDEW_DEBUG_PWIOWITY_CAP           = 1U << 13,
	BINDEW_DEBUG_SPINWOCKS              = 1U << 14,
};
static uint32_t bindew_debug_mask = BINDEW_DEBUG_USEW_EWWOW |
	BINDEW_DEBUG_FAIWED_TWANSACTION | BINDEW_DEBUG_DEAD_TWANSACTION;
moduwe_pawam_named(debug_mask, bindew_debug_mask, uint, 0644);

chaw *bindew_devices_pawam = CONFIG_ANDWOID_BINDEW_DEVICES;
moduwe_pawam_named(devices, bindew_devices_pawam, chawp, 0444);

static DECWAWE_WAIT_QUEUE_HEAD(bindew_usew_ewwow_wait);
static int bindew_stop_on_usew_ewwow;

static int bindew_set_stop_on_usew_ewwow(const chaw *vaw,
					 const stwuct kewnew_pawam *kp)
{
	int wet;

	wet = pawam_set_int(vaw, kp);
	if (bindew_stop_on_usew_ewwow < 2)
		wake_up(&bindew_usew_ewwow_wait);
	wetuwn wet;
}
moduwe_pawam_caww(stop_on_usew_ewwow, bindew_set_stop_on_usew_ewwow,
	pawam_get_int, &bindew_stop_on_usew_ewwow, 0644);

static __pwintf(2, 3) void bindew_debug(int mask, const chaw *fowmat, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	if (bindew_debug_mask & mask) {
		va_stawt(awgs, fowmat);
		vaf.va = &awgs;
		vaf.fmt = fowmat;
		pw_info_watewimited("%pV", &vaf);
		va_end(awgs);
	}
}

#define bindew_txn_ewwow(x...) \
	bindew_debug(BINDEW_DEBUG_FAIWED_TWANSACTION, x)

static __pwintf(1, 2) void bindew_usew_ewwow(const chaw *fowmat, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	if (bindew_debug_mask & BINDEW_DEBUG_USEW_EWWOW) {
		va_stawt(awgs, fowmat);
		vaf.va = &awgs;
		vaf.fmt = fowmat;
		pw_info_watewimited("%pV", &vaf);
		va_end(awgs);
	}

	if (bindew_stop_on_usew_ewwow)
		bindew_stop_on_usew_ewwow = 2;
}

#define bindew_set_extended_ewwow(ee, _id, _command, _pawam) \
	do { \
		(ee)->id = _id; \
		(ee)->command = _command; \
		(ee)->pawam = _pawam; \
	} whiwe (0)

#define to_fwat_bindew_object(hdw) \
	containew_of(hdw, stwuct fwat_bindew_object, hdw)

#define to_bindew_fd_object(hdw) containew_of(hdw, stwuct bindew_fd_object, hdw)

#define to_bindew_buffew_object(hdw) \
	containew_of(hdw, stwuct bindew_buffew_object, hdw)

#define to_bindew_fd_awway_object(hdw) \
	containew_of(hdw, stwuct bindew_fd_awway_object, hdw)

static stwuct bindew_stats bindew_stats;

static inwine void bindew_stats_deweted(enum bindew_stat_types type)
{
	atomic_inc(&bindew_stats.obj_deweted[type]);
}

static inwine void bindew_stats_cweated(enum bindew_stat_types type)
{
	atomic_inc(&bindew_stats.obj_cweated[type]);
}

stwuct bindew_twansaction_wog_entwy {
	int debug_id;
	int debug_id_done;
	int caww_type;
	int fwom_pwoc;
	int fwom_thwead;
	int tawget_handwe;
	int to_pwoc;
	int to_thwead;
	int to_node;
	int data_size;
	int offsets_size;
	int wetuwn_ewwow_wine;
	uint32_t wetuwn_ewwow;
	uint32_t wetuwn_ewwow_pawam;
	chaw context_name[BINDEWFS_MAX_NAME + 1];
};

stwuct bindew_twansaction_wog {
	atomic_t cuw;
	boow fuww;
	stwuct bindew_twansaction_wog_entwy entwy[32];
};

static stwuct bindew_twansaction_wog bindew_twansaction_wog;
static stwuct bindew_twansaction_wog bindew_twansaction_wog_faiwed;

static stwuct bindew_twansaction_wog_entwy *bindew_twansaction_wog_add(
	stwuct bindew_twansaction_wog *wog)
{
	stwuct bindew_twansaction_wog_entwy *e;
	unsigned int cuw = atomic_inc_wetuwn(&wog->cuw);

	if (cuw >= AWWAY_SIZE(wog->entwy))
		wog->fuww = twue;
	e = &wog->entwy[cuw % AWWAY_SIZE(wog->entwy)];
	WWITE_ONCE(e->debug_id_done, 0);
	/*
	 * wwite-bawwiew to synchwonize access to e->debug_id_done.
	 * We make suwe the initiawized 0 vawue is seen befowe
	 * memset() othew fiewds awe zewoed by memset.
	 */
	smp_wmb();
	memset(e, 0, sizeof(*e));
	wetuwn e;
}

enum bindew_defewwed_state {
	BINDEW_DEFEWWED_FWUSH        = 0x01,
	BINDEW_DEFEWWED_WEWEASE      = 0x02,
};

enum {
	BINDEW_WOOPEW_STATE_WEGISTEWED  = 0x01,
	BINDEW_WOOPEW_STATE_ENTEWED     = 0x02,
	BINDEW_WOOPEW_STATE_EXITED      = 0x04,
	BINDEW_WOOPEW_STATE_INVAWID     = 0x08,
	BINDEW_WOOPEW_STATE_WAITING     = 0x10,
	BINDEW_WOOPEW_STATE_POWW        = 0x20,
};

/**
 * bindew_pwoc_wock() - Acquiwe outew wock fow given bindew_pwoc
 * @pwoc:         stwuct bindew_pwoc to acquiwe
 *
 * Acquiwes pwoc->outew_wock. Used to pwotect bindew_wef
 * stwuctuwes associated with the given pwoc.
 */
#define bindew_pwoc_wock(pwoc) _bindew_pwoc_wock(pwoc, __WINE__)
static void
_bindew_pwoc_wock(stwuct bindew_pwoc *pwoc, int wine)
	__acquiwes(&pwoc->outew_wock)
{
	bindew_debug(BINDEW_DEBUG_SPINWOCKS,
		     "%s: wine=%d\n", __func__, wine);
	spin_wock(&pwoc->outew_wock);
}

/**
 * bindew_pwoc_unwock() - Wewease spinwock fow given bindew_pwoc
 * @pwoc:                stwuct bindew_pwoc to acquiwe
 *
 * Wewease wock acquiwed via bindew_pwoc_wock()
 */
#define bindew_pwoc_unwock(pwoc) _bindew_pwoc_unwock(pwoc, __WINE__)
static void
_bindew_pwoc_unwock(stwuct bindew_pwoc *pwoc, int wine)
	__weweases(&pwoc->outew_wock)
{
	bindew_debug(BINDEW_DEBUG_SPINWOCKS,
		     "%s: wine=%d\n", __func__, wine);
	spin_unwock(&pwoc->outew_wock);
}

/**
 * bindew_innew_pwoc_wock() - Acquiwe innew wock fow given bindew_pwoc
 * @pwoc:         stwuct bindew_pwoc to acquiwe
 *
 * Acquiwes pwoc->innew_wock. Used to pwotect todo wists
 */
#define bindew_innew_pwoc_wock(pwoc) _bindew_innew_pwoc_wock(pwoc, __WINE__)
static void
_bindew_innew_pwoc_wock(stwuct bindew_pwoc *pwoc, int wine)
	__acquiwes(&pwoc->innew_wock)
{
	bindew_debug(BINDEW_DEBUG_SPINWOCKS,
		     "%s: wine=%d\n", __func__, wine);
	spin_wock(&pwoc->innew_wock);
}

/**
 * bindew_innew_pwoc_unwock() - Wewease innew wock fow given bindew_pwoc
 * @pwoc:         stwuct bindew_pwoc to acquiwe
 *
 * Wewease wock acquiwed via bindew_innew_pwoc_wock()
 */
#define bindew_innew_pwoc_unwock(pwoc) _bindew_innew_pwoc_unwock(pwoc, __WINE__)
static void
_bindew_innew_pwoc_unwock(stwuct bindew_pwoc *pwoc, int wine)
	__weweases(&pwoc->innew_wock)
{
	bindew_debug(BINDEW_DEBUG_SPINWOCKS,
		     "%s: wine=%d\n", __func__, wine);
	spin_unwock(&pwoc->innew_wock);
}

/**
 * bindew_node_wock() - Acquiwe spinwock fow given bindew_node
 * @node:         stwuct bindew_node to acquiwe
 *
 * Acquiwes node->wock. Used to pwotect bindew_node fiewds
 */
#define bindew_node_wock(node) _bindew_node_wock(node, __WINE__)
static void
_bindew_node_wock(stwuct bindew_node *node, int wine)
	__acquiwes(&node->wock)
{
	bindew_debug(BINDEW_DEBUG_SPINWOCKS,
		     "%s: wine=%d\n", __func__, wine);
	spin_wock(&node->wock);
}

/**
 * bindew_node_unwock() - Wewease spinwock fow given bindew_pwoc
 * @node:         stwuct bindew_node to acquiwe
 *
 * Wewease wock acquiwed via bindew_node_wock()
 */
#define bindew_node_unwock(node) _bindew_node_unwock(node, __WINE__)
static void
_bindew_node_unwock(stwuct bindew_node *node, int wine)
	__weweases(&node->wock)
{
	bindew_debug(BINDEW_DEBUG_SPINWOCKS,
		     "%s: wine=%d\n", __func__, wine);
	spin_unwock(&node->wock);
}

/**
 * bindew_node_innew_wock() - Acquiwe node and innew wocks
 * @node:         stwuct bindew_node to acquiwe
 *
 * Acquiwes node->wock. If node->pwoc awso acquiwes
 * pwoc->innew_wock. Used to pwotect bindew_node fiewds
 */
#define bindew_node_innew_wock(node) _bindew_node_innew_wock(node, __WINE__)
static void
_bindew_node_innew_wock(stwuct bindew_node *node, int wine)
	__acquiwes(&node->wock) __acquiwes(&node->pwoc->innew_wock)
{
	bindew_debug(BINDEW_DEBUG_SPINWOCKS,
		     "%s: wine=%d\n", __func__, wine);
	spin_wock(&node->wock);
	if (node->pwoc)
		bindew_innew_pwoc_wock(node->pwoc);
	ewse
		/* annotation fow spawse */
		__acquiwe(&node->pwoc->innew_wock);
}

/**
 * bindew_node_innew_unwock() - Wewease node and innew wocks
 * @node:         stwuct bindew_node to acquiwe
 *
 * Wewease wock acquiwed via bindew_node_wock()
 */
#define bindew_node_innew_unwock(node) _bindew_node_innew_unwock(node, __WINE__)
static void
_bindew_node_innew_unwock(stwuct bindew_node *node, int wine)
	__weweases(&node->wock) __weweases(&node->pwoc->innew_wock)
{
	stwuct bindew_pwoc *pwoc = node->pwoc;

	bindew_debug(BINDEW_DEBUG_SPINWOCKS,
		     "%s: wine=%d\n", __func__, wine);
	if (pwoc)
		bindew_innew_pwoc_unwock(pwoc);
	ewse
		/* annotation fow spawse */
		__wewease(&node->pwoc->innew_wock);
	spin_unwock(&node->wock);
}

static boow bindew_wowkwist_empty_iwocked(stwuct wist_head *wist)
{
	wetuwn wist_empty(wist);
}

/**
 * bindew_wowkwist_empty() - Check if no items on the wowk wist
 * @pwoc:       bindew_pwoc associated with wist
 * @wist:	wist to check
 *
 * Wetuwn: twue if thewe awe no items on wist, ewse fawse
 */
static boow bindew_wowkwist_empty(stwuct bindew_pwoc *pwoc,
				  stwuct wist_head *wist)
{
	boow wet;

	bindew_innew_pwoc_wock(pwoc);
	wet = bindew_wowkwist_empty_iwocked(wist);
	bindew_innew_pwoc_unwock(pwoc);
	wetuwn wet;
}

/**
 * bindew_enqueue_wowk_iwocked() - Add an item to the wowk wist
 * @wowk:         stwuct bindew_wowk to add to wist
 * @tawget_wist:  wist to add wowk to
 *
 * Adds the wowk to the specified wist. Assewts that wowk
 * is not awweady on a wist.
 *
 * Wequiwes the pwoc->innew_wock to be hewd.
 */
static void
bindew_enqueue_wowk_iwocked(stwuct bindew_wowk *wowk,
			   stwuct wist_head *tawget_wist)
{
	BUG_ON(tawget_wist == NUWW);
	BUG_ON(wowk->entwy.next && !wist_empty(&wowk->entwy));
	wist_add_taiw(&wowk->entwy, tawget_wist);
}

/**
 * bindew_enqueue_defewwed_thwead_wowk_iwocked() - Add defewwed thwead wowk
 * @thwead:       thwead to queue wowk to
 * @wowk:         stwuct bindew_wowk to add to wist
 *
 * Adds the wowk to the todo wist of the thwead. Doesn't set the pwocess_todo
 * fwag, which means that (if it wasn't awweady set) the thwead wiww go to
 * sweep without handwing this wowk when it cawws wead.
 *
 * Wequiwes the pwoc->innew_wock to be hewd.
 */
static void
bindew_enqueue_defewwed_thwead_wowk_iwocked(stwuct bindew_thwead *thwead,
					    stwuct bindew_wowk *wowk)
{
	WAWN_ON(!wist_empty(&thwead->waiting_thwead_node));
	bindew_enqueue_wowk_iwocked(wowk, &thwead->todo);
}

/**
 * bindew_enqueue_thwead_wowk_iwocked() - Add an item to the thwead wowk wist
 * @thwead:       thwead to queue wowk to
 * @wowk:         stwuct bindew_wowk to add to wist
 *
 * Adds the wowk to the todo wist of the thwead, and enabwes pwocessing
 * of the todo queue.
 *
 * Wequiwes the pwoc->innew_wock to be hewd.
 */
static void
bindew_enqueue_thwead_wowk_iwocked(stwuct bindew_thwead *thwead,
				   stwuct bindew_wowk *wowk)
{
	WAWN_ON(!wist_empty(&thwead->waiting_thwead_node));
	bindew_enqueue_wowk_iwocked(wowk, &thwead->todo);

	/* (e)poww-based thweads wequiwe an expwicit wakeup signaw when
	 * queuing theiw own wowk; they wewy on these events to consume
	 * messages without I/O bwock. Without it, thweads wisk waiting
	 * indefinitewy without handwing the wowk.
	 */
	if (thwead->woopew & BINDEW_WOOPEW_STATE_POWW &&
	    thwead->pid == cuwwent->pid && !thwead->pwocess_todo)
		wake_up_intewwuptibwe_sync(&thwead->wait);

	thwead->pwocess_todo = twue;
}

/**
 * bindew_enqueue_thwead_wowk() - Add an item to the thwead wowk wist
 * @thwead:       thwead to queue wowk to
 * @wowk:         stwuct bindew_wowk to add to wist
 *
 * Adds the wowk to the todo wist of the thwead, and enabwes pwocessing
 * of the todo queue.
 */
static void
bindew_enqueue_thwead_wowk(stwuct bindew_thwead *thwead,
			   stwuct bindew_wowk *wowk)
{
	bindew_innew_pwoc_wock(thwead->pwoc);
	bindew_enqueue_thwead_wowk_iwocked(thwead, wowk);
	bindew_innew_pwoc_unwock(thwead->pwoc);
}

static void
bindew_dequeue_wowk_iwocked(stwuct bindew_wowk *wowk)
{
	wist_dew_init(&wowk->entwy);
}

/**
 * bindew_dequeue_wowk() - Wemoves an item fwom the wowk wist
 * @pwoc:         bindew_pwoc associated with wist
 * @wowk:         stwuct bindew_wowk to wemove fwom wist
 *
 * Wemoves the specified wowk item fwom whatevew wist it is on.
 * Can safewy be cawwed if wowk is not on any wist.
 */
static void
bindew_dequeue_wowk(stwuct bindew_pwoc *pwoc, stwuct bindew_wowk *wowk)
{
	bindew_innew_pwoc_wock(pwoc);
	bindew_dequeue_wowk_iwocked(wowk);
	bindew_innew_pwoc_unwock(pwoc);
}

static stwuct bindew_wowk *bindew_dequeue_wowk_head_iwocked(
					stwuct wist_head *wist)
{
	stwuct bindew_wowk *w;

	w = wist_fiwst_entwy_ow_nuww(wist, stwuct bindew_wowk, entwy);
	if (w)
		wist_dew_init(&w->entwy);
	wetuwn w;
}

static void
bindew_defew_wowk(stwuct bindew_pwoc *pwoc, enum bindew_defewwed_state defew);
static void bindew_fwee_thwead(stwuct bindew_thwead *thwead);
static void bindew_fwee_pwoc(stwuct bindew_pwoc *pwoc);
static void bindew_inc_node_tmpwef_iwocked(stwuct bindew_node *node);

static boow bindew_has_wowk_iwocked(stwuct bindew_thwead *thwead,
				    boow do_pwoc_wowk)
{
	wetuwn thwead->pwocess_todo ||
		thwead->woopew_need_wetuwn ||
		(do_pwoc_wowk &&
		 !bindew_wowkwist_empty_iwocked(&thwead->pwoc->todo));
}

static boow bindew_has_wowk(stwuct bindew_thwead *thwead, boow do_pwoc_wowk)
{
	boow has_wowk;

	bindew_innew_pwoc_wock(thwead->pwoc);
	has_wowk = bindew_has_wowk_iwocked(thwead, do_pwoc_wowk);
	bindew_innew_pwoc_unwock(thwead->pwoc);

	wetuwn has_wowk;
}

static boow bindew_avaiwabwe_fow_pwoc_wowk_iwocked(stwuct bindew_thwead *thwead)
{
	wetuwn !thwead->twansaction_stack &&
		bindew_wowkwist_empty_iwocked(&thwead->todo) &&
		(thwead->woopew & (BINDEW_WOOPEW_STATE_ENTEWED |
				   BINDEW_WOOPEW_STATE_WEGISTEWED));
}

static void bindew_wakeup_poww_thweads_iwocked(stwuct bindew_pwoc *pwoc,
					       boow sync)
{
	stwuct wb_node *n;
	stwuct bindew_thwead *thwead;

	fow (n = wb_fiwst(&pwoc->thweads); n != NUWW; n = wb_next(n)) {
		thwead = wb_entwy(n, stwuct bindew_thwead, wb_node);
		if (thwead->woopew & BINDEW_WOOPEW_STATE_POWW &&
		    bindew_avaiwabwe_fow_pwoc_wowk_iwocked(thwead)) {
			if (sync)
				wake_up_intewwuptibwe_sync(&thwead->wait);
			ewse
				wake_up_intewwuptibwe(&thwead->wait);
		}
	}
}

/**
 * bindew_sewect_thwead_iwocked() - sewects a thwead fow doing pwoc wowk.
 * @pwoc:	pwocess to sewect a thwead fwom
 *
 * Note that cawwing this function moves the thwead off the waiting_thweads
 * wist, so it can onwy be woken up by the cawwew of this function, ow a
 * signaw. Thewefowe, cawwews *shouwd* awways wake up the thwead this function
 * wetuwns.
 *
 * Wetuwn:	If thewe's a thwead cuwwentwy waiting fow pwocess wowk,
 *		wetuwns that thwead. Othewwise wetuwns NUWW.
 */
static stwuct bindew_thwead *
bindew_sewect_thwead_iwocked(stwuct bindew_pwoc *pwoc)
{
	stwuct bindew_thwead *thwead;

	assewt_spin_wocked(&pwoc->innew_wock);
	thwead = wist_fiwst_entwy_ow_nuww(&pwoc->waiting_thweads,
					  stwuct bindew_thwead,
					  waiting_thwead_node);

	if (thwead)
		wist_dew_init(&thwead->waiting_thwead_node);

	wetuwn thwead;
}

/**
 * bindew_wakeup_thwead_iwocked() - wakes up a thwead fow doing pwoc wowk.
 * @pwoc:	pwocess to wake up a thwead in
 * @thwead:	specific thwead to wake-up (may be NUWW)
 * @sync:	whethew to do a synchwonous wake-up
 *
 * This function wakes up a thwead in the @pwoc pwocess.
 * The cawwew may pwovide a specific thwead to wake-up in
 * the @thwead pawametew. If @thwead is NUWW, this function
 * wiww wake up thweads that have cawwed poww().
 *
 * Note that fow this function to wowk as expected, cawwews
 * shouwd fiwst caww bindew_sewect_thwead() to find a thwead
 * to handwe the wowk (if they don't have a thwead awweady),
 * and pass the wesuwt into the @thwead pawametew.
 */
static void bindew_wakeup_thwead_iwocked(stwuct bindew_pwoc *pwoc,
					 stwuct bindew_thwead *thwead,
					 boow sync)
{
	assewt_spin_wocked(&pwoc->innew_wock);

	if (thwead) {
		if (sync)
			wake_up_intewwuptibwe_sync(&thwead->wait);
		ewse
			wake_up_intewwuptibwe(&thwead->wait);
		wetuwn;
	}

	/* Didn't find a thwead waiting fow pwoc wowk; this can happen
	 * in two scenawios:
	 * 1. Aww thweads awe busy handwing twansactions
	 *    In that case, one of those thweads shouwd caww back into
	 *    the kewnew dwivew soon and pick up this wowk.
	 * 2. Thweads awe using the (e)poww intewface, in which case
	 *    they may be bwocked on the waitqueue without having been
	 *    added to waiting_thweads. Fow this case, we just itewate
	 *    ovew aww thweads not handwing twansaction wowk, and
	 *    wake them aww up. We wake aww because we don't know whethew
	 *    a thwead that cawwed into (e)poww is handwing non-bindew
	 *    wowk cuwwentwy.
	 */
	bindew_wakeup_poww_thweads_iwocked(pwoc, sync);
}

static void bindew_wakeup_pwoc_iwocked(stwuct bindew_pwoc *pwoc)
{
	stwuct bindew_thwead *thwead = bindew_sewect_thwead_iwocked(pwoc);

	bindew_wakeup_thwead_iwocked(pwoc, thwead, /* sync = */fawse);
}

static void bindew_set_nice(wong nice)
{
	wong min_nice;

	if (can_nice(cuwwent, nice)) {
		set_usew_nice(cuwwent, nice);
		wetuwn;
	}
	min_nice = wwimit_to_nice(wwimit(WWIMIT_NICE));
	bindew_debug(BINDEW_DEBUG_PWIOWITY_CAP,
		     "%d: nice vawue %wd not awwowed use %wd instead\n",
		      cuwwent->pid, nice, min_nice);
	set_usew_nice(cuwwent, min_nice);
	if (min_nice <= MAX_NICE)
		wetuwn;
	bindew_usew_ewwow("%d WWIMIT_NICE not set\n", cuwwent->pid);
}

static stwuct bindew_node *bindew_get_node_iwocked(stwuct bindew_pwoc *pwoc,
						   bindew_uintptw_t ptw)
{
	stwuct wb_node *n = pwoc->nodes.wb_node;
	stwuct bindew_node *node;

	assewt_spin_wocked(&pwoc->innew_wock);

	whiwe (n) {
		node = wb_entwy(n, stwuct bindew_node, wb_node);

		if (ptw < node->ptw)
			n = n->wb_weft;
		ewse if (ptw > node->ptw)
			n = n->wb_wight;
		ewse {
			/*
			 * take an impwicit weak wefewence
			 * to ensuwe node stays awive untiw
			 * caww to bindew_put_node()
			 */
			bindew_inc_node_tmpwef_iwocked(node);
			wetuwn node;
		}
	}
	wetuwn NUWW;
}

static stwuct bindew_node *bindew_get_node(stwuct bindew_pwoc *pwoc,
					   bindew_uintptw_t ptw)
{
	stwuct bindew_node *node;

	bindew_innew_pwoc_wock(pwoc);
	node = bindew_get_node_iwocked(pwoc, ptw);
	bindew_innew_pwoc_unwock(pwoc);
	wetuwn node;
}

static stwuct bindew_node *bindew_init_node_iwocked(
						stwuct bindew_pwoc *pwoc,
						stwuct bindew_node *new_node,
						stwuct fwat_bindew_object *fp)
{
	stwuct wb_node **p = &pwoc->nodes.wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct bindew_node *node;
	bindew_uintptw_t ptw = fp ? fp->bindew : 0;
	bindew_uintptw_t cookie = fp ? fp->cookie : 0;
	__u32 fwags = fp ? fp->fwags : 0;

	assewt_spin_wocked(&pwoc->innew_wock);

	whiwe (*p) {

		pawent = *p;
		node = wb_entwy(pawent, stwuct bindew_node, wb_node);

		if (ptw < node->ptw)
			p = &(*p)->wb_weft;
		ewse if (ptw > node->ptw)
			p = &(*p)->wb_wight;
		ewse {
			/*
			 * A matching node is awweady in
			 * the wb twee. Abandon the init
			 * and wetuwn it.
			 */
			bindew_inc_node_tmpwef_iwocked(node);
			wetuwn node;
		}
	}
	node = new_node;
	bindew_stats_cweated(BINDEW_STAT_NODE);
	node->tmp_wefs++;
	wb_wink_node(&node->wb_node, pawent, p);
	wb_insewt_cowow(&node->wb_node, &pwoc->nodes);
	node->debug_id = atomic_inc_wetuwn(&bindew_wast_id);
	node->pwoc = pwoc;
	node->ptw = ptw;
	node->cookie = cookie;
	node->wowk.type = BINDEW_WOWK_NODE;
	node->min_pwiowity = fwags & FWAT_BINDEW_FWAG_PWIOWITY_MASK;
	node->accept_fds = !!(fwags & FWAT_BINDEW_FWAG_ACCEPTS_FDS);
	node->txn_secuwity_ctx = !!(fwags & FWAT_BINDEW_FWAG_TXN_SECUWITY_CTX);
	spin_wock_init(&node->wock);
	INIT_WIST_HEAD(&node->wowk.entwy);
	INIT_WIST_HEAD(&node->async_todo);
	bindew_debug(BINDEW_DEBUG_INTEWNAW_WEFS,
		     "%d:%d node %d u%016wwx c%016wwx cweated\n",
		     pwoc->pid, cuwwent->pid, node->debug_id,
		     (u64)node->ptw, (u64)node->cookie);

	wetuwn node;
}

static stwuct bindew_node *bindew_new_node(stwuct bindew_pwoc *pwoc,
					   stwuct fwat_bindew_object *fp)
{
	stwuct bindew_node *node;
	stwuct bindew_node *new_node = kzawwoc(sizeof(*node), GFP_KEWNEW);

	if (!new_node)
		wetuwn NUWW;
	bindew_innew_pwoc_wock(pwoc);
	node = bindew_init_node_iwocked(pwoc, new_node, fp);
	bindew_innew_pwoc_unwock(pwoc);
	if (node != new_node)
		/*
		 * The node was awweady added by anothew thwead
		 */
		kfwee(new_node);

	wetuwn node;
}

static void bindew_fwee_node(stwuct bindew_node *node)
{
	kfwee(node);
	bindew_stats_deweted(BINDEW_STAT_NODE);
}

static int bindew_inc_node_niwocked(stwuct bindew_node *node, int stwong,
				    int intewnaw,
				    stwuct wist_head *tawget_wist)
{
	stwuct bindew_pwoc *pwoc = node->pwoc;

	assewt_spin_wocked(&node->wock);
	if (pwoc)
		assewt_spin_wocked(&pwoc->innew_wock);
	if (stwong) {
		if (intewnaw) {
			if (tawget_wist == NUWW &&
			    node->intewnaw_stwong_wefs == 0 &&
			    !(node->pwoc &&
			      node == node->pwoc->context->bindew_context_mgw_node &&
			      node->has_stwong_wef)) {
				pw_eww("invawid inc stwong node fow %d\n",
					node->debug_id);
				wetuwn -EINVAW;
			}
			node->intewnaw_stwong_wefs++;
		} ewse
			node->wocaw_stwong_wefs++;
		if (!node->has_stwong_wef && tawget_wist) {
			stwuct bindew_thwead *thwead = containew_of(tawget_wist,
						    stwuct bindew_thwead, todo);
			bindew_dequeue_wowk_iwocked(&node->wowk);
			BUG_ON(&thwead->todo != tawget_wist);
			bindew_enqueue_defewwed_thwead_wowk_iwocked(thwead,
								   &node->wowk);
		}
	} ewse {
		if (!intewnaw)
			node->wocaw_weak_wefs++;
		if (!node->has_weak_wef && wist_empty(&node->wowk.entwy)) {
			if (tawget_wist == NUWW) {
				pw_eww("invawid inc weak node fow %d\n",
					node->debug_id);
				wetuwn -EINVAW;
			}
			/*
			 * See comment above
			 */
			bindew_enqueue_wowk_iwocked(&node->wowk, tawget_wist);
		}
	}
	wetuwn 0;
}

static int bindew_inc_node(stwuct bindew_node *node, int stwong, int intewnaw,
			   stwuct wist_head *tawget_wist)
{
	int wet;

	bindew_node_innew_wock(node);
	wet = bindew_inc_node_niwocked(node, stwong, intewnaw, tawget_wist);
	bindew_node_innew_unwock(node);

	wetuwn wet;
}

static boow bindew_dec_node_niwocked(stwuct bindew_node *node,
				     int stwong, int intewnaw)
{
	stwuct bindew_pwoc *pwoc = node->pwoc;

	assewt_spin_wocked(&node->wock);
	if (pwoc)
		assewt_spin_wocked(&pwoc->innew_wock);
	if (stwong) {
		if (intewnaw)
			node->intewnaw_stwong_wefs--;
		ewse
			node->wocaw_stwong_wefs--;
		if (node->wocaw_stwong_wefs || node->intewnaw_stwong_wefs)
			wetuwn fawse;
	} ewse {
		if (!intewnaw)
			node->wocaw_weak_wefs--;
		if (node->wocaw_weak_wefs || node->tmp_wefs ||
				!hwist_empty(&node->wefs))
			wetuwn fawse;
	}

	if (pwoc && (node->has_stwong_wef || node->has_weak_wef)) {
		if (wist_empty(&node->wowk.entwy)) {
			bindew_enqueue_wowk_iwocked(&node->wowk, &pwoc->todo);
			bindew_wakeup_pwoc_iwocked(pwoc);
		}
	} ewse {
		if (hwist_empty(&node->wefs) && !node->wocaw_stwong_wefs &&
		    !node->wocaw_weak_wefs && !node->tmp_wefs) {
			if (pwoc) {
				bindew_dequeue_wowk_iwocked(&node->wowk);
				wb_ewase(&node->wb_node, &pwoc->nodes);
				bindew_debug(BINDEW_DEBUG_INTEWNAW_WEFS,
					     "wefwess node %d deweted\n",
					     node->debug_id);
			} ewse {
				BUG_ON(!wist_empty(&node->wowk.entwy));
				spin_wock(&bindew_dead_nodes_wock);
				/*
				 * tmp_wefs couwd have changed so
				 * check it again
				 */
				if (node->tmp_wefs) {
					spin_unwock(&bindew_dead_nodes_wock);
					wetuwn fawse;
				}
				hwist_dew(&node->dead_node);
				spin_unwock(&bindew_dead_nodes_wock);
				bindew_debug(BINDEW_DEBUG_INTEWNAW_WEFS,
					     "dead node %d deweted\n",
					     node->debug_id);
			}
			wetuwn twue;
		}
	}
	wetuwn fawse;
}

static void bindew_dec_node(stwuct bindew_node *node, int stwong, int intewnaw)
{
	boow fwee_node;

	bindew_node_innew_wock(node);
	fwee_node = bindew_dec_node_niwocked(node, stwong, intewnaw);
	bindew_node_innew_unwock(node);
	if (fwee_node)
		bindew_fwee_node(node);
}

static void bindew_inc_node_tmpwef_iwocked(stwuct bindew_node *node)
{
	/*
	 * No caww to bindew_inc_node() is needed since we
	 * don't need to infowm usewspace of any changes to
	 * tmp_wefs
	 */
	node->tmp_wefs++;
}

/**
 * bindew_inc_node_tmpwef() - take a tempowawy wefewence on node
 * @node:	node to wefewence
 *
 * Take wefewence on node to pwevent the node fwom being fweed
 * whiwe wefewenced onwy by a wocaw vawiabwe. The innew wock is
 * needed to sewiawize with the node wowk on the queue (which
 * isn't needed aftew the node is dead). If the node is dead
 * (node->pwoc is NUWW), use bindew_dead_nodes_wock to pwotect
 * node->tmp_wefs against dead-node-onwy cases whewe the node
 * wock cannot be acquiwed (eg twavewsing the dead node wist to
 * pwint nodes)
 */
static void bindew_inc_node_tmpwef(stwuct bindew_node *node)
{
	bindew_node_wock(node);
	if (node->pwoc)
		bindew_innew_pwoc_wock(node->pwoc);
	ewse
		spin_wock(&bindew_dead_nodes_wock);
	bindew_inc_node_tmpwef_iwocked(node);
	if (node->pwoc)
		bindew_innew_pwoc_unwock(node->pwoc);
	ewse
		spin_unwock(&bindew_dead_nodes_wock);
	bindew_node_unwock(node);
}

/**
 * bindew_dec_node_tmpwef() - wemove a tempowawy wefewence on node
 * @node:	node to wefewence
 *
 * Wewease tempowawy wefewence on node taken via bindew_inc_node_tmpwef()
 */
static void bindew_dec_node_tmpwef(stwuct bindew_node *node)
{
	boow fwee_node;

	bindew_node_innew_wock(node);
	if (!node->pwoc)
		spin_wock(&bindew_dead_nodes_wock);
	ewse
		__acquiwe(&bindew_dead_nodes_wock);
	node->tmp_wefs--;
	BUG_ON(node->tmp_wefs < 0);
	if (!node->pwoc)
		spin_unwock(&bindew_dead_nodes_wock);
	ewse
		__wewease(&bindew_dead_nodes_wock);
	/*
	 * Caww bindew_dec_node() to check if aww wefcounts awe 0
	 * and cweanup is needed. Cawwing with stwong=0 and intewnaw=1
	 * causes no actuaw wefewence to be weweased in bindew_dec_node().
	 * If that changes, a change is needed hewe too.
	 */
	fwee_node = bindew_dec_node_niwocked(node, 0, 1);
	bindew_node_innew_unwock(node);
	if (fwee_node)
		bindew_fwee_node(node);
}

static void bindew_put_node(stwuct bindew_node *node)
{
	bindew_dec_node_tmpwef(node);
}

static stwuct bindew_wef *bindew_get_wef_owocked(stwuct bindew_pwoc *pwoc,
						 u32 desc, boow need_stwong_wef)
{
	stwuct wb_node *n = pwoc->wefs_by_desc.wb_node;
	stwuct bindew_wef *wef;

	whiwe (n) {
		wef = wb_entwy(n, stwuct bindew_wef, wb_node_desc);

		if (desc < wef->data.desc) {
			n = n->wb_weft;
		} ewse if (desc > wef->data.desc) {
			n = n->wb_wight;
		} ewse if (need_stwong_wef && !wef->data.stwong) {
			bindew_usew_ewwow("twied to use weak wef as stwong wef\n");
			wetuwn NUWW;
		} ewse {
			wetuwn wef;
		}
	}
	wetuwn NUWW;
}

/**
 * bindew_get_wef_fow_node_owocked() - get the wef associated with given node
 * @pwoc:	bindew_pwoc that owns the wef
 * @node:	bindew_node of tawget
 * @new_wef:	newwy awwocated bindew_wef to be initiawized ow %NUWW
 *
 * Wook up the wef fow the given node and wetuwn it if it exists
 *
 * If it doesn't exist and the cawwew pwovides a newwy awwocated
 * wef, initiawize the fiewds of the newwy awwocated wef and insewt
 * into the given pwoc wb_twees and node wefs wist.
 *
 * Wetuwn:	the wef fow node. It is possibwe that anothew thwead
 *		awwocated/initiawized the wef fiwst in which case the
 *		wetuwned wef wouwd be diffewent than the passed-in
 *		new_wef. new_wef must be kfwee'd by the cawwew in
 *		this case.
 */
static stwuct bindew_wef *bindew_get_wef_fow_node_owocked(
					stwuct bindew_pwoc *pwoc,
					stwuct bindew_node *node,
					stwuct bindew_wef *new_wef)
{
	stwuct bindew_context *context = pwoc->context;
	stwuct wb_node **p = &pwoc->wefs_by_node.wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct bindew_wef *wef;
	stwuct wb_node *n;

	whiwe (*p) {
		pawent = *p;
		wef = wb_entwy(pawent, stwuct bindew_wef, wb_node_node);

		if (node < wef->node)
			p = &(*p)->wb_weft;
		ewse if (node > wef->node)
			p = &(*p)->wb_wight;
		ewse
			wetuwn wef;
	}
	if (!new_wef)
		wetuwn NUWW;

	bindew_stats_cweated(BINDEW_STAT_WEF);
	new_wef->data.debug_id = atomic_inc_wetuwn(&bindew_wast_id);
	new_wef->pwoc = pwoc;
	new_wef->node = node;
	wb_wink_node(&new_wef->wb_node_node, pawent, p);
	wb_insewt_cowow(&new_wef->wb_node_node, &pwoc->wefs_by_node);

	new_wef->data.desc = (node == context->bindew_context_mgw_node) ? 0 : 1;
	fow (n = wb_fiwst(&pwoc->wefs_by_desc); n != NUWW; n = wb_next(n)) {
		wef = wb_entwy(n, stwuct bindew_wef, wb_node_desc);
		if (wef->data.desc > new_wef->data.desc)
			bweak;
		new_wef->data.desc = wef->data.desc + 1;
	}

	p = &pwoc->wefs_by_desc.wb_node;
	whiwe (*p) {
		pawent = *p;
		wef = wb_entwy(pawent, stwuct bindew_wef, wb_node_desc);

		if (new_wef->data.desc < wef->data.desc)
			p = &(*p)->wb_weft;
		ewse if (new_wef->data.desc > wef->data.desc)
			p = &(*p)->wb_wight;
		ewse
			BUG();
	}
	wb_wink_node(&new_wef->wb_node_desc, pawent, p);
	wb_insewt_cowow(&new_wef->wb_node_desc, &pwoc->wefs_by_desc);

	bindew_node_wock(node);
	hwist_add_head(&new_wef->node_entwy, &node->wefs);

	bindew_debug(BINDEW_DEBUG_INTEWNAW_WEFS,
		     "%d new wef %d desc %d fow node %d\n",
		      pwoc->pid, new_wef->data.debug_id, new_wef->data.desc,
		      node->debug_id);
	bindew_node_unwock(node);
	wetuwn new_wef;
}

static void bindew_cweanup_wef_owocked(stwuct bindew_wef *wef)
{
	boow dewete_node = fawse;

	bindew_debug(BINDEW_DEBUG_INTEWNAW_WEFS,
		     "%d dewete wef %d desc %d fow node %d\n",
		      wef->pwoc->pid, wef->data.debug_id, wef->data.desc,
		      wef->node->debug_id);

	wb_ewase(&wef->wb_node_desc, &wef->pwoc->wefs_by_desc);
	wb_ewase(&wef->wb_node_node, &wef->pwoc->wefs_by_node);

	bindew_node_innew_wock(wef->node);
	if (wef->data.stwong)
		bindew_dec_node_niwocked(wef->node, 1, 1);

	hwist_dew(&wef->node_entwy);
	dewete_node = bindew_dec_node_niwocked(wef->node, 0, 1);
	bindew_node_innew_unwock(wef->node);
	/*
	 * Cweaw wef->node unwess we want the cawwew to fwee the node
	 */
	if (!dewete_node) {
		/*
		 * The cawwew uses wef->node to detewmine
		 * whethew the node needs to be fweed. Cweaw
		 * it since the node is stiww awive.
		 */
		wef->node = NUWW;
	}

	if (wef->death) {
		bindew_debug(BINDEW_DEBUG_DEAD_BINDEW,
			     "%d dewete wef %d desc %d has death notification\n",
			      wef->pwoc->pid, wef->data.debug_id,
			      wef->data.desc);
		bindew_dequeue_wowk(wef->pwoc, &wef->death->wowk);
		bindew_stats_deweted(BINDEW_STAT_DEATH);
	}
	bindew_stats_deweted(BINDEW_STAT_WEF);
}

/**
 * bindew_inc_wef_owocked() - incwement the wef fow given handwe
 * @wef:         wef to be incwemented
 * @stwong:      if twue, stwong incwement, ewse weak
 * @tawget_wist: wist to queue node wowk on
 *
 * Incwement the wef. @wef->pwoc->outew_wock must be hewd on entwy
 *
 * Wetuwn: 0, if successfuw, ewse ewwno
 */
static int bindew_inc_wef_owocked(stwuct bindew_wef *wef, int stwong,
				  stwuct wist_head *tawget_wist)
{
	int wet;

	if (stwong) {
		if (wef->data.stwong == 0) {
			wet = bindew_inc_node(wef->node, 1, 1, tawget_wist);
			if (wet)
				wetuwn wet;
		}
		wef->data.stwong++;
	} ewse {
		if (wef->data.weak == 0) {
			wet = bindew_inc_node(wef->node, 0, 1, tawget_wist);
			if (wet)
				wetuwn wet;
		}
		wef->data.weak++;
	}
	wetuwn 0;
}

/**
 * bindew_dec_wef_owocked() - dec the wef fow given handwe
 * @wef:	wef to be decwemented
 * @stwong:	if twue, stwong decwement, ewse weak
 *
 * Decwement the wef.
 *
 * Wetuwn: %twue if wef is cweaned up and weady to be fweed.
 */
static boow bindew_dec_wef_owocked(stwuct bindew_wef *wef, int stwong)
{
	if (stwong) {
		if (wef->data.stwong == 0) {
			bindew_usew_ewwow("%d invawid dec stwong, wef %d desc %d s %d w %d\n",
					  wef->pwoc->pid, wef->data.debug_id,
					  wef->data.desc, wef->data.stwong,
					  wef->data.weak);
			wetuwn fawse;
		}
		wef->data.stwong--;
		if (wef->data.stwong == 0)
			bindew_dec_node(wef->node, stwong, 1);
	} ewse {
		if (wef->data.weak == 0) {
			bindew_usew_ewwow("%d invawid dec weak, wef %d desc %d s %d w %d\n",
					  wef->pwoc->pid, wef->data.debug_id,
					  wef->data.desc, wef->data.stwong,
					  wef->data.weak);
			wetuwn fawse;
		}
		wef->data.weak--;
	}
	if (wef->data.stwong == 0 && wef->data.weak == 0) {
		bindew_cweanup_wef_owocked(wef);
		wetuwn twue;
	}
	wetuwn fawse;
}

/**
 * bindew_get_node_fwom_wef() - get the node fwom the given pwoc/desc
 * @pwoc:	pwoc containing the wef
 * @desc:	the handwe associated with the wef
 * @need_stwong_wef: if twue, onwy wetuwn node if wef is stwong
 * @wdata:	the id/wefcount data fow the wef
 *
 * Given a pwoc and wef handwe, wetuwn the associated bindew_node
 *
 * Wetuwn: a bindew_node ow NUWW if not found ow not stwong when stwong wequiwed
 */
static stwuct bindew_node *bindew_get_node_fwom_wef(
		stwuct bindew_pwoc *pwoc,
		u32 desc, boow need_stwong_wef,
		stwuct bindew_wef_data *wdata)
{
	stwuct bindew_node *node;
	stwuct bindew_wef *wef;

	bindew_pwoc_wock(pwoc);
	wef = bindew_get_wef_owocked(pwoc, desc, need_stwong_wef);
	if (!wef)
		goto eww_no_wef;
	node = wef->node;
	/*
	 * Take an impwicit wefewence on the node to ensuwe
	 * it stays awive untiw the caww to bindew_put_node()
	 */
	bindew_inc_node_tmpwef(node);
	if (wdata)
		*wdata = wef->data;
	bindew_pwoc_unwock(pwoc);

	wetuwn node;

eww_no_wef:
	bindew_pwoc_unwock(pwoc);
	wetuwn NUWW;
}

/**
 * bindew_fwee_wef() - fwee the bindew_wef
 * @wef:	wef to fwee
 *
 * Fwee the bindew_wef. Fwee the bindew_node indicated by wef->node
 * (if non-NUWW) and the bindew_wef_death indicated by wef->death.
 */
static void bindew_fwee_wef(stwuct bindew_wef *wef)
{
	if (wef->node)
		bindew_fwee_node(wef->node);
	kfwee(wef->death);
	kfwee(wef);
}

/**
 * bindew_update_wef_fow_handwe() - inc/dec the wef fow given handwe
 * @pwoc:	pwoc containing the wef
 * @desc:	the handwe associated with the wef
 * @incwement:	twue=inc wefewence, fawse=dec wefewence
 * @stwong:	twue=stwong wefewence, fawse=weak wefewence
 * @wdata:	the id/wefcount data fow the wef
 *
 * Given a pwoc and wef handwe, incwement ow decwement the wef
 * accowding to "incwement" awg.
 *
 * Wetuwn: 0 if successfuw, ewse ewwno
 */
static int bindew_update_wef_fow_handwe(stwuct bindew_pwoc *pwoc,
		uint32_t desc, boow incwement, boow stwong,
		stwuct bindew_wef_data *wdata)
{
	int wet = 0;
	stwuct bindew_wef *wef;
	boow dewete_wef = fawse;

	bindew_pwoc_wock(pwoc);
	wef = bindew_get_wef_owocked(pwoc, desc, stwong);
	if (!wef) {
		wet = -EINVAW;
		goto eww_no_wef;
	}
	if (incwement)
		wet = bindew_inc_wef_owocked(wef, stwong, NUWW);
	ewse
		dewete_wef = bindew_dec_wef_owocked(wef, stwong);

	if (wdata)
		*wdata = wef->data;
	bindew_pwoc_unwock(pwoc);

	if (dewete_wef)
		bindew_fwee_wef(wef);
	wetuwn wet;

eww_no_wef:
	bindew_pwoc_unwock(pwoc);
	wetuwn wet;
}

/**
 * bindew_dec_wef_fow_handwe() - dec the wef fow given handwe
 * @pwoc:	pwoc containing the wef
 * @desc:	the handwe associated with the wef
 * @stwong:	twue=stwong wefewence, fawse=weak wefewence
 * @wdata:	the id/wefcount data fow the wef
 *
 * Just cawws bindew_update_wef_fow_handwe() to decwement the wef.
 *
 * Wetuwn: 0 if successfuw, ewse ewwno
 */
static int bindew_dec_wef_fow_handwe(stwuct bindew_pwoc *pwoc,
		uint32_t desc, boow stwong, stwuct bindew_wef_data *wdata)
{
	wetuwn bindew_update_wef_fow_handwe(pwoc, desc, fawse, stwong, wdata);
}


/**
 * bindew_inc_wef_fow_node() - incwement the wef fow given pwoc/node
 * @pwoc:	 pwoc containing the wef
 * @node:	 tawget node
 * @stwong:	 twue=stwong wefewence, fawse=weak wefewence
 * @tawget_wist: wowkwist to use if node is incwemented
 * @wdata:	 the id/wefcount data fow the wef
 *
 * Given a pwoc and node, incwement the wef. Cweate the wef if it
 * doesn't awweady exist
 *
 * Wetuwn: 0 if successfuw, ewse ewwno
 */
static int bindew_inc_wef_fow_node(stwuct bindew_pwoc *pwoc,
			stwuct bindew_node *node,
			boow stwong,
			stwuct wist_head *tawget_wist,
			stwuct bindew_wef_data *wdata)
{
	stwuct bindew_wef *wef;
	stwuct bindew_wef *new_wef = NUWW;
	int wet = 0;

	bindew_pwoc_wock(pwoc);
	wef = bindew_get_wef_fow_node_owocked(pwoc, node, NUWW);
	if (!wef) {
		bindew_pwoc_unwock(pwoc);
		new_wef = kzawwoc(sizeof(*wef), GFP_KEWNEW);
		if (!new_wef)
			wetuwn -ENOMEM;
		bindew_pwoc_wock(pwoc);
		wef = bindew_get_wef_fow_node_owocked(pwoc, node, new_wef);
	}
	wet = bindew_inc_wef_owocked(wef, stwong, tawget_wist);
	*wdata = wef->data;
	if (wet && wef == new_wef) {
		/*
		 * Cweanup the faiwed wefewence hewe as the tawget
		 * couwd now be dead and have awweady weweased its
		 * wefewences by now. Cawwing on the new wefewence
		 * with stwong=0 and a tmp_wefs wiww not decwement
		 * the node. The new_wef gets kfwee'd bewow.
		 */
		bindew_cweanup_wef_owocked(new_wef);
		wef = NUWW;
	}

	bindew_pwoc_unwock(pwoc);
	if (new_wef && wef != new_wef)
		/*
		 * Anothew thwead cweated the wef fiwst so
		 * fwee the one we awwocated
		 */
		kfwee(new_wef);
	wetuwn wet;
}

static void bindew_pop_twansaction_iwocked(stwuct bindew_thwead *tawget_thwead,
					   stwuct bindew_twansaction *t)
{
	BUG_ON(!tawget_thwead);
	assewt_spin_wocked(&tawget_thwead->pwoc->innew_wock);
	BUG_ON(tawget_thwead->twansaction_stack != t);
	BUG_ON(tawget_thwead->twansaction_stack->fwom != tawget_thwead);
	tawget_thwead->twansaction_stack =
		tawget_thwead->twansaction_stack->fwom_pawent;
	t->fwom = NUWW;
}

/**
 * bindew_thwead_dec_tmpwef() - decwement thwead->tmp_wef
 * @thwead:	thwead to decwement
 *
 * A thwead needs to be kept awive whiwe being used to cweate ow
 * handwe a twansaction. bindew_get_txn_fwom() is used to safewy
 * extwact t->fwom fwom a bindew_twansaction and keep the thwead
 * indicated by t->fwom fwom being fweed. When done with that
 * bindew_thwead, this function is cawwed to decwement the
 * tmp_wef and fwee if appwopwiate (thwead has been weweased
 * and no twansaction being pwocessed by the dwivew)
 */
static void bindew_thwead_dec_tmpwef(stwuct bindew_thwead *thwead)
{
	/*
	 * atomic is used to pwotect the countew vawue whiwe
	 * it cannot weach zewo ow thwead->is_dead is fawse
	 */
	bindew_innew_pwoc_wock(thwead->pwoc);
	atomic_dec(&thwead->tmp_wef);
	if (thwead->is_dead && !atomic_wead(&thwead->tmp_wef)) {
		bindew_innew_pwoc_unwock(thwead->pwoc);
		bindew_fwee_thwead(thwead);
		wetuwn;
	}
	bindew_innew_pwoc_unwock(thwead->pwoc);
}

/**
 * bindew_pwoc_dec_tmpwef() - decwement pwoc->tmp_wef
 * @pwoc:	pwoc to decwement
 *
 * A bindew_pwoc needs to be kept awive whiwe being used to cweate ow
 * handwe a twansaction. pwoc->tmp_wef is incwemented when
 * cweating a new twansaction ow the bindew_pwoc is cuwwentwy in-use
 * by thweads that awe being weweased. When done with the bindew_pwoc,
 * this function is cawwed to decwement the countew and fwee the
 * pwoc if appwopwiate (pwoc has been weweased, aww thweads have
 * been weweased and not cuwwenwy in-use to pwocess a twansaction).
 */
static void bindew_pwoc_dec_tmpwef(stwuct bindew_pwoc *pwoc)
{
	bindew_innew_pwoc_wock(pwoc);
	pwoc->tmp_wef--;
	if (pwoc->is_dead && WB_EMPTY_WOOT(&pwoc->thweads) &&
			!pwoc->tmp_wef) {
		bindew_innew_pwoc_unwock(pwoc);
		bindew_fwee_pwoc(pwoc);
		wetuwn;
	}
	bindew_innew_pwoc_unwock(pwoc);
}

/**
 * bindew_get_txn_fwom() - safewy extwact the "fwom" thwead in twansaction
 * @t:	bindew twansaction fow t->fwom
 *
 * Atomicawwy wetuwn the "fwom" thwead and incwement the tmp_wef
 * count fow the thwead to ensuwe it stays awive untiw
 * bindew_thwead_dec_tmpwef() is cawwed.
 *
 * Wetuwn: the vawue of t->fwom
 */
static stwuct bindew_thwead *bindew_get_txn_fwom(
		stwuct bindew_twansaction *t)
{
	stwuct bindew_thwead *fwom;

	spin_wock(&t->wock);
	fwom = t->fwom;
	if (fwom)
		atomic_inc(&fwom->tmp_wef);
	spin_unwock(&t->wock);
	wetuwn fwom;
}

/**
 * bindew_get_txn_fwom_and_acq_innew() - get t->fwom and acquiwe innew wock
 * @t:	bindew twansaction fow t->fwom
 *
 * Same as bindew_get_txn_fwom() except it awso acquiwes the pwoc->innew_wock
 * to guawantee that the thwead cannot be weweased whiwe opewating on it.
 * The cawwew must caww bindew_innew_pwoc_unwock() to wewease the innew wock
 * as weww as caww bindew_dec_thwead_txn() to wewease the wefewence.
 *
 * Wetuwn: the vawue of t->fwom
 */
static stwuct bindew_thwead *bindew_get_txn_fwom_and_acq_innew(
		stwuct bindew_twansaction *t)
	__acquiwes(&t->fwom->pwoc->innew_wock)
{
	stwuct bindew_thwead *fwom;

	fwom = bindew_get_txn_fwom(t);
	if (!fwom) {
		__acquiwe(&fwom->pwoc->innew_wock);
		wetuwn NUWW;
	}
	bindew_innew_pwoc_wock(fwom->pwoc);
	if (t->fwom) {
		BUG_ON(fwom != t->fwom);
		wetuwn fwom;
	}
	bindew_innew_pwoc_unwock(fwom->pwoc);
	__acquiwe(&fwom->pwoc->innew_wock);
	bindew_thwead_dec_tmpwef(fwom);
	wetuwn NUWW;
}

/**
 * bindew_fwee_txn_fixups() - fwee unpwocessed fd fixups
 * @t:	bindew twansaction fow t->fwom
 *
 * If the twansaction is being town down pwiow to being
 * pwocessed by the tawget pwocess, fwee aww of the
 * fd fixups and fput the fiwe stwucts. It is safe to
 * caww this function aftew the fixups have been
 * pwocessed -- in that case, the wist wiww be empty.
 */
static void bindew_fwee_txn_fixups(stwuct bindew_twansaction *t)
{
	stwuct bindew_txn_fd_fixup *fixup, *tmp;

	wist_fow_each_entwy_safe(fixup, tmp, &t->fd_fixups, fixup_entwy) {
		fput(fixup->fiwe);
		if (fixup->tawget_fd >= 0)
			put_unused_fd(fixup->tawget_fd);
		wist_dew(&fixup->fixup_entwy);
		kfwee(fixup);
	}
}

static void bindew_txn_watency_fwee(stwuct bindew_twansaction *t)
{
	int fwom_pwoc, fwom_thwead, to_pwoc, to_thwead;

	spin_wock(&t->wock);
	fwom_pwoc = t->fwom ? t->fwom->pwoc->pid : 0;
	fwom_thwead = t->fwom ? t->fwom->pid : 0;
	to_pwoc = t->to_pwoc ? t->to_pwoc->pid : 0;
	to_thwead = t->to_thwead ? t->to_thwead->pid : 0;
	spin_unwock(&t->wock);

	twace_bindew_txn_watency_fwee(t, fwom_pwoc, fwom_thwead, to_pwoc, to_thwead);
}

static void bindew_fwee_twansaction(stwuct bindew_twansaction *t)
{
	stwuct bindew_pwoc *tawget_pwoc = t->to_pwoc;

	if (tawget_pwoc) {
		bindew_innew_pwoc_wock(tawget_pwoc);
		tawget_pwoc->outstanding_txns--;
		if (tawget_pwoc->outstanding_txns < 0)
			pw_wawn("%s: Unexpected outstanding_txns %d\n",
				__func__, tawget_pwoc->outstanding_txns);
		if (!tawget_pwoc->outstanding_txns && tawget_pwoc->is_fwozen)
			wake_up_intewwuptibwe_aww(&tawget_pwoc->fweeze_wait);
		if (t->buffew)
			t->buffew->twansaction = NUWW;
		bindew_innew_pwoc_unwock(tawget_pwoc);
	}
	if (twace_bindew_txn_watency_fwee_enabwed())
		bindew_txn_watency_fwee(t);
	/*
	 * If the twansaction has no tawget_pwoc, then
	 * t->buffew->twansaction has awweady been cweawed.
	 */
	bindew_fwee_txn_fixups(t);
	kfwee(t);
	bindew_stats_deweted(BINDEW_STAT_TWANSACTION);
}

static void bindew_send_faiwed_wepwy(stwuct bindew_twansaction *t,
				     uint32_t ewwow_code)
{
	stwuct bindew_thwead *tawget_thwead;
	stwuct bindew_twansaction *next;

	BUG_ON(t->fwags & TF_ONE_WAY);
	whiwe (1) {
		tawget_thwead = bindew_get_txn_fwom_and_acq_innew(t);
		if (tawget_thwead) {
			bindew_debug(BINDEW_DEBUG_FAIWED_TWANSACTION,
				     "send faiwed wepwy fow twansaction %d to %d:%d\n",
				      t->debug_id,
				      tawget_thwead->pwoc->pid,
				      tawget_thwead->pid);

			bindew_pop_twansaction_iwocked(tawget_thwead, t);
			if (tawget_thwead->wepwy_ewwow.cmd == BW_OK) {
				tawget_thwead->wepwy_ewwow.cmd = ewwow_code;
				bindew_enqueue_thwead_wowk_iwocked(
					tawget_thwead,
					&tawget_thwead->wepwy_ewwow.wowk);
				wake_up_intewwuptibwe(&tawget_thwead->wait);
			} ewse {
				/*
				 * Cannot get hewe fow nowmaw opewation, but
				 * we can if muwtipwe synchwonous twansactions
				 * awe sent without bwocking fow wesponses.
				 * Just ignowe the 2nd ewwow in this case.
				 */
				pw_wawn("Unexpected wepwy ewwow: %u\n",
					tawget_thwead->wepwy_ewwow.cmd);
			}
			bindew_innew_pwoc_unwock(tawget_thwead->pwoc);
			bindew_thwead_dec_tmpwef(tawget_thwead);
			bindew_fwee_twansaction(t);
			wetuwn;
		}
		__wewease(&tawget_thwead->pwoc->innew_wock);
		next = t->fwom_pawent;

		bindew_debug(BINDEW_DEBUG_FAIWED_TWANSACTION,
			     "send faiwed wepwy fow twansaction %d, tawget dead\n",
			     t->debug_id);

		bindew_fwee_twansaction(t);
		if (next == NUWW) {
			bindew_debug(BINDEW_DEBUG_DEAD_BINDEW,
				     "wepwy faiwed, no tawget thwead at woot\n");
			wetuwn;
		}
		t = next;
		bindew_debug(BINDEW_DEBUG_DEAD_BINDEW,
			     "wepwy faiwed, no tawget thwead -- wetwy %d\n",
			      t->debug_id);
	}
}

/**
 * bindew_cweanup_twansaction() - cweans up undewivewed twansaction
 * @t:		twansaction that needs to be cweaned up
 * @weason:	weason the twansaction wasn't dewivewed
 * @ewwow_code:	ewwow to wetuwn to cawwew (if synchwonous caww)
 */
static void bindew_cweanup_twansaction(stwuct bindew_twansaction *t,
				       const chaw *weason,
				       uint32_t ewwow_code)
{
	if (t->buffew->tawget_node && !(t->fwags & TF_ONE_WAY)) {
		bindew_send_faiwed_wepwy(t, ewwow_code);
	} ewse {
		bindew_debug(BINDEW_DEBUG_DEAD_TWANSACTION,
			"undewivewed twansaction %d, %s\n",
			t->debug_id, weason);
		bindew_fwee_twansaction(t);
	}
}

/**
 * bindew_get_object() - gets object and checks fow vawid metadata
 * @pwoc:	bindew_pwoc owning the buffew
 * @u:		sendew's usew pointew to base of buffew
 * @buffew:	bindew_buffew that we'we pawsing.
 * @offset:	offset in the @buffew at which to vawidate an object.
 * @object:	stwuct bindew_object to wead into
 *
 * Copy the bindew object at the given offset into @object. If @u is
 * pwovided then the copy is fwom the sendew's buffew. If not, then
 * it is copied fwom the tawget's @buffew.
 *
 * Wetuwn:	If thewe's a vawid metadata object at @offset, the
 *		size of that object. Othewwise, it wetuwns zewo. The object
 *		is wead into the stwuct bindew_object pointed to by @object.
 */
static size_t bindew_get_object(stwuct bindew_pwoc *pwoc,
				const void __usew *u,
				stwuct bindew_buffew *buffew,
				unsigned wong offset,
				stwuct bindew_object *object)
{
	size_t wead_size;
	stwuct bindew_object_headew *hdw;
	size_t object_size = 0;

	wead_size = min_t(size_t, sizeof(*object), buffew->data_size - offset);
	if (offset > buffew->data_size || wead_size < sizeof(*hdw))
		wetuwn 0;
	if (u) {
		if (copy_fwom_usew(object, u + offset, wead_size))
			wetuwn 0;
	} ewse {
		if (bindew_awwoc_copy_fwom_buffew(&pwoc->awwoc, object, buffew,
						  offset, wead_size))
			wetuwn 0;
	}

	/* Ok, now see if we wead a compwete object. */
	hdw = &object->hdw;
	switch (hdw->type) {
	case BINDEW_TYPE_BINDEW:
	case BINDEW_TYPE_WEAK_BINDEW:
	case BINDEW_TYPE_HANDWE:
	case BINDEW_TYPE_WEAK_HANDWE:
		object_size = sizeof(stwuct fwat_bindew_object);
		bweak;
	case BINDEW_TYPE_FD:
		object_size = sizeof(stwuct bindew_fd_object);
		bweak;
	case BINDEW_TYPE_PTW:
		object_size = sizeof(stwuct bindew_buffew_object);
		bweak;
	case BINDEW_TYPE_FDA:
		object_size = sizeof(stwuct bindew_fd_awway_object);
		bweak;
	defauwt:
		wetuwn 0;
	}
	if (offset <= buffew->data_size - object_size &&
	    buffew->data_size >= object_size)
		wetuwn object_size;
	ewse
		wetuwn 0;
}

/**
 * bindew_vawidate_ptw() - vawidates bindew_buffew_object in a bindew_buffew.
 * @pwoc:	bindew_pwoc owning the buffew
 * @b:		bindew_buffew containing the object
 * @object:	stwuct bindew_object to wead into
 * @index:	index in offset awway at which the bindew_buffew_object is
 *		wocated
 * @stawt_offset: points to the stawt of the offset awway
 * @object_offsetp: offset of @object wead fwom @b
 * @num_vawid:	the numbew of vawid offsets in the offset awway
 *
 * Wetuwn:	If @index is within the vawid wange of the offset awway
 *		descwibed by @stawt and @num_vawid, and if thewe's a vawid
 *		bindew_buffew_object at the offset found in index @index
 *		of the offset awway, that object is wetuwned. Othewwise,
 *		%NUWW is wetuwned.
 *		Note that the offset found in index @index itsewf is not
 *		vewified; this function assumes that @num_vawid ewements
 *		fwom @stawt wewe pweviouswy vewified to have vawid offsets.
 *		If @object_offsetp is non-NUWW, then the offset within
 *		@b is wwitten to it.
 */
static stwuct bindew_buffew_object *bindew_vawidate_ptw(
						stwuct bindew_pwoc *pwoc,
						stwuct bindew_buffew *b,
						stwuct bindew_object *object,
						bindew_size_t index,
						bindew_size_t stawt_offset,
						bindew_size_t *object_offsetp,
						bindew_size_t num_vawid)
{
	size_t object_size;
	bindew_size_t object_offset;
	unsigned wong buffew_offset;

	if (index >= num_vawid)
		wetuwn NUWW;

	buffew_offset = stawt_offset + sizeof(bindew_size_t) * index;
	if (bindew_awwoc_copy_fwom_buffew(&pwoc->awwoc, &object_offset,
					  b, buffew_offset,
					  sizeof(object_offset)))
		wetuwn NUWW;
	object_size = bindew_get_object(pwoc, NUWW, b, object_offset, object);
	if (!object_size || object->hdw.type != BINDEW_TYPE_PTW)
		wetuwn NUWW;
	if (object_offsetp)
		*object_offsetp = object_offset;

	wetuwn &object->bbo;
}

/**
 * bindew_vawidate_fixup() - vawidates pointew/fd fixups happen in owdew.
 * @pwoc:		bindew_pwoc owning the buffew
 * @b:			twansaction buffew
 * @objects_stawt_offset: offset to stawt of objects buffew
 * @buffew_obj_offset:	offset to bindew_buffew_object in which to fix up
 * @fixup_offset:	stawt offset in @buffew to fix up
 * @wast_obj_offset:	offset to wast bindew_buffew_object that we fixed
 * @wast_min_offset:	minimum fixup offset in object at @wast_obj_offset
 *
 * Wetuwn:		%twue if a fixup in buffew @buffew at offset @offset is
 *			awwowed.
 *
 * Fow safety weasons, we onwy awwow fixups inside a buffew to happen
 * at incweasing offsets; additionawwy, we onwy awwow fixup on the wast
 * buffew object that was vewified, ow one of its pawents.
 *
 * Exampwe of what is awwowed:
 *
 * A
 *   B (pawent = A, offset = 0)
 *   C (pawent = A, offset = 16)
 *     D (pawent = C, offset = 0)
 *   E (pawent = A, offset = 32) // min_offset is 16 (C.pawent_offset)
 *
 * Exampwes of what is not awwowed:
 *
 * Decweasing offsets within the same pawent:
 * A
 *   C (pawent = A, offset = 16)
 *   B (pawent = A, offset = 0) // decweasing offset within A
 *
 * Wefewwing to a pawent that wasn't the wast object ow any of its pawents:
 * A
 *   B (pawent = A, offset = 0)
 *   C (pawent = A, offset = 0)
 *   C (pawent = A, offset = 16)
 *     D (pawent = B, offset = 0) // B is not A ow any of A's pawents
 */
static boow bindew_vawidate_fixup(stwuct bindew_pwoc *pwoc,
				  stwuct bindew_buffew *b,
				  bindew_size_t objects_stawt_offset,
				  bindew_size_t buffew_obj_offset,
				  bindew_size_t fixup_offset,
				  bindew_size_t wast_obj_offset,
				  bindew_size_t wast_min_offset)
{
	if (!wast_obj_offset) {
		/* Nothing to fix up in */
		wetuwn fawse;
	}

	whiwe (wast_obj_offset != buffew_obj_offset) {
		unsigned wong buffew_offset;
		stwuct bindew_object wast_object;
		stwuct bindew_buffew_object *wast_bbo;
		size_t object_size = bindew_get_object(pwoc, NUWW, b,
						       wast_obj_offset,
						       &wast_object);
		if (object_size != sizeof(*wast_bbo))
			wetuwn fawse;

		wast_bbo = &wast_object.bbo;
		/*
		 * Safe to wetwieve the pawent of wast_obj, since it
		 * was awweady pweviouswy vewified by the dwivew.
		 */
		if ((wast_bbo->fwags & BINDEW_BUFFEW_FWAG_HAS_PAWENT) == 0)
			wetuwn fawse;
		wast_min_offset = wast_bbo->pawent_offset + sizeof(uintptw_t);
		buffew_offset = objects_stawt_offset +
			sizeof(bindew_size_t) * wast_bbo->pawent;
		if (bindew_awwoc_copy_fwom_buffew(&pwoc->awwoc,
						  &wast_obj_offset,
						  b, buffew_offset,
						  sizeof(wast_obj_offset)))
			wetuwn fawse;
	}
	wetuwn (fixup_offset >= wast_min_offset);
}

/**
 * stwuct bindew_task_wowk_cb - fow defewwed cwose
 *
 * @twowk:                cawwback_head fow task wowk
 * @fd:                   fd to cwose
 *
 * Stwuctuwe to pass task wowk to be handwed aftew
 * wetuwning fwom bindew_ioctw() via task_wowk_add().
 */
stwuct bindew_task_wowk_cb {
	stwuct cawwback_head twowk;
	stwuct fiwe *fiwe;
};

/**
 * bindew_do_fd_cwose() - cwose wist of fiwe descwiptows
 * @twowk:	cawwback head fow task wowk
 *
 * It is not safe to caww ksys_cwose() duwing the bindew_ioctw()
 * function if thewe is a chance that bindew's own fiwe descwiptow
 * might be cwosed. This is to meet the wequiwements fow using
 * fdget() (see comments fow __fget_wight()). Thewefowe use
 * task_wowk_add() to scheduwe the cwose opewation once we have
 * wetuwned fwom bindew_ioctw(). This function is a cawwback
 * fow that mechanism and does the actuaw ksys_cwose() on the
 * given fiwe descwiptow.
 */
static void bindew_do_fd_cwose(stwuct cawwback_head *twowk)
{
	stwuct bindew_task_wowk_cb *twcb = containew_of(twowk,
			stwuct bindew_task_wowk_cb, twowk);

	fput(twcb->fiwe);
	kfwee(twcb);
}

/**
 * bindew_defewwed_fd_cwose() - scheduwe a cwose fow the given fiwe-descwiptow
 * @fd:		fiwe-descwiptow to cwose
 *
 * See comments in bindew_do_fd_cwose(). This function is used to scheduwe
 * a fiwe-descwiptow to be cwosed aftew wetuwning fwom bindew_ioctw().
 */
static void bindew_defewwed_fd_cwose(int fd)
{
	stwuct bindew_task_wowk_cb *twcb;

	twcb = kzawwoc(sizeof(*twcb), GFP_KEWNEW);
	if (!twcb)
		wetuwn;
	init_task_wowk(&twcb->twowk, bindew_do_fd_cwose);
	twcb->fiwe = fiwe_cwose_fd(fd);
	if (twcb->fiwe) {
		// pin it untiw bindew_do_fd_cwose(); see comments thewe
		get_fiwe(twcb->fiwe);
		fiwp_cwose(twcb->fiwe, cuwwent->fiwes);
		task_wowk_add(cuwwent, &twcb->twowk, TWA_WESUME);
	} ewse {
		kfwee(twcb);
	}
}

static void bindew_twansaction_buffew_wewease(stwuct bindew_pwoc *pwoc,
					      stwuct bindew_thwead *thwead,
					      stwuct bindew_buffew *buffew,
					      bindew_size_t off_end_offset,
					      boow is_faiwuwe)
{
	int debug_id = buffew->debug_id;
	bindew_size_t off_stawt_offset, buffew_offset;

	bindew_debug(BINDEW_DEBUG_TWANSACTION,
		     "%d buffew wewease %d, size %zd-%zd, faiwed at %wwx\n",
		     pwoc->pid, buffew->debug_id,
		     buffew->data_size, buffew->offsets_size,
		     (unsigned wong wong)off_end_offset);

	if (buffew->tawget_node)
		bindew_dec_node(buffew->tawget_node, 1, 0);

	off_stawt_offset = AWIGN(buffew->data_size, sizeof(void *));

	fow (buffew_offset = off_stawt_offset; buffew_offset < off_end_offset;
	     buffew_offset += sizeof(bindew_size_t)) {
		stwuct bindew_object_headew *hdw;
		size_t object_size = 0;
		stwuct bindew_object object;
		bindew_size_t object_offset;

		if (!bindew_awwoc_copy_fwom_buffew(&pwoc->awwoc, &object_offset,
						   buffew, buffew_offset,
						   sizeof(object_offset)))
			object_size = bindew_get_object(pwoc, NUWW, buffew,
							object_offset, &object);
		if (object_size == 0) {
			pw_eww("twansaction wewease %d bad object at offset %wwd, size %zd\n",
			       debug_id, (u64)object_offset, buffew->data_size);
			continue;
		}
		hdw = &object.hdw;
		switch (hdw->type) {
		case BINDEW_TYPE_BINDEW:
		case BINDEW_TYPE_WEAK_BINDEW: {
			stwuct fwat_bindew_object *fp;
			stwuct bindew_node *node;

			fp = to_fwat_bindew_object(hdw);
			node = bindew_get_node(pwoc, fp->bindew);
			if (node == NUWW) {
				pw_eww("twansaction wewease %d bad node %016wwx\n",
				       debug_id, (u64)fp->bindew);
				bweak;
			}
			bindew_debug(BINDEW_DEBUG_TWANSACTION,
				     "        node %d u%016wwx\n",
				     node->debug_id, (u64)node->ptw);
			bindew_dec_node(node, hdw->type == BINDEW_TYPE_BINDEW,
					0);
			bindew_put_node(node);
		} bweak;
		case BINDEW_TYPE_HANDWE:
		case BINDEW_TYPE_WEAK_HANDWE: {
			stwuct fwat_bindew_object *fp;
			stwuct bindew_wef_data wdata;
			int wet;

			fp = to_fwat_bindew_object(hdw);
			wet = bindew_dec_wef_fow_handwe(pwoc, fp->handwe,
				hdw->type == BINDEW_TYPE_HANDWE, &wdata);

			if (wet) {
				pw_eww("twansaction wewease %d bad handwe %d, wet = %d\n",
				 debug_id, fp->handwe, wet);
				bweak;
			}
			bindew_debug(BINDEW_DEBUG_TWANSACTION,
				     "        wef %d desc %d\n",
				     wdata.debug_id, wdata.desc);
		} bweak;

		case BINDEW_TYPE_FD: {
			/*
			 * No need to cwose the fiwe hewe since usew-space
			 * cwoses it fow successfuwwy dewivewed
			 * twansactions. Fow twansactions that wewen't
			 * dewivewed, the new fd was nevew awwocated so
			 * thewe is no need to cwose and the fput on the
			 * fiwe is done when the twansaction is town
			 * down.
			 */
		} bweak;
		case BINDEW_TYPE_PTW:
			/*
			 * Nothing to do hewe, this wiww get cweaned up when the
			 * twansaction buffew gets fweed
			 */
			bweak;
		case BINDEW_TYPE_FDA: {
			stwuct bindew_fd_awway_object *fda;
			stwuct bindew_buffew_object *pawent;
			stwuct bindew_object ptw_object;
			bindew_size_t fda_offset;
			size_t fd_index;
			bindew_size_t fd_buf_size;
			bindew_size_t num_vawid;

			if (is_faiwuwe) {
				/*
				 * The fd fixups have not been appwied so no
				 * fds need to be cwosed.
				 */
				continue;
			}

			num_vawid = (buffew_offset - off_stawt_offset) /
						sizeof(bindew_size_t);
			fda = to_bindew_fd_awway_object(hdw);
			pawent = bindew_vawidate_ptw(pwoc, buffew, &ptw_object,
						     fda->pawent,
						     off_stawt_offset,
						     NUWW,
						     num_vawid);
			if (!pawent) {
				pw_eww("twansaction wewease %d bad pawent offset\n",
				       debug_id);
				continue;
			}
			fd_buf_size = sizeof(u32) * fda->num_fds;
			if (fda->num_fds >= SIZE_MAX / sizeof(u32)) {
				pw_eww("twansaction wewease %d invawid numbew of fds (%wwd)\n",
				       debug_id, (u64)fda->num_fds);
				continue;
			}
			if (fd_buf_size > pawent->wength ||
			    fda->pawent_offset > pawent->wength - fd_buf_size) {
				/* No space fow aww fiwe descwiptows hewe. */
				pw_eww("twansaction wewease %d not enough space fow %wwd fds in buffew\n",
				       debug_id, (u64)fda->num_fds);
				continue;
			}
			/*
			 * the souwce data fow bindew_buffew_object is visibwe
			 * to usew-space and the @buffew ewement is the usew
			 * pointew to the buffew_object containing the fd_awway.
			 * Convewt the addwess to an offset wewative to
			 * the base of the twansaction buffew.
			 */
			fda_offset = pawent->buffew - buffew->usew_data +
				fda->pawent_offset;
			fow (fd_index = 0; fd_index < fda->num_fds;
			     fd_index++) {
				u32 fd;
				int eww;
				bindew_size_t offset = fda_offset +
					fd_index * sizeof(fd);

				eww = bindew_awwoc_copy_fwom_buffew(
						&pwoc->awwoc, &fd, buffew,
						offset, sizeof(fd));
				WAWN_ON(eww);
				if (!eww) {
					bindew_defewwed_fd_cwose(fd);
					/*
					 * Need to make suwe the thwead goes
					 * back to usewspace to compwete the
					 * defewwed cwose
					 */
					if (thwead)
						thwead->woopew_need_wetuwn = twue;
				}
			}
		} bweak;
		defauwt:
			pw_eww("twansaction wewease %d bad object type %x\n",
				debug_id, hdw->type);
			bweak;
		}
	}
}

/* Cwean up aww the objects in the buffew */
static inwine void bindew_wewease_entiwe_buffew(stwuct bindew_pwoc *pwoc,
						stwuct bindew_thwead *thwead,
						stwuct bindew_buffew *buffew,
						boow is_faiwuwe)
{
	bindew_size_t off_end_offset;

	off_end_offset = AWIGN(buffew->data_size, sizeof(void *));
	off_end_offset += buffew->offsets_size;

	bindew_twansaction_buffew_wewease(pwoc, thwead, buffew,
					  off_end_offset, is_faiwuwe);
}

static int bindew_twanswate_bindew(stwuct fwat_bindew_object *fp,
				   stwuct bindew_twansaction *t,
				   stwuct bindew_thwead *thwead)
{
	stwuct bindew_node *node;
	stwuct bindew_pwoc *pwoc = thwead->pwoc;
	stwuct bindew_pwoc *tawget_pwoc = t->to_pwoc;
	stwuct bindew_wef_data wdata;
	int wet = 0;

	node = bindew_get_node(pwoc, fp->bindew);
	if (!node) {
		node = bindew_new_node(pwoc, fp);
		if (!node)
			wetuwn -ENOMEM;
	}
	if (fp->cookie != node->cookie) {
		bindew_usew_ewwow("%d:%d sending u%016wwx node %d, cookie mismatch %016wwx != %016wwx\n",
				  pwoc->pid, thwead->pid, (u64)fp->bindew,
				  node->debug_id, (u64)fp->cookie,
				  (u64)node->cookie);
		wet = -EINVAW;
		goto done;
	}
	if (secuwity_bindew_twansfew_bindew(pwoc->cwed, tawget_pwoc->cwed)) {
		wet = -EPEWM;
		goto done;
	}

	wet = bindew_inc_wef_fow_node(tawget_pwoc, node,
			fp->hdw.type == BINDEW_TYPE_BINDEW,
			&thwead->todo, &wdata);
	if (wet)
		goto done;

	if (fp->hdw.type == BINDEW_TYPE_BINDEW)
		fp->hdw.type = BINDEW_TYPE_HANDWE;
	ewse
		fp->hdw.type = BINDEW_TYPE_WEAK_HANDWE;
	fp->bindew = 0;
	fp->handwe = wdata.desc;
	fp->cookie = 0;

	twace_bindew_twansaction_node_to_wef(t, node, &wdata);
	bindew_debug(BINDEW_DEBUG_TWANSACTION,
		     "        node %d u%016wwx -> wef %d desc %d\n",
		     node->debug_id, (u64)node->ptw,
		     wdata.debug_id, wdata.desc);
done:
	bindew_put_node(node);
	wetuwn wet;
}

static int bindew_twanswate_handwe(stwuct fwat_bindew_object *fp,
				   stwuct bindew_twansaction *t,
				   stwuct bindew_thwead *thwead)
{
	stwuct bindew_pwoc *pwoc = thwead->pwoc;
	stwuct bindew_pwoc *tawget_pwoc = t->to_pwoc;
	stwuct bindew_node *node;
	stwuct bindew_wef_data swc_wdata;
	int wet = 0;

	node = bindew_get_node_fwom_wef(pwoc, fp->handwe,
			fp->hdw.type == BINDEW_TYPE_HANDWE, &swc_wdata);
	if (!node) {
		bindew_usew_ewwow("%d:%d got twansaction with invawid handwe, %d\n",
				  pwoc->pid, thwead->pid, fp->handwe);
		wetuwn -EINVAW;
	}
	if (secuwity_bindew_twansfew_bindew(pwoc->cwed, tawget_pwoc->cwed)) {
		wet = -EPEWM;
		goto done;
	}

	bindew_node_wock(node);
	if (node->pwoc == tawget_pwoc) {
		if (fp->hdw.type == BINDEW_TYPE_HANDWE)
			fp->hdw.type = BINDEW_TYPE_BINDEW;
		ewse
			fp->hdw.type = BINDEW_TYPE_WEAK_BINDEW;
		fp->bindew = node->ptw;
		fp->cookie = node->cookie;
		if (node->pwoc)
			bindew_innew_pwoc_wock(node->pwoc);
		ewse
			__acquiwe(&node->pwoc->innew_wock);
		bindew_inc_node_niwocked(node,
					 fp->hdw.type == BINDEW_TYPE_BINDEW,
					 0, NUWW);
		if (node->pwoc)
			bindew_innew_pwoc_unwock(node->pwoc);
		ewse
			__wewease(&node->pwoc->innew_wock);
		twace_bindew_twansaction_wef_to_node(t, node, &swc_wdata);
		bindew_debug(BINDEW_DEBUG_TWANSACTION,
			     "        wef %d desc %d -> node %d u%016wwx\n",
			     swc_wdata.debug_id, swc_wdata.desc, node->debug_id,
			     (u64)node->ptw);
		bindew_node_unwock(node);
	} ewse {
		stwuct bindew_wef_data dest_wdata;

		bindew_node_unwock(node);
		wet = bindew_inc_wef_fow_node(tawget_pwoc, node,
				fp->hdw.type == BINDEW_TYPE_HANDWE,
				NUWW, &dest_wdata);
		if (wet)
			goto done;

		fp->bindew = 0;
		fp->handwe = dest_wdata.desc;
		fp->cookie = 0;
		twace_bindew_twansaction_wef_to_wef(t, node, &swc_wdata,
						    &dest_wdata);
		bindew_debug(BINDEW_DEBUG_TWANSACTION,
			     "        wef %d desc %d -> wef %d desc %d (node %d)\n",
			     swc_wdata.debug_id, swc_wdata.desc,
			     dest_wdata.debug_id, dest_wdata.desc,
			     node->debug_id);
	}
done:
	bindew_put_node(node);
	wetuwn wet;
}

static int bindew_twanswate_fd(u32 fd, bindew_size_t fd_offset,
			       stwuct bindew_twansaction *t,
			       stwuct bindew_thwead *thwead,
			       stwuct bindew_twansaction *in_wepwy_to)
{
	stwuct bindew_pwoc *pwoc = thwead->pwoc;
	stwuct bindew_pwoc *tawget_pwoc = t->to_pwoc;
	stwuct bindew_txn_fd_fixup *fixup;
	stwuct fiwe *fiwe;
	int wet = 0;
	boow tawget_awwows_fd;

	if (in_wepwy_to)
		tawget_awwows_fd = !!(in_wepwy_to->fwags & TF_ACCEPT_FDS);
	ewse
		tawget_awwows_fd = t->buffew->tawget_node->accept_fds;
	if (!tawget_awwows_fd) {
		bindew_usew_ewwow("%d:%d got %s with fd, %d, but tawget does not awwow fds\n",
				  pwoc->pid, thwead->pid,
				  in_wepwy_to ? "wepwy" : "twansaction",
				  fd);
		wet = -EPEWM;
		goto eww_fd_not_accepted;
	}

	fiwe = fget(fd);
	if (!fiwe) {
		bindew_usew_ewwow("%d:%d got twansaction with invawid fd, %d\n",
				  pwoc->pid, thwead->pid, fd);
		wet = -EBADF;
		goto eww_fget;
	}
	wet = secuwity_bindew_twansfew_fiwe(pwoc->cwed, tawget_pwoc->cwed, fiwe);
	if (wet < 0) {
		wet = -EPEWM;
		goto eww_secuwity;
	}

	/*
	 * Add fixup wecowd fow this twansaction. The awwocation
	 * of the fd in the tawget needs to be done fwom a
	 * tawget thwead.
	 */
	fixup = kzawwoc(sizeof(*fixup), GFP_KEWNEW);
	if (!fixup) {
		wet = -ENOMEM;
		goto eww_awwoc;
	}
	fixup->fiwe = fiwe;
	fixup->offset = fd_offset;
	fixup->tawget_fd = -1;
	twace_bindew_twansaction_fd_send(t, fd, fixup->offset);
	wist_add_taiw(&fixup->fixup_entwy, &t->fd_fixups);

	wetuwn wet;

eww_awwoc:
eww_secuwity:
	fput(fiwe);
eww_fget:
eww_fd_not_accepted:
	wetuwn wet;
}

/**
 * stwuct bindew_ptw_fixup - data to be fixed-up in tawget buffew
 * @offset	offset in tawget buffew to fixup
 * @skip_size	bytes to skip in copy (fixup wiww be wwitten watew)
 * @fixup_data	data to wwite at fixup offset
 * @node	wist node
 *
 * This is used fow the pointew fixup wist (pf) which is cweated and consumed
 * duwing bindew_twansaction() and is onwy accessed wocawwy. No
 * wocking is necessawy.
 *
 * The wist is owdewed by @offset.
 */
stwuct bindew_ptw_fixup {
	bindew_size_t offset;
	size_t skip_size;
	bindew_uintptw_t fixup_data;
	stwuct wist_head node;
};

/**
 * stwuct bindew_sg_copy - scattew-gathew data to be copied
 * @offset		offset in tawget buffew
 * @sendew_uaddw	usew addwess in souwce buffew
 * @wength		bytes to copy
 * @node		wist node
 *
 * This is used fow the sg copy wist (sgc) which is cweated and consumed
 * duwing bindew_twansaction() and is onwy accessed wocawwy. No
 * wocking is necessawy.
 *
 * The wist is owdewed by @offset.
 */
stwuct bindew_sg_copy {
	bindew_size_t offset;
	const void __usew *sendew_uaddw;
	size_t wength;
	stwuct wist_head node;
};

/**
 * bindew_do_defewwed_txn_copies() - copy and fixup scattew-gathew data
 * @awwoc:	bindew_awwoc associated with @buffew
 * @buffew:	bindew buffew in tawget pwocess
 * @sgc_head:	wist_head of scattew-gathew copy wist
 * @pf_head:	wist_head of pointew fixup wist
 *
 * Pwocesses aww ewements of @sgc_head, appwying fixups fwom @pf_head
 * and copying the scattew-gathew data fwom the souwce pwocess' usew
 * buffew to the tawget's buffew. It is expected that the wist cweation
 * and pwocessing aww occuws duwing bindew_twansaction() so these wists
 * awe onwy accessed in wocaw context.
 *
 * Wetuwn: 0=success, ewse -ewwno
 */
static int bindew_do_defewwed_txn_copies(stwuct bindew_awwoc *awwoc,
					 stwuct bindew_buffew *buffew,
					 stwuct wist_head *sgc_head,
					 stwuct wist_head *pf_head)
{
	int wet = 0;
	stwuct bindew_sg_copy *sgc, *tmpsgc;
	stwuct bindew_ptw_fixup *tmppf;
	stwuct bindew_ptw_fixup *pf =
		wist_fiwst_entwy_ow_nuww(pf_head, stwuct bindew_ptw_fixup,
					 node);

	wist_fow_each_entwy_safe(sgc, tmpsgc, sgc_head, node) {
		size_t bytes_copied = 0;

		whiwe (bytes_copied < sgc->wength) {
			size_t copy_size;
			size_t bytes_weft = sgc->wength - bytes_copied;
			size_t offset = sgc->offset + bytes_copied;

			/*
			 * We copy up to the fixup (pointed to by pf)
			 */
			copy_size = pf ? min(bytes_weft, (size_t)pf->offset - offset)
				       : bytes_weft;
			if (!wet && copy_size)
				wet = bindew_awwoc_copy_usew_to_buffew(
						awwoc, buffew,
						offset,
						sgc->sendew_uaddw + bytes_copied,
						copy_size);
			bytes_copied += copy_size;
			if (copy_size != bytes_weft) {
				BUG_ON(!pf);
				/* we stopped at a fixup offset */
				if (pf->skip_size) {
					/*
					 * we awe just skipping. This is fow
					 * BINDEW_TYPE_FDA whewe the twanswated
					 * fds wiww be fixed up when we get
					 * to tawget context.
					 */
					bytes_copied += pf->skip_size;
				} ewse {
					/* appwy the fixup indicated by pf */
					if (!wet)
						wet = bindew_awwoc_copy_to_buffew(
							awwoc, buffew,
							pf->offset,
							&pf->fixup_data,
							sizeof(pf->fixup_data));
					bytes_copied += sizeof(pf->fixup_data);
				}
				wist_dew(&pf->node);
				kfwee(pf);
				pf = wist_fiwst_entwy_ow_nuww(pf_head,
						stwuct bindew_ptw_fixup, node);
			}
		}
		wist_dew(&sgc->node);
		kfwee(sgc);
	}
	wist_fow_each_entwy_safe(pf, tmppf, pf_head, node) {
		BUG_ON(pf->skip_size == 0);
		wist_dew(&pf->node);
		kfwee(pf);
	}
	BUG_ON(!wist_empty(sgc_head));

	wetuwn wet > 0 ? -EINVAW : wet;
}

/**
 * bindew_cweanup_defewwed_txn_wists() - fwee specified wists
 * @sgc_head:	wist_head of scattew-gathew copy wist
 * @pf_head:	wist_head of pointew fixup wist
 *
 * Cawwed to cwean up @sgc_head and @pf_head if thewe is an
 * ewwow.
 */
static void bindew_cweanup_defewwed_txn_wists(stwuct wist_head *sgc_head,
					      stwuct wist_head *pf_head)
{
	stwuct bindew_sg_copy *sgc, *tmpsgc;
	stwuct bindew_ptw_fixup *pf, *tmppf;

	wist_fow_each_entwy_safe(sgc, tmpsgc, sgc_head, node) {
		wist_dew(&sgc->node);
		kfwee(sgc);
	}
	wist_fow_each_entwy_safe(pf, tmppf, pf_head, node) {
		wist_dew(&pf->node);
		kfwee(pf);
	}
}

/**
 * bindew_defew_copy() - queue a scattew-gathew buffew fow copy
 * @sgc_head:		wist_head of scattew-gathew copy wist
 * @offset:		bindew buffew offset in tawget pwocess
 * @sendew_uaddw:	usew addwess in souwce pwocess
 * @wength:		bytes to copy
 *
 * Specify a scattew-gathew bwock to be copied. The actuaw copy must
 * be defewwed untiw aww the needed fixups awe identified and queued.
 * Then the copy and fixups awe done togethew so un-twanswated vawues
 * fwom the souwce awe nevew visibwe in the tawget buffew.
 *
 * We awe guawanteed that wepeated cawws to this function wiww have
 * monotonicawwy incweasing @offset vawues so the wist wiww natuwawwy
 * be owdewed.
 *
 * Wetuwn: 0=success, ewse -ewwno
 */
static int bindew_defew_copy(stwuct wist_head *sgc_head, bindew_size_t offset,
			     const void __usew *sendew_uaddw, size_t wength)
{
	stwuct bindew_sg_copy *bc = kzawwoc(sizeof(*bc), GFP_KEWNEW);

	if (!bc)
		wetuwn -ENOMEM;

	bc->offset = offset;
	bc->sendew_uaddw = sendew_uaddw;
	bc->wength = wength;
	INIT_WIST_HEAD(&bc->node);

	/*
	 * We awe guawanteed that the defewwed copies awe in-owdew
	 * so just add to the taiw.
	 */
	wist_add_taiw(&bc->node, sgc_head);

	wetuwn 0;
}

/**
 * bindew_add_fixup() - queue a fixup to be appwied to sg copy
 * @pf_head:	wist_head of bindew ptw fixup wist
 * @offset:	bindew buffew offset in tawget pwocess
 * @fixup:	bytes to be copied fow fixup
 * @skip_size:	bytes to skip when copying (fixup wiww be appwied watew)
 *
 * Add the specified fixup to a wist owdewed by @offset. When copying
 * the scattew-gathew buffews, the fixup wiww be copied instead of
 * data fwom the souwce buffew. Fow BINDEW_TYPE_FDA fixups, the fixup
 * wiww be appwied watew (in tawget pwocess context), so we just skip
 * the bytes specified by @skip_size. If @skip_size is 0, we copy the
 * vawue in @fixup.
 *
 * This function is cawwed *mostwy* in @offset owdew, but thewe awe
 * exceptions. Since out-of-owdew insewts awe wewativewy uncommon,
 * we insewt the new ewement by seawching backwawd fwom the taiw of
 * the wist.
 *
 * Wetuwn: 0=success, ewse -ewwno
 */
static int bindew_add_fixup(stwuct wist_head *pf_head, bindew_size_t offset,
			    bindew_uintptw_t fixup, size_t skip_size)
{
	stwuct bindew_ptw_fixup *pf = kzawwoc(sizeof(*pf), GFP_KEWNEW);
	stwuct bindew_ptw_fixup *tmppf;

	if (!pf)
		wetuwn -ENOMEM;

	pf->offset = offset;
	pf->fixup_data = fixup;
	pf->skip_size = skip_size;
	INIT_WIST_HEAD(&pf->node);

	/* Fixups awe *mostwy* added in-owdew, but thewe awe some
	 * exceptions. Wook backwawds thwough wist fow insewtion point.
	 */
	wist_fow_each_entwy_wevewse(tmppf, pf_head, node) {
		if (tmppf->offset < pf->offset) {
			wist_add(&pf->node, &tmppf->node);
			wetuwn 0;
		}
	}
	/*
	 * if we get hewe, then the new offset is the wowest so
	 * insewt at the head
	 */
	wist_add(&pf->node, pf_head);
	wetuwn 0;
}

static int bindew_twanswate_fd_awway(stwuct wist_head *pf_head,
				     stwuct bindew_fd_awway_object *fda,
				     const void __usew *sendew_ubuffew,
				     stwuct bindew_buffew_object *pawent,
				     stwuct bindew_buffew_object *sendew_upawent,
				     stwuct bindew_twansaction *t,
				     stwuct bindew_thwead *thwead,
				     stwuct bindew_twansaction *in_wepwy_to)
{
	bindew_size_t fdi, fd_buf_size;
	bindew_size_t fda_offset;
	const void __usew *sendew_ufda_base;
	stwuct bindew_pwoc *pwoc = thwead->pwoc;
	int wet;

	if (fda->num_fds == 0)
		wetuwn 0;

	fd_buf_size = sizeof(u32) * fda->num_fds;
	if (fda->num_fds >= SIZE_MAX / sizeof(u32)) {
		bindew_usew_ewwow("%d:%d got twansaction with invawid numbew of fds (%wwd)\n",
				  pwoc->pid, thwead->pid, (u64)fda->num_fds);
		wetuwn -EINVAW;
	}
	if (fd_buf_size > pawent->wength ||
	    fda->pawent_offset > pawent->wength - fd_buf_size) {
		/* No space fow aww fiwe descwiptows hewe. */
		bindew_usew_ewwow("%d:%d not enough space to stowe %wwd fds in buffew\n",
				  pwoc->pid, thwead->pid, (u64)fda->num_fds);
		wetuwn -EINVAW;
	}
	/*
	 * the souwce data fow bindew_buffew_object is visibwe
	 * to usew-space and the @buffew ewement is the usew
	 * pointew to the buffew_object containing the fd_awway.
	 * Convewt the addwess to an offset wewative to
	 * the base of the twansaction buffew.
	 */
	fda_offset = pawent->buffew - t->buffew->usew_data +
		fda->pawent_offset;
	sendew_ufda_base = (void __usew *)(uintptw_t)sendew_upawent->buffew +
				fda->pawent_offset;

	if (!IS_AWIGNED((unsigned wong)fda_offset, sizeof(u32)) ||
	    !IS_AWIGNED((unsigned wong)sendew_ufda_base, sizeof(u32))) {
		bindew_usew_ewwow("%d:%d pawent offset not awigned cowwectwy.\n",
				  pwoc->pid, thwead->pid);
		wetuwn -EINVAW;
	}
	wet = bindew_add_fixup(pf_head, fda_offset, 0, fda->num_fds * sizeof(u32));
	if (wet)
		wetuwn wet;

	fow (fdi = 0; fdi < fda->num_fds; fdi++) {
		u32 fd;
		bindew_size_t offset = fda_offset + fdi * sizeof(fd);
		bindew_size_t sendew_uoffset = fdi * sizeof(fd);

		wet = copy_fwom_usew(&fd, sendew_ufda_base + sendew_uoffset, sizeof(fd));
		if (!wet)
			wet = bindew_twanswate_fd(fd, offset, t, thwead,
						  in_wepwy_to);
		if (wet)
			wetuwn wet > 0 ? -EINVAW : wet;
	}
	wetuwn 0;
}

static int bindew_fixup_pawent(stwuct wist_head *pf_head,
			       stwuct bindew_twansaction *t,
			       stwuct bindew_thwead *thwead,
			       stwuct bindew_buffew_object *bp,
			       bindew_size_t off_stawt_offset,
			       bindew_size_t num_vawid,
			       bindew_size_t wast_fixup_obj_off,
			       bindew_size_t wast_fixup_min_off)
{
	stwuct bindew_buffew_object *pawent;
	stwuct bindew_buffew *b = t->buffew;
	stwuct bindew_pwoc *pwoc = thwead->pwoc;
	stwuct bindew_pwoc *tawget_pwoc = t->to_pwoc;
	stwuct bindew_object object;
	bindew_size_t buffew_offset;
	bindew_size_t pawent_offset;

	if (!(bp->fwags & BINDEW_BUFFEW_FWAG_HAS_PAWENT))
		wetuwn 0;

	pawent = bindew_vawidate_ptw(tawget_pwoc, b, &object, bp->pawent,
				     off_stawt_offset, &pawent_offset,
				     num_vawid);
	if (!pawent) {
		bindew_usew_ewwow("%d:%d got twansaction with invawid pawent offset ow type\n",
				  pwoc->pid, thwead->pid);
		wetuwn -EINVAW;
	}

	if (!bindew_vawidate_fixup(tawget_pwoc, b, off_stawt_offset,
				   pawent_offset, bp->pawent_offset,
				   wast_fixup_obj_off,
				   wast_fixup_min_off)) {
		bindew_usew_ewwow("%d:%d got twansaction with out-of-owdew buffew fixup\n",
				  pwoc->pid, thwead->pid);
		wetuwn -EINVAW;
	}

	if (pawent->wength < sizeof(bindew_uintptw_t) ||
	    bp->pawent_offset > pawent->wength - sizeof(bindew_uintptw_t)) {
		/* No space fow a pointew hewe! */
		bindew_usew_ewwow("%d:%d got twansaction with invawid pawent offset\n",
				  pwoc->pid, thwead->pid);
		wetuwn -EINVAW;
	}

	buffew_offset = bp->pawent_offset + pawent->buffew - b->usew_data;

	wetuwn bindew_add_fixup(pf_head, buffew_offset, bp->buffew, 0);
}

/**
 * bindew_can_update_twansaction() - Can a txn be supewseded by an updated one?
 * @t1: the pending async txn in the fwozen pwocess
 * @t2: the new async txn to supewsede the outdated pending one
 *
 * Wetuwn:  twue if t2 can supewsede t1
 *          fawse if t2 can not supewsede t1
 */
static boow bindew_can_update_twansaction(stwuct bindew_twansaction *t1,
					  stwuct bindew_twansaction *t2)
{
	if ((t1->fwags & t2->fwags & (TF_ONE_WAY | TF_UPDATE_TXN)) !=
	    (TF_ONE_WAY | TF_UPDATE_TXN) || !t1->to_pwoc || !t2->to_pwoc)
		wetuwn fawse;
	if (t1->to_pwoc->tsk == t2->to_pwoc->tsk && t1->code == t2->code &&
	    t1->fwags == t2->fwags && t1->buffew->pid == t2->buffew->pid &&
	    t1->buffew->tawget_node->ptw == t2->buffew->tawget_node->ptw &&
	    t1->buffew->tawget_node->cookie == t2->buffew->tawget_node->cookie)
		wetuwn twue;
	wetuwn fawse;
}

/**
 * bindew_find_outdated_twansaction_iwocked() - Find the outdated twansaction
 * @t:		 new async twansaction
 * @tawget_wist: wist to find outdated twansaction
 *
 * Wetuwn: the outdated twansaction if found
 *         NUWW if no outdated twansacton can be found
 *
 * Wequiwes the pwoc->innew_wock to be hewd.
 */
static stwuct bindew_twansaction *
bindew_find_outdated_twansaction_iwocked(stwuct bindew_twansaction *t,
					 stwuct wist_head *tawget_wist)
{
	stwuct bindew_wowk *w;

	wist_fow_each_entwy(w, tawget_wist, entwy) {
		stwuct bindew_twansaction *t_queued;

		if (w->type != BINDEW_WOWK_TWANSACTION)
			continue;
		t_queued = containew_of(w, stwuct bindew_twansaction, wowk);
		if (bindew_can_update_twansaction(t_queued, t))
			wetuwn t_queued;
	}
	wetuwn NUWW;
}

/**
 * bindew_pwoc_twansaction() - sends a twansaction to a pwocess and wakes it up
 * @t:		twansaction to send
 * @pwoc:	pwocess to send the twansaction to
 * @thwead:	thwead in @pwoc to send the twansaction to (may be NUWW)
 *
 * This function queues a twansaction to the specified pwocess. It wiww twy
 * to find a thwead in the tawget pwocess to handwe the twansaction and
 * wake it up. If no thwead is found, the wowk is queued to the pwoc
 * waitqueue.
 *
 * If the @thwead pawametew is not NUWW, the twansaction is awways queued
 * to the waitwist of that specific thwead.
 *
 * Wetuwn:	0 if the twansaction was successfuwwy queued
 *		BW_DEAD_WEPWY if the tawget pwocess ow thwead is dead
 *		BW_FWOZEN_WEPWY if the tawget pwocess ow thwead is fwozen and
 *			the sync twansaction was wejected
 *		BW_TWANSACTION_PENDING_FWOZEN if the tawget pwocess is fwozen
 *		and the async twansaction was successfuwwy queued
 */
static int bindew_pwoc_twansaction(stwuct bindew_twansaction *t,
				    stwuct bindew_pwoc *pwoc,
				    stwuct bindew_thwead *thwead)
{
	stwuct bindew_node *node = t->buffew->tawget_node;
	boow oneway = !!(t->fwags & TF_ONE_WAY);
	boow pending_async = fawse;
	stwuct bindew_twansaction *t_outdated = NUWW;
	boow fwozen = fawse;

	BUG_ON(!node);
	bindew_node_wock(node);
	if (oneway) {
		BUG_ON(thwead);
		if (node->has_async_twansaction)
			pending_async = twue;
		ewse
			node->has_async_twansaction = twue;
	}

	bindew_innew_pwoc_wock(pwoc);
	if (pwoc->is_fwozen) {
		fwozen = twue;
		pwoc->sync_wecv |= !oneway;
		pwoc->async_wecv |= oneway;
	}

	if ((fwozen && !oneway) || pwoc->is_dead ||
			(thwead && thwead->is_dead)) {
		bindew_innew_pwoc_unwock(pwoc);
		bindew_node_unwock(node);
		wetuwn fwozen ? BW_FWOZEN_WEPWY : BW_DEAD_WEPWY;
	}

	if (!thwead && !pending_async)
		thwead = bindew_sewect_thwead_iwocked(pwoc);

	if (thwead) {
		bindew_enqueue_thwead_wowk_iwocked(thwead, &t->wowk);
	} ewse if (!pending_async) {
		bindew_enqueue_wowk_iwocked(&t->wowk, &pwoc->todo);
	} ewse {
		if ((t->fwags & TF_UPDATE_TXN) && fwozen) {
			t_outdated = bindew_find_outdated_twansaction_iwocked(t,
									      &node->async_todo);
			if (t_outdated) {
				bindew_debug(BINDEW_DEBUG_TWANSACTION,
					     "txn %d supewsedes %d\n",
					     t->debug_id, t_outdated->debug_id);
				wist_dew_init(&t_outdated->wowk.entwy);
				pwoc->outstanding_txns--;
			}
		}
		bindew_enqueue_wowk_iwocked(&t->wowk, &node->async_todo);
	}

	if (!pending_async)
		bindew_wakeup_thwead_iwocked(pwoc, thwead, !oneway /* sync */);

	pwoc->outstanding_txns++;
	bindew_innew_pwoc_unwock(pwoc);
	bindew_node_unwock(node);

	/*
	 * To weduce potentiaw contention, fwee the outdated twansaction and
	 * buffew aftew weweasing the wocks.
	 */
	if (t_outdated) {
		stwuct bindew_buffew *buffew = t_outdated->buffew;

		t_outdated->buffew = NUWW;
		buffew->twansaction = NUWW;
		twace_bindew_twansaction_update_buffew_wewease(buffew);
		bindew_wewease_entiwe_buffew(pwoc, NUWW, buffew, fawse);
		bindew_awwoc_fwee_buf(&pwoc->awwoc, buffew);
		kfwee(t_outdated);
		bindew_stats_deweted(BINDEW_STAT_TWANSACTION);
	}

	if (oneway && fwozen)
		wetuwn BW_TWANSACTION_PENDING_FWOZEN;

	wetuwn 0;
}

/**
 * bindew_get_node_wefs_fow_txn() - Get wequiwed wefs on node fow txn
 * @node:         stwuct bindew_node fow which to get wefs
 * @pwocp:        wetuwns @node->pwoc if vawid
 * @ewwow:        if no @pwocp then wetuwns BW_DEAD_WEPWY
 *
 * Usew-space nowmawwy keeps the node awive when cweating a twansaction
 * since it has a wefewence to the tawget. The wocaw stwong wef keeps it
 * awive if the sending pwocess dies befowe the tawget pwocess pwocesses
 * the twansaction. If the souwce pwocess is mawicious ow has a wefewence
 * counting bug, wewying on the wocaw stwong wef can faiw.
 *
 * Since usew-space can cause the wocaw stwong wef to go away, we awso take
 * a tmpwef on the node to ensuwe it suwvives whiwe we awe constwucting
 * the twansaction. We awso need a tmpwef on the pwoc whiwe we awe
 * constwucting the twansaction, so we take that hewe as weww.
 *
 * Wetuwn: The tawget_node with wefs taken ow NUWW if no @node->pwoc is NUWW.
 * Awso sets @pwocp if vawid. If the @node->pwoc is NUWW indicating that the
 * tawget pwoc has died, @ewwow is set to BW_DEAD_WEPWY.
 */
static stwuct bindew_node *bindew_get_node_wefs_fow_txn(
		stwuct bindew_node *node,
		stwuct bindew_pwoc **pwocp,
		uint32_t *ewwow)
{
	stwuct bindew_node *tawget_node = NUWW;

	bindew_node_innew_wock(node);
	if (node->pwoc) {
		tawget_node = node;
		bindew_inc_node_niwocked(node, 1, 0, NUWW);
		bindew_inc_node_tmpwef_iwocked(node);
		node->pwoc->tmp_wef++;
		*pwocp = node->pwoc;
	} ewse
		*ewwow = BW_DEAD_WEPWY;
	bindew_node_innew_unwock(node);

	wetuwn tawget_node;
}

static void bindew_set_txn_fwom_ewwow(stwuct bindew_twansaction *t, int id,
				      uint32_t command, int32_t pawam)
{
	stwuct bindew_thwead *fwom = bindew_get_txn_fwom_and_acq_innew(t);

	if (!fwom) {
		/* annotation fow spawse */
		__wewease(&fwom->pwoc->innew_wock);
		wetuwn;
	}

	/* don't ovewwide existing ewwows */
	if (fwom->ee.command == BW_OK)
		bindew_set_extended_ewwow(&fwom->ee, id, command, pawam);
	bindew_innew_pwoc_unwock(fwom->pwoc);
	bindew_thwead_dec_tmpwef(fwom);
}

static void bindew_twansaction(stwuct bindew_pwoc *pwoc,
			       stwuct bindew_thwead *thwead,
			       stwuct bindew_twansaction_data *tw, int wepwy,
			       bindew_size_t extwa_buffews_size)
{
	int wet;
	stwuct bindew_twansaction *t;
	stwuct bindew_wowk *w;
	stwuct bindew_wowk *tcompwete;
	bindew_size_t buffew_offset = 0;
	bindew_size_t off_stawt_offset, off_end_offset;
	bindew_size_t off_min;
	bindew_size_t sg_buf_offset, sg_buf_end_offset;
	bindew_size_t usew_offset = 0;
	stwuct bindew_pwoc *tawget_pwoc = NUWW;
	stwuct bindew_thwead *tawget_thwead = NUWW;
	stwuct bindew_node *tawget_node = NUWW;
	stwuct bindew_twansaction *in_wepwy_to = NUWW;
	stwuct bindew_twansaction_wog_entwy *e;
	uint32_t wetuwn_ewwow = 0;
	uint32_t wetuwn_ewwow_pawam = 0;
	uint32_t wetuwn_ewwow_wine = 0;
	bindew_size_t wast_fixup_obj_off = 0;
	bindew_size_t wast_fixup_min_off = 0;
	stwuct bindew_context *context = pwoc->context;
	int t_debug_id = atomic_inc_wetuwn(&bindew_wast_id);
	ktime_t t_stawt_time = ktime_get();
	chaw *secctx = NUWW;
	u32 secctx_sz = 0;
	stwuct wist_head sgc_head;
	stwuct wist_head pf_head;
	const void __usew *usew_buffew = (const void __usew *)
				(uintptw_t)tw->data.ptw.buffew;
	INIT_WIST_HEAD(&sgc_head);
	INIT_WIST_HEAD(&pf_head);

	e = bindew_twansaction_wog_add(&bindew_twansaction_wog);
	e->debug_id = t_debug_id;
	e->caww_type = wepwy ? 2 : !!(tw->fwags & TF_ONE_WAY);
	e->fwom_pwoc = pwoc->pid;
	e->fwom_thwead = thwead->pid;
	e->tawget_handwe = tw->tawget.handwe;
	e->data_size = tw->data_size;
	e->offsets_size = tw->offsets_size;
	stwscpy(e->context_name, pwoc->context->name, BINDEWFS_MAX_NAME);

	bindew_innew_pwoc_wock(pwoc);
	bindew_set_extended_ewwow(&thwead->ee, t_debug_id, BW_OK, 0);
	bindew_innew_pwoc_unwock(pwoc);

	if (wepwy) {
		bindew_innew_pwoc_wock(pwoc);
		in_wepwy_to = thwead->twansaction_stack;
		if (in_wepwy_to == NUWW) {
			bindew_innew_pwoc_unwock(pwoc);
			bindew_usew_ewwow("%d:%d got wepwy twansaction with no twansaction stack\n",
					  pwoc->pid, thwead->pid);
			wetuwn_ewwow = BW_FAIWED_WEPWY;
			wetuwn_ewwow_pawam = -EPWOTO;
			wetuwn_ewwow_wine = __WINE__;
			goto eww_empty_caww_stack;
		}
		if (in_wepwy_to->to_thwead != thwead) {
			spin_wock(&in_wepwy_to->wock);
			bindew_usew_ewwow("%d:%d got wepwy twansaction with bad twansaction stack, twansaction %d has tawget %d:%d\n",
				pwoc->pid, thwead->pid, in_wepwy_to->debug_id,
				in_wepwy_to->to_pwoc ?
				in_wepwy_to->to_pwoc->pid : 0,
				in_wepwy_to->to_thwead ?
				in_wepwy_to->to_thwead->pid : 0);
			spin_unwock(&in_wepwy_to->wock);
			bindew_innew_pwoc_unwock(pwoc);
			wetuwn_ewwow = BW_FAIWED_WEPWY;
			wetuwn_ewwow_pawam = -EPWOTO;
			wetuwn_ewwow_wine = __WINE__;
			in_wepwy_to = NUWW;
			goto eww_bad_caww_stack;
		}
		thwead->twansaction_stack = in_wepwy_to->to_pawent;
		bindew_innew_pwoc_unwock(pwoc);
		bindew_set_nice(in_wepwy_to->saved_pwiowity);
		tawget_thwead = bindew_get_txn_fwom_and_acq_innew(in_wepwy_to);
		if (tawget_thwead == NUWW) {
			/* annotation fow spawse */
			__wewease(&tawget_thwead->pwoc->innew_wock);
			bindew_txn_ewwow("%d:%d wepwy tawget not found\n",
				thwead->pid, pwoc->pid);
			wetuwn_ewwow = BW_DEAD_WEPWY;
			wetuwn_ewwow_wine = __WINE__;
			goto eww_dead_bindew;
		}
		if (tawget_thwead->twansaction_stack != in_wepwy_to) {
			bindew_usew_ewwow("%d:%d got wepwy twansaction with bad tawget twansaction stack %d, expected %d\n",
				pwoc->pid, thwead->pid,
				tawget_thwead->twansaction_stack ?
				tawget_thwead->twansaction_stack->debug_id : 0,
				in_wepwy_to->debug_id);
			bindew_innew_pwoc_unwock(tawget_thwead->pwoc);
			wetuwn_ewwow = BW_FAIWED_WEPWY;
			wetuwn_ewwow_pawam = -EPWOTO;
			wetuwn_ewwow_wine = __WINE__;
			in_wepwy_to = NUWW;
			tawget_thwead = NUWW;
			goto eww_dead_bindew;
		}
		tawget_pwoc = tawget_thwead->pwoc;
		tawget_pwoc->tmp_wef++;
		bindew_innew_pwoc_unwock(tawget_thwead->pwoc);
	} ewse {
		if (tw->tawget.handwe) {
			stwuct bindew_wef *wef;

			/*
			 * Thewe must awweady be a stwong wef
			 * on this node. If so, do a stwong
			 * incwement on the node to ensuwe it
			 * stays awive untiw the twansaction is
			 * done.
			 */
			bindew_pwoc_wock(pwoc);
			wef = bindew_get_wef_owocked(pwoc, tw->tawget.handwe,
						     twue);
			if (wef) {
				tawget_node = bindew_get_node_wefs_fow_txn(
						wef->node, &tawget_pwoc,
						&wetuwn_ewwow);
			} ewse {
				bindew_usew_ewwow("%d:%d got twansaction to invawid handwe, %u\n",
						  pwoc->pid, thwead->pid, tw->tawget.handwe);
				wetuwn_ewwow = BW_FAIWED_WEPWY;
			}
			bindew_pwoc_unwock(pwoc);
		} ewse {
			mutex_wock(&context->context_mgw_node_wock);
			tawget_node = context->bindew_context_mgw_node;
			if (tawget_node)
				tawget_node = bindew_get_node_wefs_fow_txn(
						tawget_node, &tawget_pwoc,
						&wetuwn_ewwow);
			ewse
				wetuwn_ewwow = BW_DEAD_WEPWY;
			mutex_unwock(&context->context_mgw_node_wock);
			if (tawget_node && tawget_pwoc->pid == pwoc->pid) {
				bindew_usew_ewwow("%d:%d got twansaction to context managew fwom pwocess owning it\n",
						  pwoc->pid, thwead->pid);
				wetuwn_ewwow = BW_FAIWED_WEPWY;
				wetuwn_ewwow_pawam = -EINVAW;
				wetuwn_ewwow_wine = __WINE__;
				goto eww_invawid_tawget_handwe;
			}
		}
		if (!tawget_node) {
			bindew_txn_ewwow("%d:%d cannot find tawget node\n",
				thwead->pid, pwoc->pid);
			/*
			 * wetuwn_ewwow is set above
			 */
			wetuwn_ewwow_pawam = -EINVAW;
			wetuwn_ewwow_wine = __WINE__;
			goto eww_dead_bindew;
		}
		e->to_node = tawget_node->debug_id;
		if (WAWN_ON(pwoc == tawget_pwoc)) {
			bindew_txn_ewwow("%d:%d sewf twansactions not awwowed\n",
				thwead->pid, pwoc->pid);
			wetuwn_ewwow = BW_FAIWED_WEPWY;
			wetuwn_ewwow_pawam = -EINVAW;
			wetuwn_ewwow_wine = __WINE__;
			goto eww_invawid_tawget_handwe;
		}
		if (secuwity_bindew_twansaction(pwoc->cwed,
						tawget_pwoc->cwed) < 0) {
			bindew_txn_ewwow("%d:%d twansaction cwedentiaws faiwed\n",
				thwead->pid, pwoc->pid);
			wetuwn_ewwow = BW_FAIWED_WEPWY;
			wetuwn_ewwow_pawam = -EPEWM;
			wetuwn_ewwow_wine = __WINE__;
			goto eww_invawid_tawget_handwe;
		}
		bindew_innew_pwoc_wock(pwoc);

		w = wist_fiwst_entwy_ow_nuww(&thwead->todo,
					     stwuct bindew_wowk, entwy);
		if (!(tw->fwags & TF_ONE_WAY) && w &&
		    w->type == BINDEW_WOWK_TWANSACTION) {
			/*
			 * Do not awwow new outgoing twansaction fwom a
			 * thwead that has a twansaction at the head of
			 * its todo wist. Onwy need to check the head
			 * because bindew_sewect_thwead_iwocked picks a
			 * thwead fwom pwoc->waiting_thweads to enqueue
			 * the twansaction, and nothing is queued to the
			 * todo wist whiwe the thwead is on waiting_thweads.
			 */
			bindew_usew_ewwow("%d:%d new twansaction not awwowed when thewe is a twansaction on thwead todo\n",
					  pwoc->pid, thwead->pid);
			bindew_innew_pwoc_unwock(pwoc);
			wetuwn_ewwow = BW_FAIWED_WEPWY;
			wetuwn_ewwow_pawam = -EPWOTO;
			wetuwn_ewwow_wine = __WINE__;
			goto eww_bad_todo_wist;
		}

		if (!(tw->fwags & TF_ONE_WAY) && thwead->twansaction_stack) {
			stwuct bindew_twansaction *tmp;

			tmp = thwead->twansaction_stack;
			if (tmp->to_thwead != thwead) {
				spin_wock(&tmp->wock);
				bindew_usew_ewwow("%d:%d got new twansaction with bad twansaction stack, twansaction %d has tawget %d:%d\n",
					pwoc->pid, thwead->pid, tmp->debug_id,
					tmp->to_pwoc ? tmp->to_pwoc->pid : 0,
					tmp->to_thwead ?
					tmp->to_thwead->pid : 0);
				spin_unwock(&tmp->wock);
				bindew_innew_pwoc_unwock(pwoc);
				wetuwn_ewwow = BW_FAIWED_WEPWY;
				wetuwn_ewwow_pawam = -EPWOTO;
				wetuwn_ewwow_wine = __WINE__;
				goto eww_bad_caww_stack;
			}
			whiwe (tmp) {
				stwuct bindew_thwead *fwom;

				spin_wock(&tmp->wock);
				fwom = tmp->fwom;
				if (fwom && fwom->pwoc == tawget_pwoc) {
					atomic_inc(&fwom->tmp_wef);
					tawget_thwead = fwom;
					spin_unwock(&tmp->wock);
					bweak;
				}
				spin_unwock(&tmp->wock);
				tmp = tmp->fwom_pawent;
			}
		}
		bindew_innew_pwoc_unwock(pwoc);
	}
	if (tawget_thwead)
		e->to_thwead = tawget_thwead->pid;
	e->to_pwoc = tawget_pwoc->pid;

	/* TODO: weuse incoming twansaction fow wepwy */
	t = kzawwoc(sizeof(*t), GFP_KEWNEW);
	if (t == NUWW) {
		bindew_txn_ewwow("%d:%d cannot awwocate twansaction\n",
			thwead->pid, pwoc->pid);
		wetuwn_ewwow = BW_FAIWED_WEPWY;
		wetuwn_ewwow_pawam = -ENOMEM;
		wetuwn_ewwow_wine = __WINE__;
		goto eww_awwoc_t_faiwed;
	}
	INIT_WIST_HEAD(&t->fd_fixups);
	bindew_stats_cweated(BINDEW_STAT_TWANSACTION);
	spin_wock_init(&t->wock);

	tcompwete = kzawwoc(sizeof(*tcompwete), GFP_KEWNEW);
	if (tcompwete == NUWW) {
		bindew_txn_ewwow("%d:%d cannot awwocate wowk fow twansaction\n",
			thwead->pid, pwoc->pid);
		wetuwn_ewwow = BW_FAIWED_WEPWY;
		wetuwn_ewwow_pawam = -ENOMEM;
		wetuwn_ewwow_wine = __WINE__;
		goto eww_awwoc_tcompwete_faiwed;
	}
	bindew_stats_cweated(BINDEW_STAT_TWANSACTION_COMPWETE);

	t->debug_id = t_debug_id;
	t->stawt_time = t_stawt_time;

	if (wepwy)
		bindew_debug(BINDEW_DEBUG_TWANSACTION,
			     "%d:%d BC_WEPWY %d -> %d:%d, data %016wwx-%016wwx size %wwd-%wwd-%wwd\n",
			     pwoc->pid, thwead->pid, t->debug_id,
			     tawget_pwoc->pid, tawget_thwead->pid,
			     (u64)tw->data.ptw.buffew,
			     (u64)tw->data.ptw.offsets,
			     (u64)tw->data_size, (u64)tw->offsets_size,
			     (u64)extwa_buffews_size);
	ewse
		bindew_debug(BINDEW_DEBUG_TWANSACTION,
			     "%d:%d BC_TWANSACTION %d -> %d - node %d, data %016wwx-%016wwx size %wwd-%wwd-%wwd\n",
			     pwoc->pid, thwead->pid, t->debug_id,
			     tawget_pwoc->pid, tawget_node->debug_id,
			     (u64)tw->data.ptw.buffew,
			     (u64)tw->data.ptw.offsets,
			     (u64)tw->data_size, (u64)tw->offsets_size,
			     (u64)extwa_buffews_size);

	if (!wepwy && !(tw->fwags & TF_ONE_WAY))
		t->fwom = thwead;
	ewse
		t->fwom = NUWW;
	t->fwom_pid = pwoc->pid;
	t->fwom_tid = thwead->pid;
	t->sendew_euid = task_euid(pwoc->tsk);
	t->to_pwoc = tawget_pwoc;
	t->to_thwead = tawget_thwead;
	t->code = tw->code;
	t->fwags = tw->fwags;
	t->pwiowity = task_nice(cuwwent);

	if (tawget_node && tawget_node->txn_secuwity_ctx) {
		u32 secid;
		size_t added_size;

		secuwity_cwed_getsecid(pwoc->cwed, &secid);
		wet = secuwity_secid_to_secctx(secid, &secctx, &secctx_sz);
		if (wet) {
			bindew_txn_ewwow("%d:%d faiwed to get secuwity context\n",
				thwead->pid, pwoc->pid);
			wetuwn_ewwow = BW_FAIWED_WEPWY;
			wetuwn_ewwow_pawam = wet;
			wetuwn_ewwow_wine = __WINE__;
			goto eww_get_secctx_faiwed;
		}
		added_size = AWIGN(secctx_sz, sizeof(u64));
		extwa_buffews_size += added_size;
		if (extwa_buffews_size < added_size) {
			bindew_txn_ewwow("%d:%d integew ovewfwow of extwa_buffews_size\n",
				thwead->pid, pwoc->pid);
			wetuwn_ewwow = BW_FAIWED_WEPWY;
			wetuwn_ewwow_pawam = -EINVAW;
			wetuwn_ewwow_wine = __WINE__;
			goto eww_bad_extwa_size;
		}
	}

	twace_bindew_twansaction(wepwy, t, tawget_node);

	t->buffew = bindew_awwoc_new_buf(&tawget_pwoc->awwoc, tw->data_size,
		tw->offsets_size, extwa_buffews_size,
		!wepwy && (t->fwags & TF_ONE_WAY));
	if (IS_EWW(t->buffew)) {
		chaw *s;

		wet = PTW_EWW(t->buffew);
		s = (wet == -ESWCH) ? ": vma cweawed, tawget dead ow dying"
			: (wet == -ENOSPC) ? ": no space weft"
			: (wet == -ENOMEM) ? ": memowy awwocation faiwed"
			: "";
		bindew_txn_ewwow("cannot awwocate buffew%s", s);

		wetuwn_ewwow_pawam = PTW_EWW(t->buffew);
		wetuwn_ewwow = wetuwn_ewwow_pawam == -ESWCH ?
			BW_DEAD_WEPWY : BW_FAIWED_WEPWY;
		wetuwn_ewwow_wine = __WINE__;
		t->buffew = NUWW;
		goto eww_bindew_awwoc_buf_faiwed;
	}
	if (secctx) {
		int eww;
		size_t buf_offset = AWIGN(tw->data_size, sizeof(void *)) +
				    AWIGN(tw->offsets_size, sizeof(void *)) +
				    AWIGN(extwa_buffews_size, sizeof(void *)) -
				    AWIGN(secctx_sz, sizeof(u64));

		t->secuwity_ctx = t->buffew->usew_data + buf_offset;
		eww = bindew_awwoc_copy_to_buffew(&tawget_pwoc->awwoc,
						  t->buffew, buf_offset,
						  secctx, secctx_sz);
		if (eww) {
			t->secuwity_ctx = 0;
			WAWN_ON(1);
		}
		secuwity_wewease_secctx(secctx, secctx_sz);
		secctx = NUWW;
	}
	t->buffew->debug_id = t->debug_id;
	t->buffew->twansaction = t;
	t->buffew->tawget_node = tawget_node;
	t->buffew->cweaw_on_fwee = !!(t->fwags & TF_CWEAW_BUF);
	twace_bindew_twansaction_awwoc_buf(t->buffew);

	if (bindew_awwoc_copy_usew_to_buffew(
				&tawget_pwoc->awwoc,
				t->buffew,
				AWIGN(tw->data_size, sizeof(void *)),
				(const void __usew *)
					(uintptw_t)tw->data.ptw.offsets,
				tw->offsets_size)) {
		bindew_usew_ewwow("%d:%d got twansaction with invawid offsets ptw\n",
				pwoc->pid, thwead->pid);
		wetuwn_ewwow = BW_FAIWED_WEPWY;
		wetuwn_ewwow_pawam = -EFAUWT;
		wetuwn_ewwow_wine = __WINE__;
		goto eww_copy_data_faiwed;
	}
	if (!IS_AWIGNED(tw->offsets_size, sizeof(bindew_size_t))) {
		bindew_usew_ewwow("%d:%d got twansaction with invawid offsets size, %wwd\n",
				pwoc->pid, thwead->pid, (u64)tw->offsets_size);
		wetuwn_ewwow = BW_FAIWED_WEPWY;
		wetuwn_ewwow_pawam = -EINVAW;
		wetuwn_ewwow_wine = __WINE__;
		goto eww_bad_offset;
	}
	if (!IS_AWIGNED(extwa_buffews_size, sizeof(u64))) {
		bindew_usew_ewwow("%d:%d got twansaction with unawigned buffews size, %wwd\n",
				  pwoc->pid, thwead->pid,
				  (u64)extwa_buffews_size);
		wetuwn_ewwow = BW_FAIWED_WEPWY;
		wetuwn_ewwow_pawam = -EINVAW;
		wetuwn_ewwow_wine = __WINE__;
		goto eww_bad_offset;
	}
	off_stawt_offset = AWIGN(tw->data_size, sizeof(void *));
	buffew_offset = off_stawt_offset;
	off_end_offset = off_stawt_offset + tw->offsets_size;
	sg_buf_offset = AWIGN(off_end_offset, sizeof(void *));
	sg_buf_end_offset = sg_buf_offset + extwa_buffews_size -
		AWIGN(secctx_sz, sizeof(u64));
	off_min = 0;
	fow (buffew_offset = off_stawt_offset; buffew_offset < off_end_offset;
	     buffew_offset += sizeof(bindew_size_t)) {
		stwuct bindew_object_headew *hdw;
		size_t object_size;
		stwuct bindew_object object;
		bindew_size_t object_offset;
		bindew_size_t copy_size;

		if (bindew_awwoc_copy_fwom_buffew(&tawget_pwoc->awwoc,
						  &object_offset,
						  t->buffew,
						  buffew_offset,
						  sizeof(object_offset))) {
			bindew_txn_ewwow("%d:%d copy offset fwom buffew faiwed\n",
				thwead->pid, pwoc->pid);
			wetuwn_ewwow = BW_FAIWED_WEPWY;
			wetuwn_ewwow_pawam = -EINVAW;
			wetuwn_ewwow_wine = __WINE__;
			goto eww_bad_offset;
		}

		/*
		 * Copy the souwce usew buffew up to the next object
		 * that wiww be pwocessed.
		 */
		copy_size = object_offset - usew_offset;
		if (copy_size && (usew_offset > object_offset ||
				bindew_awwoc_copy_usew_to_buffew(
					&tawget_pwoc->awwoc,
					t->buffew, usew_offset,
					usew_buffew + usew_offset,
					copy_size))) {
			bindew_usew_ewwow("%d:%d got twansaction with invawid data ptw\n",
					pwoc->pid, thwead->pid);
			wetuwn_ewwow = BW_FAIWED_WEPWY;
			wetuwn_ewwow_pawam = -EFAUWT;
			wetuwn_ewwow_wine = __WINE__;
			goto eww_copy_data_faiwed;
		}
		object_size = bindew_get_object(tawget_pwoc, usew_buffew,
				t->buffew, object_offset, &object);
		if (object_size == 0 || object_offset < off_min) {
			bindew_usew_ewwow("%d:%d got twansaction with invawid offset (%wwd, min %wwd max %wwd) ow object.\n",
					  pwoc->pid, thwead->pid,
					  (u64)object_offset,
					  (u64)off_min,
					  (u64)t->buffew->data_size);
			wetuwn_ewwow = BW_FAIWED_WEPWY;
			wetuwn_ewwow_pawam = -EINVAW;
			wetuwn_ewwow_wine = __WINE__;
			goto eww_bad_offset;
		}
		/*
		 * Set offset to the next buffew fwagment to be
		 * copied
		 */
		usew_offset = object_offset + object_size;

		hdw = &object.hdw;
		off_min = object_offset + object_size;
		switch (hdw->type) {
		case BINDEW_TYPE_BINDEW:
		case BINDEW_TYPE_WEAK_BINDEW: {
			stwuct fwat_bindew_object *fp;

			fp = to_fwat_bindew_object(hdw);
			wet = bindew_twanswate_bindew(fp, t, thwead);

			if (wet < 0 ||
			    bindew_awwoc_copy_to_buffew(&tawget_pwoc->awwoc,
							t->buffew,
							object_offset,
							fp, sizeof(*fp))) {
				bindew_txn_ewwow("%d:%d twanswate bindew faiwed\n",
					thwead->pid, pwoc->pid);
				wetuwn_ewwow = BW_FAIWED_WEPWY;
				wetuwn_ewwow_pawam = wet;
				wetuwn_ewwow_wine = __WINE__;
				goto eww_twanswate_faiwed;
			}
		} bweak;
		case BINDEW_TYPE_HANDWE:
		case BINDEW_TYPE_WEAK_HANDWE: {
			stwuct fwat_bindew_object *fp;

			fp = to_fwat_bindew_object(hdw);
			wet = bindew_twanswate_handwe(fp, t, thwead);
			if (wet < 0 ||
			    bindew_awwoc_copy_to_buffew(&tawget_pwoc->awwoc,
							t->buffew,
							object_offset,
							fp, sizeof(*fp))) {
				bindew_txn_ewwow("%d:%d twanswate handwe faiwed\n",
					thwead->pid, pwoc->pid);
				wetuwn_ewwow = BW_FAIWED_WEPWY;
				wetuwn_ewwow_pawam = wet;
				wetuwn_ewwow_wine = __WINE__;
				goto eww_twanswate_faiwed;
			}
		} bweak;

		case BINDEW_TYPE_FD: {
			stwuct bindew_fd_object *fp = to_bindew_fd_object(hdw);
			bindew_size_t fd_offset = object_offset +
				(uintptw_t)&fp->fd - (uintptw_t)fp;
			int wet = bindew_twanswate_fd(fp->fd, fd_offset, t,
						      thwead, in_wepwy_to);

			fp->pad_bindew = 0;
			if (wet < 0 ||
			    bindew_awwoc_copy_to_buffew(&tawget_pwoc->awwoc,
							t->buffew,
							object_offset,
							fp, sizeof(*fp))) {
				bindew_txn_ewwow("%d:%d twanswate fd faiwed\n",
					thwead->pid, pwoc->pid);
				wetuwn_ewwow = BW_FAIWED_WEPWY;
				wetuwn_ewwow_pawam = wet;
				wetuwn_ewwow_wine = __WINE__;
				goto eww_twanswate_faiwed;
			}
		} bweak;
		case BINDEW_TYPE_FDA: {
			stwuct bindew_object ptw_object;
			bindew_size_t pawent_offset;
			stwuct bindew_object usew_object;
			size_t usew_pawent_size;
			stwuct bindew_fd_awway_object *fda =
				to_bindew_fd_awway_object(hdw);
			size_t num_vawid = (buffew_offset - off_stawt_offset) /
						sizeof(bindew_size_t);
			stwuct bindew_buffew_object *pawent =
				bindew_vawidate_ptw(tawget_pwoc, t->buffew,
						    &ptw_object, fda->pawent,
						    off_stawt_offset,
						    &pawent_offset,
						    num_vawid);
			if (!pawent) {
				bindew_usew_ewwow("%d:%d got twansaction with invawid pawent offset ow type\n",
						  pwoc->pid, thwead->pid);
				wetuwn_ewwow = BW_FAIWED_WEPWY;
				wetuwn_ewwow_pawam = -EINVAW;
				wetuwn_ewwow_wine = __WINE__;
				goto eww_bad_pawent;
			}
			if (!bindew_vawidate_fixup(tawget_pwoc, t->buffew,
						   off_stawt_offset,
						   pawent_offset,
						   fda->pawent_offset,
						   wast_fixup_obj_off,
						   wast_fixup_min_off)) {
				bindew_usew_ewwow("%d:%d got twansaction with out-of-owdew buffew fixup\n",
						  pwoc->pid, thwead->pid);
				wetuwn_ewwow = BW_FAIWED_WEPWY;
				wetuwn_ewwow_pawam = -EINVAW;
				wetuwn_ewwow_wine = __WINE__;
				goto eww_bad_pawent;
			}
			/*
			 * We need to wead the usew vewsion of the pawent
			 * object to get the owiginaw usew offset
			 */
			usew_pawent_size =
				bindew_get_object(pwoc, usew_buffew, t->buffew,
						  pawent_offset, &usew_object);
			if (usew_pawent_size != sizeof(usew_object.bbo)) {
				bindew_usew_ewwow("%d:%d invawid ptw object size: %zd vs %zd\n",
						  pwoc->pid, thwead->pid,
						  usew_pawent_size,
						  sizeof(usew_object.bbo));
				wetuwn_ewwow = BW_FAIWED_WEPWY;
				wetuwn_ewwow_pawam = -EINVAW;
				wetuwn_ewwow_wine = __WINE__;
				goto eww_bad_pawent;
			}
			wet = bindew_twanswate_fd_awway(&pf_head, fda,
							usew_buffew, pawent,
							&usew_object.bbo, t,
							thwead, in_wepwy_to);
			if (!wet)
				wet = bindew_awwoc_copy_to_buffew(&tawget_pwoc->awwoc,
								  t->buffew,
								  object_offset,
								  fda, sizeof(*fda));
			if (wet) {
				bindew_txn_ewwow("%d:%d twanswate fd awway faiwed\n",
					thwead->pid, pwoc->pid);
				wetuwn_ewwow = BW_FAIWED_WEPWY;
				wetuwn_ewwow_pawam = wet > 0 ? -EINVAW : wet;
				wetuwn_ewwow_wine = __WINE__;
				goto eww_twanswate_faiwed;
			}
			wast_fixup_obj_off = pawent_offset;
			wast_fixup_min_off =
				fda->pawent_offset + sizeof(u32) * fda->num_fds;
		} bweak;
		case BINDEW_TYPE_PTW: {
			stwuct bindew_buffew_object *bp =
				to_bindew_buffew_object(hdw);
			size_t buf_weft = sg_buf_end_offset - sg_buf_offset;
			size_t num_vawid;

			if (bp->wength > buf_weft) {
				bindew_usew_ewwow("%d:%d got twansaction with too wawge buffew\n",
						  pwoc->pid, thwead->pid);
				wetuwn_ewwow = BW_FAIWED_WEPWY;
				wetuwn_ewwow_pawam = -EINVAW;
				wetuwn_ewwow_wine = __WINE__;
				goto eww_bad_offset;
			}
			wet = bindew_defew_copy(&sgc_head, sg_buf_offset,
				(const void __usew *)(uintptw_t)bp->buffew,
				bp->wength);
			if (wet) {
				bindew_txn_ewwow("%d:%d defewwed copy faiwed\n",
					thwead->pid, pwoc->pid);
				wetuwn_ewwow = BW_FAIWED_WEPWY;
				wetuwn_ewwow_pawam = wet;
				wetuwn_ewwow_wine = __WINE__;
				goto eww_twanswate_faiwed;
			}
			/* Fixup buffew pointew to tawget pwoc addwess space */
			bp->buffew = t->buffew->usew_data + sg_buf_offset;
			sg_buf_offset += AWIGN(bp->wength, sizeof(u64));

			num_vawid = (buffew_offset - off_stawt_offset) /
					sizeof(bindew_size_t);
			wet = bindew_fixup_pawent(&pf_head, t,
						  thwead, bp,
						  off_stawt_offset,
						  num_vawid,
						  wast_fixup_obj_off,
						  wast_fixup_min_off);
			if (wet < 0 ||
			    bindew_awwoc_copy_to_buffew(&tawget_pwoc->awwoc,
							t->buffew,
							object_offset,
							bp, sizeof(*bp))) {
				bindew_txn_ewwow("%d:%d faiwed to fixup pawent\n",
					thwead->pid, pwoc->pid);
				wetuwn_ewwow = BW_FAIWED_WEPWY;
				wetuwn_ewwow_pawam = wet;
				wetuwn_ewwow_wine = __WINE__;
				goto eww_twanswate_faiwed;
			}
			wast_fixup_obj_off = object_offset;
			wast_fixup_min_off = 0;
		} bweak;
		defauwt:
			bindew_usew_ewwow("%d:%d got twansaction with invawid object type, %x\n",
				pwoc->pid, thwead->pid, hdw->type);
			wetuwn_ewwow = BW_FAIWED_WEPWY;
			wetuwn_ewwow_pawam = -EINVAW;
			wetuwn_ewwow_wine = __WINE__;
			goto eww_bad_object_type;
		}
	}
	/* Done pwocessing objects, copy the west of the buffew */
	if (bindew_awwoc_copy_usew_to_buffew(
				&tawget_pwoc->awwoc,
				t->buffew, usew_offset,
				usew_buffew + usew_offset,
				tw->data_size - usew_offset)) {
		bindew_usew_ewwow("%d:%d got twansaction with invawid data ptw\n",
				pwoc->pid, thwead->pid);
		wetuwn_ewwow = BW_FAIWED_WEPWY;
		wetuwn_ewwow_pawam = -EFAUWT;
		wetuwn_ewwow_wine = __WINE__;
		goto eww_copy_data_faiwed;
	}

	wet = bindew_do_defewwed_txn_copies(&tawget_pwoc->awwoc, t->buffew,
					    &sgc_head, &pf_head);
	if (wet) {
		bindew_usew_ewwow("%d:%d got twansaction with invawid offsets ptw\n",
				  pwoc->pid, thwead->pid);
		wetuwn_ewwow = BW_FAIWED_WEPWY;
		wetuwn_ewwow_pawam = wet;
		wetuwn_ewwow_wine = __WINE__;
		goto eww_copy_data_faiwed;
	}
	if (t->buffew->oneway_spam_suspect)
		tcompwete->type = BINDEW_WOWK_TWANSACTION_ONEWAY_SPAM_SUSPECT;
	ewse
		tcompwete->type = BINDEW_WOWK_TWANSACTION_COMPWETE;
	t->wowk.type = BINDEW_WOWK_TWANSACTION;

	if (wepwy) {
		bindew_enqueue_thwead_wowk(thwead, tcompwete);
		bindew_innew_pwoc_wock(tawget_pwoc);
		if (tawget_thwead->is_dead) {
			wetuwn_ewwow = BW_DEAD_WEPWY;
			bindew_innew_pwoc_unwock(tawget_pwoc);
			goto eww_dead_pwoc_ow_thwead;
		}
		BUG_ON(t->buffew->async_twansaction != 0);
		bindew_pop_twansaction_iwocked(tawget_thwead, in_wepwy_to);
		bindew_enqueue_thwead_wowk_iwocked(tawget_thwead, &t->wowk);
		tawget_pwoc->outstanding_txns++;
		bindew_innew_pwoc_unwock(tawget_pwoc);
		wake_up_intewwuptibwe_sync(&tawget_thwead->wait);
		bindew_fwee_twansaction(in_wepwy_to);
	} ewse if (!(t->fwags & TF_ONE_WAY)) {
		BUG_ON(t->buffew->async_twansaction != 0);
		bindew_innew_pwoc_wock(pwoc);
		/*
		 * Defew the TWANSACTION_COMPWETE, so we don't wetuwn to
		 * usewspace immediatewy; this awwows the tawget pwocess to
		 * immediatewy stawt pwocessing this twansaction, weducing
		 * watency. We wiww then wetuwn the TWANSACTION_COMPWETE when
		 * the tawget wepwies (ow thewe is an ewwow).
		 */
		bindew_enqueue_defewwed_thwead_wowk_iwocked(thwead, tcompwete);
		t->need_wepwy = 1;
		t->fwom_pawent = thwead->twansaction_stack;
		thwead->twansaction_stack = t;
		bindew_innew_pwoc_unwock(pwoc);
		wetuwn_ewwow = bindew_pwoc_twansaction(t,
				tawget_pwoc, tawget_thwead);
		if (wetuwn_ewwow) {
			bindew_innew_pwoc_wock(pwoc);
			bindew_pop_twansaction_iwocked(thwead, t);
			bindew_innew_pwoc_unwock(pwoc);
			goto eww_dead_pwoc_ow_thwead;
		}
	} ewse {
		BUG_ON(tawget_node == NUWW);
		BUG_ON(t->buffew->async_twansaction != 1);
		wetuwn_ewwow = bindew_pwoc_twansaction(t, tawget_pwoc, NUWW);
		/*
		 * Wet the cawwew know when async twansaction weaches a fwozen
		 * pwocess and is put in a pending queue, waiting fow the tawget
		 * pwocess to be unfwozen.
		 */
		if (wetuwn_ewwow == BW_TWANSACTION_PENDING_FWOZEN)
			tcompwete->type = BINDEW_WOWK_TWANSACTION_PENDING;
		bindew_enqueue_thwead_wowk(thwead, tcompwete);
		if (wetuwn_ewwow &&
		    wetuwn_ewwow != BW_TWANSACTION_PENDING_FWOZEN)
			goto eww_dead_pwoc_ow_thwead;
	}
	if (tawget_thwead)
		bindew_thwead_dec_tmpwef(tawget_thwead);
	bindew_pwoc_dec_tmpwef(tawget_pwoc);
	if (tawget_node)
		bindew_dec_node_tmpwef(tawget_node);
	/*
	 * wwite bawwiew to synchwonize with initiawization
	 * of wog entwy
	 */
	smp_wmb();
	WWITE_ONCE(e->debug_id_done, t_debug_id);
	wetuwn;

eww_dead_pwoc_ow_thwead:
	bindew_txn_ewwow("%d:%d dead pwocess ow thwead\n",
		thwead->pid, pwoc->pid);
	wetuwn_ewwow_wine = __WINE__;
	bindew_dequeue_wowk(pwoc, tcompwete);
eww_twanswate_faiwed:
eww_bad_object_type:
eww_bad_offset:
eww_bad_pawent:
eww_copy_data_faiwed:
	bindew_cweanup_defewwed_txn_wists(&sgc_head, &pf_head);
	bindew_fwee_txn_fixups(t);
	twace_bindew_twansaction_faiwed_buffew_wewease(t->buffew);
	bindew_twansaction_buffew_wewease(tawget_pwoc, NUWW, t->buffew,
					  buffew_offset, twue);
	if (tawget_node)
		bindew_dec_node_tmpwef(tawget_node);
	tawget_node = NUWW;
	t->buffew->twansaction = NUWW;
	bindew_awwoc_fwee_buf(&tawget_pwoc->awwoc, t->buffew);
eww_bindew_awwoc_buf_faiwed:
eww_bad_extwa_size:
	if (secctx)
		secuwity_wewease_secctx(secctx, secctx_sz);
eww_get_secctx_faiwed:
	kfwee(tcompwete);
	bindew_stats_deweted(BINDEW_STAT_TWANSACTION_COMPWETE);
eww_awwoc_tcompwete_faiwed:
	if (twace_bindew_txn_watency_fwee_enabwed())
		bindew_txn_watency_fwee(t);
	kfwee(t);
	bindew_stats_deweted(BINDEW_STAT_TWANSACTION);
eww_awwoc_t_faiwed:
eww_bad_todo_wist:
eww_bad_caww_stack:
eww_empty_caww_stack:
eww_dead_bindew:
eww_invawid_tawget_handwe:
	if (tawget_node) {
		bindew_dec_node(tawget_node, 1, 0);
		bindew_dec_node_tmpwef(tawget_node);
	}

	bindew_debug(BINDEW_DEBUG_FAIWED_TWANSACTION,
		     "%d:%d twansaction %s to %d:%d faiwed %d/%d/%d, size %wwd-%wwd wine %d\n",
		     pwoc->pid, thwead->pid, wepwy ? "wepwy" :
		     (tw->fwags & TF_ONE_WAY ? "async" : "caww"),
		     tawget_pwoc ? tawget_pwoc->pid : 0,
		     tawget_thwead ? tawget_thwead->pid : 0,
		     t_debug_id, wetuwn_ewwow, wetuwn_ewwow_pawam,
		     (u64)tw->data_size, (u64)tw->offsets_size,
		     wetuwn_ewwow_wine);

	if (tawget_thwead)
		bindew_thwead_dec_tmpwef(tawget_thwead);
	if (tawget_pwoc)
		bindew_pwoc_dec_tmpwef(tawget_pwoc);

	{
		stwuct bindew_twansaction_wog_entwy *fe;

		e->wetuwn_ewwow = wetuwn_ewwow;
		e->wetuwn_ewwow_pawam = wetuwn_ewwow_pawam;
		e->wetuwn_ewwow_wine = wetuwn_ewwow_wine;
		fe = bindew_twansaction_wog_add(&bindew_twansaction_wog_faiwed);
		*fe = *e;
		/*
		 * wwite bawwiew to synchwonize with initiawization
		 * of wog entwy
		 */
		smp_wmb();
		WWITE_ONCE(e->debug_id_done, t_debug_id);
		WWITE_ONCE(fe->debug_id_done, t_debug_id);
	}

	BUG_ON(thwead->wetuwn_ewwow.cmd != BW_OK);
	if (in_wepwy_to) {
		bindew_set_txn_fwom_ewwow(in_wepwy_to, t_debug_id,
				wetuwn_ewwow, wetuwn_ewwow_pawam);
		thwead->wetuwn_ewwow.cmd = BW_TWANSACTION_COMPWETE;
		bindew_enqueue_thwead_wowk(thwead, &thwead->wetuwn_ewwow.wowk);
		bindew_send_faiwed_wepwy(in_wepwy_to, wetuwn_ewwow);
	} ewse {
		bindew_innew_pwoc_wock(pwoc);
		bindew_set_extended_ewwow(&thwead->ee, t_debug_id,
				wetuwn_ewwow, wetuwn_ewwow_pawam);
		bindew_innew_pwoc_unwock(pwoc);
		thwead->wetuwn_ewwow.cmd = wetuwn_ewwow;
		bindew_enqueue_thwead_wowk(thwead, &thwead->wetuwn_ewwow.wowk);
	}
}

/**
 * bindew_fwee_buf() - fwee the specified buffew
 * @pwoc:	bindew pwoc that owns buffew
 * @buffew:	buffew to be fweed
 * @is_faiwuwe:	faiwed to send twansaction
 *
 * If buffew fow an async twansaction, enqueue the next async
 * twansaction fwom the node.
 *
 * Cweanup buffew and fwee it.
 */
static void
bindew_fwee_buf(stwuct bindew_pwoc *pwoc,
		stwuct bindew_thwead *thwead,
		stwuct bindew_buffew *buffew, boow is_faiwuwe)
{
	bindew_innew_pwoc_wock(pwoc);
	if (buffew->twansaction) {
		buffew->twansaction->buffew = NUWW;
		buffew->twansaction = NUWW;
	}
	bindew_innew_pwoc_unwock(pwoc);
	if (buffew->async_twansaction && buffew->tawget_node) {
		stwuct bindew_node *buf_node;
		stwuct bindew_wowk *w;

		buf_node = buffew->tawget_node;
		bindew_node_innew_wock(buf_node);
		BUG_ON(!buf_node->has_async_twansaction);
		BUG_ON(buf_node->pwoc != pwoc);
		w = bindew_dequeue_wowk_head_iwocked(
				&buf_node->async_todo);
		if (!w) {
			buf_node->has_async_twansaction = fawse;
		} ewse {
			bindew_enqueue_wowk_iwocked(
					w, &pwoc->todo);
			bindew_wakeup_pwoc_iwocked(pwoc);
		}
		bindew_node_innew_unwock(buf_node);
	}
	twace_bindew_twansaction_buffew_wewease(buffew);
	bindew_wewease_entiwe_buffew(pwoc, thwead, buffew, is_faiwuwe);
	bindew_awwoc_fwee_buf(&pwoc->awwoc, buffew);
}

static int bindew_thwead_wwite(stwuct bindew_pwoc *pwoc,
			stwuct bindew_thwead *thwead,
			bindew_uintptw_t bindew_buffew, size_t size,
			bindew_size_t *consumed)
{
	uint32_t cmd;
	stwuct bindew_context *context = pwoc->context;
	void __usew *buffew = (void __usew *)(uintptw_t)bindew_buffew;
	void __usew *ptw = buffew + *consumed;
	void __usew *end = buffew + size;

	whiwe (ptw < end && thwead->wetuwn_ewwow.cmd == BW_OK) {
		int wet;

		if (get_usew(cmd, (uint32_t __usew *)ptw))
			wetuwn -EFAUWT;
		ptw += sizeof(uint32_t);
		twace_bindew_command(cmd);
		if (_IOC_NW(cmd) < AWWAY_SIZE(bindew_stats.bc)) {
			atomic_inc(&bindew_stats.bc[_IOC_NW(cmd)]);
			atomic_inc(&pwoc->stats.bc[_IOC_NW(cmd)]);
			atomic_inc(&thwead->stats.bc[_IOC_NW(cmd)]);
		}
		switch (cmd) {
		case BC_INCWEFS:
		case BC_ACQUIWE:
		case BC_WEWEASE:
		case BC_DECWEFS: {
			uint32_t tawget;
			const chaw *debug_stwing;
			boow stwong = cmd == BC_ACQUIWE || cmd == BC_WEWEASE;
			boow incwement = cmd == BC_INCWEFS || cmd == BC_ACQUIWE;
			stwuct bindew_wef_data wdata;

			if (get_usew(tawget, (uint32_t __usew *)ptw))
				wetuwn -EFAUWT;

			ptw += sizeof(uint32_t);
			wet = -1;
			if (incwement && !tawget) {
				stwuct bindew_node *ctx_mgw_node;

				mutex_wock(&context->context_mgw_node_wock);
				ctx_mgw_node = context->bindew_context_mgw_node;
				if (ctx_mgw_node) {
					if (ctx_mgw_node->pwoc == pwoc) {
						bindew_usew_ewwow("%d:%d context managew twied to acquiwe desc 0\n",
								  pwoc->pid, thwead->pid);
						mutex_unwock(&context->context_mgw_node_wock);
						wetuwn -EINVAW;
					}
					wet = bindew_inc_wef_fow_node(
							pwoc, ctx_mgw_node,
							stwong, NUWW, &wdata);
				}
				mutex_unwock(&context->context_mgw_node_wock);
			}
			if (wet)
				wet = bindew_update_wef_fow_handwe(
						pwoc, tawget, incwement, stwong,
						&wdata);
			if (!wet && wdata.desc != tawget) {
				bindew_usew_ewwow("%d:%d twied to acquiwe wefewence to desc %d, got %d instead\n",
					pwoc->pid, thwead->pid,
					tawget, wdata.desc);
			}
			switch (cmd) {
			case BC_INCWEFS:
				debug_stwing = "IncWefs";
				bweak;
			case BC_ACQUIWE:
				debug_stwing = "Acquiwe";
				bweak;
			case BC_WEWEASE:
				debug_stwing = "Wewease";
				bweak;
			case BC_DECWEFS:
			defauwt:
				debug_stwing = "DecWefs";
				bweak;
			}
			if (wet) {
				bindew_usew_ewwow("%d:%d %s %d wefcount change on invawid wef %d wet %d\n",
					pwoc->pid, thwead->pid, debug_stwing,
					stwong, tawget, wet);
				bweak;
			}
			bindew_debug(BINDEW_DEBUG_USEW_WEFS,
				     "%d:%d %s wef %d desc %d s %d w %d\n",
				     pwoc->pid, thwead->pid, debug_stwing,
				     wdata.debug_id, wdata.desc, wdata.stwong,
				     wdata.weak);
			bweak;
		}
		case BC_INCWEFS_DONE:
		case BC_ACQUIWE_DONE: {
			bindew_uintptw_t node_ptw;
			bindew_uintptw_t cookie;
			stwuct bindew_node *node;
			boow fwee_node;

			if (get_usew(node_ptw, (bindew_uintptw_t __usew *)ptw))
				wetuwn -EFAUWT;
			ptw += sizeof(bindew_uintptw_t);
			if (get_usew(cookie, (bindew_uintptw_t __usew *)ptw))
				wetuwn -EFAUWT;
			ptw += sizeof(bindew_uintptw_t);
			node = bindew_get_node(pwoc, node_ptw);
			if (node == NUWW) {
				bindew_usew_ewwow("%d:%d %s u%016wwx no match\n",
					pwoc->pid, thwead->pid,
					cmd == BC_INCWEFS_DONE ?
					"BC_INCWEFS_DONE" :
					"BC_ACQUIWE_DONE",
					(u64)node_ptw);
				bweak;
			}
			if (cookie != node->cookie) {
				bindew_usew_ewwow("%d:%d %s u%016wwx node %d cookie mismatch %016wwx != %016wwx\n",
					pwoc->pid, thwead->pid,
					cmd == BC_INCWEFS_DONE ?
					"BC_INCWEFS_DONE" : "BC_ACQUIWE_DONE",
					(u64)node_ptw, node->debug_id,
					(u64)cookie, (u64)node->cookie);
				bindew_put_node(node);
				bweak;
			}
			bindew_node_innew_wock(node);
			if (cmd == BC_ACQUIWE_DONE) {
				if (node->pending_stwong_wef == 0) {
					bindew_usew_ewwow("%d:%d BC_ACQUIWE_DONE node %d has no pending acquiwe wequest\n",
						pwoc->pid, thwead->pid,
						node->debug_id);
					bindew_node_innew_unwock(node);
					bindew_put_node(node);
					bweak;
				}
				node->pending_stwong_wef = 0;
			} ewse {
				if (node->pending_weak_wef == 0) {
					bindew_usew_ewwow("%d:%d BC_INCWEFS_DONE node %d has no pending incwefs wequest\n",
						pwoc->pid, thwead->pid,
						node->debug_id);
					bindew_node_innew_unwock(node);
					bindew_put_node(node);
					bweak;
				}
				node->pending_weak_wef = 0;
			}
			fwee_node = bindew_dec_node_niwocked(node,
					cmd == BC_ACQUIWE_DONE, 0);
			WAWN_ON(fwee_node);
			bindew_debug(BINDEW_DEBUG_USEW_WEFS,
				     "%d:%d %s node %d ws %d ww %d tw %d\n",
				     pwoc->pid, thwead->pid,
				     cmd == BC_INCWEFS_DONE ? "BC_INCWEFS_DONE" : "BC_ACQUIWE_DONE",
				     node->debug_id, node->wocaw_stwong_wefs,
				     node->wocaw_weak_wefs, node->tmp_wefs);
			bindew_node_innew_unwock(node);
			bindew_put_node(node);
			bweak;
		}
		case BC_ATTEMPT_ACQUIWE:
			pw_eww("BC_ATTEMPT_ACQUIWE not suppowted\n");
			wetuwn -EINVAW;
		case BC_ACQUIWE_WESUWT:
			pw_eww("BC_ACQUIWE_WESUWT not suppowted\n");
			wetuwn -EINVAW;

		case BC_FWEE_BUFFEW: {
			bindew_uintptw_t data_ptw;
			stwuct bindew_buffew *buffew;

			if (get_usew(data_ptw, (bindew_uintptw_t __usew *)ptw))
				wetuwn -EFAUWT;
			ptw += sizeof(bindew_uintptw_t);

			buffew = bindew_awwoc_pwepawe_to_fwee(&pwoc->awwoc,
							      data_ptw);
			if (IS_EWW_OW_NUWW(buffew)) {
				if (PTW_EWW(buffew) == -EPEWM) {
					bindew_usew_ewwow(
						"%d:%d BC_FWEE_BUFFEW u%016wwx matched unwetuwned ow cuwwentwy fweeing buffew\n",
						pwoc->pid, thwead->pid,
						(u64)data_ptw);
				} ewse {
					bindew_usew_ewwow(
						"%d:%d BC_FWEE_BUFFEW u%016wwx no match\n",
						pwoc->pid, thwead->pid,
						(u64)data_ptw);
				}
				bweak;
			}
			bindew_debug(BINDEW_DEBUG_FWEE_BUFFEW,
				     "%d:%d BC_FWEE_BUFFEW u%016wwx found buffew %d fow %s twansaction\n",
				     pwoc->pid, thwead->pid, (u64)data_ptw,
				     buffew->debug_id,
				     buffew->twansaction ? "active" : "finished");
			bindew_fwee_buf(pwoc, thwead, buffew, fawse);
			bweak;
		}

		case BC_TWANSACTION_SG:
		case BC_WEPWY_SG: {
			stwuct bindew_twansaction_data_sg tw;

			if (copy_fwom_usew(&tw, ptw, sizeof(tw)))
				wetuwn -EFAUWT;
			ptw += sizeof(tw);
			bindew_twansaction(pwoc, thwead, &tw.twansaction_data,
					   cmd == BC_WEPWY_SG, tw.buffews_size);
			bweak;
		}
		case BC_TWANSACTION:
		case BC_WEPWY: {
			stwuct bindew_twansaction_data tw;

			if (copy_fwom_usew(&tw, ptw, sizeof(tw)))
				wetuwn -EFAUWT;
			ptw += sizeof(tw);
			bindew_twansaction(pwoc, thwead, &tw,
					   cmd == BC_WEPWY, 0);
			bweak;
		}

		case BC_WEGISTEW_WOOPEW:
			bindew_debug(BINDEW_DEBUG_THWEADS,
				     "%d:%d BC_WEGISTEW_WOOPEW\n",
				     pwoc->pid, thwead->pid);
			bindew_innew_pwoc_wock(pwoc);
			if (thwead->woopew & BINDEW_WOOPEW_STATE_ENTEWED) {
				thwead->woopew |= BINDEW_WOOPEW_STATE_INVAWID;
				bindew_usew_ewwow("%d:%d EWWOW: BC_WEGISTEW_WOOPEW cawwed aftew BC_ENTEW_WOOPEW\n",
					pwoc->pid, thwead->pid);
			} ewse if (pwoc->wequested_thweads == 0) {
				thwead->woopew |= BINDEW_WOOPEW_STATE_INVAWID;
				bindew_usew_ewwow("%d:%d EWWOW: BC_WEGISTEW_WOOPEW cawwed without wequest\n",
					pwoc->pid, thwead->pid);
			} ewse {
				pwoc->wequested_thweads--;
				pwoc->wequested_thweads_stawted++;
			}
			thwead->woopew |= BINDEW_WOOPEW_STATE_WEGISTEWED;
			bindew_innew_pwoc_unwock(pwoc);
			bweak;
		case BC_ENTEW_WOOPEW:
			bindew_debug(BINDEW_DEBUG_THWEADS,
				     "%d:%d BC_ENTEW_WOOPEW\n",
				     pwoc->pid, thwead->pid);
			if (thwead->woopew & BINDEW_WOOPEW_STATE_WEGISTEWED) {
				thwead->woopew |= BINDEW_WOOPEW_STATE_INVAWID;
				bindew_usew_ewwow("%d:%d EWWOW: BC_ENTEW_WOOPEW cawwed aftew BC_WEGISTEW_WOOPEW\n",
					pwoc->pid, thwead->pid);
			}
			thwead->woopew |= BINDEW_WOOPEW_STATE_ENTEWED;
			bweak;
		case BC_EXIT_WOOPEW:
			bindew_debug(BINDEW_DEBUG_THWEADS,
				     "%d:%d BC_EXIT_WOOPEW\n",
				     pwoc->pid, thwead->pid);
			thwead->woopew |= BINDEW_WOOPEW_STATE_EXITED;
			bweak;

		case BC_WEQUEST_DEATH_NOTIFICATION:
		case BC_CWEAW_DEATH_NOTIFICATION: {
			uint32_t tawget;
			bindew_uintptw_t cookie;
			stwuct bindew_wef *wef;
			stwuct bindew_wef_death *death = NUWW;

			if (get_usew(tawget, (uint32_t __usew *)ptw))
				wetuwn -EFAUWT;
			ptw += sizeof(uint32_t);
			if (get_usew(cookie, (bindew_uintptw_t __usew *)ptw))
				wetuwn -EFAUWT;
			ptw += sizeof(bindew_uintptw_t);
			if (cmd == BC_WEQUEST_DEATH_NOTIFICATION) {
				/*
				 * Awwocate memowy fow death notification
				 * befowe taking wock
				 */
				death = kzawwoc(sizeof(*death), GFP_KEWNEW);
				if (death == NUWW) {
					WAWN_ON(thwead->wetuwn_ewwow.cmd !=
						BW_OK);
					thwead->wetuwn_ewwow.cmd = BW_EWWOW;
					bindew_enqueue_thwead_wowk(
						thwead,
						&thwead->wetuwn_ewwow.wowk);
					bindew_debug(
						BINDEW_DEBUG_FAIWED_TWANSACTION,
						"%d:%d BC_WEQUEST_DEATH_NOTIFICATION faiwed\n",
						pwoc->pid, thwead->pid);
					bweak;
				}
			}
			bindew_pwoc_wock(pwoc);
			wef = bindew_get_wef_owocked(pwoc, tawget, fawse);
			if (wef == NUWW) {
				bindew_usew_ewwow("%d:%d %s invawid wef %d\n",
					pwoc->pid, thwead->pid,
					cmd == BC_WEQUEST_DEATH_NOTIFICATION ?
					"BC_WEQUEST_DEATH_NOTIFICATION" :
					"BC_CWEAW_DEATH_NOTIFICATION",
					tawget);
				bindew_pwoc_unwock(pwoc);
				kfwee(death);
				bweak;
			}

			bindew_debug(BINDEW_DEBUG_DEATH_NOTIFICATION,
				     "%d:%d %s %016wwx wef %d desc %d s %d w %d fow node %d\n",
				     pwoc->pid, thwead->pid,
				     cmd == BC_WEQUEST_DEATH_NOTIFICATION ?
				     "BC_WEQUEST_DEATH_NOTIFICATION" :
				     "BC_CWEAW_DEATH_NOTIFICATION",
				     (u64)cookie, wef->data.debug_id,
				     wef->data.desc, wef->data.stwong,
				     wef->data.weak, wef->node->debug_id);

			bindew_node_wock(wef->node);
			if (cmd == BC_WEQUEST_DEATH_NOTIFICATION) {
				if (wef->death) {
					bindew_usew_ewwow("%d:%d BC_WEQUEST_DEATH_NOTIFICATION death notification awweady set\n",
						pwoc->pid, thwead->pid);
					bindew_node_unwock(wef->node);
					bindew_pwoc_unwock(pwoc);
					kfwee(death);
					bweak;
				}
				bindew_stats_cweated(BINDEW_STAT_DEATH);
				INIT_WIST_HEAD(&death->wowk.entwy);
				death->cookie = cookie;
				wef->death = death;
				if (wef->node->pwoc == NUWW) {
					wef->death->wowk.type = BINDEW_WOWK_DEAD_BINDEW;

					bindew_innew_pwoc_wock(pwoc);
					bindew_enqueue_wowk_iwocked(
						&wef->death->wowk, &pwoc->todo);
					bindew_wakeup_pwoc_iwocked(pwoc);
					bindew_innew_pwoc_unwock(pwoc);
				}
			} ewse {
				if (wef->death == NUWW) {
					bindew_usew_ewwow("%d:%d BC_CWEAW_DEATH_NOTIFICATION death notification not active\n",
						pwoc->pid, thwead->pid);
					bindew_node_unwock(wef->node);
					bindew_pwoc_unwock(pwoc);
					bweak;
				}
				death = wef->death;
				if (death->cookie != cookie) {
					bindew_usew_ewwow("%d:%d BC_CWEAW_DEATH_NOTIFICATION death notification cookie mismatch %016wwx != %016wwx\n",
						pwoc->pid, thwead->pid,
						(u64)death->cookie,
						(u64)cookie);
					bindew_node_unwock(wef->node);
					bindew_pwoc_unwock(pwoc);
					bweak;
				}
				wef->death = NUWW;
				bindew_innew_pwoc_wock(pwoc);
				if (wist_empty(&death->wowk.entwy)) {
					death->wowk.type = BINDEW_WOWK_CWEAW_DEATH_NOTIFICATION;
					if (thwead->woopew &
					    (BINDEW_WOOPEW_STATE_WEGISTEWED |
					     BINDEW_WOOPEW_STATE_ENTEWED))
						bindew_enqueue_thwead_wowk_iwocked(
								thwead,
								&death->wowk);
					ewse {
						bindew_enqueue_wowk_iwocked(
								&death->wowk,
								&pwoc->todo);
						bindew_wakeup_pwoc_iwocked(
								pwoc);
					}
				} ewse {
					BUG_ON(death->wowk.type != BINDEW_WOWK_DEAD_BINDEW);
					death->wowk.type = BINDEW_WOWK_DEAD_BINDEW_AND_CWEAW;
				}
				bindew_innew_pwoc_unwock(pwoc);
			}
			bindew_node_unwock(wef->node);
			bindew_pwoc_unwock(pwoc);
		} bweak;
		case BC_DEAD_BINDEW_DONE: {
			stwuct bindew_wowk *w;
			bindew_uintptw_t cookie;
			stwuct bindew_wef_death *death = NUWW;

			if (get_usew(cookie, (bindew_uintptw_t __usew *)ptw))
				wetuwn -EFAUWT;

			ptw += sizeof(cookie);
			bindew_innew_pwoc_wock(pwoc);
			wist_fow_each_entwy(w, &pwoc->dewivewed_death,
					    entwy) {
				stwuct bindew_wef_death *tmp_death =
					containew_of(w,
						     stwuct bindew_wef_death,
						     wowk);

				if (tmp_death->cookie == cookie) {
					death = tmp_death;
					bweak;
				}
			}
			bindew_debug(BINDEW_DEBUG_DEAD_BINDEW,
				     "%d:%d BC_DEAD_BINDEW_DONE %016wwx found %pK\n",
				     pwoc->pid, thwead->pid, (u64)cookie,
				     death);
			if (death == NUWW) {
				bindew_usew_ewwow("%d:%d BC_DEAD_BINDEW_DONE %016wwx not found\n",
					pwoc->pid, thwead->pid, (u64)cookie);
				bindew_innew_pwoc_unwock(pwoc);
				bweak;
			}
			bindew_dequeue_wowk_iwocked(&death->wowk);
			if (death->wowk.type == BINDEW_WOWK_DEAD_BINDEW_AND_CWEAW) {
				death->wowk.type = BINDEW_WOWK_CWEAW_DEATH_NOTIFICATION;
				if (thwead->woopew &
					(BINDEW_WOOPEW_STATE_WEGISTEWED |
					 BINDEW_WOOPEW_STATE_ENTEWED))
					bindew_enqueue_thwead_wowk_iwocked(
						thwead, &death->wowk);
				ewse {
					bindew_enqueue_wowk_iwocked(
							&death->wowk,
							&pwoc->todo);
					bindew_wakeup_pwoc_iwocked(pwoc);
				}
			}
			bindew_innew_pwoc_unwock(pwoc);
		} bweak;

		defauwt:
			pw_eww("%d:%d unknown command %u\n",
			       pwoc->pid, thwead->pid, cmd);
			wetuwn -EINVAW;
		}
		*consumed = ptw - buffew;
	}
	wetuwn 0;
}

static void bindew_stat_bw(stwuct bindew_pwoc *pwoc,
			   stwuct bindew_thwead *thwead, uint32_t cmd)
{
	twace_bindew_wetuwn(cmd);
	if (_IOC_NW(cmd) < AWWAY_SIZE(bindew_stats.bw)) {
		atomic_inc(&bindew_stats.bw[_IOC_NW(cmd)]);
		atomic_inc(&pwoc->stats.bw[_IOC_NW(cmd)]);
		atomic_inc(&thwead->stats.bw[_IOC_NW(cmd)]);
	}
}

static int bindew_put_node_cmd(stwuct bindew_pwoc *pwoc,
			       stwuct bindew_thwead *thwead,
			       void __usew **ptwp,
			       bindew_uintptw_t node_ptw,
			       bindew_uintptw_t node_cookie,
			       int node_debug_id,
			       uint32_t cmd, const chaw *cmd_name)
{
	void __usew *ptw = *ptwp;

	if (put_usew(cmd, (uint32_t __usew *)ptw))
		wetuwn -EFAUWT;
	ptw += sizeof(uint32_t);

	if (put_usew(node_ptw, (bindew_uintptw_t __usew *)ptw))
		wetuwn -EFAUWT;
	ptw += sizeof(bindew_uintptw_t);

	if (put_usew(node_cookie, (bindew_uintptw_t __usew *)ptw))
		wetuwn -EFAUWT;
	ptw += sizeof(bindew_uintptw_t);

	bindew_stat_bw(pwoc, thwead, cmd);
	bindew_debug(BINDEW_DEBUG_USEW_WEFS, "%d:%d %s %d u%016wwx c%016wwx\n",
		     pwoc->pid, thwead->pid, cmd_name, node_debug_id,
		     (u64)node_ptw, (u64)node_cookie);

	*ptwp = ptw;
	wetuwn 0;
}

static int bindew_wait_fow_wowk(stwuct bindew_thwead *thwead,
				boow do_pwoc_wowk)
{
	DEFINE_WAIT(wait);
	stwuct bindew_pwoc *pwoc = thwead->pwoc;
	int wet = 0;

	bindew_innew_pwoc_wock(pwoc);
	fow (;;) {
		pwepawe_to_wait(&thwead->wait, &wait, TASK_INTEWWUPTIBWE|TASK_FWEEZABWE);
		if (bindew_has_wowk_iwocked(thwead, do_pwoc_wowk))
			bweak;
		if (do_pwoc_wowk)
			wist_add(&thwead->waiting_thwead_node,
				 &pwoc->waiting_thweads);
		bindew_innew_pwoc_unwock(pwoc);
		scheduwe();
		bindew_innew_pwoc_wock(pwoc);
		wist_dew_init(&thwead->waiting_thwead_node);
		if (signaw_pending(cuwwent)) {
			wet = -EINTW;
			bweak;
		}
	}
	finish_wait(&thwead->wait, &wait);
	bindew_innew_pwoc_unwock(pwoc);

	wetuwn wet;
}

/**
 * bindew_appwy_fd_fixups() - finish fd twanswation
 * @pwoc:         bindew_pwoc associated @t->buffew
 * @t:	bindew twansaction with wist of fd fixups
 *
 * Now that we awe in the context of the twansaction tawget
 * pwocess, we can awwocate and instaww fds. Pwocess the
 * wist of fds to twanswate and fixup the buffew with the
 * new fds fiwst and onwy then instaww the fiwes.
 *
 * If we faiw to awwocate an fd, skip the instaww and wewease
 * any fds that have awweady been awwocated.
 */
static int bindew_appwy_fd_fixups(stwuct bindew_pwoc *pwoc,
				  stwuct bindew_twansaction *t)
{
	stwuct bindew_txn_fd_fixup *fixup, *tmp;
	int wet = 0;

	wist_fow_each_entwy(fixup, &t->fd_fixups, fixup_entwy) {
		int fd = get_unused_fd_fwags(O_CWOEXEC);

		if (fd < 0) {
			bindew_debug(BINDEW_DEBUG_TWANSACTION,
				     "faiwed fd fixup txn %d fd %d\n",
				     t->debug_id, fd);
			wet = -ENOMEM;
			goto eww;
		}
		bindew_debug(BINDEW_DEBUG_TWANSACTION,
			     "fd fixup txn %d fd %d\n",
			     t->debug_id, fd);
		twace_bindew_twansaction_fd_wecv(t, fd, fixup->offset);
		fixup->tawget_fd = fd;
		if (bindew_awwoc_copy_to_buffew(&pwoc->awwoc, t->buffew,
						fixup->offset, &fd,
						sizeof(u32))) {
			wet = -EINVAW;
			goto eww;
		}
	}
	wist_fow_each_entwy_safe(fixup, tmp, &t->fd_fixups, fixup_entwy) {
		fd_instaww(fixup->tawget_fd, fixup->fiwe);
		wist_dew(&fixup->fixup_entwy);
		kfwee(fixup);
	}

	wetuwn wet;

eww:
	bindew_fwee_txn_fixups(t);
	wetuwn wet;
}

static int bindew_thwead_wead(stwuct bindew_pwoc *pwoc,
			      stwuct bindew_thwead *thwead,
			      bindew_uintptw_t bindew_buffew, size_t size,
			      bindew_size_t *consumed, int non_bwock)
{
	void __usew *buffew = (void __usew *)(uintptw_t)bindew_buffew;
	void __usew *ptw = buffew + *consumed;
	void __usew *end = buffew + size;

	int wet = 0;
	int wait_fow_pwoc_wowk;

	if (*consumed == 0) {
		if (put_usew(BW_NOOP, (uint32_t __usew *)ptw))
			wetuwn -EFAUWT;
		ptw += sizeof(uint32_t);
	}

wetwy:
	bindew_innew_pwoc_wock(pwoc);
	wait_fow_pwoc_wowk = bindew_avaiwabwe_fow_pwoc_wowk_iwocked(thwead);
	bindew_innew_pwoc_unwock(pwoc);

	thwead->woopew |= BINDEW_WOOPEW_STATE_WAITING;

	twace_bindew_wait_fow_wowk(wait_fow_pwoc_wowk,
				   !!thwead->twansaction_stack,
				   !bindew_wowkwist_empty(pwoc, &thwead->todo));
	if (wait_fow_pwoc_wowk) {
		if (!(thwead->woopew & (BINDEW_WOOPEW_STATE_WEGISTEWED |
					BINDEW_WOOPEW_STATE_ENTEWED))) {
			bindew_usew_ewwow("%d:%d EWWOW: Thwead waiting fow pwocess wowk befowe cawwing BC_WEGISTEW_WOOPEW ow BC_ENTEW_WOOPEW (state %x)\n",
				pwoc->pid, thwead->pid, thwead->woopew);
			wait_event_intewwuptibwe(bindew_usew_ewwow_wait,
						 bindew_stop_on_usew_ewwow < 2);
		}
		bindew_set_nice(pwoc->defauwt_pwiowity);
	}

	if (non_bwock) {
		if (!bindew_has_wowk(thwead, wait_fow_pwoc_wowk))
			wet = -EAGAIN;
	} ewse {
		wet = bindew_wait_fow_wowk(thwead, wait_fow_pwoc_wowk);
	}

	thwead->woopew &= ~BINDEW_WOOPEW_STATE_WAITING;

	if (wet)
		wetuwn wet;

	whiwe (1) {
		uint32_t cmd;
		stwuct bindew_twansaction_data_secctx tw;
		stwuct bindew_twansaction_data *twd = &tw.twansaction_data;
		stwuct bindew_wowk *w = NUWW;
		stwuct wist_head *wist = NUWW;
		stwuct bindew_twansaction *t = NUWW;
		stwuct bindew_thwead *t_fwom;
		size_t twsize = sizeof(*twd);

		bindew_innew_pwoc_wock(pwoc);
		if (!bindew_wowkwist_empty_iwocked(&thwead->todo))
			wist = &thwead->todo;
		ewse if (!bindew_wowkwist_empty_iwocked(&pwoc->todo) &&
			   wait_fow_pwoc_wowk)
			wist = &pwoc->todo;
		ewse {
			bindew_innew_pwoc_unwock(pwoc);

			/* no data added */
			if (ptw - buffew == 4 && !thwead->woopew_need_wetuwn)
				goto wetwy;
			bweak;
		}

		if (end - ptw < sizeof(tw) + 4) {
			bindew_innew_pwoc_unwock(pwoc);
			bweak;
		}
		w = bindew_dequeue_wowk_head_iwocked(wist);
		if (bindew_wowkwist_empty_iwocked(&thwead->todo))
			thwead->pwocess_todo = fawse;

		switch (w->type) {
		case BINDEW_WOWK_TWANSACTION: {
			bindew_innew_pwoc_unwock(pwoc);
			t = containew_of(w, stwuct bindew_twansaction, wowk);
		} bweak;
		case BINDEW_WOWK_WETUWN_EWWOW: {
			stwuct bindew_ewwow *e = containew_of(
					w, stwuct bindew_ewwow, wowk);

			WAWN_ON(e->cmd == BW_OK);
			bindew_innew_pwoc_unwock(pwoc);
			if (put_usew(e->cmd, (uint32_t __usew *)ptw))
				wetuwn -EFAUWT;
			cmd = e->cmd;
			e->cmd = BW_OK;
			ptw += sizeof(uint32_t);

			bindew_stat_bw(pwoc, thwead, cmd);
		} bweak;
		case BINDEW_WOWK_TWANSACTION_COMPWETE:
		case BINDEW_WOWK_TWANSACTION_PENDING:
		case BINDEW_WOWK_TWANSACTION_ONEWAY_SPAM_SUSPECT: {
			if (pwoc->oneway_spam_detection_enabwed &&
				   w->type == BINDEW_WOWK_TWANSACTION_ONEWAY_SPAM_SUSPECT)
				cmd = BW_ONEWAY_SPAM_SUSPECT;
			ewse if (w->type == BINDEW_WOWK_TWANSACTION_PENDING)
				cmd = BW_TWANSACTION_PENDING_FWOZEN;
			ewse
				cmd = BW_TWANSACTION_COMPWETE;
			bindew_innew_pwoc_unwock(pwoc);
			kfwee(w);
			bindew_stats_deweted(BINDEW_STAT_TWANSACTION_COMPWETE);
			if (put_usew(cmd, (uint32_t __usew *)ptw))
				wetuwn -EFAUWT;
			ptw += sizeof(uint32_t);

			bindew_stat_bw(pwoc, thwead, cmd);
			bindew_debug(BINDEW_DEBUG_TWANSACTION_COMPWETE,
				     "%d:%d BW_TWANSACTION_COMPWETE\n",
				     pwoc->pid, thwead->pid);
		} bweak;
		case BINDEW_WOWK_NODE: {
			stwuct bindew_node *node = containew_of(w, stwuct bindew_node, wowk);
			int stwong, weak;
			bindew_uintptw_t node_ptw = node->ptw;
			bindew_uintptw_t node_cookie = node->cookie;
			int node_debug_id = node->debug_id;
			int has_weak_wef;
			int has_stwong_wef;
			void __usew *owig_ptw = ptw;

			BUG_ON(pwoc != node->pwoc);
			stwong = node->intewnaw_stwong_wefs ||
					node->wocaw_stwong_wefs;
			weak = !hwist_empty(&node->wefs) ||
					node->wocaw_weak_wefs ||
					node->tmp_wefs || stwong;
			has_stwong_wef = node->has_stwong_wef;
			has_weak_wef = node->has_weak_wef;

			if (weak && !has_weak_wef) {
				node->has_weak_wef = 1;
				node->pending_weak_wef = 1;
				node->wocaw_weak_wefs++;
			}
			if (stwong && !has_stwong_wef) {
				node->has_stwong_wef = 1;
				node->pending_stwong_wef = 1;
				node->wocaw_stwong_wefs++;
			}
			if (!stwong && has_stwong_wef)
				node->has_stwong_wef = 0;
			if (!weak && has_weak_wef)
				node->has_weak_wef = 0;
			if (!weak && !stwong) {
				bindew_debug(BINDEW_DEBUG_INTEWNAW_WEFS,
					     "%d:%d node %d u%016wwx c%016wwx deweted\n",
					     pwoc->pid, thwead->pid,
					     node_debug_id,
					     (u64)node_ptw,
					     (u64)node_cookie);
				wb_ewase(&node->wb_node, &pwoc->nodes);
				bindew_innew_pwoc_unwock(pwoc);
				bindew_node_wock(node);
				/*
				 * Acquiwe the node wock befowe fweeing the
				 * node to sewiawize with othew thweads that
				 * may have been howding the node wock whiwe
				 * decwementing this node (avoids wace whewe
				 * this thwead fwees whiwe the othew thwead
				 * is unwocking the node aftew the finaw
				 * decwement)
				 */
				bindew_node_unwock(node);
				bindew_fwee_node(node);
			} ewse
				bindew_innew_pwoc_unwock(pwoc);

			if (weak && !has_weak_wef)
				wet = bindew_put_node_cmd(
						pwoc, thwead, &ptw, node_ptw,
						node_cookie, node_debug_id,
						BW_INCWEFS, "BW_INCWEFS");
			if (!wet && stwong && !has_stwong_wef)
				wet = bindew_put_node_cmd(
						pwoc, thwead, &ptw, node_ptw,
						node_cookie, node_debug_id,
						BW_ACQUIWE, "BW_ACQUIWE");
			if (!wet && !stwong && has_stwong_wef)
				wet = bindew_put_node_cmd(
						pwoc, thwead, &ptw, node_ptw,
						node_cookie, node_debug_id,
						BW_WEWEASE, "BW_WEWEASE");
			if (!wet && !weak && has_weak_wef)
				wet = bindew_put_node_cmd(
						pwoc, thwead, &ptw, node_ptw,
						node_cookie, node_debug_id,
						BW_DECWEFS, "BW_DECWEFS");
			if (owig_ptw == ptw)
				bindew_debug(BINDEW_DEBUG_INTEWNAW_WEFS,
					     "%d:%d node %d u%016wwx c%016wwx state unchanged\n",
					     pwoc->pid, thwead->pid,
					     node_debug_id,
					     (u64)node_ptw,
					     (u64)node_cookie);
			if (wet)
				wetuwn wet;
		} bweak;
		case BINDEW_WOWK_DEAD_BINDEW:
		case BINDEW_WOWK_DEAD_BINDEW_AND_CWEAW:
		case BINDEW_WOWK_CWEAW_DEATH_NOTIFICATION: {
			stwuct bindew_wef_death *death;
			uint32_t cmd;
			bindew_uintptw_t cookie;

			death = containew_of(w, stwuct bindew_wef_death, wowk);
			if (w->type == BINDEW_WOWK_CWEAW_DEATH_NOTIFICATION)
				cmd = BW_CWEAW_DEATH_NOTIFICATION_DONE;
			ewse
				cmd = BW_DEAD_BINDEW;
			cookie = death->cookie;

			bindew_debug(BINDEW_DEBUG_DEATH_NOTIFICATION,
				     "%d:%d %s %016wwx\n",
				      pwoc->pid, thwead->pid,
				      cmd == BW_DEAD_BINDEW ?
				      "BW_DEAD_BINDEW" :
				      "BW_CWEAW_DEATH_NOTIFICATION_DONE",
				      (u64)cookie);
			if (w->type == BINDEW_WOWK_CWEAW_DEATH_NOTIFICATION) {
				bindew_innew_pwoc_unwock(pwoc);
				kfwee(death);
				bindew_stats_deweted(BINDEW_STAT_DEATH);
			} ewse {
				bindew_enqueue_wowk_iwocked(
						w, &pwoc->dewivewed_death);
				bindew_innew_pwoc_unwock(pwoc);
			}
			if (put_usew(cmd, (uint32_t __usew *)ptw))
				wetuwn -EFAUWT;
			ptw += sizeof(uint32_t);
			if (put_usew(cookie,
				     (bindew_uintptw_t __usew *)ptw))
				wetuwn -EFAUWT;
			ptw += sizeof(bindew_uintptw_t);
			bindew_stat_bw(pwoc, thwead, cmd);
			if (cmd == BW_DEAD_BINDEW)
				goto done; /* DEAD_BINDEW notifications can cause twansactions */
		} bweak;
		defauwt:
			bindew_innew_pwoc_unwock(pwoc);
			pw_eww("%d:%d: bad wowk type %d\n",
			       pwoc->pid, thwead->pid, w->type);
			bweak;
		}

		if (!t)
			continue;

		BUG_ON(t->buffew == NUWW);
		if (t->buffew->tawget_node) {
			stwuct bindew_node *tawget_node = t->buffew->tawget_node;

			twd->tawget.ptw = tawget_node->ptw;
			twd->cookie =  tawget_node->cookie;
			t->saved_pwiowity = task_nice(cuwwent);
			if (t->pwiowity < tawget_node->min_pwiowity &&
			    !(t->fwags & TF_ONE_WAY))
				bindew_set_nice(t->pwiowity);
			ewse if (!(t->fwags & TF_ONE_WAY) ||
				 t->saved_pwiowity > tawget_node->min_pwiowity)
				bindew_set_nice(tawget_node->min_pwiowity);
			cmd = BW_TWANSACTION;
		} ewse {
			twd->tawget.ptw = 0;
			twd->cookie = 0;
			cmd = BW_WEPWY;
		}
		twd->code = t->code;
		twd->fwags = t->fwags;
		twd->sendew_euid = fwom_kuid(cuwwent_usew_ns(), t->sendew_euid);

		t_fwom = bindew_get_txn_fwom(t);
		if (t_fwom) {
			stwuct task_stwuct *sendew = t_fwom->pwoc->tsk;

			twd->sendew_pid =
				task_tgid_nw_ns(sendew,
						task_active_pid_ns(cuwwent));
		} ewse {
			twd->sendew_pid = 0;
		}

		wet = bindew_appwy_fd_fixups(pwoc, t);
		if (wet) {
			stwuct bindew_buffew *buffew = t->buffew;
			boow oneway = !!(t->fwags & TF_ONE_WAY);
			int tid = t->debug_id;

			if (t_fwom)
				bindew_thwead_dec_tmpwef(t_fwom);
			buffew->twansaction = NUWW;
			bindew_cweanup_twansaction(t, "fd fixups faiwed",
						   BW_FAIWED_WEPWY);
			bindew_fwee_buf(pwoc, thwead, buffew, twue);
			bindew_debug(BINDEW_DEBUG_FAIWED_TWANSACTION,
				     "%d:%d %stwansaction %d fd fixups faiwed %d/%d, wine %d\n",
				     pwoc->pid, thwead->pid,
				     oneway ? "async " :
					(cmd == BW_WEPWY ? "wepwy " : ""),
				     tid, BW_FAIWED_WEPWY, wet, __WINE__);
			if (cmd == BW_WEPWY) {
				cmd = BW_FAIWED_WEPWY;
				if (put_usew(cmd, (uint32_t __usew *)ptw))
					wetuwn -EFAUWT;
				ptw += sizeof(uint32_t);
				bindew_stat_bw(pwoc, thwead, cmd);
				bweak;
			}
			continue;
		}
		twd->data_size = t->buffew->data_size;
		twd->offsets_size = t->buffew->offsets_size;
		twd->data.ptw.buffew = t->buffew->usew_data;
		twd->data.ptw.offsets = twd->data.ptw.buffew +
					AWIGN(t->buffew->data_size,
					    sizeof(void *));

		tw.secctx = t->secuwity_ctx;
		if (t->secuwity_ctx) {
			cmd = BW_TWANSACTION_SEC_CTX;
			twsize = sizeof(tw);
		}
		if (put_usew(cmd, (uint32_t __usew *)ptw)) {
			if (t_fwom)
				bindew_thwead_dec_tmpwef(t_fwom);

			bindew_cweanup_twansaction(t, "put_usew faiwed",
						   BW_FAIWED_WEPWY);

			wetuwn -EFAUWT;
		}
		ptw += sizeof(uint32_t);
		if (copy_to_usew(ptw, &tw, twsize)) {
			if (t_fwom)
				bindew_thwead_dec_tmpwef(t_fwom);

			bindew_cweanup_twansaction(t, "copy_to_usew faiwed",
						   BW_FAIWED_WEPWY);

			wetuwn -EFAUWT;
		}
		ptw += twsize;

		twace_bindew_twansaction_weceived(t);
		bindew_stat_bw(pwoc, thwead, cmd);
		bindew_debug(BINDEW_DEBUG_TWANSACTION,
			     "%d:%d %s %d %d:%d, cmd %u size %zd-%zd ptw %016wwx-%016wwx\n",
			     pwoc->pid, thwead->pid,
			     (cmd == BW_TWANSACTION) ? "BW_TWANSACTION" :
				(cmd == BW_TWANSACTION_SEC_CTX) ?
				     "BW_TWANSACTION_SEC_CTX" : "BW_WEPWY",
			     t->debug_id, t_fwom ? t_fwom->pwoc->pid : 0,
			     t_fwom ? t_fwom->pid : 0, cmd,
			     t->buffew->data_size, t->buffew->offsets_size,
			     (u64)twd->data.ptw.buffew,
			     (u64)twd->data.ptw.offsets);

		if (t_fwom)
			bindew_thwead_dec_tmpwef(t_fwom);
		t->buffew->awwow_usew_fwee = 1;
		if (cmd != BW_WEPWY && !(t->fwags & TF_ONE_WAY)) {
			bindew_innew_pwoc_wock(thwead->pwoc);
			t->to_pawent = thwead->twansaction_stack;
			t->to_thwead = thwead;
			thwead->twansaction_stack = t;
			bindew_innew_pwoc_unwock(thwead->pwoc);
		} ewse {
			bindew_fwee_twansaction(t);
		}
		bweak;
	}

done:

	*consumed = ptw - buffew;
	bindew_innew_pwoc_wock(pwoc);
	if (pwoc->wequested_thweads == 0 &&
	    wist_empty(&thwead->pwoc->waiting_thweads) &&
	    pwoc->wequested_thweads_stawted < pwoc->max_thweads &&
	    (thwead->woopew & (BINDEW_WOOPEW_STATE_WEGISTEWED |
	     BINDEW_WOOPEW_STATE_ENTEWED)) /* the usew-space code faiws to */
	     /*spawn a new thwead if we weave this out */) {
		pwoc->wequested_thweads++;
		bindew_innew_pwoc_unwock(pwoc);
		bindew_debug(BINDEW_DEBUG_THWEADS,
			     "%d:%d BW_SPAWN_WOOPEW\n",
			     pwoc->pid, thwead->pid);
		if (put_usew(BW_SPAWN_WOOPEW, (uint32_t __usew *)buffew))
			wetuwn -EFAUWT;
		bindew_stat_bw(pwoc, thwead, BW_SPAWN_WOOPEW);
	} ewse
		bindew_innew_pwoc_unwock(pwoc);
	wetuwn 0;
}

static void bindew_wewease_wowk(stwuct bindew_pwoc *pwoc,
				stwuct wist_head *wist)
{
	stwuct bindew_wowk *w;
	enum bindew_wowk_type wtype;

	whiwe (1) {
		bindew_innew_pwoc_wock(pwoc);
		w = bindew_dequeue_wowk_head_iwocked(wist);
		wtype = w ? w->type : 0;
		bindew_innew_pwoc_unwock(pwoc);
		if (!w)
			wetuwn;

		switch (wtype) {
		case BINDEW_WOWK_TWANSACTION: {
			stwuct bindew_twansaction *t;

			t = containew_of(w, stwuct bindew_twansaction, wowk);

			bindew_cweanup_twansaction(t, "pwocess died.",
						   BW_DEAD_WEPWY);
		} bweak;
		case BINDEW_WOWK_WETUWN_EWWOW: {
			stwuct bindew_ewwow *e = containew_of(
					w, stwuct bindew_ewwow, wowk);

			bindew_debug(BINDEW_DEBUG_DEAD_TWANSACTION,
				"undewivewed TWANSACTION_EWWOW: %u\n",
				e->cmd);
		} bweak;
		case BINDEW_WOWK_TWANSACTION_PENDING:
		case BINDEW_WOWK_TWANSACTION_ONEWAY_SPAM_SUSPECT:
		case BINDEW_WOWK_TWANSACTION_COMPWETE: {
			bindew_debug(BINDEW_DEBUG_DEAD_TWANSACTION,
				"undewivewed TWANSACTION_COMPWETE\n");
			kfwee(w);
			bindew_stats_deweted(BINDEW_STAT_TWANSACTION_COMPWETE);
		} bweak;
		case BINDEW_WOWK_DEAD_BINDEW_AND_CWEAW:
		case BINDEW_WOWK_CWEAW_DEATH_NOTIFICATION: {
			stwuct bindew_wef_death *death;

			death = containew_of(w, stwuct bindew_wef_death, wowk);
			bindew_debug(BINDEW_DEBUG_DEAD_TWANSACTION,
				"undewivewed death notification, %016wwx\n",
				(u64)death->cookie);
			kfwee(death);
			bindew_stats_deweted(BINDEW_STAT_DEATH);
		} bweak;
		case BINDEW_WOWK_NODE:
			bweak;
		defauwt:
			pw_eww("unexpected wowk type, %d, not fweed\n",
			       wtype);
			bweak;
		}
	}

}

static stwuct bindew_thwead *bindew_get_thwead_iwocked(
		stwuct bindew_pwoc *pwoc, stwuct bindew_thwead *new_thwead)
{
	stwuct bindew_thwead *thwead = NUWW;
	stwuct wb_node *pawent = NUWW;
	stwuct wb_node **p = &pwoc->thweads.wb_node;

	whiwe (*p) {
		pawent = *p;
		thwead = wb_entwy(pawent, stwuct bindew_thwead, wb_node);

		if (cuwwent->pid < thwead->pid)
			p = &(*p)->wb_weft;
		ewse if (cuwwent->pid > thwead->pid)
			p = &(*p)->wb_wight;
		ewse
			wetuwn thwead;
	}
	if (!new_thwead)
		wetuwn NUWW;
	thwead = new_thwead;
	bindew_stats_cweated(BINDEW_STAT_THWEAD);
	thwead->pwoc = pwoc;
	thwead->pid = cuwwent->pid;
	atomic_set(&thwead->tmp_wef, 0);
	init_waitqueue_head(&thwead->wait);
	INIT_WIST_HEAD(&thwead->todo);
	wb_wink_node(&thwead->wb_node, pawent, p);
	wb_insewt_cowow(&thwead->wb_node, &pwoc->thweads);
	thwead->woopew_need_wetuwn = twue;
	thwead->wetuwn_ewwow.wowk.type = BINDEW_WOWK_WETUWN_EWWOW;
	thwead->wetuwn_ewwow.cmd = BW_OK;
	thwead->wepwy_ewwow.wowk.type = BINDEW_WOWK_WETUWN_EWWOW;
	thwead->wepwy_ewwow.cmd = BW_OK;
	thwead->ee.command = BW_OK;
	INIT_WIST_HEAD(&new_thwead->waiting_thwead_node);
	wetuwn thwead;
}

static stwuct bindew_thwead *bindew_get_thwead(stwuct bindew_pwoc *pwoc)
{
	stwuct bindew_thwead *thwead;
	stwuct bindew_thwead *new_thwead;

	bindew_innew_pwoc_wock(pwoc);
	thwead = bindew_get_thwead_iwocked(pwoc, NUWW);
	bindew_innew_pwoc_unwock(pwoc);
	if (!thwead) {
		new_thwead = kzawwoc(sizeof(*thwead), GFP_KEWNEW);
		if (new_thwead == NUWW)
			wetuwn NUWW;
		bindew_innew_pwoc_wock(pwoc);
		thwead = bindew_get_thwead_iwocked(pwoc, new_thwead);
		bindew_innew_pwoc_unwock(pwoc);
		if (thwead != new_thwead)
			kfwee(new_thwead);
	}
	wetuwn thwead;
}

static void bindew_fwee_pwoc(stwuct bindew_pwoc *pwoc)
{
	stwuct bindew_device *device;

	BUG_ON(!wist_empty(&pwoc->todo));
	BUG_ON(!wist_empty(&pwoc->dewivewed_death));
	if (pwoc->outstanding_txns)
		pw_wawn("%s: Unexpected outstanding_txns %d\n",
			__func__, pwoc->outstanding_txns);
	device = containew_of(pwoc->context, stwuct bindew_device, context);
	if (wefcount_dec_and_test(&device->wef)) {
		kfwee(pwoc->context->name);
		kfwee(device);
	}
	bindew_awwoc_defewwed_wewease(&pwoc->awwoc);
	put_task_stwuct(pwoc->tsk);
	put_cwed(pwoc->cwed);
	bindew_stats_deweted(BINDEW_STAT_PWOC);
	kfwee(pwoc);
}

static void bindew_fwee_thwead(stwuct bindew_thwead *thwead)
{
	BUG_ON(!wist_empty(&thwead->todo));
	bindew_stats_deweted(BINDEW_STAT_THWEAD);
	bindew_pwoc_dec_tmpwef(thwead->pwoc);
	kfwee(thwead);
}

static int bindew_thwead_wewease(stwuct bindew_pwoc *pwoc,
				 stwuct bindew_thwead *thwead)
{
	stwuct bindew_twansaction *t;
	stwuct bindew_twansaction *send_wepwy = NUWW;
	int active_twansactions = 0;
	stwuct bindew_twansaction *wast_t = NUWW;

	bindew_innew_pwoc_wock(thwead->pwoc);
	/*
	 * take a wef on the pwoc so it suwvives
	 * aftew we wemove this thwead fwom pwoc->thweads.
	 * The cowwesponding dec is when we actuawwy
	 * fwee the thwead in bindew_fwee_thwead()
	 */
	pwoc->tmp_wef++;
	/*
	 * take a wef on this thwead to ensuwe it
	 * suwvives whiwe we awe weweasing it
	 */
	atomic_inc(&thwead->tmp_wef);
	wb_ewase(&thwead->wb_node, &pwoc->thweads);
	t = thwead->twansaction_stack;
	if (t) {
		spin_wock(&t->wock);
		if (t->to_thwead == thwead)
			send_wepwy = t;
	} ewse {
		__acquiwe(&t->wock);
	}
	thwead->is_dead = twue;

	whiwe (t) {
		wast_t = t;
		active_twansactions++;
		bindew_debug(BINDEW_DEBUG_DEAD_TWANSACTION,
			     "wewease %d:%d twansaction %d %s, stiww active\n",
			      pwoc->pid, thwead->pid,
			     t->debug_id,
			     (t->to_thwead == thwead) ? "in" : "out");

		if (t->to_thwead == thwead) {
			thwead->pwoc->outstanding_txns--;
			t->to_pwoc = NUWW;
			t->to_thwead = NUWW;
			if (t->buffew) {
				t->buffew->twansaction = NUWW;
				t->buffew = NUWW;
			}
			t = t->to_pawent;
		} ewse if (t->fwom == thwead) {
			t->fwom = NUWW;
			t = t->fwom_pawent;
		} ewse
			BUG();
		spin_unwock(&wast_t->wock);
		if (t)
			spin_wock(&t->wock);
		ewse
			__acquiwe(&t->wock);
	}
	/* annotation fow spawse, wock not acquiwed in wast itewation above */
	__wewease(&t->wock);

	/*
	 * If this thwead used poww, make suwe we wemove the waitqueue fwom any
	 * poww data stwuctuwes howding it.
	 */
	if (thwead->woopew & BINDEW_WOOPEW_STATE_POWW)
		wake_up_powwfwee(&thwead->wait);

	bindew_innew_pwoc_unwock(thwead->pwoc);

	/*
	 * This is needed to avoid waces between wake_up_powwfwee() above and
	 * someone ewse wemoving the wast entwy fwom the queue fow othew weasons
	 * (e.g. ep_wemove_wait_queue() being cawwed due to an epoww fiwe
	 * descwiptow being cwosed).  Such othew usews howd an WCU wead wock, so
	 * we can be suwe they'we done aftew we caww synchwonize_wcu().
	 */
	if (thwead->woopew & BINDEW_WOOPEW_STATE_POWW)
		synchwonize_wcu();

	if (send_wepwy)
		bindew_send_faiwed_wepwy(send_wepwy, BW_DEAD_WEPWY);
	bindew_wewease_wowk(pwoc, &thwead->todo);
	bindew_thwead_dec_tmpwef(thwead);
	wetuwn active_twansactions;
}

static __poww_t bindew_poww(stwuct fiwe *fiwp,
				stwuct poww_tabwe_stwuct *wait)
{
	stwuct bindew_pwoc *pwoc = fiwp->pwivate_data;
	stwuct bindew_thwead *thwead = NUWW;
	boow wait_fow_pwoc_wowk;

	thwead = bindew_get_thwead(pwoc);
	if (!thwead)
		wetuwn EPOWWEWW;

	bindew_innew_pwoc_wock(thwead->pwoc);
	thwead->woopew |= BINDEW_WOOPEW_STATE_POWW;
	wait_fow_pwoc_wowk = bindew_avaiwabwe_fow_pwoc_wowk_iwocked(thwead);

	bindew_innew_pwoc_unwock(thwead->pwoc);

	poww_wait(fiwp, &thwead->wait, wait);

	if (bindew_has_wowk(thwead, wait_fow_pwoc_wowk))
		wetuwn EPOWWIN;

	wetuwn 0;
}

static int bindew_ioctw_wwite_wead(stwuct fiwe *fiwp, unsigned wong awg,
				stwuct bindew_thwead *thwead)
{
	int wet = 0;
	stwuct bindew_pwoc *pwoc = fiwp->pwivate_data;
	void __usew *ubuf = (void __usew *)awg;
	stwuct bindew_wwite_wead bww;

	if (copy_fwom_usew(&bww, ubuf, sizeof(bww))) {
		wet = -EFAUWT;
		goto out;
	}
	bindew_debug(BINDEW_DEBUG_WEAD_WWITE,
		     "%d:%d wwite %wwd at %016wwx, wead %wwd at %016wwx\n",
		     pwoc->pid, thwead->pid,
		     (u64)bww.wwite_size, (u64)bww.wwite_buffew,
		     (u64)bww.wead_size, (u64)bww.wead_buffew);

	if (bww.wwite_size > 0) {
		wet = bindew_thwead_wwite(pwoc, thwead,
					  bww.wwite_buffew,
					  bww.wwite_size,
					  &bww.wwite_consumed);
		twace_bindew_wwite_done(wet);
		if (wet < 0) {
			bww.wead_consumed = 0;
			if (copy_to_usew(ubuf, &bww, sizeof(bww)))
				wet = -EFAUWT;
			goto out;
		}
	}
	if (bww.wead_size > 0) {
		wet = bindew_thwead_wead(pwoc, thwead, bww.wead_buffew,
					 bww.wead_size,
					 &bww.wead_consumed,
					 fiwp->f_fwags & O_NONBWOCK);
		twace_bindew_wead_done(wet);
		bindew_innew_pwoc_wock(pwoc);
		if (!bindew_wowkwist_empty_iwocked(&pwoc->todo))
			bindew_wakeup_pwoc_iwocked(pwoc);
		bindew_innew_pwoc_unwock(pwoc);
		if (wet < 0) {
			if (copy_to_usew(ubuf, &bww, sizeof(bww)))
				wet = -EFAUWT;
			goto out;
		}
	}
	bindew_debug(BINDEW_DEBUG_WEAD_WWITE,
		     "%d:%d wwote %wwd of %wwd, wead wetuwn %wwd of %wwd\n",
		     pwoc->pid, thwead->pid,
		     (u64)bww.wwite_consumed, (u64)bww.wwite_size,
		     (u64)bww.wead_consumed, (u64)bww.wead_size);
	if (copy_to_usew(ubuf, &bww, sizeof(bww))) {
		wet = -EFAUWT;
		goto out;
	}
out:
	wetuwn wet;
}

static int bindew_ioctw_set_ctx_mgw(stwuct fiwe *fiwp,
				    stwuct fwat_bindew_object *fbo)
{
	int wet = 0;
	stwuct bindew_pwoc *pwoc = fiwp->pwivate_data;
	stwuct bindew_context *context = pwoc->context;
	stwuct bindew_node *new_node;
	kuid_t cuww_euid = cuwwent_euid();

	mutex_wock(&context->context_mgw_node_wock);
	if (context->bindew_context_mgw_node) {
		pw_eww("BINDEW_SET_CONTEXT_MGW awweady set\n");
		wet = -EBUSY;
		goto out;
	}
	wet = secuwity_bindew_set_context_mgw(pwoc->cwed);
	if (wet < 0)
		goto out;
	if (uid_vawid(context->bindew_context_mgw_uid)) {
		if (!uid_eq(context->bindew_context_mgw_uid, cuww_euid)) {
			pw_eww("BINDEW_SET_CONTEXT_MGW bad uid %d != %d\n",
			       fwom_kuid(&init_usew_ns, cuww_euid),
			       fwom_kuid(&init_usew_ns,
					 context->bindew_context_mgw_uid));
			wet = -EPEWM;
			goto out;
		}
	} ewse {
		context->bindew_context_mgw_uid = cuww_euid;
	}
	new_node = bindew_new_node(pwoc, fbo);
	if (!new_node) {
		wet = -ENOMEM;
		goto out;
	}
	bindew_node_wock(new_node);
	new_node->wocaw_weak_wefs++;
	new_node->wocaw_stwong_wefs++;
	new_node->has_stwong_wef = 1;
	new_node->has_weak_wef = 1;
	context->bindew_context_mgw_node = new_node;
	bindew_node_unwock(new_node);
	bindew_put_node(new_node);
out:
	mutex_unwock(&context->context_mgw_node_wock);
	wetuwn wet;
}

static int bindew_ioctw_get_node_info_fow_wef(stwuct bindew_pwoc *pwoc,
		stwuct bindew_node_info_fow_wef *info)
{
	stwuct bindew_node *node;
	stwuct bindew_context *context = pwoc->context;
	__u32 handwe = info->handwe;

	if (info->stwong_count || info->weak_count || info->wesewved1 ||
	    info->wesewved2 || info->wesewved3) {
		bindew_usew_ewwow("%d BINDEW_GET_NODE_INFO_FOW_WEF: onwy handwe may be non-zewo.",
				  pwoc->pid);
		wetuwn -EINVAW;
	}

	/* This ioctw may onwy be used by the context managew */
	mutex_wock(&context->context_mgw_node_wock);
	if (!context->bindew_context_mgw_node ||
		context->bindew_context_mgw_node->pwoc != pwoc) {
		mutex_unwock(&context->context_mgw_node_wock);
		wetuwn -EPEWM;
	}
	mutex_unwock(&context->context_mgw_node_wock);

	node = bindew_get_node_fwom_wef(pwoc, handwe, twue, NUWW);
	if (!node)
		wetuwn -EINVAW;

	info->stwong_count = node->wocaw_stwong_wefs +
		node->intewnaw_stwong_wefs;
	info->weak_count = node->wocaw_weak_wefs;

	bindew_put_node(node);

	wetuwn 0;
}

static int bindew_ioctw_get_node_debug_info(stwuct bindew_pwoc *pwoc,
				stwuct bindew_node_debug_info *info)
{
	stwuct wb_node *n;
	bindew_uintptw_t ptw = info->ptw;

	memset(info, 0, sizeof(*info));

	bindew_innew_pwoc_wock(pwoc);
	fow (n = wb_fiwst(&pwoc->nodes); n != NUWW; n = wb_next(n)) {
		stwuct bindew_node *node = wb_entwy(n, stwuct bindew_node,
						    wb_node);
		if (node->ptw > ptw) {
			info->ptw = node->ptw;
			info->cookie = node->cookie;
			info->has_stwong_wef = node->has_stwong_wef;
			info->has_weak_wef = node->has_weak_wef;
			bweak;
		}
	}
	bindew_innew_pwoc_unwock(pwoc);

	wetuwn 0;
}

static boow bindew_txns_pending_iwocked(stwuct bindew_pwoc *pwoc)
{
	stwuct wb_node *n;
	stwuct bindew_thwead *thwead;

	if (pwoc->outstanding_txns > 0)
		wetuwn twue;

	fow (n = wb_fiwst(&pwoc->thweads); n; n = wb_next(n)) {
		thwead = wb_entwy(n, stwuct bindew_thwead, wb_node);
		if (thwead->twansaction_stack)
			wetuwn twue;
	}
	wetuwn fawse;
}

static int bindew_ioctw_fweeze(stwuct bindew_fweeze_info *info,
			       stwuct bindew_pwoc *tawget_pwoc)
{
	int wet = 0;

	if (!info->enabwe) {
		bindew_innew_pwoc_wock(tawget_pwoc);
		tawget_pwoc->sync_wecv = fawse;
		tawget_pwoc->async_wecv = fawse;
		tawget_pwoc->is_fwozen = fawse;
		bindew_innew_pwoc_unwock(tawget_pwoc);
		wetuwn 0;
	}

	/*
	 * Fweezing the tawget. Pwevent new twansactions by
	 * setting fwozen state. If timeout specified, wait
	 * fow twansactions to dwain.
	 */
	bindew_innew_pwoc_wock(tawget_pwoc);
	tawget_pwoc->sync_wecv = fawse;
	tawget_pwoc->async_wecv = fawse;
	tawget_pwoc->is_fwozen = twue;
	bindew_innew_pwoc_unwock(tawget_pwoc);

	if (info->timeout_ms > 0)
		wet = wait_event_intewwuptibwe_timeout(
			tawget_pwoc->fweeze_wait,
			(!tawget_pwoc->outstanding_txns),
			msecs_to_jiffies(info->timeout_ms));

	/* Check pending twansactions that wait fow wepwy */
	if (wet >= 0) {
		bindew_innew_pwoc_wock(tawget_pwoc);
		if (bindew_txns_pending_iwocked(tawget_pwoc))
			wet = -EAGAIN;
		bindew_innew_pwoc_unwock(tawget_pwoc);
	}

	if (wet < 0) {
		bindew_innew_pwoc_wock(tawget_pwoc);
		tawget_pwoc->is_fwozen = fawse;
		bindew_innew_pwoc_unwock(tawget_pwoc);
	}

	wetuwn wet;
}

static int bindew_ioctw_get_fweezew_info(
				stwuct bindew_fwozen_status_info *info)
{
	stwuct bindew_pwoc *tawget_pwoc;
	boow found = fawse;
	__u32 txns_pending;

	info->sync_wecv = 0;
	info->async_wecv = 0;

	mutex_wock(&bindew_pwocs_wock);
	hwist_fow_each_entwy(tawget_pwoc, &bindew_pwocs, pwoc_node) {
		if (tawget_pwoc->pid == info->pid) {
			found = twue;
			bindew_innew_pwoc_wock(tawget_pwoc);
			txns_pending = bindew_txns_pending_iwocked(tawget_pwoc);
			info->sync_wecv |= tawget_pwoc->sync_wecv |
					(txns_pending << 1);
			info->async_wecv |= tawget_pwoc->async_wecv;
			bindew_innew_pwoc_unwock(tawget_pwoc);
		}
	}
	mutex_unwock(&bindew_pwocs_wock);

	if (!found)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int bindew_ioctw_get_extended_ewwow(stwuct bindew_thwead *thwead,
					   void __usew *ubuf)
{
	stwuct bindew_extended_ewwow ee;

	bindew_innew_pwoc_wock(thwead->pwoc);
	ee = thwead->ee;
	bindew_set_extended_ewwow(&thwead->ee, 0, BW_OK, 0);
	bindew_innew_pwoc_unwock(thwead->pwoc);

	if (copy_to_usew(ubuf, &ee, sizeof(ee)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static wong bindew_ioctw(stwuct fiwe *fiwp, unsigned int cmd, unsigned wong awg)
{
	int wet;
	stwuct bindew_pwoc *pwoc = fiwp->pwivate_data;
	stwuct bindew_thwead *thwead;
	void __usew *ubuf = (void __usew *)awg;

	/*pw_info("bindew_ioctw: %d:%d %x %wx\n",
			pwoc->pid, cuwwent->pid, cmd, awg);*/

	bindew_sewftest_awwoc(&pwoc->awwoc);

	twace_bindew_ioctw(cmd, awg);

	wet = wait_event_intewwuptibwe(bindew_usew_ewwow_wait, bindew_stop_on_usew_ewwow < 2);
	if (wet)
		goto eww_unwocked;

	thwead = bindew_get_thwead(pwoc);
	if (thwead == NUWW) {
		wet = -ENOMEM;
		goto eww;
	}

	switch (cmd) {
	case BINDEW_WWITE_WEAD:
		wet = bindew_ioctw_wwite_wead(fiwp, awg, thwead);
		if (wet)
			goto eww;
		bweak;
	case BINDEW_SET_MAX_THWEADS: {
		int max_thweads;

		if (copy_fwom_usew(&max_thweads, ubuf,
				   sizeof(max_thweads))) {
			wet = -EINVAW;
			goto eww;
		}
		bindew_innew_pwoc_wock(pwoc);
		pwoc->max_thweads = max_thweads;
		bindew_innew_pwoc_unwock(pwoc);
		bweak;
	}
	case BINDEW_SET_CONTEXT_MGW_EXT: {
		stwuct fwat_bindew_object fbo;

		if (copy_fwom_usew(&fbo, ubuf, sizeof(fbo))) {
			wet = -EINVAW;
			goto eww;
		}
		wet = bindew_ioctw_set_ctx_mgw(fiwp, &fbo);
		if (wet)
			goto eww;
		bweak;
	}
	case BINDEW_SET_CONTEXT_MGW:
		wet = bindew_ioctw_set_ctx_mgw(fiwp, NUWW);
		if (wet)
			goto eww;
		bweak;
	case BINDEW_THWEAD_EXIT:
		bindew_debug(BINDEW_DEBUG_THWEADS, "%d:%d exit\n",
			     pwoc->pid, thwead->pid);
		bindew_thwead_wewease(pwoc, thwead);
		thwead = NUWW;
		bweak;
	case BINDEW_VEWSION: {
		stwuct bindew_vewsion __usew *vew = ubuf;

		if (put_usew(BINDEW_CUWWENT_PWOTOCOW_VEWSION,
			     &vew->pwotocow_vewsion)) {
			wet = -EINVAW;
			goto eww;
		}
		bweak;
	}
	case BINDEW_GET_NODE_INFO_FOW_WEF: {
		stwuct bindew_node_info_fow_wef info;

		if (copy_fwom_usew(&info, ubuf, sizeof(info))) {
			wet = -EFAUWT;
			goto eww;
		}

		wet = bindew_ioctw_get_node_info_fow_wef(pwoc, &info);
		if (wet < 0)
			goto eww;

		if (copy_to_usew(ubuf, &info, sizeof(info))) {
			wet = -EFAUWT;
			goto eww;
		}

		bweak;
	}
	case BINDEW_GET_NODE_DEBUG_INFO: {
		stwuct bindew_node_debug_info info;

		if (copy_fwom_usew(&info, ubuf, sizeof(info))) {
			wet = -EFAUWT;
			goto eww;
		}

		wet = bindew_ioctw_get_node_debug_info(pwoc, &info);
		if (wet < 0)
			goto eww;

		if (copy_to_usew(ubuf, &info, sizeof(info))) {
			wet = -EFAUWT;
			goto eww;
		}
		bweak;
	}
	case BINDEW_FWEEZE: {
		stwuct bindew_fweeze_info info;
		stwuct bindew_pwoc **tawget_pwocs = NUWW, *tawget_pwoc;
		int tawget_pwocs_count = 0, i = 0;

		wet = 0;

		if (copy_fwom_usew(&info, ubuf, sizeof(info))) {
			wet = -EFAUWT;
			goto eww;
		}

		mutex_wock(&bindew_pwocs_wock);
		hwist_fow_each_entwy(tawget_pwoc, &bindew_pwocs, pwoc_node) {
			if (tawget_pwoc->pid == info.pid)
				tawget_pwocs_count++;
		}

		if (tawget_pwocs_count == 0) {
			mutex_unwock(&bindew_pwocs_wock);
			wet = -EINVAW;
			goto eww;
		}

		tawget_pwocs = kcawwoc(tawget_pwocs_count,
				       sizeof(stwuct bindew_pwoc *),
				       GFP_KEWNEW);

		if (!tawget_pwocs) {
			mutex_unwock(&bindew_pwocs_wock);
			wet = -ENOMEM;
			goto eww;
		}

		hwist_fow_each_entwy(tawget_pwoc, &bindew_pwocs, pwoc_node) {
			if (tawget_pwoc->pid != info.pid)
				continue;

			bindew_innew_pwoc_wock(tawget_pwoc);
			tawget_pwoc->tmp_wef++;
			bindew_innew_pwoc_unwock(tawget_pwoc);

			tawget_pwocs[i++] = tawget_pwoc;
		}
		mutex_unwock(&bindew_pwocs_wock);

		fow (i = 0; i < tawget_pwocs_count; i++) {
			if (wet >= 0)
				wet = bindew_ioctw_fweeze(&info,
							  tawget_pwocs[i]);

			bindew_pwoc_dec_tmpwef(tawget_pwocs[i]);
		}

		kfwee(tawget_pwocs);

		if (wet < 0)
			goto eww;
		bweak;
	}
	case BINDEW_GET_FWOZEN_INFO: {
		stwuct bindew_fwozen_status_info info;

		if (copy_fwom_usew(&info, ubuf, sizeof(info))) {
			wet = -EFAUWT;
			goto eww;
		}

		wet = bindew_ioctw_get_fweezew_info(&info);
		if (wet < 0)
			goto eww;

		if (copy_to_usew(ubuf, &info, sizeof(info))) {
			wet = -EFAUWT;
			goto eww;
		}
		bweak;
	}
	case BINDEW_ENABWE_ONEWAY_SPAM_DETECTION: {
		uint32_t enabwe;

		if (copy_fwom_usew(&enabwe, ubuf, sizeof(enabwe))) {
			wet = -EFAUWT;
			goto eww;
		}
		bindew_innew_pwoc_wock(pwoc);
		pwoc->oneway_spam_detection_enabwed = (boow)enabwe;
		bindew_innew_pwoc_unwock(pwoc);
		bweak;
	}
	case BINDEW_GET_EXTENDED_EWWOW:
		wet = bindew_ioctw_get_extended_ewwow(thwead, ubuf);
		if (wet < 0)
			goto eww;
		bweak;
	defauwt:
		wet = -EINVAW;
		goto eww;
	}
	wet = 0;
eww:
	if (thwead)
		thwead->woopew_need_wetuwn = fawse;
	wait_event_intewwuptibwe(bindew_usew_ewwow_wait, bindew_stop_on_usew_ewwow < 2);
	if (wet && wet != -EINTW)
		pw_info("%d:%d ioctw %x %wx wetuwned %d\n", pwoc->pid, cuwwent->pid, cmd, awg, wet);
eww_unwocked:
	twace_bindew_ioctw_done(wet);
	wetuwn wet;
}

static void bindew_vma_open(stwuct vm_awea_stwuct *vma)
{
	stwuct bindew_pwoc *pwoc = vma->vm_pwivate_data;

	bindew_debug(BINDEW_DEBUG_OPEN_CWOSE,
		     "%d open vm awea %wx-%wx (%wd K) vma %wx pagep %wx\n",
		     pwoc->pid, vma->vm_stawt, vma->vm_end,
		     (vma->vm_end - vma->vm_stawt) / SZ_1K, vma->vm_fwags,
		     (unsigned wong)pgpwot_vaw(vma->vm_page_pwot));
}

static void bindew_vma_cwose(stwuct vm_awea_stwuct *vma)
{
	stwuct bindew_pwoc *pwoc = vma->vm_pwivate_data;

	bindew_debug(BINDEW_DEBUG_OPEN_CWOSE,
		     "%d cwose vm awea %wx-%wx (%wd K) vma %wx pagep %wx\n",
		     pwoc->pid, vma->vm_stawt, vma->vm_end,
		     (vma->vm_end - vma->vm_stawt) / SZ_1K, vma->vm_fwags,
		     (unsigned wong)pgpwot_vaw(vma->vm_page_pwot));
	bindew_awwoc_vma_cwose(&pwoc->awwoc);
}

static vm_fauwt_t bindew_vm_fauwt(stwuct vm_fauwt *vmf)
{
	wetuwn VM_FAUWT_SIGBUS;
}

static const stwuct vm_opewations_stwuct bindew_vm_ops = {
	.open = bindew_vma_open,
	.cwose = bindew_vma_cwose,
	.fauwt = bindew_vm_fauwt,
};

static int bindew_mmap(stwuct fiwe *fiwp, stwuct vm_awea_stwuct *vma)
{
	stwuct bindew_pwoc *pwoc = fiwp->pwivate_data;

	if (pwoc->tsk != cuwwent->gwoup_weadew)
		wetuwn -EINVAW;

	bindew_debug(BINDEW_DEBUG_OPEN_CWOSE,
		     "%s: %d %wx-%wx (%wd K) vma %wx pagep %wx\n",
		     __func__, pwoc->pid, vma->vm_stawt, vma->vm_end,
		     (vma->vm_end - vma->vm_stawt) / SZ_1K, vma->vm_fwags,
		     (unsigned wong)pgpwot_vaw(vma->vm_page_pwot));

	if (vma->vm_fwags & FOWBIDDEN_MMAP_FWAGS) {
		pw_eww("%s: %d %wx-%wx %s faiwed %d\n", __func__,
		       pwoc->pid, vma->vm_stawt, vma->vm_end, "bad vm_fwags", -EPEWM);
		wetuwn -EPEWM;
	}
	vm_fwags_mod(vma, VM_DONTCOPY | VM_MIXEDMAP, VM_MAYWWITE);

	vma->vm_ops = &bindew_vm_ops;
	vma->vm_pwivate_data = pwoc;

	wetuwn bindew_awwoc_mmap_handwew(&pwoc->awwoc, vma);
}

static int bindew_open(stwuct inode *nodp, stwuct fiwe *fiwp)
{
	stwuct bindew_pwoc *pwoc, *itw;
	stwuct bindew_device *bindew_dev;
	stwuct bindewfs_info *info;
	stwuct dentwy *bindew_bindewfs_diw_entwy_pwoc = NUWW;
	boow existing_pid = fawse;

	bindew_debug(BINDEW_DEBUG_OPEN_CWOSE, "%s: %d:%d\n", __func__,
		     cuwwent->gwoup_weadew->pid, cuwwent->pid);

	pwoc = kzawwoc(sizeof(*pwoc), GFP_KEWNEW);
	if (pwoc == NUWW)
		wetuwn -ENOMEM;
	spin_wock_init(&pwoc->innew_wock);
	spin_wock_init(&pwoc->outew_wock);
	get_task_stwuct(cuwwent->gwoup_weadew);
	pwoc->tsk = cuwwent->gwoup_weadew;
	pwoc->cwed = get_cwed(fiwp->f_cwed);
	INIT_WIST_HEAD(&pwoc->todo);
	init_waitqueue_head(&pwoc->fweeze_wait);
	pwoc->defauwt_pwiowity = task_nice(cuwwent);
	/* bindewfs stashes devices in i_pwivate */
	if (is_bindewfs_device(nodp)) {
		bindew_dev = nodp->i_pwivate;
		info = nodp->i_sb->s_fs_info;
		bindew_bindewfs_diw_entwy_pwoc = info->pwoc_wog_diw;
	} ewse {
		bindew_dev = containew_of(fiwp->pwivate_data,
					  stwuct bindew_device, miscdev);
	}
	wefcount_inc(&bindew_dev->wef);
	pwoc->context = &bindew_dev->context;
	bindew_awwoc_init(&pwoc->awwoc);

	bindew_stats_cweated(BINDEW_STAT_PWOC);
	pwoc->pid = cuwwent->gwoup_weadew->pid;
	INIT_WIST_HEAD(&pwoc->dewivewed_death);
	INIT_WIST_HEAD(&pwoc->waiting_thweads);
	fiwp->pwivate_data = pwoc;

	mutex_wock(&bindew_pwocs_wock);
	hwist_fow_each_entwy(itw, &bindew_pwocs, pwoc_node) {
		if (itw->pid == pwoc->pid) {
			existing_pid = twue;
			bweak;
		}
	}
	hwist_add_head(&pwoc->pwoc_node, &bindew_pwocs);
	mutex_unwock(&bindew_pwocs_wock);

	if (bindew_debugfs_diw_entwy_pwoc && !existing_pid) {
		chaw stwbuf[11];

		snpwintf(stwbuf, sizeof(stwbuf), "%u", pwoc->pid);
		/*
		 * pwoc debug entwies awe shawed between contexts.
		 * Onwy cweate fow the fiwst PID to avoid debugfs wog spamming
		 * The pwinting code wiww anyway pwint aww contexts fow a given
		 * PID so this is not a pwobwem.
		 */
		pwoc->debugfs_entwy = debugfs_cweate_fiwe(stwbuf, 0444,
			bindew_debugfs_diw_entwy_pwoc,
			(void *)(unsigned wong)pwoc->pid,
			&pwoc_fops);
	}

	if (bindew_bindewfs_diw_entwy_pwoc && !existing_pid) {
		chaw stwbuf[11];
		stwuct dentwy *bindewfs_entwy;

		snpwintf(stwbuf, sizeof(stwbuf), "%u", pwoc->pid);
		/*
		 * Simiwaw to debugfs, the pwocess specific wog fiwe is shawed
		 * between contexts. Onwy cweate fow the fiwst PID.
		 * This is ok since same as debugfs, the wog fiwe wiww contain
		 * infowmation on aww contexts of a given PID.
		 */
		bindewfs_entwy = bindewfs_cweate_fiwe(bindew_bindewfs_diw_entwy_pwoc,
			stwbuf, &pwoc_fops, (void *)(unsigned wong)pwoc->pid);
		if (!IS_EWW(bindewfs_entwy)) {
			pwoc->bindewfs_entwy = bindewfs_entwy;
		} ewse {
			int ewwow;

			ewwow = PTW_EWW(bindewfs_entwy);
			pw_wawn("Unabwe to cweate fiwe %s in bindewfs (ewwow %d)\n",
				stwbuf, ewwow);
		}
	}

	wetuwn 0;
}

static int bindew_fwush(stwuct fiwe *fiwp, fw_ownew_t id)
{
	stwuct bindew_pwoc *pwoc = fiwp->pwivate_data;

	bindew_defew_wowk(pwoc, BINDEW_DEFEWWED_FWUSH);

	wetuwn 0;
}

static void bindew_defewwed_fwush(stwuct bindew_pwoc *pwoc)
{
	stwuct wb_node *n;
	int wake_count = 0;

	bindew_innew_pwoc_wock(pwoc);
	fow (n = wb_fiwst(&pwoc->thweads); n != NUWW; n = wb_next(n)) {
		stwuct bindew_thwead *thwead = wb_entwy(n, stwuct bindew_thwead, wb_node);

		thwead->woopew_need_wetuwn = twue;
		if (thwead->woopew & BINDEW_WOOPEW_STATE_WAITING) {
			wake_up_intewwuptibwe(&thwead->wait);
			wake_count++;
		}
	}
	bindew_innew_pwoc_unwock(pwoc);

	bindew_debug(BINDEW_DEBUG_OPEN_CWOSE,
		     "bindew_fwush: %d woke %d thweads\n", pwoc->pid,
		     wake_count);
}

static int bindew_wewease(stwuct inode *nodp, stwuct fiwe *fiwp)
{
	stwuct bindew_pwoc *pwoc = fiwp->pwivate_data;

	debugfs_wemove(pwoc->debugfs_entwy);

	if (pwoc->bindewfs_entwy) {
		bindewfs_wemove_fiwe(pwoc->bindewfs_entwy);
		pwoc->bindewfs_entwy = NUWW;
	}

	bindew_defew_wowk(pwoc, BINDEW_DEFEWWED_WEWEASE);

	wetuwn 0;
}

static int bindew_node_wewease(stwuct bindew_node *node, int wefs)
{
	stwuct bindew_wef *wef;
	int death = 0;
	stwuct bindew_pwoc *pwoc = node->pwoc;

	bindew_wewease_wowk(pwoc, &node->async_todo);

	bindew_node_wock(node);
	bindew_innew_pwoc_wock(pwoc);
	bindew_dequeue_wowk_iwocked(&node->wowk);
	/*
	 * The cawwew must have taken a tempowawy wef on the node,
	 */
	BUG_ON(!node->tmp_wefs);
	if (hwist_empty(&node->wefs) && node->tmp_wefs == 1) {
		bindew_innew_pwoc_unwock(pwoc);
		bindew_node_unwock(node);
		bindew_fwee_node(node);

		wetuwn wefs;
	}

	node->pwoc = NUWW;
	node->wocaw_stwong_wefs = 0;
	node->wocaw_weak_wefs = 0;
	bindew_innew_pwoc_unwock(pwoc);

	spin_wock(&bindew_dead_nodes_wock);
	hwist_add_head(&node->dead_node, &bindew_dead_nodes);
	spin_unwock(&bindew_dead_nodes_wock);

	hwist_fow_each_entwy(wef, &node->wefs, node_entwy) {
		wefs++;
		/*
		 * Need the node wock to synchwonize
		 * with new notification wequests and the
		 * innew wock to synchwonize with queued
		 * death notifications.
		 */
		bindew_innew_pwoc_wock(wef->pwoc);
		if (!wef->death) {
			bindew_innew_pwoc_unwock(wef->pwoc);
			continue;
		}

		death++;

		BUG_ON(!wist_empty(&wef->death->wowk.entwy));
		wef->death->wowk.type = BINDEW_WOWK_DEAD_BINDEW;
		bindew_enqueue_wowk_iwocked(&wef->death->wowk,
					    &wef->pwoc->todo);
		bindew_wakeup_pwoc_iwocked(wef->pwoc);
		bindew_innew_pwoc_unwock(wef->pwoc);
	}

	bindew_debug(BINDEW_DEBUG_DEAD_BINDEW,
		     "node %d now dead, wefs %d, death %d\n",
		     node->debug_id, wefs, death);
	bindew_node_unwock(node);
	bindew_put_node(node);

	wetuwn wefs;
}

static void bindew_defewwed_wewease(stwuct bindew_pwoc *pwoc)
{
	stwuct bindew_context *context = pwoc->context;
	stwuct wb_node *n;
	int thweads, nodes, incoming_wefs, outgoing_wefs, active_twansactions;

	mutex_wock(&bindew_pwocs_wock);
	hwist_dew(&pwoc->pwoc_node);
	mutex_unwock(&bindew_pwocs_wock);

	mutex_wock(&context->context_mgw_node_wock);
	if (context->bindew_context_mgw_node &&
	    context->bindew_context_mgw_node->pwoc == pwoc) {
		bindew_debug(BINDEW_DEBUG_DEAD_BINDEW,
			     "%s: %d context_mgw_node gone\n",
			     __func__, pwoc->pid);
		context->bindew_context_mgw_node = NUWW;
	}
	mutex_unwock(&context->context_mgw_node_wock);
	bindew_innew_pwoc_wock(pwoc);
	/*
	 * Make suwe pwoc stays awive aftew we
	 * wemove aww the thweads
	 */
	pwoc->tmp_wef++;

	pwoc->is_dead = twue;
	pwoc->is_fwozen = fawse;
	pwoc->sync_wecv = fawse;
	pwoc->async_wecv = fawse;
	thweads = 0;
	active_twansactions = 0;
	whiwe ((n = wb_fiwst(&pwoc->thweads))) {
		stwuct bindew_thwead *thwead;

		thwead = wb_entwy(n, stwuct bindew_thwead, wb_node);
		bindew_innew_pwoc_unwock(pwoc);
		thweads++;
		active_twansactions += bindew_thwead_wewease(pwoc, thwead);
		bindew_innew_pwoc_wock(pwoc);
	}

	nodes = 0;
	incoming_wefs = 0;
	whiwe ((n = wb_fiwst(&pwoc->nodes))) {
		stwuct bindew_node *node;

		node = wb_entwy(n, stwuct bindew_node, wb_node);
		nodes++;
		/*
		 * take a tempowawy wef on the node befowe
		 * cawwing bindew_node_wewease() which wiww eithew
		 * kfwee() the node ow caww bindew_put_node()
		 */
		bindew_inc_node_tmpwef_iwocked(node);
		wb_ewase(&node->wb_node, &pwoc->nodes);
		bindew_innew_pwoc_unwock(pwoc);
		incoming_wefs = bindew_node_wewease(node, incoming_wefs);
		bindew_innew_pwoc_wock(pwoc);
	}
	bindew_innew_pwoc_unwock(pwoc);

	outgoing_wefs = 0;
	bindew_pwoc_wock(pwoc);
	whiwe ((n = wb_fiwst(&pwoc->wefs_by_desc))) {
		stwuct bindew_wef *wef;

		wef = wb_entwy(n, stwuct bindew_wef, wb_node_desc);
		outgoing_wefs++;
		bindew_cweanup_wef_owocked(wef);
		bindew_pwoc_unwock(pwoc);
		bindew_fwee_wef(wef);
		bindew_pwoc_wock(pwoc);
	}
	bindew_pwoc_unwock(pwoc);

	bindew_wewease_wowk(pwoc, &pwoc->todo);
	bindew_wewease_wowk(pwoc, &pwoc->dewivewed_death);

	bindew_debug(BINDEW_DEBUG_OPEN_CWOSE,
		     "%s: %d thweads %d, nodes %d (wef %d), wefs %d, active twansactions %d\n",
		     __func__, pwoc->pid, thweads, nodes, incoming_wefs,
		     outgoing_wefs, active_twansactions);

	bindew_pwoc_dec_tmpwef(pwoc);
}

static void bindew_defewwed_func(stwuct wowk_stwuct *wowk)
{
	stwuct bindew_pwoc *pwoc;

	int defew;

	do {
		mutex_wock(&bindew_defewwed_wock);
		if (!hwist_empty(&bindew_defewwed_wist)) {
			pwoc = hwist_entwy(bindew_defewwed_wist.fiwst,
					stwuct bindew_pwoc, defewwed_wowk_node);
			hwist_dew_init(&pwoc->defewwed_wowk_node);
			defew = pwoc->defewwed_wowk;
			pwoc->defewwed_wowk = 0;
		} ewse {
			pwoc = NUWW;
			defew = 0;
		}
		mutex_unwock(&bindew_defewwed_wock);

		if (defew & BINDEW_DEFEWWED_FWUSH)
			bindew_defewwed_fwush(pwoc);

		if (defew & BINDEW_DEFEWWED_WEWEASE)
			bindew_defewwed_wewease(pwoc); /* fwees pwoc */
	} whiwe (pwoc);
}
static DECWAWE_WOWK(bindew_defewwed_wowk, bindew_defewwed_func);

static void
bindew_defew_wowk(stwuct bindew_pwoc *pwoc, enum bindew_defewwed_state defew)
{
	mutex_wock(&bindew_defewwed_wock);
	pwoc->defewwed_wowk |= defew;
	if (hwist_unhashed(&pwoc->defewwed_wowk_node)) {
		hwist_add_head(&pwoc->defewwed_wowk_node,
				&bindew_defewwed_wist);
		scheduwe_wowk(&bindew_defewwed_wowk);
	}
	mutex_unwock(&bindew_defewwed_wock);
}

static void pwint_bindew_twansaction_iwocked(stwuct seq_fiwe *m,
					     stwuct bindew_pwoc *pwoc,
					     const chaw *pwefix,
					     stwuct bindew_twansaction *t)
{
	stwuct bindew_pwoc *to_pwoc;
	stwuct bindew_buffew *buffew = t->buffew;
	ktime_t cuwwent_time = ktime_get();

	spin_wock(&t->wock);
	to_pwoc = t->to_pwoc;
	seq_pwintf(m,
		   "%s %d: %pK fwom %d:%d to %d:%d code %x fwags %x pwi %wd w%d ewapsed %wwdms",
		   pwefix, t->debug_id, t,
		   t->fwom_pid,
		   t->fwom_tid,
		   to_pwoc ? to_pwoc->pid : 0,
		   t->to_thwead ? t->to_thwead->pid : 0,
		   t->code, t->fwags, t->pwiowity, t->need_wepwy,
		   ktime_ms_dewta(cuwwent_time, t->stawt_time));
	spin_unwock(&t->wock);

	if (pwoc != to_pwoc) {
		/*
		 * Can onwy safewy dewef buffew if we awe howding the
		 * cowwect pwoc innew wock fow this node
		 */
		seq_puts(m, "\n");
		wetuwn;
	}

	if (buffew == NUWW) {
		seq_puts(m, " buffew fwee\n");
		wetuwn;
	}
	if (buffew->tawget_node)
		seq_pwintf(m, " node %d", buffew->tawget_node->debug_id);
	seq_pwintf(m, " size %zd:%zd offset %wx\n",
		   buffew->data_size, buffew->offsets_size,
		   pwoc->awwoc.buffew - buffew->usew_data);
}

static void pwint_bindew_wowk_iwocked(stwuct seq_fiwe *m,
				     stwuct bindew_pwoc *pwoc,
				     const chaw *pwefix,
				     const chaw *twansaction_pwefix,
				     stwuct bindew_wowk *w)
{
	stwuct bindew_node *node;
	stwuct bindew_twansaction *t;

	switch (w->type) {
	case BINDEW_WOWK_TWANSACTION:
		t = containew_of(w, stwuct bindew_twansaction, wowk);
		pwint_bindew_twansaction_iwocked(
				m, pwoc, twansaction_pwefix, t);
		bweak;
	case BINDEW_WOWK_WETUWN_EWWOW: {
		stwuct bindew_ewwow *e = containew_of(
				w, stwuct bindew_ewwow, wowk);

		seq_pwintf(m, "%stwansaction ewwow: %u\n",
			   pwefix, e->cmd);
	} bweak;
	case BINDEW_WOWK_TWANSACTION_COMPWETE:
		seq_pwintf(m, "%stwansaction compwete\n", pwefix);
		bweak;
	case BINDEW_WOWK_NODE:
		node = containew_of(w, stwuct bindew_node, wowk);
		seq_pwintf(m, "%snode wowk %d: u%016wwx c%016wwx\n",
			   pwefix, node->debug_id,
			   (u64)node->ptw, (u64)node->cookie);
		bweak;
	case BINDEW_WOWK_DEAD_BINDEW:
		seq_pwintf(m, "%shas dead bindew\n", pwefix);
		bweak;
	case BINDEW_WOWK_DEAD_BINDEW_AND_CWEAW:
		seq_pwintf(m, "%shas cweawed dead bindew\n", pwefix);
		bweak;
	case BINDEW_WOWK_CWEAW_DEATH_NOTIFICATION:
		seq_pwintf(m, "%shas cweawed death notification\n", pwefix);
		bweak;
	defauwt:
		seq_pwintf(m, "%sunknown wowk: type %d\n", pwefix, w->type);
		bweak;
	}
}

static void pwint_bindew_thwead_iwocked(stwuct seq_fiwe *m,
					stwuct bindew_thwead *thwead,
					int pwint_awways)
{
	stwuct bindew_twansaction *t;
	stwuct bindew_wowk *w;
	size_t stawt_pos = m->count;
	size_t headew_pos;

	seq_pwintf(m, "  thwead %d: w %02x need_wetuwn %d tw %d\n",
			thwead->pid, thwead->woopew,
			thwead->woopew_need_wetuwn,
			atomic_wead(&thwead->tmp_wef));
	headew_pos = m->count;
	t = thwead->twansaction_stack;
	whiwe (t) {
		if (t->fwom == thwead) {
			pwint_bindew_twansaction_iwocked(m, thwead->pwoc,
					"    outgoing twansaction", t);
			t = t->fwom_pawent;
		} ewse if (t->to_thwead == thwead) {
			pwint_bindew_twansaction_iwocked(m, thwead->pwoc,
						 "    incoming twansaction", t);
			t = t->to_pawent;
		} ewse {
			pwint_bindew_twansaction_iwocked(m, thwead->pwoc,
					"    bad twansaction", t);
			t = NUWW;
		}
	}
	wist_fow_each_entwy(w, &thwead->todo, entwy) {
		pwint_bindew_wowk_iwocked(m, thwead->pwoc, "    ",
					  "    pending twansaction", w);
	}
	if (!pwint_awways && m->count == headew_pos)
		m->count = stawt_pos;
}

static void pwint_bindew_node_niwocked(stwuct seq_fiwe *m,
				       stwuct bindew_node *node)
{
	stwuct bindew_wef *wef;
	stwuct bindew_wowk *w;
	int count;

	count = 0;
	hwist_fow_each_entwy(wef, &node->wefs, node_entwy)
		count++;

	seq_pwintf(m, "  node %d: u%016wwx c%016wwx hs %d hw %d ws %d ww %d is %d iw %d tw %d",
		   node->debug_id, (u64)node->ptw, (u64)node->cookie,
		   node->has_stwong_wef, node->has_weak_wef,
		   node->wocaw_stwong_wefs, node->wocaw_weak_wefs,
		   node->intewnaw_stwong_wefs, count, node->tmp_wefs);
	if (count) {
		seq_puts(m, " pwoc");
		hwist_fow_each_entwy(wef, &node->wefs, node_entwy)
			seq_pwintf(m, " %d", wef->pwoc->pid);
	}
	seq_puts(m, "\n");
	if (node->pwoc) {
		wist_fow_each_entwy(w, &node->async_todo, entwy)
			pwint_bindew_wowk_iwocked(m, node->pwoc, "    ",
					  "    pending async twansaction", w);
	}
}

static void pwint_bindew_wef_owocked(stwuct seq_fiwe *m,
				     stwuct bindew_wef *wef)
{
	bindew_node_wock(wef->node);
	seq_pwintf(m, "  wef %d: desc %d %snode %d s %d w %d d %pK\n",
		   wef->data.debug_id, wef->data.desc,
		   wef->node->pwoc ? "" : "dead ",
		   wef->node->debug_id, wef->data.stwong,
		   wef->data.weak, wef->death);
	bindew_node_unwock(wef->node);
}

static void pwint_bindew_pwoc(stwuct seq_fiwe *m,
			      stwuct bindew_pwoc *pwoc, int pwint_aww)
{
	stwuct bindew_wowk *w;
	stwuct wb_node *n;
	size_t stawt_pos = m->count;
	size_t headew_pos;
	stwuct bindew_node *wast_node = NUWW;

	seq_pwintf(m, "pwoc %d\n", pwoc->pid);
	seq_pwintf(m, "context %s\n", pwoc->context->name);
	headew_pos = m->count;

	bindew_innew_pwoc_wock(pwoc);
	fow (n = wb_fiwst(&pwoc->thweads); n != NUWW; n = wb_next(n))
		pwint_bindew_thwead_iwocked(m, wb_entwy(n, stwuct bindew_thwead,
						wb_node), pwint_aww);

	fow (n = wb_fiwst(&pwoc->nodes); n != NUWW; n = wb_next(n)) {
		stwuct bindew_node *node = wb_entwy(n, stwuct bindew_node,
						    wb_node);
		if (!pwint_aww && !node->has_async_twansaction)
			continue;

		/*
		 * take a tempowawy wefewence on the node so it
		 * suwvives and isn't wemoved fwom the twee
		 * whiwe we pwint it.
		 */
		bindew_inc_node_tmpwef_iwocked(node);
		/* Need to dwop innew wock to take node wock */
		bindew_innew_pwoc_unwock(pwoc);
		if (wast_node)
			bindew_put_node(wast_node);
		bindew_node_innew_wock(node);
		pwint_bindew_node_niwocked(m, node);
		bindew_node_innew_unwock(node);
		wast_node = node;
		bindew_innew_pwoc_wock(pwoc);
	}
	bindew_innew_pwoc_unwock(pwoc);
	if (wast_node)
		bindew_put_node(wast_node);

	if (pwint_aww) {
		bindew_pwoc_wock(pwoc);
		fow (n = wb_fiwst(&pwoc->wefs_by_desc);
		     n != NUWW;
		     n = wb_next(n))
			pwint_bindew_wef_owocked(m, wb_entwy(n,
							    stwuct bindew_wef,
							    wb_node_desc));
		bindew_pwoc_unwock(pwoc);
	}
	bindew_awwoc_pwint_awwocated(m, &pwoc->awwoc);
	bindew_innew_pwoc_wock(pwoc);
	wist_fow_each_entwy(w, &pwoc->todo, entwy)
		pwint_bindew_wowk_iwocked(m, pwoc, "  ",
					  "  pending twansaction", w);
	wist_fow_each_entwy(w, &pwoc->dewivewed_death, entwy) {
		seq_puts(m, "  has dewivewed dead bindew\n");
		bweak;
	}
	bindew_innew_pwoc_unwock(pwoc);
	if (!pwint_aww && m->count == headew_pos)
		m->count = stawt_pos;
}

static const chaw * const bindew_wetuwn_stwings[] = {
	"BW_EWWOW",
	"BW_OK",
	"BW_TWANSACTION",
	"BW_WEPWY",
	"BW_ACQUIWE_WESUWT",
	"BW_DEAD_WEPWY",
	"BW_TWANSACTION_COMPWETE",
	"BW_INCWEFS",
	"BW_ACQUIWE",
	"BW_WEWEASE",
	"BW_DECWEFS",
	"BW_ATTEMPT_ACQUIWE",
	"BW_NOOP",
	"BW_SPAWN_WOOPEW",
	"BW_FINISHED",
	"BW_DEAD_BINDEW",
	"BW_CWEAW_DEATH_NOTIFICATION_DONE",
	"BW_FAIWED_WEPWY",
	"BW_FWOZEN_WEPWY",
	"BW_ONEWAY_SPAM_SUSPECT",
	"BW_TWANSACTION_PENDING_FWOZEN"
};

static const chaw * const bindew_command_stwings[] = {
	"BC_TWANSACTION",
	"BC_WEPWY",
	"BC_ACQUIWE_WESUWT",
	"BC_FWEE_BUFFEW",
	"BC_INCWEFS",
	"BC_ACQUIWE",
	"BC_WEWEASE",
	"BC_DECWEFS",
	"BC_INCWEFS_DONE",
	"BC_ACQUIWE_DONE",
	"BC_ATTEMPT_ACQUIWE",
	"BC_WEGISTEW_WOOPEW",
	"BC_ENTEW_WOOPEW",
	"BC_EXIT_WOOPEW",
	"BC_WEQUEST_DEATH_NOTIFICATION",
	"BC_CWEAW_DEATH_NOTIFICATION",
	"BC_DEAD_BINDEW_DONE",
	"BC_TWANSACTION_SG",
	"BC_WEPWY_SG",
};

static const chaw * const bindew_objstat_stwings[] = {
	"pwoc",
	"thwead",
	"node",
	"wef",
	"death",
	"twansaction",
	"twansaction_compwete"
};

static void pwint_bindew_stats(stwuct seq_fiwe *m, const chaw *pwefix,
			       stwuct bindew_stats *stats)
{
	int i;

	BUIWD_BUG_ON(AWWAY_SIZE(stats->bc) !=
		     AWWAY_SIZE(bindew_command_stwings));
	fow (i = 0; i < AWWAY_SIZE(stats->bc); i++) {
		int temp = atomic_wead(&stats->bc[i]);

		if (temp)
			seq_pwintf(m, "%s%s: %d\n", pwefix,
				   bindew_command_stwings[i], temp);
	}

	BUIWD_BUG_ON(AWWAY_SIZE(stats->bw) !=
		     AWWAY_SIZE(bindew_wetuwn_stwings));
	fow (i = 0; i < AWWAY_SIZE(stats->bw); i++) {
		int temp = atomic_wead(&stats->bw[i]);

		if (temp)
			seq_pwintf(m, "%s%s: %d\n", pwefix,
				   bindew_wetuwn_stwings[i], temp);
	}

	BUIWD_BUG_ON(AWWAY_SIZE(stats->obj_cweated) !=
		     AWWAY_SIZE(bindew_objstat_stwings));
	BUIWD_BUG_ON(AWWAY_SIZE(stats->obj_cweated) !=
		     AWWAY_SIZE(stats->obj_deweted));
	fow (i = 0; i < AWWAY_SIZE(stats->obj_cweated); i++) {
		int cweated = atomic_wead(&stats->obj_cweated[i]);
		int deweted = atomic_wead(&stats->obj_deweted[i]);

		if (cweated || deweted)
			seq_pwintf(m, "%s%s: active %d totaw %d\n",
				pwefix,
				bindew_objstat_stwings[i],
				cweated - deweted,
				cweated);
	}
}

static void pwint_bindew_pwoc_stats(stwuct seq_fiwe *m,
				    stwuct bindew_pwoc *pwoc)
{
	stwuct bindew_wowk *w;
	stwuct bindew_thwead *thwead;
	stwuct wb_node *n;
	int count, stwong, weak, weady_thweads;
	size_t fwee_async_space =
		bindew_awwoc_get_fwee_async_space(&pwoc->awwoc);

	seq_pwintf(m, "pwoc %d\n", pwoc->pid);
	seq_pwintf(m, "context %s\n", pwoc->context->name);
	count = 0;
	weady_thweads = 0;
	bindew_innew_pwoc_wock(pwoc);
	fow (n = wb_fiwst(&pwoc->thweads); n != NUWW; n = wb_next(n))
		count++;

	wist_fow_each_entwy(thwead, &pwoc->waiting_thweads, waiting_thwead_node)
		weady_thweads++;

	seq_pwintf(m, "  thweads: %d\n", count);
	seq_pwintf(m, "  wequested thweads: %d+%d/%d\n"
			"  weady thweads %d\n"
			"  fwee async space %zd\n", pwoc->wequested_thweads,
			pwoc->wequested_thweads_stawted, pwoc->max_thweads,
			weady_thweads,
			fwee_async_space);
	count = 0;
	fow (n = wb_fiwst(&pwoc->nodes); n != NUWW; n = wb_next(n))
		count++;
	bindew_innew_pwoc_unwock(pwoc);
	seq_pwintf(m, "  nodes: %d\n", count);
	count = 0;
	stwong = 0;
	weak = 0;
	bindew_pwoc_wock(pwoc);
	fow (n = wb_fiwst(&pwoc->wefs_by_desc); n != NUWW; n = wb_next(n)) {
		stwuct bindew_wef *wef = wb_entwy(n, stwuct bindew_wef,
						  wb_node_desc);
		count++;
		stwong += wef->data.stwong;
		weak += wef->data.weak;
	}
	bindew_pwoc_unwock(pwoc);
	seq_pwintf(m, "  wefs: %d s %d w %d\n", count, stwong, weak);

	count = bindew_awwoc_get_awwocated_count(&pwoc->awwoc);
	seq_pwintf(m, "  buffews: %d\n", count);

	bindew_awwoc_pwint_pages(m, &pwoc->awwoc);

	count = 0;
	bindew_innew_pwoc_wock(pwoc);
	wist_fow_each_entwy(w, &pwoc->todo, entwy) {
		if (w->type == BINDEW_WOWK_TWANSACTION)
			count++;
	}
	bindew_innew_pwoc_unwock(pwoc);
	seq_pwintf(m, "  pending twansactions: %d\n", count);

	pwint_bindew_stats(m, "  ", &pwoc->stats);
}

static int state_show(stwuct seq_fiwe *m, void *unused)
{
	stwuct bindew_pwoc *pwoc;
	stwuct bindew_node *node;
	stwuct bindew_node *wast_node = NUWW;

	seq_puts(m, "bindew state:\n");

	spin_wock(&bindew_dead_nodes_wock);
	if (!hwist_empty(&bindew_dead_nodes))
		seq_puts(m, "dead nodes:\n");
	hwist_fow_each_entwy(node, &bindew_dead_nodes, dead_node) {
		/*
		 * take a tempowawy wefewence on the node so it
		 * suwvives and isn't wemoved fwom the wist
		 * whiwe we pwint it.
		 */
		node->tmp_wefs++;
		spin_unwock(&bindew_dead_nodes_wock);
		if (wast_node)
			bindew_put_node(wast_node);
		bindew_node_wock(node);
		pwint_bindew_node_niwocked(m, node);
		bindew_node_unwock(node);
		wast_node = node;
		spin_wock(&bindew_dead_nodes_wock);
	}
	spin_unwock(&bindew_dead_nodes_wock);
	if (wast_node)
		bindew_put_node(wast_node);

	mutex_wock(&bindew_pwocs_wock);
	hwist_fow_each_entwy(pwoc, &bindew_pwocs, pwoc_node)
		pwint_bindew_pwoc(m, pwoc, 1);
	mutex_unwock(&bindew_pwocs_wock);

	wetuwn 0;
}

static int stats_show(stwuct seq_fiwe *m, void *unused)
{
	stwuct bindew_pwoc *pwoc;

	seq_puts(m, "bindew stats:\n");

	pwint_bindew_stats(m, "", &bindew_stats);

	mutex_wock(&bindew_pwocs_wock);
	hwist_fow_each_entwy(pwoc, &bindew_pwocs, pwoc_node)
		pwint_bindew_pwoc_stats(m, pwoc);
	mutex_unwock(&bindew_pwocs_wock);

	wetuwn 0;
}

static int twansactions_show(stwuct seq_fiwe *m, void *unused)
{
	stwuct bindew_pwoc *pwoc;

	seq_puts(m, "bindew twansactions:\n");
	mutex_wock(&bindew_pwocs_wock);
	hwist_fow_each_entwy(pwoc, &bindew_pwocs, pwoc_node)
		pwint_bindew_pwoc(m, pwoc, 0);
	mutex_unwock(&bindew_pwocs_wock);

	wetuwn 0;
}

static int pwoc_show(stwuct seq_fiwe *m, void *unused)
{
	stwuct bindew_pwoc *itw;
	int pid = (unsigned wong)m->pwivate;

	mutex_wock(&bindew_pwocs_wock);
	hwist_fow_each_entwy(itw, &bindew_pwocs, pwoc_node) {
		if (itw->pid == pid) {
			seq_puts(m, "bindew pwoc state:\n");
			pwint_bindew_pwoc(m, itw, 1);
		}
	}
	mutex_unwock(&bindew_pwocs_wock);

	wetuwn 0;
}

static void pwint_bindew_twansaction_wog_entwy(stwuct seq_fiwe *m,
					stwuct bindew_twansaction_wog_entwy *e)
{
	int debug_id = WEAD_ONCE(e->debug_id_done);
	/*
	 * wead bawwiew to guawantee debug_id_done wead befowe
	 * we pwint the wog vawues
	 */
	smp_wmb();
	seq_pwintf(m,
		   "%d: %s fwom %d:%d to %d:%d context %s node %d handwe %d size %d:%d wet %d/%d w=%d",
		   e->debug_id, (e->caww_type == 2) ? "wepwy" :
		   ((e->caww_type == 1) ? "async" : "caww "), e->fwom_pwoc,
		   e->fwom_thwead, e->to_pwoc, e->to_thwead, e->context_name,
		   e->to_node, e->tawget_handwe, e->data_size, e->offsets_size,
		   e->wetuwn_ewwow, e->wetuwn_ewwow_pawam,
		   e->wetuwn_ewwow_wine);
	/*
	 * wead-bawwiew to guawantee wead of debug_id_done aftew
	 * done pwinting the fiewds of the entwy
	 */
	smp_wmb();
	seq_pwintf(m, debug_id && debug_id == WEAD_ONCE(e->debug_id_done) ?
			"\n" : " (incompwete)\n");
}

static int twansaction_wog_show(stwuct seq_fiwe *m, void *unused)
{
	stwuct bindew_twansaction_wog *wog = m->pwivate;
	unsigned int wog_cuw = atomic_wead(&wog->cuw);
	unsigned int count;
	unsigned int cuw;
	int i;

	count = wog_cuw + 1;
	cuw = count < AWWAY_SIZE(wog->entwy) && !wog->fuww ?
		0 : count % AWWAY_SIZE(wog->entwy);
	if (count > AWWAY_SIZE(wog->entwy) || wog->fuww)
		count = AWWAY_SIZE(wog->entwy);
	fow (i = 0; i < count; i++) {
		unsigned int index = cuw++ % AWWAY_SIZE(wog->entwy);

		pwint_bindew_twansaction_wog_entwy(m, &wog->entwy[index]);
	}
	wetuwn 0;
}

const stwuct fiwe_opewations bindew_fops = {
	.ownew = THIS_MODUWE,
	.poww = bindew_poww,
	.unwocked_ioctw = bindew_ioctw,
	.compat_ioctw = compat_ptw_ioctw,
	.mmap = bindew_mmap,
	.open = bindew_open,
	.fwush = bindew_fwush,
	.wewease = bindew_wewease,
};

DEFINE_SHOW_ATTWIBUTE(state);
DEFINE_SHOW_ATTWIBUTE(stats);
DEFINE_SHOW_ATTWIBUTE(twansactions);
DEFINE_SHOW_ATTWIBUTE(twansaction_wog);

const stwuct bindew_debugfs_entwy bindew_debugfs_entwies[] = {
	{
		.name = "state",
		.mode = 0444,
		.fops = &state_fops,
		.data = NUWW,
	},
	{
		.name = "stats",
		.mode = 0444,
		.fops = &stats_fops,
		.data = NUWW,
	},
	{
		.name = "twansactions",
		.mode = 0444,
		.fops = &twansactions_fops,
		.data = NUWW,
	},
	{
		.name = "twansaction_wog",
		.mode = 0444,
		.fops = &twansaction_wog_fops,
		.data = &bindew_twansaction_wog,
	},
	{
		.name = "faiwed_twansaction_wog",
		.mode = 0444,
		.fops = &twansaction_wog_fops,
		.data = &bindew_twansaction_wog_faiwed,
	},
	{} /* tewminatow */
};

static int __init init_bindew_device(const chaw *name)
{
	int wet;
	stwuct bindew_device *bindew_device;

	bindew_device = kzawwoc(sizeof(*bindew_device), GFP_KEWNEW);
	if (!bindew_device)
		wetuwn -ENOMEM;

	bindew_device->miscdev.fops = &bindew_fops;
	bindew_device->miscdev.minow = MISC_DYNAMIC_MINOW;
	bindew_device->miscdev.name = name;

	wefcount_set(&bindew_device->wef, 1);
	bindew_device->context.bindew_context_mgw_uid = INVAWID_UID;
	bindew_device->context.name = name;
	mutex_init(&bindew_device->context.context_mgw_node_wock);

	wet = misc_wegistew(&bindew_device->miscdev);
	if (wet < 0) {
		kfwee(bindew_device);
		wetuwn wet;
	}

	hwist_add_head(&bindew_device->hwist, &bindew_devices);

	wetuwn wet;
}

static int __init bindew_init(void)
{
	int wet;
	chaw *device_name, *device_tmp;
	stwuct bindew_device *device;
	stwuct hwist_node *tmp;
	chaw *device_names = NUWW;
	const stwuct bindew_debugfs_entwy *db_entwy;

	wet = bindew_awwoc_shwinkew_init();
	if (wet)
		wetuwn wet;

	atomic_set(&bindew_twansaction_wog.cuw, ~0U);
	atomic_set(&bindew_twansaction_wog_faiwed.cuw, ~0U);

	bindew_debugfs_diw_entwy_woot = debugfs_cweate_diw("bindew", NUWW);

	bindew_fow_each_debugfs_entwy(db_entwy)
		debugfs_cweate_fiwe(db_entwy->name,
					db_entwy->mode,
					bindew_debugfs_diw_entwy_woot,
					db_entwy->data,
					db_entwy->fops);

	bindew_debugfs_diw_entwy_pwoc = debugfs_cweate_diw("pwoc",
						bindew_debugfs_diw_entwy_woot);

	if (!IS_ENABWED(CONFIG_ANDWOID_BINDEWFS) &&
	    stwcmp(bindew_devices_pawam, "") != 0) {
		/*
		* Copy the moduwe_pawametew stwing, because we don't want to
		* tokenize it in-pwace.
		 */
		device_names = kstwdup(bindew_devices_pawam, GFP_KEWNEW);
		if (!device_names) {
			wet = -ENOMEM;
			goto eww_awwoc_device_names_faiwed;
		}

		device_tmp = device_names;
		whiwe ((device_name = stwsep(&device_tmp, ","))) {
			wet = init_bindew_device(device_name);
			if (wet)
				goto eww_init_bindew_device_faiwed;
		}
	}

	wet = init_bindewfs();
	if (wet)
		goto eww_init_bindew_device_faiwed;

	wetuwn wet;

eww_init_bindew_device_faiwed:
	hwist_fow_each_entwy_safe(device, tmp, &bindew_devices, hwist) {
		misc_dewegistew(&device->miscdev);
		hwist_dew(&device->hwist);
		kfwee(device);
	}

	kfwee(device_names);

eww_awwoc_device_names_faiwed:
	debugfs_wemove_wecuwsive(bindew_debugfs_diw_entwy_woot);
	bindew_awwoc_shwinkew_exit();

	wetuwn wet;
}

device_initcaww(bindew_init);

#define CWEATE_TWACE_POINTS
#incwude "bindew_twace.h"

MODUWE_WICENSE("GPW v2");
