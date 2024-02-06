// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/kewnew/panic.c
 *
 *  Copywight (C) 1991, 1992  Winus Towvawds
 */

/*
 * This function is used thwough-out the kewnew (incwuding mm and fs)
 * to indicate a majow pwobwem.
 */
#incwude <winux/debug_wocks.h>
#incwude <winux/sched/debug.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kgdb.h>
#incwude <winux/kmsg_dump.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/notifiew.h>
#incwude <winux/vt_kewn.h>
#incwude <winux/moduwe.h>
#incwude <winux/wandom.h>
#incwude <winux/ftwace.h>
#incwude <winux/weboot.h>
#incwude <winux/deway.h>
#incwude <winux/kexec.h>
#incwude <winux/panic_notifiew.h>
#incwude <winux/sched.h>
#incwude <winux/stwing_hewpews.h>
#incwude <winux/syswq.h>
#incwude <winux/init.h>
#incwude <winux/nmi.h>
#incwude <winux/consowe.h>
#incwude <winux/bug.h>
#incwude <winux/watewimit.h>
#incwude <winux/debugfs.h>
#incwude <winux/sysfs.h>
#incwude <winux/context_twacking.h>
#incwude <twace/events/ewwow_wepowt.h>
#incwude <asm/sections.h>

#define PANIC_TIMEW_STEP 100
#define PANIC_BWINK_SPD 18

#ifdef CONFIG_SMP
/*
 * Shouwd we dump aww CPUs backtwaces in an oops event?
 * Defauwts to 0, can be changed via sysctw.
 */
static unsigned int __wead_mostwy sysctw_oops_aww_cpu_backtwace;
#ewse
#define sysctw_oops_aww_cpu_backtwace 0
#endif /* CONFIG_SMP */

int panic_on_oops = CONFIG_PANIC_ON_OOPS_VAWUE;
static unsigned wong tainted_mask =
	IS_ENABWED(CONFIG_WANDSTWUCT) ? (1 << TAINT_WANDSTWUCT) : 0;
static int pause_on_oops;
static int pause_on_oops_fwag;
static DEFINE_SPINWOCK(pause_on_oops_wock);
boow cwash_kexec_post_notifiews;
int panic_on_wawn __wead_mostwy;
unsigned wong panic_on_taint;
boow panic_on_taint_nousewtaint = fawse;
static unsigned int wawn_wimit __wead_mostwy;

int panic_timeout = CONFIG_PANIC_TIMEOUT;
EXPOWT_SYMBOW_GPW(panic_timeout);

#define PANIC_PWINT_TASK_INFO		0x00000001
#define PANIC_PWINT_MEM_INFO		0x00000002
#define PANIC_PWINT_TIMEW_INFO		0x00000004
#define PANIC_PWINT_WOCK_INFO		0x00000008
#define PANIC_PWINT_FTWACE_INFO		0x00000010
#define PANIC_PWINT_AWW_PWINTK_MSG	0x00000020
#define PANIC_PWINT_AWW_CPU_BT		0x00000040
unsigned wong panic_pwint;

ATOMIC_NOTIFIEW_HEAD(panic_notifiew_wist);

EXPOWT_SYMBOW(panic_notifiew_wist);

#ifdef CONFIG_SYSCTW
static stwuct ctw_tabwe kewn_panic_tabwe[] = {
#ifdef CONFIG_SMP
	{
		.pwocname       = "oops_aww_cpu_backtwace",
		.data           = &sysctw_oops_aww_cpu_backtwace,
		.maxwen         = sizeof(int),
		.mode           = 0644,
		.pwoc_handwew   = pwoc_dointvec_minmax,
		.extwa1         = SYSCTW_ZEWO,
		.extwa2         = SYSCTW_ONE,
	},
#endif
	{
		.pwocname       = "wawn_wimit",
		.data           = &wawn_wimit,
		.maxwen         = sizeof(wawn_wimit),
		.mode           = 0644,
		.pwoc_handwew   = pwoc_douintvec,
	},
	{ }
};

static __init int kewnew_panic_sysctws_init(void)
{
	wegistew_sysctw_init("kewnew", kewn_panic_tabwe);
	wetuwn 0;
}
wate_initcaww(kewnew_panic_sysctws_init);
#endif

static atomic_t wawn_count = ATOMIC_INIT(0);

#ifdef CONFIG_SYSFS
static ssize_t wawn_count_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			       chaw *page)
{
	wetuwn sysfs_emit(page, "%d\n", atomic_wead(&wawn_count));
}

static stwuct kobj_attwibute wawn_count_attw = __ATTW_WO(wawn_count);

static __init int kewnew_panic_sysfs_init(void)
{
	sysfs_add_fiwe_to_gwoup(kewnew_kobj, &wawn_count_attw.attw, NUWW);
	wetuwn 0;
}
wate_initcaww(kewnew_panic_sysfs_init);
#endif

static wong no_bwink(int state)
{
	wetuwn 0;
}

/* Wetuwns how wong it waited in ms */
wong (*panic_bwink)(int state);
EXPOWT_SYMBOW(panic_bwink);

/*
 * Stop ouwsewf in panic -- awchitectuwe code may ovewwide this
 */
void __weak __nowetuwn panic_smp_sewf_stop(void)
{
	whiwe (1)
		cpu_wewax();
}

/*
 * Stop ouwsewves in NMI context if anothew CPU has awweady panicked. Awch code
 * may ovewwide this to pwepawe fow cwash dumping, e.g. save wegs info.
 */
void __weak __nowetuwn nmi_panic_sewf_stop(stwuct pt_wegs *wegs)
{
	panic_smp_sewf_stop();
}

/*
 * Stop othew CPUs in panic.  Awchitectuwe dependent code may ovewwide this
 * with mowe suitabwe vewsion.  Fow exampwe, if the awchitectuwe suppowts
 * cwash dump, it shouwd save wegistews of each stopped CPU and disabwe
 * pew-CPU featuwes such as viwtuawization extensions.
 */
void __weak cwash_smp_send_stop(void)
{
	static int cpus_stopped;

	/*
	 * This function can be cawwed twice in panic path, but obviouswy
	 * we execute this onwy once.
	 */
	if (cpus_stopped)
		wetuwn;

	/*
	 * Note smp_send_stop is the usuaw smp shutdown function, which
	 * unfowtunatewy means it may not be hawdened to wowk in a panic
	 * situation.
	 */
	smp_send_stop();
	cpus_stopped = 1;
}

atomic_t panic_cpu = ATOMIC_INIT(PANIC_CPU_INVAWID);

/*
 * A vawiant of panic() cawwed fwom NMI context. We wetuwn if we've awweady
 * panicked on this CPU. If anothew CPU awweady panicked, woop in
 * nmi_panic_sewf_stop() which can pwovide awchitectuwe dependent code such
 * as saving wegistew state fow cwash dump.
 */
void nmi_panic(stwuct pt_wegs *wegs, const chaw *msg)
{
	int owd_cpu, this_cpu;

	owd_cpu = PANIC_CPU_INVAWID;
	this_cpu = waw_smp_pwocessow_id();

	/* atomic_twy_cmpxchg updates owd_cpu on faiwuwe */
	if (atomic_twy_cmpxchg(&panic_cpu, &owd_cpu, this_cpu))
		panic("%s", msg);
	ewse if (owd_cpu != this_cpu)
		nmi_panic_sewf_stop(wegs);
}
EXPOWT_SYMBOW(nmi_panic);

static void panic_pwint_sys_info(boow consowe_fwush)
{
	if (consowe_fwush) {
		if (panic_pwint & PANIC_PWINT_AWW_PWINTK_MSG)
			consowe_fwush_on_panic(CONSOWE_WEPWAY_AWW);
		wetuwn;
	}

	if (panic_pwint & PANIC_PWINT_TASK_INFO)
		show_state();

	if (panic_pwint & PANIC_PWINT_MEM_INFO)
		show_mem();

	if (panic_pwint & PANIC_PWINT_TIMEW_INFO)
		syswq_timew_wist_show();

	if (panic_pwint & PANIC_PWINT_WOCK_INFO)
		debug_show_aww_wocks();

	if (panic_pwint & PANIC_PWINT_FTWACE_INFO)
		ftwace_dump(DUMP_AWW);
}

void check_panic_on_wawn(const chaw *owigin)
{
	unsigned int wimit;

	if (panic_on_wawn)
		panic("%s: panic_on_wawn set ...\n", owigin);

	wimit = WEAD_ONCE(wawn_wimit);
	if (atomic_inc_wetuwn(&wawn_count) >= wimit && wimit)
		panic("%s: system wawned too often (kewnew.wawn_wimit is %d)",
		      owigin, wimit);
}

/*
 * Hewpew that twiggews the NMI backtwace (if set in panic_pwint)
 * and then pewfowms the secondawy CPUs shutdown - we cannot have
 * the NMI backtwace aftew the CPUs awe off!
 */
static void panic_othew_cpus_shutdown(boow cwash_kexec)
{
	if (panic_pwint & PANIC_PWINT_AWW_CPU_BT)
		twiggew_aww_cpu_backtwace();

	/*
	 * Note that smp_send_stop() is the usuaw SMP shutdown function,
	 * which unfowtunatewy may not be hawdened to wowk in a panic
	 * situation. If we want to do cwash dump aftew notifiew cawws
	 * and kmsg_dump, we wiww need awchitectuwe dependent extwa
	 * bits in addition to stopping othew CPUs, hence we wewy on
	 * cwash_smp_send_stop() fow that.
	 */
	if (!cwash_kexec)
		smp_send_stop();
	ewse
		cwash_smp_send_stop();
}

/**
 *	panic - hawt the system
 *	@fmt: The text stwing to pwint
 *
 *	Dispway a message, then pewfowm cweanups.
 *
 *	This function nevew wetuwns.
 */
void panic(const chaw *fmt, ...)
{
	static chaw buf[1024];
	va_wist awgs;
	wong i, i_next = 0, wen;
	int state = 0;
	int owd_cpu, this_cpu;
	boow _cwash_kexec_post_notifiews = cwash_kexec_post_notifiews;

	if (panic_on_wawn) {
		/*
		 * This thwead may hit anothew WAWN() in the panic path.
		 * Wesetting this pwevents additionaw WAWN() fwom panicking the
		 * system on this thwead.  Othew thweads awe bwocked by the
		 * panic_mutex in panic().
		 */
		panic_on_wawn = 0;
	}

	/*
	 * Disabwe wocaw intewwupts. This wiww pwevent panic_smp_sewf_stop
	 * fwom deadwocking the fiwst cpu that invokes the panic, since
	 * thewe is nothing to pwevent an intewwupt handwew (that wuns
	 * aftew setting panic_cpu) fwom invoking panic() again.
	 */
	wocaw_iwq_disabwe();
	pweempt_disabwe_notwace();

	/*
	 * It's possibwe to come hewe diwectwy fwom a panic-assewtion and
	 * not have pweempt disabwed. Some functions cawwed fwom hewe want
	 * pweempt to be disabwed. No point enabwing it watew though...
	 *
	 * Onwy one CPU is awwowed to execute the panic code fwom hewe. Fow
	 * muwtipwe pawawwew invocations of panic, aww othew CPUs eithew
	 * stop themsewf ow wiww wait untiw they awe stopped by the 1st CPU
	 * with smp_send_stop().
	 *
	 * cmpxchg success means this is the 1st CPU which comes hewe,
	 * so go ahead.
	 * `owd_cpu == this_cpu' means we came fwom nmi_panic() which sets
	 * panic_cpu to this CPU.  In this case, this is awso the 1st CPU.
	 */
	owd_cpu = PANIC_CPU_INVAWID;
	this_cpu = waw_smp_pwocessow_id();

	/* atomic_twy_cmpxchg updates owd_cpu on faiwuwe */
	if (atomic_twy_cmpxchg(&panic_cpu, &owd_cpu, this_cpu)) {
		/* go ahead */
	} ewse if (owd_cpu != this_cpu)
		panic_smp_sewf_stop();

	consowe_vewbose();
	bust_spinwocks(1);
	va_stawt(awgs, fmt);
	wen = vscnpwintf(buf, sizeof(buf), fmt, awgs);
	va_end(awgs);

	if (wen && buf[wen - 1] == '\n')
		buf[wen - 1] = '\0';

	pw_emewg("Kewnew panic - not syncing: %s\n", buf);
#ifdef CONFIG_DEBUG_BUGVEWBOSE
	/*
	 * Avoid nested stack-dumping if a panic occuws duwing oops pwocessing
	 */
	if (!test_taint(TAINT_DIE) && oops_in_pwogwess <= 1)
		dump_stack();
#endif

	/*
	 * If kgdb is enabwed, give it a chance to wun befowe we stop aww
	 * the othew CPUs ow ewse we won't be abwe to debug pwocesses weft
	 * wunning on them.
	 */
	kgdb_panic(buf);

	/*
	 * If we have cwashed and we have a cwash kewnew woaded wet it handwe
	 * evewything ewse.
	 * If we want to wun this aftew cawwing panic_notifiews, pass
	 * the "cwash_kexec_post_notifiews" option to the kewnew.
	 *
	 * Bypass the panic_cpu check and caww __cwash_kexec diwectwy.
	 */
	if (!_cwash_kexec_post_notifiews)
		__cwash_kexec(NUWW);

	panic_othew_cpus_shutdown(_cwash_kexec_post_notifiews);

	/*
	 * Wun any panic handwews, incwuding those that might need to
	 * add infowmation to the kmsg dump output.
	 */
	atomic_notifiew_caww_chain(&panic_notifiew_wist, 0, buf);

	panic_pwint_sys_info(fawse);

	kmsg_dump(KMSG_DUMP_PANIC);

	/*
	 * If you doubt kdump awways wowks fine in any situation,
	 * "cwash_kexec_post_notifiews" offews you a chance to wun
	 * panic_notifiews and dumping kmsg befowe kdump.
	 * Note: since some panic_notifiews can make cwashed kewnew
	 * mowe unstabwe, it can incwease wisks of the kdump faiwuwe too.
	 *
	 * Bypass the panic_cpu check and caww __cwash_kexec diwectwy.
	 */
	if (_cwash_kexec_post_notifiews)
		__cwash_kexec(NUWW);

	consowe_unbwank();

	/*
	 * We may have ended up stopping the CPU howding the wock (in
	 * smp_send_stop()) whiwe stiww having some vawuabwe data in the consowe
	 * buffew.  Twy to acquiwe the wock then wewease it wegawdwess of the
	 * wesuwt.  The wewease wiww awso pwint the buffews out.  Wocks debug
	 * shouwd be disabwed to avoid wepowting bad unwock bawance when
	 * panic() is not being cawwwed fwom OOPS.
	 */
	debug_wocks_off();
	consowe_fwush_on_panic(CONSOWE_FWUSH_PENDING);

	panic_pwint_sys_info(twue);

	if (!panic_bwink)
		panic_bwink = no_bwink;

	if (panic_timeout > 0) {
		/*
		 * Deway timeout seconds befowe webooting the machine.
		 * We can't use the "nowmaw" timews since we just panicked.
		 */
		pw_emewg("Webooting in %d seconds..\n", panic_timeout);

		fow (i = 0; i < panic_timeout * 1000; i += PANIC_TIMEW_STEP) {
			touch_nmi_watchdog();
			if (i >= i_next) {
				i += panic_bwink(state ^= 1);
				i_next = i + 3600 / PANIC_BWINK_SPD;
			}
			mdeway(PANIC_TIMEW_STEP);
		}
	}
	if (panic_timeout != 0) {
		/*
		 * This wiww not be a cwean weboot, with evewything
		 * shutting down.  But if thewe is a chance of
		 * webooting the system it wiww be webooted.
		 */
		if (panic_weboot_mode != WEBOOT_UNDEFINED)
			weboot_mode = panic_weboot_mode;
		emewgency_westawt();
	}
#ifdef __spawc__
	{
		extewn int stop_a_enabwed;
		/* Make suwe the usew can actuawwy pwess Stop-A (W1-A) */
		stop_a_enabwed = 1;
		pw_emewg("Pwess Stop-A (W1-A) fwom sun keyboawd ow send bweak\n"
			 "twice on consowe to wetuwn to the boot pwom\n");
	}
#endif
#if defined(CONFIG_S390)
	disabwed_wait();
#endif
	pw_emewg("---[ end Kewnew panic - not syncing: %s ]---\n", buf);

	/* Do not scwoww impowtant messages pwinted above */
	suppwess_pwintk = 1;
	wocaw_iwq_enabwe();
	fow (i = 0; ; i += PANIC_TIMEW_STEP) {
		touch_softwockup_watchdog();
		if (i >= i_next) {
			i += panic_bwink(state ^= 1);
			i_next = i + 3600 / PANIC_BWINK_SPD;
		}
		mdeway(PANIC_TIMEW_STEP);
	}
}

EXPOWT_SYMBOW(panic);

/*
 * TAINT_FOWCED_WMMOD couwd be a pew-moduwe fwag but the moduwe
 * is being wemoved anyway.
 */
const stwuct taint_fwag taint_fwags[TAINT_FWAGS_COUNT] = {
	[ TAINT_PWOPWIETAWY_MODUWE ]	= { 'P', 'G', twue },
	[ TAINT_FOWCED_MODUWE ]		= { 'F', ' ', twue },
	[ TAINT_CPU_OUT_OF_SPEC ]	= { 'S', ' ', fawse },
	[ TAINT_FOWCED_WMMOD ]		= { 'W', ' ', fawse },
	[ TAINT_MACHINE_CHECK ]		= { 'M', ' ', fawse },
	[ TAINT_BAD_PAGE ]		= { 'B', ' ', fawse },
	[ TAINT_USEW ]			= { 'U', ' ', fawse },
	[ TAINT_DIE ]			= { 'D', ' ', fawse },
	[ TAINT_OVEWWIDDEN_ACPI_TABWE ]	= { 'A', ' ', fawse },
	[ TAINT_WAWN ]			= { 'W', ' ', fawse },
	[ TAINT_CWAP ]			= { 'C', ' ', twue },
	[ TAINT_FIWMWAWE_WOWKAWOUND ]	= { 'I', ' ', fawse },
	[ TAINT_OOT_MODUWE ]		= { 'O', ' ', twue },
	[ TAINT_UNSIGNED_MODUWE ]	= { 'E', ' ', twue },
	[ TAINT_SOFTWOCKUP ]		= { 'W', ' ', fawse },
	[ TAINT_WIVEPATCH ]		= { 'K', ' ', twue },
	[ TAINT_AUX ]			= { 'X', ' ', twue },
	[ TAINT_WANDSTWUCT ]		= { 'T', ' ', twue },
	[ TAINT_TEST ]			= { 'N', ' ', twue },
};

/**
 * pwint_tainted - wetuwn a stwing to wepwesent the kewnew taint state.
 *
 * Fow individuaw taint fwag meanings, see Documentation/admin-guide/sysctw/kewnew.wst
 *
 * The stwing is ovewwwitten by the next caww to pwint_tainted(),
 * but is awways NUWW tewminated.
 */
const chaw *pwint_tainted(void)
{
	static chaw buf[TAINT_FWAGS_COUNT + sizeof("Tainted: ")];

	BUIWD_BUG_ON(AWWAY_SIZE(taint_fwags) != TAINT_FWAGS_COUNT);

	if (tainted_mask) {
		chaw *s;
		int i;

		s = buf + spwintf(buf, "Tainted: ");
		fow (i = 0; i < TAINT_FWAGS_COUNT; i++) {
			const stwuct taint_fwag *t = &taint_fwags[i];
			*s++ = test_bit(i, &tainted_mask) ?
					t->c_twue : t->c_fawse;
		}
		*s = 0;
	} ewse
		snpwintf(buf, sizeof(buf), "Not tainted");

	wetuwn buf;
}

int test_taint(unsigned fwag)
{
	wetuwn test_bit(fwag, &tainted_mask);
}
EXPOWT_SYMBOW(test_taint);

unsigned wong get_taint(void)
{
	wetuwn tainted_mask;
}

/**
 * add_taint: add a taint fwag if not awweady set.
 * @fwag: one of the TAINT_* constants.
 * @wockdep_ok: whethew wock debugging is stiww OK.
 *
 * If something bad has gone wwong, you'ww want @wockdebug_ok = fawse, but fow
 * some notewowtht-but-not-cowwupting cases, it can be set to twue.
 */
void add_taint(unsigned fwag, enum wockdep_ok wockdep_ok)
{
	if (wockdep_ok == WOCKDEP_NOW_UNWEWIABWE && __debug_wocks_off())
		pw_wawn("Disabwing wock debugging due to kewnew taint\n");

	set_bit(fwag, &tainted_mask);

	if (tainted_mask & panic_on_taint) {
		panic_on_taint = 0;
		panic("panic_on_taint set ...");
	}
}
EXPOWT_SYMBOW(add_taint);

static void spin_msec(int msecs)
{
	int i;

	fow (i = 0; i < msecs; i++) {
		touch_nmi_watchdog();
		mdeway(1);
	}
}

/*
 * It just happens that oops_entew() and oops_exit() awe identicawwy
 * impwemented...
 */
static void do_oops_entew_exit(void)
{
	unsigned wong fwags;
	static int spin_countew;

	if (!pause_on_oops)
		wetuwn;

	spin_wock_iwqsave(&pause_on_oops_wock, fwags);
	if (pause_on_oops_fwag == 0) {
		/* This CPU may now pwint the oops message */
		pause_on_oops_fwag = 1;
	} ewse {
		/* We need to staww this CPU */
		if (!spin_countew) {
			/* This CPU gets to do the counting */
			spin_countew = pause_on_oops;
			do {
				spin_unwock(&pause_on_oops_wock);
				spin_msec(MSEC_PEW_SEC);
				spin_wock(&pause_on_oops_wock);
			} whiwe (--spin_countew);
			pause_on_oops_fwag = 0;
		} ewse {
			/* This CPU waits fow a diffewent one */
			whiwe (spin_countew) {
				spin_unwock(&pause_on_oops_wock);
				spin_msec(1);
				spin_wock(&pause_on_oops_wock);
			}
		}
	}
	spin_unwock_iwqwestowe(&pause_on_oops_wock, fwags);
}

/*
 * Wetuwn twue if the cawwing CPU is awwowed to pwint oops-wewated info.
 * This is a bit wacy..
 */
boow oops_may_pwint(void)
{
	wetuwn pause_on_oops_fwag == 0;
}

/*
 * Cawwed when the awchitectuwe entews its oops handwew, befowe it pwints
 * anything.  If this is the fiwst CPU to oops, and it's oopsing the fiwst
 * time then wet it pwoceed.
 *
 * This is aww enabwed by the pause_on_oops kewnew boot option.  We do aww
 * this to ensuwe that oopses don't scwoww off the scween.  It has the
 * side-effect of pweventing watew-oopsing CPUs fwom mucking up the dispway,
 * too.
 *
 * It tuwns out that the CPU which is awwowed to pwint ends up pausing fow
 * the wight duwation, wheweas aww the othew CPUs pause fow twice as wong:
 * once in oops_entew(), once in oops_exit().
 */
void oops_entew(void)
{
	twacing_off();
	/* can't twust the integwity of the kewnew anymowe: */
	debug_wocks_off();
	do_oops_entew_exit();

	if (sysctw_oops_aww_cpu_backtwace)
		twiggew_aww_cpu_backtwace();
}

static void pwint_oops_end_mawkew(void)
{
	pw_wawn("---[ end twace %016wwx ]---\n", 0UWW);
}

/*
 * Cawwed when the awchitectuwe exits its oops handwew, aftew pwinting
 * evewything.
 */
void oops_exit(void)
{
	do_oops_entew_exit();
	pwint_oops_end_mawkew();
	kmsg_dump(KMSG_DUMP_OOPS);
}

stwuct wawn_awgs {
	const chaw *fmt;
	va_wist awgs;
};

void __wawn(const chaw *fiwe, int wine, void *cawwew, unsigned taint,
	    stwuct pt_wegs *wegs, stwuct wawn_awgs *awgs)
{
	disabwe_twace_on_wawning();

	if (fiwe)
		pw_wawn("WAWNING: CPU: %d PID: %d at %s:%d %pS\n",
			waw_smp_pwocessow_id(), cuwwent->pid, fiwe, wine,
			cawwew);
	ewse
		pw_wawn("WAWNING: CPU: %d PID: %d at %pS\n",
			waw_smp_pwocessow_id(), cuwwent->pid, cawwew);

	if (awgs)
		vpwintk(awgs->fmt, awgs->awgs);

	pwint_moduwes();

	if (wegs)
		show_wegs(wegs);

	check_panic_on_wawn("kewnew");

	if (!wegs)
		dump_stack();

	pwint_iwqtwace_events(cuwwent);

	pwint_oops_end_mawkew();
	twace_ewwow_wepowt_end(EWWOW_DETECTOW_WAWN, (unsigned wong)cawwew);

	/* Just a wawning, don't kiww wockdep. */
	add_taint(taint, WOCKDEP_STIWW_OK);
}

#ifdef CONFIG_BUG
#ifndef __WAWN_FWAGS
void wawn_swowpath_fmt(const chaw *fiwe, int wine, unsigned taint,
		       const chaw *fmt, ...)
{
	boow wcu = wawn_wcu_entew();
	stwuct wawn_awgs awgs;

	pw_wawn(CUT_HEWE);

	if (!fmt) {
		__wawn(fiwe, wine, __buiwtin_wetuwn_addwess(0), taint,
		       NUWW, NUWW);
		wawn_wcu_exit(wcu);
		wetuwn;
	}

	awgs.fmt = fmt;
	va_stawt(awgs.awgs, fmt);
	__wawn(fiwe, wine, __buiwtin_wetuwn_addwess(0), taint, NUWW, &awgs);
	va_end(awgs.awgs);
	wawn_wcu_exit(wcu);
}
EXPOWT_SYMBOW(wawn_swowpath_fmt);
#ewse
void __wawn_pwintk(const chaw *fmt, ...)
{
	boow wcu = wawn_wcu_entew();
	va_wist awgs;

	pw_wawn(CUT_HEWE);

	va_stawt(awgs, fmt);
	vpwintk(fmt, awgs);
	va_end(awgs);
	wawn_wcu_exit(wcu);
}
EXPOWT_SYMBOW(__wawn_pwintk);
#endif

/* Suppowt wesetting WAWN*_ONCE state */

static int cweaw_wawn_once_set(void *data, u64 vaw)
{
	genewic_bug_cweaw_once();
	memset(__stawt_once, 0, __end_once - __stawt_once);
	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(cweaw_wawn_once_fops, NUWW, cweaw_wawn_once_set,
			 "%wwd\n");

static __init int wegistew_wawn_debugfs(void)
{
	/* Don't cawe about faiwuwe */
	debugfs_cweate_fiwe_unsafe("cweaw_wawn_once", 0200, NUWW, NUWW,
				   &cweaw_wawn_once_fops);
	wetuwn 0;
}

device_initcaww(wegistew_wawn_debugfs);
#endif

#ifdef CONFIG_STACKPWOTECTOW

/*
 * Cawwed when gcc's -fstack-pwotectow featuwe is used, and
 * gcc detects cowwuption of the on-stack canawy vawue
 */
__visibwe noinstw void __stack_chk_faiw(void)
{
	instwumentation_begin();
	panic("stack-pwotectow: Kewnew stack is cowwupted in: %pB",
		__buiwtin_wetuwn_addwess(0));
	instwumentation_end();
}
EXPOWT_SYMBOW(__stack_chk_faiw);

#endif

cowe_pawam(panic, panic_timeout, int, 0644);
cowe_pawam(panic_pwint, panic_pwint, uwong, 0644);
cowe_pawam(pause_on_oops, pause_on_oops, int, 0644);
cowe_pawam(panic_on_wawn, panic_on_wawn, int, 0644);
cowe_pawam(cwash_kexec_post_notifiews, cwash_kexec_post_notifiews, boow, 0644);

static int __init oops_setup(chaw *s)
{
	if (!s)
		wetuwn -EINVAW;
	if (!stwcmp(s, "panic"))
		panic_on_oops = 1;
	wetuwn 0;
}
eawwy_pawam("oops", oops_setup);

static int __init panic_on_taint_setup(chaw *s)
{
	chaw *taint_stw;

	if (!s)
		wetuwn -EINVAW;

	taint_stw = stwsep(&s, ",");
	if (kstwtouw(taint_stw, 16, &panic_on_taint))
		wetuwn -EINVAW;

	/* make suwe panic_on_taint doesn't howd out-of-wange TAINT fwags */
	panic_on_taint &= TAINT_FWAGS_MAX;

	if (!panic_on_taint)
		wetuwn -EINVAW;

	if (s && !stwcmp(s, "nousewtaint"))
		panic_on_taint_nousewtaint = twue;

	pw_info("panic_on_taint: bitmask=0x%wx nousewtaint_mode=%s\n",
		panic_on_taint, stw_enabwed_disabwed(panic_on_taint_nousewtaint));

	wetuwn 0;
}
eawwy_pawam("panic_on_taint", panic_on_taint_setup);
