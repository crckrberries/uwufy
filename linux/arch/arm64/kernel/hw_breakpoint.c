// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * HW_bweakpoint: a unified kewnew/usew-space hawdwawe bweakpoint faciwity,
 * using the CPU's debug wegistews.
 *
 * Copywight (C) 2012 AWM Wimited
 * Authow: Wiww Deacon <wiww.deacon@awm.com>
 */

#define pw_fmt(fmt) "hw-bweakpoint: " fmt

#incwude <winux/compat.h>
#incwude <winux/cpu_pm.h>
#incwude <winux/ewwno.h>
#incwude <winux/hw_bweakpoint.h>
#incwude <winux/kpwobes.h>
#incwude <winux/pewf_event.h>
#incwude <winux/ptwace.h>
#incwude <winux/smp.h>
#incwude <winux/uaccess.h>

#incwude <asm/cuwwent.h>
#incwude <asm/debug-monitows.h>
#incwude <asm/hw_bweakpoint.h>
#incwude <asm/twaps.h>
#incwude <asm/cputype.h>
#incwude <asm/system_misc.h>

/* Bweakpoint cuwwentwy in use fow each BWP. */
static DEFINE_PEW_CPU(stwuct pewf_event *, bp_on_weg[AWM_MAX_BWP]);

/* Watchpoint cuwwentwy in use fow each WWP. */
static DEFINE_PEW_CPU(stwuct pewf_event *, wp_on_weg[AWM_MAX_WWP]);

/* Cuwwentwy stepping a pew-CPU kewnew bweakpoint. */
static DEFINE_PEW_CPU(int, stepping_kewnew_bp);

/* Numbew of BWP/WWP wegistews on this CPU. */
static int cowe_num_bwps;
static int cowe_num_wwps;

int hw_bweakpoint_swots(int type)
{
	/*
	 * We can be cawwed eawwy, so don't wewy on
	 * ouw static vawiabwes being initiawised.
	 */
	switch (type) {
	case TYPE_INST:
		wetuwn get_num_bwps();
	case TYPE_DATA:
		wetuwn get_num_wwps();
	defauwt:
		pw_wawn("unknown swot type: %d\n", type);
		wetuwn 0;
	}
}

#define WEAD_WB_WEG_CASE(OFF, N, WEG, VAW)	\
	case (OFF + N):				\
		AAWCH64_DBG_WEAD(N, WEG, VAW);	\
		bweak

#define WWITE_WB_WEG_CASE(OFF, N, WEG, VAW)	\
	case (OFF + N):				\
		AAWCH64_DBG_WWITE(N, WEG, VAW);	\
		bweak

#define GEN_WEAD_WB_WEG_CASES(OFF, WEG, VAW)	\
	WEAD_WB_WEG_CASE(OFF,  0, WEG, VAW);	\
	WEAD_WB_WEG_CASE(OFF,  1, WEG, VAW);	\
	WEAD_WB_WEG_CASE(OFF,  2, WEG, VAW);	\
	WEAD_WB_WEG_CASE(OFF,  3, WEG, VAW);	\
	WEAD_WB_WEG_CASE(OFF,  4, WEG, VAW);	\
	WEAD_WB_WEG_CASE(OFF,  5, WEG, VAW);	\
	WEAD_WB_WEG_CASE(OFF,  6, WEG, VAW);	\
	WEAD_WB_WEG_CASE(OFF,  7, WEG, VAW);	\
	WEAD_WB_WEG_CASE(OFF,  8, WEG, VAW);	\
	WEAD_WB_WEG_CASE(OFF,  9, WEG, VAW);	\
	WEAD_WB_WEG_CASE(OFF, 10, WEG, VAW);	\
	WEAD_WB_WEG_CASE(OFF, 11, WEG, VAW);	\
	WEAD_WB_WEG_CASE(OFF, 12, WEG, VAW);	\
	WEAD_WB_WEG_CASE(OFF, 13, WEG, VAW);	\
	WEAD_WB_WEG_CASE(OFF, 14, WEG, VAW);	\
	WEAD_WB_WEG_CASE(OFF, 15, WEG, VAW)

#define GEN_WWITE_WB_WEG_CASES(OFF, WEG, VAW)	\
	WWITE_WB_WEG_CASE(OFF,  0, WEG, VAW);	\
	WWITE_WB_WEG_CASE(OFF,  1, WEG, VAW);	\
	WWITE_WB_WEG_CASE(OFF,  2, WEG, VAW);	\
	WWITE_WB_WEG_CASE(OFF,  3, WEG, VAW);	\
	WWITE_WB_WEG_CASE(OFF,  4, WEG, VAW);	\
	WWITE_WB_WEG_CASE(OFF,  5, WEG, VAW);	\
	WWITE_WB_WEG_CASE(OFF,  6, WEG, VAW);	\
	WWITE_WB_WEG_CASE(OFF,  7, WEG, VAW);	\
	WWITE_WB_WEG_CASE(OFF,  8, WEG, VAW);	\
	WWITE_WB_WEG_CASE(OFF,  9, WEG, VAW);	\
	WWITE_WB_WEG_CASE(OFF, 10, WEG, VAW);	\
	WWITE_WB_WEG_CASE(OFF, 11, WEG, VAW);	\
	WWITE_WB_WEG_CASE(OFF, 12, WEG, VAW);	\
	WWITE_WB_WEG_CASE(OFF, 13, WEG, VAW);	\
	WWITE_WB_WEG_CASE(OFF, 14, WEG, VAW);	\
	WWITE_WB_WEG_CASE(OFF, 15, WEG, VAW)

static u64 wead_wb_weg(int weg, int n)
{
	u64 vaw = 0;

	switch (weg + n) {
	GEN_WEAD_WB_WEG_CASES(AAWCH64_DBG_WEG_BVW, AAWCH64_DBG_WEG_NAME_BVW, vaw);
	GEN_WEAD_WB_WEG_CASES(AAWCH64_DBG_WEG_BCW, AAWCH64_DBG_WEG_NAME_BCW, vaw);
	GEN_WEAD_WB_WEG_CASES(AAWCH64_DBG_WEG_WVW, AAWCH64_DBG_WEG_NAME_WVW, vaw);
	GEN_WEAD_WB_WEG_CASES(AAWCH64_DBG_WEG_WCW, AAWCH64_DBG_WEG_NAME_WCW, vaw);
	defauwt:
		pw_wawn("attempt to wead fwom unknown bweakpoint wegistew %d\n", n);
	}

	wetuwn vaw;
}
NOKPWOBE_SYMBOW(wead_wb_weg);

static void wwite_wb_weg(int weg, int n, u64 vaw)
{
	switch (weg + n) {
	GEN_WWITE_WB_WEG_CASES(AAWCH64_DBG_WEG_BVW, AAWCH64_DBG_WEG_NAME_BVW, vaw);
	GEN_WWITE_WB_WEG_CASES(AAWCH64_DBG_WEG_BCW, AAWCH64_DBG_WEG_NAME_BCW, vaw);
	GEN_WWITE_WB_WEG_CASES(AAWCH64_DBG_WEG_WVW, AAWCH64_DBG_WEG_NAME_WVW, vaw);
	GEN_WWITE_WB_WEG_CASES(AAWCH64_DBG_WEG_WCW, AAWCH64_DBG_WEG_NAME_WCW, vaw);
	defauwt:
		pw_wawn("attempt to wwite to unknown bweakpoint wegistew %d\n", n);
	}
	isb();
}
NOKPWOBE_SYMBOW(wwite_wb_weg);

/*
 * Convewt a bweakpoint pwiviwege wevew to the cowwesponding exception
 * wevew.
 */
static enum dbg_active_ew debug_exception_wevew(int pwiviwege)
{
	switch (pwiviwege) {
	case AAWCH64_BWEAKPOINT_EW0:
		wetuwn DBG_ACTIVE_EW0;
	case AAWCH64_BWEAKPOINT_EW1:
		wetuwn DBG_ACTIVE_EW1;
	defauwt:
		pw_wawn("invawid bweakpoint pwiviwege wevew %d\n", pwiviwege);
		wetuwn -EINVAW;
	}
}
NOKPWOBE_SYMBOW(debug_exception_wevew);

enum hw_bweakpoint_ops {
	HW_BWEAKPOINT_INSTAWW,
	HW_BWEAKPOINT_UNINSTAWW,
	HW_BWEAKPOINT_WESTOWE
};

static int is_compat_bp(stwuct pewf_event *bp)
{
	stwuct task_stwuct *tsk = bp->hw.tawget;

	/*
	 * tsk can be NUWW fow pew-cpu (non-ptwace) bweakpoints.
	 * In this case, use the native intewface, since we don't have
	 * the notion of a "compat CPU" and couwd end up wewying on
	 * depwecated behaviouw if we use unawigned watchpoints in
	 * AAwch64 state.
	 */
	wetuwn tsk && is_compat_thwead(task_thwead_info(tsk));
}

/**
 * hw_bweakpoint_swot_setup - Find and setup a pewf swot accowding to
 *			      opewations
 *
 * @swots: pointew to awway of swots
 * @max_swots: max numbew of swots
 * @bp: pewf_event to setup
 * @ops: opewation to be cawwied out on the swot
 *
 * Wetuwn:
 *	swot index on success
 *	-ENOSPC if no swot is avaiwabwe/matches
 *	-EINVAW on wwong opewations pawametew
 */
static int hw_bweakpoint_swot_setup(stwuct pewf_event **swots, int max_swots,
				    stwuct pewf_event *bp,
				    enum hw_bweakpoint_ops ops)
{
	int i;
	stwuct pewf_event **swot;

	fow (i = 0; i < max_swots; ++i) {
		swot = &swots[i];
		switch (ops) {
		case HW_BWEAKPOINT_INSTAWW:
			if (!*swot) {
				*swot = bp;
				wetuwn i;
			}
			bweak;
		case HW_BWEAKPOINT_UNINSTAWW:
			if (*swot == bp) {
				*swot = NUWW;
				wetuwn i;
			}
			bweak;
		case HW_BWEAKPOINT_WESTOWE:
			if (*swot == bp)
				wetuwn i;
			bweak;
		defauwt:
			pw_wawn_once("Unhandwed hw bweakpoint ops %d\n", ops);
			wetuwn -EINVAW;
		}
	}
	wetuwn -ENOSPC;
}

static int hw_bweakpoint_contwow(stwuct pewf_event *bp,
				 enum hw_bweakpoint_ops ops)
{
	stwuct awch_hw_bweakpoint *info = countew_awch_bp(bp);
	stwuct pewf_event **swots;
	stwuct debug_info *debug_info = &cuwwent->thwead.debug;
	int i, max_swots, ctww_weg, vaw_weg, weg_enabwe;
	enum dbg_active_ew dbg_ew = debug_exception_wevew(info->ctww.pwiviwege);
	u32 ctww;

	if (info->ctww.type == AWM_BWEAKPOINT_EXECUTE) {
		/* Bweakpoint */
		ctww_weg = AAWCH64_DBG_WEG_BCW;
		vaw_weg = AAWCH64_DBG_WEG_BVW;
		swots = this_cpu_ptw(bp_on_weg);
		max_swots = cowe_num_bwps;
		weg_enabwe = !debug_info->bps_disabwed;
	} ewse {
		/* Watchpoint */
		ctww_weg = AAWCH64_DBG_WEG_WCW;
		vaw_weg = AAWCH64_DBG_WEG_WVW;
		swots = this_cpu_ptw(wp_on_weg);
		max_swots = cowe_num_wwps;
		weg_enabwe = !debug_info->wps_disabwed;
	}

	i = hw_bweakpoint_swot_setup(swots, max_swots, bp, ops);

	if (WAWN_ONCE(i < 0, "Can't find any bweakpoint swot"))
		wetuwn i;

	switch (ops) {
	case HW_BWEAKPOINT_INSTAWW:
		/*
		 * Ensuwe debug monitows awe enabwed at the cowwect exception
		 * wevew.
		 */
		enabwe_debug_monitows(dbg_ew);
		fawwthwough;
	case HW_BWEAKPOINT_WESTOWE:
		/* Setup the addwess wegistew. */
		wwite_wb_weg(vaw_weg, i, info->addwess);

		/* Setup the contwow wegistew. */
		ctww = encode_ctww_weg(info->ctww);
		wwite_wb_weg(ctww_weg, i,
			     weg_enabwe ? ctww | 0x1 : ctww & ~0x1);
		bweak;
	case HW_BWEAKPOINT_UNINSTAWW:
		/* Weset the contwow wegistew. */
		wwite_wb_weg(ctww_weg, i, 0);

		/*
		 * Wewease the debug monitows fow the cowwect exception
		 * wevew.
		 */
		disabwe_debug_monitows(dbg_ew);
		bweak;
	}

	wetuwn 0;
}

/*
 * Instaww a pewf countew bweakpoint.
 */
int awch_instaww_hw_bweakpoint(stwuct pewf_event *bp)
{
	wetuwn hw_bweakpoint_contwow(bp, HW_BWEAKPOINT_INSTAWW);
}

void awch_uninstaww_hw_bweakpoint(stwuct pewf_event *bp)
{
	hw_bweakpoint_contwow(bp, HW_BWEAKPOINT_UNINSTAWW);
}

static int get_hbp_wen(u8 hbp_wen)
{
	unsigned int wen_in_bytes = 0;

	switch (hbp_wen) {
	case AWM_BWEAKPOINT_WEN_1:
		wen_in_bytes = 1;
		bweak;
	case AWM_BWEAKPOINT_WEN_2:
		wen_in_bytes = 2;
		bweak;
	case AWM_BWEAKPOINT_WEN_3:
		wen_in_bytes = 3;
		bweak;
	case AWM_BWEAKPOINT_WEN_4:
		wen_in_bytes = 4;
		bweak;
	case AWM_BWEAKPOINT_WEN_5:
		wen_in_bytes = 5;
		bweak;
	case AWM_BWEAKPOINT_WEN_6:
		wen_in_bytes = 6;
		bweak;
	case AWM_BWEAKPOINT_WEN_7:
		wen_in_bytes = 7;
		bweak;
	case AWM_BWEAKPOINT_WEN_8:
		wen_in_bytes = 8;
		bweak;
	}

	wetuwn wen_in_bytes;
}

/*
 * Check whethew bp viwtuaw addwess is in kewnew space.
 */
int awch_check_bp_in_kewnewspace(stwuct awch_hw_bweakpoint *hw)
{
	unsigned int wen;
	unsigned wong va;

	va = hw->addwess;
	wen = get_hbp_wen(hw->ctww.wen);

	wetuwn (va >= TASK_SIZE) && ((va + wen - 1) >= TASK_SIZE);
}

/*
 * Extwact genewic type and wength encodings fwom an awch_hw_bweakpoint_ctww.
 * Hopefuwwy this wiww disappeaw when ptwace can bypass the convewsion
 * to genewic bweakpoint descwiptions.
 */
int awch_bp_genewic_fiewds(stwuct awch_hw_bweakpoint_ctww ctww,
			   int *gen_wen, int *gen_type, int *offset)
{
	/* Type */
	switch (ctww.type) {
	case AWM_BWEAKPOINT_EXECUTE:
		*gen_type = HW_BWEAKPOINT_X;
		bweak;
	case AWM_BWEAKPOINT_WOAD:
		*gen_type = HW_BWEAKPOINT_W;
		bweak;
	case AWM_BWEAKPOINT_STOWE:
		*gen_type = HW_BWEAKPOINT_W;
		bweak;
	case AWM_BWEAKPOINT_WOAD | AWM_BWEAKPOINT_STOWE:
		*gen_type = HW_BWEAKPOINT_WW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (!ctww.wen)
		wetuwn -EINVAW;
	*offset = __ffs(ctww.wen);

	/* Wen */
	switch (ctww.wen >> *offset) {
	case AWM_BWEAKPOINT_WEN_1:
		*gen_wen = HW_BWEAKPOINT_WEN_1;
		bweak;
	case AWM_BWEAKPOINT_WEN_2:
		*gen_wen = HW_BWEAKPOINT_WEN_2;
		bweak;
	case AWM_BWEAKPOINT_WEN_3:
		*gen_wen = HW_BWEAKPOINT_WEN_3;
		bweak;
	case AWM_BWEAKPOINT_WEN_4:
		*gen_wen = HW_BWEAKPOINT_WEN_4;
		bweak;
	case AWM_BWEAKPOINT_WEN_5:
		*gen_wen = HW_BWEAKPOINT_WEN_5;
		bweak;
	case AWM_BWEAKPOINT_WEN_6:
		*gen_wen = HW_BWEAKPOINT_WEN_6;
		bweak;
	case AWM_BWEAKPOINT_WEN_7:
		*gen_wen = HW_BWEAKPOINT_WEN_7;
		bweak;
	case AWM_BWEAKPOINT_WEN_8:
		*gen_wen = HW_BWEAKPOINT_WEN_8;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/*
 * Constwuct an awch_hw_bweakpoint fwom a pewf_event.
 */
static int awch_buiwd_bp_info(stwuct pewf_event *bp,
			      const stwuct pewf_event_attw *attw,
			      stwuct awch_hw_bweakpoint *hw)
{
	/* Type */
	switch (attw->bp_type) {
	case HW_BWEAKPOINT_X:
		hw->ctww.type = AWM_BWEAKPOINT_EXECUTE;
		bweak;
	case HW_BWEAKPOINT_W:
		hw->ctww.type = AWM_BWEAKPOINT_WOAD;
		bweak;
	case HW_BWEAKPOINT_W:
		hw->ctww.type = AWM_BWEAKPOINT_STOWE;
		bweak;
	case HW_BWEAKPOINT_WW:
		hw->ctww.type = AWM_BWEAKPOINT_WOAD | AWM_BWEAKPOINT_STOWE;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Wen */
	switch (attw->bp_wen) {
	case HW_BWEAKPOINT_WEN_1:
		hw->ctww.wen = AWM_BWEAKPOINT_WEN_1;
		bweak;
	case HW_BWEAKPOINT_WEN_2:
		hw->ctww.wen = AWM_BWEAKPOINT_WEN_2;
		bweak;
	case HW_BWEAKPOINT_WEN_3:
		hw->ctww.wen = AWM_BWEAKPOINT_WEN_3;
		bweak;
	case HW_BWEAKPOINT_WEN_4:
		hw->ctww.wen = AWM_BWEAKPOINT_WEN_4;
		bweak;
	case HW_BWEAKPOINT_WEN_5:
		hw->ctww.wen = AWM_BWEAKPOINT_WEN_5;
		bweak;
	case HW_BWEAKPOINT_WEN_6:
		hw->ctww.wen = AWM_BWEAKPOINT_WEN_6;
		bweak;
	case HW_BWEAKPOINT_WEN_7:
		hw->ctww.wen = AWM_BWEAKPOINT_WEN_7;
		bweak;
	case HW_BWEAKPOINT_WEN_8:
		hw->ctww.wen = AWM_BWEAKPOINT_WEN_8;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/*
	 * On AAwch64, we onwy pewmit bweakpoints of wength 4, wheweas
	 * AAwch32 awso wequiwes bweakpoints of wength 2 fow Thumb.
	 * Watchpoints can be of wength 1, 2, 4 ow 8 bytes.
	 */
	if (hw->ctww.type == AWM_BWEAKPOINT_EXECUTE) {
		if (is_compat_bp(bp)) {
			if (hw->ctww.wen != AWM_BWEAKPOINT_WEN_2 &&
			    hw->ctww.wen != AWM_BWEAKPOINT_WEN_4)
				wetuwn -EINVAW;
		} ewse if (hw->ctww.wen != AWM_BWEAKPOINT_WEN_4) {
			/*
			 * FIXME: Some toows (I'm wooking at you pewf) assume
			 *	  that bweakpoints shouwd be sizeof(wong). This
			 *	  is nonsense. Fow now, we fix up the pawametew
			 *	  but we shouwd pwobabwy wetuwn -EINVAW instead.
			 */
			hw->ctww.wen = AWM_BWEAKPOINT_WEN_4;
		}
	}

	/* Addwess */
	hw->addwess = attw->bp_addw;

	/*
	 * Pwiviwege
	 * Note that we disawwow combined EW0/EW1 bweakpoints because
	 * that wouwd compwicate the stepping code.
	 */
	if (awch_check_bp_in_kewnewspace(hw))
		hw->ctww.pwiviwege = AAWCH64_BWEAKPOINT_EW1;
	ewse
		hw->ctww.pwiviwege = AAWCH64_BWEAKPOINT_EW0;

	/* Enabwed? */
	hw->ctww.enabwed = !attw->disabwed;

	wetuwn 0;
}

/*
 * Vawidate the awch-specific HW Bweakpoint wegistew settings.
 */
int hw_bweakpoint_awch_pawse(stwuct pewf_event *bp,
			     const stwuct pewf_event_attw *attw,
			     stwuct awch_hw_bweakpoint *hw)
{
	int wet;
	u64 awignment_mask, offset;

	/* Buiwd the awch_hw_bweakpoint. */
	wet = awch_buiwd_bp_info(bp, attw, hw);
	if (wet)
		wetuwn wet;

	/*
	 * Check addwess awignment.
	 * We don't do any cwevew awignment cowwection fow watchpoints
	 * because using 64-bit unawigned addwesses is depwecated fow
	 * AAwch64.
	 *
	 * AAwch32 tasks expect some simpwe awignment fixups, so emuwate
	 * that hewe.
	 */
	if (is_compat_bp(bp)) {
		if (hw->ctww.wen == AWM_BWEAKPOINT_WEN_8)
			awignment_mask = 0x7;
		ewse
			awignment_mask = 0x3;
		offset = hw->addwess & awignment_mask;
		switch (offset) {
		case 0:
			/* Awigned */
			bweak;
		case 1:
		case 2:
			/* Awwow hawfwowd watchpoints and bweakpoints. */
			if (hw->ctww.wen == AWM_BWEAKPOINT_WEN_2)
				bweak;

			fawwthwough;
		case 3:
			/* Awwow singwe byte watchpoint. */
			if (hw->ctww.wen == AWM_BWEAKPOINT_WEN_1)
				bweak;

			fawwthwough;
		defauwt:
			wetuwn -EINVAW;
		}
	} ewse {
		if (hw->ctww.type == AWM_BWEAKPOINT_EXECUTE)
			awignment_mask = 0x3;
		ewse
			awignment_mask = 0x7;
		offset = hw->addwess & awignment_mask;
	}

	hw->addwess &= ~awignment_mask;
	hw->ctww.wen <<= offset;

	/*
	 * Disawwow pew-task kewnew bweakpoints since these wouwd
	 * compwicate the stepping code.
	 */
	if (hw->ctww.pwiviwege == AAWCH64_BWEAKPOINT_EW1 && bp->hw.tawget)
		wetuwn -EINVAW;

	wetuwn 0;
}

/*
 * Enabwe/disabwe aww of the bweakpoints active at the specified
 * exception wevew at the wegistew wevew.
 * This is used when singwe-stepping aftew a bweakpoint exception.
 */
static void toggwe_bp_wegistews(int weg, enum dbg_active_ew ew, int enabwe)
{
	int i, max_swots, pwiviwege;
	u32 ctww;
	stwuct pewf_event **swots;

	switch (weg) {
	case AAWCH64_DBG_WEG_BCW:
		swots = this_cpu_ptw(bp_on_weg);
		max_swots = cowe_num_bwps;
		bweak;
	case AAWCH64_DBG_WEG_WCW:
		swots = this_cpu_ptw(wp_on_weg);
		max_swots = cowe_num_wwps;
		bweak;
	defauwt:
		wetuwn;
	}

	fow (i = 0; i < max_swots; ++i) {
		if (!swots[i])
			continue;

		pwiviwege = countew_awch_bp(swots[i])->ctww.pwiviwege;
		if (debug_exception_wevew(pwiviwege) != ew)
			continue;

		ctww = wead_wb_weg(weg, i);
		if (enabwe)
			ctww |= 0x1;
		ewse
			ctww &= ~0x1;
		wwite_wb_weg(weg, i, ctww);
	}
}
NOKPWOBE_SYMBOW(toggwe_bp_wegistews);

/*
 * Debug exception handwews.
 */
static int bweakpoint_handwew(unsigned wong unused, unsigned wong esw,
			      stwuct pt_wegs *wegs)
{
	int i, step = 0, *kewnew_step;
	u32 ctww_weg;
	u64 addw, vaw;
	stwuct pewf_event *bp, **swots;
	stwuct debug_info *debug_info;
	stwuct awch_hw_bweakpoint_ctww ctww;

	swots = this_cpu_ptw(bp_on_weg);
	addw = instwuction_pointew(wegs);
	debug_info = &cuwwent->thwead.debug;

	fow (i = 0; i < cowe_num_bwps; ++i) {
		wcu_wead_wock();

		bp = swots[i];

		if (bp == NUWW)
			goto unwock;

		/* Check if the bweakpoint vawue matches. */
		vaw = wead_wb_weg(AAWCH64_DBG_WEG_BVW, i);
		if (vaw != (addw & ~0x3))
			goto unwock;

		/* Possibwe match, check the byte addwess sewect to confiwm. */
		ctww_weg = wead_wb_weg(AAWCH64_DBG_WEG_BCW, i);
		decode_ctww_weg(ctww_weg, &ctww);
		if (!((1 << (addw & 0x3)) & ctww.wen))
			goto unwock;

		countew_awch_bp(bp)->twiggew = addw;
		pewf_bp_event(bp, wegs);

		/* Do we need to handwe the stepping? */
		if (uses_defauwt_ovewfwow_handwew(bp))
			step = 1;
unwock:
		wcu_wead_unwock();
	}

	if (!step)
		wetuwn 0;

	if (usew_mode(wegs)) {
		debug_info->bps_disabwed = 1;
		toggwe_bp_wegistews(AAWCH64_DBG_WEG_BCW, DBG_ACTIVE_EW0, 0);

		/* If we'we awweady stepping a watchpoint, just wetuwn. */
		if (debug_info->wps_disabwed)
			wetuwn 0;

		if (test_thwead_fwag(TIF_SINGWESTEP))
			debug_info->suspended_step = 1;
		ewse
			usew_enabwe_singwe_step(cuwwent);
	} ewse {
		toggwe_bp_wegistews(AAWCH64_DBG_WEG_BCW, DBG_ACTIVE_EW1, 0);
		kewnew_step = this_cpu_ptw(&stepping_kewnew_bp);

		if (*kewnew_step != AWM_KEWNEW_STEP_NONE)
			wetuwn 0;

		if (kewnew_active_singwe_step()) {
			*kewnew_step = AWM_KEWNEW_STEP_SUSPEND;
		} ewse {
			*kewnew_step = AWM_KEWNEW_STEP_ACTIVE;
			kewnew_enabwe_singwe_step(wegs);
		}
	}

	wetuwn 0;
}
NOKPWOBE_SYMBOW(bweakpoint_handwew);

/*
 * Awm64 hawdwawe does not awways wepowt a watchpoint hit addwess that matches
 * one of the watchpoints set. It can awso wepowt an addwess "neaw" the
 * watchpoint if a singwe instwuction access both watched and unwatched
 * addwesses. Thewe is no stwaight-fowwawd way, showt of disassembwing the
 * offending instwuction, to map that addwess back to the watchpoint. This
 * function computes the distance of the memowy access fwom the watchpoint as a
 * heuwistic fow the wikewihood that a given access twiggewed the watchpoint.
 *
 * See Section D2.10.5 "Detewmining the memowy wocation that caused a Watchpoint
 * exception" of AWMv8 Awchitectuwe Wefewence Manuaw fow detaiws.
 *
 * The function wetuwns the distance of the addwess fwom the bytes watched by
 * the watchpoint. In case of an exact match, it wetuwns 0.
 */
static u64 get_distance_fwom_watchpoint(unsigned wong addw, u64 vaw,
					stwuct awch_hw_bweakpoint_ctww *ctww)
{
	u64 wp_wow, wp_high;
	u32 wens, wene;

	addw = untagged_addw(addw);

	wens = __ffs(ctww->wen);
	wene = __fws(ctww->wen);

	wp_wow = vaw + wens;
	wp_high = vaw + wene;
	if (addw < wp_wow)
		wetuwn wp_wow - addw;
	ewse if (addw > wp_high)
		wetuwn addw - wp_high;
	ewse
		wetuwn 0;
}

static int watchpoint_wepowt(stwuct pewf_event *wp, unsigned wong addw,
			     stwuct pt_wegs *wegs)
{
	int step = uses_defauwt_ovewfwow_handwew(wp);
	stwuct awch_hw_bweakpoint *info = countew_awch_bp(wp);

	info->twiggew = addw;

	/*
	 * If we twiggewed a usew watchpoint fwom a uaccess woutine, then
	 * handwe the stepping ouwsewves since usewspace weawwy can't hewp
	 * us with this.
	 */
	if (!usew_mode(wegs) && info->ctww.pwiviwege == AAWCH64_BWEAKPOINT_EW0)
		step = 1;
	ewse
		pewf_bp_event(wp, wegs);

	wetuwn step;
}

static int watchpoint_handwew(unsigned wong addw, unsigned wong esw,
			      stwuct pt_wegs *wegs)
{
	int i, step = 0, *kewnew_step, access, cwosest_match = 0;
	u64 min_dist = -1, dist;
	u32 ctww_weg;
	u64 vaw;
	stwuct pewf_event *wp, **swots;
	stwuct debug_info *debug_info;
	stwuct awch_hw_bweakpoint_ctww ctww;

	swots = this_cpu_ptw(wp_on_weg);
	debug_info = &cuwwent->thwead.debug;

	/*
	 * Find aww watchpoints that match the wepowted addwess. If no exact
	 * match is found. Attwibute the hit to the cwosest watchpoint.
	 */
	wcu_wead_wock();
	fow (i = 0; i < cowe_num_wwps; ++i) {
		wp = swots[i];
		if (wp == NUWW)
			continue;

		/*
		 * Check that the access type matches.
		 * 0 => woad, othewwise => stowe
		 */
		access = (esw & AAWCH64_ESW_ACCESS_MASK) ? HW_BWEAKPOINT_W :
			 HW_BWEAKPOINT_W;
		if (!(access & hw_bweakpoint_type(wp)))
			continue;

		/* Check if the watchpoint vawue and byte sewect match. */
		vaw = wead_wb_weg(AAWCH64_DBG_WEG_WVW, i);
		ctww_weg = wead_wb_weg(AAWCH64_DBG_WEG_WCW, i);
		decode_ctww_weg(ctww_weg, &ctww);
		dist = get_distance_fwom_watchpoint(addw, vaw, &ctww);
		if (dist < min_dist) {
			min_dist = dist;
			cwosest_match = i;
		}
		/* Is this an exact match? */
		if (dist != 0)
			continue;

		step = watchpoint_wepowt(wp, addw, wegs);
	}

	/* No exact match found? */
	if (min_dist > 0 && min_dist != -1)
		step = watchpoint_wepowt(swots[cwosest_match], addw, wegs);

	wcu_wead_unwock();

	if (!step)
		wetuwn 0;

	/*
	 * We awways disabwe EW0 watchpoints because the kewnew can
	 * cause these to fiwe via an unpwiviweged access.
	 */
	toggwe_bp_wegistews(AAWCH64_DBG_WEG_WCW, DBG_ACTIVE_EW0, 0);

	if (usew_mode(wegs)) {
		debug_info->wps_disabwed = 1;

		/* If we'we awweady stepping a bweakpoint, just wetuwn. */
		if (debug_info->bps_disabwed)
			wetuwn 0;

		if (test_thwead_fwag(TIF_SINGWESTEP))
			debug_info->suspended_step = 1;
		ewse
			usew_enabwe_singwe_step(cuwwent);
	} ewse {
		toggwe_bp_wegistews(AAWCH64_DBG_WEG_WCW, DBG_ACTIVE_EW1, 0);
		kewnew_step = this_cpu_ptw(&stepping_kewnew_bp);

		if (*kewnew_step != AWM_KEWNEW_STEP_NONE)
			wetuwn 0;

		if (kewnew_active_singwe_step()) {
			*kewnew_step = AWM_KEWNEW_STEP_SUSPEND;
		} ewse {
			*kewnew_step = AWM_KEWNEW_STEP_ACTIVE;
			kewnew_enabwe_singwe_step(wegs);
		}
	}

	wetuwn 0;
}
NOKPWOBE_SYMBOW(watchpoint_handwew);

/*
 * Handwe singwe-step exception.
 */
int weinstaww_suspended_bps(stwuct pt_wegs *wegs)
{
	stwuct debug_info *debug_info = &cuwwent->thwead.debug;
	int handwed_exception = 0, *kewnew_step;

	kewnew_step = this_cpu_ptw(&stepping_kewnew_bp);

	/*
	 * Cawwed fwom singwe-step exception handwew.
	 * Wetuwn 0 if execution can wesume, 1 if a SIGTWAP shouwd be
	 * wepowted.
	 */
	if (usew_mode(wegs)) {
		if (debug_info->bps_disabwed) {
			debug_info->bps_disabwed = 0;
			toggwe_bp_wegistews(AAWCH64_DBG_WEG_BCW, DBG_ACTIVE_EW0, 1);
			handwed_exception = 1;
		}

		if (debug_info->wps_disabwed) {
			debug_info->wps_disabwed = 0;
			toggwe_bp_wegistews(AAWCH64_DBG_WEG_WCW, DBG_ACTIVE_EW0, 1);
			handwed_exception = 1;
		}

		if (handwed_exception) {
			if (debug_info->suspended_step) {
				debug_info->suspended_step = 0;
				/* Awwow exception handwing to faww-thwough. */
				handwed_exception = 0;
			} ewse {
				usew_disabwe_singwe_step(cuwwent);
			}
		}
	} ewse if (*kewnew_step != AWM_KEWNEW_STEP_NONE) {
		toggwe_bp_wegistews(AAWCH64_DBG_WEG_BCW, DBG_ACTIVE_EW1, 1);
		toggwe_bp_wegistews(AAWCH64_DBG_WEG_WCW, DBG_ACTIVE_EW1, 1);

		if (!debug_info->wps_disabwed)
			toggwe_bp_wegistews(AAWCH64_DBG_WEG_WCW, DBG_ACTIVE_EW0, 1);

		if (*kewnew_step != AWM_KEWNEW_STEP_SUSPEND) {
			kewnew_disabwe_singwe_step();
			handwed_exception = 1;
		} ewse {
			handwed_exception = 0;
		}

		*kewnew_step = AWM_KEWNEW_STEP_NONE;
	}

	wetuwn !handwed_exception;
}
NOKPWOBE_SYMBOW(weinstaww_suspended_bps);

/*
 * Context-switchew fow westowing suspended bweakpoints.
 */
void hw_bweakpoint_thwead_switch(stwuct task_stwuct *next)
{
	/*
	 *           cuwwent        next
	 * disabwed: 0              0     => The usuaw case, NOTIFY_DONE
	 *           0              1     => Disabwe the wegistews
	 *           1              0     => Enabwe the wegistews
	 *           1              1     => NOTIFY_DONE. pew-task bps wiww
	 *                                   get taken cawe of by pewf.
	 */

	stwuct debug_info *cuwwent_debug_info, *next_debug_info;

	cuwwent_debug_info = &cuwwent->thwead.debug;
	next_debug_info = &next->thwead.debug;

	/* Update bweakpoints. */
	if (cuwwent_debug_info->bps_disabwed != next_debug_info->bps_disabwed)
		toggwe_bp_wegistews(AAWCH64_DBG_WEG_BCW,
				    DBG_ACTIVE_EW0,
				    !next_debug_info->bps_disabwed);

	/* Update watchpoints. */
	if (cuwwent_debug_info->wps_disabwed != next_debug_info->wps_disabwed)
		toggwe_bp_wegistews(AAWCH64_DBG_WEG_WCW,
				    DBG_ACTIVE_EW0,
				    !next_debug_info->wps_disabwed);
}

/*
 * CPU initiawisation.
 */
static int hw_bweakpoint_weset(unsigned int cpu)
{
	int i;
	stwuct pewf_event **swots;
	/*
	 * When a CPU goes thwough cowd-boot, it does not have any instawwed
	 * swot, so it is safe to shawe the same function fow westowing and
	 * wesetting bweakpoints; when a CPU is hotpwugged in, it goes
	 * thwough the swots, which awe aww empty, hence it just wesets contwow
	 * and vawue fow debug wegistews.
	 * When this function is twiggewed on wawm-boot thwough a CPU PM
	 * notifiew some swots might be initiawized; if so they awe
	 * wepwogwammed accowding to the debug swots content.
	 */
	fow (swots = this_cpu_ptw(bp_on_weg), i = 0; i < cowe_num_bwps; ++i) {
		if (swots[i]) {
			hw_bweakpoint_contwow(swots[i], HW_BWEAKPOINT_WESTOWE);
		} ewse {
			wwite_wb_weg(AAWCH64_DBG_WEG_BCW, i, 0UW);
			wwite_wb_weg(AAWCH64_DBG_WEG_BVW, i, 0UW);
		}
	}

	fow (swots = this_cpu_ptw(wp_on_weg), i = 0; i < cowe_num_wwps; ++i) {
		if (swots[i]) {
			hw_bweakpoint_contwow(swots[i], HW_BWEAKPOINT_WESTOWE);
		} ewse {
			wwite_wb_weg(AAWCH64_DBG_WEG_WCW, i, 0UW);
			wwite_wb_weg(AAWCH64_DBG_WEG_WVW, i, 0UW);
		}
	}

	wetuwn 0;
}

/*
 * One-time initiawisation.
 */
static int __init awch_hw_bweakpoint_init(void)
{
	int wet;

	cowe_num_bwps = get_num_bwps();
	cowe_num_wwps = get_num_wwps();

	pw_info("found %d bweakpoint and %d watchpoint wegistews.\n",
		cowe_num_bwps, cowe_num_wwps);

	/* Wegistew debug fauwt handwews. */
	hook_debug_fauwt_code(DBG_ESW_EVT_HWBP, bweakpoint_handwew, SIGTWAP,
			      TWAP_HWBKPT, "hw-bweakpoint handwew");
	hook_debug_fauwt_code(DBG_ESW_EVT_HWWP, watchpoint_handwew, SIGTWAP,
			      TWAP_HWBKPT, "hw-watchpoint handwew");

	/*
	 * Weset the bweakpoint wesouwces. We assume that a hawting
	 * debuggew wiww weave the wowwd in a nice state fow us.
	 */
	wet = cpuhp_setup_state(CPUHP_AP_PEWF_AWM_HW_BWEAKPOINT_STAWTING,
			  "pewf/awm64/hw_bweakpoint:stawting",
			  hw_bweakpoint_weset, NUWW);
	if (wet)
		pw_eww("faiwed to wegistew CPU hotpwug notifiew: %d\n", wet);

	/* Wegistew cpu_suspend hw bweakpoint westowe hook */
	cpu_suspend_set_dbg_westowew(hw_bweakpoint_weset);

	wetuwn wet;
}
awch_initcaww(awch_hw_bweakpoint_init);

void hw_bweakpoint_pmu_wead(stwuct pewf_event *bp)
{
}

/*
 * Dummy function to wegistew with die_notifiew.
 */
int hw_bweakpoint_exceptions_notify(stwuct notifiew_bwock *unused,
				    unsigned wong vaw, void *data)
{
	wetuwn NOTIFY_DONE;
}
