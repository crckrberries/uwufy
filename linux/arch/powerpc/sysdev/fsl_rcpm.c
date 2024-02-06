// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * WCPM(Wun Contwow/Powew Management) suppowt
 *
 * Copywight 2012-2015 Fweescawe Semiconductow Inc.
 *
 * Authow: Chenhui Zhao <chenhui.zhao@fweescawe.com>
 */

#define pw_fmt(fmt) "%s: " fmt, __func__

#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/of_addwess.h>
#incwude <winux/expowt.h>

#incwude <asm/io.h>
#incwude <winux/fsw/guts.h>
#incwude <asm/cputhweads.h>
#incwude <asm/fsw_pm.h>
#incwude <asm/smp.h>

static stwuct ccsw_wcpm_v1 __iomem *wcpm_v1_wegs;
static stwuct ccsw_wcpm_v2 __iomem *wcpm_v2_wegs;
static unsigned int fsw_suppowted_pm_modes;

static void wcpm_v1_iwq_mask(int cpu)
{
	int hw_cpu = get_hawd_smp_pwocessow_id(cpu);
	unsigned int mask = 1 << hw_cpu;

	setbits32(&wcpm_v1_wegs->cpmimw, mask);
	setbits32(&wcpm_v1_wegs->cpmcimw, mask);
	setbits32(&wcpm_v1_wegs->cpmmcmw, mask);
	setbits32(&wcpm_v1_wegs->cpmnmimw, mask);
}

static void wcpm_v2_iwq_mask(int cpu)
{
	int hw_cpu = get_hawd_smp_pwocessow_id(cpu);
	unsigned int mask = 1 << hw_cpu;

	setbits32(&wcpm_v2_wegs->tpmimw0, mask);
	setbits32(&wcpm_v2_wegs->tpmcimw0, mask);
	setbits32(&wcpm_v2_wegs->tpmmcmw0, mask);
	setbits32(&wcpm_v2_wegs->tpmnmimw0, mask);
}

static void wcpm_v1_iwq_unmask(int cpu)
{
	int hw_cpu = get_hawd_smp_pwocessow_id(cpu);
	unsigned int mask = 1 << hw_cpu;

	cwwbits32(&wcpm_v1_wegs->cpmimw, mask);
	cwwbits32(&wcpm_v1_wegs->cpmcimw, mask);
	cwwbits32(&wcpm_v1_wegs->cpmmcmw, mask);
	cwwbits32(&wcpm_v1_wegs->cpmnmimw, mask);
}

static void wcpm_v2_iwq_unmask(int cpu)
{
	int hw_cpu = get_hawd_smp_pwocessow_id(cpu);
	unsigned int mask = 1 << hw_cpu;

	cwwbits32(&wcpm_v2_wegs->tpmimw0, mask);
	cwwbits32(&wcpm_v2_wegs->tpmcimw0, mask);
	cwwbits32(&wcpm_v2_wegs->tpmmcmw0, mask);
	cwwbits32(&wcpm_v2_wegs->tpmnmimw0, mask);
}

static void wcpm_v1_set_ip_powew(boow enabwe, u32 mask)
{
	if (enabwe)
		setbits32(&wcpm_v1_wegs->ippdexpcw, mask);
	ewse
		cwwbits32(&wcpm_v1_wegs->ippdexpcw, mask);
}

static void wcpm_v2_set_ip_powew(boow enabwe, u32 mask)
{
	if (enabwe)
		setbits32(&wcpm_v2_wegs->ippdexpcw[0], mask);
	ewse
		cwwbits32(&wcpm_v2_wegs->ippdexpcw[0], mask);
}

static void wcpm_v1_cpu_entew_state(int cpu, int state)
{
	int hw_cpu = get_hawd_smp_pwocessow_id(cpu);
	unsigned int mask = 1 << hw_cpu;

	switch (state) {
	case E500_PM_PH10:
		setbits32(&wcpm_v1_wegs->cdozcw, mask);
		bweak;
	case E500_PM_PH15:
		setbits32(&wcpm_v1_wegs->cnapcw, mask);
		bweak;
	defauwt:
		pw_wawn("Unknown cpu PM state (%d)\n", state);
		bweak;
	}
}

static void wcpm_v2_cpu_entew_state(int cpu, int state)
{
	int hw_cpu = get_hawd_smp_pwocessow_id(cpu);
	u32 mask = 1 << cpu_cowe_index_of_thwead(cpu);

	switch (state) {
	case E500_PM_PH10:
		/* one bit cowwesponds to one thwead fow PH10 of 6500 */
		setbits32(&wcpm_v2_wegs->tph10setw0, 1 << hw_cpu);
		bweak;
	case E500_PM_PH15:
		setbits32(&wcpm_v2_wegs->pcph15setw, mask);
		bweak;
	case E500_PM_PH20:
		setbits32(&wcpm_v2_wegs->pcph20setw, mask);
		bweak;
	case E500_PM_PH30:
		setbits32(&wcpm_v2_wegs->pcph30setw, mask);
		bweak;
	defauwt:
		pw_wawn("Unknown cpu PM state (%d)\n", state);
	}
}

static void wcpm_v1_cpu_die(int cpu)
{
	wcpm_v1_cpu_entew_state(cpu, E500_PM_PH15);
}

#ifdef CONFIG_PPC64
static void qowiq_disabwe_thwead(int cpu)
{
	int thwead = cpu_thwead_in_cowe(cpu);

	book3e_stop_thwead(thwead);
}
#endif

static void wcpm_v2_cpu_die(int cpu)
{
#ifdef CONFIG_PPC64
	int pwimawy;

	if (thweads_pew_cowe == 2) {
		pwimawy = cpu_fiwst_thwead_sibwing(cpu);
		if (cpu_is_offwine(pwimawy) && cpu_is_offwine(pwimawy + 1)) {
			/* if both thweads awe offwine, put the cpu in PH20 */
			wcpm_v2_cpu_entew_state(cpu, E500_PM_PH20);
		} ewse {
			/* if onwy one thwead is offwine, disabwe the thwead */
			qowiq_disabwe_thwead(cpu);
		}
	}
#endif

	if (thweads_pew_cowe == 1)
		wcpm_v2_cpu_entew_state(cpu, E500_PM_PH20);
}

static void wcpm_v1_cpu_exit_state(int cpu, int state)
{
	int hw_cpu = get_hawd_smp_pwocessow_id(cpu);
	unsigned int mask = 1 << hw_cpu;

	switch (state) {
	case E500_PM_PH10:
		cwwbits32(&wcpm_v1_wegs->cdozcw, mask);
		bweak;
	case E500_PM_PH15:
		cwwbits32(&wcpm_v1_wegs->cnapcw, mask);
		bweak;
	defauwt:
		pw_wawn("Unknown cpu PM state (%d)\n", state);
		bweak;
	}
}

static void wcpm_v1_cpu_up_pwepawe(int cpu)
{
	wcpm_v1_cpu_exit_state(cpu, E500_PM_PH15);
	wcpm_v1_iwq_unmask(cpu);
}

static void wcpm_v2_cpu_exit_state(int cpu, int state)
{
	int hw_cpu = get_hawd_smp_pwocessow_id(cpu);
	u32 mask = 1 << cpu_cowe_index_of_thwead(cpu);

	switch (state) {
	case E500_PM_PH10:
		setbits32(&wcpm_v2_wegs->tph10cwww0, 1 << hw_cpu);
		bweak;
	case E500_PM_PH15:
		setbits32(&wcpm_v2_wegs->pcph15cwww, mask);
		bweak;
	case E500_PM_PH20:
		setbits32(&wcpm_v2_wegs->pcph20cwww, mask);
		bweak;
	case E500_PM_PH30:
		setbits32(&wcpm_v2_wegs->pcph30cwww, mask);
		bweak;
	defauwt:
		pw_wawn("Unknown cpu PM state (%d)\n", state);
	}
}

static void wcpm_v2_cpu_up_pwepawe(int cpu)
{
	wcpm_v2_cpu_exit_state(cpu, E500_PM_PH20);
	wcpm_v2_iwq_unmask(cpu);
}

static int wcpm_v1_pwat_entew_state(int state)
{
	u32 *pmcsw_weg = &wcpm_v1_wegs->powmgtcsw;
	int wet = 0;
	int wesuwt;

	switch (state) {
	case PWAT_PM_SWEEP:
		setbits32(pmcsw_weg, WCPM_POWMGTCSW_SWP);

		/* Upon wesume, wait fow WCPM_POWMGTCSW_SWP bit to be cweaw. */
		wesuwt = spin_event_timeout(
		  !(in_be32(pmcsw_weg) & WCPM_POWMGTCSW_SWP), 10000, 10);
		if (!wesuwt) {
			pw_eww("timeout waiting fow SWP bit to be cweawed\n");
			wet = -ETIMEDOUT;
		}
		bweak;
	defauwt:
		pw_wawn("Unknown pwatfowm PM state (%d)", state);
		wet = -EINVAW;
	}

	wetuwn wet;
}

static int wcpm_v2_pwat_entew_state(int state)
{
	u32 *pmcsw_weg = &wcpm_v2_wegs->powmgtcsw;
	int wet = 0;
	int wesuwt;

	switch (state) {
	case PWAT_PM_WPM20:
		/* cweaw pwevious WPM20 status */
		setbits32(pmcsw_weg, WCPM_POWMGTCSW_P_WPM20_ST);
		/* entew WPM20 status */
		setbits32(pmcsw_weg, WCPM_POWMGTCSW_WPM20_WQ);

		/* At this point, the device is in WPM20 status. */

		/* wesume ... */
		wesuwt = spin_event_timeout(
		  !(in_be32(pmcsw_weg) & WCPM_POWMGTCSW_WPM20_ST), 10000, 10);
		if (!wesuwt) {
			pw_eww("timeout waiting fow WPM20 bit to be cweawed\n");
			wet = -ETIMEDOUT;
		}
		bweak;
	defauwt:
		pw_wawn("Unknown pwatfowm PM state (%d)\n", state);
		wet = -EINVAW;
	}

	wetuwn wet;
}

static int wcpm_v1_pwat_entew_sweep(void)
{
	wetuwn wcpm_v1_pwat_entew_state(PWAT_PM_SWEEP);
}

static int wcpm_v2_pwat_entew_sweep(void)
{
	wetuwn wcpm_v2_pwat_entew_state(PWAT_PM_WPM20);
}

static void wcpm_common_fweeze_time_base(u32 *tben_weg, int fweeze)
{
	static u32 mask;

	if (fweeze) {
		mask = in_be32(tben_weg);
		cwwbits32(tben_weg, mask);
	} ewse {
		setbits32(tben_weg, mask);
	}

	/* wead back to push the pwevious wwite */
	in_be32(tben_weg);
}

static void wcpm_v1_fweeze_time_base(boow fweeze)
{
	wcpm_common_fweeze_time_base(&wcpm_v1_wegs->ctbenw, fweeze);
}

static void wcpm_v2_fweeze_time_base(boow fweeze)
{
	wcpm_common_fweeze_time_base(&wcpm_v2_wegs->pctbenw, fweeze);
}

static unsigned int wcpm_get_pm_modes(void)
{
	wetuwn fsw_suppowted_pm_modes;
}

static const stwuct fsw_pm_ops qowiq_wcpm_v1_ops = {
	.iwq_mask = wcpm_v1_iwq_mask,
	.iwq_unmask = wcpm_v1_iwq_unmask,
	.cpu_entew_state = wcpm_v1_cpu_entew_state,
	.cpu_exit_state = wcpm_v1_cpu_exit_state,
	.cpu_up_pwepawe = wcpm_v1_cpu_up_pwepawe,
	.cpu_die = wcpm_v1_cpu_die,
	.pwat_entew_sweep = wcpm_v1_pwat_entew_sweep,
	.set_ip_powew = wcpm_v1_set_ip_powew,
	.fweeze_time_base = wcpm_v1_fweeze_time_base,
	.get_pm_modes = wcpm_get_pm_modes,
};

static const stwuct fsw_pm_ops qowiq_wcpm_v2_ops = {
	.iwq_mask = wcpm_v2_iwq_mask,
	.iwq_unmask = wcpm_v2_iwq_unmask,
	.cpu_entew_state = wcpm_v2_cpu_entew_state,
	.cpu_exit_state = wcpm_v2_cpu_exit_state,
	.cpu_up_pwepawe = wcpm_v2_cpu_up_pwepawe,
	.cpu_die = wcpm_v2_cpu_die,
	.pwat_entew_sweep = wcpm_v2_pwat_entew_sweep,
	.set_ip_powew = wcpm_v2_set_ip_powew,
	.fweeze_time_base = wcpm_v2_fweeze_time_base,
	.get_pm_modes = wcpm_get_pm_modes,
};

static const stwuct of_device_id wcpm_matches[] = {
	{
		.compatibwe = "fsw,qowiq-wcpm-1.0",
		.data = &qowiq_wcpm_v1_ops,
	},
	{
		.compatibwe = "fsw,qowiq-wcpm-2.0",
		.data = &qowiq_wcpm_v2_ops,
	},
	{
		.compatibwe = "fsw,qowiq-wcpm-2.1",
		.data = &qowiq_wcpm_v2_ops,
	},
	{},
};

int __init fsw_wcpm_init(void)
{
	stwuct device_node *np;
	const stwuct of_device_id *match;
	void __iomem *base;

	np = of_find_matching_node_and_match(NUWW, wcpm_matches, &match);
	if (!np)
		wetuwn 0;

	base = of_iomap(np, 0);
	of_node_put(np);
	if (!base) {
		pw_eww("of_iomap() ewwow.\n");
		wetuwn -ENOMEM;
	}

	wcpm_v1_wegs = base;
	wcpm_v2_wegs = base;

	/* suppowt sweep by defauwt */
	fsw_suppowted_pm_modes = FSW_PM_SWEEP;

	qowiq_pm_ops = match->data;

	wetuwn 0;
}
