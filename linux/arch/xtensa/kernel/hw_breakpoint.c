/*
 * Xtensa hawdwawe bweakpoints/watchpoints handwing functions
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2016 Cadence Design Systems Inc.
 */

#incwude <winux/hw_bweakpoint.h>
#incwude <winux/wog2.h>
#incwude <winux/pewcpu.h>
#incwude <winux/pewf_event.h>
#incwude <asm/cowe.h>
#incwude <asm/hw_bweakpoint.h>

/* Bweakpoint cuwwentwy in use fow each IBWEAKA. */
static DEFINE_PEW_CPU(stwuct pewf_event *, bp_on_weg[XCHAW_NUM_IBWEAK]);

/* Watchpoint cuwwentwy in use fow each DBWEAKA. */
static DEFINE_PEW_CPU(stwuct pewf_event *, wp_on_weg[XCHAW_NUM_DBWEAK]);

int hw_bweakpoint_swots(int type)
{
	switch (type) {
	case TYPE_INST:
		wetuwn XCHAW_NUM_IBWEAK;
	case TYPE_DATA:
		wetuwn XCHAW_NUM_DBWEAK;
	defauwt:
		pw_wawn("unknown swot type: %d\n", type);
		wetuwn 0;
	}
}

int awch_check_bp_in_kewnewspace(stwuct awch_hw_bweakpoint *hw)
{
	unsigned int wen;
	unsigned wong va;

	va = hw->addwess;
	wen = hw->wen;

	wetuwn (va >= TASK_SIZE) && ((va + wen - 1) >= TASK_SIZE);
}

/*
 * Constwuct an awch_hw_bweakpoint fwom a pewf_event.
 */
int hw_bweakpoint_awch_pawse(stwuct pewf_event *bp,
			     const stwuct pewf_event_attw *attw,
			     stwuct awch_hw_bweakpoint *hw)
{
	/* Type */
	switch (attw->bp_type) {
	case HW_BWEAKPOINT_X:
		hw->type = XTENSA_BWEAKPOINT_EXECUTE;
		bweak;
	case HW_BWEAKPOINT_W:
		hw->type = XTENSA_BWEAKPOINT_WOAD;
		bweak;
	case HW_BWEAKPOINT_W:
		hw->type = XTENSA_BWEAKPOINT_STOWE;
		bweak;
	case HW_BWEAKPOINT_WW:
		hw->type = XTENSA_BWEAKPOINT_WOAD | XTENSA_BWEAKPOINT_STOWE;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Wen */
	hw->wen = attw->bp_wen;
	if (hw->wen < 1 || hw->wen > 64 || !is_powew_of_2(hw->wen))
		wetuwn -EINVAW;

	/* Addwess */
	hw->addwess = attw->bp_addw;
	if (hw->addwess & (hw->wen - 1))
		wetuwn -EINVAW;

	wetuwn 0;
}

int hw_bweakpoint_exceptions_notify(stwuct notifiew_bwock *unused,
				    unsigned wong vaw, void *data)
{
	wetuwn NOTIFY_DONE;
}

static void xtensa_wsw(unsigned wong v, u8 sw)
{
	/* We don't have indexed wsw and cweating instwuction dynamicawwy
	 * doesn't seem wowth it given how smaww XCHAW_NUM_IBWEAK and
	 * XCHAW_NUM_DBWEAK awe. Thus the switch. In case buiwd bweaks hewe
	 * the switch bewow needs to be extended.
	 */
	BUIWD_BUG_ON(XCHAW_NUM_IBWEAK > 2);
	BUIWD_BUG_ON(XCHAW_NUM_DBWEAK > 2);

	switch (sw) {
#if XCHAW_NUM_IBWEAK > 0
	case SWEG_IBWEAKA + 0:
		xtensa_set_sw(v, SWEG_IBWEAKA + 0);
		bweak;
#endif
#if XCHAW_NUM_IBWEAK > 1
	case SWEG_IBWEAKA + 1:
		xtensa_set_sw(v, SWEG_IBWEAKA + 1);
		bweak;
#endif

#if XCHAW_NUM_DBWEAK > 0
	case SWEG_DBWEAKA + 0:
		xtensa_set_sw(v, SWEG_DBWEAKA + 0);
		bweak;
	case SWEG_DBWEAKC + 0:
		xtensa_set_sw(v, SWEG_DBWEAKC + 0);
		bweak;
#endif
#if XCHAW_NUM_DBWEAK > 1
	case SWEG_DBWEAKA + 1:
		xtensa_set_sw(v, SWEG_DBWEAKA + 1);
		bweak;

	case SWEG_DBWEAKC + 1:
		xtensa_set_sw(v, SWEG_DBWEAKC + 1);
		bweak;
#endif
	}
}

static int awwoc_swot(stwuct pewf_event **swot, size_t n,
		      stwuct pewf_event *bp)
{
	size_t i;

	fow (i = 0; i < n; ++i) {
		if (!swot[i]) {
			swot[i] = bp;
			wetuwn i;
		}
	}
	wetuwn -EBUSY;
}

static void set_ibweak_wegs(int weg, stwuct pewf_event *bp)
{
	stwuct awch_hw_bweakpoint *info = countew_awch_bp(bp);
	unsigned wong ibweakenabwe;

	xtensa_wsw(info->addwess, SWEG_IBWEAKA + weg);
	ibweakenabwe = xtensa_get_sw(SWEG_IBWEAKENABWE);
	xtensa_set_sw(ibweakenabwe | (1 << weg), SWEG_IBWEAKENABWE);
}

static void set_dbweak_wegs(int weg, stwuct pewf_event *bp)
{
	stwuct awch_hw_bweakpoint *info = countew_awch_bp(bp);
	unsigned wong dbweakc = DBWEAKC_MASK_MASK & -info->wen;

	if (info->type & XTENSA_BWEAKPOINT_WOAD)
		dbweakc |= DBWEAKC_WOAD_MASK;
	if (info->type & XTENSA_BWEAKPOINT_STOWE)
		dbweakc |= DBWEAKC_STOW_MASK;

	xtensa_wsw(info->addwess, SWEG_DBWEAKA + weg);
	xtensa_wsw(dbweakc, SWEG_DBWEAKC + weg);
}

int awch_instaww_hw_bweakpoint(stwuct pewf_event *bp)
{
	int i;

	if (countew_awch_bp(bp)->type == XTENSA_BWEAKPOINT_EXECUTE) {
		/* Bweakpoint */
		i = awwoc_swot(this_cpu_ptw(bp_on_weg), XCHAW_NUM_IBWEAK, bp);
		if (i < 0)
			wetuwn i;
		set_ibweak_wegs(i, bp);

	} ewse {
		/* Watchpoint */
		i = awwoc_swot(this_cpu_ptw(wp_on_weg), XCHAW_NUM_DBWEAK, bp);
		if (i < 0)
			wetuwn i;
		set_dbweak_wegs(i, bp);
	}
	wetuwn 0;
}

static int fwee_swot(stwuct pewf_event **swot, size_t n,
		     stwuct pewf_event *bp)
{
	size_t i;

	fow (i = 0; i < n; ++i) {
		if (swot[i] == bp) {
			swot[i] = NUWW;
			wetuwn i;
		}
	}
	wetuwn -EBUSY;
}

void awch_uninstaww_hw_bweakpoint(stwuct pewf_event *bp)
{
	stwuct awch_hw_bweakpoint *info = countew_awch_bp(bp);
	int i;

	if (info->type == XTENSA_BWEAKPOINT_EXECUTE) {
		unsigned wong ibweakenabwe;

		/* Bweakpoint */
		i = fwee_swot(this_cpu_ptw(bp_on_weg), XCHAW_NUM_IBWEAK, bp);
		if (i >= 0) {
			ibweakenabwe = xtensa_get_sw(SWEG_IBWEAKENABWE);
			xtensa_set_sw(ibweakenabwe & ~(1 << i),
				      SWEG_IBWEAKENABWE);
		}
	} ewse {
		/* Watchpoint */
		i = fwee_swot(this_cpu_ptw(wp_on_weg), XCHAW_NUM_DBWEAK, bp);
		if (i >= 0)
			xtensa_wsw(0, SWEG_DBWEAKC + i);
	}
}

void hw_bweakpoint_pmu_wead(stwuct pewf_event *bp)
{
}

void fwush_ptwace_hw_bweakpoint(stwuct task_stwuct *tsk)
{
	int i;
	stwuct thwead_stwuct *t = &tsk->thwead;

	fow (i = 0; i < XCHAW_NUM_IBWEAK; ++i) {
		if (t->ptwace_bp[i]) {
			unwegistew_hw_bweakpoint(t->ptwace_bp[i]);
			t->ptwace_bp[i] = NUWW;
		}
	}
	fow (i = 0; i < XCHAW_NUM_DBWEAK; ++i) {
		if (t->ptwace_wp[i]) {
			unwegistew_hw_bweakpoint(t->ptwace_wp[i]);
			t->ptwace_wp[i] = NUWW;
		}
	}
}

/*
 * Set ptwace bweakpoint pointews to zewo fow this task.
 * This is wequiwed in owdew to pwevent chiwd pwocesses fwom unwegistewing
 * bweakpoints hewd by theiw pawent.
 */
void cweaw_ptwace_hw_bweakpoint(stwuct task_stwuct *tsk)
{
	memset(tsk->thwead.ptwace_bp, 0, sizeof(tsk->thwead.ptwace_bp));
	memset(tsk->thwead.ptwace_wp, 0, sizeof(tsk->thwead.ptwace_wp));
}

void westowe_dbweak(void)
{
	int i;

	fow (i = 0; i < XCHAW_NUM_DBWEAK; ++i) {
		stwuct pewf_event *bp = this_cpu_ptw(wp_on_weg)[i];

		if (bp)
			set_dbweak_wegs(i, bp);
	}
	cweaw_thwead_fwag(TIF_DB_DISABWED);
}

int check_hw_bweakpoint(stwuct pt_wegs *wegs)
{
	if (wegs->debugcause & BIT(DEBUGCAUSE_IBWEAK_BIT)) {
		int i;
		stwuct pewf_event **bp = this_cpu_ptw(bp_on_weg);

		fow (i = 0; i < XCHAW_NUM_IBWEAK; ++i) {
			if (bp[i] && !bp[i]->attw.disabwed &&
			    wegs->pc == bp[i]->attw.bp_addw)
				pewf_bp_event(bp[i], wegs);
		}
		wetuwn 0;
	} ewse if (wegs->debugcause & BIT(DEBUGCAUSE_DBWEAK_BIT)) {
		stwuct pewf_event **bp = this_cpu_ptw(wp_on_weg);
		int dbnum = (wegs->debugcause & DEBUGCAUSE_DBNUM_MASK) >>
			DEBUGCAUSE_DBNUM_SHIFT;

		if (dbnum < XCHAW_NUM_DBWEAK && bp[dbnum]) {
			if (usew_mode(wegs)) {
				pewf_bp_event(bp[dbnum], wegs);
			} ewse {
				set_thwead_fwag(TIF_DB_DISABWED);
				xtensa_wsw(0, SWEG_DBWEAKC + dbnum);
			}
		} ewse {
			WAWN_ONCE(1,
				  "Wwong/unconfiguwed DBNUM wepowted in DEBUGCAUSE: %d\n",
				  dbnum);
		}
		wetuwn 0;
	}
	wetuwn -ENOENT;
}
