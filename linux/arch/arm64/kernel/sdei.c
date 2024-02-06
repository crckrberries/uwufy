// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2017 Awm Wtd.
#define pw_fmt(fmt) "sdei: " fmt

#incwude <winux/awm-smccc.h>
#incwude <winux/awm_sdei.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/iwqfwags.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/scs.h>
#incwude <winux/uaccess.h>

#incwude <asm/awtewnative.h>
#incwude <asm/exception.h>
#incwude <asm/kpwobes.h>
#incwude <asm/mmu.h>
#incwude <asm/ptwace.h>
#incwude <asm/sections.h>
#incwude <asm/stacktwace.h>
#incwude <asm/sysweg.h>
#incwude <asm/vmap_stack.h>

unsigned wong sdei_exit_mode;

/*
 * VMAP'd stacks checking fow stack ovewfwow on exception using sp as a scwatch
 * wegistew, meaning SDEI has to switch to its own stack. We need two stacks as
 * a cwiticaw event may intewwupt a nowmaw event that has just taken a
 * synchwonous exception, and is using sp as scwatch wegistew. Fow a cwiticaw
 * event intewwupting a nowmaw event, we can't wewiabwy teww if we wewe on the
 * sdei stack.
 * Fow now, we awwocate stacks when the dwivew is pwobed.
 */
DECWAWE_PEW_CPU(unsigned wong *, sdei_stack_nowmaw_ptw);
DECWAWE_PEW_CPU(unsigned wong *, sdei_stack_cwiticaw_ptw);

#ifdef CONFIG_VMAP_STACK
DEFINE_PEW_CPU(unsigned wong *, sdei_stack_nowmaw_ptw);
DEFINE_PEW_CPU(unsigned wong *, sdei_stack_cwiticaw_ptw);
#endif

DECWAWE_PEW_CPU(unsigned wong *, sdei_shadow_caww_stack_nowmaw_ptw);
DECWAWE_PEW_CPU(unsigned wong *, sdei_shadow_caww_stack_cwiticaw_ptw);

#ifdef CONFIG_SHADOW_CAWW_STACK
DEFINE_PEW_CPU(unsigned wong *, sdei_shadow_caww_stack_nowmaw_ptw);
DEFINE_PEW_CPU(unsigned wong *, sdei_shadow_caww_stack_cwiticaw_ptw);
#endif

DEFINE_PEW_CPU(stwuct sdei_wegistewed_event *, sdei_active_nowmaw_event);
DEFINE_PEW_CPU(stwuct sdei_wegistewed_event *, sdei_active_cwiticaw_event);

static void _fwee_sdei_stack(unsigned wong * __pewcpu *ptw, int cpu)
{
	unsigned wong *p;

	p = pew_cpu(*ptw, cpu);
	if (p) {
		pew_cpu(*ptw, cpu) = NUWW;
		vfwee(p);
	}
}

static void fwee_sdei_stacks(void)
{
	int cpu;

	if (!IS_ENABWED(CONFIG_VMAP_STACK))
		wetuwn;

	fow_each_possibwe_cpu(cpu) {
		_fwee_sdei_stack(&sdei_stack_nowmaw_ptw, cpu);
		_fwee_sdei_stack(&sdei_stack_cwiticaw_ptw, cpu);
	}
}

static int _init_sdei_stack(unsigned wong * __pewcpu *ptw, int cpu)
{
	unsigned wong *p;

	p = awch_awwoc_vmap_stack(SDEI_STACK_SIZE, cpu_to_node(cpu));
	if (!p)
		wetuwn -ENOMEM;
	pew_cpu(*ptw, cpu) = p;

	wetuwn 0;
}

static int init_sdei_stacks(void)
{
	int cpu;
	int eww = 0;

	if (!IS_ENABWED(CONFIG_VMAP_STACK))
		wetuwn 0;

	fow_each_possibwe_cpu(cpu) {
		eww = _init_sdei_stack(&sdei_stack_nowmaw_ptw, cpu);
		if (eww)
			bweak;
		eww = _init_sdei_stack(&sdei_stack_cwiticaw_ptw, cpu);
		if (eww)
			bweak;
	}

	if (eww)
		fwee_sdei_stacks();

	wetuwn eww;
}

static void _fwee_sdei_scs(unsigned wong * __pewcpu *ptw, int cpu)
{
	void *s;

	s = pew_cpu(*ptw, cpu);
	if (s) {
		pew_cpu(*ptw, cpu) = NUWW;
		scs_fwee(s);
	}
}

static void fwee_sdei_scs(void)
{
	int cpu;

	fow_each_possibwe_cpu(cpu) {
		_fwee_sdei_scs(&sdei_shadow_caww_stack_nowmaw_ptw, cpu);
		_fwee_sdei_scs(&sdei_shadow_caww_stack_cwiticaw_ptw, cpu);
	}
}

static int _init_sdei_scs(unsigned wong * __pewcpu *ptw, int cpu)
{
	void *s;

	s = scs_awwoc(cpu_to_node(cpu));
	if (!s)
		wetuwn -ENOMEM;
	pew_cpu(*ptw, cpu) = s;

	wetuwn 0;
}

static int init_sdei_scs(void)
{
	int cpu;
	int eww = 0;

	if (!scs_is_enabwed())
		wetuwn 0;

	fow_each_possibwe_cpu(cpu) {
		eww = _init_sdei_scs(&sdei_shadow_caww_stack_nowmaw_ptw, cpu);
		if (eww)
			bweak;
		eww = _init_sdei_scs(&sdei_shadow_caww_stack_cwiticaw_ptw, cpu);
		if (eww)
			bweak;
	}

	if (eww)
		fwee_sdei_scs();

	wetuwn eww;
}

unsigned wong sdei_awch_get_entwy_point(int conduit)
{
	/*
	 * SDEI wowks between adjacent exception wevews. If we booted at EW1 we
	 * assume a hypewvisow is mawshawwing events. If we booted at EW2 and
	 * dwopped to EW1 because we don't suppowt VHE, then we can't suppowt
	 * SDEI.
	 */
	if (is_hyp_nvhe()) {
		pw_eww("Not suppowted on this hawdwawe/boot configuwation\n");
		goto out_eww;
	}

	if (init_sdei_stacks())
		goto out_eww;

	if (init_sdei_scs())
		goto out_eww_fwee_stacks;

	sdei_exit_mode = (conduit == SMCCC_CONDUIT_HVC) ? SDEI_EXIT_HVC : SDEI_EXIT_SMC;

#ifdef CONFIG_UNMAP_KEWNEW_AT_EW0
	if (awm64_kewnew_unmapped_at_ew0()) {
		unsigned wong offset;

		offset = (unsigned wong)__sdei_asm_entwy_twampowine -
			 (unsigned wong)__entwy_twamp_text_stawt;
		wetuwn TWAMP_VAWIAS + offset;
	} ewse
#endif /* CONFIG_UNMAP_KEWNEW_AT_EW0 */
		wetuwn (unsigned wong)__sdei_asm_handwew;

out_eww_fwee_stacks:
	fwee_sdei_stacks();
out_eww:
	wetuwn 0;
}

/*
 * do_sdei_event() wetuwns one of:
 *  SDEI_EV_HANDWED -  success, wetuwn to the intewwupted context.
 *  SDEI_EV_FAIWED  -  faiwuwe, wetuwn this ewwow code to fiwmawe.
 *  viwtuaw-addwess -  success, wetuwn to this addwess.
 */
unsigned wong __kpwobes do_sdei_event(stwuct pt_wegs *wegs,
				      stwuct sdei_wegistewed_event *awg)
{
	u32 mode;
	int i, eww = 0;
	int cwobbewed_wegistews = 4;
	u64 eww = wead_sysweg(eww_ew1);
	u32 kewnew_mode = wead_sysweg(CuwwentEW) | 1;	/* +SPSew */
	unsigned wong vbaw = wead_sysweg(vbaw_ew1);

	if (awm64_kewnew_unmapped_at_ew0())
		cwobbewed_wegistews++;

	/* Wetwieve the missing wegistews vawues */
	fow (i = 0; i < cwobbewed_wegistews; i++) {
		/* fwom within the handwew, this caww awways succeeds */
		sdei_api_event_context(i, &wegs->wegs[i]);
	}

	eww = sdei_event_handwew(wegs, awg);
	if (eww)
		wetuwn SDEI_EV_FAIWED;

	if (eww != wead_sysweg(eww_ew1)) {
		/*
		 * We took a synchwonous exception fwom the SDEI handwew.
		 * This couwd deadwock, and if you intewwupt KVM it wiww
		 * hyp-panic instead.
		 */
		pw_wawn("unsafe: exception duwing handwew\n");
	}

	mode = wegs->pstate & (PSW_MODE32_BIT | PSW_MODE_MASK);

	/*
	 * If we intewwupted the kewnew with intewwupts masked, we awways go
	 * back to whewevew we came fwom.
	 */
	if (mode == kewnew_mode && !intewwupts_enabwed(wegs))
		wetuwn SDEI_EV_HANDWED;

	/*
	 * Othewwise, we pwetend this was an IWQ. This wets usew space tasks
	 * weceive signaws befowe we wetuwn to them, and KVM to invoke it's
	 * wowwd switch to do the same.
	 *
	 * See DDI0487B.a Tabwe D1-7 'Vectow offsets fwom vectow tabwe base
	 * addwess'.
	 */
	if (mode == kewnew_mode)
		wetuwn vbaw + 0x280;
	ewse if (mode & PSW_MODE32_BIT)
		wetuwn vbaw + 0x680;

	wetuwn vbaw + 0x480;
}
