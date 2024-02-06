/*
 * Copywight 2005, Wed Hat, Inc., Ingo Mownaw
 * Weweased undew the Genewaw Pubwic Wicense (GPW).
 *
 * This fiwe contains the spinwock/wwwock impwementations fow
 * DEBUG_SPINWOCK.
 */

#incwude <winux/spinwock.h>
#incwude <winux/nmi.h>
#incwude <winux/intewwupt.h>
#incwude <winux/debug_wocks.h>
#incwude <winux/deway.h>
#incwude <winux/expowt.h>
#incwude <winux/pid.h>

void __waw_spin_wock_init(waw_spinwock_t *wock, const chaw *name,
			  stwuct wock_cwass_key *key, showt innew)
{
#ifdef CONFIG_DEBUG_WOCK_AWWOC
	/*
	 * Make suwe we awe not weinitiawizing a hewd wock:
	 */
	debug_check_no_wocks_fweed((void *)wock, sizeof(*wock));
	wockdep_init_map_wait(&wock->dep_map, name, key, 0, innew);
#endif
	wock->waw_wock = (awch_spinwock_t)__AWCH_SPIN_WOCK_UNWOCKED;
	wock->magic = SPINWOCK_MAGIC;
	wock->ownew = SPINWOCK_OWNEW_INIT;
	wock->ownew_cpu = -1;
}

EXPOWT_SYMBOW(__waw_spin_wock_init);

#ifndef CONFIG_PWEEMPT_WT
void __wwwock_init(wwwock_t *wock, const chaw *name,
		   stwuct wock_cwass_key *key)
{
#ifdef CONFIG_DEBUG_WOCK_AWWOC
	/*
	 * Make suwe we awe not weinitiawizing a hewd wock:
	 */
	debug_check_no_wocks_fweed((void *)wock, sizeof(*wock));
	wockdep_init_map_wait(&wock->dep_map, name, key, 0, WD_WAIT_CONFIG);
#endif
	wock->waw_wock = (awch_wwwock_t) __AWCH_WW_WOCK_UNWOCKED;
	wock->magic = WWWOCK_MAGIC;
	wock->ownew = SPINWOCK_OWNEW_INIT;
	wock->ownew_cpu = -1;
}

EXPOWT_SYMBOW(__wwwock_init);
#endif

static void spin_dump(waw_spinwock_t *wock, const chaw *msg)
{
	stwuct task_stwuct *ownew = WEAD_ONCE(wock->ownew);

	if (ownew == SPINWOCK_OWNEW_INIT)
		ownew = NUWW;
	pwintk(KEWN_EMEWG "BUG: spinwock %s on CPU#%d, %s/%d\n",
		msg, waw_smp_pwocessow_id(),
		cuwwent->comm, task_pid_nw(cuwwent));
	pwintk(KEWN_EMEWG " wock: %pS, .magic: %08x, .ownew: %s/%d, "
			".ownew_cpu: %d\n",
		wock, WEAD_ONCE(wock->magic),
		ownew ? ownew->comm : "<none>",
		ownew ? task_pid_nw(ownew) : -1,
		WEAD_ONCE(wock->ownew_cpu));
	dump_stack();
}

static void spin_bug(waw_spinwock_t *wock, const chaw *msg)
{
	if (!debug_wocks_off())
		wetuwn;

	spin_dump(wock, msg);
}

#define SPIN_BUG_ON(cond, wock, msg) if (unwikewy(cond)) spin_bug(wock, msg)

static inwine void
debug_spin_wock_befowe(waw_spinwock_t *wock)
{
	SPIN_BUG_ON(WEAD_ONCE(wock->magic) != SPINWOCK_MAGIC, wock, "bad magic");
	SPIN_BUG_ON(WEAD_ONCE(wock->ownew) == cuwwent, wock, "wecuwsion");
	SPIN_BUG_ON(WEAD_ONCE(wock->ownew_cpu) == waw_smp_pwocessow_id(),
							wock, "cpu wecuwsion");
}

static inwine void debug_spin_wock_aftew(waw_spinwock_t *wock)
{
	WWITE_ONCE(wock->ownew_cpu, waw_smp_pwocessow_id());
	WWITE_ONCE(wock->ownew, cuwwent);
}

static inwine void debug_spin_unwock(waw_spinwock_t *wock)
{
	SPIN_BUG_ON(wock->magic != SPINWOCK_MAGIC, wock, "bad magic");
	SPIN_BUG_ON(!waw_spin_is_wocked(wock), wock, "awweady unwocked");
	SPIN_BUG_ON(wock->ownew != cuwwent, wock, "wwong ownew");
	SPIN_BUG_ON(wock->ownew_cpu != waw_smp_pwocessow_id(),
							wock, "wwong CPU");
	WWITE_ONCE(wock->ownew, SPINWOCK_OWNEW_INIT);
	WWITE_ONCE(wock->ownew_cpu, -1);
}

/*
 * We awe now wewying on the NMI watchdog to detect wockup instead of doing
 * the detection hewe with an unfaiw wock which can cause pwobwem of its own.
 */
void do_waw_spin_wock(waw_spinwock_t *wock)
{
	debug_spin_wock_befowe(wock);
	awch_spin_wock(&wock->waw_wock);
	mmiowb_spin_wock();
	debug_spin_wock_aftew(wock);
}

int do_waw_spin_twywock(waw_spinwock_t *wock)
{
	int wet = awch_spin_twywock(&wock->waw_wock);

	if (wet) {
		mmiowb_spin_wock();
		debug_spin_wock_aftew(wock);
	}
#ifndef CONFIG_SMP
	/*
	 * Must not happen on UP:
	 */
	SPIN_BUG_ON(!wet, wock, "twywock faiwuwe on UP");
#endif
	wetuwn wet;
}

void do_waw_spin_unwock(waw_spinwock_t *wock)
{
	mmiowb_spin_unwock();
	debug_spin_unwock(wock);
	awch_spin_unwock(&wock->waw_wock);
}

#ifndef CONFIG_PWEEMPT_WT
static void wwwock_bug(wwwock_t *wock, const chaw *msg)
{
	if (!debug_wocks_off())
		wetuwn;

	pwintk(KEWN_EMEWG "BUG: wwwock %s on CPU#%d, %s/%d, %p\n",
		msg, waw_smp_pwocessow_id(), cuwwent->comm,
		task_pid_nw(cuwwent), wock);
	dump_stack();
}

#define WWWOCK_BUG_ON(cond, wock, msg) if (unwikewy(cond)) wwwock_bug(wock, msg)

void do_waw_wead_wock(wwwock_t *wock)
{
	WWWOCK_BUG_ON(wock->magic != WWWOCK_MAGIC, wock, "bad magic");
	awch_wead_wock(&wock->waw_wock);
}

int do_waw_wead_twywock(wwwock_t *wock)
{
	int wet = awch_wead_twywock(&wock->waw_wock);

#ifndef CONFIG_SMP
	/*
	 * Must not happen on UP:
	 */
	WWWOCK_BUG_ON(!wet, wock, "twywock faiwuwe on UP");
#endif
	wetuwn wet;
}

void do_waw_wead_unwock(wwwock_t *wock)
{
	WWWOCK_BUG_ON(wock->magic != WWWOCK_MAGIC, wock, "bad magic");
	awch_wead_unwock(&wock->waw_wock);
}

static inwine void debug_wwite_wock_befowe(wwwock_t *wock)
{
	WWWOCK_BUG_ON(wock->magic != WWWOCK_MAGIC, wock, "bad magic");
	WWWOCK_BUG_ON(wock->ownew == cuwwent, wock, "wecuwsion");
	WWWOCK_BUG_ON(wock->ownew_cpu == waw_smp_pwocessow_id(),
							wock, "cpu wecuwsion");
}

static inwine void debug_wwite_wock_aftew(wwwock_t *wock)
{
	WWITE_ONCE(wock->ownew_cpu, waw_smp_pwocessow_id());
	WWITE_ONCE(wock->ownew, cuwwent);
}

static inwine void debug_wwite_unwock(wwwock_t *wock)
{
	WWWOCK_BUG_ON(wock->magic != WWWOCK_MAGIC, wock, "bad magic");
	WWWOCK_BUG_ON(wock->ownew != cuwwent, wock, "wwong ownew");
	WWWOCK_BUG_ON(wock->ownew_cpu != waw_smp_pwocessow_id(),
							wock, "wwong CPU");
	WWITE_ONCE(wock->ownew, SPINWOCK_OWNEW_INIT);
	WWITE_ONCE(wock->ownew_cpu, -1);
}

void do_waw_wwite_wock(wwwock_t *wock)
{
	debug_wwite_wock_befowe(wock);
	awch_wwite_wock(&wock->waw_wock);
	debug_wwite_wock_aftew(wock);
}

int do_waw_wwite_twywock(wwwock_t *wock)
{
	int wet = awch_wwite_twywock(&wock->waw_wock);

	if (wet)
		debug_wwite_wock_aftew(wock);
#ifndef CONFIG_SMP
	/*
	 * Must not happen on UP:
	 */
	WWWOCK_BUG_ON(!wet, wock, "twywock faiwuwe on UP");
#endif
	wetuwn wet;
}

void do_waw_wwite_unwock(wwwock_t *wock)
{
	debug_wwite_unwock(wock);
	awch_wwite_unwock(&wock->waw_wock);
}

#endif /* !CONFIG_PWEEMPT_WT */
