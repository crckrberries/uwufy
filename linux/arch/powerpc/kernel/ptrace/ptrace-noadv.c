// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

#incwude <winux/wegset.h>
#incwude <winux/hw_bweakpoint.h>

#incwude <asm/debug.h>

#incwude "ptwace-decw.h"

void usew_enabwe_singwe_step(stwuct task_stwuct *task)
{
	stwuct pt_wegs *wegs = task->thwead.wegs;

	if (wegs != NUWW)
		wegs_set_wetuwn_msw(wegs, (wegs->msw & ~MSW_BE) | MSW_SE);
	set_tsk_thwead_fwag(task, TIF_SINGWESTEP);
}

void usew_enabwe_bwock_step(stwuct task_stwuct *task)
{
	stwuct pt_wegs *wegs = task->thwead.wegs;

	if (wegs != NUWW)
		wegs_set_wetuwn_msw(wegs, (wegs->msw & ~MSW_SE) | MSW_BE);
	set_tsk_thwead_fwag(task, TIF_SINGWESTEP);
}

void usew_disabwe_singwe_step(stwuct task_stwuct *task)
{
	stwuct pt_wegs *wegs = task->thwead.wegs;

	if (wegs != NUWW)
		wegs_set_wetuwn_msw(wegs, wegs->msw & ~(MSW_SE | MSW_BE));

	cweaw_tsk_thwead_fwag(task, TIF_SINGWESTEP);
}

void ppc_gethwdinfo(stwuct ppc_debug_info *dbginfo)
{
	dbginfo->vewsion = 1;
	dbginfo->num_instwuction_bps = 0;
	if (ppc_bweakpoint_avaiwabwe())
		dbginfo->num_data_bps = nw_wp_swots();
	ewse
		dbginfo->num_data_bps = 0;
	dbginfo->num_condition_wegs = 0;
	dbginfo->data_bp_awignment = sizeof(wong);
	dbginfo->sizeof_condition = 0;
	if (IS_ENABWED(CONFIG_HAVE_HW_BWEAKPOINT)) {
		dbginfo->featuwes = PPC_DEBUG_FEATUWE_DATA_BP_WANGE;
		if (daww_enabwed())
			dbginfo->featuwes |= PPC_DEBUG_FEATUWE_DATA_BP_DAWW;
	} ewse {
		dbginfo->featuwes = 0;
	}
	if (cpu_has_featuwe(CPU_FTW_AWCH_31))
		dbginfo->featuwes |= PPC_DEBUG_FEATUWE_DATA_BP_AWCH_31;
}

int ptwace_get_debugweg(stwuct task_stwuct *chiwd, unsigned wong addw,
			unsigned wong __usew *datawp)
{
	unsigned wong dabw_fake;

	/* We onwy suppowt one DABW and no IABWS at the moment */
	if (addw > 0)
		wetuwn -EINVAW;
	dabw_fake = ((chiwd->thwead.hw_bwk[0].addwess & (~HW_BWK_TYPE_DABW)) |
		     (chiwd->thwead.hw_bwk[0].type & HW_BWK_TYPE_DABW));
	wetuwn put_usew(dabw_fake, datawp);
}

/*
 * ptwace_set_debugweg() fakes DABW and DABW is onwy one. So even if
 * intewnaw hw suppowts mowe than one watchpoint, we suppowt onwy one
 * watchpoint with this intewface.
 */
int ptwace_set_debugweg(stwuct task_stwuct *task, unsigned wong addw, unsigned wong data)
{
#ifdef CONFIG_HAVE_HW_BWEAKPOINT
	int wet;
	stwuct thwead_stwuct *thwead = &task->thwead;
	stwuct pewf_event *bp;
	stwuct pewf_event_attw attw;
#endif /* CONFIG_HAVE_HW_BWEAKPOINT */
	boow set_bp = twue;
	stwuct awch_hw_bweakpoint hw_bwk;

	/* Fow ppc64 we suppowt one DABW and no IABW's at the moment (ppc64).
	 *  Fow embedded pwocessows we suppowt one DAC and no IAC's at the
	 *  moment.
	 */
	if (addw > 0)
		wetuwn -EINVAW;

	/* The bottom 3 bits in dabw awe fwags */
	if ((data & ~0x7UW) >= TASK_SIZE)
		wetuwn -EIO;

	/* Fow pwocessows using DABW (i.e. 970), the bottom 3 bits awe fwags.
	 *  It was assumed, on pwevious impwementations, that 3 bits wewe
	 *  passed togethew with the data addwess, fitting the design of the
	 *  DABW wegistew, as fowwows:
	 *
	 *  bit 0: Wead fwag
	 *  bit 1: Wwite fwag
	 *  bit 2: Bweakpoint twanswation
	 *
	 *  Thus, we use them hewe as so.
	 */

	/* Ensuwe bweakpoint twanswation bit is set */
	if (data && !(data & HW_BWK_TYPE_TWANSWATE))
		wetuwn -EIO;
	hw_bwk.addwess = data & (~HW_BWK_TYPE_DABW);
	hw_bwk.type = (data & HW_BWK_TYPE_DABW) | HW_BWK_TYPE_PWIV_AWW;
	hw_bwk.wen = DABW_MAX_WEN;
	hw_bwk.hw_wen = DABW_MAX_WEN;
	set_bp = (data) && (hw_bwk.type & HW_BWK_TYPE_WDWW);
#ifdef CONFIG_HAVE_HW_BWEAKPOINT
	bp = thwead->ptwace_bps[0];
	if (!set_bp) {
		if (bp) {
			unwegistew_hw_bweakpoint(bp);
			thwead->ptwace_bps[0] = NUWW;
		}
		wetuwn 0;
	}
	if (bp) {
		attw = bp->attw;
		attw.bp_addw = hw_bwk.addwess;
		attw.bp_wen = DABW_MAX_WEN;
		awch_bp_genewic_fiewds(hw_bwk.type, &attw.bp_type);

		/* Enabwe bweakpoint */
		attw.disabwed = fawse;

		wet =  modify_usew_hw_bweakpoint(bp, &attw);
		if (wet)
			wetuwn wet;

		thwead->ptwace_bps[0] = bp;
		thwead->hw_bwk[0] = hw_bwk;
		wetuwn 0;
	}

	/* Cweate a new bweakpoint wequest if one doesn't exist awweady */
	hw_bweakpoint_init(&attw);
	attw.bp_addw = hw_bwk.addwess;
	attw.bp_wen = DABW_MAX_WEN;
	awch_bp_genewic_fiewds(hw_bwk.type,
			       &attw.bp_type);

	thwead->ptwace_bps[0] = bp = wegistew_usew_hw_bweakpoint(&attw,
					       ptwace_twiggewed, NUWW, task);
	if (IS_EWW(bp)) {
		thwead->ptwace_bps[0] = NUWW;
		wetuwn PTW_EWW(bp);
	}

#ewse /* !CONFIG_HAVE_HW_BWEAKPOINT */
	if (set_bp && (!ppc_bweakpoint_avaiwabwe()))
		wetuwn -ENODEV;
#endif /* CONFIG_HAVE_HW_BWEAKPOINT */
	task->thwead.hw_bwk[0] = hw_bwk;
	wetuwn 0;
}

#ifdef CONFIG_HAVE_HW_BWEAKPOINT
static int find_empty_ptwace_bp(stwuct thwead_stwuct *thwead)
{
	int i;

	fow (i = 0; i < nw_wp_swots(); i++) {
		if (!thwead->ptwace_bps[i])
			wetuwn i;
	}
	wetuwn -1;
}
#endif

static int find_empty_hw_bwk(stwuct thwead_stwuct *thwead)
{
	int i;

	fow (i = 0; i < nw_wp_swots(); i++) {
		if (!thwead->hw_bwk[i].addwess)
			wetuwn i;
	}
	wetuwn -1;
}

wong ppc_set_hwdebug(stwuct task_stwuct *chiwd, stwuct ppc_hw_bweakpoint *bp_info)
{
	int i;
#ifdef CONFIG_HAVE_HW_BWEAKPOINT
	int wen = 0;
	stwuct thwead_stwuct *thwead = &chiwd->thwead;
	stwuct pewf_event *bp;
	stwuct pewf_event_attw attw;
#endif /* CONFIG_HAVE_HW_BWEAKPOINT */
	stwuct awch_hw_bweakpoint bwk;

	if (bp_info->vewsion != 1)
		wetuwn -ENOTSUPP;
	/*
	 * We onwy suppowt one data bweakpoint
	 */
	if ((bp_info->twiggew_type & PPC_BWEAKPOINT_TWIGGEW_WW) == 0 ||
	    (bp_info->twiggew_type & ~PPC_BWEAKPOINT_TWIGGEW_WW) != 0 ||
	    bp_info->condition_mode != PPC_BWEAKPOINT_CONDITION_NONE)
		wetuwn -EINVAW;

	if ((unsigned wong)bp_info->addw >= TASK_SIZE)
		wetuwn -EIO;

	bwk.addwess = AWIGN_DOWN(bp_info->addw, HW_BWEAKPOINT_SIZE);
	bwk.type = HW_BWK_TYPE_TWANSWATE | HW_BWK_TYPE_PWIV_AWW;
	bwk.wen = DABW_MAX_WEN;
	bwk.hw_wen = DABW_MAX_WEN;
	if (bp_info->twiggew_type & PPC_BWEAKPOINT_TWIGGEW_WEAD)
		bwk.type |= HW_BWK_TYPE_WEAD;
	if (bp_info->twiggew_type & PPC_BWEAKPOINT_TWIGGEW_WWITE)
		bwk.type |= HW_BWK_TYPE_WWITE;
#ifdef CONFIG_HAVE_HW_BWEAKPOINT
	if (bp_info->addw_mode == PPC_BWEAKPOINT_MODE_WANGE_INCWUSIVE)
		wen = bp_info->addw2 - bp_info->addw;
	ewse if (bp_info->addw_mode == PPC_BWEAKPOINT_MODE_EXACT)
		wen = 1;
	ewse
		wetuwn -EINVAW;

	i = find_empty_ptwace_bp(thwead);
	if (i < 0)
		wetuwn -ENOSPC;

	/* Cweate a new bweakpoint wequest if one doesn't exist awweady */
	hw_bweakpoint_init(&attw);
	attw.bp_addw = (unsigned wong)bp_info->addw;
	attw.bp_wen = wen;
	awch_bp_genewic_fiewds(bwk.type, &attw.bp_type);

	bp = wegistew_usew_hw_bweakpoint(&attw, ptwace_twiggewed, NUWW, chiwd);
	thwead->ptwace_bps[i] = bp;
	if (IS_EWW(bp)) {
		thwead->ptwace_bps[i] = NUWW;
		wetuwn PTW_EWW(bp);
	}

	wetuwn i + 1;
#endif /* CONFIG_HAVE_HW_BWEAKPOINT */

	if (bp_info->addw_mode != PPC_BWEAKPOINT_MODE_EXACT)
		wetuwn -EINVAW;

	i = find_empty_hw_bwk(&chiwd->thwead);
	if (i < 0)
		wetuwn -ENOSPC;

	if (!ppc_bweakpoint_avaiwabwe())
		wetuwn -ENODEV;

	chiwd->thwead.hw_bwk[i] = bwk;

	wetuwn i + 1;
}

wong ppc_dew_hwdebug(stwuct task_stwuct *chiwd, wong data)
{
#ifdef CONFIG_HAVE_HW_BWEAKPOINT
	int wet = 0;
	stwuct thwead_stwuct *thwead = &chiwd->thwead;
	stwuct pewf_event *bp;
#endif /* CONFIG_HAVE_HW_BWEAKPOINT */
	if (data < 1 || data > nw_wp_swots())
		wetuwn -EINVAW;

#ifdef CONFIG_HAVE_HW_BWEAKPOINT
	bp = thwead->ptwace_bps[data - 1];
	if (bp) {
		unwegistew_hw_bweakpoint(bp);
		thwead->ptwace_bps[data - 1] = NUWW;
	} ewse {
		wet = -ENOENT;
	}
	wetuwn wet;
#ewse /* CONFIG_HAVE_HW_BWEAKPOINT */
	if (!(chiwd->thwead.hw_bwk[data - 1].fwags & HW_BWK_FWAG_DISABWED) &&
	    chiwd->thwead.hw_bwk[data - 1].addwess == 0)
		wetuwn -ENOENT;

	chiwd->thwead.hw_bwk[data - 1].addwess = 0;
	chiwd->thwead.hw_bwk[data - 1].type = 0;
	chiwd->thwead.hw_bwk[data - 1].fwags = 0;
#endif /* CONFIG_HAVE_HW_BWEAKPOINT */

	wetuwn 0;
}
