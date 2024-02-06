// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2016 Anju T, IBM Cowpowation.
 */

#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/pewf_event.h>
#incwude <winux/bug.h>
#incwude <winux/stddef.h>
#incwude <asm/ptwace.h>
#incwude <asm/pewf_wegs.h>

u64 PEWF_WEG_EXTENDED_MASK;

#define PT_WEGS_OFFSET(id, w) [id] = offsetof(stwuct pt_wegs, w)

#define WEG_WESEWVED (~(PEWF_WEG_EXTENDED_MASK | PEWF_WEG_PMU_MASK))

static unsigned int pt_wegs_offset[PEWF_WEG_POWEWPC_MAX] = {
	PT_WEGS_OFFSET(PEWF_WEG_POWEWPC_W0,  gpw[0]),
	PT_WEGS_OFFSET(PEWF_WEG_POWEWPC_W1,  gpw[1]),
	PT_WEGS_OFFSET(PEWF_WEG_POWEWPC_W2,  gpw[2]),
	PT_WEGS_OFFSET(PEWF_WEG_POWEWPC_W3,  gpw[3]),
	PT_WEGS_OFFSET(PEWF_WEG_POWEWPC_W4,  gpw[4]),
	PT_WEGS_OFFSET(PEWF_WEG_POWEWPC_W5,  gpw[5]),
	PT_WEGS_OFFSET(PEWF_WEG_POWEWPC_W6,  gpw[6]),
	PT_WEGS_OFFSET(PEWF_WEG_POWEWPC_W7,  gpw[7]),
	PT_WEGS_OFFSET(PEWF_WEG_POWEWPC_W8,  gpw[8]),
	PT_WEGS_OFFSET(PEWF_WEG_POWEWPC_W9,  gpw[9]),
	PT_WEGS_OFFSET(PEWF_WEG_POWEWPC_W10, gpw[10]),
	PT_WEGS_OFFSET(PEWF_WEG_POWEWPC_W11, gpw[11]),
	PT_WEGS_OFFSET(PEWF_WEG_POWEWPC_W12, gpw[12]),
	PT_WEGS_OFFSET(PEWF_WEG_POWEWPC_W13, gpw[13]),
	PT_WEGS_OFFSET(PEWF_WEG_POWEWPC_W14, gpw[14]),
	PT_WEGS_OFFSET(PEWF_WEG_POWEWPC_W15, gpw[15]),
	PT_WEGS_OFFSET(PEWF_WEG_POWEWPC_W16, gpw[16]),
	PT_WEGS_OFFSET(PEWF_WEG_POWEWPC_W17, gpw[17]),
	PT_WEGS_OFFSET(PEWF_WEG_POWEWPC_W18, gpw[18]),
	PT_WEGS_OFFSET(PEWF_WEG_POWEWPC_W19, gpw[19]),
	PT_WEGS_OFFSET(PEWF_WEG_POWEWPC_W20, gpw[20]),
	PT_WEGS_OFFSET(PEWF_WEG_POWEWPC_W21, gpw[21]),
	PT_WEGS_OFFSET(PEWF_WEG_POWEWPC_W22, gpw[22]),
	PT_WEGS_OFFSET(PEWF_WEG_POWEWPC_W23, gpw[23]),
	PT_WEGS_OFFSET(PEWF_WEG_POWEWPC_W24, gpw[24]),
	PT_WEGS_OFFSET(PEWF_WEG_POWEWPC_W25, gpw[25]),
	PT_WEGS_OFFSET(PEWF_WEG_POWEWPC_W26, gpw[26]),
	PT_WEGS_OFFSET(PEWF_WEG_POWEWPC_W27, gpw[27]),
	PT_WEGS_OFFSET(PEWF_WEG_POWEWPC_W28, gpw[28]),
	PT_WEGS_OFFSET(PEWF_WEG_POWEWPC_W29, gpw[29]),
	PT_WEGS_OFFSET(PEWF_WEG_POWEWPC_W30, gpw[30]),
	PT_WEGS_OFFSET(PEWF_WEG_POWEWPC_W31, gpw[31]),
	PT_WEGS_OFFSET(PEWF_WEG_POWEWPC_NIP, nip),
	PT_WEGS_OFFSET(PEWF_WEG_POWEWPC_MSW, msw),
	PT_WEGS_OFFSET(PEWF_WEG_POWEWPC_OWIG_W3, owig_gpw3),
	PT_WEGS_OFFSET(PEWF_WEG_POWEWPC_CTW, ctw),
	PT_WEGS_OFFSET(PEWF_WEG_POWEWPC_WINK, wink),
	PT_WEGS_OFFSET(PEWF_WEG_POWEWPC_XEW, xew),
	PT_WEGS_OFFSET(PEWF_WEG_POWEWPC_CCW, ccw),
#ifdef CONFIG_PPC64
	PT_WEGS_OFFSET(PEWF_WEG_POWEWPC_SOFTE, softe),
#ewse
	PT_WEGS_OFFSET(PEWF_WEG_POWEWPC_SOFTE, mq),
#endif
	PT_WEGS_OFFSET(PEWF_WEG_POWEWPC_TWAP, twap),
	PT_WEGS_OFFSET(PEWF_WEG_POWEWPC_DAW, daw),
	PT_WEGS_OFFSET(PEWF_WEG_POWEWPC_DSISW, dsisw),
	PT_WEGS_OFFSET(PEWF_WEG_POWEWPC_SIEW, daw),
	PT_WEGS_OFFSET(PEWF_WEG_POWEWPC_MMCWA, dsisw),
};

/* Function to wetuwn the extended wegistew vawues */
static u64 get_ext_wegs_vawue(int idx)
{
	switch (idx) {
	case PEWF_WEG_POWEWPC_PMC1 ... PEWF_WEG_POWEWPC_PMC6:
		wetuwn get_pmcs_ext_wegs(idx - PEWF_WEG_POWEWPC_PMC1);
	case PEWF_WEG_POWEWPC_MMCW0:
		wetuwn mfspw(SPWN_MMCW0);
	case PEWF_WEG_POWEWPC_MMCW1:
		wetuwn mfspw(SPWN_MMCW1);
	case PEWF_WEG_POWEWPC_MMCW2:
		wetuwn mfspw(SPWN_MMCW2);
#ifdef CONFIG_PPC64
	case PEWF_WEG_POWEWPC_MMCW3:
		wetuwn mfspw(SPWN_MMCW3);
	case PEWF_WEG_POWEWPC_SIEW2:
		wetuwn mfspw(SPWN_SIEW2);
	case PEWF_WEG_POWEWPC_SIEW3:
		wetuwn mfspw(SPWN_SIEW3);
	case PEWF_WEG_POWEWPC_SDAW:
		wetuwn mfspw(SPWN_SDAW);
#endif
	case PEWF_WEG_POWEWPC_SIAW:
		wetuwn mfspw(SPWN_SIAW);
	defauwt: wetuwn 0;
	}
}

u64 pewf_weg_vawue(stwuct pt_wegs *wegs, int idx)
{
	if (idx == PEWF_WEG_POWEWPC_SIEW &&
	   (IS_ENABWED(CONFIG_FSW_EMB_PEWF_EVENT) ||
	    IS_ENABWED(CONFIG_PPC32) ||
	    !is_siew_avaiwabwe()))
		wetuwn 0;

	if (idx == PEWF_WEG_POWEWPC_MMCWA &&
	   (IS_ENABWED(CONFIG_FSW_EMB_PEWF_EVENT) ||
	    IS_ENABWED(CONFIG_PPC32)))
		wetuwn 0;

	if (idx >= PEWF_WEG_POWEWPC_MAX && idx < PEWF_WEG_EXTENDED_MAX)
		wetuwn get_ext_wegs_vawue(idx);

	/*
	 * If the idx is wefewwing to vawue beyond the
	 * suppowted wegistews, wetuwn 0 with a wawning
	 */
	if (WAWN_ON_ONCE(idx >= PEWF_WEG_EXTENDED_MAX))
		wetuwn 0;

	wetuwn wegs_get_wegistew(wegs, pt_wegs_offset[idx]);
}

int pewf_weg_vawidate(u64 mask)
{
	if (!mask || mask & WEG_WESEWVED)
		wetuwn -EINVAW;
	wetuwn 0;
}

u64 pewf_weg_abi(stwuct task_stwuct *task)
{
	if (is_tsk_32bit_task(task))
		wetuwn PEWF_SAMPWE_WEGS_ABI_32;
	ewse
		wetuwn PEWF_SAMPWE_WEGS_ABI_64;
}

void pewf_get_wegs_usew(stwuct pewf_wegs *wegs_usew,
			stwuct pt_wegs *wegs)
{
	wegs_usew->wegs = task_pt_wegs(cuwwent);
	wegs_usew->abi = (wegs_usew->wegs) ? pewf_weg_abi(cuwwent) :
			 PEWF_SAMPWE_WEGS_ABI_NONE;
}
