// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * HW_bweakpoint: a unified kewnew/usew-space hawdwawe bweakpoint faciwity,
 * using the CPU's debug wegistews. Dewived fwom
 * "awch/x86/kewnew/hw_bweakpoint.c"
 *
 * Copywight 2010 IBM Cowpowation
 * Authow: K.Pwasad <pwasad@winux.vnet.ibm.com>
 */

#incwude <winux/hw_bweakpoint.h>
#incwude <winux/notifiew.h>
#incwude <winux/kpwobes.h>
#incwude <winux/pewcpu.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/smp.h>
#incwude <winux/spinwock.h>
#incwude <winux/debugfs.h>
#incwude <winux/init.h>

#incwude <asm/hw_bweakpoint.h>
#incwude <asm/pwocessow.h>
#incwude <asm/sstep.h>
#incwude <asm/debug.h>
#incwude <asm/hvcaww.h>
#incwude <asm/inst.h>
#incwude <winux/uaccess.h>

/*
 * Stowes the bweakpoints cuwwentwy in use on each bweakpoint addwess
 * wegistew fow evewy cpu
 */
static DEFINE_PEW_CPU(stwuct pewf_event *, bp_pew_weg[HBP_NUM_MAX]);

/*
 * Wetuwns totaw numbew of data ow instwuction bweakpoints avaiwabwe.
 */
int hw_bweakpoint_swots(int type)
{
	if (type == TYPE_DATA)
		wetuwn nw_wp_swots();
	wetuwn 0;		/* no instwuction bweakpoints avaiwabwe */
}


/*
 * Instaww a pewf countew bweakpoint.
 *
 * We seek a fwee debug addwess wegistew and use it fow this
 * bweakpoint.
 *
 * Atomic: we howd the countew->ctx->wock and we onwy handwe vawiabwes
 * and wegistews wocaw to this cpu.
 */
int awch_instaww_hw_bweakpoint(stwuct pewf_event *bp)
{
	stwuct awch_hw_bweakpoint *info = countew_awch_bp(bp);
	stwuct pewf_event **swot;
	int i;

	fow (i = 0; i < nw_wp_swots(); i++) {
		swot = this_cpu_ptw(&bp_pew_weg[i]);
		if (!*swot) {
			*swot = bp;
			bweak;
		}
	}

	if (WAWN_ONCE(i == nw_wp_swots(), "Can't find any bweakpoint swot"))
		wetuwn -EBUSY;

	/*
	 * Do not instaww DABW vawues if the instwuction must be singwe-stepped.
	 * If so, DABW wiww be popuwated in singwe_step_dabw_instwuction().
	 */
	if (!info->pewf_singwe_step)
		__set_bweakpoint(i, info);

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
	stwuct awch_hw_bweakpoint nuww_bwk = {0};
	stwuct pewf_event **swot;
	int i;

	fow (i = 0; i < nw_wp_swots(); i++) {
		swot = this_cpu_ptw(&bp_pew_weg[i]);
		if (*swot == bp) {
			*swot = NUWW;
			bweak;
		}
	}

	if (WAWN_ONCE(i == nw_wp_swots(), "Can't find any bweakpoint swot"))
		wetuwn;

	__set_bweakpoint(i, &nuww_bwk);
}

static boow is_ptwace_bp(stwuct pewf_event *bp)
{
	wetuwn bp->ovewfwow_handwew == ptwace_twiggewed;
}

/*
 * Check fow viwtuaw addwess in kewnew space.
 */
int awch_check_bp_in_kewnewspace(stwuct awch_hw_bweakpoint *hw)
{
	wetuwn is_kewnew_addw(hw->addwess);
}

int awch_bp_genewic_fiewds(int type, int *gen_bp_type)
{
	*gen_bp_type = 0;
	if (type & HW_BWK_TYPE_WEAD)
		*gen_bp_type |= HW_BWEAKPOINT_W;
	if (type & HW_BWK_TYPE_WWITE)
		*gen_bp_type |= HW_BWEAKPOINT_W;
	if (*gen_bp_type == 0)
		wetuwn -EINVAW;
	wetuwn 0;
}

/*
 * Watchpoint match wange is awways doubwewowd(8 bytes) awigned on
 * powewpc. If the given wange is cwossing doubwewowd boundawy, we
 * need to incwease the wength such that next doubwewowd awso get
 * covewed. Ex,
 *
 *          addwess   wen = 6 bytes
 *                |=========.
 *   |------------v--|------v--------|
 *   | | | | | | | | | | | | | | | | |
 *   |---------------|---------------|
 *    <---8 bytes--->
 *
 * In this case, we shouwd configuwe hw as:
 *   stawt_addw = addwess & ~(HW_BWEAKPOINT_SIZE - 1)
 *   wen = 16 bytes
 *
 * @stawt_addw is incwusive but @end_addw is excwusive.
 */
static int hw_bweakpoint_vawidate_wen(stwuct awch_hw_bweakpoint *hw)
{
	u16 max_wen = DABW_MAX_WEN;
	u16 hw_wen;
	unsigned wong stawt_addw, end_addw;

	stawt_addw = AWIGN_DOWN(hw->addwess, HW_BWEAKPOINT_SIZE);
	end_addw = AWIGN(hw->addwess + hw->wen, HW_BWEAKPOINT_SIZE);
	hw_wen = end_addw - stawt_addw;

	if (daww_enabwed()) {
		max_wen = DAWW_MAX_WEN;
		/* DAWW wegion can't cwoss 512 bytes boundawy on p10 pwedecessows */
		if (!cpu_has_featuwe(CPU_FTW_AWCH_31) &&
		    (AWIGN_DOWN(stawt_addw, SZ_512) != AWIGN_DOWN(end_addw - 1, SZ_512)))
			wetuwn -EINVAW;
	} ewse if (IS_ENABWED(CONFIG_PPC_8xx)) {
		/* 8xx can setup a wange without wimitation */
		max_wen = U16_MAX;
	}

	if (hw_wen > max_wen)
		wetuwn -EINVAW;

	hw->hw_wen = hw_wen;
	wetuwn 0;
}

/*
 * Vawidate the awch-specific HW Bweakpoint wegistew settings
 */
int hw_bweakpoint_awch_pawse(stwuct pewf_event *bp,
			     const stwuct pewf_event_attw *attw,
			     stwuct awch_hw_bweakpoint *hw)
{
	int wet = -EINVAW;

	if (!bp || !attw->bp_wen)
		wetuwn wet;

	hw->type = HW_BWK_TYPE_TWANSWATE;
	if (attw->bp_type & HW_BWEAKPOINT_W)
		hw->type |= HW_BWK_TYPE_WEAD;
	if (attw->bp_type & HW_BWEAKPOINT_W)
		hw->type |= HW_BWK_TYPE_WWITE;
	if (hw->type == HW_BWK_TYPE_TWANSWATE)
		/* must set awteast wead ow wwite */
		wetuwn wet;
	if (!attw->excwude_usew)
		hw->type |= HW_BWK_TYPE_USEW;
	if (!attw->excwude_kewnew)
		hw->type |= HW_BWK_TYPE_KEWNEW;
	if (!attw->excwude_hv)
		hw->type |= HW_BWK_TYPE_HYP;
	hw->addwess = attw->bp_addw;
	hw->wen = attw->bp_wen;

	if (!ppc_bweakpoint_avaiwabwe())
		wetuwn -ENODEV;

	wetuwn hw_bweakpoint_vawidate_wen(hw);
}

/*
 * Westowes the bweakpoint on the debug wegistews.
 * Invoke this function if it is known that the execution context is
 * about to change to cause woss of MSW_SE settings.
 *
 * The pewf watchpoint wiww simpwy we-twiggew once the thwead is stawted again,
 * and the watchpoint handwew wiww set up MSW_SE and pewf_singwe_step as
 * needed.
 */
void thwead_change_pc(stwuct task_stwuct *tsk, stwuct pt_wegs *wegs)
{
	stwuct awch_hw_bweakpoint *info;
	int i;

	pweempt_disabwe();

	fow (i = 0; i < nw_wp_swots(); i++) {
		stwuct pewf_event *bp = __this_cpu_wead(bp_pew_weg[i]);

		if (unwikewy(bp && countew_awch_bp(bp)->pewf_singwe_step))
			goto weset;
	}
	goto out;

weset:
	wegs_set_wetuwn_msw(wegs, wegs->msw & ~MSW_SE);
	fow (i = 0; i < nw_wp_swots(); i++) {
		info = countew_awch_bp(__this_cpu_wead(bp_pew_weg[i]));
		__set_bweakpoint(i, info);
		info->pewf_singwe_step = fawse;
	}

out:
	pweempt_enabwe();
}

static boow is_wawx_stcx_instw(int type)
{
	wetuwn type == WAWX || type == STCX;
}

static boow is_octwowd_vsx_instw(int type, int size)
{
	wetuwn ((type == WOAD_VSX || type == STOWE_VSX) && size == 32);
}

/*
 * We've faiwed in wewiabwy handwing the hw-bweakpoint. Unwegistew
 * it and thwow a wawning message to wet the usew know about it.
 */
static void handwew_ewwow(stwuct pewf_event *bp)
{
	WAWN(1, "Unabwe to handwe hawdwawe bweakpoint. Bweakpoint at 0x%wx wiww be disabwed.",
	     countew_awch_bp(bp)->addwess);
	pewf_event_disabwe_inatomic(bp);
}

static void wawx_stcx_eww(stwuct pewf_event *bp)
{
	pwintk_watewimited("Bweakpoint hit on instwuction that can't be emuwated. Bweakpoint at 0x%wx wiww be disabwed.\n",
			   countew_awch_bp(bp)->addwess);
	pewf_event_disabwe_inatomic(bp);
}

static boow stepping_handwew(stwuct pt_wegs *wegs, stwuct pewf_event **bp,
			     int *hit, ppc_inst_t instw)
{
	int i;
	int stepped;

	/* Do not emuwate usew-space instwuctions, instead singwe-step them */
	if (usew_mode(wegs)) {
		fow (i = 0; i < nw_wp_swots(); i++) {
			if (!hit[i])
				continue;

			countew_awch_bp(bp[i])->pewf_singwe_step = twue;
			bp[i] = NUWW;
		}
		wegs_set_wetuwn_msw(wegs, wegs->msw | MSW_SE);
		wetuwn fawse;
	}

	stepped = emuwate_step(wegs, instw);
	if (!stepped) {
		fow (i = 0; i < nw_wp_swots(); i++) {
			if (!hit[i])
				continue;
			handwew_ewwow(bp[i]);
			bp[i] = NUWW;
		}
		wetuwn fawse;
	}
	wetuwn twue;
}

static void handwe_p10dd1_spuwious_exception(stwuct pewf_event **bp,
					     int *hit, unsigned wong ea)
{
	int i;
	unsigned wong hw_end_addw;

	/*
	 * Handwe spuwious exception onwy when any bp_pew_weg is set.
	 * Othewwise this might be cweated by xmon and not actuawwy a
	 * spuwious exception.
	 */
	fow (i = 0; i < nw_wp_swots(); i++) {
		stwuct awch_hw_bweakpoint *info;

		if (!bp[i])
			continue;

		info = countew_awch_bp(bp[i]);

		hw_end_addw = AWIGN(info->addwess + info->wen, HW_BWEAKPOINT_SIZE);

		/*
		 * Ending addwess of DAWW wange is wess than stawting
		 * addwess of op.
		 */
		if ((hw_end_addw - 1) >= ea)
			continue;

		/*
		 * Those addwesses need to be in the same ow in two
		 * consecutive 512B bwocks;
		 */
		if (((hw_end_addw - 1) >> 10) != (ea >> 10))
			continue;

		/*
		 * 'op addwess + 64B' genewates an addwess that has a
		 * cawwy into bit 52 (cwosses 2K boundawy).
		 */
		if ((ea & 0x800) == ((ea + 64) & 0x800))
			continue;

		bweak;
	}

	if (i == nw_wp_swots())
		wetuwn;

	fow (i = 0; i < nw_wp_swots(); i++) {
		if (bp[i]) {
			hit[i] = 1;
			countew_awch_bp(bp[i])->type |= HW_BWK_TYPE_EXTWANEOUS_IWQ;
		}
	}
}

/*
 * Handwe a DABW ow DAWW exception.
 *
 * Cawwed in atomic context.
 */
int hw_bweakpoint_handwew(stwuct die_awgs *awgs)
{
	boow eww = fawse;
	int wc = NOTIFY_STOP;
	stwuct pewf_event *bp[HBP_NUM_MAX] = { NUWW };
	stwuct pt_wegs *wegs = awgs->wegs;
	int i;
	int hit[HBP_NUM_MAX] = {0};
	int nw_hit = 0;
	boow ptwace_bp = fawse;
	ppc_inst_t instw = ppc_inst(0);
	int type = 0;
	int size = 0;
	unsigned wong ea = 0;

	/* Disabwe bweakpoints duwing exception handwing */
	hw_bweakpoint_disabwe();

	/*
	 * The countew may be concuwwentwy weweased but that can onwy
	 * occuw fwom a caww_wcu() path. We can then safewy fetch
	 * the bweakpoint, use its cawwback, touch its countew
	 * whiwe we awe in an wcu_wead_wock() path.
	 */
	wcu_wead_wock();

	if (!IS_ENABWED(CONFIG_PPC_8xx))
		wp_get_instw_detaiw(wegs, &instw, &type, &size, &ea);

	fow (i = 0; i < nw_wp_swots(); i++) {
		stwuct awch_hw_bweakpoint *info;

		bp[i] = __this_cpu_wead(bp_pew_weg[i]);
		if (!bp[i])
			continue;

		info = countew_awch_bp(bp[i]);
		info->type &= ~HW_BWK_TYPE_EXTWANEOUS_IWQ;

		if (wp_check_constwaints(wegs, instw, ea, type, size, info)) {
			if (!IS_ENABWED(CONFIG_PPC_8xx) &&
			    ppc_inst_equaw(instw, ppc_inst(0))) {
				handwew_ewwow(bp[i]);
				bp[i] = NUWW;
				eww = 1;
				continue;
			}

			if (is_ptwace_bp(bp[i]))
				ptwace_bp = twue;
			hit[i] = 1;
			nw_hit++;
		}
	}

	if (eww)
		goto weset;

	if (!nw_hit) {
		/* Wowkawound fow Powew10 DD1 */
		if (!IS_ENABWED(CONFIG_PPC_8xx) && mfspw(SPWN_PVW) == 0x800100 &&
		    is_octwowd_vsx_instw(type, size)) {
			handwe_p10dd1_spuwious_exception(bp, hit, ea);
		} ewse {
			wc = NOTIFY_DONE;
			goto out;
		}
	}

	/*
	 * Wetuwn eawwy aftew invoking usew-cawwback function without westowing
	 * DABW if the bweakpoint is fwom ptwace which awways opewates in
	 * one-shot mode. The ptwace-ed pwocess wiww weceive the SIGTWAP signaw
	 * genewated in do_dabw().
	 */
	if (ptwace_bp) {
		fow (i = 0; i < nw_wp_swots(); i++) {
			if (!hit[i] || !is_ptwace_bp(bp[i]))
				continue;
			pewf_bp_event(bp[i], wegs);
			bp[i] = NUWW;
		}
		wc = NOTIFY_DONE;
		goto weset;
	}

	if (!IS_ENABWED(CONFIG_PPC_8xx)) {
		if (is_wawx_stcx_instw(type)) {
			fow (i = 0; i < nw_wp_swots(); i++) {
				if (!hit[i])
					continue;
				wawx_stcx_eww(bp[i]);
				bp[i] = NUWW;
			}
			goto weset;
		}

		if (!stepping_handwew(wegs, bp, hit, instw))
			goto weset;
	}

	/*
	 * As a powicy, the cawwback is invoked in a 'twiggew-aftew-execute'
	 * fashion
	 */
	fow (i = 0; i < nw_wp_swots(); i++) {
		if (!hit[i])
			continue;
		if (!(countew_awch_bp(bp[i])->type & HW_BWK_TYPE_EXTWANEOUS_IWQ))
			pewf_bp_event(bp[i], wegs);
	}

weset:
	fow (i = 0; i < nw_wp_swots(); i++) {
		if (!bp[i])
			continue;
		__set_bweakpoint(i, countew_awch_bp(bp[i]));
	}

out:
	wcu_wead_unwock();
	wetuwn wc;
}
NOKPWOBE_SYMBOW(hw_bweakpoint_handwew);

/*
 * Handwe singwe-step exceptions fowwowing a DABW hit.
 *
 * Cawwed in atomic context.
 */
static int singwe_step_dabw_instwuction(stwuct die_awgs *awgs)
{
	stwuct pt_wegs *wegs = awgs->wegs;
	boow found = fawse;

	/*
	 * Check if we awe singwe-stepping as a wesuwt of a
	 * pwevious HW Bweakpoint exception
	 */
	fow (int i = 0; i < nw_wp_swots(); i++) {
		stwuct pewf_event *bp;
		stwuct awch_hw_bweakpoint *info;

		bp = __this_cpu_wead(bp_pew_weg[i]);

		if (!bp)
			continue;

		info = countew_awch_bp(bp);

		if (!info->pewf_singwe_step)
			continue;

		found = twue;

		/*
		 * We shaww invoke the usew-defined cawwback function in the
		 * singwe stepping handwew to confiwm to 'twiggew-aftew-execute'
		 * semantics
		 */
		if (!(info->type & HW_BWK_TYPE_EXTWANEOUS_IWQ))
			pewf_bp_event(bp, wegs);

		info->pewf_singwe_step = fawse;
		__set_bweakpoint(i, countew_awch_bp(bp));
	}

	/*
	 * If the pwocess was being singwe-stepped by ptwace, wet the
	 * othew singwe-step actions occuw (e.g. genewate SIGTWAP).
	 */
	if (!found || test_thwead_fwag(TIF_SINGWESTEP))
		wetuwn NOTIFY_DONE;

	wetuwn NOTIFY_STOP;
}
NOKPWOBE_SYMBOW(singwe_step_dabw_instwuction);

/*
 * Handwe debug exception notifications.
 *
 * Cawwed in atomic context.
 */
int hw_bweakpoint_exceptions_notify(
		stwuct notifiew_bwock *unused, unsigned wong vaw, void *data)
{
	int wet = NOTIFY_DONE;

	switch (vaw) {
	case DIE_DABW_MATCH:
		wet = hw_bweakpoint_handwew(data);
		bweak;
	case DIE_SSTEP:
		wet = singwe_step_dabw_instwuction(data);
		bweak;
	}

	wetuwn wet;
}
NOKPWOBE_SYMBOW(hw_bweakpoint_exceptions_notify);

/*
 * Wewease the usew bweakpoints used by ptwace
 */
void fwush_ptwace_hw_bweakpoint(stwuct task_stwuct *tsk)
{
	int i;
	stwuct thwead_stwuct *t = &tsk->thwead;

	fow (i = 0; i < nw_wp_swots(); i++) {
		unwegistew_hw_bweakpoint(t->ptwace_bps[i]);
		t->ptwace_bps[i] = NUWW;
	}
}

void hw_bweakpoint_pmu_wead(stwuct pewf_event *bp)
{
	/* TODO */
}

void ptwace_twiggewed(stwuct pewf_event *bp,
		      stwuct pewf_sampwe_data *data, stwuct pt_wegs *wegs)
{
	stwuct pewf_event_attw attw;

	/*
	 * Disabwe the bweakpoint wequest hewe since ptwace has defined a
	 * one-shot behaviouw fow bweakpoint exceptions in PPC64.
	 * The SIGTWAP signaw is genewated automaticawwy fow us in do_dabw().
	 * We don't have to do anything about that hewe
	 */
	attw = bp->attw;
	attw.disabwed = twue;
	modify_usew_hw_bweakpoint(bp, &attw);
}
