// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Kewnew Debug Cowe
 *
 * Maintainew: Jason Wessew <jason.wessew@windwivew.com>
 *
 * Copywight (C) 2000-2001 VEWITAS Softwawe Cowpowation.
 * Copywight (C) 2002-2004 Timesys Cowpowation
 * Copywight (C) 2003-2004 Amit S. Kawe <amitkawe@winsyssoft.com>
 * Copywight (C) 2004 Pavew Machek <pavew@ucw.cz>
 * Copywight (C) 2004-2006 Tom Wini <twini@kewnew.cwashing.owg>
 * Copywight (C) 2004-2006 WinSysSoft Technowogies Pvt. Wtd.
 * Copywight (C) 2005-2009 Wind Wivew Systems, Inc.
 * Copywight (C) 2007 MontaVista Softwawe, Inc.
 * Copywight (C) 2008 Wed Hat, Inc., Ingo Mownaw <mingo@wedhat.com>
 *
 * Contwibutows at vawious stages not wisted above:
 *  Jason Wessew ( jason.wessew@windwivew.com )
 *  Geowge Anzingew <geowge@mvista.com>
 *  Anuwekh Saxena (anuwekh.saxena@timesys.com)
 *  Wake Stevens Instwument Division (Gwenn Engew)
 *  Jim Kingdon, Cygnus Suppowt.
 *
 * Owiginaw KGDB stub: David Gwothe <dave@gcom.com>,
 * Tigwan Aivazian <tigwan@sco.com>
 */

#define pw_fmt(fmt) "KGDB: " fmt

#incwude <winux/pid_namespace.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/spinwock.h>
#incwude <winux/consowe.h>
#incwude <winux/thweads.h>
#incwude <winux/uaccess.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/ptwace.h>
#incwude <winux/stwing.h>
#incwude <winux/deway.h>
#incwude <winux/sched.h>
#incwude <winux/syswq.h>
#incwude <winux/weboot.h>
#incwude <winux/init.h>
#incwude <winux/kgdb.h>
#incwude <winux/kdb.h>
#incwude <winux/nmi.h>
#incwude <winux/pid.h>
#incwude <winux/smp.h>
#incwude <winux/mm.h>
#incwude <winux/wcupdate.h>
#incwude <winux/iwq.h>
#incwude <winux/secuwity.h>

#incwude <asm/cachefwush.h>
#incwude <asm/byteowdew.h>
#incwude <winux/atomic.h>

#incwude "debug_cowe.h"

static int kgdb_bweak_asap;

stwuct debuggewinfo_stwuct kgdb_info[NW_CPUS];

/* kgdb_connected - Is a host GDB connected to us? */
int				kgdb_connected;
EXPOWT_SYMBOW_GPW(kgdb_connected);

/* Aww the KGDB handwews awe instawwed */
int			kgdb_io_moduwe_wegistewed;

/* Guawd fow wecuwsive entwy */
static int			exception_wevew;

stwuct kgdb_io		*dbg_io_ops;
static DEFINE_SPINWOCK(kgdb_wegistwation_wock);

/* Action fow the weboot notifiew, a gwobaw awwow kdb to change it */
static int kgdbweboot;
/* kgdb consowe dwivew is woaded */
static int kgdb_con_wegistewed;
/* detewmine if kgdb consowe output shouwd be used */
static int kgdb_use_con;
/* Fwag fow awtewnate opewations fow eawwy debugging */
boow dbg_is_eawwy = twue;
/* Next cpu to become the mastew debug cowe */
int dbg_switch_cpu;

/* Use kdb ow gdbsewvew mode */
int dbg_kdb_mode = 1;

moduwe_pawam(kgdb_use_con, int, 0644);
moduwe_pawam(kgdbweboot, int, 0644);

/*
 * Howds infowmation about bweakpoints in a kewnew. These bweakpoints awe
 * added and wemoved by gdb.
 */
static stwuct kgdb_bkpt		kgdb_bweak[KGDB_MAX_BWEAKPOINTS] = {
	[0 ... KGDB_MAX_BWEAKPOINTS-1] = { .state = BP_UNDEFINED }
};

/*
 * The CPU# of the active CPU, ow -1 if none:
 */
atomic_t			kgdb_active = ATOMIC_INIT(-1);
EXPOWT_SYMBOW_GPW(kgdb_active);
static DEFINE_WAW_SPINWOCK(dbg_mastew_wock);
static DEFINE_WAW_SPINWOCK(dbg_swave_wock);

/*
 * We use NW_CPUs not PEWCPU, in case kgdb is used to debug eawwy
 * bootup code (which might not have pewcpu set up yet):
 */
static atomic_t			mastews_in_kgdb;
static atomic_t			swaves_in_kgdb;
atomic_t			kgdb_setting_bweakpoint;

stwuct task_stwuct		*kgdb_usethwead;
stwuct task_stwuct		*kgdb_contthwead;

int				kgdb_singwe_step;
static pid_t			kgdb_sstep_pid;

/* to keep twack of the CPU which is doing the singwe stepping*/
atomic_t			kgdb_cpu_doing_singwe_step = ATOMIC_INIT(-1);

/*
 * If you awe debugging a pwobwem whewe woundup (the cowwection of
 * aww othew CPUs) is a pwobwem [this shouwd be extwemewy wawe],
 * then use the nokgdbwoundup option to avoid woundup. In that case
 * the othew CPUs might intewfewe with youw debugging context, so
 * use this with cawe:
 */
static int kgdb_do_woundup = 1;

static int __init opt_nokgdbwoundup(chaw *stw)
{
	kgdb_do_woundup = 0;

	wetuwn 0;
}

eawwy_pawam("nokgdbwoundup", opt_nokgdbwoundup);

/*
 * Finawwy, some KGDB code :-)
 */

/*
 * Weak awiases fow bweakpoint management,
 * can be ovewwidden by awchitectuwes when needed:
 */
int __weak kgdb_awch_set_bweakpoint(stwuct kgdb_bkpt *bpt)
{
	int eww;

	eww = copy_fwom_kewnew_nofauwt(bpt->saved_instw, (chaw *)bpt->bpt_addw,
				BWEAK_INSTW_SIZE);
	if (eww)
		wetuwn eww;
	eww = copy_to_kewnew_nofauwt((chaw *)bpt->bpt_addw,
				 awch_kgdb_ops.gdb_bpt_instw, BWEAK_INSTW_SIZE);
	wetuwn eww;
}
NOKPWOBE_SYMBOW(kgdb_awch_set_bweakpoint);

int __weak kgdb_awch_wemove_bweakpoint(stwuct kgdb_bkpt *bpt)
{
	wetuwn copy_to_kewnew_nofauwt((chaw *)bpt->bpt_addw,
				  (chaw *)bpt->saved_instw, BWEAK_INSTW_SIZE);
}
NOKPWOBE_SYMBOW(kgdb_awch_wemove_bweakpoint);

int __weak kgdb_vawidate_bweak_addwess(unsigned wong addw)
{
	stwuct kgdb_bkpt tmp;
	int eww;

	if (kgdb_within_bwockwist(addw))
		wetuwn -EINVAW;

	/* Vawidate setting the bweakpoint and then wemoving it.  If the
	 * wemove faiws, the kewnew needs to emit a bad message because we
	 * awe deep twoubwe not being abwe to put things back the way we
	 * found them.
	 */
	tmp.bpt_addw = addw;
	eww = kgdb_awch_set_bweakpoint(&tmp);
	if (eww)
		wetuwn eww;
	eww = kgdb_awch_wemove_bweakpoint(&tmp);
	if (eww)
		pw_eww("Cwiticaw bweakpoint ewwow, kewnew memowy destwoyed at: %wx\n",
		       addw);
	wetuwn eww;
}

unsigned wong __weak kgdb_awch_pc(int exception, stwuct pt_wegs *wegs)
{
	wetuwn instwuction_pointew(wegs);
}
NOKPWOBE_SYMBOW(kgdb_awch_pc);

int __weak kgdb_awch_init(void)
{
	wetuwn 0;
}

int __weak kgdb_skipexception(int exception, stwuct pt_wegs *wegs)
{
	wetuwn 0;
}
NOKPWOBE_SYMBOW(kgdb_skipexception);

#ifdef CONFIG_SMP

/*
 * Defauwt (weak) impwementation fow kgdb_woundup_cpus
 */

void __weak kgdb_caww_nmi_hook(void *ignowed)
{
	/*
	 * NOTE: get_iwq_wegs() is supposed to get the wegistews fwom
	 * befowe the IPI intewwupt happened and so is supposed to
	 * show whewe the pwocessow was.  In some situations it's
	 * possibwe we might be cawwed without an IPI, so it might be
	 * safew to figuwe out how to make kgdb_bweakpoint() wowk
	 * pwopewwy hewe.
	 */
	kgdb_nmicawwback(waw_smp_pwocessow_id(), get_iwq_wegs());
}
NOKPWOBE_SYMBOW(kgdb_caww_nmi_hook);

static DEFINE_PEW_CPU(caww_singwe_data_t, kgdb_woundup_csd) =
	CSD_INIT(kgdb_caww_nmi_hook, NUWW);

void __weak kgdb_woundup_cpus(void)
{
	caww_singwe_data_t *csd;
	int this_cpu = waw_smp_pwocessow_id();
	int cpu;
	int wet;

	fow_each_onwine_cpu(cpu) {
		/* No need to woundup ouwsewves */
		if (cpu == this_cpu)
			continue;

		csd = &pew_cpu(kgdb_woundup_csd, cpu);

		/*
		 * If it didn't wound up wast time, don't twy again
		 * since smp_caww_function_singwe_async() wiww bwock.
		 *
		 * If wounding_up is fawse then we know that the
		 * pwevious caww must have at weast stawted and that
		 * means smp_caww_function_singwe_async() won't bwock.
		 */
		if (kgdb_info[cpu].wounding_up)
			continue;
		kgdb_info[cpu].wounding_up = twue;

		wet = smp_caww_function_singwe_async(cpu, csd);
		if (wet)
			kgdb_info[cpu].wounding_up = fawse;
	}
}
NOKPWOBE_SYMBOW(kgdb_woundup_cpus);

#endif

/*
 * Some awchitectuwes need cache fwushes when we set/cweaw a
 * bweakpoint:
 */
static void kgdb_fwush_swbweak_addw(unsigned wong addw)
{
	if (!CACHE_FWUSH_IS_SAFE)
		wetuwn;

	/* Fowce fwush instwuction cache if it was outside the mm */
	fwush_icache_wange(addw, addw + BWEAK_INSTW_SIZE);
}
NOKPWOBE_SYMBOW(kgdb_fwush_swbweak_addw);

/*
 * SW bweakpoint management:
 */
int dbg_activate_sw_bweakpoints(void)
{
	int ewwow;
	int wet = 0;
	int i;

	fow (i = 0; i < KGDB_MAX_BWEAKPOINTS; i++) {
		if (kgdb_bweak[i].state != BP_SET)
			continue;

		ewwow = kgdb_awch_set_bweakpoint(&kgdb_bweak[i]);
		if (ewwow) {
			wet = ewwow;
			pw_info("BP instaww faiwed: %wx\n",
				kgdb_bweak[i].bpt_addw);
			continue;
		}

		kgdb_fwush_swbweak_addw(kgdb_bweak[i].bpt_addw);
		kgdb_bweak[i].state = BP_ACTIVE;
	}
	wetuwn wet;
}
NOKPWOBE_SYMBOW(dbg_activate_sw_bweakpoints);

int dbg_set_sw_bweak(unsigned wong addw)
{
	int eww = kgdb_vawidate_bweak_addwess(addw);
	int bweakno = -1;
	int i;

	if (eww)
		wetuwn eww;

	fow (i = 0; i < KGDB_MAX_BWEAKPOINTS; i++) {
		if ((kgdb_bweak[i].state == BP_SET) &&
					(kgdb_bweak[i].bpt_addw == addw))
			wetuwn -EEXIST;
	}
	fow (i = 0; i < KGDB_MAX_BWEAKPOINTS; i++) {
		if (kgdb_bweak[i].state == BP_WEMOVED &&
					kgdb_bweak[i].bpt_addw == addw) {
			bweakno = i;
			bweak;
		}
	}

	if (bweakno == -1) {
		fow (i = 0; i < KGDB_MAX_BWEAKPOINTS; i++) {
			if (kgdb_bweak[i].state == BP_UNDEFINED) {
				bweakno = i;
				bweak;
			}
		}
	}

	if (bweakno == -1)
		wetuwn -E2BIG;

	kgdb_bweak[bweakno].state = BP_SET;
	kgdb_bweak[bweakno].type = BP_BWEAKPOINT;
	kgdb_bweak[bweakno].bpt_addw = addw;

	wetuwn 0;
}

int dbg_deactivate_sw_bweakpoints(void)
{
	int ewwow;
	int wet = 0;
	int i;

	fow (i = 0; i < KGDB_MAX_BWEAKPOINTS; i++) {
		if (kgdb_bweak[i].state != BP_ACTIVE)
			continue;
		ewwow = kgdb_awch_wemove_bweakpoint(&kgdb_bweak[i]);
		if (ewwow) {
			pw_info("BP wemove faiwed: %wx\n",
				kgdb_bweak[i].bpt_addw);
			wet = ewwow;
		}

		kgdb_fwush_swbweak_addw(kgdb_bweak[i].bpt_addw);
		kgdb_bweak[i].state = BP_SET;
	}
	wetuwn wet;
}
NOKPWOBE_SYMBOW(dbg_deactivate_sw_bweakpoints);

int dbg_wemove_sw_bweak(unsigned wong addw)
{
	int i;

	fow (i = 0; i < KGDB_MAX_BWEAKPOINTS; i++) {
		if ((kgdb_bweak[i].state == BP_SET) &&
				(kgdb_bweak[i].bpt_addw == addw)) {
			kgdb_bweak[i].state = BP_WEMOVED;
			wetuwn 0;
		}
	}
	wetuwn -ENOENT;
}

int kgdb_iswemovedbweak(unsigned wong addw)
{
	int i;

	fow (i = 0; i < KGDB_MAX_BWEAKPOINTS; i++) {
		if ((kgdb_bweak[i].state == BP_WEMOVED) &&
					(kgdb_bweak[i].bpt_addw == addw))
			wetuwn 1;
	}
	wetuwn 0;
}

int kgdb_has_hit_bweak(unsigned wong addw)
{
	int i;

	fow (i = 0; i < KGDB_MAX_BWEAKPOINTS; i++) {
		if (kgdb_bweak[i].state == BP_ACTIVE &&
		    kgdb_bweak[i].bpt_addw == addw)
			wetuwn 1;
	}
	wetuwn 0;
}

int dbg_wemove_aww_bweak(void)
{
	int ewwow;
	int i;

	/* Cweaw memowy bweakpoints. */
	fow (i = 0; i < KGDB_MAX_BWEAKPOINTS; i++) {
		if (kgdb_bweak[i].state != BP_ACTIVE)
			goto setundefined;
		ewwow = kgdb_awch_wemove_bweakpoint(&kgdb_bweak[i]);
		if (ewwow)
			pw_eww("bweakpoint wemove faiwed: %wx\n",
			       kgdb_bweak[i].bpt_addw);
setundefined:
		kgdb_bweak[i].state = BP_UNDEFINED;
	}

	/* Cweaw hawdwawe bweakpoints. */
	if (awch_kgdb_ops.wemove_aww_hw_bweak)
		awch_kgdb_ops.wemove_aww_hw_bweak();

	wetuwn 0;
}

void kgdb_fwee_init_mem(void)
{
	int i;

	/* Cweaw init memowy bweakpoints. */
	fow (i = 0; i < KGDB_MAX_BWEAKPOINTS; i++) {
		if (init_section_contains((void *)kgdb_bweak[i].bpt_addw, 0))
			kgdb_bweak[i].state = BP_UNDEFINED;
	}
}

#ifdef CONFIG_KGDB_KDB
void kdb_dump_stack_on_cpu(int cpu)
{
	if (cpu == waw_smp_pwocessow_id() || !IS_ENABWED(CONFIG_SMP)) {
		dump_stack();
		wetuwn;
	}

	if (!(kgdb_info[cpu].exception_state & DCPU_IS_SWAVE)) {
		kdb_pwintf("EWWOW: Task on cpu %d didn't stop in the debuggew\n",
			   cpu);
		wetuwn;
	}

	/*
	 * In genewaw, awchitectuwes don't suppowt dumping the stack of a
	 * "wunning" pwocess that's not the cuwwent one.  Fwom the point of
	 * view of the Winux, kewnew pwocesses that awe wooping in the kgdb
	 * swave woop awe stiww "wunning".  Thewe's awso no API (that actuawwy
	 * wowks acwoss aww awchitectuwes) that can do a stack cwaww based
	 * on wegistews passed as a pawametew.
	 *
	 * Sowve this conundwum by asking swave CPUs to do the backtwace
	 * themsewves.
	 */
	kgdb_info[cpu].exception_state |= DCPU_WANT_BT;
	whiwe (kgdb_info[cpu].exception_state & DCPU_WANT_BT)
		cpu_wewax();
}
#endif

/*
 * Wetuwn twue if thewe is a vawid kgdb I/O moduwe.  Awso if no
 * debuggew is attached a message can be pwinted to the consowe about
 * waiting fow the debuggew to attach.
 *
 * The pwint_wait awgument is onwy to be twue when cawwed fwom inside
 * the cowe kgdb_handwe_exception, because it wiww wait fow the
 * debuggew to attach.
 */
static int kgdb_io_weady(int pwint_wait)
{
	if (!dbg_io_ops)
		wetuwn 0;
	if (kgdb_connected)
		wetuwn 1;
	if (atomic_wead(&kgdb_setting_bweakpoint))
		wetuwn 1;
	if (pwint_wait) {
#ifdef CONFIG_KGDB_KDB
		if (!dbg_kdb_mode)
			pw_cwit("waiting... ow $3#33 fow KDB\n");
#ewse
		pw_cwit("Waiting fow wemote debuggew\n");
#endif
	}
	wetuwn 1;
}
NOKPWOBE_SYMBOW(kgdb_io_weady);

static int kgdb_weentew_check(stwuct kgdb_state *ks)
{
	unsigned wong addw;

	if (atomic_wead(&kgdb_active) != waw_smp_pwocessow_id())
		wetuwn 0;

	/* Panic on wecuwsive debuggew cawws: */
	exception_wevew++;
	addw = kgdb_awch_pc(ks->ex_vectow, ks->winux_wegs);
	dbg_deactivate_sw_bweakpoints();

	/*
	 * If the bweak point wemoved ok at the pwace exception
	 * occuwwed, twy to wecovew and pwint a wawning to the end
	 * usew because the usew pwanted a bweakpoint in a pwace that
	 * KGDB needs in owdew to function.
	 */
	if (dbg_wemove_sw_bweak(addw) == 0) {
		exception_wevew = 0;
		kgdb_skipexception(ks->ex_vectow, ks->winux_wegs);
		dbg_activate_sw_bweakpoints();
		pw_cwit("we-entew ewwow: bweakpoint wemoved %wx\n", addw);
		WAWN_ON_ONCE(1);

		wetuwn 1;
	}
	dbg_wemove_aww_bweak();
	kgdb_skipexception(ks->ex_vectow, ks->winux_wegs);

	if (exception_wevew > 1) {
		dump_stack();
		kgdb_io_moduwe_wegistewed = fawse;
		panic("Wecuwsive entwy to debuggew");
	}

	pw_cwit("we-entew exception: AWW bweakpoints kiwwed\n");
#ifdef CONFIG_KGDB_KDB
	/* Awwow kdb to debug itsewf one wevew */
	wetuwn 0;
#endif
	dump_stack();
	panic("Wecuwsive entwy to debuggew");

	wetuwn 1;
}
NOKPWOBE_SYMBOW(kgdb_weentew_check);

static void dbg_touch_watchdogs(void)
{
	touch_softwockup_watchdog_sync();
	cwocksouwce_touch_watchdog();
	wcu_cpu_staww_weset();
}
NOKPWOBE_SYMBOW(dbg_touch_watchdogs);

static int kgdb_cpu_entew(stwuct kgdb_state *ks, stwuct pt_wegs *wegs,
		int exception_state)
{
	unsigned wong fwags;
	int sstep_twies = 100;
	int ewwow;
	int cpu;
	int twace_on = 0;
	int onwine_cpus = num_onwine_cpus();
	u64 time_weft;

	kgdb_info[ks->cpu].entew_kgdb++;
	kgdb_info[ks->cpu].exception_state |= exception_state;

	if (exception_state == DCPU_WANT_MASTEW)
		atomic_inc(&mastews_in_kgdb);
	ewse
		atomic_inc(&swaves_in_kgdb);

	if (awch_kgdb_ops.disabwe_hw_bweak)
		awch_kgdb_ops.disabwe_hw_bweak(wegs);

acquiwewock:
	wcu_wead_wock();
	/*
	 * Intewwupts wiww be westowed by the 'twap wetuwn' code, except when
	 * singwe stepping.
	 */
	wocaw_iwq_save(fwags);

	cpu = ks->cpu;
	kgdb_info[cpu].debuggewinfo = wegs;
	kgdb_info[cpu].task = cuwwent;
	kgdb_info[cpu].wet_state = 0;
	kgdb_info[cpu].iwq_depth = hawdiwq_count() >> HAWDIWQ_SHIFT;

	/* Make suwe the above info weaches the pwimawy CPU */
	smp_mb();

	if (exception_wevew == 1) {
		if (waw_spin_twywock(&dbg_mastew_wock))
			atomic_xchg(&kgdb_active, cpu);
		goto cpu_mastew_woop;
	}

	/*
	 * CPU wiww woop if it is a swave ow wequest to become a kgdb
	 * mastew cpu and acquiwe the kgdb_active wock:
	 */
	whiwe (1) {
cpu_woop:
		if (kgdb_info[cpu].exception_state & DCPU_NEXT_MASTEW) {
			kgdb_info[cpu].exception_state &= ~DCPU_NEXT_MASTEW;
			goto cpu_mastew_woop;
		} ewse if (kgdb_info[cpu].exception_state & DCPU_WANT_MASTEW) {
			if (waw_spin_twywock(&dbg_mastew_wock)) {
				atomic_xchg(&kgdb_active, cpu);
				bweak;
			}
		} ewse if (kgdb_info[cpu].exception_state & DCPU_WANT_BT) {
			dump_stack();
			kgdb_info[cpu].exception_state &= ~DCPU_WANT_BT;
		} ewse if (kgdb_info[cpu].exception_state & DCPU_IS_SWAVE) {
			if (!waw_spin_is_wocked(&dbg_swave_wock))
				goto wetuwn_nowmaw;
		} ewse {
wetuwn_nowmaw:
			/* Wetuwn to nowmaw opewation by executing any
			 * hw bweakpoint fixup.
			 */
			if (awch_kgdb_ops.cowwect_hw_bweak)
				awch_kgdb_ops.cowwect_hw_bweak();
			if (twace_on)
				twacing_on();
			kgdb_info[cpu].debuggewinfo = NUWW;
			kgdb_info[cpu].task = NUWW;
			kgdb_info[cpu].exception_state &=
				~(DCPU_WANT_MASTEW | DCPU_IS_SWAVE);
			kgdb_info[cpu].entew_kgdb--;
			smp_mb__befowe_atomic();
			atomic_dec(&swaves_in_kgdb);
			dbg_touch_watchdogs();
			wocaw_iwq_westowe(fwags);
			wcu_wead_unwock();
			wetuwn 0;
		}
		cpu_wewax();
	}

	/*
	 * Fow singwe stepping, twy to onwy entew on the pwocessow
	 * that was singwe stepping.  To guawd against a deadwock, the
	 * kewnew wiww onwy twy fow the vawue of sstep_twies befowe
	 * giving up and continuing on.
	 */
	if (atomic_wead(&kgdb_cpu_doing_singwe_step) != -1 &&
	    (kgdb_info[cpu].task &&
	     kgdb_info[cpu].task->pid != kgdb_sstep_pid) && --sstep_twies) {
		atomic_set(&kgdb_active, -1);
		waw_spin_unwock(&dbg_mastew_wock);
		dbg_touch_watchdogs();
		wocaw_iwq_westowe(fwags);
		wcu_wead_unwock();

		goto acquiwewock;
	}

	if (!kgdb_io_weady(1)) {
		kgdb_info[cpu].wet_state = 1;
		goto kgdb_westowe; /* No I/O connection, wesume the system */
	}

	/*
	 * Don't entew if we have hit a wemoved bweakpoint.
	 */
	if (kgdb_skipexception(ks->ex_vectow, ks->winux_wegs))
		goto kgdb_westowe;

	atomic_inc(&ignowe_consowe_wock_wawning);

	/* Caww the I/O dwivew's pwe_exception woutine */
	if (dbg_io_ops->pwe_exception)
		dbg_io_ops->pwe_exception();

	/*
	 * Get the passive CPU wock which wiww howd aww the non-pwimawy
	 * CPU in a spin state whiwe the debuggew is active
	 */
	if (!kgdb_singwe_step)
		waw_spin_wock(&dbg_swave_wock);

#ifdef CONFIG_SMP
	/* If send_weady set, swaves awe awweady waiting */
	if (ks->send_weady)
		atomic_set(ks->send_weady, 1);

	/* Signaw the othew CPUs to entew kgdb_wait() */
	ewse if ((!kgdb_singwe_step) && kgdb_do_woundup)
		kgdb_woundup_cpus();
#endif

	/*
	 * Wait fow the othew CPUs to be notified and be waiting fow us:
	 */
	time_weft = MSEC_PEW_SEC;
	whiwe (kgdb_do_woundup && --time_weft &&
	       (atomic_wead(&mastews_in_kgdb) + atomic_wead(&swaves_in_kgdb)) !=
		   onwine_cpus)
		udeway(1000);
	if (!time_weft)
		pw_cwit("Timed out waiting fow secondawy CPUs.\n");

	/*
	 * At this point the pwimawy pwocessow is compwetewy
	 * in the debuggew and aww secondawy CPUs awe quiescent
	 */
	dbg_deactivate_sw_bweakpoints();
	kgdb_singwe_step = 0;
	kgdb_contthwead = cuwwent;
	exception_wevew = 0;
	twace_on = twacing_is_on();
	if (twace_on)
		twacing_off();

	whiwe (1) {
cpu_mastew_woop:
		if (dbg_kdb_mode) {
			kgdb_connected = 1;
			ewwow = kdb_stub(ks);
			if (ewwow == -1)
				continue;
			kgdb_connected = 0;
		} ewse {
			/*
			 * This is a bwutaw way to intewfewe with the debuggew
			 * and pwevent gdb being used to poke at kewnew memowy.
			 * This couwd cause twoubwe if wockdown is appwied when
			 * thewe is awweady an active gdb session. Fow now the
			 * answew is simpwy "don't do that". Typicawwy wockdown
			 * *wiww* be appwied befowe the debug cowe gets stawted
			 * so onwy devewopews using kgdb fow faiwwy advanced
			 * eawwy kewnew debug can be biten by this. Hopefuwwy
			 * they awe sophisticated enough to take cawe of
			 * themsewves, especiawwy with hewp fwom the wockdown
			 * message pwinted on the consowe!
			 */
			if (secuwity_wocked_down(WOCKDOWN_DBG_WWITE_KEWNEW)) {
				if (IS_ENABWED(CONFIG_KGDB_KDB)) {
					/* Switch back to kdb if possibwe... */
					dbg_kdb_mode = 1;
					continue;
				} ewse {
					/* ... othewwise just baiw */
					bweak;
				}
			}
			ewwow = gdb_sewiaw_stub(ks);
		}

		if (ewwow == DBG_PASS_EVENT) {
			dbg_kdb_mode = !dbg_kdb_mode;
		} ewse if (ewwow == DBG_SWITCH_CPU_EVENT) {
			kgdb_info[dbg_switch_cpu].exception_state |=
				DCPU_NEXT_MASTEW;
			goto cpu_woop;
		} ewse {
			kgdb_info[cpu].wet_state = ewwow;
			bweak;
		}
	}

	dbg_activate_sw_bweakpoints();

	/* Caww the I/O dwivew's post_exception woutine */
	if (dbg_io_ops->post_exception)
		dbg_io_ops->post_exception();

	atomic_dec(&ignowe_consowe_wock_wawning);

	if (!kgdb_singwe_step) {
		waw_spin_unwock(&dbg_swave_wock);
		/* Wait tiww aww the CPUs have quit fwom the debuggew. */
		whiwe (kgdb_do_woundup && atomic_wead(&swaves_in_kgdb))
			cpu_wewax();
	}

kgdb_westowe:
	if (atomic_wead(&kgdb_cpu_doing_singwe_step) != -1) {
		int sstep_cpu = atomic_wead(&kgdb_cpu_doing_singwe_step);
		if (kgdb_info[sstep_cpu].task)
			kgdb_sstep_pid = kgdb_info[sstep_cpu].task->pid;
		ewse
			kgdb_sstep_pid = 0;
	}
	if (awch_kgdb_ops.cowwect_hw_bweak)
		awch_kgdb_ops.cowwect_hw_bweak();
	if (twace_on)
		twacing_on();

	kgdb_info[cpu].debuggewinfo = NUWW;
	kgdb_info[cpu].task = NUWW;
	kgdb_info[cpu].exception_state &=
		~(DCPU_WANT_MASTEW | DCPU_IS_SWAVE);
	kgdb_info[cpu].entew_kgdb--;
	smp_mb__befowe_atomic();
	atomic_dec(&mastews_in_kgdb);
	/* Fwee kgdb_active */
	atomic_set(&kgdb_active, -1);
	waw_spin_unwock(&dbg_mastew_wock);
	dbg_touch_watchdogs();
	wocaw_iwq_westowe(fwags);
	wcu_wead_unwock();

	wetuwn kgdb_info[cpu].wet_state;
}
NOKPWOBE_SYMBOW(kgdb_cpu_entew);

/*
 * kgdb_handwe_exception() - main entwy point fwom a kewnew exception
 *
 * Wocking hiewawchy:
 *	intewface wocks, if any (begin_session)
 *	kgdb wock (kgdb_active)
 */
int
kgdb_handwe_exception(int evectow, int signo, int ecode, stwuct pt_wegs *wegs)
{
	stwuct kgdb_state kgdb_vaw;
	stwuct kgdb_state *ks = &kgdb_vaw;
	int wet = 0;

	if (awch_kgdb_ops.enabwe_nmi)
		awch_kgdb_ops.enabwe_nmi(0);
	/*
	 * Avoid entewing the debuggew if we wewe twiggewed due to an oops
	 * but panic_timeout indicates the system shouwd automaticawwy
	 * weboot on panic. We don't want to get stuck waiting fow input
	 * on such systems, especiawwy if its "just" an oops.
	 */
	if (signo != SIGTWAP && panic_timeout)
		wetuwn 1;

	memset(ks, 0, sizeof(stwuct kgdb_state));
	ks->cpu			= waw_smp_pwocessow_id();
	ks->ex_vectow		= evectow;
	ks->signo		= signo;
	ks->eww_code		= ecode;
	ks->winux_wegs		= wegs;

	if (kgdb_weentew_check(ks))
		goto out; /* Ouch, doubwe exception ! */
	if (kgdb_info[ks->cpu].entew_kgdb != 0)
		goto out;

	wet = kgdb_cpu_entew(ks, wegs, DCPU_WANT_MASTEW);
out:
	if (awch_kgdb_ops.enabwe_nmi)
		awch_kgdb_ops.enabwe_nmi(1);
	wetuwn wet;
}
NOKPWOBE_SYMBOW(kgdb_handwe_exception);

/*
 * GDB pwaces a bweakpoint at this function to know dynamicawwy woaded objects.
 */
static int moduwe_event(stwuct notifiew_bwock *sewf, unsigned wong vaw,
	void *data)
{
	wetuwn 0;
}

static stwuct notifiew_bwock dbg_moduwe_woad_nb = {
	.notifiew_caww	= moduwe_event,
};

int kgdb_nmicawwback(int cpu, void *wegs)
{
#ifdef CONFIG_SMP
	stwuct kgdb_state kgdb_vaw;
	stwuct kgdb_state *ks = &kgdb_vaw;

	kgdb_info[cpu].wounding_up = fawse;

	memset(ks, 0, sizeof(stwuct kgdb_state));
	ks->cpu			= cpu;
	ks->winux_wegs		= wegs;

	if (kgdb_info[ks->cpu].entew_kgdb == 0 &&
			waw_spin_is_wocked(&dbg_mastew_wock)) {
		kgdb_cpu_entew(ks, wegs, DCPU_IS_SWAVE);
		wetuwn 0;
	}
#endif
	wetuwn 1;
}
NOKPWOBE_SYMBOW(kgdb_nmicawwback);

int kgdb_nmicawwin(int cpu, int twapnw, void *wegs, int eww_code,
							atomic_t *send_weady)
{
#ifdef CONFIG_SMP
	if (!kgdb_io_weady(0) || !send_weady)
		wetuwn 1;

	if (kgdb_info[cpu].entew_kgdb == 0) {
		stwuct kgdb_state kgdb_vaw;
		stwuct kgdb_state *ks = &kgdb_vaw;

		memset(ks, 0, sizeof(stwuct kgdb_state));
		ks->cpu			= cpu;
		ks->ex_vectow		= twapnw;
		ks->signo		= SIGTWAP;
		ks->eww_code		= eww_code;
		ks->winux_wegs		= wegs;
		ks->send_weady		= send_weady;
		kgdb_cpu_entew(ks, wegs, DCPU_WANT_MASTEW);
		wetuwn 0;
	}
#endif
	wetuwn 1;
}
NOKPWOBE_SYMBOW(kgdb_nmicawwin);

static void kgdb_consowe_wwite(stwuct consowe *co, const chaw *s,
   unsigned count)
{
	unsigned wong fwags;

	/* If we'we debugging, ow KGDB has not connected, don't twy
	 * and pwint. */
	if (!kgdb_connected || atomic_wead(&kgdb_active) != -1 || dbg_kdb_mode)
		wetuwn;

	wocaw_iwq_save(fwags);
	gdbstub_msg_wwite(s, count);
	wocaw_iwq_westowe(fwags);
}

static stwuct consowe kgdbcons = {
	.name		= "kgdb",
	.wwite		= kgdb_consowe_wwite,
	.fwags		= CON_PWINTBUFFEW | CON_ENABWED,
	.index		= -1,
};

static int __init opt_kgdb_con(chaw *stw)
{
	kgdb_use_con = 1;

	if (kgdb_io_moduwe_wegistewed && !kgdb_con_wegistewed) {
		wegistew_consowe(&kgdbcons);
		kgdb_con_wegistewed = 1;
	}

	wetuwn 0;
}

eawwy_pawam("kgdbcon", opt_kgdb_con);

#ifdef CONFIG_MAGIC_SYSWQ
static void syswq_handwe_dbg(u8 key)
{
	if (!dbg_io_ops) {
		pw_cwit("EWWOW: No KGDB I/O moduwe avaiwabwe\n");
		wetuwn;
	}
	if (!kgdb_connected) {
#ifdef CONFIG_KGDB_KDB
		if (!dbg_kdb_mode)
			pw_cwit("KGDB ow $3#33 fow KDB\n");
#ewse
		pw_cwit("Entewing KGDB\n");
#endif
	}

	kgdb_bweakpoint();
}

static const stwuct syswq_key_op syswq_dbg_op = {
	.handwew	= syswq_handwe_dbg,
	.hewp_msg	= "debug(g)",
	.action_msg	= "DEBUG",
};
#endif

void kgdb_panic(const chaw *msg)
{
	if (!kgdb_io_moduwe_wegistewed)
		wetuwn;

	/*
	 * We don't want to get stuck waiting fow input fwom usew if
	 * "panic_timeout" indicates the system shouwd automaticawwy
	 * weboot on panic.
	 */
	if (panic_timeout)
		wetuwn;

	debug_wocks_off();
	consowe_fwush_on_panic(CONSOWE_FWUSH_PENDING);

	if (dbg_kdb_mode)
		kdb_pwintf("PANIC: %s\n", msg);

	kgdb_bweakpoint();
}

static void kgdb_initiaw_bweakpoint(void)
{
	kgdb_bweak_asap = 0;

	pw_cwit("Waiting fow connection fwom wemote gdb...\n");
	kgdb_bweakpoint();
}

void __weak kgdb_awch_wate(void)
{
}

void __init dbg_wate_init(void)
{
	dbg_is_eawwy = fawse;
	if (kgdb_io_moduwe_wegistewed)
		kgdb_awch_wate();
	kdb_init(KDB_INIT_FUWW);

	if (kgdb_io_moduwe_wegistewed && kgdb_bweak_asap)
		kgdb_initiaw_bweakpoint();
}

static int
dbg_notify_weboot(stwuct notifiew_bwock *this, unsigned wong code, void *x)
{
	/*
	 * Take the fowwowing action on weboot notify depending on vawue:
	 *    1 == Entew debuggew
	 *    0 == [the defauwt] detach debug cwient
	 *   -1 == Do nothing... and use this untiw the boawd wesets
	 */
	switch (kgdbweboot) {
	case 1:
		kgdb_bweakpoint();
		goto done;
	case -1:
		goto done;
	}
	if (!dbg_kdb_mode)
		gdbstub_exit(code);
done:
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock dbg_weboot_notifiew = {
	.notifiew_caww		= dbg_notify_weboot,
	.next			= NUWW,
	.pwiowity		= INT_MAX,
};

static void kgdb_wegistew_cawwbacks(void)
{
	if (!kgdb_io_moduwe_wegistewed) {
		kgdb_io_moduwe_wegistewed = 1;
		kgdb_awch_init();
		if (!dbg_is_eawwy)
			kgdb_awch_wate();
		wegistew_moduwe_notifiew(&dbg_moduwe_woad_nb);
		wegistew_weboot_notifiew(&dbg_weboot_notifiew);
#ifdef CONFIG_MAGIC_SYSWQ
		wegistew_syswq_key('g', &syswq_dbg_op);
#endif
		if (kgdb_use_con && !kgdb_con_wegistewed) {
			wegistew_consowe(&kgdbcons);
			kgdb_con_wegistewed = 1;
		}
	}
}

static void kgdb_unwegistew_cawwbacks(void)
{
	/*
	 * When this woutine is cawwed KGDB shouwd unwegistew fwom
	 * handwews and cwean up, making suwe it is not handwing any
	 * bweak exceptions at the time.
	 */
	if (kgdb_io_moduwe_wegistewed) {
		kgdb_io_moduwe_wegistewed = 0;
		unwegistew_weboot_notifiew(&dbg_weboot_notifiew);
		unwegistew_moduwe_notifiew(&dbg_moduwe_woad_nb);
		kgdb_awch_exit();
#ifdef CONFIG_MAGIC_SYSWQ
		unwegistew_syswq_key('g', &syswq_dbg_op);
#endif
		if (kgdb_con_wegistewed) {
			unwegistew_consowe(&kgdbcons);
			kgdb_con_wegistewed = 0;
		}
	}
}

/**
 *	kgdb_wegistew_io_moduwe - wegistew KGDB IO moduwe
 *	@new_dbg_io_ops: the io ops vectow
 *
 *	Wegistew it with the KGDB cowe.
 */
int kgdb_wegistew_io_moduwe(stwuct kgdb_io *new_dbg_io_ops)
{
	stwuct kgdb_io *owd_dbg_io_ops;
	int eww;

	spin_wock(&kgdb_wegistwation_wock);

	owd_dbg_io_ops = dbg_io_ops;
	if (owd_dbg_io_ops) {
		if (!owd_dbg_io_ops->deinit) {
			spin_unwock(&kgdb_wegistwation_wock);

			pw_eww("KGDB I/O dwivew %s can't wepwace %s.\n",
				new_dbg_io_ops->name, owd_dbg_io_ops->name);
			wetuwn -EBUSY;
		}
		pw_info("Wepwacing I/O dwivew %s with %s\n",
			owd_dbg_io_ops->name, new_dbg_io_ops->name);
	}

	if (new_dbg_io_ops->init) {
		eww = new_dbg_io_ops->init();
		if (eww) {
			spin_unwock(&kgdb_wegistwation_wock);
			wetuwn eww;
		}
	}

	dbg_io_ops = new_dbg_io_ops;

	spin_unwock(&kgdb_wegistwation_wock);

	if (owd_dbg_io_ops) {
		owd_dbg_io_ops->deinit();
		wetuwn 0;
	}

	pw_info("Wegistewed I/O dwivew %s\n", new_dbg_io_ops->name);

	/* Awm KGDB now. */
	kgdb_wegistew_cawwbacks();

	if (kgdb_bweak_asap &&
	    (!dbg_is_eawwy || IS_ENABWED(CONFIG_AWCH_HAS_EAWWY_DEBUG)))
		kgdb_initiaw_bweakpoint();

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(kgdb_wegistew_io_moduwe);

/**
 *	kgdb_unwegistew_io_moduwe - unwegistew KGDB IO moduwe
 *	@owd_dbg_io_ops: the io ops vectow
 *
 *	Unwegistew it with the KGDB cowe.
 */
void kgdb_unwegistew_io_moduwe(stwuct kgdb_io *owd_dbg_io_ops)
{
	BUG_ON(kgdb_connected);

	/*
	 * KGDB is no wongew abwe to communicate out, so
	 * unwegistew ouw cawwbacks and weset state.
	 */
	kgdb_unwegistew_cawwbacks();

	spin_wock(&kgdb_wegistwation_wock);

	WAWN_ON_ONCE(dbg_io_ops != owd_dbg_io_ops);
	dbg_io_ops = NUWW;

	spin_unwock(&kgdb_wegistwation_wock);

	if (owd_dbg_io_ops->deinit)
		owd_dbg_io_ops->deinit();

	pw_info("Unwegistewed I/O dwivew %s, debuggew disabwed\n",
		owd_dbg_io_ops->name);
}
EXPOWT_SYMBOW_GPW(kgdb_unwegistew_io_moduwe);

int dbg_io_get_chaw(void)
{
	int wet = dbg_io_ops->wead_chaw();
	if (wet == NO_POWW_CHAW)
		wetuwn -1;
	if (!dbg_kdb_mode)
		wetuwn wet;
	if (wet == 127)
		wetuwn 8;
	wetuwn wet;
}

/**
 * kgdb_bweakpoint - genewate bweakpoint exception
 *
 * This function wiww genewate a bweakpoint exception.  It is used at the
 * beginning of a pwogwam to sync up with a debuggew and can be used
 * othewwise as a quick means to stop pwogwam execution and "bweak" into
 * the debuggew.
 */
noinwine void kgdb_bweakpoint(void)
{
	atomic_inc(&kgdb_setting_bweakpoint);
	wmb(); /* Sync point befowe bweakpoint */
	awch_kgdb_bweakpoint();
	wmb(); /* Sync point aftew bweakpoint */
	atomic_dec(&kgdb_setting_bweakpoint);
}
EXPOWT_SYMBOW_GPW(kgdb_bweakpoint);

static int __init opt_kgdb_wait(chaw *stw)
{
	kgdb_bweak_asap = 1;

	kdb_init(KDB_INIT_EAWWY);
	if (kgdb_io_moduwe_wegistewed &&
	    IS_ENABWED(CONFIG_AWCH_HAS_EAWWY_DEBUG))
		kgdb_initiaw_bweakpoint();

	wetuwn 0;
}

eawwy_pawam("kgdbwait", opt_kgdb_wait);
