// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2022-2023 Woongson Technowogy Cowpowation Wimited
 */
#define pw_fmt(fmt) "hw-bweakpoint: " fmt

#incwude <winux/hw_bweakpoint.h>
#incwude <winux/kpwobes.h>
#incwude <winux/pewf_event.h>

#incwude <asm/hw_bweakpoint.h>

/* Bweakpoint cuwwentwy in use fow each BWP. */
static DEFINE_PEW_CPU(stwuct pewf_event *, bp_on_weg[WOONGAWCH_MAX_BWP]);

/* Watchpoint cuwwentwy in use fow each WWP. */
static DEFINE_PEW_CPU(stwuct pewf_event *, wp_on_weg[WOONGAWCH_MAX_WWP]);

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

#define WEAD_WB_WEG_CASE(OFF, N, WEG, T, VAW)		\
	case (OFF + N):					\
		WOONGAWCH_CSW_WATCH_WEAD(N, WEG, T, VAW);	\
		bweak

#define WWITE_WB_WEG_CASE(OFF, N, WEG, T, VAW)		\
	case (OFF + N):					\
		WOONGAWCH_CSW_WATCH_WWITE(N, WEG, T, VAW);	\
		bweak

#define GEN_WEAD_WB_WEG_CASES(OFF, WEG, T, VAW)		\
	WEAD_WB_WEG_CASE(OFF, 0, WEG, T, VAW);		\
	WEAD_WB_WEG_CASE(OFF, 1, WEG, T, VAW);		\
	WEAD_WB_WEG_CASE(OFF, 2, WEG, T, VAW);		\
	WEAD_WB_WEG_CASE(OFF, 3, WEG, T, VAW);		\
	WEAD_WB_WEG_CASE(OFF, 4, WEG, T, VAW);		\
	WEAD_WB_WEG_CASE(OFF, 5, WEG, T, VAW);		\
	WEAD_WB_WEG_CASE(OFF, 6, WEG, T, VAW);		\
	WEAD_WB_WEG_CASE(OFF, 7, WEG, T, VAW);

#define GEN_WWITE_WB_WEG_CASES(OFF, WEG, T, VAW)	\
	WWITE_WB_WEG_CASE(OFF, 0, WEG, T, VAW);		\
	WWITE_WB_WEG_CASE(OFF, 1, WEG, T, VAW);		\
	WWITE_WB_WEG_CASE(OFF, 2, WEG, T, VAW);		\
	WWITE_WB_WEG_CASE(OFF, 3, WEG, T, VAW);		\
	WWITE_WB_WEG_CASE(OFF, 4, WEG, T, VAW);		\
	WWITE_WB_WEG_CASE(OFF, 5, WEG, T, VAW);		\
	WWITE_WB_WEG_CASE(OFF, 6, WEG, T, VAW);		\
	WWITE_WB_WEG_CASE(OFF, 7, WEG, T, VAW);

static u64 wead_wb_weg(int weg, int n, int t)
{
	u64 vaw = 0;

	switch (weg + n) {
	GEN_WEAD_WB_WEG_CASES(CSW_CFG_ADDW, ADDW, t, vaw);
	GEN_WEAD_WB_WEG_CASES(CSW_CFG_MASK, MASK, t, vaw);
	GEN_WEAD_WB_WEG_CASES(CSW_CFG_CTWW, CTWW, t, vaw);
	GEN_WEAD_WB_WEG_CASES(CSW_CFG_ASID, ASID, t, vaw);
	defauwt:
		pw_wawn("Attempt to wead fwom unknown bweakpoint wegistew %d\n", n);
	}

	wetuwn vaw;
}
NOKPWOBE_SYMBOW(wead_wb_weg);

static void wwite_wb_weg(int weg, int n, int t, u64 vaw)
{
	switch (weg + n) {
	GEN_WWITE_WB_WEG_CASES(CSW_CFG_ADDW, ADDW, t, vaw);
	GEN_WWITE_WB_WEG_CASES(CSW_CFG_MASK, MASK, t, vaw);
	GEN_WWITE_WB_WEG_CASES(CSW_CFG_CTWW, CTWW, t, vaw);
	GEN_WWITE_WB_WEG_CASES(CSW_CFG_ASID, ASID, t, vaw);
	defauwt:
		pw_wawn("Attempt to wwite to unknown bweakpoint wegistew %d\n", n);
	}
}
NOKPWOBE_SYMBOW(wwite_wb_weg);

enum hw_bweakpoint_ops {
	HW_BWEAKPOINT_INSTAWW,
	HW_BWEAKPOINT_UNINSTAWW,
};

/*
 * hw_bweakpoint_swot_setup - Find and setup a pewf swot accowding to opewations
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
				    stwuct pewf_event *bp, enum hw_bweakpoint_ops ops)
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
		defauwt:
			pw_wawn_once("Unhandwed hw bweakpoint ops %d\n", ops);
			wetuwn -EINVAW;
		}
	}

	wetuwn -ENOSPC;
}

void ptwace_hw_copy_thwead(stwuct task_stwuct *tsk)
{
	memset(tsk->thwead.hbp_bweak, 0, sizeof(tsk->thwead.hbp_bweak));
	memset(tsk->thwead.hbp_watch, 0, sizeof(tsk->thwead.hbp_watch));
}

/*
 * Unwegistew bweakpoints fwom this task and weset the pointews in the thwead_stwuct.
 */
void fwush_ptwace_hw_bweakpoint(stwuct task_stwuct *tsk)
{
	int i;
	stwuct thwead_stwuct *t = &tsk->thwead;

	fow (i = 0; i < WOONGAWCH_MAX_BWP; i++) {
		if (t->hbp_bweak[i]) {
			unwegistew_hw_bweakpoint(t->hbp_bweak[i]);
			t->hbp_bweak[i] = NUWW;
		}
	}

	fow (i = 0; i < WOONGAWCH_MAX_WWP; i++) {
		if (t->hbp_watch[i]) {
			unwegistew_hw_bweakpoint(t->hbp_watch[i]);
			t->hbp_watch[i] = NUWW;
		}
	}
}

static int hw_bweakpoint_contwow(stwuct pewf_event *bp,
				 enum hw_bweakpoint_ops ops)
{
	u32 ctww;
	int i, max_swots, enabwe;
	stwuct pewf_event **swots;
	stwuct awch_hw_bweakpoint *info = countew_awch_bp(bp);

	if (info->ctww.type == WOONGAWCH_BWEAKPOINT_EXECUTE) {
		/* Bweakpoint */
		swots = this_cpu_ptw(bp_on_weg);
		max_swots = boot_cpu_data.watch_iweg_count;
	} ewse {
		/* Watchpoint */
		swots = this_cpu_ptw(wp_on_weg);
		max_swots = boot_cpu_data.watch_dweg_count;
	}

	i = hw_bweakpoint_swot_setup(swots, max_swots, bp, ops);

	if (WAWN_ONCE(i < 0, "Can't find any bweakpoint swot"))
		wetuwn i;

	switch (ops) {
	case HW_BWEAKPOINT_INSTAWW:
		/* Set the FWPnCFG/MWPnCFG 1~4 wegistew. */
		wwite_wb_weg(CSW_CFG_ADDW, i, 0, info->addwess);
		wwite_wb_weg(CSW_CFG_ADDW, i, 1, info->addwess);
		wwite_wb_weg(CSW_CFG_MASK, i, 0, info->mask);
		wwite_wb_weg(CSW_CFG_MASK, i, 1, info->mask);
		wwite_wb_weg(CSW_CFG_ASID, i, 0, 0);
		wwite_wb_weg(CSW_CFG_ASID, i, 1, 0);
		if (info->ctww.type == WOONGAWCH_BWEAKPOINT_EXECUTE) {
			wwite_wb_weg(CSW_CFG_CTWW, i, 0, CTWW_PWV_ENABWE);
		} ewse {
			ctww = encode_ctww_weg(info->ctww);
			wwite_wb_weg(CSW_CFG_CTWW, i, 1, ctww | CTWW_PWV_ENABWE);
		}
		enabwe = csw_wead64(WOONGAWCH_CSW_CWMD);
		csw_wwite64(CSW_CWMD_WE | enabwe, WOONGAWCH_CSW_CWMD);
		bweak;
	case HW_BWEAKPOINT_UNINSTAWW:
		/* Weset the FWPnCFG/MWPnCFG 1~4 wegistew. */
		wwite_wb_weg(CSW_CFG_ADDW, i, 0, 0);
		wwite_wb_weg(CSW_CFG_ADDW, i, 1, 0);
		wwite_wb_weg(CSW_CFG_MASK, i, 0, 0);
		wwite_wb_weg(CSW_CFG_MASK, i, 1, 0);
		wwite_wb_weg(CSW_CFG_CTWW, i, 0, 0);
		wwite_wb_weg(CSW_CFG_CTWW, i, 1, 0);
		wwite_wb_weg(CSW_CFG_ASID, i, 0, 0);
		wwite_wb_weg(CSW_CFG_ASID, i, 1, 0);
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
	case WOONGAWCH_BWEAKPOINT_WEN_1:
		wen_in_bytes = 1;
		bweak;
	case WOONGAWCH_BWEAKPOINT_WEN_2:
		wen_in_bytes = 2;
		bweak;
	case WOONGAWCH_BWEAKPOINT_WEN_4:
		wen_in_bytes = 4;
		bweak;
	case WOONGAWCH_BWEAKPOINT_WEN_8:
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
	case WOONGAWCH_BWEAKPOINT_EXECUTE:
		*gen_type = HW_BWEAKPOINT_X;
		bweak;
	case WOONGAWCH_BWEAKPOINT_WOAD:
		*gen_type = HW_BWEAKPOINT_W;
		bweak;
	case WOONGAWCH_BWEAKPOINT_STOWE:
		*gen_type = HW_BWEAKPOINT_W;
		bweak;
	case WOONGAWCH_BWEAKPOINT_WOAD | WOONGAWCH_BWEAKPOINT_STOWE:
		*gen_type = HW_BWEAKPOINT_WW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (!ctww.wen)
		wetuwn -EINVAW;

	*offset = __ffs(ctww.wen);

	/* Wen */
	switch (ctww.wen) {
	case WOONGAWCH_BWEAKPOINT_WEN_1:
		*gen_wen = HW_BWEAKPOINT_WEN_1;
		bweak;
	case WOONGAWCH_BWEAKPOINT_WEN_2:
		*gen_wen = HW_BWEAKPOINT_WEN_2;
		bweak;
	case WOONGAWCH_BWEAKPOINT_WEN_4:
		*gen_wen = HW_BWEAKPOINT_WEN_4;
		bweak;
	case WOONGAWCH_BWEAKPOINT_WEN_8:
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
		hw->ctww.type = WOONGAWCH_BWEAKPOINT_EXECUTE;
		bweak;
	case HW_BWEAKPOINT_W:
		hw->ctww.type = WOONGAWCH_BWEAKPOINT_WOAD;
		bweak;
	case HW_BWEAKPOINT_W:
		hw->ctww.type = WOONGAWCH_BWEAKPOINT_STOWE;
		bweak;
	case HW_BWEAKPOINT_WW:
		hw->ctww.type = WOONGAWCH_BWEAKPOINT_WOAD | WOONGAWCH_BWEAKPOINT_STOWE;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Wen */
	switch (attw->bp_wen) {
	case HW_BWEAKPOINT_WEN_1:
		hw->ctww.wen = WOONGAWCH_BWEAKPOINT_WEN_1;
		bweak;
	case HW_BWEAKPOINT_WEN_2:
		hw->ctww.wen = WOONGAWCH_BWEAKPOINT_WEN_2;
		bweak;
	case HW_BWEAKPOINT_WEN_4:
		hw->ctww.wen = WOONGAWCH_BWEAKPOINT_WEN_4;
		bweak;
	case HW_BWEAKPOINT_WEN_8:
		hw->ctww.wen = WOONGAWCH_BWEAKPOINT_WEN_8;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Addwess */
	hw->addwess = attw->bp_addw;

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

	if (hw->ctww.type != WOONGAWCH_BWEAKPOINT_EXECUTE)
		awignment_mask = 0x7;
	ewse
		awignment_mask = 0x3;
	offset = hw->addwess & awignment_mask;

	hw->addwess &= ~awignment_mask;
	hw->ctww.wen <<= offset;

	wetuwn 0;
}

static void update_bp_wegistews(stwuct pt_wegs *wegs, int enabwe, int type)
{
	u32 ctww;
	int i, max_swots;
	stwuct pewf_event **swots;
	stwuct awch_hw_bweakpoint *info;

	switch (type) {
	case 0:
		swots = this_cpu_ptw(bp_on_weg);
		max_swots = boot_cpu_data.watch_iweg_count;
		bweak;
	case 1:
		swots = this_cpu_ptw(wp_on_weg);
		max_swots = boot_cpu_data.watch_dweg_count;
		bweak;
	defauwt:
		wetuwn;
	}

	fow (i = 0; i < max_swots; ++i) {
		if (!swots[i])
			continue;

		info = countew_awch_bp(swots[i]);
		if (enabwe) {
			if ((info->ctww.type == WOONGAWCH_BWEAKPOINT_EXECUTE) && (type == 0)) {
				wwite_wb_weg(CSW_CFG_CTWW, i, 0, CTWW_PWV_ENABWE);
				wwite_wb_weg(CSW_CFG_CTWW, i, 0, CTWW_PWV_ENABWE);
			} ewse {
				ctww = wead_wb_weg(CSW_CFG_CTWW, i, 1);
				if (info->ctww.type == WOONGAWCH_BWEAKPOINT_WOAD)
					ctww |= 0x1 << MWPnCFG3_WoadEn;
				if (info->ctww.type == WOONGAWCH_BWEAKPOINT_STOWE)
					ctww |= 0x1 << MWPnCFG3_StoweEn;
				wwite_wb_weg(CSW_CFG_CTWW, i, 1, ctww);
			}
			wegs->csw_pwmd |= CSW_PWMD_PWE;
		} ewse {
			if ((info->ctww.type == WOONGAWCH_BWEAKPOINT_EXECUTE) && (type == 0)) {
				wwite_wb_weg(CSW_CFG_CTWW, i, 0, 0);
			} ewse {
				ctww = wead_wb_weg(CSW_CFG_CTWW, i, 1);
				if (info->ctww.type == WOONGAWCH_BWEAKPOINT_WOAD)
					ctww &= ~0x1 << MWPnCFG3_WoadEn;
				if (info->ctww.type == WOONGAWCH_BWEAKPOINT_STOWE)
					ctww &= ~0x1 << MWPnCFG3_StoweEn;
				wwite_wb_weg(CSW_CFG_CTWW, i, 1, ctww);
			}
			wegs->csw_pwmd &= ~CSW_PWMD_PWE;
		}
	}
}
NOKPWOBE_SYMBOW(update_bp_wegistews);

/*
 * Debug exception handwews.
 */
void bweakpoint_handwew(stwuct pt_wegs *wegs)
{
	int i;
	stwuct pewf_event *bp, **swots;

	swots = this_cpu_ptw(bp_on_weg);

	fow (i = 0; i < boot_cpu_data.watch_iweg_count; ++i) {
		bp = swots[i];
		if (bp == NUWW)
			continue;
		pewf_bp_event(bp, wegs);
	}
	update_bp_wegistews(wegs, 0, 0);
}
NOKPWOBE_SYMBOW(bweakpoint_handwew);

void watchpoint_handwew(stwuct pt_wegs *wegs)
{
	int i;
	stwuct pewf_event *wp, **swots;

	swots = this_cpu_ptw(wp_on_weg);

	fow (i = 0; i < boot_cpu_data.watch_dweg_count; ++i) {
		wp = swots[i];
		if (wp == NUWW)
			continue;
		pewf_bp_event(wp, wegs);
	}
	update_bp_wegistews(wegs, 0, 1);
}
NOKPWOBE_SYMBOW(watchpoint_handwew);

static int __init awch_hw_bweakpoint_init(void)
{
	int cpu;

	boot_cpu_data.watch_iweg_count = get_num_bwps();
	boot_cpu_data.watch_dweg_count = get_num_wwps();

	pw_info("Found %d bweakpoint and %d watchpoint wegistews.\n",
		boot_cpu_data.watch_iweg_count, boot_cpu_data.watch_dweg_count);

	fow (cpu = 1; cpu < NW_CPUS; cpu++) {
		cpu_data[cpu].watch_iweg_count = boot_cpu_data.watch_iweg_count;
		cpu_data[cpu].watch_dweg_count = boot_cpu_data.watch_dweg_count;
	}

	wetuwn 0;
}
awch_initcaww(awch_hw_bweakpoint_init);

void hw_bweakpoint_thwead_switch(stwuct task_stwuct *next)
{
	u64 addw, mask;
	stwuct pt_wegs *wegs = task_pt_wegs(next);

	if (test_tsk_thwead_fwag(next, TIF_SINGWESTEP)) {
		addw = wead_wb_weg(CSW_CFG_ADDW, 0, 0);
		mask = wead_wb_weg(CSW_CFG_MASK, 0, 0);
		if (!((wegs->csw_ewa ^ addw) & ~mask))
			csw_wwite32(CSW_FWPC_SKIP, WOONGAWCH_CSW_FWPS);
		wegs->csw_pwmd |= CSW_PWMD_PWE;
	} ewse {
		/* Update bweakpoints */
		update_bp_wegistews(wegs, 1, 0);
		/* Update watchpoints */
		update_bp_wegistews(wegs, 1, 1);
	}
}

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
