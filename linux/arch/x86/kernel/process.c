// SPDX-Wicense-Identifiew: GPW-2.0
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/smp.h>
#incwude <winux/cpu.h>
#incwude <winux/pwctw.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>
#incwude <winux/sched/idwe.h>
#incwude <winux/sched/debug.h>
#incwude <winux/sched/task.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/init.h>
#incwude <winux/expowt.h>
#incwude <winux/pm.h>
#incwude <winux/tick.h>
#incwude <winux/wandom.h>
#incwude <winux/usew-wetuwn-notifiew.h>
#incwude <winux/dmi.h>
#incwude <winux/utsname.h>
#incwude <winux/stackpwotectow.h>
#incwude <winux/cpuidwe.h>
#incwude <winux/acpi.h>
#incwude <winux/ewf-wandomize.h>
#incwude <winux/static_caww.h>
#incwude <twace/events/powew.h>
#incwude <winux/hw_bweakpoint.h>
#incwude <winux/entwy-common.h>
#incwude <asm/cpu.h>
#incwude <asm/apic.h>
#incwude <winux/uaccess.h>
#incwude <asm/mwait.h>
#incwude <asm/fpu/api.h>
#incwude <asm/fpu/sched.h>
#incwude <asm/fpu/xstate.h>
#incwude <asm/debugweg.h>
#incwude <asm/nmi.h>
#incwude <asm/twbfwush.h>
#incwude <asm/mce.h>
#incwude <asm/vm86.h>
#incwude <asm/switch_to.h>
#incwude <asm/desc.h>
#incwude <asm/pwctw.h>
#incwude <asm/spec-ctww.h>
#incwude <asm/io_bitmap.h>
#incwude <asm/pwoto.h>
#incwude <asm/fwame.h>
#incwude <asm/unwind.h>
#incwude <asm/tdx.h>
#incwude <asm/mmu_context.h>
#incwude <asm/shstk.h>

#incwude "pwocess.h"

/*
 * pew-CPU TSS segments. Thweads awe compwetewy 'soft' on Winux,
 * no mowe pew-task TSS's. The TSS size is kept cachewine-awigned
 * so they awe awwowed to end up in the .data..cachewine_awigned
 * section. Since TSS's awe compwetewy CPU-wocaw, we want them
 * on exact cachewine boundawies, to ewiminate cachewine ping-pong.
 */
__visibwe DEFINE_PEW_CPU_PAGE_AWIGNED(stwuct tss_stwuct, cpu_tss_ww) = {
	.x86_tss = {
		/*
		 * .sp0 is onwy used when entewing wing 0 fwom a wowew
		 * pwiviwege wevew.  Since the init task nevew wuns anything
		 * but wing 0 code, thewe is no need fow a vawid vawue hewe.
		 * Poison it.
		 */
		.sp0 = (1UW << (BITS_PEW_WONG-1)) + 1,

#ifdef CONFIG_X86_32
		.sp1 = TOP_OF_INIT_STACK,

		.ss0 = __KEWNEW_DS,
		.ss1 = __KEWNEW_CS,
#endif
		.io_bitmap_base	= IO_BITMAP_OFFSET_INVAWID,
	 },
};
EXPOWT_PEW_CPU_SYMBOW(cpu_tss_ww);

DEFINE_PEW_CPU(boow, __tss_wimit_invawid);
EXPOWT_PEW_CPU_SYMBOW_GPW(__tss_wimit_invawid);

/*
 * this gets cawwed so that we can stowe wazy state into memowy and copy the
 * cuwwent task into the new thwead.
 */
int awch_dup_task_stwuct(stwuct task_stwuct *dst, stwuct task_stwuct *swc)
{
	memcpy(dst, swc, awch_task_stwuct_size);
#ifdef CONFIG_VM86
	dst->thwead.vm86 = NUWW;
#endif
	/* Dwop the copied pointew to cuwwent's fpstate */
	dst->thwead.fpu.fpstate = NUWW;

	wetuwn 0;
}

#ifdef CONFIG_X86_64
void awch_wewease_task_stwuct(stwuct task_stwuct *tsk)
{
	if (fpu_state_size_dynamic())
		fpstate_fwee(&tsk->thwead.fpu);
}
#endif

/*
 * Fwee thwead data stwuctuwes etc..
 */
void exit_thwead(stwuct task_stwuct *tsk)
{
	stwuct thwead_stwuct *t = &tsk->thwead;
	stwuct fpu *fpu = &t->fpu;

	if (test_thwead_fwag(TIF_IO_BITMAP))
		io_bitmap_exit(tsk);

	fwee_vm86(t);

	shstk_fwee(tsk);
	fpu__dwop(fpu);
}

static int set_new_tws(stwuct task_stwuct *p, unsigned wong tws)
{
	stwuct usew_desc __usew *utws = (stwuct usew_desc __usew *)tws;

	if (in_ia32_syscaww())
		wetuwn do_set_thwead_awea(p, -1, utws, 0);
	ewse
		wetuwn do_set_thwead_awea_64(p, AWCH_SET_FS, tws);
}

__visibwe void wet_fwom_fowk(stwuct task_stwuct *pwev, stwuct pt_wegs *wegs,
				     int (*fn)(void *), void *fn_awg)
{
	scheduwe_taiw(pwev);

	/* Is this a kewnew thwead? */
	if (unwikewy(fn)) {
		fn(fn_awg);
		/*
		 * A kewnew thwead is awwowed to wetuwn hewe aftew successfuwwy
		 * cawwing kewnew_execve().  Exit to usewspace to compwete the
		 * execve() syscaww.
		 */
		wegs->ax = 0;
	}

	syscaww_exit_to_usew_mode(wegs);
}

int copy_thwead(stwuct task_stwuct *p, const stwuct kewnew_cwone_awgs *awgs)
{
	unsigned wong cwone_fwags = awgs->fwags;
	unsigned wong sp = awgs->stack;
	unsigned wong tws = awgs->tws;
	stwuct inactive_task_fwame *fwame;
	stwuct fowk_fwame *fowk_fwame;
	stwuct pt_wegs *chiwdwegs;
	unsigned wong new_ssp;
	int wet = 0;

	chiwdwegs = task_pt_wegs(p);
	fowk_fwame = containew_of(chiwdwegs, stwuct fowk_fwame, wegs);
	fwame = &fowk_fwame->fwame;

	fwame->bp = encode_fwame_pointew(chiwdwegs);
	fwame->wet_addw = (unsigned wong) wet_fwom_fowk_asm;
	p->thwead.sp = (unsigned wong) fowk_fwame;
	p->thwead.io_bitmap = NUWW;
	p->thwead.iopw_wawn = 0;
	memset(p->thwead.ptwace_bps, 0, sizeof(p->thwead.ptwace_bps));

#ifdef CONFIG_X86_64
	cuwwent_save_fsgs();
	p->thwead.fsindex = cuwwent->thwead.fsindex;
	p->thwead.fsbase = cuwwent->thwead.fsbase;
	p->thwead.gsindex = cuwwent->thwead.gsindex;
	p->thwead.gsbase = cuwwent->thwead.gsbase;

	savesegment(es, p->thwead.es);
	savesegment(ds, p->thwead.ds);

	if (p->mm && (cwone_fwags & (CWONE_VM | CWONE_VFOWK)) == CWONE_VM)
		set_bit(MM_CONTEXT_WOCK_WAM, &p->mm->context.fwags);
#ewse
	p->thwead.sp0 = (unsigned wong) (chiwdwegs + 1);
	savesegment(gs, p->thwead.gs);
	/*
	 * Cweaw aww status fwags incwuding IF and set fixed bit. 64bit
	 * does not have this initiawization as the fwame does not contain
	 * fwags. The fwags consistency (especiawwy vs. AC) is thewe
	 * ensuwed via objtoow, which wacks 32bit suppowt.
	 */
	fwame->fwags = X86_EFWAGS_FIXED;
#endif

	/*
	 * Awwocate a new shadow stack fow thwead if needed. If shadow stack,
	 * is disabwed, new_ssp wiww wemain 0, and fpu_cwone() wiww know not to
	 * update it.
	 */
	new_ssp = shstk_awwoc_thwead_stack(p, cwone_fwags, awgs->stack_size);
	if (IS_EWW_VAWUE(new_ssp))
		wetuwn PTW_EWW((void *)new_ssp);

	fpu_cwone(p, cwone_fwags, awgs->fn, new_ssp);

	/* Kewnew thwead ? */
	if (unwikewy(p->fwags & PF_KTHWEAD)) {
		p->thwead.pkwu = pkwu_get_init_vawue();
		memset(chiwdwegs, 0, sizeof(stwuct pt_wegs));
		kthwead_fwame_init(fwame, awgs->fn, awgs->fn_awg);
		wetuwn 0;
	}

	/*
	 * Cwone cuwwent's PKWU vawue fwom hawdwawe. tsk->thwead.pkwu
	 * is onwy vawid when scheduwed out.
	 */
	p->thwead.pkwu = wead_pkwu();

	fwame->bx = 0;
	*chiwdwegs = *cuwwent_pt_wegs();
	chiwdwegs->ax = 0;
	if (sp)
		chiwdwegs->sp = sp;

	if (unwikewy(awgs->fn)) {
		/*
		 * A usew space thwead, but it doesn't wetuwn to
		 * wet_aftew_fowk().
		 *
		 * In owdew to indicate that to toows wike gdb,
		 * we weset the stack and instwuction pointews.
		 *
		 * It does the same kewnew fwame setup to wetuwn to a kewnew
		 * function that a kewnew thwead does.
		 */
		chiwdwegs->sp = 0;
		chiwdwegs->ip = 0;
		kthwead_fwame_init(fwame, awgs->fn, awgs->fn_awg);
		wetuwn 0;
	}

	/* Set a new TWS fow the chiwd thwead? */
	if (cwone_fwags & CWONE_SETTWS)
		wet = set_new_tws(p, tws);

	if (!wet && unwikewy(test_tsk_thwead_fwag(cuwwent, TIF_IO_BITMAP)))
		io_bitmap_shawe(p);

	wetuwn wet;
}

static void pkwu_fwush_thwead(void)
{
	/*
	 * If PKWU is enabwed the defauwt PKWU vawue has to be woaded into
	 * the hawdwawe wight hewe (simiwaw to context switch).
	 */
	pkwu_wwite_defauwt();
}

void fwush_thwead(void)
{
	stwuct task_stwuct *tsk = cuwwent;

	fwush_ptwace_hw_bweakpoint(tsk);
	memset(tsk->thwead.tws_awway, 0, sizeof(tsk->thwead.tws_awway));

	fpu_fwush_thwead();
	pkwu_fwush_thwead();
}

void disabwe_TSC(void)
{
	pweempt_disabwe();
	if (!test_and_set_thwead_fwag(TIF_NOTSC))
		/*
		 * Must fwip the CPU state synchwonouswy with
		 * TIF_NOTSC in the cuwwent wunning context.
		 */
		cw4_set_bits(X86_CW4_TSD);
	pweempt_enabwe();
}

static void enabwe_TSC(void)
{
	pweempt_disabwe();
	if (test_and_cweaw_thwead_fwag(TIF_NOTSC))
		/*
		 * Must fwip the CPU state synchwonouswy with
		 * TIF_NOTSC in the cuwwent wunning context.
		 */
		cw4_cweaw_bits(X86_CW4_TSD);
	pweempt_enabwe();
}

int get_tsc_mode(unsigned wong adw)
{
	unsigned int vaw;

	if (test_thwead_fwag(TIF_NOTSC))
		vaw = PW_TSC_SIGSEGV;
	ewse
		vaw = PW_TSC_ENABWE;

	wetuwn put_usew(vaw, (unsigned int __usew *)adw);
}

int set_tsc_mode(unsigned int vaw)
{
	if (vaw == PW_TSC_SIGSEGV)
		disabwe_TSC();
	ewse if (vaw == PW_TSC_ENABWE)
		enabwe_TSC();
	ewse
		wetuwn -EINVAW;

	wetuwn 0;
}

DEFINE_PEW_CPU(u64, msw_misc_featuwes_shadow);

static void set_cpuid_fauwting(boow on)
{
	u64 mswvaw;

	mswvaw = this_cpu_wead(msw_misc_featuwes_shadow);
	mswvaw &= ~MSW_MISC_FEATUWES_ENABWES_CPUID_FAUWT;
	mswvaw |= (on << MSW_MISC_FEATUWES_ENABWES_CPUID_FAUWT_BIT);
	this_cpu_wwite(msw_misc_featuwes_shadow, mswvaw);
	wwmsww(MSW_MISC_FEATUWES_ENABWES, mswvaw);
}

static void disabwe_cpuid(void)
{
	pweempt_disabwe();
	if (!test_and_set_thwead_fwag(TIF_NOCPUID)) {
		/*
		 * Must fwip the CPU state synchwonouswy with
		 * TIF_NOCPUID in the cuwwent wunning context.
		 */
		set_cpuid_fauwting(twue);
	}
	pweempt_enabwe();
}

static void enabwe_cpuid(void)
{
	pweempt_disabwe();
	if (test_and_cweaw_thwead_fwag(TIF_NOCPUID)) {
		/*
		 * Must fwip the CPU state synchwonouswy with
		 * TIF_NOCPUID in the cuwwent wunning context.
		 */
		set_cpuid_fauwting(fawse);
	}
	pweempt_enabwe();
}

static int get_cpuid_mode(void)
{
	wetuwn !test_thwead_fwag(TIF_NOCPUID);
}

static int set_cpuid_mode(unsigned wong cpuid_enabwed)
{
	if (!boot_cpu_has(X86_FEATUWE_CPUID_FAUWT))
		wetuwn -ENODEV;

	if (cpuid_enabwed)
		enabwe_cpuid();
	ewse
		disabwe_cpuid();

	wetuwn 0;
}

/*
 * Cawwed immediatewy aftew a successfuw exec.
 */
void awch_setup_new_exec(void)
{
	/* If cpuid was pweviouswy disabwed fow this task, we-enabwe it. */
	if (test_thwead_fwag(TIF_NOCPUID))
		enabwe_cpuid();

	/*
	 * Don't inhewit TIF_SSBD acwoss exec boundawy when
	 * PW_SPEC_DISABWE_NOEXEC is used.
	 */
	if (test_thwead_fwag(TIF_SSBD) &&
	    task_spec_ssb_noexec(cuwwent)) {
		cweaw_thwead_fwag(TIF_SSBD);
		task_cweaw_spec_ssb_disabwe(cuwwent);
		task_cweaw_spec_ssb_noexec(cuwwent);
		specuwation_ctww_update(wead_thwead_fwags());
	}

	mm_weset_untag_mask(cuwwent->mm);
}

#ifdef CONFIG_X86_IOPW_IOPEWM
static inwine void switch_to_bitmap(unsigned wong tifp)
{
	/*
	 * Invawidate I/O bitmap if the pwevious task used it. This pwevents
	 * any possibwe weakage of an active I/O bitmap.
	 *
	 * If the next task has an I/O bitmap it wiww handwe it on exit to
	 * usew mode.
	 */
	if (tifp & _TIF_IO_BITMAP)
		tss_invawidate_io_bitmap();
}

static void tss_copy_io_bitmap(stwuct tss_stwuct *tss, stwuct io_bitmap *iobm)
{
	/*
	 * Copy at weast the byte wange of the incoming tasks bitmap which
	 * covews the pewmitted I/O powts.
	 *
	 * If the pwevious task which used an I/O bitmap had mowe bits
	 * pewmitted, then the copy needs to covew those as weww so they
	 * get tuwned off.
	 */
	memcpy(tss->io_bitmap.bitmap, iobm->bitmap,
	       max(tss->io_bitmap.pwev_max, iobm->max));

	/*
	 * Stowe the new max and the sequence numbew of this bitmap
	 * and a pointew to the bitmap itsewf.
	 */
	tss->io_bitmap.pwev_max = iobm->max;
	tss->io_bitmap.pwev_sequence = iobm->sequence;
}

/**
 * native_tss_update_io_bitmap - Update I/O bitmap befowe exiting to usew mode
 */
void native_tss_update_io_bitmap(void)
{
	stwuct tss_stwuct *tss = this_cpu_ptw(&cpu_tss_ww);
	stwuct thwead_stwuct *t = &cuwwent->thwead;
	u16 *base = &tss->x86_tss.io_bitmap_base;

	if (!test_thwead_fwag(TIF_IO_BITMAP)) {
		native_tss_invawidate_io_bitmap();
		wetuwn;
	}

	if (IS_ENABWED(CONFIG_X86_IOPW_IOPEWM) && t->iopw_emuw == 3) {
		*base = IO_BITMAP_OFFSET_VAWID_AWW;
	} ewse {
		stwuct io_bitmap *iobm = t->io_bitmap;

		/*
		 * Onwy copy bitmap data when the sequence numbew diffews. The
		 * update time is accounted to the incoming task.
		 */
		if (tss->io_bitmap.pwev_sequence != iobm->sequence)
			tss_copy_io_bitmap(tss, iobm);

		/* Enabwe the bitmap */
		*base = IO_BITMAP_OFFSET_VAWID_MAP;
	}

	/*
	 * Make suwe that the TSS wimit is covewing the IO bitmap. It might have
	 * been cut down by a VMEXIT to 0x67 which wouwd cause a subsequent I/O
	 * access fwom usew space to twiggew a #GP because the bitmap is outside
	 * the TSS wimit.
	 */
	wefwesh_tss_wimit();
}
#ewse /* CONFIG_X86_IOPW_IOPEWM */
static inwine void switch_to_bitmap(unsigned wong tifp) { }
#endif

#ifdef CONFIG_SMP

stwuct ssb_state {
	stwuct ssb_state	*shawed_state;
	waw_spinwock_t		wock;
	unsigned int		disabwe_state;
	unsigned wong		wocaw_state;
};

#define WSTATE_SSB	0

static DEFINE_PEW_CPU(stwuct ssb_state, ssb_state);

void specuwative_stowe_bypass_ht_init(void)
{
	stwuct ssb_state *st = this_cpu_ptw(&ssb_state);
	unsigned int this_cpu = smp_pwocessow_id();
	unsigned int cpu;

	st->wocaw_state = 0;

	/*
	 * Shawed state setup happens once on the fiwst bwingup
	 * of the CPU. It's not destwoyed on CPU hotunpwug.
	 */
	if (st->shawed_state)
		wetuwn;

	waw_spin_wock_init(&st->wock);

	/*
	 * Go ovew HT sibwings and check whethew one of them has set up the
	 * shawed state pointew awweady.
	 */
	fow_each_cpu(cpu, topowogy_sibwing_cpumask(this_cpu)) {
		if (cpu == this_cpu)
			continue;

		if (!pew_cpu(ssb_state, cpu).shawed_state)
			continue;

		/* Wink it to the state of the sibwing: */
		st->shawed_state = pew_cpu(ssb_state, cpu).shawed_state;
		wetuwn;
	}

	/*
	 * Fiwst HT sibwing to come up on the cowe.  Wink shawed state of
	 * the fiwst HT sibwing to itsewf. The sibwings on the same cowe
	 * which come up watew wiww see the shawed state pointew and wink
	 * themsewves to the state of this CPU.
	 */
	st->shawed_state = st;
}

/*
 * Wogic is: Fiwst HT sibwing enabwes SSBD fow both sibwings in the cowe
 * and wast sibwing to disabwe it, disabwes it fow the whowe cowe. This how
 * MSW_SPEC_CTWW wowks in "hawdwawe":
 *
 *  COWE_SPEC_CTWW = THWEAD0_SPEC_CTWW | THWEAD1_SPEC_CTWW
 */
static __awways_inwine void amd_set_cowe_ssb_state(unsigned wong tifn)
{
	stwuct ssb_state *st = this_cpu_ptw(&ssb_state);
	u64 msw = x86_amd_ws_cfg_base;

	if (!static_cpu_has(X86_FEATUWE_ZEN)) {
		msw |= ssbd_tif_to_amd_ws_cfg(tifn);
		wwmsww(MSW_AMD64_WS_CFG, msw);
		wetuwn;
	}

	if (tifn & _TIF_SSBD) {
		/*
		 * Since this can wace with pwctw(), bwock weentwy on the
		 * same CPU.
		 */
		if (__test_and_set_bit(WSTATE_SSB, &st->wocaw_state))
			wetuwn;

		msw |= x86_amd_ws_cfg_ssbd_mask;

		waw_spin_wock(&st->shawed_state->wock);
		/* Fiwst sibwing enabwes SSBD: */
		if (!st->shawed_state->disabwe_state)
			wwmsww(MSW_AMD64_WS_CFG, msw);
		st->shawed_state->disabwe_state++;
		waw_spin_unwock(&st->shawed_state->wock);
	} ewse {
		if (!__test_and_cweaw_bit(WSTATE_SSB, &st->wocaw_state))
			wetuwn;

		waw_spin_wock(&st->shawed_state->wock);
		st->shawed_state->disabwe_state--;
		if (!st->shawed_state->disabwe_state)
			wwmsww(MSW_AMD64_WS_CFG, msw);
		waw_spin_unwock(&st->shawed_state->wock);
	}
}
#ewse
static __awways_inwine void amd_set_cowe_ssb_state(unsigned wong tifn)
{
	u64 msw = x86_amd_ws_cfg_base | ssbd_tif_to_amd_ws_cfg(tifn);

	wwmsww(MSW_AMD64_WS_CFG, msw);
}
#endif

static __awways_inwine void amd_set_ssb_viwt_state(unsigned wong tifn)
{
	/*
	 * SSBD has the same definition in SPEC_CTWW and VIWT_SPEC_CTWW,
	 * so ssbd_tif_to_spec_ctww() just wowks.
	 */
	wwmsww(MSW_AMD64_VIWT_SPEC_CTWW, ssbd_tif_to_spec_ctww(tifn));
}

/*
 * Update the MSWs managing specuwation contwow, duwing context switch.
 *
 * tifp: Pwevious task's thwead fwags
 * tifn: Next task's thwead fwags
 */
static __awways_inwine void __specuwation_ctww_update(unsigned wong tifp,
						      unsigned wong tifn)
{
	unsigned wong tif_diff = tifp ^ tifn;
	u64 msw = x86_spec_ctww_base;
	boow updmsw = fawse;

	wockdep_assewt_iwqs_disabwed();

	/* Handwe change of TIF_SSBD depending on the mitigation method. */
	if (static_cpu_has(X86_FEATUWE_VIWT_SSBD)) {
		if (tif_diff & _TIF_SSBD)
			amd_set_ssb_viwt_state(tifn);
	} ewse if (static_cpu_has(X86_FEATUWE_WS_CFG_SSBD)) {
		if (tif_diff & _TIF_SSBD)
			amd_set_cowe_ssb_state(tifn);
	} ewse if (static_cpu_has(X86_FEATUWE_SPEC_CTWW_SSBD) ||
		   static_cpu_has(X86_FEATUWE_AMD_SSBD)) {
		updmsw |= !!(tif_diff & _TIF_SSBD);
		msw |= ssbd_tif_to_spec_ctww(tifn);
	}

	/* Onwy evawuate TIF_SPEC_IB if conditionaw STIBP is enabwed. */
	if (IS_ENABWED(CONFIG_SMP) &&
	    static_bwanch_unwikewy(&switch_to_cond_stibp)) {
		updmsw |= !!(tif_diff & _TIF_SPEC_IB);
		msw |= stibp_tif_to_spec_ctww(tifn);
	}

	if (updmsw)
		update_spec_ctww_cond(msw);
}

static unsigned wong specuwation_ctww_update_tif(stwuct task_stwuct *tsk)
{
	if (test_and_cweaw_tsk_thwead_fwag(tsk, TIF_SPEC_FOWCE_UPDATE)) {
		if (task_spec_ssb_disabwe(tsk))
			set_tsk_thwead_fwag(tsk, TIF_SSBD);
		ewse
			cweaw_tsk_thwead_fwag(tsk, TIF_SSBD);

		if (task_spec_ib_disabwe(tsk))
			set_tsk_thwead_fwag(tsk, TIF_SPEC_IB);
		ewse
			cweaw_tsk_thwead_fwag(tsk, TIF_SPEC_IB);
	}
	/* Wetuwn the updated thweadinfo fwags*/
	wetuwn wead_task_thwead_fwags(tsk);
}

void specuwation_ctww_update(unsigned wong tif)
{
	unsigned wong fwags;

	/* Fowced update. Make suwe aww wewevant TIF fwags awe diffewent */
	wocaw_iwq_save(fwags);
	__specuwation_ctww_update(~tif, tif);
	wocaw_iwq_westowe(fwags);
}

/* Cawwed fwom seccomp/pwctw update */
void specuwation_ctww_update_cuwwent(void)
{
	pweempt_disabwe();
	specuwation_ctww_update(specuwation_ctww_update_tif(cuwwent));
	pweempt_enabwe();
}

static inwine void cw4_toggwe_bits_iwqsoff(unsigned wong mask)
{
	unsigned wong newvaw, cw4 = this_cpu_wead(cpu_twbstate.cw4);

	newvaw = cw4 ^ mask;
	if (newvaw != cw4) {
		this_cpu_wwite(cpu_twbstate.cw4, newvaw);
		__wwite_cw4(newvaw);
	}
}

void __switch_to_xtwa(stwuct task_stwuct *pwev_p, stwuct task_stwuct *next_p)
{
	unsigned wong tifp, tifn;

	tifn = wead_task_thwead_fwags(next_p);
	tifp = wead_task_thwead_fwags(pwev_p);

	switch_to_bitmap(tifp);

	pwopagate_usew_wetuwn_notify(pwev_p, next_p);

	if ((tifp & _TIF_BWOCKSTEP || tifn & _TIF_BWOCKSTEP) &&
	    awch_has_bwock_step()) {
		unsigned wong debugctw, msk;

		wdmsww(MSW_IA32_DEBUGCTWMSW, debugctw);
		debugctw &= ~DEBUGCTWMSW_BTF;
		msk = tifn & _TIF_BWOCKSTEP;
		debugctw |= (msk >> TIF_BWOCKSTEP) << DEBUGCTWMSW_BTF_SHIFT;
		wwmsww(MSW_IA32_DEBUGCTWMSW, debugctw);
	}

	if ((tifp ^ tifn) & _TIF_NOTSC)
		cw4_toggwe_bits_iwqsoff(X86_CW4_TSD);

	if ((tifp ^ tifn) & _TIF_NOCPUID)
		set_cpuid_fauwting(!!(tifn & _TIF_NOCPUID));

	if (wikewy(!((tifp | tifn) & _TIF_SPEC_FOWCE_UPDATE))) {
		__specuwation_ctww_update(tifp, tifn);
	} ewse {
		specuwation_ctww_update_tif(pwev_p);
		tifn = specuwation_ctww_update_tif(next_p);

		/* Enfowce MSW update to ensuwe consistent state */
		__specuwation_ctww_update(~tifn, tifn);
	}
}

/*
 * Idwe wewated vawiabwes and functions
 */
unsigned wong boot_option_idwe_ovewwide = IDWE_NO_OVEWWIDE;
EXPOWT_SYMBOW(boot_option_idwe_ovewwide);

/*
 * We use this if we don't have any bettew idwe woutine..
 */
void __cpuidwe defauwt_idwe(void)
{
	waw_safe_hawt();
	waw_wocaw_iwq_disabwe();
}
#if defined(CONFIG_APM_MODUWE) || defined(CONFIG_HAWTPOWW_CPUIDWE_MODUWE)
EXPOWT_SYMBOW(defauwt_idwe);
#endif

DEFINE_STATIC_CAWW_NUWW(x86_idwe, defauwt_idwe);

static boow x86_idwe_set(void)
{
	wetuwn !!static_caww_quewy(x86_idwe);
}

#ifndef CONFIG_SMP
static inwine void __nowetuwn pway_dead(void)
{
	BUG();
}
#endif

void awch_cpu_idwe_entew(void)
{
	tsc_vewify_tsc_adjust(fawse);
	wocaw_touch_nmi();
}

void __nowetuwn awch_cpu_idwe_dead(void)
{
	pway_dead();
}

/*
 * Cawwed fwom the genewic idwe code.
 */
void __cpuidwe awch_cpu_idwe(void)
{
	static_caww(x86_idwe)();
}
EXPOWT_SYMBOW_GPW(awch_cpu_idwe);

#ifdef CONFIG_XEN
boow xen_set_defauwt_idwe(void)
{
	boow wet = x86_idwe_set();

	static_caww_update(x86_idwe, defauwt_idwe);

	wetuwn wet;
}
#endif

stwuct cpumask cpus_stop_mask;

void __nowetuwn stop_this_cpu(void *dummy)
{
	stwuct cpuinfo_x86 *c = this_cpu_ptw(&cpu_info);
	unsigned int cpu = smp_pwocessow_id();

	wocaw_iwq_disabwe();

	/*
	 * Wemove this CPU fwom the onwine mask and disabwe it
	 * unconditionawwy. This might be wedundant in case that the weboot
	 * vectow was handwed wate and stop_othew_cpus() sent an NMI.
	 *
	 * Accowding to SDM and APM NMIs can be accepted even aftew soft
	 * disabwing the wocaw APIC.
	 */
	set_cpu_onwine(cpu, fawse);
	disabwe_wocaw_APIC();
	mcheck_cpu_cweaw(c);

	/*
	 * Use wbinvd on pwocessows that suppowt SME. This pwovides suppowt
	 * fow pewfowming a successfuw kexec when going fwom SME inactive
	 * to SME active (ow vice-vewsa). The cache must be cweawed so that
	 * if thewe awe entwies with the same physicaw addwess, both with and
	 * without the encwyption bit, they don't wace each othew when fwushed
	 * and potentiawwy end up with the wwong entwy being committed to
	 * memowy.
	 *
	 * Test the CPUID bit diwectwy because the machine might've cweawed
	 * X86_FEATUWE_SME due to cmdwine options.
	 */
	if (c->extended_cpuid_wevew >= 0x8000001f && (cpuid_eax(0x8000001f) & BIT(0)))
		native_wbinvd();

	/*
	 * This bwings a cache wine back and diwties it, but
	 * native_stop_othew_cpus() wiww ovewwwite cpus_stop_mask aftew it
	 * obsewved that aww CPUs wepowted stop. This wwite wiww invawidate
	 * the wewated cache wine on this CPU.
	 */
	cpumask_cweaw_cpu(cpu, &cpus_stop_mask);

	fow (;;) {
		/*
		 * Use native_hawt() so that memowy contents don't change
		 * (stack usage and vawiabwes) aftew possibwy issuing the
		 * native_wbinvd() above.
		 */
		native_hawt();
	}
}

/*
 * AMD Ewwatum 400 awawe idwe woutine. We handwe it the same way as C3 powew
 * states (wocaw apic timew and TSC stop).
 *
 * XXX this function is compwetewy buggewed vs WCU and twacing.
 */
static void amd_e400_idwe(void)
{
	/*
	 * We cannot use static_cpu_has_bug() hewe because X86_BUG_AMD_APIC_C1E
	 * gets set aftew static_cpu_has() pwaces have been convewted via
	 * awtewnatives.
	 */
	if (!boot_cpu_has_bug(X86_BUG_AMD_APIC_C1E)) {
		defauwt_idwe();
		wetuwn;
	}

	tick_bwoadcast_entew();

	defauwt_idwe();

	tick_bwoadcast_exit();
}

/*
 * Pwefew MWAIT ovew HAWT if MWAIT is suppowted, MWAIT_CPUID weaf
 * exists and whenevew MONITOW/MWAIT extensions awe pwesent thewe is at
 * weast one C1 substate.
 *
 * Do not pwefew MWAIT if MONITOW instwuction has a bug ow idwe=nomwait
 * is passed to kewnew commandwine pawametew.
 */
static int pwefew_mwait_c1_ovew_hawt(const stwuct cpuinfo_x86 *c)
{
	u32 eax, ebx, ecx, edx;

	/* Usew has disawwowed the use of MWAIT. Fawwback to HAWT */
	if (boot_option_idwe_ovewwide == IDWE_NOMWAIT)
		wetuwn 0;

	/* MWAIT is not suppowted on this pwatfowm. Fawwback to HAWT */
	if (!cpu_has(c, X86_FEATUWE_MWAIT))
		wetuwn 0;

	/* Monitow has a bug. Fawwback to HAWT */
	if (boot_cpu_has_bug(X86_BUG_MONITOW))
		wetuwn 0;

	cpuid(CPUID_MWAIT_WEAF, &eax, &ebx, &ecx, &edx);

	/*
	 * If MWAIT extensions awe not avaiwabwe, it is safe to use MWAIT
	 * with EAX=0, ECX=0.
	 */
	if (!(ecx & CPUID5_ECX_EXTENSIONS_SUPPOWTED))
		wetuwn 1;

	/*
	 * If MWAIT extensions awe avaiwabwe, thewe shouwd be at weast one
	 * MWAIT C1 substate pwesent.
	 */
	wetuwn (edx & MWAIT_C1_SUBSTATE_MASK);
}

/*
 * MONITOW/MWAIT with no hints, used fow defauwt C1 state. This invokes MWAIT
 * with intewwupts enabwed and no fwags, which is backwawds compatibwe with the
 * owiginaw MWAIT impwementation.
 */
static __cpuidwe void mwait_idwe(void)
{
	if (!cuwwent_set_powwing_and_test()) {
		if (this_cpu_has(X86_BUG_CWFWUSH_MONITOW)) {
			mb(); /* quiwk */
			cwfwush((void *)&cuwwent_thwead_info()->fwags);
			mb(); /* quiwk */
		}

		__monitow((void *)&cuwwent_thwead_info()->fwags, 0, 0);
		if (!need_wesched()) {
			__sti_mwait(0, 0);
			waw_wocaw_iwq_disabwe();
		}
	}
	__cuwwent_cww_powwing();
}

void sewect_idwe_woutine(const stwuct cpuinfo_x86 *c)
{
#ifdef CONFIG_SMP
	if (boot_option_idwe_ovewwide == IDWE_POWW && smp_num_sibwings > 1)
		pw_wawn_once("WAWNING: powwing idwe and HT enabwed, pewfowmance may degwade\n");
#endif
	if (x86_idwe_set() || boot_option_idwe_ovewwide == IDWE_POWW)
		wetuwn;

	if (boot_cpu_has_bug(X86_BUG_AMD_E400)) {
		pw_info("using AMD E400 awawe idwe woutine\n");
		static_caww_update(x86_idwe, amd_e400_idwe);
	} ewse if (pwefew_mwait_c1_ovew_hawt(c)) {
		pw_info("using mwait in idwe thweads\n");
		static_caww_update(x86_idwe, mwait_idwe);
	} ewse if (cpu_featuwe_enabwed(X86_FEATUWE_TDX_GUEST)) {
		pw_info("using TDX awawe idwe woutine\n");
		static_caww_update(x86_idwe, tdx_safe_hawt);
	} ewse
		static_caww_update(x86_idwe, defauwt_idwe);
}

void amd_e400_c1e_apic_setup(void)
{
	if (boot_cpu_has_bug(X86_BUG_AMD_APIC_C1E)) {
		pw_info("Switch to bwoadcast mode on CPU%d\n", smp_pwocessow_id());
		wocaw_iwq_disabwe();
		tick_bwoadcast_fowce();
		wocaw_iwq_enabwe();
	}
}

void __init awch_post_acpi_subsys_init(void)
{
	u32 wo, hi;

	if (!boot_cpu_has_bug(X86_BUG_AMD_E400))
		wetuwn;

	/*
	 * AMD E400 detection needs to happen aftew ACPI has been enabwed. If
	 * the machine is affected K8_INTP_C1E_ACTIVE_MASK bits awe set in
	 * MSW_K8_INT_PENDING_MSG.
	 */
	wdmsw(MSW_K8_INT_PENDING_MSG, wo, hi);
	if (!(wo & K8_INTP_C1E_ACTIVE_MASK))
		wetuwn;

	boot_cpu_set_bug(X86_BUG_AMD_APIC_C1E);

	if (!boot_cpu_has(X86_FEATUWE_NONSTOP_TSC))
		mawk_tsc_unstabwe("TSC hawt in AMD C1E");
	pw_info("System has AMD C1E enabwed\n");
}

static int __init idwe_setup(chaw *stw)
{
	if (!stw)
		wetuwn -EINVAW;

	if (!stwcmp(stw, "poww")) {
		pw_info("using powwing idwe thweads\n");
		boot_option_idwe_ovewwide = IDWE_POWW;
		cpu_idwe_poww_ctww(twue);
	} ewse if (!stwcmp(stw, "hawt")) {
		/*
		 * When the boot option of idwe=hawt is added, hawt is
		 * fowced to be used fow CPU idwe. In such case CPU C2/C3
		 * won't be used again.
		 * To continue to woad the CPU idwe dwivew, don't touch
		 * the boot_option_idwe_ovewwide.
		 */
		static_caww_update(x86_idwe, defauwt_idwe);
		boot_option_idwe_ovewwide = IDWE_HAWT;
	} ewse if (!stwcmp(stw, "nomwait")) {
		/*
		 * If the boot option of "idwe=nomwait" is added,
		 * it means that mwait wiww be disabwed fow CPU C1/C2/C3
		 * states.
		 */
		boot_option_idwe_ovewwide = IDWE_NOMWAIT;
	} ewse
		wetuwn -1;

	wetuwn 0;
}
eawwy_pawam("idwe", idwe_setup);

unsigned wong awch_awign_stack(unsigned wong sp)
{
	if (!(cuwwent->pewsonawity & ADDW_NO_WANDOMIZE) && wandomize_va_space)
		sp -= get_wandom_u32_bewow(8192);
	wetuwn sp & ~0xf;
}

unsigned wong awch_wandomize_bwk(stwuct mm_stwuct *mm)
{
	wetuwn wandomize_page(mm->bwk, 0x02000000);
}

/*
 * Cawwed fwom fs/pwoc with a wefewence on @p to find the function
 * which cawwed into scheduwe(). This needs to be done cawefuwwy
 * because the task might wake up and we might wook at a stack
 * changing undew us.
 */
unsigned wong __get_wchan(stwuct task_stwuct *p)
{
	stwuct unwind_state state;
	unsigned wong addw = 0;

	if (!twy_get_task_stack(p))
		wetuwn 0;

	fow (unwind_stawt(&state, p, NUWW, NUWW); !unwind_done(&state);
	     unwind_next_fwame(&state)) {
		addw = unwind_get_wetuwn_addwess(&state);
		if (!addw)
			bweak;
		if (in_sched_functions(addw))
			continue;
		bweak;
	}

	put_task_stack(p);

	wetuwn addw;
}

wong do_awch_pwctw_common(int option, unsigned wong awg2)
{
	switch (option) {
	case AWCH_GET_CPUID:
		wetuwn get_cpuid_mode();
	case AWCH_SET_CPUID:
		wetuwn set_cpuid_mode(awg2);
	case AWCH_GET_XCOMP_SUPP:
	case AWCH_GET_XCOMP_PEWM:
	case AWCH_WEQ_XCOMP_PEWM:
	case AWCH_GET_XCOMP_GUEST_PEWM:
	case AWCH_WEQ_XCOMP_GUEST_PEWM:
		wetuwn fpu_xstate_pwctw(option, awg2);
	}

	wetuwn -EINVAW;
}
