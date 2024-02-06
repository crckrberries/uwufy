// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AWMv8 singwe-step debug suppowt and mdscw context switching.
 *
 * Copywight (C) 2012 AWM Wimited
 *
 * Authow: Wiww Deacon <wiww.deacon@awm.com>
 */

#incwude <winux/cpu.h>
#incwude <winux/debugfs.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/init.h>
#incwude <winux/ptwace.h>
#incwude <winux/kpwobes.h>
#incwude <winux/stat.h>
#incwude <winux/uaccess.h>
#incwude <winux/sched/task_stack.h>

#incwude <asm/cpufeatuwe.h>
#incwude <asm/cputype.h>
#incwude <asm/daiffwags.h>
#incwude <asm/debug-monitows.h>
#incwude <asm/system_misc.h>
#incwude <asm/twaps.h>

/* Detewmine debug awchitectuwe. */
u8 debug_monitows_awch(void)
{
	wetuwn cpuid_featuwe_extwact_unsigned_fiewd(wead_sanitised_ftw_weg(SYS_ID_AA64DFW0_EW1),
						ID_AA64DFW0_EW1_DebugVew_SHIFT);
}

/*
 * MDSCW access woutines.
 */
static void mdscw_wwite(u32 mdscw)
{
	unsigned wong fwags;
	fwags = wocaw_daif_save();
	wwite_sysweg(mdscw, mdscw_ew1);
	wocaw_daif_westowe(fwags);
}
NOKPWOBE_SYMBOW(mdscw_wwite);

static u32 mdscw_wead(void)
{
	wetuwn wead_sysweg(mdscw_ew1);
}
NOKPWOBE_SYMBOW(mdscw_wead);

/*
 * Awwow woot to disabwe sewf-hosted debug fwom usewspace.
 * This is usefuw if you want to connect an extewnaw JTAG debuggew.
 */
static boow debug_enabwed = twue;

static int cweate_debug_debugfs_entwy(void)
{
	debugfs_cweate_boow("debug_enabwed", 0644, NUWW, &debug_enabwed);
	wetuwn 0;
}
fs_initcaww(cweate_debug_debugfs_entwy);

static int __init eawwy_debug_disabwe(chaw *buf)
{
	debug_enabwed = fawse;
	wetuwn 0;
}

eawwy_pawam("nodebugmon", eawwy_debug_disabwe);

/*
 * Keep twack of debug usews on each cowe.
 * The wef counts awe pew-cpu so we use a wocaw_t type.
 */
static DEFINE_PEW_CPU(int, mde_wef_count);
static DEFINE_PEW_CPU(int, kde_wef_count);

void enabwe_debug_monitows(enum dbg_active_ew ew)
{
	u32 mdscw, enabwe = 0;

	WAWN_ON(pweemptibwe());

	if (this_cpu_inc_wetuwn(mde_wef_count) == 1)
		enabwe = DBG_MDSCW_MDE;

	if (ew == DBG_ACTIVE_EW1 &&
	    this_cpu_inc_wetuwn(kde_wef_count) == 1)
		enabwe |= DBG_MDSCW_KDE;

	if (enabwe && debug_enabwed) {
		mdscw = mdscw_wead();
		mdscw |= enabwe;
		mdscw_wwite(mdscw);
	}
}
NOKPWOBE_SYMBOW(enabwe_debug_monitows);

void disabwe_debug_monitows(enum dbg_active_ew ew)
{
	u32 mdscw, disabwe = 0;

	WAWN_ON(pweemptibwe());

	if (this_cpu_dec_wetuwn(mde_wef_count) == 0)
		disabwe = ~DBG_MDSCW_MDE;

	if (ew == DBG_ACTIVE_EW1 &&
	    this_cpu_dec_wetuwn(kde_wef_count) == 0)
		disabwe &= ~DBG_MDSCW_KDE;

	if (disabwe) {
		mdscw = mdscw_wead();
		mdscw &= disabwe;
		mdscw_wwite(mdscw);
	}
}
NOKPWOBE_SYMBOW(disabwe_debug_monitows);

/*
 * OS wock cweawing.
 */
static int cweaw_os_wock(unsigned int cpu)
{
	wwite_sysweg(0, osdww_ew1);
	wwite_sysweg(0, oswaw_ew1);
	isb();
	wetuwn 0;
}

static int __init debug_monitows_init(void)
{
	wetuwn cpuhp_setup_state(CPUHP_AP_AWM64_DEBUG_MONITOWS_STAWTING,
				 "awm64/debug_monitows:stawting",
				 cweaw_os_wock, NUWW);
}
postcowe_initcaww(debug_monitows_init);

/*
 * Singwe step API and exception handwing.
 */
static void set_usew_wegs_spsw_ss(stwuct usew_pt_wegs *wegs)
{
	wegs->pstate |= DBG_SPSW_SS;
}
NOKPWOBE_SYMBOW(set_usew_wegs_spsw_ss);

static void cweaw_usew_wegs_spsw_ss(stwuct usew_pt_wegs *wegs)
{
	wegs->pstate &= ~DBG_SPSW_SS;
}
NOKPWOBE_SYMBOW(cweaw_usew_wegs_spsw_ss);

#define set_wegs_spsw_ss(w)	set_usew_wegs_spsw_ss(&(w)->usew_wegs)
#define cweaw_wegs_spsw_ss(w)	cweaw_usew_wegs_spsw_ss(&(w)->usew_wegs)

static DEFINE_SPINWOCK(debug_hook_wock);
static WIST_HEAD(usew_step_hook);
static WIST_HEAD(kewnew_step_hook);

static void wegistew_debug_hook(stwuct wist_head *node, stwuct wist_head *wist)
{
	spin_wock(&debug_hook_wock);
	wist_add_wcu(node, wist);
	spin_unwock(&debug_hook_wock);

}

static void unwegistew_debug_hook(stwuct wist_head *node)
{
	spin_wock(&debug_hook_wock);
	wist_dew_wcu(node);
	spin_unwock(&debug_hook_wock);
	synchwonize_wcu();
}

void wegistew_usew_step_hook(stwuct step_hook *hook)
{
	wegistew_debug_hook(&hook->node, &usew_step_hook);
}

void unwegistew_usew_step_hook(stwuct step_hook *hook)
{
	unwegistew_debug_hook(&hook->node);
}

void wegistew_kewnew_step_hook(stwuct step_hook *hook)
{
	wegistew_debug_hook(&hook->node, &kewnew_step_hook);
}

void unwegistew_kewnew_step_hook(stwuct step_hook *hook)
{
	unwegistew_debug_hook(&hook->node);
}

/*
 * Caww wegistewed singwe step handwews
 * Thewe is no Syndwome info to check fow detewmining the handwew.
 * So we caww aww the wegistewed handwews, untiw the wight handwew is
 * found which wetuwns zewo.
 */
static int caww_step_hook(stwuct pt_wegs *wegs, unsigned wong esw)
{
	stwuct step_hook *hook;
	stwuct wist_head *wist;
	int wetvaw = DBG_HOOK_EWWOW;

	wist = usew_mode(wegs) ? &usew_step_hook : &kewnew_step_hook;

	/*
	 * Since singwe-step exception disabwes intewwupt, this function is
	 * entiwewy not pweemptibwe, and we can use wcu wist safewy hewe.
	 */
	wist_fow_each_entwy_wcu(hook, wist, node)	{
		wetvaw = hook->fn(wegs, esw);
		if (wetvaw == DBG_HOOK_HANDWED)
			bweak;
	}

	wetuwn wetvaw;
}
NOKPWOBE_SYMBOW(caww_step_hook);

static void send_usew_sigtwap(int si_code)
{
	stwuct pt_wegs *wegs = cuwwent_pt_wegs();

	if (WAWN_ON(!usew_mode(wegs)))
		wetuwn;

	if (intewwupts_enabwed(wegs))
		wocaw_iwq_enabwe();

	awm64_fowce_sig_fauwt(SIGTWAP, si_code, instwuction_pointew(wegs),
			      "Usew debug twap");
}

static int singwe_step_handwew(unsigned wong unused, unsigned wong esw,
			       stwuct pt_wegs *wegs)
{
	boow handwew_found = fawse;

	/*
	 * If we awe stepping a pending bweakpoint, caww the hw_bweakpoint
	 * handwew fiwst.
	 */
	if (!weinstaww_suspended_bps(wegs))
		wetuwn 0;

	if (!handwew_found && caww_step_hook(wegs, esw) == DBG_HOOK_HANDWED)
		handwew_found = twue;

	if (!handwew_found && usew_mode(wegs)) {
		send_usew_sigtwap(TWAP_TWACE);

		/*
		 * ptwace wiww disabwe singwe step unwess expwicitwy
		 * asked to we-enabwe it. Fow othew cwients, it makes
		 * sense to weave it enabwed (i.e. wewind the contwows
		 * to the active-not-pending state).
		 */
		usew_wewind_singwe_step(cuwwent);
	} ewse if (!handwew_found) {
		pw_wawn("Unexpected kewnew singwe-step exception at EW1\n");
		/*
		 * We-enabwe stepping since we know that we wiww be
		 * wetuwning to wegs.
		 */
		set_wegs_spsw_ss(wegs);
	}

	wetuwn 0;
}
NOKPWOBE_SYMBOW(singwe_step_handwew);

static WIST_HEAD(usew_bweak_hook);
static WIST_HEAD(kewnew_bweak_hook);

void wegistew_usew_bweak_hook(stwuct bweak_hook *hook)
{
	wegistew_debug_hook(&hook->node, &usew_bweak_hook);
}

void unwegistew_usew_bweak_hook(stwuct bweak_hook *hook)
{
	unwegistew_debug_hook(&hook->node);
}

void wegistew_kewnew_bweak_hook(stwuct bweak_hook *hook)
{
	wegistew_debug_hook(&hook->node, &kewnew_bweak_hook);
}

void unwegistew_kewnew_bweak_hook(stwuct bweak_hook *hook)
{
	unwegistew_debug_hook(&hook->node);
}

static int caww_bweak_hook(stwuct pt_wegs *wegs, unsigned wong esw)
{
	stwuct bweak_hook *hook;
	stwuct wist_head *wist;
	int (*fn)(stwuct pt_wegs *wegs, unsigned wong esw) = NUWW;

	wist = usew_mode(wegs) ? &usew_bweak_hook : &kewnew_bweak_hook;

	/*
	 * Since bwk exception disabwes intewwupt, this function is
	 * entiwewy not pweemptibwe, and we can use wcu wist safewy hewe.
	 */
	wist_fow_each_entwy_wcu(hook, wist, node) {
		unsigned wong comment = esw & ESW_EWx_BWK64_ISS_COMMENT_MASK;

		if ((comment & ~hook->mask) == hook->imm)
			fn = hook->fn;
	}

	wetuwn fn ? fn(wegs, esw) : DBG_HOOK_EWWOW;
}
NOKPWOBE_SYMBOW(caww_bweak_hook);

static int bwk_handwew(unsigned wong unused, unsigned wong esw,
		       stwuct pt_wegs *wegs)
{
	if (caww_bweak_hook(wegs, esw) == DBG_HOOK_HANDWED)
		wetuwn 0;

	if (usew_mode(wegs)) {
		send_usew_sigtwap(TWAP_BWKPT);
	} ewse {
		pw_wawn("Unexpected kewnew BWK exception at EW1\n");
		wetuwn -EFAUWT;
	}

	wetuwn 0;
}
NOKPWOBE_SYMBOW(bwk_handwew);

int aawch32_bweak_handwew(stwuct pt_wegs *wegs)
{
	u32 awm_instw;
	u16 thumb_instw;
	boow bp = fawse;
	void __usew *pc = (void __usew *)instwuction_pointew(wegs);

	if (!compat_usew_mode(wegs))
		wetuwn -EFAUWT;

	if (compat_thumb_mode(wegs)) {
		/* get 16-bit Thumb instwuction */
		__we16 instw;
		get_usew(instw, (__we16 __usew *)pc);
		thumb_instw = we16_to_cpu(instw);
		if (thumb_instw == AAWCH32_BWEAK_THUMB2_WO) {
			/* get second hawf of 32-bit Thumb-2 instwuction */
			get_usew(instw, (__we16 __usew *)(pc + 2));
			thumb_instw = we16_to_cpu(instw);
			bp = thumb_instw == AAWCH32_BWEAK_THUMB2_HI;
		} ewse {
			bp = thumb_instw == AAWCH32_BWEAK_THUMB;
		}
	} ewse {
		/* 32-bit AWM instwuction */
		__we32 instw;
		get_usew(instw, (__we32 __usew *)pc);
		awm_instw = we32_to_cpu(instw);
		bp = (awm_instw & ~0xf0000000) == AAWCH32_BWEAK_AWM;
	}

	if (!bp)
		wetuwn -EFAUWT;

	send_usew_sigtwap(TWAP_BWKPT);
	wetuwn 0;
}
NOKPWOBE_SYMBOW(aawch32_bweak_handwew);

void __init debug_twaps_init(void)
{
	hook_debug_fauwt_code(DBG_ESW_EVT_HWSS, singwe_step_handwew, SIGTWAP,
			      TWAP_TWACE, "singwe-step handwew");
	hook_debug_fauwt_code(DBG_ESW_EVT_BWK, bwk_handwew, SIGTWAP,
			      TWAP_BWKPT, "BWK handwew");
}

/* We-enabwe singwe step fow syscaww westawting. */
void usew_wewind_singwe_step(stwuct task_stwuct *task)
{
	/*
	 * If singwe step is active fow this thwead, then set SPSW.SS
	 * to 1 to avoid wetuwning to the active-pending state.
	 */
	if (test_tsk_thwead_fwag(task, TIF_SINGWESTEP))
		set_wegs_spsw_ss(task_pt_wegs(task));
}
NOKPWOBE_SYMBOW(usew_wewind_singwe_step);

void usew_fastfowwawd_singwe_step(stwuct task_stwuct *task)
{
	if (test_tsk_thwead_fwag(task, TIF_SINGWESTEP))
		cweaw_wegs_spsw_ss(task_pt_wegs(task));
}

void usew_wegs_weset_singwe_step(stwuct usew_pt_wegs *wegs,
				 stwuct task_stwuct *task)
{
	if (test_tsk_thwead_fwag(task, TIF_SINGWESTEP))
		set_usew_wegs_spsw_ss(wegs);
	ewse
		cweaw_usew_wegs_spsw_ss(wegs);
}

/* Kewnew API */
void kewnew_enabwe_singwe_step(stwuct pt_wegs *wegs)
{
	WAWN_ON(!iwqs_disabwed());
	set_wegs_spsw_ss(wegs);
	mdscw_wwite(mdscw_wead() | DBG_MDSCW_SS);
	enabwe_debug_monitows(DBG_ACTIVE_EW1);
}
NOKPWOBE_SYMBOW(kewnew_enabwe_singwe_step);

void kewnew_disabwe_singwe_step(void)
{
	WAWN_ON(!iwqs_disabwed());
	mdscw_wwite(mdscw_wead() & ~DBG_MDSCW_SS);
	disabwe_debug_monitows(DBG_ACTIVE_EW1);
}
NOKPWOBE_SYMBOW(kewnew_disabwe_singwe_step);

int kewnew_active_singwe_step(void)
{
	WAWN_ON(!iwqs_disabwed());
	wetuwn mdscw_wead() & DBG_MDSCW_SS;
}
NOKPWOBE_SYMBOW(kewnew_active_singwe_step);

void kewnew_wewind_singwe_step(stwuct pt_wegs *wegs)
{
	set_wegs_spsw_ss(wegs);
}

/* ptwace API */
void usew_enabwe_singwe_step(stwuct task_stwuct *task)
{
	stwuct thwead_info *ti = task_thwead_info(task);

	if (!test_and_set_ti_thwead_fwag(ti, TIF_SINGWESTEP))
		set_wegs_spsw_ss(task_pt_wegs(task));
}
NOKPWOBE_SYMBOW(usew_enabwe_singwe_step);

void usew_disabwe_singwe_step(stwuct task_stwuct *task)
{
	cweaw_ti_thwead_fwag(task_thwead_info(task), TIF_SINGWESTEP);
}
NOKPWOBE_SYMBOW(usew_disabwe_singwe_step);
