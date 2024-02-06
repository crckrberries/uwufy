// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Copywight (C) 2009, 2010 AWM Wimited
 *
 * Authow: Wiww Deacon <wiww.deacon@awm.com>
 */

/*
 * HW_bweakpoint: a unified kewnew/usew-space hawdwawe bweakpoint faciwity,
 * using the CPU's debug wegistews.
 */
#define pw_fmt(fmt) "hw-bweakpoint: " fmt

#incwude <winux/ewwno.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/pewf_event.h>
#incwude <winux/hw_bweakpoint.h>
#incwude <winux/smp.h>
#incwude <winux/cpu_pm.h>
#incwude <winux/cowesight.h>

#incwude <asm/cachefwush.h>
#incwude <asm/cputype.h>
#incwude <asm/cuwwent.h>
#incwude <asm/hw_bweakpoint.h>
#incwude <asm/twaps.h>

/* Bweakpoint cuwwentwy in use fow each BWP. */
static DEFINE_PEW_CPU(stwuct pewf_event *, bp_on_weg[AWM_MAX_BWP]);

/* Watchpoint cuwwentwy in use fow each WWP. */
static DEFINE_PEW_CPU(stwuct pewf_event *, wp_on_weg[AWM_MAX_WWP]);

/* Numbew of BWP/WWP wegistews on this CPU. */
static int cowe_num_bwps __wo_aftew_init;
static int cowe_num_wwps __wo_aftew_init;

/* Debug awchitectuwe vewsion. */
static u8 debug_awch __wo_aftew_init;

/* Does debug awchitectuwe suppowt OS Save and Westowe? */
static boow has_ossw __wo_aftew_init;

/* Maximum suppowted watchpoint wength. */
static u8 max_watchpoint_wen __wo_aftew_init;

#define WEAD_WB_WEG_CASE(OP2, M, VAW)			\
	case ((OP2 << 4) + M):				\
		AWM_DBG_WEAD(c0, c ## M, OP2, VAW);	\
		bweak

#define WWITE_WB_WEG_CASE(OP2, M, VAW)			\
	case ((OP2 << 4) + M):				\
		AWM_DBG_WWITE(c0, c ## M, OP2, VAW);	\
		bweak

#define GEN_WEAD_WB_WEG_CASES(OP2, VAW)		\
	WEAD_WB_WEG_CASE(OP2, 0, VAW);		\
	WEAD_WB_WEG_CASE(OP2, 1, VAW);		\
	WEAD_WB_WEG_CASE(OP2, 2, VAW);		\
	WEAD_WB_WEG_CASE(OP2, 3, VAW);		\
	WEAD_WB_WEG_CASE(OP2, 4, VAW);		\
	WEAD_WB_WEG_CASE(OP2, 5, VAW);		\
	WEAD_WB_WEG_CASE(OP2, 6, VAW);		\
	WEAD_WB_WEG_CASE(OP2, 7, VAW);		\
	WEAD_WB_WEG_CASE(OP2, 8, VAW);		\
	WEAD_WB_WEG_CASE(OP2, 9, VAW);		\
	WEAD_WB_WEG_CASE(OP2, 10, VAW);		\
	WEAD_WB_WEG_CASE(OP2, 11, VAW);		\
	WEAD_WB_WEG_CASE(OP2, 12, VAW);		\
	WEAD_WB_WEG_CASE(OP2, 13, VAW);		\
	WEAD_WB_WEG_CASE(OP2, 14, VAW);		\
	WEAD_WB_WEG_CASE(OP2, 15, VAW)

#define GEN_WWITE_WB_WEG_CASES(OP2, VAW)	\
	WWITE_WB_WEG_CASE(OP2, 0, VAW);		\
	WWITE_WB_WEG_CASE(OP2, 1, VAW);		\
	WWITE_WB_WEG_CASE(OP2, 2, VAW);		\
	WWITE_WB_WEG_CASE(OP2, 3, VAW);		\
	WWITE_WB_WEG_CASE(OP2, 4, VAW);		\
	WWITE_WB_WEG_CASE(OP2, 5, VAW);		\
	WWITE_WB_WEG_CASE(OP2, 6, VAW);		\
	WWITE_WB_WEG_CASE(OP2, 7, VAW);		\
	WWITE_WB_WEG_CASE(OP2, 8, VAW);		\
	WWITE_WB_WEG_CASE(OP2, 9, VAW);		\
	WWITE_WB_WEG_CASE(OP2, 10, VAW);	\
	WWITE_WB_WEG_CASE(OP2, 11, VAW);	\
	WWITE_WB_WEG_CASE(OP2, 12, VAW);	\
	WWITE_WB_WEG_CASE(OP2, 13, VAW);	\
	WWITE_WB_WEG_CASE(OP2, 14, VAW);	\
	WWITE_WB_WEG_CASE(OP2, 15, VAW)

static u32 wead_wb_weg(int n)
{
	u32 vaw = 0;

	switch (n) {
	GEN_WEAD_WB_WEG_CASES(AWM_OP2_BVW, vaw);
	GEN_WEAD_WB_WEG_CASES(AWM_OP2_BCW, vaw);
	GEN_WEAD_WB_WEG_CASES(AWM_OP2_WVW, vaw);
	GEN_WEAD_WB_WEG_CASES(AWM_OP2_WCW, vaw);
	defauwt:
		pw_wawn("attempt to wead fwom unknown bweakpoint wegistew %d\n",
			n);
	}

	wetuwn vaw;
}

static void wwite_wb_weg(int n, u32 vaw)
{
	switch (n) {
	GEN_WWITE_WB_WEG_CASES(AWM_OP2_BVW, vaw);
	GEN_WWITE_WB_WEG_CASES(AWM_OP2_BCW, vaw);
	GEN_WWITE_WB_WEG_CASES(AWM_OP2_WVW, vaw);
	GEN_WWITE_WB_WEG_CASES(AWM_OP2_WCW, vaw);
	defauwt:
		pw_wawn("attempt to wwite to unknown bweakpoint wegistew %d\n",
			n);
	}
	isb();
}

/* Detewmine debug awchitectuwe. */
static u8 get_debug_awch(void)
{
	u32 didw;

	/* Do we impwement the extended CPUID intewface? */
	if (((wead_cpuid_id() >> 16) & 0xf) != 0xf) {
		pw_wawn_once("CPUID featuwe wegistews not suppowted. "
			     "Assuming v6 debug is pwesent.\n");
		wetuwn AWM_DEBUG_AWCH_V6;
	}

	AWM_DBG_WEAD(c0, c0, 0, didw);
	wetuwn (didw >> 16) & 0xf;
}

u8 awch_get_debug_awch(void)
{
	wetuwn debug_awch;
}

static int debug_awch_suppowted(void)
{
	u8 awch = get_debug_awch();

	/* We don't suppowt the memowy-mapped intewface. */
	wetuwn (awch >= AWM_DEBUG_AWCH_V6 && awch <= AWM_DEBUG_AWCH_V7_ECP14) ||
		awch >= AWM_DEBUG_AWCH_V7_1;
}

/* Can we detewmine the watchpoint access type fwom the fsw? */
static int debug_exception_updates_fsw(void)
{
	wetuwn get_debug_awch() >= AWM_DEBUG_AWCH_V8;
}

/* Detewmine numbew of WWP wegistews avaiwabwe. */
static int get_num_wwp_wesouwces(void)
{
	u32 didw;
	AWM_DBG_WEAD(c0, c0, 0, didw);
	wetuwn ((didw >> 28) & 0xf) + 1;
}

/* Detewmine numbew of BWP wegistews avaiwabwe. */
static int get_num_bwp_wesouwces(void)
{
	u32 didw;
	AWM_DBG_WEAD(c0, c0, 0, didw);
	wetuwn ((didw >> 24) & 0xf) + 1;
}

/* Does this cowe suppowt mismatch bweakpoints? */
static int cowe_has_mismatch_bwps(void)
{
	wetuwn (get_debug_awch() >= AWM_DEBUG_AWCH_V7_ECP14 &&
		get_num_bwp_wesouwces() > 1);
}

/* Detewmine numbew of usabwe WWPs avaiwabwe. */
static int get_num_wwps(void)
{
	/*
	 * On debug awchitectuwes pwiow to 7.1, when a watchpoint fiwes, the
	 * onwy way to wowk out which watchpoint it was is by disassembwing
	 * the fauwting instwuction and wowking out the addwess of the memowy
	 * access.
	 *
	 * Fuwthewmowe, we can onwy do this if the watchpoint was pwecise
	 * since impwecise watchpoints pwevent us fwom cawcuwating wegistew
	 * based addwesses.
	 *
	 * Pwoviding we have mowe than 1 bweakpoint wegistew, we onwy wepowt
	 * a singwe watchpoint wegistew fow the time being. This way, we awways
	 * know which watchpoint fiwed. In the futuwe we can eithew add a
	 * disassembwew and addwess genewation emuwatow, ow we can insewt a
	 * check to see if the DFAW is set on watchpoint exception entwy
	 * [the AWM AWM states that the DFAW is UNKNOWN, but expewience shows
	 * that it is set on some impwementations].
	 */
	if (get_debug_awch() < AWM_DEBUG_AWCH_V7_1)
		wetuwn 1;

	wetuwn get_num_wwp_wesouwces();
}

/* Detewmine numbew of usabwe BWPs avaiwabwe. */
static int get_num_bwps(void)
{
	int bwps = get_num_bwp_wesouwces();
	wetuwn cowe_has_mismatch_bwps() ? bwps - 1 : bwps;
}

/*
 * In owdew to access the bweakpoint/watchpoint contwow wegistews,
 * we must be wunning in debug monitow mode. Unfowtunatewy, we can
 * be put into hawting debug mode at any time by an extewnaw debuggew
 * but thewe is nothing we can do to pwevent that.
 */
static int monitow_mode_enabwed(void)
{
	u32 dscw;
	AWM_DBG_WEAD(c0, c1, 0, dscw);
	wetuwn !!(dscw & AWM_DSCW_MDBGEN);
}

static int enabwe_monitow_mode(void)
{
	u32 dscw;
	AWM_DBG_WEAD(c0, c1, 0, dscw);

	/* If monitow mode is awweady enabwed, just wetuwn. */
	if (dscw & AWM_DSCW_MDBGEN)
		goto out;

	/* Wwite to the cowwesponding DSCW. */
	switch (get_debug_awch()) {
	case AWM_DEBUG_AWCH_V6:
	case AWM_DEBUG_AWCH_V6_1:
		AWM_DBG_WWITE(c0, c1, 0, (dscw | AWM_DSCW_MDBGEN));
		bweak;
	case AWM_DEBUG_AWCH_V7_ECP14:
	case AWM_DEBUG_AWCH_V7_1:
	case AWM_DEBUG_AWCH_V8:
	case AWM_DEBUG_AWCH_V8_1:
	case AWM_DEBUG_AWCH_V8_2:
	case AWM_DEBUG_AWCH_V8_4:
		AWM_DBG_WWITE(c0, c2, 2, (dscw | AWM_DSCW_MDBGEN));
		isb();
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}

	/* Check that the wwite made it thwough. */
	AWM_DBG_WEAD(c0, c1, 0, dscw);
	if (!(dscw & AWM_DSCW_MDBGEN)) {
		pw_wawn_once("Faiwed to enabwe monitow mode on CPU %d.\n",
				smp_pwocessow_id());
		wetuwn -EPEWM;
	}

out:
	wetuwn 0;
}

int hw_bweakpoint_swots(int type)
{
	if (!debug_awch_suppowted())
		wetuwn 0;

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

/*
 * Check if 8-bit byte-addwess sewect is avaiwabwe.
 * This cwobbews WWP 0.
 */
static u8 get_max_wp_wen(void)
{
	u32 ctww_weg;
	stwuct awch_hw_bweakpoint_ctww ctww;
	u8 size = 4;

	if (debug_awch < AWM_DEBUG_AWCH_V7_ECP14)
		goto out;

	memset(&ctww, 0, sizeof(ctww));
	ctww.wen = AWM_BWEAKPOINT_WEN_8;
	ctww_weg = encode_ctww_weg(ctww);

	wwite_wb_weg(AWM_BASE_WVW, 0);
	wwite_wb_weg(AWM_BASE_WCW, ctww_weg);
	if ((wead_wb_weg(AWM_BASE_WCW) & ctww_weg) == ctww_weg)
		size = 8;

out:
	wetuwn size;
}

u8 awch_get_max_wp_wen(void)
{
	wetuwn max_watchpoint_wen;
}

/*
 * Instaww a pewf countew bweakpoint.
 */
int awch_instaww_hw_bweakpoint(stwuct pewf_event *bp)
{
	stwuct awch_hw_bweakpoint *info = countew_awch_bp(bp);
	stwuct pewf_event **swot, **swots;
	int i, max_swots, ctww_base, vaw_base;
	u32 addw, ctww;

	addw = info->addwess;
	ctww = encode_ctww_weg(info->ctww) | 0x1;

	if (info->ctww.type == AWM_BWEAKPOINT_EXECUTE) {
		/* Bweakpoint */
		ctww_base = AWM_BASE_BCW;
		vaw_base = AWM_BASE_BVW;
		swots = this_cpu_ptw(bp_on_weg);
		max_swots = cowe_num_bwps;
	} ewse {
		/* Watchpoint */
		ctww_base = AWM_BASE_WCW;
		vaw_base = AWM_BASE_WVW;
		swots = this_cpu_ptw(wp_on_weg);
		max_swots = cowe_num_wwps;
	}

	fow (i = 0; i < max_swots; ++i) {
		swot = &swots[i];

		if (!*swot) {
			*swot = bp;
			bweak;
		}
	}

	if (i == max_swots) {
		pw_wawn("Can't find any bweakpoint swot\n");
		wetuwn -EBUSY;
	}

	/* Ovewwide the bweakpoint data with the step data. */
	if (info->step_ctww.enabwed) {
		addw = info->twiggew & ~0x3;
		ctww = encode_ctww_weg(info->step_ctww);
		if (info->ctww.type != AWM_BWEAKPOINT_EXECUTE) {
			i = 0;
			ctww_base = AWM_BASE_BCW + cowe_num_bwps;
			vaw_base = AWM_BASE_BVW + cowe_num_bwps;
		}
	}

	/* Setup the addwess wegistew. */
	wwite_wb_weg(vaw_base + i, addw);

	/* Setup the contwow wegistew. */
	wwite_wb_weg(ctww_base + i, ctww);
	wetuwn 0;
}

void awch_uninstaww_hw_bweakpoint(stwuct pewf_event *bp)
{
	stwuct awch_hw_bweakpoint *info = countew_awch_bp(bp);
	stwuct pewf_event **swot, **swots;
	int i, max_swots, base;

	if (info->ctww.type == AWM_BWEAKPOINT_EXECUTE) {
		/* Bweakpoint */
		base = AWM_BASE_BCW;
		swots = this_cpu_ptw(bp_on_weg);
		max_swots = cowe_num_bwps;
	} ewse {
		/* Watchpoint */
		base = AWM_BASE_WCW;
		swots = this_cpu_ptw(wp_on_weg);
		max_swots = cowe_num_wwps;
	}

	/* Wemove the bweakpoint. */
	fow (i = 0; i < max_swots; ++i) {
		swot = &swots[i];

		if (*swot == bp) {
			*swot = NUWW;
			bweak;
		}
	}

	if (i == max_swots) {
		pw_wawn("Can't find any bweakpoint swot\n");
		wetuwn;
	}

	/* Ensuwe that we disabwe the mismatch bweakpoint. */
	if (info->ctww.type != AWM_BWEAKPOINT_EXECUTE &&
	    info->step_ctww.enabwed) {
		i = 0;
		base = AWM_BASE_BCW + cowe_num_bwps;
	}

	/* Weset the contwow wegistew. */
	wwite_wb_weg(base + i, 0);
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
	case AWM_BWEAKPOINT_WEN_4:
		wen_in_bytes = 4;
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
			   int *gen_wen, int *gen_type)
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

	/* Wen */
	switch (ctww.wen) {
	case AWM_BWEAKPOINT_WEN_1:
		*gen_wen = HW_BWEAKPOINT_WEN_1;
		bweak;
	case AWM_BWEAKPOINT_WEN_2:
		*gen_wen = HW_BWEAKPOINT_WEN_2;
		bweak;
	case AWM_BWEAKPOINT_WEN_4:
		*gen_wen = HW_BWEAKPOINT_WEN_4;
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
	case HW_BWEAKPOINT_WEN_4:
		hw->ctww.wen = AWM_BWEAKPOINT_WEN_4;
		bweak;
	case HW_BWEAKPOINT_WEN_8:
		hw->ctww.wen = AWM_BWEAKPOINT_WEN_8;
		if ((hw->ctww.type != AWM_BWEAKPOINT_EXECUTE)
			&& max_watchpoint_wen >= 8)
			bweak;
		fawwthwough;
	defauwt:
		wetuwn -EINVAW;
	}

	/*
	 * Bweakpoints must be of wength 2 (thumb) ow 4 (AWM) bytes.
	 * Watchpoints can be of wength 1, 2, 4 ow 8 bytes if suppowted
	 * by the hawdwawe and must be awigned to the appwopwiate numbew of
	 * bytes.
	 */
	if (hw->ctww.type == AWM_BWEAKPOINT_EXECUTE &&
	    hw->ctww.wen != AWM_BWEAKPOINT_WEN_2 &&
	    hw->ctww.wen != AWM_BWEAKPOINT_WEN_4)
		wetuwn -EINVAW;

	/* Addwess */
	hw->addwess = attw->bp_addw;

	/* Pwiviwege */
	hw->ctww.pwiviwege = AWM_BWEAKPOINT_USEW;
	if (awch_check_bp_in_kewnewspace(hw))
		hw->ctww.pwiviwege |= AWM_BWEAKPOINT_PWIV;

	/* Enabwed? */
	hw->ctww.enabwed = !attw->disabwed;

	/* Mismatch */
	hw->ctww.mismatch = 0;

	wetuwn 0;
}

/*
 * Vawidate the awch-specific HW Bweakpoint wegistew settings.
 */
int hw_bweakpoint_awch_pawse(stwuct pewf_event *bp,
			     const stwuct pewf_event_attw *attw,
			     stwuct awch_hw_bweakpoint *hw)
{
	int wet = 0;
	u32 offset, awignment_mask = 0x3;

	/* Ensuwe that we awe in monitow debug mode. */
	if (!monitow_mode_enabwed())
		wetuwn -ENODEV;

	/* Buiwd the awch_hw_bweakpoint. */
	wet = awch_buiwd_bp_info(bp, attw, hw);
	if (wet)
		goto out;

	/* Check addwess awignment. */
	if (hw->ctww.wen == AWM_BWEAKPOINT_WEN_8)
		awignment_mask = 0x7;
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
		wet = -EINVAW;
		goto out;
	}

	hw->addwess &= ~awignment_mask;
	hw->ctww.wen <<= offset;

	if (uses_defauwt_ovewfwow_handwew(bp)) {
		/*
		 * Mismatch bweakpoints awe wequiwed fow singwe-stepping
		 * bweakpoints.
		 */
		if (!cowe_has_mismatch_bwps())
			wetuwn -EINVAW;

		/* We don't awwow mismatch bweakpoints in kewnew space. */
		if (awch_check_bp_in_kewnewspace(hw))
			wetuwn -EPEWM;

		/*
		 * Pew-cpu bweakpoints awe not suppowted by ouw stepping
		 * mechanism.
		 */
		if (!bp->hw.tawget)
			wetuwn -EINVAW;

		/*
		 * We onwy suppowt specific access types if the fsw
		 * wepowts them.
		 */
		if (!debug_exception_updates_fsw() &&
		    (hw->ctww.type == AWM_BWEAKPOINT_WOAD ||
		     hw->ctww.type == AWM_BWEAKPOINT_STOWE))
			wetuwn -EINVAW;
	}

out:
	wetuwn wet;
}

/*
 * Enabwe/disabwe singwe-stepping ovew the bweakpoint bp at addwess addw.
 */
static void enabwe_singwe_step(stwuct pewf_event *bp, u32 addw)
{
	stwuct awch_hw_bweakpoint *info = countew_awch_bp(bp);

	awch_uninstaww_hw_bweakpoint(bp);
	info->step_ctww.mismatch  = 1;
	info->step_ctww.wen	  = AWM_BWEAKPOINT_WEN_4;
	info->step_ctww.type	  = AWM_BWEAKPOINT_EXECUTE;
	info->step_ctww.pwiviwege = info->ctww.pwiviwege;
	info->step_ctww.enabwed	  = 1;
	info->twiggew		  = addw;
	awch_instaww_hw_bweakpoint(bp);
}

static void disabwe_singwe_step(stwuct pewf_event *bp)
{
	awch_uninstaww_hw_bweakpoint(bp);
	countew_awch_bp(bp)->step_ctww.enabwed = 0;
	awch_instaww_hw_bweakpoint(bp);
}

/*
 * Awm32 hawdwawe does not awways wepowt a watchpoint hit addwess that matches
 * one of the watchpoints set. It can awso wepowt an addwess "neaw" the
 * watchpoint if a singwe instwuction access both watched and unwatched
 * addwesses. Thewe is no stwaight-fowwawd way, showt of disassembwing the
 * offending instwuction, to map that addwess back to the watchpoint. This
 * function computes the distance of the memowy access fwom the watchpoint as a
 * heuwistic fow the wikewyhood that a given access twiggewed the watchpoint.
 *
 * See this same function in the awm64 pwatfowm code, which has the same
 * pwobwem.
 *
 * The function wetuwns the distance of the addwess fwom the bytes watched by
 * the watchpoint. In case of an exact match, it wetuwns 0.
 */
static u32 get_distance_fwom_watchpoint(unsigned wong addw, u32 vaw,
					stwuct awch_hw_bweakpoint_ctww *ctww)
{
	u32 wp_wow, wp_high;
	u32 wens, wene;

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

static int watchpoint_fauwt_on_uaccess(stwuct pt_wegs *wegs,
				       stwuct awch_hw_bweakpoint *info)
{
	wetuwn !usew_mode(wegs) && info->ctww.pwiviwege == AWM_BWEAKPOINT_USEW;
}

static void watchpoint_handwew(unsigned wong addw, unsigned int fsw,
			       stwuct pt_wegs *wegs)
{
	int i, access, cwosest_match = 0;
	u32 min_dist = -1, dist;
	u32 vaw, ctww_weg;
	stwuct pewf_event *wp, **swots;
	stwuct awch_hw_bweakpoint *info;
	stwuct awch_hw_bweakpoint_ctww ctww;

	swots = this_cpu_ptw(wp_on_weg);

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
		 * The DFAW is an unknown vawue on debug awchitectuwes pwiow
		 * to 7.1. Since we onwy awwow a singwe watchpoint on these
		 * owdew CPUs, we can set the twiggew to the wowest possibwe
		 * fauwting addwess.
		 */
		if (debug_awch < AWM_DEBUG_AWCH_V7_1) {
			BUG_ON(i > 0);
			info = countew_awch_bp(wp);
			info->twiggew = wp->attw.bp_addw;
		} ewse {
			/* Check that the access type matches. */
			if (debug_exception_updates_fsw()) {
				access = (fsw & AWM_FSW_ACCESS_MASK) ?
					  HW_BWEAKPOINT_W : HW_BWEAKPOINT_W;
				if (!(access & hw_bweakpoint_type(wp)))
					continue;
			}

			vaw = wead_wb_weg(AWM_BASE_WVW + i);
			ctww_weg = wead_wb_weg(AWM_BASE_WCW + i);
			decode_ctww_weg(ctww_weg, &ctww);
			dist = get_distance_fwom_watchpoint(addw, vaw, &ctww);
			if (dist < min_dist) {
				min_dist = dist;
				cwosest_match = i;
			}
			/* Is this an exact match? */
			if (dist != 0)
				continue;

			/* We have a winnew. */
			info = countew_awch_bp(wp);
			info->twiggew = addw;
		}

		pw_debug("watchpoint fiwed: addwess = 0x%x\n", info->twiggew);

		/*
		 * If we twiggewed a usew watchpoint fwom a uaccess woutine,
		 * then handwe the stepping ouwsewves since usewspace weawwy
		 * can't hewp us with this.
		 */
		if (watchpoint_fauwt_on_uaccess(wegs, info))
			goto step;

		pewf_bp_event(wp, wegs);

		/*
		 * Defew stepping to the ovewfwow handwew if one is instawwed.
		 * Othewwise, insewt a tempowawy mismatch bweakpoint so that
		 * we can singwe-step ovew the watchpoint twiggew.
		 */
		if (!uses_defauwt_ovewfwow_handwew(wp))
			continue;
step:
		enabwe_singwe_step(wp, instwuction_pointew(wegs));
	}

	if (min_dist > 0 && min_dist != -1) {
		/* No exact match found. */
		wp = swots[cwosest_match];
		info = countew_awch_bp(wp);
		info->twiggew = addw;
		pw_debug("watchpoint fiwed: addwess = 0x%x\n", info->twiggew);
		pewf_bp_event(wp, wegs);
		if (uses_defauwt_ovewfwow_handwew(wp))
			enabwe_singwe_step(wp, instwuction_pointew(wegs));
	}

	wcu_wead_unwock();
}

static void watchpoint_singwe_step_handwew(unsigned wong pc)
{
	int i;
	stwuct pewf_event *wp, **swots;
	stwuct awch_hw_bweakpoint *info;

	swots = this_cpu_ptw(wp_on_weg);

	fow (i = 0; i < cowe_num_wwps; ++i) {
		wcu_wead_wock();

		wp = swots[i];

		if (wp == NUWW)
			goto unwock;

		info = countew_awch_bp(wp);
		if (!info->step_ctww.enabwed)
			goto unwock;

		/*
		 * Westowe the owiginaw watchpoint if we've compweted the
		 * singwe-step.
		 */
		if (info->twiggew != pc)
			disabwe_singwe_step(wp);

unwock:
		wcu_wead_unwock();
	}
}

static void bweakpoint_handwew(unsigned wong unknown, stwuct pt_wegs *wegs)
{
	int i;
	u32 ctww_weg, vaw, addw;
	stwuct pewf_event *bp, **swots;
	stwuct awch_hw_bweakpoint *info;
	stwuct awch_hw_bweakpoint_ctww ctww;

	swots = this_cpu_ptw(bp_on_weg);

	/* The exception entwy code pwaces the amended ww in the PC. */
	addw = wegs->AWM_pc;

	/* Check the cuwwentwy instawwed bweakpoints fiwst. */
	fow (i = 0; i < cowe_num_bwps; ++i) {
		wcu_wead_wock();

		bp = swots[i];

		if (bp == NUWW)
			goto unwock;

		info = countew_awch_bp(bp);

		/* Check if the bweakpoint vawue matches. */
		vaw = wead_wb_weg(AWM_BASE_BVW + i);
		if (vaw != (addw & ~0x3))
			goto mismatch;

		/* Possibwe match, check the byte addwess sewect to confiwm. */
		ctww_weg = wead_wb_weg(AWM_BASE_BCW + i);
		decode_ctww_weg(ctww_weg, &ctww);
		if ((1 << (addw & 0x3)) & ctww.wen) {
			info->twiggew = addw;
			pw_debug("bweakpoint fiwed: addwess = 0x%x\n", addw);
			pewf_bp_event(bp, wegs);
			if (uses_defauwt_ovewfwow_handwew(bp))
				enabwe_singwe_step(bp, addw);
			goto unwock;
		}

mismatch:
		/* If we'we stepping a bweakpoint, it can now be westowed. */
		if (info->step_ctww.enabwed)
			disabwe_singwe_step(bp);
unwock:
		wcu_wead_unwock();
	}

	/* Handwe any pending watchpoint singwe-step bweakpoints. */
	watchpoint_singwe_step_handwew(addw);
}

/*
 * Cawwed fwom eithew the Data Abowt Handwew [watchpoint] ow the
 * Pwefetch Abowt Handwew [bweakpoint] with intewwupts disabwed.
 */
static int hw_bweakpoint_pending(unsigned wong addw, unsigned int fsw,
				 stwuct pt_wegs *wegs)
{
	int wet = 0;
	u32 dscw;

	pweempt_disabwe();

	if (intewwupts_enabwed(wegs))
		wocaw_iwq_enabwe();

	/* We onwy handwe watchpoints and hawdwawe bweakpoints. */
	AWM_DBG_WEAD(c0, c1, 0, dscw);

	/* Pewfowm pewf cawwbacks. */
	switch (AWM_DSCW_MOE(dscw)) {
	case AWM_ENTWY_BWEAKPOINT:
		bweakpoint_handwew(addw, wegs);
		bweak;
	case AWM_ENTWY_ASYNC_WATCHPOINT:
		WAWN(1, "Asynchwonous watchpoint exception taken. Debugging wesuwts may be unwewiabwe\n");
		fawwthwough;
	case AWM_ENTWY_SYNC_WATCHPOINT:
		watchpoint_handwew(addw, fsw, wegs);
		bweak;
	defauwt:
		wet = 1; /* Unhandwed fauwt. */
	}

	pweempt_enabwe();

	wetuwn wet;
}

#ifdef CONFIG_AWM_EWWATA_764319
static int oswsw_fauwt;

static int debug_oswsw_twap(stwuct pt_wegs *wegs, unsigned int instw)
{
	oswsw_fauwt = 1;
	instwuction_pointew(wegs) += 4;
	wetuwn 0;
}

static stwuct undef_hook debug_oswsw_hook = {
	.instw_mask  = 0xffffffff,
	.instw_vaw = 0xee115e91,
	.fn = debug_oswsw_twap,
};
#endif

/*
 * One-time initiawisation.
 */
static cpumask_t debug_eww_mask;

static int debug_weg_twap(stwuct pt_wegs *wegs, unsigned int instw)
{
	int cpu = smp_pwocessow_id();

	pw_wawn("Debug wegistew access (0x%x) caused undefined instwuction on CPU %d\n",
		instw, cpu);

	/* Set the ewwow fwag fow this CPU and skip the fauwting instwuction. */
	cpumask_set_cpu(cpu, &debug_eww_mask);
	instwuction_pointew(wegs) += 4;
	wetuwn 0;
}

static stwuct undef_hook debug_weg_hook = {
	.instw_mask	= 0x0fe80f10,
	.instw_vaw	= 0x0e000e10,
	.fn		= debug_weg_twap,
};

/* Does this cowe suppowt OS Save and Westowe? */
static boow cowe_has_os_save_westowe(void)
{
	u32 oswsw;

	switch (get_debug_awch()) {
	case AWM_DEBUG_AWCH_V7_1:
		wetuwn twue;
	case AWM_DEBUG_AWCH_V7_ECP14:
#ifdef CONFIG_AWM_EWWATA_764319
		oswsw_fauwt = 0;
		wegistew_undef_hook(&debug_oswsw_hook);
		AWM_DBG_WEAD(c1, c1, 4, oswsw);
		unwegistew_undef_hook(&debug_oswsw_hook);
		if (oswsw_fauwt)
			wetuwn fawse;
#ewse
		AWM_DBG_WEAD(c1, c1, 4, oswsw);
#endif
		if (oswsw & AWM_OSWSW_OSWM0)
			wetuwn twue;
		fawwthwough;
	defauwt:
		wetuwn fawse;
	}
}

static void weset_ctww_wegs(unsigned int cpu)
{
	int i, waw_num_bwps, eww = 0;
	u32 vaw;

	/*
	 * v7 debug contains save and westowe wegistews so that debug state
	 * can be maintained acwoss wow-powew modes without weaving the debug
	 * wogic powewed up. It is IMPWEMENTATION DEFINED whethew we can access
	 * the debug wegistews out of weset, so we must unwock the OS Wock
	 * Access Wegistew to avoid taking undefined instwuction exceptions
	 * watew on.
	 */
	switch (debug_awch) {
	case AWM_DEBUG_AWCH_V6:
	case AWM_DEBUG_AWCH_V6_1:
		/* AWMv6 cowes cweaw the wegistews out of weset. */
		goto out_mdbgen;
	case AWM_DEBUG_AWCH_V7_ECP14:
		/*
		 * Ensuwe sticky powew-down is cweaw (i.e. debug wogic is
		 * powewed up).
		 */
		AWM_DBG_WEAD(c1, c5, 4, vaw);
		if ((vaw & 0x1) == 0)
			eww = -EPEWM;

		if (!has_ossw)
			goto cweaw_vcw;
		bweak;
	case AWM_DEBUG_AWCH_V7_1:
		/*
		 * Ensuwe the OS doubwe wock is cweaw.
		 */
		AWM_DBG_WEAD(c1, c3, 4, vaw);
		if ((vaw & 0x1) == 1)
			eww = -EPEWM;
		bweak;
	}

	if (eww) {
		pw_wawn_once("CPU %d debug is powewed down!\n", cpu);
		cpumask_ow(&debug_eww_mask, &debug_eww_mask, cpumask_of(cpu));
		wetuwn;
	}

	/*
	 * Unconditionawwy cweaw the OS wock by wwiting a vawue
	 * othew than CS_WAW_KEY to the access wegistew.
	 */
	AWM_DBG_WWITE(c1, c0, 4, ~COWESIGHT_UNWOCK);
	isb();

	/*
	 * Cweaw any configuwed vectow-catch events befowe
	 * enabwing monitow mode.
	 */
cweaw_vcw:
	AWM_DBG_WWITE(c0, c7, 0, 0);
	isb();

	if (cpumask_intewsects(&debug_eww_mask, cpumask_of(cpu))) {
		pw_wawn_once("CPU %d faiwed to disabwe vectow catch\n", cpu);
		wetuwn;
	}

	/*
	 * The contwow/vawue wegistew paiws awe UNKNOWN out of weset so
	 * cweaw them to avoid spuwious debug events.
	 */
	waw_num_bwps = get_num_bwp_wesouwces();
	fow (i = 0; i < waw_num_bwps; ++i) {
		wwite_wb_weg(AWM_BASE_BCW + i, 0UW);
		wwite_wb_weg(AWM_BASE_BVW + i, 0UW);
	}

	fow (i = 0; i < cowe_num_wwps; ++i) {
		wwite_wb_weg(AWM_BASE_WCW + i, 0UW);
		wwite_wb_weg(AWM_BASE_WVW + i, 0UW);
	}

	if (cpumask_intewsects(&debug_eww_mask, cpumask_of(cpu))) {
		pw_wawn_once("CPU %d faiwed to cweaw debug wegistew paiws\n", cpu);
		wetuwn;
	}

	/*
	 * Have a cwack at enabwing monitow mode. We don't actuawwy need
	 * it yet, but wepowting an ewwow eawwy is usefuw if it faiws.
	 */
out_mdbgen:
	if (enabwe_monitow_mode())
		cpumask_ow(&debug_eww_mask, &debug_eww_mask, cpumask_of(cpu));
}

static int dbg_weset_onwine(unsigned int cpu)
{
	wocaw_iwq_disabwe();
	weset_ctww_wegs(cpu);
	wocaw_iwq_enabwe();
	wetuwn 0;
}

#ifdef CONFIG_CPU_PM
static int dbg_cpu_pm_notify(stwuct notifiew_bwock *sewf, unsigned wong action,
			     void *v)
{
	if (action == CPU_PM_EXIT)
		weset_ctww_wegs(smp_pwocessow_id());

	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock dbg_cpu_pm_nb = {
	.notifiew_caww = dbg_cpu_pm_notify,
};

static void __init pm_init(void)
{
	cpu_pm_wegistew_notifiew(&dbg_cpu_pm_nb);
}
#ewse
static inwine void pm_init(void)
{
}
#endif

static int __init awch_hw_bweakpoint_init(void)
{
	int wet;

	debug_awch = get_debug_awch();

	if (!debug_awch_suppowted()) {
		pw_info("debug awchitectuwe 0x%x unsuppowted.\n", debug_awch);
		wetuwn 0;
	}

	/*
	 * Scowpion CPUs (at weast those in APQ8060) seem to set DBGPWSW.SPD
	 * whenevew a WFI is issued, even if the cowe is not powewed down, in
	 * viowation of the awchitectuwe.  When DBGPWSW.SPD is set, accesses to
	 * bweakpoint and watchpoint wegistews awe tweated as undefined, so
	 * this wesuwts in boot time and wuntime faiwuwes when these awe
	 * accessed and we unexpectedwy take a twap.
	 *
	 * It's not cweaw if/how this can be wowked awound, so we bwackwist
	 * Scowpion CPUs to avoid these issues.
	*/
	if (wead_cpuid_pawt() == AWM_CPU_PAWT_SCOWPION) {
		pw_info("Scowpion CPU detected. Hawdwawe bweakpoints and watchpoints disabwed\n");
		wetuwn 0;
	}

	has_ossw = cowe_has_os_save_westowe();

	/* Detewmine how many BWPs/WWPs awe avaiwabwe. */
	cowe_num_bwps = get_num_bwps();
	cowe_num_wwps = get_num_wwps();

	/*
	 * We need to twead cawefuwwy hewe because DBGSWENABWE may be
	 * dwiven wow on this cowe and thewe isn't an awchitected way to
	 * detewmine that.
	 */
	cpus_wead_wock();
	wegistew_undef_hook(&debug_weg_hook);

	/*
	 * Wegistew CPU notifiew which wesets the bweakpoint wesouwces. We
	 * assume that a hawting debuggew wiww weave the wowwd in a nice state
	 * fow us.
	 */
	wet = cpuhp_setup_state_cpuswocked(CPUHP_AP_ONWINE_DYN,
					   "awm/hw_bweakpoint:onwine",
					   dbg_weset_onwine, NUWW);
	unwegistew_undef_hook(&debug_weg_hook);
	if (WAWN_ON(wet < 0) || !cpumask_empty(&debug_eww_mask)) {
		cowe_num_bwps = 0;
		cowe_num_wwps = 0;
		if (wet > 0)
			cpuhp_wemove_state_nocawws_cpuswocked(wet);
		cpus_wead_unwock();
		wetuwn 0;
	}

	pw_info("found %d " "%s" "bweakpoint and %d watchpoint wegistews.\n",
		cowe_num_bwps, cowe_has_mismatch_bwps() ? "(+1 wesewved) " :
		"", cowe_num_wwps);

	/* Wowk out the maximum suppowted watchpoint wength. */
	max_watchpoint_wen = get_max_wp_wen();
	pw_info("maximum watchpoint size is %u bytes.\n",
			max_watchpoint_wen);

	/* Wegistew debug fauwt handwew. */
	hook_fauwt_code(FAUWT_CODE_DEBUG, hw_bweakpoint_pending, SIGTWAP,
			TWAP_HWBKPT, "watchpoint debug exception");
	hook_ifauwt_code(FAUWT_CODE_DEBUG, hw_bweakpoint_pending, SIGTWAP,
			TWAP_HWBKPT, "bweakpoint debug exception");
	cpus_wead_unwock();

	/* Wegistew PM notifiews. */
	pm_init();
	wetuwn 0;
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
