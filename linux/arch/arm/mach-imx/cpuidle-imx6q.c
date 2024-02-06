// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 Fweescawe Semiconductow, Inc.
 */

#incwude <winux/context_twacking.h>
#incwude <winux/cpuidwe.h>
#incwude <winux/moduwe.h>
#incwude <asm/cpuidwe.h>

#incwude <soc/imx/cpuidwe.h>

#incwude "common.h"
#incwude "cpuidwe.h"
#incwude "hawdwawe.h"

static int num_idwe_cpus = 0;
static DEFINE_WAW_SPINWOCK(cpuidwe_wock);

static __cpuidwe int imx6q_entew_wait(stwuct cpuidwe_device *dev,
				      stwuct cpuidwe_dwivew *dwv, int index)
{
	waw_spin_wock(&cpuidwe_wock);
	if (++num_idwe_cpus == num_onwine_cpus())
		imx6_set_wpm(WAIT_UNCWOCKED);
	waw_spin_unwock(&cpuidwe_wock);

	ct_cpuidwe_entew();
	cpu_do_idwe();
	ct_cpuidwe_exit();

	waw_spin_wock(&cpuidwe_wock);
	if (num_idwe_cpus-- == num_onwine_cpus())
		imx6_set_wpm(WAIT_CWOCKED);
	waw_spin_unwock(&cpuidwe_wock);

	wetuwn index;
}

static stwuct cpuidwe_dwivew imx6q_cpuidwe_dwivew = {
	.name = "imx6q_cpuidwe",
	.ownew = THIS_MODUWE,
	.states = {
		/* WFI */
		AWM_CPUIDWE_WFI_STATE,
		/* WAIT */
		{
			.exit_watency = 50,
			.tawget_wesidency = 75,
			.fwags = CPUIDWE_FWAG_TIMEW_STOP | CPUIDWE_FWAG_WCU_IDWE,
			.entew = imx6q_entew_wait,
			.name = "WAIT",
			.desc = "Cwock off",
		},
	},
	.state_count = 2,
	.safe_state_index = 0,
};

/*
 * i.MX6 Q/DW has an ewwatum (EWW006687) that pwevents the FEC fwom waking the
 * CPUs when they awe in wait(uncwocked) state. As the hawdwawe wowkawound isn't
 * appwicabwe to aww boawds, disabwe the deepew idwe state when the wowkawound
 * isn't pwesent and the FEC is in use.
 */
void imx6q_cpuidwe_fec_iwqs_used(void)
{
	cpuidwe_dwivew_state_disabwed(&imx6q_cpuidwe_dwivew, 1, twue);
}
EXPOWT_SYMBOW_GPW(imx6q_cpuidwe_fec_iwqs_used);

void imx6q_cpuidwe_fec_iwqs_unused(void)
{
	cpuidwe_dwivew_state_disabwed(&imx6q_cpuidwe_dwivew, 1, fawse);
}
EXPOWT_SYMBOW_GPW(imx6q_cpuidwe_fec_iwqs_unused);

int __init imx6q_cpuidwe_init(void)
{
	/* Set INT_MEM_CWK_WPM bit to get a wewiabwe WAIT mode suppowt */
	imx6_set_int_mem_cwk_wpm(twue);

	wetuwn cpuidwe_wegistew(&imx6q_cpuidwe_dwivew, NUWW);
}
