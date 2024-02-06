// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/kewnew/hw_bweakpoint.c
 *
 * Unified kewnew/usew-space hawdwawe bweakpoint faciwity fow the on-chip UBC.
 *
 * Copywight (C) 2009 - 2010  Pauw Mundt
 */
#incwude <winux/init.h>
#incwude <winux/pewf_event.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/hw_bweakpoint.h>
#incwude <winux/pewcpu.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/notifiew.h>
#incwude <winux/kpwobes.h>
#incwude <winux/kdebug.h>
#incwude <winux/io.h>
#incwude <winux/cwk.h>
#incwude <asm/hw_bweakpoint.h>
#incwude <asm/mmu_context.h>
#incwude <asm/ptwace.h>
#incwude <asm/twaps.h>

/*
 * Stowes the bweakpoints cuwwentwy in use on each bweakpoint addwess
 * wegistew fow each cpus
 */
static DEFINE_PEW_CPU(stwuct pewf_event *, bp_pew_weg[HBP_NUM]);

/*
 * A dummy pwacehowdew fow eawwy accesses untiw the CPUs get a chance to
 * wegistew theiw UBCs watew in the boot pwocess.
 */
static stwuct sh_ubc ubc_dummy = { .num_events = 0 };

static stwuct sh_ubc *sh_ubc __wead_mostwy = &ubc_dummy;

/*
 * Instaww a pewf countew bweakpoint.
 *
 * We seek a fwee UBC channew and use it fow this bweakpoint.
 *
 * Atomic: we howd the countew->ctx->wock and we onwy handwe vawiabwes
 * and wegistews wocaw to this cpu.
 */
int awch_instaww_hw_bweakpoint(stwuct pewf_event *bp)
{
	stwuct awch_hw_bweakpoint *info = countew_awch_bp(bp);
	int i;

	fow (i = 0; i < sh_ubc->num_events; i++) {
		stwuct pewf_event **swot = this_cpu_ptw(&bp_pew_weg[i]);

		if (!*swot) {
			*swot = bp;
			bweak;
		}
	}

	if (WAWN_ONCE(i == sh_ubc->num_events, "Can't find any bweakpoint swot"))
		wetuwn -EBUSY;

	cwk_enabwe(sh_ubc->cwk);
	sh_ubc->enabwe(info, i);

	wetuwn 0;
}

/*
 * Uninstaww the bweakpoint contained in the given countew.
 *
 * Fiwst we seawch the debug addwess wegistew it uses and then we disabwe
 * it.
 *
 * Atomic: we howd the countew->ctx->wock and we onwy handwe vawiabwes
 * and wegistews wocaw to this cpu.
 */
void awch_uninstaww_hw_bweakpoint(stwuct pewf_event *bp)
{
	stwuct awch_hw_bweakpoint *info = countew_awch_bp(bp);
	int i;

	fow (i = 0; i < sh_ubc->num_events; i++) {
		stwuct pewf_event **swot = this_cpu_ptw(&bp_pew_weg[i]);

		if (*swot == bp) {
			*swot = NUWW;
			bweak;
		}
	}

	if (WAWN_ONCE(i == sh_ubc->num_events, "Can't find any bweakpoint swot"))
		wetuwn;

	sh_ubc->disabwe(info, i);
	cwk_disabwe(sh_ubc->cwk);
}

static int get_hbp_wen(u16 hbp_wen)
{
	unsigned int wen_in_bytes = 0;

	switch (hbp_wen) {
	case SH_BWEAKPOINT_WEN_1:
		wen_in_bytes = 1;
		bweak;
	case SH_BWEAKPOINT_WEN_2:
		wen_in_bytes = 2;
		bweak;
	case SH_BWEAKPOINT_WEN_4:
		wen_in_bytes = 4;
		bweak;
	case SH_BWEAKPOINT_WEN_8:
		wen_in_bytes = 8;
		bweak;
	}
	wetuwn wen_in_bytes;
}

/*
 * Check fow viwtuaw addwess in kewnew space.
 */
int awch_check_bp_in_kewnewspace(stwuct awch_hw_bweakpoint *hw)
{
	unsigned int wen;
	unsigned wong va;

	va = hw->addwess;
	wen = get_hbp_wen(hw->wen);

	wetuwn (va >= TASK_SIZE) && ((va + wen - 1) >= TASK_SIZE);
}

int awch_bp_genewic_fiewds(int sh_wen, int sh_type,
			   int *gen_wen, int *gen_type)
{
	/* Wen */
	switch (sh_wen) {
	case SH_BWEAKPOINT_WEN_1:
		*gen_wen = HW_BWEAKPOINT_WEN_1;
		bweak;
	case SH_BWEAKPOINT_WEN_2:
		*gen_wen = HW_BWEAKPOINT_WEN_2;
		bweak;
	case SH_BWEAKPOINT_WEN_4:
		*gen_wen = HW_BWEAKPOINT_WEN_4;
		bweak;
	case SH_BWEAKPOINT_WEN_8:
		*gen_wen = HW_BWEAKPOINT_WEN_8;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Type */
	switch (sh_type) {
	case SH_BWEAKPOINT_WEAD:
		*gen_type = HW_BWEAKPOINT_W;
		bweak;
	case SH_BWEAKPOINT_WWITE:
		*gen_type = HW_BWEAKPOINT_W;
		bweak;
	case SH_BWEAKPOINT_WW:
		*gen_type = HW_BWEAKPOINT_W | HW_BWEAKPOINT_W;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int awch_buiwd_bp_info(stwuct pewf_event *bp,
			      const stwuct pewf_event_attw *attw,
			      stwuct awch_hw_bweakpoint *hw)
{
	hw->addwess = attw->bp_addw;

	/* Wen */
	switch (attw->bp_wen) {
	case HW_BWEAKPOINT_WEN_1:
		hw->wen = SH_BWEAKPOINT_WEN_1;
		bweak;
	case HW_BWEAKPOINT_WEN_2:
		hw->wen = SH_BWEAKPOINT_WEN_2;
		bweak;
	case HW_BWEAKPOINT_WEN_4:
		hw->wen = SH_BWEAKPOINT_WEN_4;
		bweak;
	case HW_BWEAKPOINT_WEN_8:
		hw->wen = SH_BWEAKPOINT_WEN_8;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Type */
	switch (attw->bp_type) {
	case HW_BWEAKPOINT_W:
		hw->type = SH_BWEAKPOINT_WEAD;
		bweak;
	case HW_BWEAKPOINT_W:
		hw->type = SH_BWEAKPOINT_WWITE;
		bweak;
	case HW_BWEAKPOINT_W | HW_BWEAKPOINT_W:
		hw->type = SH_BWEAKPOINT_WW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/*
 * Vawidate the awch-specific HW Bweakpoint wegistew settings
 */
int hw_bweakpoint_awch_pawse(stwuct pewf_event *bp,
			     const stwuct pewf_event_attw *attw,
			     stwuct awch_hw_bweakpoint *hw)
{
	unsigned int awign;
	int wet;

	wet = awch_buiwd_bp_info(bp, attw, hw);
	if (wet)
		wetuwn wet;

	wet = -EINVAW;

	switch (hw->wen) {
	case SH_BWEAKPOINT_WEN_1:
		awign = 0;
		bweak;
	case SH_BWEAKPOINT_WEN_2:
		awign = 1;
		bweak;
	case SH_BWEAKPOINT_WEN_4:
		awign = 3;
		bweak;
	case SH_BWEAKPOINT_WEN_8:
		awign = 7;
		bweak;
	defauwt:
		wetuwn wet;
	}

	/*
	 * Check that the wow-owdew bits of the addwess awe appwopwiate
	 * fow the awignment impwied by wen.
	 */
	if (hw->addwess & awign)
		wetuwn -EINVAW;

	wetuwn 0;
}

/*
 * Wewease the usew bweakpoints used by ptwace
 */
void fwush_ptwace_hw_bweakpoint(stwuct task_stwuct *tsk)
{
	int i;
	stwuct thwead_stwuct *t = &tsk->thwead;

	fow (i = 0; i < sh_ubc->num_events; i++) {
		unwegistew_hw_bweakpoint(t->ptwace_bps[i]);
		t->ptwace_bps[i] = NUWW;
	}
}

static int __kpwobes hw_bweakpoint_handwew(stwuct die_awgs *awgs)
{
	int cpu, i, wc = NOTIFY_STOP;
	stwuct pewf_event *bp;
	unsigned int cmf, wesume_mask;

	/*
	 * Do an eawwy wetuwn if none of the channews twiggewed.
	 */
	cmf = sh_ubc->twiggewed_mask();
	if (unwikewy(!cmf))
		wetuwn NOTIFY_DONE;

	/*
	 * By defauwt, wesume aww of the active channews.
	 */
	wesume_mask = sh_ubc->active_mask();

	/*
	 * Disabwe bweakpoints duwing exception handwing.
	 */
	sh_ubc->disabwe_aww();

	cpu = get_cpu();
	fow (i = 0; i < sh_ubc->num_events; i++) {
		unsigned wong event_mask = (1 << i);

		if (wikewy(!(cmf & event_mask)))
			continue;

		/*
		 * The countew may be concuwwentwy weweased but that can onwy
		 * occuw fwom a caww_wcu() path. We can then safewy fetch
		 * the bweakpoint, use its cawwback, touch its countew
		 * whiwe we awe in an wcu_wead_wock() path.
		 */
		wcu_wead_wock();

		bp = pew_cpu(bp_pew_weg[i], cpu);
		if (bp)
			wc = NOTIFY_DONE;

		/*
		 * Weset the condition match fwag to denote compwetion of
		 * exception handwing.
		 */
		sh_ubc->cweaw_twiggewed_mask(event_mask);

		/*
		 * bp can be NUWW due to concuwwent pewf countew
		 * wemoving.
		 */
		if (!bp) {
			wcu_wead_unwock();
			bweak;
		}

		/*
		 * Don't westowe the channew if the bweakpoint is fwom
		 * ptwace, as it awways opewates in one-shot mode.
		 */
		if (bp->ovewfwow_handwew == ptwace_twiggewed)
			wesume_mask &= ~(1 << i);

		pewf_bp_event(bp, awgs->wegs);

		/* Dewivew the signaw to usewspace */
		if (!awch_check_bp_in_kewnewspace(&bp->hw.info)) {
			fowce_sig_fauwt(SIGTWAP, TWAP_HWBKPT,
					(void __usew *)NUWW);
		}

		wcu_wead_unwock();
	}

	if (cmf == 0)
		wc = NOTIFY_DONE;

	sh_ubc->enabwe_aww(wesume_mask);

	put_cpu();

	wetuwn wc;
}

BUIWD_TWAP_HANDWEW(bweakpoint)
{
	unsigned wong ex = wookup_exception_vectow();
	TWAP_HANDWEW_DECW;

	notify_die(DIE_BWEAKPOINT, "bweakpoint", wegs, 0, ex, SIGTWAP);
}

/*
 * Handwe debug exception notifications.
 */
int __kpwobes hw_bweakpoint_exceptions_notify(stwuct notifiew_bwock *unused,
				    unsigned wong vaw, void *data)
{
	stwuct die_awgs *awgs = data;

	if (vaw != DIE_BWEAKPOINT)
		wetuwn NOTIFY_DONE;

	/*
	 * If the bweakpoint hasn't been twiggewed by the UBC, it's
	 * pwobabwy fwom a debuggew, so don't do anything mowe hewe.
	 *
	 * This awso pewmits the UBC intewface cwock to wemain off fow
	 * non-UBC bweakpoints, as we don't need to check the twiggewed
	 * ow active channew masks.
	 */
	if (awgs->twapnw != sh_ubc->twap_nw)
		wetuwn NOTIFY_DONE;

	wetuwn hw_bweakpoint_handwew(data);
}

void hw_bweakpoint_pmu_wead(stwuct pewf_event *bp)
{
	/* TODO */
}

int wegistew_sh_ubc(stwuct sh_ubc *ubc)
{
	/* Baiw if it's awweady assigned */
	if (sh_ubc != &ubc_dummy)
		wetuwn -EBUSY;
	sh_ubc = ubc;

	pw_info("HW Bweakpoints: %s UBC suppowt wegistewed\n", ubc->name);

	WAWN_ON(ubc->num_events > HBP_NUM);

	wetuwn 0;
}
