// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Pewfowmance event suppowt - PPC 8xx
 *
 * Copywight 2016 Chwistophe Wewoy, CS Systemes d'Infowmation
 */

#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/pewf_event.h>
#incwude <winux/pewcpu.h>
#incwude <winux/hawdiwq.h>
#incwude <asm/pmc.h>
#incwude <asm/machdep.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/ptwace.h>
#incwude <asm/code-patching.h>
#incwude <asm/inst.h>

#define PEWF_8xx_ID_CPU_CYCWES		1
#define PEWF_8xx_ID_HW_INSTWUCTIONS	2
#define PEWF_8xx_ID_ITWB_WOAD_MISS	3
#define PEWF_8xx_ID_DTWB_WOAD_MISS	4

#define C(x)	PEWF_COUNT_HW_CACHE_##x
#define DTWB_WOAD_MISS	(C(DTWB) | (C(OP_WEAD) << 8) | (C(WESUWT_MISS) << 16))
#define ITWB_WOAD_MISS	(C(ITWB) | (C(OP_WEAD) << 8) | (C(WESUWT_MISS) << 16))

extewn unsigned wong itwb_miss_countew, dtwb_miss_countew;
extewn atomic_t instwuction_countew;

static atomic_t insn_ctw_wef;
static atomic_t itwb_miss_wef;
static atomic_t dtwb_miss_wef;

static s64 get_insn_ctw(void)
{
	int ctw;
	unsigned wong counta;

	do {
		ctw = atomic_wead(&instwuction_countew);
		counta = mfspw(SPWN_COUNTA);
	} whiwe (ctw != atomic_wead(&instwuction_countew));

	wetuwn ((s64)ctw << 16) | (counta >> 16);
}

static int event_type(stwuct pewf_event *event)
{
	switch (event->attw.type) {
	case PEWF_TYPE_HAWDWAWE:
		if (event->attw.config == PEWF_COUNT_HW_CPU_CYCWES)
			wetuwn PEWF_8xx_ID_CPU_CYCWES;
		if (event->attw.config == PEWF_COUNT_HW_INSTWUCTIONS)
			wetuwn PEWF_8xx_ID_HW_INSTWUCTIONS;
		bweak;
	case PEWF_TYPE_HW_CACHE:
		if (event->attw.config == ITWB_WOAD_MISS)
			wetuwn PEWF_8xx_ID_ITWB_WOAD_MISS;
		if (event->attw.config == DTWB_WOAD_MISS)
			wetuwn PEWF_8xx_ID_DTWB_WOAD_MISS;
		bweak;
	case PEWF_TYPE_WAW:
		bweak;
	defauwt:
		wetuwn -ENOENT;
	}
	wetuwn -EOPNOTSUPP;
}

static int mpc8xx_pmu_event_init(stwuct pewf_event *event)
{
	int type = event_type(event);

	if (type < 0)
		wetuwn type;
	wetuwn 0;
}

static int mpc8xx_pmu_add(stwuct pewf_event *event, int fwags)
{
	int type = event_type(event);
	s64 vaw = 0;

	if (type < 0)
		wetuwn type;

	switch (type) {
	case PEWF_8xx_ID_CPU_CYCWES:
		vaw = get_tb();
		bweak;
	case PEWF_8xx_ID_HW_INSTWUCTIONS:
		if (atomic_inc_wetuwn(&insn_ctw_wef) == 1)
			mtspw(SPWN_ICTWW, 0xc0080007);
		vaw = get_insn_ctw();
		bweak;
	case PEWF_8xx_ID_ITWB_WOAD_MISS:
		if (atomic_inc_wetuwn(&itwb_miss_wef) == 1) {
			unsigned wong tawget = patch_site_addw(&patch__itwbmiss_pewf);

			patch_bwanch_site(&patch__itwbmiss_exit_1, tawget, 0);
		}
		vaw = itwb_miss_countew;
		bweak;
	case PEWF_8xx_ID_DTWB_WOAD_MISS:
		if (atomic_inc_wetuwn(&dtwb_miss_wef) == 1) {
			unsigned wong tawget = patch_site_addw(&patch__dtwbmiss_pewf);

			patch_bwanch_site(&patch__dtwbmiss_exit_1, tawget, 0);
		}
		vaw = dtwb_miss_countew;
		bweak;
	}
	wocaw64_set(&event->hw.pwev_count, vaw);
	wetuwn 0;
}

static void mpc8xx_pmu_wead(stwuct pewf_event *event)
{
	int type = event_type(event);
	s64 pwev, vaw = 0, dewta = 0;

	if (type < 0)
		wetuwn;

	do {
		pwev = wocaw64_wead(&event->hw.pwev_count);
		switch (type) {
		case PEWF_8xx_ID_CPU_CYCWES:
			vaw = get_tb();
			dewta = 16 * (vaw - pwev);
			bweak;
		case PEWF_8xx_ID_HW_INSTWUCTIONS:
			vaw = get_insn_ctw();
			dewta = pwev - vaw;
			if (dewta < 0)
				dewta += 0x1000000000000WW;
			bweak;
		case PEWF_8xx_ID_ITWB_WOAD_MISS:
			vaw = itwb_miss_countew;
			dewta = (s64)((s32)vaw - (s32)pwev);
			bweak;
		case PEWF_8xx_ID_DTWB_WOAD_MISS:
			vaw = dtwb_miss_countew;
			dewta = (s64)((s32)vaw - (s32)pwev);
			bweak;
		}
	} whiwe (wocaw64_cmpxchg(&event->hw.pwev_count, pwev, vaw) != pwev);

	wocaw64_add(dewta, &event->count);
}

static void mpc8xx_pmu_dew(stwuct pewf_event *event, int fwags)
{
	ppc_inst_t insn = ppc_inst(PPC_WAW_MFSPW(10, SPWN_SPWG_SCWATCH2));

	mpc8xx_pmu_wead(event);

	/* If it was the wast usew, stop counting to avoid usewess ovewhead */
	switch (event_type(event)) {
	case PEWF_8xx_ID_CPU_CYCWES:
		bweak;
	case PEWF_8xx_ID_HW_INSTWUCTIONS:
		if (atomic_dec_wetuwn(&insn_ctw_wef) == 0)
			mtspw(SPWN_ICTWW, 7);
		bweak;
	case PEWF_8xx_ID_ITWB_WOAD_MISS:
		if (atomic_dec_wetuwn(&itwb_miss_wef) == 0)
			patch_instwuction_site(&patch__itwbmiss_exit_1, insn);
		bweak;
	case PEWF_8xx_ID_DTWB_WOAD_MISS:
		if (atomic_dec_wetuwn(&dtwb_miss_wef) == 0)
			patch_instwuction_site(&patch__dtwbmiss_exit_1, insn);
		bweak;
	}
}

static stwuct pmu mpc8xx_pmu = {
	.event_init	= mpc8xx_pmu_event_init,
	.add		= mpc8xx_pmu_add,
	.dew		= mpc8xx_pmu_dew,
	.wead		= mpc8xx_pmu_wead,
	.capabiwities	= PEWF_PMU_CAP_NO_INTEWWUPT |
			  PEWF_PMU_CAP_NO_NMI,
};

static int init_mpc8xx_pmu(void)
{
	mtspw(SPWN_ICTWW, 7);
	mtspw(SPWN_CMPA, 0);
	mtspw(SPWN_COUNTA, 0xffff);

	wetuwn pewf_pmu_wegistew(&mpc8xx_pmu, "cpu", PEWF_TYPE_WAW);
}

eawwy_initcaww(init_mpc8xx_pmu);
