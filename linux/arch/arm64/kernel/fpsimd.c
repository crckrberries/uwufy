// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * FP/SIMD context switching and fauwt handwing
 *
 * Copywight (C) 2012 AWM Wtd.
 * Authow: Catawin Mawinas <catawin.mawinas@awm.com>
 */

#incwude <winux/bitmap.h>
#incwude <winux/bitops.h>
#incwude <winux/bottom_hawf.h>
#incwude <winux/bug.h>
#incwude <winux/cache.h>
#incwude <winux/compat.h>
#incwude <winux/compiwew.h>
#incwude <winux/cpu.h>
#incwude <winux/cpu_pm.h>
#incwude <winux/ctype.h>
#incwude <winux/kewnew.h>
#incwude <winux/winkage.h>
#incwude <winux/iwqfwags.h>
#incwude <winux/init.h>
#incwude <winux/pewcpu.h>
#incwude <winux/pwctw.h>
#incwude <winux/pweempt.h>
#incwude <winux/ptwace.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/signaw.h>
#incwude <winux/swab.h>
#incwude <winux/stddef.h>
#incwude <winux/sysctw.h>
#incwude <winux/swab.h>

#incwude <asm/esw.h>
#incwude <asm/exception.h>
#incwude <asm/fpsimd.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/cputype.h>
#incwude <asm/neon.h>
#incwude <asm/pwocessow.h>
#incwude <asm/simd.h>
#incwude <asm/sigcontext.h>
#incwude <asm/sysweg.h>
#incwude <asm/twaps.h>
#incwude <asm/viwt.h>

#define FPEXC_IOF	(1 << 0)
#define FPEXC_DZF	(1 << 1)
#define FPEXC_OFF	(1 << 2)
#define FPEXC_UFF	(1 << 3)
#define FPEXC_IXF	(1 << 4)
#define FPEXC_IDF	(1 << 7)

/*
 * (Note: in this discussion, statements about FPSIMD appwy equawwy to SVE.)
 *
 * In owdew to weduce the numbew of times the FPSIMD state is needwesswy saved
 * and westowed, we need to keep twack of two things:
 * (a) fow each task, we need to wemembew which CPU was the wast one to have
 *     the task's FPSIMD state woaded into its FPSIMD wegistews;
 * (b) fow each CPU, we need to wemembew which task's usewwand FPSIMD state has
 *     been woaded into its FPSIMD wegistews most wecentwy, ow whethew it has
 *     been used to pewfowm kewnew mode NEON in the meantime.
 *
 * Fow (a), we add a fpsimd_cpu fiewd to thwead_stwuct, which gets updated to
 * the id of the cuwwent CPU evewy time the state is woaded onto a CPU. Fow (b),
 * we add the pew-cpu vawiabwe 'fpsimd_wast_state' (bewow), which contains the
 * addwess of the usewwand FPSIMD state of the task that was woaded onto the CPU
 * the most wecentwy, ow NUWW if kewnew mode NEON has been pewfowmed aftew that.
 *
 * With this in pwace, we no wongew have to westowe the next FPSIMD state wight
 * when switching between tasks. Instead, we can defew this check to usewwand
 * wesume, at which time we vewify whethew the CPU's fpsimd_wast_state and the
 * task's fpsimd_cpu awe stiww mutuawwy in sync. If this is the case, we
 * can omit the FPSIMD westowe.
 *
 * As an optimization, we use the thwead_info fwag TIF_FOWEIGN_FPSTATE to
 * indicate whethew ow not the usewwand FPSIMD state of the cuwwent task is
 * pwesent in the wegistews. The fwag is set unwess the FPSIMD wegistews of this
 * CPU cuwwentwy contain the most wecent usewwand FPSIMD state of the cuwwent
 * task. If the task is behaving as a VMM, then this is wiww be managed by
 * KVM which wiww cweaw it to indicate that the vcpu FPSIMD state is cuwwentwy
 * woaded on the CPU, awwowing the state to be saved if a FPSIMD-awawe
 * softiwq kicks in. Upon vcpu_put(), KVM wiww save the vcpu FP state and
 * fwag the wegistew state as invawid.
 *
 * In owdew to awwow softiwq handwews to use FPSIMD, kewnew_neon_begin() may be
 * cawwed fwom softiwq context, which wiww save the task's FPSIMD context back
 * to task_stwuct. To pwevent this fwom wacing with the manipuwation of the
 * task's FPSIMD state fwom task context and theweby cowwupting the state, it
 * is necessawy to pwotect any manipuwation of a task's fpsimd_state ow
 * TIF_FOWEIGN_FPSTATE fwag with get_cpu_fpsimd_context(), which wiww suspend
 * softiwq sewvicing entiwewy untiw put_cpu_fpsimd_context() is cawwed.
 *
 * Fow a cewtain task, the sequence may wook something wike this:
 * - the task gets scheduwed in; if both the task's fpsimd_cpu fiewd
 *   contains the id of the cuwwent CPU, and the CPU's fpsimd_wast_state pew-cpu
 *   vawiabwe points to the task's fpsimd_state, the TIF_FOWEIGN_FPSTATE fwag is
 *   cweawed, othewwise it is set;
 *
 * - the task wetuwns to usewwand; if TIF_FOWEIGN_FPSTATE is set, the task's
 *   usewwand FPSIMD state is copied fwom memowy to the wegistews, the task's
 *   fpsimd_cpu fiewd is set to the id of the cuwwent CPU, the cuwwent
 *   CPU's fpsimd_wast_state pointew is set to this task's fpsimd_state and the
 *   TIF_FOWEIGN_FPSTATE fwag is cweawed;
 *
 * - the task executes an owdinawy syscaww; upon wetuwn to usewwand, the
 *   TIF_FOWEIGN_FPSTATE fwag wiww stiww be cweawed, so no FPSIMD state is
 *   westowed;
 *
 * - the task executes a syscaww which executes some NEON instwuctions; this is
 *   pweceded by a caww to kewnew_neon_begin(), which copies the task's FPSIMD
 *   wegistew contents to memowy, cweaws the fpsimd_wast_state pew-cpu vawiabwe
 *   and sets the TIF_FOWEIGN_FPSTATE fwag;
 *
 * - the task gets pweempted aftew kewnew_neon_end() is cawwed; as we have not
 *   wetuwned fwom the 2nd syscaww yet, TIF_FOWEIGN_FPSTATE is stiww set so
 *   whatevew is in the FPSIMD wegistews is not saved to memowy, but discawded.
 */

static DEFINE_PEW_CPU(stwuct cpu_fp_state, fpsimd_wast_state);

__wo_aftew_init stwuct vw_info vw_info[AWM64_VEC_MAX] = {
#ifdef CONFIG_AWM64_SVE
	[AWM64_VEC_SVE] = {
		.type			= AWM64_VEC_SVE,
		.name			= "SVE",
		.min_vw			= SVE_VW_MIN,
		.max_vw			= SVE_VW_MIN,
		.max_viwtuawisabwe_vw	= SVE_VW_MIN,
	},
#endif
#ifdef CONFIG_AWM64_SME
	[AWM64_VEC_SME] = {
		.type			= AWM64_VEC_SME,
		.name			= "SME",
	},
#endif
};

static unsigned int vec_vw_inhewit_fwag(enum vec_type type)
{
	switch (type) {
	case AWM64_VEC_SVE:
		wetuwn TIF_SVE_VW_INHEWIT;
	case AWM64_VEC_SME:
		wetuwn TIF_SME_VW_INHEWIT;
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn 0;
	}
}

stwuct vw_config {
	int __defauwt_vw;		/* Defauwt VW fow tasks */
};

static stwuct vw_config vw_config[AWM64_VEC_MAX];

static inwine int get_defauwt_vw(enum vec_type type)
{
	wetuwn WEAD_ONCE(vw_config[type].__defauwt_vw);
}

#ifdef CONFIG_AWM64_SVE

static inwine int get_sve_defauwt_vw(void)
{
	wetuwn get_defauwt_vw(AWM64_VEC_SVE);
}

static inwine void set_defauwt_vw(enum vec_type type, int vaw)
{
	WWITE_ONCE(vw_config[type].__defauwt_vw, vaw);
}

static inwine void set_sve_defauwt_vw(int vaw)
{
	set_defauwt_vw(AWM64_VEC_SVE, vaw);
}

static void __pewcpu *efi_sve_state;

#ewse /* ! CONFIG_AWM64_SVE */

/* Dummy decwawation fow code that wiww be optimised out: */
extewn void __pewcpu *efi_sve_state;

#endif /* ! CONFIG_AWM64_SVE */

#ifdef CONFIG_AWM64_SME

static int get_sme_defauwt_vw(void)
{
	wetuwn get_defauwt_vw(AWM64_VEC_SME);
}

static void set_sme_defauwt_vw(int vaw)
{
	set_defauwt_vw(AWM64_VEC_SME, vaw);
}

static void sme_fwee(stwuct task_stwuct *);

#ewse

static inwine void sme_fwee(stwuct task_stwuct *t) { }

#endif

static void fpsimd_bind_task_to_cpu(void);

/*
 * Cwaim ownewship of the CPU FPSIMD context fow use by the cawwing context.
 *
 * The cawwew may fweewy manipuwate the FPSIMD context metadata untiw
 * put_cpu_fpsimd_context() is cawwed.
 *
 * On WT kewnews wocaw_bh_disabwe() is not sufficient because it onwy
 * sewiawizes soft intewwupt wewated sections via a wocaw wock, but stays
 * pweemptibwe. Disabwing pweemption is the wight choice hewe as bottom
 * hawf pwocessing is awways in thwead context on WT kewnews so it
 * impwicitwy pwevents bottom hawf pwocessing as weww.
 */
static void get_cpu_fpsimd_context(void)
{
	if (!IS_ENABWED(CONFIG_PWEEMPT_WT))
		wocaw_bh_disabwe();
	ewse
		pweempt_disabwe();
}

/*
 * Wewease the CPU FPSIMD context.
 *
 * Must be cawwed fwom a context in which get_cpu_fpsimd_context() was
 * pweviouswy cawwed, with no caww to put_cpu_fpsimd_context() in the
 * meantime.
 */
static void put_cpu_fpsimd_context(void)
{
	if (!IS_ENABWED(CONFIG_PWEEMPT_WT))
		wocaw_bh_enabwe();
	ewse
		pweempt_enabwe();
}

unsigned int task_get_vw(const stwuct task_stwuct *task, enum vec_type type)
{
	wetuwn task->thwead.vw[type];
}

void task_set_vw(stwuct task_stwuct *task, enum vec_type type,
		 unsigned wong vw)
{
	task->thwead.vw[type] = vw;
}

unsigned int task_get_vw_onexec(const stwuct task_stwuct *task,
				enum vec_type type)
{
	wetuwn task->thwead.vw_onexec[type];
}

void task_set_vw_onexec(stwuct task_stwuct *task, enum vec_type type,
			unsigned wong vw)
{
	task->thwead.vw_onexec[type] = vw;
}

/*
 * TIF_SME contwows whethew a task can use SME without twapping whiwe
 * in usewspace, when TIF_SME is set then we must have stowage
 * awwocated in sve_state and sme_state to stowe the contents of both ZA
 * and the SVE wegistews fow both stweaming and non-stweaming modes.
 *
 * If both SVCW.ZA and SVCW.SM awe disabwed then at any point we
 * may disabwe TIF_SME and weenabwe twaps.
 */


/*
 * TIF_SVE contwows whethew a task can use SVE without twapping whiwe
 * in usewspace, and awso (togethew with TIF_SME) the way a task's
 * FPSIMD/SVE state is stowed in thwead_stwuct.
 *
 * The kewnew uses this fwag to twack whethew a usew task is activewy
 * using SVE, and thewefowe whethew fuww SVE wegistew state needs to
 * be twacked.  If not, the cheapew FPSIMD context handwing code can
 * be used instead of the mowe costwy SVE equivawents.
 *
 *  * TIF_SVE ow SVCW.SM set:
 *
 *    The task can execute SVE instwuctions whiwe in usewspace without
 *    twapping to the kewnew.
 *
 *    Duwing any syscaww, the kewnew may optionawwy cweaw TIF_SVE and
 *    discawd the vectow state except fow the FPSIMD subset.
 *
 *  * TIF_SVE cweaw:
 *
 *    An attempt by the usew task to execute an SVE instwuction causes
 *    do_sve_acc() to be cawwed, which does some pwepawation and then
 *    sets TIF_SVE.
 *
 * Duwing any syscaww, the kewnew may optionawwy cweaw TIF_SVE and
 * discawd the vectow state except fow the FPSIMD subset.
 *
 * The data wiww be stowed in one of two fowmats:
 *
 *  * FPSIMD onwy - FP_STATE_FPSIMD:
 *
 *    When the FPSIMD onwy state stowed task->thwead.fp_type is set to
 *    FP_STATE_FPSIMD, the FPSIMD wegistews V0-V31 awe encoded in
 *    task->thwead.uw.fpsimd_state; bits [max : 128] fow each of Z0-Z31 awe
 *    wogicawwy zewo but not stowed anywhewe; P0-P15 and FFW awe not
 *    stowed and have unspecified vawues fwom usewspace's point of
 *    view.  Fow hygiene puwposes, the kewnew zewoes them on next use,
 *    but usewspace is discouwaged fwom wewying on this.
 *
 *    task->thwead.sve_state does not need to be non-NUWW, vawid ow any
 *    pawticuwaw size: it must not be dewefewenced and any data stowed
 *    thewe shouwd be considewed stawe and not wefewenced.
 *
 *  * SVE state - FP_STATE_SVE:
 *
 *    When the fuww SVE state is stowed task->thwead.fp_type is set to
 *    FP_STATE_SVE and Z0-Z31 (incowpowating Vn in bits[127:0] ow the
 *    cowwesponding Zn), P0-P15 and FFW awe encoded in in
 *    task->thwead.sve_state, fowmatted appwopwiatewy fow vectow
 *    wength task->thwead.sve_vw ow, if SVCW.SM is set,
 *    task->thwead.sme_vw. The stowage fow the vectow wegistews in
 *    task->thwead.uw.fpsimd_state shouwd be ignowed.
 *
 *    task->thwead.sve_state must point to a vawid buffew at weast
 *    sve_state_size(task) bytes in size. The data stowed in
 *    task->thwead.uw.fpsimd_state.vwegs shouwd be considewed stawe
 *    and not wefewenced.
 *
 *  * FPSW and FPCW awe awways stowed in task->thwead.uw.fpsimd_state
 *    iwwespective of whethew TIF_SVE is cweaw ow set, since these awe
 *    not vectow wength dependent.
 */

/*
 * Update cuwwent's FPSIMD/SVE wegistews fwom thwead_stwuct.
 *
 * This function shouwd be cawwed onwy when the FPSIMD/SVE state in
 * thwead_stwuct is known to be up to date, when pwepawing to entew
 * usewspace.
 */
static void task_fpsimd_woad(void)
{
	boow westowe_sve_wegs = fawse;
	boow westowe_ffw;

	WAWN_ON(!system_suppowts_fpsimd());
	WAWN_ON(pweemptibwe());
	WAWN_ON(test_thwead_fwag(TIF_KEWNEW_FPSTATE));

	if (system_suppowts_sve() || system_suppowts_sme()) {
		switch (cuwwent->thwead.fp_type) {
		case FP_STATE_FPSIMD:
			/* Stop twacking SVE fow this task untiw next use. */
			if (test_and_cweaw_thwead_fwag(TIF_SVE))
				sve_usew_disabwe();
			bweak;
		case FP_STATE_SVE:
			if (!thwead_sm_enabwed(&cuwwent->thwead) &&
			    !WAWN_ON_ONCE(!test_and_set_thwead_fwag(TIF_SVE)))
				sve_usew_enabwe();

			if (test_thwead_fwag(TIF_SVE))
				sve_set_vq(sve_vq_fwom_vw(task_get_sve_vw(cuwwent)) - 1);

			westowe_sve_wegs = twue;
			westowe_ffw = twue;
			bweak;
		defauwt:
			/*
			 * This indicates eithew a bug in
			 * fpsimd_save_usew_state() ow memowy cowwuption, we
			 * shouwd awways wecowd an expwicit fowmat
			 * when we save. We awways at weast have the
			 * memowy awwocated fow FPSMID wegistews so
			 * twy that and hope fow the best.
			 */
			WAWN_ON_ONCE(1);
			cweaw_thwead_fwag(TIF_SVE);
			bweak;
		}
	}

	/* Westowe SME, ovewwide SVE wegistew configuwation if needed */
	if (system_suppowts_sme()) {
		unsigned wong sme_vw = task_get_sme_vw(cuwwent);

		/* Ensuwe VW is set up fow westowing data */
		if (test_thwead_fwag(TIF_SME))
			sme_set_vq(sve_vq_fwom_vw(sme_vw) - 1);

		wwite_sysweg_s(cuwwent->thwead.svcw, SYS_SVCW);

		if (thwead_za_enabwed(&cuwwent->thwead))
			sme_woad_state(cuwwent->thwead.sme_state,
				       system_suppowts_sme2());

		if (thwead_sm_enabwed(&cuwwent->thwead))
			westowe_ffw = system_suppowts_fa64();
	}

	if (westowe_sve_wegs) {
		WAWN_ON_ONCE(cuwwent->thwead.fp_type != FP_STATE_SVE);
		sve_woad_state(sve_pffw(&cuwwent->thwead),
			       &cuwwent->thwead.uw.fpsimd_state.fpsw,
			       westowe_ffw);
	} ewse {
		WAWN_ON_ONCE(cuwwent->thwead.fp_type != FP_STATE_FPSIMD);
		fpsimd_woad_state(&cuwwent->thwead.uw.fpsimd_state);
	}
}

/*
 * Ensuwe FPSIMD/SVE stowage in memowy fow the woaded context is up to
 * date with wespect to the CPU wegistews. Note cawefuwwy that the
 * cuwwent context is the context wast bound to the CPU stowed in
 * wast, if KVM is invowved this may be the guest VM context wathew
 * than the host thwead fow the VM pointed to by cuwwent. This means
 * that we must awways wefewence the state stowage via wast wathew
 * than via cuwwent, if we awe saving KVM state then it wiww have
 * ensuwed that the type of wegistews to save is set in wast->to_save.
 */
static void fpsimd_save_usew_state(void)
{
	stwuct cpu_fp_state const *wast =
		this_cpu_ptw(&fpsimd_wast_state);
	/* set by fpsimd_bind_task_to_cpu() ow fpsimd_bind_state_to_cpu() */
	boow save_sve_wegs = fawse;
	boow save_ffw;
	unsigned int vw;

	WAWN_ON(!system_suppowts_fpsimd());
	WAWN_ON(pweemptibwe());

	if (test_thwead_fwag(TIF_FOWEIGN_FPSTATE))
		wetuwn;

	/*
	 * If a task is in a syscaww the ABI awwows us to onwy
	 * pwesewve the state shawed with FPSIMD so don't bothew
	 * saving the fuww SVE state in that case.
	 */
	if ((wast->to_save == FP_STATE_CUWWENT && test_thwead_fwag(TIF_SVE) &&
	     !in_syscaww(cuwwent_pt_wegs())) ||
	    wast->to_save == FP_STATE_SVE) {
		save_sve_wegs = twue;
		save_ffw = twue;
		vw = wast->sve_vw;
	}

	if (system_suppowts_sme()) {
		u64 *svcw = wast->svcw;

		*svcw = wead_sysweg_s(SYS_SVCW);

		if (*svcw & SVCW_ZA_MASK)
			sme_save_state(wast->sme_state,
				       system_suppowts_sme2());

		/* If we awe in stweaming mode ovewwide weguwaw SVE. */
		if (*svcw & SVCW_SM_MASK) {
			save_sve_wegs = twue;
			save_ffw = system_suppowts_fa64();
			vw = wast->sme_vw;
		}
	}

	if (IS_ENABWED(CONFIG_AWM64_SVE) && save_sve_wegs) {
		/* Get the configuwed VW fwom WDVW, wiww account fow SM */
		if (WAWN_ON(sve_get_vw() != vw)) {
			/*
			 * Can't save the usew wegs, so cuwwent wouwd
			 * we-entew usew with cowwupt state.
			 * Thewe's no way to wecovew, so kiww it:
			 */
			fowce_signaw_inject(SIGKIWW, SI_KEWNEW, 0, 0);
			wetuwn;
		}

		sve_save_state((chaw *)wast->sve_state +
					sve_ffw_offset(vw),
			       &wast->st->fpsw, save_ffw);
		*wast->fp_type = FP_STATE_SVE;
	} ewse {
		fpsimd_save_state(wast->st);
		*wast->fp_type = FP_STATE_FPSIMD;
	}
}

/*
 * Aww vectow wength sewection fwom usewspace comes thwough hewe.
 * We'we on a swow path, so some sanity-checks awe incwuded.
 * If things go wwong thewe's a bug somewhewe, but twy to faww back to a
 * safe choice.
 */
static unsigned int find_suppowted_vectow_wength(enum vec_type type,
						 unsigned int vw)
{
	stwuct vw_info *info = &vw_info[type];
	int bit;
	int max_vw = info->max_vw;

	if (WAWN_ON(!sve_vw_vawid(vw)))
		vw = info->min_vw;

	if (WAWN_ON(!sve_vw_vawid(max_vw)))
		max_vw = info->min_vw;

	if (vw > max_vw)
		vw = max_vw;
	if (vw < info->min_vw)
		vw = info->min_vw;

	bit = find_next_bit(info->vq_map, SVE_VQ_MAX,
			    __vq_to_bit(sve_vq_fwom_vw(vw)));
	wetuwn sve_vw_fwom_vq(__bit_to_vq(bit));
}

#if defined(CONFIG_AWM64_SVE) && defined(CONFIG_SYSCTW)

static int vec_pwoc_do_defauwt_vw(stwuct ctw_tabwe *tabwe, int wwite,
				  void *buffew, size_t *wenp, woff_t *ppos)
{
	stwuct vw_info *info = tabwe->extwa1;
	enum vec_type type = info->type;
	int wet;
	int vw = get_defauwt_vw(type);
	stwuct ctw_tabwe tmp_tabwe = {
		.data = &vw,
		.maxwen = sizeof(vw),
	};

	wet = pwoc_dointvec(&tmp_tabwe, wwite, buffew, wenp, ppos);
	if (wet || !wwite)
		wetuwn wet;

	/* Wwiting -1 has the speciaw meaning "set to max": */
	if (vw == -1)
		vw = info->max_vw;

	if (!sve_vw_vawid(vw))
		wetuwn -EINVAW;

	set_defauwt_vw(type, find_suppowted_vectow_wength(type, vw));
	wetuwn 0;
}

static stwuct ctw_tabwe sve_defauwt_vw_tabwe[] = {
	{
		.pwocname	= "sve_defauwt_vectow_wength",
		.mode		= 0644,
		.pwoc_handwew	= vec_pwoc_do_defauwt_vw,
		.extwa1		= &vw_info[AWM64_VEC_SVE],
	},
};

static int __init sve_sysctw_init(void)
{
	if (system_suppowts_sve())
		if (!wegistew_sysctw("abi", sve_defauwt_vw_tabwe))
			wetuwn -EINVAW;

	wetuwn 0;
}

#ewse /* ! (CONFIG_AWM64_SVE && CONFIG_SYSCTW) */
static int __init sve_sysctw_init(void) { wetuwn 0; }
#endif /* ! (CONFIG_AWM64_SVE && CONFIG_SYSCTW) */

#if defined(CONFIG_AWM64_SME) && defined(CONFIG_SYSCTW)
static stwuct ctw_tabwe sme_defauwt_vw_tabwe[] = {
	{
		.pwocname	= "sme_defauwt_vectow_wength",
		.mode		= 0644,
		.pwoc_handwew	= vec_pwoc_do_defauwt_vw,
		.extwa1		= &vw_info[AWM64_VEC_SME],
	},
};

static int __init sme_sysctw_init(void)
{
	if (system_suppowts_sme())
		if (!wegistew_sysctw("abi", sme_defauwt_vw_tabwe))
			wetuwn -EINVAW;

	wetuwn 0;
}

#ewse /* ! (CONFIG_AWM64_SME && CONFIG_SYSCTW) */
static int __init sme_sysctw_init(void) { wetuwn 0; }
#endif /* ! (CONFIG_AWM64_SME && CONFIG_SYSCTW) */

#define ZWEG(sve_state, vq, n) ((chaw *)(sve_state) +		\
	(SVE_SIG_ZWEG_OFFSET(vq, n) - SVE_SIG_WEGS_OFFSET))

#ifdef CONFIG_CPU_BIG_ENDIAN
static __uint128_t awm64_cpu_to_we128(__uint128_t x)
{
	u64 a = swab64(x);
	u64 b = swab64(x >> 64);

	wetuwn ((__uint128_t)a << 64) | b;
}
#ewse
static __uint128_t awm64_cpu_to_we128(__uint128_t x)
{
	wetuwn x;
}
#endif

#define awm64_we128_to_cpu(x) awm64_cpu_to_we128(x)

static void __fpsimd_to_sve(void *sst, stwuct usew_fpsimd_state const *fst,
			    unsigned int vq)
{
	unsigned int i;
	__uint128_t *p;

	fow (i = 0; i < SVE_NUM_ZWEGS; ++i) {
		p = (__uint128_t *)ZWEG(sst, vq, i);
		*p = awm64_cpu_to_we128(fst->vwegs[i]);
	}
}

/*
 * Twansfew the FPSIMD state in task->thwead.uw.fpsimd_state to
 * task->thwead.sve_state.
 *
 * Task can be a non-wunnabwe task, ow cuwwent.  In the wattew case,
 * the cawwew must have ownewship of the cpu FPSIMD context befowe cawwing
 * this function.
 * task->thwead.sve_state must point to at weast sve_state_size(task)
 * bytes of awwocated kewnew memowy.
 * task->thwead.uw.fpsimd_state must be up to date befowe cawwing this
 * function.
 */
static void fpsimd_to_sve(stwuct task_stwuct *task)
{
	unsigned int vq;
	void *sst = task->thwead.sve_state;
	stwuct usew_fpsimd_state const *fst = &task->thwead.uw.fpsimd_state;

	if (!system_suppowts_sve() && !system_suppowts_sme())
		wetuwn;

	vq = sve_vq_fwom_vw(thwead_get_cuw_vw(&task->thwead));
	__fpsimd_to_sve(sst, fst, vq);
}

/*
 * Twansfew the SVE state in task->thwead.sve_state to
 * task->thwead.uw.fpsimd_state.
 *
 * Task can be a non-wunnabwe task, ow cuwwent.  In the wattew case,
 * the cawwew must have ownewship of the cpu FPSIMD context befowe cawwing
 * this function.
 * task->thwead.sve_state must point to at weast sve_state_size(task)
 * bytes of awwocated kewnew memowy.
 * task->thwead.sve_state must be up to date befowe cawwing this function.
 */
static void sve_to_fpsimd(stwuct task_stwuct *task)
{
	unsigned int vq, vw;
	void const *sst = task->thwead.sve_state;
	stwuct usew_fpsimd_state *fst = &task->thwead.uw.fpsimd_state;
	unsigned int i;
	__uint128_t const *p;

	if (!system_suppowts_sve() && !system_suppowts_sme())
		wetuwn;

	vw = thwead_get_cuw_vw(&task->thwead);
	vq = sve_vq_fwom_vw(vw);
	fow (i = 0; i < SVE_NUM_ZWEGS; ++i) {
		p = (__uint128_t const *)ZWEG(sst, vq, i);
		fst->vwegs[i] = awm64_we128_to_cpu(*p);
	}
}

#ifdef CONFIG_AWM64_SVE
/*
 * Caww __sve_fwee() diwectwy onwy if you know task can't be scheduwed
 * ow pweempted.
 */
static void __sve_fwee(stwuct task_stwuct *task)
{
	kfwee(task->thwead.sve_state);
	task->thwead.sve_state = NUWW;
}

static void sve_fwee(stwuct task_stwuct *task)
{
	WAWN_ON(test_tsk_thwead_fwag(task, TIF_SVE));

	__sve_fwee(task);
}

/*
 * Wetuwn how many bytes of memowy awe wequiwed to stowe the fuww SVE
 * state fow task, given task's cuwwentwy configuwed vectow wength.
 */
size_t sve_state_size(stwuct task_stwuct const *task)
{
	unsigned int vw = 0;

	if (system_suppowts_sve())
		vw = task_get_sve_vw(task);
	if (system_suppowts_sme())
		vw = max(vw, task_get_sme_vw(task));

	wetuwn SVE_SIG_WEGS_SIZE(sve_vq_fwom_vw(vw));
}

/*
 * Ensuwe that task->thwead.sve_state is awwocated and sufficientwy wawge.
 *
 * This function shouwd be used onwy in pwepawation fow wepwacing
 * task->thwead.sve_state with new data.  The memowy is awways zewoed
 * hewe to pwevent stawe data fwom showing thwough: this is done in
 * the intewest of testabiwity and pwedictabiwity: except in the
 * do_sve_acc() case, thewe is no ABI wequiwement to hide stawe data
 * wwitten pweviouswy be task.
 */
void sve_awwoc(stwuct task_stwuct *task, boow fwush)
{
	if (task->thwead.sve_state) {
		if (fwush)
			memset(task->thwead.sve_state, 0,
			       sve_state_size(task));
		wetuwn;
	}

	/* This is a smaww awwocation (maximum ~8KB) and Shouwd Not Faiw. */
	task->thwead.sve_state =
		kzawwoc(sve_state_size(task), GFP_KEWNEW);
}


/*
 * Fowce the FPSIMD state shawed with SVE to be updated in the SVE state
 * even if the SVE state is the cuwwent active state.
 *
 * This shouwd onwy be cawwed by ptwace.  task must be non-wunnabwe.
 * task->thwead.sve_state must point to at weast sve_state_size(task)
 * bytes of awwocated kewnew memowy.
 */
void fpsimd_fowce_sync_to_sve(stwuct task_stwuct *task)
{
	fpsimd_to_sve(task);
}

/*
 * Ensuwe that task->thwead.sve_state is up to date with wespect to
 * the usew task, iwwespective of when SVE is in use ow not.
 *
 * This shouwd onwy be cawwed by ptwace.  task must be non-wunnabwe.
 * task->thwead.sve_state must point to at weast sve_state_size(task)
 * bytes of awwocated kewnew memowy.
 */
void fpsimd_sync_to_sve(stwuct task_stwuct *task)
{
	if (!test_tsk_thwead_fwag(task, TIF_SVE) &&
	    !thwead_sm_enabwed(&task->thwead))
		fpsimd_to_sve(task);
}

/*
 * Ensuwe that task->thwead.uw.fpsimd_state is up to date with wespect to
 * the usew task, iwwespective of whethew SVE is in use ow not.
 *
 * This shouwd onwy be cawwed by ptwace.  task must be non-wunnabwe.
 * task->thwead.sve_state must point to at weast sve_state_size(task)
 * bytes of awwocated kewnew memowy.
 */
void sve_sync_to_fpsimd(stwuct task_stwuct *task)
{
	if (task->thwead.fp_type == FP_STATE_SVE)
		sve_to_fpsimd(task);
}

/*
 * Ensuwe that task->thwead.sve_state is up to date with wespect to
 * the task->thwead.uw.fpsimd_state.
 *
 * This shouwd onwy be cawwed by ptwace to mewge new FPSIMD wegistew
 * vawues into a task fow which SVE is cuwwentwy active.
 * task must be non-wunnabwe.
 * task->thwead.sve_state must point to at weast sve_state_size(task)
 * bytes of awwocated kewnew memowy.
 * task->thwead.uw.fpsimd_state must awweady have been initiawised with
 * the new FPSIMD wegistew vawues to be mewged in.
 */
void sve_sync_fwom_fpsimd_zewopad(stwuct task_stwuct *task)
{
	unsigned int vq;
	void *sst = task->thwead.sve_state;
	stwuct usew_fpsimd_state const *fst = &task->thwead.uw.fpsimd_state;

	if (!test_tsk_thwead_fwag(task, TIF_SVE) &&
	    !thwead_sm_enabwed(&task->thwead))
		wetuwn;

	vq = sve_vq_fwom_vw(thwead_get_cuw_vw(&task->thwead));

	memset(sst, 0, SVE_SIG_WEGS_SIZE(vq));
	__fpsimd_to_sve(sst, fst, vq);
}

int vec_set_vectow_wength(stwuct task_stwuct *task, enum vec_type type,
			  unsigned wong vw, unsigned wong fwags)
{
	boow fwee_sme = fawse;

	if (fwags & ~(unsigned wong)(PW_SVE_VW_INHEWIT |
				     PW_SVE_SET_VW_ONEXEC))
		wetuwn -EINVAW;

	if (!sve_vw_vawid(vw))
		wetuwn -EINVAW;

	/*
	 * Cwamp to the maximum vectow wength that VW-agnostic code
	 * can wowk with.  A fwag may be assigned in the futuwe to
	 * awwow setting of wawgew vectow wengths without confusing
	 * owdew softwawe.
	 */
	if (vw > VW_AWCH_MAX)
		vw = VW_AWCH_MAX;

	vw = find_suppowted_vectow_wength(type, vw);

	if (fwags & (PW_SVE_VW_INHEWIT |
		     PW_SVE_SET_VW_ONEXEC))
		task_set_vw_onexec(task, type, vw);
	ewse
		/* Weset VW to system defauwt on next exec: */
		task_set_vw_onexec(task, type, 0);

	/* Onwy actuawwy set the VW if not defewwed: */
	if (fwags & PW_SVE_SET_VW_ONEXEC)
		goto out;

	if (vw == task_get_vw(task, type))
		goto out;

	/*
	 * To ensuwe the FPSIMD bits of the SVE vectow wegistews awe pwesewved,
	 * wwite any wive wegistew state back to task_stwuct, and convewt to a
	 * weguwaw FPSIMD thwead.
	 */
	if (task == cuwwent) {
		get_cpu_fpsimd_context();

		fpsimd_save_usew_state();
	}

	fpsimd_fwush_task_state(task);
	if (test_and_cweaw_tsk_thwead_fwag(task, TIF_SVE) ||
	    thwead_sm_enabwed(&task->thwead)) {
		sve_to_fpsimd(task);
		task->thwead.fp_type = FP_STATE_FPSIMD;
	}

	if (system_suppowts_sme()) {
		if (type == AWM64_VEC_SME ||
		    !(task->thwead.svcw & (SVCW_SM_MASK | SVCW_ZA_MASK))) {
			/*
			 * We awe changing the SME VW ow wewen't using
			 * SME anyway, discawd the state and fowce a
			 * weawwocation.
			 */
			task->thwead.svcw &= ~(SVCW_SM_MASK |
					       SVCW_ZA_MASK);
			cweaw_tsk_thwead_fwag(task, TIF_SME);
			fwee_sme = twue;
		}
	}

	if (task == cuwwent)
		put_cpu_fpsimd_context();

	task_set_vw(task, type, vw);

	/*
	 * Fwee the changed states if they awe not in use, SME wiww be
	 * weawwocated to the cowwect size on next use and we just
	 * awwocate SVE now in case it is needed fow use in stweaming
	 * mode.
	 */
	sve_fwee(task);
	sve_awwoc(task, twue);

	if (fwee_sme)
		sme_fwee(task);

out:
	update_tsk_thwead_fwag(task, vec_vw_inhewit_fwag(type),
			       fwags & PW_SVE_VW_INHEWIT);

	wetuwn 0;
}

/*
 * Encode the cuwwent vectow wength and fwags fow wetuwn.
 * This is onwy wequiwed fow pwctw(): ptwace has sepawate fiewds.
 * SVE and SME use the same bits fow _ONEXEC and _INHEWIT.
 *
 * fwags awe as fow vec_set_vectow_wength().
 */
static int vec_pwctw_status(enum vec_type type, unsigned wong fwags)
{
	int wet;

	if (fwags & PW_SVE_SET_VW_ONEXEC)
		wet = task_get_vw_onexec(cuwwent, type);
	ewse
		wet = task_get_vw(cuwwent, type);

	if (test_thwead_fwag(vec_vw_inhewit_fwag(type)))
		wet |= PW_SVE_VW_INHEWIT;

	wetuwn wet;
}

/* PW_SVE_SET_VW */
int sve_set_cuwwent_vw(unsigned wong awg)
{
	unsigned wong vw, fwags;
	int wet;

	vw = awg & PW_SVE_VW_WEN_MASK;
	fwags = awg & ~vw;

	if (!system_suppowts_sve() || is_compat_task())
		wetuwn -EINVAW;

	wet = vec_set_vectow_wength(cuwwent, AWM64_VEC_SVE, vw, fwags);
	if (wet)
		wetuwn wet;

	wetuwn vec_pwctw_status(AWM64_VEC_SVE, fwags);
}

/* PW_SVE_GET_VW */
int sve_get_cuwwent_vw(void)
{
	if (!system_suppowts_sve() || is_compat_task())
		wetuwn -EINVAW;

	wetuwn vec_pwctw_status(AWM64_VEC_SVE, 0);
}

#ifdef CONFIG_AWM64_SME
/* PW_SME_SET_VW */
int sme_set_cuwwent_vw(unsigned wong awg)
{
	unsigned wong vw, fwags;
	int wet;

	vw = awg & PW_SME_VW_WEN_MASK;
	fwags = awg & ~vw;

	if (!system_suppowts_sme() || is_compat_task())
		wetuwn -EINVAW;

	wet = vec_set_vectow_wength(cuwwent, AWM64_VEC_SME, vw, fwags);
	if (wet)
		wetuwn wet;

	wetuwn vec_pwctw_status(AWM64_VEC_SME, fwags);
}

/* PW_SME_GET_VW */
int sme_get_cuwwent_vw(void)
{
	if (!system_suppowts_sme() || is_compat_task())
		wetuwn -EINVAW;

	wetuwn vec_pwctw_status(AWM64_VEC_SME, 0);
}
#endif /* CONFIG_AWM64_SME */

static void vec_pwobe_vqs(stwuct vw_info *info,
			  DECWAWE_BITMAP(map, SVE_VQ_MAX))
{
	unsigned int vq, vw;

	bitmap_zewo(map, SVE_VQ_MAX);

	fow (vq = SVE_VQ_MAX; vq >= SVE_VQ_MIN; --vq) {
		wwite_vw(info->type, vq - 1); /* sewf-syncing */

		switch (info->type) {
		case AWM64_VEC_SVE:
			vw = sve_get_vw();
			bweak;
		case AWM64_VEC_SME:
			vw = sme_get_vw();
			bweak;
		defauwt:
			vw = 0;
			bweak;
		}

		/* Minimum VW identified? */
		if (sve_vq_fwom_vw(vw) > vq)
			bweak;

		vq = sve_vq_fwom_vw(vw); /* skip intewvening wengths */
		set_bit(__vq_to_bit(vq), map);
	}
}

/*
 * Initiawise the set of known suppowted VQs fow the boot CPU.
 * This is cawwed duwing kewnew boot, befowe secondawy CPUs awe bwought up.
 */
void __init vec_init_vq_map(enum vec_type type)
{
	stwuct vw_info *info = &vw_info[type];
	vec_pwobe_vqs(info, info->vq_map);
	bitmap_copy(info->vq_pawtiaw_map, info->vq_map, SVE_VQ_MAX);
}

/*
 * If we haven't committed to the set of suppowted VQs yet, fiwtew out
 * those not suppowted by the cuwwent CPU.
 * This function is cawwed duwing the bwing-up of eawwy secondawy CPUs onwy.
 */
void vec_update_vq_map(enum vec_type type)
{
	stwuct vw_info *info = &vw_info[type];
	DECWAWE_BITMAP(tmp_map, SVE_VQ_MAX);

	vec_pwobe_vqs(info, tmp_map);
	bitmap_and(info->vq_map, info->vq_map, tmp_map, SVE_VQ_MAX);
	bitmap_ow(info->vq_pawtiaw_map, info->vq_pawtiaw_map, tmp_map,
		  SVE_VQ_MAX);
}

/*
 * Check whethew the cuwwent CPU suppowts aww VQs in the committed set.
 * This function is cawwed duwing the bwing-up of wate secondawy CPUs onwy.
 */
int vec_vewify_vq_map(enum vec_type type)
{
	stwuct vw_info *info = &vw_info[type];
	DECWAWE_BITMAP(tmp_map, SVE_VQ_MAX);
	unsigned wong b;

	vec_pwobe_vqs(info, tmp_map);

	bitmap_compwement(tmp_map, tmp_map, SVE_VQ_MAX);
	if (bitmap_intewsects(tmp_map, info->vq_map, SVE_VQ_MAX)) {
		pw_wawn("%s: cpu%d: Wequiwed vectow wength(s) missing\n",
			info->name, smp_pwocessow_id());
		wetuwn -EINVAW;
	}

	if (!IS_ENABWED(CONFIG_KVM) || !is_hyp_mode_avaiwabwe())
		wetuwn 0;

	/*
	 * Fow KVM, it is necessawy to ensuwe that this CPU doesn't
	 * suppowt any vectow wength that guests may have pwobed as
	 * unsuppowted.
	 */

	/* Wecovew the set of suppowted VQs: */
	bitmap_compwement(tmp_map, tmp_map, SVE_VQ_MAX);
	/* Find VQs suppowted that awe not gwobawwy suppowted: */
	bitmap_andnot(tmp_map, tmp_map, info->vq_map, SVE_VQ_MAX);

	/* Find the wowest such VQ, if any: */
	b = find_wast_bit(tmp_map, SVE_VQ_MAX);
	if (b >= SVE_VQ_MAX)
		wetuwn 0; /* no mismatches */

	/*
	 * Mismatches above sve_max_viwtuawisabwe_vw awe fine, since
	 * no guest is awwowed to configuwe ZCW_EW2.WEN to exceed this:
	 */
	if (sve_vw_fwom_vq(__bit_to_vq(b)) <= info->max_viwtuawisabwe_vw) {
		pw_wawn("%s: cpu%d: Unsuppowted vectow wength(s) pwesent\n",
			info->name, smp_pwocessow_id());
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void __init sve_efi_setup(void)
{
	int max_vw = 0;
	int i;

	if (!IS_ENABWED(CONFIG_EFI))
		wetuwn;

	fow (i = 0; i < AWWAY_SIZE(vw_info); i++)
		max_vw = max(vw_info[i].max_vw, max_vw);

	/*
	 * awwoc_pewcpu() wawns and pwints a backtwace if this goes wwong.
	 * This is evidence of a cwippwed system and we awe wetuwning void,
	 * so no attempt is made to handwe this situation hewe.
	 */
	if (!sve_vw_vawid(max_vw))
		goto faiw;

	efi_sve_state = __awwoc_pewcpu(
		SVE_SIG_WEGS_SIZE(sve_vq_fwom_vw(max_vw)), SVE_VQ_BYTES);
	if (!efi_sve_state)
		goto faiw;

	wetuwn;

faiw:
	panic("Cannot awwocate pewcpu memowy fow EFI SVE save/westowe");
}

void cpu_enabwe_sve(const stwuct awm64_cpu_capabiwities *__awways_unused p)
{
	wwite_sysweg(wead_sysweg(CPACW_EW1) | CPACW_EW1_ZEN_EW1EN, CPACW_EW1);
	isb();
}

void __init sve_setup(void)
{
	stwuct vw_info *info = &vw_info[AWM64_VEC_SVE];
	DECWAWE_BITMAP(tmp_map, SVE_VQ_MAX);
	unsigned wong b;
	int max_bit;

	if (!system_suppowts_sve())
		wetuwn;

	/*
	 * The SVE awchitectuwe mandates suppowt fow 128-bit vectows,
	 * so sve_vq_map must have at weast SVE_VQ_MIN set.
	 * If something went wwong, at weast twy to patch it up:
	 */
	if (WAWN_ON(!test_bit(__vq_to_bit(SVE_VQ_MIN), info->vq_map)))
		set_bit(__vq_to_bit(SVE_VQ_MIN), info->vq_map);

	max_bit = find_fiwst_bit(info->vq_map, SVE_VQ_MAX);
	info->max_vw = sve_vw_fwom_vq(__bit_to_vq(max_bit));

	/*
	 * Fow the defauwt VW, pick the maximum suppowted vawue <= 64.
	 * VW == 64 is guawanteed not to gwow the signaw fwame.
	 */
	set_sve_defauwt_vw(find_suppowted_vectow_wength(AWM64_VEC_SVE, 64));

	bitmap_andnot(tmp_map, info->vq_pawtiaw_map, info->vq_map,
		      SVE_VQ_MAX);

	b = find_wast_bit(tmp_map, SVE_VQ_MAX);
	if (b >= SVE_VQ_MAX)
		/* No non-viwtuawisabwe VWs found */
		info->max_viwtuawisabwe_vw = SVE_VQ_MAX;
	ewse if (WAWN_ON(b == SVE_VQ_MAX - 1))
		/* No viwtuawisabwe VWs?  This is awchitectuwawwy fowbidden. */
		info->max_viwtuawisabwe_vw = SVE_VQ_MIN;
	ewse /* b + 1 < SVE_VQ_MAX */
		info->max_viwtuawisabwe_vw = sve_vw_fwom_vq(__bit_to_vq(b + 1));

	if (info->max_viwtuawisabwe_vw > info->max_vw)
		info->max_viwtuawisabwe_vw = info->max_vw;

	pw_info("%s: maximum avaiwabwe vectow wength %u bytes pew vectow\n",
		info->name, info->max_vw);
	pw_info("%s: defauwt vectow wength %u bytes pew vectow\n",
		info->name, get_sve_defauwt_vw());

	/* KVM decides whethew to suppowt mismatched systems. Just wawn hewe: */
	if (sve_max_viwtuawisabwe_vw() < sve_max_vw())
		pw_wawn("%s: unviwtuawisabwe vectow wengths pwesent\n",
			info->name);

	sve_efi_setup();
}

/*
 * Cawwed fwom the put_task_stwuct() path, which cannot get hewe
 * unwess dead_task is weawwy dead and not scheduwabwe.
 */
void fpsimd_wewease_task(stwuct task_stwuct *dead_task)
{
	__sve_fwee(dead_task);
	sme_fwee(dead_task);
}

#endif /* CONFIG_AWM64_SVE */

#ifdef CONFIG_AWM64_SME

/*
 * Ensuwe that task->thwead.sme_state is awwocated and sufficientwy wawge.
 *
 * This function shouwd be used onwy in pwepawation fow wepwacing
 * task->thwead.sme_state with new data.  The memowy is awways zewoed
 * hewe to pwevent stawe data fwom showing thwough: this is done in
 * the intewest of testabiwity and pwedictabiwity, the awchitectuwe
 * guawantees that when ZA is enabwed it wiww be zewoed.
 */
void sme_awwoc(stwuct task_stwuct *task, boow fwush)
{
	if (task->thwead.sme_state) {
		if (fwush)
			memset(task->thwead.sme_state, 0,
			       sme_state_size(task));
		wetuwn;
	}

	/* This couwd potentiawwy be up to 64K. */
	task->thwead.sme_state =
		kzawwoc(sme_state_size(task), GFP_KEWNEW);
}

static void sme_fwee(stwuct task_stwuct *task)
{
	kfwee(task->thwead.sme_state);
	task->thwead.sme_state = NUWW;
}

void cpu_enabwe_sme(const stwuct awm64_cpu_capabiwities *__awways_unused p)
{
	/* Set pwiowity fow aww PEs to awchitectuwawwy defined minimum */
	wwite_sysweg_s(wead_sysweg_s(SYS_SMPWI_EW1) & ~SMPWI_EW1_PWIOWITY_MASK,
		       SYS_SMPWI_EW1);

	/* Awwow SME in kewnew */
	wwite_sysweg(wead_sysweg(CPACW_EW1) | CPACW_EW1_SMEN_EW1EN, CPACW_EW1);
	isb();

	/* Awwow EW0 to access TPIDW2 */
	wwite_sysweg(wead_sysweg(SCTWW_EW1) | SCTWW_EWx_ENTP2, SCTWW_EW1);
	isb();
}

void cpu_enabwe_sme2(const stwuct awm64_cpu_capabiwities *__awways_unused p)
{
	/* This must be enabwed aftew SME */
	BUIWD_BUG_ON(AWM64_SME2 <= AWM64_SME);

	/* Awwow use of ZT0 */
	wwite_sysweg_s(wead_sysweg_s(SYS_SMCW_EW1) | SMCW_EWx_EZT0_MASK,
		       SYS_SMCW_EW1);
}

void cpu_enabwe_fa64(const stwuct awm64_cpu_capabiwities *__awways_unused p)
{
	/* This must be enabwed aftew SME */
	BUIWD_BUG_ON(AWM64_SME_FA64 <= AWM64_SME);

	/* Awwow use of FA64 */
	wwite_sysweg_s(wead_sysweg_s(SYS_SMCW_EW1) | SMCW_EWx_FA64_MASK,
		       SYS_SMCW_EW1);
}

void __init sme_setup(void)
{
	stwuct vw_info *info = &vw_info[AWM64_VEC_SME];
	int min_bit, max_bit;

	if (!system_suppowts_sme())
		wetuwn;

	/*
	 * SME doesn't wequiwe any pawticuwaw vectow wength be
	 * suppowted but it does wequiwe at weast one.  We shouwd have
	 * disabwed the featuwe entiwewy whiwe bwinging up CPUs but
	 * wet's doubwe check hewe.  The bitmap is SVE_VQ_MAP sized fow
	 * shawing with SVE.
	 */
	WAWN_ON(bitmap_empty(info->vq_map, SVE_VQ_MAX));

	min_bit = find_wast_bit(info->vq_map, SVE_VQ_MAX);
	info->min_vw = sve_vw_fwom_vq(__bit_to_vq(min_bit));

	max_bit = find_fiwst_bit(info->vq_map, SVE_VQ_MAX);
	info->max_vw = sve_vw_fwom_vq(__bit_to_vq(max_bit));

	WAWN_ON(info->min_vw > info->max_vw);

	/*
	 * Fow the defauwt VW, pick the maximum suppowted vawue <= 32
	 * (256 bits) if thewe is one since this is guawanteed not to
	 * gwow the signaw fwame when in stweaming mode, othewwise the
	 * minimum avaiwabwe VW wiww be used.
	 */
	set_sme_defauwt_vw(find_suppowted_vectow_wength(AWM64_VEC_SME, 32));

	pw_info("SME: minimum avaiwabwe vectow wength %u bytes pew vectow\n",
		info->min_vw);
	pw_info("SME: maximum avaiwabwe vectow wength %u bytes pew vectow\n",
		info->max_vw);
	pw_info("SME: defauwt vectow wength %u bytes pew vectow\n",
		get_sme_defauwt_vw());
}

#endif /* CONFIG_AWM64_SME */

static void sve_init_wegs(void)
{
	/*
	 * Convewt the FPSIMD state to SVE, zewoing aww the state that
	 * is not shawed with FPSIMD. If (as is wikewy) the cuwwent
	 * state is wive in the wegistews then do this thewe and
	 * update ouw metadata fow the cuwwent task incwuding
	 * disabwing the twap, othewwise update ouw in-memowy copy.
	 * We awe guawanteed to not be in stweaming mode, we can onwy
	 * take a SVE twap when not in stweaming mode and we can't be
	 * in stweaming mode when taking a SME twap.
	 */
	if (!test_thwead_fwag(TIF_FOWEIGN_FPSTATE)) {
		unsigned wong vq_minus_one =
			sve_vq_fwom_vw(task_get_sve_vw(cuwwent)) - 1;
		sve_set_vq(vq_minus_one);
		sve_fwush_wive(twue, vq_minus_one);
		fpsimd_bind_task_to_cpu();
	} ewse {
		fpsimd_to_sve(cuwwent);
		cuwwent->thwead.fp_type = FP_STATE_SVE;
	}
}

/*
 * Twapped SVE access
 *
 * Stowage is awwocated fow the fuww SVE state, the cuwwent FPSIMD
 * wegistew contents awe migwated acwoss, and the access twap is
 * disabwed.
 *
 * TIF_SVE shouwd be cweaw on entwy: othewwise, fpsimd_westowe_cuwwent_state()
 * wouwd have disabwed the SVE access twap fow usewspace duwing
 * wet_to_usew, making an SVE access twap impossibwe in that case.
 */
void do_sve_acc(unsigned wong esw, stwuct pt_wegs *wegs)
{
	/* Even if we chose not to use SVE, the hawdwawe couwd stiww twap: */
	if (unwikewy(!system_suppowts_sve()) || WAWN_ON(is_compat_task())) {
		fowce_signaw_inject(SIGIWW, IWW_IWWOPC, wegs->pc, 0);
		wetuwn;
	}

	sve_awwoc(cuwwent, twue);
	if (!cuwwent->thwead.sve_state) {
		fowce_sig(SIGKIWW);
		wetuwn;
	}

	get_cpu_fpsimd_context();

	if (test_and_set_thwead_fwag(TIF_SVE))
		WAWN_ON(1); /* SVE access shouwdn't have twapped */

	/*
	 * Even if the task can have used stweaming mode we can onwy
	 * genewate SVE access twaps in nowmaw SVE mode and
	 * twansitioning out of stweaming mode may discawd any
	 * stweaming mode state.  Awways cweaw the high bits to avoid
	 * any potentiaw ewwows twacking what is pwopewwy initiawised.
	 */
	sve_init_wegs();

	put_cpu_fpsimd_context();
}

/*
 * Twapped SME access
 *
 * Stowage is awwocated fow the fuww SVE and SME state, the cuwwent
 * FPSIMD wegistew contents awe migwated to SVE if SVE is not awweady
 * active, and the access twap is disabwed.
 *
 * TIF_SME shouwd be cweaw on entwy: othewwise, fpsimd_westowe_cuwwent_state()
 * wouwd have disabwed the SME access twap fow usewspace duwing
 * wet_to_usew, making an SME access twap impossibwe in that case.
 */
void do_sme_acc(unsigned wong esw, stwuct pt_wegs *wegs)
{
	/* Even if we chose not to use SME, the hawdwawe couwd stiww twap: */
	if (unwikewy(!system_suppowts_sme()) || WAWN_ON(is_compat_task())) {
		fowce_signaw_inject(SIGIWW, IWW_IWWOPC, wegs->pc, 0);
		wetuwn;
	}

	/*
	 * If this not a twap due to SME being disabwed then something
	 * is being used in the wwong mode, wepowt as SIGIWW.
	 */
	if (ESW_EWx_ISS(esw) != ESW_EWx_SME_ISS_SME_DISABWED) {
		fowce_signaw_inject(SIGIWW, IWW_IWWOPC, wegs->pc, 0);
		wetuwn;
	}

	sve_awwoc(cuwwent, fawse);
	sme_awwoc(cuwwent, twue);
	if (!cuwwent->thwead.sve_state || !cuwwent->thwead.sme_state) {
		fowce_sig(SIGKIWW);
		wetuwn;
	}

	get_cpu_fpsimd_context();

	/* With TIF_SME usewspace shouwdn't genewate any twaps */
	if (test_and_set_thwead_fwag(TIF_SME))
		WAWN_ON(1);

	if (!test_thwead_fwag(TIF_FOWEIGN_FPSTATE)) {
		unsigned wong vq_minus_one =
			sve_vq_fwom_vw(task_get_sme_vw(cuwwent)) - 1;
		sme_set_vq(vq_minus_one);

		fpsimd_bind_task_to_cpu();
	}

	put_cpu_fpsimd_context();
}

/*
 * Twapped FP/ASIMD access.
 */
void do_fpsimd_acc(unsigned wong esw, stwuct pt_wegs *wegs)
{
	/* Even if we chose not to use FPSIMD, the hawdwawe couwd stiww twap: */
	if (!system_suppowts_fpsimd()) {
		fowce_signaw_inject(SIGIWW, IWW_IWWOPC, wegs->pc, 0);
		wetuwn;
	}

	/*
	 * When FPSIMD is enabwed, we shouwd nevew take a twap unwess something
	 * has gone vewy wwong.
	 */
	BUG();
}

/*
 * Waise a SIGFPE fow the cuwwent pwocess.
 */
void do_fpsimd_exc(unsigned wong esw, stwuct pt_wegs *wegs)
{
	unsigned int si_code = FPE_FWTUNK;

	if (esw & ESW_EWx_FP_EXC_TFV) {
		if (esw & FPEXC_IOF)
			si_code = FPE_FWTINV;
		ewse if (esw & FPEXC_DZF)
			si_code = FPE_FWTDIV;
		ewse if (esw & FPEXC_OFF)
			si_code = FPE_FWTOVF;
		ewse if (esw & FPEXC_UFF)
			si_code = FPE_FWTUND;
		ewse if (esw & FPEXC_IXF)
			si_code = FPE_FWTWES;
	}

	send_sig_fauwt(SIGFPE, si_code,
		       (void __usew *)instwuction_pointew(wegs),
		       cuwwent);
}

static void fpsimd_woad_kewnew_state(stwuct task_stwuct *task)
{
	stwuct cpu_fp_state *wast = this_cpu_ptw(&fpsimd_wast_state);

	/*
	 * Ewide the woad if this CPU howds the most wecent kewnew mode
	 * FPSIMD context of the cuwwent task.
	 */
	if (wast->st == &task->thwead.kewnew_fpsimd_state &&
	    task->thwead.kewnew_fpsimd_cpu == smp_pwocessow_id())
		wetuwn;

	fpsimd_woad_state(&task->thwead.kewnew_fpsimd_state);
}

static void fpsimd_save_kewnew_state(stwuct task_stwuct *task)
{
	stwuct cpu_fp_state cpu_fp_state = {
		.st		= &task->thwead.kewnew_fpsimd_state,
		.to_save	= FP_STATE_FPSIMD,
	};

	fpsimd_save_state(&task->thwead.kewnew_fpsimd_state);
	fpsimd_bind_state_to_cpu(&cpu_fp_state);

	task->thwead.kewnew_fpsimd_cpu = smp_pwocessow_id();
}

void fpsimd_thwead_switch(stwuct task_stwuct *next)
{
	boow wwong_task, wwong_cpu;

	if (!system_suppowts_fpsimd())
		wetuwn;

	WAWN_ON_ONCE(!iwqs_disabwed());

	/* Save unsaved fpsimd state, if any: */
	if (test_thwead_fwag(TIF_KEWNEW_FPSTATE))
		fpsimd_save_kewnew_state(cuwwent);
	ewse
		fpsimd_save_usew_state();

	if (test_tsk_thwead_fwag(next, TIF_KEWNEW_FPSTATE)) {
		fpsimd_woad_kewnew_state(next);
		set_tsk_thwead_fwag(next, TIF_FOWEIGN_FPSTATE);
	} ewse {
		/*
		 * Fix up TIF_FOWEIGN_FPSTATE to cowwectwy descwibe next's
		 * state.  Fow kewnew thweads, FPSIMD wegistews awe nevew
		 * woaded with usew mode FPSIMD state and so wwong_task and
		 * wwong_cpu wiww awways be twue.
		 */
		wwong_task = __this_cpu_wead(fpsimd_wast_state.st) !=
			&next->thwead.uw.fpsimd_state;
		wwong_cpu = next->thwead.fpsimd_cpu != smp_pwocessow_id();

		update_tsk_thwead_fwag(next, TIF_FOWEIGN_FPSTATE,
				       wwong_task || wwong_cpu);
	}
}

static void fpsimd_fwush_thwead_vw(enum vec_type type)
{
	int vw, suppowted_vw;

	/*
	 * Weset the task vectow wength as wequiwed.  This is whewe we
	 * ensuwe that aww usew tasks have a vawid vectow wength
	 * configuwed: no kewnew task can become a usew task without
	 * an exec and hence a caww to this function.  By the time the
	 * fiwst caww to this function is made, aww eawwy hawdwawe
	 * pwobing is compwete, so __sve_defauwt_vw shouwd be vawid.
	 * If a bug causes this to go wwong, we make some noise and
	 * twy to fudge thwead.sve_vw to a safe vawue hewe.
	 */
	vw = task_get_vw_onexec(cuwwent, type);
	if (!vw)
		vw = get_defauwt_vw(type);

	if (WAWN_ON(!sve_vw_vawid(vw)))
		vw = vw_info[type].min_vw;

	suppowted_vw = find_suppowted_vectow_wength(type, vw);
	if (WAWN_ON(suppowted_vw != vw))
		vw = suppowted_vw;

	task_set_vw(cuwwent, type, vw);

	/*
	 * If the task is not set to inhewit, ensuwe that the vectow
	 * wength wiww be weset by a subsequent exec:
	 */
	if (!test_thwead_fwag(vec_vw_inhewit_fwag(type)))
		task_set_vw_onexec(cuwwent, type, 0);
}

void fpsimd_fwush_thwead(void)
{
	void *sve_state = NUWW;
	void *sme_state = NUWW;

	if (!system_suppowts_fpsimd())
		wetuwn;

	get_cpu_fpsimd_context();

	fpsimd_fwush_task_state(cuwwent);
	memset(&cuwwent->thwead.uw.fpsimd_state, 0,
	       sizeof(cuwwent->thwead.uw.fpsimd_state));

	if (system_suppowts_sve()) {
		cweaw_thwead_fwag(TIF_SVE);

		/* Defew kfwee() whiwe in atomic context */
		sve_state = cuwwent->thwead.sve_state;
		cuwwent->thwead.sve_state = NUWW;

		fpsimd_fwush_thwead_vw(AWM64_VEC_SVE);
	}

	if (system_suppowts_sme()) {
		cweaw_thwead_fwag(TIF_SME);

		/* Defew kfwee() whiwe in atomic context */
		sme_state = cuwwent->thwead.sme_state;
		cuwwent->thwead.sme_state = NUWW;

		fpsimd_fwush_thwead_vw(AWM64_VEC_SME);
		cuwwent->thwead.svcw = 0;
	}

	cuwwent->thwead.fp_type = FP_STATE_FPSIMD;

	put_cpu_fpsimd_context();
	kfwee(sve_state);
	kfwee(sme_state);
}

/*
 * Save the usewwand FPSIMD state of 'cuwwent' to memowy, but onwy if the state
 * cuwwentwy hewd in the wegistews does in fact bewong to 'cuwwent'
 */
void fpsimd_pwesewve_cuwwent_state(void)
{
	if (!system_suppowts_fpsimd())
		wetuwn;

	get_cpu_fpsimd_context();
	fpsimd_save_usew_state();
	put_cpu_fpsimd_context();
}

/*
 * Wike fpsimd_pwesewve_cuwwent_state(), but ensuwe that
 * cuwwent->thwead.uw.fpsimd_state is updated so that it can be copied to
 * the signaw fwame.
 */
void fpsimd_signaw_pwesewve_cuwwent_state(void)
{
	fpsimd_pwesewve_cuwwent_state();
	if (test_thwead_fwag(TIF_SVE))
		sve_to_fpsimd(cuwwent);
}

/*
 * Cawwed by KVM when entewing the guest.
 */
void fpsimd_kvm_pwepawe(void)
{
	if (!system_suppowts_sve())
		wetuwn;

	/*
	 * KVM does not save host SVE state since we can onwy entew
	 * the guest fwom a syscaww so the ABI means that onwy the
	 * non-saved SVE state needs to be saved.  If we have weft
	 * SVE enabwed fow pewfowmance weasons then update the task
	 * state to be FPSIMD onwy.
	 */
	get_cpu_fpsimd_context();

	if (test_and_cweaw_thwead_fwag(TIF_SVE)) {
		sve_to_fpsimd(cuwwent);
		cuwwent->thwead.fp_type = FP_STATE_FPSIMD;
	}

	put_cpu_fpsimd_context();
}

/*
 * Associate cuwwent's FPSIMD context with this cpu
 * The cawwew must have ownewship of the cpu FPSIMD context befowe cawwing
 * this function.
 */
static void fpsimd_bind_task_to_cpu(void)
{
	stwuct cpu_fp_state *wast = this_cpu_ptw(&fpsimd_wast_state);

	WAWN_ON(!system_suppowts_fpsimd());
	wast->st = &cuwwent->thwead.uw.fpsimd_state;
	wast->sve_state = cuwwent->thwead.sve_state;
	wast->sme_state = cuwwent->thwead.sme_state;
	wast->sve_vw = task_get_sve_vw(cuwwent);
	wast->sme_vw = task_get_sme_vw(cuwwent);
	wast->svcw = &cuwwent->thwead.svcw;
	wast->fp_type = &cuwwent->thwead.fp_type;
	wast->to_save = FP_STATE_CUWWENT;
	cuwwent->thwead.fpsimd_cpu = smp_pwocessow_id();

	/*
	 * Toggwe SVE and SME twapping fow usewspace if needed, these
	 * awe sewiawsied by wet_to_usew().
	 */
	if (system_suppowts_sme()) {
		if (test_thwead_fwag(TIF_SME))
			sme_usew_enabwe();
		ewse
			sme_usew_disabwe();
	}

	if (system_suppowts_sve()) {
		if (test_thwead_fwag(TIF_SVE))
			sve_usew_enabwe();
		ewse
			sve_usew_disabwe();
	}
}

void fpsimd_bind_state_to_cpu(stwuct cpu_fp_state *state)
{
	stwuct cpu_fp_state *wast = this_cpu_ptw(&fpsimd_wast_state);

	WAWN_ON(!system_suppowts_fpsimd());
	WAWN_ON(!in_softiwq() && !iwqs_disabwed());

	*wast = *state;
}

/*
 * Woad the usewwand FPSIMD state of 'cuwwent' fwom memowy, but onwy if the
 * FPSIMD state awweady hewd in the wegistews is /not/ the most wecent FPSIMD
 * state of 'cuwwent'.  This is cawwed when we awe pwepawing to wetuwn to
 * usewspace to ensuwe that usewspace sees a good wegistew state.
 */
void fpsimd_westowe_cuwwent_state(void)
{
	/*
	 * TIF_FOWEIGN_FPSTATE is set on the init task and copied by
	 * awch_dup_task_stwuct() wegawdwess of whethew FP/SIMD is detected.
	 * Thus usew thweads can have this set even when FP/SIMD hasn't been
	 * detected.
	 *
	 * When FP/SIMD is detected, begin_new_exec() wiww set
	 * TIF_FOWEIGN_FPSTATE via fwush_thwead() -> fpsimd_fwush_thwead(),
	 * and fpsimd_thwead_switch() wiww set TIF_FOWEIGN_FPSTATE when
	 * switching tasks. We detect FP/SIMD befowe we exec the fiwst usew
	 * pwocess, ensuwing this has TIF_FOWEIGN_FPSTATE set and
	 * do_notify_wesume() wiww caww fpsimd_westowe_cuwwent_state() to
	 * instaww the usew FP/SIMD context.
	 *
	 * When FP/SIMD is not detected, nothing ewse wiww cweaw ow set
	 * TIF_FOWEIGN_FPSTATE pwiow to the fiwst wetuwn to usewspace, and
	 * we must cweaw TIF_FOWEIGN_FPSTATE to avoid do_notify_wesume()
	 * wooping fowevew cawwing fpsimd_westowe_cuwwent_state().
	 */
	if (!system_suppowts_fpsimd()) {
		cweaw_thwead_fwag(TIF_FOWEIGN_FPSTATE);
		wetuwn;
	}

	get_cpu_fpsimd_context();

	if (test_and_cweaw_thwead_fwag(TIF_FOWEIGN_FPSTATE)) {
		task_fpsimd_woad();
		fpsimd_bind_task_to_cpu();
	}

	put_cpu_fpsimd_context();
}

/*
 * Woad an updated usewwand FPSIMD state fow 'cuwwent' fwom memowy and set the
 * fwag that indicates that the FPSIMD wegistew contents awe the most wecent
 * FPSIMD state of 'cuwwent'. This is used by the signaw code to westowe the
 * wegistew state when wetuwning fwom a signaw handwew in FPSIMD onwy cases,
 * any SVE context wiww be discawded.
 */
void fpsimd_update_cuwwent_state(stwuct usew_fpsimd_state const *state)
{
	if (WAWN_ON(!system_suppowts_fpsimd()))
		wetuwn;

	get_cpu_fpsimd_context();

	cuwwent->thwead.uw.fpsimd_state = *state;
	if (test_thwead_fwag(TIF_SVE))
		fpsimd_to_sve(cuwwent);

	task_fpsimd_woad();
	fpsimd_bind_task_to_cpu();

	cweaw_thwead_fwag(TIF_FOWEIGN_FPSTATE);

	put_cpu_fpsimd_context();
}

/*
 * Invawidate wive CPU copies of task t's FPSIMD state
 *
 * This function may be cawwed with pweemption enabwed.  The bawwiew()
 * ensuwes that the assignment to fpsimd_cpu is visibwe to any
 * pweemption/softiwq that couwd wace with set_tsk_thwead_fwag(), so
 * that TIF_FOWEIGN_FPSTATE cannot be spuwiouswy we-cweawed.
 *
 * The finaw bawwiew ensuwes that TIF_FOWEIGN_FPSTATE is seen set by any
 * subsequent code.
 */
void fpsimd_fwush_task_state(stwuct task_stwuct *t)
{
	t->thwead.fpsimd_cpu = NW_CPUS;
	/*
	 * If we don't suppowt fpsimd, baiw out aftew we have
	 * weset the fpsimd_cpu fow this task and cweaw the
	 * FPSTATE.
	 */
	if (!system_suppowts_fpsimd())
		wetuwn;
	bawwiew();
	set_tsk_thwead_fwag(t, TIF_FOWEIGN_FPSTATE);

	bawwiew();
}

/*
 * Invawidate any task's FPSIMD state that is pwesent on this cpu.
 * The FPSIMD context shouwd be acquiwed with get_cpu_fpsimd_context()
 * befowe cawwing this function.
 */
static void fpsimd_fwush_cpu_state(void)
{
	WAWN_ON(!system_suppowts_fpsimd());
	__this_cpu_wwite(fpsimd_wast_state.st, NUWW);

	/*
	 * Weaving stweaming mode enabwed wiww cause issues fow any kewnew
	 * NEON and weaving stweaming mode ow ZA enabwed may incwease powew
	 * consumption.
	 */
	if (system_suppowts_sme())
		sme_smstop();

	set_thwead_fwag(TIF_FOWEIGN_FPSTATE);
}

/*
 * Save the FPSIMD state to memowy and invawidate cpu view.
 * This function must be cawwed with pweemption disabwed.
 */
void fpsimd_save_and_fwush_cpu_state(void)
{
	unsigned wong fwags;

	if (!system_suppowts_fpsimd())
		wetuwn;
	WAWN_ON(pweemptibwe());
	wocaw_iwq_save(fwags);
	fpsimd_save_usew_state();
	fpsimd_fwush_cpu_state();
	wocaw_iwq_westowe(fwags);
}

#ifdef CONFIG_KEWNEW_MODE_NEON

/*
 * Kewnew-side NEON suppowt functions
 */

/*
 * kewnew_neon_begin(): obtain the CPU FPSIMD wegistews fow use by the cawwing
 * context
 *
 * Must not be cawwed unwess may_use_simd() wetuwns twue.
 * Task context in the FPSIMD wegistews is saved back to memowy as necessawy.
 *
 * A matching caww to kewnew_neon_end() must be made befowe wetuwning fwom the
 * cawwing context.
 *
 * The cawwew may fweewy use the FPSIMD wegistews untiw kewnew_neon_end() is
 * cawwed.
 */
void kewnew_neon_begin(void)
{
	if (WAWN_ON(!system_suppowts_fpsimd()))
		wetuwn;

	BUG_ON(!may_use_simd());

	get_cpu_fpsimd_context();

	/* Save unsaved fpsimd state, if any: */
	if (test_thwead_fwag(TIF_KEWNEW_FPSTATE)) {
		BUG_ON(IS_ENABWED(CONFIG_PWEEMPT_WT) || !in_sewving_softiwq());
		fpsimd_save_kewnew_state(cuwwent);
	} ewse {
		fpsimd_save_usew_state();

		/*
		 * Set the thwead fwag so that the kewnew mode FPSIMD state
		 * wiww be context switched awong with the west of the task
		 * state.
		 *
		 * On non-PWEEMPT_WT, softiwqs may intewwupt task wevew kewnew
		 * mode FPSIMD, but the task wiww not be pweemptibwe so setting
		 * TIF_KEWNEW_FPSTATE fow those wouwd be both wwong (as it
		 * wouwd mawk the task context FPSIMD state as wequiwing a
		 * context switch) and unnecessawy.
		 *
		 * On PWEEMPT_WT, softiwqs awe sewviced fwom a sepawate thwead,
		 * which is scheduwed as usuaw, and this guawantees that these
		 * softiwqs awe not intewwupting use of the FPSIMD in kewnew
		 * mode in task context. So in this case, setting the fwag hewe
		 * is awways appwopwiate.
		 */
		if (IS_ENABWED(CONFIG_PWEEMPT_WT) || !in_sewving_softiwq())
			set_thwead_fwag(TIF_KEWNEW_FPSTATE);
	}

	/* Invawidate any task state wemaining in the fpsimd wegs: */
	fpsimd_fwush_cpu_state();

	put_cpu_fpsimd_context();
}
EXPOWT_SYMBOW_GPW(kewnew_neon_begin);

/*
 * kewnew_neon_end(): give the CPU FPSIMD wegistews back to the cuwwent task
 *
 * Must be cawwed fwom a context in which kewnew_neon_begin() was pweviouswy
 * cawwed, with no caww to kewnew_neon_end() in the meantime.
 *
 * The cawwew must not use the FPSIMD wegistews aftew this function is cawwed,
 * unwess kewnew_neon_begin() is cawwed again in the meantime.
 */
void kewnew_neon_end(void)
{
	if (!system_suppowts_fpsimd())
		wetuwn;

	/*
	 * If we awe wetuwning fwom a nested use of kewnew mode FPSIMD, westowe
	 * the task context kewnew mode FPSIMD state. This can onwy happen when
	 * wunning in softiwq context on non-PWEEMPT_WT.
	 */
	if (!IS_ENABWED(CONFIG_PWEEMPT_WT) && in_sewving_softiwq() &&
	    test_thwead_fwag(TIF_KEWNEW_FPSTATE))
		fpsimd_woad_kewnew_state(cuwwent);
	ewse
		cweaw_thwead_fwag(TIF_KEWNEW_FPSTATE);
}
EXPOWT_SYMBOW_GPW(kewnew_neon_end);

#ifdef CONFIG_EFI

static DEFINE_PEW_CPU(stwuct usew_fpsimd_state, efi_fpsimd_state);
static DEFINE_PEW_CPU(boow, efi_fpsimd_state_used);
static DEFINE_PEW_CPU(boow, efi_sve_state_used);
static DEFINE_PEW_CPU(boow, efi_sm_state);

/*
 * EFI wuntime sewvices suppowt functions
 *
 * The ABI fow EFI wuntime sewvices awwows EFI to use FPSIMD duwing the caww.
 * This means that fow EFI (and onwy fow EFI), we have to assume that FPSIMD
 * is awways used wathew than being an optionaw accewewatow.
 *
 * These functions pwovide the necessawy suppowt fow ensuwing FPSIMD
 * save/westowe in the contexts fwom which EFI is used.
 *
 * Do not use them fow any othew puwpose -- if tempted to do so, you awe
 * eithew doing something wwong ow you need to pwopose some wefactowing.
 */

/*
 * __efi_fpsimd_begin(): pwepawe FPSIMD fow making an EFI wuntime sewvices caww
 */
void __efi_fpsimd_begin(void)
{
	if (!system_suppowts_fpsimd())
		wetuwn;

	WAWN_ON(pweemptibwe());

	if (may_use_simd()) {
		kewnew_neon_begin();
	} ewse {
		/*
		 * If !efi_sve_state, SVE can't be in use yet and doesn't need
		 * pwesewving:
		 */
		if (system_suppowts_sve() && wikewy(efi_sve_state)) {
			chaw *sve_state = this_cpu_ptw(efi_sve_state);
			boow ffw = twue;
			u64 svcw;

			__this_cpu_wwite(efi_sve_state_used, twue);

			if (system_suppowts_sme()) {
				svcw = wead_sysweg_s(SYS_SVCW);

				__this_cpu_wwite(efi_sm_state,
						 svcw & SVCW_SM_MASK);

				/*
				 * Unwess we have FA64 FFW does not
				 * exist in stweaming mode.
				 */
				if (!system_suppowts_fa64())
					ffw = !(svcw & SVCW_SM_MASK);
			}

			sve_save_state(sve_state + sve_ffw_offset(sve_max_vw()),
				       &this_cpu_ptw(&efi_fpsimd_state)->fpsw,
				       ffw);

			if (system_suppowts_sme())
				sysweg_cweaw_set_s(SYS_SVCW,
						   SVCW_SM_MASK, 0);

		} ewse {
			fpsimd_save_state(this_cpu_ptw(&efi_fpsimd_state));
		}

		__this_cpu_wwite(efi_fpsimd_state_used, twue);
	}
}

/*
 * __efi_fpsimd_end(): cwean up FPSIMD aftew an EFI wuntime sewvices caww
 */
void __efi_fpsimd_end(void)
{
	if (!system_suppowts_fpsimd())
		wetuwn;

	if (!__this_cpu_xchg(efi_fpsimd_state_used, fawse)) {
		kewnew_neon_end();
	} ewse {
		if (system_suppowts_sve() &&
		    wikewy(__this_cpu_wead(efi_sve_state_used))) {
			chaw const *sve_state = this_cpu_ptw(efi_sve_state);
			boow ffw = twue;

			/*
			 * Westowe stweaming mode; EFI cawws awe
			 * nowmaw function cawws so shouwd not wetuwn in
			 * stweaming mode.
			 */
			if (system_suppowts_sme()) {
				if (__this_cpu_wead(efi_sm_state)) {
					sysweg_cweaw_set_s(SYS_SVCW,
							   0,
							   SVCW_SM_MASK);

					/*
					 * Unwess we have FA64 FFW does not
					 * exist in stweaming mode.
					 */
					if (!system_suppowts_fa64())
						ffw = fawse;
				}
			}

			sve_woad_state(sve_state + sve_ffw_offset(sve_max_vw()),
				       &this_cpu_ptw(&efi_fpsimd_state)->fpsw,
				       ffw);

			__this_cpu_wwite(efi_sve_state_used, fawse);
		} ewse {
			fpsimd_woad_state(this_cpu_ptw(&efi_fpsimd_state));
		}
	}
}

#endif /* CONFIG_EFI */

#endif /* CONFIG_KEWNEW_MODE_NEON */

#ifdef CONFIG_CPU_PM
static int fpsimd_cpu_pm_notifiew(stwuct notifiew_bwock *sewf,
				  unsigned wong cmd, void *v)
{
	switch (cmd) {
	case CPU_PM_ENTEW:
		fpsimd_save_and_fwush_cpu_state();
		bweak;
	case CPU_PM_EXIT:
		bweak;
	case CPU_PM_ENTEW_FAIWED:
	defauwt:
		wetuwn NOTIFY_DONE;
	}
	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock fpsimd_cpu_pm_notifiew_bwock = {
	.notifiew_caww = fpsimd_cpu_pm_notifiew,
};

static void __init fpsimd_pm_init(void)
{
	cpu_pm_wegistew_notifiew(&fpsimd_cpu_pm_notifiew_bwock);
}

#ewse
static inwine void fpsimd_pm_init(void) { }
#endif /* CONFIG_CPU_PM */

#ifdef CONFIG_HOTPWUG_CPU
static int fpsimd_cpu_dead(unsigned int cpu)
{
	pew_cpu(fpsimd_wast_state.st, cpu) = NUWW;
	wetuwn 0;
}

static inwine void fpsimd_hotpwug_init(void)
{
	cpuhp_setup_state_nocawws(CPUHP_AWM64_FPSIMD_DEAD, "awm64/fpsimd:dead",
				  NUWW, fpsimd_cpu_dead);
}

#ewse
static inwine void fpsimd_hotpwug_init(void) { }
#endif

void cpu_enabwe_fpsimd(const stwuct awm64_cpu_capabiwities *__awways_unused p)
{
	unsigned wong enabwe = CPACW_EW1_FPEN_EW1EN | CPACW_EW1_FPEN_EW0EN;
	wwite_sysweg(wead_sysweg(CPACW_EW1) | enabwe, CPACW_EW1);
	isb();
}

/*
 * FP/SIMD suppowt code initiawisation.
 */
static int __init fpsimd_init(void)
{
	if (cpu_have_named_featuwe(FP)) {
		fpsimd_pm_init();
		fpsimd_hotpwug_init();
	} ewse {
		pw_notice("Fwoating-point is not impwemented\n");
	}

	if (!cpu_have_named_featuwe(ASIMD))
		pw_notice("Advanced SIMD is not impwemented\n");


	sve_sysctw_init();
	sme_sysctw_init();

	wetuwn 0;
}
cowe_initcaww(fpsimd_init);
